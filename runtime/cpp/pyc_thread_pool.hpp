#pragma once

// Fork-join parallel_for used by generated simulators to dispatch independent
// SimObject tick parts across threads.
//
// Contract (mirrors the sequential emission it replaces):
//   pyc_parallel_for(n, fn) invokes fn(i) exactly once for every i in [0, n),
//   and blocks until all invocations return. Calls may nest: a dispatch made
//   from inside a part publishes a new frame on top of the frame list and is
//   served by every thread in the pool, so hierarchical module trees get real
//   concurrency instead of degrading to a sequential loop.
//
// Frames and slot recycling:
//   Frames live in a fixed pool `frames_[]` and are never freed, so a worker
//   holding a stale pointer can never touch dead memory. Slots are handed out
//   from a free stack, so a hot slot is recycled almost immediately. Each
//   publish stamps the frame with a new generation `gen` and resets its claim
//   counter to `(gen << 32) | 0`; a claim therefore carries the generation it
//   belongs to. A worker drops a claim whose generation no longer matches:
//   a generation can only be superseded after it completed, so dropping it
//   cannot lose work. Comparing against a saved base/count instead is NOT
//   safe - a claim taken with an older base is rejected exactly when it lands
//   on the first index of the next generation, silently dropping live work.
//
//   Active frames form a doubly-linked list with `top_` as the newest head;
//   publish pushes to the head and unpublish unlinks from the middle, because
//   sibling nested frames complete in arbitrary order.
//
// Fast paths:
//   * inline-only (PYC_THREADS=0/1, or thread creation failure): run() is a
//     plain loop over fn, with no type erasure, no try/catch and no
//     synchronization - the generated part switch is the only addition over
//     the sequential emission.
//   * workers spin for a bounded window after the last observed activity
//     (PYC_TP_SPIN) before falling back to cvWork_, so a burst of short
//     dispatches costs no futex round trips. The spin loop re-reads the claim
//     counter before touching it, so an exhausted frame costs no atomics.
//   * only the thread that finishes the last index takes mutex_, to notify.
//   * sticky-frame fast dispatch: a tick loop re-issues the same top-level
//     dispatch every cycle. The first such dispatch goes through the full
//     publish/unpublish protocol and its frame is then RETIRED-IN-PLACE as
//     `sticky_` (it stays on the frame list). A later top-level dispatch that
//     finds the pool otherwise idle (tlsDepth == 1, no concurrent dispatch,
//     stickyBusy_ acquired) republishes that frame WITHOUT taking mutex_:
//     plain stores to obj/call, atomic stores to count/remaining, then the
//     generation bump rides the release store of `claim` (workers acquire
//     through claim, so they can never observe the new generation with stale
//     payloads). Parking is prevented from losing wakeups by the `parked_`
//     handshake: workers count themselves about to sleep under mutex_; the
//     fast dispatcher bumps activity_ before checking parked_, and re-notify
//     under mutex_ whenever it sees any parked worker mid-dispatch. Both
//     interleavings of (worker parks / dispatcher checks) are safe: either
//     the worker re-evaluates activity_ under mutex_ and stays awake, or it
//     sleeps and the dispatcher's notify_all wakes it. Anything that fails
//     the fast-path preconditions - nesting, concurrent dispatch, frame pool
//     exhaustion - silently uses the original slow path.
//
// Thread count is resolved once, when the pool is first used, from
// pyc_set_threads() > PYC_THREADS env > hardware_concurrency; 0/1 selects
// inline-only mode (every dispatch runs on the caller thread).
//
// Tasks must not throw: an escaping exception terminates the process (the
// generated simulator kernels are noexcept by construction).

#include <algorithm>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <exception>
#include <functional>
#include <mutex>
#include <thread>
#include <type_traits>
#include <vector>

namespace pyc {
namespace cpp {

namespace detail {

// Opt-in load-balance probe (enabled by PYC_TP_STATS=1 at process start).
// Each thread that executes dispatch parts accumulates its part count and
// busy time; the pool destructor prints a per-thread table. Disabled by
// default and costs one relaxed load per dispatch when off.
struct TpStatSlot {
  std::atomic<unsigned long> parts{0};
  std::atomic<unsigned long long> busyNs{0};
};

inline TpStatSlot tpStatSlots[64];
inline std::atomic<int> tpStatNextSlot{0};
inline std::atomic<bool> tpStatsEnabled{false};

inline TpStatSlot *tpStatSlot() {
  static thread_local TpStatSlot *slot = []() -> TpStatSlot * {
    if (!tpStatsEnabled.load(std::memory_order_relaxed))
      return nullptr;
    int idx = tpStatNextSlot.fetch_add(1, std::memory_order_relaxed);
    return idx < 64 ? &tpStatSlots[idx] : nullptr;
  }();
  return slot;
}

inline unsigned &threadOverride() {
  static unsigned value = 0;
  return value;
}

inline unsigned resolvedThreads() {
  if (unsigned set = threadOverride())
    return set;
  if (const char *env = std::getenv("PYC_THREADS")) {
    int parsed = std::atoi(env);
    if (parsed > 0)
      return static_cast<unsigned>(parsed);
  }
  unsigned hw = std::thread::hardware_concurrency();
  return hw == 0 ? 1u : hw;
}

inline unsigned envUnsigned(const char *name, unsigned fallback) {
  if (const char *e = std::getenv(name)) {
    int v = std::atoi(e);
    if (v >= 0)
      return static_cast<unsigned>(v);
  }
  return fallback;
}

inline void cpuPause() {
#if defined(__x86_64__) || defined(__i386__)
  __builtin_ia32_pause();
#elif defined(__aarch64__) || defined(__arm__)
  __asm__ __volatile__("yield");
#else
  std::this_thread::yield();
#endif
}

// Nesting depth of run() on this thread. 1 = a top-level dispatch (the tick
// loop's own fork-join), >= 2 = nested inside a part. Used only to route
// eligible dispatches to the sticky fast path.
inline unsigned &tlsDepth() {
  static thread_local unsigned depth = 0;
  return depth;
}

// One fork-join dispatch frame. See the file comment for the generation-tagged
// claim counter and the doubly-linked active list. alignas(64) keeps adjacent
// frames off the same cache line.
struct alignas(64) Dispatch {
  void *obj = nullptr;
  void (*call)(void *, unsigned) = nullptr;
  // (gen << 32) | next index to hand out; reset to (gen << 32) on publish.
  std::atomic<std::uint64_t> claim{0};
  std::atomic<unsigned> gen{0};        // current generation
  std::atomic<unsigned> count{0};     // current generation index count
  std::atomic<unsigned> remaining{0}; // indices claimed but not yet finished
  unsigned slot = 0;                  // index in ForkJoinPool::frames_
  Dispatch *newer = nullptr;          // guarded by mutex_
  Dispatch *older = nullptr;          // guarded by mutex_
};

class ForkJoinPool {
public:
  static ForkJoinPool &instance() {
    static ForkJoinPool pool;
    return pool;
  }

  bool hasWorkers() const { return !workers_.empty(); }

  template <class F> void run(unsigned count, F &&fn) {
    if (count == 0)
      return;
    // Inline-only: identical cost to the sequential emission apart from the
    // generated part switch. No type erasure, no synchronization.
    if (!hasWorkers()) {
      invokeAll(count, fn);
      return;
    }
    if (count == 1) {
      fn(0);
      return;
    }
    ++tlsDepth();
    // Top-level dispatch over an idle pool with a retired sticky frame:
    // republish it lock-free instead of the mutex publish/unpublish pair.
    // Main-thread only: the pool creator runs the tick loop, and only its
    // dispatches are semantically top-level. A worker calling run() is by
    // construction nested inside someone's part (its tlsDepth is 1 there, so
    // depth alone cannot tell them apart) and MUST use the slow path: a fast
    // publish on the sticky frame is invisible to other threads while any
    // other frame tops the list, which deadlocks the pool.
    if (fastEnabled_ && std::this_thread::get_id() == mainTid_ && tlsDepth() == 1 &&
        sticky_.load(std::memory_order_acquire) != nullptr &&
        inflightDispatch_.load(std::memory_order_acquire) == 0 &&
        stickyBusy_.exchange(true, std::memory_order_acq_rel)) {
      fastDispatch(sticky_.load(std::memory_order_relaxed), count, fn);
      --tlsDepth();
      return;
    }
    {
      Dispatch *f = publish(count, fn);
      if (!f) { // frame pool exhausted: degrade to inline rather than drop work.
        --tlsDepth();
        invokeAll(count, fn);
        return;
      }
      inflightDispatch_.fetch_add(1, std::memory_order_release);
      participate(f);
      bool keep;
      {
        std::lock_guard<std::mutex> lock(mutex_);
        // Retire-in-place as the sticky frame when this was the pool's only
        // dispatch: the tick loop re-issues it every cycle, so keeping it
        // published lets later cycles take the lock-free path above.
        keep = std::this_thread::get_id() == mainTid_ && tlsDepth() == 1 &&
               sticky_.load(std::memory_order_relaxed) == nullptr && active_ == 1;
        if (keep)
          sticky_.store(f, std::memory_order_release);
      }
      if (!keep)
        unpublish(f);
      inflightDispatch_.fetch_sub(1, std::memory_order_release);
    }
    --tlsDepth();
  }

private:
  static constexpr unsigned kMaxFrames = 64;
  static constexpr std::uint64_t kIndexMask = 0xffffffffULL;

  template <class F> static void invokeAll(unsigned count, F &fn) {
    for (unsigned i = 0; i < count; ++i)
      fn(i);
  }

  template <class Fn> static void trampoline(void *p, unsigned i) {
    (*static_cast<Fn *>(p))(i);
  }

  static bool complete(const Dispatch *f) {
    return f->remaining.load(std::memory_order_acquire) == 0;
  }

  unsigned spinBudget() const { return spin_; }
  unsigned maxFrames() const { return maxFrames_; }

  // Lock-free republish of a retired sticky frame. Ordering: obj/call are
  // plain (only reachable after a successful claim of the new generation,
  // which acquires everything released below); count/remaining are atomic
  // stores sequenced before the release store of claim, so a worker that
  // reads an old claim cannot latch onto new payloads, and one that reads
  // the new claim sees the new count. No worker touches this frame between
  // generations: a retired generation has all indices finished and workers
  // only reach runOne/obj/call through a successful new-generation claim.
  template <class F> void fastDispatch(Dispatch *f, unsigned count, F &fn) {
    using Fn = typename std::remove_reference<F>::type;
    const unsigned g = f->gen.load(std::memory_order_relaxed) + 1;
    f->obj = const_cast<void *>(static_cast<const void *>(&fn));
    f->call = &trampoline<Fn>;
    f->count.store(count, std::memory_order_relaxed);
    f->remaining.store(count, std::memory_order_release);
    f->gen.store(g, std::memory_order_relaxed);
    f->claim.store(static_cast<std::uint64_t>(g) << 32,
                   std::memory_order_release);
    inflightDispatch_.fetch_add(1, std::memory_order_release);
    // Wake parked workers. activity_ is bumped BEFORE the parked_ check, so a
    // worker that has not slept yet re-evaluates activity_ under mutex_ and
    // stays awake; one that did sleep is caught by notify_all below.
    activity_.fetch_add(1, std::memory_order_release);
    if (parked_.load(std::memory_order_acquire) != 0) {
      std::lock_guard<std::mutex> lock(mutex_);
      cvWork_.notify_all();
    }
    participateFast(f);
    inflightDispatch_.fetch_sub(1, std::memory_order_release);
    stickyBusy_.store(false, std::memory_order_release);
  }

  // Dispatcher side of a fast dispatch: help with the frame, spin for
  // completion, and keep parked workers from being forgotten: any worker that
  // parks mid-dispatch is re-notified under mutex_.
  void participateFast(Dispatch *f) {
    TpStatSlot *st = tpStatSlot();
    int spins = static_cast<int>(spinBudget());
    int sinceParkCheck = 0;
    for (;;) {
      Dispatch *t = nullptr;
      unsigned localIdx = 0;
      if (tryClaim(t, localIdx)) {
        runOne(t, localIdx, st);
        spins = static_cast<int>(spinBudget());
        continue;
      }
      if (complete(f))
        return;
      if (--spins > 0) {
        if (++sinceParkCheck >= 64) {
          sinceParkCheck = 0;
          if (parked_.load(std::memory_order_acquire) != 0) {
            std::lock_guard<std::mutex> lock(mutex_);
            cvWork_.notify_all();
          }
        }
        cpuPause();
        continue;
      }
      std::unique_lock<std::mutex> lock(mutex_);
      if (complete(f))
        return;
      cvDone_.wait(lock, [&] { return complete(f); });
      return;
    }
  }

  template <class F> Dispatch *publish(unsigned count, F &fn) {
    using Fn = typename std::remove_reference<F>::type;
    std::lock_guard<std::mutex> lock(mutex_);
    if (active_ >= maxFrames())
      return nullptr;
    Dispatch *f = &frames_[free_[--freeCount_]];
    const unsigned g = f->gen.load(std::memory_order_relaxed) + 1;
    ++active_;
    f->obj = const_cast<void *>(static_cast<const void *>(&fn));
    f->call = &trampoline<Fn>;
    f->count.store(count, std::memory_order_relaxed);
    f->remaining.store(count, std::memory_order_relaxed);
    f->gen.store(g, std::memory_order_relaxed);
    f->newer = nullptr;
    f->older = top_.load(std::memory_order_relaxed);
    if (f->older)
      f->older->newer = f;
    // Release store publishes {obj, call, count, gen} and makes the frame
    // claimable; workers acquire through claim_.
    f->claim.store(static_cast<std::uint64_t>(g) << 32, std::memory_order_release);
    top_.store(f, std::memory_order_release);
    activity_.fetch_add(1, std::memory_order_release);
    cvWork_.notify_all();
    return f;
  }

  void unpublish(Dispatch *f) {
    std::unique_lock<std::mutex> lock(mutex_);
    if (f->newer)
      f->newer->older = f->older;
    else
      top_.store(f->older, std::memory_order_release);
    if (f->older)
      f->older->newer = f->newer;
    f->newer = nullptr;
    f->older = nullptr;
    --active_;
    free_[freeCount_++] = f->slot;
    // Parked workers must see the drop: without this, a worker that fell
    // asleep after the last publish would never notice the list changed and
    // an outer dispatch would wait for help that never arrives.
    activity_.fetch_add(1, std::memory_order_release);
    lock.unlock();
    cvWork_.notify_all();
  }

  // Try to claim one index from the innermost active frame. Returns false
  // when there is no frame, the frame is exhausted, or the claim belongs to a
  // superseded generation (safe to drop: superseded implies completed).
  bool tryClaim(Dispatch *&out, unsigned &localIdx) {
    Dispatch *t = top_.load(std::memory_order_acquire);
    if (!t)
      return false;
    // Cheap pre-checks that consume nothing, so a spinning thread does not
    // hammer the claim counter on an exhausted frame.
    const std::uint64_t cur = t->claim.load(std::memory_order_acquire);
    const unsigned g = static_cast<unsigned>(cur >> 32);
    if (g != t->gen.load(std::memory_order_acquire))
      return false; // superseded generation: nothing safe to claim right now
    if ((cur & kIndexMask) >= t->count.load(std::memory_order_acquire))
      return false; // exhausted: no atomic RMW, spinners stay cheap

    const std::uint64_t v = t->claim.fetch_add(1, std::memory_order_acq_rel);
    // Compare against the generation read AFTER the claim, never the one read
    // before it: if the slot was recycled in between, the claim belongs to the
    // new generation and is live work. Dropping it by comparing against the
    // pre-read generation would consume a real index and lose it.
    if (static_cast<unsigned>(v >> 32) != t->gen.load(std::memory_order_acquire))
      return false; // superseded => already completed, so dropping is safe
    const unsigned idx = static_cast<unsigned>(v & kIndexMask);
    if (idx >= t->count.load(std::memory_order_acquire))
      return false; // beyond the generation: not real work
    out = t;
    localIdx = idx;
    return true;
  }

  void runOne(Dispatch *f, unsigned localIdx, TpStatSlot *st) {
    const auto t0 =
        st ? std::chrono::steady_clock::now() : std::chrono::steady_clock::time_point{};
    f->call(f->obj, localIdx);
    if (st) {
      st->busyNs.fetch_add(
          static_cast<unsigned long long>(
              std::chrono::duration_cast<std::chrono::nanoseconds>(
                  std::chrono::steady_clock::now() - t0)
                  .count()),
          std::memory_order_relaxed);
      st->parts.fetch_add(1, std::memory_order_relaxed);
    }
    // Notify under mutex_: the waiter evaluates its predicate while holding
    // mutex_, so waking after the decrement cannot be lost.
    if (f->remaining.fetch_sub(1, std::memory_order_acq_rel) == 1) {
      std::lock_guard<std::mutex> lock(mutex_);
      cvDone_.notify_all();
    }
  }

  // Dispatcher side: help with whatever is on top (possibly a nested frame
  // published by another thread), then wait for `f` to finish.
  void participate(Dispatch *f) {
    TpStatSlot *st = tpStatSlot();
    int spins = static_cast<int>(spinBudget());
    while (spins-- > 0) {
      Dispatch *t = nullptr;
      unsigned localIdx = 0;
      if (tryClaim(t, localIdx)) {
        runOne(t, localIdx, st);
        spins = static_cast<int>(spinBudget());
        continue;
      }
      if (complete(f))
        return;
      cpuPause();
    }
    std::unique_lock<std::mutex> lock(mutex_);
    cvDone_.wait(lock, [&] { return complete(f); });
  }

  void workerLoop() {
    TpStatSlot *st = tpStatSlot();
    unsigned long long seen = activity_.load(std::memory_order_relaxed);
    int spins = static_cast<int>(spinBudget());
    for (;;) {
      Dispatch *t = nullptr;
      unsigned localIdx = 0;
      if (tryClaim(t, localIdx)) {
        runOne(t, localIdx, st);
        spins = static_cast<int>(spinBudget());
        continue;
      }
      const unsigned long long now = activity_.load(std::memory_order_relaxed);
      if (now != seen) {
        seen = now;
        spins = static_cast<int>(spinBudget());
        continue;
      }
      if (spins-- > 0) {
        cpuPause();
        continue;
      }
      {
        // Announce the park BEFORE taking mutex_: fast-path dispatchers
        // check parked_ after bumping activity_, so this thread is either
        // seen here (and gets the notify below) or re-evaluates activity_
        // under mutex_ and never sleeps.
        parked_.fetch_add(1, std::memory_order_release);
        std::unique_lock<std::mutex> lock(mutex_);
        if (shutdown_) {
          parked_.fetch_sub(1, std::memory_order_release);
          return;
        }
        seen = activity_.load(std::memory_order_relaxed);
        // Sleep only on activity changes: publish and unpublish both bump
        // activity_, so a parked worker cannot miss a frame or wait forever
        // on one that already retired.
        cvWork_.wait(lock, [&] {
          return shutdown_ ||
                 activity_.load(std::memory_order_relaxed) != seen;
        });
        parked_.fetch_sub(1, std::memory_order_acquire);
        if (shutdown_)
          return;
        seen = activity_.load(std::memory_order_relaxed);
        spins = static_cast<int>(spinBudget());
      }
    }
  }

  ForkJoinPool()
      : spin_(envUnsigned("PYC_TP_SPIN", 2000)),
        maxFrames_(std::min(kMaxFrames, std::max(1u, envUnsigned("PYC_TP_MAX_DEPTH", 32)))) {
    fastEnabled_ = envUnsigned("PYC_TP_FAST", 1) != 0;
    for (unsigned i = 0; i < kMaxFrames; ++i) {
      frames_[i].slot = i;
      free_[i] = i;
    }
    if (const char *e = std::getenv("PYC_TP_STATS"))
      tpStatsEnabled.store(e[0] == '1', std::memory_order_relaxed);
    unsigned threads = resolvedThreads();
    if (threads <= 1)
      return;
    try {
      workers_.reserve(threads);
      for (unsigned t = 0; t < threads; ++t)
        workers_.emplace_back([this] { workerLoop(); });
    } catch (...) {
      // Thread creation failure: retire any partial workers and degrade to
      // inline-only execution (hasWorkers() == false routes run() inline).
      {
        std::lock_guard<std::mutex> lock(mutex_);
        shutdown_ = true;
      }
      cvWork_.notify_all();
      for (auto &w : workers_)
        if (w.joinable())
          w.join();
      workers_.clear();
    }
  }

  ~ForkJoinPool() {
    {
      std::lock_guard<std::mutex> lock(mutex_);
      shutdown_ = true;
    }
    cvWork_.notify_all();
    for (auto &w : workers_)
      if (w.joinable())
        w.join();
    if (tpStatsEnabled.load(std::memory_order_relaxed)) {
      unsigned long long total = 0;
      for (const auto &s : tpStatSlots)
        total += s.busyNs.load(std::memory_order_relaxed);
      std::fprintf(stderr,
                   "PYC_TP_STATS: total busy = %.1f ms across %d threads\n",
                   static_cast<double>(total) / 1e6,
                   tpStatNextSlot.load(std::memory_order_relaxed));
      for (int i = 0; i < 64; ++i) {
        const auto &s = tpStatSlots[i];
        unsigned long p = s.parts.load(std::memory_order_relaxed);
        unsigned long long b = s.busyNs.load(std::memory_order_relaxed);
        if (!p)
          continue;
        std::fprintf(stderr,
                     "PYC_TP_STATS: thread%-2d parts=%-6lu busy=%7.1f ms share=%5.1f%%\n",
                     i, p, static_cast<double>(b) / 1e6,
                     total ? 100.0 * static_cast<double>(b) / static_cast<double>(total) : 0.0);
      }
    }
  }

  unsigned spin_;
  unsigned maxFrames_;
  bool fastEnabled_ = true; // PYC_TP_FAST=0 disables the sticky fast path
  const std::thread::id mainTid_ = std::this_thread::get_id(); // tick-loop thread
  std::mutex mutex_;
  std::condition_variable cvWork_; // wakes parked workers on activity changes
  std::condition_variable cvDone_; // dispatcher waits here for completion
  std::atomic<Dispatch *> top_{nullptr};
  std::atomic<unsigned long long> activity_{0}; // bumped on publish/unpublish
  // Sticky fast-path state. sticky_ stores under mutex_ with release and
  // loads with acquire (nullptr -> frame is a one-way transition, so a stale
  // nullptr read merely misses the fast path).
  std::atomic<Dispatch *> sticky_{nullptr};     // retired-in-place fast frame
  std::atomic<bool> stickyBusy_{false};     // exclusive fast-dispatch holder
  std::atomic<unsigned> inflightDispatch_{0}; // slow+fast dispatches in flight
  std::atomic<unsigned> parked_{0};         // workers inside cvWork_ wait
  unsigned free_[kMaxFrames];                  // free-slot stack, mutex_-guarded
  unsigned freeCount_ = kMaxFrames;             // guarded by mutex_
  unsigned active_ = 0;                         // guarded by mutex_
  bool shutdown_ = false;                       // guarded by mutex_
  Dispatch frames_[kMaxFrames];
  std::vector<std::thread> workers_;
};

} // namespace detail

/// Override PYC_THREADS for this process (0/1 = run everything inline).
/// Must be called before the first dispatch: the pool's thread count is fixed
/// when the pool is created.
inline void pyc_set_threads(unsigned threads) {
  detail::threadOverride() = threads;
}

/// Number of threads the pool will use (0 = inline-only).
inline unsigned pyc_threads() {
  unsigned resolved = detail::resolvedThreads();
  return resolved <= 1 ? 0u : resolved;
}

/// Fork-join parallel for: fn(i) runs exactly once per index on at most
/// pyc_threads() threads; blocks until complete. Nested calls publish a new
/// frame and are served by the whole pool.
template <class F>
inline void pyc_parallel_for(unsigned count, F &&fn) {
  if (count == 0)
    return;
  detail::ForkJoinPool::instance().run(count, fn);
}

} // namespace cpp
} // namespace pyc

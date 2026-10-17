#pragma once

// Fork-join parallel_for used by generated simulators to dispatch independent
// SimObject tick parts across threads.
//
// Contract (mirrors the sequential emission it replaces):
//   pyc_parallel_for(n, fn) invokes fn(i) exactly once for every i in [0, n),
//   blocks until all invocations return, and is safe to nest: a call made from
//   inside a worker (or when the pool runs inline) degrades to a sequential
//   loop, so nested module hierarchies never deadlock.
//
// Synchronization design (generation/epoch based):
//   Each dispatch publishes under mutex_ a fresh epoch with its task pointer,
//   claim counter and completion counter. Workers block on cvWork_ until the
//   epoch *changes*, consume it, and drain claims until the claim counter is
//   exhausted. When every index finished, the dispatcher retires the dispatch
//   (clears the task, bumps the epoch again) and notifies cvWork_ so workers
//   fall back to sleep. Bumping the epoch on retire is what keeps workers from
//   busy-spinning on "task_ != nullptr" between the last completion and the
//   retire — under a pointer-only predicate, spinning workers can starve the
//   dispatcher's mutex reacquisition and livelock the pool permanently.
//
// Thread count is resolved once, when the pool is first used, from
// pyc_set_threads() > PYC_THREADS env > hardware_concurrency; 0/1 selects
// inline-only mode (every dispatch runs on the caller thread).
//
// Tasks must not throw: an escaping exception terminates the process (the
// generated simulator kernels are noexcept by construction).

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <functional>
#include <mutex>
#include <thread>
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

class ForkJoinPool {
public:
  static ForkJoinPool &instance() {
    static ForkJoinPool pool;
    return pool;
  }

  void run(unsigned count, const std::function<void(unsigned)> &fn) {
    if (count <= 1 || workers_.empty() || workerMarker()) {
      for (unsigned i = 0; i < count; ++i)
        call(fn, i);
      return;
    }
    // Mark the caller as "inside a dispatch" so parallel_for calls nested in
    // fn (which may execute here on the caller thread) run inline instead of
    // overwriting the single dispatch slot while workers still use it.
    workerMarker() = true;
    {
      std::lock_guard<std::mutex> lock(mutex_);
      task_.store(&fn, std::memory_order_relaxed);
      count_.store(count, std::memory_order_relaxed);
      next_.store(0, std::memory_order_relaxed);
      done_.store(0, std::memory_order_relaxed);
      ++epoch_; // publish the dispatch
    }
    cvWork_.notify_all();
    drain(); // caller participates in index claiming
    {
      std::unique_lock<std::mutex> lock(mutex_);
      cvDone_.wait(lock, [&] {
        return done_.load(std::memory_order_acquire) >= count;
      });
      // done_ == count implies every claimed index finished its fn call, so no
      // worker can still dereference task_; retire the dispatch and move the
      // epoch so workers that consumed it fall back to sleep instead of
      // spinning on stale state.
      task_.store(nullptr, std::memory_order_relaxed);
      count_.store(0, std::memory_order_relaxed);
      ++epoch_; // retire
    }
    cvWork_.notify_all();
    workerMarker() = false;
  }

private:
  static void call(const std::function<void(unsigned)> &fn, unsigned i) {
    try {
      fn(i);
    } catch (...) {
      std::terminate();
    }
  }

  static bool &workerMarker() {
    static thread_local bool m = false;
    return m;
  }

  void drain() {
    TpStatSlot *st = tpStatSlot();
    for (;;) {
      // Claim an index under the dispatch lock so {task_, next_, count_} are
      // read as one consistent snapshot. A lock-free fetch_add can straddle a
      // dispatch boundary (claim from the freshly reset counter, bound check
      // against the retired count_) and silently swallow an index, hanging the
      // dispatcher's completion wait; the mutex claim makes that impossible.
      // The fn call itself stays outside the lock.
      const std::function<void(unsigned)> *fn = nullptr;
      unsigned index = 0;
      unsigned bound = 0;
      {
        std::lock_guard<std::mutex> lock(mutex_);
        if (task_ == nullptr)
          return; // no active dispatch
        index = next_.fetch_add(1, std::memory_order_relaxed);
        if (index >= count_)
          return; // dispatch exhausted (monotonic claim counter)
        fn = task_;
        bound = count_;
      }
      const auto t0 =
          st ? std::chrono::steady_clock::now() : std::chrono::steady_clock::time_point{};
      call(*fn, index);
      if (st) {
        st->busyNs.fetch_add(
            static_cast<unsigned long long>(
                std::chrono::duration_cast<std::chrono::nanoseconds>(
                    std::chrono::steady_clock::now() - t0)
                    .count()),
            std::memory_order_relaxed);
        st->parts.fetch_add(1, std::memory_order_relaxed);
      }
      {
        // Completion must be published under the dispatch lock. The waiter's
        // cvDone_ predicate is only safe against lost wakeups if every change
        // of done_ happens while holding mutex_: an unlocked increment can
        // slip between the waiter's predicate check and its internal sleep,
        // firing notify into the void and hanging the dispatcher forever.
        std::lock_guard<std::mutex> lock(mutex_);
        if (done_.fetch_add(1, std::memory_order_acq_rel) + 1 == bound)
          cvDone_.notify_all();
      }
    }
  }

  void workerLoop() {
    unsigned seenEpoch = epoch_.load(std::memory_order_relaxed);
    for (;;) {
      {
        std::unique_lock<std::mutex> lock(mutex_);
        cvWork_.wait(lock, [&] { return epoch_ != seenEpoch || shutdown_; });
        if (shutdown_)
          return;
        seenEpoch = epoch_; // consume the published (or retired) epoch
      }
      drain();
    }
  }

  ForkJoinPool() {
    if (const char *e = std::getenv("PYC_TP_STATS"))
      tpStatsEnabled.store(e[0] == '1', std::memory_order_relaxed);
    unsigned threads = resolvedThreads();
    if (threads <= 1)
      return;
    try {
      workers_.reserve(threads);
      for (unsigned t = 0; t < threads; ++t)
        workers_.emplace_back([this] {
          workerMarker() = true;
          workerLoop();
        });
    } catch (...) {
      // Thread creation failure: retire any partial workers and degrade to
      // inline-only execution (workers_.empty() routes run() inline).
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

  std::mutex mutex_;
  std::condition_variable cvWork_; // wakes workers on epoch changes
  std::condition_variable cvDone_; // caller waits here for completion
  std::atomic<const std::function<void(unsigned)> *> task_{nullptr};
  std::atomic<unsigned> count_{0};
  std::atomic<unsigned> epoch_{0}; // bumped on dispatch publish and retire
  std::atomic<unsigned> next_{0};
  std::atomic<unsigned> done_{0};
  bool shutdown_ = false;
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
/// pyc_threads() threads; blocks until complete; nested calls run inline.
inline void pyc_parallel_for(unsigned count,
                             const std::function<void(unsigned)> &fn) {
  if (count == 0)
    return;
  detail::ForkJoinPool::instance().run(count, fn);
}

} // namespace cpp
} // namespace pyc

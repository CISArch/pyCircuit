// DelayBank / VecBank equivalence: drive mixed designs through the per-object
// primitives and the bank implementations with identical stimuli; checksums
// and wake bitmaps must match exactly.
#include <cstdio>
#include <cstdint>
#include <random>
#include <vector>

#include "pyc_bits.hpp"
#include "pyc_primitives.hpp"
#include "pyc_seq_bank_ext.hpp"

using namespace pyc::cpp;

namespace {
constexpr unsigned kDelayLanes = 70;   // crosses the 64-bit bitmap boundary
constexpr unsigned kVecLanes = 40;
constexpr unsigned kCycles = 4000;

struct Sum {
  std::uint64_t v = 1469598103934665603ull;
  void mix(std::uint64_t x) { v ^= x; v *= 1099511628211ull; }
};
}  // namespace

int main() {
  std::mt19937_64 rng(999);

  // ---- DelayBank vs per-object pyc_delay_line ----
  Wire<1> clk{0}, rst{0}, en{1};
  std::vector<Wire<8>> dK(kDelayLanes), initK(kDelayLanes), qRef(kDelayLanes), qBank(kDelayLanes);
  std::vector<pyc_delay_line<8, 4>> ref;
  ref.reserve(kDelayLanes);
  std::vector<pyc_delay_line<8, 4>*> refPtr(kDelayLanes);
  DelayBank<8> bank;
  for (unsigned i = 0; i < kDelayLanes; ++i) {
    dK[i] = Wire<8>{i * 3 + 1};
    initK[i] = Wire<8>{0};
    qRef[i] = Wire<8>{0};
    qBank[i] = Wire<8>{0};
    ref.emplace_back(clk, rst, en, dK[i], initK[i], qRef[i]);
    refPtr[i] = &ref.back();
    bank.add_lane({&qBank[i], &dK[i], &rst, &en, &initK[i], 4u});
  }

  // VecBank vs per-object pyc_vec_reg<VecT>
  using VecT = Wire<24>;  // standalone vector-like Bits type for the test
  std::vector<Wire<24>> dv(kVecLanes), initv(kVecLanes), qvRef(kVecLanes), qvBank(kVecLanes);
  std::vector<pyc_vec_reg<Wire<24>>> vref;
  vref.reserve(kVecLanes);
  VecBank<Wire<24>> vbank;
  for (unsigned i = 0; i < kVecLanes; ++i) {
    dv[i] = Wire<24>{i * 11 + 2};
    initv[i] = Wire<24>{0};
    qvRef[i] = Wire<24>{0};
    qvBank[i] = Wire<24>{0};
    vref.emplace_back(clk, rst, en, dv[i], initv[i], qvRef[i]);
    vbank.add_lane({&qvBank[i], &dv[i], &rst, &en, &initv[i]});
  }

  bool refPrev = false, bankPrev = false, vrefPrev = false, vbankPrev = false;
  Sum sRef, sBank, sVRef, sVBank;

  for (unsigned c = 0; c < kCycles; ++c) {
    const bool now = (c % 3) != 0;
    clk = Wire<1>{now ? 1u : 0u};
    rst = Wire<1>{(c % 89) == 7 ? 1u : 0u};
    en = Wire<1>{(c % 13) == 9 ? 0u : 1u};
    for (unsigned i = 0; i < kDelayLanes; ++i)
      if (rng() % 3 == 0) dK[i] = Wire<8>{rng() & 0xFFu};
    for (unsigned i = 0; i < kVecLanes; ++i)
      if (rng() % 4 == 0) dv[i] = Wire<24>{rng() & 0xFFFFFFu};

    const bool rise = (!refPrev) & now, fall = refPrev & (!now);
    refPrev = now;
    // --- reference ---
    if (rise) {
      for (auto &r : ref) r.posedge_tick_compute();
      for (auto &r : vref) r.posedge_tick_compute();
    } else if (fall) {
      for (auto &r : ref) r.negedge_update();
      for (auto &r : vref) r.negedge_update();
    } else {
      for (auto &r : ref) r.tick_compute();
      for (auto &r : vref) r.tick_compute();
    }
    for (unsigned i = 0; i < kDelayLanes; ++i) {
      refPtr[i]->tick_commit();
      sRef.mix(qRef[i].value() * (i + 1) + refPtr[i]->tap(2).value());
    }
    for (unsigned i = 0; i < kVecLanes; ++i) {
      vref[i].tick_commit();
      sVRef.mix(qvRef[i].value() + i);
    }

    // --- bank path ---
    const bool brise = (!bankPrev) & now, bfall = bankPrev & (!now);
    bankPrev = now; vbankPrev = now;
    if (brise) {
      bank.compute_rise(); vbank.compute_rise();
    } else if (bfall) {
      bank.negedge(); vbank.negedge();
    } else {
      bank.compute_generic(now); vbank.compute_generic(now);
    }
    auto res = bank.commit();
    const auto &tail = res.tailDirty;
    const auto &adv = res.advanced;
    for (unsigned i = 0; i < kDelayLanes; ++i) {
      sBank.mix(qBank[i].value() * (i + 1) + bank.lane_tap_next(i, 2).value());
    }
    (void)tail; (void)adv;
    vbank.commit();
    for (unsigned i = 0; i < kVecLanes; ++i) sVBank.mix(qvBank[i].value() + i);

    if (sRef.v != sBank.v) {
      std::fprintf(stderr, "DELAY MISMATCH cycle %u\n", c);
      return 1;
    }
    if (sVRef.v != sVBank.v) {
      std::fprintf(stderr, "VEC MISMATCH cycle %u\n", c);
      return 1;
    }
  }

  // Wake-precision: after one more edge, per-lane advanced/dirty bitmaps must
  // match per-object pending/changed exactly.
  clk = Wire<1>{0}; bank.commit(); for (auto &r : ref) r.tick_commit();
  clk = Wire<1>{1};
  for (auto &r : ref) r.posedge_tick_compute();
  bank.compute_rise();
  auto res = bank.commit();
  for (unsigned i = 0; i < kDelayLanes; ++i) {
    const bool refPending = refPtr[i]->has_pending();
    const bool changed = refPtr[i]->tick_commit();
    const bool adv = (res.advanced[i >> 6] >> (i & 63)) & 1u;
    const bool dirty = (res.tailDirty[i >> 6] >> (i & 63)) & 1u;
    if (refPending != adv || changed != dirty) {
      std::fprintf(stderr, "DELAY WAKE MISMATCH lane %u (pending=%d adv=%d "
                   "changed=%d dirty=%d)\n", i, (int)refPending, (int)adv,
                   (int)changed, (int)dirty);
      return 1;
    }
  }

  std::printf("delay/vec bank equivalence verified: %u+%u lanes, %d cycles, "
              "checksum=%llu\n", kDelayLanes, kVecLanes, kCycles,
              (unsigned long long)sRef.v);
  return 0;
}

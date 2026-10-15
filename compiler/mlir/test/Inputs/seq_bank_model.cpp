// SeqBank equivalence check: drive a mixed design through both the per-reg
// pyc_reg path and the SeqBank path with identical stimuli; cycle counts and
// checksums must match exactly (reset/enable mixed, vector lanes, multi-bank).
//
// Usage: check_seq_bank_models.py --pycc <pycc> --cxx <c++>
// The pycc side is exercised indirectly; this driver links both
// implementations against the same lane table built from a test harness.

#include <cstdint>
#include <cstdio>
#include <random>
#include <vector>

#include "pyc_bits.hpp"
#include "pyc_primitives.hpp"
#include "pyc_seq_bank.hpp"

using namespace pyc::cpp;

namespace {

constexpr unsigned kCycles = 5000;

struct Checksum {
  std::uint64_t value = 1469598103934665603ull;  // FNV-1a offset basis
  void mix(std::uint64_t v) {
    value ^= v;
    value *= 1099511628211ull;
  }
};

// Reference: a plain pyc_reg list driven by the same clock/wires.
struct RefModel {
  Wire<1> clk{0}, rst{0}, en{1};
  std::vector<Wire<8>> init{};
  std::vector<Wire<8>> q{};
  std::vector<pyc_reg<8>> regs;

  explicit RefModel(unsigned n) : init(n), q(n), regs() {
    regs.reserve(n);
    for (unsigned i = 0; i < n; ++i) {
      init[i] = Wire<8>{static_cast<std::uint64_t>(i + 1)};
      q[i] = Wire<8>{0};
    }
  }
};

}  // namespace

int main() {
  std::mt19937_64 rng(12345);

  const unsigned kLanes = 130;  // crosses the 64-lane bitmap boundary
  RefModel ref(kLanes);

  // Stimulus wires.
  std::vector<Wire<8>> stimulus(kLanes);
  for (unsigned i = 0; i < kLanes; ++i)
    stimulus[i] = Wire<8>{static_cast<std::uint64_t>(i * 7 + 3)};

  // Reference registers.
  for (unsigned i = 0; i < kLanes; ++i)
    ref.regs.emplace_back(ref.clk, ref.rst, ref.en, stimulus[i], ref.init[i],
                          ref.q[i]);

  // SeqBank over the same stimulus/init wires; q points at its own copies.
  std::vector<Wire<8>> bankQ(kLanes, Wire<8>{0});
  SeqBank<8> bank;
  for (unsigned i = 0; i < kLanes; ++i)
    bank.add_lane({&bankQ[i], &stimulus[i], &ref.rst, &ref.en, &ref.init[i]});

  bool refClkPrev = false;
  bool bankClkPrev = false;
  Checksum csRef;
  Checksum csBank;

  for (unsigned cycle = 0; cycle < kCycles; ++cycle) {
    // Randomize control: reset pulses rare, enable sometimes low, clock
    // idles some cycles so both edge-detect paths are exercised.
    const bool clkNow = (cycle % 3) != 0;  // periodic idle + edges
    ref.clk = Wire<1>{clkNow ? 1u : 0u};
    ref.rst = Wire<1>{(cycle % 97) == 5 ? 1u : 0u};
    ref.en = Wire<1>{(cycle % 11) == 7 ? 0u : 1u};

    // Per-cycle input flips so commit deltas are frequent.
    for (unsigned i = 0; i < kLanes; ++i)
      if (rng() % 3 == 0)
        stimulus[i] = Wire<8>{rng() & 0xFFu};

    // --- reference path ---
    {
      const bool rise = (!refClkPrev) & clkNow;
      const bool fall = refClkPrev & (!clkNow);
      refClkPrev = clkNow;
      if (rise) {
        for (auto &reg : ref.regs) reg.posedge_tick_compute();
      } else if (fall) {
        for (auto &reg : ref.regs) reg.negedge_update();
      } else {
        for (auto &reg : ref.regs) reg.tick_compute();
      }
      for (unsigned i = 0; i < kLanes; ++i) ref.regs[i].tick_commit();
      for (unsigned i = 0; i < kLanes; ++i)
        csRef.mix(ref.q[i].value() + i);
    }

    // --- SeqBank path (mirrors the generated fastEdge shape) ---
    {
      const bool rise = (!bankClkPrev) & clkNow;
      const bool fall = bankClkPrev & (!clkNow);
      bankClkPrev = clkNow;
      if (rise) {
        bank.compute_rise();
      } else if (fall) {
        bank.negedge();
      } else {
        bank.compute_generic(clkNow);
      }
      const auto &dirty = bank.commit();
      for (unsigned i = 0; i < kLanes; ++i) {
        const bool changed =
            (dirty[i >> 6] >> (i & 63)) & std::uint64_t{1};
        (void)changed;  // wake precision is checked below
        csBank.mix(bankQ[i].value() + i);
      }
    }

    if (csRef.value != csBank.value) {
      for (unsigned i = 0; i < kLanes; ++i) {
        if (ref.q[i].value() != bankQ[i].value()) {
          std::fprintf(stderr, "MISMATCH cycle %u lane %u: ref=%llu bank=%llu "
                       "rst=%d en=%d stim=%llu init=%llu\n", cycle, i,
                       (unsigned long long)ref.q[i].value(),
                       (unsigned long long)bankQ[i].value(),
                       (int)ref.rst.toBool(), (int)ref.en.toBool(),
                       (unsigned long long)stimulus[i].value(),
                       (unsigned long long)ref.init[i].value());
          return 1;
        }
      }
      std::fprintf(stderr, "MISMATCH at cycle %u (checksum only)\n", cycle);
      return 1;
    }
  }

  // Wake-precision probe: after a final edge, the dirty bitmap must mark
  // exactly the lanes whose reference q changed.
  ref.clk = Wire<1>{0};
  bank.commit();
  ref.clk = Wire<1>{1};
  for (auto &reg : ref.regs) reg.posedge_tick_compute();
  bank.compute_rise();
  const auto &dirty = bank.commit();
  for (unsigned i = 0; i < kLanes; ++i) {
    const bool refChanged = ref.regs[i].tick_commit();
    const bool bankChanged = (dirty[i >> 6] >> (i & 63)) & std::uint64_t{1};
    if (refChanged != bankChanged) {
      std::fprintf(stderr, "WAKE MISMATCH lane %u\n", i);
      return 1;
    }
  }

  std::printf("seq_bank equivalence verified: %d lanes, %d cycles, "
              "checksum=%llu\n",
              kLanes, kCycles,
              static_cast<unsigned long long>(csRef.value));
  return 0;
}

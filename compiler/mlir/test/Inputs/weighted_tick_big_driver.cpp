// Load driver for weighted_tick_big: verifies the XOR aggregate of every
// accumulator against its closed form and prints per-phase wall time so the
// sequential comb phase and the parallel tick phase can be read separately.
//   light i (i < nLight):            acc += 1 + i      per rising edge
//   nest  j (offset nLight):         acc += 1 + j + 3
//   heavy k (offset nLight+nNest):   q_m += (m+1) for m in [0,24), output =
//                                    (XOR_m q_m) ^ (1 + global index)
#include "weighted_tick_big.cpp"

#include <chrono>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

namespace {

using Dut = pyc::gen::weighted_tick_big;

constexpr unsigned kNLight = 1200;
constexpr unsigned kNNest = 12;
constexpr unsigned kNHeavy = 400;

using Clock = std::chrono::steady_clock;

} // namespace

int main(int argc, char **argv) {
  const unsigned kTicks = argc > 1 ? static_cast<unsigned>(std::atoi(argv[1]))
                                   : 20000u;
  Dut dut;
  dut.clk = pyc::cpp::Wire<1>(0);
  dut.rst = pyc::cpp::Wire<1>(0);
  dut.incr = pyc::cpp::Wire<8>(1);
  dut.comb();

  double combMs = 0.0, tickMs = 0.0;
  const auto t0 = Clock::now();
  for (unsigned c = 0; c < kTicks; ++c) {
    for (int phase = 0; phase < 2; ++phase) {
      dut.clk = pyc::cpp::Wire<1>(phase == 0 ? 1 : 0);
      auto a = Clock::now();
      dut.comb();
      auto b = Clock::now();
      dut.tick();
      dut.commit();
      auto e = Clock::now();
      combMs += std::chrono::duration<double, std::milli>(b - a).count();
      tickMs += std::chrono::duration<double, std::milli>(e - b).count();
      dut.comb();
      combMs += std::chrono::duration<double, std::milli>(Clock::now() - b)
                    .count() * 0.0; // folded into next loop iteration
    }
  }
  const double wallMs = std::chrono::duration<double, std::milli>(Clock::now() -
                                                                  t0)
                            .count();

  std::uint8_t expected = 0;
  for (unsigned i = 0; i < kNLight; ++i)
    expected = static_cast<std::uint8_t>(expected ^ ((1 + i) * kTicks));
  for (unsigned i = kNLight; i < kNLight + kNNest; ++i)
    expected = static_cast<std::uint8_t>(expected ^ ((1 + i + 3) * kTicks));
  std::uint8_t heavyV = 0;
  for (unsigned m = 0; m < 24; ++m)
    heavyV = static_cast<std::uint8_t>(heavyV ^ ((m + 1) * kTicks));
  for (unsigned k = 0; k < kNHeavy; ++k) {
    const unsigned j = kNLight + kNNest + k;
    expected = static_cast<std::uint8_t>(expected ^ heavyV ^ (1 + j));
  }
  const std::uint8_t agg = static_cast<std::uint8_t>(dut.agg.word(0));
  if (agg != expected) {
    std::fprintf(stderr, "fail: agg=%u expected %u\n", agg, expected);
    return 1;
  }
  const double phases = 2.0 * kTicks;
  std::printf(
      "ok ticks=%u wall_ms=%.1f ns_per_tick=%.1f comb_ns=%.1f tick_ns=%.1f"
      " | threads=%u\n",
      kTicks, wallMs, wallMs * 1e6 / phases, combMs * 1e6 / phases,
      tickMs * 1e6 / phases, pyc::cpp::pyc_threads());
  return 0;
}

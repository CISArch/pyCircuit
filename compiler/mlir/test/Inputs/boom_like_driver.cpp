// Boom-like parallel-tick load driver: every top-level instance m{pos} is a
// kBoomArms[pos]-register module (q_j += j+1 per rising edge, balanced XOR
// keep-alive tree folded with x = incr + pos). The printed line is a pure
// function of the tick count, so seq / uniform / weighted and any
// PYC_THREADS must agree byte-for-byte.
#include "boom_like.cpp"
#include "boom_like_manifest.h"

#include <chrono>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

namespace {

using Dut = pyc::gen::boom_like;
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

  double tickMs = 0.0;
  const auto t0 = Clock::now();
  for (unsigned c = 0; c < kTicks; ++c) {
    for (int phase = 0; phase < 2; ++phase) {
      dut.clk = pyc::cpp::Wire<1>(phase == 0 ? 1 : 0);
      dut.comb();
      auto b = Clock::now();
      dut.tick();
      dut.commit();
      auto e = Clock::now();
      tickMs += std::chrono::duration<double, std::milli>(e - b).count();
      dut.comb();
    }
  }
  const double wallMs =
      std::chrono::duration<double, std::milli>(Clock::now() - t0).count();

  std::uint8_t expected = 0;
  for (unsigned pos = 0; pos < kBoomN; ++pos) {
    const unsigned k = kBoomArms[pos];
    std::uint8_t modXor = 0;
    for (unsigned j = 1; j <= k; ++j)
      modXor = static_cast<std::uint8_t>(modXor ^
                                         static_cast<std::uint8_t>(j * kTicks));
    expected = static_cast<std::uint8_t>(
        expected ^ modXor ^ static_cast<std::uint8_t>(1 + (pos % 256)));
  }
  const std::uint8_t agg = static_cast<std::uint8_t>(dut.agg.word(0));
  if (agg != expected) {
    std::fprintf(stderr, "fail: agg=%u expected=%u\n", agg, expected);
    return 1;
  }
  const double phases = 2.0 * kTicks;
  std::printf("ok ticks=%u wall_ms=%.1f ns_per_tick=%.1f tick_ns=%.1f"
              " | threads=%u\n",
              kTicks, wallMs, wallMs * 1e6 / phases, tickMs * 1e6 / phases,
              pyc::cpp::pyc_threads());
  return 0;
}

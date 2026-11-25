// Weighted-partition load driver: 12 light + 1 nested + 4 heavy accumulator
// children. Prints per-tick wall time so uniform vs weighted emission can be
// compared, and verifies every accumulator against its closed form:
//   light i (i=0..11): acc += (1 + i)       per rising edge
//   nested (i=12):     acc += (1 + 12 + 3)  (parent adds 12, wnest adds 3)
//   heavy  j (j=13..16): acc += 78 + 12*(1+j)
#include "weighted_tick_instances.cpp"

#include <chrono>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

namespace {

using Dut = pyc::gen::weighted_tick_instances;

void runPhase(Dut &dut) {
  dut.comb();
  dut.tick();
  dut.commit();
  dut.comb();
}

} // namespace

int main(int argc, char **argv) {
  const unsigned kTicks = argc > 1 ? static_cast<unsigned>(std::atoi(argv[1]))
                                   : 200000u;
  Dut dut;
  dut.clk = pyc::cpp::Wire<1>(0);
  dut.rst = pyc::cpp::Wire<1>(0);
  dut.incr = pyc::cpp::Wire<8>(1);
  dut.comb();

  const auto t0 = std::chrono::steady_clock::now();
  for (unsigned c = 0; c < kTicks; ++c) {
    dut.clk = pyc::cpp::Wire<1>(1);
    runPhase(dut);
    dut.clk = pyc::cpp::Wire<1>(0);
    runPhase(dut);
  }
  const double wallMs = std::chrono::duration<double, std::milli>(
                            std::chrono::steady_clock::now() - t0)
                            .count();

  const std::uint8_t q[17] = {
      static_cast<std::uint8_t>(dut.q0.word(0)),
      static_cast<std::uint8_t>(dut.q1.word(0)),
      static_cast<std::uint8_t>(dut.q2.word(0)),
      static_cast<std::uint8_t>(dut.q3.word(0)),
      static_cast<std::uint8_t>(dut.q4.word(0)),
      static_cast<std::uint8_t>(dut.q5.word(0)),
      static_cast<std::uint8_t>(dut.q6.word(0)),
      static_cast<std::uint8_t>(dut.q7.word(0)),
      static_cast<std::uint8_t>(dut.q8.word(0)),
      static_cast<std::uint8_t>(dut.q9.word(0)),
      static_cast<std::uint8_t>(dut.q10.word(0)),
      static_cast<std::uint8_t>(dut.q11.word(0)),
      static_cast<std::uint8_t>(dut.q12.word(0)),
      static_cast<std::uint8_t>(dut.q13.word(0)),
      static_cast<std::uint8_t>(dut.q14.word(0)),
      static_cast<std::uint8_t>(dut.q15.word(0)),
      static_cast<std::uint8_t>(dut.q16.word(0)),
  };
  for (unsigned i = 0; i < 17; ++i) {
    unsigned step;
    if (i <= 11)
      step = 1 + i;                     // light: x = incr + i = 1 + i
    else if (i == 12)
      step = 1 + 12 + 3;                // nested: wlight sees x + 3
    else
      step = 78 + 12 * (1 + i);         // heavy: 12 dependent x/const adds
    const std::uint8_t expected =
        static_cast<std::uint8_t>(step * kTicks);
    if (q[i] != expected) {
      std::fprintf(stderr, "fail: q%u=%u expected %u\n", i, q[i], expected);
      return 1;
    }
  }
  std::printf("ok ticks=%u wall_ms=%.1f ns_per_tick=%.1f | threads=%u\n",
              kTicks, wallMs, wallMs * 1e6 / (kTicks * 2.0),
              pyc::cpp::pyc_threads());
  return 0;
}

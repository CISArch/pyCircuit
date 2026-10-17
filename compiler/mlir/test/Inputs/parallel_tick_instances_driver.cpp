// Parallel tick gate: eight accumulator children updated per rising edge.
// The printed line is a pure function of the cycle count, so sequential,
// PYC_THREADS=1 and PYC_THREADS=N runs must print byte-identical output.
#include "parallel_tick_instances.cpp"

#include <cstdint>
#include <cstdio>

namespace {

using Dut = pyc::gen::parallel_tick_instances;

void runPhase(Dut &dut) {
  dut.comb();
  dut.tick();
  dut.commit();
  dut.comb();
}

} // namespace

int main() {
  Dut dut;
  dut.clk = pyc::cpp::Wire<1>(0);
  dut.rst = pyc::cpp::Wire<1>(0);
  dut.incr = pyc::cpp::Wire<8>(1);
  dut.comb();

  const unsigned kRising = 300;
  for (unsigned c = 0; c < kRising; ++c) {
    dut.clk = pyc::cpp::Wire<1>(1);
    runPhase(dut);
    dut.clk = pyc::cpp::Wire<1>(0);
    runPhase(dut);
  }

  const std::uint8_t q[8] = {
      static_cast<std::uint8_t>(dut.q0.word(0)),
      static_cast<std::uint8_t>(dut.q1.word(0)),
      static_cast<std::uint8_t>(dut.q2.word(0)),
      static_cast<std::uint8_t>(dut.q3.word(0)),
      static_cast<std::uint8_t>(dut.q4.word(0)),
      static_cast<std::uint8_t>(dut.q5.word(0)),
      static_cast<std::uint8_t>(dut.q6.word(0)),
      static_cast<std::uint8_t>(dut.q7.word(0)),
  };
  for (unsigned i = 0; i < 8; ++i) {
    std::uint8_t expected =
        static_cast<std::uint8_t>((1u + i) * kRising);
    if (q[i] != expected) {
      std::fprintf(stderr, "fail: q%u=%u expected %u\n", i, q[i], expected);
      return 1;
    }
    std::printf("%u ", q[i]);
  }
  std::printf("| threads=%u\n", pyc::cpp::pyc_threads());
  return 0;
}

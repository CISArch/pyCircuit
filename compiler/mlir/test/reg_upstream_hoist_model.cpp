#include MODEL_HEADER

#include <cassert>
#include <cstdint>
#include <iostream>

// Independent model of `q' = a & b` (enable is constant 1), `out = q ^ a`.
// Checked after the rising edge, matching the generated C++ step order:
// reset loads the init, otherwise q becomes this cycle's a & b, then out
// is computed from that q.
int main() {
  pyc::gen::hoist_upstream_model model;
  std::uint8_t q = 0;
  std::uint64_t checksum = 0;
  constexpr unsigned kCycles = 64;
  for (unsigned cycle = 0; cycle < kCycles; ++cycle) {
    const bool reset = cycle < 2 || cycle == 17 || cycle == 40;
    const std::uint8_t a = static_cast<std::uint8_t>(cycle * 3 + 1);
    const std::uint8_t b = static_cast<std::uint8_t>(cycle * 5 + 9);
    model.rst = pyc::cpp::Wire<1>(reset ? 1 : 0);
    model.a = pyc::cpp::Wire<8>(a);
    model.b = pyc::cpp::Wire<8>(b);
    model.clk = pyc::cpp::Wire<1>(0);
    model.step();
    model.clk = pyc::cpp::Wire<1>(1);
    model.step();

    if (reset)
      q = 0;
    else
      q = static_cast<std::uint8_t>(a & b);
    const auto expected = static_cast<std::uint8_t>(q ^ a);
    assert(model.out.value() == expected);
    checksum = checksum * 131u + expected;
  }
  std::cout << "cycles=" << kCycles << " checksum=" << checksum << "\n";
  return 0;
}

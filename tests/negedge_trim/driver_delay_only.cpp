// Driver for the delay-only regression of the --cpp-negedge-trim A/B.
//
// The leaf under test owns a single loopified delay line and no register, so
// the emitter routes it through the generic `compute_generic(clk)` edge path.
// That path lowers the loop's own clkPrev on every falling edge; if the trim
// skips it the delay line stops advancing.  Both models are driven clock-cycle
// shape (clk=1; step(); clk=0; step()) and must print the same trace.
#include <cstdint>
#include <cstdio>

#include "dl_top.hpp"

using namespace pyc::gen;
using pyc::cpp::Bits;

int main() {
  dl_top d;
  d.rst = Bits<1>{1};
  d.clk = Bits<1>{0};
  d.step();
  d.clk = Bits<1>{1};
  d.step();
  d.clk = Bits<1>{0};
  d.step();
  d.rst = Bits<1>{0};

  for (unsigned c = 1; c <= 8; ++c) {
    d.en = Bits<1>{1};
    d.din = Bits<8>{static_cast<std::uint8_t>(c)};

    d.clk = Bits<1>{1};
    d.step();
    std::printf("c%u posedge q=%llu y=%llu\n", c,
                static_cast<unsigned long long>(d.q.value()),
                static_cast<unsigned long long>(d.y.value()));

    d.clk = Bits<1>{0};
    d.step();
    std::printf("c%u fall    q=%llu y=%llu\n", c,
                static_cast<unsigned long long>(d.q.value()),
                static_cast<unsigned long long>(d.y.value()));
  }
  return 0;
}

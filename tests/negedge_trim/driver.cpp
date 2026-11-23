// Cycle-by-cycle driver for the --cpp-negedge-trim A/B smoke.
//
// The benchmark wrapper drives one clock cycle as `clk=1; step(); clk=0;
// step();`.  This driver replays that shape over a scripted stimulus and also
// changes the data input *between* the two steps of a cycle (a falling-edge
// input change), which is the case the falling-edge trim must not lose.
//
// The same driver is compiled against the serial model and the trimmed model;
// their printed traces must match line for line.
#include <cstdint>
#include <cstdio>

#include "trim_top.hpp"

using namespace pyc::gen;
using pyc::cpp::Bits;

static void dump(const trim_top &d, unsigned cycle, const char *tag) {
  std::printf("c%03u %-12s qtop=%3llu qa=%3llu tap=%3llu mix=%3llu\n", cycle,
              tag, static_cast<unsigned long long>(d.qtop.value()),
              static_cast<unsigned long long>(d.qa.value()),
              static_cast<unsigned long long>(d.tap.value()),
              static_cast<unsigned long long>(d.mix.value()));
}

int main() {
  trim_top d;

  // Reset: clock low, assert, two edges, deassert (mirrors the trace wrapper).
  d.rst = Bits<1>{1};
  d.clk = Bits<1>{0};
  d.step();
  d.clk = Bits<1>{1};
  d.step();
  d.clk = Bits<1>{0};
  d.step();
  d.rst = Bits<1>{0};
  dump(d, 0, "after-reset");

  for (unsigned c = 1; c <= 40; ++c) {
    d.ena = Bits<1>{(c % 3) != 0};
    d.enb = Bits<1>{(c % 4) != 0};
    d.din = Bits<8>{static_cast<std::uint8_t>(c * 7u + 1u)};

    // Rising edge: sample next state.
    d.clk = Bits<1>{1};
    d.step();
    dump(d, c, "posedge");

    // Falling edge with the input changed in between: the serial model
    // re-evaluates here, so the trimmed model must keep the same outputs.
    d.din = Bits<8>{static_cast<std::uint8_t>(c * 11u + 3u)};
    d.clk = Bits<1>{0};
    d.step();
    dump(d, c, "fall-in-changed");

    // Every fifth cycle also change the input after the falling edge, so the
    // next rising edge samples a value the model has not evaluated yet.
    if (c % 5 == 0) {
      d.din = Bits<8>{static_cast<std::uint8_t>(c + 100u)};
      dump(d, c, "idle-changed");
    }
  }
  return 0;
}

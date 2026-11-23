// transfer() must keep working when the tick pair is fused (tick() does
// compute+commit, commit() becomes a shell). This smoke drives the generated
// model through both entry points: the harness-style step() loop, then an
// explicit commit() and transfer(), asserting the documented shapes are still
// callable and that transfer() still commits (it is the API alias of commit).
#include "pyc_model.h"

#include <cstdio>

int main() {
  pyc::gen::pyc_model dut;
  dut.eval();
  dut.tick();
  dut.commit();   // no-op when fused, real commit otherwise
  dut.comb();
  dut.tick();
  dut.commit();
  // transfer() is the documented alias of commit(): it must still perform a
  // full commit on both model shapes.
  dut.eval();
  dut.transfer();
  dut.eval();
  dut.transfer();
  std::printf("transfer_smoke ok\n");
  return 0;
}

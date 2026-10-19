// PackedRegBank smoke: one packed storage covering 3/8/50-bit lanes driven by
// the same clock/reset/enable as a reference pyc_reg<3>; lane q must track the
// reference register exactly across rise/fall/idle/reset/enable patterns.
#include <cstdio>
#include "pyc_bits.hpp"
#include "pyc_primitives.hpp"
#include "pyc_seq_bank_ext.hpp"
using namespace pyc::cpp;

int main() {
  PackedRegBank b;
  Wire<64> q0{0}, d0{0}, init{0};
  Wire<64> q1{0}, d1{0}, init1{0};
  Wire<64> q2{0}, d2{0}, init2{0};
  Wire<1> clk{0}, rst{0}, en{1};
  b.add_lane({&q0, &d0, &rst, &en, &init, 3u});
  b.add_lane({&q1, &d1, &rst, &en, &init1, 8u});
  b.add_lane({&q2, &d2, &rst, &en, &init2, 50u});

  // Reference register with the same 3-bit lane controls.
  Wire<3> dR{0}, initR{0}, qR{0};
  pyc_reg<3> refReg(clk, rst, en, dR, initR, qR);

  bool prev = false;
  int bad = 0;
  for (int c = 0; c < 3000; ++c) {
    const bool now = (c % 3) != 0;
    const bool rstOn = (c % 97) == 5;
    const bool enOn = (c % 11) != 4;
    const uint64_t dv = (uint64_t)(c * 7 + 1) & 7u;
    clk = Wire<1>{now ? 1u : 0u};
    rst = Wire<1>{rstOn ? 1u : 0u};
    en = Wire<1>{enOn ? 1u : 0u};
    d0 = Wire<64>{dv};
    dR = Wire<3>{dv};

    const bool rise = (!prev) & now, fall = prev & (!now);
    prev = now;
    if (rise) {
      b.compute_rise();
      refReg.posedge_tick_compute();
    } else if (fall) {
      b.negedge();
      refReg.negedge_update();
    } else {
      b.compute_generic(now);
      refReg.tick_compute();
    }
    b.commit();
    refReg.tick_commit();

    if ((int)q0.value() != (int)qR.value()) {
      if (++bad <= 3)
        printf("c%d q0=%llu ref=%llu\n", c,
               (unsigned long long)q0.value(),
               (unsigned long long)qR.value());
    }
  }
  if (bad) {
    printf("PACKED BANK MISMATCH (%d)\n", bad);
    return 1;
  }
  printf("packed bank ok (3000 cycles, 3/8/50-bit lanes)\n");
}

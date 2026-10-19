// State-lane packing gates (pyc-pack-state-lanes): same-control integer regs /
// delay lines become one wider state op; lanes return as state_pack_lsb
// extracts. PACK uses max-width=256, CAP uses max-width=12.
//
// PACK-LABEL: func.func @pack_integer_regs
// PACK-DAG: %[[NEXT:.*]] = pyc.concat({{.*}}) : (i3, i8, i4) -> i15
// PACK-DAG: %[[INIT:.*]] = pyc.concat({{.*}}) : (i3, i8, i4) -> i15
// PACK: %[[PACKED:.*]] = pyc.reg {{.*}}, %[[NEXT]], %[[INIT]]
// PACK-SAME: pyc.optimized_by = "pack_state_lanes"
// PACK-SAME: pyc.state_pack_lanes = 3 : i64
// PACK-SAME: pyc.state_pack_width = 15 : i64
// PACK-SAME: : i15
// PACK-DAG: %[[Q0:.*]] = pyc.extract %[[PACKED]] {lsb = 0 : i64, msb = 3 : i64{{.*}}} : i15 -> i4
// PACK-DAG: %[[Q1:.*]] = pyc.extract %[[PACKED]] {lsb = 4 : i64, msb = 11 : i64{{.*}}} : i15 -> i8
// PACK-DAG: %[[Q2:.*]] = pyc.extract %[[PACKED]] {lsb = 12 : i64, msb = 14 : i64{{.*}}} : i15 -> i3
// PACK-NOT: pyc.reg
// PACK-LABEL: func.func @pack_delay_lines
// PACK: pyc.delay_line
// PACK-SAME: depth = 3 : i64
// PACK-SAME: pyc.optimized_by = "pack_state_lanes"
// PACK-SAME: pyc.state_pack_width = 12 : i64
// PACK-SAME: : i12
// PACK-NOT: pyc.delay_line
// PACK-LABEL: func.func @pack_named_state
// PACK-COUNT-1: pyc.reg
// PACK-SAME: pyc.state_pack_width = 16 : i64
// PACK: pyc.alias
// PACK-SAME: pyc.name = "architectural_state"
// PACK-LABEL: func.func @keep_direct_state_outputs
// PACK-COUNT-1: pyc.reg
// PACK-SAME: pyc.state_pack_width = 16 : i64
// PACK-COUNT-2: pyc.extract
// PACK-LABEL: func.func @keep_mismatched_controls
// PACK-COUNT-2: pyc.reg
// PACK-NOT: pyc.concat
// PACK-LABEL: func.func @keep_passthrough_state_outputs
// PACK-COUNT-1: pyc.reg
// PACK-SAME: pyc.state_pack_width = 16 : i64
// PACK-COUNT-2: pyc.extract
// PACK-LABEL: func.func @keep_debug_state
// PACK-COUNT-1: pyc.reg
// PACK-SAME: pyc.state_pack_width = 16 : i64
// PACK: pyc.alias
// PACK-SAME: pyc.debug_keep = true
// PACK-LABEL: func.func @pack_cross_bucket_alias_dependency
// PACK-COUNT-2: pyc.reg
// PACK-NOT: pyc.alias
// PACK-LABEL: func.func @pack_aliased_controls
// PACK-COUNT-1: pyc.reg
// PACK-SAME: pyc.state_pack_width = 16 : i64

// CAP-LABEL: func.func @pack_integer_regs
// CAP: pyc.reg
// CAP-SAME: pyc.optimized_by = "pack_state_lanes"
// CAP-SAME: pyc.state_pack_width = 12 : i64
// CAP-SAME: : i12
// CAP: pyc.reg
// CAP-SAME: : i3
// CAP-NOT: pyc.state_pack_width = 15 : i64
// CAP-LABEL: func.func @pack_delay_lines

module {
  func.func @pack_integer_regs(
      %clk: !pyc.clock, %rst: !pyc.reset,
      %a: i4, %b: i8, %c: i3) -> (i4, i8, i3) {
    %en = pyc.constant 1 : i1
    %init0 = pyc.constant 1 : i4
    %init1 = pyc.constant 2 : i8
    %init2 = pyc.constant 3 : i3
    %q0 = pyc.reg %clk, %rst, %en, %a, %init0 : i4
    %q1 = pyc.reg %clk, %rst, %en, %b, %init1 : i8
    %q2 = pyc.reg %clk, %rst, %en, %c, %init2 : i3
    %o0 = pyc.add %q0, %a : i4, i4 -> i4
    %o1 = pyc.add %q1, %b : i8, i8 -> i8
    %o2 = pyc.add %q2, %c : i3, i3 -> i3
    func.return %o0, %o1, %o2 : i4, i8, i3
  }

  func.func @pack_delay_lines(
      %clk: !pyc.clock, %rst: !pyc.reset, %a: i4, %b: i8) -> (i4, i8) {
    %en = pyc.constant 1 : i1
    %init0 = pyc.constant 1 : i4
    %init1 = pyc.constant 2 : i8
    %q0 = pyc.delay_line %clk, %rst, %en, %a, %init0 {depth = 3 : i64} : i4
    %q1 = pyc.delay_line %clk, %rst, %en, %b, %init1 {depth = 3 : i64} : i8
    %o0 = pyc.add %q0, %a : i4, i4 -> i4
    %o1 = pyc.add %q1, %b : i8, i8 -> i8
    func.return %o0, %o1 : i4, i8
  }

  func.func @pack_named_state(
      %clk: !pyc.clock, %rst: !pyc.reset, %a: i8, %b: i8) -> (i8, i8) {
    %en = pyc.constant 1 : i1
    %init = pyc.constant 0 : i8
    %q0 = pyc.reg %clk, %rst, %en, %a, %init {pyc.name = "architectural_state"} : i8
    %q1 = pyc.reg %clk, %rst, %en, %b, %init : i8
    %o0 = pyc.add %q0, %a : i8, i8 -> i8
    %o1 = pyc.add %q1, %b : i8, i8 -> i8
    func.return %o0, %o1 : i8, i8
  }

  func.func @keep_direct_state_outputs(
      %clk: !pyc.clock, %rst: !pyc.reset, %a: i8, %b: i8) -> (i8, i8) {
    %en = pyc.constant 1 : i1
    %init = pyc.constant 0 : i8
    %q0 = pyc.reg %clk, %rst, %en, %a, %init : i8
    %q1 = pyc.reg %clk, %rst, %en, %b, %init : i8
    func.return %q0, %q1 : i8, i8
  }

  func.func @keep_mismatched_controls(
      %clk: !pyc.clock, %rst: !pyc.reset, %en0: i1, %en1: i1,
      %a: i8, %b: i8) -> (i8, i8) {
    %init = pyc.constant 0 : i8
    %q0 = pyc.reg %clk, %rst, %en0, %a, %init : i8
    %q1 = pyc.reg %clk, %rst, %en1, %b, %init : i8
    %o0 = pyc.add %q0, %a : i8, i8 -> i8
    %o1 = pyc.add %q1, %b : i8, i8 -> i8
    func.return %o0, %o1 : i8, i8
  }

  func.func @keep_passthrough_state_outputs(
      %clk: !pyc.clock, %rst: !pyc.reset, %a: i8, %b: i8) -> (i8, i8) {
    %en = pyc.constant 1 : i1
    %init = pyc.constant 0 : i8
    %q0 = pyc.reg %clk, %rst, %en, %a, %init : i8
    %q1 = pyc.reg %clk, %rst, %en, %b, %init : i8
    %o0 = pyc.comb(%q0) : (i8) -> i8 {
    ^bb0(%in: i8):
      pyc.yield %in : i8
    }
    %o1 = pyc.comb(%q1) : (i8) -> i8 {
    ^bb0(%in: i8):
      pyc.yield %in : i8
    }
    func.return %o0, %o1 : i8, i8
  }

  func.func @keep_debug_state(
      %clk: !pyc.clock, %rst: !pyc.reset, %a: i8, %b: i8) -> (i8, i8) {
    %en = pyc.constant 1 : i1
    %init = pyc.constant 0 : i8
    %q0 = pyc.reg %clk, %rst, %en, %a, %init {pyc.debug_keep = true} : i8
    %q1 = pyc.reg %clk, %rst, %en, %b, %init : i8
    %o0 = pyc.add %q0, %a : i8, i8 -> i8
    %o1 = pyc.add %q1, %b : i8, i8 -> i8
    func.return %o0, %o1 : i8, i8
  }

  func.func @pack_cross_bucket_alias_dependency(
      %clk: !pyc.clock, %rst: !pyc.reset, %en0: i1, %en1: i1,
      %a: i8, %b: i8, %c: i8) -> (i8, i8, i8, i8) {
    %init = pyc.constant 0 : i8
    %q0 = pyc.reg %clk, %rst, %en0, %a, %init : i8
    %q2 = pyc.reg %clk, %rst, %en0, %b, %init : i8
    %forward = pyc.alias %q0 : i8
    %q1 = pyc.reg %clk, %rst, %en1, %forward, %init : i8
    %q3 = pyc.reg %clk, %rst, %en1, %c, %init : i8
    %o0 = pyc.add %q0, %a : i8, i8 -> i8
    %o1 = pyc.add %q1, %a : i8, i8 -> i8
    %o2 = pyc.add %q2, %a : i8, i8 -> i8
    %o3 = pyc.add %q3, %a : i8, i8 -> i8
    func.return %o0, %o1, %o2, %o3 : i8, i8, i8, i8
  }

  func.func @pack_aliased_controls(
      %clk: !pyc.clock, %rst: !pyc.reset,
      %a: i8, %b: i8) -> (i8, i8) {
    %clk_alias = pyc.alias %clk : !pyc.clock
    %rst_alias = pyc.alias %rst : !pyc.reset
    %en = pyc.constant 1 : i1
    %init = pyc.constant 0 : i8
    %q0 = pyc.reg %clk, %rst, %en, %a, %init : i8
    %q1 = pyc.reg %clk_alias, %rst_alias, %en, %b, %init : i8
    %o0 = pyc.add %q0, %a : i8, i8 -> i8
    %o1 = pyc.add %q1, %b : i8, i8 -> i8
    func.return %o0, %o1 : i8, i8
  }
}

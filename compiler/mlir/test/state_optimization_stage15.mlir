// Stage 1.5 bounded refinement (cascade equivalent-state merge) gate.
//
// CASCADE-LABEL: func.func @cascade_equivalent_state
// CASCADE-SAME: pyc.stats.state_opt_cascade_regs_merged = 1 : i64
// CASCADE-SAME: pyc.stats.state_opt_merge_rounds = 2 : i64
// CASCADE-SAME: pyc.stats.state_opt_regs_merged = 2 : i64
// CASCADE-COUNT-2: pyc.reg
// CASCADE-NOT: pyc.reg

module {
  func.func @cascade_equivalent_state(
      %clk: !pyc.clock, %rst: !pyc.reset, %x: i8, %c: i8) -> (i8, i8) {
    %en = pyc.constant 1 : i1
    %init = pyc.constant 0 : i8
    %q0a = pyc.reg %clk, %rst, %en, %x, %init : i8
    %q0b = pyc.reg %clk, %rst, %en, %x, %init : i8
    %next1a = pyc.add %q0a, %c : i8, i8 -> i8
    %next1b = pyc.add %q0b, %c : i8, i8 -> i8
    %q1a = pyc.reg %clk, %rst, %en, %next1a, %init : i8
    %q1b = pyc.reg %clk, %rst, %en, %next1b, %init : i8
    func.return %q1a, %q1b : i8, i8
  }
}

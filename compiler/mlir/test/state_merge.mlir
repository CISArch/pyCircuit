// Equivalent-state merge (first stage of pyc-state-optimize). Run with:
//   pyc-opt state_merge.mlir --pass-pipeline='builtin.module(func.func(pyc-state-optimize))'

// CHECK-LABEL: func.func @merge_equivalent
// CHECK-COUNT-1: pyc.reg
// CHECK-SAME: pyc.optimized_by = "merge_equivalent_state"
// CHECK-NOT: pyc.reg
func.func @merge_equivalent(%clk: !pyc.clock, %rst: !pyc.reset, %x: i8, %y: i8) -> i8 {
  %en = pyc.constant 1 : i1
  %init = pyc.constant 0 : i8
  %q0 = pyc.reg %clk, %rst, %en, %x, %init : i8
  %q1 = pyc.reg %clk, %rst, %en, %x, %init : i8
  %o = pyc.add %q0, %q1 : i8, i8 -> i8
  %r = pyc.add %o, %y : i8, i8 -> i8
  return %r : i8
}

// A merge exposes equivalent next cones; the second round merges them too
// (cascade): q0a/q0b merge, then q1a/q1b become identical and merge.
// CHECK-LABEL: func.func @merge_cascade
// CHECK-COUNT-2: pyc.reg
// CHECK-NOT: pyc.reg
func.func @merge_cascade(%clk: !pyc.clock, %rst: !pyc.reset, %x: i8, %c: i8) -> (i8, i8) {
  %en = pyc.constant 1 : i1
  %init = pyc.constant 0 : i8
  %q0a = pyc.reg %clk, %rst, %en, %x, %init : i8
  %q0b = pyc.reg %clk, %rst, %en, %x, %init : i8
  %n1a = pyc.add %q0a, %c : i8, i8 -> i8
  %n1b = pyc.add %q0b, %c : i8, i8 -> i8
  %q1a = pyc.reg %clk, %rst, %en, %n1a, %init : i8
  %q1b = pyc.reg %clk, %rst, %en, %n1b, %init : i8
  return %q1a, %q1b : i8, i8
}

// Different enable / init / next are different state (distinct enables keep
// them out of lane packing too).
// CHECK-LABEL: func.func @keep_different_state
// CHECK-COUNT-3: pyc.reg
// CHECK-NOT: pyc.reg
func.func @keep_different_state(%clk: !pyc.clock, %rst: !pyc.reset,
                                %en0: i1, %en1: i1, %en2: i1, %x: i8, %y: i8) -> (i8, i8, i8) {
  %init0 = pyc.constant 0 : i8
  %init1 = pyc.constant 1 : i8
  %q0 = pyc.reg %clk, %rst, %en0, %x, %init0 : i8
  %q1 = pyc.reg %clk, %rst, %en1, %x, %init0 : i8
  %q2 = pyc.reg %clk, %rst, %en2, %y, %init1 : i8
  %a = pyc.add %q0, %y : i8, i8 -> i8
  %b = pyc.add %q1, %y : i8, i8 -> i8
  %c = pyc.add %q2, %y : i8, i8 -> i8
  return %a, %b, %c : i8, i8, i8
}

// The merged-away register keeps its observable name as an alias.
// CHECK-LABEL: func.func @merge_keeps_name
// CHECK-COUNT-1: pyc.reg
// CHECK-NOT: pyc.reg
// CHECK: pyc.name = "second"
func.func @merge_keeps_name(%clk: !pyc.clock, %rst: !pyc.reset, %x: i8, %y: i8) -> i8 {
  %en = pyc.constant 1 : i1
  %init = pyc.constant 0 : i8
  %q0 = pyc.reg %clk, %rst, %en, %x, %init : i8
  %q1 = pyc.reg %clk, %rst, %en, %x, %init {pyc.name = "second"} : i8
  %o = pyc.add %q0, %q1 : i8, i8 -> i8
  %r = pyc.add %o, %y : i8, i8 -> i8
  return %r : i8
}

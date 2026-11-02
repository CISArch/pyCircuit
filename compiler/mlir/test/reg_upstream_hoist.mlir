// RUN: pyc-opt %s --pass-pipeline='builtin.module(func.func(pyc-hoist-regs-upstream))' | FileCheck %s

// CHECK-LABEL: func.func @and_two
// CHECK-SAME: pyc.stats.hoist_ops_moved = 1
// CHECK-SAME: pyc.stats.hoist_regs_upstream = 1
// CHECK: %[[Z:.*]] = pyc.constant 0 : i8
// CHECK: %[[RA:.*]] = pyc.reg %arg0, %arg1, %arg2, %arg3, %[[Z]]
// CHECK-SAME: pyc.optimized_by = "hoist_regs_upstream"
// CHECK: %[[RB:.*]] = pyc.reg %arg0, %arg1, %arg2, %arg4, %[[Z]]
// CHECK-SAME: pyc.optimized_by = "hoist_regs_upstream"
// CHECK: %[[AND:.*]] = pyc.and %[[RA]], %[[RB]]
// CHECK: pyc.xor %[[AND]], %arg3

// CHECK-LABEL: func.func @unary_xor
// CHECK-SAME: pyc.stats.hoist_regs_upstream = 1
// CHECK: %[[ONE:.*]] = pyc.constant 1 : i8
// CHECK: %[[EN:.*]] = pyc.constant 1 : i1
// CHECK: %[[Q:.*]] = pyc.reg %arg0, %arg1, %[[EN]], %arg3, %[[ONE]]
// CHECK-SAME: pyc.optimized_by = "hoist_regs_upstream"
// CHECK: %[[X:.*]] = pyc.xor %[[Q]], %[[ONE]]
// CHECK: pyc.and %[[X]], %arg3

// CHECK-LABEL: func.func @fork_not
// CHECK-SAME: pyc.stats.hoist_regs_upstream = 1
// CHECK: %[[ONE:.*]] = pyc.constant 1 : i1
// CHECK: %[[Q:.*]] = pyc.reg %arg0, %arg1, %arg2, %arg3, %[[ONE]]
// CHECK: %[[N:.*]] = pyc.not %[[Q]]
// CHECK: %[[LONG:.*]] = pyc.xor %[[N]], %arg4
// CHECK: %[[SHORT:.*]] = pyc.and %arg3, %arg4
// CHECK: pyc.or %[[LONG]], %[[SHORT]]

// CHECK-LABEL: func.func @double_not
// CHECK-SAME: pyc.stats.hoist_regs_upstream = 2
// CHECK: %[[Z:.*]] = pyc.constant 0 : i1
// CHECK: %[[Q:.*]] = pyc.reg %arg0, %arg1, %arg2, %arg3, %[[Z]]
// CHECK: %[[N1:.*]] = pyc.not %[[Q]]
// CHECK: %[[N2:.*]] = pyc.not %[[N1]]
// CHECK: pyc.xor %[[N2]], %arg3

// CHECK-LABEL: func.func @hold_mux
// CHECK-SAME: pyc.stats.hoist_regs_upstream = 1
// CHECK: %[[BIT:.*]] = pyc.constant 1 : i8
// CHECK: %[[Q:.*]] = pyc.reg %arg0, %arg1, %arg2, %arg3, %[[BIT]]
// CHECK-SAME: pyc.optimized_by = "hoist_regs_upstream"
// CHECK: %[[X:.*]] = pyc.xor %[[Q]], %[[BIT]]
// CHECK: pyc.and %[[X]], %arg3
// CHECK-NOT: pyc.mux

// CHECK-LABEL: func.func @keep_named_add
// CHECK-SAME: pyc.stats.hoist_regs_upstream = 1
// CHECK: pyc.add %arg3, %arg4
// CHECK-SAME: pyc.name = "sum"
// CHECK: pyc.optimized_by = "hoist_regs_upstream"
// CHECK: pyc.add %
// CHECK-NOT: pyc.name = "sum"

// CHECK-LABEL: func.func @reject_feedback
// CHECK-SAME: pyc.stats.hoist_regs_upstream = 0
// CHECK: pyc.xor
// CHECK-NOT: pyc.optimized_by = "hoist_regs_upstream"

// CHECK-LABEL: func.func @reject_init
// CHECK-SAME: pyc.stats.hoist_blocked_init = 1
// CHECK-SAME: pyc.stats.hoist_regs_upstream = 0
// CHECK-NOT: pyc.optimized_by = "hoist_regs_upstream"

// CHECK-LABEL: func.func @direct_chain
// CHECK-SAME: pyc.stats.hoist_regs_upstream = 0
// CHECK: %[[N:.*]] = pyc.not %arg3
// CHECK: pyc.reg %arg0, %arg1, %arg2, %[[N]],
// CHECK-NOT: pyc.optimized_by = "hoist_regs_upstream"

module {
  func.func @and_two(%clk: !pyc.clock, %rst: !pyc.reset, %en: i1, %a: i8, %b: i8) -> i8 {
    %zero = pyc.constant 0 : i8
    %n = pyc.and %a, %b : i8, i8 -> i8
    %q = pyc.reg %clk, %rst, %en, %n, %zero : i8
    %u = pyc.xor %q, %a : i8, i8 -> i8
    func.return %u : i8
  }

  func.func @unary_xor(%clk: !pyc.clock, %rst: !pyc.reset, %en: i1, %in: i8) -> i8 {
    %zero = pyc.constant 0 : i8
    %one = pyc.constant 1 : i8
    %en1 = pyc.constant 1 : i1
    %n = pyc.xor %in, %one : i8, i8 -> i8
    %q = pyc.reg %clk, %rst, %en1, %n, %zero : i8
    %u = pyc.and %q, %in : i8, i8 -> i8
    func.return %u : i8
  }

  func.func @fork_not(%clk: !pyc.clock, %rst: !pyc.reset, %en: i1, %s: i1, %k: i1) -> i1 {
    %zero = pyc.constant 0 : i1
    %n = pyc.not %s : i1
    %q = pyc.reg %clk, %rst, %en, %n, %zero : i1
    %long = pyc.xor %q, %k : i1, i1 -> i1
    %short = pyc.and %s, %k : i1, i1 -> i1
    %join = pyc.or %long, %short : i1, i1 -> i1
    func.return %join : i1
  }

  func.func @double_not(%clk: !pyc.clock, %rst: !pyc.reset, %en: i1, %s: i1) -> i1 {
    %zero = pyc.constant 0 : i1
    %inner = pyc.not %s : i1
    %outer = pyc.not %inner : i1
    %q = pyc.reg %clk, %rst, %en, %outer, %zero : i1
    %u = pyc.xor %q, %s : i1, i1 -> i1
    func.return %u : i1
  }

  func.func @hold_mux(%clk: !pyc.clock, %rst: !pyc.reset, %cond: i1, %in: i8) -> i8 {
    %w = pyc.wire : i8
    %one = pyc.constant 1 : i1
    %zero = pyc.constant 0 : i8
    %bit = pyc.constant 1 : i8
    %q = pyc.reg %clk, %rst, %one, %w, %zero : i8
    %data = pyc.xor %in, %bit : i8, i8 -> i8
    %m = pyc.mux %cond, %data, %q : i1, i8, i8 -> i8
    pyc.assign %w, %m : i8
    %u = pyc.and %q, %in : i8, i8 -> i8
    func.return %u : i8
  }

  func.func @keep_named_add(%clk: !pyc.clock, %rst: !pyc.reset, %en: i1, %a: i8, %b: i8) -> i8 {
    %zero = pyc.constant 0 : i8
    %n = pyc.add %a, %b {pyc.name = "sum"} : i8, i8 -> i8
    %q = pyc.reg %clk, %rst, %en, %n, %zero : i8
    %u = pyc.xor %q, %a : i8, i8 -> i8
    func.return %u : i8
  }

  func.func @reject_feedback(%clk: !pyc.clock, %rst: !pyc.reset, %in: i8) -> i8 {
    %w = pyc.wire : i8
    %one = pyc.constant 1 : i1
    %zero = pyc.constant 0 : i8
    %q = pyc.reg %clk, %rst, %one, %w, %zero : i8
    %n = pyc.xor %q, %in : i8, i8 -> i8
    pyc.assign %w, %n : i8
    %u = pyc.and %q, %in : i8, i8 -> i8
    func.return %u : i8
  }

  func.func @reject_init(%clk: !pyc.clock, %rst: !pyc.reset, %en: i1, %a: i8, %b: i8) -> i8 {
    %two = pyc.constant 2 : i8
    %n = pyc.and %a, %b : i8, i8 -> i8
    %q = pyc.reg %clk, %rst, %en, %n, %two : i8
    %u = pyc.xor %q, %a : i8, i8 -> i8
    func.return %u : i8
  }

  func.func @direct_chain(%clk: !pyc.clock, %rst: !pyc.reset, %en: i1, %s: i1) -> i1 {
    %zero = pyc.constant 0 : i1
    %n = pyc.not %s : i1
    %q = pyc.reg %clk, %rst, %en, %n, %zero : i1
    %q2 = pyc.reg %clk, %rst, %en, %q, %zero : i1
    func.return %q2 : i1
  }
}

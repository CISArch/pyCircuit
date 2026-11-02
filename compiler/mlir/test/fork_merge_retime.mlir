// RUN: pyc-opt %s --pass-pipeline='builtin.module(func.func(pyc-fork-merge-retime))' | FileCheck %s

// Parallel copies with identical stage semantics collapse into one shared
// chain register (fork-merge of the common stage).
// CHECK-LABEL: func.func @merge_copies
// CHECK-SAME: pyc.stats.fork_merge_regs_created = 1
// CHECK-SAME: pyc.stats.fork_merge_sinks_rewritten = 2
// CHECK: %[[Q:.*]] = pyc.reg %arg0, %arg1, %arg2, %arg3, %{{.*}} {pyc.optimized_by = "fork_merge_retime"}
// CHECK: pyc.xor %[[Q]], %[[Q]]
// CHECK-NOT: pyc.reg

// A stage-gap path shares the common stage chain: level 1 (next = %a / %b)
// is shared, the extra stage chains on top of it, and the crossed and is
// cloned downstream once per delay.
// CHECK-LABEL: func.func @stage_gap
// CHECK-SAME: pyc.stats.fork_merge_regs_created = 4
// CHECK-SAME: pyc.stats.fork_merge_sinks_rewritten = 2
// CHECK: %[[B1:.*]] = pyc.reg %arg0, %arg1, %arg2, %arg4, %{{.*}} {pyc.optimized_by = "fork_merge_retime"}
// CHECK: %[[B2:.*]] = pyc.reg %arg0, %arg1, %arg2, %[[B1]], %{{.*}} {pyc.optimized_by = "fork_merge_retime"}
// CHECK: %[[A1:.*]] = pyc.reg %arg0, %arg1, %arg2, %arg3, %{{.*}} {pyc.optimized_by = "fork_merge_retime"}
// CHECK: %[[A2:.*]] = pyc.reg %arg0, %arg1, %arg2, %[[A1]], %{{.*}} {pyc.optimized_by = "fork_merge_retime"}
// CHECK: %[[X2:.*]] = pyc.and %[[A2]], %[[B2]] {pyc.optimized_by = "fork_merge_retime"}
// CHECK: %[[X1:.*]] = pyc.and %[[A1]], %[[B1]] {pyc.optimized_by = "fork_merge_retime"}
// CHECK: pyc.xor %[[X1]], %[[X2]]

// Different enable semantics never share one chain.
// CHECK-LABEL: func.func @distinct_en
// CHECK-SAME: pyc.stats.fork_merge_regs_created = 2
// CHECK-SAME: pyc.stats.fork_merge_sinks_rewritten = 2
// CHECK: pyc.reg %arg0, %arg1, %arg2, %arg3
// CHECK: pyc.reg %arg0, %arg1, %[[ONE:.*]], %arg3

// Hold loops (next reads own q through a mux) stay untouched.
// CHECK-LABEL: func.func @hold_loop
// CHECK-SAME: pyc.stats.fork_merge_sinks_rewritten = 0
// CHECK: pyc.mux
// CHECK-NOT: pyc.optimized_by = "fork_merge_retime"

// Non-constant init is out of scope.
// CHECK-LABEL: func.func @nonconst_init
// CHECK-SAME: pyc.stats.fork_merge_sinks_rewritten = 0
// CHECK-NOT: pyc.optimized_by = "fork_merge_retime"

// Observation names stay on the original op (same cycle); the lifted clone
// carries no observation identity.
// CHECK-LABEL: func.func @named_op
// CHECK-SAME: pyc.stats.fork_merge_clones = 1
// CHECK: %[[RB:.*]] = pyc.reg %arg0, %arg1, %arg2, %arg4, %{{.*}} {pyc.optimized_by = "fork_merge_retime"}
// CHECK: %[[RA:.*]] = pyc.reg %arg0, %arg1, %arg2, %arg3, %{{.*}} {pyc.optimized_by = "fork_merge_retime"}
// CHECK: %[[CL:.*]] = pyc.add %[[RA]], %[[RB]] {pyc.optimized_by = "fork_merge_retime"}
// CHECK: pyc.add %arg3, %arg4 {pyc.name = "sum"}
// CHECK: pyc.xor %[[CL]], %arg3

module {
  func.func @merge_copies(%clk: !pyc.clock, %rst: !pyc.reset, %en: i1, %a: i8) -> i8 {
    %zero = pyc.constant 0 : i8
    %q1 = pyc.reg %clk, %rst, %en, %a, %zero : i8
    %q2 = pyc.reg %clk, %rst, %en, %a, %zero : i8
    %u = pyc.xor %q1, %q2 : i8, i8 -> i8
    func.return %u : i8
  }

  func.func @stage_gap(%clk: !pyc.clock, %rst: !pyc.reset, %en: i1, %a: i8, %b: i8) -> i8 {
    %zero = pyc.constant 0 : i8
    %x = pyc.and %a, %b : i8, i8 -> i8
    %q1 = pyc.reg %clk, %rst, %en, %x, %zero : i8
    %q2 = pyc.reg %clk, %rst, %en, %q1, %zero : i8
    %out = pyc.xor %q1, %q2 : i8, i8 -> i8
    func.return %out : i8
  }

  func.func @distinct_en(%clk: !pyc.clock, %rst: !pyc.reset, %en: i1, %a: i8) -> i8 {
    %one = pyc.constant 1 : i1
    %zero = pyc.constant 0 : i8
    %q1 = pyc.reg %clk, %rst, %en, %a, %zero : i8
    %q2 = pyc.reg %clk, %rst, %one, %a, %zero : i8
    %u = pyc.xor %q1, %q2 : i8, i8 -> i8
    func.return %u : i8
  }

  func.func @hold_loop(%clk: !pyc.clock, %rst: !pyc.reset, %cond: i1, %in: i8) -> i8 {
    %w = pyc.wire : i8
    %one = pyc.constant 1 : i1
    %zero = pyc.constant 0 : i8
    %q = pyc.reg %clk, %rst, %one, %w, %zero : i8
    %n = pyc.xor %q, %in : i8, i8 -> i8
    %m = pyc.mux %cond, %n, %q : i1, i8, i8 -> i8
    pyc.assign %w, %m : i8
    %u = pyc.and %q, %in : i8, i8 -> i8
    func.return %u : i8
  }

  func.func @nonconst_init(%clk: !pyc.clock, %rst: !pyc.reset, %en: i1, %a: i8, %k: i8) -> i8 {
    %q = pyc.reg %clk, %rst, %en, %a, %k : i8
    %u = pyc.xor %q, %a : i8, i8 -> i8
    func.return %u : i8
  }

  func.func @named_op(%clk: !pyc.clock, %rst: !pyc.reset, %en: i1, %a: i8, %b: i8) -> i8 {
    %zero = pyc.constant 0 : i8
    %n = pyc.add %a, %b {pyc.name = "sum"} : i8, i8 -> i8
    %q = pyc.reg %clk, %rst, %en, %n, %zero : i8
    %u = pyc.xor %q, %a : i8, i8 -> i8
    func.return %u : i8
  }
}

// SeqBank partition: regs on the same clock share a bank id; a second clock
// gets its own bank; a clk alias resolves into the same bank. Run with:
//   pyc-opt seq_bank_partition.mlir \
//     --pass-pipeline='builtin.module(func.func(pyc-seq-bank-partition))'

// CHECK-LABEL: func.func @two_domains
// CHECK-SAME: pyc.stats.seq_bank_groups = 2 : i64
// CHECK-SAME: pyc.stats.seq_bank_lanes = 4 : i64
func.func @two_domains(%clk: !pyc.clock, %clk2: !pyc.clock, %rst: !pyc.reset, %in: i8) -> i8 {
  %c0 = arith.constant 0 : i8
  %en = arith.constant 1 : i1
  %clk_alias = pyc.alias %clk : !pyc.clock
  // Same domain: bank 0.
  // CHECK: pyc.reg %{{.*}}, %{{.*}}, %{{.*}}, %{{.*}}, %{{.*}} {pyc.seq_bank_id = 0 : i64}
  %q0 = pyc.reg %clk, %rst, %en, %in, %c0 : i8
  // CHECK: pyc.reg %{{.*}}, %{{.*}}, %{{.*}}, %{{.*}}, %{{.*}} {pyc.seq_bank_id = 0 : i64}
  %q1 = pyc.reg %clk, %rst, %en, %q0, %c0 : i8
  // Alias resolves to the same bank.
  // CHECK: pyc.reg %{{.*}}, %{{.*}}, %{{.*}}, %{{.*}}, %{{.*}} {pyc.seq_bank_id = 0 : i64}
  %q2 = pyc.reg %clk_alias, %rst, %en, %q1, %c0 : i8
  // Second clock: bank 1.
  // CHECK: pyc.reg %{{.*}}, %{{.*}}, %{{.*}}, %{{.*}}, %{{.*}} {pyc.seq_bank_id = 1 : i64}
  %q3 = pyc.reg %clk2, %rst, %en, %q2, %c0 : i8
  return %q3 : i8
}

// CHECK-LABEL: func.func @no_regs
// CHECK-SAME: pyc.stats.seq_bank_groups = 0 : i64
// CHECK-SAME: pyc.stats.seq_bank_lanes = 0 : i64
func.func @no_regs(%a: i8) -> i8 {
  // CHECK-NOT: pyc.seq_bank_id
  // CHECK: arith.addi %{{.*}}, %{{.*}} : i8
  %r = arith.addi %a, %a : i8
  return %r : i8
}

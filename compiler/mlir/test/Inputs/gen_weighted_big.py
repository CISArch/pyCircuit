#!/usr/bin/env python3
"""Generate weighted_tick_big.mlir: a parallel-tick load-test design with a
deliberately skewed instance mix (1200 light + 12 nested + 400 heavy
accumulators), aggregated into one output via an XOR tree. The heavy block
sits at the end of the schedule so uniform chunking piles it into few parts
while --cpp-tick-partition=weighted spreads the boundaries.

Usage: gen_weighted_big.py [n_light n_nest n_heavy] > weighted_tick_big.mlir
"""
import sys

n_light = int(sys.argv[1]) if len(sys.argv) > 1 else 1200
n_nest = int(sys.argv[2]) if len(sys.argv) > 2 else 12
n_heavy = int(sys.argv[3]) if len(sys.argv) > 3 else 400
total = n_light + n_nest + n_heavy

attrs = (
    'attributes {{arg_names = ["clk", "rst", "x"], result_names = ["acc"], '
    'pyc.kind = "module", pyc.inline = "false", pyc.base = "{base}", '
    'pyc.params = "{{}}", pyc.value_params = [], pyc.value_param_types = [], '
    'pyc.struct.collections = "[]", '
    'pyc.struct.metrics = "{{'
    '\\22ast_node_count\\22:8,\\22collection_count\\22:0,'
    '\\22collection_instance_count\\22:0,\\22estimated_inline_cost\\22:4,'
    '\\22hardware_call_count\\22:0,\\22instance_count\\22:0,'
    '\\22loop_count\\22:0,\\22module_call_count\\22:0,'
    '\\22module_family_collection_count\\22:0,\\22repeat_pressure\\22:0,'
    '\\22repeated_body_clusters\\22:[],\\22source_loc\\22:3,'
    '\\22state_alloc_count\\22:1,\\22state_call_count\\22:0}}"}}'
)

out = []
out.append(
    'module attributes {pyc.top = @weighted_tick_big, '
    'pyc.frontend.contract = "pycircuit"} {'
)

# light: acc += x
out.append("  func.func @wlight(%clk: !pyc.clock, %rst: !pyc.reset, %x: i8) -> i8 "
           + attrs.format(base="wlight") + " {")
out.append('    %next = pyc.wire {pyc.name = "acc__next"} : i8')
out.append("    %en = pyc.constant 1 : i1")
out.append("    %zero = pyc.constant 0 : i8")
out.append("    %q = pyc.reg %clk, %rst, %en, %next, %zero : i8")
out.append('    %qa = pyc.alias %q {pyc.name = "acc"} : i8')
out.append("    %sum = pyc.add %qa, %x : i8, i8 -> i8")
out.append("    pyc.assign %next, %sum : i8")
out.append("    func.return %qa : i8")
out.append("  }")

# heavy: 24 register counters (tick-phase weight = 24 reg arms), kept live
# through an XOR tree folded with x. q_k += (k+1) per rising edge.
out.append("  func.func @wheavy(%clk: !pyc.clock, %rst: !pyc.reset, %x: i8) -> i8 "
           + attrs.format(base="wheavy") + " {")
out.append("    %en = pyc.constant 1 : i1")
out.append("    %zero = pyc.constant 0 : i8")
for k in range(24):
    out.append(f'    %n{k} = pyc.wire {{pyc.name = "q{k}__next"}} : i8')
    out.append(f"    %r{k} = pyc.reg %clk, %rst, %en, %n{k}, %zero : i8")
    out.append(f'    %a{k} = pyc.alias %r{k} {{pyc.name = "q{k}"}} : i8')
    out.append(f"    %c{k} = pyc.constant {k + 1} : i8")
    out.append(f"    %s{k} = pyc.add %a{k}, %c{k} : i8, i8 -> i8")
    out.append(f"    pyc.assign %n{k}, %s{k} : i8")
prev = "%a0"
for k in range(1, 24):
    out.append(f"    %y{k} = pyc.xor {prev}, %a{k} : i8, i8 -> i8")
    prev = f"%y{k}"
out.append(f"    %out = pyc.xor {prev}, %x : i8, i8 -> i8")
out.append("    func.return %out : i8")
out.append("  }")

# nest: x+3 into a wlight instance
out.append("  func.func @wnest(%clk: !pyc.clock, %rst: !pyc.reset, %x: i8) -> i8 "
           + attrs.format(base="wnest") + " {")
out.append("    %one = pyc.constant 1 : i8")
out.append("    %s1 = pyc.add %x, %one : i8, i8 -> i8")
out.append("    %s2 = pyc.add %s1, %one : i8, i8 -> i8")
out.append("    %s3 = pyc.add %s2, %one : i8, i8 -> i8")
out.append('    %acc = pyc.instance %clk, %rst, %s3 {callee = @wlight, name = "inner"} : (!pyc.clock, !pyc.reset, i8) -> i8')
out.append("    func.return %acc : i8")
out.append("  }")

# top: constants, x_i = incr + i, instances in light/nest/heavy order,
# XOR tree over all accumulator outputs.
out.append("  func.func @weighted_tick_big(%clk: !pyc.clock, %rst: !pyc.reset, %incr: i8) -> i8 "
           + attrs.format(base="build").replace('arg_names = ["clk", "rst", "x"]',
                                                'arg_names = ["clk", "rst", "incr"]').replace('result_names = ["acc"]',
                                                'result_names = ["agg"]') + " {")
for i in range(total):
    out.append(f"    %k{i} = pyc.constant {i % 256} : i8")
for i in range(total):
    out.append(f"    %x{i} = pyc.add %incr, %k{i} : i8, i8 -> i8")
for i in range(n_light):
    out.append(f'    %q{i} = pyc.instance %clk, %rst, %x{i} {{callee = @wlight, name = "l{i}"}} : (!pyc.clock, !pyc.reset, i8) -> i8')
for i in range(n_nest):
    j = n_light + i
    out.append(f'    %q{j} = pyc.instance %clk, %rst, %x{j} {{callee = @wnest, name = "n{i}"}} : (!pyc.clock, !pyc.reset, i8) -> i8')
for i in range(n_heavy):
    j = n_light + n_nest + i
    out.append(f'    %q{j} = pyc.instance %clk, %rst, %x{j} {{callee = @wheavy, name = "h{i}"}} : (!pyc.clock, !pyc.reset, i8) -> i8')
acc = "%q0"
for i in range(1, total):
    out.append(f"    %agg{i} = pyc.xor {acc}, %q{i} : i8, i8 -> i8")
    acc = f"%agg{i}"
out.append(f"    func.return {acc} : i8")
out.append("  }")
out.append("}")
print("\n".join(out))

#!/usr/bin/env python3
"""分析 boom_modstats.txt 的模块层级树：统计各候选裁剪顶层（BoomTile /
BoomCore / BoomFrontend / BoomNonBlockingDCache 等）子树的模块数与寄存器数，
并与 TestHarness 总量对比，评估裁剪后保留的规模比例。

boom_modstats.txt 每行: <module> <num_regs> <instantiated_children...>
（children 为模块名，无后缀区分实例；按名字建树，取首次出现位置）。"""
import sys
from collections import defaultdict

stats_path = sys.argv[1] if len(sys.argv) > 1 else \
    "/home/zhangzijie/pyCircuit/compiler/mlir/test/Inputs/boom_modstats.txt"

mods = {}          # name -> regs
children = {}      # name -> [child names]
for line in open(stats_path):
    p = line.split()
    if len(p) < 2:
        continue
    name, regs = p[0], int(p[1])
    kids = [c for c in p[2:] if c in mods or True]  # forward refs allowed
    mods.setdefault(name, regs)
    children.setdefault(name, [])
    children[name].extend(p[2:])

# fix forward references: children referenced before defined are fine,
# we only need names present in mods for tree walking
children = {n: [c for c in ks if c in mods] for n, ks in children.items()}

ROOT = "TestHarness"

def subtree(root):
    """BFS collect unique module names under root (inclusive)."""
    seen, stack = set(), [root]
    while stack:
        n = stack.pop()
        if n in seen or n not in mods:
            continue
        seen.add(n)
        stack.extend(children.get(n, []))
    return seen

def report(name):
    if name not in mods:
        print(f"  {name}: NOT FOUND")
        return
    sub = subtree(name)
    regs = sum(mods[m] for m in sub)
    n = len(sub)
    print(f"  {name:35s} modules={n:5d}  regs={regs:7d}")
    return n, regs

total_mods = len(mods)
total_regs = sum(mods.values())
print(f"TestHarness total: modules={total_mods} regs={total_regs}")
print()

cands = ["BoomTile", "BoomCore", "BoomFrontend", "BoomNonBlockingDCache",
         "LSU", "FpPipeline", "PTW", "Rob", "IssueUnitCollapsing",
         "FetchTargetQueue", "BranchPredictor", "CSRFile",
         "TLXbar_MasterXbar_BoomTile_i2_o1_a32d128s4k4z4c",
         "DigitalTop", "SystemBus"]
for c in cands:
    report(c)

print()
print("== 占比（相对 TestHarness）==")
for c in ["BoomTile", "BoomCore", "DigitalTop"]:
    if c in mods:
        sub = subtree(c)
        regs = sum(mods[m] for m in sub)
        print(f"  {c:10s} modules {len(sub)}/{total_mods} = {100*len(sub)/total_mods:.1f}%"
              f"   regs {regs}/{total_regs} = {100*regs/total_regs:.1f}%")

# BoomTile 子树内含多少 AsyncQueue/跨时钟域残留
print()
print("== BoomTile 子树内的跨时钟域/异步残留 ==")
tile = subtree("BoomTile")
for pat in ["AsyncQueue", "ClockCrossingReg", "AsyncResetSynchronizerShiftReg",
            "AsyncValidSync", "ClockSink", "FixedClockBroadcast", "ClockGroup"]:
    hits = [m for m in tile if pat in m]
    if hits:
        print(f"  {pat}: {len(hits)} 个模块（如 {hits[:3]}）")

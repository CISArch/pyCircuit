#!/usr/bin/env bash
# gen_trace.sh — 从 .S 汇编生成 Rocket-pyc 可回放的 ST trace 并对拍
#
# 流程：clang 汇编 → ld.lld 零重定位链接 → elf2imem.py → Verilator golden
#       自由跑 → （可选）判定 PASS/FAIL → rocket_sim 回放对拍
#
# 用法：scripts/gen_trace.sh <prog.S> [cycles]
#   产物写入 build/<prog>/：<prog>.{o,elf,hex,st} 与 replay_diff.txt
#   判定口径：程序最后一条 store 的地址 —— 0x80=PASS / 0x88=FAIL
set -euo pipefail

TESTS_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"   # designs/Rocket-pyc/tests
DESIGN_DIR="$(cd "$TESTS_DIR/.." && pwd)"                       # designs/Rocket-pyc
GOLDEN_TB="$TESTS_DIR/tb/tb_rocket_pgm.v"
VLOG_DIR="${ROCKET_GOLDEN_VERILOG:-$HOME/rocket-chip-v16/generated-verilog}"
SIM="${ROCKET_SIM:-$DESIGN_DIR/sim/build/rocket_sim}"

SRC="$(readlink -f "$1")"; PROG="$(basename "${SRC%.*}")"
CYCLES="${2:-1500}"
OUT="$TESTS_DIR/build/$PROG"; mkdir -p "$OUT"

echo "[1/5] assemble+link: $PROG"
clang --target=riscv64-unknown-elf -march=rv64ima -c "$SRC" -o "$OUT/$PROG.o"
ld.lld --image-base=0 -Ttext=0 --no-relax "$OUT/$PROG.o" -o "$OUT/$PROG.elf"
python3 "$TESTS_DIR/scripts/elf2imem.py" "$OUT/$PROG.elf" "$OUT/$PROG.hex"

echo "[2/5] verilator golden (tb_rocket_pgm.v), $CYCLES cycles"
if [[ ! -x "$OUT/vobj/sim_pgm" || "$GOLDEN_TB" -nt "$OUT/vobj/sim_pgm" ]]; then
    verilator --binary --timing --x-initial 0 -DSYNTHESIS -Wno-fatal \
        "$VLOG_DIR"/*.v "$GOLDEN_TB" --top-module tb_Rocket \
        -o sim_pgm --Mdir "$OUT/vobj" > "$OUT/vlt_build.log" 2>&1
fi
"$OUT/vobj/sim_pgm" +imem="$OUT/$PROG.hex" +cycles="$CYCLES" \
    > "$OUT/$PROG.st" 2> "$OUT/$PROG.stderr" || true
# 去掉末尾 Verilator 统计行（walltime 非确定）
grep '^ST ' "$OUT/$PROG.st" > "$OUT/$PROG.st.tmp" && mv "$OUT/$PROG.st.tmp" "$OUT/$PROG.st"

echo "[3/5] verdict（最后一条 store 地址：128=PASS / 136=FAIL）"
LAST_ST=$(awk '$39==1 && $42==1 {a=$40} END {print a+0}' "$OUT/$PROG.st")
if   [[ "$LAST_ST" == 128 ]]; then echo "  PASS"
elif [[ "$LAST_ST" == 136 ]]; then echo "  FAIL"; exit 2
else echo "  NO-VERDICT（最后 store addr=$LAST_ST，判定型程序请检查）"; fi

echo "[4/5] rocket_sim replay"
"$SIM" "$OUT/$PROG.st" "$CYCLES" > "$OUT/cpp_$PROG.st" 2> "$OUT/cpp_$PROG.stderr" || true
grep '^ST ' "$OUT/cpp_$PROG.st" > "$OUT/cpp_$PROG.st.tmp" && mv "$OUT/cpp_$PROG.st.tmp" "$OUT/cpp_$PROG.st"

echo "[5/5] 逐列对拍（golden 行末 77 输出列 vs runner 第 3 列起）"
python3 - "$OUT/$PROG.st" "$OUT/cpp_$PROG.st" "$OUT/replay_diff.txt" <<'PY'
import sys
v=[l.split() for l in open(sys.argv[1]) if l.startswith('ST ')]
c=[l.split() for l in open(sys.argv[2]) if l.startswith('ST ')]
n=len(c[0])-2 if c else 0
diffs=[(i,[ (j,a[-n:][j],c[i][2:][j]) for j in range(n) if a[-n:][j]!=c[i][2:][j]][:3])
       for i,(a,b) in enumerate(zip(v,c)) if a[-n:]!=b[2:]]
open(sys.argv[3],'w').write('\n'.join(f"t={i} {cols}" for i,cols in diffs)+'\n')
status = 'MATCH' if not diffs and len(v)==len(c) else f'DIFF rows={len(diffs)}/{len(v)}'
print(f"  {len(v)} cycles x {n} outputs: {status}")
PY
echo "done: $OUT"

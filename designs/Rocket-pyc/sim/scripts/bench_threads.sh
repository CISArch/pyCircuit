#!/bin/bash
# Rocket-pyc：单线程基线 vs 多线程 tick 的等价性 + 吞吐对比。
#
# 用法：
#   bash scripts/bench_threads.sh
#   PYC_FLAT_BIN=/abs/sim_flat PYC_MT_BIN=/abs/sim_mt \
#     PYC_BENCH_CYCLES=10000 PYC_THREAD_LIST="1 2 4 8" PYC_BENCH_REPEAT=3 \
#     bash scripts/bench_threads.sh
#
# 未指定二进制时自动用 gen.sh / build.sh 构建两份：
#   PYC_PARALLEL_TICK=0 -> 平铺/串行 baseline
#   PYC_PARALLEL_TICK=1 -> 层级导入 + --cpp-parallel-tick（运行时由 PYC_THREADS 控制）
# 环境变量：PYC_TRACE、PYC_BENCH_DIR、PYC_BENCH_CYCLES、PYC_BENCH_REPEAT、
#   PYC_THREAD_LIST、PYC_TICK_CHUNK、PYC_TICK_PARTITION、PYC_TP_STATS。
set -euo pipefail

HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
TRACE="${PYC_TRACE:-/home/zhangzijie/verilog2pyc/build/check_Rocket/golden.st}"
WORK="${PYC_BENCH_DIR:-/tmp/pyc-rocket-bench}"
CYCLES="${PYC_BENCH_CYCLES:-10000}"
REPEAT="${PYC_BENCH_REPEAT:-3}"
THREAD_LIST="${PYC_THREAD_LIST:-1 2 4 8}"
mkdir -p "$WORK"

# 波形不足 CYCLES 拍时按行重复（runner 只按列取输入，忽略 "ST" 后的 tick 序号）。
python3 - "$TRACE" "$WORK/trace.st" "$CYCLES" <<'PY'
import sys
src, dst, need = sys.argv[1], sys.argv[2], int(sys.argv[3])
lines = [l for l in open(src) if l.startswith("ST ")]
with open(dst, "w") as f:
    for _ in range((need + len(lines) - 1) // len(lines)):
        f.writelines(lines)
print(f"[bench] trace: {len(lines)} source cycles -> >= {need} cycles")
PY

build_one() {
    local mode="$1" gen="$WORK/gen$1" bin="$WORK/sim_$1"
    [[ -x "$bin" ]] && return 0
    echo "[bench] building PYC_PARALLEL_TICK=$mode -> $bin"
    PYC_PARALLEL_TICK="$mode" ROCKET_GEN_DIR="$gen" ROCKET_SIM_BIN="$bin" \
        PYC_TICK_CHUNK="${PYC_TICK_CHUNK:-1}" \
        PYC_TICK_PARTITION="${PYC_TICK_PARTITION:-weighted}" \
        bash "$HERE/scripts/gen.sh" > "$WORK/gen$1.log" 2>&1
    PYC_PARALLEL_TICK="$mode" ROCKET_GEN_DIR="$gen" ROCKET_SIM_BIN="$bin" \
        bash "$HERE/scripts/build.sh" > "$WORK/build$1.log" 2>&1
}

FLAT="${PYC_FLAT_BIN:-}"
MT="${PYC_MT_BIN:-}"
if [[ -z "$FLAT" || -z "$MT" ]]; then
    build_one 0
    build_one 1
    FLAT="${FLAT:-$WORK/sim_0}"
    MT="${MT:-$WORK/sim_1}"
fi
[[ -x "$FLAT" && -x "$MT" ]] || { echo "error: binaries missing: $FLAT / $MT" >&2; exit 2; }

# 功能等价：单线程基线的逐拍输出必须与每个线程数的输出完全一致。
PYC_TP_STATS=0 "$FLAT" "$WORK/trace.st" "$CYCLES" > "$WORK/out_flat.st"
for t in $THREAD_LIST; do
    PYC_TP_STATS=0 PYC_THREADS="$t" "$MT" "$WORK/trace.st" "$CYCLES" > "$WORK/out_t${t}.st"
    if ! diff -q "$WORK/out_flat.st" "$WORK/out_t${t}.st" > /dev/null; then
        echo "[bench] FAIL: PYC_THREADS=$t diverged from flat baseline" >&2
        exit 1
    fi
done
echo "[bench] equivalence: flat == PYC_THREADS=[$THREAD_LIST] ($CYCLES cycles, $(wc -l < "$WORK/out_flat.st") ST lines)"

# 吞吐：固定总拍数，重复 REPEAT 次取总时间。
: > "$WORK/results.tsv"
bench() {
    local label="$1" bin="$2" t="$3" s e
    s=$(date +%s.%N)
    for _ in $(seq 1 "$REPEAT"); do
        PYC_TP_STATS=0 PYC_THREADS="$t" "$bin" "$WORK/trace.st" "$CYCLES" > /dev/null
    done
    e=$(date +%s.%N)
    printf '%s\t%s\t%s\t%s\t%s\n' "$label" "$t" "$CYCLES" "$REPEAT" "$s $e" >> "$WORK/results.tsv"
}
bench "flat baseline" "$FLAT" 1
for t in $THREAD_LIST; do bench "hier + parallel tick" "$MT" "$t"; done

python3 - "$WORK/results.tsv" <<'PY'
import sys
rows = []
for line in open(sys.argv[1]):
    lab, t, cyc, rep, times = line.rstrip("\n").split("\t")
    s, e = map(float, times.split())
    rows.append((lab, int(t), int(cyc) * int(rep), e - s))
base = rows[0][2] / rows[0][3] / 1000
print(f"{'config':<24}{'threads':>9}{'cycles':>10}{'dt(s)':>10}{'kcycles/s':>12}{'vs flat':>10}")
for lab, t, cyc, dt in rows:
    kc = cyc / dt / 1000
    print(f"{lab:<24}{t:>9}{cyc:>10}{dt:>9.3f}{kc:>12.1f}{kc / base:>9.2f}x")
PY

if [[ "${PYC_TP_STATS:-0}" == "1" ]]; then
    echo "[bench] thread pool stats (PYC_THREADS=4, first 7 lines):"
    PYC_TP_STATS=1 PYC_THREADS=4 "$MT" "$WORK/trace.st" "$CYCLES" \
        > /dev/null 2> "$WORK/tp_stats.txt"
    head -7 "$WORK/tp_stats.txt"
fi

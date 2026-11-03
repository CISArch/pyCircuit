#!/bin/bash
# Verilator 基线 cycles/s  vs  pyCircuit C++ 多线程 cycles/s 的性能对比测试。
#
# 对标 DavinciBaseLine/auto_perf 的「PyCircuit / Verilator 吞吐矩阵」：
#   auto_perf 自身是 CI 调度层，真正的测量在 model/rtl/run_pycircuit_trace_align.sh
#   （6 步：trace -> hints、pycc --emit=cpp、pycc --emit=verilog、C++ runner、
#    verilator --cc --build、compare），由 replay_pycircuit_trace.py 换算
#   cycles_per_s = cycles / (elapsed_ms/1000)，结果行含
#   cycles_per_s / verilator_cycles_per_s / pycircuit_to_verilator_ratio /
#   common_metrics_match（auto_perf/src/auto_perf/runner.py:315-337）。
#
# 本脚本在 pyCircuit 内用 Rocket-pyc 链路复刻同一套对比，但把「被测后端」换成
# 开启 --cpp-parallel-tick 的 pyCircuit C++ 模型：
#   [1/4] Verilator 基线：g_Rocket（golden Verilator 二进制），输出 ST 行数 = cycles
#   [2/4] 用同一份 ST 激励构造长波形（runner 只按列取输入，忽略 tick 序号）
#   [3/4] 功能等价：每个线程数回放基线的周期数，与 Verilator 输出逐行 diff
#         （等价 auto_perf 的 common_metrics_match）
#   [4/4] 吞吐：固定总拍数重复计时，输出 cycles/s 表 + comparison.json
#
# 口径（与 auto_perf 的差异，写进 comparison.json）：
#   - 分子：Verilator = 输出 ST 行数；C++ = runner 主循环次数（ncycles）
#   - 分母：进程外 date +%s.%N 墙钟，含进程启动/读 trace，不含编译；
#           auto_perf 用 runner 进程内 steady_clock(ms)
#   - 两侧 stdout 均丢弃，同 -O2/-O3 由各自构建产物决定；编译耗时不计入
#   - Verilator 每次固定 400 拍（TB $finish），C++ 每次 PYC_BENCH_CYCLES 拍；
#     cycles/s 是归一化吞吐率，repeat 次数用于摊薄进程启动开销
#
# 用法：
#   bash scripts/bench_verilator_vs_mt.sh
#   PYC_BENCH_CYCLES=10000 PYC_BENCH_REPEAT=3 PYC_THREAD_LIST="1 2 4 8" \
#     PYC_PERF_MIN_RATIO=0.8 bash scripts/bench_verilator_vs_mt.sh
# 参数（环境变量）：
#   PYC_VERILATOR_BIN   默认 v2p check_Rocket/golden/vobj/g_Rocket（可换 p_Rocket）
#   PYC_MT_BIN          默认 build/rocket_sim（不存在则自动 gen.sh+build.sh 构建）
#   PYC_BENCH_DIR       默认 /tmp/pyc-verilator-vs-mt
#   PYC_BENCH_CYCLES / PYC_BENCH_REPEAT / PYC_THREAD_LIST
#   PYC_TICK_CHUNK / PYC_TICK_PARTITION（自动构建时）
#   PYC_PERF_MIN_RATIO  可选回归阈值：任一线程数 P/V 低于它则 exit 1
#   PYC_TP_STATS=1      末尾单独打印线程池负载（计时阶段强制关闭）
set -euo pipefail

HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
V2P_CHECK="${PYC_V2P_CHECK_DIR:-/home/zhangzijie/verilog2pyc/build/check_Rocket}"
VBIN="${PYC_VERILATOR_BIN:-$V2P_CHECK/golden/vobj/g_Rocket}"
MT="${PYC_MT_BIN:-$HERE/build/rocket_sim}"
WORK="${PYC_BENCH_DIR:-/tmp/pyc-verilator-vs-mt}"
CYCLES="${PYC_BENCH_CYCLES:-10000}"
REPEAT="${PYC_BENCH_REPEAT:-3}"
THREAD_LIST="${PYC_THREAD_LIST:-1 2 4 8}"
MIN_RATIO="${PYC_PERF_MIN_RATIO:-}"
mkdir -p "$WORK"

# [0/4] 多线程 C++ 模型缺失时自动构建（层级导入 + --cpp-parallel-tick + -pthread）。
if [[ ! -x "$MT" ]]; then
    echo "[bench] building multithreaded C++ model -> $WORK/rocket_sim_mt"
    PYC_PARALLEL_TICK=1 ROCKET_GEN_DIR="$WORK/gen" ROCKET_SIM_BIN="$WORK/rocket_sim_mt" \
        PYC_TICK_CHUNK="${PYC_TICK_CHUNK:-1}" \
        PYC_TICK_PARTITION="${PYC_TICK_PARTITION:-weighted}" \
        bash "$HERE/scripts/gen.sh" > "$WORK/gen.log" 2>&1
    PYC_PARALLEL_TICK=1 ROCKET_GEN_DIR="$WORK/gen" ROCKET_SIM_BIN="$WORK/rocket_sim_mt" \
        bash "$HERE/scripts/build.sh" > "$WORK/build.log" 2>&1
    MT="$WORK/rocket_sim_mt"
fi
[[ -x "$VBIN" ]] || { echo "error: verilator binary missing: $VBIN (set PYC_VERILATOR_BIN)" >&2; exit 2; }

# [1/4] 基线：跑一次拿到 ST 输出（即两侧共用的激励/期望），再重复计时。
echo "[1/4] verilator baseline: $VBIN"
"$VBIN" 2> "$WORK/verilator.stderr" | grep '^ST ' > "$WORK/verilator.st"
V_CYCLES=$(grep -c '^ST ' "$WORK/verilator.st" || true)
[[ "$V_CYCLES" -gt 0 ]] || { echo "error: verilator produced no ST lines" >&2; exit 2; }
s=$(date +%s.%N)
for _ in $(seq 1 "$REPEAT"); do
    "$VBIN" > /dev/null 2>&1
done
e=$(date +%s.%N)
printf 'verilator\t1\t%s\t%s\t%s %s\n' "$V_CYCLES" "$REPEAT" "$s" "$e" > "$WORK/results.tsv"

# [2/4] 同一份 ST 激励重复到 CYCLES 拍，供 C++ 侧长跑。
python3 - "$WORK/verilator.st" "$WORK/trace.st" "$CYCLES" <<'PY'
import sys
src, dst, need = sys.argv[1], sys.argv[2], int(sys.argv[3])
lines = [l for l in open(src) if l.startswith("ST ")]
with open(dst, "w") as f:
    for _ in range((need + len(lines) - 1) // len(lines)):
        f.writelines(lines)
print(f"[2/4] shared stimulus: {len(lines)} ST lines -> >= {need} cycles")
PY

# [3/4] 功能等价：Verilator ST 行 = ST tick + 28 inputs + 77 outputs；
# C++ runner 输出 = ST cyc + 77 outputs，因此只比较共有的输出列（等价 auto_perf
# 的 common_metrics_match：后端无关的确定性指标必须一致）。
echo "[3/4] functional equivalence (verilator vs pycircuit, $V_CYCLES cycles)"
MATCH=1
for t in $THREAD_LIST; do
    PYC_TP_STATS=0 PYC_THREADS="$t" "$MT" "$WORK/verilator.st" "$V_CYCLES" \
        > "$WORK/cpp_t${t}.st" 2> "$WORK/cpp_t${t}.stderr"
    python3 - "$WORK/verilator.st" "$WORK/cpp_t${t}.st" \
        "$WORK/diff_t${t}.txt" "$WORK/equiv_t${t}.flag" <<'PY'
import sys
v = [l.split() for l in open(sys.argv[1]) if l.startswith("ST ")]
c = [l.split() for l in open(sys.argv[2]) if l.startswith("ST ")]
n_out = len(c[0]) - 2 if c else 0
diffs = []
if len(v) != len(c):
    diffs.append(f"line count verilator={len(v)} cpp={len(c)}")
for i, (a, b) in enumerate(zip(v, c)):
    if a[-n_out:] != b[2:]:
        diffs.append(f"@{i}: verilator_out={a[-n_out:][:6]}... cpp_out={b[2:][:6]}...")
        if len(diffs) >= 10:
            break
open(sys.argv[3], "w").write("\n".join(diffs) + "\n")
open(sys.argv[4], "w").write("DIFF" if diffs else "MATCH")
print(f"[3/4] {len(v)} cycles x {n_out} output columns: {'MATCH' if not diffs else 'DIFF'}")
PY
    if [[ "$(cat "$WORK/equiv_t${t}.flag")" != "MATCH" ]]; then
        echo "[bench] FAIL: PYC_THREADS=$t diverged from verilator baseline" >&2
        MATCH=0
    fi
done
[[ "$MATCH" == "1" ]] && echo "[3/4] common_metrics_match: MATCH" \
    || echo "[3/4] common_metrics_match: DIFF (see $WORK/diff_t*.txt)" >&2

# [4/4] 吞吐：每个线程数固定 CYCLES×REPEAT 拍，计时阶段关闭 TP_STATS 避免 I/O 干扰。
echo "[4/4] throughput"
for t in $THREAD_LIST; do
    s=$(date +%s.%N)
    for _ in $(seq 1 "$REPEAT"); do
        PYC_TP_STATS=0 PYC_THREADS="$t" "$MT" "$WORK/trace.st" "$CYCLES" > /dev/null
    done
    e=$(date +%s.%N)
    printf 'cpp_mt\t%s\t%s\t%s\t%s %s\n' "$t" "$CYCLES" "$REPEAT" "$s" "$e" >> "$WORK/results.tsv"
done

python3 - "$WORK/results.tsv" "$WORK/comparison.json" "$MATCH" "$MIN_RATIO" \
        "$VBIN" "$MT" "$V_CYCLES" "$CYCLES" "$REPEAT" "$THREAD_LIST" <<'PY'
import json, sys

tsv, out, match, min_ratio, vbin, mt, v_cycles, cycles, repeat, threads = sys.argv[1:]
rows = []
for line in open(tsv):
    backend, t, cyc, rep, times = line.rstrip("\n").split("\t")
    s, e = map(float, times.split())
    total = int(cyc) * int(rep)
    wall = e - s
    rows.append({
        "backend": backend,
        "threads": int(t),
        "cycles_per_run": int(cyc),
        "simulated_cycles": total,
        "repeats": int(rep),
        "sim_wall_time_s": wall,
        "cycles_per_s": (total / wall) if wall > 0 else None,
    })
v = rows[0]
v_rate = v["cycles_per_s"]
comparison_rows = []
for r in rows[1:]:
    ratio = (r["cycles_per_s"] / v_rate) if (v_rate and r["cycles_per_s"]) else None
    comparison_rows.append({
        "threads": r["threads"],
        "simulated_cycles": r["simulated_cycles"],
        "verilator_simulated_cycles": v["simulated_cycles"],
        "sim_wall_time_s": r["sim_wall_time_s"],
        "cycles_per_s": r["cycles_per_s"],
        "verilator_cycles_per_s": v_rate,
        "verilator_sim_wall_time_s": v["sim_wall_time_s"],
        "pycircuit_to_verilator_ratio": ratio,
        "common_metrics_match": match == "1",
    })

result = {
    "baseline": {
        "backend": "verilator",
        "binary": vbin,
        "cycles_per_run": int(v_cycles),
        "simulated_cycles": v["simulated_cycles"],
        "sim_wall_time_s": v["sim_wall_time_s"],
        "cycles_per_s": v_rate,
    },
    "pycircuit_mt": {
        "binary": mt,
        "emission": "--cpp-parallel-tick (hierarchical pyc.instance parts)",
        "thread_control": "PYC_THREADS",
        "rows": comparison_rows,
    },
    "common_metrics_match": match == "1",
    "formula": "cycles_per_s = simulated_cycles / sim_wall_time_s",
    "timing": {
        "scope": "process wall clock (date +%s.%N), stdout discarded, compile time excluded",
        "auto_perf_difference": "auto_perf uses in-process std::chrono::steady_clock (ms)",
        "cycles_definition": {
            "verilator": "count of ST output lines",
            "pycircuit_cpp": "runner main-loop iterations (ncycles)",
        },
        "cycles_per_run": {"verilator": int(v_cycles), "pycircuit_cpp": int(cycles)},
        "repeats": int(repeat),
    },
    "config": {"threads": threads, "cycles": int(cycles), "repeat": int(repeat)},
}
with open(out, "w") as f:
    json.dump(result, f, indent=2)

print(f"{'backend':<30}{'threads':>9}{'cycles':>11}{'wall_s':>10}"
      f"{'cycles/s':>14}{'kcycles/s':>12}{'P/V':>9}")
print(f"{'verilator (baseline)':<30}{v['threads']:>9}{v['simulated_cycles']:>11}"
      f"{v['sim_wall_time_s']:>10.3f}{v_rate:>14.0f}{v_rate/1000:>12.1f}{1.0:>8.2f}x")
for r in comparison_rows:
    rate = r["cycles_per_s"]
    ratio = r["pycircuit_to_verilator_ratio"]
    print(f"{'pycircuit cpp + parallel tick':<30}{r['threads']:>9}"
          f"{r['simulated_cycles']:>11}{r['sim_wall_time_s']:>10.3f}"
          f"{rate:>14.0f}{rate/1000:>12.1f}{ratio:>8.2f}x")

if match != "1":
    print("[bench] FAIL: functional equivalence broke", file=sys.stderr)
    sys.exit(1)
if min_ratio:
    floor = float(min_ratio)
    bad = [r for r in comparison_rows
           if r["pycircuit_to_verilator_ratio"] is None
           or r["pycircuit_to_verilator_ratio"] < floor]
    if bad:
        print(f"[bench] FAIL: P/V < {floor} for threads="
              f"{[r['threads'] for r in bad]}", file=sys.stderr)
        sys.exit(1)
print(f"[bench] PASS  artifacts: {out}")
PY

if [[ "${PYC_TP_STATS:-0}" == "1" ]]; then
    echo "[bench] thread pool stats (PYC_THREADS=4, first 7 lines):"
    PYC_TP_STATS=1 PYC_THREADS=4 "$MT" "$WORK/trace.st" "$CYCLES" \
        > /dev/null 2> "$WORK/tp_stats.txt"
    head -7 "$WORK/tp_stats.txt"
fi

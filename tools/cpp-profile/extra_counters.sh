#!/usr/bin/env bash
# 扩展硬件计数器 pass:对每条 trace 的 runner 跑一次 perf stat,采集
# I-cache / D-cache / LLC / TLB 缺失与分支行为,用于判断“指令足迹 vs 数据足迹”瓶颈。
#
# 结果写 runs/<trace>/perf.stat2.txt;矩阵脚本里的基础计数器在 perf.stat.txt。
set -uo pipefail

ROOT=${ROOT:-/home/ldz/pycircuit-workspace/logs/cpp-perf-profiling}
RUNNER=${RUNNER:-$ROOT/cpp/pycircuit_trace_runner}
DRAIN=${DRAIN:-512}
# 与 flat pass 同口径:限周期保证墙钟可控(计数器比率与周期数无关)
export V5_TRACE_MAX_CYCLES=${V5_TRACE_MAX_CYCLES:-4000}
EVENTS=${EVENTS:-cycles:u,instructions:u,branch-instructions:u,branch-misses:u,\
L1-icache-load-misses:u,L1-dcache-load-misses:u,LLC-load-misses:u,\
dTLB-load-misses:u,iTLB-load-misses:u,stalled-cycles-frontend:u,stalled-cycles-backend:u}

for run in "$ROOT"/runs/*/; do
  [[ -f "$run/hints.txt" ]] || continue
  stem=$(basename "$run")
  [[ -s "$run/perf.stat2.txt" ]] && continue
  echo "=== $stem ==="
  sudo perf stat -e "$EVENTS" -o "$run/perf.stat2.txt" -- \
    "$RUNNER" "$run/hints.txt" "$DRAIN" "$run/replay-stat2.json" >/dev/null 2>&1
  sudo chown "$(id -u):$(id -g)" "$run/perf.stat2.txt" 2>/dev/null
  grep -E "cycles:u|instructions:u|L1-icache|stalled" "$run/perf.stat2.txt" | head -4
done
echo done

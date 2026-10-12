#!/usr/bin/env bash
# 在 DavinciBaseLine 上对生成的 C++ model 做逐 trace 采样剖析。
#
#   - 结果全部落在 $ROOT/runs/<trace>/ 下(perf.data / perf.script.txt / trace.pftrace /
#     report.json / flame.svg / meta.json),可复用、可深挖。
#   - 采样用 sudo perf record(容器内 perf_event_paranoid=4,非 root 无法 perf_event_open)。
#   - 每个 trace 先做一次不限时长的“计时跑”,据此决定重复次数,保证采样数充足。
#
# 用法: run_profile_matrix.sh [trace ...]      (缺省全部 34 条)
set -uo pipefail

ROOT=${ROOT:-/home/ldz/pycircuit-workspace/logs/cpp-perf-profiling}
PYCROOT=${PYCROOT:-/home/ldz/pycircuit-workspace/pyCircuit-cpp-perf}
DAVINCI=${DAVINCI:-/home/ldz/pycircuit-workspace/DavinciBaseLine}
RUNNER=${RUNNER:-$ROOT/prof-ws/pycircuit_trace_runner}
GENERATED=${GENERATED:-$ROOT/dev-cpp/cpp}
TOOLS=$ROOT/tools
TRACE_DIR=$DAVINCI/model/tests/fixtures/traces
TARGET_SECONDS=${TARGET_SECONDS:-3.0}
PERF_HZ=${PERF_HZ:-4000}
DRAIN=${DRAIN:-512}
# fp   = 需要 -fno-omit-frame-pointer 构建(体积小、可 annotate)
# dwarf= 任意 -O3 构建可用(体积大、无需重建)
CALLGRAPH=${CALLGRAPH:-fp}
KEEP_PERF_DATA=${KEEP_PERF_DATA:-1}
if [[ "$CALLGRAPH" == dwarf* ]]; then
  CG_ARG=(--call-graph dwarf,2048)
else
  CG_ARG=(--call-graph fp)
fi

export PYTHONPATH="$DAVINCI/srcs/core:$PYCROOT/compiler/frontend${PYTHONPATH:+:$PYTHONPATH}"
export PYCIRCUIT_ROOT="$PYCROOT"
export LD_LIBRARY_PATH="$PYCROOT/.pycircuit_out/toolchain/install/lib${LD_LIBRARY_PATH:+:$LD_LIBRARY_PATH}"
RUNS_DIR=${RUNS_DIR:-$ROOT/runs}
PYTHON=$(command -v python3)

if [[ $# -gt 0 ]]; then
  TRACES=("$@")
else
  mapfile -t TRACES < <(ls "$TRACE_DIR"/*.pto.trace)
fi

command -v perf >/dev/null || { echo "perf missing" >&2; exit 1; }
[[ -x "$RUNNER" ]] || { echo "runner missing: $RUNNER" >&2; exit 1; }

for trace in "${TRACES[@]}"; do
  stem=$(basename "$trace" .pto.trace)
  run="$RUNS_DIR/$stem"
  mkdir -p "$run"
  echo "=== $stem ==="

  # 1) trace -> hints(纯 Python,无需 root)
  if [[ ! -s "$run/hints.txt" ]]; then
    "$PYTHON" "$DAVINCI/model/rtl/replay_pycircuit_trace.py" --trace "$trace" \
      --workspace "$run/conv" --convert-only >"$run/convert.log" 2>&1 || {
        echo "convert failed: $stem" >&2; continue; }
    cp "$run/conv/hints.txt" "$run/hints.txt"
    cp "$run/conv/conversion.json" "$run/conversion.json" 2>/dev/null || true
  fi

  # 2) 计时跑:决定重复次数
  t0=$(date +%s.%N)
  "$RUNNER" "$run/hints.txt" "$DRAIN" "$run/replay-timed.json" >/dev/null 2>&1
  t1=$(date +%s.%N)
  elapsed=$(echo "$t1 - $t0" | bc)
  reps=$("$PYTHON" -c "import math,sys;e=float(sys.argv[1]);print(max(1,min(20,math.ceil($TARGET_SECONDS/max(e,0.05)))))" "$elapsed")

  # 3) 采样跑(重复 reps 次,单次 perf record 会话)
  sudo rm -f "$run/perf.data"
  sudo perf record -o "$run/perf.data" -F "$PERF_HZ" -e cycles:u -g "${CG_ARG[@]}" \
    -- bash -c "for i in \$(seq $reps); do \"$RUNNER\" \"$run/hints.txt\" \"$DRAIN\" \"$run/replay.json\" >/dev/null 2>&1; done" \
    >"$run/perf-record.log" 2>&1

  # 4) 计数器统计(IPC / cache miss / branch miss)
  sudo perf stat -e cycles:u,instructions:u,branch-instructions:u,branch-misses:u,cache-references:u,cache-misses:u \
    -o "$run/perf.stat.txt" -- "$RUNNER" "$run/hints.txt" "$DRAIN" "$run/replay-stat.json" \
    >/dev/null 2>&1

  # 5) 文本化与聚合
  sudo perf script -i "$run/perf.data" --inline >"$run/perf.script.raw" 2>/dev/null
  sudo perf report --stdio -i "$run/perf.data" --sort symbol -g none >"$run/perf.report.txt" 2>/dev/null
  sudo chown -R "$(id -u):$(id -g)" "$run" 2>/dev/null

  "$PYTHON" "$TOOLS/prof_tools.py" convert "$run/perf.script.raw" "$run/trace.pftrace" \
    --process "pycircuit:$stem" >"$run/convert-pftrace.json" 2>"$run/convert-pftrace.err"
  "$PYTHON" "$TOOLS/prof_tools.py" report "$run/perf.script.raw" "$run/report.json" \
    --top 60 >/dev/null 2>&1
  "$PYTHON" "$TOOLS/prof_tools.py" flame "$run/perf.script.raw" "$run/flame.svg" \
    --title "$stem" >/dev/null 2>&1
  "$PYTHON" "$TOOLS/prof_tools.py" json "$run/perf.script.raw" "$run/trace.json" >/dev/null 2>&1

  # 6) 可选:用 traceconv 生成官方风格 trace(存在则优先)
  if [[ -x "$TOOLS/tracebox" ]]; then
    "$TOOLS/tracebox" traceconv perf "$run/perf.data" "$run/trace.official.pftrace" \
      >"$run/traceconv.log" 2>&1 || true
  fi
  # 大文件策略:dwarf 的 perf.data 可达百 MB,压缩保留原文,raw 在压缩后删除
  gzip -9 -f "$run/perf.script.raw" 2>/dev/null || true

  # 7) 逐符号注解(热符号的指令/源码行级)
  top_syms=$("$PYTHON" - "$run/report.json" <<'PY'
import json,sys
rep=json.load(open(sys.argv[1]))
out=[]
for row in rep.get("self_top",[])[:6]:
    s=row["symbol"]
    if s.startswith("0x") or "[unknown]" in s: continue
    out.append(s)
print("\n".join(out[:4]))
PY
)
  : >"$run/annotate.txt"
  while IFS= read -r sym; do
    [[ -z "$sym" ]] && continue
    echo "########## $sym ##########" >>"$run/annotate.txt"
    sudo perf annotate --stdio -i "$run/perf.data" -s "$sym" 2>/dev/null | head -80 >>"$run/annotate.txt"
  done <<<"$top_syms"

  if [[ "$KEEP_PERF_DATA" != 1 ]]; then
    rm -f "$run/perf.data"
  fi

  echo "  reps=$reps elapsed=${elapsed}s samples=$("$PYTHON" -c "
import json;print(json.load(open('$run/report.json'))['samples'])" 2>/dev/null || echo '?')"
done
echo "done: $RUNS_DIR"

#!/usr/bin/env bash
# 轻量“扁平剖面”pass:对还没有调用栈剖面的 trace,用无 -g 的低开销采样
# (perf record -c 50000)→ perf report --sort symbol --show-nr-samples → report-flat.json。
#
# 用途:把 self-sample 相位分布覆盖到全部 34 条 trace;调用栈(火焰图/合并 trace)
# 只对代表性子集做。两种方法的 self 占比已在同一 trace 上交叉验证一致。
#
# 环境:V5_TRACE_MAX_CYCLES 限制每次仿真的周期数,保证墙钟可控(份额与周期数无关)。
set -uo pipefail

ROOT=${ROOT:-/home/ldz/pycircuit-workspace/logs/cpp-perf-profiling}
RUNNER=${RUNNER:-$ROOT/prof-ws/pycircuit_trace_runner}
DAVINCI=${DAVINCI:-/home/ldz/pycircuit-workspace/DavinciBaseLine}
PYCROOT=${PYCROOT:-/home/ldz/pycircuit-workspace/pyCircuit-cpp-perf}
T=$ROOT/tools
DRAIN=${DRAIN:-512}
MAXC=${V5_TRACE_MAX_CYCLES:-4000}
PERIOD=${PERIOD:-50000}

export V5_TRACE_MAX_CYCLES="$MAXC"
export PYTHONPATH="$DAVINCI/srcs/core:$PYCROOT/compiler/frontend${PYTHONPATH:+:$PYTHONPATH}"
export PYCIRCUIT_ROOT="$PYCROOT"
export LD_LIBRARY_PATH="$PYCROOT/.pycircuit_out/toolchain/install/lib${LD_LIBRARY_PATH:+:$LD_LIBRARY_PATH}"

mapfile -t TRACES < <(ls "$DAVINCI"/model/tests/fixtures/traces/*.pto.trace)
for trace in "${TRACES[@]}"; do
  stem=$(basename "$trace" .pto.trace)
  run="$ROOT/runs/$stem"
  mkdir -p "$run"
  [[ -s "$run/flame.svg" ]] && continue        # 已有调用栈剖面,跳过
  [[ -s "$run/report-flat.json" ]] && continue
  echo "=== $stem"

  if [[ ! -s "$run/hints.txt" ]]; then
    python3 "$DAVINCI/model/rtl/replay_pycircuit_trace.py" --trace "$trace" \
      --workspace "$run/conv" --convert-only >"$run/convert.log" 2>&1 || {
        echo "convert failed" >&2; continue; }
    cp "$run/conv/hints.txt" "$run/hints.txt"
    cp "$run/conv/conversion.json" "$run/conversion.json" 2>/dev/null || true
  fi

  t0=$(date +%s.%N)
  "$RUNNER" "$run/hints.txt" "$DRAIN" "$run/replay-flat.json" >/dev/null 2>&1
  t1=$(date +%s.%N)

  sudo rm -f "$run/perf.flat.data" "$run/perf.flat.txt"
  sudo perf record -o "$run/perf.flat.data" -e cycles:u -c "$PERIOD" \
    -- "$RUNNER" "$run/hints.txt" "$DRAIN" "$run/replay-flat.json" \
    >"$run/perf-flat-record.log" 2>&1
  sudo perf report --stdio -f -i "$run/perf.flat.data" --sort symbol \
    --show-nr-samples >"$run/perf.flat.txt" 2>/dev/null
  sudo chown -R "$(id -u):$(id -g)" "$run" 2>/dev/null
  rm -f "$run/perf.flat.data"

  python3 "$T/prof_tools.py" flat "$run/perf.flat.txt" "$run/report-flat.json" >/dev/null
  echo "  elapsed=$(echo "$t1 - $t0" | bc)s samples=$(python3 -c "
import json;print(json.load(open('$run/report-flat.json'))['samples'])" 2>/dev/null || echo '?')"
done
echo done

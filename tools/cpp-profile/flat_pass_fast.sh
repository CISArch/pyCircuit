#!/usr/bin/env bash
# 精简扁平剖面 pass:每条 trace 只跑一次模型(perf record)+ 一次 perf report。
# 目标:把 self-sample 的相位分布覆盖到全部 34 条 trace(墙钟优先)。
set -uo pipefail

ROOT=${ROOT:-/home/ldz/pycircuit-workspace/logs/cpp-perf-profiling}
RUNNER=${RUNNER:-$ROOT/prof-ws/pycircuit_trace_runner}
DAVINCI=${DAVINCI:-/home/ldz/pycircuit-workspace/DavinciBaseLine}
PYCROOT=${PYCROOT:-/home/ldz/pycircuit-workspace/pyCircuit-cpp-perf}
T=$ROOT/tools
DRAIN=${DRAIN:-512}
export V5_TRACE_MAX_CYCLES=${V5_TRACE_MAX_CYCLES:-4000}
PERIOD=${PERIOD:-50000}

export PYTHONPATH="$DAVINCI/srcs/core:$PYCROOT/compiler/frontend${PYTHONPATH:+:$PYTHONPATH}"
export PYCIRCUIT_ROOT="$PYCROOT"
export LD_LIBRARY_PATH="$PYCROOT/.pycircuit_out/toolchain/install/lib${LD_LIBRARY_PATH:+:$LD_LIBRARY_PATH}"

for trace in "$DAVINCI"/model/tests/fixtures/traces/*.pto.trace; do
  stem=$(basename "$trace" .pto.trace)
  run="$ROOT/runs/$stem"
  mkdir -p "$run"
  [[ -s "$run/flame.svg" || -s "$run/report-flat.json" ]] && continue
  echo "=== $stem"
  if [[ ! -s "$run/hints.txt" ]]; then
    python3 "$DAVINCI/model/rtl/replay_pycircuit_trace.py" --trace "$trace" \
      --workspace "$run/conv" --convert-only >"$run/convert.log" 2>&1 || continue
    cp "$run/conv/hints.txt" "$run/hints.txt"
    cp "$run/conv/conversion.json" "$run/conversion.json" 2>/dev/null || true
  fi
  sudo rm -f "$run/perf.flat.data"
  sudo perf record -o "$run/perf.flat.data" -e cycles:u -c "$PERIOD" \
    -- "$RUNNER" "$run/hints.txt" "$DRAIN" "$run/replay-flat.json" \
    >"$run/perf-flat-record.log" 2>&1
  sudo perf report --stdio -f -i "$run/perf.flat.data" --sort symbol \
    --show-nr-samples >"$run/perf.flat.txt" 2>/dev/null
  sudo chown -R "$(id -u):$(id -g)" "$run" 2>/dev/null
  rm -f "$run/perf.flat.data"
  python3 "$T/prof_tools.py" flat "$run/perf.flat.txt" "$run/report-flat.json" >/dev/null
  echo "  samples=$(python3 -c "
import json;print(json.load(open('$run/report-flat.json'))['samples'])" 2>/dev/null || echo '?')"
done
echo done

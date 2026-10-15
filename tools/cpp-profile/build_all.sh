#!/usr/bin/env bash
# 采样跑完之后的一次性收尾:统一重生成 Perfetto trace → 汇总 → 热点回映 → 元数据。
set -euo pipefail
ROOT=${ROOT:-/home/ldz/pycircuit-workspace/logs/cpp-perf-profiling}
GEN=${GEN:-$ROOT/dev-cpp/cpp}
T=$ROOT/tools
PY=python3

echo "[1/5] 逐 trace 重生成 pftrace / json / flame(轨道按进程名聚合)"
for run in "$ROOT"/runs/*/; do
  stem=$(basename "$run")
  script="$run/perf.script.raw"
  [[ -f "$script" ]] || { [[ -f "$script.gz" ]] && script="$script.gz" || continue; }
  "$PY" "$T/prof_tools.py" convert "$script" "$run/trace.pftrace" --process "pycircuit:$stem" >/dev/null
  "$PY" "$T/prof_tools.py" json "$script" "$run/trace.json" >/dev/null
  "$PY" "$T/prof_tools.py" flame "$script" "$run/flame.svg" --title "$stem" >/dev/null
  "$PY" "$T/prof_tools.py" report "$script" "$run/report.json" --top 60 >/dev/null
done

echo "[2/5] 跨 trace 汇总 + 合并 trace"
"$PY" "$T/aggregate.py" "$ROOT/runs" >/dev/null

echo "[3/5] 热点符号 → 生成代码体量"
"$PY" "$T/hot_bodies.py" "$ROOT/runs/summary.json" "$GEN" --top 40 \
  --out "$ROOT/hot_bodies.json" >/dev/null

echo "[4/5] 结构校验(自研校验器 + Perfetto 官方 trace_processor)"
TPS=$T/linux-amd64/trace_processor_shell
for f in "$ROOT"/runs/*/trace.pftrace; do
  "$PY" "$T/validate_pftrace.py" "$f" >"${f%.pftrace}.validate.txt" 2>&1 || echo "  !! $f 结构校验失败"
  if [[ -x "$TPS" ]]; then
    printf 'select count(*) as slices from slice;\nselect count(*) as tracks from track;\n' \
      | "$TPS" "$f" >"${f%.pftrace}.tp.txt" 2>&1 || echo "  !! $f trace_processor 校验失败"
  fi
done
"$PY" "$T/validate_pftrace.py" "$ROOT/runs/all.pftrace" >"$ROOT/all.validate.txt" 2>&1 || true
if [[ -x "$TPS" ]]; then
  printf 'select count(*) as slices from slice;\n' | "$TPS" "$ROOT/runs/all.pftrace" >"$ROOT/all.tp.txt" 2>&1 || true
fi

echo "[5/5] 元数据"
PYCROOT=${PYCROOT:-/home/ldz/pycircuit-workspace/pyCircuit-cpp-perf} \
  "$PY" "$T/collect_metadata.py" "$ROOT" >/dev/null

echo "done"
ls -la "$ROOT" | tail -12

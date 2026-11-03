#!/bin/bash
# 独立回放仿真器的性能冒烟测试：把 golden ST 波形（真实工作负载：
# 复位 + 取指/访存流量）喂给 pycc C++ 模型回放，报告吞吐。
#
# 用法：perf.sh [trace.st] [cycles]
# 环境变量：TRACE（默认取等价性验证的 golden 波形）
set -euo pipefail

HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"   # 本目录 = designs/Rocket-pyc/sim
BIN="${ROCKET_SIM_BIN:-$HERE/build/rocket_sim}"
TRACE="${1:-${TRACE:-/home/zhangzijie/verilog2pyc/build/check_Rocket/golden.st}}"
N="${2:-400}"
echo "[perf] bin=$BIN cycles=$N PYC_THREADS=${PYC_THREADS:-auto} PYC_TP_STATS=${PYC_TP_STATS:-0}" >&2

# 仿真器/波形缺失时自动补跑（先 build 后提示波形需先跑 check_rocket.sh）
[ -x "$BIN" ] || "$(dirname "${BASH_SOURCE[0]}")"/build.sh
[ -f "$TRACE" ] || { echo "trace not found: $TRACE (run check_rocket.sh first)"; exit 2; }

OUT=$(mktemp /tmp/rocket_sim_XXXX.st); trap 'rm -f "$OUT"' EXIT
T0=$(date +%s.%N)
"$BIN" "$TRACE" "$N" > "$OUT"
T1=$(date +%s.%N)

# 统计实际回放行数并折算吞吐（kcycles/s）
python3 - "$T0" "$T1" "$OUT" <<'EOF'
import sys
t0, t1, out = sys.argv[1], sys.argv[2], sys.argv[3]
rows = sum(1 for l in open(out, errors="ignore") if l.startswith("ST "))
dt = float(t1) - float(t0)
print(f"rocket_sim: replayed {rows} cycles in {dt:.2f}s "
      f"= {rows / dt / 1000:.1f} kcycles/s")
EOF

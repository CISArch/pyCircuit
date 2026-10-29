#!/usr/bin/env bash
# Gate for pyc-eliminate-wires: single-driver wires, declared first, driven last.
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../../.." && pwd)"
PYC_OPT="${PYC_OPT:-${ROOT}/.pycircuit_out/toolchain/build/bin/pyc-opt}"

if [[ ! -x "${PYC_OPT}" ]]; then
  echo "fail: build pyc-opt before running this gate" >&2
  exit 1
fi

"${PYC_OPT}" "${ROOT}/compiler/mlir/test/eliminate_wires_multi_driver.mlir" \
  --pyc-eliminate-wires --verify-diagnostics -o /dev/null

"${PYC_OPT}" "${ROOT}/compiler/mlir/test/Inputs/eliminate_wires_layout.mlir" \
  --pyc-eliminate-wires | python3 -c '
import re, sys
ops = [m.group(1) for line in sys.stdin
       if (m := re.match(r"\s*(?:%\S+ = )?(pyc\.\w+|return)\b", line))]
expected_head = ["pyc.wire", "pyc.wire"]
expected_tail = ["pyc.assign", "pyc.assign", "return"]
if ops[:2] != expected_head or ops[-3:] != expected_tail:
    raise SystemExit(f"fail: unexpected wire/assign layout {ops}")
'

echo "eliminate_wires_layout_smoke: PASS"

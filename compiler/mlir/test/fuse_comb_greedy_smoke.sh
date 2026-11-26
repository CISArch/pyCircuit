#!/usr/bin/env bash
# Gate: the greedy grouping option keeps a contiguous run whole: the fixture
# block fuses into one comb that reads the port directly, instead of the
# signature split into per-input cones with a forwarding comb.
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../../.." && pwd)"
PYC_OPT="${PYC_OPT:-${ROOT}/.pycircuit_out/toolchain/build/bin/pyc-opt}"

if [[ ! -x "${PYC_OPT}" ]]; then
  echo "fail: build pyc-opt before running this gate" >&2
  exit 1
fi

"${PYC_OPT}" "${ROOT}/compiler/mlir/test/Inputs/fuse_comb_split.mlir" \
  --pyc-fuse-comb=algo=greedy | python3 -c '
import re, sys
ir = sys.stdin.read()
combs = re.findall(r"= pyc\.comb\(([^)]*)\)", ir)
regs = re.findall(r"(%\d+) = pyc\.reg", ir)
ok = (len(combs) == 1
      and sorted(combs[0].split(", ")) == sorted(regs + ["%arg3"]))
if not ok:
    raise SystemExit(f"fail: greedy mode did not keep the run whole\n{ir}")
'

echo "fuse_comb_greedy_smoke: PASS"

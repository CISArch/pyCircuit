#!/usr/bin/env bash
# Gate for state-lane packing: FileCheck on pyc-pack-state-lanes, packed probe
# metadata/runtime through pycc, and packed-vs-flat equivalence of generated C++.
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../../.." && pwd)"
TEST="${ROOT}/compiler/mlir/test"
PYC_OPT="${PYC_OPT:-${ROOT}/.pycircuit_out/toolchain/build/bin/pyc-opt}"
PYCC="${PYCC:-${ROOT}/.pycircuit_out/toolchain/build/bin/pycc}"

if [[ ! -x "${PYC_OPT}" || ! -x "${PYCC}" ]]; then
  echo "fail: build pyc-opt and pycc before running this gate" >&2
  exit 1
fi

if [[ -n "${FILECHECK:-}" ]]; then
  FILECHECK_BIN="${FILECHECK}"
elif command -v FileCheck >/dev/null 2>&1; then
  FILECHECK_BIN="$(command -v FileCheck)"
else
  FILECHECK_BIN="$(ls -1v /usr/lib/llvm-*/bin/FileCheck /usr/local/opt/llvm/bin/FileCheck /opt/homebrew/opt/llvm/bin/FileCheck 2>/dev/null | tail -1)" || true
fi
if [[ -z "${FILECHECK_BIN}" || ! -x "${FILECHECK_BIN}" ]]; then
  echo "fail: FileCheck not found (install any llvm package or set FILECHECK)" >&2
  exit 1
fi

TMP_DIR="$(mktemp -d /tmp/pyc-state-pack.XXXXXX)"
trap 'rm -rf "${TMP_DIR}"' EXIT

LANES="${TEST}/state_pack_lanes.mlir"
"${PYC_OPT}" "${LANES}" \
  --pass-pipeline='builtin.module(func.func(pyc-pack-state-lanes{max-width=256}))' \
  -o "${TMP_DIR}/packed.mlir"
"${FILECHECK_BIN}" "${LANES}" --check-prefix=PACK --input-file="${TMP_DIR}/packed.mlir"
"${PYC_OPT}" "${LANES}" \
  --pass-pipeline='builtin.module(func.func(pyc-pack-state-lanes{max-width=12}))' \
  -o "${TMP_DIR}/packed-cap12.mlir"
"${FILECHECK_BIN}" "${LANES}" --check-prefix=CAP --input-file="${TMP_DIR}/packed-cap12.mlir"
"${PYC_OPT}" "${LANES}" \
  --pass-pipeline='builtin.module(func.func(pyc-pack-state-lanes{max-width=0}))' \
  -o "${TMP_DIR}/packed-off.mlir"
if grep -q 'pyc.state_pack_width' "${TMP_DIR}/packed-off.mlir"; then
  echo "fail: max-width=0 still packed state" >&2
  exit 1
fi

PROBE="${TEST}/state_pack_probe.mlir"
"${PYCC}" "${PROBE}" --emit=cpp --state-pack-width=192 --observe-named=demand \
  -o "${TMP_DIR}/packed-probes-demand.hpp" 2>"${TMP_DIR}/packed-probes-demand.stderr"
if grep -qE 'lane0_state[[:space:]]*=|lane1_state[[:space:]]*=' \
  "${TMP_DIR}/packed-probes-demand.hpp"; then
  echo "fail: demand mode still assigned undemanded packed lane names" >&2
  exit 1
fi
grep -q 'addRegLazySlice<8, 16>' "${TMP_DIR}/packed-probes-demand.hpp"
"${CXX:-c++}" -std=c++17 -O2 -I"${ROOT}/runtime" \
  -DMODEL_HEADER="\"${TMP_DIR}/packed-probes-demand.hpp\"" \
  "${TEST}/state_pack_probe_demand_runtime.cpp" \
  -o "${TMP_DIR}/state-pack-probe-demand-runtime"
"${TMP_DIR}/state-pack-probe-demand-runtime"

"${PYCC}" "${PROBE}" --emit=cpp --state-pack-width=192 --observe-named=all \
  -o "${TMP_DIR}/packed-probes.hpp" 2>"${TMP_DIR}/packed-probes.stderr"
if [[ $(grep -c 'addRegSlice<8, 16>' "${TMP_DIR}/packed-probes.hpp") -lt 4 ]]; then
  echo "fail: packed outputs or named lanes missing sliced ProbeRegistry entries" >&2
  exit 1
fi
"${CXX:-c++}" -std=c++17 -O2 -I"${ROOT}/runtime" \
  -DMODEL_HEADER="\"${TMP_DIR}/packed-probes.hpp\"" \
  "${TEST}/state_pack_probe_runtime.cpp" \
  -o "${TMP_DIR}/state-pack-probe-runtime"
"${TMP_DIR}/state-pack-probe-runtime"

python3 "${TEST}/check_state_pack_models.py" \
  --pycc "${PYCC}" --cxx "${CXX:-c++}"

echo "state_pack_smoke: PASS"

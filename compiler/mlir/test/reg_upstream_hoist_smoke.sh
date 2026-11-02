#!/usr/bin/env bash
# Gate for upstream register hoisting: FileCheck on the rewrite, then a
# generated C++ model checked against an independent cycle model.
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../../.." && pwd)"
TEST="${ROOT}/compiler/mlir/test"
PYC_OPT="${PYC_OPT:-${ROOT}/.pycircuit_out/toolchain/build/bin/pyc-opt}"
PYCC="${PYCC:-${ROOT}/.pycircuit_out/toolchain/build/bin/pycc}"
CXX="${CXX:-c++}"

if [[ ! -x "${PYC_OPT}" || ! -x "${PYCC}" ]]; then
  echo "fail: build pyc-opt and pycc before running this gate" >&2
  exit 1
fi

if [[ -n "${FILECHECK:-}" ]]; then
  FILECHECK_BIN="${FILECHECK}"
elif command -v FileCheck >/dev/null 2>&1; then
  FILECHECK_BIN="$(command -v FileCheck)"
else
  FILECHECK_BIN="$(ls -1v /usr/lib/llvm-*/bin/FileCheck /usr/lib64/llvm*/bin/FileCheck /usr/local/opt/llvm/bin/FileCheck /opt/homebrew/opt/llvm/bin/FileCheck /opt/llvm19/bin/FileCheck 2>/dev/null | tail -1)" || true
fi
if [[ -z "${FILECHECK_BIN}" || ! -x "${FILECHECK_BIN}" ]]; then
  echo "fail: FileCheck not found (install any llvm package or set FILECHECK)" >&2
  exit 1
fi

TMP_DIR="$(mktemp -d /tmp/pyc-reg-upstream.XXXXXX)"
trap 'rm -rf "${TMP_DIR}"' EXIT

"${PYC_OPT}" "${TEST}/reg_upstream_hoist.mlir" \
  --pass-pipeline='builtin.module(func.func(pyc-hoist-regs-upstream))' \
  -o "${TMP_DIR}/hoisted.mlir"
"${FILECHECK_BIN}" "${TEST}/reg_upstream_hoist.mlir" \
  --input-file="${TMP_DIR}/hoisted.mlir"

"${PYCC}" "${TEST}/reg_upstream_hoist_model.mlir" --emit=cpp \
  -o "${TMP_DIR}/model.hpp"
"${CXX}" -std=c++17 -O2 -I"${ROOT}/runtime" \
  -DMODEL_HEADER="\"${TMP_DIR}/model.hpp\"" \
  "${TEST}/reg_upstream_hoist_model.cpp" \
  -o "${TMP_DIR}/model"
"${TMP_DIR}/model" >"${TMP_DIR}/model.out"
grep -q '^cycles=64 checksum=' "${TMP_DIR}/model.out"

echo "reg_upstream_hoist_smoke: PASS"

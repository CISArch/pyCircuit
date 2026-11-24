#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../../.." && pwd)"
PYCC="${PYCC:-${ROOT}/.pycircuit_out/toolchain/install/bin/pycc}"
OUT="${PYC_INSTANCE_VECTOR_CACHE_OUT:-${ROOT}/.pycircuit_out/gates/instance_vector_cache}"
INPUT="${ROOT}/compiler/mlir/test/Inputs/instance_vector_cache.mlir"

rm -rf "${OUT}"
mkdir -p "${OUT}"

"${PYCC}" "${INPUT}" --emit=cpp --logic-depth=256 \
  -o "${OUT}/instance_vector_cache.cpp"

python3 - "${OUT}/instance_vector_cache.cpp" <<'PY'
import sys

text = open(sys.argv[1], encoding="utf-8").read()
if "_eval_cache_words" in text:
    raise SystemExit("wide instance input still materialises a packed shadow array")
if "_eval_cache_in_" in text:
    raise SystemExit("wide instance input fell back to the per-port versioned cache")
if "u_child->in" not in text:
    raise SystemExit("wide instance input is not compared against the child's own port")
PY

"${CXX:-c++}" -std=c++17 -O0 \
  -I"${ROOT}/.pycircuit_out/toolchain/install/include" \
  -c "${OUT}/instance_vector_cache.cpp" \
  -o "${OUT}/instance_vector_cache.o"

echo "ok: wide instance input is compared against the child port, no packed shadow"

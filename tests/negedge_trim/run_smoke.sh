#!/usr/bin/env bash
# Gate for --cpp-negedge-trim: the trimmed falling edge must be equivalent to
# the serial one.  Both models are emitted from the same fixture and driven by
# the same cycle-by-cycle driver; their output traces must match.
#
#   --cpp-negedge-trim=off  serial model (byte-identical to the untrimmed
#                           emitter; set BASE_PYCC to also diff it against a
#                           reference pycc build)
#   --cpp-negedge-trim=on   trimmed model
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
CC="${PYCC:-${ROOT}/.pycircuit_out/toolchain/build/bin/pycc}"
CXX="${CXX:-clang++}"
FIXTURE="${ROOT}/tests/negedge_trim/negedge_trim.mlir"
DRIVER="${ROOT}/tests/negedge_trim/driver.cpp"
RUNTIME_INC="${ROOT}/runtime"

if [[ ! -x "${CC}" ]]; then
  echo "fail: build pycc before running this gate (${CC})" >&2
  exit 1
fi

WORK="${NEGEDGE_TRIM_WORKDIR:-$(mktemp -d /tmp/pyc-negedge-trim.XXXXXX)}"
mkdir -p "${WORK}/off" "${WORK}/on"

echo "[negedge-trim] emit serial model"
"${CC}" "${FIXTURE}" --emit=cpp --out-dir "${WORK}/off" --cpp-split=module \
  --cpp-negedge-trim=off >/dev/null
echo "[negedge-trim] emit trimmed model"
"${CC}" "${FIXTURE}" --emit=cpp --out-dir "${WORK}/on" --cpp-split=module \
  --cpp-negedge-trim=on >/dev/null

# The trim must exist in the "on" model and be absent from the "off" model.
if ! grep -q "tick_negedge" "${WORK}/on/trim_top.cpp"; then
  echo "fail: --cpp-negedge-trim=on emitted no tick_negedge()" >&2
  exit 1
fi
if grep -q "tick_negedge" "${WORK}/off/trim_top.cpp"; then
  echo "fail: --cpp-negedge-trim=off emitted tick_negedge()" >&2
  exit 1
fi

# "off" must stay byte-identical to a reference (untrimmed) pycc build.
if [[ -n "${BASE_PYCC:-}" && -x "${BASE_PYCC}" ]]; then
  mkdir -p "${WORK}/base"
  "${BASE_PYCC}" "${FIXTURE}" --emit=cpp --out-dir "${WORK}/base" \
    --cpp-split=module >/dev/null
  if ! diff -r -x 'compile_stats.json' -x '*.json' "${WORK}/base" "${WORK}/off"; then
    echo "fail: --cpp-negedge-trim=off differs from the reference emitter" >&2
    exit 1
  fi
  echo "[negedge-trim] off == reference emitter (byte-identical)"
fi

build_model() {
  local dir="$1"
  local out="$2"
  "${CXX}" -std=c++17 -O2 -o "${out}" \
    -I"${dir}" -I"${RUNTIME_INC}" \
    "${DRIVER}" "${dir}/trim_top.cpp" "${dir}/trim_leaf.cpp"
}

echo "[negedge-trim] build serial model"
build_model "${WORK}/off" "${WORK}/off.bin"
echo "[negedge-trim] build trimmed model"
build_model "${WORK}/on" "${WORK}/on.bin"

"${WORK}/off.bin" > "${WORK}/off.trace"
"${WORK}/on.bin" > "${WORK}/on.trace"

if ! diff -u "${WORK}/off.trace" "${WORK}/on.trace"; then
  echo "fail: trimmed model diverged from the serial model" >&2
  echo "      (traces under ${WORK})" >&2
  exit 1
fi

lines="$(wc -l < "${WORK}/off.trace")"
echo "negedge_trim_smoke: PASS (${lines} compared lines, 40 cycles)"

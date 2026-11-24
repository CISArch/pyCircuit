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

# Regression: a leaf whose only state is a loopified delay line runs through the
# generic compute_generic(clk) path and needs its falling edge.  The trim must
# leave that subtree serial (no tick_negedge in the generated top) and the two
# models must stay equal.
DL_FIXTURE="${ROOT}/tests/negedge_trim/delay_only.mlir"
DL_DRIVER="${ROOT}/tests/negedge_trim/driver_delay_only.cpp"
mkdir -p "${WORK}/dl_off" "${WORK}/dl_on"
"${CC}" "${DL_FIXTURE}" --emit=cpp --out-dir "${WORK}/dl_off" --cpp-split=module \
  --cpp-negedge-trim=off >/dev/null
"${CC}" "${DL_FIXTURE}" --emit=cpp --out-dir "${WORK}/dl_on" --cpp-split=module \
  --cpp-negedge-trim=on >/dev/null
if grep -q "Falling edge after a committed rising edge" "${WORK}/dl_on/dl_top.cpp"; then
  echo "fail: trim reached a subtree with generic delay loops" >&2
  exit 1
fi
build_dl_model() {
  local dir="$1"
  local out="$2"
  "${CXX}" -std=c++17 -O2 -o "${out}" \
    -I"${dir}" -I"${RUNTIME_INC}" \
    "${DL_DRIVER}" "${dir}/dl_top.cpp" "${dir}/dl_leaf.cpp"
}
build_dl_model "${WORK}/dl_off" "${WORK}/dl_off.bin"
build_dl_model "${WORK}/dl_on" "${WORK}/dl_on.bin"
"${WORK}/dl_off.bin" > "${WORK}/dl_off.trace"
"${WORK}/dl_on.bin" > "${WORK}/dl_on.trace"
if ! diff -u "${WORK}/dl_off.trace" "${WORK}/dl_on.trace"; then
  echo "fail: --cpp-negedge-trim stalled a delay-only sub-module" >&2
  exit 1
fi
echo "negedge_trim_delay_only: PASS ($(wc -l < "${WORK}/dl_off.trace") compared lines, 8 cycles)"

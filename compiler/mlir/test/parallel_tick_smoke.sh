#!/usr/bin/env bash
# Parallel tick gate: --cpp-parallel-tick dispatches submodule tick helper parts
# through the runtime thread pool. Sequential, pool-inline (PYC_THREADS=1) and
# multi-thread (PYC_THREADS=4) runs must agree byte-for-byte, and the threaded
# build must stay TSan-clean. Default flags must keep the sequential emission.
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../../.." && pwd)"
PYCC="${PYCC:-${ROOT}/.pycircuit_out/toolchain/build/bin/pycc}"
CXX="${CXX:-c++}"
INPUT="${ROOT}/compiler/mlir/test/Inputs/parallel_tick_instances.mlir"
DRIVER="${ROOT}/compiler/mlir/test/Inputs/parallel_tick_instances_driver.cpp"
OUT="${ROOT}/.pycircuit_out/gates/parallel_tick"

if [[ ! -x "${PYCC}" ]]; then
  echo "skip: pycc not built at ${PYCC}" >&2
  exit 0
fi

rm -rf "${OUT}"
mkdir -p "${OUT}"

common=(--logic-depth=256 --build-profile=dev-fast
        --inline-policy=off --hierarchy-policy=strict)

# --- 1. Baseline: default flags stay sequential. -----------------------------
base_dir="${OUT}/base"
mkdir -p "${base_dir}"
"${PYCC}" "${INPUT}" --emit=cpp -o "${base_dir}/parallel_tick_instances.cpp" "${common[@]}"
if grep -q 'pyc_parallel_for' "${base_dir}/parallel_tick_instances.cpp"; then
  echo "fail: default emission dispatches through the thread pool" >&2
  exit 1
fi
"${CXX}" -std=c++17 -O2 \
  -I"${base_dir}" -I"${ROOT}/runtime" \
  "${DRIVER}" -o "${OUT}/run_base"
"${OUT}/run_base" | sed 's/ | threads=.*//' > "${OUT}/baseline.txt"

# --- 2. Parallel emission, single part (8 instances < chunk 256): guard. ----
wide_dir="${OUT}/wide"
mkdir -p "${wide_dir}"
"${PYCC}" "${INPUT}" --emit=cpp --cpp-parallel-tick \
  -o "${wide_dir}/parallel_tick_instances.cpp" "${common[@]}"
if grep -q 'pyc_parallel_for' "${wide_dir}/parallel_tick_instances.cpp"; then
  echo "fail: single-part design dispatched through the thread pool" >&2
  exit 1
fi

# --- 3. Parallel emission, per-instance parts. -------------------------------
par_dir="${OUT}/parallel"
mkdir -p "${par_dir}"
"${PYCC}" "${INPUT}" --emit=cpp --cpp-parallel-tick --cpp-tick-chunk=1 \
  -o "${par_dir}/parallel_tick_instances.cpp" "${common[@]}"
sim_cpp="${par_dir}/parallel_tick_instances.cpp"
grep -q 'pyc::cpp::pyc_parallel_for(8u' "${sim_cpp}"
grep -q 'tick_compute_part_' "${sim_cpp}"
grep -q 'tick_commit_part_' "${sim_cpp}"

"${CXX}" -std=c++17 -O2 -pthread \
  -I"${par_dir}" -I"${ROOT}/runtime" \
  "${DRIVER}" -o "${OUT}/run_par"

for mode in 1 4; do
  PYC_THREADS=${mode} "${OUT}/run_par" | sed 's/ | threads=.*//' \
    > "${OUT}/par_t${mode}.txt"
  if ! diff -u "${OUT}/baseline.txt" "${OUT}/par_t${mode}.txt"; then
    echo "fail: PYC_THREADS=${mode} diverged from sequential baseline" >&2
    exit 1
  fi
done
PYC_THREADS=4 "${OUT}/run_par" | grep -q 'threads=4'

# Repeated runs shake out scheduling flakes.
for rep in $(seq 1 25); do
  PYC_THREADS=4 "${OUT}/run_par" > /dev/null
done

# --- 4. ThreadSanitizer pass on the threaded build. --------------------------
if "${CXX}" -std=c++17 -fsanitize=thread -pthread \
    -I"${par_dir}" -I"${ROOT}/runtime" \
    "${DRIVER}" -o "${OUT}/run_par_tsan" 2>"${OUT}/tsan_build.log"; then
  PYC_THREADS=4 "${OUT}/run_par_tsan" | sed 's/ | threads=.*//' \
    > "${OUT}/par_tsan.txt"
  if ! diff -u "${OUT}/baseline.txt" "${OUT}/par_tsan.txt"; then
    echo "fail: TSan run diverged from sequential baseline" >&2
    exit 1
  fi
else
  echo "note: TSan build unavailable, skipping (see ${OUT}/tsan_build.log)"
fi

echo "ok: parallel tick smoke"

#!/usr/bin/env bash
# Parallel tick gate: --cpp-parallel-tick dispatches submodule tick helper parts
# through the runtime thread pool. Sequential, pool-inline (PYC_THREADS=1) and
# multi-thread (PYC_THREADS=4) runs must agree byte-for-byte, and the threaded
# build must stay TSan-clean. Default flags must keep the sequential emission.
# Section 5 additionally regression-checks the pool's load balance (tp_balance)
# and that the PYC_TP_STATS probe stays opt-in.
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

# --- 5. Pool load-balance regression (tp_balance + opt-in stats probe). ------
"${CXX}" -std=c++17 -O2 -pthread -I"${ROOT}/runtime" \
  "${ROOT}/compiler/mlir/test/tp_balance.cpp" -o "${OUT}/tp_balance"

# The stats probe must stay silent without an explicit opt-in.
"${OUT}/tp_balance" uniform >/dev/null 2>"${OUT}/balance_nostats.err"
if grep -q 'PYC_TP_STATS' "${OUT}/balance_nostats.err"; then
  echo "fail: PYC_TP_STATS probe active without PYC_TP_STATS=1" >&2
  exit 1
fi

if ! "${OUT}/tp_balance" --check; then
  echo "fail: pool load-balance regression" >&2
  exit 1
fi

cores="$(nproc 2>/dev/null || grep -c ^processor /proc/cpuinfo 2>/dev/null || echo 1)"
cores=$((cores + 0))
if (( cores >= 2 )); then
  if (( cores > 4 )); then
    cores=4
  fi
  PYC_TP_STATS=1 PYC_THREADS=${cores} "${OUT}/tp_balance" uniform \
    >/dev/null 2>"${OUT}/balance_stats.raw"
  # Every claimer must take part, and no thread may hog the dispatch.
  grep 'PYC_TP_STATS: thread' "${OUT}/balance_stats.raw" \
    > "${OUT}/balance_stats.txt"
  awk '{
         s = $NF; gsub(/%/, "", s);
         if (s + 0 < 2 || s + 0 > 50) bad = 1;
         n++;
       }
       END { exit (bad || n < 2) ? 1 : 0 }' "${OUT}/balance_stats.txt" || {
    echo "fail: per-thread busy share outside [2%, 50%]:" >&2
    cat "${OUT}/balance_stats.txt" >&2
    exit 1
  }
else
  echo "note: <2 cores, skipping per-thread share check"
fi

echo "ok: parallel tick smoke"

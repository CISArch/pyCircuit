#!/usr/bin/env bash
set -euo pipefail
repo_root="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
build_dir="$(mktemp -d)"
trap 'rm -rf "$build_dir"' EXIT
cxx="${CXX:-c++}"
includes=(-std=c++17 -Wall -Wextra -Werror -I"${repo_root}/runtime/cpp")

# Positive: both module kinds through one parent template, same three entries.
"${cxx}" "${includes[@]}" "${repo_root}/tests/runtime/test_module_base.cpp" -o "${build_dir}/t"
"${build_dir}/t"

# Negative: calling a clocked entry on a comb-only module must fail to compile.
if "${cxx}" "${includes[@]}" "${repo_root}/tests/runtime/neg_module_base_comb_only.cpp"     -o "${build_dir}/neg" 2>"${build_dir}/neg.err"; then
  echo "fail: tick_sample() on a comb-only module compiled" >&2
  exit 1
fi
if ! grep -q "deleted" "${build_dir}/neg.err"; then
  echo "fail: expected a deleted-function diagnostic, got:" >&2
  cat "${build_dir}/neg.err" >&2
  exit 1
fi
echo "module base runtime tests passed (comb-only tick_sample rejected)"

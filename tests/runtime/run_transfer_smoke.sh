#!/usr/bin/env bash
# Build and run transfer_smoke against a generated model directory.
# usage: run_transfer_smoke.sh <generated-cpp-dir> [top-header-basename]
set -euo pipefail
dir="${1:?generated cpp dir}"
hdr="${2:-pyc_model}"
root="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/../.." && pwd)"
inc="$root/.pycircuit_out/toolchain/install/include"
tmp="$(mktemp -d)"
trap 'rm -rf "$tmp"' EXIT
sed "s|#include \"pyc_model.h\"|#include \"$hdr.h\"|; s|pyc::gen::pyc_model|pyc::gen::$hdr|g" \
  "$(dirname -- "${BASH_SOURCE[0]}")/transfer_smoke.cpp" > "$tmp/transfer_smoke.cpp"
# The model is compiled from the generated sources plus this driver.
clang++ -std=c++17 -O2 -I"$dir" -I"$inc" "$tmp/transfer_smoke.cpp" \
  $(find "$dir" -name '*.cpp' | sort) -o "$tmp/transfer_smoke"
"$tmp/transfer_smoke"

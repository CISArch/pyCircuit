#!/bin/bash
# Three-way equivalence check for the Rocket bare core (ST protocol).
#
#   golden Verilator  vs  MLIR->Verilog (pyc.verilog emitter)  vs  MLIR->C++ (pycc)
#
# Usage: check_rocket.sh [extra v2p check args, e.g. --cycles 100]
# Env overrides: V2P_DIR, ROCKET_CHIP_V16, PYCC
set -euo pipefail

HERE="$(cd "$(dirname "$0")/.." && pwd)"   # designs/Rocket-pyc
V2P_DIR="${V2P_DIR:-/home/zhangzijie/verilog2pyc}"
RCV16="${ROCKET_CHIP_V16:-/home/zhangzijie/rocket-chip-v16}"
PYCC="${PYCC:-/home/zhangzijie/pyCircuit/.pycircuit_out/toolchain/build/bin/pycc}"

cd "$V2P_DIR"
exec python3 -m v2p.cli check "$RCV16"/generated-verilog/*.v \
    --top Rocket \
    --tb "$HERE/tb/tb_rocket.v" \
    --memory-map \
    --pycc "$PYCC" \
    "$@"

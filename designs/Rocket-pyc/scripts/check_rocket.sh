#!/bin/bash
# Rocket 裸核三方等价性对拍（ST 协议）。
#
#   golden（Verilator 仿真）
#     vs  MLIR -> Verilog（pyc.verilog 发射器）
#     vs  MLIR -> C++（pycc 编译 + 回放 runner）
#
# 用法：check_rocket.sh [v2p check 额外参数，如 --cycles 100]
#       check_rocket.sh --keep-hierarchy [--cycles N]
#         层级导入：每模块一个 func.func + pyc.instance 例化；
#         已验证 400 拍 0 失配（verilog 路径 + 原生层级 cpp 路径）。
#         注：层级模式 cpp 构建不加 --flatten——flatten 会内联实例并把
#         wire 驱动/读端融合进同一 comb 区域，导致每拍陈旧 wire 读。
# 环境变量覆盖：V2P_DIR、ROCKET_CHIP_V16、PYCC
set -euo pipefail

HERE="$(cd "$(dirname "$0")/.." && pwd)"   # 本目录 = designs/Rocket-pyc
V2P_DIR="${V2P_DIR:-/home/zhangzijie/verilog2pyc}"          # verilog2pyc 仓库
RCV16="${ROCKET_CHIP_V16:-/home/zhangzijie/rocket-chip-v16}" # v1.6 发布 Verilog
PYCC="${PYCC:-/home/zhangzijie/pyCircuit/.pycircuit_out/toolchain/build/bin/pycc}"

cd "$V2P_DIR"
exec python3 -m v2p.cli check "$RCV16"/generated-verilog/*.v \
    --top Rocket \
    --tb "$HERE/tb/tb_rocket.v" \
    --memory-map \
    --pycc "$PYCC" \
    "$@"

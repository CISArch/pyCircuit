#!/bin/bash
# 生成 MLIR + C++ 模型 + ST 波形回放驱动（三步级联）。
# 对标 DavinciBaseLine sim/scripts/gen.sh——差别在于此处"源"是 v2p 导入
# 的 Verilog（而非原生 PyCircuit Python）。
# 默认启用多线程 tick：v2p 保留模块层级（pyc.instance），pycc 把子模块
# tick 拆成可分派的 part，运行时由 PYC_THREADS 决定线程数。
# 环境变量：V2P_DIR、ROCKET_CHIP_V16、PYCC、ROCKET_GEN_DIR、
#   PYC_PARALLEL_TICK（默认 1，设 0 回到平铺/串行）、
#   PYC_TICK_CHUNK（默认 1）、PYC_TICK_PARTITION（默认 weighted）。
set -euo pipefail

HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"   # 本目录 = designs/Rocket-pyc/sim
V2P_DIR="${V2P_DIR:-/home/zhangzijie/verilog2pyc}"           # verilog2pyc 仓库
RCV16="${ROCKET_CHIP_V16:-/home/zhangzijie/rocket-chip-v16}" # v1.6 发布 Verilog
PYCC="${PYCC:-/home/zhangzijie/pyCircuit/.pycircuit_out/toolchain/build/bin/pycc}"
GEN="${ROCKET_GEN_DIR:-$HERE/build/generated}"
PYC_PARALLEL_TICK="${PYC_PARALLEL_TICK:-1}"
PYC_TICK_CHUNK="${PYC_TICK_CHUNK:-1}"
PYC_TICK_PARTITION="${PYC_TICK_PARTITION:-weighted}"
mkdir -p "$GEN"

# 平铺模型没有 pyc.instance，即使加 --cpp-parallel-tick 也不会产生分派；
# 因此多线程路径必须同时打开 --keep-hierarchy。
convert_args=(--top Rocket --memory-map)
pycc_args=(--emit=cpp --logic-depth=256)
if [[ "${PYC_PARALLEL_TICK}" == "1" ]]; then
    convert_args+=(--keep-hierarchy)
    pycc_args+=(--cpp-parallel-tick
                "--cpp-tick-chunk=${PYC_TICK_CHUNK}"
                "--cpp-tick-partition=${PYC_TICK_PARTITION}")
fi

cd "$V2P_DIR"

# 第 1 步：Verilog -> pyc MLIR（yosys 归一化 + v2p 导入）
echo "[gen] Verilog -> pyc MLIR (yosys normalize + import, parallel_tick=${PYC_PARALLEL_TICK})"
python3 -m v2p.cli convert "$RCV16"/generated-verilog/*.v \
    "${convert_args[@]}" -o "$GEN/Rocket.mlir" \
    --workdir "$GEN/yosys"

# 第 2 步：MLIR -> C++ 模型（pycc C++ 后端）
echo "[gen] MLIR -> C++ model (pycc)"
"$PYCC" "$GEN/Rocket.mlir" "${pycc_args[@]}" \
    -o "$GEN/Rocket_gen.cpp"

# 第 3 步：生成 ST 波形回放驱动（解析激励 + 打时钟 + 打印输出）
echo "[gen] replay driver (v2p.gen_runner)"
python3 -m v2p.gen_runner "$GEN/Rocket.mlir" Rocket \
    "$GEN/Rocket_gen.cpp" "$GEN"

echo "[gen] done: $GEN/Rocket.mlir, Rocket_gen.cpp, runner.cpp, v2p_model.hpp"
if [[ "${PYC_PARALLEL_TICK}" == "1" ]]; then
    echo "[gen] run with PYC_THREADS=<n> (0/1 = sequential); PYC_TP_STATS=1 prints per-thread load"
fi

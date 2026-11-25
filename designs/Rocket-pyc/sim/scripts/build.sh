#!/bin/bash
# 编译独立回放仿真器（对标 DavinciOO sim/scripts/build.sh；这里用
# 单翻译单元的 c++ 直接编译，不用 cmake）。
# 若 gen.sh 产物（runner.cpp）缺失会自动先跑 gen.sh。
# 环境变量：ROCKET_GEN_DIR、ROCKET_SIM_BIN、PYC_PARALLEL_TICK（默认 1）。
set -euo pipefail

HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"   # 本目录 = designs/Rocket-pyc/sim
V2P_DIR="${V2P_DIR:-/home/zhangzijie/verilog2pyc}"
GEN="${ROCKET_GEN_DIR:-$HERE/build/generated}"
BIN="${ROCKET_SIM_BIN:-$HERE/build/rocket_sim}"
PYC_PARALLEL_TICK="${PYC_PARALLEL_TICK:-1}"

if [ ! -f "$GEN/runner.cpp" ]; then
    echo "[build] generated driver missing — running gen.sh first"
    "$(dirname "${BASH_SOURCE[0]}")"/gen.sh
fi

# 定位 pycc 运行时头文件目录（runner.cpp include 其 cpp/ 子目录）
RUNTIME_INC="$(cd "$V2P_DIR" && python3 -c \
    'import v2p.env as e; print(e.runtime_cpp_dir().parent)')"

# 并行 tick 发射的 pyc_parallel_for 依赖 std::thread，需要 -pthread。
pthread_args=()
if [[ "${PYC_PARALLEL_TICK}" == "1" ]]; then
    pthread_args=(-pthread)
fi

mkdir -p "$(dirname "$BIN")"
echo "[build] c++ -O2 -std=c++20 ${pthread_args[*]} -I $RUNTIME_INC"
c++ -O2 -std=c++20 "${pthread_args[@]}" -I "$RUNTIME_INC" -I "$GEN" \
    "$GEN/runner.cpp" -o "$BIN"
echo "[build] done: $BIN"

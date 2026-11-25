# Rocket-pyc 独立仿真（pycc C++ 后端）

对标 DavinciBaseLine `sim/` 的等价物流：构建**不依赖 Verilator** 的独立
C++ 回放仿真器，由 golden ST 波形（即"工作负载"，对应 DavinciOO PTO 的
`hints.txt`）驱动。

```text
rocket-chip-v16/generated-verilog/*.v
  │  v2p.cli convert（yosys 归一化 + 导入）
  ▼
build/generated/Rocket.mlir
  │  pycc --emit=cpp --logic-depth=256
  ▼
build/generated/Rocket_gen.cpp（即 v2p_model.hpp）
  │  + v2p.gen_runner → runner.cpp（ST 解析 + 激励 + 时钟 + 打印）
  ▼  c++ -O2
build/rocket_sim
  │  ./scripts/perf.sh <trace.st> <cycles>
  ▼  吞吐（kcycles/s）
```

与 DavinciOO `sim/` 的差异：源是导入的 Verilog（非原生 PyCircuit
Python）。默认启用多线程 tick：v2p 以 `--keep-hierarchy` 导入（func.func
+ pyc.instance），pycc 用 `--cpp-parallel-tick` 把子模块 tick 拆成可分派
part，运行时由 `PYC_THREADS` 决定线程数。设 `PYC_PARALLEL_TICK=0` 可回到
平铺/串行发射（平铺模型没有实例 part，单独设 `PYC_THREADS` 无效）。
层级原生 cpp 回放约 43 kcycles/s vs 平铺 58 kcycles/s（400 拍含进程启动
开销），实例原语调度存在一定开销，多线程需先补回这部分差距。驱动端同样
以 golden 波形回放（而非 idle hints）。

## 用法

```bash
scripts/gen.sh                       # Verilog -> MLIR -> cpp -> 驱动（默认多线程发射）
scripts/build.sh                     # -> build/rocket_sim（自动加 -pthread）
PYC_THREADS=8 scripts/perf.sh        # 回放 check_Rocket/golden.st（400 拍）
PYC_TP_STATS=1 PYC_THREADS=8 scripts/perf.sh   # 打印每线程负载
scripts/bench_threads.sh             # 平铺单线程基线 vs 多线程：功能 diff + kcycles/s 表
scripts/bench_verilator_vs_mt.sh     # Verilator cycles/s 基线 vs 多线程：P/V 表 + comparison.json
PYC_PARALLEL_TICK=0 scripts/gen.sh && scripts/build.sh   # 平铺/串行 baseline
scripts/perf.sh other.st 1000        # 自定义波形/拍数
```

环境依赖：`verilog2pyc`（V2P_DIR）、`pycc`（PYCC）、rocket-chip-v16
（ROCKET_CHIP_V16）；golden 波形来自 `../scripts/check_rocket.sh`。

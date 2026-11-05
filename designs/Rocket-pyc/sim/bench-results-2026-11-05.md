# Rocket-pyc Verilator vs pyCircuit C++ 多线程性能测试（2026-11-05）

仿照 DavinciBaseLine `auto_perf` 的吞吐矩阵流程（trace → 双后端 → `cycles_per_s` / `pycircuit_to_verilator_ratio` / `common_metrics_match`），用 `scripts/bench_verilator_vs_mt.sh` 对 Rocket 裸核（RV32IMA，verilog2pyc 层级导入 + `--cpp-parallel-tick`）复测：Verilator 基线 vs pyCircuit C++ 在 1/2/4 线程下的吞吐。

- 参数：`PYC_THREAD_LIST="1 2 4"`，`PYC_BENCH_CYCLES=10000`，`PYC_BENCH_REPEAT=3`
- 复用既有二进制（零重编）：Verilator 基线 `check_Rocket/golden/vobj/g_Rocket`、C++ 侧 `sim/build/rocket_sim`
- 激励：golden ST 波形 400 拍重复至 ≥10000 拍；功能等价按 400 拍 × 77 输出列逐行 diff
- 口径：进程外 `date` 墙钟（含进程启动，repeat 摊薄），`cycles_per_s = simulated_cycles / wall`，编译不计入

## 1. 结果（common_metrics_match：3/3 MATCH）

| backend | threads | simulated cycles | wall (s) | cycles/s | kcycles/s | P/V |
|---|---|---|---|---|---|---|
| verilator (g_Rocket) | 1 | 1200 | 0.020 | 59560 | 59.6 | 1.000 |
| pycircuit cpp (parallel tick) | 1 | 30000 | 0.582 | 51581 | 51.6 | **0.866** |
| pycircuit cpp (parallel tick) | 2 | 30000 | 0.775 | 38728 | 38.7 | 0.650 |
| pycircuit cpp (parallel tick) | 4 | 30000 | 0.784 | 38267 | 38.3 | 0.642 |

## 2. 线程扩展性

| 对比 | 吞吐比 | 说明 |
|---|---|---|
| t2 / t1 | 0.751（-24.9%） | 多线程反而降速 |
| t4 / t1 | 0.742（-25.8%） | 同上，且 t4 无进一步损失 |
| t4 / t2 | 0.988 | 2→4 线程持平 |

## 3. 与上次 bench（threads=1/2/4/8）对照

| threads | 上次 P/V | 本轮 P/V |
|---|---|---|
| 1 | 0.890 | 0.866 |
| 2 | 0.647 | 0.650 |
| 4 | 0.642 | 0.642 |
| （8） | 0.613 | 未测 |

两轮各线程数 P/V 偏差 ≤0.024（t1），t2/t4 偏差 <0.003，结果可复现；Verilator 基线 58715 → 59560 c/s（+1.4%），稳定。

## 4. 结论

1. **单线程是当前最优配置**：P/V = 0.866，pyCircuit C++ 已达 Verilator 基线的 87%。
2. **多线程负扩展**：t2 起吞吐掉约 25%。原因（sim/README.md 已记录）：层级导入后每拍仅 6 个实例 part（Rocket→ALU/BreakpointUnit/CSRFile/IBuf/MulDiv，IBuf→RVCExpander），粒度太细，fork-join 同步开销超过并行收益；且层级实例调度相对平铺本有开销（43 vs 58 kcycles/s），单靠多线程补不回。
3. 与 DavinciBaseLine（v5_superscalar，34 条 trace）方向相反：那边 t2 +16.7%/t4 +17.6%（每拍 12 instance、4–8 part 有并行空间），Rocket 每拍 6 part 且单 part 更小，不适合多线程。
4. 功能等价不受线程数影响：3 个线程数 × 400 拍 × 77 列全部 MATCH。

## 5. 产物

- 本轮：`/tmp/rocket-bench-1105/comparison.json`（含 `results.tsv`、`verilator.st`、`cpp_t{1,2,4}.st`、`diff_t*.txt`）
- 上次（1/2/4/8 线程）：`/tmp/pyc-verilator-vs-mt/comparison.json`
- 复现：`PYC_BENCH_DIR=<dir> PYC_THREAD_LIST="1 2 4" PYC_BENCH_CYCLES=10000 PYC_BENCH_REPEAT=3 bash scripts/bench_verilator_vs_mt.sh`

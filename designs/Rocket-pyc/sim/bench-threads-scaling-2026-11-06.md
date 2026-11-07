# Rocket-pyc pyCircuit 多线程扩展测试（2026-11-06）

补全 [bench-results-2026-11-05.md](bench-results-2026-11-05.md) 的线程扩展曲线：同日同环境对 1/2/4/6/8/16 六档完整重跑（不混用昨日数据），负载与功能等价口径不变。

## 1. 测试方式

- 脚本：`scripts/bench_verilator_vs_mt.sh`，`PYC_THREAD_LIST="1 2 4 6 8 16"`、`PYC_BENCH_CYCLES=10000`、`PYC_BENCH_REPEAT=3`
- 二进制复用：`g_Rocket`（Verilator 基线）与 `rocket_sim`（pyCircuit C++，`--cpp-parallel-tick`）零重编
- 激励：golden ST 波形重复成长激励；计时为进程外墙钟、repeat 摊薄（`comparison.json` 的 `timing` 字段）

## 2. 结果（六档全部 common_metrics_match=True）

| backend | threads | wall (3×10k 拍) | cycles/s | P/V | vs t1 |
|---|---|---|---|---|---|
| verilator (g_Rocket) | — | 0.020 s | 60006 | 1.000 | — |
| pycircuit cpp | 1 | 0.577 s | 51973 | 0.866 | 1.000 |
| pycircuit cpp | 2 | 0.780 s | 38465 | 0.641 | 0.740 |
| pycircuit cpp | 4 | 0.787 s | 38142 | 0.636 | 0.734 |
| pycircuit cpp | 6 | 0.816 s | 36754 | 0.613 | 0.707 |
| pycircuit cpp | 8 | 0.829 s | 36181 | 0.603 | 0.696 |
| pycircuit cpp | 16 | 0.935 s | 32077 | **0.535** | **0.617** |

## 3. 结论

1. **单调负扩展、无拐点**：1→2 线程即 -26%，之后逐级缓降，16 线程累计 -38%（P/V 0.866 → 0.535）。与 DavinciBaseLine（12 instance/拍，t2 +16.7% 后饱和）方向相反
2. **根因是粒度上限**：层级导入后每拍仅 6 个实例 part（Rocket→ALU/BreakpointUnit/CSRFile/IBuf/MulDiv，IBuf→RVCExpander），t≥6 后新增线程只摊薄空转、纯增 fork-join 同步开销（t4→t16 每档再降 1~8%）
3. **生产配置建议 t1**：P/V 0.866 即当前最优；多线程要转正需先解决层级 part 过细（扁平化合并或按模块簇重组分区），而非加线程
4. **可复现性**：与 11-05 轮（t1 0.866 / t2 0.650 / t4 0.642）及更早含 t8 轮（0.613）对照，P/V 偏差 ≤0.009；Verilator 基线 60006 vs 上轮 59560（+0.7%）
5. 功能等价不受线程数影响：6 档 × 400 拍 × 77 输出列逐行 diff 全 MATCH

## 4. 产物

- 本轮：`/tmp/rocket-bench-1106-mt/comparison.json`（六档完整数据）
- 基线对照：`/tmp/rocket-bench-1105/`（11-05，1/2/4）、`/tmp/pyc-verilator-vs-mt/`（含 t8）
- 复现：`cd sim && PYC_BENCH_DIR=/tmp/rocket-bench-1106-mt PYC_THREAD_LIST="1 2 4 6 8 16" PYC_BENCH_CYCLES=10000 PYC_BENCH_REPEAT=3 bash scripts/bench_verilator_vs_mt.sh`

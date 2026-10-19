# 逐层拆分终点（stack-4）与 combine-old（e4c5e82f）对照

`ldz/feat/stack-1-delay-line` → `stack-2-state-loop` → `stack-3-reg-pack` → `stack-4-state-merge`
四层依次叠加，每层 auto_perf（先看能否编译）+ GitHub CI（Linux/macOS）通过后才进入下一层。

| 层 | tip | auto_perf 均值 cycles/s | P/V | 34 trace |
|----|-----|-----------------------|-----|----------|
| L1 delay-line + demand + retime + trace plan | 66eee89 | 1156.8 | 0.26 | 34/34 MATCH |
| L2 + state-loop（RegLoop/DelayLoop） | b22ef9a | 1709.8 | 0.391 | 34/34 MATCH |
| L3 + reg-pack | 98cb627 | 2544.0 | 0.568 | 34/34 MATCH |
| L4 + 等价状态合并 | e920d54f | 3233.9 | 0.724 | 34/34 MATCH |
| 基线 combine-old | e4c5e82f | 3174.4 | 0.724 | 34/34 MATCH |

结论：L4 与 e4c5e82f 相差 +1.9%，在 ±3% 机器噪声内，P/V 同为 0.724，34 条 trace 的
`simulated_cycles` 逐条完全一致，面积综合顶层同为 `v5_superscalar_v5_core`。
功能与性能等价于 combine-old。merge 层贡献 L3→L4 +27.1%（merge 让重复寄存器合一后
state-loop/pack 的 lane 数大幅减少）。

## 与 e4c5e82f 的差异（均为有意）

- `SeqBank`/`DelayBank` 合并并改名为 `RegLoop`/`DelayLoop`（单头 `pyc_state_loop.hpp`），
  `SeqBankPartitionPass` → `StateLoopPartitionPass`，`--state-loop` 取代旧旗标。
- 不含 `VecBank`/`PackedRegBank` 及 `--no-seq-bank`、对应 smoke/测试（死代码，未接入主路径）。
- 去掉 pack 统计计数器与重复头文件（`include/cpp` 与 `runtime/cpp` 的两份拷贝合一）。
- `pyc-state-optimize` 内 merge 在 dead-state 清理之后（e4c5e82f 在其之前），结果等价。
- 编译器相关目录净减约 2000 行（+1401 / −3379）。

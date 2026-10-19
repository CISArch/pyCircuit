# 取消寄存器打包（reg pack）、改用银行轮询（bank）——需求分析与实施规划

> 状态：**三项决策已拍板（见末尾「待确认事项」），方案待最终批准；尚未修改任何代码，也未创建新目录/分支**。
> 日期：2026-10-19。
> 本文档放在工作区根目录（与 `branch-ancestry-perf.md` 同级）；批准并建好新开发目录后，应随实施同步复制到新仓库的 `docs/` 下。

## 背景与目标

pyCircuit 把电路编译成 C++ 仿真模型（`pycc --emit=cpp`）。项目目标是提升这个 C++ 模型的仿真速度（cycles/s）。

生成的模型采用「change-driven（变化驱动）」调度：每个寄存器在时钟沿提交新值时，如果值**没有变化**，依赖它的组合逻辑（comb）就不会被唤醒重算；值变了，才把依赖它的 comb 标记为 dirty 去重算。这个「没变就跳过」的能力是模型快的重要来源。

目前 `zxy/feat/cycle-combine`（远端 `e4c5e82f`）上有两套互相重叠的「降低寄存器对象数量」手段：

1. **IR 级打包（pack）**：编译期把多个同时钟/同使能的寄存器（delay_line 也算）拼成一个更宽的寄存器，读出时再用 extract 切回各自的位段。对象变少，但**拼成的宽寄存器只有一个「值是否变化」的判断**：只要其中任何一个小寄存器变了，所有从这个宽寄存器 extract 出来的下游都被唤醒。原本某个小寄存器没变、下游本可跳过的情况就丢了。
2. **银行（bank）化 lowering**：C++ 发射阶段，同一时钟域的寄存器收进一个 `SeqBank`（delay_line 进 `DelayBank`，向量寄存器进 `VecBank`）。银行里每个寄存器仍是独立的一条 lane，用一个循环轮询所有 lane 去采样/提交，并用 **per-lane 的脏位图**记录哪些 lane 的值真的变了，只唤醒变了的 lane 的下游。寄存器在 IR 里**不合并**，所以保留跳过能力。

**用户目标**：不再做任何 reg pack（因为 pack 之后损失了下游 change-driven 的跳过能力），只依靠银行循环轮询来换取性能，并保持跳过能力。

## 项目现状与执行流程定位

对 `--emit=cpp` 的编译流水线（`compiler/mlir/tools/pycc.cpp`，约 2630–2660 行）中与 pack/bank 相关的步骤，顺序如下：

1. `EliminateDeadState` 等前置清理。
2. **`StateOptimizePass`**（仅 cpp 发射）：依次做等价状态合并、retiming、delay chain 形成与共享，最后调用 `runPackStateLanes(function, packMaxWidth)` —— 这就是 **pack ① state-lane 打包**，由 `--state-pack-width`（默认 **1024**，0 = 禁用）控制。
3. `SLPPackWiresPass`：把 `pyc.vcreate` 等 **wire/组合逻辑**按元素打包（SLP 向量化）。它不是寄存器，不改变寄存器的唤醒粒度。
4. `CombCanonicalize`、`CheckClockDomains`。
5. **`PackI1RegsPass`**（所有发射目标都会执行，无开关）：把连续的、同 clk/rst/en 的 **i1 寄存器**拼成一个宽寄存器——这是 **pack ② i1 打包**。同样会丢失每个 bit 的独立唤醒。
6. **`SeqBankPartitionPass`**（cpp 发射、`--seq-bank` 默认开）：只做分析，给每个 reg / 标量 delay_line 打上 `pyc.seq_bank_id`（按等价时钟分组）。注意它跑在 pack 之后，所以分组的对象是**打包后**的寄存器。
7. C++ 发射（`CppEmitter.cpp`）：按 bank id 发出 `SeqBank<W>` / `DelayBank<W>` / `VecBank<T>`；若显式加 `--packed-bank`，则改发 `PackedRegBank`（把银行里所有 lane 存进连续位存储，仍 per-lane 唤醒；默认关）。

即：当前默认配置是「IR pack（1024 位上限）+ i1 pack + SeqBank」叠加，**pack 先把寄存器合并，bank 再对合并后的宽寄存器分组**。

## 相关现有实现说明

- `compiler/mlir/lib/Transforms/PackStateLanesPass.cpp`：实现 pack ①。`maxWidth == 0` 时直接返回，不打包。
- `compiler/mlir/lib/Transforms/StateOptimizePass.cpp`（约 96 行）：在 StateOptimize 末尾调用 `runPackStateLanes`。
- `compiler/mlir/lib/Transforms/StateOptimization.cpp`：观测/探针解析里认识 `pyc.state_pack_lsb`（packed extract 的位偏移标记）；不打包时这些分支不会触发，但代码保留。
- `compiler/mlir/lib/Transforms/PackI1RegsPass.cpp`：实现 pack ②，在 `pycc.cpp` 里无条件加入 pass 管线。
- `compiler/mlir/lib/Transforms/SeqBankPartitionPass.cpp`：分组分析。
- `runtime/cpp/pyc_seq_bank_ext.hpp`：`DelayBank`、`VecBank`、`PackedRegBank`；`SeqBank` 同族。采样循环遍历全部 lane；`commit()` 返回 per-lane 脏位图（`dirty_`，delay 另有 `advanced_`），生成代码只唤醒位图中置位的 lane 的下游。
- `runtime/cpp/pyc_change_scheduler.hpp`：`DirtyBitset`，下游 comb 的 dirty 集合。
- `compiler/mlir/test/` 下与 pack 相关的测试：`state_optimization_stage15_stage2.mlir`、`state_pack_probe*.{mlir,cpp}`、`state_delay_optimization_smoke.sh`、`delay_line_diagnostics_smoke.sh`（均显式 `--state-pack-width=192`）、`_state_model_check.py`（用 `--state-pack-width=0` 做对照）。

## 已有的实测证据（决定本方案风险的关键）

数据均取自 `branch-ancestry-perf.md` 与 `auto_perf_logs/*/result.json`（34 条 trace 几何平均 cycles/s，P/V = pycircuit/verilator）：

| 配置 | 提交 | gm cycles/s | P/V | 备注 |
|---|---|---|---|---|
| pack 192、无 bank | a9dc4e2d | 2560.5 | 0.567 | 基线 |
| **pack 关闭、无 bank** | 99a1fcb6 | **1310.0** | 0.298 | **−48.8%**，34/34 全慢 |
| pack 1024、无 bank | e26d5756 | 2718.6 | 0.608 | +6.2% |
| pack 1024 + SeqBank + DelayBank + VecBank | seq-bank c3224848 | 3047.8 | 0.691 | 当前 seq-bank 终态 |
| 同上，cycle-combine 合并后 | zxy/feat/cycle-combine e4c5e82f | **3145.3** | 0.717 | 本方案的对照基线（34/34 pass 且全 MATCH）；同一提交的家族另几次实测 3211.9、3241.3，噪声约 ±3% |

关键结论：

1. 「pack 关闭」**只在没有 bank 的时代测过**（1310.0，−48.8%）。那次慢的主因是寄存器对象数量爆炸（每个寄存器一份独立的 tick/commit 代码），不是跳过能力的问题。
2. 之后加入的 SeqBank/DelayBank/VecBank 正是为了消除这个「对象税」。但**所有 bank 实测（含 3047.8 与 3145.3）都是在 pack 1024 仍开启的情况下测的**，「pack 关闭 + bank」这一组合**从未被测过**。
3. 因此用户的目标（pack 关闭 + bank）是否真的更快，目前**没有数据**；这是一个需要先实测验证的假设，而不是已知结论。

## 需求与验收标准

功能需求：

- F1：`--emit=cpp` 的默认编译配置下，不再执行 pack ①（state-lane 打包）和 pack ②（i1 寄存器打包）。生成模型中每个原始寄存器/标量 delay_line 保持独立 lane，经 `SeqBank/DelayBank/VecBank` 轮询。
- F2：银行的 per-lane 脏位图唤醒语义保持不变（没变化的 lane 不唤醒下游）。
- F3（已按决策 2 选 C 调整）：`PackI1RegsPass` 在**所有发射目标（含 Verilog）**默认关闭，因此 Verilog 网表会发生变化（i1 寄存器不再合并，primitive 数增加）。需要用 Verilator 对拍确认功能等价。
- F4：仍可通过显式旗标（`--state-pack-width=<N>`、`--pack-i1-regs`）重新开启 pack（便于 A/B 对比与回退）。

验收标准（均基于 auto_perf 的 DavinciTop 34 条 trace）：

- A1（正确性，硬性）：34/34 `status=pass`，`common_metrics_match` 全真（MATCH）；仓库自带 `make smoke`、相关 MLIR/pytest 测试通过。
- A2（性能，主判据）：新配置 gm cycles/s 相对对照基线 `zxy/feat/cycle-combine@e4c5e82f` 的 3145.3，**不低于 −3%（噪声带）**视为「不退化」；高于 +3% 视为「有收益」。
- A3（唤醒精度，辅助判据）：生成代码里不再出现 `pyc.state_pack_lsb` 的 packed extract；pass stats 中 `pack_state_lanes` 的 `packed_state_ops` 为 0（或字段缺省）；P/V 不低于基线 0.717 的 −3%。
- A4：若 A2 判定为明显退化（< −3%），**不合入默认**，改为交付「可选旗标 + 实测报告」，并在文档中记录原因（见待确认 1）。

## 方案设计

### 模块边界、输入与输出

- 输入：pyc MLIR（前端生成），经 `pycc --emit=cpp` 编译。
- 输出：C++ 仿真模型。本方案只改变 **StateOptimize 阶段是否打包** 和 **PackI1Regs 是否对 cpp 发射生效**，不改 SeqBank/DelayBank/VecBank 的运行时语义。
- 不属于本方案范围：`SLPPackWiresPass`（wire 打包，不影响寄存器唤醒粒度）；`PackedRegBank`（保持 opt-in 不动）；Verilog 发射。

### 上下游关系与数据/控制流

打包关闭后，数据流变为：前端 IR 寄存器 → StateOptimize（等价合并、retiming、delay chain，**无 pack**）→ SeqBankPartition（按时钟分组，对象是原始寄存器）→ CppEmitter（`SeqBank<W>` 按宽度/时钟域分银行）。下游 comb 的唤醒来自银行 `commit()` 返回的 per-lane 脏位图。

需要注意的潜在副作用（实测要重点看）：

- 打包前 IR 里寄存器很多（DavinciTop 约 5890 个被打包的 state op），`SeqBank<W>` 是**按宽度**分模板（`W` 不同分不同银行）。关闭 pack 后，宽度种类更多、每个银行 lane 数更大，采样循环遍历的 lane 总数变多——这是「轮询」的成本，需要看是否抵消跳过能力的收益。
- 发射代码体量变化可能影响 host 编译时间（clang 编译 `-O` 的耗时）。需在实测里记录 compile_seconds。

### 文件和接口改动清单

分三步，每步一个原子提交，便于单独回退和测量：

1. **步骤 1（最小）**：`compiler/mlir/tools/pycc.cpp`：`--state-pack-width` 的 `cl::init` 从 1024 改为 0。`StateOptimizeTunables::packMaxWidth`（`compiler/mlir/include/pyc/Transforms/StateOptimization.h`）默认值同步改 0；`PackStateLanesPass.cpp` 的 `max-width` 选项默认改 0（保持「0 = 禁用」的现有语义，不需要改 pass 内部逻辑）。
2. **步骤 2**：`compiler/mlir/tools/pycc.cpp`：新增 `--pack-i1-regs` 旗标（默认 false），所有发射目标（cpp 与 verilog）都按该旗标决定是否加入 `createPackI1RegsPass()`；`PackI1RegsPass.cpp` 本身不改，pass 仍可通过 `pyc-opt` 单独使用。
3. **步骤 3（收尾）**：更新相关测试与文档：
   - `state_delay_optimization_smoke.sh`、`delay_line_diagnostics_smoke.sh`、`state_optimization_stage15_stage2.mlir`、`state_pack_probe*`：这些用例是专门验证「pack 打开时」的行为，保持显式 `--state-pack-width=192`，不改；新增一条「默认配置下 pack 关闭」的断言用例（检查 stats 中 `packed_state_ops` 为 0、生成 C++ 无 `state_pack_lsb`）。
   - `docs/delay_line.md`：更新 `--state-pack-width` 默认值说明与 9.4 / 17.3 节的结论，注明「在 bank 化之后 pack 不再默认开启」及实测依据。
   - 根目录 `README.md`、`AGENTS.md`：新增目录、分支、实测数据。

### 边界条件、错误处理与兼容性

- `--state-pack-width=<N>` 仍可显式开启（回退通路）；`_state_model_check.py` 用 0 做对照的用法不变，且现在等价于默认。
- 已知失败模式：`--state-pack-width` 不封顶会让 `SumWidth<>` 变参模板超过 clang 的 1024 层递归上限（旧 `39b26a2c`）。本方案**不涉及**不封顶，不触发该问题；关闭 pack 后宽度更小，更不会触发。
- Verilog 兼容（决策 2 选 C 带来的影响）：步骤 2 会改变 Verilog 网表（i1 寄存器不再合并），可能影响依赖旧网表的 Verilog 测试、Verilator 对拍及面积综合（Nangate45 面积会略有变化）。必须在步骤 2 提交后跑：`make smoke` 中的 Verilog 路径、`flows/scripts/run_sims.sh`、auto_perf 的 Verilator 侧（`common_metrics_match`）；若有测试对 i1 打包后的 Verilog 文本做了快照，需同步更新或显式加 `--pack-i1-regs`。
- 探针/观测（`--probe`、observe named）：打包关闭后探针直接绑定原始寄存器，不经 `state_pack_lsb` extract。银行化探针路径（`delayBinding`、`DelayBank::TapView`）已存在并测过，但「pack 关闭」下的探针覆盖面比以前大，需要由 smoke 测试覆盖。

## 与既有文档和约束的一致性检查

检查范围：工作区 `AGENTS.md`、`README.md` 分支树、`branch-ancestry-perf.md`、仓库内 `docs/delay_line.md`、`docs/MLIR_PASS_PIPELINE.md`，以及 `zxy/feat/cycle-combine` 的编译器源码。

- 工作区规则「一个功能 = 一个目录 = 一个分支」：本方案**不在** `pyCircuit-seq-bank/`、`pyCircuit-cycle-combine/` 等现有目录里修改，而是新建 `pyCircuit-no-pack-bank/`，从 `origin/zxy/feat/cycle-combine@e4c5e82f` clone，新分支建议 `ldz/feat/no-pack-bank`。符合。
- 仓库 AGENTS.md「Gate-first」：本方案不改变 dialect 语义，仅改 pass 管线的默认配置与一个旗标，不涉及「仅后端的语义修复」。符合。
- `docs/delay_line.md` 的现有结论（pack 是 DavinciTop 净收益、默认 1024）是**在无 bank 时代**得出的，与本方案的新假设不冲突，但需要在文档里加注「该结论在 bank 化之前成立」。
- `branch-ancestry-perf.md` 记录⑤⑦（pack 关闭 −48.8%）：与本方案不矛盾，那次没有 bank；本方案正是要验证这一点。
- 发现的约束冲突：**无**。

## 测试与验证计划

环境与前置：LLVM/MLIR 19，`make tools` 构建 `pycc`；宿主机 CPU 在 auto_perf 出数前必须空闲（历史教训：CPU 被占满会使 34/34 均匀劣化，见 `branch-ancestry-perf.md` 记录⑧补）。

1. **功能回归**（每个提交都跑）：
   ```bash
   cd pyCircuit-no-pack-bank
   make tools && make smoke
   ```
   外加相关 MLIR/脚本测试：`compiler/mlir/test/state_delay_optimization_smoke.sh`、`delay_line_diagnostics_smoke.sh`、`_state_model_check.py`（需要 `PYCC` 指向新构建产物）。
2. **性能 A/B（核心）**：每个步骤提交 push 到远端分支（或用本地路径方式，见 `perf-test-request` skill），经 auto_perf（HTTP 8790）提测，取 `result.json` 的 34 条 trace：
   - 对照基线：`zxy/feat/cycle-combine@e4c5e82f`，gm 3145.3 / P/V 0.717（已有 task：`task-20261019T084403444617Z-zxy_feat_cycle-combine-e4c5e82f`）。
   - 步骤 1 提交 = 「pack ① 关闭 + bank」；步骤 2 提交 = 「pack ①② 都关闭 + bank」。
   - 每个配置**至少重复 3 次**入队，取中位数；宿主 CPU 空闲时测。统计量：34 条 trace 的 cycles/s 几何平均、P/V 几何平均、快/慢条数、compile_seconds。
   - 通过阈值：见验收标准 A1–A4。
   - 步骤 2 另需确认 Verilator 侧 34/34 仍 MATCH，并记录 Nangate45 面积（auto_perf 全 PASS 后自动异步产出）相对基线的变化。
3. **唤醒精度验证**：对比步骤 1 前后 `--emit=cpp` 的 compile stats（`pycc` 输出的 `packed_state_ops` / `pack_bits`），确认从约 5890 降到 0；抽样检查生成 C++ 中不含 `state_pack_lsb` extract。
4. **结果回写**：把实测数据与偏差补写到本文档，并更新 `branch-ancestry-perf.md` 与 `README.md` 分支树。

## 实施步骤

（仅在用户批准后执行）

1. 按 `new-feature-workspace` skill：从 `origin/zxy/feat/cycle-combine@e4c5e82f` clone 出 `pyCircuit-no-pack-bank/`，建分支 `ldz/feat/no-pack-bank`；同步更新工作区 `README.md` 与 `AGENTS.md`（目录、分支、checkout）。
2. 步骤 1 提交（默认 `--state-pack-width` 1024→0）；本地 `make smoke`；提测 3 次。
3. 若步骤 1 数据支持，步骤 2 提交（`--pack-i1-regs` 旗标，cpp 默认关）；本地验证；提测 3 次。
4. 步骤 3：补测试、更新 `docs/delay_line.md`，运行完整验证。
5. 汇总实测，回写文档；按 A2/A4 判定是否建议合入默认。

## 待确认事项

无待确认项。用户已拍板三项决策（2026-10-19），后果如下：

1. **性能退化的处理 = 先分析并优化银行轮询，再判定。** 若「关 pack + bank」实测低于对照基线 3145.3 的 −3%，先分析原因并在本分支优化银行轮询（可能修改 `runtime/cpp/pyc_seq_bank_ext.hpp`、`CppEmitter.cpp`，如按脏位图跳过整字空闲 lane），重测；优化后仍低于 −3% 则退回「默认不改、仅提供显式旗标 + 实测报告」。后果：范围可能扩大到银行运行时与发射器；默认值只在达标后才改。
2. **`PackI1RegsPass` 全局默认关闭（含 Verilog）。** 新增 `--pack-i1-regs` 旗标，默认 off，对 cpp 与 verilog 一致生效。后果：Verilog 网表会变化，需要 Verilator 对拍、面积综合与相关测试快照一起验证；这是此次决策带来的额外验证成本。
3. **新目录 `pyCircuit-no-pack-bank/`，分支 `ldz/feat/no-pack-bank`，基于 `zxy/feat/cycle-combine@e4c5e82f`。** 后果：与已测对照基线（3145.3 / 0.717）同源，A/B 干净；若有收益可直接提 PR 给 cycle-combine。

## 实施与实测记录（2026-10-19）

分支 `ldz/feat/no-pack-bank`（基于 `zxy/feat/cycle-combine@e4c5e82f`），已推送远端。提交：

| 提交 | 内容 |
|---|---|
| `cca01133` | 本规划文档 |
| `4bd4f556` | `--state-pack-width` 默认 1024→0（步骤 1） |
| `2df2beb1` | `--pack-i1-regs` 旗标，默认关，cpp 与 verilog 一致（步骤 2，含测试与文档） |

本地验证：`make tools && make install && make smoke`（examples + sims）通过；`state_delay_optimization_smoke.sh`（含新增的默认不打包 / i1 打包旗标门）、`delay_line_diagnostics_smoke.sh`、`comb_dirty_scheduler_smoke.sh` 全部 PASS。

auto_perf（DavinciTop 34 trace，每个配置 3 次，宿主空闲，全部 34/34 `pass` 且 `common_metrics_match` 全真）：

| 配置 | 提交 | 3 次 gm cycles/s | 中位数 | 相对基线 3145.3 |
|---|---|---|---|---|
| 基线：pack 1024 + i1 pack + SeqBank | `e4c5e82f` | 3145.3（该家族另测 3211.9、3241.3） | 3145.3 | — |
| pack① 关、i1 pack 开 + bank | `4bd4f556` | 1916.3 / 1996.5 / 1975.8 | 1975.8 | **−37.2%**（34/34 全慢） |
| pack①、i1 pack 全关 + bank | `2df2beb1` | 2977.8 / 2948.9 / 3035.3 | 2977.8 | **−5.3%**（每次快 5/4/12、慢 29/30/22 条） |

结论（对照验收标准）：

- A1 通过：两个配置均 34/34 MATCH。
- A2 **未通过**：最终配置（`2df2beb1`）中位数 −5.3%，落在 −3% 噪声带之外（基线家族自身波动约 ±3%）。
- 新发现：只关 pack①、保留 i1 pack 时（`4bd4f556`）最差（−37%）。保留 i1 pack 时它会把更多相邻 i1 寄存器拼成宽寄存器，再叠加 bank，慢得多；i1 pack 一并关闭后立刻恢复到 −5%。因此「去掉所有 reg pack」必须两处同时关，单关 pack① 是更差的中间态。
- 按待确认 1 的决策：先分析并优化银行轮询，再重测；优化后仍低于 −3% 则不改默认。**银行轮询优化尚未做**（需要在新配置下对生成的 DavinciTop C++ 做采样剖析，确认剩余 5% 的来源，见下）。

## 剩余差距的初步判断（待剖析验证，未经实测）

- `SeqBank::compute_rise()` 与 `commit()` 对**所有 lane** 每个周期各遍历一次（采样时读 `rst/en/d` 三个指针目标，提交时检查 `pending_`），`lane` 的 `q/d/rst/en` 都是指向模型结构体里分散位置的指针；不打包后 lane 数更多，遍历与指针追逐的成本随 lane 数线性上升，与寄存器是否变化无关。
- 候选优化方向（均需剖析确认后再选）：① 对静止 lane（`en==0 && rst==0`）不读 `d`、不写 `qNext_`；② 按脏位图按字跳过整字空闲 lane；③ 让 lane 的 `d/en/rst/q` 在银行内连续存放以减少指针追逐。

## 补充实验：只关 i1 打包，保留 state-lane 打包（2026-10-19，分支 `ldz/feat/no-i1-pack`）

动机：上面的实测里，只关 state-lane 打包而 i1 打包仍开是最差（−37%），两处全关为 −5.3%，说明 i1 打包是否开启影响很大。本实验把 `--state-pack-width` 默认值恢复为 1024，只保留 `--pack-i1-regs` 默认关闭，单独看 i1 打包的作用。提交 `593933e0`（在 `2df2beb1`/`d70a998f` 之上，revert `4bd4f556` 的默认值改动）。

| 配置 | 提交 | gm cycles/s（次数） | 中位数 | 对比基线 3145.3 |
|---|---|---|---|---|
| pack① 1024 + i1 pack + bank（基线） | `e4c5e82f` | 3145.3 | 3145.3 | — |
| pack① 关 + i1 pack 开 + bank | `4bd4f556` | 1916.3 / 1996.5 / 1975.8 | 1975.8 | −37.2% |
| pack① 关 + i1 pack 关 + bank | `2df2beb1`/`d70a998f` | 2977.8 / 2948.9 / 3035.3 / 3031.4 | 3004.7 | −4.5% |
| **pack① 1024 + i1 pack 关 + bank** | **`593933e0`** | **3197.5 / 3205.9 / 3195.7** | **3197.5** | **+1.7%**（快 19/22/21、慢 15/12/13；34/34 MATCH） |

结论（**已更正**：初版结论把 +1.7% 误读为"关 i1 打包带来的收益"，生成代码比对后推翻，见下）：

- **`593933e0` 与基线 `e4c5e82f` 生成的 C++ 完全一致**（DavinciTop `v5_superscalar_v5_core` 用两套旗标各生成一次，`diff -r` 仅 manifest 里的输出路径不同；`compile_stats` 的 `reg_count=3272`、`pack_groups=496` 等也相同）。原因：state-lane 打包（1024）先把能打包的 i1 寄存器拼走了，`PackI1RegsPass` 已无可合并的 i1，是空操作。所以这 +1.7% 只是测量噪声（同一份代码的波动 ±3%），**不是 i1 打包关闭带来的收益**，也不能据此说 i1 打包有害。
- i1 打包只有在 state-lane 打包关闭时才起作用，此时它有害：同为 pack① 关闭，i1 打包开（`4bd4f556`）−37.2%，关（`2df2beb1`）−4.5%。生成代码对比（`--state-pack-width=0` 加/不加 `--pack-i1-regs`）：reg 对象 16150→12469（合并了 3681 个 i1 reg），但生成 C++ 678,749→798,026 行（+17.6%），extract/slice 引用 51,754→75,847（+47%），因为每个被合并的 i1 都要从宽寄存器里 extract 出来给下游，合并侧要拼接；此外合并后的宽寄存器任一 bit 变化会唤醒全部 extract 下游。哪一项是 −37% 的主因尚未剖析验证。
- state-lane 打包在当前 bank 实现下仍是净收益：开（基线 3145–3205）对关（3004.7，两处全关）约 +5%~+6%。生成代码对比：reg 对象 16150→3272，`SeqBank` 的 add_lane 调用 167→315 次，lane 数少了约 5 倍（单 lane 更宽）；打包把轮询的 lane 数降下来，而它丢失的 per-lane 跳过能力，没有大到抵消这一收益。
- 因此：「完全不做 reg pack」目前不成立（欠约 4.5%），「只关 i1 打包」在 pack① 开启时没有任何效果。本分支 `ldz/feat/no-i1-pack` 实际上与基线代码等价，不建议合入，仅保留作为证据。

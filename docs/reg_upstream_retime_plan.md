# 支路寄存器上移（retiming）需求分析与实施规划

日期：2026-11-02。状态：已批准选项 B，并在 `ldz/exp/reg-upstream` 实现。一次只跨过一个组合操作；多输入时每个非常量输入一个寄存器，位数允许增加。不一次跨过整棵锥。`pyc.stats.hoist_blocked_fanin` 不输出，因为选项 B 不因位数变多而放弃。

## 背景与目标

Davinci 里很多流水级不是「每条支路同样多拍」。分叉之后，一条支路比另一条多一拍或几拍。多出来的那些寄存器插在组合逻辑中间，把本来可以连成一片的组合逻辑切开。两条支路拍数不同，不能收成同一个寄存器（拍数差是电路语义，消掉会错）。

本次只做一件事：在不改变每条支路总拍数的前提下，把多拍那条支路上的寄存器尽量往上游（靠近分叉、靠近输入）挪。挪完以后，被越过的组合逻辑落到寄存器下游，和汇合点、以及另一条支路同一拍上的组合逻辑连成一片，给后面的 CSE / comb 融合留空间。

示意（`R` 是寄存器，其余是组合逻辑）：

```
现在:   分叉 ─ f ─ R ─ g ─ 汇合
        分叉 ─ h ───── 汇合

上移后: 分叉 ─ R ─ f ─ g ─ 汇合
        分叉 ─ h ───── 汇合
```

`f`、`g`、`h` 和汇合点之间不再有寄存器。长支路仍然比短支路多 1 拍，多出来的那拍贴在分叉口。

这不是把两条支路收成一个寄存器。并行的 `cycle_balance` 拷贝合并不在本次范围。

## 项目现状与执行流程定位

分析用的编译器是实验栈终点 `pyCircuit-dirty-consume`，分支 `ldz/exp/dirty-consume`，提交 `f70f6a6`。IR 来自 auto_perf 任务 `task-20261101T072932427879Z-ldz_exp_dirty-consume-f70f6a60` 里、`pyc-state-optimize` 之前的 13 个模块 dump：21079 个 `pyc.reg`，906992 bit。

前端把 pyCircuit 设计降成 pyc MLIR。`pycc --emit=cpp` 按 `docs/MLIR_PASS_PIPELINE.md` 跑 pass。和本次有关的一段是：

1. `pyc-eliminate-wires`：能替换的 wire 换成直连。
2. `pyc-eliminate-dead-state`：删掉外部看不到的死状态。
3. `pyc-state-optimize`（只在 C++ 路径）：死状态 → 现有 retiming → 规范化加 CSE → 再清死状态 → 把串行寄存器收成 `pyc.delay_line`。
4. 更后面的 `pyc-fuse-comb` 把连续组合逻辑收成 `pyc.comb`。

寄存器在融合时会被提到块首，所以「q 和 next 能不能进同一个 comb 函数」已经不是切分点。本次要连上的是**数据流上的状态边**：现在 `f` 在 `next` 一侧、`g` 在 `q` 一侧，中间隔着寄存器；上移之后 `f(g(...))` 都在 `q` 的下游，中间没有状态边。后面的 comb 划分看到的是一块，而不是被寄存器切开的两块。

Verilog 路径不跑 `pyc-state-optimize`。本次改写放在这个 pass 里面，Verilog 网表保持原样。这和现有 retiming、delay-line 的约定一致。

## 相关现有实现说明

`compiler/mlir/lib/Transforms/RetimePipelinesPass.cpp` 做两种改写，都由 `StateOptimizePass` 调用：

- **流水线折叠**：要求一串寄存器，级与级之间的组合逻辑只能依赖前一级 `q` 加常量，然后收成一条 `pyc.delay_line`，后面的级用 tap 重算。方向是「历史放在最前面，组合逻辑放到 tap 后面」。它不处理「只有一个寄存器、后面还有组合逻辑」的支路，也不处理多输入组合逻辑。Davinci 上 `retime_regions_rewritten = 0`，两个 PE cluster 各有 15 个候选因为折叠后位数变多被丢掉（`retime_blocked_cost = 30`）。
- **common-delay sinking**：把多个状态共有的下游组合逻辑改去读 `next`，从而和产生 `next` 的逻辑合成一块。这是把组合逻辑拉到寄存器前面。本次要的是相反方向：把寄存器挪到组合逻辑前面。

`CombineDelayChainsPass` 只认「下一级 `next` 穿过 alias 直接接到上一级 `q`」的串。组合逻辑夹在中间时不成链。寄存器上移之后，如果两级变成直连，这一步才能把它们收成 delay-line。所以上移要排在成链之前。

观测身份（`pyc.name`、probe、trace 等）由 `hasExternalObservationIdentity` 判定。`cycle_balance` 自动名字不算外部身份。改写不能让 probe / VCD / `dut.read` 读到另一个拍上的值。

`pyc.reg` 的操作数顺序是 `clk, rst, en, next, init`。很多 Davinci 寄存器的 `en` 是常量 1，保持写在 `next` 里：`next = mux(cond, data, q)`。这种形式先看成 `en = cond`、数据是 `data`，再考虑上移。嵌得更深的自环（计数器、状态机）不动。

## 需求与验收标准

功能需求：

1. 一个寄存器的数据输入是纯组合操作，输出侧（剥掉保持 mux 和 alias/wire 之后）还有组合逻辑用户时，允许把该寄存器向上游跨过这个操作。
2. 跨过之后，该操作改在寄存器 `q` 的下游重算；其它支路、端口、不相关用户看到的值不变。每条从输入到输出的路径上，寄存器个数不变。
3. 保持 mux `mux(cond, data, q)` 先收成 enable，再上移 data 路径。`en = 0` 时输出保持，和改写前一致。
4. 复位初值必须对得上：新初值经过被跨过的操作，常量折叠结果等于旧初值。对不上就放弃这一步，电路保持原样。
5. 重复做到不动为止，使同一条支路上能跨的寄存器都贴到上游边界。
6. 带外部观测身份的组合操作：原操作留在原拍，供 probe 读取；寄存器下游使用克隆出来的副本。没有观测身份、且唯一用户就是这个寄存器时，直接把操作挪到下游，不复制。
7. 反馈（数据锥里读到自己的 `q`）、存储器、实例、非常量多驱动 wire：不跨。

非功能需求：

- 只改 C++ 编译路径，Verilog 行为不变。
- 不新增 IR 操作，不改 `pyc.reg` 的语义定义。等价性由 pass 保证。
- 代码只加这一次改写所需要的文件和调用，不重构现有 retiming。

验收：

- 新的 FileCheck 门禁覆盖：单输入上移成功、两拍支路把寄存器顶到分叉侧、初值不合法则不动、自环不动、观测名字仍指向原拍。
- 现有 `state_retime_smoke.sh` 仍然通过。
- 一个小电路的 C++ 模型与手写周期模型逐拍一致（做法见测试计划）。
- `make smoke` 通过。

本次不验收「Davinci 周期变快」。上移是为后面的 comb 优化腾地方，本身可能增加少量组合逻辑副本。性能只做记录，不作为通过条件。

## 方案设计

### 模块边界、输入与输出

新 pass 名：`pyc-hoist-regs-upstream`。输入是一个 `func.func` 里的 `pyc.reg` 和它们周围的组合逻辑。输出是同一函数：某些寄存器的 `next` 改到更上游的值，被跨过的组合操作出现在 `q` 的用户侧。函数端口、时钟复位、寄存器个数在「不增加位数」的策略下不变。

统计写到函数属性上，便于和现有 `pyc.stats.retime_*` 一样在编译统计里看到：

- `pyc.stats.hoist_regs_upstream`：成功上移的寄存器次数（同一寄存器跨多步算多次）。
- `pyc.stats.hoist_ops_moved`：挪到下游的组合操作数。
- `pyc.stats.hoist_blocked_init`：因初值无解而放弃的次数。
- `pyc.stats.hoist_blocked_fanin`：因会增加寄存器位数而放弃的次数。

### 上下游关系与数据/控制流

`StateOptimizePass::runOnOperation` 的顺序改为：

1. `runEliminateDeadState`
2. **`runHoistRegsUpstream`（新）**
3. `runRetimePipelines`（现有，不改匹配规则）
4. canonicalize + CSE
5. `runEliminateDeadState`
6. `runDelayChainFormAndShare`

先上移，再跑现有流水线折叠和成链。上移可能把 `f → R → g → R` 收成 `R → R → f → g`，后面的成链才能把直连的两级收成 delay-line。CSE 仍然留在 retiming 后面，因为现有 sinking 依赖它。

一次上移只跨过**生产 `next` 的那一个操作**，不一次跨过整棵锥。整棵锥一起跨会在每个叶子上放寄存器。在这份 Davinci IR 上，3678 个多叶子锥会从约 8.9 万 bit 变成约 598 万 bit，不能这么做。

单步规则（数据 `next` 已经剥掉一层保持 mux）：

- 根操作在白名单内：与现有 retiming 相同的纯组合操作（`add/sub/mul/and/or/xor/not/mux/eq/ult/slt/trunc/zext/sext/extract/shli/lshri/ashri/shl/lshr/ashr/concat`）。不跨 `v_get`、除法、存储器、实例。
- 根操作不读本寄存器的 `q`。
- 剥掉 alias/wire 之后，`q` 至少有一个组合逻辑用户。只有下一级寄存器、没有组合用户的，留给现有成链，不上移。
- 每个非常量输入变成一个新的采样点。常量输入仍然是常量，不为之新建寄存器。
- **位数可以增加**（已选选项 B）：每个非常量输入一个新寄存器。单输入时位数不变。不一次跨过整棵锥。

改写形状（单输入，初值可解）：

```
改写前:
  %n = pyc.xor %s, %c
  %r = pyc.reg %clk, %rst, %en, %n, %init
  %u = pyc.and %r, %k

改写后:
  %r = pyc.reg %clk, %rst, %en, %s, %init_pre
  %n2 = pyc.xor %r, %c
  %u = pyc.and %n2, %k
```

`%n` 若没有别的用户且没有观测身份，删除。若有观测身份，`%n` 留在原处继续表示未打拍的值。

初值：沿用 `RetimePipelinesPass` 里已有的常量折叠（`evaluateConeOp` 一类逻辑，抽共用或在新文件里写一份同等的单操作折叠，不复制整份流水线匹配）。对新初值只尝试结构求解，例如 `xor` 常量、`add` 常量、`not`，以及「旧初值是 0 且该操作在 0 上得到 0」。不搜索 `2^位宽`。无解则 `hoist_blocked_init += 1`，本寄存器本步跳过。

多输入时：原寄存器换成每个非常量输入上的一个寄存器，下游用这些 `q` 重算原操作。这些新寄存器共用原 `clk/rst/en`。任一输入的初值无解，则整步放弃。

固定点：每轮扫描所有寄存器，本轮没有任何一次成功就停。每轮每个寄存器最多跨一步，避免在一轮里沿着链来回改。

### 文件和接口改动清单

实现放在新目录 `pyCircuit-reg-upstream/`，分支 `ldz/exp/reg-upstream`，从 `ldz/exp/dirty-consume` 的 `f70f6a6` 拉出来。不在 `pyCircuit-dirty-consume/` 里改代码。工作区根 `README.md`、`AGENTS.md` 增加这个目录。本规划在批准后移到新目录的 `docs/`，并从 dirty-consume 工作区删掉未提交的副本。

| 文件 | 改动 |
| --- | --- |
| `compiler/mlir/lib/Transforms/HoistRegsUpstreamPass.cpp` | 新文件。匹配、初值求解、改写、统计。 |
| `compiler/mlir/include/pyc/Transforms/Passes.h` | 声明 `createHoistRegsUpstreamPass` 与 `runHoistRegsUpstream`。 |
| `compiler/mlir/lib/Transforms/StateOptimizePass.cpp` | 在 `runRetimePipelines` 之前调用一次。 |
| `compiler/mlir/CMakeLists.txt` | 把新 cpp 加进 `pyc_transforms` 的源文件列表。 |
| `compiler/mlir/test/reg_upstream_hoist.mlir` | FileCheck 输入。 |
| `compiler/mlir/test/reg_upstream_hoist_smoke.sh` | 跑 `pyc-opt` 并 FileCheck。 |
| `compiler/mlir/test/reg_upstream_hoist_model.cpp` 与一份小 mlir | 逐拍对照，见测试计划。 |
| `.github/workflows/ci.yml` | 在现有 `state_retime_smoke.sh` 旁边加这一条门禁。 |
| `docs/MLIR_PASS_PIPELINE.md`、`docs/delay_line.md` | 补上新步骤的一句顺序说明。 |

不改 `PYCOps.cpp`（没有新操作）。不改 `RetimePipelinesPass.cpp` 的匹配。不改 emitter。

### 边界条件、错误处理与兼容性

- 初值无解、位数会增加、自环、非白名单操作：跳过，不报错，电路保持原样。pass 不因此失败。
- 规范化或 CSE 失败时，仍按 `StateOptimizePass` 现有逻辑 `signalPassFailure`。新 pass 本身不新增失败路径。
- 外部观测名字留在原拍。寄存器自己的名字留在寄存器上，读到的仍是打拍后的值。
- 模块边界：不跨 `pyc.instance`。端口可以作为上移停止处（寄存器改为采样端口），但不能再往端口外面挪。
- Verilog：不跑这个 pass。
- 已有 delay-line 不主动拆开。本 pass 只看 `pyc.reg`。

### Davinci 上这一步大概能碰到多少

在 `state-optimize` 之前的 IR 上，只统计「根操作是组合逻辑，且 `q` 穿过 alias 后立刻有组合用户」的寄存器（12581 个）：

| 根操作的非常量输入数 | 寄存器个数 | 一次上移的位数 |
| --- | ---: | --- |
| 1（不增加寄存器） | 380 | 4709 bit，原样搬走 |
| 多个，但新位宽之和 ≤ 原位宽 | 145 | 16089 → 16039 bit |
| 多个，且位宽会变大 | 12056 | 538067 → 897931 bit |

扇入 2 和 3 是大头（4930 与 7161）。选项 B 会跨过它们，所以一轮上移的位数上界大约从 53.8 万增到 89.8 万。这些数字是上移前的一轮上界，固定点之后还会多一些。

## 与既有文档和约束的一致性检查

对照过：

- `docs/delay_line.md` 第 3 节：现有 retiming 是单源流水线折叠和 common-delay sinking，且写明收益不是位数差。新 pass 是另一步，不放宽那两条的匹配，也不为了减位数去折叠。文档要补一句新顺序。
- `docs/MLIR_PASS_PIPELINE.md` 第 17 行：要改 `pyc-state-optimize` 的内部顺序描述。
- `AGENTS.md` 的 gate-first：不改方言语义，等价改写落在 MLIR pass，并先加 FileCheck 门禁。没有「只改 C++ emitter」的语义修复。
- 工作区「一个功能一个目录」：新目录实施，不动 dirty-consume 的代码。
- 「代码修改最小化」：新文件加一处调用，不重构 `RetimePipelinesPass.cpp`。
- Verilog 不支持 delay-line 的约定：新 pass 不产生新的 delay-line，只重排 `pyc.reg`，且仅 C++ 路径运行。

没有无法规避的冲突。

## 测试与验证计划

1. **形状门禁** `compiler/mlir/test/reg_upstream_hoist_smoke.sh`
   - 输入 `reg_upstream_hoist.mlir`。
   - 命令：`pyc-opt <file> --pass-pipeline='builtin.module(func.func(pyc-hoist-regs-upstream))'`，再用 FileCheck。
   - 用例：单输入 `xor` 上移；短支路无寄存器、长支路 `not` 后寄存器，上移后 `not` 与短支路在同一侧；`not` 的初值 0 能解出初值 1；初值无解的 `ult` 保持原样；`next` 依赖自己 `q` 的保持环不动；带 `pyc.name` 的 `add` 原操作还在，寄存器下游是副本。
   - 通过标准：脚本打印 `reg_upstream_hoist_smoke: PASS`。

2. **现有门禁** `bash compiler/mlir/test/state_retime_smoke.sh` 必须仍 PASS，确认没有改坏流水线折叠。

3. **逐拍模型**
   - 新增一份只含上述「分叉 + 长支路一拍」的 mlir，以及 `reg_upstream_hoist_model.cpp`。
   - 用现有 `compiler/mlir/test/_state_model_check.py` 的 `emit` / `compile_cpp`，对优化后的 C++ 跑固定输入若干拍。
   - 驱动里用普通整数手写同一电路（不经过 pycc），每拍比较输出。
   - 通过标准：进程退出码 0。

4. **回归** `make smoke`。通过标准：该目标退出码 0。

5. **性能记录（不作为功能通过条件）**
   - 本地门禁和 `make smoke` 通过、并且新目录的提交已推送、CI 变绿之后，按 `perf-test-request` 对 `ldz/exp/reg-upstream` 提交 **一次** auto_perf。
   - 对照是同栈 `f70f6a6` 的 12029.6 cycle/s、P/V 2.663（任务 `task-20261101T072932427879Z`）。
   - 看 34 条 trace 是否 MATCH，以及 cycle/s 变化。变慢可以接受，因为本步的目的是 comb 连通，不是当前栈提速。
   - 不自动跑第二次。第一次无效（基础设施失败）时才补一次。

## 实施步骤

批准之后：

1. 按 `new-feature-workspace`：从 `ldz/exp/dirty-consume` @ `f70f6a6` clone 出 `pyCircuit-reg-upstream/`，分支 `ldz/exp/reg-upstream`。把本文件移到新仓库 `docs/`，并更新工作区 `README.md`、`AGENTS.md`。
2. 加 `HoistRegsUpstreamPass.cpp`、Passes.h 声明、CMake 源文件、`StateOptimizePass` 一处调用。
3. 加 FileCheck 门禁和逐拍模型，把 shell 挂进 CI 的 G1 附近（与 `state_retime_smoke.sh` 相邻）。
4. 更新 `docs/MLIR_PASS_PIPELINE.md` 与 `docs/delay_line.md` 的顺序说明。
5. `make tools`，跑新门禁、`state_retime_smoke.sh`、`make smoke`。
6. 提交并推送，看 GitHub CI。CI 与本地编译都通过之后，再提交那一次 auto_perf。

## 待确认事项

已决定：选项 B。多输入操作也上移，每个非常量输入一个寄存器，位数可以增加。一次只跨过一个操作，不跨整棵锥。

### 待确认 1：多输入组合逻辑会让寄存器变多时，还上移吗？

**为何现在必须决定：**

这次改写每一步只把寄存器往上游跨过一个组合操作。操作只有一个非常量输入时，仍然是一个寄存器，只是改采样更早的值，组合逻辑落到寄存器后面，支路在汇合点重新连上。操作有两个及以上非常量输入时，每个输入都要各有一个寄存器，总位数通常变大。不先定这条，pass 的匹配条件和 Davinci 上能不能动起来都不确定，没法开始写。

**相关背景：**

现有 `pyc-state-optimize`（只在生成 C++ 时运行）会折叠「单源寄存器流水线」并做 common-delay sinking，不会把单个支路寄存器往上游挪。Verilog 不跑这段。

在 dirty-consume（`f70f6a6`）对应的 Davinci IR 上，`state-optimize` 之前、并且寄存器输出侧紧挨着组合逻辑的约 12581 个寄存器里：

- 380 个的根操作只有 1 个非常量输入，上移不增加寄存器，涉及 4709 bit。
- 145 个虽有多个输入，但新位宽之和不超过原位宽，16089 bit 略降到 16039 bit。
- 12056 个主要是 2 输入或 3 输入（例如两个同宽信号的 `and`/`add`）。一次上移会把位数从约 53.8 万增加到约 89.8 万。

前两类是「把多出来的拍贴到分叉附近、又不增加状态」的部分。第三类才是 Davinci 里数量最多的支路，但状态变多，后面每拍要采样和提交的位数增加，可能让当前实验栈变慢。无论选哪一个，拍数差都保持，Verilog 都不改，初值解不出就放弃这一步。

**选项与结果：**

- **选项 A：只做不增加位数的上移**
  - 将做：单输入，以及新位宽之和 ≤ 原位宽的多输入。重复做到不能再挪。
  - 不做：位数会变大的 2 输入、3 输入操作。
  - 结果：新 pass、门禁、C++ 路径顺序如正文。Davinci 上第一轮大约几百个寄存器会动，多数 2/3 输入支路保持原样，comb 连通的收益集中在单输入链上。状态位数不升。风险是对「一边多拍」的常见与/或/加法切开帮助很小。
- **选项 B：允许位数变多，一步跨过任意白名单操作**
  - 将做：选项 A 的全部，再加位数变大的多输入。每个非常量输入一个寄存器，共用原时钟、复位、使能。
  - 不做：一次跨过整棵锥（那会把位数抬到约 598 万，明确排除）。
  - 结果：汇合点前的多输入操作也能挪到寄存器下游，comb 更完整。Davinci 状态位数有一轮就增加约 36 万的上界，仿真可能变慢。门禁要多一个「2 输入 and 上移后变成两个寄存器」的 FileCheck。初值仍必须能解，否则该步跳过。

**推荐：**

当时推荐选项 A。审查时改为选项 B，实现按选项 B。

## 验证结果

2026-11-02，本机：

- `reg_upstream_hoist_smoke.sh`：PASS。FileCheck 覆盖两输入 `and`、单输入 `xor`、`not` 上移到分叉侧、两层 `not` 固定点、保持 mux、带名字的 `add`、自环不动、初值无解不动、直连寄存器链不动。C++ 模型 64 拍与手写 `q' = a & b; out = q ^ a` 一致。
- `state_retime_smoke.sh`：PASS。`check_state_retime_models.py`：613 拍 checksum 与改前一致。
- `make smoke`：examples 与 sims 均通过。语义回归里 `xz_value_model_smoke` 只有寄存器、没有 comb，融合唤醒仍引用 `_pyc_comb_dirty`。这在上移之前的 IR 里也是这样。发射器在没有 comb 时补了一个局部 `DirtyBitset<1>`，该例才编得过。

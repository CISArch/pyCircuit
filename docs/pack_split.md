# pack 拆分：cycle-combine-base 与 pack 分支

> **本文件所在分支是 `ldz/feat/pack`**：它在 `ldz/feat/cycle-combine-base` 之上通过 revert 拆除提交
> `093d7e4c` 把 IR 级 reg pack（`--state-pack-width` 默认 1024、`PackStateLanesPass`、
> `PackI1RegsPass`）加回，代码与 `zxy/feat/cycle-combine@e4c5e82f` 逐文件等价。下面「本分支拆掉了什么」
> 指的是 `ldz/feat/cycle-combine-base` 相对它做的拆除，在本分支已被还原。

## 背景

`zxy/feat/cycle-combine` 同时包含两类减少 C++ 模型状态对象数量的手段：

1. **delay-line 与 bank**（本分支保留）：`pyc.delay_line` 周期状态优化（等价合并、retiming、
   直连链/共享），以及 C++ 发射层的 `SeqBank` / `DelayBank` / `VecBank`（`--packed-bank`
   的 `PackedRegBank` 也属 bank 实现，默认关）。它们按 lane 轮询、per-lane 脏位图唤醒，
   **不合并 IR 状态**。
2. **IR 级 reg pack**（已拆出）：`PackStateLanesPass`（`--state-pack-width`）把多个 reg /
   delay-line 拼成宽寄存器，`PackI1RegsPass` 把相邻 i1 reg 拼成宽 reg。拼出的宽寄存器任一
   小 lane 变化都会唤醒全部 extract 下游，丢失 per-lane 跳过。

## 分支关系

```text
zxy/feat/cycle-combine@e4c5e82f   （未改动，PR #8）
└─ ldz/feat/cycle-combine-base    本分支：去掉 reg pack，只留 delay-line + bank
   └─ ldz/feat/pack               把 pack 作为附加功能加回（revert 本分支的拆除提交）
```

`ldz/feat/pack` 的代码与 `zxy/feat/cycle-combine@e4c5e82f` 逐文件等价，只是历史上多出
“先拆除再加回”两个提交，使 pack 成为叠在 base 上的独立功能。

## 本分支拆掉了什么

- 删除 `PackStateLanesPass.cpp`、`PackI1RegsPass.cpp` 及其在 `CMakeLists.txt`、`Passes.h`、
  `pyc-opt.cpp` 的注册；`StateOptimizePass` 不再调用 `runPackStateLanes`，
  `StateOptimizeTunables` 随之移除（`createStateOptimizePass()` 无参）。
- 删除 `pycc --state-pack-width`，删除 `PackI1RegsPass` 在管线中的无条件调用；编译统计里
  的 `state_opt_pack_*` / `pack_width` / `pack_groups` 字段一并删除。
- 测试：删除 `state_pack_probe*`，`state_optimization_stage15_stage2.mlir` 去掉 PACK/CAP
  门禁后改名 `state_optimization_stage15.mlir`；相关 smoke 脚本去掉 pack 用例与旗标。
- 文档：`docs/delay_line.md` 第 9 章改为拆出说明，`docs/MLIR_PASS_PIPELINE.md` 去掉
  `pyc-pack-i1-regs` 行并重排序号。

## 刻意保留的

- `pyc.state_pack_lsb` 的通用 state-slice 解析（`StateOptimization.cpp`、`pycc.cpp` 的
  probe 分类）与 `CppEmitter` 的 slice probe 注册：不依赖 pack pass，保留供显式 slice 使用；
  不产生该属性时是死分支，不改变行为。
- `SLPPackWiresPass`（组合逻辑 wire 的 SLP 向量化，不是寄存器打包）。
- `PackedRegBank` 与 `--packed-bank`（bank 的存储布局选项，仍逐 lane 唤醒）。

## 验证

- 以 DavinciTop `v5_superscalar_v5_core` 生成 C++：本分支与旧基线 `--state-pack-width=0
  --pack-i1-regs` 关闭的配置逐文件一致（`diff -r`，仅 stats json 的 pack 字段不同）。
- `make tools && make install && make smoke`、`state_delay_optimization_smoke.sh`、
  `delay_line_diagnostics_smoke.sh`、`comb_dirty_scheduler_smoke.sh` 通过。
- 性能：见 `docs/no_reg_pack_bank_plan.md`（本分支预期约 3004.7 cycles/s，相对含 pack 的
  3145.3 慢约 4.5%；auto_perf 提测结果见提交说明/仓库根文档）。

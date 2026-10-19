# State loop（同时钟域状态的统一更新循环）

同一时钟域的 `pyc.reg` 与标量 `pyc.delay_line`，不再在生成的 C++ 里逐对象调用
`tick_compute` / `tick_commit`，而是各自归入一个 loop，由一个生成的循环统一更新。
值**不在 IR 中合并**，`q` 仍是 model 结构体里的 `Wire<W>`，comb 读取、probe、trace、
VCD 路径都不需要适配。

## 组成

- `pyc-state-loop-partition`（`StateLoopPartitionPass.cpp`）：分析 pass，每个等价时钟域一个
  `pyc.loop_id`（clk alias 归一），并给函数写 `pyc.stats.loop_groups` / `loop_lanes`。
- `runtime/cpp/pyc_state_loop.hpp`：`RegLoop<W>`、`DelayLoop<W>`。语义与逐对象 primitive 严格一致：
  `compute_rise / compute_generic / negedge / commit`；`commit()` 返回逐 lane 脏位图
  （`DelayLoop` 返回 tail 与 advanced 两张），change-driven 唤醒精度不变。
- `CppEmitter.cpp`：按 `(loop_id, width[, depth])` 拆成单一模板宽度的 loop 成员；探针写意图
  走 `lane_pending/lane_qnext`，delay tap 探针走 `DelayLoop::TapView`。
- `pycc --state-loop`（默认开）；`--state-loop=false` 回退逐对象展开。

## 相对 e4c5e82f 的取舍

- 取代 SeqBank / DelayBank：重命名为 RegLoop / DelayLoop，两份头文件合并为一份。
- 不带 VecBank：e4c5e82f 中 emitter 从不生成它（只有头文件和测试），属死代码，已删除。
- 不带 PackedRegBank / `--packed-bank`：默认关闭、实测更慢，已删除。
- 删除冗余的 `--no-seq-bank`，只留一个布尔 `--state-loop`。
- 逐对象与 loop 两种路径的 C++ 对拍：`check_state_loop_models.py`；runtime 等价与逐 lane 唤醒
  位图对拍：`tests/runtime/test_state_loop.cpp`。

## 已知性能含义

此前实测（cycle-combine-base）有 loop 但无 reg pack 时，比带 pack 的基线慢约 5%，推断来自
循环遍历的 lane 过多。L2 不强求补回，由下一层 reg pack 处理。

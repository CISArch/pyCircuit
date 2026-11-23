# 顶层实例级并行（可选）

`--cpp-parallel-instances=N`，**默认 0**（串行，生成码与基线发射器逐字节相同）；N≥2 时按拓扑检查过的依赖边给 eval 分层，把互不依赖的同层 sibling 实例的 eval 与 tick_compute/tick_commit 分叉到常驻池。
- 唤醒：instance helper 的 comb-dirty fanout 延迟写入 per-instance 字缓冲，由分叉线程 join 后合并（无需原子）。
- 活性第一：每轮 fork 在自己的调用栈上拥有 Job（tasks/next/done），worker 只认领手里 Job 的任务，`done == tasks` 即终结；退役前清 `job_` 并等 `inside_ == 0`，worker 复核指针后退出。
- 退化：亲和掩码 <2 CPU、`PYC_PARALLEL_DISABLE=1`、或交接连续过慢 ⇒ 直接串行。
- 测试：`tests/runtime/run_parallel_pool.sh`。
- `--cpp-parallel-fuse-tick`（需 N≥2）：把一次边沿的两次 fork 合成一次（每个实例先算后提交，再跑两段本地序列）；`commit()` 因此变空壳，但 `transfer()` 仍走完整 `tick_commit()`。

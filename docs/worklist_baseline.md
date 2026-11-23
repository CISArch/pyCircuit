# settle fast-path（`--cpp-eval-fast-exit`，默认 on）

`eval()` 的派发是「逐 comb `dirty.test` + 跨 TU `eval_comb_N()` 调用」，一次 eval 的固定成本与脏 comb 数无关，所以先砍「整次 eval」。
打开时先查 `_pyc_comb_dirty.empty()`：为空则只跑拓扑序的**无条件子序列**（polled-boundary comb、delay-tap 转发叶子、输出端口刷新），仍未置脏即返回，否则落回完整 walk。

子序列重跑幂等（脏位已消费、输入快照相等、赋值等值），因此逐拍等价、不需要为 polled comb 引入新状态。
只对纯 comb 函数生效：含 Instance/Fifo/AsyncFifo/ByteMem/SyncMemNM/CdcSync/Assert 的函数生成码不变（这些原语每 pass 要轮询输入/刷新 cache）。

开关关闭时生成码与基线逐字节一致。

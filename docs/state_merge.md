# 等价状态合并（state merge）

`pyc-state-optimize` 在 retime 之前运行两轮 `runDelayChainMergeRound`，中间夹一次
canonicalize/CSE：

1. 把 `(q 类型, clk, rst, en, next, init)` 语义等价的 `pyc.reg` 合并为同一状态，保留第一个，
   其余的观测身份（`pyc.name` 等）经 `remapStateOpIdentity` 重映射到幸存者的 `q`，
   幸存者标注 `pyc.optimized_by = "merge_equivalent_state"`。
2. 第一轮合并后，下游寄存器的 `next` 锥会因输入被统一而变得相同；CSE 后第二轮可级联合并。

等价判定与哈希在 `StateOptimization.{h,cpp}`（`equivalentRegisterState` / `registerStateHash`），
与 `equivalentDelayLineState` 共用 `equivalentStateValue` / `semanticValueHash`。

门禁：`compiler/mlir/test/state_merge_smoke.sh`（FileCheck：等价合并、级联合并、
不同 en/init/next 不合并、被合并寄存器的名字仍可观测）。

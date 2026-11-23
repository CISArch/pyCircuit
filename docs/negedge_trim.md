# 下降沿 trim（`--cpp-negedge-trim`，默认 on）

下降沿不 sample 任何状态：fall 分支只重算 delay-tap（值在上一上升沿已提交、重算恒等）并递归子模块，而子模块的 fall 分支同样什么都不采。
默认打开时生成：`tick_negedge()`（落下本模块边沿锁存器、递归子模块并重开其 tick 门、只对存储原语调各自的 `tick_compute()` 以落下它们的 `clkPrev`）+ `tick_compute()` 开头的 `!_pyc_seq_armed && _pyc_clk_prev && !clk` 判定（命中则调 `tick_negedge()` 后返回）。

只在 IR 可证「整个实例子树由同一时钟驱动」时生效：`subtreeIsSingleClock()` 要求每个时序原语的时钟操作数 trace 到本模块寄存器时钟，实例中凡送进 callee 时钟操作数的实参用 `argumentFeedsClock()` 判定并递归验证；证明不了就退化为串行代码（不报错）。子树里若有模块自身没有单时钟边沿锁存、只能走 generic `compute_generic(clk)` 路径（例如状态全是 loopified delay-line、没有 register 的模块），它的 `clkPrev` 要在落沿被落下，该子树同样保持串行代码。

`--cpp-negedge-trim=off` 的生成码与未加本特性的发射器逐字节一致。

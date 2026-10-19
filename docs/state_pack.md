# State-lane packing

`pyc-pack-state-lanes`（`PackStateLanesPass.cpp`）把同控制信号（clk/rst/en 等价，delay-line 另需同
depth）的整型 `pyc.reg` / `pyc.delay_line` 打包成一个更宽的状态 op，各 lane 的 `q` 用带
`pyc.state_pack_lsb` 的 `pyc.extract` 取回，被删状态的 name/debug/probe/trace 身份挂到 extract
上的只读 alias。作为 `pyc-state-optimize` 的最后一步运行（仅 C++ 路径）。

- `--state-pack-width=N`：最大打包宽度，默认 1024；`0` 关闭（不再有"0=无上限"含义）。
- 带 `pyc.delay_tap` 的 delay-line 不参与打包；会让 lane 值在插入点之前被使用的组也会被拆开。
- 探针：打包后的 lane 走 `addRegSlice` / `addRegLazySlice`（storage 宽度 + lsb），与 state loop
  的 lane 绑定兼容。
- 门禁：`state_pack_smoke.sh`（FileCheck、打包探针 runtime、packed==flat 对拍）。

## 相对 e4c5e82f 的取舍

- 删除全部 `pyc.stats.state_opt_pack_*` 计数器与 `pyc.source_reg_count` / `shared_chain_count`
  传播（后者属于 merge 层，见 L4）。
- 不带 `--packed-bank`（已在 L2 删除）。

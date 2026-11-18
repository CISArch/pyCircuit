# BoomCore（golden firtool 网表）— 原始代码测试用例与多线程仿真吞吐报告

日期: 2026-11-17 ｜ 机器: 32 逻辑核 ｜ DUT: `designs/Boom-pyc/generated-verilog/BoomTrimHarness.v`（firtool 黄金网表，保留 RTL 信号名）
仿真器: Verilator `--binary --timing`（`/tmp/boom_sim/obj_boom/sim_boom`，tb: `tb_boom_gold.v`）

## 0. 背景与路线选择

- BOOM（RV64IM OoO 核）与 DavinciBaseLine 的 34 条 PTO trace（自定义 PE 语义）ISA 不匹配，**不能**走 v5/Rocket 的 trace 回放路线（见 `docs/RocketCore/report.md`）。
- pycc 生成的 `BoomTrimHarness_fix.v` 存在功能缺陷（顶层 `arvalid` 恒 0，I$ 永不发起取指 refill），**不可用作测试载体**；本报告全部结果基于 firtool 黄金网表。
- 判定协议：BOOM D$ 为 **writeback 型**（store 不落 AXI W 通道），无法沿用 Rocket 的 MMIO-store 观测判定，改用 **PC 死循环协议**——`s0_vpc` 连续 64 拍稳定于 `spin`（PASS）或落 `fail` 循环体（FAIL），标签地址由 `nm` 提取存 `tests/labels.json`。

## 1. 测试用例（依据原始代码改编）

程序源自原始测试套件（`designs/Rocket-pyc/tests/asm` + `mini_sd/mini_z32`），经 `build_tests2.py::boomify()` 做三类 BOOM 适配：

1. **地址搬移**：裸地址 `0x80/0x88/0x100/0x200` → SimAXIMem DRAM（`0x80010000/0x80010008/0x80008000/0x80008020`），否则 PMA 违例 trap 至 PC=0；
2. **fail 路径独立死循环**：`fail` 段 `j spin` → `j fail`（含 rvui_arith 的 PASS/FAIL 汇合型尾部拆解），使 PC 可区分 spin/fail；
3. **RV64 语义期望修正**：`lw` 必须符号扩展（`0x88776655` 经 `lw` = `0xFFFFFFFF88776655`），原套件按 32 位心智模型写的期望值已在 `mini_nop/mini_lb/rvui_arith` 中修正（核行为正确，见 §3）。

### 功能判定矩阵（+cycles=80000）

| 程序 | 覆盖 | 周期 (tick) | 判定 | spin PC |
|---|---|--:|:--:|--:|
| probe_rf | rf 读写 / x0 / 基址+偏移 | 208 | **PASS** | 0x80000034 |
| mini_dbg | sw→lhu→sw 观测链 | 244 | **PASS** | 0x80000054 |
| mini_h | lhu/lh 半字矩阵（零扩/符号扩） | 263 | **PASS** | 0x80000068 |
| mini_lb | sw 后背靠背 lbu/lhu/lw | 262 | **PASS** | 0x80000064 |
| mini_nop | 子字 load 全矩阵（nop 隔离） | 287 | **PASS** | 0x80000098 |
| mini_z32 | 64 位全宽 sd/ld + 高 32 位语义 | 289 | **PASS** | 0x800000a8 |
| mini_sd | sd/ld + sb/sh/sw 混合覆盖 | 323 | **PASS** | 0x800000cc |
| rvui_arith | 逻辑/移位/乘除/jal-jalr/lw-sw/溢出 | 504 | **PASS** | 0x80000164 |
| mt_bench | 伪双线程轮转负载 + 校验和 | 603 | **PASS** | 0x80000098 (done) |
| bootrom_win | Rocket bootrom CSR 序列 | — | 不适用 | — |

**9/10 PASS**。`bootrom_win` 依赖 Rocket 专属 CustomCSR（`csrwi 0x7c1` 关 chicken bits），BOOM 裁剪网表无该 CSR，属设计性不兼容而非功能错误（现象：入口即停滞，ar=1）。

## 2. 过程中发现的问题（根因均已定位）

| 现象 | 根因 | 结论 |
|---|---|---|
| 所有程序 trap 至 PC=0 | boomify 缺地址搬移（`li x27,0x80` 未改写，store 触发 PMA 违例） | 构建脚本 bug，已修复 |
| mt_bench/rvui_arith 仍 trap | `li` 行尾注释使 `0x80$` 正则不匹配；`li x26,0x200` 无搬移规则 | 构建脚本 bug，已修复 |
| mini_nop/mini_lb/rvui_arith 走 fail 分支 | **RV64 `lw` 符号扩展**：核返回 `0xFFFFFFFF88776655`，测试期望零扩展 | **核正确，测试期望错误**，已修正；二分矩阵（正数 PASS / 位31=1 FAIL / `sd+ld` PASS / 加 nop 不变）完整收敛于该语义 |
| pycc 版 `BoomTrimHarness_fix.v` arvalid=0 | pycc Verilog 发射缺陷 | 黄金网表替代，缺陷单列上报 |

## 3. 多线程仿真吞吐（宿主侧进程级并行）

协议镜像 `bench_rocket_mt.py`：10 程序 × 10 轮 = 100 任务，每任务固定 **200,000 周期窗口**（`+stable` 禁用提前退出 → 每任务确定性仿真完整窗口），总负载 20M 周期/线程档；ThreadPoolExecutor 派发独立 sim 进程。脚本：`/tmp/boom_sim/bench_boom_mt.py`。

| 线程 | 墙钟 (s) | 汇总吞吐 (cycles/s) | 每核 (c/s) | 加速比 |
|--:|--:|--:|--:|--:|
| 1 | 412.62 | 48,471 | 48,471 | 1.00x |
| 2 | 214.29 | 93,331 | 46,665 | 1.93x |
| 4 | 105.09 | 190,304 | 47,576 | 3.93x |
| 8 | 54.48 | 367,114 | 45,889 | **7.57x** |
| 16 | 34.59 | 578,132 | 36,133 | 11.93x |

### 分析

- **≤8 线程近线性扩展**（每核衰减 ≤5.3%）：Verilator 单线程模型 + 每进程独立内存镜像，线程间几乎无共享争用，BOOM 网表规模（OoO 前端+分支预测+写回 D$）下仿真器本身是纯计算密集型。
- **8→16 出现饱和拐点**：每核吞吐降至 36.1k c/s（−25%），典型共享 LLC/内存带宽墙；32 逻辑核（推测 16 物理核 + SMT）下继续加线程收益递减。
- 对照 Rocket（v5 trace 回放，pyc C++ runner 单核 ~12k c/s、Verilator ~4.5k c/s）：BOOM 黄金网表 Verilator 单进程 **~48.5k c/s**——网表虽大（全 OoO 微结构），但周期窗口判定协议下无 trace 同步开销，绝对吞吐反而更高。
- 多线程下的功能一致性：100 任务全窗口 VERDICT 均正常（spin 循环 PC 稳定、无 trap 回 0），并发对功能无影响。

## 4. 结论

1. 基于原始代码改编的 10 个测试中 **9 个在 BOOM 黄金网表上功能 PASS**（含 M 扩展、子字/全宽访存、jal/jalr、伪双线程负载），1 个因 Rocket 专属 CSR 不适用；
2. 此前疑似「子字 load 缺陷」经二分定位为 **RV64 `lw` 符号扩展的正确核行为 vs 错误测试期望**，核功能无缺陷；
3. 多线程仿真吞吐在 8 线程内近线性（7.57x，367k c/s），16 线程 11.93x 进入带宽饱和区；
4. pycc Verilog 发射缺陷（`arvalid` 恒 0）阻断了对 pycc 产物的等价测试，建议优先修复后重跑本套件做 golden vs pycc 对比。

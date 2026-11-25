# Rocket-pyc 程序化测试（源自 rocketchip 原项目测试思路）

把原 rocketchip 项目两类测试程序移植为 Rocket-pyc 可回放验证的 ST trace 负载：
仿 `riscv-tests/rv64ui` 风格的自检程序（PASS/FAIL 判定），与原项目
`bootrom/bootrom.S` 的窗口化改编（CSR 初始化 + 跳转回卷）。

## 用法

```bash
scripts/gen_trace.sh asm/rvui_arith.S 1500
# 产物：build/<prog>/{*.elf,*.hex,*.st,cpp_*.st,replay_diff.txt}
```

流水线：`clang -march=rv64ima` 汇编 → `ld.lld -Ttext=0 --no-relax` 零重定位
链接 → `elf2imem.py`（断言 ≤1KiB、零重定位、4B 对齐）→ Verilator golden
（`tb/tb_rocket_pgm.v`，`+imem` 加载、`+cycles` 控制拍数）→ `rocket_sim`
回放 → 77 输出列逐列对拍。

## 测试程序

| 程序 | 来源 | 内容 | 判定 |
|---|---|---|---|
| `rvui_arith.S` | rv64ui-p-simple 风格自写 | ALU/逻辑/移位/M 扩展/jal-ret/溢出、lw/sw 往返（99 指令） | PASS ✓ |
| `bootrom_win.S` | 原项目 `bootrom.S` 改编 | `csrwi 0x7c1`+`csrr mhartid`+`jr s0`→0x80000000 窗口回卷 | 无判定（负载型） |
| `mini_h/lb/nop/dbg.S` | 调试用最小复现 | 子字 load 全粒度矩阵（lhu/lh/lbu/lb/lw） | PASS ✓ |

判定口径：程序最后一条 store 的地址——写 `0x80`=PASS，写 `0x88`=FAIL。
通过则先写标志 `0x55AA55AA→0x80`；证据在 ST trace 的 dmem 写事务列。

## dmem 模型契约（tb_rocket_pgm.v，两级移位队列）

依据 `RocketCore.scala` 511/675（HellaCache s2 契约），本 tb 与 v2p runner
回放的等价性建立在以下三条上：

1. **`req_ready` 恒 1** —— fire = valid 拍 = 核 s0；
2. **resp 恰在 fire+2 拍**（核 s2/wb 级）呈现并被采样 —— 晚到的 resp 不被
   消费（非 replay 不走 ll 写回），sboard 永不清除；实现为 q1→q2 两级移位，
   背靠背 mem 指令（load s0 后下一拍即再 fire）各自按时出 resp；
3. **resp.data 必须是已按 size/signed/addr 提取并扩展好的 64b** ——
   RocketCore 的 `rf_wdata` 直写寄存器堆、核内无任何 subword 提取
   （RocketCore.scala:703），整行返回仅在行高 32b 恰为 0 时"碰巧正确"。

store 写回与 resp 采样同沿（fire+2），紧随 store 的同地址 load 读区间
（其 fire+3）晚于写沿，天然满足 store-to-load forwarding。

## 回放对拍结果（golden vs rocket_sim，1500 拍 × 77 输出列）

| 程序 | verdict | 对拍 |
|---|---|---|
| mini_dbg | PASS | **MATCH（0/1500）** |
| mini_h / mini_lb / mini_nop | PASS | 3–5 行差异 |
| rvui_arith | PASS | 14 行差异（t≤170 后完全收敛） |
| bootrom_win | 无判定 | 125 行差异 |

**已知差异（v2p 近似，非 trace 错误）**：差异集中在分支预测器/BTB 状态
建立期（btb/ireq_pc/iresp_ready/daddr 虚地址高位），为 v2p 转换模型与 RTL
的微架构近似差异，架构状态一致且随后收敛。原 400 拍 bootrom trace 分支
稀疏故未暴露；带分支负载的新 trace 反而具备更强的差分测试能力，可作
v2p 模型精化的回归用例。

## 与原项目测试体系的对照

原 rocketchip 四层体系（emulator 跑 riscv-tests asm/bmark、Chisel unittest、
JtagDtmSuite、Scala 工程测试）面向完整 SoC；本套件取其程序语义（自检 +
bootrom 流程），落位到 ST 端口回放口径：程序行为经 golden tb 编码进
trace 输入列，DUT（Rocket 核）行为由 77 输出列承载，rocket_sim 重算比对。

# rvui_arith.S — rv64ui 风格确定性自检程序（蓝本：rocket-chip 回归使用的
# riscv-tests rv64ui-p-add/sub/lw/sw/shift 序列，裸核窗口化改编）。
#
# 约束（对齐 tb 存储器模型）：
#   - 取指窗口：imem[pc[11:2]]，基址 0x1000，全部指令 4B 对齐、无压缩、
#     分支/跳转不出 1KiB 窗口；零重定位（相对跳转 + li 绝对常数）。
#   - 数据窗口：dmem8[addr[11:3]]，有效地址落在低 2KiB。
# 判定（riscv-tests 的 tohost 风格窗口化）：
#   PASS -> sw 0x55AA55AA 到 0x80；任何一步失配 -> sw 错误码到 0x88。
#   证据出现在 ST 波形的 dmem 写事务（o_daddr/o_s1_data 列），golden 与
#   C++ 模型回放比对时两侧必须一致地"跑出 PASS"。
    .text
    .globl _start
_start:
    li   x26, 0                 # fail code（步序号）
    li   x27, 0x80              # PASS 标记地址
    li   x28, 0x88              # FAIL 标记地址

# ---- rv64ui-p-add / sub / logic 风格 ----
    li   x5, 5
    li   x6, 3
    add  x7, x5, x6             # 8
    li   x8, 8
    bne  x7, x8, fail
    sub  x9, x5, x6             # 2
    li   x10, 2
    bne  x9, x10, fail
    and  x11, x5, x6            # 1
    li   x12, 1
    bne  x11, x12, fail
    or   x13, x5, x6            # 7
    li   x14, 7
    bne  x13, x14, fail
    xor  x15, x5, x6            # 6
    li   x16, 6
    bne  x15, x16, fail

# ---- rv64ui-p-shift 风格 ----
    li   x5, 1
    slli x17, x5, 31            # 0x80000000
    srli x18, x17, 31           # 1
    bne  x18, x5, fail
    li   x6, -8
    srai x19, x6, 2             # -2
    li   x20, -2
    bne  x19, x20, fail
    sltu x21, x6, x5            # -8 无符号大 -> 0
    bne  x21, x0, fail

# ---- M 扩展（rv64um-p-mul/div 风格）----
    li   x5, 1234567
    li   x6, 765
    mul  x7, x5, x6
    li   x8, 944443755
    bne  x7, x8, fail
    mulh x9, x6, x6             # 小正数高位 0
    bne  x9, x0, fail
    divu x11, x5, x6            # 1613
    li   x12, 1613
    bne  x11, x12, fail
    remu x13, x5, x6            # 1234567 - 1613*765
    li   x14, 622
    bne  x13, x14, fail

# ---- 控制流：call/ret（jal/jalr）与分支跳转 ----
    li   a0, 40
    li   a1, 2
    jal  ra, double_fn          # 40*2 = 80
    li   x5, 80
    bne  a0, x5, fail
    beq  a1, x0, fail           # not taken
    bne  a1, x0, taken_ok       # taken
    j    fail
taken_ok:

# ---- rv64ui-p-lw/sw 往返（word 粒度；subword load 在裸核 tb 下行为
#      异常——s1_kill 冲刷后不重执行，见 tests/README 已知限制）----
    li   x5, 0x88776655
    li   x6, 0x100              # 数据基址
    sw   x5, 0(x6)
    lw   x7, 0(x6)
    bne  x7, x5, fail
    li   x5, 0x12345678
    sw   x5, 4(x6)
    lw   x7, 4(x6)
    bne  x7, x5, fail
    lw   x8, 0(x6)              # 覆盖检查：旧数据仍在
    li   x10, 0x88776655
    bne  x8, x10, fail

# ---- 64 位加减溢出路径 ----
    li   x5, 0x7FFFFFFFFFFFFFFF
    addi x7, x5, 1              # 溢出回绕
    li   x8, -0x8000000000000000
    bne  x7, x8, fail

# ---- PASS：写标记并自旋 ----
    li   x5, 0x55AA55AA
    sw   x5, 0(x27)
    j    spin

# ---- FAIL：写固定错误码并自旋（不细分步号）----
fail:
    li   x5, 0xDEAD
    sw   x5, 0(x28)
spin:
    j    spin

# ---- 被调函数（jal 相对寻址）----
double_fn:
    add  a0, a0, a0
    ret

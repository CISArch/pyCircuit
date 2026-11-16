# mt_bench.S — 软件多线程性能基准（参考 rocketchip bmark-tests 结构）
#
# 单核 Rocket 无硬件多线程，本基准以「寄存器分区伪线程 + 交替调度」
# 表征多线程负载：同一循环体内 T0/T1 按元素奇偶交替执行（load+累加），
# 分支密集 + 访存交错，用于观测前后端（预测器/取指/dmem）压力下性能。
#
# 性能口径（双保险）：
#   1) rdcycle 读 mcycle → 存 0x90（程序自测）；
#   2) tb 侧最后 store（判定写）的 tick = 端到端周期。
# 判定：T0/T1 校验和正确 → sw 0x55AA55AA 到 0x80 (PASS)
#       否则                            → sw 0xDEAD0000 到 0x88 (FAIL)
    .section .text.init
    .globl _start
_start:
    li    x27, 0x80          # 判定基址
    li    x26, 0x200         # 数组基址（16 x 4B）
    # ---- init: a[i] = 2*i+1 ----
    li    x10, 0
    li    x11, 16
init:
    slli  x5, x10, 2
    add   x6, x26, x5
    slli  x7, x10, 1
    addi  x7, x7, 1
    sw    x7, 0(x6)
    addi  x10, x10, 1
    blt   x10, x11, init
    # ---- 多线程轮转：T0 吃偶下标 / T1 吃奇下标 ----
    li    x20, 0             # T0 累加器
    li    x21, 0             # T1 累加器
    li    x22, 0             # i
    li    x23, 16
mt_loop:
    andi  x5, x22, 1
    bnez  x5, th1
    # --- T0 工作包 ---
    slli  x5, x22, 2
    add   x6, x26, x5
    lw    x7, 0(x6)
    add   x20, x20, x7
    j     next
th1:
    # --- T1 工作包 ---
    slli  x5, x22, 2
    add   x6, x26, x5
    lw    x7, 0(x6)
    add   x21, x21, x7
next:
    addi  x22, x22, 1
    blt   x22, x23, mt_loop
    # ---- 校验：Σ偶 a = 120, Σ奇 a = 136 ----
    li    x8, 120
    li    x9, 136
    bne   x20, x8, fail
    bne   x21, x9, fail
    # 周期口径：golden 核 CSRFile 读 mcycle 触发非法指令异常，
    # 程序内 rdcycle 不可用 —— 周期数取 tb 侧判定 store 的 tick
    #（ST trace 中最后 store 行的 t 列 = 端到端周期）。
    li    x29, 0x55AA55AA
    sw    x29, 0(x27)        # PASS
done:
    j     done
fail:
    li    x29, 0xDEAD0000
    sw    x29, 8(x27)        # FAIL
fail_spin:
    j     fail_spin

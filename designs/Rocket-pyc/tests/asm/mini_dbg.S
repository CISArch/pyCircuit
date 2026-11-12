# mini_dbg.S — 观测核内 load 结果：lhu 后立即 sw 出来对照
    .text
    .globl _start
_start:
    li   x27, 0x80
    li   x28, 0x88
    li   x5, 0x88776655
    li   x6, 0x100
    sw   x5, 0(x6)
    lhu  x7, 0(x6)          # 期望 0x6655
    sw   x7, 8(x6)          # 写出 x7 供 ST 观测
    lhu  x11, 8(x6)         # 读回
    bne  x11, x7, fail      # 自洽：同一值应相等
    li   x8, 0x6655
    bne  x7, x8, fail       # 对照期望
    li   x5, 0x55AA55AA
    sw   x5, 0(x27)
spin:
    j    spin
fail:
    li   x5, 0xDEAD
    sw   x5, 0(x28)
    j    spin

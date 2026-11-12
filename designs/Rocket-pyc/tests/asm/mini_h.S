# mini_h.S — 半字 load 矩阵：lhu0/lhu2/lh0/lh2 逐一隔离
    .text
    .globl _start
_start:
    li   x27, 0x80
    li   x28, 0x88
    li   x5, 0x88776655
    li   x6, 0x100
    sw   x5, 0(x6)
    lhu  x7, 2(x6)          # 0x8877（shift16）
    li   x8, 0x8877
    bne  x7, x8, fail
    lhu  x7, 0(x6)          # 0x6655（shift0）
    li   x8, 0x6655
    bne  x7, x8, fail
    lh   x7, 2(x6)          # 0x8877 sext = 负数
    li   x8, -30601         # 0xFFFF8877（0x8877-0x10000）
    bne  x7, x8, fail
    li   x5, 0x55AA55AA
    sw   x5, 0(x27)
spin:
    j    spin
fail:
    li   x5, 0xDEAD
    sw   x5, 0(x28)
    j    spin

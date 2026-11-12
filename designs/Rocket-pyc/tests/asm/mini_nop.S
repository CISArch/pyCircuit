# mini_nop.S — 隔离「store 后紧邻 load」问题：插入 nop 缓冲
    .text
    .globl _start
_start:
    li   x27, 0x80
    li   x28, 0x88
    li   x5, 0x88776655
    li   x6, 0x100
    sw   x5, 0(x6)
    nop
    nop
    lhu  x7, 0(x6)          # 0x6655
    li   x8, 0x6655
    bne  x7, x8, fail
    lhu  x7, 2(x6)          # 0x8877
    nop
    li   x8, 0x8877
    bne  x7, x8, fail
    lbu  x7, 0(x6)          # 0x55
    nop
    li   x8, 0x55
    bne  x7, x8, fail
    lb   x7, 3(x6)          # -120
    nop
    li   x8, -120
    bne  x7, x8, fail
    lw   x7, 0(x6)          # 0x88776655
    nop
    li   x8, 0x88776655
    bne  x7, x8, fail
    li   x5, 0x55AA55AA
    sw   x5, 0(x27)
spin:
    j    spin
fail:
    li   x5, 0xDEAD
    sw   x5, 0(x28)
    j    spin

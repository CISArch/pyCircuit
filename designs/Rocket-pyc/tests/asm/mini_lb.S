# mini_lb.S — 最小复现：sw 后背靠背 lbu / lhu 是否读回正确子字
    .text
    .globl _start
_start:
    li   x27, 0x80
    li   x28, 0x88
    li   x5, 0x88776655
    li   x6, 0x100
    sw   x5, 0(x6)
    lbu  x7, 0(x6)          # 背靠背 subword load（不经 lw）
    li   x8, 0x55
    bne  x7, x8, fail
    lhu  x7, 2(x6)          # 0x8877
    li   x8, 0x8877
    bne  x7, x8, fail
    lw   x7, 0(x6)          # 0x88776655
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

# probe_rf.S — 隔离 rf 写后读 / x0 / 基址+偏移
    .text
    .globl _start
_start:
    li   x6, 0x100
    li   x5, 0xAABBCCDD
    sw   x5, 0(x6)        # 期望 store addr=0x100 data=0xAABBCCDD
    lw   x7, 0(x6)        # 读回
    sw   x7, 4(x6)        # 期望 addr=0x104 data=0xAABBCCDD（验证 rf 写后读）
    sw   x0, 8(x6)        # 期望 addr=0x108 data=0（x0 硬连 0）
    addi x8, x0, 0x77
    addi x8, x8, 1        # x8 = 0x78
    sw   x8, 12(x6)       # 期望 addr=0x10C data=0x78（rf 常规读写）
spin:
    j    spin

# bootrom_win.S — 原项目 rocket-chip-v16/bootrom/bootrom.S 的取指窗口化改编。
# 指令序列原样保留（csrwi 0x7c1 关 chicken bits、csrr mhartid、设 a1=_dtb、
# jr s0 跳 DRAM_BASE）；改动仅两点：
#   1) 单 .text、4KiB 窗口内自包含（无 linker script / 无重定位）；
#   2) jr 0x80000000 后 pc[11:2] 回卷到 imem[0]，形成"每轮重跑 bootrom"
#      的真实循环：持续驱动 CSRFile 写路径（o_csr_value 输出列可见）、
#      mhartid 读、auipc 相对取址与前端 redirect。
    .text
    .globl _start
_start:
    csrwi 0x7c1, 0              # disable chicken bits（customCSR 写路径）
    li   s0, 0x80000000         # DRAM_BASE
    csrr a0, mhartid            # hartid 读
    auipc a1, 0                 # a1 = 此处地址
    addi a1, a1, 12             # -> dtb 字符串
    jr   s0                     # redirect -> 窗口回卷 imem[0]，循环
    .ascii "DTB goes here"      # 原项目 rodata 原样保留（不被执行）
    .byte 0

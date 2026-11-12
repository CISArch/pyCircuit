#!/usr/bin/env python3
"""elf2imem.py — 汇编 .o（clang riscv64）→ tb_rocket_pgm.v 的 imem hex。

最小 ELF64 小端解析：抽取按地址排序的分配段（SHT_PROGBITS + SHF_ALLOC），
拼进 1KiB（256 × 32b）取指窗口，未用槽填 jal x0,0（0x0000006f）。
硬性校验（窗口契约）：
  1) .text 总长 ≤ 1KiB；
  2) .text 段地址 ≡ 0 (mod 4)；
  3) 零重定位（.rela.text 必须不存在或为空）——所有控制流须是
     相对跳转/常数地址，否则拒绝。
用法：elf2imem.py input.o output.hex
"""
import struct
import sys


def main(argv):
    if len(argv) != 3:
        sys.exit(__doc__)
    data = open(argv[1], "rb").read()

    # ELF64 header
    assert data[:4] == b"\x7fELF" and data[4] == 2 and data[5] == 1, "not ELF64 LE"
    e_shoff, = struct.unpack_from("<Q", data, 0x28)
    e_shentsize, e_shnum, e_shstrndx = struct.unpack_from("<HHH", data, 0x3A)
    shdrs = [struct.unpack_from("<IIQQQQIIQQ", data, e_shoff + i * e_shentsize)
             for i in range(e_shnum)]
    shstr_off = shdrs[e_shstrndx][4]

    def name(h):
        end = data.index(b"\0", shstr_off + h[0])
        return data[shstr_off + h[0]:end].decode()

    segs = []       # (addr, bytes, sname)
    relocs = 0
    for h in shdrs:
        nm = name(h)
        sh_type, sh_flags, sh_addr, sh_off, sh_size = h[1], h[2], h[3], h[4], h[5]
        if sh_type == 4 or "rela" in nm:            # SHT_RELA
            relocs += sh_size // 24
        if sh_type == 1 and (sh_flags & 0x2) and sh_size:  # PROGBITS+ALLOC
            segs.append((sh_addr, data[sh_off:sh_off + sh_size], nm))
    assert relocs == 0, f"{relocs} relocations: use only pc-relative jumps / li constants"
    segs.sort()
    assert all(a % 4 == 0 for a, _, _ in segs), "text must be 4-byte aligned"

    image = bytearray(1024)
    for addr, blob, nm in segs:
        assert addr + len(blob) <= 1024, f"segment {nm} exceeds 1KiB window"
        image[addr:addr + len(blob)] = blob

    with open(argv[2], "w") as f:
        for w in range(256):
            word = struct.unpack_from("<I", image, w * 4)[0]
            f.write(f"{word:08x}\n")
    used = sum(len(b) for _, b, _ in segs)
    print(f"elf2imem: {used} B / 1KiB, {len(segs)} segment(s): "
          + ", ".join(f"{nm}@0x{a:x}" for a, _, nm in segs))


if __name__ == "__main__":
    main(sys.argv)

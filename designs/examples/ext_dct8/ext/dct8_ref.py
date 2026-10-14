"""Golden reference model for ext_dct8 (manifest backends.golden).

lane_u = sum(byte[x] * (u+1)) truncated to 16 bits; out packs lanes 0..3.
"""


def dct8(ins: list[int]) -> list[int]:
    value = ins[0] & 0xFFFFFFFFFFFFFFFF
    out = 0
    for u in range(4):
        acc = sum(((value >> (8 * x)) & 0xFF) * (u + 1) for x in range(8))
        out |= (acc & 0xFFFF) << (16 * u)
    return [out]

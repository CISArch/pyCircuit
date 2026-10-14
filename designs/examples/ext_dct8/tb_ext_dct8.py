"""Testbench for the ext_dct8 external-module example (docs/external-modules.md).

Drives stimulus into the black box and checks outputs against the embedded
golden function (same formula as ext/dct8_ref.py, ext/dct8.cpp, ext/dct8.v).
"""
from __future__ import annotations

import sys
from pathlib import Path

from pycircuit import Tb, compile_cycle_aware, testbench

_THIS_DIR = Path(__file__).resolve().parent
if str(_THIS_DIR) not in sys.path:
    sys.path.insert(0, str(_THIS_DIR))

from ext_dct8 import build  # noqa: E402
from ext_dct8_config import DEFAULT_PARAMS, TB_PRESETS  # noqa: E402


def _golden(value: int) -> int:
    out = 0
    for u in range(4):
        acc = sum(((value >> (8 * x)) & 0xFF) * (u + 1) for x in range(8))
        out |= (acc & 0xFFFF) << (16 * u)
    return out


VECTORS = [
    0x0807060504030201,
    0x0000000000000000,
    0xFF00FF00FF00FF00,
    0x0123456789ABCDEF,
]


@testbench
def tb(t: Tb) -> None:
    p = TB_PRESETS["smoke"]
    t.timeout(int(p["timeout"]))

    for i, vec in enumerate(VECTORS):
        t.drive("x", vec, at=i)
        t.expect("y", _golden(vec), at=i)

    t.finish(at=int(p["finish"]))


if __name__ == "__main__":
    print(compile_cycle_aware(build, name="tb_ext_dct8_top", eager=True, **DEFAULT_PARAMS).emit_mlir())

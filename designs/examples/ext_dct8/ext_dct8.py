"""ext_dct8 example: instantiate the external black-box module declared in
ext/ext_dct8.toml. See docs/external-modules.md for the interface contract."""
from __future__ import annotations

import sys
from pathlib import Path

from pycircuit import CycleAwareCircuit, CycleAwareDomain

_THIS_DIR = Path(__file__).resolve().parent
if str(_THIS_DIR) not in sys.path:
    sys.path.insert(0, str(_THIS_DIR))


def build(m: CycleAwareCircuit, domain: CycleAwareDomain) -> None:
    from pycircuit import ext as extmod

    manifest = _THIS_DIR / "ext" / "ext_dct8.toml"
    dct = extmod.declare(m, manifest)

    x = m.input("x", width=64)
    y = dct.bind(m, name="u_dct", in_=x, valid=1)
    m.output("y", y)


build.__pycircuit_name__ = "ext_dct8_top"

if __name__ == "__main__":
    print(compile_cycle_aware(build, name="ext_dct8", eager=True).emit_mlir())

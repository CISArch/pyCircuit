"""ext_dct8: external black-box module (docs/external-modules.md)."""
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
    x = m.input("x", width=64)
    y = extmod.instance(m, manifest, name="u_dct", in_=x, valid=1)
    m.output("y", y)


build.__pycircuit_name__ = "ext_dct8_top"

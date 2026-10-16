"""ext_cache example: stateful external black-box write-back cache.

Scaled-down flavor of DavinciBaseLine's v5_l1d_cache (2 sets x 2 ways,
16-byte lines) instantiated through the ext-module interface. Exercises the
sequential half of the binding contract (tick_compute/tick_commit state, miss
FSM) plus a 128b data port — ext_dct8 only covers the combinational half.

The cache black box takes a 32b address request and returns a 128b line view;
see ext/ext_cache.toml for the full port list and ext/cache_core.hpp for the
cycle contract. See docs/external-modules.md for the interface contract.
"""
from __future__ import annotations

import sys
from pathlib import Path

from pycircuit import CycleAwareCircuit, CycleAwareDomain

_THIS_DIR = Path(__file__).resolve().parent
if str(_THIS_DIR) not in sys.path:
    sys.path.insert(0, str(_THIS_DIR))


def build(m: CycleAwareCircuit, domain: CycleAwareDomain) -> None:
    from pycircuit import ext as extmod

    manifest = _THIS_DIR / "ext" / "ext_cache.toml"
    cache = extmod.declare(m, manifest)

    cd = domain.clock_domain
    addr = m.input("addr", width=32)
    req_valid = m.input("req_valid", width=1)
    wr = m.input("wr", width=1)
    wdata = m.input("wdata", width=128)
    wmask = m.input("wmask", width=16)
    resp_ready = m.input("resp_ready", width=1)
    flush = m.input("flush", width=1)

    outs = cache(
        m,
        name="u_cache",
        clk=cd.clk,
        rst=cd.rst,
        addr=addr,
        req_valid=req_valid,
        wr=wr,
        wdata=wdata,
        wmask=wmask,
        resp_ready=resp_ready,
        flush=flush,
    )
    # Multiple outputs come back as a dict (docs/external-modules.md).
    m.output("rdata", outs["rdata"])
    m.output("hit", outs["hit"])
    m.output("resp_valid", outs["resp_valid"])
    m.output("dirty_evict", outs["dirty_evict"])


build.__pycircuit_name__ = "ext_cache_top"

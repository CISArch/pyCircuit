"""Testbench for the ext_cache external-module example (docs/external-modules.md).

Directed sequence exercising every path of the 2-set x 2-way write-back cache:
read-miss fill (2-cycle latency), read hit, write hit (dirty), write miss with
dirty eviction (LRU), flush, and re-read through the backing store.
Expectations come from an embedded pure-Python golden model (same algorithm as
ext/cache_core.hpp / ext/cache.v).

Per-cycle view (matches the generated C++ testbench): expectations are taken
AFTER the cycle's posedge commit, i.e. golden.tick(inputs) runs before
golden.eval(inputs) for the same cycle's drives.
  - a read hit drives rdata/hit in the SAME cycle as the request;
  - a read miss accepted on cycle N drives resp_valid/rdata on cycle N+2
    (hit stays 0; dirty_evict flags a write-back that cycle);
  - writes update the line at the end of the request cycle.
"""
from __future__ import annotations

import sys
from pathlib import Path

from pycircuit import CycleAwareTb, Tb, testbench

_THIS_DIR = Path(__file__).resolve().parent
if str(_THIS_DIR) not in sys.path:
    sys.path.insert(0, str(_THIS_DIR))

from ext_cache import build  # noqa: E402
from ext_cache_config import TB_PRESETS  # noqa: E402

LINE_WORDS = 4
SETS = 2
WAYS = 2
REFILL = 2
BACK_WORDS = 1 << 12


def set_of(addr: int) -> int:
    return (addr >> 2) & (SETS - 1)


def tag_of(addr: int) -> int:
    return addr >> 5


def word_of(addr: int) -> int:
    return (addr >> 2) & (LINE_WORDS - 1)


def line_base(addr: int) -> int:
    return addr & ~0x1F


def split128(v: int) -> tuple[int, int]:
    return v & ((1 << 64) - 1), (v >> 64) & ((1 << 64) - 1)


class Golden:
    """Pure-Python mirror of cache_core.hpp."""

    def __init__(self) -> None:
        self.tag = [[0] * WAYS for _ in range(SETS)]
        self.word = [[[0] * LINE_WORDS for _ in range(WAYS)] for _ in range(SETS)]
        self.valid = [[False] * WAYS for _ in range(SETS)]
        self.dirty = [[False] * WAYS for _ in range(SETS)]
        self.age = [[0] * WAYS for _ in range(SETS)]
        self.now = 0
        self.miss_pending = False
        self.miss_addr = 0
        self.miss_write = False
        self.miss_wdata = 0
        self.miss_timer = 0
        self.miss_dirty_evict = False
        self.backing = [0] * BACK_WORDS

    def find_hit(self, s: int, tag: int) -> int:
        for w in range(WAYS):
            if self.valid[s][w] and self.tag[s][w] == tag:
                return w
        return -1

    def victim(self, s: int) -> int:
        for w in range(WAYS):
            if not self.valid[s][w]:
                return w
        return min(range(WAYS), key=lambda w: self.age[s][w])

    def eval(self, addr: int, req_valid: bool, wr: bool, wdata: int):
        """Same-cycle combinational view (pre-commit state)."""
        hit = False
        resp_valid = False
        dirty_evict = False
        rdata = 0
        if req_valid:
            s = set_of(addr)
            w = self.find_hit(s, tag_of(addr))
            if w >= 0:
                hit = True
                resp_valid = True
                words = list(self.word[s][w])
                if wr:
                    words[word_of(addr)] = (wdata >> (32 * word_of(addr))) & 0xFFFFFFFF
                rdata = sum(words[i] << (32 * i) for i in range(LINE_WORDS))
        if self.miss_pending and not self.miss_write and self.miss_timer == 0:
            if not resp_valid:
                resp_valid = True
                dirty_evict = self.miss_dirty_evict
                base = line_base(self.miss_addr) >> 2
                words = [self.backing[base + i] for i in range(LINE_WORDS)]
                rdata = sum(words[i] << (32 * i) for i in range(LINE_WORDS))
        return rdata, hit, resp_valid, dirty_evict

    def tick(self, addr: int, req_valid: bool, wr: bool, wdata: int, flush: bool) -> None:
        """Posedge state update."""
        self.now += 1
        if flush:
            for s in range(SETS):
                for w in range(WAYS):
                    self.valid[s][w] = False
            self.miss_pending = False
            return
        if self.miss_pending:
            if self.miss_timer > 0:
                self.miss_timer -= 1
            else:
                s = set_of(self.miss_addr)
                v = self.victim(s)
                base = line_base(self.miss_addr) >> 2
                self.word[s][v] = [self.backing[base + i] for i in range(LINE_WORDS)]
                if self.miss_write:
                    self.word[s][v][word_of(self.miss_addr)] = (
                        self.miss_wdata >> (32 * word_of(self.miss_addr))
                    ) & 0xFFFFFFFF
                self.tag[s][v] = tag_of(self.miss_addr)
                self.valid[s][v] = True
                self.dirty[s][v] = self.miss_write
                self.age[s][v] = self.now
                self.miss_pending = False
        if not req_valid:
            return
        s = set_of(addr)
        w = self.find_hit(s, tag_of(addr))
        if w >= 0:
            self.age[s][w] = self.now
            if wr:
                self.word[s][w][word_of(addr)] = (wdata >> (32 * word_of(addr))) & 0xFFFFFFFF
                self.dirty[s][w] = True
        elif not self.miss_pending:
            v = self.victim(s)
            self.miss_pending = True
            self.miss_addr = addr
            self.miss_write = wr
            self.miss_wdata = wdata
            self.miss_timer = REFILL - 1
            self.miss_dirty_evict = self.valid[s][v] and self.dirty[s][v]
            if self.miss_dirty_evict:
                vbase = (self.tag[s][v] << 5 | s << 2) >> 2
                for i in range(LINE_WORDS):
                    self.backing[vbase + i] = self.word[s][v][i]


# Directed request sequence: (addr, wr, wdata128)
REQS = [
    (0x00, False, 0),                     # read miss A.set0 -> fill (backing zeros)
    (0x00, True, 0xDEADBEEF00000011),     # write hit A (word1)
    (0x20, False, 0),                     # read miss B.set0 -> evicts dirty A
    (0x00, False, 0),                     # read miss A again -> dirty_evict=1 (B), backing data
    (0x40, False, 0),                     # read miss C.set0 -> evicts A
    (0x20, False, 0),                     # read hit B
    (0x00, True, 0x123456789ABCDEF0),     # write miss A (word0)
    (0x00, False, 0),                     # read miss A -> dirty_evict (A dirty)
    (0x20, True, 0xAAAA),                 # write hit B (word0)
    (0x40, False, 0),                     # read miss C -> LRU eviction again
]


@testbench
def tb(t: Tb) -> None:
    tbw = CycleAwareTb(t)
    p = TB_PRESETS["smoke"]
    tbw.clock("clk")
    tbw.reset("rst", cycles_asserted=2, cycles_deasserted=1)
    tbw.timeout(int(p["timeout"]))

    g = Golden()

    def drive(addr: int, valid: bool, wr: bool, wdata: int, flush: bool = False) -> None:
        tbw.drive("addr", addr)
        tbw.drive("req_valid", 1 if valid else 0)
        tbw.drive("wr", 1 if wr else 0)
        tbw.drive("wdata", wdata)
        tbw.drive("wmask", 0xFFFF)
        tbw.drive("resp_ready", 1)
        tbw.drive("flush", 1 if flush else 0)

    def expect_post_tick(addr: int, valid: bool, wr: bool, wdata: int, flush: bool = False) -> None:
        """Expect the post-commit view: tick first, then eval (same inputs)."""
        g.tick(addr, valid, wr, wdata, flush)
        rdata, hit, resp_valid, dirty_evict = g.eval(addr, valid, wr, wdata)
        tbw.expect("rdata", rdata)
        tbw.expect("hit", 1 if hit else 0)
        tbw.expect("resp_valid", 1 if resp_valid else 0)
        tbw.expect("dirty_evict", 1 if dirty_evict else 0)

    IDLE = (0, False, False, 0)

    # cycle 0: idle
    drive(*IDLE)
    expect_post_tick(*IDLE)
    tbw.next()

    for addr, wr, wdata in REQS:
        # Request cycle.
        drive(addr, True, wr, wdata)
        expect_post_tick(addr, True, wr, wdata)
        tbw.next()
        # Second cycle of a read miss carries the response (hit stays 0).
        drive(*IDLE)
        expect_post_tick(*IDLE)
        tbw.next()
        # One settle cycle after a miss: the fill lands on this cycle's
        # posedge, and the Verilog view (post-edge hit lookup) must not race
        # a same-cycle request against the line it just filled.
        drive(*IDLE)
        expect_post_tick(*IDLE)
        tbw.next()

    # flush cycle: everything invalid afterwards
    drive(0, False, False, 0, flush=True)
    expect_post_tick(0, False, False, 0, flush=True)
    tbw.next()

    # post-flush read of previously dirty line: data comes from the backing
    # store via a fresh miss (word1 keeps the pre-eviction write-back value).
    drive(0x00, True, False, 0)
    expect_post_tick(0x00, True, False, 0)
    tbw.next()
    drive(*IDLE)
    expect_post_tick(*IDLE)
    tbw.next()

    tbw.finish(at=int(p["finish"]))


if __name__ == "__main__":
    from pycircuit import compile_cycle_aware

    print(compile_cycle_aware(build, name="ext_cache_top", eager=True).emit_mlir())

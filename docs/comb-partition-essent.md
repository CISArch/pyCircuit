# Comb Partitioning (ESSENT-style combine)

Branch: `ldz/feat/combine-split` (derived from `feat/change-driven-scheduler`)

This document describes the acyclic comb-domain partitioning introduced on this
branch. The design follows the coarsening idea of ESSENT
(Beamer et al., *ESSENT: A High-Performance RTL Simulator*, WoSET 2021):
instead of paying per-node activity checks, coarsen the graph into partitions
and skip whole partitions when their inputs are unchanged.

## Relation to the removed `PartitionCombPass`

`PartitionCombPass` (supernode static partitioning, removed in `c7e5744`) was a
general supernode partitioner with a large contract surface (~2.3k lines with
its checkers). This branch deliberately re-implements only the essential
kernel on top of the existing change-driven schedule infrastructure:

| Reused infrastructure | Role |
| --- | --- |
| `CombDepGraph` / `buildChangeScheduleDag` | same-tick candidate dependency DAG |
| `pyc.change_schedule.v1` metadata | slot/rank/fanout contract, extended additively |
| `CppEmitter` comb path | input-snapshot guards, result publish filtering |
| `pyc::cpp::DirtyBitset` | runtime dirty set, now keyed by partition |

## Algorithm (combine)

Atoms are the fused `pyc.comb` regions produced by `pyc-fuse-comb`. The
partitioner (`pyc-comb-partition`, `CombPartitionPass.cpp`) walks regions in
schedule slot (topological) order:

1. Count comb dependency edges from region `r` into each predecessor
   partition.
2. Pick the strongest-connected predecessor partition (ties: lowest id).
3. If the merged weight (number of scheduled results) stays within
   `targetSize`, join it; otherwise start a new partition.

Because a region only ever merges into a **predecessor** partition, the
partition-induced graph is acyclic by construction. The pass still verifies
this directly (every cross-partition edge must point forward in slot order) as
a gate, together with the size bound.

State sources (regs, memories, fifos, CDC syncs) and instances are never
merged; they remain standalone schedule units and act as partition boundaries.

The result is attached as:
- `pyc.change_schedule.partition = <id>` per comb operation,
- `partition_count` appended to `pyc.change_schedule.summary`.

## Emission

The C++ emitter groups combs by partition and emits one
`eval_comb_part_<id>()` method per partition:

- a single guard takes the partition dirty bit and compares the polled
  boundary-input snapshots of **all** member regions once,
- member bodies then run unconditionally in schedule order; results are still
  published through the unchanged change-compare + fanout path, so
  intra-partition consumers need no re-marking (marks targeting the partition
  currently being evaluated are suppressed),
- dispatch sites (`eval_comb_pass`, dirty tick) call the group method only at
  the first member's position; partitions without any polled boundary input are
  called only when their dirty bit is set.

Without partition metadata the emitter falls back to **identity partitions**
(one per scheduled operation), which reproduces the pre-partition dispatch
exactly — the default pipeline is unchanged bit-for-bit.

## Usage

```bash
pycc design.py --emit=cpp --comb-partition-size=64   # coarseness target
pycc design.py --emit=cpp                            # no comb fusion (default)
pycc design.py --emit=cpp --comb-textual-fuse        # legacy textual runs
```

`--comb-partition-size=0` (default) means **no comb fusion at all**: fusible
comb ops stay individual top-level ops and both emitters evaluate them per-op.
The legacy textual-run fusion (previously the implicit cp=0 behavior) is now
opt-in via `--comb-textual-fuse`. As in ESSENT, a single coarseness parameter
controls the tradeoff between skip granularity and per-partition check
overhead; results are independent of the value chosen (only performance
changes).

### Measured: keep the default `0`

The coarseness sweep on the DavinciTop design (`v5_superscalar_v5_core`,
`examples_intermediate_gemm` trace, same MLIR, same replay flow, interleaved
CPU-time A/B) shows graph mode is a net loss on this workload (measured when
`0` still meant textual fusion; per-op emission is the successor default):

| `--comb-partition-size` | emit | cluster0 partitions | wall time | vs `0` |
|---|---|---|---|---|
| `0` (textual fusion, then-default) | ok | 926 | 0.26 s | 1.00x |
| `1` | fails (residual dominance) | — | — | — |
| `4` | ok | 4828 | 1.15 s | 0.23x |
| `8` | fails (residual dominance) | — | — | — |
| `16` | fails (residual dominance) | — | — | — |
| `64` | ok | 25 | 0.88 s | 0.32x |
| `1` + `--comb-cones-only` | ok | 14121 | 3.87 s | 0.07x |

Functional results are bit-identical in every case that compiles
(`cycles`/`pe0_busy_cycles`/`max_raw_pc` unchanged).

Removing the merge phases entirely (`--comb-cones-only`, i.e. only the MFFC
bootstrap cones) is the worst configuration of all: cluster0 ends up with
14121 single-head cones — the fanout-free cone condition ("all successors
already inside the cone") almost never holds on this high-fanout design, so
the cones degenerate to one op each — and the run is 14.3x slower than textual
fusion. Cone-only partitioning is not a viable direction here.

Both ends of the sweep lose: coarse partitions (25) collapse skip granularity,
while fine graph partitions (4828) multiply boundary snapshot compares and
dispatch sites. ESSENT's premise — large designs with low activity factors
(1-2%) — does not hold for DavinciTop, which is near-fully active every cycle
(`pe0_busy_cycles` ≈ 85%). Textual fusion keeps the useful property (fine
identity partitions, 926) without graph-mode boundary overhead, so `0` stays
the default. Graph mode also still hits occasional residual dominance failures
at some thresholds (see the reorder relay handling in `FuseCombPass.cpp`).

## Verification

- `compiler/mlir/test/comb_partition_smoke.sh`: compiles the dirty-scheduler
  design in both modes and diffs 256-cycle simulation traces bit-for-bit; also
  checks the partitioned eval structure and the IR metadata contract.
- `compiler/mlir/test/change_schedule_gate.sh`: unchanged schedule contract.
- `compiler/mlir/test/comb_dirty_scheduler_smoke.sh` and
  `cpp_member_placement_smoke.sh`: identity-mode emission unchanged.

### Future work (split phase)

ESSENT additionally exploits dynamic don't-cares (e.g. unselected mux ways and
write-disabled register inputs) to shrink the evaluated portion further. That
"split" direction is intentionally left out of this branch.

# Rocket-pyc: Rocket Chip bare core in PyCircuit (import flow)

Verilog→pyc import and equivalence-check flow for the freechips
Rocket core (RV32IMA, bare `Rocket` top from rocket-chip v1.6
`generated-verilog`, with a local `plusarg_reader_stub.v` fix).

Status: **400 cycles, 0 mismatches** on both export paths
(golden Verilator vs `pyc.verilog` emitter; golden vs pycc C++ runner).

## Pipeline

```
rocket-chip (mill + Chisel 6.7)                      [regeneration path]
  manual_build.sh -> generated-fir/*.fir
  strip_fir.py     -> drop printf/assert (firtool vs chisel<=6.7, circt#6970)
  firtool          -> Verilog
rocket-chip-v16/generated-verilog/*.v                [check input, v1.6 release]
  scripts/check_rocket.sh
    -> v2p (verilog2pyc): yosys normalize -> pyc MLIR
       path A: MLIR -> pyc.v Verilog  \ three-way ST-trace
       path B: MLIR -> pycc C++       / equivalence check
```

## Layout

- `tb/tb_rocket.v` — golden testbench (ST protocol). Free-running
  instruction-fetch model + registered redirect reaction; DUT inputs are
  held stable across each row's [sample, edge, print] window (cpp runner
  replay contract). Program: addi/add/sw/lw data loop.
- `scripts/check_rocket.sh` — canonical three-way check entry point.
- `scripts/manual_build.sh` — scalac workaround build + FIRRTL elaboration
  (`ROCKET_CHIP_DIR` overrides the source tree).
- `scripts/strip_fir.py` — FIRRTL purification for firtool consumption.
- `scripts/status.sh` — mill/elaboration progress helper.

## Usage

```bash
scripts/check_rocket.sh                 # 400-cycle default
scripts/check_rocket.sh --cycles 100
```

Prereqs: `pycc` built (`toolchain`), verilator/yosys on PATH, and the
`verilog2pyc` repo (V2P_DIR; the importer is not vendored here).

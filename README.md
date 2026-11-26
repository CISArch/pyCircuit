# pyCircuit (pyc4.0 / pyc0.40)

<p align="center">
  <img src="https://img.shields.io/badge/License-MIT-blue.svg" alt="License">
  <img src="https://img.shields.io/badge/Python-3.10%2B-green.svg" alt="Python">
  <img src="https://img.shields.io/badge/MLIR-19-orange.svg" alt="MLIR">
  <a href="https://github.com/LinxISA/pyCircuit/actions"><img src="https://github.com/LinxISA/pyCircuit/actions/workflows/ci.yml/badge.svg" alt="CI"></a>
  <a href="https://github.com/LinxISA/pyCircuit/actions/workflows/release.yml"><img src="https://github.com/LinxISA/pyCircuit/actions/workflows/release.yml/badge.svg" alt="Release"></a>
  <a href="https://github.com/LinxISA/pyCircuit/releases"><img src="https://img.shields.io/github/v/release/LinxISA/pyCircuit?display_name=tag" alt="Latest Release"></a>
  <img src="https://img.shields.io/badge/PyPI-pycircuit--hisi-blue.svg" alt="PyPI Package">
</p>

pyCircuit is a Python-based hardware construction DSL that compiles Python
modules to an MLIR hardware dialect and emits:

- **C++ functional simulation** (module instances become SimObjects with `tick()` / `transfer()`)
- **Verilog** (RTL integration + Verilator)

pyc4.0 is a hard-break release focused on **ultra-large designs**, scalable DFX,
and strict IR legality gates.

## Key features (pyc4.0)

- **Hierarchy-preserving `@module` boundaries** (1:1 with simulation objects)
- **Two-phase cycle model**: `tick()` then `transfer()`
- **Gate-first compiler**: static-hardware IR legality, comb-cycle checks, logic-depth propagation
- **Structured interfaces** via `spec` (Bundle/Struct/Signature) with deterministic flattening
- **Integrated `@testbench`** flow (device + TB compiled together)

## Quick start

Build the backend tool (`pycc`):

```bash
bash flows/scripts/pyc build
```

The staged toolchain is installed under `.pycircuit_out/toolchain/install/` by default.

Install a release wheel instead of building locally:

```bash
python3 -m pip install /path/to/pycircuit_hisi-<version>-py3-none-<platform>.whl
pycc --version
```

The platform wheel bundles the matching `pycc` toolchain under the `pycircuit`
package, so `pycircuit.cli` and the `pycc` wrapper use the same installed source
tree and do not require a separate repo-local build. The wheel must match both
your OS/architecture and Python 3.10+.

Published package install command:

```bash
python3 -m pip install pycircuit-hisi
```

The distribution name is `pycircuit-hisi` to avoid the existing unrelated
`pycircuit` package on PyPI. The Python import path remains `pycircuit`, and
the installed compiler command remains `pycc`.

Install the frontend from source for development:

```bash
python3 -m pip install -e .
python3 -m pycircuit.cli --help
```

Editable source install is frontend-only. It does not install `pycc`; build the
toolchain with `bash flows/scripts/pyc build` and point `PYC_TOOLCHAIN_ROOT` at
`.pycircuit_out/toolchain/install`, or use a release wheel.

Run the smoke gates:

```bash
bash flows/scripts/run_examples.sh
bash flows/scripts/run_sims.sh
```

### Minimal design snippet (counter)

```python
from pycircuit import Circuit, module, u

@module
def build(m: Circuit, width: int = 8) -> None:
    clk = m.clock("clk")
    rst = m.reset("rst")
    en = m.input("enable", width=1)

    count = m.out("count_q", clk=clk, rst=rst, width=width, init=u(width, 0))
    count.set(count.out() + 1, when=en)
    m.output("count", count)
```

Build a multi-module project (device + TB):

```bash
PYTHONPATH=compiler/frontend \
PYC_TOOLCHAIN_ROOT=.pycircuit_out/toolchain/install \
python3 -m pycircuit.cli build \
  designs/examples/counter/tb_counter.py \
  --out-dir /tmp/pyc_counter \
  --target both \
  --jobs 8
```

Emit device RTL without requiring a testbench:

```bash
PYTHONPATH=compiler/frontend \
  PYC_TOOLCHAIN_ROOT=.pycircuit_out/toolchain/install \
python3 -m pycircuit.cli build \
  designs/examples/counter/counter.py \
  --out-dir /tmp/pyc_counter_rtl \
  --target verilog
```

An optional XingTian post-Verilog flow can run remote logic synthesis after all
normal MLIR gates pass:

```bash
python3 -m pycircuit.cli build design.py \
  --out-dir build/design \
  --target verilog \
  --eda-flow xingtian
```

Machine-local SDC and SSH paths can be stored in the Git-ignored
`eda/xingtian/config.local.json`. Public backend documentation, templates,
scripts, tests, and examples live under `eda/<backend>/`; private credentials
and generated results remain ignored. See `eda/README.md` and
`docs/PIPELINE.md`.

For open 45 nm research synthesis, install the pinned Nangate45 Liberty and
select the local Yosys/ABC adapter:

```bash
./eda/nangate45/scripts/setup.sh
cp eda/nangate45/config.example.json eda/nangate45/config.local.json
python3 -m pycircuit.cli build designs/examples/counter/counter.py \
  --out-dir eda/nangate45/build/counter \
  --target verilog \
  --param width=8 \
  --eda-flow nangate45
```

Nangate45 is non-manufacturable and intended for research/flow bring-up.

For more end-to-end commands, see `docs/QUICKSTART.md`.

## Repo layout

```
pyCircuit
├── compiler/
│   ├── frontend/          # Python frontend (pycircuit package)
│   └── mlir/              # MLIR dialect + passes + tools (pycc, pyc-opt)
├── runtime/
│   ├── cpp/               # C++ simulation runtime
│   └── verilog/           # Verilog primitives
├── designs/
│   └── examples/          # Example designs
└── docs/                  # Documentation
```

## Documentation

- `docs/QUICKSTART.md`
- `docs/FRONTEND_API.md`
- `docs/TESTBENCH.md`
- `docs/IR_SPEC.md`
- `docs/updatePLAN.md` and `docs/rfcs/pyc4.0-decisions.md`

## Examples

| Example | Description |
|---------|-------------|
| [Counter](designs/examples/counter/) | Basic counter with enable |
| [Calculator](designs/examples/calculator/) | Stateful keypad calculator |
| [FIFO Loopback](designs/examples/fifo_loopback/) | FIFO queue with loopback |
| [Digital Clock](designs/examples/digital_clock/) | Time-of-day clock display |
| [FastFWD](designs/examples/fastfwd/) | Network packet forwarding |
| [Linx CPU](contrib/linx/designs/examples/linx_cpu_pyc/) | Full 5-stage pipeline CPU |

## 消融实验开关总表（`test` 分支专用）

本分支（`test`，基 dev@`17b23c41`）是**消融实验专用分支**：论文需要的「关闭/替换某一项设计决策」对照都在这里以开关档位实现，每档默认值保持 dev 行为。所有消融开关登记在下面两张表里，新开关合入时必须同步加行。

**新增消融开关的固定流程**：① 默认值 = dev 行为（PR 形态默认不变）；② 实现落在 MLIR pass + 驱动旗标（gate-first），未知取值要报错；③ 配一个 smoke 门并挂进 `ci.yml`；④ 测量时另做 `MEASUREMENT ONLY — do not merge` 本地提交把默认翻到待测档（存 `backup-meas-*` 分支，不 push），导出提测树与 dev 基线**背靠背成对**提测；⑤ 出数后把数字回填到下表（绑定精确 SHA）并同步工作区根 README 与 branch-ancestry-perf.md。

### 本分支新增的消融开关

| 开关 | 层级 | 默认 | 档位与语义 | 消融测量 |
|---|---|---|---|---|
| `--comb-fuse-algo=signature\|greedy` | `pycc` 驱动 | `signature` | comb run 分组算法。`signature`：按 op 读取的输入集合签名划分 run，每梳只在自己输入变化时唤醒（端口经一个转发 comb 轮询）；`greedy`：签名划分引入前的旧基本算法——不划分，连续 run 一梳到底融成整块 comb（每模块一大 comb，端口直读、无转发 comb） | **6.4655×**（signature vs greedy，2026-11-26 同窗口成对，34/34 更快，min 5.77/max 8.28）：signature=dev@`17b23c41` pyc_gm 16375.7，greedy=`0d8b612d`（backup-meas-fusecomb）2532.8；Verilator 哨兵 1.0025≈1；34/34 MATCH |
| `--pyc-fuse-comb=algo=signature\|greedy` | `pyc-opt` pass 选项 | `signature` | 同上，pass 级入口（IR 级实验用；pycc 档即由此传入） | 同上 |

门：`compiler/mlir/test/fuse_comb_greedy_smoke.sh`（断言 greedy 态 fixture 融成单 comb 直读端口）；已挂 `ci.yml`。

### dev 既有、可作消融对照的开关（本分支不改动，备查）

| 开关 | 默认 | 语义（消融视角） |
|---|---|---|
| `--cpp-parallel-instances=<N>` | `1` | 1=串行（逐字节同基线）；0=按硬件核数 auto（夹 [2,32]）；N≥2=固定 N 路池。宽度扫描：=2 是唯一正收益档 |
| `--sim-mode=cpp-only` + `--cpp-only-preserve-ops` | `default` / `false` | 两项同时设置时跳过 comb 融合（per-op 发射），可作「无融合」对照档 |
| `--emit-structural=auto\|on\|off` | `auto` | comb fusion 的结构化发射策略 |
| `--state-loop` | `true` | 同时钟域 reg/delay_line 降成每时钟域一个状态更新循环（关掉=退回逐 reg 形态） |
| `--hierarchy-policy=strict\|instantiate` / `--hierarchical` / `--flatten` | `strict` | 层级保持 vs 拍平的发射形态对照 |
| `--inline-policy=default\|off\|threshold:<n>` / `--noinline` | `default` | inliner 策略（模块边界保持 vs 内联） |
| `--logic-depth=<N>` | `32` | 组合逻辑深度检查上限（合法性门，非性能开关） |
| `--cpp-shard-max-ast-nodes=<N>` / `--cpp-shard-threshold-*` | `0` / 4MiB | 巨型 eval 拓扑分片（代码布局类对照） |

## License

pyCircuit is licensed under the MIT License. See `LICENSE`.

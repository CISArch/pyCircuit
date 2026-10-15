#!/usr/bin/env python3
"""Cross-check retimed C++ against unoptimized C++ (delay lines are C++-only)."""

from __future__ import annotations

import argparse
import json
import subprocess
import tempfile
from pathlib import Path

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[2]
DEFAULT_BUILD = ROOT / ".pycircuit_out/toolchain/build/bin"
RESULT_RE = __import__("re").compile(r"cycles=(\d+) checksum=(\d+)")


def run(command: list[str], *, env: dict[str, str] | None = None) -> str:
    return subprocess.run(
        command, cwd=ROOT, check=True, text=True, capture_output=True, env=env
    ).stdout


def result(command: list[str]) -> tuple[int, int]:
    match = RESULT_RE.search(run(command))
    if not match:
        raise RuntimeError(f"missing model result: {command}")
    return int(match.group(1)), int(match.group(2))


def emit(pycc: Path, output: Path, kind: str) -> dict[str, object]:
    run([
        str(pycc), str(HERE / "state_retime_codegen.mlir"), f"--emit={kind}",
        "--state-pack-width=1", "-o", str(output),
    ])
    return json.loads(Path(f"{output}.stats.json").read_text(encoding="utf-8"))


def compile_cpp(cxx: str, header: Path, binary: Path) -> None:
    run([
        cxx, "-std=c++17", "-O2", f"-I{ROOT / 'runtime'}",
        f'-DMODEL_HEADER="{header}"', str(HERE / "state_retime_model.cpp"),
        "-o", str(binary),
    ])


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--pycc", type=Path, default=DEFAULT_BUILD / "pycc")
    parser.add_argument("--cxx", default=__import__("os").environ.get("CXX", "c++"))
    args = parser.parse_args()

    with tempfile.TemporaryDirectory(prefix="pyc-retime-", dir="/tmp") as path:
        temp = Path(path)
        opt_cpp = temp / "opt.hpp"
        plain_cpp = temp / "plain.hpp"
        observed: dict[str, tuple[int, int]] = {}
        cpp_stats = emit(args.pycc, opt_cpp, "cpp")
        # Unoptimized reference: state optimization is C++-path-only; disabling
        # it keeps the plain register netlist for the equivalence reference.
        run([
            str(args.pycc), str(HERE / "state_retime_codegen.mlir"),
            "--emit=cpp", "--state-pack-width=1",
            "--observe-named=all", "--no-state-opt", "-o", str(plain_cpp),
        ])
        plain_stats = json.loads(
            Path(f"{plain_cpp}.stats.json").read_text(encoding="utf-8")
        )
        if (cpp_stats.get("reg_count") != 5 or cpp_stats.get("reg_bits") != 33):
            raise AssertionError(f"cpp: logical state changed: {cpp_stats}")
        if cpp_stats.get("retime_regions_rewritten") != 2:
            raise AssertionError(f"cpp: retiming stats mismatch: {cpp_stats}")
        if cpp_stats.get("retime_state_bits_removed") != 15:
            raise AssertionError(f"cpp: retiming bit delta mismatch: {cpp_stats}")
        if cpp_stats.get("delay_line_count") != 1:
            raise AssertionError(f"cpp: delay line mismatch: {cpp_stats}")
        if cpp_stats.get("state_opt_policy") != "structural":
            raise AssertionError(f"cpp: policy is not structural: {cpp_stats}")
        if cpp_stats.get("state_retime_policy") != "pipeline":
            raise AssertionError(f"cpp: retime policy is not pipeline: {cpp_stats}")
        if (plain_stats.get("reg_count") != 6 or
                plain_stats.get("reg_bits") != 48):
            raise AssertionError(
                f"plain: unoptimized state changed: {plain_stats}"
            )
        if plain_stats.get("retime_regions_rewritten"):
            raise AssertionError(
                f"plain: retiming ran unexpectedly: {plain_stats}"
            )
        if plain_stats.get("delay_line_count"):
            raise AssertionError(
                f"plain: delay line formed unexpectedly: {plain_stats}"
            )
        if plain_stats.get("state_opt_policy") != "off":
            raise AssertionError(f"plain: policy is not off: {plain_stats}")
        if plain_stats.get("state_retime_policy") != "off":
            raise AssertionError(
                f"plain: retime policy is not off: {plain_stats}"
            )

        compile_cpp(args.cxx, opt_cpp, temp / "opt_bin")
        observed["opt"] = result([str(temp / "opt_bin")])
        compile_cpp(args.cxx, plain_cpp, temp / "plain_bin")
        observed["plain"] = result([str(temp / "plain_bin")])
        if len(set(observed.values())) != 1:
            raise AssertionError(f"retiming model mismatch: {observed}")
        cycles, checksum = next(iter(observed.values()))
        print(
            "retiming verified: a 3-register computed pipeline -> one depth-3 "
            "history and two delayed i8 operands -> one i1 result state; "
            "optimized C++ matches unoptimized C++ for "
            f"{cycles} cycles (checksum={checksum})"
        )


if __name__ == "__main__":
    main()

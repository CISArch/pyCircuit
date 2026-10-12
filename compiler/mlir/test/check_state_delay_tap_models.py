#!/usr/bin/env python3
"""Verify C++ delay taps against unoptimized C++ (delay lines are C++-only)."""

from __future__ import annotations

import argparse
import json
import os
import re
import subprocess
import tempfile
from pathlib import Path

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[2]
DEFAULT_BUILD = ROOT / ".pycircuit_out/toolchain/build/bin"
RESULT_RE = re.compile(r"cycles=(\d+) checksum=(\d+)")


def run(command: list[str], *, env: dict[str, str] | None = None) -> str:
    return subprocess.run(
        command, cwd=ROOT, check=True, text=True, capture_output=True, env=env
    ).stdout


def result(command: list[str]) -> tuple[int, int]:
    match = RESULT_RE.search(run(command))
    if not match:
        raise RuntimeError(f"missing result for {command}")
    return int(match.group(1)), int(match.group(2))


def emit(pycc: Path, source: Path, output: Path, extra: list[str]) -> dict[str, object]:
    run([
        str(pycc), str(source), "--emit=cpp",
        "--state-pack-width=0", *extra, "-o", str(output),
    ])
    return json.loads(Path(f"{output}.stats.json").read_text(encoding="utf-8"))


def compile_cpp(cxx: str, header: Path, binary: Path) -> None:
    run([
        cxx, "-std=c++17", "-O2", "-DNDEBUG", f"-I{ROOT / 'runtime'}",
        f'-DMODEL_HEADER="{header}"', str(HERE / "state_delay_tap_model.cpp"),
        "-o", str(binary),
    ])


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--pycc", type=Path, default=DEFAULT_BUILD / "pycc")
    parser.add_argument("--cxx", default=os.environ.get("CXX", "c++"))
    args = parser.parse_args()

    source = HERE / "state_delay_tap_codegen.mlir"
    with tempfile.TemporaryDirectory(prefix="pyc-delay-tap-", dir="/tmp") as path:
        temp = Path(path)
        opt_cpp = temp / "opt.hpp"
        plain_cpp = temp / "plain.hpp"
        observed: dict[str, tuple[int, int]] = {}
        opt_stats = emit(args.pycc, source, opt_cpp, [])
        plain_stats = emit(args.pycc, source, plain_cpp, ["--no-state-opt"])
        if opt_stats.get("delay_chain_taps_created") != 1:
            raise AssertionError(f"opt: unexpected tap stats: {opt_stats}")
        if opt_stats.get("reg_count") != 4 or opt_stats.get("reg_bits") != 32:
            raise AssertionError(f"opt: logical state changed: {opt_stats}")
        if plain_stats.get("delay_chain_taps_created"):
            raise AssertionError(
                f"plain: tap rewrite ran unexpectedly: {plain_stats}"
            )
        if (plain_stats.get("reg_count") != 4 or
                plain_stats.get("reg_bits") != 32):
            raise AssertionError(
                f"plain: unoptimized state changed: {plain_stats}"
            )
        if plain_stats.get("state_opt_policy") != "off":
            raise AssertionError(f"plain: policy is not off: {plain_stats}")

        compile_cpp(args.cxx, opt_cpp, temp / "opt_bin")
        observed["opt"] = result([str(temp / "opt_bin")])
        compile_cpp(args.cxx, plain_cpp, temp / "plain_bin")
        observed["plain"] = result([str(temp / "plain_bin")])
        if len(set(observed.values())) != 1:
            raise AssertionError(f"delay tap backend mismatch: {observed}")
        cycles, checksum = next(iter(observed.values()))
        print(
            "delay tap equivalence verified: 4-reg chain -> one depth-4 history "
            f"with depth-2 tap; optimized C++ matches unoptimized C++ for "
            f"{cycles} cycles "
            f"(checksum={checksum})"
        )


if __name__ == "__main__":
    main()

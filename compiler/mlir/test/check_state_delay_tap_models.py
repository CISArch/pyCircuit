#!/usr/bin/env python3
"""Verify C++ delay taps against unoptimized C++ (delay lines are C++-only)."""

from __future__ import annotations

import argparse
import os
import tempfile
from pathlib import Path

from _state_model_check import DEFAULT_BUILD, compile_cpp, emit, result

HERE = Path(__file__).resolve().parent


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
        opt_stats = emit(args.pycc, source, opt_cpp)
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

        driver = HERE / "state_delay_tap_model.cpp"
        compile_cpp(args.cxx, opt_cpp, temp / "opt_bin", driver,
                    ["-DNDEBUG"])
        observed["opt"] = result([str(temp / "opt_bin")])
        compile_cpp(args.cxx, plain_cpp, temp / "plain_bin", driver,
                    ["-DNDEBUG"])
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

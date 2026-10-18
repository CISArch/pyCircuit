#!/usr/bin/env python3
"""Cross-check retimed C++ against unoptimized C++ (delay lines are C++-only)."""

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

    source = HERE / "state_retime_codegen.mlir"
    with tempfile.TemporaryDirectory(prefix="pyc-retime-", dir="/tmp") as path:
        temp = Path(path)
        opt_cpp = temp / "opt.hpp"
        plain_cpp = temp / "plain.hpp"
        observed: dict[str, tuple[int, int]] = {}
        cpp_stats = emit(args.pycc, source, opt_cpp)
        # Unoptimized reference: state optimization is C++-path-only; disabling
        # it keeps the plain register netlist for the equivalence reference.
        plain_stats = emit(
            args.pycc, source, plain_cpp,
            ["--observe-named=all", "--no-state-opt"],
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

        driver = HERE / "state_retime_model.cpp"
        compile_cpp(args.cxx, opt_cpp, temp / "opt_bin", driver)
        observed["opt"] = result([str(temp / "opt_bin")])
        compile_cpp(args.cxx, plain_cpp, temp / "plain_bin", driver)
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

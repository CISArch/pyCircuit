#!/usr/bin/env python3
from __future__ import annotations

import sys
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
FRONTEND = ROOT / "compiler" / "frontend"
sys.path.insert(0, str(FRONTEND))

from pycircuit.cli import _backend_build_flag_hashes


TICK_DEFAULTS = {
    "cpp_parallel_tick": False,
    "cpp_tick_chunk": None,
    "cpp_tick_partition": None,
}


class TestCppPchCacheKeys(unittest.TestCase):
    def test_pch_only_invalidates_cpp_key(self) -> None:
        shared_flags = {
            "pycc": "/toolchain/bin/pycc",
            "logic_depth": 32,
            "target": "both",
        }

        shared_off, cpp_off = _backend_build_flag_hashes(
            shared_flags, cpp_flags={"cpp_pch": False, **TICK_DEFAULTS}
        )
        shared_on, cpp_on = _backend_build_flag_hashes(
            shared_flags, cpp_flags={"cpp_pch": True, **TICK_DEFAULTS}
        )

        self.assertEqual(shared_off, shared_on)
        self.assertNotEqual(cpp_off, cpp_on)
        self.assertNotIn("cpp_pch", shared_flags)

    def test_parallel_tick_only_invalidates_cpp_key(self) -> None:
        shared_flags = {
            "pycc": "/toolchain/bin/pycc",
            "logic_depth": 32,
            "target": "both",
        }

        shared_off, cpp_off = _backend_build_flag_hashes(
            shared_flags, cpp_flags={"cpp_pch": False, **TICK_DEFAULTS}
        )
        shared_on, cpp_on = _backend_build_flag_hashes(
            shared_flags, cpp_flags={"cpp_pch": False, **TICK_DEFAULTS, "cpp_parallel_tick": True}
        )

        self.assertEqual(shared_off, shared_on)
        self.assertNotEqual(cpp_off, cpp_on)
        self.assertNotIn("cpp_parallel_tick", shared_flags)

    def test_tick_knobs_only_invalidate_cpp_key(self) -> None:
        shared_flags = {
            "pycc": "/toolchain/bin/pycc",
            "logic_depth": 32,
            "target": "both",
        }

        base = _backend_build_flag_hashes(
            shared_flags, cpp_flags={"cpp_pch": False, **TICK_DEFAULTS}
        )
        chunked = _backend_build_flag_hashes(
            shared_flags, cpp_flags={"cpp_pch": False, **TICK_DEFAULTS, "cpp_tick_chunk": 32}
        )
        weighted = _backend_build_flag_hashes(
            shared_flags,
            cpp_flags={"cpp_pch": False, **TICK_DEFAULTS, "cpp_tick_partition": "weighted"},
        )

        self.assertEqual(base[0], chunked[0])
        self.assertEqual(base[0], weighted[0])
        self.assertNotEqual(base[1], chunked[1])
        self.assertNotEqual(base[1], weighted[1])


if __name__ == "__main__":
    unittest.main()

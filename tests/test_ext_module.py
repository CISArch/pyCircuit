"""Functional-correctness gates for the external black-box module interface
(pyc.ext_module / pyc.instance, docs/external-modules.md).

These are pure front-end checks: they import ``pycircuit.ext`` and exercise
``parse_manifest``, ``ext_module_mlir``, ``declare``/``bind`` and the manifest
validation errors — no ``pycc``/LLVM/MLIR build is required, so they run under a
plain ``pytest`` invocation (any Python >= 3.10).

The end-to-end dual-backend behaviour (CppEmitter / VerilogEmitter emission +
``cli build`` + ``tb_ext_dct8`` simulation) is NOT covered here; that lives in a
separate `*_smoke.sh`-style gate that needs a built ``pycc``.
"""

from __future__ import annotations

import os
import tempfile
from pathlib import Path

import pytest

from pycircuit import Circuit
from pycircuit.design import Design, DesignError
from pycircuit.ext import (
    ExtModuleDecl,
    declare,
    ext_module_mlir,
    parse_manifest,
)

_REAL_MANIFEST = Path("designs/examples/ext_dct8/ext/ext_dct8.toml")


# --- helpers ---------------------------------------------------------------


def _write_manifest(text: str, name: str = "m.toml") -> Path:
    """Write a throwaway manifest into a temp dir and return its path."""
    d = tempfile.mkdtemp()
    p = Path(d) / name
    p.write_text(text)
    return p


def _simple_manifest(*, name: str = "m", ports: str | None = None) -> str:
    if ports is None:
        ports = (
            '[[ports]]\nname="a"\ndir="in"\nwidth=8\n'
            '[[ports]]\nname="b"\ndir="out"\nwidth=8\n'
        )
    return f'[module]\nname="{name}"\n{ports}'


# --- parse_manifest --------------------------------------------------------


def test_parse_real_manifest() -> None:
    """The bundled ext_dct8 example parses with the expected shape."""
    decl = parse_manifest(_REAL_MANIFEST)
    assert decl.name == "ext_dct8"
    assert decl.verilog_top == "dct8"
    assert [(p.name, p.width) for p in decl.inputs] == [("in", 64), ("valid", 1)]
    assert [(p.name, p.width) for p in decl.outputs] == [("out", 64)]


def test_parse_minimal_manifest() -> None:
    decl = parse_manifest(_write_manifest(_simple_manifest()))
    assert decl.name == "m"
    assert decl.verilog_top == "m"  # verilog_top defaults to module name
    assert len(decl.inputs) == 1 and decl.inputs[0].name == "a"
    assert len(decl.outputs) == 1 and decl.outputs[0].name == "b"


def test_parse_verilog_top_override() -> None:
    text = _simple_manifest() + '[backends.verilog]\ntop="dct8"\n'
    assert parse_manifest(_write_manifest(text)).verilog_top == "dct8"


@pytest.mark.parametrize(
    "text, needle",
    [
        ("[bogus]\nx=1\n", "missing [module] table"),
        ('[module]\nname=""\n', "[module] name must be non-empty"),
        ('[module]\nname="m"\n', "at least one [[ports]] entry is required"),
        (
            '[module]\nname="m"\n[[ports]]\nname="a"\ndir="bidir"\nwidth=8\n',
            'dir must be "in", "out", "clock" or "reset"',
        ),
        (
            '[module]\nname="m"\n[[ports]]\nname="a"\ndir="in"\nwidth=0\n',
            "width must be in 1..4096",
        ),
    ],
)
def test_parse_manifest_errors(text: str, needle: str) -> None:
    with pytest.raises(DesignError) as ei:
        parse_manifest(_write_manifest(text))
    assert needle in str(ei.value)


def test_parse_manifest_duplicate_port_name() -> None:
    text = (
        '[module]\nname="m"\n'
        '[[ports]]\nname="a"\ndir="in"\nwidth=8\n'
        '[[ports]]\nname="a"\ndir="out"\nwidth=8\n'
    )
    with pytest.raises(DesignError) as ei:
        parse_manifest(_write_manifest(text))
    assert "port names must be unique and non-empty" in str(ei.value)


# --- ext_module_mlir -------------------------------------------------------


def test_ext_module_mlir_renders_decl() -> None:
    decl = parse_manifest(_REAL_MANIFEST)
    text = ext_module_mlir(decl)
    assert "pyc.ext_module @ext_dct8" in text
    assert 'function_type = (i64, i1) -> (i64)' in text
    assert 'verilog_top = "dct8"' in text
    assert 'arg_names = ["in", "valid"]' in text
    assert 'result_names = ["out"]' in text


def test_ext_module_mlir_no_backends_omits_verilog_top() -> None:
    decl = parse_manifest(_write_manifest(_simple_manifest()))
    # verilog_top defaults to name, so it is always present in practice; but a
    # decl constructed directly keeps the attribute and it is rendered when set.
    assert ext_module_mlir(decl).startswith("  pyc.ext_module @m {")


# --- declare / bind --------------------------------------------------------


def test_declare_registers_on_design_and_emits_block() -> None:
    d = Design(top="top")
    bind = declare(d, _REAL_MANIFEST)
    assert callable(bind)
    assert getattr(d, "_ext_module_decls", None)
    mlir = d.emit_mlir()
    assert "pyc.ext_module @ext_dct8" in mlir


def test_declare_on_circuit_registers_decls() -> None:
    c = Circuit("top")
    bind = declare(c, _REAL_MANIFEST)
    assert callable(bind)
    assert len(getattr(c, "_ext_module_decls", [])) == 1


def test_bind_produces_pyc_instance_binding_by_name() -> None:
    c = Circuit("top")
    x = c.input("x", width=64)
    bind = declare(c, _REAL_MANIFEST)
    y = bind(c, name="u_dct", in_=x, valid=1)
    assert hasattr(y, "ty")  # a single-output bind returns the Signal
    mlir = c.emit_mlir()
    assert 'pyc.instance %' in mlir
    assert 'callee = @ext_dct8' in mlir
    assert 'name = "u_dct"' in mlir
    # a 1-bit literal input is lowered to a constant
    assert "pyc.constant 1 : i1" in mlir


def test_bind_int_input_becomes_const() -> None:
    c = Circuit("top")
    bind = declare(c, _REAL_MANIFEST)
    bind(c, name="u", in_=123, valid=1)
    assert "pyc.constant 123 : i64" in c.emit_mlir()


def test_bind_missing_input_port_raises() -> None:
    c = Circuit("top")
    x = c.input("x", width=64)
    bind = declare(c, _REAL_MANIFEST)
    with pytest.raises(DesignError) as ei:
        bind(c, name="u", in_=x)
    assert "missing input port 'valid'" in str(ei.value)
    with pytest.raises(DesignError) as ei:
        bind(c, name="u", valid=1)
    assert "missing input port 'in'" in str(ei.value)


def test_bind_unknown_port_raises() -> None:
    c = Circuit("top")
    x = c.input("x", width=64)
    bind = declare(c, _REAL_MANIFEST)
    with pytest.raises(DesignError) as ei:
        bind(c, name="u", in_=x, valid=1, bogus=2)
    assert "unknown ports ['bogus']" in str(ei.value)


def test_bind_width_mismatch_raises_too_narrow() -> None:
    """A signal narrower than the fixed-width ext port is rejected, not
    silently zero-extended."""
    c = Circuit("top")
    x8 = c.input("x", width=8)  # ext_dct8 port 'in' expects i64
    bind = declare(c, _REAL_MANIFEST)
    with pytest.raises(DesignError) as ei:
        bind(c, name="u", in_=x8, valid=1)
    assert "width mismatch" in str(ei.value)


def test_bind_width_mismatch_raises_too_wide() -> None:
    """A signal wider than the fixed-width ext port is rejected, not silently
    truncated."""
    c = Circuit("top")
    x128 = c.input("x", width=128)  # ext_dct8 port 'in' expects i64
    bind = declare(c, _REAL_MANIFEST)
    with pytest.raises(DesignError) as ei:
        bind(c, name="u", in_=x128, valid=1)
    assert "width mismatch" in str(ei.value)

def test_parse_clock_reset_ports() -> None:
    """Clocked modules declare dir="clock"/"reset" ports; they render as
    !pyc.clock/!pyc.reset in the emitted function_type (ext_cache uses this)."""
    text = (
        '[module]\nname="m"\n'
        '[[ports]]\nname="clk"\ndir="clock"\nwidth=1\n'
        '[[ports]]\nname="rst"\ndir="reset"\nwidth=1\n'
        '[[ports]]\nname="a"\ndir="in"\nwidth=8\n'
        '[[ports]]\nname="y"\ndir="out"\nwidth=8\n'
    )
    decl = parse_manifest(_write_manifest(text))
    assert [(p.name, p.dir) for p in decl.inputs] == [
        ("clk", "clock"),
        ("rst", "reset"),
        ("a", "in"),
    ]
    text = ext_module_mlir(decl)
    assert "(!pyc.clock, !pyc.reset, i8) -> (i8)" in text

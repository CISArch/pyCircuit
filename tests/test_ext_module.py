"""Front-end gates for external black-box modules (pyc.ext_module / pyc.instance).

Pure front-end: no pycc needed. Dual-backend emission/simulation lives in
designs/examples/ext_dct8 (docs/external-modules.md).
"""

from __future__ import annotations

import re
from pathlib import Path

import pytest

from pycircuit import Circuit
from pycircuit.design import Design, DesignError
from pycircuit.ext import ext_module_mlir, instance, parse_manifest

_MANIFEST = (
    Path(__file__).resolve().parents[1] / "designs/examples/ext_dct8/ext/ext_dct8.toml"
)


def _write(tmp_path: Path, text: str) -> Path:
    p = tmp_path / "m.toml"
    p.write_text(text)
    return p


def _simple(name: str = "m") -> str:
    return (
        f'[module]\nname = "{name}"\n'
        '[[ports]]\nname = "a"\ndir = "in"\nwidth = 8\n'
        '[[ports]]\nname = "y"\ndir = "out"\nwidth = 8\n'
    )


def test_parse_example_manifest() -> None:
    decl = parse_manifest(_MANIFEST)
    assert decl.name == "ext_dct8"
    assert decl.verilog_top == "dct8"  # [backends.verilog].top
    assert [(p.name, p.width) for p in decl.inputs] == [("in", 64), ("valid", 1)]
    assert [(p.name, p.width) for p in decl.outputs] == [("out", 64)]


def test_parse_minimal_defaults_verilog_top(tmp_path: Path) -> None:
    decl = parse_manifest(_write(tmp_path, _simple()))
    assert decl.name == "m" and decl.verilog_top == "m"


@pytest.mark.parametrize(
    "text, needle",
    [
        ("[bogus]\nx = 1\n", "missing [module] table"),
        ('[module]\nname = ""\n', "[module] name must be non-empty"),
        ('[module]\nname = "m"\n', "at least one [[ports]] entry"),
        (
            '[module]\nname = "m"\n[[ports]]\nname = "a"\ndir = "bidir"\nwidth = 8\n',
            'dir must be "in", "out", "clock" or "reset"',
        ),
        (
            '[module]\nname = "m"\n[[ports]]\nname = "a"\ndir = "in"\nwidth = 0\n',
            "width must be in 1..4096",
        ),
        (
            '[module]\nname = "m"\n[[ports]]\nname = "a"\ndir = "in"\nwidth = "abc"\n',
            "width must be an integer",
        ),
        (_simple() + '[backends.cpp]\nheader = "other.hpp"\n', "header must be m.hpp"),
    ],
)
def test_parse_manifest_errors(tmp_path: Path, text: str, needle: str) -> None:
    with pytest.raises(DesignError, match=re.escape(needle)):
        parse_manifest(_write(tmp_path, text))


def test_clock_reset_ports_render_domain_types(tmp_path: Path) -> None:
    text = (
        '[module]\nname = "m"\n'
        '[[ports]]\nname = "clk"\ndir = "clock"\nwidth = 1\n'
        '[[ports]]\nname = "rst"\ndir = "reset"\nwidth = 1\n'
        '[[ports]]\nname = "a"\ndir = "in"\nwidth = 8\n'
        '[[ports]]\nname = "y"\ndir = "out"\nwidth = 8\n'
    )
    decl = parse_manifest(_write(tmp_path, text))
    assert [p.dir for p in decl.inputs] == ["clock", "reset", "in"]
    assert "(!pyc.clock, !pyc.reset, i8) -> (i8)" in ext_module_mlir(decl)


def test_ext_module_mlir_renders_decl() -> None:
    text = ext_module_mlir(parse_manifest(_MANIFEST))
    assert text.startswith("  pyc.ext_module @ext_dct8 {")
    assert "function_type = (i64, i1) -> (i64)" in text
    assert text.rstrip().endswith(": (i64, i1) -> (i64)")
    assert 'verilog_top = "dct8"' in text
    assert 'arg_names = ["in", "valid"]' in text
    assert 'result_names = ["out"]' in text


def test_instance_registers_and_instantiates() -> None:
    c = Circuit("top")
    x = c.input("x", width=64)
    y = instance(c, _MANIFEST, name="u_dct", in_=x, valid=1)  # in_ -> port "in"
    assert str(y.ty) == "i64"  # single output returns a Signal
    instance(c, _MANIFEST, name="u_dct2", in_=123, valid=0)
    assert len(c._ext_module_decls) == 1  # same manifest is registered once
    mlir = c.emit_mlir()
    assert "callee = @ext_dct8" in mlir
    assert 'name = "u_dct"' in mlir
    assert "pyc.constant 1 : i1" in mlir  # int port inputs lower to constants
    assert "pyc.constant 123 : i64" in mlir


def test_instance_port_errors() -> None:
    c = Circuit("top")
    x = c.input("x", width=64)
    with pytest.raises(DesignError, match="missing input port 'valid'"):
        instance(c, _MANIFEST, name="u", in_=x)
    with pytest.raises(DesignError, match=re.escape("unknown ports ['bogus']")):
        instance(c, _MANIFEST, name="u", in_=x, valid=1, bogus=2)


def test_design_emit_mlir_includes_declaration() -> None:
    d = Design(top="top")
    d._ext_module_decls = [parse_manifest(_MANIFEST)]  # what cli.py propagates
    assert "pyc.ext_module @ext_dct8" in d.emit_mlir()

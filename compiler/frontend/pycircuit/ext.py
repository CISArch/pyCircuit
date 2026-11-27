"""External black-box modules (pyc.ext_module); see docs/external-modules.md.

Requires Python >= 3.11 (tomllib).
"""

from __future__ import annotations

try:
    import tomllib
except ModuleNotFoundError:  # Python 3.10: no stdlib TOML reader.
    tomllib = None  # type: ignore[assignment]
from dataclasses import dataclass
from pathlib import Path
from typing import Any, Iterable

from .data import Data
from .design import DesignError
from .hw import Signal, Wire


@dataclass(frozen=True)
class ExtPort:
    name: str
    dir: str  # "in" | "out" | "clock" | "reset"
    width: int


@dataclass(frozen=True)
class ExtModuleDecl:
    name: str
    inputs: tuple[ExtPort, ...]
    outputs: tuple[ExtPort, ...]
    verilog_top: str
    cpp_files: tuple[str, ...] = ()
    cpp_header: str = ""


def parse_manifest(path: str | Path) -> ExtModuleDecl:
    """Parse and validate an external-module TOML manifest."""
    if tomllib is None:
        raise DesignError("pycircuit.ext requires Python >= 3.11 (tomllib)")
    p = Path(path)
    raw = tomllib.loads(p.read_text(encoding="utf-8"))
    mod = raw.get("module")
    if not isinstance(mod, dict):
        raise DesignError(f"{p}: missing [module] table")
    name = str(mod.get("name", "")).strip()
    if not name:
        raise DesignError(f"{p}: [module] name must be non-empty")
    entries = raw.get("ports")
    if not isinstance(entries, list) or not entries:
        raise DesignError(f"{p}: at least one [[ports]] entry is required")
    ins: list[ExtPort] = []
    outs: list[ExtPort] = []
    for e in entries:
        pname, pdir = str(e.get("name", "")).strip(), str(e.get("dir", "")).strip()
        try:
            width = int(e.get("width", 0))
        except (TypeError, ValueError):
            raise DesignError(f"{p}: port {pname!r} width must be an integer") from None
        if not pname or any(q.name == pname for q in ins + outs):
            raise DesignError(f"{p}: port names must be unique and non-empty (got {pname!r})")
        if pdir not in ("in", "out", "clock", "reset"):
            raise DesignError(f'{p}: port {pname!r} dir must be "in", "out", "clock" or "reset"')
        if not 1 <= width <= 4096:
            raise DesignError(f"{p}: port {pname!r} width must be in 1..4096")
        (outs if pdir == "out" else ins).append(ExtPort(pname, pdir, width))
    backends = raw.get("backends") or {}
    cpp = backends.get("cpp") or {}
    files = tuple(map(str, cpp.get("files") or ())) if str(cpp.get("type", "source")) == "source" else ()
    header = str(cpp.get("header") or "")
    if header and Path(header).name != f"{name}.hpp":
        raise DesignError(f"{p}: [backends.cpp].header must be {name}.hpp (the C++ include name is fixed)")
    top = str((backends.get("verilog") or {}).get("top") or "").strip() or name
    return ExtModuleDecl(name, tuple(ins), tuple(outs), top, files, header)


def _mlir_str(s: str) -> str:
    return '"' + s.replace("\\", "\\\\").replace('"', '\\"') + '"'


def ext_module_mlir(decl: ExtModuleDecl) -> str:
    """Render the pyc.ext_module symbol declaration line."""

    def tys(ports: tuple[ExtPort, ...]) -> str:
        return ", ".join(f"!pyc.{p.dir}" if p.dir in ("clock", "reset") else f"i{p.width}" for p in ports)

    ft = f"({tys(decl.inputs)}) -> ({tys(decl.outputs)})"
    attrs = [f"function_type = {ft}", f"verilog_top = {_mlir_str(decl.verilog_top)}"]
    if decl.inputs:
        attrs.append("arg_names = [" + ", ".join(_mlir_str(p.name) for p in decl.inputs) + "]")
    if decl.outputs:
        attrs.append("result_names = [" + ", ".join(_mlir_str(p.name) for p in decl.outputs) + "]")
    return f"  pyc.ext_module @{decl.name} {{{', '.join(attrs)}}} : {ft}\n"


def instance(circuit: Any, manifest: str | Path, *, name: str, **ports: Any) -> Signal | list[Signal]:
    """Register the manifest declaration on circuit and emit one pyc.instance."""
    decl = parse_manifest(manifest)
    decls = getattr(circuit, "_ext_module_decls", None)
    if decls is None:
        circuit._ext_module_decls = decls = []
    if all(d.name != decl.name for d in decls):
        decls.append(decl)
    design = getattr(getattr(circuit, "_design_ctx", None), "design", None)
    if design is not None:  # JIT path: the caller only gets the Design back
        design._ext_module_decls = decls

    operands: list[Any] = []
    for port in decl.inputs:
        for key in (port.name, port.name + "_"):
            if key in ports:
                value = ports.pop(key)
                break
        else:
            raise DesignError(f"ext module {decl.name}: missing input port {port.name!r}")
        if isinstance(value, int):
            value = circuit.const(value, width=port.width)
        operands.append(value.sig if isinstance(value, Wire) else value)
    if ports:
        raise DesignError(f"ext module {decl.name}: unknown ports {sorted(ports)}")

    result_types = [Data.from_str(f"i{p.width}") for p in decl.outputs]
    outs = circuit.instance_op(decl.name, *operands, result_types=result_types, name=str(name))
    return outs[0] if len(outs) == 1 else outs


def discover_cpp_sources(roots: Iterable[str | Path]) -> tuple[list[Path], list[Path]]:
    """Collect [backends.cpp] sources and header dirs of ext manifests under roots."""
    sources: list[Path] = []
    include_dirs: list[Path] = []
    for root in (Path(r) for r in roots):
        if not root.is_dir():
            continue
        for manifest in sorted(root.rglob("*.toml")):
            try:
                decl = parse_manifest(manifest)
            except Exception:  # noqa: BLE001 - non-ext/unparsable TOML files are skipped
                continue
            for rel in decl.cpp_files:
                p = (manifest.parent / rel).resolve()
                if p.is_file() and p not in sources:
                    sources.append(p)
            if decl.cpp_header:
                d = (manifest.parent / decl.cpp_header).resolve().parent
                if d.is_dir() and d not in include_dirs:
                    include_dirs.append(d)
    return sources, include_dirs

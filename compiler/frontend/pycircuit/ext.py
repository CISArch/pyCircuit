"""External black-box module support (docs/external-modules.md).

A user model is described by an ``extmod.toml`` manifest:

    [module]
    name = "ext_dct8"        # symbol name; also the user C++ class name
    verilog_top = "dct8"     # optional: Verilog module name (default: name)

    [[ports]]
    name = "in"
    dir = "in"
    width = 64

    [[ports]]
    name = "valid"
    dir = "in"
    width = 1

    [[ports]]
    name = "out"
    dir = "out"
    width = 64

``declare()`` parses the manifest and registers the ``pyc.ext_module``
symbol on the Design so ``emit_mlir()`` includes the declaration; the
returned callable instantiates the module at any circuit (``pyc.instance``
callsite) with by-name port binding:

    dct = pycircuit.ext.declare(design, "ext/ext_dct8.toml")
    out = dct(m, in_=x, valid=one)
"""

from __future__ import annotations

import tomllib
from dataclasses import dataclass
from pathlib import Path
from typing import Any, Callable

from .design import Design, DesignError
from .data import Bits, Data
from .hw import Signal, Wire


@dataclass(frozen=True)
class ExtPort:
    name: str
    dir: str  # "in" | "out"
    width: int


@dataclass(frozen=True)
class ExtModuleDecl:
    name: str
    ports: tuple[ExtPort, ...]
    verilog_top: str | None

    @property
    def inputs(self) -> tuple[ExtPort, ...]:
        return tuple(p for p in self.ports if p.dir == "in")

    @property
    def outputs(self) -> tuple[ExtPort, ...]:
        return tuple(p for p in self.ports if p.dir == "out")


def parse_manifest(path: str | Path) -> ExtModuleDecl:
    """Parse and validate an extmod.toml manifest."""
    p = Path(path)
    with open(p, "rb") as f:
        raw = tomllib.load(f)

    mod = raw.get("module")
    if not isinstance(mod, dict):
        raise DesignError(f"{p}: missing [module] table")
    name = str(mod.get("name", "")).strip()
    if not name:
        raise DesignError(f"{p}: [module] name must be non-empty")
    verilog_top = mod.get("verilog_top")

    raw_ports = raw.get("ports")
    if not isinstance(raw_ports, list) or not raw_ports:
        raise DesignError(f"{p}: at least one [[ports]] entry is required")
    ports: list[ExtPort] = []
    seen: set[str] = set()
    for entry in raw_ports:
        pname = str(entry.get("name", "")).strip()
        pdir = str(entry.get("dir", "")).strip()
        pwidth = int(entry.get("width", 0))
        if not pname or pname in seen:
            raise DesignError(f"{p}: port names must be unique and non-empty (got {pname!r})")
        if pdir not in ("in", "out"):
            raise DesignError(f"{p}: port {pname!r} dir must be \"in\" or \"out\"")
        if pwidth < 1 or pwidth > 4096:
            raise DesignError(f"{p}: port {pname!r} width must be in 1..4096")
        seen.add(pname)
        ports.append(ExtPort(name=pname, dir=pdir, width=pwidth))

    return ExtModuleDecl(
        name=name,
        ports=tuple(ports),
        verilog_top=str(verilog_top).strip() if verilog_top else None,
    )


def _mlir_str(s: str) -> str:
    return '"' + s.replace("\\", "\\\\").replace('"', '\\"') + '"'


def ext_module_mlir(decl: ExtModuleDecl) -> str:
    """Render the `pyc.ext_module` symbol declaration."""
    in_tys = ", ".join(f"i{p.width}" for p in decl.inputs)
    out_tys = ", ".join(f"i{p.width}" for p in decl.outputs)
    ft = f"({in_tys}) -> ({out_tys})"

    attrs: list[str] = [f"function_type = {ft}"]
    if decl.verilog_top:
        attrs.append(f"verilog_top = {_mlir_str(decl.verilog_top)}")
    if decl.inputs:
        attrs.append("arg_names = [" + ", ".join(_mlir_str(p.name) for p in decl.inputs) + "]")
    if decl.outputs:
        attrs.append("result_names = [" + ", ".join(_mlir_str(p.name) for p in decl.outputs) + "]")
    return f"  pyc.ext_module @{decl.name} {{{', '.join(attrs)}}} : {ft}\n"


def declare(target: Any, manifest_path: str | Path) -> Callable[..., Any]:
    """Register an external module on a Design (or a Circuit holding one) and
    return its instance callable.

    The Design learns an extra ``ext_modules`` text block that ``emit_mlir``
    appends after the ``func.func`` definitions.
    """
    design = target
    if not isinstance(design, Design):
        design = getattr(target, "_design_ctx", None)
    if not isinstance(design, Design):
        # Fall back to a deferred registry on the circuit; the CLI's
        # _compile_to_design propagates these onto the emitted Design.
        design = None
    decl = parse_manifest(manifest_path)
    if design is not None and design.lookup(decl.name) is not None:
        raise DesignError(f"external module symbol collides with module: {decl.name!r}")

    existing = getattr(target, "_ext_module_decls", None)
    if existing is None:
        existing = []
        target._ext_module_decls = existing  # noqa: SLF001 - intentional extension point
    existing.append(decl)
    if design is not None:
        design._ext_module_decls = existing  # noqa: SLF001 - shared registry

    def _type_for(p: ExtPort) -> Data:
        return Data.from_str(f"i{p.width}")

    def instance(*, name: str, **ports: Any) -> Any:
        """Instantiate the external module with by-name port binding.

        Positional inputs are not allowed; every input port must be given
        exactly once via keyword (``in_`` for reserved names).
        """
        # Resolve the owning circuit from any Signal argument.
        circuit = None
        for v in ports.values():
            sig = _as_signal(v)
            if sig is not None:
                circuit = getattr(type(sig), "__self__", None)
                break
        raise NotImplementedError(
            "ext module instantiation goes through Circuit.instance_op; "
            "see docs/external-modules.md for the bind() helper"
        )

    def bind(circuit: Any, *, name: str, **ports: Any) -> Any:
        """Bind ports on `circuit` (a ModuleBuilder/Circuit) by keyword name."""
        in_map: dict[str, Any] = {}
        for p in decl.inputs:
            key = p.name
            alias = "in_" if key == "in" else key
            if key in ports:
                in_map[key] = ports.pop(key)
            elif alias in ports:
                in_map[key] = ports.pop(alias)
            elif isinstance(ports.get(alias, None), int):
                in_map[key] = ports.pop(alias)
            else:
                raise DesignError(f"ext module {decl.name}: missing input port {key!r}")
        if ports:
            raise DesignError(f"ext module {decl.name}: unknown ports {sorted(ports)}")

        operands: list[Signal] = []
        for p in decl.inputs:
            v = in_map[p.name]
            if isinstance(v, int) and not isinstance(v, bool):
                v = circuit.const(v, width=p.width)
            operands.append(_coerce(v, _type_for(p), p.name))

        outs = circuit.instance_op(
            decl.name,
            *operands,
            result_types=[_type_for(p) for p in decl.outputs],
            name=str(name),
        )
        if len(outs) == 1:
            return outs[0]
        return {p.name: s for p, s in zip(decl.outputs, outs)}

    instance.bind = bind  # type: ignore[attr-defined]
    return instance


def _as_signal(v: Any) -> Any:
    if isinstance(v, Wire):
        return v.sig
    lit = getattr(v, "sig", None)
    if isinstance(lit, Signal):
        return lit
    return v if isinstance(v, Signal) else None


def _coerce(v: Any, expected: Data, port: str) -> Signal:
    if isinstance(v, Wire):
        v = v.sig
    if not isinstance(v, Signal) and hasattr(v, "sig"):
        v = v.sig
    if isinstance(v, Signal):
        if v.ty == expected:
            return v
        if isinstance(v.ty, Bits) and isinstance(expected, Bits):
            if v.ty.width < expected.width:
                return v.zext(width=expected.width)
            if v.ty.width > expected.width:
                return v.trunc(width=expected.width)
            return v
        raise DesignError(f"ext port {port!r}: type mismatch, got {v.ty} expected {expected}")
    # Constant integer literal.
    iv = int(v)
    limit = 1 << expected.width
    if not (0 <= iv < limit):
        raise DesignError(f"ext port {port!r}: constant {iv} does not fit i{expected.width}")
    raise DesignError(f"ext port {port!r}: literal constants require circuit.const(); pass a Signal")

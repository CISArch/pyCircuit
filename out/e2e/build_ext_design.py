"""End-to-end driver: declare ext_dct8 via manifest, build a design, emit MLIR."""
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[2] / "compiler" / "frontend"))
sys.path.insert(0, str(Path(__file__).resolve().parents[2] / "designs" / "examples" / "ext_dct8"))

from pycircuit.design import Design
from pycircuit import ext as extmod
from pycircuit.v5 import compile_cycle_aware

design = Design(top="top")

dct = extmod.declare(design, Path(__file__).resolve().parents[2] / "designs" / "examples" / "ext_dct8" / "ext" / "ext_dct8.toml")

def build(m, domain):
    x = m.input("x", width=64)
    one = m.const(1, width=1)
    y = dct.bind(m, name="u_dct", in_=x, valid=one)
    m.output("y", y)

result = compile_cycle_aware(build, name="top", eager=True, design_ctx=design)

# Splice ext_module declarations into the emitted MLIR.
mlir = result.emit_mlir()
ext_block = "".join(extmod.ext_module_mlir(d) for d in design._ext_module_decls)
idx = mlir.rfind("}")
mlir = mlir[:idx] + ext_block + mlir[idx:]

out = Path(__file__).resolve().parent / "ext_design.mlir"
out.write_text(mlir)
print("wrote", out)

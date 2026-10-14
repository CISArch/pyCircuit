# External Black-Box Modules (User-Provided Verilog / C++ Models)

外部自定义模块接口：用户以一份 TOML 清单 + 自有的 Verilog / C++ 仿真代码接入
pyCircuit 的编译、优化与双后端仿真链路。IR 中外部模块以 `pyc.ext_module` 符号
声明，调用点复用 `pyc.instance`（callee 指向 ext 符号）。

## 1. 接口契约

### 1.1 清单文件（`*.toml`，随设计存放）

```toml
[module]
name = "ext_dct8"        # 全局唯一符号名（不得与任何 func 同名）
kind = "comb"            # comb | seq
latency = 0              # comb 必须 0；seq >= 1（调度注解，见 §3）
pure = true              # comb 必须为 true
verilog_top = "dct8"     # 可选：Verilog module 名（默认 = name）

[[ports]]                # 顺序即端口顺序；name/dir/width 必填
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

[module.seq]             # 仅 kind="seq" 需要
clock = "clk"            # 必须引用已声明端口
reset = "rst"
init = ["0"]             # 每个 out 端口一个复位值

[backends.verilog]       # Verilog/Verilator 后端
files = ["ext/dct8.v"]   # 相对示例根目录

[backends.cpp]           # C++ 后端
type = "source"          # source（推荐）：源文件直接进仿真器链接
files = ["ext/dct8.cpp"]
symbol_prefix = "ext_dct8"

[backends.golden]        # 可选：Python 参考模型（自检用）
type = "python"
entry = "ext.dct8_ref:dct8"
```

### 1.2 MLIR 形态

```mlir
pyc.ext_module @ext_dct8 {function_type = (i64, i1) -> (i64),
    ext_kind = "comb", latency = 0, pure = true,
    verilog_top = "dct8",
    arg_names = ["in", "valid"], result_names = ["out"]} : (i64, i1) -> (i64)

%y = pyc.instance %x, %v {callee = @ext_dct8, name = "u_dct"} : (i64, i1) -> i64
```

Verifier 约束（gate-first，`PYCOps.cpp`）：
- `ext_kind` ∈ {comb, seq}；comb ⇒ latency=0 且 pure=true 且无 clock/reset；
- seq ⇒ latency≥1 且必须声明 clock/reset；`arg_names`/`result_names`/`init`
  与签名 arity 匹配。
- `pyc.instance` callee 可指向 `func.func` 或 `pyc.ext_module`，类型必须一致。

### 1.3 C ABI（`runtime/cpp/pyc_ext.hpp`）

```c
// comb（state 恒为 nullptr，当拍出结果）：
void <prefix>_eval(void *state, uint64_t *outs, const uint64_t *ins,
                   uint64_t cycle);
// seq（每拍 tick 相位调用一次；模块自管流水状态）：
void   <prefix>_eval(void *state, uint64_t *outs, const uint64_t *ins,
                     uint64_t cycle);
size_t <prefix>_state_size();                    // 可选
void   <prefix>_reset(void *state, const uint64_t *init); // 可选
```

端口按位宽展平到 64 位字、小端序（<64 位零扩展）。`outs`/`ins` 用
`ctx.outs.data()` / `ctx.ins.data()` 传入。

## 2. 双后端语义

- **C++**：`[backends.cpp] type="source"` 的源文件由 `pycircuit build` 自动
  发现并追加进仿真器链接（`cpp_project_manifest.json` 的 `ext_sources`，
  `flows/tools/gen_cmake_from_manifest.py` 消费）。生成代码在 comb 求值点
  **直接调用** `<prefix>_eval`——全部计算来自用户代码。
- **Verilog**：`pyc.instance`→ext 符号发射为 Verilog 实例化（模块名 =
  `verilog_top`，端口按 `arg_names`/`result_names` 绑定）；用户 `.v` 文件
  加入 Verilator 源列表（`verilator_manifest.json`）。

## 3. latency 的语义（调度注解，不是调用方式）

用户代码每拍都被真实调用；`latency` 只告诉 change-driven 调度器输出在
第几拍生效：
- comb（latency=0）：输出与输入同拍，CombDepGraph 按"依赖全部输入、深度+1"
  的黑盒叶节点处理（Decision 0134/0135 的合法切点）；
- seq（latency=L）：`_eval` 在 tick 相位调用，输出 L 拍后对下游可见，
  唤醒事件按 delay-line 同款机制注册。

分析边界：`pyc-flatten-instances`/`InlineFunctions` 不内联 ext 符号；
`CheckCombCycles`/`CheckLogicDepth`/`CheckClockDomains` 在 ext 边界停止传播
（黑盒内部不可见）。

## 4. 前端接入

```python
from pycircuit import ext as extmod

def build(m, domain):
    dct = extmod.declare(m, manifest_path)   # 注册 ext_module 符号
    y = dct.bind(m, name="u_dct", in_=x, valid=1)   # 按名绑端口
    m.output("y", y)
```

`declare` 接受 Design 或 Circuit（CLI build 流程会自动把声明传播进
`design.pyc` 与逐模块 `.pyc`）。

## 5. 完整示例

`designs/examples/ext_dct8/`：`ext_dct8.py`（设计）、`ext/ext_dct8.toml`
（清单）、`ext/dct8.v` + `ext/dct8.cpp`（同一参考算法的双语言实现）、
`ext/dct8_ref.py`（golden）、`tb_ext_dct8.py`（4 向量 expect 校验）。

```bash
# C++ 后端（链接用户 dct8.cpp，直呼 ABI）
PYTHONPATH=compiler/frontend PYC_TOOLCHAIN_ROOT=.pycircuit_out/toolchain/install \
  python3 -m pycircuit.cli build designs/examples/ext_dct8/tb_ext_dct8.py \
  --out-dir out/sim --target cpp --jobs 4
out/sim/cpp_build/build/pyc_tb   # → OK

# Verilator 后端（实例化用户 dct8.v；用户 .v 需加入 verilator_manifest.json sources）
```

两个后端对同一 trace 均输出 `OK`（功能一致）。

# External Black-Box Modules (User-Provided Verilog / C++ Models)

外部自定义模块接口：用户以一份 TOML 清单 + 自有的 Verilog / C++ 仿真代码接入
pyCircuit 的编译、优化与双后端仿真链路。IR 中外部模块以 `pyc.ext_module` 符号
声明，调用点复用 `pyc.instance`（callee 指向 ext 符号）。

## 1. 接口契约

### 1.1 清单文件（`*.toml`，随设计存放）

```toml
[module]
name = "ext_dct8"        # 全局唯一符号名（不得与任何 func 同名；也是用户 C++ 类名）

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

[backends.verilog]       # Verilog/Verilator 后端
files = ["ext/dct8.v"]   # 相对示例根目录
top = "dct8"             # 可选：Verilog module 名（默认 = name）

[backends.cpp]           # C++ 后端
type = "source"          # source（推荐）：源文件直接进仿真器链接
files = ["ext/dct8.cpp"]
header = "ext_dct8.hpp"  # 用户类：端口成员 + eval()（见 §1.3）
```

### 1.2 MLIR 形态

```mlir
pyc.ext_module @ext_dct8 {function_type = (i64, i1) -> (i64),
    arg_names = ["in", "valid"], result_names = ["out"]} : (i64, i1) -> (i64)

%y = pyc.instance %x, %v {callee = @ext_dct8, name = "u_dct"} : (i64, i1) -> i64
```

Verifier 约束（gate-first，`PYCOps.cpp`）：
- `arg_names`/`result_names` 与签名 arity 匹配。
- `pyc.instance` callee 可指向 `func.func` 或 `pyc.ext_module`，类型必须一致。

### 1.3 C++ 类绑定（`runtime/cpp/pyc_ext.hpp`）

ext 模块按 **instance 级**处理：与内部子模块完全同款的 `unique_ptr` 子对象 +
输入缓存 + eval 调用 + 输出变化唤醒。区别仅在子对象的类型由用户提供——
`[backends.cpp] header` 指向的头文件必须定义与 `module.name` 同名的类：

```cpp
struct ext_dct8 {                       // 类名 = module name
  pyc::cpp::Wire<64> in;                // 每个清单端口一个 Wire<width> 成员
  pyc::cpp::Wire<1>  valid;
  pyc::cpp::Wire<64> out;
  void eval() { out = compute(in, valid); }   // 必须提供
  // 可选：void tick_compute(); void tick_commit();
  //   两者都提供 ⇒ 实例进入 tick 相位（有状态模块，step() 语义正确）。
  // 可选：pyc_trace_vcd(...) / pyc_register_probes(...)
  //   与生成 SimObjects 同签名 ⇒ 自动接入 VCD trace 与 probe 注册。
};
```

编译器把黑盒当普通子 SimObject 对待（直接 `member->eval()`），只是从不
打开类体；可选能力经 `pyc::cpp::has_tick` 等 trait 在 C++17 下降级为空操作。

## 2. 双后端语义

- **C++**：`[backends.cpp]` 的源文件与头文件目录由 `pycircuit build` 自动
  发现并追加进仿真器链接/包含路径（`cpp_project_manifest.json` 的
  `ext_sources`，`flows/tools/gen_cmake_from_manifest.py` 消费）。生成代码
  走内部 instance 同款路径：`u_dct->in = x; u_dct->eval();`——全部计算来自
  用户代码，黑盒语义体现为编译器从不打开类体。
- **Verilog**：`pyc.instance`→ext 符号发射为 Verilog 实例化（模块名 =
  `[backends.verilog].top`（默认 = name），端口按 `arg_names`/`result_names` 绑定）；用户 `.v` 文件
  加入 Verilator 源列表（`verilator_manifest.json`）。

## 3. 调度语义

ext 实例是父模块 change-driven 调度图里的一个普通节点（有
`pyc.change_schedule.rank/slot/fanout` 属性）：输入指纹缓存 → 变化才调用
`eval()` → 输出变化才唤醒下游。组合边界按 "依赖全部输入、深度 +1" 处理
（Decision 0134/0135 的合法切点）。多拍延迟模块在自己的 `tick_commit()`
内部状态里实现流水，行为正确；当前不做基于声明的提前唤醒优化。

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
`tb_ext_dct8.py`（4 向量 expect 校验，期望值内嵌于 tb）。

```bash
# C++ 后端（链接用户 dct8.cpp，直呼 ABI）
PYTHONPATH=compiler/frontend PYC_TOOLCHAIN_ROOT=.pycircuit_out/toolchain/install \
  python3 -m pycircuit.cli build designs/examples/ext_dct8/tb_ext_dct8.py \
  --out-dir out/sim --target cpp --jobs 4
out/sim/cpp_build/build/pyc_tb   # → OK

# Verilator 后端（实例化用户 dct8.v；用户 .v 需加入 verilator_manifest.json sources）
```

两个后端对同一 trace 均输出 `OK`（功能一致）。

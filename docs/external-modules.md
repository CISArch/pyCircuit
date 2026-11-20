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
top = "dct8"             # 可选：Verilog module 名（默认 = name）
# 注意：本 PR 的 Verilog 后端尚不会自动把用户 .v 加入 Verilator 源列表，
# 需要用户手动填写（见 §2）。

[backends.cpp]           # C++ 后端
type = "source"          # source（推荐）：源文件直接进仿真器链接
files = ["ext/dct8.cpp"]
header = "ext_dct8.hpp"  # 见 §1.3：头文件名必须等于 module.name + ".hpp"
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

ext 模块按 **instance 级**处理：与内部子模块同款 `unique_ptr` 子对象 +
输入缓存 + eval 调用 + 输出变化唤醒，区别仅在子对象类型由用户提供。头文件名
必须等于 `module.name + ".hpp"`（CppEmitter 硬编码 `#include "<symbol>.hpp"`，
`header` 字段仅用于把它所在目录加进 include_dirs）：

```cpp
struct ext_dct8 {                       // 类名 = module name
  pyc::cpp::Wire<64> in;                // 每个清单端口一个 Wire<width> 成员
  pyc::cpp::Wire<1>  valid;
  pyc::cpp::Wire<64> out;
  void eval() { out = compute(in, valid); }
  void tick_compute() {}                // 顺序相位 1（无状态模块给空体）
  void tick_commit() {}                 // 顺序相位 2
  template <class TbT, class EnabledInstT, class EnabledSigT>
  void pyc_trace_vcd(TbT &tb, const std::string &prefix,
                     EnabledInstT &&, EnabledSigT &&enabledSig);  // VCD trace
  void pyc_register_probes(pyc::cpp::ProbeRegistry &reg,
                           const std::string &prefix);            // probe 注册
};
```

**五个成员全部是硬性合同**：生成的仿真器经 `pyc::cpp::ext_tick_compute` 等包装
直调它们，缺任何一个都会在生成模型编译期报错（无 trait 探测、无静默降级）。
无状态模块给空的 tick 体即可；trace/probe 也可为空体。有状态模块在
`tick_compute()/tick_commit()` 内实现自己的流水状态（step() 语义正确）。

编译器把黑盒当普通子 SimObject 对待（直接 `member->eval()`），只是从不打开
类体。

## 2. 双后端语义

- **C++**：`[backends.cpp]` 的源文件与头文件目录由 `pycircuit build` 自动发现并
  追加进仿真器链接/包含路径（`cpp_project_manifest.json` 的 `ext_sources`，
  `flows/tools/gen_cmake_from_manifest.py` 消费）。生成代码走内部 instance 同款
  路径：`u_dct->in = x; u_dct->eval();`——全部计算来自用户代码。
- **Verilog**：`pyc.instance`→ext 符号发射为 Verilog 实例化（模块名 =
  `[backends.verilog].top`（默认 = name），端口按 `arg_names`/`result_names` 绑定）。
  **用户 `.v` 文件不会被自动加入 `verilator_manifest.json` sources**，须手动补上，
  否则 Verilator 编译会因模块未定义而失败。

## 3. 调度语义

ext 实例是父模块 change-driven 调度图里的一个普通节点（有
`pyc.change_schedule.rank/slot/fanout` 属性）：输入指纹缓存 → 变化才调用
`eval()` → 输出变化才唤醒下游。组合边界按 "依赖全部输入、深度 +1" 处理
（Decision 0134/0135 的合法切点）。多拍延迟模块在自己的 `tick_commit()`
内部状态里实现流水，行为正确；当前不做基于声明的提前唤醒优化。

**有状态 ext 与 eval 缓存**：ext 实例的输出会因内部状态推进而变化（输入
不变），因此每次 `tick_commit` 后生成代码强制失效该实例的 eval 指纹缓存，
下一拍必定重调 `eval()`——不要依赖"输入没变输出就不变"的纯组合假设。

**时钟模块**：`dir = "clock"` / `dir = "reset"` 端口（width=1）绑定 domain
的 clk/rst，两个后端都会连上（Verilog 按端口名接顶层 net；C++ 赋给同名
Wire 成员）。运行时每周期在 posedge 与 negedge 各调一次 `tick_commit()`，
时钟模块必须在 `tick_commit()` 内部自己门控：记录上次 clk 值，仅在 0→1
跳变时推进状态（参考 `designs/examples/ext_cache/ext/ext_cache.hpp`）。
`rst` 按同步复位处理。

分析边界：`pyc-flatten-instances`/`InlineFunctions` 不内联 ext 符号；
`CheckCombCycles`/`CheckLogicDepth`/`CheckClockDomains` 在 ext 边界停止传播
（黑盒内部不可见）。

## 4. 前端接入

```python
from pycircuit import ext as extmod

def build(m, domain):
    dct = extmod.declare(m, manifest_path)   # 注册 ext_module 符号，返回绑端口函数
    y = dct(m, name="u_dct", in_=x, valid=1)   # 以 circuit 为首参，按名绑端口
    m.output("y", y)
```

`declare` 接受 Design 或 Circuit（CLI build 流程会自动把声明传播进
`design.pyc` 与逐模块 `.pyc`）。返回的实例函数以 circuit 为首个位置参数，
其余端口用关键字绑定（`in_` 映射到名为 `in` 的端口）。

## 5. 完整示例

`designs/examples/ext_dct8/`：`ext_dct8.py`（设计）、`ext/ext_dct8.toml`
（清单）、`ext/dct8.v` + `ext/dct8.cpp`（同一参考算法的双语言实现）、
`tb_ext_dct8.py`（4 向量 expect 校验，期望值内嵌于 tb）。

```bash
# C++ 后端（链接用户 dct8.cpp）
PYTHONPATH=compiler/frontend PYC_TOOLCHAIN_ROOT=.pycircuit_out/toolchain/install \
  python3 -m pycircuit.cli build designs/examples/ext_dct8/tb_ext_dct8.py \
  --out-dir out/sim --target cpp --jobs 4
out/sim/cpp_build/build/pyc_tb   # → OK

# Verilator 后端：用 --target verilator 生成后，需手动把 ext/dct8.v 加入
# verilator_manifest.json 的 sources，才能正确实例化 module dct8。
```

（C++ 后端已实测 OK；Verilog 后端受上述 `.v` 手动接入限制，需补源后再验证。）
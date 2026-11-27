# 外接黑盒模块（ext_module）

用户以 TOML 清单 + 自有 C++/Verilog 代码接入 pyCircuit：IR 用 `pyc.ext_module` 声明
符号，实例化复用 `pyc.instance`（callee 指向该符号）。

## 清单

```toml
[module]
name = "ext_dct8"   # 全局唯一；即 C++ 类名与头文件名（ext_dct8.hpp）
[[ports]]           # 每端口一条，顺序即端口顺序；dir ∈ in|out|clock|reset
name = "in"
dir = "in"
width = 64          # 1..4096
[[ports]]
name = "out"
dir = "out"
width = 64
[backends.verilog]
top = "dct8"        # Verilog module 名，缺省 = name
[backends.cpp]      # type = "source"：files 自动进链接，header 目录进 include 路径
files = ["dct8.cpp"]
header = "ext_dct8.hpp"
```

## MLIR

```mlir
pyc.ext_module @ext_dct8 {function_type = (i64, i1) -> (i64), verilog_top = "dct8",
    arg_names = ["in", "valid"], result_names = ["out"]} : (i64, i1) -> (i64)
%y = pyc.instance %x, %v {callee = @ext_dct8, name = "u_dct"} : (i64, i1) -> i64
```

verifier（PYCOps.cpp）：arg_names/result_names 必须与 function_type 的 arity 一致；
pyc.instance 的 callee 可指向 func.func 或 pyc.ext_module，操作数/结果类型必须与该签名逐项相同。

## C++ 组件契约（3 动词）

```cpp
struct ext_dct8 {                 // 类名 = [module].name
  pyc::cpp::Wire<64> in;          // 每端口一个成员，名字与清单一致
  pyc::cpp::Wire<1> valid;
  pyc::cpp::Wire<64> out;
  void eval();                    // 组合读；父模块输入指纹未变时跳过
  void tick_compute() {}          // 无状态模块给空体
  void tick_commit() {}
};
```

父模块把 ext 实例当普通子模块调度，只发上述三个动词。trace/probe 不进用户 ABI——C++ 父模块
生成码按端口名自己发 `tb.vcdTrace`/`reg.addWire`（Verilog probe manifest 暂不覆盖 ext
端口），用户类不必实现 `pyc_trace_vcd`/`pyc_register_probes`。**无输出端口的 ext** 因结果全未
使用会被 dead-instance 消除（与普通子模块同构）；需要保留其副作用时给 instance 加
`pyc.debug_keep = true`。ext 一律按有状态处理：每次 `tick_commit` 后父模块强制失效输入
指纹缓存，下一拍必重调 `eval()`。时钟模块的 `dir="clock"`/`dir="reset"` 端口每拍绑定，
运行时每周期 posedge 与 negedge 各调一次 `tick_compute()`/`tick_commit()`，必须自己
记录上次 clk、只在 0→1 沿推进（`rst` 按同步复位处理）。

## 双后端与运行

- **C++**：`[backends.cpp].files` 由 `pycircuit build` 发现后写入 `ext_sources` 并进链接。
- **Verilog**：实例化名 = `verilog_top`；用户 `.v` 不会自动进 `verilator_manifest.json`
  sources（follow-up），需手动补；ext 不内联/flatten，深度/时钟域检查在边界停止。

前端：`from pycircuit import ext as extmod`，
`y = extmod.instance(m, "ext/ext_dct8.toml", name="u_dct", in_=x, valid=1)`；端口按名绑定
（`name` 或 `name_`），int 自动成常量，缺/未知端口抛 `DesignError`；单输出返回 `Signal`，
多输出返回 list。示例见 `designs/examples/ext_dct8/`。

```bash
PYTHONPATH=compiler/frontend PYC_TOOLCHAIN_ROOT=.pycircuit_out/toolchain/install \
  python3 -m pycircuit.cli build designs/examples/ext_dct8/tb_ext_dct8.py \
  --out-dir /tmp/pyc_ext_dct8 --target cpp --jobs 8
/tmp/pyc_ext_dct8/cpp_build/build/pyc_tb     # → OK
```

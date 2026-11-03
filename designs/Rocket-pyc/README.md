# Rocket-pyc：Rocket Chip 裸核导入 PyCircuit（导入与等价验证流）

本目录承载 freechips Rocket 核（RV32IMA，取自 rocket-chip v1.6
`generated-verilog` 的裸 `Rocket` 顶层，含本地 `plusarg_reader_stub.v`
修补）的 **Verilog → pyc MLIR 导入**与**等价性验证**全部产物。

当前状态（三方对拍，ST 协议）：

| 模式 | verilog 路径（MLIR→Verilog） | cpp 路径（MLIR→C++） |
|---|---|---|
| 平铺导入（默认） | 400 拍 0 失配 | 400 拍 0 失配 |
| **层级导入**（`--keep-hierarchy`） | **400 拍 0 失配** | **400 拍 0 失配** |

层级导入说明：每个模块一个 `func.func` + `pyc.instance` 例化保留层级。
裸核从 `Rocket` 顶层细化后的真实层级为 **7 个模块 / 6 个实例边界**
（Rocket→ALU、BreakpointUnit、CSRFile、IBuf、MulDiv；IBuf→RVCExpander），
全部保留；`PlusArgTimeout` 因无任何输出端口被 yosys `opt_clean` 合法修剪
（平铺流同样处理，语义无差）。注意 cpp 路径以**原生层级构建**（pycc 不加
`--flatten`）——flatten 内联实例后 `pyc.wire` 的驱动与读端会被融合进同一
comb 区域，发射器把 wire 回填排到 pass 末尾，导致每拍陈旧读（见
verilog2pyc/v2p/check.py 内注释）。

## 流水线

```
rocket-chip（mill + Chisel 6.7）                       〔再生成路径〕
  manual_build.sh -> generated-fir/*.fir
  strip_fir.py     -> 去除 printf/assert（firtool vs chisel<=6.7，circt#6970）
  firtool          -> Verilog
rocket-chip-v16/generated-verilog/*.v                  〔验证输入，v1.6 发布物〕
  scripts/check_rocket.sh
    -> v2p（verilog2pyc）：yosys 归一化 -> pyc MLIR
       路径 A：MLIR -> pyc.v Verilog   \ 三方 ST 波形
       路径 B：MLIR -> pycc C++        / 等价比对
```

## 目录结构

- `tb/tb_rocket.v` —— golden 测试台（ST 协议）。自由运行的取指模型 +
  寄存化重定向响应；DUT 输入在每行 [采样, 沿, 打印] 窗口内保持稳定
  （cpp 回放契约）。程序为 addi/add/sw/lw 数据循环。
- `sim/` —— 独立 pycc C++ 回放仿真（对标 DavinciOO 流程）：
  `sim/scripts/{gen,build,perf}.sh` 依次发射 MLIR→cpp→驱动、编译
  `rocket_sim`、回放 golden 波形并报告吞吐。详见 `sim/README.md`。
- `scripts/check_rocket.sh` —— 正规三方对拍入口。
- `scripts/manual_build.sh` —— scalac 手工构建 + FIRRTL 细化
  （绕过 mill 的源码沙箱问题；`ROCKET_CHIP_DIR` 可覆盖源码树）。
- `scripts/strip_fir.py` —— FIRRTL 净化（去验证语句），供 firtool 消费。
- `scripts/status.sh` —— mill 细化进度查看辅助。

## 用法

```bash
scripts/check_rocket.sh                        # 平铺模式，默认 400 拍
scripts/check_rocket.sh --cycles 100           # 平铺模式，截断到 100 拍
scripts/check_rocket.sh --keep-hierarchy       # 层级模式（func.func + pyc.instance）
sim/scripts/gen.sh && sim/scripts/build.sh && sim/scripts/perf.sh
```

环境依赖：已构建的 `pycc`（toolchain）、PATH 上的 verilator/yosys、
以及 `verilog2pyc` 仓库（V2P_DIR；导入器未内置在本目录）。
可用环境变量：`V2P_DIR`、`ROCKET_CHIP_V16`、`PYCC`。

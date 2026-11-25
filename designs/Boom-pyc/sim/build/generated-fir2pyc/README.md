# fir2pyc 路线产物（BOOM BoomTrimHarness）

由 `/home/zhangzijie/fir2pyc` 从 `../../../generated-fir/BoomTrimHarness.stripped.fir`
（FIRRTL 3.3.0，571 模块）发射的 pyc MLIR 及 pycc 产物。

## 产物清单

| 文件 | 说明 |
|---|---|
| `BoomTrimHarness.mlir` | fir2pyc 全顶层发射，1,680,380 行 / 82.8MB |
| `BoomTrimHarness.opt.mlir` | pyc-opt 后，80.6MB |
| `BoomTrimHarness.v` | pycc `--emit=verilog`，78MB |
| `BoomTrimHarness_gen.cpp` | pycc `--emit=cpp` C++ model，186MB，g++ 语法校验 0 error |
| `BoomTrimHarness_gen.cpp.stats.json` | regs 34449，max_depth 513/1024，TNS=0 |
| `build_*.log`, `pyc_opt.log` | 构建日志 |

## 生成命令

与 Rocket 完全相同（`PYC_DISABLE_THREADS=1 pycc … --emit=cpp
--logic-depth 1024`），详见
`../../../../Rocket-pyc/sim/build/generated-fir2pyc/README.md`（含编译器
修复清单与 2026-11-16 多线程测试记录：pyc-opt 微观复现并行 3/3 segfault、
单线程通过；pycc 全管线多线程 4/4 通过但建议正式构建保持单线程）。

无需 `--no-state-opt`（11-11 版需要的 BoomIOMSHR 收敛修复已在当前 pycc；
本次 max_depth 513 与 11-11 记录一致）。

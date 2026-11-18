# fir2pyc 路线产物（Rocket TestHarness）

由 `/home/zhangzijie/fir2pyc` 从 `rocket-chip/generated-fir/TestHarness.fir`
（FIRRTL 3.3.0，565 模块）直接发射的 pyc MLIR 及 pycc 产物。
与 v2p 路线的 `../generated/` 平行，互不影响。

## 产物清单

| 文件 | 说明 |
|---|---|
| `TestHarness.mlir` | fir2pyc 全顶层发射，334,529 行 / 15.6MB |
| `TestHarness.opt.mlir` | pyc-opt 后，15.2MB |
| `TestHarness.v` | pycc `--emit=verilog`，14MB |
| `TestHarness_gen.cpp` | pycc `--emit=cpp` C++ model，32MB，g++ 语法校验 0 error |
| `TestHarness_gen.cpp.stats.json` | pycc stats（regs 12927→2228，max_depth 518/1024，TNS=0） |
| `build_*.log`, `pyc_opt.log` | 构建日志 |

## 生成命令

```bash
PYC_DISABLE_THREADS=1 $TOOLCHAIN/bin/pycc TestHarness.mlir \
  --emit=cpp --logic-depth 1024 \
  --cpp TestHarness_gen.cpp -o TestHarness_gen.cpp.stats.json
```

`--emit=verilog` 同参数。`PYC_DISABLE_THREADS=1` 见下文多线程说明。

## 依赖的编译器修复（未提交，工作树 4 文件 +57/-9）

1. `ForkMergeRetimePass.cpp`：`keyOf()` 用 `os << Value` 构造分组 key 触发
   MLIR 通用打印器在大 IR 上崩溃 → 改 `getAsOpaquePointer()` 指针身份。
2. `StateOptimizePass.cpp`：`canonicalizeAndCSE` greedy 默认 `maxIterations=10`
   在大函数不收敛 → **静默** `signalPassFailure`（即"pass pipeline failed"
   无消息的真凶）→ 提到 100。与 slp-pack-wires / BoomIOMSHR 同族。
3. `CppEmitter.cpp` 三处命名冲突：成员被 `pyc_register_probes(ProbeRegistry &reg,…)`
   参数遮蔽（生成 `this->member`）；FIRRTL 信号名 `tick` 撞方法 `void tick()`
   （NameTable 预保留方法名）；成员名撞类型名（reserve 全模块函数名 +
   `unique()` 后缀候选防 `X`/`X_2` 交叉碰撞）。
4. `pycc.cpp`：新增 `PYC_DISABLE_THREADS` 环境变量（多线程逃生阀，见下）。

## 多线程测试记录（2026-11-16）

**微观复现**（pyc-opt 对 fork-merge-retime + comb-canonicalize 两 pass 快照）：
- 并行（默认）：**3/3 segfault**（verifier 报 MuxOp 类型非法 → MLIR 诊断打印
  路径自身崩溃，真实错误被掩盖）
- `--mlir-disable-threading`：通过；valgrind（串行化）：0 内存错误
- 结论：MLIR 并行 pass adaptor 存在数据竞争，该输入下 100% 复现

**pycc 全管线多线程**（本目录 TestHarness.mlir，`--emit=cpp`，不设
PYC_DISABLE_THREADS）：
- **4/4 exit 0**，产物字节一致（32,298,606 B，stats 与串行版相同）
- 耗时约为串行的 1/3
- 解释：完整管线的 pass 调度未踩中上述竞态窗口，但风险仍在

**建议**：正式/过夜构建一律加 `PYC_DISABLE_THREADS=1`；竞态根因
（MLIR pass adaptor 层）待 TSAN 级分析后修复。

## 已知 caveat

- `TLDebugModuleInner`（1/565）宽度推断失败被降级为常量 0 stub（debug
  模块功能丢失，子模块 `TLDebugModuleInnerAsync` 正常）。
- 叶模块对拍 DMIToTL 存在与旧版相同的 `iodmi.resp` 无驱动差族
  （golden=0 vs cpp=随机值），其余抽样模块全 PASS。

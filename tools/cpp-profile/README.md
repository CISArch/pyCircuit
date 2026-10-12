# cpp-profile —— 生成 C++ model 的采样剖析工具链

对 pyCircuit 生成的 C++ model 做 CPU 采样剖析,产出 **Perfetto 可直接打开**的调用剖面,
用于定位仿真性能瓶颈(而不是靠猜)。

## 为什么不用 `perf record` 直接转 Perfetto

本机/容器里 `perf_event_paranoid=4` 且非 root,`perf_event_open` 被拒;`perf` 需要用 `sudo` 运行。
另外官方 `traceconv`(perf → Perfetto)不一定可得,所以这里自带一个零依赖的转换器:
`perf script` 文本 → Perfetto protobuf(`.pftrace`)+ Chrome JSON + 静态 SVG 火焰图。

## 流程

```bash
# 0) 采样器(可选:LICENSE-free 的回退方案,容器里连 sudo 都没有时用)
cc -shared -fPIC -O2 -o libpycprof.so sampler.c        # LD_PRELOAD 用户态采样

# 1) 一次性生成被测 model(与 DavinciBaseLine 的 build_pycircuit_module.py 一致)
#    见 DavinciBaseLine/model/rtl/run_pycircuit_trace_align.sh

# 2) 逐 trace 采样
ROOT=<产物目录> RUNS_DIR=$ROOT/runs CALLGRAPH=dwarf KEEP_PERF_DATA=0 \
  TARGET_SECONDS=2 PERF_HZ=1999 ./run_profile_matrix.sh [trace ...]

# 3) 跨 trace 汇总 + 合并 Perfetto trace
python3 aggregate.py $ROOT/runs
python3 collect_metadata.py $ROOT        # 版本/工具链/宿主/逐 trace 元数据
python3 hot_bodies.py $ROOT/summary.json <生成目录>   # 热点 → 生成文件 + 函数体行数
```

## 产物

| 文件 | 说明 |
|------|------|
| `runs/<trace>/trace.pftrace` | Perfetto 原生 trace(切片/火焰视图),单条 trace 一个文件 |
| `runs/<trace>/trace.json` | Chrome Trace Event 备用格式(Perfetto UI 同样可开) |
| `runs/<trace>/perf.script.raw.gz` | `perf script --inline` 原文(全部样本+调用栈,可复算) |
| `runs/<trace>/perf.data` | 原始 perf 采样(默认保留;`KEEP_PERF_DATA=0` 时删除) |
| `runs/<trace>/report.json` | self/inclusive 排名 + 相位分类 |
| `runs/<trace>/flame.svg` | 静态火焰图 |
| `runs/<trace>/annotate.txt` | 热符号的指令/源码行级注解(`perf annotate`) |
| `runs/<trace>/perf.stat.txt` | IPC / cache-miss / branch-miss 计数器 |
| `summary.{json,md}` | 跨 trace 汇总(相位占比、逐 trace 表) |
| `all.pftrace` | 全部 trace 合并(每条 trace 一条轨道,顺序排列) |
| `flame_all.svg` | 跨 trace 合并火焰图 |
| `metadata.json` / `METADATA.md` | 版本、工具链、宿主、采样配置、产物校验和 |

## 看结果

1. 打开 <https://ui.perfetto.dev>,把 `trace.pftrace`(或 `all.pftrace`)拖进去;
2. 左侧选线程/trace 轨道,主视图是嵌套切片(火焰图),底部 "Flame Graph" 标签是聚合火焰图;
3. 想按函数聚合排序,直接用 `report.json` / `summary.md`。

## 两个构建变体

- **标准构建**(`-O3`,无 `-g`):就是基准跑的那份二进制 → 结论最贴近基准。用 `CALLGRAPH=dwarf` 采样
  (不需要 frame pointer),但 perf.data 体积大、无行号注解。
- **剖析构建**(`PYC_REPLAY_OPT="-O3 -g -fno-omit-frame-pointer"`):符号/行号全,
  `CALLGRAPH=fp` 采样体积小,可 `perf annotate` 到源码行。代码生成几乎一致,用于交叉验证。

## 注意

- 采样是 **CPU 时间**采样(`cycles:u` + SIGPROF),宿主负载只影响墙钟,不影响 self/inclusive 占比;
  但 `elapsed_ms`/cycle/s 会被负载放大,别拿它跟 auto_perf 的 cycle/s 直接比。
- `perf record` 需要 `sudo`;产物默认 root 属主,脚本结束时会 `chown` 回当前用户。

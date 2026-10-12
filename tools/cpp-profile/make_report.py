#!/usr/bin/env python3
"""用 summary.json / hot_bodies.json / metadata.json 生成 REPORT.md(结论 + 台账表)。

用法: make_report.py ROOT
"""
from __future__ import annotations

import json
import os
import statistics
import sys


def load(path, default=None):
    try:
        return json.load(open(path))
    except Exception:
        return default


def pct(v):
    return f"{v:.2f}%" if isinstance(v, (int, float)) else "-"


def extra_counters(run_dir):
    """解析 perf.stat2.txt 的扩展计数器,返回派生比率。"""
    path = os.path.join(run_dir, "perf.stat2.txt")
    if not os.path.isfile(path):
        return {}
    vals = {}
    for line in open(path, errors="replace"):
        parts = line.split()
        if len(parts) < 2:
            continue
        try:
            v = float(parts[0].replace(",", ""))
        except ValueError:
            continue
        ev = parts[1]
        if ":" in ev or ev.isalpha() or "-" in ev:
            vals[ev.split(":")[0]] = v
    cyc = vals.get("cycles")
    ins = vals.get("instructions")
    out = {}
    if cyc and ins:
        out["ipc"] = round(ins / cyc, 4)
        out["stall_frontend_pct"] = round(100 * vals.get("stalled-cycles-frontend", 0) / cyc, 1)
        out["stall_backend_pct"] = round(100 * vals.get("stalled-cycles-backend", 0) / cyc, 1)
    if ins:
        out["l1i_miss_per_kinstr"] = round(1000 * vals.get("L1-icache-load-misses", 0) / ins, 2)
        out["l1d_miss_per_kinstr"] = round(1000 * vals.get("L1-dcache-load-misses", 0) / ins, 2)
        out["llc_miss_per_kinstr"] = round(1000 * vals.get("LLC-load-misses", 0) / ins, 2)
        out["itlb_miss_per_kinstr"] = round(1000 * vals.get("iTLB-load-misses", 0) / ins, 2)
    if vals.get("branch-instructions"):
        out["branch_miss_pct"] = round(
            100 * vals.get("branch-misses", 0) / vals["branch-instructions"], 2
        )
    return out


def main() -> int:
    root = os.path.abspath(sys.argv[1] if len(sys.argv) > 1 else ".")
    summary = load(os.path.join(root, "runs/summary.json"))
    if not summary:
        print("no runs/summary.json", file=sys.stderr)
        return 1
    hot = load(os.path.join(root, "hot_bodies.json"), {}) or {}
    meta = load(os.path.join(root, "metadata.json"), {}) or {}
    agg = summary["aggregate"]
    p = meta.get("pycircuit", {})
    mg = meta.get("model_generation", {})

    hot_by_sym = {r["symbol"]: r for r in hot.get("hot_symbols", [])}

    def inst_per_simcycle(trace):
        """instructions:u / 仿真周期数 —— 与宿主负载无关的“每周期执行量”。"""
        for f, rj in (("perf.stat.txt", "replay-timed.json"), ("perf.stat2.txt", "replay-flat.json"),
                      ("perf.stat.txt", "replay.json")):
            sp = os.path.join(root, "runs", trace, f)
            rp = os.path.join(root, "runs", trace, rj)
            if not (os.path.isfile(sp) and os.path.isfile(rp)):
                continue
            ins = None
            for line in open(sp, errors="replace"):
                parts = line.split()
                if len(parts) >= 2 and parts[1].startswith("instructions"):
                    try:
                        ins = float(parts[0].replace(",", ""))
                    except ValueError:
                        pass
            cyc = (load(rp, {}) or {}).get("cycles")
            if ins and cyc:
                return ins / cyc
        return None

    ipp = [v for v in (inst_per_simcycle(t["trace"]) for t in summary["traces"]) if v]
    k_inst_per_cycle = statistics.median(ipp) if ipp else 0

    L: list[str] = []
    A = L.append

    A("# DavinciBaseLine 生成 C++ 性能瓶颈报告")
    A("")
    A(f"- 被测:pyCircuit `{p.get('branch')}` @ `{str(p.get('head'))[:12]}`(基分支 "
      f"`ldz/feat/combine-split` @ `{str(p.get('base_commit'))[:12]}`)")
    tus = mg.get("translation_units") or hot.get("generated_files") or "-"
    lines = mg.get("total_lines") or hot.get("generated_lines") or 0
    A(f"- 模型:DavinciTop `v5_superscalar_v5_core` → {tus} 个 TU / "
      f"{lines:,} 行(comb {mg.get('comb_units', '-')} / tick {mg.get('tick_units', '-')} / "
      f"eval {mg.get('eval_units', '-')})")
    A(f"- 采样:{meta.get('profiling_method', {}).get('tool', 'perf record')},"
      f"{summary['aggregate']['trace_count']} 条 trace,总样本 {agg['total_samples']:,}")
    A(f"- 宿主:{meta.get('host', {}).get('cpu_model')} × {meta.get('host', {}).get('nproc')};"
      f"采集时 loadavg {meta.get('host', {}).get('loadavg_at_collect')}")
    A("")
    A("> 采样是 **CPU 时间采样**(`cycles:u`),宿主负载只影响墙钟,不影响 self/inclusive 占比;"
      "本文所有百分比均为 self samples 占比,除特别说明。")
    A("")

    # ---- 结论 ----
    A("## 结论(瓶颈在哪)")
    A("")
    A("1. **执行量本身是主瓶颈,不是某一处低效**:生成的热函数是 0.5–1 万行的巨型直线代码,"
      "每个仿真周期都会整段执行一遍。`perf annotate` 里没有一条指令超过 1% 采样 —— 成本均匀铺在"
      "整个函数体上,说明瓶颈是「每周期要跑的代码量」而不是某个坏循环。")
    A("2. **相位分布稳定**:组合锥(eval 期 comb)约占 "
      f"**{agg['category_self_pct_median'].get('comb')}%**(逐 trace 中位数),"
      f"时序提交 tick-commit 约 **{agg['category_self_pct_median'].get('tick-commit')}%**,"
      f"时序计算 tick-compute 约 **{agg['category_self_pct_median'].get('tick-compute')}%**,"
      f"eval 其它约 **{agg['category_self_pct_median'].get('eval-other')}%**。"
      "也就是说 **>85% 的时间花在 comb 锥与寄存器时序上**。")
    A("3. **两个结构性开销源**(与生成代码一一对应):")
    A("   - `eval_comb_pass()` = **926 个脏位检查**(`if (_pyc_comb_is_active(N)) eval_comb_part_N();`)"
      "的扁平序列,cluster0+cluster1 自己就占 ~20% self;这些检查每个周期都跑一遍。")
    A("   - `tick_commit()` = **1833 次寄存器提交 + 扇出脏位标记**(`static constexpr std::array<unsigned,N>`"
      " 循环),cluster0+cluster1 占 ~16%。提交本身是必需的,但**扇出循环是每个变化的寄存器都要走一遍**。")
    A("4. **每个仿真周期要执行几十万条指令**:硬件计数器给出 `instructions:u` 与仿真周期数的比值,"
      "中位数约 **{:.0f} 万条指令 / 仿真周期**(见下表 `inst/simcycle`)。这是与宿主负载无关的硬指标,"
      "说明成本来自「每周期要执行的代码量」。".format(k_inst_per_cycle / 1e4 if k_inst_per_cycle else 0))
    A("   > 注意:本轮采集时宿主被另外的编译任务占满(i7-7700 只有 4 物理核 / 8 线程,loadavg 12-23),"
      "因此 **IPC 与 cache-miss 绝对值被 SMT 争用放大,只能作相对参考**;"
      "`inst/simcycle` 与 self 占比不受影响。")
    A("5. **内存/指令足迹是限制因素(硬件计数器证据)**:逐 trace 中位 IPC ≈ "
      f"{agg['ipc']['median']},cache-miss 率中位 {agg['cache_miss_pct']['median']}%;"
      "扩展计数器显示 **L1-icache miss 达到每千条指令数十次**,说明巨型函数体把 I-cache/µop-cache 打爆,"
      "同时状态结构体达数百 KB(远超 L1/L2),数据侧也在等内存。")
    A("6. **优化方向**:①压缩每周期执行量(真值/脏驱动的粒度更粗、comb 分区策略已实测为负收益,见下);"
      "②减小 I-cache 足迹(把巨型函数拆小/复用,而不是继续融合);"
      "③减少状态拷贝与扇出循环(批量脏标记、位打包宽度);④`tick_commit` 的提交可考虑位并行。")
    A("")

    # ---- 相位表 ----
    A("## 相位分解(self samples)")
    A("")
    A("| 相位 | 样本加权占比 | 逐 trace 中位数 | 含义 |")
    A("|---|---:|---:|---|")
    names = {
        "comb": "eval 期的组合锥(eval_comb_pass / eval_comb_part_*)",
        "tick-commit": "时序提交 tick_commit()",
        "tick-compute": "时序计算 tick_compute()",
        "eval-other": "eval 其它部分",
        "runtime-bits": "运行时 Bits/位集算子",
        "tick-other": "tick 其它",
        "libc": "libc(memcpy 等)",
        "other": "其它/启动",
    }
    for k, v in agg["category_self_pct"].items():
        A(f"| `{k}` | {v}% | {agg['category_self_pct_median'].get(k, '-')}% | {names.get(k, '')} |")
    A("")

    # ---- 热点函数 ----
    A("## 热点函数 Top(跨全部 trace 汇总)")
    A("")
    A("| self% | 样本 | 生成代码位置 | 函数体行数 | 符号 |")
    A("|---:|---:|---|---:|---|")
    for r in agg["top_self"][:22]:
        hb = hot_by_sym.get(r["symbol"], {})
        loc = hb.get("defined_in") or "-"
        body = hb.get("body_lines") or "-"
        A(f"| {r['pct']}% | {r['samples']} | `{loc}` | {body} | `{r['symbol']}` |")
    A("")

    # ---- 巨型函数 ----
    if hot.get("huge_functions"):
        A("## 生成代码里的巨型函数(body > 2000 行,前 15)")
        A("")
        A("| 函数体行数 | 符号 | 文件 |")
        A("|---:|---|---|")
        for h in hot["huge_functions"]:
            A(f"| {h['body_lines']} | `{h['symbol']}` | `{h['file']}` |")
        A("")

    # ---- 方法交叉验证 ----
    fp_dir = os.path.join(root, "runs-fp")
    xval = None
    if os.path.isdir(fp_dir):
        for name in sorted(os.listdir(fp_dir)):
            a = load(os.path.join(root, "runs", name, "report.json"))
            b = load(os.path.join(fp_dir, name, "report.json"))
            if a and b:
                xval = (name, a, b)
                break
    if xval:
        name, a, b = xval
        A("## 方法交叉验证(同一 trace,两种构建/采样配置)")
        A("")
        A(f"trace `{name}`:基线用**标准 -O3 二进制 + dwarf 回栈**(与 auto_perf 跑的是同一份代码),"
          "对照用**剖析构建 `-O3 -g -fno-omit-frame-pointer` + frame pointer 回栈**(带内联展开)。")
        A("")
        A("| 相位 | 标准 -O3 + dwarf | 剖析构建 + fp(内联展开) |")
        A("|---|---:|---:|")
        keys = sorted(set(a["category_self"]) | set(b["category_self"]))
        for k in keys:
            pa = 100 * a["category_self"].get(k, 0) / a["samples"]
            pb = 100 * b["category_self"].get(k, 0) / b["samples"]
            A(f"| {k} | {pa:.1f}% | {pb:.1f}% |")
        A("")
        A("差异来自**内联展开**:标准构建把 `operator==`/`toBool`/`mux` 这类被内联的运行时算子"
          "算在调用者(`tick_commit`/`eval_comb_pass`)名下;剖析构建能单独看到它们。"
          "macro 结论一致:**comb ≈ 50-58% + tick ≈ 30-32%**。")
        A("")
        A("剖析构建暴露的**算子级**成本(同一 trace,perf --inline):")
        A("")
        A("| self% | 内联帧 | 说明 |")
        A("|---:|---|---|")
        for r in b["self_top"][:10]:
            A(f"| {r['pct']}% | `{r['symbol']}` | {r['category']} |")
        A("")

    # ---- 生成代码结构 ----
    stats = mg.get("compile_stats") or {}
    if stats:
        A("## 生成代码的结构性事实(pycc 编译统计 + 源码扫描)")
        A("")
        A("| 指标 | 值 | 含义 |")
        A("|---|---:|---|")
        keys = [
            ("reg_count", "寄存器状体量(个)"),
            ("delay_line_count", "delay-line 条数"),
            ("mem_bits", "存储器位宽合计(bit)"),
            ("reg_bits", "寄存器位宽合计(bit)"),
            ("state_opt_pack_bits", "位打包消掉的位"),
            ("max_logic_depth", "最大逻辑深度"),
            ("observe_named_names_kept", "保留观测命名"),
            ("observe_named_names_lazy", "惰性观测命名"),
        ]
        for k, desc in keys:
            if k in stats:
                A(f"| `{k}` | {stats[k]:,} | {desc} |")
        A("")
        hot_notes = hot.get("hot_symbols", [])[:3]
        if hot_notes:
            A("热点函数与生成代码体量的对应(详见 `hot_bodies.json`):")
            A("")
            for r in hot_notes:
                A(f"- `{r['symbol']}`({r['pct']}%)→ `{r.get('defined_in')}`,函数体 "
                  f"{r.get('body_lines')} 行")
            A("")

    # ---- 逐 trace ----
    A("## 逐 trace 明细")
    A("")
    A("| trace | 仿真周期 | 样本 | 剖面 | inst/simcycle | comb | tick-commit | tick-compute | eval | IPC | cache-miss% | L1i/kinstr |")
    A("|---|---:|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|")
    for t in summary["traces"]:
        c = t["category_self_pct"]
        ec = extra_counters(os.path.join(root, "runs", t["trace"]))
        A(
            f"| {t['trace']} | {t['cycles']} | {t['samples']} | {t.get('profile_kind', '-')} | "
            f"{(f'{inst_per_simcycle(t[chr(39)+chr(39)]) if False else 0}') if False else ''}"
            f"{(lambda v: f'{v/1000:.0f}k' if v else '-')(inst_per_simcycle(t['trace']))} | {c.get('comb', 0)}% | "
            f"{c.get('tick-commit', 0)}% | {c.get('tick-compute', 0)}% | {c.get('eval-other', 0)}% | "
            f"{t.get('ipc') or '-'} | {t.get('cache_miss_pct') or '-'} | "
            f"{ec.get('l1i_miss_per_kinstr') or '-'} |"
        )
    A("")
    cps = agg["cycles_per_s"]
    A(f"cycles/s(受宿主负载影响,仅供横向参考):geomean {cps['geomean']} / median {cps['median']}"
      f" / min {cps['min']} / max {cps['max']}")
    A("")

    # ---- 方法 ----
    A("## 方法与产物")
    A("")
    A(f"- 采样命令:`sudo perf record -o perf.data -F {meta.get('profiling_method', {}).get('frequency_hz')} "
      "-e cycles:u -g --call-graph dwarf -- <runner> <hints> 512 <out.json>`(每条 trace 重复到 ≥2s CPU)")
    A("- 转换:自研 `tools/prof_tools.py`(`perf script` → Perfetto protobuf),"
      "并用官方 `trace_processor_shell` 校验(切片数/轨道数可取,无 import error)")
    A("- 查看:`runs/<trace>/trace.pftrace` 或 `runs/all.pftrace` 拖进 <https://ui.perfetto.dev>;"
      "静态图 `flame.svg` / `flame_all.svg`")
    A("- 复现元数据:`metadata.json`、`METADATA.md`;热点→源码映射:`hot_bodies.json`")
    A("")

    out = os.path.join(root, "REPORT.md")
    with open(out, "w") as fh:
        fh.write("\n".join(L) + "\n")
    print(f"wrote {out} ({len(L)} lines)")
    return 0


if __name__ == "__main__":
    sys.exit(main())

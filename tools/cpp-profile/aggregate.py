#!/usr/bin/env python3
"""汇总 runs/* 的逐 trace 剖面,产出跨 trace 的瓶颈台账。

输出:
  summary.json  —— 逐 trace 指标 + 全局聚合(机器可读,供后续深挖)
  summary.md    —— 人读表格
  all.pftrace   —— 全部 trace 合并的 Perfetto trace(每条 trace 一条轨道)
  flame_all.svg —— 跨 trace 合并火焰图

用法: aggregate.py RUNS_DIR [--out DIR]
"""
from __future__ import annotations

import argparse
import json
import os
import re
import statistics
import subprocess
import sys
from collections import defaultdict

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
from prof_tools import build_report, parse_perf_script, write_flame_svg, is_model_sample  # noqa: E402


def read_json(path, default=None):
    try:
        with open(path) as fh:
            return json.load(fh)
    except Exception:
        return default


def parse_perf_stat(path):
    """解析 perf stat -o 输出,返回原始计数器 + 派生指标(IPC/缺失率)。"""
    if not os.path.isfile(path):
        return {}
    text = open(path, errors="replace").read()
    raw = {}
    for line in text.splitlines():
        m = re.match(
            r"^\s*([\d,]+(?:\.\d+)?)\s+([a-zA-Z][\w:./\-]*)\s*(?:#.*)?(?:\([\d.]+%\))?\s*$",
            line,
        )
        if not m:
            continue
        event = m.group(2)
        if event in {"seconds", "elapsed"}:
            continue
        try:
            raw[event] = float(m.group(1).replace(",", ""))
        except ValueError:
            continue
    out = dict(raw)
    cyc = raw.get("cycles:u") or raw.get("cycles")
    ins = raw.get("instructions:u") or raw.get("instructions")
    if cyc and ins:
        out["ipc"] = round(ins / cyc, 4)
    cref = raw.get("cache-references:u") or raw.get("cache-references")
    cmiss = raw.get("cache-misses:u") or raw.get("cache-misses")
    if cref and cmiss:
        out["cache_miss_pct"] = round(100.0 * cmiss / cref, 2)
    bref = raw.get("branch-instructions:u") or raw.get("branch-instructions")
    bmiss = raw.get("branch-misses:u") or raw.get("branch-misses")
    if bref and bmiss:
        out["branch_miss_pct"] = round(100.0 * bmiss / bref, 2)
    return out


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("runs_dir")
    ap.add_argument("--out", default=None)
    args = ap.parse_args()
    runs_dir = os.path.abspath(args.runs_dir)
    out_dir = os.path.abspath(args.out or runs_dir)

    traces = []
    all_samples = []          # (trace, [samples]) 供合并火焰图
    agg_self = defaultdict(int)
    agg_incl = defaultdict(int)
    agg_cat_self = defaultdict(int)
    agg_cat_incl = defaultdict(int)
    agg_cat_by_trace = defaultdict(lambda: defaultdict(int))
    total_samples = 0
    per_trace_self = defaultdict(lambda: defaultdict(int))

    for name in sorted(os.listdir(runs_dir)):
        run = os.path.join(runs_dir, name)
        if not os.path.isdir(run):
            continue
        script = os.path.join(run, "perf.script.raw")
        if not os.path.isfile(script) and os.path.isfile(script + ".gz"):
            script += ".gz"
        timed = read_json(os.path.join(run, "replay-timed.json"), {}) or {}
        if not timed:
            timed = read_json(os.path.join(run, "replay-flat.json"), {}) or {}
        conv = read_json(os.path.join(run, "conversion.json"), {}) or {}
        stat = parse_perf_stat(os.path.join(run, "perf.stat.txt"))
        kind = "callstack"
        if not os.path.isfile(script):
            flat = os.path.join(run, "report-flat.json")
            if not os.path.isfile(flat):
                continue
            rep = read_json(flat, {}) or {}
            kind = "flat"
            samples = []
        else:
            samples = [s for s in parse_perf_script(script) if is_model_sample(s)]
            if not samples:
                continue
            rep = build_report(samples, top=25)
        if samples:
            all_samples.append((name, samples))
        total_samples += rep["samples"]
        for row in rep["self_top"]:
            agg_self[row["symbol"]] += row["samples"]
        for row in rep["inclusive_top"]:
            agg_incl[row["symbol"]] += row["samples"]
        for k, v in rep["category_self"].items():
            agg_cat_self[k] += v
            agg_cat_by_trace[k][name] += v
        for k, v in rep["category_inclusive"].items():
            agg_cat_incl[k] += v
        for row in rep["self_top"]:
            per_trace_self[name][row["symbol"]] += row["samples"]

        cycles = timed.get("cycles")
        elapsed_ms = timed.get("elapsed_ms")
        traces.append(
            {
                "trace": name,
                "instructions": timed.get("instructions"),
                "cycles": cycles,
                "elapsed_ms": elapsed_ms,
                "cycles_per_s": round(cycles / (elapsed_ms / 1000.0)) if cycles and elapsed_ms else None,
                "samples": rep["samples"],
                "profile_kind": kind,
                "category_self_pct": {
                    k: round(100.0 * v / rep["samples"], 2)
                    for k, v in rep["category_self"].items()
                },
                "top_self": rep["self_top"][:10],
                "perf_stat": stat,
                "ipc": stat.get("ipc"),
                "cache_miss_pct": stat.get("cache_miss_pct"),
                "branch_miss_pct": stat.get("branch_miss_pct"),
                "conversion": {
                    k: conv.get(k)
                    for k in ("instructions", "cell_bits", "trace", "hints")
                    if k in conv
                },
            }
        )

    traces.sort(key=lambda t: -(t["cycles_per_s"] or 0))

    # 逐 trace 百分比的“中位数”——避免被样本量最大的 trace 主导,给出更公平的全景
    cat_names = sorted({k for t in traces for k in t["category_self_pct"]})
    cat_median = {}
    for k in cat_names:
        vals = [t["category_self_pct"][k] for t in traces if k in t["category_self_pct"]]
        if vals:
            cat_median[k] = round(statistics.median(vals), 2)
    cps = [t["cycles_per_s"] for t in traces if t.get("cycles_per_s")]
    summary = {
        "traces": traces,
        "aggregate": {
            "trace_count": len(traces),
            "total_samples": total_samples,
            "category_self_pct": {
                k: round(100.0 * v / total_samples, 2)
                for k, v in sorted(agg_cat_self.items(), key=lambda kv: -kv[1])
            }
            if total_samples
            else {},
            "category_inclusive_pct": {
                k: round(100.0 * v / total_samples, 2)
                for k, v in sorted(agg_cat_incl.items(), key=lambda kv: -kv[1])
            }
            if total_samples
            else {},
            "category_self_pct_median": cat_median,
            "top_self": [
                {"symbol": k, "samples": v, "pct": round(100.0 * v / total_samples, 2)}
                for k, v in sorted(agg_self.items(), key=lambda kv: -kv[1])[:40]
            ]
            if total_samples
            else [],
            "top_inclusive": [
                {"symbol": k, "samples": v, "pct": round(100.0 * v / total_samples, 2)}
                for k, v in sorted(agg_incl.items(), key=lambda kv: -kv[1])[:40]
            ]
            if total_samples
            else [],
            "cycles_per_s": {
                "geomean": round(
                    statistics.geometric_mean(cps), 1
                )
                if cps
                else None,
                "median": round(statistics.median(cps), 1) if cps else None,
                "min": round(min(cps), 1) if cps else None,
                "max": round(max(cps), 1) if cps else None,
            },
            "ipc": {
                "median": round(statistics.median([t["ipc"] for t in traces if t.get("ipc")]), 3)
                if any(t.get("ipc") for t in traces)
                else None
            },
            "cache_miss_pct": {
                "median": round(
                    statistics.median(
                        [t["cache_miss_pct"] for t in traces if t.get("cache_miss_pct")]
                    ),
                    2,
                )
                if any(t.get("cache_miss_pct") for t in traces)
                else None
            },
        },
    }

    os.makedirs(out_dir, exist_ok=True)
    with open(os.path.join(out_dir, "summary.json"), "w") as fh:
        json.dump(summary, fh, indent=2)

    # 合并火焰图(所有 trace 的样本堆到一张图上)
    merged = []
    for _, samples in all_samples:
        merged.extend(samples)
    if merged:
        write_flame_svg(merged, os.path.join(out_dir, "flame_all.svg"),
                        title="all traces (merged)")

    # 合并 perfetto trace
    proc = subprocess.run(
        [sys.executable, os.path.join(HERE, "merge_pftrace.py"),
         os.path.join(out_dir, "all.pftrace")]
        + [os.path.join(runs_dir, n) for n, _ in all_samples],
        capture_output=True, text=True,
    )
    merge_info = proc.stdout.strip() or proc.stderr.strip()

    # 人读表格
    lines = ["# DavinciBaseLine C++ model 采样剖面汇总", ""]
    agg = summary["aggregate"]
    lines += [
        f"- traces: {agg['trace_count']}  总样本: {agg['total_samples']}",
        f"- cycles/s: geomean {agg['cycles_per_s']['geomean']} / median {agg['cycles_per_s']['median']}",
        f"- IPC 中位数: {agg['ipc']['median']}   cache-miss 中位数: {agg['cache_miss_pct']['median']}%",
        "",
        "## 全局热点(self samples)",
        "",
        "| 占比 | 样本 | 符号 |",
        "|---:|---:|---|",
    ]
    for row in agg["top_self"][:25]:
        lines.append(f"| {row['pct']}% | {row['samples']} | `{row['symbol']}` |")
    lines += ["", "## 相位分解(self samples)", "", "| 相位 | 占比 |", "|---|---:|"]
    for k, v in agg["category_self_pct"].items():
        lines.append(f"| {k} | {v}% |")
    lines += ["", "## 逐 trace", "",
              "| trace | cycles | cycles/s | IPC | samples | comb | tick-commit | tick-compute | eval-other |",
              "|---|---:|---:|---:|---:|---:|---:|---:|---:|"]
    for t in traces:
        c = t["category_self_pct"]
        lines.append(
            f"| {t['trace']} | {t['cycles']} | {t['cycles_per_s']} | {t.get('ipc') or '-'} | {t['samples']} | "
            f"{c.get('comb', 0)}% | {c.get('tick-commit', 0)}% | {c.get('tick-compute', 0)}% | {c.get('eval-other', 0)}% |"
        )
    with open(os.path.join(out_dir, "summary.md"), "w") as fh:
        fh.write("\n".join(lines) + "\n")

    print(json.dumps({"traces": len(traces), "samples": total_samples,
                      "categories": agg["category_self_pct"], "merge": merge_info},
                     ensure_ascii=False))
    return 0


if __name__ == "__main__":
    sys.exit(main())

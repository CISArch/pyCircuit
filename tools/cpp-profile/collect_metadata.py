#!/usr/bin/env python3
"""收集本次剖面的全部元数据,写入 metadata.json / METADATA.md。

覆盖:被测仓库版本、编译器与工具链、生成模型规模、采样配置、宿主环境、
逐 trace 运行参数与产物校验和 —— 供后续深挖时复现同一条件。
"""
from __future__ import annotations

import hashlib
import json
import os
import platform
import re
import subprocess
import sys
import time
from datetime import datetime, timezone


def sh(cmd, cwd=None, timeout=60):
    try:
        out = subprocess.run(cmd, cwd=cwd, capture_output=True, text=True,
                             timeout=timeout, errors="replace")
        return (out.stdout + out.stderr).strip()
    except Exception as exc:  # noqa: BLE001
        return f"<error: {exc}>"


def sha256(path, limit=None):
    h = hashlib.sha256()
    with open(path, "rb") as fh:
        while True:
            chunk = fh.read(1 << 20)
            if not chunk:
                break
            h.update(chunk)
            if limit and h.digest_size and fh.tell() > limit:
                break
    return h.hexdigest()


def main() -> int:
    root = os.path.abspath(sys.argv[1] if len(sys.argv) > 1 else ".")
    pyc = os.environ.get("PYCROOT", "/home/ldz/pycircuit-workspace/pyCircuit-cpp-perf")
    davinci = os.environ.get(
        "DAVINCI", "/home/ldz/pycircuit-workspace/DavinciBaseLine"
    )
    perfetto = os.environ.get(
        "PERFETTO_UI", "https://ui.perfetto.dev"
    )

    pycc = os.path.join(pyc, ".pycircuit_out/toolchain/install/bin/pycc")
    meta = {
        "generated_at": datetime.now(timezone.utc).astimezone().isoformat(),
        "workspace": root,
        "pycircuit": {
            "path": pyc,
            "branch": sh(["git", "rev-parse", "--abbrev-ref", "HEAD"], cwd=pyc),
            "head": sh(["git", "rev-parse", "HEAD"], cwd=pyc),
            "head_subject": sh(["git", "log", "-1", "--pretty=%s"], cwd=pyc),
            "dirty": bool(sh(["git", "status", "--porcelain"], cwd=pyc)),
            "base_branch": sh(
                ["git", "rev-parse", "--abbrev-ref", "origin/ldz/feat/combine-split"],
                cwd=pyc,
            ),
            "base_commit": sh(["git", "rev-parse", "origin/ldz/feat/combine-split"], cwd=pyc),
        },
        "davinci": {
            "path": davinci,
            "head": sh(["git", "rev-parse", "HEAD"], cwd=davinci),
            "branch": sh(["git", "rev-parse", "--abbrev-ref", "HEAD"], cwd=davinci),
            "runner_source": os.path.join(davinci, "model/rtl/pycircuit_trace_runner.cpp"),
            "align_script": os.path.join(davinci, "model/rtl/run_pycircuit_trace_align.sh"),
        },
        "toolchain": {
            "pycc": os.path.join(pyc, ".pycircuit_out/toolchain/install/bin/pycc"),
            "pycc_sha256": sha256(pycc) if os.path.isfile(pycc) else None,
            "pycc_version": sh([pycc, "--version"])[:400] if os.path.isfile(pycc) else None,
            "clang": sh(["clang++", "--version"]).splitlines()[:2],
            "llvm_config": sh(["llvm-config-19", "--version"]),
            "cmake": sh(["cmake", "--version"]).splitlines()[:1],
        },
        "host": {
            "os": platform.platform(),
            "kernel": platform.release(),
            "cpu_model": next(
                (
                    l.split(":", 1)[1].strip()
                    for l in open("/proc/cpuinfo")
                    if l.startswith("model name")
                ),
                "?",
            ),
            "nproc": os.cpu_count(),
            "perf_version": sh(["perf", "--version"]),
            "perf_event_paranoid": open("/proc/sys/kernel/perf_event_paranoid").read().strip()
            if os.path.isfile("/proc/sys/kernel/perf_event_paranoid")
            else "?",
            "loadavg_at_collect": open("/proc/loadavg").read().strip(),
            "note": "perf_event_open 需要 root:CAP_PERFMON;本机以 sudo perf 运行。",
        },
        "profiling_method": {
            "tool": "perf record(sudo),cycles:u 事件",
            "callgraph": os.environ.get("CALLGRAPH", "fp(需 -fno-omit-frame-pointer 构建)")
            + " / dwarf(标准 -O3 构建亦可)",
            "frequency_hz": int(os.environ.get("PERF_HZ", "4000")),
            "perf_stat_events": [
                "cycles:u", "instructions:u", "branch-instructions:u",
                "branch-misses:u", "cache-references:u", "cache-misses:u",
            ],
            "converter": "tools/prof_tools.py(自研 perf script -> Perfetto protobuf)",
            "why": "容器内非 root 无法 perf_event_open;perf 采样为 CPU-time 采样,"
                   "宿主负载只影响墙钟,不影响 self/inclusive 占比。",
        },
        "viewer": {
            "perfetto_ui": perfetto,
            "open_hint": "打开 https://ui.perfetto.dev 拖入 *.pftrace(或直接拖 Chrome JSON);"
                         "Perfetto 里用 Flame Graph / 切片视图看调用栈,用 track 名区分 trace。",
        },
        "model_generation": {
            "generated_dir": os.path.join(root, "dev-cpp/cpp"),
            "mlir": os.path.join(root, "dev-cpp/v5_superscalar_v5_core.mlir"),
        },
    }

    # 生成模型的规模统计
    gen = meta["model_generation"]["generated_dir"]
    if os.path.isdir(gen):
        cpps = [f for f in os.listdir(gen) if f.endswith(".cpp")]
        loc = 0
        for f in cpps:
            try:
                with open(os.path.join(gen, f), errors="replace") as fh:
                    loc += sum(1 for _ in fh)
            except OSError:
                pass
        stats_path = os.path.join(gen, "compile_stats.json")
        meta["model_generation"].update(
            {
                "translation_units": len(cpps),
                "total_lines": loc,
                "comb_units": sum(1 for f in cpps if "__comb_" in f),
                "tick_units": sum(1 for f in cpps if "__tick" in f),
                "eval_units": sum(1 for f in cpps if "__eval" in f),
                "compile_stats": json.load(open(stats_path)) if os.path.isfile(stats_path) else None,
                "hashes": {
                    "manifest.json": sha256(os.path.join(gen, "manifest.json"))
                    if os.path.isfile(os.path.join(gen, "manifest.json"))
                    else None,
                },
            }
        )

    for key, path in (
        ("perf_data_example", os.path.join(root, "runs")),
        ("runner_binary", os.path.join(root, "cpp/pycircuit_trace_runner")),
        ("runner_binary_prof", os.path.join(root, "prof-ws/pycircuit_trace_runner")),
    ):
        if os.path.isfile(path):
            meta.setdefault("artifacts", {})[key] = {
                "path": path,
                "sha256": sha256(path),
                "bytes": os.path.getsize(path),
            }

    # 逐 trace 运行记录
    per_trace = []
    for base in ("runs", "runs-std"):
        d = os.path.join(root, base)
        if not os.path.isdir(d):
            continue
        for name in sorted(os.listdir(d)):
            run = os.path.join(d, name)
            if not os.path.isdir(run):
                continue
            rec = {"variant": base, "trace": name}
            for f in ("replay-timed.json", "replay.json", "conversion.json",
                      "perf.stat.txt", "perf-record.log"):
                p = os.path.join(run, f)
                if os.path.isfile(p):
                    rec[f] = (json.load(open(p)) if f.endswith(".json")
                              else open(p, errors="replace").read()[-2000:])
            rep = os.path.join(run, "report.json")
            if os.path.isfile(rep):
                r = json.load(open(rep))
                rec["samples"] = r.get("samples")
                rec["category_self"] = r.get("category_self")
                rec["top_self"] = r.get("self_top", [])[:5]
            for f in ("trace.pftrace", "flame.svg", "perf.data", "perf.script.raw.gz"):
                p = os.path.join(run, f)
                if os.path.isfile(p):
                    rec.setdefault("artifacts", {})[f] = {
                        "bytes": os.path.getsize(p),
                        "sha256": sha256(p) if os.path.getsize(p) < (64 << 20) else None,
                    }
            per_trace.append(rec)
    meta["runs"] = per_trace

    out_json = os.path.join(root, "metadata.json")
    with open(out_json, "w") as fh:
        json.dump(meta, fh, indent=2, ensure_ascii=False)

    md = [
        "# 元数据 — DavinciBaseLine C++ model 采样剖面",
        "",
        f"生成时间: {meta['generated_at']}",
        "",
        "## 被测代码",
        f"- pyCircuit: `{meta['pycircuit']['path']}` 分支 `{meta['pycircuit']['branch']}` "
        f"@ `{meta['pycircuit']['head'][:12]}` ({meta['pycircuit']['head_subject']})",
        f"- 基线(combine-split): `{meta['pycircuit']['base_commit'][:12]}`",
        f"- DavinciBaseLine: `{meta['davinci']['head'][:12]}` 分支 `{meta['davinci']['branch']}`",
        f"- pycc: {meta['toolchain']['pycc']} sha256={str(meta['toolchain']['pycc_sha256'])[:16]}…",
        "",
        "## 生成模型",
    ]
    mg = meta["model_generation"]
    if "translation_units" in mg:
        md += [
            f"- 目录: `{mg['generated_dir']}`",
            f"- TU 数: {mg['translation_units']}  总行数: {mg['total_lines']}",
            f"- 其中 comb 单元 {mg['comb_units']} / tick 单元 {mg['tick_units']} / eval 单元 {mg['eval_units']}",
        ]
    md += [
        "",
        "## 采样方法",
        f"- {meta['profiling_method']['tool']};callgraph: {meta['profiling_method']['callgraph']};"
        f"频率: {meta['profiling_method']['frequency_hz']} Hz",
        f"- {meta['profiling_method']['why']}",
        "",
        "## 宿主",
        f"- {meta['host']['cpu_model']} × {meta['host']['nproc']}",
        f"- {meta['host']['os']} (kernel {meta['host']['kernel']})",
        f"- perf: {meta['host']['perf_version']};perf_event_paranoid={meta['host']['perf_event_paranoid']}",
        f"- 采集时 loadavg: {meta['host']['loadavg_at_collect']}",
        "",
        "## 查看方式",
        f"- 上传 `*.pftrace` 到 {meta['viewer']['perfetto_ui']}(Flame Graph / 切片视图)",
        "- `summary.md` 是跨 trace 的瓶颈台账;`runs/<trace>/report.json` 是该 trace 的 self/inclusive 排名",
        "",
    ]
    with open(os.path.join(root, "METADATA.md"), "w") as fh:
        fh.write("\n".join(md) + "\n")

    print(json.dumps({"metadata": out_json, "runs": len(per_trace)},
                     ensure_ascii=False))
    return 0


if __name__ == "__main__":
    sys.exit(main())

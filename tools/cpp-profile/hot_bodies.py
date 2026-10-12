#!/usr/bin/env python3
"""把热点符号映射回生成代码:定位定义文件与函数体行数,量化“巨型融合函数”问题。

用法: hot_bodies.py summary.json dev-cpp/cpp [--top 30] [--out hot_bodies.json]
"""
from __future__ import annotations

import argparse
import json
import os
import re
import sys
from collections import defaultdict


def build_index(gen_dir: str):
    """扫描生成目录,建 symbol-suffix -> (file, body_lines) 索引。"""
    index = {}
    sizes = {}
    for fname in sorted(os.listdir(gen_dir)):
        if not fname.endswith((".cpp", ".hpp")):
            continue
        path = os.path.join(gen_dir, fname)
        try:
            text = open(path, errors="replace").read()
        except OSError:
            continue
        sizes[fname] = text.count("\n")
        for m in re.finditer(
            r"^(?:[\w:<>,*&\s]+?\s)?([A-Za-z_]\w*)::([A-Za-z_]\w*)\s*\(([^;{]*)\)\s*\{",
            text,
            re.M,
        ):
            ns, fn = m.group(1), m.group(2)
            brace = text.index("{", m.end() - 1)
            depth = 0
            end = brace
            for i in range(brace, len(text)):
                if text[i] == "{":
                    depth += 1
                elif text[i] == "}":
                    depth -= 1
                    if depth == 0:
                        end = i
                        break
            index.setdefault((ns, fn), (fname, text.count("\n", brace, end)))
    return index, sizes


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("summary")
    ap.add_argument("gen_dir")
    ap.add_argument("--top", type=int, default=30)
    ap.add_argument("--out", default=None)
    args = ap.parse_args()

    summary = json.load(open(args.summary))
    index, sizes = build_index(args.gen_dir)

    rows = []
    ranked = summary["aggregate"].get("top_self_trace_mean") or summary["aggregate"]["top_self"]
    for row in ranked[: args.top]:
        sym = row["symbol"]
        parts = re.sub(r"\(.*$", "", sym).split("::")
        hit = index.get((parts[-2], parts[-1])) if len(parts) >= 3 else None
        rows.append(
            {
                "symbol": sym,
                "pct": row["pct"],
                "samples": row.get("samples"),
                "defined_in": hit[0] if hit else None,
                "body_lines": hit[1] if hit else None,
                "file_lines": sizes.get(hit[0]) if hit else None,
            }
        )

    out = {
        "generated_dir": os.path.abspath(args.gen_dir),
        "generated_files": len(sizes),
        "generated_lines": sum(sizes.values()),
        "hot_symbols": rows,
        "body_line_gini": None,
    }
    # 巨型函数统计:生成目录里 body > 2000 行的函数top10
    huge = sorted(
        ((fn, ns, f, n) for (ns, fn), (f, n) in index.items() if n > 2000),
        key=lambda t: -t[3],
    )[:15]
    out["huge_functions"] = [
        {"symbol": f"{ns}::{fn}", "file": f, "body_lines": n} for fn, ns, f, n in huge
    ]
    if args.out:
        json.dump(out, open(args.out, "w"), indent=2)
    print(json.dumps(out, indent=2)[:4000])
    return 0


if __name__ == "__main__":
    sys.exit(main())

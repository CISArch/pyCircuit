#!/usr/bin/env python3
"""split_straggler.py — 按权重模型点名的巨 trace 做 hints 二分, 验证 straggler 下界解锁
A 级: csa/hca/swa 二分 (最大残留 = decode_front 4.88s)
B 级: 再二分 front (最大残留 = moe 3.48s)
naive 动态派发 12/16 线程"""
import json, os, subprocess, time
from concurrent.futures import ThreadPoolExecutor
import bench_p2w as B

SPLIT = "/tmp/v5_bench/ws_split"
os.makedirs(SPLIT, exist_ok=True)
GIANT = {"models_deepseek_v4_decode_csa", "models_deepseek_v4_decode_hca",
         "models_deepseek_v4_decode_swa"}
FRONT = {"models_deepseek_v3_2_deepseek_v3_2_decode_front"}

def make_chunk(src, cname, a, b):
    d = f"{SPLIT}/{cname}"; os.makedirs(d, exist_ok=True)
    with open(src) as f, open(f"{d}/hints.txt", "w") as g:
        for k, ln in enumerate(f):
            if k >= b: break
            if k >= a: g.write(ln)
    return f"{d}/hints.txt"

def taskset(halve_extra=False):
    tasks = []
    for p in B.HINTS:
        n = p.split("/")[-2]
        if n in GIANT or (halve_extra and n in FRONT):
            L = sum(1 for _ in open(p)); h = L // 2
            tasks += [(f"{n}_h{k}", make_chunk(p, f"{n}_h{k}", k * h, (k + 1) * h if k else h))
                      for k in range(2)]
        else:
            tasks.append((n, p))
    return tasks

def run(path, out):
    subprocess.run([B.CPP, path, str(B.DRAIN), out], check=True,
                   stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    return json.load(open(out))

def sweep(tasks, nthr, tag):
    args = [(p, f"{B.OUT}/sp_{tag}_{k}.json") for k, (n, p) in enumerate(tasks)]
    t0 = time.perf_counter()
    with ThreadPoolExecutor(nthr) as ex:
        rs = list(ex.map(lambda a: run(a[0], a[1]), args))
    wall = time.perf_counter() - t0
    cyc = sum(r["cycles"] for r in rs)
    longest = max(r["elapsed_ms"] for r in rs) / 1000
    return wall, cyc, longest

if __name__ == "__main__":
    for tag, extra in [("A", False), ("B", True)]:
        ts = taskset(extra)
        for nthr in ([12] if tag == "A" else [12, 16]):
            wall, cyc, longest = sweep(ts, nthr, f"{tag}{nthr}")
            print(f"[{tag}级 {nthr:>2}thr] 任务数={len(ts)}  wall={wall:>6.2f}s  "
                  f"最长块={longest:>5.2f}s  cycles={cyc:,}  agg={cyc/wall:>9,.0f} c/s")

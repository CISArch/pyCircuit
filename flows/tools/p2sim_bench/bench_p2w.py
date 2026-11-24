#!/usr/bin/env python3
"""bench_p2w.py — 借鉴 P2SIM(ggsim) deprecated/repcut2.rs 的权重划分法做多线程 trace 调度
移植对应关系:
  compute_inst_costs (静态指令开销估计)  ->  先运行 K 条小 trace 实测 elapsed_ms,
                                            线性回归 ms = a + b*hints 得全体权重
  weighted IOU (边权 = 逻辑块开销)       ->  trace 特征集 {模型族,规模桶,busy桶} 的 Jaccard
  partition() 贪心合并 + total_weight 阈值 -> LPT 装箱 + 每箱载荷上限 θ=τ*Σw/N
                                            + 组内按相关性排序 (同族相邻执行, 复用热缓存)
对照: naive 动态派发(ThreadPoolExecutor 队列) vs LPT 静态 vs LPT+相关性, 1/2/4/8 线程。"""
import json, subprocess, sys, time, glob, statistics, itertools, random, math
from concurrent.futures import ThreadPoolExecutor

CPP = "/tmp/v5_align/cpp/pycircuit_trace_runner"
HINTS = sorted(glob.glob("/tmp/v5_bench/ws/*/hints.txt"))
DRAIN = 512
OUT = "/tmp/v5_bench/p2w"
import os
os.makedirs(OUT, exist_ok=True)
K_PROFILE = 10          # 剖面用小 trace 数 (P2SIM: inst-cost 采样)
TAU = 1.15              # 箱载荷上限系数 (P2SIM total_weight threshold)
REPS = 2                # 每配置重复 (交错抵消机器漂移)

def name(i): return HINTS[i].split("/")[-2]

def static_size(i):
    return sum(1 for _ in open(HINTS[i]))

def run_one(i, tag):
    out = f"{OUT}/{tag}_{i}.json"
    t0 = time.perf_counter()
    subprocess.run([CPP, HINTS[i], str(DRAIN), out],
                   stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL, check=True)
    w = (time.perf_counter() - t0) * 1000
    d = json.load(open(out))
    return {"wall_ms": w, "cycles": d["cycles"], "busy": d["pe0_busy_cycles"],
            "runner_ms": d["elapsed_ms"], "hints": static_size(i)}

# ---------- Phase 1: 小 trace 剖面 ----------
def profile():
    by_size = sorted(range(len(HINTS)), key=static_size)
    small = by_size[:K_PROFILE]
    prof = {}
    for i in small:                       # 顺序跑, 干净的单任务计时
        prof[i] = run_one(i, "prof")
        print(f"  [profile] {name(i):<52} hints={prof[i]['hints']:>6} "
              f"ms={prof[i]['wall_ms']:>7.1f}")
    return prof

# ---------- Phase 2: 权重模型 (线性回归 ms = a + b*hints) ----------
def fit_weights(prof):
    xs = [p["hints"] for p in prof.values()]
    ys = [p["wall_ms"] for p in prof.values()]
    mx, my = statistics.mean(xs), statistics.mean(ys)
    b = sum((x - mx) * (y - my) for x, y in zip(xs, ys)) / sum((x - mx) ** 2 for x in xs)
    a = my - b * mx
    print(f"  [model] ms = {a:.1f} + {b:.4f}*hints  "
          f"(R2 fit on K={len(xs)}: fixed_cost={a:.1f}ms)")
    return lambda h: a + b * h
# ---------- 相关性特征集与 weighted IOU (P2SIM iou_col) ----------
def feat_set(i, busy_of):
    n = name(i); h = static_size(i)
    fam = n.split("_")[0]                          # examples / models
    model = "_".join(n.split("_")[:3]) if fam == "models" else fam
    size_b = min(9, int(math.log10(max(h, 1)) * 3))          # ~1/3 decade 桶
    busy = busy_of(i)
    busy_b = min(9, int(busy * 10))                           # 10% 桶
    return {("fam", fam), ("model", model), ("sz", size_b), ("busy", busy_b)}

def iou(A, B):                                     # Jaccard = P2SIM weighted-IOU 的无权版本
    u = len(A | B)
    return len(A & B) / u if u else 0.0

# ---------- Phase 3: 加权划分 (LPT + 阈值 + 相关性排序) ----------
def partition_weighted(order, wof, feat, n, use_corr=True):
    bins = [[] for _ in range(n)]
    loads = [0.0] * n
    total = sum(wof(i) for i in order)
    cap = TAU * total / n                           # P2SIM total_weight threshold
    for i in sorted(order, key=lambda i: -wof(i)):  # LPT: 大任务先装箱
        cands = [j for j in range(n) if loads[j] + wof(i) <= cap] or list(range(n))
        j = min(cands, key=lambda j: loads[j])      # 最轻箱优先 (无阈值回退=纯 LPT)
        bins[j].append(i)
        loads[j] += wof(i)
    if use_corr:                                     # 组内相关性排序: 贪心选与上一条 IOU 最高者
        for b in bins:
            if len(b) < 3: continue
            seq, rest = [b[0]], b[1:]
            while rest:
                nxt = max(rest, key=lambda i: iou(feat[seq[-1]], feat[i]))
                seq.append(nxt); rest.remove(nxt)
            b[:] = seq
    return bins

# ---------- Phase 4: 执行 ----------
def run_bin(bin_):                                  # 单线程顺序执行一个箱
    return [run_one(i, f"w{t}") for i, t in zip(bin_, range(len(bin_)))]

def sweep_static(bins, nthr):
    t0 = time.perf_counter()
    with ThreadPoolExecutor(nthr) as ex:
        res = list(ex.map(run_bin, bins))
    wall = time.perf_counter() - t0
    cyc = sum(r["cycles"] for b in res for r in b)
    per = [sum(r["wall_ms"] for r in b) for b in res]
    return wall, cyc, per

def sweep_naive(nthr):
    t0 = time.perf_counter()
    with ThreadPoolExecutor(nthr) as ex:
        res = list(ex.map(lambda i: run_one(i, f"n{nthr}"), range(len(HINTS))))
    wall = time.perf_counter() - t0
    cyc = sum(r["cycles"] for r in res)
    return wall, cyc, [r["wall_ms"] for r in res]

if __name__ == "__main__":
    print(f"traces={len(HINTS)}  K_profile={K_PROFILE}  tau={TAU}  reps={REPS}\n")
    print("== Phase 1/2: 小trace剖面 + 权重模型 (P2SIM compute_inst_costs 实测版)")
    prof = profile()
    wf = fit_weights(prof)
    wof = lambda i: wf(static_size(i))              # 权重: 由 hints 预测 (修复: 按索引调用的 bug)

    # busy% 预测: 剖面样本回归 busy ~ log10(hints)
    bx = [math.log10(p["hints"]) for p in prof.values()]
    by = [p["busy"] / p["cycles"] for p in prof.values()]
    mbx, mby = statistics.mean(bx), statistics.mean(by)
    kb = sum((x - mbx) * (y - mby) for x, y in zip(bx, by)) / sum((x - mbx) ** 2 for x in bx)
    bb = mby - kb * mbx
    busy_of = lambda i: max(0.0, min(1.0, kb * math.log10(static_size(i)) + bb))
    feat = {i: feat_set(i, busy_of) for i in range(len(HINTS))}

    print("\n== 预测权重 (Top10 大任务, 剖面未见)")
    for i in sorted(range(len(HINTS)), key=lambda i: -wof(i))[:10]:
        print(f"  {name(i):<52} hints={static_size(i):>6} pred_ms={wof(i):>9.1f}")

    # 单线程基线 + 实际权重 (预测质量评估的地面真值)
    print("\n== 1-thread baseline (兼作预测质量地面真值)")
    t0 = time.perf_counter()
    actual = [run_one(i, "base1") for i in range(len(HINTS))]
    wall1 = time.perf_counter() - t0
    cyc_all = sum(a["cycles"] for a in actual)
    errs = [abs(wf(a["hints"]) - a["wall_ms"]) / a["wall_ms"] for a in actual]
    big = [e for e, a in zip(errs, actual) if a["hints"] > 1000]
    print(f"  wall={wall1:.2f}s  agg={cyc_all/wall1:,.0f} c/s")
    print(f"  预测误差: mean={statistics.mean(errs)*100:.1f}%  "
          f"max={max(errs)*100:.1f}%  |  大trace(>1k hints): mean={statistics.mean(big)*100:.1f}%")
    json.dump({"wall1": wall1, "cycles": cyc_all,
               "per_trace": [{**a, "name": name(i), "pred_ms": wf(a["hints"])}
                             for i, a in enumerate(actual)]},
              open(f"{OUT}/baseline1.json", "w"), indent=1)

    results = []
    for nthr in [2, 4, 8]:
        bins = partition_weighted(list(range(len(HINTS))), wof, feat, nthr)
        bins_nc = partition_weighted(list(range(len(HINTS))), wof, feat, nthr, use_corr=False)
        loads = [sum(wof(i) for i in b) for b in bins]
        print(f"\n== {nthr} 线程  LPT+θ={TAU} 划分: 箱任务数={[len(b) for b in bins]} "
              f"预测载荷(ms)={[round(l) for l in loads]}")
        for rep in range(REPS):
            for mode, bs in [("naive", None), ("wpt", bins), ("lpt_nc", bins_nc)]:
                if mode == "naive":
                    wall, cyc, per = sweep_naive(nthr)
                else:
                    wall, cyc, per = sweep_static(bs, nthr)
                spread = (max(per) - min(per)) / max(per) * 100 if mode != "naive" else float("nan")
                agg = cyc / wall
                results.append({"thr": nthr, "mode": mode, "rep": rep,
                                "wall": round(wall, 3), "agg": round(agg), "spread%": round(spread, 1)})
                print(f"  rep{rep} {mode:<6} wall={wall:>7.2f}s agg={agg:>9,.0f} c/s "
                      f"{'箱载荷极差%=' + format(spread, '.1f') if mode != 'naive' else ''}")
    json.dump(results, open(f"{OUT}/results.json", "w"), indent=1)
    print(f"\nsaved -> {OUT}/results.json")

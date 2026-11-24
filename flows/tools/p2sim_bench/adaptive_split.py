#!/usr/bin/env python3
"""adaptive_split.py — 权重模型引导的自适应切分
每条 trace 份数 k_i = ceil(pred_ms_i / (Σpred/N)), 使每片 ≤ 均摊载荷;
naive 动态派发 8/12/16/24/32 线程 × 2 rep, 对比理论下界 max(片最大, Σ/N)"""
import json, math
import bench_p2w as B
import split_straggler as S

A, Bc = 22.8, 0.3734                     # 次日缓存模型 ms = 22.8 + 0.3734*hints
pred = lambda h: A + Bc * h

def plan_for(nthr):
    ws = [pred(B.static_size(i)) for i in range(len(B.HINTS))]
    total = sum(ws); cap = total / nthr
    plan = [(i, max(1, math.ceil(w / cap)), w) for i, w in enumerate(ws)]
    return plan, total, cap

def build(plan):
    tasks = []                            # (name, hints_path, pred_ms)
    for i, k, w in plan:
        p = B.HINTS[i]; n = p.split("/")[-2]
        if k == 1:
            tasks.append((n, p, w))
        else:
            L = sum(1 for _ in open(p)); step = L / k
            bnds = [round(step * j) for j in range(k + 1)]
            for j in range(k):
                h = bnds[j + 1] - bnds[j]
                tasks.append((f"{n}_c{j}",
                              S.make_chunk(p, f"{n}_c{j}", bnds[j], bnds[j + 1]),
                              pred(h)))
    return tasks

if __name__ == "__main__":
    res = []
    for nthr in [8, 12, 16, 24, 32]:
        plan, total, cap = plan_for(nthr)
        tasks = build(plan)
        cmax = max(t[2] for t in tasks)
        bound = max(cmax, total / nthr) / 1000
        for rep in range(2):
            wall, cyc, longest = S.sweep([(n, p) for n, p, _ in tasks], nthr, f"ad{nthr}")
            agg = cyc / wall
            res.append({"thr": nthr, "rep": rep, "tasks": len(tasks),
                        "wall": round(wall, 2), "agg": round(agg), "cycles": cyc,
                        "bound_s": round(bound, 2), "chunk_max_pred_s": round(cmax / 1000, 2)})
            print(f"[{nthr:>2}thr r{rep}] tasks={len(tasks):>3}  wall={wall:>5.2f}s  "
                  f"agg={agg:>9,.0f} c/s  bound={bound:.2f}s  达界={bound / wall * 100:.1f}%")
    json.dump(res, open(f"{B.OUT}/adaptive_split.json", "w"), indent=1)
    print(f"saved -> {B.OUT}/adaptive_split.json")

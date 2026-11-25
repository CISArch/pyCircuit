# DavinciBaseLine 34 条 trace 内部多线程划分适用性扫描（1/2/4 线程）

日期: 2026-11-19 ｜ 机器: 32 逻辑核 ｜ 脚本: `/tmp/v5_bench/per_trace_scan.py` ｜ 数据: `/tmp/v5_bench/p2w/per_trace_scan.json`
关联: [p2w_trace_sched.md](p2w_trace_sched.md)（任务级并行/切分）、[p2w_vs_naive_mt_comparison.md](../p2w_vs_naive_mt_comparison.md)

## 1. 目的与协议

逐 trace 评测流程（逐条跑、比较、再平均）下，判定**每条 trace 内部**是否值得做多线程划分。

- 方法: 将该 trace 的 hints 按行均分为 k 片，k 个进程**各自从 reset 独立回放**（片 = 合法回放流，零改 runner），单条 trace 独占机器窗口
- 扫描: k ∈ {1, 2, 4}，共 34 × 3 = 102 次测量（顺序执行，无跨 trace 干扰）
- 指标: `wall(k)` 墙钟、`sp_k = wall1/wall_k` 加速比、`eff4 = sp4/4` 四线程效率、`Δwall` 绝对节省、`膨胀% = cyc4/cyc1−1`（切片超计数）

**分级标准**: A 强适合（eff4 ≥ 0.90）｜ B 适合（0.70~0.89）｜ C 边缘（0.45~0.69）｜ D 不适合（< 0.45）

## 2. 总览

| 等级 | 条数 | hints 范围 | wall1 范围 | 平均 sp2 | 平均 eff4 | 膨胀中位 |
|:-:|--:|--:|--:|--:|--:|--:|
| **A 强适合** | 16 | 1,176~21,614 | 0.48~8.04s | 1.95 | 0.94 | 9% |
| **B 适合** | 10 | 385~2,433 | 0.17~0.94s | 1.87 | 0.81 | 35% |
| C 边缘 | 3 | 157~327 | 0.08~0.15s | 1.56 | 0.55 | 109% |
| D 不适合 | 5 | 8~77 | 0.03~0.05s | 1.18 | 0.32 | 240% |

**整体收益**（34 条逐个顺序跑的总墙钟）:

| 方案 | Σwall | 加速比 |
|---|--:|--:|
| 全部 k=1（单线程） | 49.98s | 1.00x |
| 全部 k=2 | 25.77s | **1.94x** |
| 全部 k=4 | 13.49s | **3.71x** |

## 3. 全 34 条明细（按 hints 降序）

| # | trace | hints | wall1 | wall2 | wall4 | sp2 | sp4 | eff4 | Δwall(ms) | 膨胀% | 等级 |
|--:|---|--:|--:|--:|--:|--:|--:|--:|--:|--:|:-:|
| 1 | `deepseek_v4_decode_csa` | 21,614 | 8.041 | 3.994 | 2.103 | 2.01 | 3.82 | 0.95 | 5,938 | 1 | A |
| 2 | `deepseek_v4_decode_hca` | 20,097 | 7.331 | 3.689 | 1.924 | 1.99 | 3.81 | 0.95 | 5,407 | 2 | A |
| 3 | `deepseek_v4_decode_swa` | 19,215 | 7.351 | 3.731 | 1.866 | 1.97 | 3.94 | 0.98 | 5,485 | 1 | A |
| 4 | `deepseek_v3_2_deepseek_v3_2_decode_front` | 12,891 | 4.727 | 2.502 | 1.257 | 1.89 | 3.76 | 0.94 | 3,470 | 2 | A |
| 5 | `qwen3_32b_qwen3_32b_decode_4d` | 9,238 | 3.398 | 1.775 | 0.910 | 1.91 | 3.73 | 0.93 | 2,488 | 3 | A |
| 6 | `deepseek_v4_moe` | 8,995 | 3.315 | 1.735 | 0.874 | 1.91 | 3.79 | 0.95 | 2,441 | 3 | A |
| 7 | `qwen3_32b_qwen3_32b_decode` | 7,880 | 2.882 | 1.542 | 0.784 | 1.87 | 3.68 | 0.92 | 2,098 | 4 | A |
| 8 | `qwen3_14b_decode_layer` | 4,250 | 1.569 | 0.839 | 0.423 | 1.87 | 3.71 | 0.93 | 1,146 | 6 | A |
| 9 | `deepseek_v3_2_deepseek_v3_2_decode_back` | 2,702 | 1.055 | 0.546 | 0.280 | 1.93 | 3.77 | 0.94 | 775 | 9 | A |
| 10 | `deepseek_v4_combine` | 2,433 | 0.938 | 0.481 | 0.266 | 1.95 | 3.53 | 0.88 | 672 | 12 | B |
| 11 | `deepseek_v4_decode_indexer` | 2,322 | 0.939 | 0.468 | 0.244 | 2.01 | 3.85 | 0.96 | 695 | 11 | A |
| 12 | `deepseek_v4_mtp_projection` | 2,214 | 0.871 | 0.449 | 0.237 | 1.94 | 3.68 | 0.92 | 634 | 14 | A |
| 13 | `qwen3_14b_decode_fwd` | 2,191 | 0.874 | 0.451 | 0.227 | 1.94 | 3.85 | 0.96 | 647 | 14 | A |
| 14 | `deepseek_v4_decode_compressor_ratio128` | 2,124 | 0.798 | 0.414 | 0.229 | 1.93 | 3.48 | 0.87 | 569 | 13 | B |
| 15 | `deepseek_v4_gate` | 1,932 | 0.787 | 0.396 | 0.209 | 1.99 | 3.77 | 0.94 | 578 | 14 | A |
| 16 | `deepseek_v4_hc_pre` | 1,884 | 0.711 | 0.369 | 0.203 | 1.93 | 3.50 | 0.88 | 508 | 16 | B |
| 17 | `ex_advanced_multi_proj` | 1,540 | 0.587 | 0.306 | 0.169 | 1.92 | 3.47 | 0.87 | 418 | 17 | B |
| 18 | `deepseek_v4_dispatch` | 1,537 | 0.627 | 0.302 | 0.170 | 2.08 | 3.69 | 0.92 | 457 | 17 | A |
| 19 | `deepseek_v4_prefill_qkv_proj_rope` | 1,313 | 0.533 | 0.278 | 0.148 | 1.92 | 3.60 | 0.90 | 385 | 20 | A |
| 20 | `deepseek_v4_expert_shared` | 1,176 | 0.484 | 0.247 | 0.135 | 1.96 | 3.59 | 0.90 | 349 | 20 | A |
| 21 | `deepseek_v4_expert_routed` | 1,063 | 0.422 | 0.217 | 0.128 | 1.94 | 3.30 | 0.82 | 294 | 28 | B |
| 22 | `deepseek_v4_decode_indexer_compressor` | 869 | 0.354 | 0.184 | 0.109 | 1.92 | 3.25 | 0.81 | 245 | 34 | B |
| 23 | `deepseek_v4_hc_head` | 669 | 0.275 | 0.147 | 0.089 | 1.87 | 3.09 | 0.77 | 186 | 44 | B |
| 24 | `deepseek_v4_decode_compressor_ratio4` | 585 | 0.244 | 0.135 | 0.080 | 1.81 | 3.05 | 0.76 | 164 | 43 | B |
| 25 | `deepseek_v4_prefill_indexer_compressor` | 473 | 0.196 | 0.115 | 0.070 | 1.70 | 2.80 | 0.70 | 126 | 59 | B |
| 26 | `ex_beginner_hello_world` | 385 | 0.167 | 0.095 | 0.059 | 1.76 | 2.83 | 0.71 | 108 | 61 | B |
| 27 | `ex_advanced_gemm_eltwise` | 327 | 0.145 | 0.083 | 0.057 | 1.75 | 2.54 | 0.64 | 88 | 74 | C |
| 28 | `ex_intermediate_gemm` | 169 | 0.084 | 0.056 | 0.040 | 1.50 | 2.10 | 0.53 | 44 | 109 | C |
| 29 | `deepseek_v4_hc_post` | 157 | 0.078 | 0.055 | 0.041 | 1.42 | 1.90 | 0.47 | 37 | 130 | C |
| 30 | `ex_intermediate_rms_norm` | 77 | 0.052 | 0.038 | 0.034 | 1.37 | 1.53 | 0.38 | 18 | 188 | D |
| 31 | `ex_beginner_matmul` | 73 | 0.048 | 0.037 | 0.033 | 1.30 | 1.45 | 0.36 | 15 | 189 | D |
| 32 | `ex_intermediate_rope` | 57 | 0.043 | 0.037 | 0.032 | 1.16 | 1.34 | 0.34 | 11 | 240 | D |
| 33 | `ex_intermediate_layer_norm` | 19 | 0.031 | 0.028 | 0.029 | 1.11 | 1.07 | 0.27 | 2 | 281 | D |
| 34 | `ex_intermediate_softmax` | 8 | 0.027 | 0.028 | 0.028 | 0.96 | 0.96 | 0.24 | -1 | 292 | D |

## 3b. 各 trace 聚合吞吐 cycles/s（c/s = cycles/wall，k 片并发时为 Σcyc/Σwall）

套件级（34 条逐跑，Σcyc/Σwall）: **@1thr = 11.6k → @2thr = 22.9k → @4thr = 46.1k**

| # | trace | hints | c/s@1thr | c/s@2thr | c/s@4thr | 吞吐倍数 | 真实加速 sp4 | 膨胀倍 | 等级 |
|--:|---|--:|--:|--:|--:|--:|--:|--:|:-:|
| 1 | `deepseek_v4_decode_csa` | 21,614 | 11,482 | 23,193 | 44,520 | 3.88x | 3.82x | 1.01x | A |
| 2 | `deepseek_v4_decode_hca` | 20,097 | 11,709 | 23,404 | 45,288 | 3.87x | 3.81x | 1.02x | A |
| 3 | `deepseek_v4_decode_swa` | 19,215 | 11,172 | 22,095 | 44,601 | 3.99x | 3.94x | 1.01x | A |
| 4 | `deepseek_v3_2_deepseek_v3_2_decode_front` | 12,891 | 11,683 | 22,272 | 44,819 | 3.84x | 3.76x | 1.02x | A |
| 5 | `qwen3_32b_qwen3_32b_decode_4d` | 9,238 | 11,687 | 22,545 | 44,863 | 3.84x | 3.73x | 1.03x | A |
| 6 | `deepseek_v4_moe` | 8,995 | 11,669 | 22,527 | 45,641 | 3.91x | 3.79x | 1.03x | A |
| 7 | `qwen3_32b_qwen3_32b_decode` | 7,880 | 11,754 | 22,224 | 44,728 | 3.81x | 3.68x | 1.04x | A |
| 8 | `qwen3_14b_decode_layer` | 4,250 | 11,795 | 22,533 | 46,376 | 3.93x | 3.71x | 1.06x | A |
| 9 | `deepseek_v3_2_deepseek_v3_2_decode_back` | 2,702 | 11,327 | 22,449 | 46,604 | 4.11x | 3.77x | 1.09x | A |
| 10 | `deepseek_v4_combine` | 2,433 | 11,479 | 23,418 | 45,346 | 3.95x | 3.53x | 1.12x | B |
| 11 | `deepseek_v4_decode_indexer` | 2,322 | 10,997 | 22,720 | 46,857 | 4.26x | 3.85x | 1.11x | A |
| 12 | `deepseek_v4_mtp_projection` | 2,214 | 11,249 | 22,702 | 47,228 | 4.20x | 3.68x | 1.14x | A |
| 13 | `qwen3_14b_decode_fwd` | 2,191 | 11,148 | 22,501 | 49,031 | 4.40x | 3.85x | 1.14x | A |
| 14 | `deepseek_v4_decode_compressor_ratio128` | 2,124 | 11,782 | 23,684 | 46,275 | 3.93x | 3.48x | 1.13x | B |
| 15 | `deepseek_v4_gate` | 1,932 | 10,910 | 22,699 | 46,799 | 4.29x | 3.77x | 1.14x | A |
| 16 | `deepseek_v4_hc_pre` | 1,884 | 11,789 | 24,057 | 47,709 | 4.05x | 3.50x | 1.16x | B |
| 17 | `ex_advanced_multi_proj` | 1,540 | 11,813 | 23,964 | 48,124 | 4.07x | 3.47x | 1.17x | B |
| 18 | `deepseek_v4_dispatch` | 1,537 | 11,048 | 24,265 | 47,800 | 4.33x | 3.69x | 1.17x | A |
| 19 | `deepseek_v4_prefill_qkv_proj_rope` | 1,313 | 11,330 | 23,165 | 48,959 | 4.32x | 3.60x | 1.20x | A |
| 20 | `deepseek_v4_expert_shared` | 1,176 | 11,252 | 23,275 | 48,556 | 4.32x | 3.59x | 1.20x | A |
| 21 | `deepseek_v4_expert_routed` | 1,063 | 11,618 | 24,424 | 49,203 | 4.23x | 3.30x | 1.28x | B |
| 22 | `deepseek_v4_decode_indexer_compressor` | 869 | 11,523 | 24,348 | 50,330 | 4.37x | 3.25x | 1.34x | B |
| 23 | `deepseek_v4_hc_head` | 669 | 11,807 | 24,816 | 52,382 | 4.44x | 3.09x | 1.44x | B |
| 24 | `deepseek_v4_decode_compressor_ratio4` | 585 | 11,750 | 24,207 | 51,275 | 4.36x | 3.05x | 1.43x | B |
| 25 | `deepseek_v4_prefill_indexer_compressor` | 473 | 12,362 | 24,591 | 55,171 | 4.46x | 2.80x | 1.59x | B |
| 26 | `ex_beginner_hello_world` | 385 | 12,162 | 25,684 | 55,492 | 4.56x | 2.83x | 1.61x | B |
| 27 | `ex_advanced_gemm_eltwise` | 327 | 12,462 | 25,639 | 55,123 | 4.42x | 2.54x | 1.74x | C |
| 28 | `ex_intermediate_gemm` | 169 | 13,893 | 28,321 | 60,850 | 4.38x | 2.10x | 2.09x | C |
| 29 | `deepseek_v4_hc_post` | 157 | 13,449 | 28,327 | 58,780 | 4.37x | 1.90x | 2.30x | C |
| 30 | `ex_intermediate_rms_norm` | 77 | 14,885 | 31,632 | 65,588 | 4.41x | 1.53x | 2.88x | D |
| 31 | `ex_beginner_matmul` | 73 | 15,958 | 32,270 | 67,091 | 4.20x | 1.45x | 2.89x | D |
| 32 | `ex_intermediate_rope` | 57 | 14,884 | 31,189 | 68,062 | 4.57x | 1.34x | 3.40x | D |
| 33 | `ex_intermediate_layer_norm` | 19 | 17,806 | 38,214 | 72,483 | 4.07x | 1.07x | 3.81x | D |
| 34 | `ex_intermediate_softmax` | 8 | 19,667 | 37,393 | 74,250 | 3.78x | 0.96x | 3.92x | D |

**吞吐表的三条规律**:

1. **恒等分解: 吞吐倍数 = 真实加速 sp4 × 膨胀倍（cyc4/cyc1）**。全表 34 条吞吐倍数都挤在 3.78~4.57x，但成分天差地别——A 级 csa `3.88x = 3.82x × 1.01`（几乎全是真实加速）；D 级 softmax `3.78x = 0.96x × 3.92`（墙钟没快，吞吐全靠多数了 2.9 倍的边界排水 cycles）
2. **⚠ c/s@4thr 表面值与真实收益反相关**: 最高者 softmax 74k、layer_norm 72k 全是 D 级伪吞吐（真实加速 ≤1.07x）；真实吞吐最高的恰是表观最低的 A 级巨 trace（csa 44.5k，sp4=3.82x、膨胀仅 1%）。**跨 trace 平均/比较切片态 c/s 必须先除以膨胀倍还原**，否则 D 级虚高 1.7~3.9 倍
3. **c/s@1thr 与规模无关（11~12.5k）**: runner 全量网表求值，每周期宿主成本与 trace 内容无关；小 trace 略高（13~20k）是因为其 cycles/hint 密度更高（如 softmax 66 cyc/hint vs csa 4.3 cyc/hint），固定开销被更密的周期摊薄

## 4. 分级名单

**A 强适合（16 条，4 线程近线性 0.90~0.98）**: `decode_csa/hca/swa`、`v3_2_decode_front/back`、`qwen3_32b_decode(+_4d)`、`qwen3_14b_decode_layer/fwd`、`v4_moe`、`v4_decode_indexer`、`v4_mtp_projection`、`v4_gate`、`v4_dispatch`、`v4_prefill_qkv_proj_rope`、`v4_expert_shared`

**B 适合（10 条，eff4 0.70~0.88）**: `v4_combine`、`v4_decode_compressor_ratio128/ratio4`、`v4_hc_pre`、`v4_hc_head`、`v4_expert_routed`、`v4_decode_indexer_compressor`、`v4_prefill_indexer_compressor`、`ex_advanced_multi_proj`、`ex_beginner_hello_world`

**C 边缘（3 条）**: `ex_advanced_gemm_eltwise`（327 hints, 2.54x）、`ex_intermediate_gemm`、`v4_hc_post`

**D 不适合（5 条，切分无收益甚至为负）**: `ex_intermediate_rms_norm`、`ex_beginner_matmul`、`ex_intermediate_rope`、`ex_intermediate_layer_norm`、`ex_intermediate_softmax`

## 5. 分界规律与机理

1. **适用性由 trace 规模单一决定，分界极清晰**:
   - 2 线程: hints ≥ ~300（wall1 ≥ ~0.15s）即有 1.7x+，几乎全部值得
   - 4 线程: hints ≥ ~1,100 → 近线性（A）；350~1,100 → 0.70~0.89（B）；< 350 → 边缘/不适合
2. **机理** = 每片固定成本主导小 trace：权重模型 `ms = 22.8 + 0.3734·hints` 的截距 22.8ms（进程启动 + hint 装载）在切 k 片后变为 k×22.8ms。wall1 = 0.027s 的 softmax 切 4 片 = 固定成本膨胀 4 倍，可变部分已趋零 → 无收益
3. **cycles 超计数随片数与占比恶化**: 每片独立回放自带 ~300~500 周期边界/排水开销。大 trace（csa/hca/swa）4 片仅 +1~2%，B 级 +12~61%，C/D 级 +74~292%
4. **等级与 trace 类型无关**: A/B 级横跨 attention（csa/hca/swa）、MoE、投影、norm 等所有模型族——适用性只看规模，不看语义

## 6. 逐 trace 评测流程的建议

1. **判定规则可直接落地**: `hints ≥ 350 → 切（k = min(4, ⌈wall1/0.15s⌉)）；hints < 350 → 不切`。34 条按此规则全 4 切后 Σwall = 13.5s（3.71x），D 级不切零损失（其 wall4 ≈ wall1）
2. **DUT 侧指标（cycles/逐 trace 比较语义）必须取 k=1 的值**: 切片的 cycles 有超计数（每片 +300~500 周期边界开销），膨胀率在小 trace 上不可接受；同理，**切片态 c/s 跨 trace 比较前必须除以膨胀倍还原**（§3b 规律 2: D 级表观吞吐虚高 1.7~3.9 倍）
3. **宿主吞吐指标用切分 wall**: 墙钟收益真实（csa 单条 8.04s → 2.10s）
4. 与任务级并行正交: 单机逐 trace 评测用本协议（3.71x）；全量吞吐评测用任务级+自适应切分（190k c/s）

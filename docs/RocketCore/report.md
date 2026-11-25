# v5_superscalar_v5_core — 34 PTO Trace 回放吞吐报告

日期: 2026-11-16 ｜ 机器: 32 逻辑核 ｜ 仿真负载: DavinciBaseLine 34 个 `.pto.trace`（hint 回放，drain=512）
后端: pyc C++ runner（pycircuit_trace_runner） vs Verilator runner（Vv5_superscalar_v5_core，单核）
正确性: 34/34 trace 两后端 cycles 逐条一致（0 mismatch）

## 1. 逐 trace 结果（单线程）

| # | trace | hints | cycles | PE0 busy | pyc ms | Verilator ms | pyc c/s | V c/s | 加速比 |
|--:|---|--:|--:|--:|--:|--:|--:|--:|--:|
| 1 | examples_advanced_gemm_eltwise | 327 | 1,807 | 62% | 150 | 396 | 12,047 | 4,563 | 2.64x |
| 2 | examples_advanced_multi_proj | 1540 | 6,934 | 82% | 620 | 1512 | 11,184 | 4,586 | 2.44x |
| 3 | examples_beginner_hello_world | 385 | 2,031 | 65% | 171 | 445 | 11,877 | 4,564 | 2.60x |
| 4 | examples_beginner_matmul | 73 | 766 | 29% | 52 | 171 | 14,731 | 4,480 | 3.29x |
| 5 | examples_intermediate_gemm | 169 | 1,167 | 49% | 90 | 255 | 12,967 | 4,576 | 2.83x |
| 6 | examples_intermediate_layer_norm | 19 | 552 | 7% | 30 | 130 | 18,400 | 4,246 | 4.33x |
| 7 | examples_intermediate_rms_norm | 77 | 774 | 30% | 49 | 181 | 15,796 | 4,276 | 3.69x |
| 8 | examples_intermediate_rope | 57 | 640 | 31% | 42 | 151 | 15,238 | 4,238 | 3.60x |
| 9 | examples_intermediate_softmax | 8 | 531 | 4% | 26 | 113 | 20,423 | 4,699 | 4.35x |
| 10 | models_deepseek_v3_2_deepseek_v3_2_decode_back | 2702 | 11,950 | 83% | 1066 | 2577 | 11,210 | 4,637 | 2.42x |
| 11 | models_deepseek_v3_2_deepseek_v3_2_decode_front | 12891 | 55,227 | 86% | 5049 | 12631 | 10,938 | 4,372 | 2.50x |
| 12 | models_deepseek_v4_combine | 2433 | 10,767 | 83% | 917 | 2462 | 11,742 | 4,373 | 2.68x |
| 13 | models_deepseek_v4_decode_compressor_ratio128 | 2124 | 9,402 | 83% | 808 | 2161 | 11,636 | 4,351 | 2.67x |
| 14 | models_deepseek_v4_decode_compressor_ratio4 | 585 | 2,867 | 74% | 240 | 660 | 11,946 | 4,344 | 2.75x |
| 15 | models_deepseek_v4_decode_csa | 21614 | 92,326 | 86% | 7943 | 20886 | 11,624 | 4,420 | 2.63x |
| 16 | models_deepseek_v4_decode_hca | 20097 | 85,839 | 86% | 7442 | 19400 | 11,534 | 4,425 | 2.61x |
| 17 | models_deepseek_v4_decode_indexer | 2322 | 10,326 | 83% | 933 | 2386 | 11,068 | 4,328 | 2.56x |
| 18 | models_deepseek_v4_decode_indexer_compressor | 869 | 4,079 | 78% | 344 | 948 | 11,858 | 4,303 | 2.76x |
| 19 | models_deepseek_v4_decode_swa | 19215 | 82,127 | 86% | 7058 | 18642 | 11,636 | 4,405 | 2.64x |
| 20 | models_deepseek_v4_dispatch | 1537 | 6,927 | 80% | 579 | 1591 | 11,964 | 4,354 | 2.75x |
| 21 | models_deepseek_v4_expert_routed | 1063 | 4,903 | 80% | 406 | 1131 | 12,076 | 4,335 | 2.79x |
| 22 | models_deepseek_v4_expert_shared | 1176 | 5,446 | 79% | 448 | 1251 | 12,156 | 4,353 | 2.79x |
| 23 | models_deepseek_v4_gate | 1932 | 8,586 | 83% | 730 | 1967 | 11,762 | 4,365 | 2.69x |
| 24 | models_deepseek_v4_hc_head | 669 | 3,247 | 73% | 266 | 753 | 12,207 | 4,312 | 2.83x |
| 25 | models_deepseek_v4_hc_post | 157 | 1,049 | 53% | 79 | 247 | 13,278 | 4,247 | 3.13x |
| 26 | models_deepseek_v4_hc_pre | 1884 | 8,382 | 83% | 722 | 1924 | 11,609 | 4,357 | 2.66x |
| 27 | models_deepseek_v4_moe | 8995 | 38,683 | 86% | 3315 | 8772 | 11,669 | 4,410 | 2.65x |
| 28 | models_deepseek_v4_mtp_projection | 2214 | 9,798 | 83% | 826 | 2246 | 11,862 | 4,362 | 2.72x |
| 29 | models_deepseek_v4_prefill_indexer_compressor | 473 | 2,423 | 68% | 192 | 564 | 12,620 | 4,296 | 2.94x |
| 30 | models_deepseek_v4_prefill_qkv_proj_rope | 1313 | 6,039 | 80% | 503 | 1400 | 12,006 | 4,314 | 2.78x |
| 31 | models_qwen3_14b_decode_fwd | 2191 | 9,743 | 82% | 822 | 2238 | 11,853 | 4,353 | 2.72x |
| 32 | models_qwen3_14b_decode_layer | 4250 | 18,506 | 84% | 1596 | 4255 | 11,595 | 4,349 | 2.67x |
| 33 | models_qwen3_32b_qwen3_32b_decode | 7880 | 33,874 | 86% | 2949 | 7753 | 11,487 | 4,369 | 2.63x |
| 34 | models_qwen3_32b_qwen3_32b_decode_4d | 9238 | 39,714 | 86% | 3470 | 8956 | 11,445 | 4,434 | 2.58x |

## 2. 平均与汇总

| 指标 | pyc C++ | Verilator | 倍数 |
|---|--:|--:|--:|
| 顺序总时间 (s) | 49.93 | 131.15 | 2.63x |
| 总仿真 cycles | 577,432 | 577,432 | 一致 |
| 聚合吞吐 (cycles/s) | 11,564 | 4,403 | 2.63x |
| 每条 trace 吞吐·算术平均 (c/s) | 12,572 | 4,394 | — |
| 每条 trace 吞吐·中位数 (c/s) | 11,860 | 4,359 | — |
| 单条加速比·算术平均 | — | — | 2.86x |
| 单条加速比·几何平均 | — | — | 2.83x |
| 单条加速比·范围 | — | — | 2.42x ~ 4.35x |

## 3. 多线程聚合吞吐（pyc C++ runner）

| 线程 | wall(s) | 聚合 cycles/s | 扩展比 | 相对 Verilator 单核 |
|--:|--:|--:|--:|--:|
| 1 | 51.36 | 11,243 | 1.00x | 2.47x |
| 2 | 26.28 | 21,976 | 1.95x | 4.83x |
| 4 | 13.66 | 42,269 | 3.76x | 9.28x |
| 5 | 11.68 | 49,455 | 4.40x | 10.86x |
| 6 | 9.86 | 58,534 | 5.21x | 12.85x |
| 7 | 8.03 | 71,886 | 6.39x | 15.79x |
| 8 | 8.54 | 67,632 | 6.02x | 14.85x |
| 16 | 8.19 | 70,565 | 6.28x | 15.50x |
| 24 | 8.03 | 71,963 | 6.40x | 15.81x |
| Verilator 单核 | 126.83 | 4,553 | — | 1.00x |

（16/24 线程为 2026-11-17 补测，每点两次取均值，单次波动 ±3%；5/6/7 线程与下表 Verilator 1-6 为同日补测，wall 地板见分析 3）

## 3b. Verilator runner 多线程（1-6 线程，进程级同测法）

| 线程 | wall(s) | 聚合 cycles/s | 每核 c/s | 扩展比 | 同线程 pyc 领先 |
|--:|--:|--:|--:|--:|--:|
| 1 | 127.69 | 4,522 | 4,522 | 1.00x | 2.49x |
| 2 | 66.18 | 8,726 | 4,363 | 1.93x | 2.52x |
| 3 | 44.33 | 13,026 | 4,342 | 2.88x | — |
| 4 | 34.21 | 16,880 | 4,220 | 3.73x | 2.51x |
| 5 | 28.69 | 20,124 | 4,025 | 4.45x | 2.46x |
| 6 | 23.99 | 24,070 | 4,012 | 5.32x | 2.43x |

## 4. 分析

1. **单线程绝对优势**: pyc C++ runner 顺序跑完 34 条共 49.9s，Verilator 需 131.2s（2.63x）。几何平均单条加速 2.83x，区间 2.42x~4.35x，全部 34 条均快于 Verilator。
2. **加速比与 trace 规模弱相关**: 最快 examples_intermediate_softmax（20,423 c/s），最慢 models_deepseek_v3_2_deepseek_v3_2_decode_front（10,938 c/s），差异主要来自核内活跃逻辑占比（PE0 busy 86% vs 4%）而非 trace 长度。
3. **多线程扩展（饱和拐点 = 6→7 线程）**: 2 线程 1.96x（98%/核），4 线程 3.76x（94%/核），5 线程 4.40x，6 线程 5.21x；**7 线程 71.9k 直接跳上平台**（与 8/16/24 线程的 67.6k~72.0k 同水平）——因为 6 线程均摊 8.3s ≈ 最长 trace models_deepseek_v4_decode_csa 的单进程时长 7.94s，7 线程起 wall 即被该任务锁死在 ~8.0s。聚合吞吐理论上限 ≈ 577,432/7.94 ≈ **72.7k c/s**，7/16/24 线程实测均贴住此上限（尾段其余核空闲）。
3b. **Verilator 进程级 1-6 线程近线性**（5.32x@6thr，每核仅降 11%）：其单进程跑最长 trace 需 20.9s，6 线程均摊 21.3s 尚未触及该地板，故仍处线性区（7 线程起才会撞 20.9s 地板）。同线程数下 pyc 领先稳定在 **2.43~2.52x**，与单线程比 2.47x 一致——两后端线性区内加速比守恒，pyc 的优势是纯粹的每周期求值效率差。
4. **极限对比**: pyc 自 7 线程起饱和于 ~72k c/s（Verilator 单核的 **~15.8 倍**、Verilator 6 线程的 3.0 倍）。继续加核无效，突破方向只有两条：对大 trace 用 `--skip-records/--max-records` 分段并行（消除单任务地板），或 Verilator `--threads`。
5. **一致性**: 两后端逐条 cycles 全等、hints 全部注入成功，吞吐对比基于行为等价仿真。

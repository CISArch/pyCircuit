#!/usr/bin/env python3
"""把多个 trace 的采样剖面合并成一个 Perfetto trace(每个 trace 一条进程轨道)。

每条 trace 在时间轴上顺序排列(而不是重叠),因此在 Perfetto UI 里可以:
  - 一次打开拿到全部 34 条 trace 的调用情况;
  - 用 “Flame Graph”/切片视图逐 trace 对比;
  - 按 track 过滤(每个 track 名即 trace 名)。

用法: merge_pftrace.py out.pftrace run_dir_1 run_dir_2 ...
      其中每个 run_dir 需含 perf.script.raw(hints:也可以直接给 perf script 文本)
"""
from __future__ import annotations

import os
import sys
import time

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from prof_tools import (  # noqa: E402
    CLOCK_MONOTONIC,
    clock_snapshot_packet,
    SEQ_INCREMENTAL_STATE_CLEARED,
    SEQ_NEEDS_INCREMENTAL_STATE,
    TYPE_SLICE_BEGIN,
    TYPE_SLICE_END,
    descriptor_packet_process,
    descriptor_packet_thread,
    interned_event_names,
    parse_perf_script,
    pb_bytes,
    pb_varint,
    stack_of,
    trace_packet,
)

GAP_NS = 50_000_000  # 每个 trace 之间留 50ms 间隙,便于区分


def main() -> int:
    out_path = sys.argv[1]
    dirs = sys.argv[2:]

    groups = []  # (label, [samples], base_ts_ns)
    for d in dirs:
        script = os.path.join(d, "perf.script.raw")
        if not os.path.isfile(script) and os.path.isfile(script + ".gz"):
            script += ".gz"
        if not os.path.isfile(script):
            continue
        label = os.path.basename(d.rstrip("/"))
        samples = [s for s in parse_perf_script(script) if s["frames"]]
        if not samples:
            continue
        samples.sort(key=lambda s: s["time"])
        groups.append((label, samples))

    if not groups:
        print("no samples", file=sys.stderr)
        return 1

    # 名称驻留
    names: dict[str, int] = {}
    for _, samples in groups:
        for s in samples:
            for f in stack_of(s):
                if f not in names:
                    names[f] = len(names) + 1
    pairs = [(iid, nm) for nm, iid in names.items()]

    out = bytearray()
    out += trace_packet(
        None,
        clock_snapshot_packet(
            int(time.clock_gettime(time.CLOCK_MONOTONIC) * 1e9),
            int(time.clock_gettime(time.CLOCK_BOOTTIME) * 1e9),
            time.time_ns(),
        ),
        SEQ_INCREMENTAL_STATE_CLEARED,
    )
    # 描述符:每个 trace 一个进程 + 每个 (trace, tid) 一个线程
    first = b""
    for idx, (label, samples) in enumerate(groups, start=1):
        first += pb_bytes(60, descriptor_packet_process(idx, idx * 10_000, label))
    out += trace_packet(None, first, SEQ_INCREMENTAL_STATE_CLEARED)
    first = b""
    track_uuids: dict[tuple[int, int], int] = {}
    for idx, (label, samples) in enumerate(groups, start=1):
        for tid in sorted({s["tid"] for s in samples}):
            uuid = idx * 10_000 + tid
            track_uuids[(idx, tid)] = uuid
            first += pb_bytes(
                60, descriptor_packet_thread(uuid, idx * 10_000, tid, f"{label} tid={tid}")
            )
    first += pb_bytes(12, interned_event_names(pairs))
    out += trace_packet(None, first, SEQ_NEEDS_INCREMENTAL_STATE)

    seq_flags = SEQ_NEEDS_INCREMENTAL_STATE
    cursor = 0
    spans = []
    for idx, (label, samples) in enumerate(groups, start=1):
        base = samples[0]["time"]
        dur = max(samples[-1]["time"] - base, 0.001)
        offset_ns = cursor - int(round(base * 1e9))
        start_ns = cursor
        state = {}
        for s in samples:
            ts = int(round(s["time"] * 1e9)) + offset_ns
            tid = s["tid"]
            uuid = track_uuids[(idx, tid)]
            want = list(reversed(stack_of(s)))
            cur = state.get(tid, [])
            common = 0
            while common < len(cur) and common < len(want) and cur[common] == want[common]:
                common += 1
            for depth in range(len(cur) - 1, common - 1, -1):
                out += trace_packet(
                    ts,
                    pb_bytes(
                        11,
                        pb_varint(9, TYPE_SLICE_END)
                        + pb_varint(10, names[cur[depth]])
                        + pb_varint(11, uuid),
                    ),
                    seq_flags,
                    clock_id=CLOCK_MONOTONIC,
                )
            for depth in range(common, len(want)):
                out += trace_packet(
                    ts,
                    pb_bytes(
                        11,
                        pb_varint(9, TYPE_SLICE_BEGIN)
                        + pb_varint(10, names[want[depth]])
                        + pb_varint(11, uuid),
                    ),
                    seq_flags,
                    clock_id=CLOCK_MONOTONIC,
                )
            state[tid] = want
        end_ns = int(round(samples[-1]["time"] * 1e9)) + offset_ns + 1_000_000
        for tid, cur in state.items():
            uuid = track_uuids[(idx, tid)]
            for depth in range(len(cur) - 1, -1, -1):
                out += trace_packet(
                    end_ns,
                    pb_bytes(
                        11,
                        pb_varint(9, TYPE_SLICE_END)
                        + pb_varint(10, names[cur[depth]])
                        + pb_varint(11, uuid),
                    ),
                    seq_flags,
                    clock_id=CLOCK_MONOTONIC,
                )
        cursor = end_ns + GAP_NS
        spans.append({"trace": label, "samples": len(samples), "start_ns": start_ns,
                      "end_ns": end_ns})

    with open(out_path, "wb") as fh:
        fh.write(out)
    print(f"wrote {out_path}: {len(out)} bytes, {len(groups)} traces, {len(pairs)} symbols")
    for s in spans:
        print(f"  {s['trace']}: {s['samples']} samples, {(s['end_ns']-s['start_ns'])/1e6:.1f} ms")
    return 0


if __name__ == "__main__":
    sys.exit(main())

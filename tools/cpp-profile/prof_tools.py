#!/usr/bin/env python3
"""perf.data -> Perfetto 原生 trace(.pftrace) + 火焰图 + 聚合报告(无第三方依赖)。

用途:在没有 traceconv(或 traceconv 不含 perf 支持)时,把 `perf script`
的文本采样流转换成 Perfetto UI 可直接打开的 protobuf trace,并产出聚合分析。

子命令:
  convert  perf-script.txt  out.pftrace  [--process NAME]
  json     perf-script.txt  out.json          # Chrome Trace Event 格式(备用)
  report   perf-script.txt  report.json       # self/inclusive 聚合 + 分类台账
  flame    perf-script.txt  out.svg [--title T]   # 交互式火焰图 SVG

perf script 文本按默认格式解析:样本行
  comm PID [CPU] TS: EVENT:  ...           (含 callchain 则随后是缩进的栈帧)
  帧行:  <indent>ADDR SYM+0xOFF (/path/dso)   或   <indent>ADDR (dso)
"""
from __future__ import annotations

import argparse
import html
import json
import re
import sys
from collections import defaultdict

# ----------------------------------------------------------------------------
# perf script 解析
# ----------------------------------------------------------------------------
SAMPLE_RE = re.compile(
    r"^(?P<comm>\S.*?)\s+(?P<pid>\d+)(?:/(?P<tid>\d+))?\s+"
    r"(?:\[(?P<cpu>\d+)\]\s+)?"
    r"(?P<time>\d+\.\d+):\s+"
    r"(?:(?P<event>[\w/:\-]+):\s*)?(?P<rest>.*)$"
)
FRAME_RE = re.compile(
    r"^\s+(?:(?P<addr>[0-9a-fA-F]+)\s+)?"
    r"(?P<sym>.*?)(?:\+0x(?P<off>[0-9a-fA-F]+))?"
    r"\s+\((?P<dso>[^)]*)\)\s*$"
)


def parse_perf_script(path: str):
    """yield (comm, pid, time_s, [frames]) ,frames 顺序为 叶->根。"""
    with open(path, "r", errors="replace") as fh:
        cur = None
        for line in fh:
            if not line.strip():
                if cur:
                    yield cur
                    cur = None
                continue
            if line[0] in " \t":
                if cur is None:
                    continue
                m = FRAME_RE.match(line.rstrip("\n"))
                if m:
                    sym = (m.group("sym") or "").strip()
                    off = m.group("off")
                    dso = (m.group("dso") or "").strip()
                    if not sym and m.group("addr"):
                        sym = f"0x{m.group('addr')}"
                    if off and sym and not sym.startswith("0x"):
                        sym = f"{sym}+0x{off}"
                    if sym:
                        cur["frames"].append((sym, dso))
                continue
            if cur:
                yield cur
            m = SAMPLE_RE.match(line.rstrip("\n"))
            if not m:
                cur = None
                continue
            cur = {
                "comm": m.group("comm").strip(),
                "pid": int(m.group("pid")),
                "tid": int(m.group("tid") or m.group("pid")),
                "cpu": int(m.group("cpu") or 0),
                "time": float(m.group("time")),
                "event": (m.group("event") or "").strip(),
                "frames": [],
            }
        if cur:
            yield cur


def clean_sym(sym: str) -> str:
    """去掉偏移、demangle 后的冗余空格,保留可读名。"""
    if "+0x" in sym and not sym.startswith("0x"):
        sym = sym.split("+0x", 1)[0]
    sym = sym.replace("(anonymous namespace)::", "")
    return sym.strip() or "[unknown]"


def stack_of(sample) -> list[str]:
    return [clean_sym(s) for s, _ in sample["frames"]]


# ----------------------------------------------------------------------------
# 最小 protobuf 编码(仅覆盖 Perfetto Trace 所需字段)
# ----------------------------------------------------------------------------
def _varint(v: int) -> bytes:
    out = bytearray()
    while True:
        b = v & 0x7F
        v >>= 7
        if v:
            out.append(b | 0x80)
        else:
            out.append(b)
            return bytes(out)


def _tag(field: int, wire: int) -> bytes:
    return _varint((field << 3) | wire)


def pb_varint(field: int, value: int) -> bytes:
    return _tag(field, 0) + _varint(value)


def pb_bytes(field: int, payload: bytes) -> bytes:
    return _tag(field, 2) + _varint(len(payload)) + payload


def pb_str(field: int, value: str) -> bytes:
    return pb_bytes(field, value.encode("utf-8"))


# Perfetto BuiltinClock.MONOTONIC = 3
CLOCK_MONOTONIC = 3
SEQ_INCREMENTAL_STATE_CLEARED = 1
SEQ_NEEDS_INCREMENTAL_STATE = 2

TYPE_SLICE_BEGIN = 1
TYPE_SLICE_END = 2
TYPE_INSTANT = 3
TYPE_COUNTER = 4


def track_event(name_iid: int, track_uuid: int, etype: int) -> bytes:
    out = pb_varint(9, etype) + pb_varint(10, name_iid) + pb_varint(11, track_uuid)
    return out


def trace_packet(timestamp_ns: int | None, payload: bytes, seq_flags: int,
                 seq_id: int = 1, clock_id: int | None = None) -> bytes:
    out = b""
    if timestamp_ns is not None:
        out += pb_varint(8, timestamp_ns)
    out += pb_varint(10, seq_id)
    out += payload
    out += pb_varint(13, seq_flags)
    if timestamp_ns is not None and clock_id is not None:
        out += pb_varint(58, clock_id)
    return pb_bytes(1, out)  # Trace.packet


def descriptor_packet_process(uuid: int, pid: int, name: str) -> bytes:
    desc = pb_varint(1, uuid) + pb_str(2, name)
    proc = pb_varint(1, pid) + pb_str(6, name)
    desc += pb_bytes(3, proc)
    return desc


def descriptor_packet_thread(uuid: int, pid: int, tid: int, name: str) -> bytes:
    desc = pb_varint(1, uuid) + pb_str(2, name)
    thread = pb_varint(1, pid) + pb_varint(2, tid) + pb_str(5, name)
    desc += pb_bytes(4, thread)
    return desc


def interned_event_names(pairs: list[tuple[int, str]]) -> bytes:
    inner = b""
    for iid, name in pairs:
        ev = pb_varint(1, iid) + pb_str(2, name)
        inner += pb_bytes(2, ev)  # InternedData.event_names
    return inner


def write_pftrace(samples, out_path: str, process_name: str = "pycircuit-trace-runner",
                  extra_tracks=None):
    """samples: 已按时间排序的解析结果;每个样本用它自己的 tid 作为 track。"""
    samples = list(samples)
    samples.sort(key=lambda s: s["time"])

    # 名称驻留表:每个唯一栈帧名一个 iid
    names: dict[str, int] = {}
    for s in samples:
        for f in stack_of(s):
            if f not in names:
                names[f] = len(names) + 1
    pairs = [(iid, nm) for nm, iid in names.items()]

    out = bytearray()
    pid = samples[0]["pid"] if samples else 1
    proc_uuid = 1
    thread_uuids: dict[int, int] = {}
    for tid in sorted({s["tid"] for s in samples}):
        thread_uuids[tid] = 1000 + tid

    # 1) 描述符 + 驻留数据(整条 sequence 的初始状态一次给全)
    first_payload = b""
    first_payload += pb_bytes(60, descriptor_packet_process(proc_uuid, pid, process_name))
    for tid, uuid in thread_uuids.items():
        first_payload += pb_bytes(
            60, descriptor_packet_thread(uuid, pid, tid, f"cpu-sim tid={tid}")
        )
    first_payload += pb_bytes(12, interned_event_names(pairs))
    out += trace_packet(None, first_payload, SEQ_INCREMENTAL_STATE_CLEARED)

    # 2) 采样 -> BEGIN/END 切片(栈间差分,保证嵌套一致)
    state: dict[int, list[str]] = defaultdict(list)
    prev_ts: dict[int, int] = {}
    started: dict[int, int] = {}
    seq_flags = SEQ_NEEDS_INCREMENTAL_STATE

    for s in samples:
        tid = s["tid"]
        ts = int(round(s["time"] * 1e9))
        stack = stack_of(s)          # 叶 -> 根
        want = list(reversed(stack))  # 根 -> 叶
        cur = state[tid]
        if prev_ts.get(tid) is None:
            prev_ts[tid] = ts

        # 公共前缀
        common = 0
        while common < len(cur) and common < len(want) and cur[common] == want[common]:
            common += 1
        # 收栈
        for depth in range(len(cur) - 1, common - 1, -1):
            out += trace_packet(
                ts,
                pb_bytes(11, track_event(names[cur[depth]], thread_uuids[tid], TYPE_SLICE_END)),
                seq_flags,
                clock_id=CLOCK_MONOTONIC,
            )
        # 开栈
        for depth in range(common, len(want)):
            out += trace_packet(
                ts,
                pb_bytes(11, track_event(names[want[depth]], thread_uuids[tid], TYPE_SLICE_BEGIN)),
                seq_flags,
                clock_id=CLOCK_MONOTONIC,
            )
        state[tid] = want
        prev_ts[tid] = ts

    # 3) 收尾:关掉所有未闭合切片
    end_ts = int(round((samples[-1]["time"] if samples else 0) * 1e9)) + 1_000_000
    for tid, cur in state.items():
        for depth in range(len(cur) - 1, -1, -1):
            out += trace_packet(
                end_ts,
                pb_bytes(11, track_event(names[cur[depth]], thread_uuids[tid], TYPE_SLICE_END)),
                seq_flags,
                clock_id=CLOCK_MONOTONIC,
            )

    with open(out_path, "wb") as fh:
        fh.write(out)
    return {
        "packets": out.count(b""),  # 占位,真实统计见下
        "event_names": len(pairs),
        "samples": len(samples),
        "threads": len(thread_uuids),
        "bytes": len(out),
    }


def write_chrome_json(samples, out_path: str, process_name: str = "trace-runner"):
    """Chrome Trace Event Format JSON —— Perfetto UI 亦可直接打开。"""
    samples = sorted(samples, key=lambda s: s["time"])
    events = []
    state: dict[int, list[str]] = defaultdict(list)
    base = samples[0]["time"] if samples else 0.0

    def ts(s):
        return (s["time"] - base) * 1e6  # us

    for s in samples:
        tid = s["tid"]
        want = list(reversed(stack_of(s)))
        cur = state[tid]
        common = 0
        while common < len(cur) and common < len(want) and cur[common] == want[common]:
            common += 1
        for depth in range(len(cur) - 1, common - 1, -1):
            events.append({"ph": "E", "ts": ts(s), "tid": tid, "pid": s["pid"]})
        for depth in range(common, len(want)):
            events.append(
                {
                    "ph": "B",
                    "ts": ts(s),
                    "tid": tid,
                    "pid": s["pid"],
                    "name": want[depth],
                    "cat": "sampled",
                }
            )
        state[tid] = want

    payload = {
        "traceEvents": events,
        "displayTimeUnit": "ms",
        "metadata": {"process_name": process_name, "source": "perf script (sampled)"},
    }
    with open(out_path, "w") as fh:
        json.dump(payload, fh)
    return {"events": len(events)}


# ----------------------------------------------------------------------------
# 聚合报告
# ----------------------------------------------------------------------------
# 生成代码的命名规律:
#   eval_comb_pass() / eval_comb_part_N()  -> 组合锥(eval 期的 comb 部分)
#   eval_pass() / eval_*                   -> eval 其它部分
#   tick_commit() / tick_compute()         -> 时序提交 / 时序计算
#   tick_*                                 -> tick 其它
# 顺序敏感:tick_commit/tick_compute 必须先于泛化的 tick 判断。
def classify(sym: str) -> str:
    s = sym.lower()
    if "tick_commit" in s or "commit" in s and "tick" in s:
        return "tick-commit"
    if "tick_compute" in s:
        return "tick-compute"
    if "eval_comb" in s or "comb_pass" in s or "comb_part" in s:
        return "comb"
    if "eval" in s:
        return "eval-other"
    if "tick" in s:
        return "tick-other"
    if "bits" in s or "words" in s or "dirtybitset" in s or "operator" in s or "bitset" in s:
        return "runtime-bits"
    if "memcpy" in s or "memmove" in s or "memset" in s or "malloc" in s or "free" in s:
        return "libc"
    if "ld-linux" in s or "dso" in s or "libc" in s:
        return "startup"
    return "other"


MODEL_HINT = ("pyc::gen::", "v5_", "pyc::runtime", "pycircuit")


def is_model_sample(sample) -> bool:
    """过滤进程启动/退出阶段(动态链接器等)的样本,只看被测模型。"""
    return any(any(h in f for h in MODEL_HINT) for f in stack_of(sample))


def build_report(samples, top: int = 40) -> dict:
    self_n: dict[str, int] = defaultdict(int)
    incl_n: dict[str, int] = defaultdict(int)
    self_dso: dict[str, str] = {}
    total = 0
    for s in samples:
        stack = stack_of(s)
        if not stack:
            continue
        total += 1
        self_n[stack[0]] += 1
        self_dso.setdefault(stack[0], s["frames"][0][1])
        for f in set(stack):
            incl_n[f] += 1

    def table(d, key=lambda kv: -kv[1], n=top):
        rows = sorted(d.items(), key=key)[:n]
        return [
            {
                "symbol": k,
                "samples": v,
                "pct": round(100.0 * v / total, 2) if total else 0.0,
                "category": classify(k),
                "dso": self_dso.get(k, ""),
            }
            for k, v in rows
        ]

    cat_self: dict[str, int] = defaultdict(int)
    cat_incl: dict[str, int] = defaultdict(int)
    for k, v in self_n.items():
        cat_self[classify(k)] += v
    for k, v in incl_n.items():
        cat_incl[classify(k)] += v

    return {
        "samples": total,
        "self_top": table(self_n),
        "inclusive_top": table(incl_n),
        "category_self": dict(sorted(cat_self.items(), key=lambda kv: -kv[1])),
        "category_inclusive": dict(sorted(cat_incl.items(), key=lambda kv: -kv[1])),
    }


def write_flame_svg(samples, out_path: str, title: str = "flamegraph", width: int = 1600):
    """自下而上聚合的静态火焰图(按样本数计宽)。"""
    total = 0
    frames: dict[tuple, int] = defaultdict(int)  # (path tuple) -> self samples
    for s in samples:
        stack = stack_of(s)
        if not stack:
            continue
        total += 1
        for depth in range(1, len(stack) + 1):
            frames[tuple(reversed(stack[:depth]))] += 1
    if total == 0:
        open(out_path, "w").write("<svg xmlns='http://www.w3.org/2000/svg'/>")
        return {}

    max_depth = max(len(k) for k in frames)
    row_h = 16
    height = (max_depth + 1) * row_h + 30
    rects = []
    for path, count in sorted(frames.items(), key=lambda kv: (len(kv[0]), kv[0])):
        w = max(1.0, width * count / total)
        y = height - 20 - len(path) * row_h
        x = 0.0
        # 位置:按前序宽度累加(近似;同一父下顺序稳定)
        prefix = 0.0
        for depth in range(1, len(path)):
            partial = tuple(path[:depth])
            prefix += sum(
                max(1.0, width * c / total)
                for p, c in frames.items()
                if len(p) == depth and p[: depth - 1] == partial[: depth - 1] and p < partial
            )
        x = prefix
        color = f"hsl({(hash(path[-1]) % 60) + 10},70%,{(45 + len(path) * 4) % 30 + 50}%)"
        label = html.escape(path[-1])[:60]
        rects.append(
            f"<g><rect x='{x:.1f}' y='{y}' width='{w:.1f}' height='{row_h - 1}' fill='{color}'>"
            f"<title>{label}: {count} samples ({100.0*count/total:.2f}%)</title></rect>"
            f"<text x='{x + 3:.1f}' y='{y + 11}' font-size='10' fill='#111'>{label}</text></g>"
        )
    svg = (
        f"<svg xmlns='http://www.w3.org/2000/svg' width='{width}' height='{height}'>"
        f"<rect width='100%' height='100%' fill='#f7f7f7'/>"
        f"<text x='8' y='16' font-size='13' font-family='monospace'>{html.escape(title)}"
        f" — {total} samples</text>" + "".join(rects) + "</svg>"
    )
    with open(out_path, "w") as fh:
        fh.write(svg)
    return {"frames": len(frames), "total_samples": total}


def main() -> int:
    ap = argparse.ArgumentParser()
    sub = ap.add_subparsers(dest="cmd", required=True)

    p = sub.add_parser("convert")
    p.add_argument("perf_script")
    p.add_argument("out")
    p.add_argument("--process", default="pycircuit-trace-runner")

    p = sub.add_parser("json")
    p.add_argument("perf_script")
    p.add_argument("out")

    p = sub.add_parser("report")
    p.add_argument("perf_script")
    p.add_argument("out")
    p.add_argument("--top", type=int, default=40)

    p = sub.add_parser("flame")
    p.add_argument("perf_script")
    p.add_argument("out")
    p.add_argument("--title", default="flamegraph")

    args = ap.parse_args()
    if args.cmd == "convert":
        info = write_pftrace(parse_perf_script(args.perf_script), args.out, args.process)
    elif args.cmd == "json":
        info = write_chrome_json(parse_perf_script(args.perf_script), args.out)
    elif args.cmd == "report":
        rep = build_report(list(parse_perf_script(args.perf_script)), args.top)
        with open(args.out, "w") as fh:
            json.dump(rep, fh, indent=2)
        info = {"samples": rep["samples"], "categories": rep["category_self"]}
    else:
        info = write_flame_svg(
            list(parse_perf_script(args.perf_script)), args.out, args.title
        )
    print(json.dumps(info))
    return 0


if __name__ == "__main__":
    sys.exit(main())

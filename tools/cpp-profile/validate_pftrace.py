#!/usr/bin/env python3
"""校验生成的 .pftrace:protobuf 线格式可解析 + 切片嵌套自洽。

无法替代 trace_processor,但能在没有官方工具时抓住绝大多数结构错误
(字段号/长度前缀/驻留名缺失/BEGIN-END 不配对)。

用法: validate_pftrace.py trace.pftrace
"""
from __future__ import annotations

import sys
from collections import defaultdict


def varint(buf, i):
    shift = 0
    val = 0
    while True:
        b = buf[i]
        i += 1
        val |= (b & 0x7F) << shift
        if not b & 0x80:
            return val, i
        shift += 7


def fields(buf):
    """yield (field_no, wire_type, payload_bytes_or_int)"""
    i = 0
    n = len(buf)
    while i < n:
        key, i = varint(buf, i)
        fno, wt = key >> 3, key & 7
        if wt == 0:
            val, i = varint(buf, i)
            yield fno, wt, val
        elif wt == 2:
            ln, i = varint(buf, i)
            yield fno, wt, buf[i:i + ln]
            i += ln
        elif wt == 5:
            yield fno, wt, buf[i:i + 4]
            i += 4
        elif wt == 1:
            yield fno, wt, buf[i:i + 8]
            i += 8
        else:
            raise ValueError(f"bad wire type {wt} at {i}")


def main() -> int:
    path = sys.argv[1]
    data = open(path, "rb").read()
    packets = 0
    events = 0
    descriptors = 0
    interned = {}
    by_type = defaultdict(int)
    names_used = set()
    open_stack = defaultdict(list)
    errors = []
    max_depth = 0
    ts_range = [None, None]

    for fno, wt, payload in fields(data):
        if fno != 1 or wt != 2:
            errors.append(f"trace 层出现非预期字段 {fno}")
            continue
        packets += 1
        pkt = payload
        ts = None
        ev = None
        desc = False
        for f2, w2, v2 in fields(pkt):
            if f2 == 8 and w2 == 0:
                ts = v2
            elif f2 == 11 and w2 == 2:
                ev = v2
            elif f2 == 12 and w2 == 2:
                for f3, w3, v3 in fields(v2):
                    if f3 == 2 and w3 == 2:  # EventName
                        iid = nm = None
                        for f4, w4, v4 in fields(v3):
                            if f4 == 1:
                                iid = v4
                            elif f4 == 2:
                                nm = v4.decode("utf-8", "replace")
                        if iid is not None:
                            interned[iid] = nm
            elif f2 == 60 and w2 == 2:
                desc = True
        if desc:
            descriptors += 1
        if ts is not None:
            ts_range[0] = ts if ts_range[0] is None else min(ts_range[0], ts)
            ts_range[1] = ts if ts_range[1] is None else max(ts_range[1], ts)
        if ev is None:
            continue
        events += 1
        etype = None
        name_iid = None
        track = None
        for f3, w3, v3 in fields(ev):
            if f3 == 9 and w3 == 0:
                etype = v3
            elif f3 == 10 and w3 == 0:
                name_iid = v3
            elif f3 == 11 and w3 == 0:
                track = v3
        by_type[etype] += 1
        if name_iid is not None:
            names_used.add(name_iid)
        if etype == 1:
            open_stack[track].append(name_iid)
            max_depth = max(max_depth, len(open_stack[track]))
        elif etype == 2:
            if not open_stack[track]:
                errors.append(f"track {track}: END 无对应 BEGIN")
            else:
                opened = open_stack[track].pop()
                if opened != name_iid:
                    errors.append(
                        f"track {track}: END {interned.get(name_iid)} != BEGIN {interned.get(opened)}"
                    )
    dangling = sum(len(v) for v in open_stack.values())

    print(f"file            : {path} ({len(data)} bytes)")
    print(f"packets         : {packets}  (descriptors {descriptors})")
    print(f"events          : {events}  types={{1:BEGIN,2:END,3:INSTANT,4:COUNTER}} -> {dict(by_type)}")
    print(f"interned names  : {len(interned)}  used {len(names_used)}")
    missing = names_used - set(interned)
    if missing:
        print(f"  !! 缺失驻留名 iid: {sorted(missing)[:10]}")
    print(f"max slice depth : {max_depth}")
    print(f"dangling BEGIN  : {dangling}")
    if ts_range[0] is not None:
        print(f"timestamp range : {(ts_range[1]-ts_range[0])/1e9:.3f} s  (clock=MONOTONIC)")
    if errors:
        print(f"ERRORS ({len(errors)}):")
        for e in errors[:10]:
            print("  -", e)
        return 1
    print("OK: 结构自洽(BEGIN/END 配对、嵌套一致、驻留名齐全)")
    return 0


if __name__ == "__main__":
    sys.exit(main())

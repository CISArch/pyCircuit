#!/usr/bin/env python3
"""FIRRTL 净化脚本：从 .fir 中去除 printf/assert/assume/cover 语句及空 when 块。

背景：较新的 firtool 构建会拒绝 chisel<=6.7 用 printf 编码的验证算子
（circt#6970）；这些语句在本场景下均为单行。删除后可能留下空的
`when` 块——FIRRTL 同样不接受空块，因此迭代剪枝直到不动点
（空块在 assert 模式中会嵌套出现）。

用法：strip_fir.py <输入.fir> <输出.fir>
"""
import re
import sys

HEADS = ('printf(', 'assert(', 'assume(', 'cover(')
WHEN_RE = re.compile(r'^(\s*)(when|else)\b.*:\s*(@\[.*\])?\s*$')

src, dst = sys.argv[1], sys.argv[2]
lines = [l.rstrip('\r\n') for l in open(src)]

# 第 1 步：删除验证语句（printf/assert/assume/cover，均为单行）
lines = [l for l in lines if not l.lstrip().startswith(HEADS)]

def indent(l):
    return len(l) - len(l.lstrip())

# 第 2 步：迭代剪除空 when/else 块，直到没有变化（不动点）
changed = True
while changed:
    changed = False
    out = []
    i = 0
    while i < len(lines):
        l = lines[i]
        m = WHEN_RE.match(l)
        if m:
            w = indent(l)
            # 收集块体（缩进 > w）直到缩进回落
            j = i + 1
            while j < len(lines) and (not lines[j].strip() or indent(lines[j]) > w):
                j += 1
            # 下一行非空且缩进 <= w
            nxt = lines[j] if j < len(lines) else None
            has_stmt_body = any(lines[k].strip() and indent(lines[k]) > w
                                for k in range(i + 1, j))
            if not has_stmt_body:
                # 空块：检查同缩进处是否有 `else` 续行
                if nxt and nxt.strip().startswith('else') and indent(nxt) == w:
                    # `when c:`（空）+ `else ...` -> 只保留 else 侧
                    if l.lstrip().startswith('when'):
                        # 丢弃 when 行；若其后是带体的 `else :`，
                        # 需要取反：改写为 when not(c)
                        cond = l.strip()[len('when'):-1].strip().rstrip(':').strip()
                        if nxt.strip() == 'else :':
                            out.append(' ' * w + f'when not({cond}) :')
                            changed = True
                            i += 1
                            continue
                # 普通空 when/else 行 -> 直接丢弃
                changed = True
                i += 1
                continue
        out.append(l)
        i += 1
    lines = out

open(dst, 'w').write('\n'.join(lines) + '\n')
print(f"kept {len(lines)} lines -> {dst}")

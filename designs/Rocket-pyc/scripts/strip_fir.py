#!/usr/bin/env python3
"""Drop printf/assert/assume/cover statements and empty when-blocks from .fir.

Newer firtool builds reject chisel<=6.7 printf-encoded verification ops
(circt#6970); those statements are single-line here. Removing them can leave
`when` blocks empty, which FIRRTL also rejects, so empty blocks are pruned
iteratively (they nest in assert patterns).
"""
import re
import sys

HEADS = ('printf(', 'assert(', 'assume(', 'cover(')
WHEN_RE = re.compile(r'^(\s*)(when|else)\b.*:\s*(@\[.*\])?\s*$')

src, dst = sys.argv[1], sys.argv[2]
lines = [l.rstrip('\r\n') for l in open(src)]

# 1) drop verification statements
lines = [l for l in lines if not l.lstrip().startswith(HEADS)]

def indent(l):
    return len(l) - len(l.lstrip())

# 2) prune empty when/else blocks until fixpoint
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
            # collect body lines (indent > w) until dedent
            j = i + 1
            while j < len(lines) and (not lines[j].strip() or indent(lines[j]) > w):
                j += 1
            # next non-empty line at indent <= w
            nxt = lines[j] if j < len(lines) else None
            has_stmt_body = any(lines[k].strip() and indent(lines[k]) > w
                                for k in range(i + 1, j))
            if not has_stmt_body:
                # empty block: check for `else` continuation at same indent
                if nxt and nxt.strip().startswith('else') and indent(nxt) == w:
                    # `when c:` (empty) + `else ...` -> keep else side only
                    if l.lstrip().startswith('when'):
                        # drop the when line; an `else :` following with body
                        # needs inversion: rewrite as when not(c)
                        cond = l.strip()[len('when'):-1].strip().rstrip(':').strip()
                        if nxt.strip() == 'else :':
                            out.append(' ' * w + f'when not({cond}) :')
                            changed = True
                            i += 1
                            continue
                # plain empty when/else line -> drop it
                changed = True
                i += 1
                continue
        out.append(l)
        i += 1
    lines = out

open(dst, 'w').write('\n'.join(lines) + '\n')
print(f"kept {len(lines)} lines -> {dst}")

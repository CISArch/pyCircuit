#!/bin/bash
# Status of the rocket-chip mill regeneration (see mill_elab.log).
cd "${ROCKET_CHIP_DIR:-/home/zhangzijie/rocket-chip}"
echo "== mill: $(pgrep -f mill >/dev/null && echo RUNNING || echo EXITED)"
echo "== fir output:"
ls -la generated-fir/ 2>/dev/null || echo "  (not yet)"
echo "== log tail:"
tr '\r' '\n' < mill_elab.log 2>/dev/null | grep -vE "^\s*$|Download" | tail -5

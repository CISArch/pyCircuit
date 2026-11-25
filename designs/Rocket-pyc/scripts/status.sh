#!/bin/bash
# 查看 rocket-chip mill 再生成进度（详见 mill_elab.log）：
# mill 进程是否存活、FIRRTL 产物是否出现、日志尾部摘要。
# 环境变量：ROCKET_CHIP_DIR 覆盖 rocket-chip 源码树位置。
cd "${ROCKET_CHIP_DIR:-/home/zhangzijie/rocket-chip}"
echo "== mill: $(pgrep -f mill >/dev/null && echo RUNNING || echo EXITED)"
echo "== fir output:"
ls -la generated-fir/ 2>/dev/null || echo "  (not yet)"
echo "== log tail:"
tr '\r' '\n' < mill_elab.log 2>/dev/null | grep -vE "^\s*$|Download" | tail -5

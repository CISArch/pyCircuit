#!/bin/bash
# MediumBOOM 裁剪构建：scalac 手工编译 BOOM v4（复用 rocket-chip
# manual-classes 产物 + /tmp/cp.txt classpath），elaborate 出 FIRRTL，
# strip 净化后交 firtool 生成 Verilog。
#
# 产物：
#   generated-fir/*.fir          —— diplomacy elaborate 原始 FIRRTL
#   generated-fir/*.stripped.fir —— 净化后（去 printf/assert，circt#6970）
#   generated-verilog/*.v        —— firtool 输出
#
# 环境变量：ROCKET_CHIP_DIR、BOOM_DIR（源码树）；缺省用默认路径。
set -euo pipefail

RC_DIR="${ROCKET_CHIP_DIR:-/home/zhangzijie/rocket-chip}"
BOOM_DIR="${BOOM_DIR:-/home/zhangzijie/riscv-boom}"
HERE="$(cd "$(dirname "$0")/.." && pwd)"   # designs/Boom-pyc

MAVEN=/home/zhangzijie/.cache/coursier/v1/https/repo1.maven.org/maven2
SCALAC_CP="$MAVEN/org/scala-lang/scala-compiler/2.13.12/scala-compiler-2.13.12.jar"
PLUGIN="$MAVEN/org/chipsalliance/chisel-plugin_2.13.12/6.7.0/chisel-plugin_2.13.12-6.7.0.jar"
RUNCP="$(cat /tmp/cp.txt)"
LIBCP="$(python3 - <<'EOF'
cp = open('/tmp/cp.txt').read().split(':')
keep = [p for p in cp if p.split('/')[-1] in (
    'scala-library-2.13.12.jar', 'scala-reflect-2.13.12.jar')]
print(':'.join(keep))
EOF
)"

RC_OUT="$RC_DIR/out/manual-classes"        # rocket-chip 已编译产物
OUT="$HERE/out/boom-classes"
mkdir -p "$OUT"
rm -rf "$OUT"/*

# 1. 编译 BOOM v4 源码 + 裁剪 config
find "$BOOM_DIR/src/main/scala/v4" -name '*.scala' > /tmp/boom_srcs.txt
echo "$HERE/scala/MediumBoomTrim.scala" >> /tmp/boom_srcs.txt
echo "$HERE/scala/ElaborateMain.scala" >> /tmp/boom_srcs.txt
echo "$HERE/scala/BoomTrimHarness.scala" >> /tmp/boom_srcs.txt
echo "[compile] boom v4 ($(wc -l < /tmp/boom_srcs.txt | tr -d ' ') files)"
java -Xss8m -Xmx8g -cp "$SCALAC_CP:$LIBCP" scala.tools.nsc.Main \
    -usejavacp -d "$OUT" -Xplugin:"$PLUGIN" -Ymacro-annotations \
    -classpath "$LIBCP:$RUNCP:$RC_OUT/macros:$RC_OUT/cde:$RC_OUT/diplomacy:$RC_OUT/hardfloat:$RC_OUT/rocket" \
    @/tmp/boom_srcs.txt

# 2. FIRRTL 细化（TestHarness 顶层 + 裁剪 config）
mkdir -p "$HERE/generated-fir" "$HERE/generated-verilog"
rm -f "$HERE"/generated-fir/*.fir "$HERE"/generated-fir/*.anno.json "$HERE"/generated-verilog/*.v
echo "[elaborate]"
# rocket-chip src/main/resources 提供 blackbox 资源（vsrc/plusarg_reader.v 等）
java -Xss16m -Xmx16g \
    -cp "$OUT:$RC_OUT/rocket:$RC_OUT/macros:$RC_OUT/cde:$RC_OUT/diplomacy:$RC_OUT/hardfloat:$RC_DIR/src/main/resources:$RUNCP" \
    boomtrim.ElaborateMain \
    "$HERE/generated-fir" \
    boomtrim.BoomTrimHarness \
    boomtrim.MediumBoomTrimConfig

# 3. 净化 + firtool → Verilog
echo "[strip + firtool]"
for fir in "$HERE"/generated-fir/*.fir; do
  name="$(basename "$fir" .fir)"
  python3 "$HERE/scripts/strip_fir.py" "$fir" "$HERE/generated-fir/$name.stripped.fir"
  firtool "$HERE/generated-fir/$name.stripped.fir" \
      --format=fir --verilog \
      --lowering-options=disallowLocalVariables,locationInfoStyle=none \
      -o "$HERE/generated-verilog/$name.v"
  # 后处理：yosys(0.67) 不支持 packed array 的赋值模式 '{...}。
  # 对简单常量列表，'{a,b,..} 与拼接 {a,b,..} 语义等价（首元素为最高切片）。
  python3 - "$HERE/generated-verilog/$name.v" <<'PYEOF'
import sys
p = sys.argv[1]
s = open(p).read()
n = s.count("'{")
if n:
    s = s.replace("'{", "{")
    open(p, "w").write(s)
print(f"fix_assign_pattern: {n} rewritten")
PYEOF
done
echo DONE

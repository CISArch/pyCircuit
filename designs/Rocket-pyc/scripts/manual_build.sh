#!/bin/bash
# rocket-chip 手工 scalac 构建（绕过 mill 的源码沙箱问题），随后做
# FIRRTL 细化（elaborate）。产物：generated-fir/*.fir（供 strip_fir.py
# + firtool 生成 Verilog，即"再生成路径"）。
# 环境变量：ROCKET_CHIP_DIR 覆盖 rocket-chip 源码树位置。
# 依赖：/tmp/cp.txt 为 mill 解析出的运行期 classpath（约 79 个 jar）。
set -euo pipefail
RC_DIR="${ROCKET_CHIP_DIR:-/home/zhangzijie/rocket-chip}"
cd "$RC_DIR"

MAVEN=/home/zhangzijie/.cache/coursier/v1/https/repo1.maven.org/maven2
SCALAC_CP="$MAVEN/org/scala-lang/scala-compiler/2.13.12/scala-compiler-2.13.12.jar"  # scala 编译器
PLUGIN="$MAVEN/org/chipsalliance/chisel-plugin_2.13.12/6.7.0/chisel-plugin_2.13.12-6.7.0.jar"  # Chisel 编译插件
# 三个 classpath 片段：仅 scala 库（LIBCP）/ Chisel+firrtl 相关库（CHISEL_CP）/ 完整运行期（RUNCP）
RUNCP="$(cat /tmp/cp.txt)"   # mill-resolved run classpath (79 jars)
LIBCP="$(python3 - <<'EOF'
cp = open('/tmp/cp.txt').read().split(':')
keep = [p for p in cp if p.split('/')[-1] in (
    'scala-library-2.13.12.jar', 'scala-reflect-2.13.12.jar')]
print(':'.join(keep))
EOF
)"
CHISEL_CP="$(python3 - <<'EOF'
cp = open('/tmp/cp.txt').read().split(':')
keep = [p for p in cp if any(k in p for k in (
    'chisel_2.13-6.7.0.jar', 'sourcecode', 'math3', 'commons-text',
    'commons-lang3', 'commons-io', 'firrtl', 'upickle', 'ujson', 'upack',
    'geny', 'os-lib', 'collections', 'macro-compat', 'jackson', 'json4s'))]
print(':'.join(keep))
EOF
)"

OUT=out/manual-classes
rm -rf "$OUT"; mkdir -p "$OUT"/{macros,cde,diplomacy,hardfloat,rocket}

# compile 函数：按依赖顺序逐子项目编译（macros -> cde -> diplomacy ->
# hardfloat -> rocket 主体）。
# 参数：<名称> <源文件列表> <输出目录> <编译期classpath> [chisel插件]
compile() { # name srclist outdir extracp [plugin]
  local name=$1 src=$2 dest=$3 cp=$4 plugin=${5:-}
  echo "[compile] $name ($(wc -l < "$src" | tr -d ' ') files)"
  local extra=()
  [ -n "$plugin" ] && extra=(-Xplugin:"$plugin")
  java -Xss8m -Xmx4g -cp "$SCALAC_CP:$LIBCP" scala.tools.nsc.Main \
      -usejavacp -d "$dest" "${extra[@]}" \
      -classpath "$LIBCP:$cp" "@$src"
}

find macros/src/main/scala -name '*.scala' > /tmp/m1.txt
compile macros /tmp/m1.txt "$OUT/macros" "$LIBCP"

find dependencies/cde/cde/src -name '*.scala' > /tmp/m2.txt
compile cde /tmp/m2.txt "$OUT/cde" "$LIBCP"

find dependencies/diplomacy/diplomacy/src -name '*.scala' > /tmp/m3.txt
compile diplomacy /tmp/m3.txt "$OUT/diplomacy" "$LIBCP:$CHISEL_CP:$OUT/cde" "$PLUGIN"

find dependencies/hardfloat/hardfloat/src/main/scala -name '*.scala' > /tmp/m4.txt
compile hardfloat /tmp/m4.txt "$OUT/hardfloat" "$LIBCP:$CHISEL_CP" "$PLUGIN"

find src/main/scala -name '*.scala' > /tmp/m5.txt
compile rocket /tmp/m5.txt "$OUT/rocket" \
    "$LIBCP:$RUNCP:$OUT/macros:$OUT/cde:$OUT/diplomacy:$OUT/hardfloat" "$PLUGIN"

# FIRRTL 细化：TestHarness 顶层 + DefaultSmallConfig，产物进 generated-fir/
echo "[elaborate]"
java -Xss16m -Xmx16g -cp "$OUT/rocket:$OUT/macros:$OUT/cde:$OUT/diplomacy:$OUT/hardfloat:$RUNCP" \
    freechips.rocketchip.diplomacy.Main elaborate \
    --dir "$RC_DIR/generated-fir" \
    --top freechips.rocketchip.system.TestHarness \
    --config freechips.rocketchip.system.DefaultSmallConfig
echo DONE

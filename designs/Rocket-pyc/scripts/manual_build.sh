#!/bin/bash
# Manual scalac build of rocket-chip (bypasses mill's source-sandbox issue).
set -euo pipefail
RC_DIR="${ROCKET_CHIP_DIR:-/home/zhangzijie/rocket-chip}"
cd "$RC_DIR"

MAVEN=/home/zhangzijie/.cache/coursier/v1/https/repo1.maven.org/maven2
SCALAC_CP="$MAVEN/org/scala-lang/scala-compiler/2.13.12/scala-compiler-2.13.12.jar"
PLUGIN="$MAVEN/org/chipsalliance/chisel-plugin_2.13.12/6.7.0/chisel-plugin_2.13.12-6.7.0.jar"
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

echo "[elaborate]"
java -Xss16m -Xmx16g -cp "$OUT/rocket:$OUT/macros:$OUT/cde:$OUT/diplomacy:$OUT/hardfloat:$RUNCP" \
    freechips.rocketchip.diplomacy.Main elaborate \
    --dir "$RC_DIR/generated-fir" \
    --top freechips.rocketchip.system.TestHarness \
    --config freechips.rocketchip.system.DefaultSmallConfig
echo DONE

// The named op and the broadcast must not split the run: all five ops fuse into
// one pyc.comb, and "mid" survives on a leaf alias.
func.func @Obs(%a : vector<2xi1>) -> i1 {
  %b = pyc.v_broadcast_dim %a to 2, 0 : vector<2xi1> -> vector<2x2xi1>
  %c = pyc.v_or_reduce %b {mode = "tree"} : vector<2x2xi1> -> i1
  %x = pyc.not %c : i1
  %y = pyc.not %x {pyc.name = "mid"} : i1
  %z = pyc.not %y : i1
  return %z : i1
}

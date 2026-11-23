// Small hierarchical fixture for --cpp-negedge-trim: one top module with two
// instances of a stateful leaf, a top-level reg, a delay line with a tap, and
// combs that read the input port (so eval() is sensitive to input changes).
module attributes {pyc.top = @trim_top, pyc.frontend.contract = "pycircuit"} {
  func.func @trim_leaf(%clk: !pyc.clock, %rst: !pyc.reset, %en: i1, %din: i8) -> i8
      attributes {arg_names = ["clk", "rst", "en", "din"], result_names = ["y"],
                  pyc.kind = "module", pyc.inline = "false", pyc.params = "{}",
                  pyc.base = "trim_leaf",
                  pyc.struct.metrics = "{\22ast_node_count\22:0,\22collection_count\22:0,\22collection_instance_count\22:0,\22estimated_inline_cost\22:0,\22hardware_call_count\22:0,\22instance_count\22:0,\22loop_count\22:0,\22module_call_count\22:0,\22module_family_collection_count\22:0,\22repeat_pressure\22:0,\22repeated_body_clusters\22:[],\22source_loc\22:0,\22state_alloc_count\22:0,\22state_call_count\22:0}",
                  pyc.struct.collections = "[]", pyc.value_params = [],
                  pyc.value_param_types = []} {
    %init = pyc.constant 0 : i8
    %q = pyc.reg %clk, %rst, %en, %din, %init : i8
    %y = pyc.add %q, %din : i8, i8 -> i8
    func.return %y : i8
  }

  func.func @trim_top(%clk: !pyc.clock, %rst: !pyc.reset, %ena: i1, %enb: i1, %din: i8)
      -> (i8, i8, i8, i8)
      attributes {arg_names = ["clk", "rst", "ena", "enb", "din"],
                  result_names = ["qtop", "qa", "tap", "mix"],
                  pyc.kind = "module", pyc.inline = "false", pyc.params = "{}",
                  pyc.base = "trim_top",
                  pyc.struct.metrics = "{\22ast_node_count\22:0,\22collection_count\22:0,\22collection_instance_count\22:0,\22estimated_inline_cost\22:0,\22hardware_call_count\22:0,\22instance_count\22:2,\22loop_count\22:0,\22module_call_count\22:2,\22module_family_collection_count\22:0,\22repeat_pressure\22:0,\22repeated_body_clusters\22:[],\22source_loc\22:0,\22state_alloc_count\22:0,\22state_call_count\22:0}",
                  pyc.struct.collections = "[]", pyc.value_params = [],
                  pyc.value_param_types = []} {
    %init = pyc.constant 0 : i8
    %din1 = pyc.comb(%din) : (i8) -> i8 {
    ^bb0(%arg0: i8):
      %one = pyc.constant 1 : i8
      %r = pyc.add %arg0, %one : i8, i8 -> i8
      pyc.yield %r : i8
    }
    %qtop = pyc.reg %clk, %rst, %ena, %din1, %init : i8
    %dl = pyc.delay_line %clk, %rst, %enb, %din1, %init {depth = 2 : i64} : i8
    %tap = pyc.delay_tap %dl {depth = 2 : i64} : i8
    %qa = pyc.instance %clk, %rst, %ena, %din1 {callee = @trim_leaf, name = "u_a", short_name = "u_a"} : (!pyc.clock, !pyc.reset, i1, i8) -> i8
    %qb = pyc.instance %clk, %rst, %enb, %tap {callee = @trim_leaf, name = "u_b", short_name = "u_b"} : (!pyc.clock, !pyc.reset, i1, i8) -> i8
    %mix = pyc.comb(%qa, %qb) : (i8, i8) -> i8 {
    ^bb0(%arg0: i8, %arg1: i8):
      %r = pyc.xor %arg0, %arg1 : i8, i8 -> i8
      pyc.yield %r : i8
    }
    func.return %qtop, %qa, %tap, %mix : i8, i8, i8, i8
  }
}

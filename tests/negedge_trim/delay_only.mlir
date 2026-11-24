// Regression for --cpp-negedge-trim: this leaf owns only a loopified
// delay line, so it runs through the generic compute_generic(clk) path and
// must keep receiving its falling edge.  The trim has to leave such a
// subtree on the serial code (no tick_negedge in the generated top).
module attributes {pyc.top = @dl_top, pyc.frontend.contract = "pycircuit"} {
  func.func @dl_leaf(%clk: !pyc.clock, %rst: !pyc.reset, %en: i1, %din: i8) -> i8
      attributes {arg_names = ["clk", "rst", "en", "din"], result_names = ["y"],
                  pyc.kind = "module", pyc.inline = "false", pyc.params = "{}",
                  pyc.base = "dl_leaf",
                  pyc.struct.metrics = "{\22ast_node_count\22:0,\22collection_count\22:0,\22collection_instance_count\22:0,\22estimated_inline_cost\22:0,\22hardware_call_count\22:0,\22instance_count\22:0,\22loop_count\22:0,\22module_call_count\22:0,\22module_family_collection_count\22:0,\22repeat_pressure\22:0,\22repeated_body_clusters\22:[],\22source_loc\22:0,\22state_alloc_count\22:0,\22state_call_count\22:0}",
                  pyc.struct.collections = "[]", pyc.value_params = [],
                  pyc.value_param_types = []} {
    %init = pyc.constant 0 : i8
    %dl = pyc.delay_line %clk, %rst, %en, %din, %init {depth = 2 : i64} : i8
    %tap = pyc.delay_tap %dl {depth = 2 : i64} : i8
    func.return %tap : i8
  }

  func.func @dl_top(%clk: !pyc.clock, %rst: !pyc.reset, %en: i1, %din: i8) -> (i8, i8)
      attributes {arg_names = ["clk", "rst", "en", "din"], result_names = ["q", "y"],
                  pyc.kind = "module", pyc.inline = "false", pyc.params = "{}",
                  pyc.base = "dl_top",
                  pyc.struct.metrics = "{\22ast_node_count\22:0,\22collection_count\22:0,\22collection_instance_count\22:0,\22estimated_inline_cost\22:0,\22hardware_call_count\22:0,\22instance_count\22:1,\22loop_count\22:0,\22module_call_count\22:1,\22module_family_collection_count\22:0,\22repeat_pressure\22:0,\22repeated_body_clusters\22:[],\22source_loc\22:0,\22state_alloc_count\22:0,\22state_call_count\22:0}",
                  pyc.struct.collections = "[]", pyc.value_params = [],
                  pyc.value_param_types = []} {
    %init = pyc.constant 0 : i8
    %q = pyc.reg %clk, %rst, %en, %din, %init : i8
    %y = pyc.instance %clk, %rst, %en, %din {callee = @dl_leaf, name = "u_l", short_name = "u_l"} : (!pyc.clock, !pyc.reset, i1, i8) -> i8
    func.return %q, %y : i8, i8
  }
}

module attributes {pyc.top = @parallel_tick_instances, pyc.frontend.contract = "pycircuit"} {
  func.func @tick_child(%clk: !pyc.clock, %rst: !pyc.reset, %incr: i8) -> i8 attributes {arg_names = ["clk", "rst", "incr"], result_names = ["acc"], pyc.kind = "module", pyc.inline = "false", pyc.base = "tick_child", pyc.params = "{}", pyc.value_params = [], pyc.value_param_types = [], pyc.struct.collections = "[]", pyc.struct.metrics = "{\22ast_node_count\22:24,\22collection_count\22:0,\22collection_instance_count\22:0,\22estimated_inline_cost\22:8,\22hardware_call_count\22:0,\22instance_count\22:0,\22loop_count\22:0,\22module_call_count\22:0,\22module_family_collection_count\22:0,\22repeat_pressure\22:0,\22repeated_body_clusters\22:[],\22source_loc\22:3,\22state_alloc_count\22:1,\22state_call_count\22:0}"} {
    %next = pyc.wire {pyc.name = "acc__next"} : i8
    %en = pyc.constant 1 : i1
    %zero = pyc.constant 0 : i8
    %q = pyc.reg %clk, %rst, %en, %next, %zero : i8
    %qa = pyc.alias %q {pyc.name = "acc"} : i8
    %sum = pyc.add %qa, %incr : i8, i8 -> i8
    pyc.assign %next, %sum : i8
    func.return %qa : i8
  }

  func.func @parallel_tick_instances(%clk: !pyc.clock, %rst: !pyc.reset, %incr: i8) -> (i8, i8, i8, i8, i8, i8, i8, i8) attributes {arg_names = ["clk", "rst", "incr"], result_names = ["q0", "q1", "q2", "q3", "q4", "q5", "q6", "q7"], pyc.kind = "module", pyc.inline = "false", pyc.base = "build", pyc.params = "{}", pyc.value_params = [], pyc.value_param_types = [], pyc.struct.collections = "[]", pyc.struct.metrics = "{\22ast_node_count\22:64,\22collection_count\22:0,\22collection_instance_count\22:0,\22estimated_inline_cost\22:48,\22hardware_call_count\22:16,\22instance_count\22:8,\22loop_count\22:0,\22module_call_count\22:8,\22module_family_collection_count\22:0,\22repeat_pressure\22:0,\22repeated_body_clusters\22:[],\22source_loc\22:12,\22state_alloc_count\22:0,\22state_call_count\22:0}"} {
    %c0 = pyc.constant 0 : i8
    %c1 = pyc.constant 1 : i8
    %c2 = pyc.constant 2 : i8
    %c3 = pyc.constant 3 : i8
    %c4 = pyc.constant 4 : i8
    %c5 = pyc.constant 5 : i8
    %c6 = pyc.constant 6 : i8
    %c7 = pyc.constant 7 : i8
    %s0 = pyc.add %incr, %c0 : i8, i8 -> i8
    %s1 = pyc.add %incr, %c1 : i8, i8 -> i8
    %s2 = pyc.add %incr, %c2 : i8, i8 -> i8
    %s3 = pyc.add %incr, %c3 : i8, i8 -> i8
    %s4 = pyc.add %incr, %c4 : i8, i8 -> i8
    %s5 = pyc.add %incr, %c5 : i8, i8 -> i8
    %s6 = pyc.add %incr, %c6 : i8, i8 -> i8
    %s7 = pyc.add %incr, %c7 : i8, i8 -> i8
    %q0 = pyc.instance %clk, %rst, %s0 {callee = @tick_child, name = "u0"} : (!pyc.clock, !pyc.reset, i8) -> i8
    %q1 = pyc.instance %clk, %rst, %s1 {callee = @tick_child, name = "u1"} : (!pyc.clock, !pyc.reset, i8) -> i8
    %q2 = pyc.instance %clk, %rst, %s2 {callee = @tick_child, name = "u2"} : (!pyc.clock, !pyc.reset, i8) -> i8
    %q3 = pyc.instance %clk, %rst, %s3 {callee = @tick_child, name = "u3"} : (!pyc.clock, !pyc.reset, i8) -> i8
    %q4 = pyc.instance %clk, %rst, %s4 {callee = @tick_child, name = "u4"} : (!pyc.clock, !pyc.reset, i8) -> i8
    %q5 = pyc.instance %clk, %rst, %s5 {callee = @tick_child, name = "u5"} : (!pyc.clock, !pyc.reset, i8) -> i8
    %q6 = pyc.instance %clk, %rst, %s6 {callee = @tick_child, name = "u6"} : (!pyc.clock, !pyc.reset, i8) -> i8
    %q7 = pyc.instance %clk, %rst, %s7 {callee = @tick_child, name = "u7"} : (!pyc.clock, !pyc.reset, i8) -> i8
    func.return %q0, %q1, %q2, %q3, %q4, %q5, %q6, %q7 : i8, i8, i8, i8, i8, i8, i8, i8
  }
}

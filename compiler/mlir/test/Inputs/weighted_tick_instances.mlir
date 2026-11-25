module attributes {pyc.top = @weighted_tick_instances, pyc.frontend.contract = "pycircuit"} {
  func.func @wlight(%clk: !pyc.clock, %rst: !pyc.reset, %x: i8) -> i8 attributes {arg_names = ["clk", "rst", "x"], result_names = ["acc"], pyc.kind = "module", pyc.inline = "false", pyc.base = "wlight", pyc.params = "{}", pyc.value_params = [], pyc.value_param_types = [], pyc.struct.collections = "[]", pyc.struct.metrics = "{\22ast_node_count\22:8,\22collection_count\22:0,\22collection_instance_count\22:0,\22estimated_inline_cost\22:4,\22hardware_call_count\22:0,\22instance_count\22:0,\22loop_count\22:0,\22module_call_count\22:0,\22module_family_collection_count\22:0,\22repeat_pressure\22:0,\22repeated_body_clusters\22:[],\22source_loc\22:3,\22state_alloc_count\22:1,\22state_call_count\22:0}"} {
    %next = pyc.wire {pyc.name = "acc__next"} : i8
    %en = pyc.constant 1 : i1
    %zero = pyc.constant 0 : i8
    %q = pyc.reg %clk, %rst, %en, %next, %zero : i8
    %qa = pyc.alias %q {pyc.name = "acc"} : i8
    %sum = pyc.add %qa, %x : i8, i8 -> i8
    pyc.assign %next, %sum : i8
    func.return %qa : i8
  }

  func.func @wheavy(%clk: !pyc.clock, %rst: !pyc.reset, %x: i8) -> i8 attributes {arg_names = ["clk", "rst", "x"], result_names = ["acc"], pyc.kind = "module", pyc.inline = "false", pyc.base = "wheavy", pyc.params = "{}", pyc.value_params = [], pyc.value_param_types = [], pyc.struct.collections = "[]", pyc.struct.metrics = "{\22ast_node_count\22:32,\22collection_count\22:0,\22collection_instance_count\22:0,\22estimated_inline_cost\22:26,\22hardware_call_count\22:0,\22instance_count\22:0,\22loop_count\22:0,\22module_call_count\22:0,\22module_family_collection_count\22:0,\22repeat_pressure\22:0,\22repeated_body_clusters\22:[],\22source_loc\22:3,\22state_alloc_count\22:1,\22state_call_count\22:0}"} {
    %next = pyc.wire {pyc.name = "acc__next"} : i8
    %en = pyc.constant 1 : i1
    %zero = pyc.constant 0 : i8
    %q = pyc.reg %clk, %rst, %en, %next, %zero : i8
    %qa = pyc.alias %q {pyc.name = "acc"} : i8
    %c1 = pyc.constant 1 : i8
    %c2 = pyc.constant 2 : i8
    %c3 = pyc.constant 3 : i8
    %c4 = pyc.constant 4 : i8
    %c5 = pyc.constant 5 : i8
    %c6 = pyc.constant 6 : i8
    %c7 = pyc.constant 7 : i8
    %c8 = pyc.constant 8 : i8
    %c9 = pyc.constant 9 : i8
    %c10 = pyc.constant 10 : i8
    %c11 = pyc.constant 11 : i8
    %c12 = pyc.constant 12 : i8
    %s1 = pyc.add %qa, %c1 : i8, i8 -> i8
    %s2 = pyc.add %s1, %x : i8, i8 -> i8
    %s3 = pyc.add %s2, %c2 : i8, i8 -> i8
    %s4 = pyc.add %s3, %x : i8, i8 -> i8
    %s5 = pyc.add %s4, %c3 : i8, i8 -> i8
    %s6 = pyc.add %s5, %x : i8, i8 -> i8
    %s7 = pyc.add %s6, %c4 : i8, i8 -> i8
    %s8 = pyc.add %s7, %x : i8, i8 -> i8
    %s9 = pyc.add %s8, %c5 : i8, i8 -> i8
    %s10 = pyc.add %s9, %x : i8, i8 -> i8
    %s11 = pyc.add %s10, %c6 : i8, i8 -> i8
    %s12 = pyc.add %s11, %x : i8, i8 -> i8
    %s13 = pyc.add %s12, %c7 : i8, i8 -> i8
    %s14 = pyc.add %s13, %x : i8, i8 -> i8
    %s15 = pyc.add %s14, %c8 : i8, i8 -> i8
    %s16 = pyc.add %s15, %x : i8, i8 -> i8
    %s17 = pyc.add %s16, %c9 : i8, i8 -> i8
    %s18 = pyc.add %s17, %x : i8, i8 -> i8
    %s19 = pyc.add %s18, %c10 : i8, i8 -> i8
    %s20 = pyc.add %s19, %x : i8, i8 -> i8
    %s21 = pyc.add %s20, %c11 : i8, i8 -> i8
    %s22 = pyc.add %s21, %x : i8, i8 -> i8
    %s23 = pyc.add %s22, %c12 : i8, i8 -> i8
    %s24 = pyc.add %s23, %x : i8, i8 -> i8
    pyc.assign %next, %s24 : i8
    func.return %qa : i8
  }

  func.func @wnest(%clk: !pyc.clock, %rst: !pyc.reset, %x: i8) -> i8 attributes {arg_names = ["clk", "rst", "x"], result_names = ["acc"], pyc.kind = "module", pyc.inline = "false", pyc.base = "wnest", pyc.params = "{}", pyc.value_params = [], pyc.value_param_types = [], pyc.struct.collections = "[]", pyc.struct.metrics = "{\22ast_node_count\22:16,\22collection_count\22:0,\22collection_instance_count\22:0,\22estimated_inline_cost\22:11,\22hardware_call_count\22:0,\22instance_count\22:1,\22loop_count\22:0,\22module_call_count\22:1,\22module_family_collection_count\22:0,\22repeat_pressure\22:0,\22repeated_body_clusters\22:[],\22source_loc\22:3,\22state_alloc_count\22:0,\22state_call_count\22:0}"} {
    %one = pyc.constant 1 : i8
    %s1 = pyc.add %x, %one : i8, i8 -> i8
    %s2 = pyc.add %s1, %one : i8, i8 -> i8
    %s3 = pyc.add %s2, %one : i8, i8 -> i8
    %acc = pyc.instance %clk, %rst, %s3 {callee = @wlight, name = "inner"} : (!pyc.clock, !pyc.reset, i8) -> i8
    func.return %acc : i8
  }

  func.func @weighted_tick_instances(%clk: !pyc.clock, %rst: !pyc.reset, %incr: i8) -> (i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8) attributes {arg_names = ["clk", "rst", "incr"], result_names = ["q0", "q1", "q2", "q3", "q4", "q5", "q6", "q7", "q8", "q9", "q10", "q11", "q12", "q13", "q14", "q15", "q16"], pyc.kind = "module", pyc.inline = "false", pyc.base = "build", pyc.params = "{}", pyc.value_params = [], pyc.value_param_types = [], pyc.struct.collections = "[]", pyc.struct.metrics = "{\22ast_node_count\22:96,\22collection_count\22:0,\22collection_instance_count\22:0,\22estimated_inline_cost\22:100,\22hardware_call_count\22:0,\22instance_count\22:17,\22loop_count\22:0,\22module_call_count\22:17,\22module_family_collection_count\22:0,\22repeat_pressure\22:0,\22repeated_body_clusters\22:[],\22source_loc\22:12,\22state_alloc_count\22:0,\22state_call_count\22:0}"} {
    %c0 = pyc.constant 0 : i8
    %c1 = pyc.constant 1 : i8
    %c2 = pyc.constant 2 : i8
    %c3 = pyc.constant 3 : i8
    %c4 = pyc.constant 4 : i8
    %c5 = pyc.constant 5 : i8
    %c6 = pyc.constant 6 : i8
    %c7 = pyc.constant 7 : i8
    %c8 = pyc.constant 8 : i8
    %c9 = pyc.constant 9 : i8
    %c10 = pyc.constant 10 : i8
    %c11 = pyc.constant 11 : i8
    %c12 = pyc.constant 12 : i8
    %c13 = pyc.constant 13 : i8
    %c14 = pyc.constant 14 : i8
    %c15 = pyc.constant 15 : i8
    %c16 = pyc.constant 16 : i8
    %x0 = pyc.add %incr, %c0 : i8, i8 -> i8
    %x1 = pyc.add %incr, %c1 : i8, i8 -> i8
    %x2 = pyc.add %incr, %c2 : i8, i8 -> i8
    %x3 = pyc.add %incr, %c3 : i8, i8 -> i8
    %x4 = pyc.add %incr, %c4 : i8, i8 -> i8
    %x5 = pyc.add %incr, %c5 : i8, i8 -> i8
    %x6 = pyc.add %incr, %c6 : i8, i8 -> i8
    %x7 = pyc.add %incr, %c7 : i8, i8 -> i8
    %x8 = pyc.add %incr, %c8 : i8, i8 -> i8
    %x9 = pyc.add %incr, %c9 : i8, i8 -> i8
    %x10 = pyc.add %incr, %c10 : i8, i8 -> i8
    %x11 = pyc.add %incr, %c11 : i8, i8 -> i8
    %x12 = pyc.add %incr, %c12 : i8, i8 -> i8
    %x13 = pyc.add %incr, %c13 : i8, i8 -> i8
    %x14 = pyc.add %incr, %c14 : i8, i8 -> i8
    %x15 = pyc.add %incr, %c15 : i8, i8 -> i8
    %x16 = pyc.add %incr, %c16 : i8, i8 -> i8
    %q0 = pyc.instance %clk, %rst, %x0 {callee = @wlight, name = "l0"} : (!pyc.clock, !pyc.reset, i8) -> i8
    %q1 = pyc.instance %clk, %rst, %x1 {callee = @wlight, name = "l1"} : (!pyc.clock, !pyc.reset, i8) -> i8
    %q2 = pyc.instance %clk, %rst, %x2 {callee = @wlight, name = "l2"} : (!pyc.clock, !pyc.reset, i8) -> i8
    %q3 = pyc.instance %clk, %rst, %x3 {callee = @wlight, name = "l3"} : (!pyc.clock, !pyc.reset, i8) -> i8
    %q4 = pyc.instance %clk, %rst, %x4 {callee = @wlight, name = "l4"} : (!pyc.clock, !pyc.reset, i8) -> i8
    %q5 = pyc.instance %clk, %rst, %x5 {callee = @wlight, name = "l5"} : (!pyc.clock, !pyc.reset, i8) -> i8
    %q6 = pyc.instance %clk, %rst, %x6 {callee = @wlight, name = "l6"} : (!pyc.clock, !pyc.reset, i8) -> i8
    %q7 = pyc.instance %clk, %rst, %x7 {callee = @wlight, name = "l7"} : (!pyc.clock, !pyc.reset, i8) -> i8
    %q8 = pyc.instance %clk, %rst, %x8 {callee = @wlight, name = "l8"} : (!pyc.clock, !pyc.reset, i8) -> i8
    %q9 = pyc.instance %clk, %rst, %x9 {callee = @wlight, name = "l9"} : (!pyc.clock, !pyc.reset, i8) -> i8
    %q10 = pyc.instance %clk, %rst, %x10 {callee = @wlight, name = "l10"} : (!pyc.clock, !pyc.reset, i8) -> i8
    %q11 = pyc.instance %clk, %rst, %x11 {callee = @wlight, name = "l11"} : (!pyc.clock, !pyc.reset, i8) -> i8
    %q12 = pyc.instance %clk, %rst, %x12 {callee = @wnest, name = "n0"} : (!pyc.clock, !pyc.reset, i8) -> i8
    %q13 = pyc.instance %clk, %rst, %x13 {callee = @wheavy, name = "h0"} : (!pyc.clock, !pyc.reset, i8) -> i8
    %q14 = pyc.instance %clk, %rst, %x14 {callee = @wheavy, name = "h1"} : (!pyc.clock, !pyc.reset, i8) -> i8
    %q15 = pyc.instance %clk, %rst, %x15 {callee = @wheavy, name = "h2"} : (!pyc.clock, !pyc.reset, i8) -> i8
    %q16 = pyc.instance %clk, %rst, %x16 {callee = @wheavy, name = "h3"} : (!pyc.clock, !pyc.reset, i8) -> i8
    func.return %q0, %q1, %q2, %q3, %q4, %q5, %q6, %q7, %q8, %q9, %q10, %q11, %q12, %q13, %q14, %q15, %q16 : i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8
  }
}

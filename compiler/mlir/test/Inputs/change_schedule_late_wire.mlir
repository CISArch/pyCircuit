module attributes {pyc.top = @top, pyc.frontend.contract = "pycircuit"} {
  func.func @child(%in: i1) -> i1 attributes {
      arg_names = ["in"], result_names = ["out"], pyc.kind = "module",
      pyc.inline = "false", pyc.params = "{}", pyc.base = "child",
      pyc.struct.metrics = "{\"ast_node_count\":0,\"collection_count\":0,\"collection_instance_count\":0,\"estimated_inline_cost\":0,\"hardware_call_count\":0,\"instance_count\":0,\"loop_count\":0,\"module_call_count\":0,\"module_family_collection_count\":0,\"repeat_pressure\":0,\"repeated_body_clusters\":[],\"source_loc\":0,\"state_alloc_count\":0,\"state_call_count\":0}",
      pyc.struct.collections = "[]", pyc.value_params = [],
      pyc.value_param_types = []} {
    %0 = pyc.comb(%in) : (i1) -> i1 {
    ^bb0(%arg0: i1):
      %1 = pyc.not %arg0 : i1
      pyc.yield %1 : i1
    }
    return %0 : i1
  }

  func.func @top(%in: i1) -> (i1, i1) attributes {
      arg_names = ["in"], result_names = ["before", "child_out"],
      pyc.kind = "module", pyc.inline = "false", pyc.params = "{}",
      pyc.base = "top",
      pyc.struct.metrics = "{\"ast_node_count\":0,\"collection_count\":0,\"collection_instance_count\":1,\"estimated_inline_cost\":0,\"hardware_call_count\":0,\"instance_count\":1,\"loop_count\":0,\"module_call_count\":1,\"module_family_collection_count\":0,\"repeat_pressure\":0,\"repeated_body_clusters\":[],\"source_loc\":0,\"state_alloc_count\":0,\"state_call_count\":0}",
      pyc.struct.collections = "[]", pyc.value_params = [],
      pyc.value_param_types = []} {
    %w = pyc.wire {pyc.name = "w"} : i1
    %0 = pyc.comb(%w) : (i1) -> i1 {
    ^bb0(%arg0: i1):
      %n = pyc.not %arg0 : i1
      pyc.yield %n : i1
    }
    %1 = pyc.instance %in {callee = @child, name = "u_child"} : (i1) -> i1
    pyc.assign %w, %1 : i1
    return %0, %1 : i1, i1
  }
}

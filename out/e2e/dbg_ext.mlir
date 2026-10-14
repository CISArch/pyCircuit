module attributes {pyc.frontend.contract = "pycircuit", pyc.top = @top} {
  pyc.ext_module @ext_dct8 {function_type = (i64, i1) -> (i64), ext_kind = "comb", latency = 0, pure = true} : (i64, i1) -> (i64)
  func.func @top(%arg0: i64, %arg1: i1) -> i64 attributes {
      arg_names = ["in", "valid"], result_names = ["out"], pyc.kind = "module",
      pyc.inline = "false", pyc.params = "{}", pyc.base = "top",
      pyc.struct.metrics = "{\"ast_node_count\":0,\"collection_count\":0,\"collection_instance_count\":0,\"estimated_inline_cost\":0,\"hardware_call_count\":0,\"instance_count\":0,\"loop_count\":0,\"module_call_count\":0,\"module_family_collection_count\":0,\"repeat_pressure\":0,\"repeated_body_clusters\":[],\"source_loc\":0,\"state_alloc_count\":0,\"state_call_count\":0}",
      pyc.struct.collections = "[]", pyc.value_params = [], pyc.value_param_types = []} {
    %y = pyc.instance %arg0, %arg1 {callee = @ext_dct8, name = "u_dct"} : (i64, i1) -> i64
    func.return %y : i64
  }
}

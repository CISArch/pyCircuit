module attributes {pyc.frontend.contract = "pycircuit", pyc.top = @top} {
  pyc.ext_module @ext_seq {ext_kind = "seq", latency = 1, pure = false} : (i64) -> i64
  func.func @top(%arg0: i64) -> i64 attributes {
      arg_names = ["in"], result_names = ["out"], pyc.kind = "module",
      pyc.inline = "false", pyc.params = "{}", pyc.base = "top",
      pyc.struct.metrics = "{\"ast_node_count\":0,\"collection_count\":0,\"collection_instance_count\":0,\"estimated_inline_cost\":0,\"hardware_call_count\":0,\"instance_count\":0,\"loop_count\":0,\"module_call_count\":0,\"module_family_collection_count\":0,\"repeat_pressure\":0,\"repeated_body_clusters\":[],\"source_loc\":0,\"state_alloc_count\":0,\"state_call_count\":0}",
      pyc.struct.collections = "[]", pyc.value_params = [], pyc.value_param_types = []} {
    %out = pyc.instance %arg0 {callee = @ext_seq} : (i64) -> i64
    func.return %out : i64
  }
}

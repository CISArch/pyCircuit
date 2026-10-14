module attributes {pyc.frontend.contract = "pycircuit", pyc.top = @top} {
  pyc.ext_module @ext_dct8 {function_type = (i64, i1) -> (i64), ext_kind = "comb", latency = 0, pure = true, verilog_top = "dct8", arg_names = ["in", "valid"], result_names = ["out"]} : (i64, i1) -> (i64)
  func.func @top(%x: i64) -> i64 attributes {arg_names = ["x"], result_names = ["y"], pyc.kind = "module", pyc.inline = "false", pyc.params = "{}", pyc.base = "top", pyc.struct.metrics = "{}", pyc.struct.collections = "[]", pyc.value_params = [], pyc.value_param_types = []} {
    %c = pyc.constant 1 : i1
    %y = pyc.instance %x, %c {callee = @ext_dct8, name = "u_dct"} : (i64, i1) -> i64
    func.return %y : i64
  }
}

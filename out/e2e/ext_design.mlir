module {
func.func @top(%clk: !pyc.clock, %rst: !pyc.reset, %x: i64) -> i64 attributes {arg_names = ["clk", "rst", "x"], result_names = ["y"]} {
  %v1 = pyc.constant 1 : i1
  %v2 = pyc.instance %x, %v1 {callee = @ext_dct8, name = "u_dct"} : (i64, i1) -> i64
  func.return %v2 : i64
}
  pyc.ext_module @ext_dct8 {function_type = (i64, i1) -> (i64), ext_kind = "comb", latency = 0, pure = true, verilog_top = "dct8", arg_names = ["in", "valid"], result_names = ["out"]} : (i64, i1) -> (i64)
}

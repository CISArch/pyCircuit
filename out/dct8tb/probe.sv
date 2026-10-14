module probe;
  initial begin
    $display("%0d %0d %0d %0d", dut_coef(0,0), dut_coef(0,1), dut_coef(1,0), dut_coef(7,7));
  end
  function integer dut_coef(input integer u, input integer x);
    begin
      case (u * 8 + x)
        0: dut_coef = 181;
        1: dut_coef = 181;
        8: dut_coef = 126;
        63: dut_coef = -36;
        default: dut_coef = 0;
      endcase
    end
  endfunction
endmodule

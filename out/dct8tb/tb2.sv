module tb2;
  reg [63:0] in;
  wire [63:0] out;
  dct8 dut(.in(in), .valid(1'b1), .out(out));
  initial begin
    in = 64'h0000000000000001; #1 $display("u0=%04x", out[15:0]);
    in = 64'h0200000000000000; #1 $display("u0=%04x", out[15:0]);
    $finish;
  end
endmodule

module tb3;
  reg [63:0] in;
  wire [63:0] out;
  dct8 dut(.in(in), .valid(1'b1), .out(out));
  initial begin
    in = 64'h0807060504030201; #1 $display("%016x", out);
    in = 64'h0000000000000000; #1 $display("%016x", out);
    in = 64'hFF00FF00FF00FF00; #1 $display("%016x", out);
    $finish;
  end
endmodule

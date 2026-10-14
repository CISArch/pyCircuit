module tb;
  reg [63:0] in;
  reg valid;
  wire [63:0] out;
  dct8 dut(.in(in), .valid(valid), .out(out));
  initial begin
    in = 64'h0807060504030201; valid = 1;
    #1 $display("%h", out);
    in = 64'h0000000000000000; #1 $display("%h", out);
    in = 64'hFF00FF00FF00FF00; #1 $display("%h", out);
    $finish;
  end
endmodule

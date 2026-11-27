// dct8.v — reference Verilog model for ext_dct8 (bit-exact with dct8.cpp).
// lane_u = sum(byte[x] * (u+1)) truncated to 16 bits; out packs lanes 0..3.
`timescale 1ns/1ps

/* verilator lint_off UNUSEDSIGNAL */
module dct8 (
  input  wire [63:0] in,
  input  wire        valid,   // interface port only; unused by the datapath
  output wire [63:0] out
);
  wire [7:0] b0 = in[7:0];
  wire [7:0] b1 = in[15:8];
  wire [7:0] b2 = in[23:16];
  wire [7:0] b3 = in[31:24];
  wire [7:0] b4 = in[39:32];
  wire [7:0] b5 = in[47:40];
  wire [7:0] b6 = in[55:48];
  wire [7:0] b7 = in[63:56];

  wire [15:0] sum8 = {8'b0, b0} + {8'b0, b1} + {8'b0, b2} + {8'b0, b3}
                    + {8'b0, b4} + {8'b0, b5} + {8'b0, b6} + {8'b0, b7};

  assign out = {sum8 << 2, (sum8 << 1) + sum8, sum8 << 1, sum8};
endmodule
/* verilator lint_on UNUSEDSIGNAL */

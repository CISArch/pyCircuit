// dct8.v — reference Verilog implementation of the ext_dct8 black box.
// Bit-exact with ext/dct8.cpp:
//   lane_u = sum over x of byte[x] * (u+1), truncated to 16 bits;
//   out packs lanes 0..3 into 16-bit fields.
// `valid` is a declared interface port (see ext_dct8.toml) but is not used by
// the datapath; it is kept as a port so the C++/Verilog bindings stay symmetric.
`timescale 1ns/1ps

module dct8 (
  input  wire [63:0] in,
  input  wire        valid,
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

  wire [15:0] sum8 = b0 + b1 + b2 + b3 + b4 + b5 + b6 + b7;
  wire [15:0] l0 = (1 * sum8);
  wire [15:0] l1 = (2 * sum8);
  wire [15:0] l2 = (3 * sum8);
  wire [15:0] l3 = (4 * sum8);

  assign out = {l3, l2, l1, l0};
endmodule

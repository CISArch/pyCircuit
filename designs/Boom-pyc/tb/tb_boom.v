// tb_boom.v — golden testbench for MediumBOOM trim harness (ST protocol).
// BoomTrimHarness integrates the core system plus an on-chip SimAXIMem, so
// external stimulus is clock/reset only; observable outputs are the AXI
// read-address channel taps io_mem_araddr / io_mem_arvalid.
// ST row: tick | io_mem_araddr | io_mem_arvalid  (sampled post-edge).
`timescale 1ns/1ps
module tb_Boom;
    reg clk = 0;
    reg reset = 1;
    wire [63:0] io_mem_araddr;
    wire        io_mem_arvalid;
    integer tick = 0;

    BoomTrimHarness dut (
        .clock(clk), .reset(reset),
        .io_mem_araddr(io_mem_araddr),
        .io_mem_arvalid(io_mem_arvalid)
    );

    always #5 clk = ~clk;

    initial begin
        #17;
        reset = 0;
    end

    initial begin
        #1;
        forever begin
            @(posedge clk);
            #1;
            tick = tick + 1;
            $display("ST %0d %0d %0d", tick, io_mem_araddr, io_mem_arvalid);
            if (tick >= 400) $finish;
        end
    end
endmodule

// cache.v — reference Verilog implementation of the ext_cache black box.
// Bit-exact with ext/cache_core.hpp (same cycle contract):
//   - hit/rdata/resp_valid are combinational on the current inputs;
//   - tag/data arrays and the miss FSM update on posedge (tick_commit).
//   2 sets x 2 ways, 16B lines, 32-bit aligned addresses, 128b data port.
//   addr[1:0] ignored | addr[3:2] word in line | addr[4] set | addr[31:5] tag
`timescale 1ns/1ps

module ext_cache (
  input  wire [31:0]  addr,
  input  wire         req_valid,
  input  wire         wr,
  input  wire [127:0] wdata,
  input  wire [15:0]  wmask,
  input  wire         resp_ready,   // no backpressure in this model; unused
  input  wire         flush,
  output reg  [127:0] rdata,
  output reg          hit,
  output reg          resp_valid,
  output reg          dirty_evict,
  input  wire         clk,
  input  wire         rst
);
  localparam SETS = 2, WAYS = 2, LINE_WORDS = 4;

  function [1:0] set_of(input [31:0] a);
    set_of = a[4:4] ? 2'd1 : 2'd0;
  endfunction
  function [26:0] tag_of(input [31:0] a);
    tag_of = a[31:5];
  endfunction
  function [1:0] word_of(input [31:0] a);
    word_of = a[3:2];
  endfunction

  // ---- state ----
  reg [26:0] line_tag   [0:SETS-1][0:WAYS-1];
  reg [31:0] line_word  [0:SETS-1][0:WAYS-1][0:LINE_WORDS-1];
  reg        line_valid [0:SETS-1][0:WAYS-1];
  reg        line_dirty [0:SETS-1][0:WAYS-1];
  reg [31:0] age        [0:SETS-1][0:WAYS-1];
  reg [31:0] now;

  // single-entry miss FSM, refill latency = 2
  reg         miss_pending;
  reg [31:0]  miss_addr;
  reg         miss_write;
  reg [127:0] miss_wdata;
  reg [15:0]  miss_wmask;
  reg         miss_dirty_evict;
  reg [1:0]   miss_timer;

  // backing store (next-level memory stand-in): 4K words
  reg [31:0] backing [0:4095];

  integer w, i;

  // hit lookup (combinational)
  reg       hit_found;
  reg [0:0] hit_way;
  always @* begin
    hit_found = 1'b0;
    hit_way = 1'b0;
    for (w = 0; w < WAYS; w = w + 1)
      if (line_valid[set_of(addr)][w] && line_tag[set_of(addr)][w] == tag_of(addr)) begin
        hit_found = 1'b1;
        hit_way = w[0:0];
      end
  end

  wire [127:0] hit_line = {line_word[set_of(addr)][hit_way][3],
                           line_word[set_of(addr)][hit_way][2],
                           line_word[set_of(addr)][hit_way][1],
                           line_word[set_of(addr)][hit_way][0]};

  // combinational outputs (eval view)
  always @* begin
    hit = 1'b0;
    resp_valid = 1'b0;
    dirty_evict = 1'b0;
    rdata = 128'd0;
    if (req_valid && !flush && hit_found) begin
      hit = 1'b1;
      resp_valid = 1'b1;
      rdata = hit_line;
      if (wr) begin
        case (word_of(addr))
          2'd0: rdata[31:0]   = wdata[31:0];
          2'd1: rdata[63:32]  = wdata[63:32];
          2'd2: rdata[95:64]  = wdata[95:64];
          2'd3: rdata[127:96] = wdata[127:96];
        endcase
      end
    end else if (miss_pending && !miss_write && miss_timer == 2'd0 && !flush) begin
      // read-miss completion response
      resp_valid = 1'b1;
      dirty_evict = miss_dirty_evict;
      rdata = {backing[{miss_addr[31:4], 2'd3}],
               backing[{miss_addr[31:4], 2'd2}],
               backing[{miss_addr[31:4], 2'd1}],
               backing[{miss_addr[31:4], 2'd0}]};
    end
  end

  // victim pick (invalid way first, then LRU)
  reg victim;
  always @* begin
    if (!line_valid[set_of(miss_addr)][0])      victim = 1'b0;
    else if (!line_valid[set_of(miss_addr)][1]) victim = 1'b1;
    else if (age[set_of(miss_addr)][0] <= age[set_of(miss_addr)][1]) victim = 1'b0;
    else victim = 1'b1;
  end

  // sequential update (tick_commit)
  always @(posedge clk) begin
    if (rst) begin
      for (i = 0; i < SETS; i = i + 1) begin
        line_valid[i][0] <= 1'b0;
        line_valid[i][1] <= 1'b0;
        line_dirty[i][0] <= 1'b0;
        line_dirty[i][1] <= 1'b0;
      end
      miss_pending <= 1'b0;
      miss_timer <= 2'd0;
      now <= 32'd0;
    end else begin
      now <= now + 32'd1;

      if (flush) begin
        for (i = 0; i < SETS; i = i + 1) begin
          line_valid[i][0] <= 1'b0;
          line_valid[i][1] <= 1'b0;
        end
        miss_pending <= 1'b0;
      end else begin
        // advance miss FSM
        if (miss_pending) begin
          if (miss_timer != 2'd0) begin
            miss_timer <= miss_timer - 2'd1;
          end else begin
            // fill
            miss_pending <= 1'b0;
            line_tag[set_of(miss_addr)][victim]   <= tag_of(miss_addr);
            line_valid[set_of(miss_addr)][victim] <= 1'b1;
            line_dirty[set_of(miss_addr)][victim] <= miss_write;
            age[set_of(miss_addr)][victim]        <= now;
            for (i = 0; i < LINE_WORDS; i = i + 1)
              line_word[set_of(miss_addr)][victim][i]
                <= backing[{miss_addr[31:4], i[1:0]}];
            if (miss_write) begin
              case (word_of(miss_addr))
                2'd0: line_word[set_of(miss_addr)][victim][0] <= miss_wdata[31:0];
                2'd1: line_word[set_of(miss_addr)][victim][1] <= miss_wdata[63:32];
                2'd2: line_word[set_of(miss_addr)][victim][2] <= miss_wdata[95:64];
                2'd3: line_word[set_of(miss_addr)][victim][3] <= miss_wdata[127:96];
              endcase
            end
          end
        end

        // accept new requests
        if (req_valid) begin
          if (hit_found) begin
            age[set_of(addr)][hit_way] <= now;
            if (wr) begin
              line_dirty[set_of(addr)][hit_way] <= 1'b1;
              case (word_of(addr))
                2'd0: line_word[set_of(addr)][hit_way][0] <= wdata[31:0];
                2'd1: line_word[set_of(addr)][hit_way][1] <= wdata[63:32];
                2'd2: line_word[set_of(addr)][hit_way][2] <= wdata[95:64];
                2'd3: line_word[set_of(addr)][hit_way][3] <= wdata[127:96];
              endcase
            end
          end else if (!miss_pending) begin
            // start miss; write back victim first if dirty
            miss_pending      <= 1'b1;
            miss_addr         <= addr;
            miss_write        <= wr;
            miss_wdata        <= wdata;
            miss_wmask        <= wmask;
            miss_timer        <= 2'd1; // 2 cycles to response
            miss_dirty_evict  <= line_valid[set_of(addr)][victim] && line_dirty[set_of(addr)][victim];
            if (line_valid[set_of(addr)][victim] && line_dirty[set_of(addr)][victim]) begin
              for (i = 0; i < LINE_WORDS; i = i + 1)
                backing[{line_tag[set_of(addr)][victim], set_of(addr), i[1:0]}]
                  <= line_word[set_of(addr)][victim][i];
            end
          end
        end
      end
    end
  end

endmodule

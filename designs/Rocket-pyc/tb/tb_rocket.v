// tb_rocket.v — golden testbench for the external Rocket core (ST protocol).
// imem: 1KiB ROM (imem[pc[11:2]]), 4-deep PC FIFO, resp held until resp_ready.
// dmem: 2KiB 64-bit-block RAM (dmem8[addr[11:3]]), req_ready=1, 2-cycle
//       registered resp (single-cycle valid pulse).  Store data arrives one
//       cycle after req fire on io_dmem_s1_data_data (core pre-shifts it);
//       loads answer with the whole 8-byte block (core selects subword).
// Program (any 4KiB-aligned reset vector lands on idx 0 via pc[11:2]):
//   addi x5,x0,5; addi x6,x0,3; add x7,x5,x6; sw x7,4(x0); lw x8,4(x0);
//   sw x8,12(x0); jal x0,0   — the second sw exposes the load result.
// ST: tick | 28 input cols (pre-edge, func-arg order) | 77 output cols.
`timescale 1ns/1ps
module tb_Rocket;
    reg clk = 0;
    reg reset = 1;
    wire i_irq_debug = 0, i_irq_mtip = 0, i_irq_msip = 0, i_irq_meip = 0;
    wire i_iresp_valid; wire [33:0] i_iresp_pc; wire [31:0] i_iresp_data;
    wire i_iresp_xcpt = 0, i_iresp_replay = 0;
    wire i_dreq_ready = 1, i_s2_nack = 0, i_dresp_valid;
    wire [5:0] i_dresp_tag; wire [63:0] i_dresp_data, i_dresp_byp;
    wire i_dresp_replay = 0, i_dresp_has_data, i_replay_next = 0;
    wire i_x_ma_ld = 0, i_x_ma_st = 0, i_x_pf_ld = 0, i_x_pf_st = 0;
    wire i_x_ae_ld = 0, i_x_ae_st = 0, i_ordered = 1;
    wire i_perf_release = 0, i_perf_grant = 0;
    wire o_might_req, o_ireq_valid, o_ireq_spec, o_iresp_ready;
    wire [33:0] o_ireq_pc;
    wire o_btb, o_bht, o_flush, o_dreq_valid, o_dv, o_s1_kill, o_dsigned;
    wire [33:0] o_daddr; wire [5:0] o_dtag; wire [4:0] o_dcmd; wire [1:0] o_dsize;
    wire [63:0] o_s1_data;
    wire o_ptw_debug, o_rocc_valid, o_wfi;
    wire [63:0] o_csr_value;
    wire [7:0] pmp_l, pmp_x, pmp_w, pmp_r;
    wire [15:0] pmp_a;
    wire [239:0] pmp_addr;
    wire [255:0] pmp_mask;

    Rocket dut (
        .clock(clk), .reset(reset),
        .io_interrupts_debug(i_irq_debug), .io_interrupts_mtip(i_irq_mtip),
        .io_interrupts_msip(i_irq_msip), .io_interrupts_meip(i_irq_meip),
        .io_imem_might_request(o_might_req), .io_imem_req_valid(o_ireq_valid),
        .io_imem_req_bits_pc(o_ireq_pc), .io_imem_req_bits_speculative(o_ireq_spec),
        .io_imem_resp_ready(o_iresp_ready), .io_imem_resp_valid(i_iresp_valid),
        .io_imem_resp_bits_pc(i_iresp_pc), .io_imem_resp_bits_data(i_iresp_data),
        .io_imem_resp_bits_xcpt_ae_inst(i_iresp_xcpt), .io_imem_resp_bits_replay(i_iresp_replay),
        .io_imem_btb_update_valid(o_btb), .io_imem_bht_update_valid(o_bht),
        .io_imem_flush_icache(o_flush),
        .io_dmem_req_ready(i_dreq_ready), .io_dmem_req_valid(o_dreq_valid),
        .io_dmem_req_bits_addr(o_daddr), .io_dmem_req_bits_tag(o_dtag),
        .io_dmem_req_bits_cmd(o_dcmd), .io_dmem_req_bits_size(o_dsize),
        .io_dmem_req_bits_signed(o_dsigned), .io_dmem_req_bits_dv(o_dv),
        .io_dmem_s1_kill(o_s1_kill), .io_dmem_s1_data_data(o_s1_data),
        .io_dmem_s2_nack(i_s2_nack), .io_dmem_resp_valid(i_dresp_valid),
        .io_dmem_resp_bits_tag(i_dresp_tag), .io_dmem_resp_bits_data(i_dresp_data),
        .io_dmem_resp_bits_replay(i_dresp_replay), .io_dmem_resp_bits_has_data(i_dresp_has_data),
        .io_dmem_resp_bits_data_word_bypass(i_dresp_byp), .io_dmem_replay_next(i_replay_next),
        .io_dmem_s2_xcpt_ma_ld(i_x_ma_ld), .io_dmem_s2_xcpt_ma_st(i_x_ma_st),
        .io_dmem_s2_xcpt_pf_ld(i_x_pf_ld), .io_dmem_s2_xcpt_pf_st(i_x_pf_st),
        .io_dmem_s2_xcpt_ae_ld(i_x_ae_ld), .io_dmem_s2_xcpt_ae_st(i_x_ae_st),
        .io_dmem_ordered(i_ordered), .io_dmem_perf_release(i_perf_release),
        .io_dmem_perf_grant(i_perf_grant), .io_ptw_status_debug(o_ptw_debug),
        .io_ptw_pmp_0_cfg_l(pmp_l[0]), .io_ptw_pmp_1_cfg_l(pmp_l[1]),
        .io_ptw_pmp_2_cfg_l(pmp_l[2]), .io_ptw_pmp_3_cfg_l(pmp_l[3]),
        .io_ptw_pmp_4_cfg_l(pmp_l[4]), .io_ptw_pmp_5_cfg_l(pmp_l[5]),
        .io_ptw_pmp_6_cfg_l(pmp_l[6]), .io_ptw_pmp_7_cfg_l(pmp_l[7]),
        .io_ptw_pmp_0_cfg_a(pmp_a[1:0]), .io_ptw_pmp_1_cfg_a(pmp_a[3:2]),
        .io_ptw_pmp_2_cfg_a(pmp_a[5:4]), .io_ptw_pmp_3_cfg_a(pmp_a[7:6]),
        .io_ptw_pmp_4_cfg_a(pmp_a[9:8]), .io_ptw_pmp_5_cfg_a(pmp_a[11:10]),
        .io_ptw_pmp_6_cfg_a(pmp_a[13:12]), .io_ptw_pmp_7_cfg_a(pmp_a[15:14]),
        .io_ptw_pmp_0_cfg_x(pmp_x[0]), .io_ptw_pmp_1_cfg_x(pmp_x[1]),
        .io_ptw_pmp_2_cfg_x(pmp_x[2]), .io_ptw_pmp_3_cfg_x(pmp_x[3]),
        .io_ptw_pmp_4_cfg_x(pmp_x[4]), .io_ptw_pmp_5_cfg_x(pmp_x[5]),
        .io_ptw_pmp_6_cfg_x(pmp_x[6]), .io_ptw_pmp_7_cfg_x(pmp_x[7]),
        .io_ptw_pmp_0_cfg_w(pmp_w[0]), .io_ptw_pmp_1_cfg_w(pmp_w[1]),
        .io_ptw_pmp_2_cfg_w(pmp_w[2]), .io_ptw_pmp_3_cfg_w(pmp_w[3]),
        .io_ptw_pmp_4_cfg_w(pmp_w[4]), .io_ptw_pmp_5_cfg_w(pmp_w[5]),
        .io_ptw_pmp_6_cfg_w(pmp_w[6]), .io_ptw_pmp_7_cfg_w(pmp_w[7]),
        .io_ptw_pmp_0_cfg_r(pmp_r[0]), .io_ptw_pmp_1_cfg_r(pmp_r[1]),
        .io_ptw_pmp_2_cfg_r(pmp_r[2]), .io_ptw_pmp_3_cfg_r(pmp_r[3]),
        .io_ptw_pmp_4_cfg_r(pmp_r[4]), .io_ptw_pmp_5_cfg_r(pmp_r[5]),
        .io_ptw_pmp_6_cfg_r(pmp_r[6]), .io_ptw_pmp_7_cfg_r(pmp_r[7]),
        .io_ptw_pmp_0_addr(pmp_addr[29:0]), .io_ptw_pmp_1_addr(pmp_addr[59:30]),
        .io_ptw_pmp_2_addr(pmp_addr[89:60]), .io_ptw_pmp_3_addr(pmp_addr[119:90]),
        .io_ptw_pmp_4_addr(pmp_addr[149:120]), .io_ptw_pmp_5_addr(pmp_addr[179:150]),
        .io_ptw_pmp_6_addr(pmp_addr[209:180]), .io_ptw_pmp_7_addr(pmp_addr[239:210]),
        .io_ptw_pmp_0_mask(pmp_mask[31:0]), .io_ptw_pmp_1_mask(pmp_mask[63:32]),
        .io_ptw_pmp_2_mask(pmp_mask[95:64]), .io_ptw_pmp_3_mask(pmp_mask[127:96]),
        .io_ptw_pmp_4_mask(pmp_mask[159:128]), .io_ptw_pmp_5_mask(pmp_mask[191:160]),
        .io_ptw_pmp_6_mask(pmp_mask[223:192]), .io_ptw_pmp_7_mask(pmp_mask[255:224]),
        .io_ptw_customCSRs_csrs_0_value(o_csr_value),
        .io_rocc_cmd_valid(o_rocc_valid), .io_wfi(o_wfi)
    );

    always #5 clk = ~clk;

    // ---------- imem model: free-running fetcher ----------
    // The Rocket module is the bare core: sequential fetch is driven from
    // outside (a frontend/icache in the real SoC), the core's io_imem_req
    // is only a redirect hint.  So this model streams instructions at
    // resp_ready, follows redirects, and pauses otherwise.
    // Replay contract: every DUT input must be stable over the whole
    // [pre-edge sampling, post-edge print] window of a trace row.  The
    // redirect reaction is therefore computed once at the START of the ST
    // loop iteration (blocking assign into red_d), so it can never flip
    // between the sampling and the print of the same row.  A stale fetch
    // may pass a redirect; the core kills it (io_kill/take_pc).
    reg [31:0] imem [0:255];
    reg [33:0] fpc;
    reg        red_d = 0;              // redirect indicator (set in ST loop)
    wire       redirect_now = o_ireq_valid && !reset;
    wire       iresp_fire = !red_d && o_iresp_ready;
    assign i_iresp_valid = !red_d;
    assign i_iresp_pc  = fpc;
    assign i_iresp_data = imem[fpc[11:2]];

    integer i;
    initial begin
        fpc = 34'h000001000; // 4KiB-aligned base; windowed by pc[11:2]
        imem[0] = 32'h00500293;  // addi x5, x0, 5
        imem[1] = 32'h00300313;  // addi x6, x0, 3
        imem[2] = 32'h006283b3;  // add  x7, x5, x6
        imem[3] = 32'h00702223;  // sw   x7, 4(x0)
        imem[4] = 32'h00402403;  // lw   x8, 4(x0)
        imem[5] = 32'h00802623;  // sw   x8, 12(x0)
        for (i = 6; i < 256; i = i + 1)
            imem[i] = 32'h0000006f;  // jal x0, 0
    end

    always @(posedge clk) begin
        if (reset)
            fpc <= 34'h000001000;
        else if (redirect_now)
            fpc <= o_ireq_pc;
        else if (iresp_fire)
            fpc <= fpc + 4;
    end

    // ---------- dmem model ----------
    reg [63:0] dmem8 [0:255];
    reg [1:0]  d_state = 0;            // 0 idle, 1 got req, 2 respond
    reg        d_is_load = 0;
    reg [5:0]  d_tag = 0;
    reg [33:0] d_addr = 0;
    reg [1:0]  d_size = 0;
    reg [63:0] d_s1_r = 0;             // sampled io_dmem_s1_data_data
    wire       dreq_fire = o_dreq_valid && i_dreq_ready && !reset;
    assign i_dresp_valid    = (d_state == 3'd2);
    assign i_dresp_tag      = d_tag;
    assign i_dresp_has_data = d_is_load;
    assign i_dresp_data     = d_is_load ? dmem8[d_addr[11:3]] : 64'd0;
    assign i_dresp_byp      = d_is_load ? dmem8[d_addr[11:3]] : 64'd0;

    reg [63:0] wdata_shift, blk;
    reg [7:0]  wbe;
    always @* begin
        wbe = 8'd0;
        case (d_size)
            2'd0: wbe = 8'b00000001 << d_addr[2:0];
            2'd1: wbe = 8'b00000011 << {d_addr[2:1], 1'b0};
            2'd2: wbe = d_addr[2] ? 8'b11110000 : 8'b00001111;
            2'd3: wbe = 8'b11111111;
        endcase
        wdata_shift = 64'd0;
        if (wbe[0]) wdata_shift[ 7: 0] = d_s1_r[ 7: 0];
        if (wbe[1]) wdata_shift[15: 8] = d_s1_r[15: 8];
        if (wbe[2]) wdata_shift[23:16] = d_s1_r[23:16];
        if (wbe[3]) wdata_shift[31:24] = d_s1_r[31:24];
        if (wbe[4]) wdata_shift[39:32] = d_s1_r[39:32];
        if (wbe[5]) wdata_shift[47:40] = d_s1_r[47:40];
        if (wbe[6]) wdata_shift[55:48] = d_s1_r[55:48];
        if (wbe[7]) wdata_shift[63:56] = d_s1_r[63:56];
    end

    integer j;
    initial begin
        for (j = 0; j < 256; j = j + 1) dmem8[j] = 64'd0;
    end

    always @(posedge clk) begin
        d_s1_r <= o_s1_data;
        if (reset) begin
            d_state <= 0;
        end else begin
            case (d_state)
                0: if (dreq_fire) begin
                    d_addr <= o_daddr; d_tag <= o_dtag;
                    d_size <= o_dsize; d_is_load <= (o_dcmd == 5'd0);
                    d_state <= 1;
                end
                1: d_state <= 2;
                2: begin
                    if (!d_is_load) begin
                        blk = dmem8[d_addr[11:3]];
                        if (wbe[0]) blk[ 7: 0] = wdata_shift[ 7: 0];
                        if (wbe[1]) blk[15: 8] = wdata_shift[15: 8];
                        if (wbe[2]) blk[23:16] = wdata_shift[23:16];
                        if (wbe[3]) blk[31:24] = wdata_shift[31:24];
                        if (wbe[4]) blk[39:32] = wdata_shift[39:32];
                        if (wbe[5]) blk[47:40] = wdata_shift[47:40];
                        if (wbe[6]) blk[55:48] = wdata_shift[55:48];
                        if (wbe[7]) blk[63:56] = wdata_shift[63:56];
                        dmem8[d_addr[11:3]] <= blk;
                    end
                    d_state <= 0;
                end
            endcase
        end
    end

    // ---------- ST trace ----------
    // Pre-edge shadow of every DUT input (the contract the cpp runner
    // replays): sample before the edge, print after it.
    reg        s_reset, s_irq_debug, s_irq_mtip, s_irq_msip, s_irq_meip;
    reg        s_iresp_valid, s_iresp_xcpt, s_iresp_replay;
    reg [33:0] s_iresp_pc; reg [31:0] s_iresp_data;
    reg        s_dreq_ready, s_s2_nack, s_dresp_valid;
    reg        s_dresp_replay, s_dresp_has_data, s_replay_next;
    reg        s_x_ma_ld, s_x_ma_st, s_x_pf_ld, s_x_pf_st, s_x_ae_ld, s_x_ae_st;
    reg        s_ordered, s_perf_release, s_perf_grant;
    reg [5:0]  s_dresp_tag; reg [63:0] s_dresp_data, s_dresp_byp;

    integer tick;
    initial begin
        @(posedge clk); #1;
        for (tick = 0; tick < 400; tick = tick + 1) begin
            #1; // settle gap after the previous print: the wire network
            // driven by red_d/reset below must be stable when sampled.
            reset = (tick < 3);
            red_d = reset ? 1'b0 : o_ireq_valid; // reaction lands BEFORE the
            // row's input sampling: stable through this row's print window.
            #1; // let continuous assigns settle before shadow-sampling
            s_reset = reset;
            s_irq_debug = i_irq_debug; s_irq_mtip = i_irq_mtip;
            s_irq_msip = i_irq_msip;   s_irq_meip = i_irq_meip;
            s_iresp_valid = i_iresp_valid; s_iresp_pc = i_iresp_pc;
            s_iresp_data = i_iresp_data; s_iresp_xcpt = i_iresp_xcpt;
            s_iresp_replay = i_iresp_replay;
            s_dreq_ready = i_dreq_ready; s_s2_nack = i_s2_nack;
            s_dresp_valid = i_dresp_valid; s_dresp_tag = i_dresp_tag;
            s_dresp_data = i_dresp_data; s_dresp_replay = i_dresp_replay;
            s_dresp_has_data = i_dresp_has_data; s_dresp_byp = i_dresp_byp;
            s_replay_next = i_replay_next;
            s_x_ma_ld = i_x_ma_ld; s_x_ma_st = i_x_ma_st;
            s_x_pf_ld = i_x_pf_ld; s_x_pf_st = i_x_pf_st;
            s_x_ae_ld = i_x_ae_ld; s_x_ae_st = i_x_ae_st;
            s_ordered = i_ordered; s_perf_release = i_perf_release;
            s_perf_grant = i_perf_grant;
            @(posedge clk);
            #1;
            $display("ST %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d",
                tick,
                s_reset, s_irq_debug, s_irq_mtip, s_irq_msip, s_irq_meip,
                s_iresp_valid, s_iresp_pc, s_iresp_data, s_iresp_xcpt, s_iresp_replay,
                s_dreq_ready, s_s2_nack, s_dresp_valid, s_dresp_tag, s_dresp_data,
                s_dresp_replay, s_dresp_has_data, s_dresp_byp, s_replay_next,
                s_x_ma_ld, s_x_ma_st, s_x_pf_ld, s_x_pf_st, s_x_ae_ld, s_x_ae_st,
                s_ordered, s_perf_release, s_perf_grant,
                o_might_req, o_ireq_valid, o_ireq_pc, o_ireq_spec, o_iresp_ready,
                o_btb, o_bht, o_flush,
                o_dreq_valid, o_daddr, o_dtag, o_dcmd, o_dsize, o_dsigned, o_dv,
                o_s1_kill, o_s1_data,
                o_ptw_debug,
                pmp_l[0], pmp_a[1:0], pmp_x[0], pmp_w[0], pmp_r[0], pmp_addr[29:0], pmp_mask[31:0],
                pmp_l[1], pmp_a[3:2], pmp_x[1], pmp_w[1], pmp_r[1], pmp_addr[59:30], pmp_mask[63:32],
                pmp_l[2], pmp_a[5:4], pmp_x[2], pmp_w[2], pmp_r[2], pmp_addr[89:60], pmp_mask[95:64],
                pmp_l[3], pmp_a[7:6], pmp_x[3], pmp_w[3], pmp_r[3], pmp_addr[119:90], pmp_mask[127:96],
                pmp_l[4], pmp_a[9:8], pmp_x[4], pmp_w[4], pmp_r[4], pmp_addr[149:120], pmp_mask[159:128],
                pmp_l[5], pmp_a[11:10], pmp_x[5], pmp_w[5], pmp_r[5], pmp_addr[179:150], pmp_mask[191:160],
                pmp_l[6], pmp_a[13:12], pmp_x[6], pmp_w[6], pmp_r[6], pmp_addr[209:180], pmp_mask[223:192],
                pmp_l[7], pmp_a[15:14], pmp_x[7], pmp_w[7], pmp_r[7], pmp_addr[239:210], pmp_mask[255:224],
                o_csr_value, o_rocc_valid, o_wfi);
        end
        $finish;
    end
endmodule

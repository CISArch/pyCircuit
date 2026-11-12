// tb_rocket_pgm.v — 程序驱动的 golden testbench（tb_rocket.v 的参数化变体）。
// 差异仅三处，其余（imem/dmem 行为模型、ST pre-edge 采样 / post-edge 打印、
// redirect 时序）逐字继承 tb_rocket.v，保证 C++ runner 回放协议不变：
//   1) imem 内容来自 +imem=<hex>（$readmemh，256 × 32b，elf2imem.py 产出）；
//   2) 拍数来自 +cycles=<n>（默认 400）；
//   3) 复位后 fpc 基址仍 0x1000（4KiB 对齐，任意复位向量落窗口 idx0）；
//   4) dmem 模型改为一级移位队列（req_ready 恒 1、resp 恰在 fire+2 拍），
//      满足 HellaCache s2 契约并支持背靠背 mem 指令（见下方注释）。
// 测试程序（tests/asm/*.S）：PASS/FAIL 证据通过 ST 输出列的 dmem 写事务
// （io_dmem_req_bits_addr / io_dmem_s1_data_data）观察。
`timescale 1ns/1ps
module tb_Rocket;
    reg clk = 0;
    reg reset = 1;
    wire i_irq_debug = 0, i_irq_mtip = 0, i_irq_msip = 0, i_irq_meip = 0;
    wire i_iresp_valid; wire [33:0] i_iresp_pc; wire [31:0] i_iresp_data;
    wire i_iresp_xcpt = 0, i_iresp_replay = 0;
    wire i_dreq_ready, i_s2_nack = 0, i_dresp_valid;
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

    // ---------- imem model: free-running fetcher（同 tb_rocket.v） ----------
    reg [31:0] imem [0:255];
    reg [33:0] fpc;
    reg        red_d = 0;
    wire       redirect_now = o_ireq_valid && !reset;
    wire       iresp_fire = !red_d && o_iresp_ready;
    assign i_iresp_valid = !red_d;
    assign i_iresp_pc  = fpc;
    assign i_iresp_data = imem[fpc[11:2]];

    // [1/3] 程序映像由 +imem=<hex> 加载（elf2imem.py 产出 256 行）。
    reg [1023:0] imem_file;
    integer cycles_arg;
    initial begin
        if (!$value$plusargs("imem=%s", imem_file)) begin
            $display("ERROR: +imem=<hex> required");
            $finish;
        end
        for (integer k = 0; k < 256; k = k + 1) imem[k] = 32'h0000006f;
        $readmemh(imem_file, imem);
        fpc = 34'h000001000;
    end

    always @(posedge clk) begin
        if (reset)
            fpc <= 34'h000001000;
        else if (redirect_now)
            fpc <= o_ireq_pc;
        else if (iresp_fire)
            fpc <= fpc + 4;
    end

    // ---------- dmem model：HellaCache 命中时序（两级移位队列） ----------
    // 契约（RocketCore.scala 511/675）：
    //   1) req_ready 恒 1 —— fire = valid 拍，即核的 s0；
    //   2) resp_valid 恰在 fire+2 拍（核 s2/wb 级）呈现并被采样 —— 晚到的
    //      resp 不被消费（非 replay 不走 ll 写回），sboard 永不清除。
    // 实现：fire 拍锁存入 q1（对应核 s1 拍），次拍移入 q2（对应核 s2 拍）
    // 呈现 resp；store 写回与 resp 采样同沿（fire+2 沿），此时 d_s1_r 已于
    // 上一沿采到核 s1 数据。背靠背 mem 指令各自 fire+2 出 resp 互不阻塞；
    // 紧随 store 的同地址 load 读区间（其 fire+3）晚于 store 写沿（fire+2），
    // 天然满足 store-to-load forwarding。
    reg [63:0] dmem8 [0:255];
    reg        q1_v = 0, q2_v = 0;
    reg        q1_is_load = 0, q2_is_load = 0;
    reg        q1_signed = 0, q2_signed = 0;
    reg [5:0]  q1_tag = 0, q2_tag = 0;
    reg [33:0] q1_addr = 0, q2_addr = 0;
    reg [1:0]  q1_size = 0, q2_size = 0;
    reg [63:0] d_s1_r = 0;          // 核 s1 拍数据沿采到的 store 写数据

    assign i_dreq_ready    = 1'b1;
    assign i_dresp_valid    = q2_v;
    assign i_dresp_tag      = q2_tag;
    assign i_dresp_has_data = q2_is_load;
    // HellaCache s2 契约：resp.data 必须是已按 size/signed/addr 提取并
    // 扩展好的 64b 数据 —— RocketCore 的 rf_wdata 直写寄存器堆，无提取
    //（RocketCore.scala 703：rf_wdata = Mux(dmem_resp_xpu, resp.bits.data,…)）。
    wire [63:0] q_line = dmem8[q2_addr[11:3]];
    wire [31:0] q_word = q2_addr[2] ? q_line[63:32] : q_line[31:0];
    wire [15:0] q_half = q_line[16 * q2_addr[2:1] +: 16];
    wire [7:0]  q_byte = q_line[8  * q2_addr[2:0] +: 8];
    reg  [63:0] ldata;
    always @* begin
        case (q2_size)
            2'd3: ldata = q_line;                       // ld
            2'd2: ldata = {32'b0, q_word};              // lw / lwu（零扩展）
            2'd1: ldata = q2_signed ? {{48{q_half[15]}}, q_half}
                                     : {48'b0, q_half}; // lh / lhu
            2'd0: ldata = q2_signed ? {{56{q_byte[7]}},  q_byte}
                                     : {56'b0, q_byte}; // lb / lbu
        endcase
    end
    assign i_dresp_data = q2_is_load ? ldata : 64'd0;
    assign i_dresp_byp  = i_dresp_data;

    reg [63:0] wdata_shift, blk;
    reg [7:0]  wbe;
    always @* begin
        wbe = 8'd0;
        case (q2_size)
            2'd0: wbe = 8'b00000001 << q2_addr[2:0];
            2'd1: wbe = 8'b00000011 << {q2_addr[2:1], 1'b0};
            2'd2: wbe = q2_addr[2] ? 8'b11110000 : 8'b00001111;
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
            q1_v <= 1'b0; q2_v <= 1'b0;
        end else begin
            // store 写回与 resp 采样同沿（fire+2 沿）：用移位前的 q2 旧值
            if (q2_v && !q2_is_load) begin
                blk = dmem8[q2_addr[11:3]];
                if (wbe[0]) blk[ 7: 0] = wdata_shift[ 7: 0];
                if (wbe[1]) blk[15: 8] = wdata_shift[15: 8];
                if (wbe[2]) blk[23:16] = wdata_shift[23:16];
                if (wbe[3]) blk[31:24] = wdata_shift[31:24];
                if (wbe[4]) blk[39:32] = wdata_shift[39:32];
                if (wbe[5]) blk[47:40] = wdata_shift[47:40];
                if (wbe[6]) blk[55:48] = wdata_shift[55:48];
                if (wbe[7]) blk[63:56] = wdata_shift[63:56];
                dmem8[q2_addr[11:3]] <= blk;
            end
            // 两级移位：q2 <= q1（出 resp），q1 <= 本拍 fire 的事务
            //（ready 恒 1，valid 拍即 fire）
            q2_v       <= q1_v;
            q2_tag     <= q1_tag;
            q2_addr    <= q1_addr;
            q2_size    <= q1_size;
            q2_is_load <= q1_is_load;
            q2_signed  <= q1_signed;
            q1_v       <= o_dreq_valid;
            q1_tag     <= o_dtag;
            q1_addr    <= o_daddr;
            q1_size    <= o_dsize;
            q1_is_load <= (o_dcmd == 5'd0);
            q1_signed  <= o_dsigned;
        end
    end

    // ---------- ST trace（同 tb_rocket.v） ----------
    reg        s_reset, s_irq_debug, s_irq_mtip, s_irq_msip, s_irq_meip;
    reg        s_iresp_valid, s_iresp_xcpt, s_iresp_replay;
    reg [33:0] s_iresp_pc; reg [31:0] s_iresp_data;
    reg        s_dreq_ready, s_s2_nack, s_dresp_valid;
    reg        s_dresp_replay, s_dresp_has_data, s_replay_next;
    reg        s_x_ma_ld, s_x_ma_st, s_x_pf_ld, s_x_pf_st, s_x_ae_ld, s_x_ae_st;
    reg        s_ordered, s_perf_release, s_perf_grant;
    reg [5:0]  s_dresp_tag; reg [63:0] s_dresp_data, s_dresp_byp;

    // [2/3] 拍数由 +cycles=<n> 控制（默认 400）。
    integer tick, max_tick;
    initial begin
        if (!$value$plusargs("cycles=%d", max_tick)) max_tick = 400;
    end
    initial begin
        @(posedge clk); #1;
        for (tick = 0; tick < max_tick; tick = tick + 1) begin
            #1;
            reset = (tick < 3);
            red_d = reset ? 1'b0 : o_ireq_valid;
            #1;
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

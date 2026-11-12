// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_Rocket.h for the primary calling header

#include "Vtb_Rocket__pch.h"

VlCoroutine Vtb_Rocket___024root___eval_initial__TOP__Vtiming__0(Vtb_Rocket___024root* vlSelf);
VlCoroutine Vtb_Rocket___024root___eval_initial__TOP__Vtiming__1(Vtb_Rocket___024root* vlSelf);

void Vtb_Rocket___024root___eval_initial(Vtb_Rocket___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_Rocket___024root___eval_initial\n"); );
    Vtb_Rocket__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    {
        // Inlined CFunc: _eval_initial__TOP
        IData/*31:0*/ __Vinline_0__eval_initial__TOP_tb_Rocket__DOT____VlemExpr_1;
        IData/*31:0*/ __Vinline_0__eval_initial__TOP_tb_Rocket__DOT____VlemExpr_0;
        IData/*31:0*/ __Vinline_0__eval_initial__TOP_tb_Rocket__DOT__j;
        __Vinline_0__eval_initial__TOP_tb_Rocket__DOT__j = 0;
        IData/*31:0*/ __Vinline_0__eval_initial__TOP_tb_Rocket__DOT__unnamedblk1__DOT__k;
        __Vinline_0__eval_initial__TOP_tb_Rocket__DOT__unnamedblk1__DOT__k = 0;
        __Vinline_0__eval_initial__TOP_tb_Rocket__DOT____VlemExpr_0 
            = VL_VALUEPLUSARGS_INW(1024, "imem=%s"s, 
                                   vlSelfRef.tb_Rocket__DOT__imem_file);
        if (VL_UNLIKELY(((! __Vinline_0__eval_initial__TOP_tb_Rocket__DOT____VlemExpr_0)))) {
            VL_WRITEF_NX("ERROR: +imem=<hex> required\n",0);
            VL_FINISH_MT("/home/zhangzijie/pyCircuit/designs/Rocket-pyc/tests/tb/tb_rocket_pgm.v", 111, "");
        }
        __Vinline_0__eval_initial__TOP_tb_Rocket__DOT__unnamedblk1__DOT__k = 0U;
        while (VL_GTS_III(32, 0x00000100U, __Vinline_0__eval_initial__TOP_tb_Rocket__DOT__unnamedblk1__DOT__k)) {
            vlSelfRef.tb_Rocket__DOT__imem[(0x000000ffU 
                                            & __Vinline_0__eval_initial__TOP_tb_Rocket__DOT__unnamedblk1__DOT__k)] = 0x0000006fU;
            __Vinline_0__eval_initial__TOP_tb_Rocket__DOT__unnamedblk1__DOT__k 
                = ((IData)(1U) + __Vinline_0__eval_initial__TOP_tb_Rocket__DOT__unnamedblk1__DOT__k);
        }
        VL_READMEM_N(true, 32, 256, 0, VL_CVT_PACK_STR_NW(32, vlSelfRef.tb_Rocket__DOT__imem_file)
                     ,  &(vlSelfRef.tb_Rocket__DOT__imem)
                     , 0, ~0ULL);
        vlSelfRef.tb_Rocket__DOT__fpc = 0x0000000000001000ULL;
        __Vinline_0__eval_initial__TOP_tb_Rocket__DOT__j = 0U;
        while (VL_GTS_III(32, 0x00000100U, __Vinline_0__eval_initial__TOP_tb_Rocket__DOT__j)) {
            vlSelfRef.tb_Rocket__DOT__dmem8[(0x000000ffU 
                                             & __Vinline_0__eval_initial__TOP_tb_Rocket__DOT__j)] = 0ULL;
            __Vinline_0__eval_initial__TOP_tb_Rocket__DOT__j 
                = ((IData)(1U) + __Vinline_0__eval_initial__TOP_tb_Rocket__DOT__j);
        }
        __Vinline_0__eval_initial__TOP_tb_Rocket__DOT____VlemExpr_1 
            = VL_VALUEPLUSARGS_INI(32, "cycles=%d"s, 
                                   vlSelfRef.tb_Rocket__DOT__max_tick);
        if ((! __Vinline_0__eval_initial__TOP_tb_Rocket__DOT____VlemExpr_1)) {
            vlSelfRef.tb_Rocket__DOT__max_tick = 0x00000190U;
        }
    }
    Vtb_Rocket___024root___eval_initial__TOP__Vtiming__0(vlSelf);
    Vtb_Rocket___024root___eval_initial__TOP__Vtiming__1(vlSelf);
}

void Vtb_Rocket___024root____VbeforeTrig_h7b2495ab__0(Vtb_Rocket___024root* vlSelf, const char* __VeventDescription);

VlCoroutine Vtb_Rocket___024root___eval_initial__TOP__Vtiming__0(Vtb_Rocket___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_Rocket___024root___eval_initial__TOP__Vtiming__0\n"); );
    Vtb_Rocket__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ tb_Rocket__DOT__tick;
    tb_Rocket__DOT__tick = 0;
    // Body
    Vtb_Rocket___024root____VbeforeTrig_h7b2495ab__0(vlSelf, 
                                                     "@(posedge tb_Rocket.clk)");
    co_await vlSelfRef.__VtrigSched_h7b2495ab__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_Rocket.clk)", 
                                                         "/home/zhangzijie/pyCircuit/designs/Rocket-pyc/tests/tb/tb_rocket_pgm.v", 
                                                         248);
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/home/zhangzijie/pyCircuit/designs/Rocket-pyc/tests/tb/tb_rocket_pgm.v", 
                                         248);
    tb_Rocket__DOT__tick = 0U;
    while (VL_LTS_III(32, tb_Rocket__DOT__tick, vlSelfRef.tb_Rocket__DOT__max_tick)) {
        co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                             nullptr, 
                                             "/home/zhangzijie/pyCircuit/designs/Rocket-pyc/tests/tb/tb_rocket_pgm.v", 
                                             250);
        vlSelfRef.tb_Rocket__DOT__reset = VL_GTS_III(32, 3U, tb_Rocket__DOT__tick);
        vlSelfRef.tb_Rocket__DOT__red_d = ((~ (IData)(vlSelfRef.tb_Rocket__DOT__reset)) 
                                           & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf_io_kill));
        co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                             nullptr, 
                                             "/home/zhangzijie/pyCircuit/designs/Rocket-pyc/tests/tb/tb_rocket_pgm.v", 
                                             253);
        vlSelfRef.tb_Rocket__DOT__s_reset = vlSelfRef.tb_Rocket__DOT__reset;
        vlSelfRef.tb_Rocket__DOT__s_irq_debug = 0U;
        vlSelfRef.tb_Rocket__DOT__s_irq_mtip = 0U;
        vlSelfRef.tb_Rocket__DOT__s_irq_msip = 0U;
        vlSelfRef.tb_Rocket__DOT__s_irq_meip = 0U;
        vlSelfRef.tb_Rocket__DOT__s_iresp_valid = vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf_io_imem_valid;
        vlSelfRef.tb_Rocket__DOT__s_iresp_pc = vlSelfRef.tb_Rocket__DOT__fpc;
        vlSelfRef.tb_Rocket__DOT__s_iresp_data = vlSelfRef.tb_Rocket__DOT__imem
            [(0x000000ffU & (IData)((vlSelfRef.tb_Rocket__DOT__fpc 
                                     >> 2U)))];
        vlSelfRef.tb_Rocket__DOT__s_iresp_xcpt = 0U;
        vlSelfRef.tb_Rocket__DOT__s_iresp_replay = 0U;
        vlSelfRef.tb_Rocket__DOT__s_dreq_ready = 1U;
        vlSelfRef.tb_Rocket__DOT__s_s2_nack = 0U;
        vlSelfRef.tb_Rocket__DOT__s_dresp_valid = vlSelfRef.tb_Rocket__DOT__q2_v;
        vlSelfRef.tb_Rocket__DOT__s_dresp_tag = vlSelfRef.tb_Rocket__DOT__q2_tag;
        vlSelfRef.tb_Rocket__DOT__s_dresp_data = vlSelfRef.tb_Rocket__DOT__i_dresp_data;
        vlSelfRef.tb_Rocket__DOT__s_dresp_replay = 0U;
        vlSelfRef.tb_Rocket__DOT__s_dresp_has_data 
            = vlSelfRef.tb_Rocket__DOT__q2_is_load;
        vlSelfRef.tb_Rocket__DOT__s_dresp_byp = vlSelfRef.tb_Rocket__DOT__i_dresp_data;
        vlSelfRef.tb_Rocket__DOT__s_replay_next = 0U;
        vlSelfRef.tb_Rocket__DOT__s_x_ma_ld = 0U;
        vlSelfRef.tb_Rocket__DOT__s_x_ma_st = 0U;
        vlSelfRef.tb_Rocket__DOT__s_x_pf_ld = 0U;
        vlSelfRef.tb_Rocket__DOT__s_x_pf_st = 0U;
        vlSelfRef.tb_Rocket__DOT__s_x_ae_ld = 0U;
        vlSelfRef.tb_Rocket__DOT__s_x_ae_st = 0U;
        vlSelfRef.tb_Rocket__DOT__s_ordered = 1U;
        vlSelfRef.tb_Rocket__DOT__s_perf_release = 0U;
        vlSelfRef.tb_Rocket__DOT__s_perf_grant = 0U;
        Vtb_Rocket___024root____VbeforeTrig_h7b2495ab__0(vlSelf, 
                                                         "@(posedge tb_Rocket.clk)");
        co_await vlSelfRef.__VtrigSched_h7b2495ab__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_Rocket.clk)", 
                                                             "/home/zhangzijie/pyCircuit/designs/Rocket-pyc/tests/tb/tb_rocket_pgm.v", 
                                                             270);
        co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                             nullptr, 
                                             "/home/zhangzijie/pyCircuit/designs/Rocket-pyc/tests/tb/tb_rocket_pgm.v", 
                                             271);
        VL_WRITEF_NX("ST %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d 0 %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d\n",105
                     , '~',32,tb_Rocket__DOT__tick, '#',1,(IData)(vlSelfRef.tb_Rocket__DOT__s_reset)
                     , '#',1,vlSelfRef.tb_Rocket__DOT__s_irq_debug
                     , '#',1,(IData)(vlSelfRef.tb_Rocket__DOT__s_irq_mtip)
                     , '#',1,vlSelfRef.tb_Rocket__DOT__s_irq_msip
                     , '#',1,(IData)(vlSelfRef.tb_Rocket__DOT__s_irq_meip)
                     , '#',1,vlSelfRef.tb_Rocket__DOT__s_iresp_valid
                     , '#',34,vlSelfRef.tb_Rocket__DOT__s_iresp_pc
                     , '#',32,vlSelfRef.tb_Rocket__DOT__s_iresp_data
                     , '#',1,(IData)(vlSelfRef.tb_Rocket__DOT__s_iresp_xcpt)
                     , '#',1,vlSelfRef.tb_Rocket__DOT__s_iresp_replay
                     , '#',1,(IData)(vlSelfRef.tb_Rocket__DOT__s_dreq_ready)
                     , '#',1,vlSelfRef.tb_Rocket__DOT__s_s2_nack
                     , '#',1,(IData)(vlSelfRef.tb_Rocket__DOT__s_dresp_valid)
                     , '#',6,vlSelfRef.tb_Rocket__DOT__s_dresp_tag
                     , '#',64,vlSelfRef.tb_Rocket__DOT__s_dresp_data
                     , '#',1,(IData)(vlSelfRef.tb_Rocket__DOT__s_dresp_replay)
                     , '#',1,vlSelfRef.tb_Rocket__DOT__s_dresp_has_data
                     , '#',64,vlSelfRef.tb_Rocket__DOT__s_dresp_byp
                     , '#',1,(IData)(vlSelfRef.tb_Rocket__DOT__s_replay_next)
                     , '#',1,vlSelfRef.tb_Rocket__DOT__s_x_ma_ld
                     , '#',1,(IData)(vlSelfRef.tb_Rocket__DOT__s_x_ma_st)
                     , '#',1,vlSelfRef.tb_Rocket__DOT__s_x_pf_ld
                     , '#',1,(IData)(vlSelfRef.tb_Rocket__DOT__s_x_pf_st)
                     , '#',1,vlSelfRef.tb_Rocket__DOT__s_x_ae_ld
                     , '#',1,(IData)(vlSelfRef.tb_Rocket__DOT__s_x_ae_st)
                     , '#',1,vlSelfRef.tb_Rocket__DOT__s_ordered
                     , '#',1,(IData)(vlSelfRef.tb_Rocket__DOT__s_perf_release)
                     , '#',1,vlSelfRef.tb_Rocket__DOT__s_perf_grant
                     , '#',1,(IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__imem_might_request_reg)
                     , '#',1,vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf_io_kill
                     , '#',34,(((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_xcpt) 
                                | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr_io_eret))
                                ? ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__insn_ret)
                                    ? ((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_25)
                                        ? vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___T_44
                                        : vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___T_30)
                                    : ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__trapToDebug)
                                        ? ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_debug)
                                            ? ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__insn_break)
                                                ? 0x0000000000000800ULL
                                                : 0x0000000000000808ULL)
                                            : 0x0000000000000800ULL)
                                        : ((QData)((IData)(
                                                           (((IData)(
                                                                     ((QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___read_mtvec_T_5)) 
                                                                      >> 8U)) 
                                                             << 6U) 
                                                            | (0x0000003fU 
                                                               & ((IData)(
                                                                          ((0x8000000000000000ULL 
                                                                            == 
                                                                            (0x80000000000000c0ULL 
                                                                             & vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__cause)) 
                                                                           & vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___read_mtvec_T_5))
                                                                   ? (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__cause)
                                                                   : 
                                                                  (vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___read_mtvec_T_5 
                                                                   >> 2U)))))) 
                                           << 2U)))
                                : ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__replay_wb)
                                    ? vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_pc
                                    : vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_npc))
                     , '#',1,(1U & (~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__take_pc_wb)))
                     , '#',1,((~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ctrl_stalld)) 
                              & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT___io_imem_ready_T) 
                                 & ((1U >= (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT___io_imem_ready_T_4)) 
                                    | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__nICReady) 
                                       >= (3U & ((IData)(2U) 
                                                 - 
                                                 (1U 
                                                  & (IData)(
                                                            (vlSelfRef.tb_Rocket__DOT__fpc 
                                                             >> 1U)))))))))
                     , '#',1,(IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_98)
                     , '#',1,((~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__take_pc_wb)) 
                              & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_valid))
                     , '#',1,((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_valid) 
                              & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_ctrl_fence_i))
                     , '#',1,(IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__id_mem_busy)
                     , '#',34,(((QData)((IData)((1U 
                                                 & (((0U 
                                                      == 
                                                      (0x7fffffffU 
                                                       & (IData)(
                                                                 (vlSelfRef.tb_Rocket__DOT__dut__DOT__div_io_req_bits_in1 
                                                                  >> 0x00000021U)))) 
                                                     | (0x7fffffffU 
                                                        == 
                                                        (0x7fffffffU 
                                                         & (IData)(
                                                                   (vlSelfRef.tb_Rocket__DOT__dut__DOT__div_io_req_bits_in1 
                                                                    >> 0x00000021U)))))
                                                     ? (IData)(
                                                               (vlSelfRef.tb_Rocket__DOT__dut__DOT__alu_io_adder_out 
                                                                >> 0x00000021U))
                                                     : 
                                                    (~ (IData)(
                                                               (vlSelfRef.tb_Rocket__DOT__dut__DOT__alu_io_adder_out 
                                                                >> 0x00000020U))))))) 
                                << 0x00000021U) | (0x00000001ffffffffULL 
                                                   & vlSelfRef.tb_Rocket__DOT__dut__DOT__alu_io_adder_out))
                     , '#',6,((0x0000003eU & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_inst 
                                              >> 6U)) 
                              | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_fp))
                     , '#',5,(IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_mem_cmd)
                     , '#',2,vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_mem_size
                     , '#',1,(1U & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_inst 
                                       >> 0x0000000eU)))
                     , '#',1,((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__killm_common) 
                              | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_ldst_xcpt))
                     , '#',64,vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_rs2
                     , '#',1,(IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_debug)
                     , '#',1,vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_0_cfg_l
                     , '#',2,(IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_0_cfg_a)
                     , '#',1,vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_0_cfg_x
                     , '#',1,(IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_0_cfg_w)
                     , '#',1,vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_0_cfg_r
                     , '#',30,vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_0_addr
                     , '#',32,(3U | (((~ ((IData)(1U) 
                                          + vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__pmp_mask_base)) 
                                      & vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__pmp_mask_base) 
                                     << 2U)), '#',1,(IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_1_cfg_l)
                     , '#',2,vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_1_cfg_a
                     , '#',1,(IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_1_cfg_x)
                     , '#',1,vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_1_cfg_w
                     , '#',1,(IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_1_cfg_r)
                     , '#',30,vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_1_addr
                     , '#',32,(3U | (((~ ((IData)(1U) 
                                          + vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__pmp_mask_base_1)) 
                                      & vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__pmp_mask_base_1) 
                                     << 2U)), '#',1,(IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_2_cfg_l)
                     , '#',2,vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_2_cfg_a
                     , '#',1,(IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_2_cfg_x)
                     , '#',1,vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_2_cfg_w
                     , '#',1,(IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_2_cfg_r)
                     , '#',30,vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_2_addr
                     , '#',32,(3U | (((~ ((IData)(1U) 
                                          + vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__pmp_mask_base_2)) 
                                      & vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__pmp_mask_base_2) 
                                     << 2U)), '#',1,(IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_3_cfg_l)
                     , '#',2,vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_3_cfg_a
                     , '#',1,(IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_3_cfg_x)
                     , '#',1,vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_3_cfg_w
                     , '#',1,(IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_3_cfg_r)
                     , '#',30,vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_3_addr
                     , '#',32,(3U | (((~ ((IData)(1U) 
                                          + vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__pmp_mask_base_3)) 
                                      & vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__pmp_mask_base_3) 
                                     << 2U)), '#',1,(IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_4_cfg_l)
                     , '#',2,vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_4_cfg_a
                     , '#',1,(IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_4_cfg_x)
                     , '#',1,vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_4_cfg_w
                     , '#',1,(IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_4_cfg_r)
                     , '#',30,vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_4_addr
                     , '#',32,(3U | (((~ ((IData)(1U) 
                                          + vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__pmp_mask_base_4)) 
                                      & vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__pmp_mask_base_4) 
                                     << 2U)), '#',1,(IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_5_cfg_l)
                     , '#',2,vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_5_cfg_a
                     , '#',1,(IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_5_cfg_x)
                     , '#',1,vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_5_cfg_w
                     , '#',1,(IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_5_cfg_r)
                     , '#',30,vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_5_addr
                     , '#',32,(3U | (((~ ((IData)(1U) 
                                          + vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__pmp_mask_base_5)) 
                                      & vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__pmp_mask_base_5) 
                                     << 2U)), '#',1,(IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_6_cfg_l)
                     , '#',2,vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_6_cfg_a
                     , '#',1,(IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_6_cfg_x)
                     , '#',1,vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_6_cfg_w
                     , '#',1,(IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_6_cfg_r)
                     , '#',30,vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_6_addr
                     , '#',32,(3U | (((~ ((IData)(1U) 
                                          + vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__pmp_mask_base_6)) 
                                      & vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__pmp_mask_base_6) 
                                     << 2U)), '#',1,(IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_7_cfg_l)
                     , '#',2,vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_7_cfg_a
                     , '#',1,(IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_7_cfg_x)
                     , '#',1,vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_7_cfg_w
                     , '#',1,(IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_7_cfg_r)
                     , '#',30,vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_7_addr
                     , '#',32,(3U | (((~ ((IData)(1U) 
                                          + vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__pmp_mask_base_7)) 
                                      & vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__pmp_mask_base_7) 
                                     << 2U)), '#',64,vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_custom_0
                     , '#',1,((~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_replay)) 
                              & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__replay_wb_rocc))
                     , '#',1,(IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_wfi));
        tb_Rocket__DOT__tick = ((IData)(1U) + tb_Rocket__DOT__tick);
    }
    VL_FINISH_MT("/home/zhangzijie/pyCircuit/designs/Rocket-pyc/tests/tb/tb_rocket_pgm.v", 295, "");
    co_return;
}

VlCoroutine Vtb_Rocket___024root___eval_initial__TOP__Vtiming__1(Vtb_Rocket___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_Rocket___024root___eval_initial__TOP__Vtiming__1\n"); );
    Vtb_Rocket__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    while (VL_LIKELY(!vlSymsp->_vm_contextp__->gotFinish())) {
        co_await vlSelfRef.__VdlySched.delay(0x0000000000001388ULL, 
                                             nullptr, 
                                             "/home/zhangzijie/pyCircuit/designs/Rocket-pyc/tests/tb/tb_rocket_pgm.v", 
                                             93);
        vlSelfRef.tb_Rocket__DOT__clk = (1U & (~ (IData)(vlSelfRef.tb_Rocket__DOT__clk)));
    }
    co_return;
}

bool Vtb_Rocket___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_Rocket___024root___trigger_anySet__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        if (in[n]) {
            return (1U);
        }
        n = ((IData)(1U) + n);
    } while ((1U > n));
    return (0U);
}

void Vtb_Rocket___024root___nba_sequent__TOP__0(Vtb_Rocket___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_Rocket___024root___nba_sequent__TOP__0\n"); );
    Vtb_Rocket__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    SData/*15:0*/ tb_Rocket__DOT__q_half;
    tb_Rocket__DOT__q_half = 0;
    CData/*7:0*/ tb_Rocket__DOT__q_byte;
    tb_Rocket__DOT__q_byte = 0;
    QData/*63:0*/ tb_Rocket__DOT__dut__DOT__rf_id_rs_MPORT_data;
    tb_Rocket__DOT__dut__DOT__rf_id_rs_MPORT_data = 0;
    QData/*63:0*/ tb_Rocket__DOT__dut__DOT__rf_id_rs_MPORT_1_data;
    tb_Rocket__DOT__dut__DOT__rf_id_rs_MPORT_1_data = 0;
    QData/*63:0*/ tb_Rocket__DOT__dut__DOT__csr_io_rw_rdata;
    tb_Rocket__DOT__dut__DOT__csr_io_rw_rdata = 0;
    CData/*0:0*/ tb_Rocket__DOT__dut__DOT__csr_io_csr_stall;
    tb_Rocket__DOT__dut__DOT__csr_io_csr_stall = 0;
    QData/*63:0*/ tb_Rocket__DOT__dut__DOT__alu_io_in2;
    tb_Rocket__DOT__dut__DOT__alu_io_in2 = 0;
    QData/*63:0*/ tb_Rocket__DOT__dut__DOT__alu_io_in1;
    tb_Rocket__DOT__dut__DOT__alu_io_in1 = 0;
    CData/*0:0*/ tb_Rocket__DOT__dut__DOT___mem_cfi_taken_T;
    tb_Rocket__DOT__dut__DOT___mem_cfi_taken_T = 0;
    CData/*0:0*/ tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_19;
    tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_19 = 0;
    SData/*13:0*/ tb_Rocket__DOT__dut__DOT__id_ctrl_decoder_decoded_lo_21;
    tb_Rocket__DOT__dut__DOT__id_ctrl_decoder_decoded_lo_21 = 0;
    CData/*6:0*/ tb_Rocket__DOT__dut__DOT__id_ctrl_decoder_decoded_hi_lo_20;
    tb_Rocket__DOT__dut__DOT__id_ctrl_decoder_decoded_hi_lo_20 = 0;
    CData/*7:0*/ tb_Rocket__DOT__dut__DOT__id_ctrl_decoder_decoded_hi_lo_21;
    tb_Rocket__DOT__dut__DOT__id_ctrl_decoder_decoded_hi_lo_21 = 0;
    CData/*0:0*/ tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_49;
    tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_49 = 0;
    CData/*0:0*/ tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_53;
    tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_53 = 0;
    CData/*0:0*/ tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_137;
    tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_137 = 0;
    CData/*0:0*/ tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_139;
    tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_139 = 0;
    CData/*0:0*/ tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_141;
    tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_141 = 0;
    SData/*13:0*/ tb_Rocket__DOT__dut__DOT__id_ctrl_decoder_decoded_lo_71;
    tb_Rocket__DOT__dut__DOT__id_ctrl_decoder_decoded_lo_71 = 0;
    CData/*0:0*/ tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_147;
    tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_147 = 0;
    SData/*13:0*/ tb_Rocket__DOT__dut__DOT__id_ctrl_decoder_decoded_lo_75;
    tb_Rocket__DOT__dut__DOT__id_ctrl_decoder_decoded_lo_75 = 0;
    CData/*6:0*/ tb_Rocket__DOT__dut__DOT__id_ctrl_decoder_decoded_hi_lo_74;
    tb_Rocket__DOT__dut__DOT__id_ctrl_decoder_decoded_hi_lo_74 = 0;
    SData/*13:0*/ tb_Rocket__DOT__dut__DOT__id_ctrl_decoder_decoded_lo_82;
    tb_Rocket__DOT__dut__DOT__id_ctrl_decoder_decoded_lo_82 = 0;
    CData/*0:0*/ tb_Rocket__DOT__dut__DOT___id_csr_en_T_3;
    tb_Rocket__DOT__dut__DOT___id_csr_en_T_3 = 0;
    CData/*0:0*/ tb_Rocket__DOT__dut__DOT___T_27;
    tb_Rocket__DOT__dut__DOT___T_27 = 0;
    CData/*0:0*/ tb_Rocket__DOT__dut__DOT___T_28;
    tb_Rocket__DOT__dut__DOT___T_28 = 0;
    CData/*0:0*/ tb_Rocket__DOT__dut__DOT___T_30;
    tb_Rocket__DOT__dut__DOT___T_30 = 0;
    CData/*0:0*/ tb_Rocket__DOT__dut__DOT__ex_imm_sign;
    tb_Rocket__DOT__dut__DOT__ex_imm_sign = 0;
    CData/*0:0*/ tb_Rocket__DOT__dut__DOT___T_135;
    tb_Rocket__DOT__dut__DOT___T_135 = 0;
    CData/*0:0*/ tb_Rocket__DOT__dut__DOT___data_hazard_ex_T;
    tb_Rocket__DOT__dut__DOT___data_hazard_ex_T = 0;
    CData/*0:0*/ tb_Rocket__DOT__dut__DOT___T_137;
    tb_Rocket__DOT__dut__DOT___T_137 = 0;
    CData/*0:0*/ tb_Rocket__DOT__dut__DOT___data_hazard_ex_T_2;
    tb_Rocket__DOT__dut__DOT___data_hazard_ex_T_2 = 0;
    CData/*0:0*/ tb_Rocket__DOT__dut__DOT___T_139;
    tb_Rocket__DOT__dut__DOT___T_139 = 0;
    CData/*0:0*/ tb_Rocket__DOT__dut__DOT___data_hazard_mem_T;
    tb_Rocket__DOT__dut__DOT___data_hazard_mem_T = 0;
    CData/*0:0*/ tb_Rocket__DOT__dut__DOT___data_hazard_mem_T_2;
    tb_Rocket__DOT__dut__DOT___data_hazard_mem_T_2 = 0;
    CData/*0:0*/ tb_Rocket__DOT__dut__DOT__wb_dcache_miss;
    tb_Rocket__DOT__dut__DOT__wb_dcache_miss = 0;
    CData/*0:0*/ tb_Rocket__DOT__dut__DOT__wb_set_sboard;
    tb_Rocket__DOT__dut__DOT__wb_set_sboard = 0;
    CData/*0:0*/ tb_Rocket__DOT__dut__DOT__wb_wen;
    tb_Rocket__DOT__dut__DOT__wb_wen = 0;
    IData/*31:0*/ tb_Rocket__DOT__dut__DOT___mem_br_target_T_8;
    tb_Rocket__DOT__dut__DOT___mem_br_target_T_8 = 0;
    CData/*4:0*/ tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rd;
    tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rd = 0;
    CData/*7:0*/ tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_s_T_15;
    tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_s_T_15 = 0;
    SData/*11:0*/ tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_s_T_147;
    tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_s_T_147 = 0;
    CData/*2:0*/ tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_s_funct_T_2;
    tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_s_funct_T_2 = 0;
    CData/*4:0*/ tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_T_2;
    tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_T_2 = 0;
    CData/*2:0*/ tb_Rocket__DOT__dut__DOT__div__DOT___GEN_6;
    tb_Rocket__DOT__dut__DOT__div__DOT___GEN_6 = 0;
    CData/*0:0*/ tb_Rocket__DOT__dut__DOT__div__DOT___GEN_7;
    tb_Rocket__DOT__dut__DOT__div__DOT___GEN_7 = 0;
    IData/*31:0*/ tb_Rocket__DOT__dut__DOT__div__DOT__loOut;
    tb_Rocket__DOT__dut__DOT__div__DOT__loOut = 0;
    QData/*63:0*/ tb_Rocket__DOT__dut__DOT__alu__DOT__in2_inv;
    tb_Rocket__DOT__dut__DOT__alu__DOT__in2_inv = 0;
    QData/*63:0*/ tb_Rocket__DOT__dut__DOT__alu__DOT__shin_r;
    tb_Rocket__DOT__dut__DOT__alu__DOT__shin_r = 0;
    CData/*0:0*/ tb_Rocket__DOT__dut__DOT__alu__DOT___shin_T_2;
    tb_Rocket__DOT__dut__DOT__alu__DOT___shin_T_2 = 0;
    QData/*63:0*/ tb_Rocket__DOT__dut__DOT__alu__DOT___shin_T_11;
    tb_Rocket__DOT__dut__DOT__alu__DOT___shin_T_11 = 0;
    QData/*63:0*/ tb_Rocket__DOT__dut__DOT__alu__DOT___shin_T_21;
    tb_Rocket__DOT__dut__DOT__alu__DOT___shin_T_21 = 0;
    QData/*63:0*/ tb_Rocket__DOT__dut__DOT__alu__DOT___shin_T_31;
    tb_Rocket__DOT__dut__DOT__alu__DOT___shin_T_31 = 0;
    QData/*63:0*/ tb_Rocket__DOT__dut__DOT__alu__DOT___shin_T_41;
    tb_Rocket__DOT__dut__DOT__alu__DOT___shin_T_41 = 0;
    QData/*63:0*/ tb_Rocket__DOT__dut__DOT__alu__DOT___shin_T_51;
    tb_Rocket__DOT__dut__DOT__alu__DOT___shin_T_51 = 0;
    QData/*63:0*/ tb_Rocket__DOT__dut__DOT__alu__DOT__shin;
    tb_Rocket__DOT__dut__DOT__alu__DOT__shin = 0;
    QData/*63:0*/ tb_Rocket__DOT__dut__DOT__alu__DOT__shout_r;
    tb_Rocket__DOT__dut__DOT__alu__DOT__shout_r = 0;
    QData/*63:0*/ tb_Rocket__DOT__dut__DOT__alu__DOT___shout_l_T_8;
    tb_Rocket__DOT__dut__DOT__alu__DOT___shout_l_T_8 = 0;
    QData/*63:0*/ tb_Rocket__DOT__dut__DOT__alu__DOT___shout_l_T_18;
    tb_Rocket__DOT__dut__DOT__alu__DOT___shout_l_T_18 = 0;
    QData/*63:0*/ tb_Rocket__DOT__dut__DOT__alu__DOT___shout_l_T_28;
    tb_Rocket__DOT__dut__DOT__alu__DOT___shout_l_T_28 = 0;
    QData/*63:0*/ tb_Rocket__DOT__dut__DOT__alu__DOT___shout_l_T_38;
    tb_Rocket__DOT__dut__DOT__alu__DOT___shout_l_T_38 = 0;
    QData/*63:0*/ tb_Rocket__DOT__dut__DOT__alu__DOT___shout_l_T_48;
    tb_Rocket__DOT__dut__DOT__alu__DOT___shout_l_T_48 = 0;
    CData/*0:0*/ tb_Rocket__DOT__dut__DOT__bpu__DOT___r_T_8;
    tb_Rocket__DOT__dut__DOT__bpu__DOT___r_T_8 = 0;
    QData/*32:0*/ tb_Rocket__DOT__dut__DOT__bpu__DOT___GEN_11;
    tb_Rocket__DOT__dut__DOT__bpu__DOT___GEN_11 = 0;
    QData/*32:0*/ tb_Rocket__DOT__dut__DOT__bpu__DOT___r_T_24;
    tb_Rocket__DOT__dut__DOT__bpu__DOT___r_T_24 = 0;
    CData/*0:0*/ tb_Rocket__DOT__dut__DOT__bpu__DOT___r_T_26;
    tb_Rocket__DOT__dut__DOT__bpu__DOT___r_T_26 = 0;
    CData/*0:0*/ tb_Rocket__DOT__dut__DOT__bpu__DOT__r;
    tb_Rocket__DOT__dut__DOT__bpu__DOT__r = 0;
    CData/*0:0*/ tb_Rocket__DOT__dut__DOT__bpu__DOT__w;
    tb_Rocket__DOT__dut__DOT__bpu__DOT__w = 0;
    CData/*0:0*/ tb_Rocket__DOT__dut__DOT__bpu__DOT__x;
    tb_Rocket__DOT__dut__DOT__bpu__DOT__x = 0;
    CData/*6:0*/ tb_Rocket__DOT__dut__DOT__csr__DOT__nextSmall;
    tb_Rocket__DOT__dut__DOT__csr__DOT__nextSmall = 0;
    CData/*6:0*/ tb_Rocket__DOT__dut__DOT__csr__DOT__nextSmall_1;
    tb_Rocket__DOT__dut__DOT__csr__DOT__nextSmall_1 = 0;
    QData/*63:0*/ tb_Rocket__DOT__dut__DOT__csr__DOT___T_20;
    tb_Rocket__DOT__dut__DOT__csr__DOT___T_20 = 0;
    QData/*63:0*/ tb_Rocket__DOT__dut__DOT__csr__DOT___wdata_T_6;
    tb_Rocket__DOT__dut__DOT__csr__DOT___wdata_T_6 = 0;
    CData/*0:0*/ tb_Rocket__DOT__dut__DOT__csr__DOT__insn_call;
    tb_Rocket__DOT__dut__DOT__csr__DOT__insn_call = 0;
    CData/*5:0*/ tb_Rocket__DOT__dut__DOT__csr__DOT__decoded_lo_5;
    tb_Rocket__DOT__dut__DOT__csr__DOT__decoded_lo_5 = 0;
    CData/*3:0*/ tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_T_16;
    tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_T_16 = 0;
    CData/*1:0*/ tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_T_22;
    tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_T_22 = 0;
    CData/*0:0*/ tb_Rocket__DOT__dut__DOT__csr__DOT___io_eret_T;
    tb_Rocket__DOT__dut__DOT__csr__DOT___io_eret_T = 0;
    CData/*0:0*/ tb_Rocket__DOT__dut__DOT__csr__DOT___GEN_219;
    tb_Rocket__DOT__dut__DOT__csr__DOT___GEN_219 = 0;
    CData/*1:0*/ __VdfgRegularize_h6e95ff9d_0_0;
    __VdfgRegularize_h6e95ff9d_0_0 = 0;
    CData/*0:0*/ __VdfgRegularize_h6e95ff9d_0_5;
    __VdfgRegularize_h6e95ff9d_0_5 = 0;
    CData/*0:0*/ __VdfgRegularize_h6e95ff9d_0_9;
    __VdfgRegularize_h6e95ff9d_0_9 = 0;
    SData/*15:0*/ __VdfgRegularize_h6e95ff9d_0_11;
    __VdfgRegularize_h6e95ff9d_0_11 = 0;
    CData/*1:0*/ __VdfgRegularize_h6e95ff9d_0_12;
    __VdfgRegularize_h6e95ff9d_0_12 = 0;
    CData/*1:0*/ __VdfgRegularize_h6e95ff9d_0_14;
    __VdfgRegularize_h6e95ff9d_0_14 = 0;
    CData/*2:0*/ __VdfgRegularize_h6e95ff9d_0_19;
    __VdfgRegularize_h6e95ff9d_0_19 = 0;
    CData/*1:0*/ __VdfgRegularize_h6e95ff9d_0_20;
    __VdfgRegularize_h6e95ff9d_0_20 = 0;
    CData/*1:0*/ __VdfgRegularize_h6e95ff9d_0_21;
    __VdfgRegularize_h6e95ff9d_0_21 = 0;
    CData/*2:0*/ __VdfgRegularize_h6e95ff9d_0_22;
    __VdfgRegularize_h6e95ff9d_0_22 = 0;
    CData/*1:0*/ __VdfgRegularize_h6e95ff9d_0_24;
    __VdfgRegularize_h6e95ff9d_0_24 = 0;
    CData/*0:0*/ __VdfgRegularize_h6e95ff9d_0_26;
    __VdfgRegularize_h6e95ff9d_0_26 = 0;
    CData/*0:0*/ __VdfgRegularize_h6e95ff9d_0_27;
    __VdfgRegularize_h6e95ff9d_0_27 = 0;
    CData/*0:0*/ __VdfgRegularize_h6e95ff9d_0_28;
    __VdfgRegularize_h6e95ff9d_0_28 = 0;
    IData/*29:0*/ __VdfgRegularize_h6e95ff9d_0_29;
    __VdfgRegularize_h6e95ff9d_0_29 = 0;
    CData/*0:0*/ __VdfgRegularize_h6e95ff9d_0_30;
    __VdfgRegularize_h6e95ff9d_0_30 = 0;
    CData/*0:0*/ __VdfgRegularize_h6e95ff9d_0_31;
    __VdfgRegularize_h6e95ff9d_0_31 = 0;
    CData/*0:0*/ __VdfgRegularize_h6e95ff9d_0_34;
    __VdfgRegularize_h6e95ff9d_0_34 = 0;
    CData/*0:0*/ __VdfgRegularize_h6e95ff9d_0_35;
    __VdfgRegularize_h6e95ff9d_0_35 = 0;
    SData/*11:0*/ __VdfgRegularize_h6e95ff9d_0_38;
    __VdfgRegularize_h6e95ff9d_0_38 = 0;
    CData/*2:0*/ __VdfgRegularize_h6e95ff9d_0_41;
    __VdfgRegularize_h6e95ff9d_0_41 = 0;
    CData/*4:0*/ __VdfgRegularize_h6e95ff9d_0_42;
    __VdfgRegularize_h6e95ff9d_0_42 = 0;
    CData/*4:0*/ __VdfgRegularize_h6e95ff9d_0_44;
    __VdfgRegularize_h6e95ff9d_0_44 = 0;
    CData/*5:0*/ __VdfgRegularize_h6e95ff9d_0_45;
    __VdfgRegularize_h6e95ff9d_0_45 = 0;
    CData/*2:0*/ __VdfgRegularize_h6e95ff9d_0_46;
    __VdfgRegularize_h6e95ff9d_0_46 = 0;
    CData/*5:0*/ __VdfgRegularize_h6e95ff9d_0_47;
    __VdfgRegularize_h6e95ff9d_0_47 = 0;
    CData/*6:0*/ __VdfgRegularize_h6e95ff9d_0_48;
    __VdfgRegularize_h6e95ff9d_0_48 = 0;
    CData/*5:0*/ __VdfgRegularize_h6e95ff9d_0_50;
    __VdfgRegularize_h6e95ff9d_0_50 = 0;
    CData/*0:0*/ __VdfgRegularize_h6e95ff9d_0_66;
    __VdfgRegularize_h6e95ff9d_0_66 = 0;
    CData/*0:0*/ __VdfgRegularize_h6e95ff9d_0_67;
    __VdfgRegularize_h6e95ff9d_0_67 = 0;
    CData/*0:0*/ __VdfgRegularize_h6e95ff9d_0_70;
    __VdfgRegularize_h6e95ff9d_0_70 = 0;
    CData/*0:0*/ __VdfgRegularize_h6e95ff9d_0_73;
    __VdfgRegularize_h6e95ff9d_0_73 = 0;
    CData/*0:0*/ __VdfgRegularize_h6e95ff9d_0_74;
    __VdfgRegularize_h6e95ff9d_0_74 = 0;
    CData/*0:0*/ __VdfgRegularize_h6e95ff9d_0_75;
    __VdfgRegularize_h6e95ff9d_0_75 = 0;
    CData/*0:0*/ __VdfgRegularize_h6e95ff9d_0_77;
    __VdfgRegularize_h6e95ff9d_0_77 = 0;
    CData/*0:0*/ __VdfgRegularize_h6e95ff9d_0_78;
    __VdfgRegularize_h6e95ff9d_0_78 = 0;
    CData/*0:0*/ __VdfgRegularize_h6e95ff9d_0_81;
    __VdfgRegularize_h6e95ff9d_0_81 = 0;
    CData/*5:0*/ __VdfgRegularize_h6e95ff9d_0_82;
    __VdfgRegularize_h6e95ff9d_0_82 = 0;
    CData/*3:0*/ __VdfgRegularize_h6e95ff9d_0_84;
    __VdfgRegularize_h6e95ff9d_0_84 = 0;
    CData/*1:0*/ __VdfgRegularize_h6e95ff9d_0_85;
    __VdfgRegularize_h6e95ff9d_0_85 = 0;
    SData/*11:0*/ __VdfgRegularize_h6e95ff9d_0_86;
    __VdfgRegularize_h6e95ff9d_0_86 = 0;
    QData/*33:0*/ __Vdly__tb_Rocket__DOT__fpc;
    __Vdly__tb_Rocket__DOT__fpc = 0;
    CData/*0:0*/ __Vdly__tb_Rocket__DOT__dut__DOT__id_reg_fence;
    __Vdly__tb_Rocket__DOT__dut__DOT__id_reg_fence = 0;
    CData/*0:0*/ __Vdly__tb_Rocket__DOT__dut__DOT__id_reg_pause;
    __Vdly__tb_Rocket__DOT__dut__DOT__id_reg_pause = 0;
    CData/*0:0*/ __Vdly__tb_Rocket__DOT__dut__DOT__mem_reg_flush_pipe;
    __Vdly__tb_Rocket__DOT__dut__DOT__mem_reg_flush_pipe = 0;
    CData/*2:0*/ __Vdly__tb_Rocket__DOT__dut__DOT__div__DOT__state;
    __Vdly__tb_Rocket__DOT__dut__DOT__div__DOT__state = 0;
    CData/*6:0*/ __Vdly__tb_Rocket__DOT__dut__DOT__div__DOT__count;
    __Vdly__tb_Rocket__DOT__dut__DOT__div__DOT__count = 0;
    CData/*0:0*/ __Vdly__tb_Rocket__DOT__dut__DOT__div__DOT__neg_out;
    __Vdly__tb_Rocket__DOT__dut__DOT__div__DOT__neg_out = 0;
    VlWide<3>/*64:0*/ __Vdly__tb_Rocket__DOT__dut__DOT__div__DOT__divisor;
    VL_ZERO_W(65, __Vdly__tb_Rocket__DOT__dut__DOT__div__DOT__divisor);
    CData/*0:0*/ __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_7_cfg_l;
    __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_7_cfg_l = 0;
    CData/*0:0*/ __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_singleStepped;
    __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_singleStepped = 0;
    CData/*0:0*/ __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_4_cfg_l;
    __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_4_cfg_l = 0;
    CData/*0:0*/ __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_3_cfg_l;
    __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_3_cfg_l = 0;
    CData/*0:0*/ __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_5_cfg_l;
    __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_5_cfg_l = 0;
    CData/*0:0*/ __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_6_cfg_l;
    __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_6_cfg_l = 0;
    CData/*0:0*/ __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_0_cfg_l;
    __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_0_cfg_l = 0;
    CData/*0:0*/ __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_control_dmode;
    __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_control_dmode = 0;
    CData/*0:0*/ __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_2_cfg_l;
    __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_2_cfg_l = 0;
    CData/*0:0*/ __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_1_cfg_l;
    __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_1_cfg_l = 0;
    QData/*63:0*/ __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_misa;
    __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_misa = 0;
    CData/*2:0*/ __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mcountinhibit;
    __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mcountinhibit = 0;
    QData/*63:0*/ __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_custom_0;
    __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_custom_0 = 0;
    QData/*63:0*/ __VdlyVal__tb_Rocket__DOT__dmem8__v0;
    __VdlyVal__tb_Rocket__DOT__dmem8__v0 = 0;
    CData/*7:0*/ __VdlyDim0__tb_Rocket__DOT__dmem8__v0;
    __VdlyDim0__tb_Rocket__DOT__dmem8__v0 = 0;
    CData/*0:0*/ __VdlySet__tb_Rocket__DOT__dmem8__v0;
    __VdlySet__tb_Rocket__DOT__dmem8__v0 = 0;
    QData/*63:0*/ __VdlyVal__tb_Rocket__DOT__dut__DOT__rf__v0;
    __VdlyVal__tb_Rocket__DOT__dut__DOT__rf__v0 = 0;
    CData/*4:0*/ __VdlyDim0__tb_Rocket__DOT__dut__DOT__rf__v0;
    __VdlyDim0__tb_Rocket__DOT__dut__DOT__rf__v0 = 0;
    CData/*0:0*/ __VdlySet__tb_Rocket__DOT__dut__DOT__rf__v0;
    __VdlySet__tb_Rocket__DOT__dut__DOT__rf__v0 = 0;
    VlWide<5>/*159:0*/ __Vtemp_1;
    VlWide<3>/*95:0*/ __Vtemp_9;
    VlWide<3>/*95:0*/ __Vtemp_10;
    VlWide<3>/*95:0*/ __Vtemp_13;
    VlWide<3>/*95:0*/ __Vtemp_14;
    VlWide<3>/*95:0*/ __Vtemp_16;
    VlWide<3>/*95:0*/ __Vtemp_17;
    VlWide<3>/*95:0*/ __Vtemp_18;
    VlWide<3>/*95:0*/ __Vtemp_22;
    VlWide<3>/*95:0*/ __Vtemp_23;
    VlWide<6>/*191:0*/ __Vtemp_27;
    VlWide<6>/*191:0*/ __Vtemp_28;
    VlWide<3>/*95:0*/ __Vtemp_31;
    VlWide<3>/*95:0*/ __Vtemp_32;
    // Body
    __VdlySet__tb_Rocket__DOT__dut__DOT__rf__v0 = 0U;
    __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_singleStepped 
        = vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_singleStepped;
    __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_custom_0 
        = vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_custom_0;
    __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mcountinhibit 
        = vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mcountinhibit;
    __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_0_cfg_l 
        = vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_0_cfg_l;
    __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_4_cfg_l 
        = vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_4_cfg_l;
    __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_3_cfg_l 
        = vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_3_cfg_l;
    __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_5_cfg_l 
        = vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_5_cfg_l;
    __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_6_cfg_l 
        = vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_6_cfg_l;
    __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_2_cfg_l 
        = vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_2_cfg_l;
    __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_1_cfg_l 
        = vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_1_cfg_l;
    __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_7_cfg_l 
        = vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_7_cfg_l;
    __VdlySet__tb_Rocket__DOT__dmem8__v0 = 0U;
    __Vdly__tb_Rocket__DOT__dut__DOT__id_reg_fence 
        = vlSelfRef.tb_Rocket__DOT__dut__DOT__id_reg_fence;
    __Vdly__tb_Rocket__DOT__dut__DOT__id_reg_pause 
        = vlSelfRef.tb_Rocket__DOT__dut__DOT__id_reg_pause;
    __Vdly__tb_Rocket__DOT__dut__DOT__div__DOT__neg_out 
        = vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__neg_out;
    __Vdly__tb_Rocket__DOT__dut__DOT__div__DOT__divisor[0U] 
        = vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__divisor[0U];
    __Vdly__tb_Rocket__DOT__dut__DOT__div__DOT__divisor[1U] 
        = vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__divisor[1U];
    __Vdly__tb_Rocket__DOT__dut__DOT__div__DOT__divisor[2U] 
        = vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__divisor[2U];
    __Vdly__tb_Rocket__DOT__dut__DOT__div__DOT__count 
        = vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__count;
    __Vdly__tb_Rocket__DOT__dut__DOT__div__DOT__state 
        = vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__state;
    __Vdly__tb_Rocket__DOT__dut__DOT__mem_reg_flush_pipe 
        = vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_flush_pipe;
    __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_misa 
        = vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_misa;
    __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_control_dmode 
        = vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_control_dmode;
    __Vdly__tb_Rocket__DOT__fpc = vlSelfRef.tb_Rocket__DOT__fpc;
    if (((0U != (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__rf_waddr)) 
         & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__rf_wen))) {
        if ((0x1eU >= (0x0000001fU & (~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__rf_waddr))))) {
            __VdlyVal__tb_Rocket__DOT__dut__DOT__rf__v0 
                = vlSelfRef.tb_Rocket__DOT__dut__DOT__rf_MPORT_data;
            __VdlyDim0__tb_Rocket__DOT__dut__DOT__rf__v0 
                = (0x0000001fU & (~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__rf_waddr)));
            __VdlySet__tb_Rocket__DOT__dut__DOT__rf__v0 = 1U;
        }
    }
    __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_singleStepped 
        = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr_io_singleStep) 
           && ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr_io_retire) 
               | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_singleStepped) 
                  | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__exception))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mstatus_spp 
        = ((~ (IData)(vlSelfRef.tb_Rocket__DOT__reset)) 
           & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mstatus_spp));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mtvec 
        = ((IData)(((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__csr_wen)
                     ? ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_7)
                         ? vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata
                         : (QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mtvec)))
                     : (QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mtvec)))) 
           & (IData)((- (QData)((IData)((1U & (~ (IData)(vlSelfRef.tb_Rocket__DOT__reset))))))));
    __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mcountinhibit 
        = (7U & ((IData)(((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__csr_wen)
                           ? ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_9)
                               ? (0xfffffffffffffffdULL 
                                  & vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata)
                               : (QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mcountinhibit)))
                           : (QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mcountinhibit)))) 
                 & (IData)((- (QData)((IData)((1U & 
                                               (~ (IData)(vlSelfRef.tb_Rocket__DOT__reset)))))))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_6_addr 
        = (0x3fffffffU & (IData)(((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__csr_wen)
                                   ? (((~ ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_6_cfg_l) 
                                           | (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_39))) 
                                       & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_95))
                                       ? vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata
                                       : (QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_6_addr)))
                                   : (QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_6_addr)))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_7_addr 
        = (0x3fffffffU & (IData)(((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__csr_wen)
                                   ? (((~ ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_7_cfg_l) 
                                           | (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_39))) 
                                       & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_97))
                                       ? vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata
                                       : (QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_7_addr)))
                                   : (QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_7_addr)))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_0_addr 
        = (0x3fffffffU & (IData)(((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__csr_wen)
                                   ? (((~ ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_0_cfg_l) 
                                           | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_1_cfg_l) 
                                              & (1U 
                                                 == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_1_cfg_a))))) 
                                       & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_83))
                                       ? vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata
                                       : (QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_0_addr)))
                                   : (QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_0_addr)))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_5_addr 
        = (0x3fffffffU & (IData)(((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__csr_wen)
                                   ? (((~ ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_5_cfg_l) 
                                           | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_6_cfg_l) 
                                              & (1U 
                                                 == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_6_cfg_a))))) 
                                       & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_93))
                                       ? vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata
                                       : (QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_5_addr)))
                                   : (QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_5_addr)))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_4_addr 
        = (0x3fffffffU & (IData)(((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__csr_wen)
                                   ? (((~ ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_4_cfg_l) 
                                           | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_5_cfg_l) 
                                              & (1U 
                                                 == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_5_cfg_a))))) 
                                       & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_91))
                                       ? vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata
                                       : (QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_4_addr)))
                                   : (QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_4_addr)))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_3_addr 
        = (0x3fffffffU & (IData)(((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__csr_wen)
                                   ? (((~ ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_3_cfg_l) 
                                           | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_4_cfg_l) 
                                              & (1U 
                                                 == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_4_cfg_a))))) 
                                       & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_89))
                                       ? vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata
                                       : (QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_3_addr)))
                                   : (QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_3_addr)))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_1_addr 
        = (0x3fffffffU & (IData)(((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__csr_wen)
                                   ? (((~ ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_1_cfg_l) 
                                           | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_2_cfg_l) 
                                              & (1U 
                                                 == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_2_cfg_a))))) 
                                       & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_85))
                                       ? vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata
                                       : (QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_1_addr)))
                                   : (QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_1_addr)))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_2_addr 
        = (0x3fffffffU & (IData)(((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__csr_wen)
                                   ? (((~ ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_2_cfg_l) 
                                           | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_3_cfg_l) 
                                              & (1U 
                                                 == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_3_cfg_a))))) 
                                       & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_87))
                                       ? vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata
                                       : (QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_2_addr)))
                                   : (QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_2_addr)))));
    if (vlSelfRef.tb_Rocket__DOT__reset) {
        __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_custom_0 = 0x0000000000000208ULL;
        __Vdly__tb_Rocket__DOT__dut__DOT__id_reg_fence = 0U;
        __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_misa = 0x8000000000801105ULL;
        __Vdly__tb_Rocket__DOT__fpc = 0x0000000000001000ULL;
        vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mstatus_gva = 0U;
        vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__large_1 = 0ULL;
        vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__large_ = 0ULL;
        vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mcause = 0ULL;
        vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_dcsr_ebreakm = 0U;
        vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_dcsr_step = 0U;
        __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_0_cfg_l = 0U;
        vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_0_cfg_a = 0U;
        __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_7_cfg_l = 0U;
        vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_7_cfg_a = 0U;
        __Vdly__tb_Rocket__DOT__dut__DOT__div__DOT__state = 0U;
        vlSelfRef.tb_Rocket__DOT__dut__DOT___r = 0U;
        vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_dcsr_cause = 0U;
        __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_control_dmode = 0U;
        vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_control_action = 0U;
        vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_control_x = 0U;
        vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_control_w = 0U;
        vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_control_r = 0U;
        __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_1_cfg_l = 0U;
        vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_1_cfg_a = 0U;
        __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_6_cfg_l = 0U;
        vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_6_cfg_a = 0U;
        __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_5_cfg_l = 0U;
        vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_5_cfg_a = 0U;
        __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_4_cfg_l = 0U;
        vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_4_cfg_a = 0U;
        __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_2_cfg_l = 0U;
        vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_2_cfg_a = 0U;
        __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_3_cfg_l = 0U;
        vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_3_cfg_a = 0U;
    } else {
        if (vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__csr_wen) {
            if (vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_129) {
                __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_custom_0 
                    = ((0x0000000000000208ULL & vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata) 
                       | (0xfffffffffffffdf7ULL & vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_custom_0));
            }
            if (vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_3) {
                if ((1U & ((~ (IData)((vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_pc 
                                       >> 1U))) | (IData)(
                                                          (vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata 
                                                           >> 2U))))) {
                    __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_misa 
                        = ((0x0000000000001005ULL & 
                            (~ ((~ vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata) 
                                | (QData)((IData)((8U 
                                                   & ((~ (IData)(
                                                                 (vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata 
                                                                  >> 5U))) 
                                                      << 3U))))))) 
                           | (0xffffffffffffeffaULL 
                              & vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_misa));
                }
            }
            vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__large_1 
                = (0x03ffffffffffffffULL & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_131)
                                             ? (vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata 
                                                >> 6U)
                                             : vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___GEN_3));
            vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__large_ 
                = (0x03ffffffffffffffULL & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_133)
                                             ? (vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata 
                                                >> 6U)
                                             : vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___GEN_1));
            vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mcause 
                = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_73)
                    ? (0x800000000000000fULL & vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata)
                    : vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___GEN_214);
            if (vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_123) {
                vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_dcsr_ebreakm 
                    = (1U & (IData)((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata 
                                     >> 0x0000000fU)));
                vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_dcsr_step 
                    = (1U & (IData)((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata 
                                     >> 2U)));
            }
            if (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_79) 
                 & (~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_0_cfg_l)))) {
                __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_0_cfg_l 
                    = (1U & (IData)((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata 
                                     >> 7U)));
                vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_0_cfg_a 
                    = (3U & (IData)((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata 
                                     >> 3U)));
            }
            if (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_79) 
                 & (~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_7_cfg_l)))) {
                __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_7_cfg_l 
                    = (1U & (IData)((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata 
                                     >> 0x0000003fU)));
                vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_7_cfg_a 
                    = (3U & (IData)((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata 
                                     >> 0x0000003bU)));
            }
            if ((1U & ((~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_control_dmode)) 
                       | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_debug)))) {
                if (vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_117) {
                    __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_control_dmode 
                        = vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__dMode;
                    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_control_action 
                        = ((IData)((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___newBPC_T_8 
                                    >> 0x0000000cU)) 
                           & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__dMode));
                    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_control_x 
                        = (1U & (IData)((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata 
                                         >> 2U)));
                    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_control_w 
                        = (1U & (IData)((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata 
                                         >> 1U)));
                    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_control_r 
                        = (1U & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata));
                }
            }
            if (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_79) 
                 & (~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_1_cfg_l)))) {
                __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_1_cfg_l 
                    = (1U & (IData)((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata 
                                     >> 0x0000000fU)));
                vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_1_cfg_a 
                    = (3U & (IData)((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata 
                                     >> 0x0000000bU)));
            }
            if (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_79) 
                 & (~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_6_cfg_l)))) {
                __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_6_cfg_l 
                    = (1U & (IData)((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata 
                                     >> 0x00000037U)));
                vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_6_cfg_a 
                    = (3U & (IData)((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata 
                                     >> 0x00000033U)));
            }
            if (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_79) 
                 & (~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_5_cfg_l)))) {
                __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_5_cfg_l 
                    = (1U & (IData)((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata 
                                     >> 0x0000002fU)));
                vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_5_cfg_a 
                    = (3U & (IData)((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata 
                                     >> 0x0000002bU)));
            }
            if (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_79) 
                 & (~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_4_cfg_l)))) {
                __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_4_cfg_l 
                    = (1U & (IData)((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata 
                                     >> 0x00000027U)));
                vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_4_cfg_a 
                    = (3U & (IData)((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata 
                                     >> 0x00000023U)));
            }
            if (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_79) 
                 & (~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_2_cfg_l)))) {
                __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_2_cfg_l 
                    = (1U & (IData)((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata 
                                     >> 0x00000017U)));
                vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_2_cfg_a 
                    = (3U & (IData)((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata 
                                     >> 0x00000013U)));
            }
            if (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_79) 
                 & (~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_3_cfg_l)))) {
                __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_3_cfg_l 
                    = (1U & (IData)((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata 
                                     >> 0x0000001fU)));
                vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_3_cfg_a 
                    = (3U & (IData)((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata 
                                     >> 0x0000001bU)));
            }
        } else {
            vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__large_1 
                = (0x03ffffffffffffffULL & vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___GEN_3);
            vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__large_ 
                = (0x03ffffffffffffffULL & vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___GEN_1);
            vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mcause 
                = vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___GEN_214;
        }
        if (vlSelfRef.tb_Rocket__DOT__dut__DOT__ctrl_killd) {
            if ((1U & (~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__id_mem_busy)))) {
                __Vdly__tb_Rocket__DOT__dut__DOT__id_reg_fence = 0U;
            }
        } else {
            __Vdly__tb_Rocket__DOT__dut__DOT__id_reg_fence 
                = (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__id_reg_fence) 
                    & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__id_mem_busy)) 
                   | (((vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                        >> 0x0000001aU) & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_orMatrixOutputs_T_1)) 
                      | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_11)));
        }
        if (((~ (IData)(vlSelfRef.tb_Rocket__DOT__reset)) 
             & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf_io_kill))) {
            __Vdly__tb_Rocket__DOT__fpc = (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_xcpt) 
                                            | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr_io_eret))
                                            ? ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__insn_ret)
                                                ? ((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_25)
                                                    ? vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___T_44
                                                    : vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___T_30)
                                                : ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__trapToDebug)
                                                    ? 
                                                   ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_debug)
                                                     ? 
                                                    ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__insn_break)
                                                      ? 0x0000000000000800ULL
                                                      : 0x0000000000000808ULL)
                                                     : 0x0000000000000800ULL)
                                                    : 
                                                   ((QData)((IData)(
                                                                    (((IData)(
                                                                              ((QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___read_mtvec_T_5)) 
                                                                               >> 8U)) 
                                                                      << 6U) 
                                                                     | (0x0000003fU 
                                                                        & ((IData)(
                                                                                ((0x8000000000000000ULL 
                                                                                == 
                                                                                (0x80000000000000c0ULL 
                                                                                & vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__cause)) 
                                                                                & vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___read_mtvec_T_5))
                                                                            ? (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__cause)
                                                                            : 
                                                                           (vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___read_mtvec_T_5 
                                                                            >> 2U)))))) 
                                                    << 2U)))
                                            : ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__replay_wb)
                                                ? vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_pc
                                                : vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_npc));
        } else if (((~ (IData)(vlSelfRef.tb_Rocket__DOT__red_d)) 
                    & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf_io_imem_ready))) {
            __Vdly__tb_Rocket__DOT__fpc = (0x00000003ffffffffULL 
                                           & (4ULL 
                                              + vlSelfRef.tb_Rocket__DOT__fpc));
        }
        if (vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__exception) {
            if ((1U & (~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__trapToDebug)))) {
                vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mstatus_gva = 0U;
            }
            if (vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__trapToDebug) {
                if ((1U & (~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_debug)))) {
                    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_dcsr_cause 
                        = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_singleStepped)
                            ? 4U : (3U & (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__causeIsDebugTrigger)
                                            ? 2U : 1U) 
                                          | (- (IData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__causeIsDebugInt))))));
                }
            }
        }
        __Vdly__tb_Rocket__DOT__dut__DOT__div__DOT__state 
            = (7U & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT___T_23)
                      ? ((4U & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_alu_fn))
                          ? (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__lhs_sign) 
                              | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__rhs_sign))
                              ? 1U : 3U) : 2U) : (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT___T_21) 
                                                   | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div_io_kill_REG) 
                                                      & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__killm_common)))
                                                   ? 0U
                                                   : 
                                                  ((3U 
                                                    == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__state))
                                                    ? 
                                                   ((0x40U 
                                                     == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__count))
                                                     ? 
                                                    (5U 
                                                     | (- (IData)(
                                                                  (1U 
                                                                   & (~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__neg_out))))))
                                                     : (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT___GEN_12))
                                                    : (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT___GEN_12)))));
        if (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT___T_21) 
             | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___T_145))) {
            vlSelfRef.tb_Rocket__DOT__dut__DOT___r 
                = ((((IData)(1U) << (0x0000001fU & 
                                     (vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
                                      >> 7U))) & (- (IData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___T_145)))) 
                   | vlSelfRef.tb_Rocket__DOT__dut__DOT___T_143);
        } else if (vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT___T_21) {
            vlSelfRef.tb_Rocket__DOT__dut__DOT___r 
                = vlSelfRef.tb_Rocket__DOT__dut__DOT___T_143;
        }
    }
    if ((1U & (~ (IData)(vlSelfRef.tb_Rocket__DOT__reset)))) {
        if (((IData)(vlSelfRef.tb_Rocket__DOT__q2_v) 
             & (~ (IData)(vlSelfRef.tb_Rocket__DOT__q2_is_load)))) {
            vlSelfRef.tb_Rocket__DOT__blk = vlSelfRef.tb_Rocket__DOT__dmem8
                [(0x000000ffU & (IData)((vlSelfRef.tb_Rocket__DOT__q2_addr 
                                         >> 3U)))];
            if ((1U & (IData)(vlSelfRef.tb_Rocket__DOT__wbe))) {
                vlSelfRef.tb_Rocket__DOT__blk = ((0xffffffffffffff00ULL 
                                                  & vlSelfRef.tb_Rocket__DOT__blk) 
                                                 | (IData)((IData)(
                                                                   (0x000000ffU 
                                                                    & (IData)(vlSelfRef.tb_Rocket__DOT__wdata_shift)))));
            }
            if ((2U & (IData)(vlSelfRef.tb_Rocket__DOT__wbe))) {
                vlSelfRef.tb_Rocket__DOT__blk = ((0xffffffffffff00ffULL 
                                                  & vlSelfRef.tb_Rocket__DOT__blk) 
                                                 | ((QData)((IData)(
                                                                    (0x000000ffU 
                                                                     & (IData)(
                                                                               (vlSelfRef.tb_Rocket__DOT__wdata_shift 
                                                                                >> 8U))))) 
                                                    << 8U));
            }
            if ((4U & (IData)(vlSelfRef.tb_Rocket__DOT__wbe))) {
                vlSelfRef.tb_Rocket__DOT__blk = ((0xffffffffff00ffffULL 
                                                  & vlSelfRef.tb_Rocket__DOT__blk) 
                                                 | ((QData)((IData)(
                                                                    (0x000000ffU 
                                                                     & (IData)(
                                                                               (vlSelfRef.tb_Rocket__DOT__wdata_shift 
                                                                                >> 0x10U))))) 
                                                    << 0x00000010U));
            }
            if ((8U & (IData)(vlSelfRef.tb_Rocket__DOT__wbe))) {
                vlSelfRef.tb_Rocket__DOT__blk = ((0xffffffff00ffffffULL 
                                                  & vlSelfRef.tb_Rocket__DOT__blk) 
                                                 | ((QData)((IData)(
                                                                    (0x000000ffU 
                                                                     & (IData)(
                                                                               (vlSelfRef.tb_Rocket__DOT__wdata_shift 
                                                                                >> 0x18U))))) 
                                                    << 0x00000018U));
            }
            if ((0x00000010U & (IData)(vlSelfRef.tb_Rocket__DOT__wbe))) {
                vlSelfRef.tb_Rocket__DOT__blk = ((0xffffff00ffffffffULL 
                                                  & vlSelfRef.tb_Rocket__DOT__blk) 
                                                 | ((QData)((IData)(
                                                                    (0x000000ffU 
                                                                     & (IData)(
                                                                               (vlSelfRef.tb_Rocket__DOT__wdata_shift 
                                                                                >> 0x20U))))) 
                                                    << 0x00000020U));
            }
            if ((0x00000020U & (IData)(vlSelfRef.tb_Rocket__DOT__wbe))) {
                vlSelfRef.tb_Rocket__DOT__blk = ((0xffff00ffffffffffULL 
                                                  & vlSelfRef.tb_Rocket__DOT__blk) 
                                                 | ((QData)((IData)(
                                                                    (0x000000ffU 
                                                                     & (IData)(
                                                                               (vlSelfRef.tb_Rocket__DOT__wdata_shift 
                                                                                >> 0x28U))))) 
                                                    << 0x00000028U));
            }
            if ((0x00000040U & (IData)(vlSelfRef.tb_Rocket__DOT__wbe))) {
                vlSelfRef.tb_Rocket__DOT__blk = ((0xff00ffffffffffffULL 
                                                  & vlSelfRef.tb_Rocket__DOT__blk) 
                                                 | ((QData)((IData)(
                                                                    (0x000000ffU 
                                                                     & (IData)(
                                                                               (vlSelfRef.tb_Rocket__DOT__wdata_shift 
                                                                                >> 0x30U))))) 
                                                    << 0x00000030U));
            }
            if ((0x00000080U & (IData)(vlSelfRef.tb_Rocket__DOT__wbe))) {
                vlSelfRef.tb_Rocket__DOT__blk = ((0x00ffffffffffffffULL 
                                                  & vlSelfRef.tb_Rocket__DOT__blk) 
                                                 | ((QData)((IData)(
                                                                    (0x000000ffU 
                                                                     & (IData)(
                                                                               (vlSelfRef.tb_Rocket__DOT__wdata_shift 
                                                                                >> 0x38U))))) 
                                                    << 0x00000038U));
            }
            __VdlyVal__tb_Rocket__DOT__dmem8__v0 = vlSelfRef.tb_Rocket__DOT__blk;
            __VdlyDim0__tb_Rocket__DOT__dmem8__v0 = 
                (0x000000ffU & (IData)((vlSelfRef.tb_Rocket__DOT__q2_addr 
                                        >> 3U)));
            __VdlySet__tb_Rocket__DOT__dmem8__v0 = 1U;
        }
        vlSelfRef.tb_Rocket__DOT__q2_size = vlSelfRef.tb_Rocket__DOT__q1_size;
        vlSelfRef.tb_Rocket__DOT__q2_tag = vlSelfRef.tb_Rocket__DOT__q1_tag;
        vlSelfRef.tb_Rocket__DOT__q2_signed = vlSelfRef.tb_Rocket__DOT__q1_signed;
        vlSelfRef.tb_Rocket__DOT__q2_is_load = vlSelfRef.tb_Rocket__DOT__q1_is_load;
        vlSelfRef.tb_Rocket__DOT__q2_addr = vlSelfRef.tb_Rocket__DOT__q1_addr;
        vlSelfRef.tb_Rocket__DOT__q1_size = vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_mem_size;
        vlSelfRef.tb_Rocket__DOT__q1_tag = ((0x0000003eU 
                                             & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_inst 
                                                >> 6U)) 
                                            | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_fp));
        vlSelfRef.tb_Rocket__DOT__q1_signed = (1U & 
                                               (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_inst 
                                                   >> 0x0000000eU)));
        vlSelfRef.tb_Rocket__DOT__q1_is_load = (0U 
                                                == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_mem_cmd));
        vlSelfRef.tb_Rocket__DOT__q1_addr = (((QData)((IData)(
                                                              (1U 
                                                               & (((0U 
                                                                    == 
                                                                    (0x7fffffffU 
                                                                     & (IData)(
                                                                               (vlSelfRef.tb_Rocket__DOT__dut__DOT__div_io_req_bits_in1 
                                                                                >> 0x00000021U)))) 
                                                                   | (0x7fffffffU 
                                                                      == 
                                                                      (0x7fffffffU 
                                                                       & (IData)(
                                                                                (vlSelfRef.tb_Rocket__DOT__dut__DOT__div_io_req_bits_in1 
                                                                                >> 0x00000021U)))))
                                                                   ? (IData)(
                                                                             (vlSelfRef.tb_Rocket__DOT__dut__DOT__alu_io_adder_out 
                                                                              >> 0x00000021U))
                                                                   : 
                                                                  (~ (IData)(
                                                                             (vlSelfRef.tb_Rocket__DOT__dut__DOT__alu_io_adder_out 
                                                                              >> 0x00000020U))))))) 
                                              << 0x00000021U) 
                                             | (0x00000001ffffffffULL 
                                                & vlSelfRef.tb_Rocket__DOT__dut__DOT__alu_io_adder_out));
    }
    if ((1U & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mcountinhibit) 
               | ((0U == (0x0000001fU & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__small_1))) 
                  | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf_io_kill))))) {
        __Vdly__tb_Rocket__DOT__dut__DOT__id_reg_pause = 0U;
    } else if ((1U & (~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ctrl_killd)))) {
        __Vdly__tb_Rocket__DOT__dut__DOT__id_reg_pause 
            = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__id_reg_pause) 
               | (IData)(((0U == (0x00f00000U & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                          & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_11))));
    }
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__io_status_cease_r 
        = ((1U & (~ (IData)(vlSelfRef.tb_Rocket__DOT__reset))) 
           && ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__io_status_cease_r) 
               | (IData)((((4U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr_io_rw_cmd)) 
                           & (0x30400000U == (0x30400000U 
                                              & vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst))) 
                          & ((3U == (3U & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
                                              >> 0x0000001eU)))) 
                             & (0x0000001fU == (0x0000001fU 
                                                & (~ 
                                                   (vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
                                                    >> 0x00000017U)))))))));
    if (vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__csr_wen) {
        if ((1U & ((~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_control_dmode)) 
                   | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_debug)))) {
            vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_address 
                = (0x00000001ffffffffULL & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_119)
                                             ? vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata
                                             : vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_address));
            if (vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_117) {
                vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_control_tmatch 
                    = (3U & (IData)((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata 
                                     >> 7U)));
            }
        } else {
            vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_address 
                = (0x00000001ffffffffULL & vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_address);
        }
        if (vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_69) {
            vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mscratch 
                = vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata;
        }
        if (vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_5) {
            vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mie 
                = (0x0000000000000888ULL & vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata);
        }
        if (vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_127) {
            vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_dscratch0 
                = vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata;
        }
        vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mtval 
            = (0x00000003ffffffffULL & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_75)
                                         ? vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata
                                         : vlSelfRef.__VdfgRegularize_h6e95ff9d_0_64));
        vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mepc 
            = (0x00000003ffffffffULL & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_71)
                                         ? (~ (1ULL 
                                               | (~ vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata)))
                                         : vlSelfRef.__VdfgRegularize_h6e95ff9d_0_65));
        vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_dpc 
            = (0x00000003ffffffffULL & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_125)
                                         ? (~ (1ULL 
                                               | (~ vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata)))
                                         : vlSelfRef.__VdfgRegularize_h6e95ff9d_0_61));
        if (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_79) 
             & (~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_0_cfg_l)))) {
            vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_0_cfg_x 
                = (1U & (IData)((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata 
                                 >> 2U)));
            vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_0_cfg_w 
                = (IData)((3ULL == (3ULL & vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata)));
            vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_0_cfg_r 
                = (1U & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata));
        }
        if (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_79) 
             & (~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_7_cfg_l)))) {
            vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_7_cfg_x 
                = (1U & (IData)((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata 
                                 >> 0x0000003aU)));
            vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_7_cfg_w 
                = (IData)((0x0300000000000000ULL == 
                           (0x0300000000000000ULL & vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata)));
            vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_7_cfg_r 
                = (1U & (IData)((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata 
                                 >> 0x00000038U)));
        }
        if (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_79) 
             & (~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_1_cfg_l)))) {
            vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_1_cfg_x 
                = (1U & (IData)((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata 
                                 >> 0x0000000aU)));
            vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_1_cfg_w 
                = (IData)((0x0000000000000300ULL == 
                           (0x0000000000000300ULL & vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata)));
            vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_1_cfg_r 
                = (1U & (IData)((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata 
                                 >> 8U)));
        }
        if (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_79) 
             & (~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_6_cfg_l)))) {
            vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_6_cfg_x 
                = (1U & (IData)((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata 
                                 >> 0x00000032U)));
            vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_6_cfg_w 
                = (IData)((0x0003000000000000ULL == 
                           (0x0003000000000000ULL & vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata)));
            vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_6_cfg_r 
                = (1U & (IData)((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata 
                                 >> 0x00000030U)));
        }
        if (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_79) 
             & (~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_5_cfg_l)))) {
            vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_5_cfg_x 
                = (1U & (IData)((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata 
                                 >> 0x0000002aU)));
            vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_5_cfg_w 
                = (IData)((0x0000030000000000ULL == 
                           (0x0000030000000000ULL & vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata)));
            vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_5_cfg_r 
                = (1U & (IData)((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata 
                                 >> 0x00000028U)));
        }
        if (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_79) 
             & (~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_4_cfg_l)))) {
            vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_4_cfg_x 
                = (1U & (IData)((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata 
                                 >> 0x00000022U)));
            vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_4_cfg_w 
                = (IData)((0x0000000300000000ULL == 
                           (0x0000000300000000ULL & vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata)));
            vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_4_cfg_r 
                = (1U & (IData)((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata 
                                 >> 0x00000020U)));
        }
        if (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_79) 
             & (~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_2_cfg_l)))) {
            vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_2_cfg_x 
                = (1U & (IData)((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata 
                                 >> 0x00000012U)));
            vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_2_cfg_w 
                = (IData)((0x0000000000030000ULL == 
                           (0x0000000000030000ULL & vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata)));
            vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_2_cfg_r 
                = (1U & (IData)((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata 
                                 >> 0x00000010U)));
        }
        if (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_79) 
             & (~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_3_cfg_l)))) {
            vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_3_cfg_x 
                = (1U & (IData)((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata 
                                 >> 0x0000001aU)));
            vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_3_cfg_w 
                = (IData)((0x0000000003000000ULL == 
                           (0x0000000003000000ULL & vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata)));
            vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_3_cfg_r 
                = (1U & (IData)((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata 
                                 >> 0x00000018U)));
        }
    } else {
        vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_address 
            = (0x00000001ffffffffULL & vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_address);
        vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mtval 
            = (0x00000003ffffffffULL & vlSelfRef.__VdfgRegularize_h6e95ff9d_0_64);
        vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mepc 
            = (0x00000003ffffffffULL & vlSelfRef.__VdfgRegularize_h6e95ff9d_0_65);
        vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_dpc 
            = (0x00000003ffffffffULL & vlSelfRef.__VdfgRegularize_h6e95ff9d_0_61);
    }
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_wfi 
        = ((1U & (~ (IData)(vlSelfRef.tb_Rocket__DOT__reset))) 
           && ((1U & (~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__exception))) 
               && ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_wfi) 
                   | ((4U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr_io_rw_cmd)) 
                      & ((vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
                          >> 0x0000001cU) & ((~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr_io_singleStep)) 
                                             & ((~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_debug)) 
                                                & (7U 
                                                   == 
                                                   (7U 
                                                    & (~ 
                                                       (vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
                                                        >> 0x0000001dU)))))))))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__nBufValid 
        = (1U & ((~ (IData)(vlSelfRef.tb_Rocket__DOT__reset)) 
                 & ((~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf_io_kill)) 
                    & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ctrl_stalld)
                        ? (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__nBufValid)
                        : (((~ (IData)(vlSelfRef.tb_Rocket__DOT__red_d)) 
                            & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT___io_imem_ready_T) 
                               & ((1U >= (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT___io_imem_ready_T_4)) 
                                  & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__nICReady) 
                                     < (3U & ((IData)(2U) 
                                              - (1U 
                                                 & (IData)(
                                                           (vlSelfRef.tb_Rocket__DOT__fpc 
                                                            >> 1U)))))))))
                            ? (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT___io_imem_ready_T_4)
                            : (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__nBufValid) 
                                - (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__nReady)) 
                               & (- (IData)((1U & (~ 
                                                   ((~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__nBufValid)) 
                                                    | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT___io_imem_ready_T))))))))))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__blocked = 0U;
    vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_replay 
        = (((~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf_io_kill)) 
            & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf_io_inst_0_valid)) 
           & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf_io_inst_0_bits_replay));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__imem_might_request_reg 
        = (1U & (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_pc_valid) 
                  | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_pc_valid)) 
                 | (IData)((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_custom_0 
                            >> 1U))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_xcpt_interrupt 
        = ((~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf_io_kill)) 
           & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_xcpt_interrupt));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_replay 
        = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_replay) 
           & (~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__take_pc_wb)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mstatus_mpie 
        = ((1U & (~ (IData)(vlSelfRef.tb_Rocket__DOT__reset))) 
           && (1U & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__csr_wen)
                      ? ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_1)
                          ? (IData)((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata 
                                     >> 7U)) : (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___GEN_276))
                      : (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___GEN_276))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mstatus_mie 
        = ((1U & (~ (IData)(vlSelfRef.tb_Rocket__DOT__reset))) 
           && (1U & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__csr_wen)
                      ? ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_1)
                          ? (IData)((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata 
                                     >> 3U)) : (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___GEN_275))
                      : (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___GEN_275))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__small_ 
        = (0x0000003fU & ((IData)(((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__csr_wen)
                                    ? ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_133)
                                        ? vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata
                                        : vlSelfRef.__VdfgRegularize_h6e95ff9d_0_62)
                                    : vlSelfRef.__VdfgRegularize_h6e95ff9d_0_62)) 
                          & (IData)((- (QData)((IData)(
                                                       (1U 
                                                        & (~ (IData)(vlSelfRef.tb_Rocket__DOT__reset)))))))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_valid 
        = (1U & (~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ctrl_killd)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_valid 
        = (1U & (~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ctrl_killm)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__resHi 
        = ((1U & (~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT___T_23))) 
           && ((3U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__state))
                ? ((0x40U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__count))
                    ? (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__isHi)
                    : (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT___GEN_13))
                : (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT___GEN_13)));
    if (vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT___T_23) {
        vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__req_tag 
            = (0x0000001fU & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_inst 
                              >> 7U));
        vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__req_dw 
            = vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_alu_dw;
        __Vdly__tb_Rocket__DOT__dut__DOT__div__DOT__count 
            = (0x20U & (- (IData)((1U & ((~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_alu_dw)) 
                                         & (~ ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_alu_fn) 
                                               >> 2U)))))));
        __Vdly__tb_Rocket__DOT__dut__DOT__div__DOT__neg_out 
            = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT___decoded_orMatrixOutputs_T_5)
                ? (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__lhs_sign)
                : ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__lhs_sign) 
                   != (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__rhs_sign)));
        __Vdly__tb_Rocket__DOT__dut__DOT__div__DOT__divisor[0U] 
            = (IData)((((QData)((IData)(((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_alu_dw)
                                          ? (IData)(
                                                    (vlSelfRef.tb_Rocket__DOT__dut__DOT__div_io_req_bits_in2 
                                                     >> 0x00000020U))
                                          : (- (IData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__rhs_sign)))))) 
                        << 0x00000020U) | (QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div_io_req_bits_in2))));
        __Vdly__tb_Rocket__DOT__dut__DOT__div__DOT__divisor[1U] 
            = (IData)(((((QData)((IData)(((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_alu_dw)
                                           ? (IData)(
                                                     (vlSelfRef.tb_Rocket__DOT__dut__DOT__div_io_req_bits_in2 
                                                      >> 0x00000020U))
                                           : (- (IData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__rhs_sign)))))) 
                         << 0x00000020U) | (QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div_io_req_bits_in2))) 
                       >> 0x00000020U));
        __Vdly__tb_Rocket__DOT__dut__DOT__div__DOT__divisor[2U] 
            = (1U & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__rhs_sign));
        __Vtemp_1[0U] = (IData)((((QData)((IData)(((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_alu_dw)
                                                    ? (IData)(
                                                              (vlSelfRef.tb_Rocket__DOT__dut__DOT__div_io_req_bits_in1 
                                                               >> 0x00000020U))
                                                    : 
                                                   (- (IData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__lhs_sign)))))) 
                                  << 0x00000020U) | (QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div_io_req_bits_in1))));
        __Vtemp_1[1U] = (IData)(((((QData)((IData)(
                                                   ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_alu_dw)
                                                     ? (IData)(
                                                               (vlSelfRef.tb_Rocket__DOT__dut__DOT__div_io_req_bits_in1 
                                                                >> 0x00000020U))
                                                     : 
                                                    (- (IData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__lhs_sign)))))) 
                                   << 0x00000020U) 
                                  | (QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div_io_req_bits_in1))) 
                                 >> 0x00000020U));
        __Vtemp_1[2U] = 0U;
        __Vtemp_1[3U] = 0U;
        __Vtemp_1[4U] = 0U;
        vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__isHi 
            = vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT___decoded_orMatrixOutputs_T_5;
    } else {
        if ((3U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__state))) {
            __Vdly__tb_Rocket__DOT__dut__DOT__div__DOT__count 
                = vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT___count_T_1;
            if ((((~ vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__subtractor[2U]) 
                  & (0U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__count))) 
                 & (~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__isHi)))) {
                __Vdly__tb_Rocket__DOT__dut__DOT__div__DOT__neg_out = 0U;
            }
            __Vtemp_1[0U] = (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__mplier) 
                              << 1U) | (1U & (~ vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__subtractor[2U])));
            __Vtemp_1[1U] = (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__mplier) 
                              >> 0x0000001fU) | ((IData)(
                                                         (vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__mplier 
                                                          >> 0x00000020U)) 
                                                 << 1U));
            __Vtemp_1[2U] = (((IData)(((1U & vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__subtractor[2U])
                                        ? (((QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[3U])) 
                                            << 0x00000020U) 
                                           | (QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[2U])))
                                        : (((QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__subtractor[1U])) 
                                            << 0x00000020U) 
                                           | (QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__subtractor[0U]))))) 
                              << 1U) | ((IData)((vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__mplier 
                                                 >> 0x00000020U)) 
                                        >> 0x0000001fU));
            __Vtemp_1[3U] = (((IData)(((1U & vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__subtractor[2U])
                                        ? (((QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[3U])) 
                                            << 0x00000020U) 
                                           | (QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[2U])))
                                        : (((QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__subtractor[1U])) 
                                            << 0x00000020U) 
                                           | (QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__subtractor[0U]))))) 
                              >> 0x0000001fU) | ((IData)(
                                                         (((1U 
                                                            & vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__subtractor[2U])
                                                            ? 
                                                           (((QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[3U])) 
                                                             << 0x00000020U) 
                                                            | (QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[2U])))
                                                            : 
                                                           (((QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__subtractor[1U])) 
                                                             << 0x00000020U) 
                                                            | (QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__subtractor[0U])))) 
                                                          >> 0x00000020U)) 
                                                 << 1U));
            __Vtemp_1[4U] = ((IData)((((1U & vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__subtractor[2U])
                                        ? (((QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[3U])) 
                                            << 0x00000020U) 
                                           | (QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[2U])))
                                        : (((QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__subtractor[1U])) 
                                            << 0x00000020U) 
                                           | (QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__subtractor[0U])))) 
                                      >> 0x00000020U)) 
                             >> 0x0000001fU);
        } else if ((2U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__state))) {
            __Vdly__tb_Rocket__DOT__dut__DOT__div__DOT__count 
                = vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT___count_T_1;
            __Vtemp_1[0U] = (IData)((((QData)((IData)(
                                                      (1U 
                                                       & vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__nextMulReg_hi[0U]))) 
                                      << 0x0000003fU) 
                                     | (0x7fffffffffffffffULL 
                                        & (((QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[1U])) 
                                            << 0x0000001fU) 
                                           | ((QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[0U])) 
                                              >> 1U)))));
            __Vtemp_1[1U] = (IData)(((((QData)((IData)(
                                                       (1U 
                                                        & vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__nextMulReg_hi[0U]))) 
                                       << 0x0000003fU) 
                                      | (0x7fffffffffffffffULL 
                                         & (((QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[1U])) 
                                             << 0x0000001fU) 
                                            | ((QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[0U])) 
                                               >> 1U)))) 
                                     >> 0x00000020U));
            __Vtemp_1[2U] = ((0xfffffffeU & vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__nextMulReg_hi[0U]) 
                             | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__neg_out) 
                                & (0x3eU == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__count))));
            __Vtemp_1[3U] = ((1U & vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__nextMulReg_hi[1U]) 
                             | (0xfffffffeU & vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__nextMulReg_hi[1U]));
            __Vtemp_1[4U] = ((1U & vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__nextMulReg_hi[2U]) 
                             | (2U & vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__nextMulReg_hi[2U]));
        } else if ((5U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__state))) {
            __Vtemp_1[0U] = (IData)((- vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__result));
            __Vtemp_1[1U] = (IData)(((- vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__result) 
                                     >> 0x00000020U));
            __Vtemp_1[2U] = 0U;
            __Vtemp_1[3U] = 0U;
            __Vtemp_1[4U] = 0U;
        } else if ((1U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__state))) {
            if ((vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[1U] 
                 >> 0x0000001fU)) {
                __Vtemp_1[0U] = (IData)((- vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__result));
                __Vtemp_1[1U] = (IData)(((- vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__result) 
                                         >> 0x00000020U));
                __Vtemp_1[2U] = 0U;
                __Vtemp_1[3U] = 0U;
                __Vtemp_1[4U] = 0U;
            } else {
                __Vtemp_1[0U] = vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[0U];
                __Vtemp_1[1U] = vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[1U];
                __Vtemp_1[2U] = vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[2U];
                __Vtemp_1[3U] = vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[3U];
                __Vtemp_1[4U] = vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[4U];
            }
        } else {
            __Vtemp_1[0U] = vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[0U];
            __Vtemp_1[1U] = vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[1U];
            __Vtemp_1[2U] = vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[2U];
            __Vtemp_1[3U] = vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[3U];
            __Vtemp_1[4U] = vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[4U];
        }
        if ((1U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__state))) {
            if ((vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__divisor[1U] 
                 >> 0x0000001fU)) {
                __Vdly__tb_Rocket__DOT__dut__DOT__div__DOT__divisor[0U] 
                    = vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__subtractor[0U];
                __Vdly__tb_Rocket__DOT__dut__DOT__div__DOT__divisor[1U] 
                    = vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__subtractor[1U];
                __Vdly__tb_Rocket__DOT__dut__DOT__div__DOT__divisor[2U] 
                    = vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__subtractor[2U];
            }
        }
    }
    vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[0U] 
        = __Vtemp_1[0U];
    vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[1U] 
        = __Vtemp_1[1U];
    vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[2U] 
        = __Vtemp_1[2U];
    vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[3U] 
        = __Vtemp_1[3U];
    vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[4U] 
        = __Vtemp_1[4U];
    vlSelfRef.tb_Rocket__DOT__d_s1_r = vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_rs2;
    if ((1U & (~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ctrl_stalld)))) {
        if (((((~ (IData)(vlSelfRef.tb_Rocket__DOT__red_d)) 
               & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT___io_imem_ready_T)) 
              & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__nICReady) 
                 < (3U & ((IData)(2U) - (1U & (IData)(
                                                      (vlSelfRef.tb_Rocket__DOT__fpc 
                                                       >> 1U))))))) 
             & (1U >= (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT___io_imem_ready_T_4)))) {
            vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__buf___05Fxcpt_ae_inst = 0U;
            vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__buf___05Fpc 
                = ((0x00000003fffffffcULL & vlSelfRef.tb_Rocket__DOT__fpc) 
                   | (3ULL & (vlSelfRef.tb_Rocket__DOT__fpc 
                              + (QData)((IData)(((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__nICReady) 
                                                 << 1U))))));
            vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__buf___05Freplay = 0U;
            vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__buf___05Fdata 
                = (0x0000ffffU & (IData)((vlSelfRef.__VdfgRegularize_h6e95ff9d_0_52 
                                          >> (0x00000030U 
                                              & (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__nICReady) 
                                                  + 
                                                  (1U 
                                                   & (IData)(
                                                             (vlSelfRef.tb_Rocket__DOT__fpc 
                                                              >> 1U)))) 
                                                 << 4U)))));
        }
    }
    if (__VdlySet__tb_Rocket__DOT__dut__DOT__rf__v0) {
        vlSelfRef.tb_Rocket__DOT__dut__DOT__rf[__VdlyDim0__tb_Rocket__DOT__dut__DOT__rf__v0] 
            = __VdlyVal__tb_Rocket__DOT__dut__DOT__rf__v0;
    }
    if (__VdlySet__tb_Rocket__DOT__dmem8__v0) {
        vlSelfRef.tb_Rocket__DOT__dmem8[__VdlyDim0__tb_Rocket__DOT__dmem8__v0] 
            = __VdlyVal__tb_Rocket__DOT__dmem8__v0;
    }
    vlSelfRef.tb_Rocket__DOT__dut__DOT__id_reg_fence 
        = __Vdly__tb_Rocket__DOT__dut__DOT__id_reg_fence;
    vlSelfRef.tb_Rocket__DOT__dut__DOT__id_reg_pause 
        = __Vdly__tb_Rocket__DOT__dut__DOT__id_reg_pause;
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mcountinhibit 
        = __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mcountinhibit;
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_misa 
        = __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_misa;
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_custom_0 
        = __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_custom_0;
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_0_cfg_l 
        = __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_0_cfg_l;
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_7_cfg_l 
        = __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_7_cfg_l;
    vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__neg_out 
        = __Vdly__tb_Rocket__DOT__dut__DOT__div__DOT__neg_out;
    vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__divisor[0U] 
        = __Vdly__tb_Rocket__DOT__dut__DOT__div__DOT__divisor[0U];
    vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__divisor[1U] 
        = __Vdly__tb_Rocket__DOT__dut__DOT__div__DOT__divisor[1U];
    vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__divisor[2U] 
        = __Vdly__tb_Rocket__DOT__dut__DOT__div__DOT__divisor[2U];
    vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__count 
        = __Vdly__tb_Rocket__DOT__dut__DOT__div__DOT__count;
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_singleStepped 
        = __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_singleStepped;
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_control_dmode 
        = __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_control_dmode;
    vlSelfRef.tb_Rocket__DOT__fpc = __Vdly__tb_Rocket__DOT__fpc;
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___read_mtvec_T_5 
        = (vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mtvec 
           & ((1U & vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mtvec)
               ? 0xffffff01U : 0xfffffffdU));
    vlSelfRef.tb_Rocket__DOT__q2_v = ((1U & (~ (IData)(vlSelfRef.tb_Rocket__DOT__reset))) 
                                      && (IData)(vlSelfRef.tb_Rocket__DOT__q1_v));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__small_1 
        = (0x0000003fU & ((IData)(((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__csr_wen)
                                    ? ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_131)
                                        ? vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata
                                        : vlSelfRef.__VdfgRegularize_h6e95ff9d_0_63)
                                    : vlSelfRef.__VdfgRegularize_h6e95ff9d_0_63)) 
                          & (IData)((- (QData)((IData)(
                                                       (1U 
                                                        & (~ (IData)(vlSelfRef.tb_Rocket__DOT__reset)))))))));
    tb_Rocket__DOT__dut__DOT__csr_io_csr_stall = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_wfi) 
                                                  | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__io_status_cease_r));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_xcpt 
        = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_xcpt) 
           & (~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__take_pc_wb)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_replay 
        = ((~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf_io_kill)) 
           & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__replay_ex));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___T_30 
        = (0x00000003ffffffffULL & (~ ((~ vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mepc) 
                                       | (QData)((IData)(
                                                         (3U 
                                                          & (1U 
                                                             | (- (IData)(
                                                                          (1U 
                                                                           & (~ (IData)(
                                                                                (vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_misa 
                                                                                >> 2U)))))))))))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___T_44 
        = (0x00000003ffffffffULL & (~ ((~ vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_dpc) 
                                       | (QData)((IData)(
                                                         (3U 
                                                          & (1U 
                                                             | (- (IData)(
                                                                          (1U 
                                                                           & (~ (IData)(
                                                                                (vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_misa 
                                                                                >> 2U)))))))))))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__pmp_mask_base 
        = ((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_0_addr 
            << 1U) | (1U & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_0_cfg_a)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__pmp_mask_base_7 
        = ((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_7_addr 
            << 1U) | (1U & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_7_cfg_a)));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_39 = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_7_cfg_l) 
                                                 & (1U 
                                                    == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_7_cfg_a)));
    if ((1U & (~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ctrl_killd)))) {
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_rs_bypass_1 
            = vlSelfRef.tb_Rocket__DOT__dut__DOT__do_bypass_1;
        if (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_orMatrixOutputs_T_48) 
             & (~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__do_bypass_1)))) {
            vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_rs_msb_1 
                = (vlSelfRef.tb_Rocket__DOT__dut__DOT__id_rs_1 
                   >> 2U);
            vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_rs_lsb_1 
                = (3U & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__id_rs_1));
        } else {
            vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_rs_lsb_1 
                = (3U & ((0U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs2))
                          ? 0U : ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__id_bypass_src_1_1)
                                   ? 1U : (2U | (- (IData)(
                                                           (1U 
                                                            & (~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__id_bypass_src_1_2)))))))));
        }
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_rs_bypass_0 
            = ((1U & (~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__id_illegal_insn))) 
               && (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__do_bypass));
        if (vlSelfRef.tb_Rocket__DOT__dut__DOT__id_illegal_insn) {
            vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_rs_msb_0 
                = (QData)((IData)((vlSelfRef.tb_Rocket__DOT__dut__DOT__inst 
                                   >> 2U)));
            vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_rs_lsb_0 
                = (3U & vlSelfRef.tb_Rocket__DOT__dut__DOT__inst);
        } else if (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_orMatrixOutputs_T_38) 
                    & (~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__do_bypass)))) {
            vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_rs_msb_0 
                = (vlSelfRef.tb_Rocket__DOT__dut__DOT__id_rs_0 
                   >> 2U);
            vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_rs_lsb_0 
                = (3U & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__id_rs_0));
        } else {
            vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_rs_lsb_0 
                = (3U & ((0U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs1))
                          ? 0U : ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__id_bypass_src_0_1)
                                   ? 1U : (2U | (- (IData)(
                                                           (1U 
                                                            & (~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__id_bypass_src_0_2)))))))));
        }
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_sel_imm 
            = ((((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_119) 
                 | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_109) 
                    | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_95) 
                       | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_89) 
                          | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_65) 
                             | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_55) 
                                | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_51) 
                                   | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_39) 
                                      | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_13) 
                                         | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_9) 
                                            | (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_8))))))))))) 
                << 2U) | ((((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_41) 
                            | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_15)) 
                           << 1U) | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_115) 
                                     | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_105) 
                                        | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_41) 
                                           | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_33))))));
    }
    __VdfgRegularize_h6e95ff9d_0_35 = (1U & (~ ((5U 
                                                 == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_sel_imm)) 
                                                | (2U 
                                                   == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_sel_imm)))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT___count_T_1 
        = (0x0000007fU & ((IData)(1U) + (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__count)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__mplier 
        = (((QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[1U])) 
            << 0x00000020U) | (QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[0U])));
    __Vtemp_9[0U] = vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[2U];
    __Vtemp_9[1U] = vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[3U];
    __Vtemp_9[2U] = vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[4U];
    VL_SUB_W(3, __Vtemp_10, __Vtemp_9, vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__divisor);
    vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__subtractor[0U] 
        = __Vtemp_10[0U];
    vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__subtractor[1U] 
        = __Vtemp_10[1U];
    vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__subtractor[2U] 
        = (1U & __Vtemp_10[2U]);
    VL_EXTENDS_WI(67,2, __Vtemp_13, ((2U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[2U] 
                                            << 1U)) 
                                     | (1U & vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[0U])));
    __Vtemp_14[0U] = __Vtemp_13[0U];
    __Vtemp_14[1U] = __Vtemp_13[1U];
    __Vtemp_14[2U] = (7U & __Vtemp_13[2U]);
    VL_EXTENDS_WW(67,65, __Vtemp_16, vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__divisor);
    __Vtemp_17[0U] = __Vtemp_16[0U];
    __Vtemp_17[1U] = __Vtemp_16[1U];
    __Vtemp_17[2U] = (7U & __Vtemp_16[2U]);
    VL_MULS_WWW(67, __Vtemp_18, __Vtemp_14, __Vtemp_17);
    __Vtemp_22[0U] = ((vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[3U] 
                       << 0x0000001fU) | (vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[2U] 
                                          >> 1U));
    __Vtemp_22[1U] = ((vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[4U] 
                       << 0x0000001fU) | (vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[3U] 
                                          >> 1U));
    __Vtemp_22[2U] = ((6U & ((- (IData)((1U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[4U] 
                                               >> 1U)))) 
                             << 1U)) | (1U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[4U] 
                                              >> 1U)));
    VL_ADD_W(3, __Vtemp_23, __Vtemp_18, __Vtemp_22);
    vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__nextMulReg_hi[0U] 
        = __Vtemp_23[0U];
    vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__nextMulReg_hi[1U] 
        = __Vtemp_23[1U];
    vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__nextMulReg_hi[2U] 
        = (7U & __Vtemp_23[2U]);
    vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__result 
        = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__resHi)
            ? (((QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[4U])) 
                << 0x0000003fU) | (((QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[3U])) 
                                    << 0x0000001fU) 
                                   | ((QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[2U])) 
                                      >> 1U))) : (((QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[1U])) 
                                                   << 0x00000020U) 
                                                  | (QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[0U]))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__div_io_kill_REG 
        = ((0U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__state)) 
           & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div_io_req_valid));
    if (vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_pc_valid) {
        vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_ctrl_fence_i 
            = vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_ctrl_fence_i;
        vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_ctrl_div 
            = vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_ctrl_div;
        vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_ctrl_mem 
            = vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_ctrl_mem;
        vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_cause 
            = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___T_70)
                ? vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_cause
                : (QData)((IData)((((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_debug_breakpoint)
                                     ? 0x0eU : 3U) 
                                   & (- (IData)((1U 
                                                 & (~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___T_71)))))))));
        vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_ctrl_rocc 
            = vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_ctrl_rocc;
    }
    vlSelfRef.tb_Rocket__DOT__dut__DOT__replay_wb_rocc 
        = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_valid) 
           & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_ctrl_rocc));
    if (vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_pc_valid) {
        vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_ctrl_csr 
            = vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_ctrl_csr;
    }
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr_io_rw_cmd 
        = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_ctrl_csr) 
           & (3U | (- (IData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_valid)))));
    tb_Rocket__DOT__dut__DOT__csr__DOT___T_20 = (0x0080000000000000ULL 
                                                 | (((QData)((IData)(
                                                                     (4U 
                                                                      | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_control_dmode)))) 
                                                     << 0x0000003bU) 
                                                    | (QData)((IData)(
                                                                      (0x00000040U 
                                                                       | ((((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_control_action) 
                                                                            << 0x0000000cU) 
                                                                           | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_control_tmatch) 
                                                                              << 7U)) 
                                                                          | (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_control_x) 
                                                                              << 2U) 
                                                                             | (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_control_w) 
                                                                                << 1U) 
                                                                                | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_control_r)))))))));
    tb_Rocket__DOT__dut__DOT__bpu__DOT___r_T_8 = (1U 
                                                  & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_control_tmatch) 
                                                     & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_address)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_debug 
        = ((1U & (~ (IData)(vlSelfRef.tb_Rocket__DOT__reset))) 
           && ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__insn_ret)
                ? ((1U & (~ (IData)((0x48000000U == 
                                     (0x48000000U & vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst))))) 
                   && (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___GEN_184))
                : (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___GEN_184)));
    if (vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_pc_valid) {
        vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_ctrl_wxd 
            = vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_ctrl_wxd;
        vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_wdata 
            = ((((~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_xcpt)) 
                 & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_ctrl_fp)) 
                & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_ctrl_wxd))
                ? 0ULL : (((~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_xcpt)) 
                           & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_ctrl_jalr) 
                              ^ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_npc_misaligned)))
                           ? (((QData)((IData)((0x3fffffffU 
                                                & (- (IData)(
                                                             (1U 
                                                              & (IData)(
                                                                        (vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_br_target 
                                                                         >> 0x00000021U)))))))) 
                               << 0x00000022U) | vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_br_target)
                           : vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_wdata));
        vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_pc 
            = vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_pc;
        vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
            = vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_inst;
    }
    vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__buf_replay 
        = (3U & ((((IData)(1U) << (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__nBufValid)) 
                  - (IData)(1U)) & (- (IData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__buf___05Freplay)))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_xcpt 
        = ((~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ctrl_killx)) 
           & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_xcpt_interrupt) 
              | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_xcpt)));
    __VdfgRegularize_h6e95ff9d_0_11 = (vlSelfRef.tb_Rocket__DOT__imem
                                       [(0x000000ffU 
                                         & (IData)(
                                                   (vlSelfRef.tb_Rocket__DOT__fpc 
                                                    >> 2U)))] 
                                       >> 0x00000010U);
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_1_cfg_l 
        = __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_1_cfg_l;
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_6_cfg_l 
        = __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_6_cfg_l;
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_5_cfg_l 
        = __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_5_cfg_l;
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_4_cfg_l 
        = __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_4_cfg_l;
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_2_cfg_l 
        = __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_2_cfg_l;
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_3_cfg_l 
        = __Vdly__tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_3_cfg_l;
    vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__state 
        = __Vdly__tb_Rocket__DOT__dut__DOT__div__DOT__state;
    vlSelfRef.tb_Rocket__DOT__dut__DOT__replay_wb = 
        ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_replay) 
         | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__replay_wb_rocc));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__csr_wen 
        = ((6U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr_io_rw_cmd)) 
           | ((5U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr_io_rw_cmd)) 
              | (7U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr_io_rw_cmd))));
    tb_Rocket__DOT__dut__DOT__csr__DOT___wdata_T_6 
        = ((~ vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_wdata) 
           | (- (QData)((IData)((1U & (~ (3U == (3U 
                                                 & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr_io_rw_cmd)))))))));
    tb_Rocket__DOT__dut__DOT__bpu__DOT___GEN_11 = (QData)((IData)(
                                                                  ((((IData)(
                                                                             ((6ULL 
                                                                               == 
                                                                               (6ULL 
                                                                                & vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_address)) 
                                                                              & (IData)(tb_Rocket__DOT__dut__DOT__bpu__DOT___r_T_8))) 
                                                                     << 3U) 
                                                                    | (((IData)(
                                                                                (vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_address 
                                                                                >> 1U)) 
                                                                        & (IData)(tb_Rocket__DOT__dut__DOT__bpu__DOT___r_T_8)) 
                                                                       << 2U)) 
                                                                   | (((IData)(tb_Rocket__DOT__dut__DOT__bpu__DOT___r_T_8) 
                                                                       << 1U) 
                                                                      | (1U 
                                                                         & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_control_tmatch))))));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_52 = (((QData)((IData)(
                                                                  (((IData)(__VdfgRegularize_h6e95ff9d_0_11) 
                                                                    << 0x00000010U) 
                                                                   | (IData)(__VdfgRegularize_h6e95ff9d_0_11)))) 
                                                  << 0x00000020U) 
                                                 | (QData)((IData)(vlSelfRef.tb_Rocket__DOT__imem
                                                                   [
                                                                   (0x000000ffU 
                                                                    & (IData)(
                                                                              (vlSelfRef.tb_Rocket__DOT__fpc 
                                                                               >> 2U)))])));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__pmp_mask_base_1 
        = ((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_1_addr 
            << 1U) | (1U & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_1_cfg_a)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__pmp_mask_base_6 
        = ((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_6_addr 
            << 1U) | (1U & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_6_cfg_a)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__pmp_mask_base_5 
        = ((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_5_addr 
            << 1U) | (1U & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_5_cfg_a)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__pmp_mask_base_4 
        = ((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_4_addr 
            << 1U) | (1U & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_4_cfg_a)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__pmp_mask_base_2 
        = ((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_2_addr 
            << 1U) | (1U & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_2_cfg_a)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__pmp_mask_base_3 
        = ((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_3_addr 
            << 1U) | (1U & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_3_cfg_a)));
    tb_Rocket__DOT__dut__DOT__wb_dcache_miss = ((~ (IData)(vlSelfRef.tb_Rocket__DOT__q2_v)) 
                                                & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_ctrl_mem));
    vlSelfRef.tb_Rocket__DOT__q1_v = ((1U & (~ (IData)(vlSelfRef.tb_Rocket__DOT__reset))) 
                                      && (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__id_mem_busy));
    vlSelfRef.tb_Rocket__DOT__wbe = (0x000000ffU & 
                                     ((2U & (IData)(vlSelfRef.tb_Rocket__DOT__q2_size))
                                       ? ((1U & (IData)(vlSelfRef.tb_Rocket__DOT__q2_size))
                                           ? 0xffU : 
                                          ((1U & (IData)(
                                                         (vlSelfRef.tb_Rocket__DOT__q2_addr 
                                                          >> 2U)))
                                            ? 0xf0U
                                            : 0x0fU))
                                       : ((1U & (IData)(vlSelfRef.tb_Rocket__DOT__q2_size))
                                           ? ((IData)(3U) 
                                              << (6U 
                                                  & ((IData)(
                                                             (vlSelfRef.tb_Rocket__DOT__q2_addr 
                                                              >> 1U)) 
                                                     << 1U)))
                                           : ((IData)(1U) 
                                              << (7U 
                                                  & (IData)(vlSelfRef.tb_Rocket__DOT__q2_addr))))));
    vlSelfRef.tb_Rocket__DOT__wdata_shift = 0ULL;
    if ((1U & (IData)(vlSelfRef.tb_Rocket__DOT__wbe))) {
        vlSelfRef.tb_Rocket__DOT__wdata_shift = ((0xffffffffffffff00ULL 
                                                  & vlSelfRef.tb_Rocket__DOT__wdata_shift) 
                                                 | (IData)((IData)(
                                                                   (0x000000ffU 
                                                                    & (IData)(vlSelfRef.tb_Rocket__DOT__d_s1_r)))));
    }
    if ((2U & (IData)(vlSelfRef.tb_Rocket__DOT__wbe))) {
        vlSelfRef.tb_Rocket__DOT__wdata_shift = ((0xffffffffffff00ffULL 
                                                  & vlSelfRef.tb_Rocket__DOT__wdata_shift) 
                                                 | ((QData)((IData)(
                                                                    (0x000000ffU 
                                                                     & (IData)(
                                                                               (vlSelfRef.tb_Rocket__DOT__d_s1_r 
                                                                                >> 8U))))) 
                                                    << 8U));
    }
    if ((4U & (IData)(vlSelfRef.tb_Rocket__DOT__wbe))) {
        vlSelfRef.tb_Rocket__DOT__wdata_shift = ((0xffffffffff00ffffULL 
                                                  & vlSelfRef.tb_Rocket__DOT__wdata_shift) 
                                                 | ((QData)((IData)(
                                                                    (0x000000ffU 
                                                                     & (IData)(
                                                                               (vlSelfRef.tb_Rocket__DOT__d_s1_r 
                                                                                >> 0x10U))))) 
                                                    << 0x00000010U));
    }
    if ((8U & (IData)(vlSelfRef.tb_Rocket__DOT__wbe))) {
        vlSelfRef.tb_Rocket__DOT__wdata_shift = ((0xffffffff00ffffffULL 
                                                  & vlSelfRef.tb_Rocket__DOT__wdata_shift) 
                                                 | ((QData)((IData)(
                                                                    (0x000000ffU 
                                                                     & (IData)(
                                                                               (vlSelfRef.tb_Rocket__DOT__d_s1_r 
                                                                                >> 0x18U))))) 
                                                    << 0x00000018U));
    }
    if ((0x00000010U & (IData)(vlSelfRef.tb_Rocket__DOT__wbe))) {
        vlSelfRef.tb_Rocket__DOT__wdata_shift = ((0xffffff00ffffffffULL 
                                                  & vlSelfRef.tb_Rocket__DOT__wdata_shift) 
                                                 | ((QData)((IData)(
                                                                    (0x000000ffU 
                                                                     & (IData)(
                                                                               (vlSelfRef.tb_Rocket__DOT__d_s1_r 
                                                                                >> 0x20U))))) 
                                                    << 0x00000020U));
    }
    if ((0x00000020U & (IData)(vlSelfRef.tb_Rocket__DOT__wbe))) {
        vlSelfRef.tb_Rocket__DOT__wdata_shift = ((0xffff00ffffffffffULL 
                                                  & vlSelfRef.tb_Rocket__DOT__wdata_shift) 
                                                 | ((QData)((IData)(
                                                                    (0x000000ffU 
                                                                     & (IData)(
                                                                               (vlSelfRef.tb_Rocket__DOT__d_s1_r 
                                                                                >> 0x28U))))) 
                                                    << 0x00000028U));
    }
    if ((0x00000040U & (IData)(vlSelfRef.tb_Rocket__DOT__wbe))) {
        vlSelfRef.tb_Rocket__DOT__wdata_shift = ((0xff00ffffffffffffULL 
                                                  & vlSelfRef.tb_Rocket__DOT__wdata_shift) 
                                                 | ((QData)((IData)(
                                                                    (0x000000ffU 
                                                                     & (IData)(
                                                                               (vlSelfRef.tb_Rocket__DOT__d_s1_r 
                                                                                >> 0x30U))))) 
                                                    << 0x00000030U));
    }
    if ((0x00000080U & (IData)(vlSelfRef.tb_Rocket__DOT__wbe))) {
        vlSelfRef.tb_Rocket__DOT__wdata_shift = ((0x00ffffffffffffffULL 
                                                  & vlSelfRef.tb_Rocket__DOT__wdata_shift) 
                                                 | ((QData)((IData)(
                                                                    (0x000000ffU 
                                                                     & (IData)(
                                                                               (vlSelfRef.tb_Rocket__DOT__d_s1_r 
                                                                                >> 0x38U))))) 
                                                    << 0x00000038U));
    }
    tb_Rocket__DOT__q_half = (0x0000ffffU & (IData)(
                                                    (vlSelfRef.tb_Rocket__DOT__dmem8
                                                     [
                                                     (0x000000ffU 
                                                      & (IData)(
                                                                (vlSelfRef.tb_Rocket__DOT__q2_addr 
                                                                 >> 3U)))] 
                                                     >> 
                                                     (0x00000030U 
                                                      & ((IData)(
                                                                 (vlSelfRef.tb_Rocket__DOT__q2_addr 
                                                                  >> 1U)) 
                                                         << 4U)))));
    tb_Rocket__DOT__q_byte = (0x000000ffU & (IData)(
                                                    (vlSelfRef.tb_Rocket__DOT__dmem8
                                                     [
                                                     (0x000000ffU 
                                                      & (IData)(
                                                                (vlSelfRef.tb_Rocket__DOT__q2_addr 
                                                                 >> 3U)))] 
                                                     >> 
                                                     (0x00000038U 
                                                      & ((IData)(vlSelfRef.tb_Rocket__DOT__q2_addr) 
                                                         << 3U)))));
    tb_Rocket__DOT__dut__DOT__csr__DOT__nextSmall_1 
        = (0x0000007fU & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__small_1) 
                          + (1U & (~ (IData)(tb_Rocket__DOT__dut__DOT__csr_io_csr_stall)))));
    tb_Rocket__DOT__dut__DOT__div__DOT___GEN_6 = (7U 
                                                  & (((1U 
                                                       == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__state))
                                                       ? 3U
                                                       : (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__state)) 
                                                     | (- (IData)(
                                                                  (5U 
                                                                   == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__state))))));
    tb_Rocket__DOT__dut__DOT__div__DOT___GEN_7 = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__resHi) 
                                                  & (5U 
                                                     != (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__state)));
    tb_Rocket__DOT__dut__DOT__div__DOT__loOut = (((~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__req_dw)) 
                                                  & (0U 
                                                     == 
                                                     (1U 
                                                      & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__state))))
                                                  ? (IData)(
                                                            (vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__result 
                                                             >> 0x00000020U))
                                                  : (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__result));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT___T_21 
        = ((~ ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_valid) 
               & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_ctrl_wxd))) 
           & ((6U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__state)) 
              | (7U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__state))));
    __VdfgRegularize_h6e95ff9d_0_81 = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_xcpt) 
                                       | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__replay_wb));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___newBPC_T_8 
        = ((vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_wdata 
            | (tb_Rocket__DOT__dut__DOT__csr__DOT___T_20 
               & (- (QData)((IData)((1U & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr_io_rw_cmd) 
                                           >> 1U))))))) 
           & tb_Rocket__DOT__dut__DOT__csr__DOT___wdata_T_6);
    tb_Rocket__DOT__dut__DOT__bpu__DOT___r_T_24 = (0x00000001ffffffffULL 
                                                   & ((~ vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_address) 
                                                      | tb_Rocket__DOT__dut__DOT__bpu__DOT___GEN_11));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr_io_singleStep 
        = ((~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_debug)) 
           & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_dcsr_step));
    vlSelfRef.tb_Rocket__DOT__dut__DOT___T_70 = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_xcpt) 
                                                 | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_xcpt_interrupt));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_xcpt 
        = ((~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ctrl_killd)) 
           & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__id_xcpt));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_xcpt_interrupt 
        = (((~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf_io_kill)) 
            & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf_io_inst_0_valid)) 
           & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr_io_interrupt));
    tb_Rocket__DOT__dut__DOT__wb_set_sboard = ((IData)(tb_Rocket__DOT__dut__DOT__wb_dcache_miss) 
                                               | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_ctrl_rocc) 
                                                  | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_ctrl_div)));
    vlSelfRef.tb_Rocket__DOT__i_dresp_data = (((2U 
                                                & (IData)(vlSelfRef.tb_Rocket__DOT__q2_size))
                                                ? (
                                                   (1U 
                                                    & (IData)(vlSelfRef.tb_Rocket__DOT__q2_size))
                                                    ? vlSelfRef.tb_Rocket__DOT__dmem8
                                                   [
                                                   (0x000000ffU 
                                                    & (IData)(
                                                              (vlSelfRef.tb_Rocket__DOT__q2_addr 
                                                               >> 3U)))]
                                                    : (QData)((IData)(
                                                                      ((1U 
                                                                        & (IData)(
                                                                                (vlSelfRef.tb_Rocket__DOT__q2_addr 
                                                                                >> 2U)))
                                                                        ? (IData)(
                                                                                (vlSelfRef.tb_Rocket__DOT__dmem8
                                                                                [
                                                                                (0x000000ffU 
                                                                                & (IData)(
                                                                                (vlSelfRef.tb_Rocket__DOT__q2_addr 
                                                                                >> 3U)))] 
                                                                                >> 0x00000020U))
                                                                        : (IData)(vlSelfRef.tb_Rocket__DOT__dmem8
                                                                                [
                                                                                (0x000000ffU 
                                                                                & (IData)(
                                                                                (vlSelfRef.tb_Rocket__DOT__q2_addr 
                                                                                >> 3U)))])))))
                                                : (
                                                   (1U 
                                                    & (IData)(vlSelfRef.tb_Rocket__DOT__q2_size))
                                                    ? 
                                                   ((((- (QData)((IData)(
                                                                         (1U 
                                                                          & ((IData)(tb_Rocket__DOT__q_half) 
                                                                             >> 0x0000000fU))))) 
                                                      & (- (QData)((IData)(vlSelfRef.tb_Rocket__DOT__q2_signed)))) 
                                                     << 0x00000010U) 
                                                    | (QData)((IData)(tb_Rocket__DOT__q_half)))
                                                    : 
                                                   ((((- (QData)((IData)(
                                                                         (1U 
                                                                          & ((IData)(tb_Rocket__DOT__q_byte) 
                                                                             >> 7U))))) 
                                                      & (- (QData)((IData)(vlSelfRef.tb_Rocket__DOT__q2_signed)))) 
                                                     << 8U) 
                                                    | (QData)((IData)(tb_Rocket__DOT__q_byte))))) 
                                              & (- (QData)((IData)(vlSelfRef.tb_Rocket__DOT__q2_is_load))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___GEN_3 
        = (0x03ffffffffffffffULL & (vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__large_1 
                                    + (QData)((IData)(
                                                      ((~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mcountinhibit)) 
                                                       & ((IData)(tb_Rocket__DOT__dut__DOT__csr__DOT__nextSmall_1) 
                                                          >> 6U))))));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_63 = (QData)((IData)(
                                                                ((1U 
                                                                  & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mcountinhibit))
                                                                  ? (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__small_1)
                                                                  : (IData)(tb_Rocket__DOT__dut__DOT__csr__DOT__nextSmall_1))));
    if ((2U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__state))) {
        if ((0x3fU == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__count))) {
            vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT___GEN_12 = 6U;
            vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT___GEN_13 
                = vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__isHi;
        } else {
            vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT___GEN_12 
                = tb_Rocket__DOT__dut__DOT__div__DOT___GEN_6;
            vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT___GEN_13 
                = tb_Rocket__DOT__dut__DOT__div__DOT___GEN_7;
        }
    } else {
        vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT___GEN_12 
            = tb_Rocket__DOT__dut__DOT__div__DOT___GEN_6;
        vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT___GEN_13 
            = tb_Rocket__DOT__dut__DOT__div__DOT___GEN_7;
    }
    vlSelfRef.tb_Rocket__DOT__dut__DOT___T_143 = (0xfffffffeU 
                                                  & (vlSelfRef.tb_Rocket__DOT__dut__DOT___r 
                                                     & ((~ 
                                                         ((IData)(1U) 
                                                          << (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__req_tag))) 
                                                        | (- (IData)(
                                                                     (1U 
                                                                      & (~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT___T_21))))))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr_io_retire 
        = ((~ (IData)(__VdfgRegularize_h6e95ff9d_0_81)) 
           & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_valid));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__dMode 
        = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_debug) 
           & (IData)((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___newBPC_T_8 
                      >> 0x0000003bU)));
    tb_Rocket__DOT__dut__DOT__csr__DOT__nextSmall = 
        (0x0000007fU & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__small_) 
                        + (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr_io_retire)));
    tb_Rocket__DOT__dut__DOT__wb_wen = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_ctrl_wxd) 
                                        & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr_io_retire));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_25 = (IData)(
                                                        (0x48000000U 
                                                         == 
                                                         (0x48000000U 
                                                          & vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__rf_waddr = 
        (0x0000001fU & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT___T_21)
                         ? (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__req_tag)
                         : (vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
                            >> 7U)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__insn_ret 
        = ((4U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr_io_rw_cmd)) 
           & ((IData)((0x40000000U == (0xc0000000U 
                                       & vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst))) 
              | (IData)(((0x30000000U == (0x30000000U 
                                          & vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst)) 
                         & ((3U == (3U & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
                                             >> 0x0000001eU)))) 
                            & (0x0000003fU == (0x0000003fU 
                                               & (~ 
                                                  (vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
                                                   >> 0x00000016U)))))))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_1 
        = (IData)(((0x30000000U == (0x30000000U & vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst)) 
                   & ((3U == (3U & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
                                       >> 0x0000001eU)))) 
                      & (0x000000ffU == (0x000000ffU 
                                         & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
                                               >> 0x00000014U)))))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_131 
        = (IData)(((0xb0000000U == (0xf0000000U & vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst)) 
                   & (0x0000007fU == (0x0000007fU & 
                                      (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
                                          >> 0x00000015U))))));
    __VdfgRegularize_h6e95ff9d_0_66 = (IData)((0x00100000U 
                                               == (0x00300000U 
                                                   & vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst)));
    tb_Rocket__DOT__dut__DOT__csr__DOT__insn_call = 
        ((4U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr_io_rw_cmd)) 
         & (0x00000fffU == (0x00000fffU & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
                                              >> 0x00000014U)))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__insn_break 
        = ((4U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr_io_rw_cmd)) 
           & ((0x000007ffU == (0x000007ffU & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
                                                 >> 0x00000015U)))) 
              & (vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
                 >> 0x00000014U)));
    __VdfgRegularize_h6e95ff9d_0_26 = (IData)((0x60000000U 
                                               == (0xe0000000U 
                                                   & vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst)));
    __VdfgRegularize_h6e95ff9d_0_27 = (IData)((0x02000000U 
                                               == (0x06000000U 
                                                   & vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst)));
    __VdfgRegularize_h6e95ff9d_0_9 = (IData)((0x00200000U 
                                              == (0x00300000U 
                                                  & vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst)));
    __VdfgRegularize_h6e95ff9d_0_85 = (3U & ((vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
                                              >> 0x0000001cU) 
                                             & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
                                                   >> 0x0000001eU))));
    __VdfgRegularize_h6e95ff9d_0_5 = (IData)((0x1b000000U 
                                              == (0x1b000000U 
                                                  & vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst)));
    if ((1U & (~ ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_valid) 
                  & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_flush_pipe))))) {
        if (vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_pc_valid) {
            vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_ctrl_fp 
                = vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_fp;
            vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_ctrl_rocc 
                = vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_rocc;
            vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_ctrl_branch 
                = vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_branch;
            vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_ctrl_jal 
                = vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_jal;
            vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_ctrl_jalr 
                = vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_jalr;
        }
    }
    if ((1U & (~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ctrl_killd)))) {
        if (vlSelfRef.tb_Rocket__DOT__dut__DOT__id_xcpt) {
            if (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__bpu_io_xcpt_if) 
                 | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf_io_inst_0_bits_xcpt0_ae_inst))) {
                vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_sel_alu2 = 0U;
                vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_sel_alu1 = 2U;
            } else if ((0U != (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT___io_inst_0_bits_xcpt1_T_5))) {
                vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_sel_alu2 = 1U;
                vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_sel_alu1 = 2U;
            } else {
                vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_sel_alu2 = 0U;
                vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_sel_alu1 = 1U;
            }
        } else {
            vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_sel_alu2 
                = ((((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_1) 
                     | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_5) 
                        | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_7) 
                           | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_13) 
                              | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_15) 
                                 | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_23) 
                                    | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_27) 
                                       | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_29) 
                                          | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_33) 
                                             | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_37) 
                                                | ((0U 
                                                    != (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_15)) 
                                                   | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_65) 
                                                      | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_89) 
                                                         | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_93) 
                                                            | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_99) 
                                                               | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_105) 
                                                                  | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_115) 
                                                                     | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_131)))))))))))))))))) 
                    << 1U) | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_119) 
                              | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_109) 
                                 | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_95) 
                                    | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_89) 
                                       | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_65) 
                                          | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_55) 
                                             | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_51) 
                                                | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_41) 
                                                   | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_39) 
                                                      | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_15) 
                                                         | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_13) 
                                                            | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_7) 
                                                               | (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_8))))))))))))));
            vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_sel_alu1 
                = ((((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_41) 
                     | ((7U == (7U & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                        & ((3U == (3U & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                            >> 5U)))) 
                           & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_80)))) 
                    << 1U) | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_orMatrixOutputs_T_38));
        }
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_load_use 
            = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_valid) 
               & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_ctrl_mem) 
                  & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__data_hazard_mem)));
    }
    if ((1U & (~ ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_valid) 
                  & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_flush_pipe))))) {
        if (vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_pc_valid) {
            vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_ctrl_mem 
                = vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_mem;
            vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_ctrl_mul 
                = vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_mul;
            vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_ctrl_div 
                = vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_div;
            vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_ctrl_wxd 
                = vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_wxd;
            vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_ctrl_csr 
                = vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_csr;
            vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_ctrl_fence_i 
                = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_fence_i) 
                   | (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_36));
            vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_rvc 
                = vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_rvc;
            __Vdly__tb_Rocket__DOT__dut__DOT__mem_reg_flush_pipe 
                = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_flush_pipe) 
                   | (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_36));
            vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_cause 
                = vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_cause;
            vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_slow_bypass 
                = ((7U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_mem_cmd)) 
                   | (2U > (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_mem_size)));
            vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_load 
                = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_mem) 
                   & ((7U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_mem_cmd)) 
                      | ((0U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_mem_cmd)) 
                         | ((0x10U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_mem_cmd)) 
                            | ((6U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_mem_cmd)) 
                               | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___mem_reg_load_T_23))))));
            vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_store 
                = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_mem) 
                   & ((7U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_mem_cmd)) 
                      | ((1U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_mem_cmd)) 
                         | ((0x11U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_mem_cmd)) 
                            | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___mem_reg_load_T_23)))));
            vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_pc 
                = vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_pc;
            vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_inst 
                = vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_inst;
            vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_wdata 
                = (((QData)((IData)(((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_alu_dw)
                                      ? (IData)((vlSelfRef.tb_Rocket__DOT__dut__DOT__alu__DOT__out 
                                                 >> 0x00000020U))
                                      : (- (IData)(
                                                   (1U 
                                                    & (IData)(
                                                              (vlSelfRef.tb_Rocket__DOT__dut__DOT__alu__DOT__out 
                                                               >> 0x0000001fU)))))))) 
                    << 0x00000020U) | (QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__alu__DOT__out)));
            if (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_rxs2) 
                 & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_mem) 
                    | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_rocc)))) {
                vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_rs2 
                    = ((0U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__size))
                        ? (((QData)((IData)((0x000000ffU 
                                             & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div_io_req_bits_in2)))) 
                            << 0x00000038U) | (((QData)((IData)(
                                                                (0x000000ffU 
                                                                 & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div_io_req_bits_in2)))) 
                                                << 0x00000030U) 
                                               | (((QData)((IData)(
                                                                   (0x000000ffU 
                                                                    & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div_io_req_bits_in2)))) 
                                                   << 0x00000028U) 
                                                  | (((QData)((IData)(
                                                                      (0x000000ffU 
                                                                       & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div_io_req_bits_in2)))) 
                                                      << 0x00000020U) 
                                                     | (((QData)((IData)(
                                                                         (0x000000ffU 
                                                                          & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div_io_req_bits_in2)))) 
                                                         << 0x00000018U) 
                                                        | (((QData)((IData)(
                                                                            (0x000000ffU 
                                                                             & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div_io_req_bits_in2)))) 
                                                            << 0x00000010U) 
                                                           | (((QData)((IData)(
                                                                               (0x000000ffU 
                                                                                & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div_io_req_bits_in2)))) 
                                                               << 8U) 
                                                              | (QData)((IData)(
                                                                                (0x000000ffU 
                                                                                & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div_io_req_bits_in2)))))))))))
                        : ((1U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__size))
                            ? (((QData)((IData)((0x0000ffffU 
                                                 & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div_io_req_bits_in2)))) 
                                << 0x00000030U) | (
                                                   ((QData)((IData)(
                                                                    (0x0000ffffU 
                                                                     & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div_io_req_bits_in2)))) 
                                                    << 0x00000020U) 
                                                   | (((QData)((IData)(
                                                                       (0x0000ffffU 
                                                                        & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div_io_req_bits_in2)))) 
                                                       << 0x00000010U) 
                                                      | (QData)((IData)(
                                                                        (0x0000ffffU 
                                                                         & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div_io_req_bits_in2)))))))
                            : ((2U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__size))
                                ? (((QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div_io_req_bits_in2)) 
                                    << 0x00000020U) 
                                   | (QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div_io_req_bits_in2)))
                                : vlSelfRef.tb_Rocket__DOT__dut__DOT__div_io_req_bits_in2)));
            }
            vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_br_taken 
                = (1U & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_alu_fn) 
                         ^ ((8U & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_alu_fn))
                             ? (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__alu__DOT__slt)
                             : (0ULL == vlSelfRef.tb_Rocket__DOT__dut__DOT__alu__DOT__in1_xor_in2))));
        }
    }
    if ((1U & (~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ctrl_killd)))) {
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_mem_cmd 
            = vlSelfRef.__VdfgRegularize_h6e95ff9d_0_83;
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_fence_i 
            = vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_47;
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_mul = 0U;
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_fp = 0U;
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_rocc = 0U;
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_rxs2 
            = vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_orMatrixOutputs_T_48;
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_jal 
            = vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_41;
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_jalr 
            = vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_39;
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_mem 
            = vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_orMatrixOutputs_T_20;
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_wxd 
            = vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_orMatrixOutputs_T_9;
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_branch 
            = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_87) 
               | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_33));
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_div 
            = vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_orMatrixOutputs_T_11;
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_csr 
            = (((4U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__id_ctrl_decoder_23)) 
                & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_orMatrixOutputs_T_20))
                ? 0U : ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__id_csr_ren)
                         ? 2U : (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__id_ctrl_decoder_23)));
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_flush_pipe 
            = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_47) 
               | ((4U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__id_ctrl_decoder_23)) 
                  | ((~ ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__id_csr_ren) 
                         | ((0x0340U <= (0x00000fffU 
                                         & (0x0300U 
                                            | (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                               >> 0x00000014U)))) 
                            & (0x0343U >= (0x00000fffU 
                                           & (0x0300U 
                                              | (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                 >> 0x00000014U))))))) 
                     & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__id_csr_en))));
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_mem_size 
            = (3U & ((5U == (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_83))
                      ? (((0U != (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs2)) 
                          << 1U) | (0U != (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs1)))
                      : (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                         >> 0x0cU)));
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_alu_dw 
            = ((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_8) 
               | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_7) 
                  | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_15) 
                     | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_27) 
                        | (((3U == (3U & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                            & ((3U == (3U & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                >> 2U)))) 
                               & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_79))) 
                           | (((0U != (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_51)) 
                               | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_63) 
                                  | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_65) 
                                     | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_69) 
                                        | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_75) 
                                           | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_89) 
                                              | ((IData)(
                                                         ((((0x00004033U 
                                                             == 
                                                             (0x00006033U 
                                                              & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                                                            & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_32)) 
                                                           & (0x0fU 
                                                              == (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_58))) 
                                                          & ((3U 
                                                              == 
                                                              (3U 
                                                               & (~ 
                                                                  (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                                   >> 2U)))) 
                                                             & (3U 
                                                                == 
                                                                (3U 
                                                                 & (~ 
                                                                    (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                                     >> 0x00000019U))))))) 
                                                 | (0U 
                                                    != (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_49))))))))) 
                              | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__id_xcpt)))))));
        if (vlSelfRef.tb_Rocket__DOT__dut__DOT__id_xcpt) {
            vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_alu_fn = 0U;
            vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_rvc 
                = ((0U != (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT___io_inst_0_bits_xcpt1_T_5)) 
                   | (3U != (3U & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in)));
        } else {
            vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_alu_fn 
                = (((((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_163) 
                      | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_161) 
                         | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_159) 
                            | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_155) 
                               | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_87) 
                                  | ((3U == (3U & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                                     & ((IData)((((
                                                   (0x00000030U 
                                                    == 
                                                    (0x00004030U 
                                                     & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                                                   & (3U 
                                                      == (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_4))) 
                                                  & (0x7fU 
                                                     == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__id_ctrl_decoder_decoded_lo_15))) 
                                                 & (3U 
                                                    == 
                                                    (3U 
                                                     & (~ 
                                                        (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                         >> 2U)))))) 
                                        | ((~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                               >> 2U)) 
                                           & ((0x0000000fU 
                                               == (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_3)) 
                                              & (3U 
                                                 == (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_13))))))))))) 
                     << 3U) | (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_131) 
                                | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_87) 
                                   | ((IData)(((((0x0000400bU 
                                                  == 
                                                  (0x0000400fU 
                                                   & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                                                 & (3U 
                                                    == (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_40))) 
                                                & (3U 
                                                   == (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_7))) 
                                               & (0x7fU 
                                                  == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__id_ctrl_decoder_decoded_lo_15)))) 
                                      | (((3U == (3U 
                                                  & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                                          & ((3U == 
                                              (3U & 
                                               (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                   >> 2U)))) 
                                             & ((3U 
                                                 == (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_40)) 
                                                & ((3U 
                                                    == (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_7)) 
                                                   & (0x0000007fU 
                                                      == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__id_ctrl_decoder_decoded_lo_42)))))) 
                                         | ((IData)(
                                                    (((0x00004033U 
                                                       == 
                                                       (0x04004073U 
                                                        & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                                                      & (0x1fU 
                                                         == (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_57))) 
                                                     & (3U 
                                                        == 
                                                        (3U 
                                                         & (~ 
                                                            (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                             >> 2U)))))) 
                                            | ((IData)(
                                                       ((0x00004003U 
                                                         == 
                                                         (0x00005007U 
                                                          & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                                                        & (0x0fU 
                                                           == (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_3)))) 
                                               | ((IData)(
                                                          ((((0x00000033U 
                                                              == 
                                                              (0x00000033U 
                                                               & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                                                             & (3U 
                                                                == (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_4))) 
                                                            & (0x7fU 
                                                               == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__id_ctrl_decoder_decoded_lo_15))) 
                                                           & (3U 
                                                              == 
                                                              (3U 
                                                               & (~ 
                                                                  (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                                   >> 2U)))))) 
                                                  | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_65)))))))) 
                               << 2U)) | ((((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_163) 
                                            | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_161) 
                                               | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_159) 
                                                  | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_155) 
                                                     | ((3U 
                                                         == 
                                                         (3U 
                                                          & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                                                        & ((IData)(
                                                                   (((0x00004030U 
                                                                      == 
                                                                      (0x00004034U 
                                                                       & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                                                                     & (3U 
                                                                        == (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_4))) 
                                                                    & (0x7fU 
                                                                       == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__id_ctrl_decoder_decoded_lo_61)))) 
                                                           | ((IData)(
                                                                      ((((0x00000030U 
                                                                          == 
                                                                          (0x00000030U 
                                                                           & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                                                                         & (3U 
                                                                            == (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_4))) 
                                                                        & (0x7fU 
                                                                           == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__id_ctrl_decoder_decoded_lo_61))) 
                                                                       & (3U 
                                                                          == 
                                                                          (3U 
                                                                           & (~ 
                                                                              (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                                               >> 2U)))))) 
                                                              | (((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_71) 
                                                                  & (7U 
                                                                     == 
                                                                     (7U 
                                                                      & (~ 
                                                                         (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                                          >> 2U))))) 
                                                                 | ((IData)(
                                                                            ((((0x00000030U 
                                                                                == 
                                                                                (0x00000030U 
                                                                                & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                                                                               & (3U 
                                                                                == (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_4))) 
                                                                              & (0x7fU 
                                                                                == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__id_ctrl_decoder_decoded_lo_42))) 
                                                                             & (3U 
                                                                                == 
                                                                                (3U 
                                                                                & (~ 
                                                                                (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                                                >> 2U)))))) 
                                                                    | (((~ 
                                                                         (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                                          >> 2U)) 
                                                                        & ((0x0000000fU 
                                                                            == (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_3)) 
                                                                           & (3U 
                                                                              == (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_23)))) 
                                                                       | ((IData)(
                                                                                (((0x00003030U 
                                                                                == 
                                                                                (0x04003070U 
                                                                                & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                                                                                & (0x1fU 
                                                                                == (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_57))) 
                                                                                & (3U 
                                                                                == 
                                                                                (3U 
                                                                                & (~ 
                                                                                (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                                                >> 2U)))))) 
                                                                          | ((IData)(
                                                                                ((0x00003000U 
                                                                                == 
                                                                                (0x00003004U 
                                                                                & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                                                                                & (0x0fU 
                                                                                == (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_3)))) 
                                                                             | ((3U 
                                                                                == 
                                                                                (3U 
                                                                                & (~ 
                                                                                (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                                                >> 2U)))) 
                                                                                & ((7U 
                                                                                == (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_43)) 
                                                                                & (3U 
                                                                                == (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_2)))))))))))))))) 
                                           << 1U) | 
                                          ((0U != (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_15)) 
                                           | (((3U 
                                                == 
                                                (3U 
                                                 & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                                               & ((7U 
                                                   == 
                                                   (7U 
                                                    & (~ 
                                                       (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                        >> 2U)))) 
                                                  & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_76))) 
                                              | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_89) 
                                                 | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_93) 
                                                    | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_99) 
                                                       | ((IData)(
                                                                  ((((0x00004033U 
                                                                      == 
                                                                      (0x04004033U 
                                                                       & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                                                                     & (0x1fU 
                                                                        == (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_57))) 
                                                                    & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_32)) 
                                                                   & (3U 
                                                                      == 
                                                                      (3U 
                                                                       & (~ 
                                                                          (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                                           >> 2U)))))) 
                                                          | (((3U 
                                                               == 
                                                               (3U 
                                                                & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                                                              & ((7U 
                                                                  == 
                                                                  (7U 
                                                                   & (~ 
                                                                      (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                                       >> 2U)))) 
                                                                 & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_72))) 
                                                             | ((IData)(
                                                                        (((0x00001003U 
                                                                           == 
                                                                           (0x00001007U 
                                                                            & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                                                                          & (0x0fU 
                                                                             == (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_3))) 
                                                                         & (3U 
                                                                            == (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_23)))) 
                                                                | ((IData)(
                                                                           ((((0x02000033U 
                                                                               == 
                                                                               (0x06000033U 
                                                                                & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                                                                              & (0x1fU 
                                                                                == (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_57))) 
                                                                             & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_32)) 
                                                                            & (3U 
                                                                               == 
                                                                               (3U 
                                                                                & (~ 
                                                                                (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                                                >> 2U)))))) 
                                                                   | ((vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                                       >> 0x0000000cU) 
                                                                      & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_131)))))))))))));
            vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_rvc 
                = (3U != (3U & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in));
        }
    }
    vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_flush_pipe 
        = ((~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ctrl_killm)) 
           & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_flush_pipe));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___GEN_1 
        = (0x03ffffffffffffffULL & (vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__large_ 
                                    + (QData)((IData)(
                                                      ((~ 
                                                        ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mcountinhibit) 
                                                         >> 2U)) 
                                                       & ((IData)(tb_Rocket__DOT__dut__DOT__csr__DOT__nextSmall) 
                                                          >> 6U))))));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_62 = (QData)((IData)(
                                                                ((4U 
                                                                  & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mcountinhibit))
                                                                  ? (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__small_)
                                                                  : (IData)(tb_Rocket__DOT__dut__DOT__csr__DOT__nextSmall))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT___T_145 = ((IData)(tb_Rocket__DOT__dut__DOT__wb_set_sboard) 
                                                  & (IData)(tb_Rocket__DOT__dut__DOT__wb_wen));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__rf_wen = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT___T_21) 
                                                  | (IData)(tb_Rocket__DOT__dut__DOT__wb_wen));
    tb_Rocket__DOT__dut__DOT__csr__DOT___io_eret_T 
        = ((IData)(tb_Rocket__DOT__dut__DOT__csr__DOT__insn_call) 
           | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__insn_break));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__cause 
        = ((IData)(tb_Rocket__DOT__dut__DOT__csr__DOT__insn_call)
            ? 0x000000000000000bULL : ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__insn_break)
                                        ? 3ULL : ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_xcpt)
                                                   ? vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_cause
                                                   : 4ULL)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_127 
        = (((IData)(__VdfgRegularize_h6e95ff9d_0_26) 
            & (0x00200000U == (0x04200000U & vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst))) 
           & ((3U == (3U & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
                               >> 0x00000016U)))) & 
              (3U == (3U & ((vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
                             >> 0x00000018U) & (vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
                                                >> 0x0000001bU))))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_129 
        = (IData)(((0x1c000000U == (0x1c000000U & vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst)) 
                   & (IData)(__VdfgRegularize_h6e95ff9d_0_26)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_79 
        = (IData)((((0x38000000U == (0x38000000U & vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst)) 
                    & (IData)(__VdfgRegularize_h6e95ff9d_0_27)) 
                   & ((0x0000000fU == (0x0000000fU 
                                       & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
                                             >> 0x00000015U)))) 
                      & (3U == (3U & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
                                         >> 0x0000001eU)))))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_117 
        = (IData)((((0x78100000U == (0xf8100000U & vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst)) 
                    & (IData)(__VdfgRegularize_h6e95ff9d_0_27)) 
                   & ((3U == (3U & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
                                       >> 0x00000015U)))) 
                      & (3U == (3U & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
                                         >> 0x00000017U)))))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_133 
        = (IData)((((0xb0000000U == (0xf0000000U & vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst)) 
                    & (IData)(__VdfgRegularize_h6e95ff9d_0_9)) 
                   & (0x0000003fU == (0x0000003fU & 
                                      (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
                                          >> 0x00000016U))))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_119 
        = (IData)(((((0x78000000U == (0xf9000000U & vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst)) 
                     & (IData)(__VdfgRegularize_h6e95ff9d_0_27)) 
                    & (IData)(__VdfgRegularize_h6e95ff9d_0_9)) 
                   & (3U == (3U & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
                                      >> 0x00000016U))))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_3 
        = ((0x0000007fU == (0x0000007fU & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
                                              >> 0x00000015U)))) 
           & ((vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
               >> 0x00000014U) & (3U == (IData)(__VdfgRegularize_h6e95ff9d_0_85))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_5 
        = ((3U == (3U & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
                            >> 0x00000014U)))) & ((0x0000001fU 
                                                   == 
                                                   (0x0000001fU 
                                                    & (~ 
                                                       (vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
                                                        >> 0x00000017U)))) 
                                                  & ((vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
                                                      >> 0x00000016U) 
                                                     & (3U 
                                                        == (IData)(__VdfgRegularize_h6e95ff9d_0_85)))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_9 
        = ((0x0000000fU == (0x0000000fU & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
                                              >> 0x00000015U)))) 
           & ((vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
               >> 0x00000019U) & (3U == ((~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
                                             >> 0x0000001aU)) 
                                         & (IData)(__VdfgRegularize_h6e95ff9d_0_85)))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_69 
        = (IData)((((3U == (IData)(__VdfgRegularize_h6e95ff9d_0_85)) 
                    & (0x04000000U == (0x0c000000U 
                                       & vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst))) 
                   & (0x0000003fU == (0x0000003fU & 
                                      (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
                                          >> 0x00000014U))))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_71 
        = (IData)((((3U == (IData)(__VdfgRegularize_h6e95ff9d_0_85)) 
                    & (0x04100000U == (0x0e100000U 
                                       & vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst))) 
                   & (0x0000000fU == (0x0000000fU & 
                                      (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
                                          >> 0x00000015U))))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_75 
        = (IData)((((0x04300000U == (0x0c300000U & vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst)) 
                    & (3U == (IData)(__VdfgRegularize_h6e95ff9d_0_85))) 
                   & (0x0000000fU == (0x0000000fU & 
                                      (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
                                          >> 0x00000016U))))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_7 
        = ((0x0000001fU == (0x0000001fU & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
                                              >> 0x00000017U)))) 
           & ((3U == (IData)(__VdfgRegularize_h6e95ff9d_0_85)) 
              & ((vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
                  >> 0x00000016U) & (IData)(__VdfgRegularize_h6e95ff9d_0_66))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_73 
        = (IData)(((((3U == (IData)(__VdfgRegularize_h6e95ff9d_0_85)) 
                     & (0x04000000U == (0x0c000000U 
                                        & vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst))) 
                    & (IData)(__VdfgRegularize_h6e95ff9d_0_9)) 
                   & ((3U == (3U & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
                                       >> 0x00000016U)))) 
                      & (3U == (3U & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
                                         >> 0x00000018U)))))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_85 
        = (((IData)(__VdfgRegularize_h6e95ff9d_0_5) 
            & (0x20100000U == (0x24900000U & vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst))) 
           & ((3U == (3U & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
                               >> 0x00000015U)))) & 
              (3U == (3U & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
                               >> 0x0000001eU))))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_95 
        = (((IData)(__VdfgRegularize_h6e95ff9d_0_5) 
            & (0x20600000U == (0x24f00000U & vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst))) 
           & (3U == (3U & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
                              >> 0x0000001eU)))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_123 
        = (((IData)(__VdfgRegularize_h6e95ff9d_0_5) 
            & (0x60000000U == (0xe4000000U & vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst))) 
           & (0x0000000fU == (0x0000000fU & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
                                                >> 0x00000014U)))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_87 
        = ((((IData)(__VdfgRegularize_h6e95ff9d_0_5) 
             & (0x20000000U == (0x24000000U & vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst))) 
            & (IData)(__VdfgRegularize_h6e95ff9d_0_9)) 
           & ((3U == (3U & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
                               >> 0x00000016U)))) & 
              (3U == (3U & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
                               >> 0x0000001eU))))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_125 
        = ((((IData)(__VdfgRegularize_h6e95ff9d_0_26) 
             & (0x00100000U == (0x04900000U & vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst))) 
            & (IData)(__VdfgRegularize_h6e95ff9d_0_5)) 
           & (3U == (3U & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
                              >> 0x00000015U)))));
    __VdfgRegularize_h6e95ff9d_0_67 = (((IData)(__VdfgRegularize_h6e95ff9d_0_5) 
                                        & (0x20000000U 
                                           == (0x24000000U 
                                               & vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst))) 
                                       & (3U == (3U 
                                                 & (~ 
                                                    (vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
                                                     >> 0x0000001eU)))));
    __VdfgRegularize_h6e95ff9d_0_28 = (((IData)(__VdfgRegularize_h6e95ff9d_0_5) 
                                        & (0x20400000U 
                                           == (0x24c00000U 
                                               & vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst))) 
                                       & (3U == (3U 
                                                 & (~ 
                                                    (vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
                                                     >> 0x0000001eU)))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_flush_pipe 
        = __Vdly__tb_Rocket__DOT__dut__DOT__mem_reg_flush_pipe;
    vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_pc_valid 
        = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_valid) 
           | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_replay) 
              | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_xcpt_interrupt)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr_io_eret 
        = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__insn_ret) 
           | (IData)(tb_Rocket__DOT__dut__DOT__csr__DOT___io_eret_T));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__exception 
        = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_xcpt) 
           | (IData)(tb_Rocket__DOT__dut__DOT__csr__DOT___io_eret_T));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__causeIsDebugInt 
        = (IData)((0x800000000000000eULL == (0x80000000000000ffULL 
                                             & vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__cause)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__causeIsDebugTrigger 
        = (IData)((0x000000000000000eULL == (0x80000000000000ffULL 
                                             & vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__cause)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_83 
        = ((0x0000000fU == (0x0000000fU & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
                                              >> 0x00000014U)))) 
           & (IData)(__VdfgRegularize_h6e95ff9d_0_67));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_89 
        = (IData)((((0x00300000U == (0x00300000U & vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst)) 
                    & (IData)(__VdfgRegularize_h6e95ff9d_0_67)) 
                   & (3U == (3U & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
                                      >> 0x00000016U))))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_91 
        = ((3U == (3U & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
                            >> 0x00000014U)))) & (IData)(__VdfgRegularize_h6e95ff9d_0_28));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_93 
        = ((IData)(__VdfgRegularize_h6e95ff9d_0_28) 
           & (IData)(__VdfgRegularize_h6e95ff9d_0_66));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_97 
        = (IData)(((0x00300000U == (0x00300000U & vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst)) 
                   & (IData)(__VdfgRegularize_h6e95ff9d_0_28)));
    tb_Rocket__DOT__dut__DOT___mem_cfi_taken_T = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_ctrl_branch) 
                                                  & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_br_taken));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_69 = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_ctrl_jalr) 
                                                 | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_ctrl_jal));
    if ((1U & (((~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ctrl_killd)) 
                | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr_io_interrupt)) 
               | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf_io_inst_0_bits_replay)))) {
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_cause 
            = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr_io_interrupt)
                ? 0x8000000000000004ULL : (QData)((IData)(
                                                          ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__bpu_io_debug_if)
                                                            ? 0x0eU
                                                            : 
                                                           ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__bpu_io_xcpt_if)
                                                             ? 3U
                                                             : 
                                                            ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf_io_inst_0_bits_xcpt0_ae_inst)
                                                              ? 1U
                                                              : 
                                                             ((4U 
                                                               & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT___io_inst_0_bits_xcpt1_T_5))
                                                               ? 0x0cU
                                                               : 
                                                              ((2U 
                                                                & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT___io_inst_0_bits_xcpt1_T_5))
                                                                ? 0x14U
                                                                : 
                                                               ((1U 
                                                                 & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT___io_inst_0_bits_xcpt1_T_5))
                                                                 ? 1U
                                                                 : 2U)))))))));
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_pc 
            = vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf_io_pc;
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_inst 
            = vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits;
    }
    vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_valid 
        = (1U & (~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ctrl_killx)));
    tb_Rocket__DOT__dut__DOT__bpu__DOT___r_T_26 = (1U 
                                                   & ((2U 
                                                       & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_control_tmatch))
                                                       ? 
                                                      (((0x00000001ffffffffULL 
                                                         & vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_wdata) 
                                                        >= vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_address) 
                                                       ^ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_control_tmatch))
                                                       : 
                                                      ((0x00000001ffffffffULL 
                                                        & ((~ vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_wdata) 
                                                           | tb_Rocket__DOT__dut__DOT__bpu__DOT___GEN_11)) 
                                                       == tb_Rocket__DOT__dut__DOT__bpu__DOT___r_T_24)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__div_io_req_bits_in2 
        = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_rs_bypass_1)
            ? ((3U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_rs_lsb_1))
                ? vlSelfRef.tb_Rocket__DOT__i_dresp_data
                : ((2U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_rs_lsb_1))
                    ? vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_wdata
                    : (vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_wdata 
                       & (- (QData)((IData)((1U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_rs_lsb_1))))))))
            : ((vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_rs_msb_1 
                << 2U) | (QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_rs_lsb_1))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__div_io_req_bits_in1 
        = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_rs_bypass_0)
            ? ((3U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_rs_lsb_0))
                ? vlSelfRef.tb_Rocket__DOT__i_dresp_data
                : ((2U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_rs_lsb_0))
                    ? vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_wdata
                    : (vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_wdata 
                       & (- (QData)((IData)((1U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_rs_lsb_0))))))))
            : ((vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_rs_msb_0 
                << 2U) | (QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_rs_lsb_0))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__take_pc_wb 
        = ((IData)(__VdfgRegularize_h6e95ff9d_0_81) 
           | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_flush_pipe) 
              | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr_io_eret)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__trapToDebug 
        = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_singleStepped) 
           | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__causeIsDebugInt) 
              | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__causeIsDebugTrigger) 
                 | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_debug) 
                    | ((~ (IData)((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__cause 
                                   >> 0x0000003fU))) 
                       & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_dcsr_ebreakm) 
                          & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__insn_break)))))));
    tb_Rocket__DOT__dut__DOT__csr_io_rw_rdata = ((0x0000000020181004ULL 
                                                  & (- (QData)((IData)(
                                                                       ((0x11300000U 
                                                                         == 
                                                                         (0x11300000U 
                                                                          & vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst)) 
                                                                        & ((3U 
                                                                            == 
                                                                            (3U 
                                                                             & (~ 
                                                                                (vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
                                                                                >> 0x00000016U)))) 
                                                                           & (7U 
                                                                              == 
                                                                              (7U 
                                                                               & ((~ 
                                                                                (vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
                                                                                >> 0x00000019U)) 
                                                                                & (vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
                                                                                >> 0x0000001dU)))))))))) 
                                                 | ((1ULL 
                                                     & (- (QData)((IData)(
                                                                          (((0x31000000U 
                                                                             == 
                                                                             (0x31000000U 
                                                                              & vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst)) 
                                                                            & (IData)(__VdfgRegularize_h6e95ff9d_0_9)) 
                                                                           & ((7U 
                                                                               == 
                                                                               (7U 
                                                                                & (~ 
                                                                                (vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
                                                                                >> 0x00000019U)))) 
                                                                              & (3U 
                                                                                == 
                                                                                (3U 
                                                                                & ((~ 
                                                                                (vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
                                                                                >> 0x00000016U)) 
                                                                                & (vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
                                                                                >> 0x0000001eU)))))))))) 
                                                    | ((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_custom_0 
                                                        & (- (QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_129)))) 
                                                       | ((QData)((IData)(
                                                                          (vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_7_addr 
                                                                           & (- (IData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_97)))))) 
                                                          | ((QData)((IData)(
                                                                             (vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_6_addr 
                                                                              & (- (IData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_95)))))) 
                                                             | ((QData)((IData)(
                                                                                (vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_5_addr 
                                                                                & (- (IData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_93)))))) 
                                                                | ((QData)((IData)(
                                                                                (vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_4_addr 
                                                                                & (- (IData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_91)))))) 
                                                                   | ((QData)((IData)(
                                                                                (vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_3_addr 
                                                                                & (- (IData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_89)))))) 
                                                                      | ((QData)((IData)(
                                                                                (vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_2_addr 
                                                                                & (- (IData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_87)))))) 
                                                                         | ((QData)((IData)(
                                                                                (vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_1_addr 
                                                                                & (- (IData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_85)))))) 
                                                                            | ((QData)((IData)(
                                                                                (vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_0_addr 
                                                                                & (- (IData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_83)))))) 
                                                                               | (((((QData)((IData)(
                                                                                ((((((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_7_cfg_l) 
                                                                                << 0x0000000fU) 
                                                                                | (((((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_7_cfg_a) 
                                                                                << 3U) 
                                                                                | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_7_cfg_x) 
                                                                                << 2U)) 
                                                                                | (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_7_cfg_w) 
                                                                                << 1U) 
                                                                                | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_7_cfg_r))) 
                                                                                << 8U)) 
                                                                                | (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_6_cfg_l) 
                                                                                << 7U) 
                                                                                | ((((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_6_cfg_a) 
                                                                                << 3U) 
                                                                                | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_6_cfg_x) 
                                                                                << 2U)) 
                                                                                | (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_6_cfg_w) 
                                                                                << 1U) 
                                                                                | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_6_cfg_r))))) 
                                                                                << 0x00000010U) 
                                                                                | ((((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_5_cfg_l) 
                                                                                << 0x0000000fU) 
                                                                                | (((((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_5_cfg_a) 
                                                                                << 3U) 
                                                                                | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_5_cfg_x) 
                                                                                << 2U)) 
                                                                                | (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_5_cfg_w) 
                                                                                << 1U) 
                                                                                | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_5_cfg_r))) 
                                                                                << 8U)) 
                                                                                | (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_4_cfg_l) 
                                                                                << 7U) 
                                                                                | ((((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_4_cfg_a) 
                                                                                << 3U) 
                                                                                | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_4_cfg_x) 
                                                                                << 2U)) 
                                                                                | (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_4_cfg_w) 
                                                                                << 1U) 
                                                                                | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_4_cfg_r)))))))) 
                                                                                << 0x00000020U) 
                                                                                | (QData)((IData)(
                                                                                ((((((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_3_cfg_l) 
                                                                                << 0x0000000fU) 
                                                                                | (((((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_3_cfg_a) 
                                                                                << 3U) 
                                                                                | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_3_cfg_x) 
                                                                                << 2U)) 
                                                                                | (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_3_cfg_w) 
                                                                                << 1U) 
                                                                                | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_3_cfg_r))) 
                                                                                << 8U)) 
                                                                                | (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_2_cfg_l) 
                                                                                << 7U) 
                                                                                | ((((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_2_cfg_a) 
                                                                                << 3U) 
                                                                                | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_2_cfg_x) 
                                                                                << 2U)) 
                                                                                | (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_2_cfg_w) 
                                                                                << 1U) 
                                                                                | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_2_cfg_r))))) 
                                                                                << 0x00000010U) 
                                                                                | ((((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_1_cfg_l) 
                                                                                << 0x0000000fU) 
                                                                                | (((((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_1_cfg_a) 
                                                                                << 3U) 
                                                                                | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_1_cfg_x) 
                                                                                << 2U)) 
                                                                                | (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_1_cfg_w) 
                                                                                << 1U) 
                                                                                | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_1_cfg_r))) 
                                                                                << 8U)) 
                                                                                | (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_0_cfg_l) 
                                                                                << 7U) 
                                                                                | ((((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_0_cfg_a) 
                                                                                << 3U) 
                                                                                | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_0_cfg_x) 
                                                                                << 2U)) 
                                                                                | (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_0_cfg_w) 
                                                                                << 1U) 
                                                                                | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_0_cfg_r))))))))) 
                                                                                & (- (QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_79)))) 
                                                                                | ((((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__large_ 
                                                                                << 6U) 
                                                                                | (QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__small_))) 
                                                                                & (- (QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_133)))) 
                                                                                | ((((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__large_1 
                                                                                << 6U) 
                                                                                | (QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__small_1))) 
                                                                                & (- (QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_131)))) 
                                                                                | ((QData)((IData)(
                                                                                ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mcountinhibit) 
                                                                                & (- (IData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_9)))))) 
                                                                                | ((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_dscratch0 
                                                                                & (- (QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_127)))) 
                                                                                | (((((QData)((IData)(
                                                                                (0x3fffffffU 
                                                                                & (- (IData)(
                                                                                (1U 
                                                                                & (IData)(
                                                                                (vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___T_44 
                                                                                >> 0x00000021U)))))))) 
                                                                                << 0x00000022U) 
                                                                                | vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___T_44) 
                                                                                & (- (QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_125)))) 
                                                                                | ((QData)((IData)(
                                                                                ((0x40000003U 
                                                                                | (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_dcsr_ebreakm) 
                                                                                << 0x0000000fU) 
                                                                                | (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_dcsr_cause) 
                                                                                << 6U) 
                                                                                | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_dcsr_step) 
                                                                                << 2U)))) 
                                                                                & (- (IData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_123)))))) 
                                                                                | ((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mcause 
                                                                                & (- (QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_73)))) 
                                                                                | (((((QData)((IData)(
                                                                                (0x3fffffffU 
                                                                                & (- (IData)(
                                                                                (1U 
                                                                                & (IData)(
                                                                                (vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mtval 
                                                                                >> 0x00000021U)))))))) 
                                                                                << 0x00000022U) 
                                                                                | vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mtval) 
                                                                                & (- (QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_75)))) 
                                                                                | (((((QData)((IData)(
                                                                                (0x3fffffffU 
                                                                                & (- (IData)(
                                                                                (1U 
                                                                                & (IData)(
                                                                                (vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___T_30 
                                                                                >> 0x00000021U)))))))) 
                                                                                << 0x00000022U) 
                                                                                | vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___T_30) 
                                                                                & (- (QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_71)))) 
                                                                                | ((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mscratch 
                                                                                & (- (QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_69)))) 
                                                                                | ((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mie 
                                                                                & (- (QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_5)))) 
                                                                                | (((- (QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_7))) 
                                                                                & (QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___read_mtvec_T_5))) 
                                                                                | (((- (QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_1))) 
                                                                                & (((QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mstatus_gva)) 
                                                                                << 0x00000026U) 
                                                                                | (QData)((IData)(
                                                                                (0x00001800U 
                                                                                | ((((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mstatus_spp) 
                                                                                << 8U) 
                                                                                | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mstatus_mpie) 
                                                                                << 7U)) 
                                                                                | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mstatus_mie) 
                                                                                << 3U))))))) 
                                                                                | ((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_misa 
                                                                                & (- (QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_3)))) 
                                                                                | (((((QData)((IData)(
                                                                                (0x7fffffffU 
                                                                                & (- (IData)(
                                                                                (1U 
                                                                                & (IData)(
                                                                                (vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_address 
                                                                                >> 0x00000020U)))))))) 
                                                                                << 0x00000021U) 
                                                                                | vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_address) 
                                                                                & (- (QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_119)))) 
                                                                                | (tb_Rocket__DOT__dut__DOT__csr__DOT___T_20 
                                                                                & (- (QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_117)))))))))))))))))))))))))))))));
    tb_Rocket__DOT__dut__DOT___mem_br_target_T_8 = 
        ((IData)(tb_Rocket__DOT__dut__DOT___mem_cfi_taken_T)
          ? ((((0x00000800U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_inst 
                               >> 0x00000014U)) | (0x000007ffU 
                                                   & (- (IData)(
                                                                (vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_inst 
                                                                 >> 0x0000001fU))))) 
              << 0x00000014U) | ((((0x000001feU & (
                                                   (- (IData)(
                                                              (vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_inst 
                                                               >> 0x0000001fU))) 
                                                   << 1U)) 
                                   | (1U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_inst 
                                            >> 7U))) 
                                  << 0x0000000bU) | 
                                 ((0x000007e0U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_inst 
                                                  >> 0x00000014U)) 
                                  | (0x0000001eU & 
                                     (vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_inst 
                                      >> 7U))))) : 
         ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_ctrl_jal)
           ? ((((0x00000800U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_inst 
                                >> 0x00000014U)) | 
                (0x000007ffU & (- (IData)((vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_inst 
                                           >> 0x0000001fU))))) 
               << 0x00000014U) | ((((0x000001feU & 
                                     (vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_inst 
                                      >> 0x0000000bU)) 
                                    | (1U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_inst 
                                             >> 0x00000014U))) 
                                   << 0x0000000bU) 
                                  | (0x000007feU & 
                                     (vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_inst 
                                      >> 0x00000014U))))
           : (((- (IData)((1U & (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_rvc)
                                   ? 2U : 4U) >> 3U)))) 
               << 4U) | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_rvc)
                          ? 2U : 4U))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_cfi_taken 
        = ((IData)(tb_Rocket__DOT__dut__DOT___mem_cfi_taken_T) 
           | (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_69));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf_io_inst_0_bits_xcpt0_ae_inst 
        = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__buf___05Fxcpt_ae_inst) 
           & ((3U & ((IData)(1U) << (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__nBufValid))) 
              - (IData)(1U)));
    tb_Rocket__DOT__dut__DOT__bpu__DOT__r = ((~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_debug)) 
                                             & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_control_r) 
                                                & (IData)(tb_Rocket__DOT__dut__DOT__bpu__DOT___r_T_26)));
    tb_Rocket__DOT__dut__DOT__bpu__DOT__w = ((~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_debug)) 
                                             & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_control_w) 
                                                & (IData)(tb_Rocket__DOT__dut__DOT__bpu__DOT___r_T_26)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf_io_pc 
        = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__nBufValid)
            ? vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__buf___05Fpc
            : vlSelfRef.tb_Rocket__DOT__fpc);
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr_io_interrupt 
        = ((~ ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_debug) 
               | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__io_status_cease_r))) 
           & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_singleStepped));
    __Vtemp_27[0U] = ((vlSelfRef.tb_Rocket__DOT__imem
                       [(0x000000ffU & (IData)((vlSelfRef.tb_Rocket__DOT__fpc 
                                                >> 2U)))] 
                       << 0x00000010U) | (0x0000ffffU 
                                          & vlSelfRef.tb_Rocket__DOT__imem
                                          [(0x000000ffU 
                                            & (IData)(
                                                      (vlSelfRef.tb_Rocket__DOT__fpc 
                                                       >> 2U)))]));
    __Vtemp_27[1U] = (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_52);
    __Vtemp_27[2U] = (IData)((vlSelfRef.__VdfgRegularize_h6e95ff9d_0_52 
                              >> 0x00000020U));
    __Vtemp_27[3U] = (((IData)(__VdfgRegularize_h6e95ff9d_0_11) 
                       << 0x00000010U) | (IData)(__VdfgRegularize_h6e95ff9d_0_11));
    __Vtemp_27[4U] = 0U;
    __Vtemp_27[5U] = 0U;
    VL_SHIFTL_WWI(191,191,6, __Vtemp_28, __Vtemp_27, 
                  (0x00000030U & ((((IData)(2U) + (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__nBufValid)) 
                                   - (1U & (IData)(
                                                   (vlSelfRef.tb_Rocket__DOT__fpc 
                                                    >> 1U)))) 
                                  << 4U)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
        = ((__Vtemp_28[2U] & ((IData)(0xffffffffU) 
                              << ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__nBufValid) 
                                  << 4U))) | ((~ ((IData)(0xffffffffU) 
                                                  << 
                                                  ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__nBufValid) 
                                                   << 4U))) 
                                              & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__buf___05Fdata));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___GEN_184 
        = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_debug) 
           | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__exception) 
              & ((~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_debug)) 
                 & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__trapToDebug))));
    if (vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__exception) {
        if (vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__trapToDebug) {
            vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___GEN_214 
                = vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mcause;
            vlSelfRef.__VdfgRegularize_h6e95ff9d_0_65 
                = (0x00000003ffffffffULL & vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mepc);
            vlSelfRef.__VdfgRegularize_h6e95ff9d_0_61 
                = (0x00000003ffffffffULL & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_debug)
                                             ? vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_dpc
                                             : (~ (1ULL 
                                                   | (~ vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_pc)))));
            vlSelfRef.__VdfgRegularize_h6e95ff9d_0_64 
                = vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mtval;
            tb_Rocket__DOT__dut__DOT__csr__DOT___GEN_219 
                = vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mstatus_mie;
        } else {
            vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___GEN_214 
                = vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__cause;
            vlSelfRef.__VdfgRegularize_h6e95ff9d_0_65 
                = (0x00000003ffffffffULL & (~ (1ULL 
                                               | (~ vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_pc))));
            vlSelfRef.__VdfgRegularize_h6e95ff9d_0_61 
                = (0x00000003ffffffffULL & vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_dpc);
            vlSelfRef.__VdfgRegularize_h6e95ff9d_0_64 
                = ((((QData)((IData)((1U & (((0U == 
                                              (0x7fffffffU 
                                               & (IData)(
                                                         (vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_wdata 
                                                          >> 0x00000021U)))) 
                                             | (0x7fffffffU 
                                                == 
                                                (0x7fffffffU 
                                                 & (IData)(
                                                           (vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_wdata 
                                                            >> 0x00000021U)))))
                                             ? (IData)(
                                                       (vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_wdata 
                                                        >> 0x00000021U))
                                             : (~ (IData)(
                                                          (vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_wdata 
                                                           >> 0x00000020U))))))) 
                     << 0x00000021U) | (0x00000001ffffffffULL 
                                        & vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_wdata)) 
                   & (- (QData)((IData)(((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_xcpt) 
                                         & ((~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_xcpt)) 
                                            | ((2ULL 
                                                == vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_cause) 
                                               | ((3ULL 
                                                   == vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_cause) 
                                                  | ((1ULL 
                                                      == vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_cause) 
                                                     | ((0x000000000000000cULL 
                                                         == vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_cause) 
                                                        | (0x0000000000000014ULL 
                                                           == vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_cause)))))))))));
            tb_Rocket__DOT__dut__DOT__csr__DOT___GEN_219 = 0U;
        }
    } else {
        vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___GEN_214 
            = vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mcause;
        vlSelfRef.__VdfgRegularize_h6e95ff9d_0_65 = 
            (0x00000003ffffffffULL & vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mepc);
        vlSelfRef.__VdfgRegularize_h6e95ff9d_0_61 = 
            (0x00000003ffffffffULL & vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_dpc);
        vlSelfRef.__VdfgRegularize_h6e95ff9d_0_64 = vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mtval;
        tb_Rocket__DOT__dut__DOT__csr__DOT___GEN_219 
            = vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mstatus_mie;
    }
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___GEN_276 
        = (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__exception)
             ? ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__trapToDebug)
                 ? (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mstatus_mpie)
                 : (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mstatus_mie))
             : (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mstatus_mpie)) 
           | ((~ (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_25)) 
              & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__insn_ret)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__wdata 
        = (tb_Rocket__DOT__dut__DOT__csr__DOT___wdata_T_6 
           & (vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_wdata 
              | (tb_Rocket__DOT__dut__DOT__csr_io_rw_rdata 
                 & (- (QData)((IData)((1U & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr_io_rw_cmd) 
                                             >> 1U))))))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__rf_MPORT_data 
        = (((IData)(vlSelfRef.tb_Rocket__DOT__q2_v) 
            & ((~ (IData)(vlSelfRef.tb_Rocket__DOT__q2_tag)) 
               & (IData)(vlSelfRef.tb_Rocket__DOT__q2_is_load)))
            ? vlSelfRef.tb_Rocket__DOT__i_dresp_data
            : ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT___T_21)
                ? (((QData)((IData)(((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__req_dw)
                                      ? (IData)((vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__result 
                                                 >> 0x00000020U))
                                      : (- (IData)(
                                                   (tb_Rocket__DOT__dut__DOT__div__DOT__loOut 
                                                    >> 0x0000001fU)))))) 
                    << 0x00000020U) | (QData)((IData)(tb_Rocket__DOT__dut__DOT__div__DOT__loOut)))
                : ((0U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_ctrl_csr))
                    ? vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_wdata
                    : tb_Rocket__DOT__dut__DOT__csr_io_rw_rdata)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_br_target 
        = (0x00000003ffffffffULL & (vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_pc 
                                    + (((QData)((IData)(
                                                        (3U 
                                                         & (- (IData)(
                                                                      (tb_Rocket__DOT__dut__DOT___mem_br_target_T_8 
                                                                       >> 0x0000001fU)))))) 
                                        << 0x00000020U) 
                                       | (QData)((IData)(tb_Rocket__DOT__dut__DOT___mem_br_target_T_8)))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT___mem_reg_load_T_23 
        = ((4U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_mem_cmd)) 
           | ((9U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_mem_cmd)) 
              | ((0x0aU == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_mem_cmd)) 
                 | ((0x0bU == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_mem_cmd)) 
                    | ((8U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_mem_cmd)) 
                       | ((0x0cU == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_mem_cmd)) 
                          | ((0x0dU == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_mem_cmd)) 
                             | ((0x0eU == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_mem_cmd)) 
                                | (0x0fU == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_mem_cmd))))))))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_pc_valid 
        = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_valid) 
           | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_replay) 
              | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_xcpt_interrupt)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__killm_common 
        = (1U & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__take_pc_wb) 
                 | ((~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_valid)) 
                    | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_xcpt))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf_io_kill 
        = (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_valid) 
            & ((~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_xcpt)) 
               & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_cfi_taken))) 
           | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__take_pc_wb));
    tb_Rocket__DOT__dut__DOT___T_28 = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_valid) 
                                       & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_ctrl_wxd));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_36 = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_jalr) 
                                                 & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_debug));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__id_mem_busy 
        = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_valid) 
           & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_mem));
    tb_Rocket__DOT__dut__DOT___T_27 = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_valid) 
                                       & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_wxd));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_debug_breakpoint 
        = (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_load) 
            & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_control_action) 
               & (IData)(tb_Rocket__DOT__dut__DOT__bpu__DOT__r))) 
           | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_store) 
              & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_control_action) 
                 & (IData)(tb_Rocket__DOT__dut__DOT__bpu__DOT__w))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__replay_ex = 
        ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_replay) 
         | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_valid) 
            & (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_load_use) 
                & (IData)(tb_Rocket__DOT__dut__DOT__wb_dcache_miss)) 
               | ((0U != (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__state)) 
                  & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_div)))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__div_io_req_valid 
        = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_valid) 
           & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_div));
    tb_Rocket__DOT__dut__DOT__bpu__DOT__x = ((~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_debug)) 
                                             & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_control_x) 
                                                & ((2U 
                                                    & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_control_tmatch))
                                                    ? 
                                                   ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_control_tmatch) 
                                                    ^ 
                                                    ((0x00000001ffffffffULL 
                                                      & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf_io_pc) 
                                                     >= vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_address))
                                                    : 
                                                   (tb_Rocket__DOT__dut__DOT__bpu__DOT___r_T_24 
                                                    == 
                                                    (0x00000001ffffffffULL 
                                                     & ((~ vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf_io_pc) 
                                                        | tb_Rocket__DOT__dut__DOT__bpu__DOT___GEN_11))))));
    tb_Rocket__DOT__dut__DOT__alu_io_in1 = ((2U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_sel_alu1))
                                             ? (((QData)((IData)(
                                                                 (0x3fffffffU 
                                                                  & (- (IData)(
                                                                               (1U 
                                                                                & (IData)(
                                                                                (vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_pc 
                                                                                >> 0x00000021U)))))))) 
                                                 << 0x00000022U) 
                                                | vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_pc)
                                             : (vlSelfRef.tb_Rocket__DOT__dut__DOT__div_io_req_bits_in1 
                                                & (- (QData)((IData)(
                                                                     (1U 
                                                                      == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_sel_alu1)))))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__size = (3U 
                                                & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_mem_size) 
                                                   | (- (IData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_rocc)))));
    tb_Rocket__DOT__dut__DOT__ex_imm_sign = ((vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_inst 
                                              >> 0x0000001fU) 
                                             & (5U 
                                                != (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_sel_imm)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT___decoded_orMatrixOutputs_T_5 
        = (1U & (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_alu_fn) 
                  >> 1U) | (IData)((1U == (5U & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_alu_fn))))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__lhs_sign 
        = (1U & (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_alu_dw)
                   ? (IData)((vlSelfRef.tb_Rocket__DOT__dut__DOT__div_io_req_bits_in1 
                              >> 0x0000003fU)) : (IData)(
                                                         (vlSelfRef.tb_Rocket__DOT__dut__DOT__div_io_req_bits_in1 
                                                          >> 0x0000001fU))) 
                 & ((~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_alu_fn)) 
                    | (3U == (3U & (~ ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_alu_fn) 
                                       >> 1U)))))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__rhs_sign 
        = (1U & (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_alu_dw)
                   ? (IData)((vlSelfRef.tb_Rocket__DOT__dut__DOT__div_io_req_bits_in2 
                              >> 0x0000003fU)) : (IData)(
                                                         (vlSelfRef.tb_Rocket__DOT__dut__DOT__div_io_req_bits_in2 
                                                          >> 0x0000001fU))) 
                 & ((IData)((4U == (5U & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_alu_fn)))) 
                    | (3U == (3U & (~ ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_alu_fn) 
                                       >> 1U)))))));
    tb_Rocket__DOT__dut__DOT__alu__DOT___shin_T_2 = 
        ((5U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_alu_fn)) 
         | (0x0bU == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_alu_fn)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__inst = ((0xffff0000U 
                                                 & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                    & ((- (IData)(
                                                                  (3U 
                                                                   == 
                                                                   (3U 
                                                                    & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in)))) 
                                                       << 0x00000010U))) 
                                                | (0x0000ffffU 
                                                   & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf_io_inst_0_bits_replay 
        = (1U & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__buf_replay) 
                 | ((3U == (3U & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in)) 
                    & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__buf_replay) 
                       >> 1U))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT___io_inst_0_bits_xcpt1_T_5 
        = (1U & ((- (IData)((3U == (3U & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in)))) 
                 & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__buf___05Fxcpt_ae_inst) 
                    & ((((IData)(1U) << (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__nBufValid)) 
                        - (IData)(1U)) >> 1U))));
    tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_s_T_15 
        = ((0x000000c0U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                           << 1U)) | (0x00000038U & 
                                      (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                       >> 7U)));
    tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_s_T_147 
        = ((0x00000fe0U & ((- (IData)((1U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                             >> 0x0000000cU)))) 
                           << 5U)) | (0x0000001fU & 
                                      (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                       >> 2U)));
    tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_s_funct_T_2 
        = ((4U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                  >> 0x0000000aU)) | (3U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                            >> 5U)));
    __VdfgRegularize_h6e95ff9d_0_29 = (0x00042403U 
                                       | (((((0x00000010U 
                                              & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                 >> 1U)) 
                                             | ((0x0000000eU 
                                                 & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                    >> 9U)) 
                                                | (1U 
                                                   & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                      >> 6U)))) 
                                            << 0x00000016U) 
                                           | (0x00038000U 
                                              & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                 << 8U))) 
                                          | (0x00000380U 
                                             & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                << 5U))));
    __VdfgRegularize_h6e95ff9d_0_38 = ((0x00000f80U 
                                        & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in) 
                                       | ((0U != (0x0000001fU 
                                                  & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                     >> 7U)))
                                           ? 3U : 0x1fU));
    __VdfgRegularize_h6e95ff9d_0_82 = ((0x00000038U 
                                        & ((- (IData)(
                                                      (1U 
                                                       & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                          >> 0x0000000cU)))) 
                                           << 3U)) 
                                       | ((6U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                 >> 4U)) 
                                          | (1U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                   >> 2U))));
    __VdfgRegularize_h6e95ff9d_0_84 = ((0x0000000eU 
                                        & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                           >> 6U)) 
                                       | (1U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                >> 0x0000000cU)));
    __VdfgRegularize_h6e95ff9d_0_86 = (0x63U | ((0x00000c00U 
                                                 & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in) 
                                                | ((0x00000300U 
                                                    & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                       << 5U)) 
                                                   | (0x00000080U 
                                                      & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                         >> 5U)))));
    tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_T_2 
        = ((0x00000018U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                           << 3U)) | (7U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                            >> 0x0000000dU)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___GEN_275 
        = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__insn_ret)
            ? ((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_25)
                ? (IData)(tb_Rocket__DOT__dut__DOT__csr__DOT___GEN_219)
                : (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mstatus_mpie))
            : (IData)(tb_Rocket__DOT__dut__DOT__csr__DOT___GEN_219));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_npc = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_ctrl_jalr)
                                                    ? 
                                                   (0x00000003fffffffeULL 
                                                    & (((QData)((IData)(
                                                                        (1U 
                                                                         & (((0U 
                                                                              == 
                                                                              (0x7fffffffU 
                                                                               & (IData)(
                                                                                (vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_wdata 
                                                                                >> 0x00000021U)))) 
                                                                             | (0x7fffffffU 
                                                                                == 
                                                                                (0x7fffffffU 
                                                                                & (IData)(
                                                                                (vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_wdata 
                                                                                >> 0x00000021U)))))
                                                                             ? (IData)(
                                                                                (vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_wdata 
                                                                                >> 0x00000021U))
                                                                             : 
                                                                            (~ (IData)(
                                                                                (vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_wdata 
                                                                                >> 0x00000020U))))))) 
                                                        << 0x00000021U) 
                                                       | (0x00000001ffffffffULL 
                                                          & vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_wdata)))
                                                    : 
                                                   (0x00000003fffffffeULL 
                                                    & vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_br_target));
    tb_Rocket__DOT__dut__DOT___T_30 = ((~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_ctrl_mem)) 
                                       & (IData)(tb_Rocket__DOT__dut__DOT___T_28));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_ldst_xcpt 
        = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_debug_breakpoint) 
           | (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_load) 
               & ((~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_control_action)) 
                  & (IData)(tb_Rocket__DOT__dut__DOT__bpu__DOT__r))) 
              | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_store) 
                 & ((~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_control_action)) 
                    & (IData)(tb_Rocket__DOT__dut__DOT__bpu__DOT__w)))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__ctrl_killx 
        = (1U & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf_io_kill) 
                 | ((~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_valid)) 
                    | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__replay_ex))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT___T_23 
        = ((0U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__state)) 
           & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div_io_req_valid));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__bpu_io_xcpt_if 
        = ((~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_control_action)) 
           & (IData)(tb_Rocket__DOT__dut__DOT__bpu__DOT__x));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__bpu_io_debug_if 
        = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_control_action) 
           & (IData)(tb_Rocket__DOT__dut__DOT__bpu__DOT__x));
    tb_Rocket__DOT__dut__DOT__alu__DOT__shin_r = (((QData)((IData)(
                                                                   ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_alu_dw)
                                                                     ? (IData)(
                                                                               (tb_Rocket__DOT__dut__DOT__alu_io_in1 
                                                                                >> 0x00000020U))
                                                                     : 
                                                                    (- (IData)((IData)(
                                                                                (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_alu_fn) 
                                                                                >> 3U) 
                                                                                & (tb_Rocket__DOT__dut__DOT__alu_io_in1 
                                                                                >> 0x0000001fU)))))))) 
                                                   << 0x00000020U) 
                                                  | (QData)((IData)(tb_Rocket__DOT__dut__DOT__alu_io_in1)));
    tb_Rocket__DOT__dut__DOT__alu_io_in2 = ((1U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_sel_alu2))
                                             ? (((- (QData)((IData)(
                                                                    (1U 
                                                                     & (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_rvc)
                                                                          ? 2U
                                                                          : 4U) 
                                                                        >> 3U))))) 
                                                 << 4U) 
                                                | (QData)((IData)(
                                                                  ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_rvc)
                                                                    ? 2U
                                                                    : 4U))))
                                             : ((3U 
                                                 == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_sel_alu2))
                                                 ? 
                                                (((QData)((IData)(
                                                                  (- (IData)((IData)(tb_Rocket__DOT__dut__DOT__ex_imm_sign))))) 
                                                  << 0x00000020U) 
                                                 | (QData)((IData)(
                                                                   ((((IData)(tb_Rocket__DOT__dut__DOT__ex_imm_sign) 
                                                                      << 0x0000001fU) 
                                                                     | (0x7ff00000U 
                                                                        & (((2U 
                                                                             == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_sel_imm))
                                                                             ? 
                                                                            (vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_inst 
                                                                             >> 0x00000014U)
                                                                             : 
                                                                            (- (IData)((IData)(tb_Rocket__DOT__dut__DOT__ex_imm_sign)))) 
                                                                           << 0x00000014U))) 
                                                                    | ((((0x000001feU 
                                                                          & ((((2U 
                                                                                != (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_sel_imm)) 
                                                                               & (3U 
                                                                                != (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_sel_imm)))
                                                                               ? 
                                                                              (- (IData)((IData)(tb_Rocket__DOT__dut__DOT__ex_imm_sign)))
                                                                               : 
                                                                              (vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_inst 
                                                                               >> 0x0000000cU)) 
                                                                             << 1U)) 
                                                                         | ((IData)(__VdfgRegularize_h6e95ff9d_0_35) 
                                                                            & ((3U 
                                                                                == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_sel_imm))
                                                                                ? 
                                                                               (vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_inst 
                                                                                >> 0x00000014U)
                                                                                : 
                                                                               ((1U 
                                                                                == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_sel_imm))
                                                                                 ? 
                                                                                (vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_inst 
                                                                                >> 7U)
                                                                                 : (IData)(tb_Rocket__DOT__dut__DOT__ex_imm_sign))))) 
                                                                        << 0x0000000bU) 
                                                                       | ((0x000007e0U 
                                                                           & ((vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_inst 
                                                                               >> 0x00000014U) 
                                                                              & ((- (IData)((IData)(__VdfgRegularize_h6e95ff9d_0_35))) 
                                                                                << 5U))) 
                                                                          | ((0x0000001eU 
                                                                              & (((((1U 
                                                                                == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_sel_imm)) 
                                                                                | (0U 
                                                                                == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_sel_imm)))
                                                                                 ? 
                                                                                (vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_inst 
                                                                                >> 8U)
                                                                                 : 
                                                                                ((5U 
                                                                                == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_sel_imm))
                                                                                 ? 
                                                                                (vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_inst 
                                                                                >> 0x00000010U)
                                                                                 : 
                                                                                (vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_inst 
                                                                                >> 0x00000015U))) 
                                                                                & (- (IData)(
                                                                                (2U 
                                                                                != (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_sel_imm))))) 
                                                                                << 1U)) 
                                                                             | (1U 
                                                                                & ((0U 
                                                                                == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_sel_imm))
                                                                                 ? 
                                                                                (vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_inst 
                                                                                >> 7U)
                                                                                 : 
                                                                                ((4U 
                                                                                == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_sel_imm))
                                                                                 ? 
                                                                                (vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_inst 
                                                                                >> 0x00000014U)
                                                                                 : 
                                                                                ((5U 
                                                                                == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_sel_imm)) 
                                                                                & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_inst 
                                                                                >> 0x0000000fU))))))))))))
                                                 : 
                                                (vlSelfRef.tb_Rocket__DOT__dut__DOT__div_io_req_bits_in2 
                                                 & (- (QData)((IData)(
                                                                      (2U 
                                                                       == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_sel_alu2))))))));
    if ((0x1fU == (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_T_2))) {
        tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rd 
            = (0x0000001fU & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                              >> 7U));
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs2 
            = (0x0000001fU & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                              >> 0x00000014U));
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs1 
            = (0x0000001fU & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                              >> 0x0000000fU));
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
            = vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in;
    } else if ((0x1eU == (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_T_2))) {
        tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rd 
            = (0x0000001fU & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                              >> 7U));
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs2 
            = (0x0000001fU & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                              >> 0x00000014U));
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs1 
            = (0x0000001fU & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                              >> 0x0000000fU));
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
            = vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in;
    } else if ((0x1dU == (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_T_2))) {
        tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rd 
            = (0x0000001fU & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                              >> 7U));
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs2 
            = (0x0000001fU & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                              >> 0x00000014U));
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs1 
            = (0x0000001fU & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                              >> 0x0000000fU));
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
            = vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in;
    } else if ((0x1cU == (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_T_2))) {
        tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rd 
            = (0x0000001fU & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                              >> 7U));
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs2 
            = (0x0000001fU & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                              >> 0x00000014U));
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs1 
            = (0x0000001fU & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                              >> 0x0000000fU));
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
            = vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in;
    } else if ((0x1bU == (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_T_2))) {
        tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rd 
            = (0x0000001fU & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                              >> 7U));
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs2 
            = (0x0000001fU & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                              >> 0x00000014U));
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs1 
            = (0x0000001fU & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                              >> 0x0000000fU));
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
            = vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in;
    } else if ((0x1aU == (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_T_2))) {
        tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rd 
            = (0x0000001fU & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                              >> 7U));
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs2 
            = (0x0000001fU & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                              >> 0x00000014U));
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs1 
            = (0x0000001fU & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                              >> 0x0000000fU));
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
            = vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in;
    } else if ((0x19U == (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_T_2))) {
        tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rd 
            = (0x0000001fU & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                              >> 7U));
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs2 
            = (0x0000001fU & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                              >> 0x00000014U));
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs1 
            = (0x0000001fU & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                              >> 0x0000000fU));
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
            = vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in;
    } else if ((0x18U == (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_T_2))) {
        tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rd 
            = (0x0000001fU & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                              >> 7U));
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs2 
            = (0x0000001fU & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                              >> 0x00000014U));
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs1 
            = (0x0000001fU & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                              >> 0x0000000fU));
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
            = vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in;
    } else if ((0x17U == (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_T_2))) {
        tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rd 
            = (0x0000001fU & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                              >> 7U));
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs2 
            = (0x0000001fU & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                              >> 2U));
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs1 
            = (0x0000001fU & 2U);
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
            = (0x00013023U | ((((IData)(__VdfgRegularize_h6e95ff9d_0_84) 
                                << 0x00000019U) | (0x01f00000U 
                                                   & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                      << 0x00000012U))) 
                              | (0x00000f80U & ((IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_s_T_15) 
                                                << 7U))));
    } else if ((0x16U == (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_T_2))) {
        tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rd 
            = (0x0000001fU & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                              >> 7U));
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs2 
            = (0x0000001fU & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                              >> 2U));
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs1 
            = (0x0000001fU & 2U);
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
            = (0x00012023U | ((((0x000000c0U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                >> 1U)) 
                                | ((0x00000020U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                   >> 7U)) 
                                   | (0x0000001fU & 
                                      (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                       >> 2U)))) << 0x00000014U) 
                              | (0x00000e00U & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in)));
    } else if ((0x15U == (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_T_2))) {
        tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rd 
            = (0x0000001fU & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                              >> 7U));
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs2 
            = (0x0000001fU & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                              >> 2U));
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs1 
            = (0x0000001fU & 2U);
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
            = (0x00013027U | ((((IData)(__VdfgRegularize_h6e95ff9d_0_84) 
                                << 0x00000019U) | (0x01f00000U 
                                                   & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                      << 0x00000012U))) 
                              | (0x00000f80U & ((IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_s_T_15) 
                                                << 7U))));
    } else if ((0x14U == (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_T_2))) {
        if ((0x00001000U & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in)) {
            tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rd 
                = (0x0000001fU & ((0U != (0x0000001fU 
                                          & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                             >> 2U)))
                                   ? (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                      >> 7U) : 1U));
            vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs1 
                = (0x0000001fU & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                  >> 7U));
        } else {
            tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rd 
                = (0x0000001fU & ((vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                   >> 7U) & (- (IData)(
                                                       (0U 
                                                        != 
                                                        (0x0000001fU 
                                                         & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                            >> 2U)))))));
            vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs1 
                = (0x0000001fU & ((vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                   >> 7U) & (- (IData)(
                                                       (1U 
                                                        & (~ 
                                                           (0U 
                                                            != 
                                                            (0x0000001fU 
                                                             & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                                >> 2U)))))))));
        }
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs2 
            = (0x0000001fU & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                              >> 2U));
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
            = (3U | (((0x00001000U & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in)
                       ? ((0U != (0x0000001fU & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                 >> 2U)))
                           ? (0x0cU | ((0x007c0000U 
                                        & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                           << 0x00000010U)) 
                                       | ((0x0003e000U 
                                           & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                              << 6U)) 
                                          | (0x000003e0U 
                                             & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                >> 2U)))))
                           : ((0U != (0x0000001fU & 
                                      (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                       >> 7U))) ? (0x0039U 
                                                   | ((0x007c0000U 
                                                       & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                          << 0x00000010U)) 
                                                      | (0x0003e000U 
                                                         & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                            << 6U))))
                               : (0x0004001cU | (((0x0003e000U 
                                                   & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                      << 0x0000000bU)) 
                                                  | (0x00001f00U 
                                                     & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                        << 1U))) 
                                                 << 5U))))
                       : ((0x007c0000U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                          << 0x00000010U)) 
                          | ((0U != (0x0000001fU & 
                                     (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                      >> 2U))) ? (0x0cU 
                                                  | (0x000003e0U 
                                                     & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                        >> 2U)))
                              : ((0x0003e000U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                 << 6U)) 
                                 | ((0U != (0x0000001fU 
                                            & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                               >> 7U)))
                                     ? 0x0019U : 7U))))) 
                     << 2U));
    } else if ((0x13U == (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_T_2))) {
        tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rd 
            = (0x0000001fU & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                              >> 7U));
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs2 
            = (0x0000001fU & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                              >> 2U));
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs1 
            = (0x0000001fU & 2U);
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
            = (0x00013000U | ((((0x00000038U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                << 1U)) 
                                | (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_s_funct_T_2)) 
                               << 0x00000017U) | (IData)(__VdfgRegularize_h6e95ff9d_0_38)));
    } else if ((0x12U == (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_T_2))) {
        tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rd 
            = (0x0000001fU & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                              >> 7U));
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs2 
            = (0x0000001fU & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                              >> 2U));
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs1 
            = (0x0000001fU & 2U);
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
            = (0x00012000U | ((((0x00000030U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                << 2U)) 
                                | ((8U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                          >> 9U)) | 
                                   (7U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                          >> 4U)))) 
                               << 0x00000016U) | (IData)(__VdfgRegularize_h6e95ff9d_0_38)));
    } else if ((0x11U == (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_T_2))) {
        tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rd 
            = (0x0000001fU & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                              >> 7U));
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs2 
            = (0x0000001fU & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                              >> 2U));
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs1 
            = (0x0000001fU & 2U);
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
            = (0x00013007U | ((((0x00000038U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                << 1U)) 
                                | (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_s_funct_T_2)) 
                               << 0x00000017U) | (0x00000f80U 
                                                  & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in)));
    } else if ((0x10U == (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_T_2))) {
        tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rd 
            = (0x0000001fU & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                              >> 7U));
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs2 
            = (0x0000001fU & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                              >> 2U));
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs1 
            = (0x0000001fU & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                              >> 7U));
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
            = (0x00001013U | ((((0x00000020U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                >> 7U)) 
                                | (0x0000001fU & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                  >> 2U))) 
                               << 0x00000014U) | ((0x000f8000U 
                                                   & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                      << 8U)) 
                                                  | (0x00000f80U 
                                                     & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in))));
    } else {
        tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rd 
            = (0x0000001fU & (((0x0eU == (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_T_2))
                                ? (8U | (7U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                               >> 7U)))
                                : (((0x0cU == (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_T_2))
                                     ? (8U | (7U & 
                                              (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                               >> 7U)))
                                     : ((0x0bU == (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_T_2))
                                         ? (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                            >> 7U) : 
                                        ((0x0aU == (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_T_2))
                                          ? (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                             >> 7U)
                                          : ((9U == (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_T_2))
                                              ? (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                 >> 7U)
                                              : ((8U 
                                                  == (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_T_2))
                                                  ? 
                                                 (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                  >> 7U)
                                                  : 
                                                 (8U 
                                                  | (7U 
                                                     & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                        >> 2U)))))))) 
                                   & (- (IData)((0x0dU 
                                                 != (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_T_2)))))) 
                              & (- (IData)((0x0fU != (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_T_2))))));
        vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs2 
            = (0x0000001fU & ((- (IData)((0x0fU != (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_T_2)))) 
                              & ((8U | (7U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                              >> 2U))) 
                                 & (- (IData)((0x0eU 
                                               != (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_T_2)))))));
        if ((0x0fU == (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_T_2))) {
            vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs1 
                = (0x0000001fU & (8U | (7U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                              >> 7U))));
            vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                = (0x00041000U | ((((0x00002000U & 
                                     (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                      << 1U)) | ((IData)(__VdfgRegularize_h6e95ff9d_0_82) 
                                                 << 7U)) 
                                   << 0x00000012U) 
                                  | ((0x00038000U & 
                                      (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                       << 8U)) | (IData)(__VdfgRegularize_h6e95ff9d_0_86))));
        } else if ((0x0eU == (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_T_2))) {
            vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs1 
                = (0x0000001fU & (8U | (7U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                              >> 7U))));
            vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                = (0x00040000U | ((((0x00002000U & 
                                     (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                      << 1U)) | ((IData)(__VdfgRegularize_h6e95ff9d_0_82) 
                                                 << 7U)) 
                                   << 0x00000012U) 
                                  | ((0x00038000U & 
                                      (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                       << 8U)) | (IData)(__VdfgRegularize_h6e95ff9d_0_86))));
        } else if ((0x0dU == (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_T_2))) {
            vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs1 
                = (0x0000001fU & (8U | (7U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                              >> 7U))));
            vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                = (0x006fU | (((((((2U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                          >> 0x0000000bU)) 
                                   | (1U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                            >> 8U))) 
                                  << 0x0000000aU) | 
                                 (((0x0000000cU & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                   >> 7U)) 
                                   | ((2U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                             >> 5U)) 
                                      | (1U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                               >> 7U)))) 
                                  << 6U)) | ((((2U 
                                                & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                   >> 1U)) 
                                               | (1U 
                                                  & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                     >> 0x0000000bU))) 
                                              << 4U) 
                                             | ((0x0000000eU 
                                                 & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                    >> 2U)) 
                                                | (1U 
                                                   & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                      >> 0x0000000cU))))) 
                               << 0x00000014U) | (0x000ff000U 
                                                  & ((- (IData)(
                                                                (1U 
                                                                 & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                                    >> 0x0000000cU)))) 
                                                     << 0x0000000bU))));
        } else if ((0x0cU == (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_T_2))) {
            vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs1 
                = (0x0000001fU & (8U | (7U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                              >> 7U))));
            vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                = ((3U == (3U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                 >> 0x0000000aU))) ? 
                   (0x00840400U | (((((0x000000e0U 
                                       & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                          << 3U)) | 
                                      (7U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                             >> 7U))) 
                                     << 0x0000000fU) 
                                    | ((((7U == (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_s_funct_T_2))
                                          ? 3U : ((6U 
                                                   == (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_s_funct_T_2))
                                                   ? 2U
                                                   : 
                                                  (7U 
                                                   & ((- (IData)(
                                                                 (5U 
                                                                  != (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_s_funct_T_2)))) 
                                                      & ((- (IData)(
                                                                    (4U 
                                                                     != (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_s_funct_T_2)))) 
                                                         & (((2U 
                                                              == (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_s_funct_T_2))
                                                              ? 6U
                                                              : 
                                                             (4U 
                                                              & (- (IData)(
                                                                           (1U 
                                                                            == (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_s_funct_T_2)))))) 
                                                            | (- (IData)(
                                                                         (3U 
                                                                          == (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_s_funct_T_2)))))))))) 
                                        << 0x0000000cU) 
                                       | ((0x00000380U 
                                           & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in) 
                                          | ((0x00001000U 
                                              & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in)
                                              ? 0x3bU
                                              : 0x33U)))) 
                                   | (0x40000000U & 
                                      (- (IData)((0U 
                                                  == 
                                                  (3U 
                                                   & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                      >> 5U))))))))
                    : ((2U == (3U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                     >> 0x0000000aU)))
                        ? (0x00047413U | (((IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_s_T_147) 
                                           << 0x00000014U) 
                                          | ((0x00038000U 
                                              & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                 << 8U)) 
                                             | (0x00000380U 
                                                & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in))))
                        : (0x00045413U | ((0x40000000U 
                                           & (- (IData)(
                                                        (1U 
                                                         == 
                                                         (3U 
                                                          & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                             >> 0x0000000aU)))))) 
                                          | ((((0x00000400U 
                                                & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                   >> 2U)) 
                                               | ((0x000003e0U 
                                                   & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                      << 3U)) 
                                                  | (7U 
                                                     & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                        >> 7U)))) 
                                              << 0x0000000fU) 
                                             | (0x00000380U 
                                                & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in))))));
        } else if ((0x0bU == (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_T_2))) {
            vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs1 
                = (0x0000001fU & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                  >> 7U));
            vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                = (((0U == (0x0000001fU & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                           >> 7U))) 
                    | (2U == (0x0000001fU & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                             >> 7U))))
                    ? (((((0x00000038U & ((- (IData)(
                                                     (1U 
                                                      & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                         >> 0x0000000cU)))) 
                                          << 3U)) | 
                          ((6U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                  >> 2U)) | (1U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                   >> 5U)))) 
                         << 0x0000001aU) | (((0x00000020U 
                                              & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                 << 3U)) 
                                             | (0x00000010U 
                                                & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                   >> 2U))) 
                                            << 0x00000014U)) 
                       | ((0x000f8000U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                          << 8U)) | 
                          ((0x00000f80U & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in) 
                           | ((0U != (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_s_T_147))
                               ? 0x13U : 0x1fU)))) : 
                   (((- (IData)((1U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                       >> 0x0000000cU)))) 
                     << 0x00000011U) | ((0x0001f000U 
                                         & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                            << 0x0000000aU)) 
                                        | ((0x00000f80U 
                                            & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in) 
                                           | ((0U != (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_s_T_147))
                                               ? 0x37U
                                               : 0x3fU)))));
        } else {
            vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs1 
                = (0x0000001fU & (((9U == (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_T_2))
                                    ? (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                       >> 7U) : ((8U 
                                                  == (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_T_2))
                                                  ? 
                                                 (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                  >> 7U)
                                                  : 
                                                 ((7U 
                                                   == (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_T_2))
                                                   ? 
                                                  (8U 
                                                   | (7U 
                                                      & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                         >> 7U)))
                                                   : 
                                                  ((6U 
                                                    == (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_T_2))
                                                    ? 
                                                   (8U 
                                                    | (7U 
                                                       & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                          >> 7U)))
                                                    : 
                                                   ((5U 
                                                     == (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_T_2))
                                                     ? 
                                                    (8U 
                                                     | (7U 
                                                        & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                           >> 7U)))
                                                     : 
                                                    ((4U 
                                                      == (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_T_2))
                                                      ? 
                                                     (8U 
                                                      | (7U 
                                                         & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                            >> 7U)))
                                                      : 
                                                     ((3U 
                                                       == (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_T_2))
                                                       ? 
                                                      (8U 
                                                       | (7U 
                                                          & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                             >> 7U)))
                                                       : 
                                                      ((2U 
                                                        == (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_T_2))
                                                        ? 
                                                       (8U 
                                                        | (7U 
                                                           & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                              >> 7U)))
                                                        : 
                                                       ((1U 
                                                         == (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_T_2))
                                                         ? 
                                                        (8U 
                                                         | (7U 
                                                            & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                               >> 7U)))
                                                         : 2U))))))))) 
                                  & (- (IData)((0x0aU 
                                                != (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_T_2))))));
            vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                = ((0x0aU == (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_T_2))
                    ? (0x13U | (((IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_s_T_147) 
                                 << 0x00000014U) | 
                                (0x00000f80U & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in)))
                    : ((9U == (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_T_2))
                        ? (((IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_s_T_147) 
                            << 0x00000014U) | ((0x000f8000U 
                                                & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                   << 8U)) 
                                               | ((0x00000f80U 
                                                   & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in) 
                                                  | ((0U 
                                                      != 
                                                      (0x0000001fU 
                                                       & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                          >> 7U)))
                                                      ? 0x1bU
                                                      : 0x1fU))))
                        : ((8U == (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_T_2))
                            ? (0x13U | (((IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_s_T_147) 
                                         << 0x00000014U) 
                                        | ((0x000f8000U 
                                            & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                               << 8U)) 
                                           | (0x00000f80U 
                                              & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in))))
                            : ((7U == (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_T_2))
                                ? (0x00843023U | ((
                                                   ((0x00001c00U 
                                                     & ((IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_s_T_15) 
                                                        << 5U)) 
                                                    | ((0x000000e0U 
                                                        & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                           << 3U)) 
                                                       | (7U 
                                                          & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                             >> 7U)))) 
                                                   << 0x0000000fU) 
                                                  | (0x00000f80U 
                                                     & ((IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_s_T_15) 
                                                        << 7U))))
                                : ((6U == (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_T_2))
                                    ? (0x00842023U 
                                       | ((((0x00000c00U 
                                             & (__VdfgRegularize_h6e95ff9d_0_29 
                                                >> 0x0000000fU)) 
                                            | ((0x000000e0U 
                                                & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                   << 3U)) 
                                               | (7U 
                                                  & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                     >> 7U)))) 
                                           << 0x0000000fU) 
                                          | (0x00000f80U 
                                             & (__VdfgRegularize_h6e95ff9d_0_29 
                                                >> 0x0000000dU))))
                                    : ((5U == (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_T_2))
                                        ? (0x00843027U 
                                           | ((((0x00001c00U 
                                                 & ((IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_s_T_15) 
                                                    << 5U)) 
                                                | ((0x000000e0U 
                                                    & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                       << 3U)) 
                                                   | (7U 
                                                      & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                         >> 7U)))) 
                                               << 0x0000000fU) 
                                              | (0x00000f80U 
                                                 & ((IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_s_T_15) 
                                                    << 7U))))
                                        : ((4U == (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_T_2))
                                            ? (0x0084203fU 
                                               | ((((0x00000c00U 
                                                     & (__VdfgRegularize_h6e95ff9d_0_29 
                                                        >> 0x0000000fU)) 
                                                    | ((0x000000e0U 
                                                        & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                           << 3U)) 
                                                       | (7U 
                                                          & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                             >> 7U)))) 
                                                   << 0x0000000fU) 
                                                  | (0x00000f80U 
                                                     & (__VdfgRegularize_h6e95ff9d_0_29 
                                                        >> 0x0000000dU))))
                                            : ((3U 
                                                == (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_T_2))
                                                ? (0x00043403U 
                                                   | ((((IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_s_T_15) 
                                                        << 0x00000014U) 
                                                       | (0x00038000U 
                                                          & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                             << 8U))) 
                                                      | (0x00000380U 
                                                         & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                            << 5U))))
                                                : (
                                                   (2U 
                                                    == (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_T_2))
                                                    ? __VdfgRegularize_h6e95ff9d_0_29
                                                    : 
                                                   ((1U 
                                                     == (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_T_2))
                                                     ? 
                                                    (0x00043407U 
                                                     | ((((IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp__DOT___io_out_s_T_15) 
                                                          << 0x00000014U) 
                                                         | (0x00038000U 
                                                            & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                               << 8U))) 
                                                        | (0x00000380U 
                                                           & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                              << 5U))))
                                                     : 
                                                    (0x00010400U 
                                                     | ((((0x000003c0U 
                                                           & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                              >> 1U)) 
                                                          | ((((6U 
                                                                & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                                   >> 0x0000000aU)) 
                                                               | (1U 
                                                                  & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                                     >> 5U))) 
                                                              << 3U) 
                                                             | (4U 
                                                                & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                                   >> 4U)))) 
                                                         << 0x00000014U) 
                                                        | ((0x00000380U 
                                                            & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                               << 5U)) 
                                                           | ((0U 
                                                               != 
                                                               (0x000000ffU 
                                                                & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
                                                                   >> 5U)))
                                                               ? 0x13U
                                                               : 0x1fU))))))))))))));
        }
    }
    vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_npc_misaligned 
        = (1U & ((~ (IData)((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_misa 
                             >> 2U))) & (IData)((vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_npc 
                                                 >> 1U))));
    tb_Rocket__DOT__dut__DOT__alu__DOT___shin_T_11 
        = ((tb_Rocket__DOT__dut__DOT__alu__DOT__shin_r 
            << 0x00000020U) | (tb_Rocket__DOT__dut__DOT__alu__DOT__shin_r 
                               >> 0x00000020U));
    tb_Rocket__DOT__dut__DOT__alu__DOT__in2_inv = (
                                                   (8U 
                                                    & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_alu_fn))
                                                    ? 
                                                   (~ tb_Rocket__DOT__dut__DOT__alu_io_in2)
                                                    : tb_Rocket__DOT__dut__DOT__alu_io_in2);
    tb_Rocket__DOT__dut__DOT__rf_id_rs_MPORT_1_data 
        = (vlSelfRef.tb_Rocket__DOT__dut__DOT__rf[(0x0000001fU 
                                                   & (~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs2)))] 
           & (- (QData)((IData)((0x1eU >= (0x0000001fU 
                                           & (~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs2))))))));
    tb_Rocket__DOT__dut__DOT___data_hazard_ex_T_2 = 
        ((0x0000001fU & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_inst 
                         >> 7U)) == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs2));
    tb_Rocket__DOT__dut__DOT___data_hazard_mem_T_2 
        = ((0x0000001fU & (vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_inst 
                           >> 7U)) == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs2));
    tb_Rocket__DOT__dut__DOT__rf_id_rs_MPORT_data = 
        (vlSelfRef.tb_Rocket__DOT__dut__DOT__rf[(0x0000001fU 
                                                 & (~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs1)))] 
         & (- (QData)((IData)((0x1eU >= (0x0000001fU 
                                         & (~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs1))))))));
    tb_Rocket__DOT__dut__DOT___data_hazard_ex_T = (
                                                   (0x0000001fU 
                                                    & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_inst 
                                                       >> 7U)) 
                                                   == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs1));
    tb_Rocket__DOT__dut__DOT___data_hazard_mem_T = 
        ((0x0000001fU & (vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_inst 
                         >> 7U)) == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs1));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_32 = (IData)(
                                                        (0x00001000U 
                                                         == 
                                                         (0x00001040U 
                                                          & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_40 = ((2U 
                                                  & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                     >> 3U)) 
                                                 | (1U 
                                                    & (~ 
                                                       (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                        >> 6U))));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_23 = ((2U 
                                                  & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                     >> 0x0000000cU)) 
                                                 | (1U 
                                                    & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                       >> 0x0000000eU)));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_80 = (IData)(
                                                        (0x00000010U 
                                                         == 
                                                         (0x00000018U 
                                                          & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)));
    vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[vlSelfRef.__VdfgBinToOneHot_Pre_h787163e4_0_0] = 0U;
    vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                   >> 0x00000014U)] = 1U;
    vlSelfRef.__VdfgBinToOneHot_Pre_h787163e4_0_0 = 
        (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
         >> 0x00000014U);
    vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_9 
        = (IData)(((3U == (0x00004003U & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                   & (0x0000001fU == (0x0000001fU & 
                                      (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                          >> 2U))))));
    tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_19 
        = (IData)(((0x00000023U == (0x00004063U & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                   & (7U == (7U & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                      >> 2U))))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_7 
        = (IData)(((3U == (0x00004043U & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                   & (7U == (7U & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                      >> 2U))))));
    __VdfgRegularize_h6e95ff9d_0_24 = ((2U & ((~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                  >> 0x00000010U)) 
                                              << 1U)) 
                                       | (1U & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                   >> 0x00000011U))));
    tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_T_22 
        = ((2U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                  >> 0x0000001dU)) | (1U & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                               >> 0x0000001fU))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_65 
        = (IData)(((0x00002013U == (0x00002013U & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                   & ((3U == (3U & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                       >> 2U)))) & 
                      (3U == (3U & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                       >> 5U)))))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_1 
        = (IData)(((3U == (0x00001003U & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                   & ((3U == (3U & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                       >> 2U)))) & 
                      (3U == (3U & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                       >> 5U)))))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_63 
        = (IData)(((0x00001073U == (0x00001073U & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                   & (3U == (3U & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                      >> 2U))))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_75 
        = (IData)(((0x00002073U == (0x00002073U & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                   & (3U == (3U & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                      >> 2U))))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_5 
        = (IData)(((3U == (0x00002003U & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                   & (0x0000001fU == (0x0000001fU & 
                                      (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                          >> 2U))))));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_7 = ((2U 
                                                 & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                    >> 0x0000000bU)) 
                                                | (1U 
                                                   & (~ 
                                                      (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                       >> 0x0000000dU))));
    __VdfgRegularize_h6e95ff9d_0_34 = (IData)((0x00000060U 
                                               == (0x00000070U 
                                                   & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)));
    __VdfgRegularize_h6e95ff9d_0_77 = (IData)((0x00000010U 
                                               == (0x00000050U 
                                                   & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)));
    tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_139 
        = (IData)(((0x1000002fU == (0x1800007fU & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                   & ((7U == (7U & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                       >> 0x0000001dU)))) 
                      & (0x0000001fU == (0x0000001fU 
                                         & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                               >> 0x00000014U)))))));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_4 = ((2U 
                                                 & ((~ 
                                                     (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                      >> 6U)) 
                                                    << 1U)) 
                                                | (1U 
                                                   & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                      >> 0x0000000dU)));
    __VdfgRegularize_h6e95ff9d_0_20 = ((2U & ((~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                  >> 5U)) 
                                              << 1U)) 
                                       | (1U & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                   >> 6U))));
    __VdfgRegularize_h6e95ff9d_0_0 = ((2U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                             >> 4U)) 
                                      | (1U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                               >> 6U)));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_13 = ((2U 
                                                  & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                     >> 0x0000000cU)) 
                                                 | (1U 
                                                    & (~ 
                                                       (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                        >> 0x0000000eU))));
    __VdfgRegularize_h6e95ff9d_0_12 = ((2U & ((~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                  >> 6U)) 
                                              << 1U)) 
                                       | (1U & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                   >> 0x0000000cU))));
    __VdfgRegularize_h6e95ff9d_0_31 = (IData)((0U == 
                                               (0x00000044U 
                                                & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_2 = ((2U 
                                                 & ((~ 
                                                     (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                      >> 0x0000000dU)) 
                                                    << 1U)) 
                                                | (1U 
                                                   & (~ 
                                                      (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                       >> 0x0000000eU))));
    __VdfgRegularize_h6e95ff9d_0_21 = ((2U & ((~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                  >> 0x0000001eU)) 
                                              << 1U)) 
                                       | (1U & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                   >> 0x0000001fU))));
    __VdfgRegularize_h6e95ff9d_0_14 = ((2U & ((~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                  >> 0x0000001bU)) 
                                              << 1U)) 
                                       | (1U & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                   >> 0x0000001cU))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT___T_71 = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_valid) 
                                                 & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_npc_misaligned));
    tb_Rocket__DOT__dut__DOT__alu__DOT___shin_T_21 
        = ((0xffff0000ffff0000ULL & (tb_Rocket__DOT__dut__DOT__alu__DOT___shin_T_11 
                                     << 0x00000010U)) 
           | (0x0000ffff0000ffffULL & (tb_Rocket__DOT__dut__DOT__alu__DOT___shin_T_11 
                                       >> 0x00000010U)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__alu__DOT__in1_xor_in2 
        = (tb_Rocket__DOT__dut__DOT__alu_io_in1 ^ tb_Rocket__DOT__dut__DOT__alu__DOT__in2_inv);
    vlSelfRef.tb_Rocket__DOT__dut__DOT__alu_io_adder_out 
        = (tb_Rocket__DOT__dut__DOT__alu_io_in1 + (tb_Rocket__DOT__dut__DOT__alu__DOT__in2_inv 
                                                   + (QData)((IData)(
                                                                     (1U 
                                                                      & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_alu_fn) 
                                                                         >> 3U))))));
    if (vlSelfRef.tb_Rocket__DOT__dut__DOT__rf_wen) {
        if ((0U != (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__rf_waddr))) {
            vlSelfRef.tb_Rocket__DOT__dut__DOT__id_rs_1 
                = (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__rf_waddr) 
                    == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs2))
                    ? vlSelfRef.tb_Rocket__DOT__dut__DOT__rf_MPORT_data
                    : tb_Rocket__DOT__dut__DOT__rf_id_rs_MPORT_1_data);
            vlSelfRef.tb_Rocket__DOT__dut__DOT__id_rs_0 
                = (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__rf_waddr) 
                    == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs1))
                    ? vlSelfRef.tb_Rocket__DOT__dut__DOT__rf_MPORT_data
                    : tb_Rocket__DOT__dut__DOT__rf_id_rs_MPORT_data);
        } else {
            vlSelfRef.tb_Rocket__DOT__dut__DOT__id_rs_1 
                = tb_Rocket__DOT__dut__DOT__rf_id_rs_MPORT_1_data;
            vlSelfRef.tb_Rocket__DOT__dut__DOT__id_rs_0 
                = tb_Rocket__DOT__dut__DOT__rf_id_rs_MPORT_data;
        }
    } else {
        vlSelfRef.tb_Rocket__DOT__dut__DOT__id_rs_1 
            = tb_Rocket__DOT__dut__DOT__rf_id_rs_MPORT_1_data;
        vlSelfRef.tb_Rocket__DOT__dut__DOT__id_rs_0 
            = tb_Rocket__DOT__dut__DOT__rf_id_rs_MPORT_data;
    }
    vlSelfRef.tb_Rocket__DOT__dut__DOT__id_bypass_src_1_1 
        = ((IData)(tb_Rocket__DOT__dut__DOT___data_hazard_ex_T_2) 
           & (IData)(tb_Rocket__DOT__dut__DOT___T_27));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__id_bypass_src_1_2 
        = ((IData)(tb_Rocket__DOT__dut__DOT___data_hazard_mem_T_2) 
           & (IData)(tb_Rocket__DOT__dut__DOT___T_30));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__id_bypass_src_0_1 
        = ((IData)(tb_Rocket__DOT__dut__DOT___data_hazard_ex_T) 
           & (IData)(tb_Rocket__DOT__dut__DOT___T_27));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__id_bypass_src_0_2 
        = ((IData)(tb_Rocket__DOT__dut__DOT___data_hazard_mem_T) 
           & (IData)(tb_Rocket__DOT__dut__DOT___T_30));
    tb_Rocket__DOT__dut__DOT__id_ctrl_decoder_decoded_lo_82 
        = (((((((2U & ((~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                           >> 0x00000012U)) << 1U)) 
                | (1U & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                            >> 0x00000013U)))) << 5U) 
              | (((2U & ((~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                             >> 0x00000014U)) << 1U)) 
                  | (1U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                           >> 0x00000015U))) << 3U)) 
             | ((4U & ((~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                           >> 0x00000016U)) << 2U)) 
                | ((2U & ((~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                              >> 0x00000017U)) << 1U)) 
                   | (1U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                            >> 0x00000018U))))) << 7U) 
           | (((((2U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                        >> 0x00000018U)) | (1U & (~ 
                                                  (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                   >> 0x0000001aU)))) 
                << 5U) | (((2U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                  >> 0x0000001aU)) 
                           | (1U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                    >> 0x0000001cU))) 
                          << 3U)) | ((4U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                            >> 0x0000001bU)) 
                                     | (IData)(tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_T_22))));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_8 = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_5) 
                                                | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_1));
    vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_33 
        = (IData)((((3U == (0x00002003U & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                    & (IData)(__VdfgRegularize_h6e95ff9d_0_34)) 
                   & (3U == (3U & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                      >> 2U))))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_41 
        = ((0x0000000fU == (0x0000000fU & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
           & (IData)(__VdfgRegularize_h6e95ff9d_0_34));
    vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_87 
        = (IData)((((0x00004003U == (0x00004003U & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                    & (IData)(__VdfgRegularize_h6e95ff9d_0_34)) 
                   & (3U == (3U & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                      >> 2U))))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_15 
        = (IData)(((7U == (0x0000000fU & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                   & (IData)(__VdfgRegularize_h6e95ff9d_0_77)));
    __VdfgRegularize_h6e95ff9d_0_41 = ((4U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                              >> 2U)) 
                                       | (IData)(__VdfgRegularize_h6e95ff9d_0_20));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_71 = ((3U 
                                                  == (IData)(__VdfgRegularize_h6e95ff9d_0_0)) 
                                                 & (3U 
                                                    == (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_23)));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_72 = (IData)(
                                                        ((3U 
                                                          == (IData)(__VdfgRegularize_h6e95ff9d_0_0)) 
                                                         & (0x00005000U 
                                                            == 
                                                            (0x00005000U 
                                                             & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits))));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_76 = ((3U 
                                                  == (IData)(__VdfgRegularize_h6e95ff9d_0_0)) 
                                                 & (3U 
                                                    == (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_7)));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_43 = ((4U 
                                                  & ((~ 
                                                      (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                       >> 4U)) 
                                                     << 2U)) 
                                                 | (IData)(__VdfgRegularize_h6e95ff9d_0_0));
    __VdfgRegularize_h6e95ff9d_0_74 = (IData)(((0x00001000U 
                                                == 
                                                (0x00003000U 
                                                 & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                                               & (IData)(__VdfgRegularize_h6e95ff9d_0_31)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_11 
        = (IData)((((0x0000000fU == (0x0000001fU & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                    & (3U == (IData)(__VdfgRegularize_h6e95ff9d_0_20))) 
                   & (3U == (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_2))));
    __VdfgRegularize_h6e95ff9d_0_46 = ((4U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                              >> 0x0000000aU)) 
                                       | (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_2));
    __VdfgRegularize_h6e95ff9d_0_19 = ((4U & ((~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                  >> 0x0000000cU)) 
                                              << 2U)) 
                                       | (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_2));
    tb_Rocket__DOT__dut__DOT__id_ctrl_decoder_decoded_lo_71 
        = (((((((2U & ((~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                           >> 0x00000011U)) << 1U)) 
                | (1U & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                            >> 0x00000012U)))) << 5U) 
              | (((2U & ((~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                             >> 0x00000013U)) << 1U)) 
                  | (1U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                           >> 0x00000014U))) << 3U)) 
             | ((4U & ((~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                           >> 0x00000015U)) << 2U)) 
                | ((2U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                          >> 0x00000015U)) | (1U & 
                                              (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                  >> 0x00000017U)))))) 
            << 7U) | (((((2U & ((~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                    >> 0x00000018U)) 
                                << 1U)) | (1U & (~ 
                                                 (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                  >> 0x00000019U)))) 
                        << 5U) | (((2U & ((~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                              >> 0x0000001aU)) 
                                          << 1U)) | 
                                   (1U & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                             >> 0x0000001bU)))) 
                                  << 3U)) | ((4U & 
                                              (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                               >> 0x0000001aU)) 
                                             | (IData)(__VdfgRegularize_h6e95ff9d_0_21))));
    tb_Rocket__DOT__dut__DOT__id_ctrl_decoder_decoded_lo_75 
        = (((((((2U & ((~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                           >> 0x00000012U)) << 1U)) 
                | (1U & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                            >> 0x00000013U)))) << 5U) 
              | (((2U & ((~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                             >> 0x00000014U)) << 1U)) 
                  | (1U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                           >> 0x00000015U))) << 3U)) 
             | ((4U & ((~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                           >> 0x00000016U)) << 2U)) 
                | ((2U & ((~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                              >> 0x00000017U)) << 1U)) 
                   | (1U & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                               >> 0x00000018U)))))) 
            << 7U) | (((((2U & ((~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                    >> 0x00000019U)) 
                                << 1U)) | (1U & (~ 
                                                 (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                  >> 0x0000001aU)))) 
                        << 5U) | (((2U & ((~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                              >> 0x0000001bU)) 
                                          << 1U)) | 
                                   (1U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                          >> 0x0000001cU))) 
                                  << 3U)) | ((4U & 
                                              (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                               >> 0x0000001bU)) 
                                             | (IData)(__VdfgRegularize_h6e95ff9d_0_21))));
    __VdfgRegularize_h6e95ff9d_0_22 = ((4U & ((~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                  >> 0x0000001dU)) 
                                              << 2U)) 
                                       | (IData)(__VdfgRegularize_h6e95ff9d_0_21));
    __VdfgRegularize_h6e95ff9d_0_47 = ((((4U & ((~ 
                                                 (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                  >> 0x0000001aU)) 
                                                << 2U)) 
                                         | (IData)(__VdfgRegularize_h6e95ff9d_0_14)) 
                                        << 3U) | ((4U 
                                                   & ((~ 
                                                       (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                        >> 0x0000001dU)) 
                                                      << 2U)) 
                                                  | (IData)(tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_T_22)));
    __VdfgRegularize_h6e95ff9d_0_75 = (IData)((((0x00000020U 
                                                 == 
                                                 (0x00004020U 
                                                  & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                                                & (3U 
                                                   == (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_4))) 
                                               & (3U 
                                                  == (IData)(__VdfgRegularize_h6e95ff9d_0_14))));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_58 = (((IData)(__VdfgRegularize_h6e95ff9d_0_14) 
                                                  << 2U) 
                                                 | ((2U 
                                                     & ((~ 
                                                         (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                          >> 0x0000001dU)) 
                                                        << 1U)) 
                                                    | (1U 
                                                       & (~ 
                                                          (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                           >> 0x0000001fU)))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_xcpt = 
        ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___T_70) 
         | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___T_71) 
            | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_valid) 
               & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_ldst_xcpt))));
    tb_Rocket__DOT__dut__DOT__alu__DOT___shin_T_31 
        = ((0xff00ff00ff00ff00ULL & (tb_Rocket__DOT__dut__DOT__alu__DOT___shin_T_21 
                                     << 8U)) | (0x00ff00ff00ff00ffULL 
                                                & (tb_Rocket__DOT__dut__DOT__alu__DOT___shin_T_21 
                                                   >> 8U)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__alu__DOT__slt 
        = (1U & (((1U & (IData)((tb_Rocket__DOT__dut__DOT__alu_io_in2 
                                 >> 0x0000003fU))) 
                  == (1U & (IData)((tb_Rocket__DOT__dut__DOT__alu_io_in1 
                                    >> 0x0000003fU))))
                  ? (IData)((vlSelfRef.tb_Rocket__DOT__dut__DOT__alu_io_adder_out 
                             >> 0x0000003fU)) : ((2U 
                                                  & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_alu_fn))
                                                  ? (IData)(
                                                            (tb_Rocket__DOT__dut__DOT__alu_io_in2 
                                                             >> 0x0000003fU))
                                                  : (IData)(
                                                            (tb_Rocket__DOT__dut__DOT__alu_io_in1 
                                                             >> 0x0000003fU)))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__do_bypass_1 
        = ((0U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs2)) 
           | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__id_bypass_src_1_1) 
              | (((IData)(tb_Rocket__DOT__dut__DOT___data_hazard_mem_T_2) 
                  & (IData)(tb_Rocket__DOT__dut__DOT___T_28)) 
                 | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__id_bypass_src_1_2))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__do_bypass = 
        ((0U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs1)) 
         | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__id_bypass_src_0_1) 
            | (((IData)(tb_Rocket__DOT__dut__DOT___data_hazard_mem_T) 
                & (IData)(tb_Rocket__DOT__dut__DOT___T_28)) 
               | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__id_bypass_src_0_2))));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_3 = ((8U 
                                                 & ((~ 
                                                     (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                      >> 3U)) 
                                                    << 3U)) 
                                                | (IData)(__VdfgRegularize_h6e95ff9d_0_41));
    vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_115 
        = ((3U == (3U & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
           & ((3U == (3U & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                               >> 2U)))) & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_71)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_105 
        = ((3U == (3U & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
           & ((3U == (3U & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                               >> 2U)))) & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_72)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_47 
        = (IData)((((0x0000000fU == (0x0000001fU & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                    & (3U == (IData)(__VdfgRegularize_h6e95ff9d_0_20))) 
                   & (7U == (IData)(__VdfgRegularize_h6e95ff9d_0_46))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_13 
        = (IData)((((3U == (7U & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                    & (7U == (IData)(__VdfgRegularize_h6e95ff9d_0_41))) 
                   & (7U == (IData)(__VdfgRegularize_h6e95ff9d_0_19))));
    __VdfgRegularize_h6e95ff9d_0_78 = ((~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                           >> 3U)) 
                                       & ((7U == (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_43)) 
                                          & (7U == (IData)(__VdfgRegularize_h6e95ff9d_0_19))));
    __VdfgRegularize_h6e95ff9d_0_44 = ((0x00000010U 
                                        & ((~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                               >> 0x0000000bU)) 
                                           << 4U)) 
                                       | (((IData)(__VdfgRegularize_h6e95ff9d_0_19) 
                                           << 1U) | 
                                          (1U & (~ 
                                                 (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                  >> 0x0000000fU)))));
    tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_T_16 
        = ((8U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                  >> 0x00000019U)) | (IData)(__VdfgRegularize_h6e95ff9d_0_22));
    tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_137 
        = (IData)((((0x0800002fU == (0x0800007fU & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                    & (3U == (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_13))) 
                   & (7U == (IData)(__VdfgRegularize_h6e95ff9d_0_22))));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_57 = (((IData)(__VdfgRegularize_h6e95ff9d_0_14) 
                                                  << 3U) 
                                                 | (IData)(__VdfgRegularize_h6e95ff9d_0_22));
    __VdfgRegularize_h6e95ff9d_0_48 = ((0x00000040U 
                                        & ((~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                               >> 0x00000019U)) 
                                           << 6U)) 
                                       | (IData)(__VdfgRegularize_h6e95ff9d_0_47));
    vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_69 
        = (IData)(((0x0000000fU == (0x0000001fU & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                   & (IData)(__VdfgRegularize_h6e95ff9d_0_75)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_95 
        = (IData)((((0x0000501bU == (0x0000701fU & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                    & (0x0fU == (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_58))) 
                   & ((3U == (3U & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                       >> 0x00000019U)))) 
                      & (3U == (3U & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                         >> 5U)))))));
    __VdfgRegularize_h6e95ff9d_0_42 = ((0x00000010U 
                                        & ((~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                               >> 0x0000001aU)) 
                                           << 4U)) 
                                       | (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_58));
    __VdfgRegularize_h6e95ff9d_0_73 = ((3U == (3U & 
                                               (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                   >> 0x00000019U)))) 
                                       & ((0x0000000fU 
                                           == (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_58)) 
                                          & ((vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                              >> 0x0000000eU) 
                                             & (IData)(__VdfgRegularize_h6e95ff9d_0_74))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__ctrl_killm 
        = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__killm_common) 
           | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_xcpt));
    tb_Rocket__DOT__dut__DOT__alu__DOT___shin_T_41 
        = ((0xf0f0f0f0f0f0f0f0ULL & (tb_Rocket__DOT__dut__DOT__alu__DOT___shin_T_31 
                                     << 4U)) | (0x0f0f0f0f0f0f0f0fULL 
                                                & (tb_Rocket__DOT__dut__DOT__alu__DOT___shin_T_31 
                                                   >> 4U)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_159 
        = (IData)(((((0x00004003U == (0x00004007U & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                     & (0x0fU == (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_3))) 
                    & (3U == (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_7))) 
                   & (0x3fU == (IData)(__VdfgRegularize_h6e95ff9d_0_47))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_119 
        = ((vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
            >> 4U) & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_115));
    vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_109 
        = ((vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
            >> 4U) & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_105));
    vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_39 
        = ((7U == (7U & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
           & (IData)(__VdfgRegularize_h6e95ff9d_0_78));
    vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_37 
        = ((3U == (3U & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
           & (IData)(__VdfgRegularize_h6e95ff9d_0_78));
    tb_Rocket__DOT__dut__DOT__id_ctrl_decoder_decoded_hi_lo_74 
        = (((IData)(__VdfgRegularize_h6e95ff9d_0_44) 
            << 2U) | (IData)(__VdfgRegularize_h6e95ff9d_0_24));
    __VdfgRegularize_h6e95ff9d_0_45 = ((0x00000020U 
                                        & ((~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                               >> 0x0000000aU)) 
                                           << 5U)) 
                                       | (IData)(__VdfgRegularize_h6e95ff9d_0_44));
    tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_147 
        = (IData)((((0x0800002fU == (0x0800007fU & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                    & (3U == (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_13))) 
                   & (0x0fU == (IData)(tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_T_16))));
    tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_141 
        = (IData)((((0x0000002fU == (0x09f0403fU & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                    & (3U == (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_4))) 
                   & (0x0fU == (IData)(tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_T_16))));
    __VdfgRegularize_h6e95ff9d_0_30 = ((IData)(tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_139) 
                                       | (IData)(tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_137));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_49 = (((IData)(tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_137) 
                                                  << 1U) 
                                                 | (IData)(tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_139));
    vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_51 
        = (IData)((((0x00001013U == (0x04003013U & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                    & (0x1fU == (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_57))) 
                   & ((3U == (3U & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                       >> 2U)))) & 
                      (3U == (3U & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                       >> 5U)))))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_55 
        = (IData)((((0x0000101bU == (0x0000301fU & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                    & (0x1fU == (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_57))) 
                   & ((3U == (3U & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                       >> 5U)))) & 
                      (3U == (3U & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                       >> 0x00000019U)))))));
    tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_53 
        = (IData)(((((0x0000001bU == (0x0000001bU & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                     & (0x1fU == (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_57))) 
                    & (IData)(__VdfgRegularize_h6e95ff9d_0_74)) 
                   & (3U == (3U & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                      >> 0x00000019U))))));
    tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_49 
        = (IData)(((((0x00001003U == (0x04003003U & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                     & (0x1fU == (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_57))) 
                    & (IData)(__VdfgRegularize_h6e95ff9d_0_77)) 
                   & (3U == (3U & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                      >> 2U))))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_27 
        = (IData)((((0x00000033U == (0x04000073U & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                    & (0x1fU == (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_57))) 
                   & (3U == (3U & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                      >> 2U))))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_131 
        = (IData)((((0x02004033U == (0x06004033U & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                    & (0x1fU == (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_57))) 
                   & (IData)(__VdfgRegularize_h6e95ff9d_0_31)));
    tb_Rocket__DOT__dut__DOT__csr__DOT__decoded_lo_5 
        = ((0x00000020U & ((~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                               >> 0x0000001aU)) << 5U)) 
           | (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_57));
    vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_155 
        = (IData)(((((0x00000033U == (0x00000037U & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                     & (3U == (IData)(__VdfgRegularize_h6e95ff9d_0_12))) 
                    & (3U == (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_2))) 
                   & (0x7fU == (IData)(__VdfgRegularize_h6e95ff9d_0_48))));
    __VdfgRegularize_h6e95ff9d_0_70 = ((3U == (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_7)) 
                                       & ((vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                           >> 0x0000000eU) 
                                          & (0x0000007fU 
                                             == (IData)(__VdfgRegularize_h6e95ff9d_0_48))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_89 
        = (IData)(((((0x00004003U == (0x00004007U & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                     & (0x0fU == (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_3))) 
                    & (3U == (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_7))) 
                   & (0x1fU == (IData)(__VdfgRegularize_h6e95ff9d_0_42))));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_79 = (IData)(
                                                        ((((0x00000030U 
                                                            == 
                                                            (0x02000030U 
                                                             & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                                                           & (3U 
                                                              == (IData)(__VdfgRegularize_h6e95ff9d_0_12))) 
                                                          & (3U 
                                                             == (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_2))) 
                                                         & (0x1fU 
                                                            == (IData)(__VdfgRegularize_h6e95ff9d_0_42))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_93 
        = (IData)(((0x0000001bU == (0x0000001bU & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                   & (IData)(__VdfgRegularize_h6e95ff9d_0_73)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_99 
        = (IData)(((0x00000033U == (0x00000033U & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                   & (IData)(__VdfgRegularize_h6e95ff9d_0_73)));
    tb_Rocket__DOT__dut__DOT__alu__DOT___shin_T_51 
        = ((0xccccccccccccccccULL & (tb_Rocket__DOT__dut__DOT__alu__DOT___shin_T_41 
                                     << 2U)) | (0x3333333333333333ULL 
                                                & (tb_Rocket__DOT__dut__DOT__alu__DOT___shin_T_41 
                                                   >> 2U)));
    tb_Rocket__DOT__dut__DOT__id_ctrl_decoder_decoded_hi_lo_21 
        = ((0x00000080U & ((~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                               >> 8U)) << 7U)) | ((0x00000040U 
                                                   & ((~ 
                                                       (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                        >> 9U)) 
                                                      << 6U)) 
                                                  | (IData)(__VdfgRegularize_h6e95ff9d_0_45)));
    tb_Rocket__DOT__dut__DOT__id_ctrl_decoder_decoded_hi_lo_20 
        = (((IData)(__VdfgRegularize_h6e95ff9d_0_45) 
            << 1U) | (1U & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                               >> 0x00000010U))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_orMatrixOutputs_T_20 
        = ((IData)(tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_141) 
           | ((IData)(tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_137) 
              | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_69) 
                 | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_7) 
                    | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_5) 
                       | (IData)(((3U == (0x00001003U 
                                          & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                                  & (0x0000001fU == 
                                     (0x0000001fU & 
                                      (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                          >> 2U)))))))))));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_83 = ((((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_69) 
                                                   << 3U) 
                                                  | (((IData)(
                                                              ((0x8000000fU 
                                                                == 
                                                                (0x8000001fU 
                                                                 & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                                                               & (IData)(__VdfgRegularize_h6e95ff9d_0_75))) 
                                                      | (IData)(__VdfgRegularize_h6e95ff9d_0_30)) 
                                                     << 2U)) 
                                                 | ((((IData)(tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_147) 
                                                      | ((IData)(tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_139) 
                                                         | ((vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                             >> 0x0000001eU) 
                                                            & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_69)))) 
                                                     << 1U) 
                                                    | ((IData)(tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_147) 
                                                       | ((IData)(tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_19) 
                                                          | ((vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                              >> 0x0000001dU) 
                                                             & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_69))))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_orMatrixOutputs_T_1 
        = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_69) 
           | (IData)(__VdfgRegularize_h6e95ff9d_0_30));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_51 = (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_39) 
                                                  << 2U) 
                                                 | (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_41) 
                                                     << 1U) 
                                                    | (IData)(tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_49)));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_15 = (((IData)(tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_49) 
                                                  << 1U) 
                                                 | (IData)(tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_53));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__id_ctrl_decoder_decoded_lo_42 
        = ((0x00000040U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                           >> 8U)) | (IData)(tb_Rocket__DOT__dut__DOT__csr__DOT__decoded_lo_5));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__id_ctrl_decoder_decoded_lo_61 
        = ((0x00000040U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                           >> 0x00000013U)) | (IData)(tb_Rocket__DOT__dut__DOT__csr__DOT__decoded_lo_5));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__id_ctrl_decoder_decoded_lo_15 
        = ((0x00000040U & ((~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                               >> 0x00000019U)) << 6U)) 
           | (IData)(tb_Rocket__DOT__dut__DOT__csr__DOT__decoded_lo_5));
    vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_29 
        = (IData)(((((0x00000033U == (0x00000037U & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                     & (3U == (IData)(__VdfgRegularize_h6e95ff9d_0_12))) 
                    & (3U == (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_2))) 
                   & (0x3fU == (IData)(tb_Rocket__DOT__dut__DOT__csr__DOT__decoded_lo_5))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_161 
        = (IData)(((0x0000001bU == (0x0000005fU & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                   & (IData)(__VdfgRegularize_h6e95ff9d_0_70)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_163 
        = (IData)((((0x00000033U == (0x00000033U & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                    & (IData)(__VdfgRegularize_h6e95ff9d_0_31)) 
                   & (IData)(__VdfgRegularize_h6e95ff9d_0_70)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_23 
        = (IData)(((3U == (7U & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                   & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_79)));
    __VdfgRegularize_h6e95ff9d_0_50 = ((((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_89) 
                                         << 5U) | (
                                                   ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_93) 
                                                    << 4U) 
                                                   | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_99) 
                                                      << 3U))) 
                                       | (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_131) 
                                           << 2U) | (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_49)));
    tb_Rocket__DOT__dut__DOT__alu__DOT__shin = ((IData)(tb_Rocket__DOT__dut__DOT__alu__DOT___shin_T_2)
                                                 ? tb_Rocket__DOT__dut__DOT__alu__DOT__shin_r
                                                 : 
                                                ((0xaaaaaaaaaaaaaaaaULL 
                                                  & (tb_Rocket__DOT__dut__DOT__alu__DOT___shin_T_51 
                                                     << 1U)) 
                                                 | (0x5555555555555555ULL 
                                                    & (tb_Rocket__DOT__dut__DOT__alu__DOT___shin_T_51 
                                                       >> 1U))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_orMatrixOutputs_T_11 
        = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_131) 
           | ((3U == (3U & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
              & ((IData)((((0x00000030U == (0x00002034U 
                                            & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                           & (3U == (IData)(__VdfgRegularize_h6e95ff9d_0_12))) 
                          & (0x7fU == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__id_ctrl_decoder_decoded_lo_61)))) 
                 | (IData)((((0x02000030U == (0x06000070U 
                                              & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                             & (0x1fU == (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_57))) 
                            & (3U == (3U & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                               >> 2U)))))))));
    tb_Rocket__DOT__dut__DOT__id_ctrl_decoder_decoded_lo_21 
        = (((((2U & ((~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                         >> 0x00000011U)) << 1U)) | 
              (1U & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                        >> 0x00000012U)))) << 0x0000000cU) 
            | (((2U & ((~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                           >> 0x00000013U)) << 1U)) 
                | (1U & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                            >> 0x00000015U)))) << 0x0000000aU)) 
           | ((0x00000200U & ((~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                  >> 0x00000016U)) 
                              << 9U)) | ((0x00000100U 
                                          & ((~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                 >> 0x00000017U)) 
                                             << 8U)) 
                                         | ((0x00000080U 
                                             & ((~ 
                                                 (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                  >> 0x00000018U)) 
                                                << 7U)) 
                                            | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__id_ctrl_decoder_decoded_lo_15)))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_orMatrixOutputs_T_48 
        = ((IData)(__VdfgRegularize_h6e95ff9d_0_30) 
           | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_131) 
              | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_99) 
                 | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_87) 
                    | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_69) 
                       | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_29) 
                          | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_27) 
                             | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_23) 
                                | ((IData)((((0x00000033U 
                                              == (0x00000077U 
                                                  & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                                             & (0x1fU 
                                                == (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_57))) 
                                            & ((3U 
                                                == 
                                                (3U 
                                                 & (~ 
                                                    (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                     >> 0x0000000dU)))) 
                                               & (3U 
                                                  == 
                                                  (3U 
                                                   & (~ 
                                                      (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                       >> 0x00000019U))))))) 
                                   | ((IData)(((0x00000023U 
                                                == 
                                                (0x00000023U 
                                                 & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                                               & ((7U 
                                                   == 
                                                   (7U 
                                                    & (~ 
                                                       (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                        >> 2U)))) 
                                                  & (3U 
                                                     == 
                                                     (3U 
                                                      & (~ 
                                                         (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                          >> 0x0000000dU))))))) 
                                      | (IData)(tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_19)))))))))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_orMatrixOutputs_T_9 
        = ((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_8) 
           | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_9) 
              | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_13) 
                 | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_15) 
                    | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_23) 
                       | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_27) 
                          | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_29) 
                             | ((0U != (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_51)) 
                                | ((IData)(tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_53) 
                                   | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_63) 
                                      | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_65) 
                                         | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_69) 
                                            | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_75) 
                                               | (0U 
                                                  != (IData)(__VdfgRegularize_h6e95ff9d_0_50)))))))))))))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_orMatrixOutputs_T_38 
        = ((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_8) 
           | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_7) 
              | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_13) 
                 | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_23) 
                    | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_27) 
                       | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_29) 
                          | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_37) 
                             | ((0U != (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_15)) 
                                | (((3U == (3U & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                                    & ((3U == (3U & 
                                               (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                   >> 2U)))) 
                                       & ((3U == (IData)(__VdfgRegularize_h6e95ff9d_0_0)) 
                                          & (7U == (IData)(__VdfgRegularize_h6e95ff9d_0_46))))) 
                                   | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_65) 
                                      | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_69) 
                                         | ((IData)(
                                                    ((((0x00000013U 
                                                        == 
                                                        (0x00000013U 
                                                         & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                                                       & (3U 
                                                          == (IData)(__VdfgRegularize_h6e95ff9d_0_0))) 
                                                      & (3U 
                                                         == (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_13))) 
                                                     & (3U 
                                                        == 
                                                        (3U 
                                                         & (~ 
                                                            (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                             >> 2U)))))) 
                                            | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_87) 
                                               | (0U 
                                                  != (IData)(__VdfgRegularize_h6e95ff9d_0_50)))))))))))))));
    __Vtemp_31[0U] = (IData)(tb_Rocket__DOT__dut__DOT__alu__DOT__shin);
    __Vtemp_31[1U] = (IData)((tb_Rocket__DOT__dut__DOT__alu__DOT__shin 
                              >> 0x00000020U));
    __Vtemp_31[2U] = (IData)((((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_alu_fn) 
                               >> 3U) & (tb_Rocket__DOT__dut__DOT__alu__DOT__shin 
                                         >> 0x0000003fU)));
    VL_SHIFTRS_WWI(65,65,6, __Vtemp_32, __Vtemp_31, 
                   ((((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_alu_dw) 
                      & (IData)((tb_Rocket__DOT__dut__DOT__alu_io_in2 
                                 >> 5U))) << 5U) | 
                    (0x0000001fU & (IData)(tb_Rocket__DOT__dut__DOT__alu_io_in2))));
    tb_Rocket__DOT__dut__DOT__alu__DOT__shout_r = (
                                                   ((QData)((IData)(__Vtemp_32[1U])) 
                                                    << 0x00000020U) 
                                                   | (QData)((IData)(__Vtemp_32[0U])));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__id_ctrl_decoder_23 
        = ((((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_75) 
             | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_63) 
                | ((vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                    >> 4U) & ((IData)(((((3U == (IData)(__VdfgRegularize_h6e95ff9d_0_0)) 
                                         & (0U == (0x00000780U 
                                                   & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits))) 
                                        & (0x7fU == (IData)(tb_Rocket__DOT__dut__DOT__id_ctrl_decoder_decoded_hi_lo_74))) 
                                       & (0x3fffU == (IData)(tb_Rocket__DOT__dut__DOT__id_ctrl_decoder_decoded_lo_82)))) 
                              | ((IData)(((((3U == (IData)(__VdfgRegularize_h6e95ff9d_0_0)) 
                                            & (0U == 
                                               (0x00000780U 
                                                & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits))) 
                                           & (0x7fU 
                                              == (IData)(tb_Rocket__DOT__dut__DOT__id_ctrl_decoder_decoded_hi_lo_74))) 
                                          & (0x3fffU 
                                             == (IData)(tb_Rocket__DOT__dut__DOT__id_ctrl_decoder_decoded_lo_75)))) 
                                 | (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                    & ((IData)(((((3U 
                                                   == (IData)(__VdfgRegularize_h6e95ff9d_0_0)) 
                                                  & (0U 
                                                     == 
                                                     (0x00000380U 
                                                      & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits))) 
                                                 & (0x7fU 
                                                    == (IData)(tb_Rocket__DOT__dut__DOT__id_ctrl_decoder_decoded_hi_lo_20))) 
                                                & (0x3fffU 
                                                   == (IData)(tb_Rocket__DOT__dut__DOT__id_ctrl_decoder_decoded_lo_71)))) 
                                       | (IData)(((
                                                   ((3U 
                                                     == (IData)(__VdfgRegularize_h6e95ff9d_0_0)) 
                                                    & (0U 
                                                       == 
                                                       (0x00000380U 
                                                        & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits))) 
                                                   & (0x7fU 
                                                      == (IData)(tb_Rocket__DOT__dut__DOT__id_ctrl_decoder_decoded_hi_lo_20))) 
                                                  & (0x3fffU 
                                                     == (IData)(tb_Rocket__DOT__dut__DOT__id_ctrl_decoder_decoded_lo_21))))))))))) 
            << 2U) | (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_75) 
                       << 1U) | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_63)));
    tb_Rocket__DOT__dut__DOT___T_137 = ((0U != (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs2)) 
                                        & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_orMatrixOutputs_T_48));
    tb_Rocket__DOT__dut__DOT___T_139 = ((0U != (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rd)) 
                                        & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_orMatrixOutputs_T_9));
    tb_Rocket__DOT__dut__DOT___T_135 = ((0U != (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs1)) 
                                        & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_orMatrixOutputs_T_38));
    tb_Rocket__DOT__dut__DOT__alu__DOT___shout_l_T_8 
        = ((tb_Rocket__DOT__dut__DOT__alu__DOT__shout_r 
            << 0x00000020U) | (tb_Rocket__DOT__dut__DOT__alu__DOT__shout_r 
                               >> 0x00000020U));
    tb_Rocket__DOT__dut__DOT___id_csr_en_T_3 = ((6U 
                                                 == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__id_ctrl_decoder_23)) 
                                                | (7U 
                                                   == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__id_ctrl_decoder_23)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__data_hazard_mem 
        = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_ctrl_wxd) 
           & (((IData)(tb_Rocket__DOT__dut__DOT___data_hazard_mem_T) 
               & (IData)(tb_Rocket__DOT__dut__DOT___T_135)) 
              | ((((0x0000001fU & (vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_inst 
                                   >> 7U)) == (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rd)) 
                  & (IData)(tb_Rocket__DOT__dut__DOT___T_139)) 
                 | ((IData)(tb_Rocket__DOT__dut__DOT___data_hazard_mem_T_2) 
                    & (IData)(tb_Rocket__DOT__dut__DOT___T_137)))));
    tb_Rocket__DOT__dut__DOT__alu__DOT___shout_l_T_18 
        = ((0xffff0000ffff0000ULL & (tb_Rocket__DOT__dut__DOT__alu__DOT___shout_l_T_8 
                                     << 0x00000010U)) 
           | (0x0000ffff0000ffffULL & (tb_Rocket__DOT__dut__DOT__alu__DOT___shout_l_T_8 
                                       >> 0x00000010U)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__id_csr_en = 
        ((5U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__id_ctrl_decoder_23)) 
         | (IData)(tb_Rocket__DOT__dut__DOT___id_csr_en_T_3));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__id_csr_ren 
        = ((IData)(tb_Rocket__DOT__dut__DOT___id_csr_en_T_3) 
           & (0U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs1)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__ctrl_stalld 
        = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__id_reg_pause) 
           | ((((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_47) 
                | (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__id_reg_fence) 
                    & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_orMatrixOutputs_T_20)) 
                   | ((vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                       >> 0x00000019U) & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_orMatrixOutputs_T_1)))) 
               & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__id_mem_busy)) 
              | ((((~ ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT___T_21) 
                       | (0U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__state)))) 
                   | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div_io_req_valid)) 
                  & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_orMatrixOutputs_T_11)) 
                 | (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__blocked) 
                     & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_orMatrixOutputs_T_20)) 
                    | (((IData)(tb_Rocket__DOT__dut__DOT___T_27) 
                        & (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_jalr) 
                            | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_mem) 
                               | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_mul) 
                                  | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_div) 
                                     | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_fp) 
                                        | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_rocc) 
                                           | (0U != (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_csr)))))))) 
                           & (((IData)(tb_Rocket__DOT__dut__DOT___data_hazard_ex_T) 
                               & (IData)(tb_Rocket__DOT__dut__DOT___T_135)) 
                              | ((((0x0000001fU & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_inst 
                                                   >> 7U)) 
                                   == (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rd)) 
                                  & (IData)(tb_Rocket__DOT__dut__DOT___T_139)) 
                                 | ((IData)(tb_Rocket__DOT__dut__DOT___data_hazard_ex_T_2) 
                                    & (IData)(tb_Rocket__DOT__dut__DOT___T_137)))))) 
                       | (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_valid) 
                           & (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_ctrl_div) 
                               | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_ctrl_fp) 
                                  | ((0U != (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_ctrl_csr)) 
                                     | (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_ctrl_mem) 
                                         & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_slow_bypass)) 
                                        | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_ctrl_mul) 
                                           | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_ctrl_rocc)))))) 
                              & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__data_hazard_mem))) 
                          | (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_valid) 
                              & ((IData)(tb_Rocket__DOT__dut__DOT__wb_set_sboard) 
                                 & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_ctrl_wxd) 
                                    & ((((0x0000001fU 
                                          & (vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
                                             >> 7U)) 
                                         == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs1)) 
                                        & (IData)(tb_Rocket__DOT__dut__DOT___T_135)) 
                                       | ((((0x0000001fU 
                                             & (vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
                                                >> 7U)) 
                                            == (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rd)) 
                                           & (IData)(tb_Rocket__DOT__dut__DOT___T_139)) 
                                          | (((0x0000001fU 
                                               & (vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
                                                  >> 7U)) 
                                              == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs2)) 
                                             & (IData)(tb_Rocket__DOT__dut__DOT___T_137))))))) 
                             | ((((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_valid) 
                                  | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_valid) 
                                     | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_valid))) 
                                 & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr_io_singleStep)) 
                                | (((IData)(tb_Rocket__DOT__dut__DOT___T_135) 
                                    & ((~ (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__req_tag) 
                                            == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs1)) 
                                           & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT___T_21))) 
                                       & ((0xfffffffeU 
                                           & vlSelfRef.tb_Rocket__DOT__dut__DOT___r) 
                                          >> (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs1)))) 
                                   | (((IData)(tb_Rocket__DOT__dut__DOT___T_137) 
                                       & ((~ (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__req_tag) 
                                               == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs2)) 
                                              & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT___T_21))) 
                                          & ((0xfffffffeU 
                                              & vlSelfRef.tb_Rocket__DOT__dut__DOT___r) 
                                             >> (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs2)))) 
                                      | (((IData)(tb_Rocket__DOT__dut__DOT___T_139) 
                                          & ((~ (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__req_tag) 
                                                  == (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rd)) 
                                                 & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT___T_21))) 
                                             & ((0xfffffffeU 
                                                 & vlSelfRef.tb_Rocket__DOT__dut__DOT___r) 
                                                >> (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rd)))) 
                                         | (IData)(tb_Rocket__DOT__dut__DOT__csr_io_csr_stall))))))))))));
    tb_Rocket__DOT__dut__DOT__alu__DOT___shout_l_T_28 
        = ((0xff00ff00ff00ff00ULL & (tb_Rocket__DOT__dut__DOT__alu__DOT___shout_l_T_18 
                                     << 8U)) | (0x00ff00ff00ff00ffULL 
                                                & (tb_Rocket__DOT__dut__DOT__alu__DOT___shout_l_T_18 
                                                   >> 8U)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__id_illegal_insn 
        = (1U & ((IData)((((((3U == (3U & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in)) 
                             & (4U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__id_ctrl_decoder_23))) 
                            & (0x48000000U == (0x48000000U 
                                               & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits))) 
                           & (~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_debug))) 
                          & ((IData)((0x40000000U == 
                                      (0xc0000000U 
                                       & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits))) 
                             | (IData)(((0x30000000U 
                                         == (0x30000000U 
                                             & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                                        & ((3U == (3U 
                                                   & (~ 
                                                      (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                       >> 0x0000001eU)))) 
                                           & (0x0000003fU 
                                              == (0x0000003fU 
                                                  & (~ 
                                                     (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                      >> 0x00000016U)))))))))) 
                 | (((((~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__id_csr_ren)) 
                       & (3U == (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                 >> 0x0000001eU))) 
                      | ((~ (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[1952U] 
                             | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[1953U] 
                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[1954U] 
                                   | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[1955U] 
                                      | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[769U] 
                                         | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[768U] 
                                            | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[773U] 
                                               | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[836U] 
                                                  | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[772U] 
                                                     | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[832U] 
                                                        | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[833U] 
                                                           | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[835U] 
                                                              | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[834U] 
                                                                 | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[3860U] 
                                                                    | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[1968U] 
                                                                       | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[1969U] 
                                                                          | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[1970U] 
                                                                             | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[800U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[2816U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[2818U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[803U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[2819U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[804U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[2820U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[805U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[2821U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[806U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[2822U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[807U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[808U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[2823U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[2824U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[809U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[2825U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[810U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[2826U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[811U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[2827U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[812U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[2828U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[813U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[2829U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[814U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[2830U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[815U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[2831U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[816U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[2832U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[817U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[2833U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[818U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[2834U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[819U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[2835U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[820U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[2836U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[821U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[2837U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[822U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[823U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[2838U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[2839U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[824U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[2840U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[825U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[2841U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[826U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[2842U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[827U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[2843U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[828U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[2844U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[829U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[2845U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[830U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[2846U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[831U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[2847U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[928U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[930U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[944U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[945U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[946U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[947U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[948U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[949U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[950U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[951U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[952U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[953U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[954U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[955U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[956U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[957U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[958U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[959U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[1985U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[3858U] 
                                                                                | (vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[3857U] 
                                                                                | vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0[3859U])))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))) 
                         | (((~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_debug)) 
                             & (0x60000000U == (0xe4000000U 
                                                & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits))) 
                            & (3U == (3U & ((vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                             >> 0x00000018U) 
                                            & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                               >> 0x0000001bU))))))) 
                     & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__id_csr_en)) 
                    | (((~ (IData)((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_misa 
                                    >> 2U))) & (3U 
                                                != 
                                                (3U 
                                                 & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in))) 
                       | (((~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_misa)) 
                           & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_orMatrixOutputs_T_1)) 
                          | ((~ ((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_8) 
                                 | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_7) 
                                    | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_11) 
                                       | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_13) 
                                          | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_15) 
                                             | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_23) 
                                                | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_27) 
                                                   | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_29) 
                                                      | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_37) 
                                                         | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_41) 
                                                            | ((IData)(
                                                                       (((((0x00000013U 
                                                                            == 
                                                                            (0x00010093U 
                                                                             & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                                                                           & (3U 
                                                                              == (IData)(__VdfgRegularize_h6e95ff9d_0_0))) 
                                                                          & (0xffU 
                                                                             == (IData)(tb_Rocket__DOT__dut__DOT__id_ctrl_decoder_decoded_hi_lo_21))) 
                                                                         & (0x3fffU 
                                                                            == (IData)(tb_Rocket__DOT__dut__DOT__id_ctrl_decoder_decoded_lo_21))) 
                                                                        & (3U 
                                                                           == 
                                                                           (3U 
                                                                            & (~ 
                                                                               (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                                                >> 2U)))))) 
                                                               | ((0U 
                                                                   != (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_15)) 
                                                                  | (((3U 
                                                                       == 
                                                                       (3U 
                                                                        & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                                                                      & ((3U 
                                                                          == 
                                                                          (3U 
                                                                           & (~ 
                                                                              (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                                               >> 2U)))) 
                                                                         & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_76))) 
                                                                     | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_65) 
                                                                        | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_69) 
                                                                           | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_75) 
                                                                              | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_87) 
                                                                                | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_89) 
                                                                                | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_93) 
                                                                                | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_99) 
                                                                                | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_131) 
                                                                                | ((IData)(tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_137) 
                                                                                | ((IData)(tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_141) 
                                                                                | ((IData)(
                                                                                (((((0x00000013U 
                                                                                == 
                                                                                (0x00010093U 
                                                                                & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                                                                                & (3U 
                                                                                == (IData)(__VdfgRegularize_h6e95ff9d_0_0))) 
                                                                                & (0xffU 
                                                                                == (IData)(tb_Rocket__DOT__dut__DOT__id_ctrl_decoder_decoded_hi_lo_21))) 
                                                                                & (0x3fffU 
                                                                                == (IData)(tb_Rocket__DOT__dut__DOT__id_ctrl_decoder_decoded_lo_71))) 
                                                                                & (3U 
                                                                                == 
                                                                                (3U 
                                                                                & (~ 
                                                                                (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                                                >> 2U)))))) 
                                                                                | ((IData)(
                                                                                ((((((0x00000013U 
                                                                                == 
                                                                                (0x00000093U 
                                                                                & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                                                                                & (3U 
                                                                                == (IData)(__VdfgRegularize_h6e95ff9d_0_0))) 
                                                                                & (0xffU 
                                                                                == (IData)(tb_Rocket__DOT__dut__DOT__id_ctrl_decoder_decoded_hi_lo_21))) 
                                                                                & (3U 
                                                                                == (IData)(__VdfgRegularize_h6e95ff9d_0_24))) 
                                                                                & (0x3fffU 
                                                                                == (IData)(tb_Rocket__DOT__dut__DOT__id_ctrl_decoder_decoded_lo_75))) 
                                                                                & (3U 
                                                                                == 
                                                                                (3U 
                                                                                & (~ 
                                                                                (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits 
                                                                                >> 2U)))))) 
                                                                                | (IData)(
                                                                                ((((((3U 
                                                                                == 
                                                                                (0x00000087U 
                                                                                & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits)) 
                                                                                & (3U 
                                                                                == (IData)(__VdfgRegularize_h6e95ff9d_0_0))) 
                                                                                & (0xffU 
                                                                                == (IData)(tb_Rocket__DOT__dut__DOT__id_ctrl_decoder_decoded_hi_lo_21))) 
                                                                                & (3U 
                                                                                == (IData)(__VdfgRegularize_h6e95ff9d_0_24))) 
                                                                                & (0x3fffU 
                                                                                == (IData)(tb_Rocket__DOT__dut__DOT__id_ctrl_decoder_decoded_lo_82))) 
                                                                                & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_80))))))))))))))))))))))))))))) 
                             | ((~ (IData)((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_misa 
                                            >> 0x0000000cU))) 
                                & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_orMatrixOutputs_T_11))))))));
    tb_Rocket__DOT__dut__DOT__alu__DOT___shout_l_T_38 
        = ((0xf0f0f0f0f0f0f0f0ULL & (tb_Rocket__DOT__dut__DOT__alu__DOT___shout_l_T_28 
                                     << 4U)) | (0x0f0f0f0f0f0f0f0fULL 
                                                & (tb_Rocket__DOT__dut__DOT__alu__DOT___shout_l_T_28 
                                                   >> 4U)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__id_xcpt = (
                                                   (((((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr_io_interrupt) 
                                                       | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__bpu_io_debug_if)) 
                                                      | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__bpu_io_xcpt_if)) 
                                                     | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf_io_inst_0_bits_xcpt0_ae_inst)) 
                                                    | (0U 
                                                       != (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT___io_inst_0_bits_xcpt1_T_5))) 
                                                   | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__id_illegal_insn));
    tb_Rocket__DOT__dut__DOT__alu__DOT___shout_l_T_48 
        = ((0xccccccccccccccccULL & (tb_Rocket__DOT__dut__DOT__alu__DOT___shout_l_T_38 
                                     << 2U)) | (0x3333333333333333ULL 
                                                & (tb_Rocket__DOT__dut__DOT__alu__DOT___shout_l_T_38 
                                                   >> 2U)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__alu__DOT__out 
        = (((0U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_alu_fn)) 
            | (0x0aU == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_alu_fn)))
            ? vlSelfRef.tb_Rocket__DOT__dut__DOT__alu_io_adder_out
            : ((QData)((IData)(((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__alu__DOT__slt) 
                                & (0x0cU <= (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_alu_fn))))) 
               | ((tb_Rocket__DOT__dut__DOT__alu_io_in2 
                   & (tb_Rocket__DOT__dut__DOT__alu_io_in1 
                      & (- (QData)((IData)(((6U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_alu_fn)) 
                                            | (7U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_alu_fn)))))))) 
                  | ((vlSelfRef.tb_Rocket__DOT__dut__DOT__alu__DOT__in1_xor_in2 
                      & (- (QData)((IData)(((6U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_alu_fn)) 
                                            | (4U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_alu_fn))))))) 
                     | ((tb_Rocket__DOT__dut__DOT__alu__DOT__shout_r 
                         & (- (QData)((IData)(tb_Rocket__DOT__dut__DOT__alu__DOT___shin_T_2)))) 
                        | ((- (QData)((IData)((1U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_alu_fn))))) 
                           & ((0xaaaaaaaaaaaaaaaaULL 
                               & (tb_Rocket__DOT__dut__DOT__alu__DOT___shout_l_T_48 
                                  << 1U)) | (0x5555555555555555ULL 
                                             & (tb_Rocket__DOT__dut__DOT__alu__DOT___shout_l_T_48 
                                                >> 1U)))))))));
}

void Vtb_Rocket___024root___timing_ready(Vtb_Rocket___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_Rocket___024root___timing_ready\n"); );
    Vtb_Rocket__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VtrigSched_h7b2495ab__0.ready("@(posedge tb_Rocket.clk)");
    }
}

void Vtb_Rocket___024root___timing_resume(Vtb_Rocket___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_Rocket___024root___timing_resume\n"); );
    Vtb_Rocket__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VtrigSched_h7b2495ab__0.moveToResumeQueue(
                                                          "@(posedge tb_Rocket.clk)");
    vlSelfRef.__VtrigSched_h7b2495ab__0.resume("@(posedge tb_Rocket.clk)");
    if ((2ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VdlySched.resume();
    }
}

void Vtb_Rocket___024root___trigger_orInto__act_vec_vec(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_Rocket___024root___trigger_orInto__act_vec_vec\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = (out[n] | in[n]);
        n = ((IData)(1U) + n);
    } while ((0U >= n));
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_Rocket___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool Vtb_Rocket___024root___eval_phase__act(Vtb_Rocket___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_Rocket___024root___eval_phase__act\n"); );
    Vtb_Rocket__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VactExecute;
    // Body
    {
        // Inlined CFunc: _eval_triggers_vec__act
        vlSelfRef.__VactTriggered[0U] = (QData)((IData)(
                                                        ((vlSelfRef.__VdlySched.awaitingCurrentTime() 
                                                          << 1U) 
                                                         | ((IData)(vlSelfRef.tb_Rocket__DOT__clk) 
                                                            & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_Rocket__DOT__clk__0))))));
        vlSelfRef.__Vtrigprevexpr___TOP__tb_Rocket__DOT__clk__0 
            = vlSelfRef.tb_Rocket__DOT__clk;
    }
    Vtb_Rocket___024root___timing_ready(vlSelf);
    Vtb_Rocket___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VactTriggered, vlSelfRef.__VactTriggeredAcc);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtb_Rocket___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
    Vtb_Rocket___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    __VactExecute = Vtb_Rocket___024root___trigger_anySet__act(vlSelfRef.__VactTriggered);
    if (__VactExecute) {
        vlSelfRef.__VactTriggeredAcc.fill(0ULL);
        Vtb_Rocket___024root___timing_resume(vlSelf);
        {
            // Inlined CFunc: _eval_act
            if ((3ULL & vlSelfRef.__VactTriggered[0U])) {
                {
                    // Inlined CFunc: _act_comb__TOP__0
                    CData/*3:0*/ __Vinline_0__eval_act___Vinline_0__act_comb__TOP__0_tb_Rocket__DOT__dut__DOT__ibuf__DOT___valid_T_2;
                    __Vinline_0__eval_act___Vinline_0__act_comb__TOP__0_tb_Rocket__DOT__dut__DOT__ibuf__DOT___valid_T_2 = 0;
                    CData/*0:0*/ __Vinline_0__eval_act___Vinline_0__act_comb__TOP__0_tb_Rocket__DOT__dut__DOT__ibuf__DOT__full_insn;
                    __Vinline_0__eval_act___Vinline_0__act_comb__TOP__0_tb_Rocket__DOT__dut__DOT__ibuf__DOT__full_insn = 0;
                    vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf_io_imem_valid 
                        = (1U & (~ (IData)(vlSelfRef.tb_Rocket__DOT__red_d)));
                    __Vinline_0__eval_act___Vinline_0__act_comb__TOP__0_tb_Rocket__DOT__dut__DOT__ibuf__DOT___valid_T_2 
                        = (0x0000000fU & (((IData)(1U) 
                                           << (3U & 
                                               ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__nBufValid) 
                                                + (
                                                   ((IData)(2U) 
                                                    - 
                                                    (1U 
                                                     & (IData)(
                                                               (vlSelfRef.tb_Rocket__DOT__fpc 
                                                                >> 1U)))) 
                                                   & (- (IData)(
                                                                (1U 
                                                                 & (~ (IData)(vlSelfRef.tb_Rocket__DOT__red_d))))))))) 
                                          - (IData)(1U)));
                    __Vinline_0__eval_act___Vinline_0__act_comb__TOP__0_tb_Rocket__DOT__dut__DOT__ibuf__DOT__full_insn 
                        = (1U & ((3U != (3U & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in)) 
                                 | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__buf_replay) 
                                    | (__Vinline_0__eval_act___Vinline_0__act_comb__TOP__0_tb_Rocket__DOT__dut__DOT__ibuf__DOT___valid_T_2 
                                       >> 1U))));
                    vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf_io_inst_0_valid 
                        = (__Vinline_0__eval_act___Vinline_0__act_comb__TOP__0_tb_Rocket__DOT__dut__DOT__ibuf__DOT___valid_T_2 
                           & __Vinline_0__eval_act___Vinline_0__act_comb__TOP__0_tb_Rocket__DOT__dut__DOT__ibuf__DOT__full_insn);
                    vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__nReady 
                        = (((3U != (3U & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in))
                             ? 1U : 2U) & (- (IData)(__Vinline_0__eval_act___Vinline_0__act_comb__TOP__0_tb_Rocket__DOT__dut__DOT__ibuf__DOT__full_insn)));
                    vlSelfRef.tb_Rocket__DOT__dut__DOT__ctrl_killd 
                        = (1U & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf_io_inst_0_bits_replay) 
                                 | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf_io_kill) 
                                    | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ctrl_stalld) 
                                       | ((~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf_io_inst_0_valid)) 
                                          | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr_io_interrupt))))));
                    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_98 
                        = (((~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__take_pc_wb)) 
                            & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_valid)) 
                           & (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_pc_valid)
                                ? (vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_pc 
                                   != vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_npc)
                                : (~ (((~ (IData)(vlSelfRef.tb_Rocket__DOT__red_d)) 
                                       | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf_io_inst_0_valid)) 
                                      & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf_io_pc 
                                         == vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_npc)))) 
                              & ((~ ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_ctrl_branch) 
                                     | (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_69))) 
                                 | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_cfi_taken))));
                    vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT___io_imem_ready_T 
                        = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__nReady) 
                           >= (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__nBufValid));
                    vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__nICReady 
                        = (3U & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__nReady) 
                                 - (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__nBufValid)));
                    vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT___io_imem_ready_T_4 
                        = (3U & (((IData)(2U) - (1U 
                                                 & (IData)(
                                                           (vlSelfRef.tb_Rocket__DOT__fpc 
                                                            >> 1U)))) 
                                 - (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__nICReady)));
                    vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf_io_imem_ready 
                        = ((~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ctrl_stalld)) 
                           & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT___io_imem_ready_T) 
                              & ((1U >= (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT___io_imem_ready_T_4)) 
                                 | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__nICReady) 
                                    >= (3U & ((IData)(2U) 
                                              - (1U 
                                                 & (IData)(
                                                           (vlSelfRef.tb_Rocket__DOT__fpc 
                                                            >> 1U)))))))));
                }
            }
        }
    }
    return (__VactExecute);
}

bool Vtb_Rocket___024root___eval_phase__inact(Vtb_Rocket___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_Rocket___024root___eval_phase__inact\n"); );
    Vtb_Rocket__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VinactExecute;
    // Body
    __VinactExecute = vlSelfRef.__VdlySched.awaitingZeroDelay();
    if (__VinactExecute) {
        VL_FATAL_MT("/home/zhangzijie/pyCircuit/designs/Rocket-pyc/tests/tb/tb_rocket_pgm.v", 12, "", "ZERODLY: Design Verilated with '--no-sched-zero-delay', but #0 delay executed at runtime");
    }
    return (__VinactExecute);
}

void Vtb_Rocket___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_Rocket___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vtb_Rocket___024root___eval_phase__nba(Vtb_Rocket___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_Rocket___024root___eval_phase__nba\n"); );
    Vtb_Rocket__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vtb_Rocket___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        {
            // Inlined CFunc: _eval_nba
            if ((1ULL & vlSelfRef.__VnbaTriggered[0U])) {
                Vtb_Rocket___024root___nba_sequent__TOP__0(vlSelf);
            }
            if ((3ULL & vlSelfRef.__VnbaTriggered[0U])) {
                {
                    // Inlined CFunc: _nba_comb__TOP__0
                    CData/*3:0*/ __Vinline_0__eval_nba___Vinline_0__nba_comb__TOP__0_tb_Rocket__DOT__dut__DOT__ibuf__DOT___valid_T_2;
                    __Vinline_0__eval_nba___Vinline_0__nba_comb__TOP__0_tb_Rocket__DOT__dut__DOT__ibuf__DOT___valid_T_2 = 0;
                    CData/*0:0*/ __Vinline_0__eval_nba___Vinline_0__nba_comb__TOP__0_tb_Rocket__DOT__dut__DOT__ibuf__DOT__full_insn;
                    __Vinline_0__eval_nba___Vinline_0__nba_comb__TOP__0_tb_Rocket__DOT__dut__DOT__ibuf__DOT__full_insn = 0;
                    vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf_io_imem_valid 
                        = (1U & (~ (IData)(vlSelfRef.tb_Rocket__DOT__red_d)));
                    __Vinline_0__eval_nba___Vinline_0__nba_comb__TOP__0_tb_Rocket__DOT__dut__DOT__ibuf__DOT___valid_T_2 
                        = (0x0000000fU & (((IData)(1U) 
                                           << (3U & 
                                               ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__nBufValid) 
                                                + (
                                                   ((IData)(2U) 
                                                    - 
                                                    (1U 
                                                     & (IData)(
                                                               (vlSelfRef.tb_Rocket__DOT__fpc 
                                                                >> 1U)))) 
                                                   & (- (IData)(
                                                                (1U 
                                                                 & (~ (IData)(vlSelfRef.tb_Rocket__DOT__red_d))))))))) 
                                          - (IData)(1U)));
                    __Vinline_0__eval_nba___Vinline_0__nba_comb__TOP__0_tb_Rocket__DOT__dut__DOT__ibuf__DOT__full_insn 
                        = (1U & ((3U != (3U & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in)) 
                                 | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__buf_replay) 
                                    | (__Vinline_0__eval_nba___Vinline_0__nba_comb__TOP__0_tb_Rocket__DOT__dut__DOT__ibuf__DOT___valid_T_2 
                                       >> 1U))));
                    vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf_io_inst_0_valid 
                        = (__Vinline_0__eval_nba___Vinline_0__nba_comb__TOP__0_tb_Rocket__DOT__dut__DOT__ibuf__DOT___valid_T_2 
                           & __Vinline_0__eval_nba___Vinline_0__nba_comb__TOP__0_tb_Rocket__DOT__dut__DOT__ibuf__DOT__full_insn);
                    vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__nReady 
                        = (((3U != (3U & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in))
                             ? 1U : 2U) & (- (IData)(__Vinline_0__eval_nba___Vinline_0__nba_comb__TOP__0_tb_Rocket__DOT__dut__DOT__ibuf__DOT__full_insn)));
                    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_98 
                        = (((~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__take_pc_wb)) 
                            & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_valid)) 
                           & (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_pc_valid)
                                ? (vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_pc 
                                   != vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_npc)
                                : (~ (((~ (IData)(vlSelfRef.tb_Rocket__DOT__red_d)) 
                                       | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf_io_inst_0_valid)) 
                                      & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf_io_pc 
                                         == vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_npc)))) 
                              & ((~ ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_ctrl_branch) 
                                     | (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_69))) 
                                 | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_cfi_taken))));
                    vlSelfRef.tb_Rocket__DOT__dut__DOT__ctrl_killd 
                        = (1U & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf_io_inst_0_bits_replay) 
                                 | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf_io_kill) 
                                    | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ctrl_stalld) 
                                       | ((~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf_io_inst_0_valid)) 
                                          | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr_io_interrupt))))));
                    vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT___io_imem_ready_T 
                        = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__nReady) 
                           >= (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__nBufValid));
                    vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__nICReady 
                        = (3U & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__nReady) 
                                 - (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__nBufValid)));
                    vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT___io_imem_ready_T_4 
                        = (3U & (((IData)(2U) - (1U 
                                                 & (IData)(
                                                           (vlSelfRef.tb_Rocket__DOT__fpc 
                                                            >> 1U)))) 
                                 - (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__nICReady)));
                    vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf_io_imem_ready 
                        = ((~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ctrl_stalld)) 
                           & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT___io_imem_ready_T) 
                              & ((1U >= (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT___io_imem_ready_T_4)) 
                                 | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__nICReady) 
                                    >= (3U & ((IData)(2U) 
                                              - (1U 
                                                 & (IData)(
                                                           (vlSelfRef.tb_Rocket__DOT__fpc 
                                                            >> 1U)))))))));
                }
            }
        }
        Vtb_Rocket___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Vtb_Rocket___024root___eval(Vtb_Rocket___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_Rocket___024root___eval\n"); );
    Vtb_Rocket__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00002710U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vtb_Rocket___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("/home/zhangzijie/pyCircuit/designs/Rocket-pyc/tests/tb/tb_rocket_pgm.v", 12, "", "DIDNOTCONVERGE: NBA region did not converge after '--converge-limit' of 10000 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VinactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00002710U < vlSelfRef.__VinactIterCount)))) {
                VL_FATAL_MT("/home/zhangzijie/pyCircuit/designs/Rocket-pyc/tests/tb/tb_rocket_pgm.v", 12, "", "DIDNOTCONVERGE: Inactive region did not converge after '--converge-limit' of 10000 tries");
            }
            vlSelfRef.__VinactIterCount = ((IData)(1U) 
                                           + vlSelfRef.__VinactIterCount);
            vlSelfRef.__VactIterCount = 0U;
            do {
                if (VL_UNLIKELY(((0x00002710U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                    Vtb_Rocket___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                    VL_FATAL_MT("/home/zhangzijie/pyCircuit/designs/Rocket-pyc/tests/tb/tb_rocket_pgm.v", 12, "", "DIDNOTCONVERGE: Active region did not converge after '--converge-limit' of 10000 tries");
                }
                vlSelfRef.__VactIterCount = ((IData)(1U) 
                                             + vlSelfRef.__VactIterCount);
                vlSelfRef.__VactPhaseResult = Vtb_Rocket___024root___eval_phase__act(vlSelf);
            } while (vlSelfRef.__VactPhaseResult);
            vlSelfRef.__VinactPhaseResult = Vtb_Rocket___024root___eval_phase__inact(vlSelf);
        } while (vlSelfRef.__VinactPhaseResult);
        vlSelfRef.__VnbaPhaseResult = Vtb_Rocket___024root___eval_phase__nba(vlSelf);
    } while (vlSelfRef.__VnbaPhaseResult);
}

void Vtb_Rocket___024root____VbeforeTrig_h7b2495ab__0(Vtb_Rocket___024root* vlSelf, const char* __VeventDescription) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_Rocket___024root____VbeforeTrig_h7b2495ab__0\n"); );
    Vtb_Rocket__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    VlUnpacked<QData/*63:0*/, 1> __VTmp;
    // Body
    __VTmp[0U] = (QData)((IData)(((IData)(vlSelfRef.tb_Rocket__DOT__clk) 
                                  & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_Rocket__DOT__clk__0)))));
    vlSelfRef.__Vtrigprevexpr___TOP__tb_Rocket__DOT__clk__0 
        = vlSelfRef.tb_Rocket__DOT__clk;
    if ((1ULL & __VTmp[0U])) {
        vlSelfRef.__VtrigSched_h7b2495ab__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h7b2495ab__0.ready(__VeventDescription);
    }
    vlSelfRef.__VactTriggeredAcc[0U] = (vlSelfRef.__VactTriggeredAcc[0U] 
                                        | __VTmp[0U]);
}

#ifdef VL_DEBUG
void Vtb_Rocket___024root___eval_debug_assertions(Vtb_Rocket___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_Rocket___024root___eval_debug_assertions\n"); );
    Vtb_Rocket__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}
#endif  // VL_DEBUG

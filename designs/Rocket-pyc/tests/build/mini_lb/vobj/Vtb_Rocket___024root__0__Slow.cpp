// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_Rocket.h for the primary calling header

#include "Vtb_Rocket__pch.h"

void Vtb_Rocket___024root___timing_ready(Vtb_Rocket___024root* vlSelf);

VL_ATTR_COLD void Vtb_Rocket___024root___eval_static(Vtb_Rocket___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_Rocket___024root___eval_static\n"); );
    Vtb_Rocket__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    {
        // Inlined CFunc: _eval_static__TOP
        vlSelfRef.tb_Rocket__DOT__clk = 0U;
        vlSelfRef.tb_Rocket__DOT__reset = 1U;
        vlSelfRef.tb_Rocket__DOT__red_d = 0U;
        vlSelfRef.tb_Rocket__DOT__q1_v = 0U;
        vlSelfRef.tb_Rocket__DOT__q2_v = 0U;
        vlSelfRef.tb_Rocket__DOT__q1_is_load = 0U;
        vlSelfRef.tb_Rocket__DOT__q2_is_load = 0U;
        vlSelfRef.tb_Rocket__DOT__q1_signed = 0U;
        vlSelfRef.tb_Rocket__DOT__q2_signed = 0U;
        vlSelfRef.tb_Rocket__DOT__q1_tag = 0U;
        vlSelfRef.tb_Rocket__DOT__q2_tag = 0U;
        vlSelfRef.tb_Rocket__DOT__q1_addr = 0ULL;
        vlSelfRef.tb_Rocket__DOT__q2_addr = 0ULL;
        vlSelfRef.tb_Rocket__DOT__q1_size = 0U;
        vlSelfRef.tb_Rocket__DOT__q2_size = 0U;
        vlSelfRef.tb_Rocket__DOT__d_s1_r = 0ULL;
        vlSelfRef.__VdfgBinToOneHot_Pre_h787163e4_0_0 = 0U;
        vlSelfRef.__VdfgBinToOneHot_Tab_h787163e4_0_0.fill(0U);
    }
    vlSelfRef.__Vtrigprevexpr___TOP__tb_Rocket__DOT__clk__0 = 0U;
    Vtb_Rocket___024root___timing_ready(vlSelf);
    do {
        vlSelfRef.__VactTriggeredAcc[vlSelfRef.__Vi] 
            = vlSelfRef.__VactTriggered[vlSelfRef.__Vi];
        vlSelfRef.__Vi = ((IData)(1U) + vlSelfRef.__Vi);
    } while ((0U >= vlSelfRef.__Vi));
}

VL_ATTR_COLD void Vtb_Rocket___024root___eval_final(Vtb_Rocket___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_Rocket___024root___eval_final\n"); );
    Vtb_Rocket__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_Rocket___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vtb_Rocket___024root___eval_phase__stl(Vtb_Rocket___024root* vlSelf);

VL_ATTR_COLD void Vtb_Rocket___024root___eval_settle(Vtb_Rocket___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_Rocket___024root___eval_settle\n"); );
    Vtb_Rocket__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VstlIterCount;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00002710U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            Vtb_Rocket___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
#endif
            VL_FATAL_MT("/home/zhangzijie/pyCircuit/designs/Rocket-pyc/tests/tb/tb_rocket_pgm.v", 12, "", "DIDNOTCONVERGE: Settle region did not converge after '--converge-limit' of 10000 tries");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        vlSelfRef.__VstlPhaseResult = Vtb_Rocket___024root___eval_phase__stl(vlSelf);
        vlSelfRef.__VstlFirstIteration = 0U;
    } while (vlSelfRef.__VstlPhaseResult);
}

VL_ATTR_COLD bool Vtb_Rocket___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_Rocket___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_Rocket___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(Vtb_Rocket___024root___trigger_anySet__stl(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD bool Vtb_Rocket___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_Rocket___024root___trigger_anySet__stl\n"); );
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

VL_ATTR_COLD void Vtb_Rocket___024root___stl_sequent__TOP__0(Vtb_Rocket___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_Rocket___024root___stl_sequent__TOP__0\n"); );
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
    CData/*3:0*/ tb_Rocket__DOT__dut__DOT__ibuf__DOT___valid_T_2;
    tb_Rocket__DOT__dut__DOT__ibuf__DOT___valid_T_2 = 0;
    CData/*0:0*/ tb_Rocket__DOT__dut__DOT__ibuf__DOT__full_insn;
    tb_Rocket__DOT__dut__DOT__ibuf__DOT__full_insn = 0;
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
    VlWide<3>/*95:0*/ __Vtemp_2;
    VlWide<3>/*95:0*/ __Vtemp_3;
    VlWide<3>/*95:0*/ __Vtemp_6;
    VlWide<3>/*95:0*/ __Vtemp_7;
    VlWide<3>/*95:0*/ __Vtemp_9;
    VlWide<3>/*95:0*/ __Vtemp_10;
    VlWide<3>/*95:0*/ __Vtemp_11;
    VlWide<3>/*95:0*/ __Vtemp_15;
    VlWide<3>/*95:0*/ __Vtemp_16;
    VlWide<6>/*191:0*/ __Vtemp_20;
    VlWide<6>/*191:0*/ __Vtemp_21;
    VlWide<3>/*95:0*/ __Vtemp_24;
    VlWide<3>/*95:0*/ __Vtemp_25;
    // Body
    vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf_io_imem_valid 
        = (1U & (~ (IData)(vlSelfRef.tb_Rocket__DOT__red_d)));
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
    vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT___decoded_orMatrixOutputs_T_5 
        = (1U & (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_alu_fn) 
                  >> 1U) | (IData)((1U == (5U & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_alu_fn))))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__mplier 
        = (((QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[1U])) 
            << 0x00000020U) | (QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[0U])));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT___count_T_1 
        = (0x0000007fU & ((IData)(1U) + (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__count)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__size = (3U 
                                                & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_mem_size) 
                                                   | (- (IData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_rocc)))));
    __Vtemp_2[0U] = vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[2U];
    __Vtemp_2[1U] = vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[3U];
    __Vtemp_2[2U] = vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[4U];
    VL_SUB_W(3, __Vtemp_3, __Vtemp_2, vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__divisor);
    vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__subtractor[0U] 
        = __Vtemp_3[0U];
    vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__subtractor[1U] 
        = __Vtemp_3[1U];
    vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__subtractor[2U] 
        = (1U & __Vtemp_3[2U]);
    VL_EXTENDS_WI(67,2, __Vtemp_6, ((2U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[2U] 
                                           << 1U)) 
                                    | (1U & vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[0U])));
    __Vtemp_7[0U] = __Vtemp_6[0U];
    __Vtemp_7[1U] = __Vtemp_6[1U];
    __Vtemp_7[2U] = (7U & __Vtemp_6[2U]);
    VL_EXTENDS_WW(67,65, __Vtemp_9, vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__divisor);
    __Vtemp_10[0U] = __Vtemp_9[0U];
    __Vtemp_10[1U] = __Vtemp_9[1U];
    __Vtemp_10[2U] = (7U & __Vtemp_9[2U]);
    VL_MULS_WWW(67, __Vtemp_11, __Vtemp_7, __Vtemp_10);
    __Vtemp_15[0U] = ((vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[3U] 
                       << 0x0000001fU) | (vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[2U] 
                                          >> 1U));
    __Vtemp_15[1U] = ((vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[4U] 
                       << 0x0000001fU) | (vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[3U] 
                                          >> 1U));
    __Vtemp_15[2U] = ((6U & ((- (IData)((1U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[4U] 
                                               >> 1U)))) 
                             << 1U)) | (1U & (vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[4U] 
                                              >> 1U)));
    VL_ADD_W(3, __Vtemp_16, __Vtemp_11, __Vtemp_15);
    vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__nextMulReg_hi[0U] 
        = __Vtemp_16[0U];
    vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__nextMulReg_hi[1U] 
        = __Vtemp_16[1U];
    vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__nextMulReg_hi[2U] 
        = (7U & __Vtemp_16[2U]);
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__pmp_mask_base 
        = ((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_0_addr 
            << 1U) | (1U & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_0_cfg_a)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__pmp_mask_base_1 
        = ((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_1_addr 
            << 1U) | (1U & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_1_cfg_a)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__pmp_mask_base_2 
        = ((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_2_addr 
            << 1U) | (1U & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_2_cfg_a)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__pmp_mask_base_3 
        = ((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_3_addr 
            << 1U) | (1U & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_3_cfg_a)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__pmp_mask_base_4 
        = ((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_4_addr 
            << 1U) | (1U & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_4_cfg_a)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__pmp_mask_base_5 
        = ((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_5_addr 
            << 1U) | (1U & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_5_cfg_a)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__pmp_mask_base_6 
        = ((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_6_addr 
            << 1U) | (1U & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_6_cfg_a)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__pmp_mask_base_7 
        = ((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_7_addr 
            << 1U) | (1U & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_7_cfg_a)));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_36 = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_jalr) 
                                                 & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_debug));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_39 = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_7_cfg_l) 
                                                 & (1U 
                                                    == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_7_cfg_a)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_pc_valid 
        = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_valid) 
           | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_replay) 
              | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_xcpt_interrupt)));
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
    vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf_io_inst_0_bits_xcpt0_ae_inst 
        = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__buf___05Fxcpt_ae_inst) 
           & ((3U & ((IData)(1U) << (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__nBufValid))) 
              - (IData)(1U)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT___T_70 = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_xcpt) 
                                                 | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_xcpt_interrupt));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_25 = (IData)(
                                                        (0x48000000U 
                                                         == 
                                                         (0x48000000U 
                                                          & vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_pc_valid 
        = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_valid) 
           | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_replay) 
              | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_xcpt_interrupt)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr_io_interrupt 
        = ((~ ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_debug) 
               | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__io_status_cease_r))) 
           & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_singleStepped));
    tb_Rocket__DOT__dut__DOT___T_28 = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_valid) 
                                       & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_ctrl_wxd));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf_io_pc 
        = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__nBufValid)
            ? vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__buf___05Fpc
            : vlSelfRef.tb_Rocket__DOT__fpc);
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_69 = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_ctrl_jalr) 
                                                 | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_ctrl_jal));
    tb_Rocket__DOT__dut__DOT__alu__DOT___shin_T_2 = 
        ((5U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_alu_fn)) 
         | (0x0bU == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_alu_fn)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__result 
        = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__resHi)
            ? (((QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[4U])) 
                << 0x0000003fU) | (((QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[3U])) 
                                    << 0x0000001fU) 
                                   | ((QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[2U])) 
                                      >> 1U))) : (((QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[1U])) 
                                                   << 0x00000020U) 
                                                  | (QData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__remainder[0U]))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr_io_singleStep 
        = ((~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_debug)) 
           & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_dcsr_step));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__id_mem_busy 
        = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_valid) 
           & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_mem));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__div_io_req_valid 
        = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_valid) 
           & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_div));
    tb_Rocket__DOT__dut__DOT__csr_io_csr_stall = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_wfi) 
                                                  | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__io_status_cease_r));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__buf_replay 
        = (3U & ((((IData)(1U) << (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__nBufValid)) 
                  - (IData)(1U)) & (- (IData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__buf___05Freplay)))));
    tb_Rocket__DOT__dut__DOT___mem_cfi_taken_T = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_ctrl_branch) 
                                                  & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_br_taken));
    tb_Rocket__DOT__dut__DOT___T_27 = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_valid) 
                                       & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_wxd));
    tb_Rocket__DOT__dut__DOT__wb_dcache_miss = ((~ (IData)(vlSelfRef.tb_Rocket__DOT__q2_v)) 
                                                & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_ctrl_mem));
    tb_Rocket__DOT__dut__DOT__ibuf__DOT___valid_T_2 
        = (0x0000000fU & (((IData)(1U) << (3U & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__nBufValid) 
                                                 + 
                                                 (((IData)(2U) 
                                                   - 
                                                   (1U 
                                                    & (IData)(
                                                              (vlSelfRef.tb_Rocket__DOT__fpc 
                                                               >> 1U)))) 
                                                  & (- (IData)(
                                                               (1U 
                                                                & (~ (IData)(vlSelfRef.tb_Rocket__DOT__red_d))))))))) 
                          - (IData)(1U)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__replay_wb_rocc 
        = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_valid) 
           & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_ctrl_rocc));
    __VdfgRegularize_h6e95ff9d_0_35 = (1U & (~ ((5U 
                                                 == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_sel_imm)) 
                                                | (2U 
                                                   == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_sel_imm)))));
    tb_Rocket__DOT__dut__DOT__ex_imm_sign = ((vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_inst 
                                              >> 0x0000001fU) 
                                             & (5U 
                                                != (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_sel_imm)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT___T_21 
        = ((~ ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_valid) 
               & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_ctrl_wxd))) 
           & ((6U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__state)) 
              | (7U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__state))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___read_mtvec_T_5 
        = (vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mtvec 
           & ((1U & vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mtvec)
               ? 0xffffff01U : 0xfffffffdU));
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
    __VdfgRegularize_h6e95ff9d_0_66 = (IData)((0x00100000U 
                                               == (0x00300000U 
                                                   & vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst)));
    tb_Rocket__DOT__dut__DOT__bpu__DOT___r_T_8 = (1U 
                                                  & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_control_tmatch) 
                                                     & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_address)));
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
    __VdfgRegularize_h6e95ff9d_0_26 = (IData)((0x60000000U 
                                               == (0xe0000000U 
                                                   & vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst)));
    __VdfgRegularize_h6e95ff9d_0_27 = (IData)((0x02000000U 
                                               == (0x06000000U 
                                                   & vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst)));
    __VdfgRegularize_h6e95ff9d_0_9 = (IData)((0x00200000U 
                                              == (0x00300000U 
                                                  & vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr_io_rw_cmd 
        = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_ctrl_csr) 
           & (3U | (- (IData)((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_valid)))));
    __VdfgRegularize_h6e95ff9d_0_85 = (3U & ((vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
                                              >> 0x0000001cU) 
                                             & (~ (vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
                                                   >> 0x0000001eU))));
    __VdfgRegularize_h6e95ff9d_0_5 = (IData)((0x1b000000U 
                                              == (0x1b000000U 
                                                  & vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst)));
    __VdfgRegularize_h6e95ff9d_0_11 = (vlSelfRef.tb_Rocket__DOT__imem
                                       [(0x000000ffU 
                                         & (IData)(
                                                   (vlSelfRef.tb_Rocket__DOT__fpc 
                                                    >> 2U)))] 
                                       >> 0x00000010U);
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
    tb_Rocket__DOT__dut__DOT___T_30 = ((~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_ctrl_mem)) 
                                       & (IData)(tb_Rocket__DOT__dut__DOT___T_28));
    tb_Rocket__DOT__dut__DOT__div__DOT__loOut = (((~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__req_dw)) 
                                                  & (0U 
                                                     == 
                                                     (1U 
                                                      & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__state))))
                                                  ? (IData)(
                                                            (vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__result 
                                                             >> 0x00000020U))
                                                  : (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__result));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT___T_23 
        = ((0U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__state)) 
           & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div_io_req_valid));
    tb_Rocket__DOT__dut__DOT__csr__DOT__nextSmall_1 
        = (0x0000007fU & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__small_1) 
                          + (1U & (~ (IData)(tb_Rocket__DOT__dut__DOT__csr_io_csr_stall)))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_cfi_taken 
        = ((IData)(tb_Rocket__DOT__dut__DOT___mem_cfi_taken_T) 
           | (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_69));
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
    vlSelfRef.tb_Rocket__DOT__dut__DOT__replay_ex = 
        ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_replay) 
         | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_valid) 
            & (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_load_use) 
                & (IData)(tb_Rocket__DOT__dut__DOT__wb_dcache_miss)) 
               | ((0U != (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__state)) 
                  & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_div)))));
    tb_Rocket__DOT__dut__DOT__wb_set_sboard = ((IData)(tb_Rocket__DOT__dut__DOT__wb_dcache_miss) 
                                               | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_ctrl_rocc) 
                                                  | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_ctrl_div)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__replay_wb = 
        ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_replay) 
         | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__replay_wb_rocc));
    vlSelfRef.tb_Rocket__DOT__dut__DOT___T_143 = (0xfffffffeU 
                                                  & (vlSelfRef.tb_Rocket__DOT__dut__DOT___r 
                                                     & ((~ 
                                                         ((IData)(1U) 
                                                          << (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__req_tag))) 
                                                        | (- (IData)(
                                                                     (1U 
                                                                      & (~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT___T_21))))))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__rf_waddr = 
        (0x0000001fU & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT___T_21)
                         ? (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__req_tag)
                         : (vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_inst 
                            >> 7U)));
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
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__csr_wen 
        = ((6U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr_io_rw_cmd)) 
           | ((5U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr_io_rw_cmd)) 
              | (7U == (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr_io_rw_cmd))));
    tb_Rocket__DOT__dut__DOT__csr__DOT___wdata_T_6 
        = ((~ vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_wdata) 
           | (- (QData)((IData)((1U & (~ (3U == (3U 
                                                 & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr_io_rw_cmd)))))))));
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
    vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_br_target 
        = (0x00000003ffffffffULL & (vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_pc 
                                    + (((QData)((IData)(
                                                        (3U 
                                                         & (- (IData)(
                                                                      (tb_Rocket__DOT__dut__DOT___mem_br_target_T_8 
                                                                       >> 0x0000001fU)))))) 
                                        << 0x00000020U) 
                                       | (QData)((IData)(tb_Rocket__DOT__dut__DOT___mem_br_target_T_8)))));
    __VdfgRegularize_h6e95ff9d_0_81 = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_xcpt) 
                                       | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__replay_wb));
    tb_Rocket__DOT__dut__DOT__bpu__DOT___r_T_24 = (0x00000001ffffffffULL 
                                                   & ((~ vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_address) 
                                                      | tb_Rocket__DOT__dut__DOT__bpu__DOT___GEN_11));
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
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___newBPC_T_8 
        = ((vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_wdata 
            | (tb_Rocket__DOT__dut__DOT__csr__DOT___T_20 
               & (- (QData)((IData)((1U & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr_io_rw_cmd) 
                                           >> 1U))))))) 
           & tb_Rocket__DOT__dut__DOT__csr__DOT___wdata_T_6);
    tb_Rocket__DOT__dut__DOT__csr__DOT___io_eret_T 
        = ((IData)(tb_Rocket__DOT__dut__DOT__csr__DOT__insn_call) 
           | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__insn_break));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__cause 
        = ((IData)(tb_Rocket__DOT__dut__DOT__csr__DOT__insn_call)
            ? 0x000000000000000bULL : ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__insn_break)
                                        ? 3ULL : ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_xcpt)
                                                   ? vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_cause
                                                   : 4ULL)));
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
    __Vtemp_20[0U] = ((vlSelfRef.tb_Rocket__DOT__imem
                       [(0x000000ffU & (IData)((vlSelfRef.tb_Rocket__DOT__fpc 
                                                >> 2U)))] 
                       << 0x00000010U) | (0x0000ffffU 
                                          & vlSelfRef.tb_Rocket__DOT__imem
                                          [(0x000000ffU 
                                            & (IData)(
                                                      (vlSelfRef.tb_Rocket__DOT__fpc 
                                                       >> 2U)))]));
    __Vtemp_20[1U] = (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_52);
    __Vtemp_20[2U] = (IData)((vlSelfRef.__VdfgRegularize_h6e95ff9d_0_52 
                              >> 0x00000020U));
    __Vtemp_20[3U] = (((IData)(__VdfgRegularize_h6e95ff9d_0_11) 
                       << 0x00000010U) | (IData)(__VdfgRegularize_h6e95ff9d_0_11));
    __Vtemp_20[4U] = 0U;
    __Vtemp_20[5U] = 0U;
    VL_SHIFTL_WWI(191,191,6, __Vtemp_21, __Vtemp_20, 
                  (0x00000030U & ((((IData)(2U) + (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__nBufValid)) 
                                   - (1U & (IData)(
                                                   (vlSelfRef.tb_Rocket__DOT__fpc 
                                                    >> 1U)))) 
                                  << 4U)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in 
        = ((__Vtemp_21[2U] & ((IData)(0xffffffffU) 
                              << ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__nBufValid) 
                                  << 4U))) | ((~ ((IData)(0xffffffffU) 
                                                  << 
                                                  ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__nBufValid) 
                                                   << 4U))) 
                                              & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__buf___05Fdata));
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
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr_io_retire 
        = ((~ (IData)(__VdfgRegularize_h6e95ff9d_0_81)) 
           & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_reg_valid));
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
    vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__rhs_sign 
        = (1U & (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_alu_dw)
                   ? (IData)((vlSelfRef.tb_Rocket__DOT__dut__DOT__div_io_req_bits_in2 
                              >> 0x0000003fU)) : (IData)(
                                                         (vlSelfRef.tb_Rocket__DOT__dut__DOT__div_io_req_bits_in2 
                                                          >> 0x0000001fU))) 
                 & ((IData)((4U == (5U & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_alu_fn)))) 
                    | (3U == (3U & (~ ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_alu_fn) 
                                       >> 1U)))))));
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
    vlSelfRef.tb_Rocket__DOT__dut__DOT__div__DOT__lhs_sign 
        = (1U & (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_alu_dw)
                   ? (IData)((vlSelfRef.tb_Rocket__DOT__dut__DOT__div_io_req_bits_in1 
                              >> 0x0000003fU)) : (IData)(
                                                         (vlSelfRef.tb_Rocket__DOT__dut__DOT__div_io_req_bits_in1 
                                                          >> 0x0000001fU))) 
                 & ((~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_alu_fn)) 
                    | (3U == (3U & (~ ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_alu_fn) 
                                       >> 1U)))))));
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
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__dMode 
        = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_debug) 
           & (IData)((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___newBPC_T_8 
                      >> 0x0000003bU)));
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
    tb_Rocket__DOT__dut__DOT__ibuf__DOT__full_insn 
        = (1U & ((3U != (3U & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in)) 
                 | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__buf_replay) 
                    | ((IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT___valid_T_2) 
                       >> 1U))));
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
    vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_npc_misaligned 
        = (1U & ((~ (IData)((vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_misa 
                             >> 2U))) & (IData)((vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_npc 
                                                 >> 1U))));
    tb_Rocket__DOT__dut__DOT__csr__DOT__nextSmall = 
        (0x0000007fU & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__small_) 
                        + (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr_io_retire)));
    tb_Rocket__DOT__dut__DOT__wb_wen = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__wb_ctrl_wxd) 
                                        & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr_io_retire));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__bpu_io_xcpt_if 
        = ((~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_control_action)) 
           & (IData)(tb_Rocket__DOT__dut__DOT__bpu__DOT__x));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__bpu_io_debug_if 
        = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_control_action) 
           & (IData)(tb_Rocket__DOT__dut__DOT__bpu__DOT__x));
    tb_Rocket__DOT__dut__DOT__bpu__DOT__r = ((~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_debug)) 
                                             & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_control_r) 
                                                & (IData)(tb_Rocket__DOT__dut__DOT__bpu__DOT___r_T_26)));
    tb_Rocket__DOT__dut__DOT__bpu__DOT__w = ((~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_debug)) 
                                             & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_control_w) 
                                                & (IData)(tb_Rocket__DOT__dut__DOT__bpu__DOT___r_T_26)));
    tb_Rocket__DOT__dut__DOT__alu__DOT__in2_inv = (
                                                   (8U 
                                                    & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_alu_fn))
                                                    ? 
                                                   (~ tb_Rocket__DOT__dut__DOT__alu_io_in2)
                                                    : tb_Rocket__DOT__dut__DOT__alu_io_in2);
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
    vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf_io_inst_0_valid 
        = ((IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT___valid_T_2) 
           & (IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__full_insn));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__nReady 
        = (((3U != (3U & vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in))
             ? 1U : 2U) & (- (IData)((IData)(tb_Rocket__DOT__dut__DOT__ibuf__DOT__full_insn))));
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
    vlSelfRef.tb_Rocket__DOT__dut__DOT___T_71 = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_valid) 
                                                 & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_npc_misaligned));
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
    vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_debug_breakpoint 
        = (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_load) 
            & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_control_action) 
               & (IData)(tb_Rocket__DOT__dut__DOT__bpu__DOT__r))) 
           | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_store) 
              & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_control_action) 
                 & (IData)(tb_Rocket__DOT__dut__DOT__bpu__DOT__w))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__alu__DOT__in1_xor_in2 
        = (tb_Rocket__DOT__dut__DOT__alu_io_in1 ^ tb_Rocket__DOT__dut__DOT__alu__DOT__in2_inv);
    vlSelfRef.tb_Rocket__DOT__dut__DOT__alu_io_adder_out 
        = (tb_Rocket__DOT__dut__DOT__alu_io_in1 + (tb_Rocket__DOT__dut__DOT__alu__DOT__in2_inv 
                                                   + (QData)((IData)(
                                                                     (1U 
                                                                      & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_alu_fn) 
                                                                         >> 3U))))));
    tb_Rocket__DOT__dut__DOT__alu__DOT___shin_T_11 
        = ((tb_Rocket__DOT__dut__DOT__alu__DOT__shin_r 
            << 0x00000020U) | (tb_Rocket__DOT__dut__DOT__alu__DOT__shin_r 
                               >> 0x00000020U));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__killm_common 
        = (1U & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__take_pc_wb) 
                 | ((~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_valid)) 
                    | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_xcpt))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf_io_kill 
        = (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_valid) 
            & ((~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_xcpt)) 
               & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_cfi_taken))) 
           | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__take_pc_wb));
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
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_98 = (((~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__take_pc_wb)) 
                                                  & (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_valid)) 
                                                 & (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_pc_valid)
                                                      ? 
                                                     (vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_pc 
                                                      != vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_npc)
                                                      : 
                                                     (~ 
                                                      (((~ (IData)(vlSelfRef.tb_Rocket__DOT__red_d)) 
                                                        | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf_io_inst_0_valid)) 
                                                       & (vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf_io_pc 
                                                          == vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_npc)))) 
                                                    & ((~ 
                                                        ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_ctrl_branch) 
                                                         | (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_69))) 
                                                       | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_cfi_taken))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT___io_imem_ready_T 
        = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__nReady) 
           >= (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__nBufValid));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__nICReady 
        = (3U & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__nReady) 
                 - (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__nBufValid)));
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
    vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_ldst_xcpt 
        = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_debug_breakpoint) 
           | (((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_load) 
               & ((~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_control_action)) 
                  & (IData)(tb_Rocket__DOT__dut__DOT__bpu__DOT__r))) 
              | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__mem_reg_store) 
                 & ((~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_control_action)) 
                    & (IData)(tb_Rocket__DOT__dut__DOT__bpu__DOT__w)))));
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
    tb_Rocket__DOT__dut__DOT__alu__DOT___shin_T_21 
        = ((0xffff0000ffff0000ULL & (tb_Rocket__DOT__dut__DOT__alu__DOT___shin_T_11 
                                     << 0x00000010U)) 
           | (0x0000ffff0000ffffULL & (tb_Rocket__DOT__dut__DOT__alu__DOT___shin_T_11 
                                       >> 0x00000010U)));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__ctrl_killx 
        = (1U & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf_io_kill) 
                 | ((~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_reg_valid)) 
                    | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__replay_ex))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT___GEN_275 
        = ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__insn_ret)
            ? ((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_25)
                ? (IData)(tb_Rocket__DOT__dut__DOT__csr__DOT___GEN_219)
                : (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mstatus_mpie))
            : (IData)(tb_Rocket__DOT__dut__DOT__csr__DOT___GEN_219));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT___io_imem_ready_T_4 
        = (3U & (((IData)(2U) - (1U & (IData)((vlSelfRef.tb_Rocket__DOT__fpc 
                                               >> 1U)))) 
                 - (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__nICReady)));
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
    __Vtemp_24[0U] = (IData)(tb_Rocket__DOT__dut__DOT__alu__DOT__shin);
    __Vtemp_24[1U] = (IData)((tb_Rocket__DOT__dut__DOT__alu__DOT__shin 
                              >> 0x00000020U));
    __Vtemp_24[2U] = (IData)((((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_alu_fn) 
                               >> 3U) & (tb_Rocket__DOT__dut__DOT__alu__DOT__shin 
                                         >> 0x0000003fU)));
    VL_SHIFTRS_WWI(65,65,6, __Vtemp_25, __Vtemp_24, 
                   ((((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ex_ctrl_alu_dw) 
                      & (IData)((tb_Rocket__DOT__dut__DOT__alu_io_in2 
                                 >> 5U))) << 5U) | 
                    (0x0000001fU & (IData)(tb_Rocket__DOT__dut__DOT__alu_io_in2))));
    tb_Rocket__DOT__dut__DOT__alu__DOT__shout_r = (
                                                   ((QData)((IData)(__Vtemp_25[1U])) 
                                                    << 0x00000020U) 
                                                   | (QData)((IData)(__Vtemp_25[0U])));
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
    vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf_io_imem_ready 
        = ((~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ctrl_stalld)) 
           & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT___io_imem_ready_T) 
              & ((1U >= (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT___io_imem_ready_T_4)) 
                 | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf__DOT__nICReady) 
                    >= (3U & ((IData)(2U) - (1U & (IData)(
                                                          (vlSelfRef.tb_Rocket__DOT__fpc 
                                                           >> 1U)))))))));
    vlSelfRef.tb_Rocket__DOT__dut__DOT__ctrl_killd 
        = (1U & ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf_io_inst_0_bits_replay) 
                 | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf_io_kill) 
                    | ((IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ctrl_stalld) 
                       | ((~ (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__ibuf_io_inst_0_valid)) 
                          | (IData)(vlSelfRef.tb_Rocket__DOT__dut__DOT__csr_io_interrupt))))));
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

VL_ATTR_COLD bool Vtb_Rocket___024root___eval_phase__stl(Vtb_Rocket___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_Rocket___024root___eval_phase__stl\n"); );
    Vtb_Rocket__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VstlExecute;
    // Body
    {
        // Inlined CFunc: _eval_triggers_vec__stl
        vlSelfRef.__VstlTriggered[0U] = ((0xfffffffffffffffeULL 
                                          & vlSelfRef.__VstlTriggered[0U]) 
                                         | (IData)((IData)(vlSelfRef.__VstlFirstIteration)));
    }
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtb_Rocket___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
    }
#endif
    __VstlExecute = Vtb_Rocket___024root___trigger_anySet__stl(vlSelfRef.__VstlTriggered);
    if (__VstlExecute) {
        {
            // Inlined CFunc: _eval_stl
            if ((1ULL & vlSelfRef.__VstlTriggered[0U])) {
                Vtb_Rocket___024root___stl_sequent__TOP__0(vlSelf);
            }
        }
    }
    return (__VstlExecute);
}

bool Vtb_Rocket___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_Rocket___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_Rocket___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(Vtb_Rocket___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge tb_Rocket.clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 1U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 1 is active: @([true] __VdlySched.awaitingCurrentTime())\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtb_Rocket___024root___ctor_var_reset(Vtb_Rocket___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_Rocket___024root___ctor_var_reset\n"); );
    Vtb_Rocket__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelf->tb_Rocket__DOT__i_dresp_data = 0;
    for (int __Vi0 = 0; __Vi0 < 256; ++__Vi0) {
        vlSelf->tb_Rocket__DOT__imem[__Vi0] = 0;
    }
    vlSelf->tb_Rocket__DOT__fpc = 0;
    VL_ZERO_RESET_W(1024, vlSelf->tb_Rocket__DOT__imem_file);
    for (int __Vi0 = 0; __Vi0 < 256; ++__Vi0) {
        vlSelf->tb_Rocket__DOT__dmem8[__Vi0] = 0;
    }
    vlSelf->tb_Rocket__DOT__wdata_shift = 0;
    vlSelf->tb_Rocket__DOT__blk = 0;
    vlSelf->tb_Rocket__DOT__wbe = 0;
    vlSelf->tb_Rocket__DOT__s_reset = 0;
    vlSelf->tb_Rocket__DOT__s_irq_debug = 0;
    vlSelf->tb_Rocket__DOT__s_irq_mtip = 0;
    vlSelf->tb_Rocket__DOT__s_irq_msip = 0;
    vlSelf->tb_Rocket__DOT__s_irq_meip = 0;
    vlSelf->tb_Rocket__DOT__s_iresp_valid = 0;
    vlSelf->tb_Rocket__DOT__s_iresp_xcpt = 0;
    vlSelf->tb_Rocket__DOT__s_iresp_replay = 0;
    vlSelf->tb_Rocket__DOT__s_iresp_pc = 0;
    vlSelf->tb_Rocket__DOT__s_iresp_data = 0;
    vlSelf->tb_Rocket__DOT__s_dreq_ready = 0;
    vlSelf->tb_Rocket__DOT__s_s2_nack = 0;
    vlSelf->tb_Rocket__DOT__s_dresp_valid = 0;
    vlSelf->tb_Rocket__DOT__s_dresp_replay = 0;
    vlSelf->tb_Rocket__DOT__s_dresp_has_data = 0;
    vlSelf->tb_Rocket__DOT__s_replay_next = 0;
    vlSelf->tb_Rocket__DOT__s_x_ma_ld = 0;
    vlSelf->tb_Rocket__DOT__s_x_ma_st = 0;
    vlSelf->tb_Rocket__DOT__s_x_pf_ld = 0;
    vlSelf->tb_Rocket__DOT__s_x_pf_st = 0;
    vlSelf->tb_Rocket__DOT__s_x_ae_ld = 0;
    vlSelf->tb_Rocket__DOT__s_x_ae_st = 0;
    vlSelf->tb_Rocket__DOT__s_ordered = 0;
    vlSelf->tb_Rocket__DOT__s_perf_release = 0;
    vlSelf->tb_Rocket__DOT__s_perf_grant = 0;
    vlSelf->tb_Rocket__DOT__s_dresp_tag = 0;
    vlSelf->tb_Rocket__DOT__s_dresp_data = 0;
    vlSelf->tb_Rocket__DOT__s_dresp_byp = 0;
    vlSelf->tb_Rocket__DOT__max_tick = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__ibuf_io_imem_ready = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__ibuf_io_imem_valid = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__ibuf_io_kill = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__ibuf_io_pc = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__ibuf_io_inst_0_valid = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__ibuf_io_inst_0_bits_xcpt0_ae_inst = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__ibuf_io_inst_0_bits_replay = 0;
    for (int __Vi0 = 0; __Vi0 < 31; ++__Vi0) {
        vlSelf->tb_Rocket__DOT__dut__DOT__rf[__Vi0] = 0;
    }
    vlSelf->tb_Rocket__DOT__dut__DOT__rf_MPORT_data = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr_io_rw_cmd = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr_io_eret = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr_io_singleStep = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr_io_retire = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr_io_interrupt = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__bpu_io_xcpt_if = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__bpu_io_debug_if = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__alu_io_adder_out = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__div_io_req_valid = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__div_io_req_bits_in1 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__div_io_req_bits_in2 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__id_reg_pause = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__imem_might_request_reg = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__ex_ctrl_fp = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__ex_ctrl_rocc = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__ex_ctrl_branch = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__ex_ctrl_jal = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__ex_ctrl_jalr = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__ex_ctrl_rxs2 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__ex_ctrl_sel_alu2 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__ex_ctrl_sel_alu1 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__ex_ctrl_sel_imm = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__ex_ctrl_alu_dw = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__ex_ctrl_alu_fn = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__ex_ctrl_mem = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__ex_ctrl_mem_cmd = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__ex_ctrl_mul = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__ex_ctrl_div = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__ex_ctrl_wxd = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__ex_ctrl_csr = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__ex_ctrl_fence_i = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__mem_ctrl_fp = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__mem_ctrl_rocc = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__mem_ctrl_branch = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__mem_ctrl_jal = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__mem_ctrl_jalr = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__mem_ctrl_mem = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__mem_ctrl_mul = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__mem_ctrl_div = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__mem_ctrl_wxd = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__mem_ctrl_csr = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__mem_ctrl_fence_i = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__wb_ctrl_rocc = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__wb_ctrl_mem = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__wb_ctrl_div = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__wb_ctrl_wxd = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__wb_ctrl_csr = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__wb_ctrl_fence_i = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__ex_reg_xcpt_interrupt = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__ex_reg_valid = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__ex_reg_rvc = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__ex_reg_xcpt = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__ex_reg_flush_pipe = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__ex_reg_load_use = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__ex_reg_cause = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__ex_reg_replay = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__ex_reg_pc = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__ex_reg_mem_size = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__ex_reg_inst = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__mem_reg_xcpt_interrupt = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__mem_reg_valid = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__mem_reg_rvc = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__mem_reg_xcpt = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__mem_reg_replay = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__mem_reg_flush_pipe = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__mem_reg_cause = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__mem_reg_slow_bypass = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__mem_reg_load = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__mem_reg_store = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__mem_reg_pc = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__mem_reg_inst = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__mem_reg_wdata = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__mem_reg_rs2 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__mem_br_taken = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__wb_reg_valid = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__wb_reg_xcpt = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__wb_reg_replay = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__wb_reg_flush_pipe = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__wb_reg_cause = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__wb_reg_pc = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__wb_reg_inst = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__wb_reg_wdata = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__replay_wb_rocc = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__replay_wb = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__take_pc_wb = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__mem_cfi_taken = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_1 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_5 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_7 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_9 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_11 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_13 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_15 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_23 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_27 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_29 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__id_ctrl_decoder_decoded_lo_15 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_33 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_37 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_39 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_41 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_47 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_51 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_55 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_63 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_65 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_69 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_75 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__id_ctrl_decoder_decoded_lo_42 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_87 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_89 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_93 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_95 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_99 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_105 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_109 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_115 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_119 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__id_ctrl_decoder_decoded_lo_61 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_131 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_155 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_159 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_161 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_T_163 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_orMatrixOutputs_T_1 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_orMatrixOutputs_T_9 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_orMatrixOutputs_T_11 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_orMatrixOutputs_T_20 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_orMatrixOutputs_T_38 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT___id_ctrl_decoder_decoded_orMatrixOutputs_T_48 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__id_ctrl_decoder_23 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__id_reg_fence = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__id_csr_en = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__id_csr_ren = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__id_illegal_insn = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__id_mem_busy = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__id_xcpt = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__id_bypass_src_0_1 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__id_bypass_src_0_2 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__id_bypass_src_1_1 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__id_bypass_src_1_2 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__ex_reg_rs_bypass_0 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__ex_reg_rs_bypass_1 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__ex_reg_rs_lsb_0 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__ex_reg_rs_lsb_1 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__ex_reg_rs_msb_0 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__ex_reg_rs_msb_1 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__data_hazard_mem = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT___r = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__blocked = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__ctrl_stalld = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__ctrl_killd = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__do_bypass = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__rf_wen = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__rf_waddr = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__id_rs_0 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__do_bypass_1 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__id_rs_1 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__inst = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__ex_pc_valid = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__replay_ex = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__ctrl_killx = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__mem_pc_valid = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__mem_br_target = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__mem_npc = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__mem_npc_misaligned = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT___mem_reg_load_T_23 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__size = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__mem_debug_breakpoint = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__mem_ldst_xcpt = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT___T_70 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT___T_71 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__mem_xcpt = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__killm_common = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__div_io_kill_REG = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__ctrl_killm = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT___T_143 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT___T_145 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_in = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_bits = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs1 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__ibuf__DOT__exp_io_out_rs2 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__ibuf__DOT__nBufValid = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__ibuf__DOT__buf___05Fpc = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__ibuf__DOT__buf___05Fdata = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__ibuf__DOT__buf___05Fxcpt_ae_inst = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__ibuf__DOT__buf___05Freplay = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__ibuf__DOT__buf_replay = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__ibuf__DOT__nReady = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__ibuf__DOT__nICReady = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__ibuf__DOT___io_imem_ready_T = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__ibuf__DOT___io_imem_ready_T_4 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__ibuf__DOT___io_inst_0_bits_xcpt1_T_5 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__div__DOT__state = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__div__DOT__req_dw = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__div__DOT__req_tag = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__div__DOT__count = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__div__DOT__neg_out = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__div__DOT__isHi = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__div__DOT__resHi = 0;
    VL_ZERO_RESET_W(65, vlSelf->tb_Rocket__DOT__dut__DOT__div__DOT__divisor);
    VL_ZERO_RESET_W(130, vlSelf->tb_Rocket__DOT__dut__DOT__div__DOT__remainder);
    vlSelf->tb_Rocket__DOT__dut__DOT__div__DOT___decoded_orMatrixOutputs_T_5 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__div__DOT__lhs_sign = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__div__DOT__rhs_sign = 0;
    VL_ZERO_RESET_W(65, vlSelf->tb_Rocket__DOT__dut__DOT__div__DOT__subtractor);
    vlSelf->tb_Rocket__DOT__dut__DOT__div__DOT__result = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__div__DOT__mplier = 0;
    VL_ZERO_RESET_W(67, vlSelf->tb_Rocket__DOT__dut__DOT__div__DOT__nextMulReg_hi);
    vlSelf->tb_Rocket__DOT__dut__DOT__div__DOT___count_T_1 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__div__DOT___GEN_12 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__div__DOT___GEN_13 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__div__DOT___T_21 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__div__DOT___T_23 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__alu__DOT__in1_xor_in2 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__alu__DOT__slt = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__alu__DOT__out = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mstatus_gva = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mstatus_spp = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mstatus_mpie = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mstatus_mie = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_dcsr_ebreakm = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_dcsr_cause = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_dcsr_step = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_debug = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_dpc = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_dscratch0 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_singleStepped = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_control_dmode = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_control_action = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_control_tmatch = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_control_x = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_control_w = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_control_r = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_bp_0_address = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_0_cfg_l = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_0_cfg_a = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_0_cfg_x = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_0_cfg_w = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_0_cfg_r = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_0_addr = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_1_cfg_l = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_1_cfg_a = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_1_cfg_x = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_1_cfg_w = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_1_cfg_r = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_1_addr = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_2_cfg_l = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_2_cfg_a = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_2_cfg_x = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_2_cfg_w = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_2_cfg_r = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_2_addr = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_3_cfg_l = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_3_cfg_a = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_3_cfg_x = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_3_cfg_w = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_3_cfg_r = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_3_addr = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_4_cfg_l = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_4_cfg_a = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_4_cfg_x = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_4_cfg_w = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_4_cfg_r = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_4_addr = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_5_cfg_l = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_5_cfg_a = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_5_cfg_x = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_5_cfg_w = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_5_cfg_r = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_5_addr = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_6_cfg_l = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_6_cfg_a = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_6_cfg_x = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_6_cfg_w = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_6_cfg_r = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_6_addr = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_7_cfg_l = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_7_cfg_a = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_7_cfg_x = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_7_cfg_w = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_7_cfg_r = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_pmp_7_addr = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mie = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mepc = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mcause = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mtval = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mscratch = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mtvec = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_wfi = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_mcountinhibit = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__small_ = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__large_ = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT___GEN_1 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__small_1 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__large_1 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT___GEN_3 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__pmp_mask_base = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__pmp_mask_base_1 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__pmp_mask_base_2 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__pmp_mask_base_3 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__pmp_mask_base_4 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__pmp_mask_base_5 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__pmp_mask_base_6 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__pmp_mask_base_7 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_misa = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT___read_mtvec_T_5 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT___T_30 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT___T_44 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__reg_custom_0 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_1 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_3 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_5 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_7 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_9 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_69 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_71 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_73 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_75 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_79 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_83 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_85 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_87 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_89 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_91 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_93 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_95 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_97 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_117 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_119 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_123 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_125 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_127 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_129 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_131 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT___decoded_decoded_T_133 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__wdata = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__insn_break = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__insn_ret = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__cause = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__causeIsDebugInt = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__causeIsDebugTrigger = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__trapToDebug = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__exception = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT___GEN_184 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT___GEN_214 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT___GEN_275 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT___GEN_276 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__io_status_cease_r = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__csr_wen = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT___newBPC_T_8 = 0;
    vlSelf->tb_Rocket__DOT__dut__DOT__csr__DOT__dMode = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_2 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_3 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_4 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_7 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_8 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_13 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_15 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_23 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_25 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_32 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_36 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_39 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_40 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_43 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_49 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_51 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_52 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_57 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_58 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_61 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_62 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_63 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_64 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_65 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_69 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_71 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_72 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_76 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_79 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_80 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_83 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_98 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VstlTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggeredAcc[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__tb_Rocket__DOT__clk__0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
    vlSelf->__Vi = 0;
}

// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb.h for the primary calling header

#include "Vtb__pch.h"
#include "Vtb___024root.h"

VlCoroutine Vtb___024root___eval_initial__TOP__Vtiming__0(Vtb___024root* vlSelf);

void Vtb___024root___eval_initial(Vtb___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb___024root___eval_initial\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vtb___024root___eval_initial__TOP__Vtiming__0(vlSelf);
}

VL_INLINE_OPT VlCoroutine Vtb___024root___eval_initial__TOP__Vtiming__0(Vtb___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb___024root___eval_initial__TOP__Vtiming__0\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb__DOT__in = 0x807060504030201ULL;
    co_await vlSelfRef.__VdlySched.delay(0x3e8ULL, 
                                         nullptr, "tb.sv", 
                                         8);
    VL_WRITEF_NX("%x\n",0,64,(((QData)((IData)(((vlSelfRef.tb__DOT__dut__DOT____VdfgRegularize_hc321f105_0_0 
                                                 << 0x10U) 
                                                | (0xffffU 
                                                   & vlSelfRef.tb__DOT__dut__DOT____VdfgRegularize_hc321f105_0_1)))) 
                               << 0x20U) | (QData)((IData)(
                                                           ((vlSelfRef.tb__DOT__dut__DOT____VdfgRegularize_hc321f105_0_2 
                                                             << 0x10U) 
                                                            | (0xffffU 
                                                               & vlSelfRef.tb__DOT__dut__DOT____VdfgRegularize_hc321f105_0_3))))));
    vlSelfRef.tb__DOT__in = 0ULL;
    co_await vlSelfRef.__VdlySched.delay(0x3e8ULL, 
                                         nullptr, "tb.sv", 
                                         9);
    VL_WRITEF_NX("%x\n",0,64,(((QData)((IData)(((vlSelfRef.tb__DOT__dut__DOT____VdfgRegularize_hc321f105_0_0 
                                                 << 0x10U) 
                                                | (0xffffU 
                                                   & vlSelfRef.tb__DOT__dut__DOT____VdfgRegularize_hc321f105_0_1)))) 
                               << 0x20U) | (QData)((IData)(
                                                           ((vlSelfRef.tb__DOT__dut__DOT____VdfgRegularize_hc321f105_0_2 
                                                             << 0x10U) 
                                                            | (0xffffU 
                                                               & vlSelfRef.tb__DOT__dut__DOT____VdfgRegularize_hc321f105_0_3))))));
    vlSelfRef.tb__DOT__in = 0xff00ff00ff00ff00ULL;
    co_await vlSelfRef.__VdlySched.delay(0x3e8ULL, 
                                         nullptr, "tb.sv", 
                                         10);
    VL_WRITEF_NX("%x\n",0,64,(((QData)((IData)(((vlSelfRef.tb__DOT__dut__DOT____VdfgRegularize_hc321f105_0_0 
                                                 << 0x10U) 
                                                | (0xffffU 
                                                   & vlSelfRef.tb__DOT__dut__DOT____VdfgRegularize_hc321f105_0_1)))) 
                               << 0x20U) | (QData)((IData)(
                                                           ((vlSelfRef.tb__DOT__dut__DOT____VdfgRegularize_hc321f105_0_2 
                                                             << 0x10U) 
                                                            | (0xffffU 
                                                               & vlSelfRef.tb__DOT__dut__DOT____VdfgRegularize_hc321f105_0_3))))));
    VL_FINISH_MT("tb.sv", 11, "");
}

void Vtb___024root___act_sequent__TOP__0(Vtb___024root* vlSelf);

void Vtb___024root___eval_act(Vtb___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb___024root___eval_act\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VactTriggered.word(0U))) {
        Vtb___024root___act_sequent__TOP__0(vlSelf);
    }
}

VL_INLINE_OPT void Vtb___024root___act_sequent__TOP__0(Vtb___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb___024root___act_sequent__TOP__0\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb__DOT__dut__DOT____VdfgRegularize_hc321f105_0_0 
        = (VL_MULS_III(32, (IData)(0x66U), VL_EXTENDS_II(32,9, 
                                                         (0xffU 
                                                          & (IData)(vlSelfRef.tb__DOT__in)))) 
           + (VL_MULS_III(32, (IData)(0xffffffe7U), 
                          VL_EXTENDS_II(32,9, (0xffU 
                                               & (IData)(
                                                         (vlSelfRef.tb__DOT__in 
                                                          >> 8U))))) 
              + (VL_MULS_III(32, (IData)(0xffffffa1U), 
                             VL_EXTENDS_II(32,9, (0xffU 
                                                  & (IData)(
                                                            (vlSelfRef.tb__DOT__in 
                                                             >> 0x10U))))) 
                 + (VL_MULS_III(32, (IData)(0xffffffc5U), 
                                VL_EXTENDS_II(32,9, 
                                              (0xffU 
                                               & (IData)(
                                                         (vlSelfRef.tb__DOT__in 
                                                          >> 0x18U))))) 
                    + (VL_MULS_III(32, (IData)(0x3bU), 
                                   VL_EXTENDS_II(32,9, 
                                                 (0xffU 
                                                  & (IData)(
                                                            (vlSelfRef.tb__DOT__in 
                                                             >> 0x20U))))) 
                       + (VL_MULS_III(32, (IData)(0x5fU), 
                                      VL_EXTENDS_II(32,9, 
                                                    (0xffU 
                                                     & (IData)(
                                                               (vlSelfRef.tb__DOT__in 
                                                                >> 0x28U))))) 
                          + (VL_MULS_III(32, (IData)(0x19U), 
                                         VL_EXTENDS_II(32,9, 
                                                       (0xffU 
                                                        & (IData)(
                                                                  (vlSelfRef.tb__DOT__in 
                                                                   >> 0x30U))))) 
                             + VL_MULS_III(32, (IData)(0xffffff9aU), 
                                           VL_EXTENDS_II(32,9, 
                                                         (0xffU 
                                                          & (IData)(
                                                                    (vlSelfRef.tb__DOT__in 
                                                                     >> 0x38U))))))))))));
    vlSelfRef.tb__DOT__dut__DOT____VdfgRegularize_hc321f105_0_1 
        = (VL_MULS_III(32, (IData)(0x76U), VL_EXTENDS_II(32,9, 
                                                         (0xffU 
                                                          & (IData)(vlSelfRef.tb__DOT__in)))) 
           + (VL_MULS_III(32, (IData)(0x31U), VL_EXTENDS_II(32,9, 
                                                            (0xffU 
                                                             & (IData)(
                                                                       (vlSelfRef.tb__DOT__in 
                                                                        >> 8U))))) 
              + (VL_MULS_III(32, (IData)(0xffffffcfU), 
                             VL_EXTENDS_II(32,9, (0xffU 
                                                  & (IData)(
                                                            (vlSelfRef.tb__DOT__in 
                                                             >> 0x10U))))) 
                 + (VL_MULS_III(32, (IData)(0xffffff8aU), 
                                VL_EXTENDS_II(32,9, 
                                              (0xffU 
                                               & (IData)(
                                                         (vlSelfRef.tb__DOT__in 
                                                          >> 0x18U))))) 
                    + (VL_MULS_III(32, (IData)(0xffffff8aU), 
                                   VL_EXTENDS_II(32,9, 
                                                 (0xffU 
                                                  & (IData)(
                                                            (vlSelfRef.tb__DOT__in 
                                                             >> 0x20U))))) 
                       + (VL_MULS_III(32, (IData)(0xffffffcfU), 
                                      VL_EXTENDS_II(32,9, 
                                                    (0xffU 
                                                     & (IData)(
                                                               (vlSelfRef.tb__DOT__in 
                                                                >> 0x28U))))) 
                          + (VL_MULS_III(32, (IData)(0x31U), 
                                         VL_EXTENDS_II(32,9, 
                                                       (0xffU 
                                                        & (IData)(
                                                                  (vlSelfRef.tb__DOT__in 
                                                                   >> 0x30U))))) 
                             + VL_MULS_III(32, (IData)(0x76U), 
                                           VL_EXTENDS_II(32,9, 
                                                         (0xffU 
                                                          & (IData)(
                                                                    (vlSelfRef.tb__DOT__in 
                                                                     >> 0x38U))))))))))));
    vlSelfRef.tb__DOT__dut__DOT____VdfgRegularize_hc321f105_0_2 
        = (VL_MULS_III(32, (IData)(0x7eU), VL_EXTENDS_II(32,9, 
                                                         (0xffU 
                                                          & (IData)(vlSelfRef.tb__DOT__in)))) 
           + (VL_MULS_III(32, (IData)(0x6aU), VL_EXTENDS_II(32,9, 
                                                            (0xffU 
                                                             & (IData)(
                                                                       (vlSelfRef.tb__DOT__in 
                                                                        >> 8U))))) 
              + (VL_MULS_III(32, (IData)(0x47U), VL_EXTENDS_II(32,9, 
                                                               (0xffU 
                                                                & (IData)(
                                                                          (vlSelfRef.tb__DOT__in 
                                                                           >> 0x10U))))) 
                 + (VL_MULS_III(32, (IData)(0x24U), 
                                VL_EXTENDS_II(32,9, 
                                              (0xffU 
                                               & (IData)(
                                                         (vlSelfRef.tb__DOT__in 
                                                          >> 0x18U))))) 
                    + (VL_MULS_III(32, (IData)(0xffffffdcU), 
                                   VL_EXTENDS_II(32,9, 
                                                 (0xffU 
                                                  & (IData)(
                                                            (vlSelfRef.tb__DOT__in 
                                                             >> 0x20U))))) 
                       + (VL_MULS_III(32, (IData)(0xffffffb9U), 
                                      VL_EXTENDS_II(32,9, 
                                                    (0xffU 
                                                     & (IData)(
                                                               (vlSelfRef.tb__DOT__in 
                                                                >> 0x28U))))) 
                          + (VL_MULS_III(32, (IData)(0xffffff96U), 
                                         VL_EXTENDS_II(32,9, 
                                                       (0xffU 
                                                        & (IData)(
                                                                  (vlSelfRef.tb__DOT__in 
                                                                   >> 0x30U))))) 
                             + VL_MULS_III(32, (IData)(0xffffff82U), 
                                           VL_EXTENDS_II(32,9, 
                                                         (0xffU 
                                                          & (IData)(
                                                                    (vlSelfRef.tb__DOT__in 
                                                                     >> 0x38U))))))))))));
    vlSelfRef.tb__DOT__dut__DOT____VdfgRegularize_hc321f105_0_3 
        = (VL_MULS_III(32, (IData)(0xb5U), VL_EXTENDS_II(32,9, 
                                                         (0xffU 
                                                          & (IData)(vlSelfRef.tb__DOT__in)))) 
           + (VL_MULS_III(32, (IData)(0xb5U), VL_EXTENDS_II(32,9, 
                                                            (0xffU 
                                                             & (IData)(
                                                                       (vlSelfRef.tb__DOT__in 
                                                                        >> 8U))))) 
              + (VL_MULS_III(32, (IData)(0xb5U), VL_EXTENDS_II(32,9, 
                                                               (0xffU 
                                                                & (IData)(
                                                                          (vlSelfRef.tb__DOT__in 
                                                                           >> 0x10U))))) 
                 + (VL_MULS_III(32, (IData)(0xb5U), 
                                VL_EXTENDS_II(32,9, 
                                              (0xffU 
                                               & (IData)(
                                                         (vlSelfRef.tb__DOT__in 
                                                          >> 0x18U))))) 
                    + (VL_MULS_III(32, (IData)(0xb5U), 
                                   VL_EXTENDS_II(32,9, 
                                                 (0xffU 
                                                  & (IData)(
                                                            (vlSelfRef.tb__DOT__in 
                                                             >> 0x20U))))) 
                       + (VL_MULS_III(32, (IData)(0xb5U), 
                                      VL_EXTENDS_II(32,9, 
                                                    (0xffU 
                                                     & (IData)(
                                                               (vlSelfRef.tb__DOT__in 
                                                                >> 0x28U))))) 
                          + (VL_MULS_III(32, (IData)(0xb5U), 
                                         VL_EXTENDS_II(32,9, 
                                                       (0xffU 
                                                        & (IData)(
                                                                  (vlSelfRef.tb__DOT__in 
                                                                   >> 0x30U))))) 
                             + VL_MULS_III(32, (IData)(0xb5U), 
                                           VL_EXTENDS_II(32,9, 
                                                         (0xffU 
                                                          & (IData)(
                                                                    (vlSelfRef.tb__DOT__in 
                                                                     >> 0x38U))))))))))));
}

void Vtb___024root___eval_nba(Vtb___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb___024root___eval_nba\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vtb___024root___act_sequent__TOP__0(vlSelf);
    }
}

void Vtb___024root___timing_resume(Vtb___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb___024root___timing_resume\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VactTriggered.word(0U))) {
        vlSelfRef.__VdlySched.resume();
    }
}

void Vtb___024root___eval_triggers__act(Vtb___024root* vlSelf);

bool Vtb___024root___eval_phase__act(Vtb___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb___024root___eval_phase__act\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    VlTriggerVec<1> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    Vtb___024root___eval_triggers__act(vlSelf);
    __VactExecute = vlSelfRef.__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelfRef.__VactTriggered, vlSelfRef.__VnbaTriggered);
        vlSelfRef.__VnbaTriggered.thisOr(vlSelfRef.__VactTriggered);
        Vtb___024root___timing_resume(vlSelf);
        Vtb___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vtb___024root___eval_phase__nba(Vtb___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb___024root___eval_phase__nba\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelfRef.__VnbaTriggered.any();
    if (__VnbaExecute) {
        Vtb___024root___eval_nba(vlSelf);
        vlSelfRef.__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb___024root___dump_triggers__nba(Vtb___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb___024root___dump_triggers__act(Vtb___024root* vlSelf);
#endif  // VL_DEBUG

void Vtb___024root___eval(Vtb___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb___024root___eval\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
            Vtb___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("tb.sv", 1, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelfRef.__VactIterCount = 0U;
        vlSelfRef.__VactContinue = 1U;
        while (vlSelfRef.__VactContinue) {
            if (VL_UNLIKELY((0x64U < vlSelfRef.__VactIterCount))) {
#ifdef VL_DEBUG
                Vtb___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("tb.sv", 1, "", "Active region did not converge.");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
            vlSelfRef.__VactContinue = 0U;
            if (Vtb___024root___eval_phase__act(vlSelf)) {
                vlSelfRef.__VactContinue = 1U;
            }
        }
        if (Vtb___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void Vtb___024root___eval_debug_assertions(Vtb___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb___024root___eval_debug_assertions\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
}
#endif  // VL_DEBUG

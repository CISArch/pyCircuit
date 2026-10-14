// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb3.h for the primary calling header

#include "Vtb3__pch.h"
#include "Vtb3___024root.h"

VlCoroutine Vtb3___024root___eval_initial__TOP__Vtiming__0(Vtb3___024root* vlSelf);

void Vtb3___024root___eval_initial(Vtb3___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb3__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb3___024root___eval_initial\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vtb3___024root___eval_initial__TOP__Vtiming__0(vlSelf);
}

VL_INLINE_OPT VlCoroutine Vtb3___024root___eval_initial__TOP__Vtiming__0(Vtb3___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb3__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb3___024root___eval_initial__TOP__Vtiming__0\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb3__DOT__in = 0x807060504030201ULL;
    co_await vlSelfRef.__VdlySched.delay(0x3e8ULL, 
                                         nullptr, "tb3.sv", 
                                         6);
    VL_WRITEF_NX("%016x\n",0,64,(((QData)((IData)((
                                                   (VL_SHIFTL_III(16,16,32, (IData)(vlSelfRef.tb3__DOT__dut__DOT__sum8), 2U) 
                                                    << 0x10U) 
                                                   | (0xffffU 
                                                      & ((IData)(3U) 
                                                         * (IData)(vlSelfRef.tb3__DOT__dut__DOT__sum8)))))) 
                                  << 0x20U) | (QData)((IData)(
                                                              ((VL_SHIFTL_III(16,16,32, (IData)(vlSelfRef.tb3__DOT__dut__DOT__sum8), 1U) 
                                                                << 0x10U) 
                                                               | (IData)(vlSelfRef.tb3__DOT__dut__DOT__sum8))))));
    vlSelfRef.tb3__DOT__in = 0ULL;
    co_await vlSelfRef.__VdlySched.delay(0x3e8ULL, 
                                         nullptr, "tb3.sv", 
                                         7);
    VL_WRITEF_NX("%016x\n",0,64,(((QData)((IData)((
                                                   (VL_SHIFTL_III(16,16,32, (IData)(vlSelfRef.tb3__DOT__dut__DOT__sum8), 2U) 
                                                    << 0x10U) 
                                                   | (0xffffU 
                                                      & ((IData)(3U) 
                                                         * (IData)(vlSelfRef.tb3__DOT__dut__DOT__sum8)))))) 
                                  << 0x20U) | (QData)((IData)(
                                                              ((VL_SHIFTL_III(16,16,32, (IData)(vlSelfRef.tb3__DOT__dut__DOT__sum8), 1U) 
                                                                << 0x10U) 
                                                               | (IData)(vlSelfRef.tb3__DOT__dut__DOT__sum8))))));
    vlSelfRef.tb3__DOT__in = 0xff00ff00ff00ff00ULL;
    co_await vlSelfRef.__VdlySched.delay(0x3e8ULL, 
                                         nullptr, "tb3.sv", 
                                         8);
    VL_WRITEF_NX("%016x\n",0,64,(((QData)((IData)((
                                                   (VL_SHIFTL_III(16,16,32, (IData)(vlSelfRef.tb3__DOT__dut__DOT__sum8), 2U) 
                                                    << 0x10U) 
                                                   | (0xffffU 
                                                      & ((IData)(3U) 
                                                         * (IData)(vlSelfRef.tb3__DOT__dut__DOT__sum8)))))) 
                                  << 0x20U) | (QData)((IData)(
                                                              ((VL_SHIFTL_III(16,16,32, (IData)(vlSelfRef.tb3__DOT__dut__DOT__sum8), 1U) 
                                                                << 0x10U) 
                                                               | (IData)(vlSelfRef.tb3__DOT__dut__DOT__sum8))))));
    VL_FINISH_MT("tb3.sv", 9, "");
}

void Vtb3___024root___act_sequent__TOP__0(Vtb3___024root* vlSelf);

void Vtb3___024root___eval_act(Vtb3___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb3__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb3___024root___eval_act\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VactTriggered.word(0U))) {
        Vtb3___024root___act_sequent__TOP__0(vlSelf);
    }
}

VL_INLINE_OPT void Vtb3___024root___act_sequent__TOP__0(Vtb3___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb3__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb3___024root___act_sequent__TOP__0\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb3__DOT__dut__DOT__sum8 = (0xffffU & 
                                          ((0xffU & (IData)(vlSelfRef.tb3__DOT__in)) 
                                           + ((0xffU 
                                               & (IData)(
                                                         (vlSelfRef.tb3__DOT__in 
                                                          >> 8U))) 
                                              + ((0xffU 
                                                  & (IData)(
                                                            (vlSelfRef.tb3__DOT__in 
                                                             >> 0x10U))) 
                                                 + 
                                                 ((0xffU 
                                                   & (IData)(
                                                             (vlSelfRef.tb3__DOT__in 
                                                              >> 0x18U))) 
                                                  + 
                                                  ((0xffU 
                                                    & (IData)(
                                                              (vlSelfRef.tb3__DOT__in 
                                                               >> 0x20U))) 
                                                   + 
                                                   ((0xffU 
                                                     & (IData)(
                                                               (vlSelfRef.tb3__DOT__in 
                                                                >> 0x28U))) 
                                                    + 
                                                    ((0xffU 
                                                      & (IData)(
                                                                (vlSelfRef.tb3__DOT__in 
                                                                 >> 0x30U))) 
                                                     + 
                                                     (0xffU 
                                                      & (IData)(
                                                                (vlSelfRef.tb3__DOT__in 
                                                                 >> 0x38U)))))))))));
}

void Vtb3___024root___eval_nba(Vtb3___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb3__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb3___024root___eval_nba\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vtb3___024root___act_sequent__TOP__0(vlSelf);
    }
}

void Vtb3___024root___timing_resume(Vtb3___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb3__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb3___024root___timing_resume\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VactTriggered.word(0U))) {
        vlSelfRef.__VdlySched.resume();
    }
}

void Vtb3___024root___eval_triggers__act(Vtb3___024root* vlSelf);

bool Vtb3___024root___eval_phase__act(Vtb3___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb3__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb3___024root___eval_phase__act\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    VlTriggerVec<1> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    Vtb3___024root___eval_triggers__act(vlSelf);
    __VactExecute = vlSelfRef.__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelfRef.__VactTriggered, vlSelfRef.__VnbaTriggered);
        vlSelfRef.__VnbaTriggered.thisOr(vlSelfRef.__VactTriggered);
        Vtb3___024root___timing_resume(vlSelf);
        Vtb3___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vtb3___024root___eval_phase__nba(Vtb3___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb3__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb3___024root___eval_phase__nba\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelfRef.__VnbaTriggered.any();
    if (__VnbaExecute) {
        Vtb3___024root___eval_nba(vlSelf);
        vlSelfRef.__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb3___024root___dump_triggers__nba(Vtb3___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb3___024root___dump_triggers__act(Vtb3___024root* vlSelf);
#endif  // VL_DEBUG

void Vtb3___024root___eval(Vtb3___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb3__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb3___024root___eval\n"); );
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
            Vtb3___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("tb3.sv", 1, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelfRef.__VactIterCount = 0U;
        vlSelfRef.__VactContinue = 1U;
        while (vlSelfRef.__VactContinue) {
            if (VL_UNLIKELY((0x64U < vlSelfRef.__VactIterCount))) {
#ifdef VL_DEBUG
                Vtb3___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("tb3.sv", 1, "", "Active region did not converge.");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
            vlSelfRef.__VactContinue = 0U;
            if (Vtb3___024root___eval_phase__act(vlSelf)) {
                vlSelfRef.__VactContinue = 1U;
            }
        }
        if (Vtb3___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void Vtb3___024root___eval_debug_assertions(Vtb3___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb3__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb3___024root___eval_debug_assertions\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
}
#endif  // VL_DEBUG

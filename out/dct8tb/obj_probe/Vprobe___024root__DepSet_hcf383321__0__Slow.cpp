// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vprobe.h for the primary calling header

#include "Vprobe__pch.h"
#include "Vprobe___024root.h"

VL_ATTR_COLD void Vprobe___024root___eval_static(Vprobe___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vprobe__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vprobe___024root___eval_static\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vprobe___024root___eval_initial__TOP(Vprobe___024root* vlSelf);

VL_ATTR_COLD void Vprobe___024root___eval_initial(Vprobe___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vprobe__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vprobe___024root___eval_initial\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vprobe___024root___eval_initial__TOP(vlSelf);
}

VL_ATTR_COLD void Vprobe___024root___eval_initial__TOP(Vprobe___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vprobe__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vprobe___024root___eval_initial__TOP\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    VL_WRITEF_NX("181 181 126 -36\n",0);
}

VL_ATTR_COLD void Vprobe___024root___eval_final(Vprobe___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vprobe__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vprobe___024root___eval_final\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vprobe___024root___eval_settle(Vprobe___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vprobe__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vprobe___024root___eval_settle\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vprobe___024root___dump_triggers__act(Vprobe___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vprobe__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vprobe___024root___dump_triggers__act\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VactTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vprobe___024root___dump_triggers__nba(Vprobe___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vprobe__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vprobe___024root___dump_triggers__nba\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VnbaTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vprobe___024root___ctor_var_reset(Vprobe___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vprobe__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vprobe___024root___ctor_var_reset\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vprobe.h for the primary calling header

#include "Vprobe__pch.h"
#include "Vprobe__Syms.h"
#include "Vprobe___024root.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vprobe___024root___dump_triggers__act(Vprobe___024root* vlSelf);
#endif  // VL_DEBUG

void Vprobe___024root___eval_triggers__act(Vprobe___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vprobe__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vprobe___024root___eval_triggers__act\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vprobe___024root___dump_triggers__act(vlSelf);
    }
#endif
}

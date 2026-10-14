// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_ext_dct8_top.h for the primary calling header

#include "Vtb_ext_dct8_top__pch.h"
#include "Vtb_ext_dct8_top__Syms.h"
#include "Vtb_ext_dct8_top___024root.h"

VL_INLINE_OPT VlCoroutine Vtb_ext_dct8_top___024root___eval_initial__TOP__Vtiming__0(Vtb_ext_dct8_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb_ext_dct8_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_ext_dct8_top___024root___eval_initial__TOP__Vtiming__0\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    {
        vlSelfRef.tb_ext_dct8_top__DOT__x = 0ULL;
        vlSelfRef.tb_ext_dct8_top__DOT__timeout_cycles = 0x40U;
        vlSelfRef.tb_ext_dct8_top__DOT__cyc = 0U;
        while (VL_LTS_III(32, vlSelfRef.tb_ext_dct8_top__DOT__cyc, vlSelfRef.tb_ext_dct8_top__DOT__timeout_cycles)) {
            if ((0U == vlSelfRef.tb_ext_dct8_top__DOT__cyc)) {
                vlSelfRef.tb_ext_dct8_top__DOT__x = 0x807060504030201ULL;
            } else if ((1U == vlSelfRef.tb_ext_dct8_top__DOT__cyc)) {
                vlSelfRef.tb_ext_dct8_top__DOT__x = 0ULL;
            } else if ((2U == vlSelfRef.tb_ext_dct8_top__DOT__cyc)) {
                vlSelfRef.tb_ext_dct8_top__DOT__x = 0xff00ff00ff00ff00ULL;
            } else if ((3U == vlSelfRef.tb_ext_dct8_top__DOT__cyc)) {
                vlSelfRef.tb_ext_dct8_top__DOT__x = 0x123456789abcdefULL;
            }
            co_await vlSelfRef.__VdlySched.delay(0x3e8ULL, 
                                                 nullptr, 
                                                 "tb/tb_ext_dct8_top.sv", 
                                                 49);
            if ((0U == vlSelfRef.tb_ext_dct8_top__DOT__cyc)) {
                if (VL_UNLIKELY((0x90006c00480024ULL 
                                 != (((QData)((IData)(
                                                      ((VL_SHIFTL_III(16,16,32, (IData)(vlSelfRef.tb_ext_dct8_top__DOT__dut__DOT__u_dct__DOT__sum8), 2U) 
                                                        << 0x10U) 
                                                       | (0xffffU 
                                                          & ((IData)(3U) 
                                                             * (IData)(vlSelfRef.tb_ext_dct8_top__DOT__dut__DOT__u_dct__DOT__sum8)))))) 
                                      << 0x20U) | (QData)((IData)(
                                                                  ((VL_SHIFTL_III(16,16,32, (IData)(vlSelfRef.tb_ext_dct8_top__DOT__dut__DOT__u_dct__DOT__sum8), 1U) 
                                                                    << 0x10U) 
                                                                   | (IData)(vlSelfRef.tb_ext_dct8_top__DOT__dut__DOT__u_dct__DOT__sum8)))))))) {
                    VL_WRITEF_NX("[%0t] %%Fatal: tb_ext_dct8_top.sv:54: Assertion failed in %Ntb_ext_dct8_top.__pyc_tb_main: y mismatch\n",0,
                                 64,VL_TIME_UNITED_Q(1000),
                                 -9,vlSymsp->name());
                    VL_STOP_MT("tb/tb_ext_dct8_top.sv", 54, "", false);
                }
            } else if ((1U == vlSelfRef.tb_ext_dct8_top__DOT__cyc)) {
                if (VL_UNLIKELY((0ULL != (((QData)((IData)(
                                                           ((VL_SHIFTL_III(16,16,32, (IData)(vlSelfRef.tb_ext_dct8_top__DOT__dut__DOT__u_dct__DOT__sum8), 2U) 
                                                             << 0x10U) 
                                                            | (0xffffU 
                                                               & ((IData)(3U) 
                                                                  * (IData)(vlSelfRef.tb_ext_dct8_top__DOT__dut__DOT__u_dct__DOT__sum8)))))) 
                                           << 0x20U) 
                                          | (QData)((IData)(
                                                            ((VL_SHIFTL_III(16,16,32, (IData)(vlSelfRef.tb_ext_dct8_top__DOT__dut__DOT__u_dct__DOT__sum8), 1U) 
                                                              << 0x10U) 
                                                             | (IData)(vlSelfRef.tb_ext_dct8_top__DOT__dut__DOT__u_dct__DOT__sum8)))))))) {
                    VL_WRITEF_NX("[%0t] %%Fatal: tb_ext_dct8_top.sv:57: Assertion failed in %Ntb_ext_dct8_top.__pyc_tb_main: y mismatch\n",0,
                                 64,VL_TIME_UNITED_Q(1000),
                                 -9,vlSymsp->name());
                    VL_STOP_MT("tb/tb_ext_dct8_top.sv", 57, "", false);
                }
            } else if ((2U == vlSelfRef.tb_ext_dct8_top__DOT__cyc)) {
                if (VL_UNLIKELY((0xff00bf407f803fcULL 
                                 != (((QData)((IData)(
                                                      ((VL_SHIFTL_III(16,16,32, (IData)(vlSelfRef.tb_ext_dct8_top__DOT__dut__DOT__u_dct__DOT__sum8), 2U) 
                                                        << 0x10U) 
                                                       | (0xffffU 
                                                          & ((IData)(3U) 
                                                             * (IData)(vlSelfRef.tb_ext_dct8_top__DOT__dut__DOT__u_dct__DOT__sum8)))))) 
                                      << 0x20U) | (QData)((IData)(
                                                                  ((VL_SHIFTL_III(16,16,32, (IData)(vlSelfRef.tb_ext_dct8_top__DOT__dut__DOT__u_dct__DOT__sum8), 1U) 
                                                                    << 0x10U) 
                                                                   | (IData)(vlSelfRef.tb_ext_dct8_top__DOT__dut__DOT__u_dct__DOT__sum8)))))))) {
                    VL_WRITEF_NX("[%0t] %%Fatal: tb_ext_dct8_top.sv:60: Assertion failed in %Ntb_ext_dct8_top.__pyc_tb_main: y mismatch\n",0,
                                 64,VL_TIME_UNITED_Q(1000),
                                 -9,vlSymsp->name());
                    VL_STOP_MT("tb/tb_ext_dct8_top.sv", 60, "", false);
                }
            } else if ((3U == vlSelfRef.tb_ext_dct8_top__DOT__cyc)) {
                if (VL_UNLIKELY((0xf000b40078003c0ULL 
                                 != (((QData)((IData)(
                                                      ((VL_SHIFTL_III(16,16,32, (IData)(vlSelfRef.tb_ext_dct8_top__DOT__dut__DOT__u_dct__DOT__sum8), 2U) 
                                                        << 0x10U) 
                                                       | (0xffffU 
                                                          & ((IData)(3U) 
                                                             * (IData)(vlSelfRef.tb_ext_dct8_top__DOT__dut__DOT__u_dct__DOT__sum8)))))) 
                                      << 0x20U) | (QData)((IData)(
                                                                  ((VL_SHIFTL_III(16,16,32, (IData)(vlSelfRef.tb_ext_dct8_top__DOT__dut__DOT__u_dct__DOT__sum8), 1U) 
                                                                    << 0x10U) 
                                                                   | (IData)(vlSelfRef.tb_ext_dct8_top__DOT__dut__DOT__u_dct__DOT__sum8)))))))) {
                    VL_WRITEF_NX("[%0t] %%Fatal: tb_ext_dct8_top.sv:63: Assertion failed in %Ntb_ext_dct8_top.__pyc_tb_main: y mismatch\n",0,
                                 64,VL_TIME_UNITED_Q(1000),
                                 -9,vlSymsp->name());
                    VL_STOP_MT("tb/tb_ext_dct8_top.sv", 63, "", false);
                }
            }
            if (VL_UNLIKELY((4U == vlSelfRef.tb_ext_dct8_top__DOT__cyc))) {
                VL_WRITEF_NX("OK\n",0);
                VL_FINISH_MT("tb/tb_ext_dct8_top.sv", 70, "");
                goto __Vlabel1;
            }
            vlSelfRef.tb_ext_dct8_top__DOT__cyc = ((IData)(1U) 
                                                   + vlSelfRef.tb_ext_dct8_top__DOT__cyc);
        }
        __Vlabel1: ;
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_ext_dct8_top___024root___dump_triggers__act(Vtb_ext_dct8_top___024root* vlSelf);
#endif  // VL_DEBUG

void Vtb_ext_dct8_top___024root___eval_triggers__act(Vtb_ext_dct8_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb_ext_dct8_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_ext_dct8_top___024root___eval_triggers__act\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered.set(0U, vlSelfRef.__VdlySched.awaitingCurrentTime());
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtb_ext_dct8_top___024root___dump_triggers__act(vlSelf);
    }
#endif
}

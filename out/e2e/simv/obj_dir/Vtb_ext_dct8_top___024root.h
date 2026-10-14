// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtb_ext_dct8_top.h for the primary calling header

#ifndef VERILATED_VTB_EXT_DCT8_TOP___024ROOT_H_
#define VERILATED_VTB_EXT_DCT8_TOP___024ROOT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vtb_ext_dct8_top__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtb_ext_dct8_top___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __VactContinue;
    SData/*15:0*/ tb_ext_dct8_top__DOT__dut__DOT__u_dct__DOT__sum8;
    IData/*31:0*/ tb_ext_dct8_top__DOT__timeout_cycles;
    IData/*31:0*/ tb_ext_dct8_top__DOT__cyc;
    IData/*31:0*/ __VactIterCount;
    QData/*63:0*/ tb_ext_dct8_top__DOT__x;
    VlDelayScheduler __VdlySched;
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<1> __VactTriggered;
    VlTriggerVec<1> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vtb_ext_dct8_top__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vtb_ext_dct8_top___024root(Vtb_ext_dct8_top__Syms* symsp, const char* v__name);
    ~Vtb_ext_dct8_top___024root();
    VL_UNCOPYABLE(Vtb_ext_dct8_top___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard

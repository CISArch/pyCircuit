// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtb3.h for the primary calling header

#ifndef VERILATED_VTB3___024ROOT_H_
#define VERILATED_VTB3___024ROOT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vtb3__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtb3___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __VactContinue;
    SData/*15:0*/ tb3__DOT__dut__DOT__sum8;
    IData/*31:0*/ __VactIterCount;
    QData/*63:0*/ tb3__DOT__in;
    VlDelayScheduler __VdlySched;
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<1> __VactTriggered;
    VlTriggerVec<1> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vtb3__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vtb3___024root(Vtb3__Syms* symsp, const char* v__name);
    ~Vtb3___024root();
    VL_UNCOPYABLE(Vtb3___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard

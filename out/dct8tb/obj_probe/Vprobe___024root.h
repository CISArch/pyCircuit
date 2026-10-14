// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vprobe.h for the primary calling header

#ifndef VERILATED_VPROBE___024ROOT_H_
#define VERILATED_VPROBE___024ROOT_H_  // guard

#include "verilated.h"


class Vprobe__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vprobe___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    CData/*0:0*/ __VactContinue;
    IData/*31:0*/ __VactIterCount;
    VlTriggerVec<0> __VactTriggered;
    VlTriggerVec<0> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vprobe__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vprobe___024root(Vprobe__Syms* symsp, const char* v__name);
    ~Vprobe___024root();
    VL_UNCOPYABLE(Vprobe___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard

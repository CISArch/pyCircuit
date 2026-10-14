// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vprobe.h for the primary calling header

#include "Vprobe__pch.h"
#include "Vprobe__Syms.h"
#include "Vprobe___024root.h"

void Vprobe___024root___ctor_var_reset(Vprobe___024root* vlSelf);

Vprobe___024root::Vprobe___024root(Vprobe__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vprobe___024root___ctor_var_reset(this);
}

void Vprobe___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vprobe___024root::~Vprobe___024root() {
}

// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb3.h for the primary calling header

#include "Vtb3__pch.h"
#include "Vtb3__Syms.h"
#include "Vtb3___024root.h"

void Vtb3___024root___ctor_var_reset(Vtb3___024root* vlSelf);

Vtb3___024root::Vtb3___024root(Vtb3__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , __VdlySched{*symsp->_vm_contextp__}
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vtb3___024root___ctor_var_reset(this);
}

void Vtb3___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vtb3___024root::~Vtb3___024root() {
}

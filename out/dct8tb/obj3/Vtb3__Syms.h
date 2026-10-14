// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VTB3__SYMS_H_
#define VERILATED_VTB3__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vtb3.h"

// INCLUDE MODULE CLASSES
#include "Vtb3___024root.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES)Vtb3__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vtb3* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vtb3___024root                 TOP;

    // CONSTRUCTORS
    Vtb3__Syms(VerilatedContext* contextp, const char* namep, Vtb3* modelp);
    ~Vtb3__Syms();

    // METHODS
    const char* name() { return TOP.name(); }
};

#endif  // guard

// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VTB_EXT_DCT8_TOP__SYMS_H_
#define VERILATED_VTB_EXT_DCT8_TOP__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vtb_ext_dct8_top.h"

// INCLUDE MODULE CLASSES
#include "Vtb_ext_dct8_top___024root.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES)Vtb_ext_dct8_top__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vtb_ext_dct8_top* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vtb_ext_dct8_top___024root     TOP;

    // SCOPE NAMES
    VerilatedScope __Vscope_tb_ext_dct8_top;
    VerilatedScope __Vscope_tb_ext_dct8_top_____05Fpyc_tb_main;

    // CONSTRUCTORS
    Vtb_ext_dct8_top__Syms(VerilatedContext* contextp, const char* namep, Vtb_ext_dct8_top* modelp);
    ~Vtb_ext_dct8_top__Syms();

    // METHODS
    const char* name() { return TOP.name(); }
};

#endif  // guard

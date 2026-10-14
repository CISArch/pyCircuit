// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table implementation internals

#include "Vtb_ext_dct8_top__pch.h"
#include "Vtb_ext_dct8_top.h"
#include "Vtb_ext_dct8_top___024root.h"

// FUNCTIONS
Vtb_ext_dct8_top__Syms::~Vtb_ext_dct8_top__Syms()
{
}

Vtb_ext_dct8_top__Syms::Vtb_ext_dct8_top__Syms(VerilatedContext* contextp, const char* namep, Vtb_ext_dct8_top* modelp)
    : VerilatedSyms{contextp}
    // Setup internal state of the Syms class
    , __Vm_modelp{modelp}
    // Setup module instances
    , TOP{this, namep}
{
        // Check resources
        Verilated::stackCheck(18);
    // Configure time unit / time precision
    _vm_contextp__->timeunit(-9);
    _vm_contextp__->timeprecision(-12);
    // Setup each module's pointers to their submodules
    // Setup each module's pointer back to symbol table (for public functions)
    TOP.__Vconfigure(true);
    // Setup scopes
    __Vscope_tb_ext_dct8_top.configure(this, name(), "tb_ext_dct8_top", "tb_ext_dct8_top", "<null>", -9, VerilatedScope::SCOPE_OTHER);
    __Vscope_tb_ext_dct8_top_____05Fpyc_tb_main.configure(this, name(), "tb_ext_dct8_top.__pyc_tb_main", "__pyc_tb_main", "<null>", -9, VerilatedScope::SCOPE_OTHER);
}

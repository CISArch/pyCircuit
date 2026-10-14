// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vtb3__pch.h"

//============================================================
// Constructors

Vtb3::Vtb3(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vtb3__Syms(contextp(), _vcname__, this)}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vtb3::Vtb3(const char* _vcname__)
    : Vtb3(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vtb3::~Vtb3() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vtb3___024root___eval_debug_assertions(Vtb3___024root* vlSelf);
#endif  // VL_DEBUG
void Vtb3___024root___eval_static(Vtb3___024root* vlSelf);
void Vtb3___024root___eval_initial(Vtb3___024root* vlSelf);
void Vtb3___024root___eval_settle(Vtb3___024root* vlSelf);
void Vtb3___024root___eval(Vtb3___024root* vlSelf);

void Vtb3::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vtb3::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vtb3___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vtb3___024root___eval_static(&(vlSymsp->TOP));
        Vtb3___024root___eval_initial(&(vlSymsp->TOP));
        Vtb3___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vtb3___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vtb3::eventsPending() { return !vlSymsp->TOP.__VdlySched.empty(); }

uint64_t Vtb3::nextTimeSlot() { return vlSymsp->TOP.__VdlySched.nextTimeSlot(); }

//============================================================
// Utilities

const char* Vtb3::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vtb3___024root___eval_final(Vtb3___024root* vlSelf);

VL_ATTR_COLD void Vtb3::final() {
    Vtb3___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vtb3::hierName() const { return vlSymsp->name(); }
const char* Vtb3::modelName() const { return "Vtb3"; }
unsigned Vtb3::threads() const { return 1; }
void Vtb3::prepareClone() const { contextp()->prepareClone(); }
void Vtb3::atClone() const {
    contextp()->threadPoolpOnClone();
}

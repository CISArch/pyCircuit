// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vprobe__pch.h"

//============================================================
// Constructors

Vprobe::Vprobe(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vprobe__Syms(contextp(), _vcname__, this)}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vprobe::Vprobe(const char* _vcname__)
    : Vprobe(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vprobe::~Vprobe() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vprobe___024root___eval_debug_assertions(Vprobe___024root* vlSelf);
#endif  // VL_DEBUG
void Vprobe___024root___eval_static(Vprobe___024root* vlSelf);
void Vprobe___024root___eval_initial(Vprobe___024root* vlSelf);
void Vprobe___024root___eval_settle(Vprobe___024root* vlSelf);
void Vprobe___024root___eval(Vprobe___024root* vlSelf);

void Vprobe::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vprobe::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vprobe___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vprobe___024root___eval_static(&(vlSymsp->TOP));
        Vprobe___024root___eval_initial(&(vlSymsp->TOP));
        Vprobe___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vprobe___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vprobe::eventsPending() { return false; }

uint64_t Vprobe::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vprobe::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vprobe___024root___eval_final(Vprobe___024root* vlSelf);

VL_ATTR_COLD void Vprobe::final() {
    Vprobe___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vprobe::hierName() const { return vlSymsp->name(); }
const char* Vprobe::modelName() const { return "Vprobe"; }
unsigned Vprobe::threads() const { return 1; }
void Vprobe::prepareClone() const { contextp()->prepareClone(); }
void Vprobe::atClone() const {
    contextp()->threadPoolpOnClone();
}

#pragma once
// pyCircuit external-module C++ binding contract (docs/external-modules.md).
//
// The C++ backend binds a user-provided class named after the ext symbol:
//   struct <name> {
//     pyc::cpp::Wire<W> <port>;   // one member per manifest port
//     void eval();                // combinational view
//     void tick_compute();        // sequential phase 1 (empty for stateless)
//     void tick_commit();         // sequential phase 2 (empty for stateless)
//     template <class TbT, class EnabledInstT, class EnabledSigT>
//     void pyc_trace_vcd(TbT&, const std::string&,
//                        EnabledInstT&&, EnabledSigT&&);
//     void pyc_register_probes(pyc::cpp::ProbeRegistry&, const std::string&);
//   };
//
// ALL of these member functions are part of the binding contract: the
// generated simulator calls them directly through the wrappers below, so a
// missing member is a hard compile error in the generated model. Stateless
// modules simply provide empty tick_compute/tick_commit bodies; trace/probe
// hooks may be empty too.
//
// The wrappers unwrap std::unique_ptr because generated members are declared
// as std::unique_ptr<ChildType>; the call must reach the user class itself.

#include <memory>
#include <string>

namespace pyc::cpp {

template <typename T>
inline void ext_tick_compute(T &m) { m.tick_compute(); }
template <typename T>
inline void ext_tick_commit(T &m) { m.tick_commit(); }

template <typename T>
inline T &ext_deref(T &child) { return child; }
template <typename T>
inline T &ext_deref(std::unique_ptr<T> &child) { return *child; }

template <typename T, typename TbT, typename EI, typename ES>
inline void ext_trace_child(T &child, TbT &tb, const std::string &full,
                            EI &&enabledInst, ES &&enabledSig) {
  ext_deref(child).pyc_trace_vcd(tb, full, enabledInst, enabledSig);
}

template <typename T, typename R>
inline void ext_register_child(T &child, R &reg, const std::string &prefix) {
  ext_deref(child).pyc_register_probes(reg, prefix);
}

} // namespace pyc::cpp

#pragma once
// pyCircuit external-module C++ binding contract (docs/external-modules.md).
//
// The C++ backend binds a user-provided class named after the ext symbol:
//   struct <name> {
//     pyc::cpp::Wire<W> <port>;   // one member per manifest port
//     void eval();                // required — same-cycle (combinational) view
//     void tick_compute();        // optional: both present => the instance is
//     void tick_commit();         // scheduled into the tick phase (stateful)
//   };
// Optional capability hooks (same signatures as generated SimObjects):
//   template <class TbT, class EnabledInstT, class EnabledSigT>
//   void pyc_trace_vcd(TbT&, const std::string&, EnabledInstT&&, EnabledSigT&&);
//   void pyc_register_probes(pyc::cpp::ProbeRegistry&, const std::string&);
//
// Generated code calls the optional hooks through the helpers below, which
// degrade to no-ops when the user class does not provide them (C++17).

#include <cstdint>
#include <string>
#include <type_traits>

namespace pyc::cpp {

// --- tick capability -------------------------------------------------------
template <typename T, typename = void>
struct has_tick : std::false_type {};
template <typename T>
struct has_tick<T, std::void_t<decltype(std::declval<T &>().tick_compute(),
                                        std::declval<T &>().tick_commit())>>
    : std::true_type {};

template <bool HasTick, typename T>
inline void tick_compute_impl(T &m, std::true_type) { m.tick_compute(); }
template <bool HasTick, typename T>
inline void tick_compute_impl(T &, std::false_type) {}
template <typename T>
inline void ext_tick_compute(T &m) {
  tick_compute_impl<has_tick<T>::value>(m, has_tick<T>{});
}

template <bool HasTick, typename T>
inline void tick_commit_impl(T &m, std::true_type) { m.tick_commit(); }
template <bool HasTick, typename T>
inline void tick_commit_impl(T &, std::false_type) {}
template <typename T>
inline void ext_tick_commit(T &m) {
  tick_commit_impl<has_tick<T>::value>(m, has_tick<T>{});
}

// --- trace/probe capability (detected via expression SFINAE) ---------------
template <typename T, typename TbT, typename EI, typename ES, typename = void>
struct has_trace : std::false_type {};
template <typename T, typename TbT, typename EI, typename ES>
struct has_trace<T, TbT, EI, ES,
                 std::void_t<decltype(std::declval<T &>().pyc_trace_vcd(
                     std::declval<TbT &>(), std::declval<const std::string &>(),
                     std::declval<EI>(), std::declval<ES>()))>> : std::true_type {
};

template <typename T, typename R, typename P, typename = void>
struct has_probe : std::false_type {};
template <typename T, typename R, typename P>
struct has_probe<T, R, P,
                 std::void_t<decltype(std::declval<T &>().pyc_register_probes(
                     std::declval<R &>(), std::declval<const std::string &>()))>>
    : std::true_type {};

template <typename T, typename TbT, typename EI, typename ES>
inline void ext_trace_child(T &child, TbT &tb, const std::string &full, EI &&ei, ES &&es) {
  trace_dispatch(child, tb, full, ei, es,
                 has_trace<T, TbT, EI, ES>{});
}
template <typename T, typename TbT, typename EI, typename ES>
inline void trace_dispatch(T &child, TbT &tb, const std::string &full, EI &&ei, ES &&es,
                           std::true_type) {
  child.pyc_trace_vcd(tb, full, ei, es);
}
template <typename T, typename TbT, typename EI, typename ES>
inline void trace_dispatch(T &, TbT &, const std::string &, EI &&, ES &&, std::false_type) {}

template <typename T, typename R>
inline void ext_register_child(T &child, R &reg, const std::string &prefix) {
  probe_dispatch(child, reg, prefix, has_probe<T, R, std::string>{});
}
template <typename T, typename R>
inline void probe_dispatch(T &child, R &reg, const std::string &prefix, std::true_type) {
  child.pyc_register_probes(reg, prefix);
}
template <typename T, typename R>
inline void probe_dispatch(T &, R &, const std::string &, std::false_type) {}

} // namespace pyc::cpp

// pyCircuit C++ emission (prototype)
#include <array>
#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
#include <type_traits>
#include <cpp/pyc_sim.hpp>
#include <cpp/pyc_change_scheduler.hpp>
#include <cpp/pyc_ext.hpp>

namespace pyc::gen {

struct ext_dct8_top {
  static constexpr const char *_pyc_change_schedule_schema = "pyc.change_schedule.v1";
  static constexpr unsigned _pyc_change_schedule_node_count = 1u;
  static constexpr std::array<unsigned, 1> _pyc_change_schedule_rank{{0u}};
  static constexpr std::array<unsigned, 1> _pyc_change_schedule_slot{{0u}};

  pyc::cpp::Wire<1> clk{};
  pyc::cpp::Wire<1> rst{};
  pyc::cpp::Wire<64> x{};
  pyc::cpp::Wire<64> y{};

  pyc::cpp::Wire<1> pyc_constant_1{};
  pyc::cpp::Wire<64> pyc_instance_2{};

  // Sub-modules.
  pyc::cpp::ExtCallCtx u_dct_ctx{"ext_dct8"};

  // Sub-module eval cache (default-on in C++; can be disabled with
  // -DPYC_DISABLE_INSTANCE_EVAL_CACHE).
  bool u_dct_eval_cache_valid = false;
  pyc::cpp::Wire<64> u_dct_eval_cache_in_0{};
  std::uint64_t u_dct_eval_cache_in_ver_0 = 1ull;
  std::uint64_t u_dct_eval_cache_in_seen_ver_0 = 0ull;
  std::uint64_t u_dct_eval_cache_in_fp_0 = 0ull;
  pyc::cpp::Wire<1> u_dct_eval_cache_in_1{};
  std::uint64_t u_dct_eval_cache_in_ver_1 = 1ull;
  std::uint64_t u_dct_eval_cache_in_seen_ver_1 = 0ull;
  std::uint64_t u_dct_eval_cache_in_fp_1 = 0ull;

  template <typename TbT, typename EnabledInstT, typename EnabledSigT>
  void pyc_trace_vcd(TbT &tb, const std::string &prefix, EnabledInstT &&enabledInst, EnabledSigT &&enabledSig) {
    std::string inst = pyc::cpp::shortenInstancePath(prefix);
    auto trace_port = [&](auto &sig, const char *leaf) {
      std::string p = inst;
      p += ":";
      p += leaf;
      if (enabledSig(p)) tb.vcdTrace(sig, p);
    };
    trace_port(clk, "clk");
    trace_port(rst, "rst");
    trace_port(x, "x");
    trace_port(y, "y");
    auto trace_child = [&](auto &child, const char *seg) {
      std::string full = prefix;
      full += ".";
      full += seg;
      std::string inst_path = pyc::cpp::shortenInstancePath(full);
      if (enabledInst(inst_path) && child) child->pyc_trace_vcd(tb, full, enabledInst, enabledSig);
    };
  }

  void pyc_register_probes(pyc::cpp::ProbeRegistry &reg, const std::string &prefix) {
    std::string inst = pyc::cpp::shortenInstancePath(prefix);
    auto reg_path = [&](const char *leaf) {
      std::string p = inst;
      p += ":";
      p += leaf;
      return p;
    };
    reg.addWire<1>(reg_path("clk"), &clk);
    reg.addWire<1>(reg_path("rst"), &rst);
    reg.addWire<64>(reg_path("x"), &x);
    reg.addWire<64>(reg_path("y"), &y);
    auto reg_child = [&](auto &child, const char *seg) {
      std::string p = prefix;
      p += ".";
      p += seg;
      if (child) child->pyc_register_probes(reg, p);
    };
  }


  // State-source snapshots used by dirty tick_compute.
  bool u_dct_tick_inputs_valid = false;
  pyc::cpp::Wire<64> u_dct_tick_input_0{};
  pyc::cpp::Wire<1> u_dct_tick_input_1{};

  bool _pyc_sim_fast_enable = false;
  std::uint64_t _pyc_cycle = 0;

  static bool _pyc_parse_bool_env(const char *name, bool dflt = false) {
    const char *v = std::getenv(name);
    if (!v || !*v)
      return dflt;
    if (v[0] == '0')
      return false;
    if (v[0] == '1')
      return true;
    return dflt;
  }

  void _pyc_init_runtime_controls() {
    _pyc_sim_fast_enable = _pyc_parse_bool_env("PYC_SIM_FAST", false);
  }

  void _pyc_validate_primitive_bindings() const {
  }

  ext_dct8_top() {
    _pyc_validate_primitive_bindings();
    _pyc_init_runtime_controls();
    #ifdef PYC_ENABLE_CTOR_EVAL
    eval();
    #endif
  }

  inline void eval_comb_pass() {
    pyc_constant_1 = pyc::cpp::Wire<1>({0x1ull});
  }

  inline bool eval_instance_cached_0() {
    bool _pyc_inst_changed = false;
    u_dct_ctx.ins[0] = static_cast<std::uint64_t>(x.value());
    u_dct_ctx.ins[1] = static_cast<std::uint64_t>(pyc_constant_1.value());
    ext_dct8_eval(nullptr, u_dct_ctx.outs, u_dct_ctx.ins, _pyc_cycle);
    {
      auto _pyc_ext_out = pyc::cpp::Wire<64>(u_dct_ctx.outs[0]);
      if (pyc_instance_2 != _pyc_ext_out) {
        pyc_instance_2 = _pyc_ext_out;
        _pyc_inst_changed = true;
      }
    }
    return _pyc_inst_changed;
  }

  void eval() {
    ++_pyc_cycle;
    pyc_constant_1 = pyc::cpp::Wire<1>({0x1ull});
    eval_instance_cached_0();
    if (y != pyc_instance_2) y = pyc_instance_2;
  }

  inline void tick_compute_part_0() {
  }

  inline void tick_commit_part_0() {
  }

  void tick_compute() {
    // Sub-modules.
    tick_compute_part_0();
    // Local sequential primitives.
  }

  void tick_commit() {
    // Sub-modules.
    tick_commit_part_0();
    // Local sequential primitives.
    // Force re-eval on next eval() only for stateful sub-modules.
  }

  void comb() { eval(); }
  void tick() { tick_compute(); }
  void commit() { tick_commit(); }
  void transfer() { tick_commit(); }
  void step() {
    comb();
    tick();
    commit();
    comb();
  }
};

} // namespace pyc::gen

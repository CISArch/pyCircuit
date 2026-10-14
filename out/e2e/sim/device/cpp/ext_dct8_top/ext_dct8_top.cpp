// pyCircuit C++ emission (split)
#include "ext_dct8_top.hpp"

namespace pyc::gen {

void ext_dct8_top::pyc_register_probes(pyc::cpp::ProbeRegistry &reg, const std::string &prefix) {
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

bool ext_dct8_top::_pyc_parse_bool_env(const char *name, bool dflt ) {
    const char *v = std::getenv(name);
    if (!v || !*v)
      return dflt;
    if (v[0] == '0')
      return false;
    if (v[0] == '1')
      return true;
    return dflt;
  }

void ext_dct8_top::_pyc_init_runtime_controls() {
    _pyc_sim_fast_enable = _pyc_parse_bool_env("PYC_SIM_FAST", false);
  }

void ext_dct8_top::_pyc_validate_primitive_bindings() const {
  }

void ext_dct8_top::eval_comb_pass() {
    pyc_constant_1 = pyc::cpp::Wire<1>({0x1ull});
  }

bool ext_dct8_top::eval_instance_cached_0() {
    bool _pyc_inst_changed = false;
    u_dct_ctx.ins[0] = static_cast<std::uint64_t>(x.value());
    u_dct_ctx.ins[1] = static_cast<std::uint64_t>(pyc_constant_1.value());
    ext_dct8_eval(nullptr, u_dct_ctx.outs.data(), u_dct_ctx.ins.data(), _pyc_cycle);
    {
      auto _pyc_ext_out = pyc::cpp::Wire<64>(u_dct_ctx.outs[0]);
      if (pyc_instance_2 != _pyc_ext_out) {
        pyc_instance_2 = _pyc_ext_out;
        _pyc_inst_changed = true;
      }
    }
    return _pyc_inst_changed;
  }

void ext_dct8_top::eval() {
    ++_pyc_cycle;
    pyc_constant_1 = pyc::cpp::Wire<1>({0x1ull});
    eval_instance_cached_0();
    if (y != pyc_instance_2) y = pyc_instance_2;
  }

void ext_dct8_top::tick_compute_part_0() {
  }

void ext_dct8_top::tick_commit_part_0() {
  }

void ext_dct8_top::tick_compute() {
    // Sub-modules.
    tick_compute_part_0();
    // Local sequential primitives.
  }

void ext_dct8_top::tick_commit() {
    // Sub-modules.
    tick_commit_part_0();
    // Local sequential primitives.
    // Force re-eval on next eval() only for stateful sub-modules.
  }

void ext_dct8_top::comb() { eval(); }

void ext_dct8_top::tick() { tick_compute(); }

void ext_dct8_top::commit() { tick_commit(); }

void ext_dct8_top::transfer() { tick_commit(); }

void ext_dct8_top::step() {
    comb();
    tick();
    commit();
    comb();
  }

} // namespace pyc::gen

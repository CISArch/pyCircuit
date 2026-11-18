// ext_cache.hpp — user-provided class for the ext_cache external module
// (docs/external-modules.md). The class name must match [module] name.
//
// Stateful external module: hit/rdata are the same-cycle combinational view
// (eval), while tag/data arrays and the miss FSM advance in tick_commit.
// This is the ext-module interface's sequential half — ext_dct8 exercises
// only the combinational half.
#pragma once
#include <cpp/pyc_bits.hpp>
#include <cpp/pyc_probe_registry.hpp>
#include <string>
#include "cache_core.hpp"

struct ext_cache {
  // --- manifest ports (same names as ext_cache.toml) ---
  pyc::cpp::Wire<1>   clk;
  pyc::cpp::Wire<1>   rst;
  pyc::cpp::Wire<32>  addr;
  pyc::cpp::Wire<1>   req_valid;
  pyc::cpp::Wire<1>   wr;
  pyc::cpp::Wire<128> wdata;
  pyc::cpp::Wire<16>  wmask;
  pyc::cpp::Wire<1>   resp_ready;
  pyc::cpp::Wire<1>   flush;
  pyc::cpp::Wire<128> rdata;
  pyc::cpp::Wire<1>   hit;
  pyc::cpp::Wire<1>   resp_valid;
  pyc::cpp::Wire<1>   dirty_evict;

  // Whole cache state lives in the reference model.
  ext_cache_core::Model st;
  bool clk_prev = false; // posedge gate state for tick_commit

  ext_cache() { st.reset(); }

private:
  ext_cache_core::Inputs read_inputs() const {
    ext_cache_core::Inputs in;
    in.addr = (std::uint32_t)addr.value();
    in.req_valid = req_valid.toBool();
    in.wr = wr.toBool();
    in.wdata = ext_cache_core::Bits128{wdata.word(0), wdata.word(1)};
    in.wmask = (std::uint16_t)wmask.value();
    in.flush = flush.toBool();
    return in;
  }

public:
  void eval() {
    const ext_cache_core::CombOut o = st.eval(read_inputs());
    rdata = pyc::cpp::Wire<128>({o.rdata.lo, o.rdata.hi});
    hit = pyc::cpp::Wire<1>(o.hit ? 1u : 0u);
    resp_valid = pyc::cpp::Wire<1>(o.resp_valid ? 1u : 0u);
    dirty_evict = pyc::cpp::Wire<1>(o.dirty_evict ? 1u : 0u);
  }

  void tick_compute() {
    // Phase 1: inputs are sampled by the generated input latches; the FSM
    // needs no extra precompute beyond eval().
  }

  void tick_commit() {
    // Clocked module: advance state exactly once per cycle, on the clk
    // posedge (0 -> 1). The runtime calls tick_commit on both clock halves;
    // rst behaves like a synchronous reset.
    const bool now = clk.toBool();
    const bool was_lo = !clk_prev;
    clk_prev = now;
    if (rst.toBool()) {
      st.reset();
      return;
    }
    if (!(was_lo && now))
      return;
    st.tick_commit(read_inputs());
  }

  template <class TbT, class EnabledInstT, class EnabledSigT>
  void pyc_trace_vcd(TbT &tb, const std::string &prefix,
                     EnabledInstT &&, EnabledSigT &&enabledSig) {
    auto trace_port = [&](auto &sig, const char *leaf) {
      std::string p = prefix + ":" + leaf;
      if (enabledSig(p)) tb.vcdTrace(sig, p);
    };
    trace_port(clk, "clk");
    trace_port(addr, "addr");
    trace_port(req_valid, "req_valid");
    trace_port(wr, "wr");
    trace_port(wdata, "wdata");
    trace_port(rdata, "rdata");
    trace_port(hit, "hit");
    trace_port(resp_valid, "resp_valid");
    trace_port(dirty_evict, "dirty_evict");
  }

  void pyc_register_probes(pyc::cpp::ProbeRegistry &reg, const std::string &prefix) {
    reg.addWire(prefix + ":" + "addr", &addr);
    reg.addWire(prefix + ":" + "hit", &hit);
    reg.addWire(prefix + ":" + "resp_valid", &resp_valid);
    reg.addWire(prefix + ":" + "rdata", &rdata);
    reg.addWire(prefix + ":" + "dirty_evict", &dirty_evict);
  }
};

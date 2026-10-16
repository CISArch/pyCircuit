// ext_dct8.hpp — user-provided class for the ext_dct8 external module
// (docs/external-modules.md). The class name must match [module] name; port
// members use pyc::cpp::Wire<width> per the manifest ports.
//
// The binding contract is all-mandatory: eval(), tick_compute(),
// tick_commit(), pyc_trace_vcd(...) and pyc_register_probes(...) must be
// provided (missing members fail to compile in the generated model).
// ext_dct8 is stateless, so the tick bodies are empty and trace/probe simply
// export the three port wires.
#pragma once
#include <cpp/pyc_bits.hpp>
#include <cpp/pyc_probe_registry.hpp>
#include <string>
#include "dct8_core.hpp"  // shared reference datapath with dct8.cpp

struct ext_dct8 {
  pyc::cpp::Wire<64> in;
  pyc::cpp::Wire<1>  valid;
  pyc::cpp::Wire<64> out;

  void eval() { out = pyc::cpp::Wire<64>(dct8_ref_apply(in.value())); }

  // Sequential phases — empty: this module is purely combinational.
  void tick_compute() {}
  void tick_commit() {}

  // VCD trace: same shape as generated SimObjects (Decision 0023 paths).
  template <class TbT, class EnabledInstT, class EnabledSigT>
  void pyc_trace_vcd(TbT &tb, const std::string &prefix,
                     EnabledInstT &&, EnabledSigT &&enabledSig) {
    auto trace_port = [&](auto &sig, const char *leaf) {
      std::string p = prefix + ":" + leaf;
      if (enabledSig(p)) tb.vcdTrace(sig, p);
    };
    trace_port(in, "in");
    trace_port(valid, "valid");
    trace_port(out, "out");
  }

  // Probe registration.
  void pyc_register_probes(pyc::cpp::ProbeRegistry &reg, const std::string &prefix) {
    reg.addWire(prefix + ":" + "in", &in);
    reg.addWire(prefix + ":" + "valid", &valid);
    reg.addWire(prefix + ":" + "out", &out);
  }
};

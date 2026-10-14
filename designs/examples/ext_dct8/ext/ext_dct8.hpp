// ext_dct8.hpp — user-provided class for the ext_dct8 external module
// (docs/external-modules.md). The class name must match [module] name; port
// members use pyc::cpp::Wire<width> per the manifest ports; eval() is required.
#pragma once
#include <cpp/pyc_bits.hpp>
#include "dct8_core.hpp"  // shared reference datapath with dct8.cpp

struct ext_dct8 {
  pyc::cpp::Wire<64> in;
  pyc::cpp::Wire<1>  valid;
  pyc::cpp::Wire<64> out;

  void eval() { out = pyc::cpp::Wire<64>(dct8_ref_apply(in.value())); }
};

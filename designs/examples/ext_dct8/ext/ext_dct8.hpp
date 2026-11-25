// ext_dct8.hpp — user C++ class for the ext_dct8 black box (docs/external-modules.md).
// Class name = [module].name; one Wire<width> member per manifest port.
#pragma once
#include <cstdint>
#include <cpp/pyc_bits.hpp>

std::uint64_t dct8_apply(std::uint64_t x);  // defined in dct8.cpp

struct ext_dct8 {
  pyc::cpp::Wire<64> in;
  pyc::cpp::Wire<1> valid;
  pyc::cpp::Wire<64> out;

  void eval() { out = pyc::cpp::Wire<64>(dct8_apply(in.value())); }

  void tick_compute() {}  // stateless module: empty sequential bodies
  void tick_commit() {}
};

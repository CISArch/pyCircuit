// dct8.cpp — reference C++ model for ext_dct8; discovered from [backends.cpp]
// and linked into the generated simulator (ext_sources).
#include <cpp/pyc_bits.hpp>

#include "ext_dct8.hpp"

std::uint64_t dct8_apply(std::uint64_t x) {
  std::uint64_t out = 0;
  for (unsigned u = 0; u < 4; ++u) {
    unsigned acc = 0;
    for (unsigned b = 0; b < 8; ++b) acc += ((x >> (8 * b)) & 0xFFu) * (u + 1u);
    out |= static_cast<std::uint64_t>(acc & 0xFFFFu) << (16 * u);
  }
  return out;
}

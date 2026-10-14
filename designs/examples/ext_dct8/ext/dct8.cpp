// dct8.cpp — reference C++ implementation of the ext_dct8 black box.
// C ABI contract: runtime/cpp/pyc_ext.hpp (docs/external-modules.md).
//
//   void ext_dct8_eval(void *state, uint64_t *outs, const uint64_t *ins,
//                      uint64_t cycle);
//
// comb module: state is always nullptr, result is same-cycle.
//
// Reference datapath (kept deliberately simple so the three implementations
// — C++, Verilog, and the Python golden — stay bit-exact by inspection):
//   lane_u = sum over x of byte[x] * (u+1), truncated to 16 bits;
//   out packs lanes 0..3 into 16-bit fields (u>=4 wraps onto u&3).
#include <cstdint>

extern "C" void ext_dct8_eval(void * /*state*/, std::uint64_t *outs,
                              const std::uint64_t *ins, std::uint64_t /*cycle*/) {
    const std::uint64_t in = ins[0];
    std::uint64_t out = 0;
    for (unsigned u = 0; u < 4; ++u) {
        std::uint32_t acc = 0;
        for (unsigned x = 0; x < 8; ++x) {
            const std::uint8_t sample = static_cast<std::uint8_t>((in >> (8 * x)) & 0xFFu);
            acc += static_cast<std::uint32_t>(sample) * (u + 1u);
        }
        out |= static_cast<std::uint64_t>(static_cast<std::uint16_t>(acc)) << (16u * u);
    }
    outs[0] = out;
}

// dct8_core.hpp — shared bit-exact reference datapath (C++ model + user class).
#pragma once
#include <cstdint>

inline std::uint64_t dct8_ref_apply(std::uint64_t in) {
    std::uint64_t out = 0;
    for (unsigned u = 0; u < 4; ++u) {
        std::uint32_t acc = 0;
        for (unsigned x = 0; x < 8; ++x) {
            const std::uint8_t sample = static_cast<std::uint8_t>((in >> (8 * x)) & 0xFFu);
            acc += static_cast<std::uint32_t>(sample) * (u + 1u);
        }
        out |= static_cast<std::uint64_t>(static_cast<std::uint16_t>(acc)) << (16u * u);
    }
    return out;
}

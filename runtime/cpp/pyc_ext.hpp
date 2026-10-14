#pragma once
// pyCircuit external-module C ABI contract (docs/external-modules.md).
//
// A user-provided black-box model is linked into the generated simulator as
// plain C symbols named <prefix>_eval (and optionally <prefix>_reset).
//
//   comb module (ext_kind="comb", latency=0, pure=true):
//     void <prefix>_eval(void *state, uint64_t *outs, const uint64_t *ins,
//                        uint64_t cycle);
//     state is always nullptr; the result is same-cycle.
//
//   seq module (ext_kind="seq", latency>=1):
//     size_t <prefix>_state_size();          // bytes of per-instance state
//     void   <prefix>_reset(void *state, const uint64_t *init);
//     void   <prefix>_eval(void *state, uint64_t *outs, const uint64_t *ins,
//                         uint64_t cycle);
//     eval is invoked once per simulated cycle in the tick phase; the module
//     advances its own internal pipeline state. The declared latency tells
//     the change-driven scheduler when the outputs become live.
//
// Widths: every port is flattened to its bit width and transported in 64-bit
// words, little-endian (word 0 holds bits [63:0]). Values narrower than 64
// bits are zero-extended; wider values occupy ceil(w/64) consecutive words.

#include <array>
#include <cstddef>
#include <cstdint>

namespace pyc::cpp {

// Per-instance host-side context for an external module instance. ins/outs
// are generously sized for the prototype port limit (16 ports x 4 words).
inline constexpr unsigned kExtMaxPorts = 16;
inline constexpr unsigned kExtWordsPerPort = 4;

struct ExtCallCtx {
  std::uint64_t cycle = 0;
  void *state = nullptr;
  std::array<std::uint64_t, kExtMaxPorts * kExtWordsPerPort> ins{};
  std::array<std::uint64_t, kExtMaxPorts * kExtWordsPerPort> outs{};
};

} // namespace pyc::cpp

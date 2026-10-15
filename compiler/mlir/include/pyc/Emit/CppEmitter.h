#pragma once

#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/Support/LogicalResult.h"
#include "llvm/Support/raw_ostream.h"

#include <string>

namespace pyc {

struct CppEmitterOptions {
  enum class SplitMode {
    None,
    Module,
  };

  SplitMode splitMode = SplitMode::None;
  unsigned shardThresholdLines = 120000;
  unsigned shardThresholdBytes = 4 * 1024 * 1024;
  // Chunk full-topology eval bodies to avoid mega-functions that are expensive
  // for downstream C++ compilers.
  unsigned evalTopoChunkNodes = 256;
  // Chunk fused comb helpers to avoid single mega-functions that dominate
  // downstream C++ TU cost even after file sharding.
  unsigned combChunkNodes = 256;
  std::string probePlanPath{};
  // Emit the fast-edge negedge branch as module-wide bookkeeping instead of a
  // per-register negedge_update() sweep. Only valid when every register uses
  // the same clock and commit() always consumes pending (tick-fuse mode).
  bool fuseNegedgeReset = false;
  /// Gate the generated tick_commit's local reg/delay-line walk behind a
  /// module-level `_pyc_commit_needed` flag. Modules on a single unique clock
  /// (fastEdge) set it on rising/unchanged tick_compute and leave it clear on
  /// a falling edge, where every local reg/delay-line already has pending==0
  /// and the walk was provably a no-op. Sub-module recursion and clocked
  /// fifo/mem/cdc primitives keep their unconditional tick_commit: they
  /// maintain their own edge state. Off by default for A/B.
  bool fallCommitGate = false;
};

::mlir::LogicalResult emitCpp(::mlir::ModuleOp module, ::llvm::raw_ostream &os,
                              const CppEmitterOptions &opts = {});

::mlir::LogicalResult emitCppFunc(::mlir::ModuleOp module, ::mlir::func::FuncOp f, ::llvm::raw_ostream &os,
                                  const CppEmitterOptions &opts = {});

} // namespace pyc

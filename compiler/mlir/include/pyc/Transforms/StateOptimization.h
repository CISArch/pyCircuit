#pragma once

#include "pyc/Dialect/PYC/PYCOps.h"
#include "pyc/Transforms/Passes.h"

#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/IR/Builders.h"
#include "mlir/IR/BuiltinAttributes.h"
#include "mlir/IR/BuiltinOps.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/StringRef.h"

#include <cstddef>
#include <cstdint>
#include <optional>

namespace pyc {

// Shared stat-attribute helpers for the state-optimization passes.
inline void setI64Attr(mlir::Operation *op, llvm::StringRef name,
                       std::int64_t value) {
  op->setAttr(name, mlir::IntegerAttr::get(
                        mlir::IntegerType::get(op->getContext(), 64), value));
}

/// Stateful ops terminate combinational scheduling: registers, delay lines,
/// memories, FIFOs, CDC syncs, and instance boundaries.
bool isStatefulConsumer(mlir::Operation *op);

/// True for state created by the frontend to balance cycle alignment
/// (`pyc.generated = "cycle_balance"`); such names are compiler temporaries.
bool isCycleBalanceGenerated(mlir::Operation *op);

/// True when `op` carries an identity that probe/VCD/`dut.read` may consume.
/// `cycle_balance` auto-names are excluded; other observation attrs still count.
bool hasExternalObservationIdentity(mlir::Operation *op);

/// True when the state op or any alias of `q` has an external observation
/// identity that must remain readable after a rewrite.
bool stateHasExternalObservation(mlir::Operation *state, mlir::Value q);

/// Copy name/debug/probe/trace/observable attrs, skipping cycle-balance names.
void copyExternalObservationAttrs(mlir::Operation *from, mlir::Operation *to);

/// Attach a read-only alias of `source` that carries `attrSource`'s external
/// observation identity. Used when a rewrite deletes or replaces the physical
/// state but must leave a value for external reads.
pyc::AliasOp materializeObservationAlias(mlir::OpBuilder &builder,
                                         mlir::Location loc, mlir::Value source,
                                         mlir::Operation *attrSource);

/// Materialize observation aliases for identities that live on `oldState`
/// itself. Aliases of `oldQ` are left to RAUW or explicit remap of erased
/// aliases.
void remapStateOpIdentity(mlir::OpBuilder &builder, mlir::Operation *oldState,
                          mlir::Value newSource);

mlir::Value stripStateAliases(mlir::Value value);
bool equivalentStateValue(mlir::Value lhs, mlir::Value rhs);

struct StateChainLink {
  pyc::RegOp predecessor;
  llvm::SmallVector<pyc::AliasOp> aliasesFromConsumerToProducer;
};

/// Match a proven serial state chain: `consumer.next` reaches `keyReg`'s q
/// only through transparent aliases, with equivalent clock/reset/enable/init.
/// Read-only fanout off intermediate stages is allowed; the rewrite turns it
/// into fixed-depth delay taps.
std::optional<StateChainLink>
matchStateChainPredecessor(pyc::RegOp consumer, pyc::RegOp keyReg);

bool equivalentDelayLineState(pyc::DelayLineOp lhs, pyc::DelayLineOp rhs);
std::size_t delayLineStateHash(pyc::DelayLineOp delay);

} // namespace pyc

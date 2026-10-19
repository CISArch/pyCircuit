// Unified C++-path state optimization: one func-level pass that runs the state
// rewrites in a fixed order, so later phases see the result of earlier ones and
// `pycc` needs a single pass-manager entry instead of one entry per rewrite.

#include "pyc/Transforms/Passes.h"

#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Pass/Pass.h"

using namespace mlir;

namespace pyc {
namespace {

struct StateOptimizePass
    : public PassWrapper<StateOptimizePass, OperationPass<func::FuncOp>> {
  MLIR_DEFINE_EXPLICIT_INTERNAL_INLINE_TYPE_ID(StateOptimizePass)

  StringRef getArgument() const override { return "pyc-state-optimize"; }
  StringRef getDescription() const override {
    return "Unified structural state optimization: dead-state cleanup, then "
           "delay-line chain formation with observation identities preserved";
  }

  void runOnOperation() override {
    func::FuncOp function = getOperation();
    runEliminateDeadState(function);
    // Form ordinary direct chains and share equivalent histories.
    runDelayChainFormAndShare(function);
  }
};

} // namespace

std::unique_ptr<::mlir::Pass> createStateOptimizePass() {
  return std::make_unique<StateOptimizePass>();
}

static PassRegistration<StateOptimizePass> pass;

} // namespace pyc

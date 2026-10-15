//===- ShlChainFoldPass.cpp -----------------------------------------------===//
//
// Fold chains of consecutive `pyc.shli {amount = K}` ops into a single shift
// when the intermediate result has exactly one use.
//
//   %a = pyc.shli %x {amount = 1} : i16
//   %b = pyc.shli %a {amount = 8} : i16
//
// becomes
//
//   %b = pyc.shli %x {amount = 9} : i16
//
// Only the operand/amount of the outer op is modified and the inner op is
// dropped, so no new values are introduced and dominance is preserved. Both
// ops are `Pure` and `SameOperandsAndResultType`, so the outer result type is
// unchanged and the combined shift is semantically equivalent.
//
// A chain is collapsed eagerly across its maximal run by re-walking until no
// further fold applies (each pass exposes the newly combined outer shift to
// the next pass, so N consecutive shifts collapse in N-1 steps).
//
//===----------------------------------------------------------------------===//

#include "pyc/Transforms/Passes.h"

#include "pyc/Dialect/PYC/PYCOps.h"

#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/IR/Operation.h"
#include "mlir/IR/OpDefinition.h"
#include "mlir/Pass/Pass.h"

#include <cstdint>
#include <limits>

using namespace mlir;

namespace pyc {
namespace {

struct ShlChainFoldPass
    : public PassWrapper<ShlChainFoldPass, OperationPass<func::FuncOp>> {
  MLIR_DEFINE_EXPLICIT_INTERNAL_INLINE_TYPE_ID(ShlChainFoldPass)

  StringRef getArgument() const override { return "pyc-fold-shl-chains"; }
  StringRef getDescription() const override {
    return "Fold consecutive pyc.shli immediate shifts into one (comb cleanup)";
  }

  void runOnOperation() override {
    func::FuncOp f = getOperation();
    OpBuilder builder(f.getContext());

    bool changed = true;
    while (changed) {
      changed = false;

      // Find one candidate pair per pass; walk only reads, we mutate/erase
      // after the walk returns so the walker never sees a freed op.
      pyc::ShliOp outer;
      pyc::ShliOp inner;
      f.walk([&](pyc::ShliOp op) {
        if (changed)
          return; // already found a fold candidate this pass
        auto def = op.getIn().getDefiningOp<pyc::ShliOp>();
        if (!def || !def->hasOneUse())
          return;
        outer = op;
        inner = def;
        changed = true;
      });

      if (!changed)
        break;

      std::int64_t innerAmt = inner.getAmountAttr().getInt();
      std::int64_t outerAmt = outer.getAmountAttr().getInt();

      // Shift amounts are non-negative immediates; guard against overflow.
      if (innerAmt < 0 || outerAmt < 0)
        break;
      if (innerAmt > std::numeric_limits<std::int64_t>::max() - outerAmt)
        break;

      std::int64_t total = innerAmt + outerAmt;

      // Rewrite the outer op to shift straight from the chain source, then drop
      // the (now single-use-free) intermediate op.
      outer.getInMutable().assign(inner.getIn());
      outer->setAttr("amount", builder.getI64IntegerAttr(total));
      inner.erase();
      // changed already true -> re-walk to continue collapsing the chain.
    }
  }
};

} // namespace

std::unique_ptr<::mlir::Pass> createShlChainFoldPass() {
  return std::make_unique<ShlChainFoldPass>();
}

static PassRegistration<ShlChainFoldPass> pass;

} // namespace pyc
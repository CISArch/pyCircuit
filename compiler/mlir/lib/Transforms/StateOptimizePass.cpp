// Unified C++-path state optimization: one func-level pass that runs the state
// rewrites in a fixed order, so later phases see the result of earlier ones and
// `pycc` needs a single pass-manager entry instead of one entry per rewrite.

#include "pyc/Transforms/Passes.h"

#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/IR/Dominance.h"
#include "mlir/IR/PatternMatch.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Transforms/CSE.h"
#include "mlir/Transforms/GreedyPatternRewriteDriver.h"

using namespace mlir;

namespace pyc {
namespace {

// In-pass replacement for the upstream canonicalize+CSE pass pair: load the
// canonicalization patterns the upstream Canonicalizer initializes, run greedy
// folding on top of them, then dedupe the exposed equivalents with explicit CSE.
static LogicalResult canonicalizeAndCSE(func::FuncOp function) {
  MLIRContext *context = function.getContext();
  RewritePatternSet patterns(context);
  for (Dialect *dialect : context->getLoadedDialects())
    dialect->getCanonicalizationPatterns(patterns);
  for (RegisteredOperationName op : context->getRegisteredOperations())
    op.getCanonicalizationPatterns(patterns, context);
  if (failed(applyPatternsAndFoldGreedily(function, std::move(patterns),
                                          GreedyRewriteConfig())))
    return failure();
  IRRewriter rewriter(context);
  DominanceInfo domInfo(function);
  eliminateCommonSubExpressions(rewriter, domInfo, function);
  return success();
}

struct StateOptimizePass
    : public PassWrapper<StateOptimizePass, OperationPass<func::FuncOp>> {
  MLIR_DEFINE_EXPLICIT_INTERNAL_INLINE_TYPE_ID(StateOptimizePass)

  StateOptimizePass() = default;
  StateOptimizePass(const StateOptimizePass &other)
      : PassWrapper(other), tunables(other.tunables) {}
  explicit StateOptimizePass(const StateOptimizeTunables &tunables)
      : tunables(tunables) {}

  StringRef getArgument() const override { return "pyc-state-optimize"; }
  StringRef getDescription() const override {
    return "Unified structural state optimization: dead-state cleanup, "
           "equivalent-state merge, retime, delay-line chain formation, then "
           "lane packing with "
           "observation identities preserved";
  }

  void runOnOperation() override {
    func::FuncOp function = getOperation();
    runEliminateDeadState(function);
    // Merge equivalent registers before retiming, so a local retime cannot
    // consume a state that has a more profitable equivalent. The first merge
    // can expose equivalent combinational cones, so canonicalize/CSE and run
    // one more merge round.
    runDelayChainMergeRound(function);
    if (failed(canonicalizeAndCSE(function))) {
      signalPassFailure();
      return;
    }
    runDelayChainMergeRound(function);
    runRetimePipelines(function);
    // Sinking moves consumer cones onto source.next, into the same
    // combinational cone as the producers of next. The fusion win (shared
    // subexpressions, one scheduled comb region) only materializes once CSE
    // deduplicates the merged cone, so run it before chain forming.
    if (failed(canonicalizeAndCSE(function))) {
      signalPassFailure();
      return;
    }
    runEliminateDeadState(function);
    // Form ordinary direct chains only after retiming selected the more
    // general computed pipelines; also share equivalent histories here.
    runDelayChainFormAndShare(function);
    // Packing works on the final state set.
    runPackStateLanes(function, tunables.packMaxWidth);
  }

  StateOptimizeTunables tunables;
};

} // namespace

std::unique_ptr<::mlir::Pass>
createStateOptimizePass(const StateOptimizeTunables &tunables) {
  return std::make_unique<StateOptimizePass>(tunables);
}

static PassRegistration<StateOptimizePass> pass;

} // namespace pyc

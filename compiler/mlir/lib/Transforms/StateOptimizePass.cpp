#include "pyc/Transforms/Passes.h"
#include "pyc/Transforms/StateOptimization.h"

#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/IR/PatternMatch.h"
#include "mlir/IR/BuiltinAttributes.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Transforms/GreedyPatternRewriteDriver.h"
#include "mlir/Transforms/CSE.h"
#include "mlir/IR/Dominance.h"
#include "llvm/ADT/STLExtras.h"

using namespace mlir;

namespace pyc {
namespace {

// In-pass replacement for the upstream canonicalize+CSE pass pair pycc used
// between merge rounds: load the same canonicalization patterns that the
// upstream Canonicalizer initializes, run greedy folding on top of them, then
// dedupe the exposed equivalents with explicit CSE.
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
  StateOptimizePass(const StateOptimizePass &other) : PassWrapper(other) {}

  StringRef getArgument() const override { return "pyc-state-optimize"; }
  StringRef getDescription() const override {
    return "Unified structural state optimization: merge, retime, and chain "
           "state with observation identities preserved";
  }

  void runOnOperation() override {
    func::FuncOp function = getOperation();

    // Round 1: low-risk equivalent-state merge.
    const int64_t mergeRoundsBefore =
        getI64Attr(function, "pyc.stats.state_opt_merge_rounds", 0);
    runDelayChainMergeRound(function, /*cascadeRound=*/false,
                            /*accumulateStats=*/false);
    setI64Attr(function, "pyc.stats.state_opt_merge_rounds",
               mergeRoundsBefore + 1);

    // The first state merge can expose equivalent combinational cones.
    // Canonicalize/CSE once, then run one bounded merge refinement.
    if (failed(canonicalizeAndCSE(function))) {
      signalPassFailure();
      return;
    }
    runDelayChainMergeRound(function, /*cascadeRound=*/true,
                            /*accumulateStats=*/true);
    setI64Attr(function, "pyc.stats.state_opt_merge_rounds",
               mergeRoundsBefore + 2);

    // Retime after the two low-risk merge-only rounds: a local retime must
    // not consume a state that has a more profitable global equivalent-state
    // or direct-chain rewrite.
    runRetimePipelines(function);
    // Sinking moves consumer cones onto source.next, placing them in the
    // same combinational cone as the producers of next. The fusion win
    // (shared subexpressions, one scheduled comb region) only materializes
    // once CSE deduplicates the merged cone — run it here so chain
    // forming and history sharing see the deduplicated values
    // instead of structurally-identical duplicates.
    if (failed(canonicalizeAndCSE(function))) {
      signalPassFailure();
      return;
    }
    runEliminateDeadState(function);
    // Form ordinary direct chains only after retiming selected the more
    // general computed pipelines; also share equivalent histories here.
    runDelayChainFormAndShare(function, /*accumulateStats=*/true);
  }
};

} // namespace

std::unique_ptr<::mlir::Pass> createStateOptimizePass() {
  return std::make_unique<StateOptimizePass>();
}

static PassRegistration<StateOptimizePass> pass;

} // namespace pyc

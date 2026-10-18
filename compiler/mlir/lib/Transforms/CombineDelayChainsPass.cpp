// Form compact delay-line state from proven serial register chains. Every
// register is a candidate once the sequential proof holds: equivalent state is
// merged first, and untagged chains are admitted just like cycle-balance ones.
// External observation identities are remapped onto survivor / delay-line /
// delay-tap views instead of blocking the rewrite.

#include "pyc/Transforms/Passes.h"
#include "pyc/Transforms/StateOptimization.h"

#include "pyc/Dialect/PYC/PYCOps.h"

#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/IR/Builders.h"
#include "mlir/IR/BuiltinTypes.h"
#include "mlir/Pass/Pass.h"
#include "llvm/ADT/DenseMap.h"
#include "llvm/ADT/DenseSet.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/ADT/SmallVector.h"

#include <cstddef>

using namespace mlir;

namespace pyc {
namespace {

constexpr llvm::StringLiteral kOptimizedByAttr = "pyc.optimized_by";
constexpr llvm::StringLiteral kStructuralCombineDelayChains =
    "combine_delay_chains_structural";
constexpr llvm::StringLiteral kSourceRegCountAttr = "pyc.source_reg_count";
constexpr llvm::StringLiteral kSharedChainCountAttr = "pyc.shared_chain_count";

struct CombineStats {
  int64_t chainsCombined = 0;
  int64_t regsCombined = 0;
  int64_t aliasesRemoved = 0;
  int64_t delayLinesCreated = 0;
  int64_t delayLinesMerged = 0;
  int64_t stateRegsMerged = 0;
  int64_t stateRegBitsRemoved = 0;
  int64_t delayTapsCreated = 0;
  int64_t delayTapUsesRewritten = 0;
};

static int64_t stateBitWidth(Type type) {
  if (auto integer = dyn_cast<IntegerType>(type))
    return static_cast<int64_t>(integer.getWidth());
  if (auto vector = dyn_cast<VectorType>(type)) {
    int64_t lanes = 1;
    for (int64_t dimension : vector.getShape())
      lanes *= dimension;
    if (auto element = dyn_cast<IntegerType>(vector.getElementType()))
      return lanes * static_cast<int64_t>(element.getWidth());
  }
  return 0;
}

static void mergeEquivalentStates(func::FuncOp function, CombineStats &stats) {
  llvm::SmallVector<pyc::RegOp> regs;
  function.walk([&](pyc::RegOp reg) { regs.push_back(reg); });

  llvm::DenseMap<std::size_t, llvm::SmallVector<pyc::RegOp>> buckets;
  for (pyc::RegOp reg : regs) {
    auto &bucket = buckets[registerStateHash(reg)];
    pyc::RegOp survivor;
    for (pyc::RegOp existing : bucket) {
      if (equivalentRegisterState(existing, reg)) {
        survivor = existing;
        break;
      }
    }
    if (!survivor) {
      bucket.push_back(reg);
      continue;
    }

    OpBuilder builder(survivor);
    builder.setInsertionPointAfter(survivor);
    remapStateOpIdentity(builder, reg.getOperation(), survivor.getQ());
    reg.getQ().replaceAllUsesWith(survivor.getQ());
    survivor->setAttr(kOptimizedByAttr,
                      StringAttr::get(function.getContext(),
                                      "merge_equivalent_state"));
    ++stats.stateRegsMerged;
    stats.stateRegBitsRemoved += stateBitWidth(reg.getQ().getType());
    reg.erase();
  }
}

static void combineStateChains(func::FuncOp function, CombineStats &stats) {
  llvm::SmallVector<pyc::RegOp> regs;
  function.walk([&](pyc::RegOp reg) { regs.push_back(reg); });

  llvm::DenseSet<Operation *> erased;
  for (pyc::RegOp tail : llvm::reverse(regs)) {
    if (erased.contains(tail.getOperation()))
      continue;

    llvm::SmallVector<pyc::RegOp> chainFromTail{tail};
    llvm::SmallVector<StateChainLink> linksFromTail;
    pyc::RegOp cursor = tail;
    while (auto link = matchStateChainPredecessor(cursor, tail)) {
      if (erased.contains(link->predecessor.getOperation()))
        break;
      linksFromTail.push_back(*link);
      cursor = link->predecessor;
      chainFromTail.push_back(cursor);
    }
    if (chainFromTail.size() < 2)
      continue;

    // Preflight all intermediate fanout before creating the replacement. A
    // second stateful consumer cannot be represented by a read-only tap.
    bool hasIllegalFanout = false;
    for (unsigned i = 1; i < chainFromTail.size() && !hasIllegalFanout; ++i) {
      pyc::RegOp reg = chainFromTail[i];
      const StateChainLink &link = linksFromTail[i - 1];
      Operation *requiredUser = nullptr;
      if (link.aliasesFromConsumerToProducer.empty()) {
        requiredUser = chainFromTail[i - 1].getOperation();
      } else {
        pyc::AliasOp requiredAlias =
            link.aliasesFromConsumerToProducer.back();
        requiredUser = requiredAlias.getOperation();
      }
      for (Operation *user : reg.getQ().getUsers()) {
        if (user != requiredUser && isStatefulConsumer(user)) {
          hasIllegalFanout = true;
          break;
        }
      }
      for (auto aliasIt = link.aliasesFromConsumerToProducer.rbegin();
           aliasIt != link.aliasesFromConsumerToProducer.rend() &&
           !hasIllegalFanout;
           ++aliasIt) {
        pyc::AliasOp alias = *aliasIt;
        auto nextAlias = std::next(aliasIt);
        if (nextAlias == link.aliasesFromConsumerToProducer.rend()) {
          requiredUser = chainFromTail[i - 1].getOperation();
        } else {
          pyc::AliasOp nextAliasOp = *nextAlias;
          requiredUser = nextAliasOp.getOperation();
        }
        for (Operation *user : alias.getResult().getUsers()) {
          if (user != requiredUser && isStatefulConsumer(user)) {
            hasIllegalFanout = true;
            break;
          }
        }
      }
    }
    if (hasIllegalFanout)
      continue;

    const int64_t depth = static_cast<int64_t>(chainFromTail.size());
    pyc::RegOp head = chainFromTail.back();
    const bool allGenerated = llvm::all_of(
        chainFromTail,
        [](pyc::RegOp reg) { return isCycleBalanceGenerated(reg); });

    // Insert at the original head so the delay and its taps dominate every use
    // that was previously dominated by any state in the chain.
    OpBuilder builder(head);
    auto delay = builder.create<pyc::DelayLineOp>(
        tail.getLoc(), tail.getQ().getType(), head.getClk(), head.getRst(),
        head.getEn(),
        stripStateAliases(head.getNext()),
        head.getInit());
    delay->setAttr("depth", builder.getI64IntegerAttr(depth));
    if (allGenerated)
      delay->setAttr("pyc.generated",
                     builder.getStringAttr("cycle_balance"));
    delay->setAttr(kOptimizedByAttr,
                   builder.getStringAttr(kStructuralCombineDelayChains));
    delay->setAttr(kSourceRegCountAttr,
                   builder.getI64IntegerAttr(depth));
    delay->setAttr(kSharedChainCountAttr, builder.getI64IntegerAttr(1));

    // A non-tail state may have read-only fanout. Replace each such direct
    // read with a fixed-depth view of the new history, while preserving the
    // unique state-to-state edge that defines the chain. Observation
    // identities on erased stages are remapped onto the same views.
    remapStateOpIdentity(builder, tail.getOperation(), delay.getQ());
    for (unsigned i = 1; i < chainFromTail.size(); ++i) {
      pyc::RegOp reg = chainFromTail[i];
      llvm::SmallVector<OpOperand *, 8> sideUses;
      const StateChainLink &link = linksFromTail[i - 1];
      pyc::AliasOp requiredAlias;
      Operation *requiredUser = nullptr;
      if (link.aliasesFromConsumerToProducer.empty()) {
        requiredUser = chainFromTail[i - 1].getOperation();
      } else {
        requiredAlias = link.aliasesFromConsumerToProducer.back();
        requiredUser = requiredAlias.getOperation();
      }
      for (OpOperand &use : reg.getQ().getUses())
        if (use.getOwner() != requiredUser)
          sideUses.push_back(&use);
      for (auto aliasIt = link.aliasesFromConsumerToProducer.rbegin();
           aliasIt != link.aliasesFromConsumerToProducer.rend(); ++aliasIt) {
        pyc::AliasOp alias = *aliasIt;
        auto nextAlias = std::next(aliasIt);
        if (nextAlias == link.aliasesFromConsumerToProducer.rend()) {
          requiredUser = chainFromTail[i - 1].getOperation();
        } else {
          pyc::AliasOp nextAliasOp = *nextAlias;
          requiredUser = nextAliasOp.getOperation();
        }
        for (OpOperand &use : alias.getResult().getUses())
          if (use.getOwner() != requiredUser)
            sideUses.push_back(&use);
      }
      const bool needsObservationView =
          hasExternalObservationIdentity(reg.getOperation()) ||
          llvm::any_of(link.aliasesFromConsumerToProducer, [](pyc::AliasOp a) {
            return hasExternalObservationIdentity(a);
          });
      if (sideUses.empty() && !needsObservationView)
        continue;
      const int64_t tapDepth = static_cast<int64_t>(chainFromTail.size() - i);
      auto tap = builder.create<pyc::DelayTapOp>(
          tail.getLoc(), delay.getQ().getType(), delay.getQ());
      tap->setAttr("depth", builder.getI64IntegerAttr(tapDepth));
      tap->setAttr("pyc.optimized_by",
                   builder.getStringAttr("combine_delay_chain_tap"));
      ++stats.delayTapsCreated;
      remapStateOpIdentity(builder, reg.getOperation(), tap.getTap());
      for (pyc::AliasOp alias : link.aliasesFromConsumerToProducer) {
        if (hasExternalObservationIdentity(alias))
          materializeObservationAlias(builder, alias.getLoc(), tap.getTap(),
                                      alias);
      }
      for (OpOperand *use : sideUses) {
        use->set(tap.getTap());
        ++stats.delayTapUsesRewritten;
      }
    }

    ++stats.chainsCombined;
    stats.regsCombined += depth;
    ++stats.delayLinesCreated;
    for (const StateChainLink &link : linksFromTail)
      stats.aliasesRemoved +=
          static_cast<int64_t>(link.aliasesFromConsumerToProducer.size());

    tail.getQ().replaceAllUsesWith(delay.getQ());

    for (unsigned i = 0; i < linksFromTail.size(); ++i) {
      pyc::RegOp reg = chainFromTail[i];
      erased.insert(reg.getOperation());
      reg.erase();
      for (pyc::AliasOp alias :
           linksFromTail[i].aliasesFromConsumerToProducer)
        alias.erase();
    }
    erased.insert(head.getOperation());
    head.erase();
  }
}

static void shareEquivalentDelayLines(func::FuncOp function,
                                      CombineStats &stats) {
  llvm::SmallVector<pyc::DelayLineOp> delays;
  function.walk([&](pyc::DelayLineOp delay) { delays.push_back(delay); });

  llvm::DenseMap<std::size_t, llvm::SmallVector<pyc::DelayLineOp>> buckets;
  for (pyc::DelayLineOp delay : delays) {
    auto &bucket = buckets[delayLineStateHash(delay)];
    pyc::DelayLineOp survivor;
    for (pyc::DelayLineOp existing : bucket) {
      if (equivalentDelayLineState(existing, delay)) {
        survivor = existing;
        break;
      }
    }
    if (!survivor) {
      bucket.push_back(delay);
      continue;
    }

    const int64_t lhsRegs =
        getI64Attr(survivor, kSourceRegCountAttr, 0);
    const int64_t rhsRegs = getI64Attr(delay, kSourceRegCountAttr, 0);
    const int64_t lhsChains =
        getI64Attr(survivor, kSharedChainCountAttr, 0);
    const int64_t rhsChains =
        getI64Attr(delay, kSharedChainCountAttr, 0);
    if (lhsRegs || rhsRegs)
      setI64Attr(survivor, kSourceRegCountAttr, lhsRegs + rhsRegs);
    if (lhsChains || rhsChains)
      setI64Attr(survivor, kSharedChainCountAttr, lhsChains + rhsChains);

    OpBuilder builder(survivor);
    builder.setInsertionPointAfter(survivor);
    remapStateOpIdentity(builder, delay.getOperation(), survivor.getQ());
    delay.getQ().replaceAllUsesWith(survivor.getQ());
    delay.erase();
    ++stats.delayLinesMerged;
  }
}

static void writeCombineStats(func::FuncOp function, const CombineStats &stats,
                              bool accumulate, bool cascadeRound,
                              bool performedMergeRound) {
  auto write = [&](llvm::StringRef name, int64_t value) {
    if (accumulate)
      value += getI64Attr(function, name, 0);
    setI64Attr(function, name, value);
  };
  write("pyc.stats.delay_chains_combined", stats.chainsCombined);
  write("pyc.stats.delay_chain_regs_combined", stats.regsCombined);
  write("pyc.stats.delay_chain_aliases_removed", stats.aliasesRemoved);
  write("pyc.stats.delay_chain_delay_lines_created", stats.delayLinesCreated);
  write("pyc.stats.delay_chain_delay_lines_merged", stats.delayLinesMerged);
  write("pyc.stats.state_opt_regs_merged", stats.stateRegsMerged);
  write("pyc.stats.state_opt_reg_bits_removed", stats.stateRegBitsRemoved);
  write("pyc.stats.state_opt_cascade_regs_merged",
        cascadeRound && performedMergeRound ? stats.stateRegsMerged : 0);
  write("pyc.stats.state_opt_merge_rounds", performedMergeRound ? 1 : 0);
  write("pyc.stats.delay_chain_taps_created", stats.delayTapsCreated);
  write("pyc.stats.delay_chain_tap_uses_rewritten",
        stats.delayTapUsesRewritten);
}

struct CombineDelayChainsPass
    : public PassWrapper<CombineDelayChainsPass,
                         OperationPass<func::FuncOp>> {
  MLIR_DEFINE_EXPLICIT_INTERNAL_INLINE_TYPE_ID(CombineDelayChainsPass)

  CombineDelayChainsPass() = default;
  CombineDelayChainsPass(const CombineDelayChainsPass &other)
      : PassWrapper(other) {}
  CombineDelayChainsPass(bool accumulateStats, bool cascadeRound) {
    accumulateStatsOption = accumulateStats;
    cascadeRoundOption = cascadeRound;
  }

  StringRef getArgument() const override { return "pyc-combine-delay-chains"; }
  StringRef getDescription() const override {
    return "Merge equivalent state and form proven fixed-depth delay lines";
  }

  Option<bool> accumulateStatsOption{
      *this, "accumulate-stats",
      llvm::cl::desc("Add rewrite statistics to an earlier optimization round"),
      llvm::cl::init(false)};
  Option<bool> cascadeRoundOption{
      *this, "cascade-round",
      llvm::cl::desc("Attribute equivalent-state merges to cascade refinement"),
      llvm::cl::init(false)};
  void runOnOperation() override {
    func::FuncOp function = getOperation();
    CombineStats stats;
    mergeEquivalentStates(function, stats);
    combineStateChains(function, stats);
    shareEquivalentDelayLines(function, stats);
    writeCombineStats(function, stats, accumulateStatsOption,
                      cascadeRoundOption, /*performedMergeRound=*/true);
  }
};

} // namespace

std::unique_ptr<::mlir::Pass>
createCombineDelayChainsPass(bool accumulateStats, bool cascadeRound) {
  return std::make_unique<CombineDelayChainsPass>(accumulateStats,
                                                  cascadeRound);
}

void runDelayChainMergeRound(func::FuncOp function, bool cascadeRound,
                             bool accumulateStats) {
  CombineStats stats;
  mergeEquivalentStates(function, stats);
  writeCombineStats(function, stats, accumulateStats, cascadeRound,
                    /*performedMergeRound=*/true);
}

void runDelayChainFormAndShare(func::FuncOp function, bool accumulateStats) {
  CombineStats stats;
  combineStateChains(function, stats);
  shareEquivalentDelayLines(function, stats);
  writeCombineStats(function, stats, accumulateStats,
                    /*cascadeRound=*/false, /*performedMergeRound=*/false);
}

static PassRegistration<CombineDelayChainsPass> pass;

} // namespace pyc

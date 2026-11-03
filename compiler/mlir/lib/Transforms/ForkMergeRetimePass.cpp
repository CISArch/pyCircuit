// Fork-merge retiming (user design, docs/reg_upstream_dfs_merge_plan.md).
//
// Post-order delay accounting over the combinational DAG between state
// elements. Every sink register issues a "consumed at delay d" event for the
// root of its next-cone; events propagate through combinational operands
// (the delay shifts upstream, so the op is cloned downstream of the shared
// chain), through direct links (alias / single-driver wire), and through
// registers (q consumed at delay d == its next-root at d+1, extending the
// stage-semantics sequence). The semantics of a delayed instance are the
// (clk, rst, en, init) of the registers that provided that delay on the
// original path, so shared chains reuse exactly the original hold/reset
// behavior and initial values, and every input-to-output path keeps its
// register count.
//
// Registers whose next-cone reads their own q (hold loops), non-constant
// init, or non-whitelist ops where lifting would need them are left
// untouched. A budget on materialized chain bits / cloned op instances
// degrades the whole function to merge-only mode (direct-link sharing
// without cone lifting), which keeps the deep cycle_balance chains in the
// PE clusters cheap.

#include "pyc/Transforms/Passes.h"
#include "pyc/Transforms/StateOptimization.h"

#include "pyc/Dialect/PYC/PYCOps.h"

#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/IR/Builders.h"
#include "mlir/IR/IRMapping.h"
#include "mlir/Pass/Pass.h"
#include "llvm/ADT/DenseMap.h"
#include "llvm/ADT/DenseSet.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/ADT/SmallVector.h"

#include <optional>

using namespace mlir;

namespace pyc {
namespace {

constexpr llvm::StringLiteral kOptimizedBy = "fork_merge_retime";
constexpr unsigned kMaxDelay = 8;
constexpr double kWidthBudget = 2.0;
constexpr double kOpBudget = 2.0;

static std::optional<unsigned> scalarWidth(Type type) {
  if (auto integer = dyn_cast<IntegerType>(type))
    return integer.getWidth();
  return std::nullopt;
}

// Move the whole user cone of `root` below it so every use stays dominated
// after handles were materialized late in the block.
static void sinkUsersBelow(Operation *root) {
  llvm::DenseSet<Operation *> seen;
  llvm::SmallVector<Operation *> wave{root};
  seen.insert(root);
  while (!wave.empty()) {
    Operation *def = wave.pop_back_val();
    llvm::SmallVector<Operation *> users;
    for (Value result : def->getResults())
      for (Operation *user : result.getUsers())
        users.push_back(user);
    for (Operation *user : users) {
      if (user->getBlock() != def->getBlock())
        continue;
      if (!def->isBeforeInBlock(user))
        user->moveAfter(def);
      if (seen.insert(user).second)
        wave.push_back(user);
    }
  }
}

static bool isLiftableOp(Operation *op) {
  return isa<pyc::AddOp, pyc::SubOp, pyc::MulOp, pyc::AndOp, pyc::OrOp,
              pyc::XorOp, pyc::NotOp, pyc::MuxOp, pyc::EqOp, pyc::UltOp,
              pyc::SltOp, pyc::TruncOp, pyc::ZextOp, pyc::SextOp, pyc::ExtractOp,
              pyc::ShliOp, pyc::LshriOp, pyc::AshriOp, pyc::ShlOp, pyc::LshrOp,
              pyc::AshrOp, pyc::ConcatOp>(op);
}

static bool isBoundaryStateOp(Operation *op) {
  return isa<pyc::DelayLineOp, pyc::DelayTapOp, pyc::SyncMemOp,
              pyc::SyncMemDPOp, pyc::ByteMemOp, pyc::FifoOp, pyc::AsyncFifoOp,
              pyc::CdcSyncOp, pyc::InstanceOp>(op);
}

static std::optional<llvm::APInt> constantValue(Value value) {
  llvm::SmallPtrSet<Operation *, 4> seen;
  while (auto alias = value.getDefiningOp<pyc::AliasOp>()) {
    if (!seen.insert(alias).second)
      return std::nullopt;
    value = alias.getIn();
  }
  if (auto constant = value.getDefiningOp<pyc::ConstantOp>())
    return constant.getValueAttr().getValue();
  if (auto constant = value.getDefiningOp<arith::ConstantOp>()) {
    if (auto integer = dyn_cast<IntegerAttr>(constant.getValue()))
      return integer.getValue();
  }
  return std::nullopt;
}

// Single-driver wires and aliases are names, not gates.
static Value resolve(Value value) {
  llvm::SmallPtrSet<Operation *, 8> seen;
  while (value) {
    Operation *def = value.getDefiningOp();
    if (!def || !seen.insert(def).second)
      return value;
    if (auto alias = dyn_cast<pyc::AliasOp>(def)) {
      value = alias.getIn();
      continue;
    }
    if (!isa<pyc::WireOp>(def))
      return value;
    Value src;
    unsigned drivers = 0;
    for (Operation *user : value.getUsers()) {
      auto assign = dyn_cast<pyc::AssignOp>(user);
      if (!assign || assign.getDst() != value)
        continue;
      src = assign.getSrc();
      ++drivers;
    }
    if (drivers != 1)
      return value;
    value = src;
  }
  return value;
}

static bool sameSemanticValue(Value lhs, Value rhs) {
  if (lhs == rhs)
    return true;
  auto lc = constantValue(lhs);
  auto rc = constantValue(rhs);
  return lc && rc && lc->getBitWidth() == rc->getBitWidth() && *lc == *rc;
}

// Stage semantics of one register along a delayed path.
struct StageSem {
  Value clk;
  Value rst;
  Value en; // resolved operand
  llvm::APInt init;
  StringAttr generated;
};

static bool stageSemEqual(const StageSem &lhs, const StageSem &rhs) {
  if (lhs.clk != rhs.clk || lhs.rst != rhs.rst)
    return false;
  if (!sameSemanticValue(lhs.en, rhs.en))
    return false;
  return lhs.init.getBitWidth() == rhs.init.getBitWidth() &&
         lhs.init == rhs.init;
}

using Sig = llvm::SmallVector<StageSem, 4>;

static std::optional<StageSem> stageSemOf(pyc::RegOp reg) {
  auto init = constantValue(resolve(reg.getInit()));
  if (!init)
    return std::nullopt;
  return StageSem{reg.getClk(), reg.getRst(), resolve(reg.getEn()), *init,
                  reg->getAttrOfType<StringAttr>("pyc.generated")};
}

static bool sigEqual(const Sig &lhs, const Sig &rhs) {
  if (lhs.size() != rhs.size())
    return false;
  for (auto [a, b] : llvm::zip(lhs, rhs)) {
    if (!stageSemEqual(a, b))
      return false;
  }
  return true;
}

struct ForkStats {
  std::int64_t sinksRewritten = 0;
  std::int64_t regsCreated = 0;
  std::int64_t clones = 0;
  std::int64_t failed = 0;
  std::int64_t deepDrop = 0;
  std::int64_t budgetFallback = 0;
};

class ForkMergeRetime {
public:
  explicit ForkMergeRetime(func::FuncOp function) : function(function) {}

  ForkStats run() {
    collect();
    propagate();
    evaluateBudget();
    rewrite();
    return stats;
  }

private:
  func::FuncOp function;
  ForkStats stats;
  llvm::SmallVector<pyc::RegOp, 16> regs;
  llvm::DenseSet<Operation *> selfLoop;
  bool mergeOnly = false;

  // Interned signatures (stage sequences ordered sink-side first).
  llvm::SmallVector<Sig, 16> sigTable;
  unsigned internSig(const Sig &sig) {
    for (unsigned i = 0; i < sigTable.size(); ++i)
      if (sigEqual(sigTable[i], sig))
        return i;
    sigTable.push_back(sig);
    return static_cast<unsigned>(sigTable.size() - 1);
  }
  unsigned extendSig(unsigned id, const StageSem &stage) {
    Sig extended = sigTable[id];
    extended.push_back(stage);
    return internSig(extended);
  }

  // (value, sigId) -> delays at which the value is consumed.
  llvm::DenseMap<std::pair<Value, unsigned>, llvm::SmallVector<unsigned, 4>>
      valueDelays;
  void noteDelay(Value value, unsigned sigId, unsigned delay) {
    auto &set = valueDelays[{value, sigId}];
    if (!llvm::is_contained(set, delay))
      set.push_back(delay);
  }

  void collect() {
    function.walk([&](pyc::RegOp reg) { regs.push_back(reg); });
    for (pyc::RegOp reg : regs)
      if (coneReadsOwnQ(reg))
        selfLoop.insert(reg.getOperation());
  }

  bool coneReadsOwnQ(pyc::RegOp reg) {
    Value q = reg.getQ();
    llvm::DenseSet<Value> seen;
    llvm::SmallVector<Value, 8> work{reg.getNext()};
    while (!work.empty()) {
      Value v = resolve(work.pop_back_val());
      if (v == q)
        return true;
      if (!seen.insert(v).second)
        continue;
      Operation *def = v.getDefiningOp();
      if (!def || !isLiftableOp(def))
        continue;
      if (def->getBlock() != &function.front())
        continue;
      for (Value operand : def->getOperands())
        work.push_back(operand);
    }
    return false;
  }

  void propagate() {
    llvm::DenseSet<std::pair<Value, std::pair<unsigned, unsigned>>> seen;
    llvm::SmallVector<std::tuple<Value, unsigned, unsigned>, 32> work;
    auto push = [&](Value value, unsigned delay, unsigned sigId) {
      Value rv = resolve(value);
      if (rv.getParentBlock() != &function.front())
        return;
      if (seen.insert({rv, {delay, sigId}}).second)
        work.push_back({rv, delay, sigId});
    };
    for (pyc::RegOp reg : regs) {
      if (selfLoop.contains(reg.getOperation()))
        continue;
      auto stage = stageSemOf(reg);
      if (!stage)
        continue;
      unsigned id = internSig(Sig{*stage});
      push(reg.getNext(), 1, id);
    }
    while (!work.empty()) {
      auto [v, d, sigId] = work.pop_back_val();
      Operation *def = v.getDefiningOp();
      if (!def) { // block argument
        noteDelay(v, sigId, d);
        continue;
      }
      if (auto reg = dyn_cast<pyc::RegOp>(def)) {
        if (selfLoop.contains(reg.getOperation())) {
          noteDelay(v, sigId, d);
          continue;
        }
        auto stage = stageSemOf(reg);
        if (!stage || d + 1 > kMaxDelay) {
          ++stats.deepDrop;
          continue;
        }
        push(reg.getNext(), d + 1, extendSig(sigId, *stage));
        continue;
      }
      if (isBoundaryStateOp(def) || !isLiftableOp(def)) {
        noteDelay(v, sigId, d);
        continue;
      }
      noteDelay(v, sigId, d);
      if (d >= 1) {
        for (Value operand : def->getOperands())
          push(operand, d, sigId);
      }
    }
  }

  void evaluateBudget() {
    uint64_t origBits = 0;
    for (pyc::RegOp reg : regs)
      origBits += scalarWidth(reg.getQ().getType()).value_or(0);
    uint64_t origOps = 0;
    function.walk([&](Operation *op) {
      if (isLiftableOp(op))
        ++origOps;
    });

    uint64_t chainBits = 0;
    uint64_t opInstances = 0;
    // Per host value: the deepest delay over all signatures. Signatures that
    // agree on their earliest stages share those chain levels, so one chain
    // of maxDelay levels per host bounds the shared prefix construction.
    llvm::DenseMap<Value, unsigned> hostMaxDelay;
    for (const auto &kv : valueDelays) {
      Value v = kv.first.first;
      unsigned maxDelay = 0;
      for (unsigned d : kv.second)
        maxDelay = std::max(maxDelay, d);
      Operation *def = v.getDefiningOp();
      if (def && isLiftableOp(def)) {
        // Liftable values are cloned once per consumed delay, never chained.
        opInstances += kv.second.size();
        continue;
      }
      unsigned &worst = hostMaxDelay[v];
      worst = std::max(worst, maxDelay);
    }
    for (const auto &kv : hostMaxDelay) {
      uint64_t width = scalarWidth(kv.first.getType()).value_or(1);
      chainBits += width * kv.second;
    }
    if (regs.empty())
      return;
    if (chainBits > origBits * kWidthBudget ||
        opInstances > origOps * kOpBudget) {
      mergeOnly = true;
      ++stats.budgetFallback;
    }
  }

  // ---- rewrite ----

  // Interned stage semantics; a chain level is identified by (input value,
  // stage id), so prefixes are shared across signatures that agree on their
  // earliest stages (the common stages of a fork merge into one chain).
  llvm::SmallVector<StageSem, 32> stageTable;
  unsigned internStage(const StageSem &stage) {
    for (unsigned i = 0; i < stageTable.size(); ++i)
      if (stageSemEqual(stageTable[i], stage))
        return i;
    stageTable.push_back(stage);
    return static_cast<unsigned>(stageTable.size() - 1);
  }
  llvm::DenseMap<std::pair<Value, unsigned>, Value> chainLevel;
  // (value, delay, sigId) -> lifted handle; shared across all sinks.
  llvm::DenseMap<std::pair<Value, std::pair<unsigned, unsigned>>, Value>
      okMemo;
  llvm::DenseSet<
      std::pair<Operation *, std::pair<Value, std::pair<unsigned, unsigned>>>>
      failMemo;

  void setBuilderAfter(OpBuilder &builder, Operation *after) {
    if (after)
      builder.setInsertionPointAfter(after);
    else
      builder.setInsertionPointToStart(&function.front());
  }

  // Chain of `delay` registers below `base`; level k (nearest the source
  // first) uses the semantics of sig[sig.size() - k].
  std::optional<Value> buildChain(Value base, unsigned delay, unsigned sigId) {
    const Sig &sig = sigTable[sigId];
    if (sig.size() < delay)
      return std::nullopt;
    Value prev = base;
    for (unsigned k = 1; k <= delay; ++k) {
      const StageSem &stage = sig[sig.size() - k];
      // The stage semantics come from a register that delayed this exact
      // value on the original path, so its init must be as wide as the
      // chain level. A width mismatch means the delay crossed a
      // width-changing op (zext/trunc/concat/extract); inheriting the init
      // there is not sound, so skip the whole chain.
      auto prevWidth = scalarWidth(prev.getType());
      if (!prevWidth || stage.init.getBitWidth() != *prevWidth)
        return std::nullopt;
      std::pair<Value, unsigned> mapKey{prev, internStage(stage)};
      auto found = chainLevel.find(mapKey);
      if (found != chainLevel.end()) {
        prev = found->second;
        continue;
      }
      OpBuilder builder(base.getContext());
      Operation *after = prev.getDefiningOp();
      for (Value dep : {stage.clk, stage.rst, stage.en})
        if (Operation *def = dep.getDefiningOp())
          if (!after || after->isBeforeInBlock(def))
            after = def;
      setBuilderAfter(builder, after);
      Type initType = IntegerType::get(base.getContext(), *prevWidth);
      Value init = builder.create<pyc::ConstantOp>(
          function.getLoc(), initType,
          IntegerAttr::get(initType, stage.init));
      auto created = builder.create<pyc::RegOp>(
          function.getLoc(), prev.getType(), stage.clk, stage.rst, stage.en,
          prev, init);
      created->setAttr("pyc.optimized_by",
                       builder.getStringAttr(kOptimizedBy));
      if (stage.generated)
        created->setAttr("pyc.generated", stage.generated);
      prev = created.getQ();
      chainLevel[mapKey] = prev;
      ++stats.regsCreated;
    }
    return prev;
  }

  std::optional<Value> liftCone(Value value, unsigned delay, unsigned sigId,
                                pyc::RegOp current) {
    Value rv = resolve(value);
    if (delay == 0)
      return rv;
    if (rv.getParentBlock() != &function.front())
      return std::nullopt;
    std::pair<Value, std::pair<unsigned, unsigned>> okKey{rv, {delay, sigId}};
    auto found = okMemo.find(okKey);
    if (found != okMemo.end())
      return found->second;
    if (failMemo.contains({current.getOperation(), okKey}))
      return std::nullopt;

    std::optional<Value> result;
    Operation *def = rv.getDefiningOp();
    if (!def) { // block argument
      result = buildChain(rv, delay, sigId);
    } else if (auto reg = dyn_cast<pyc::RegOp>(def)) {
      if (reg == current) {
        result = std::nullopt; // two-register loop back to ourselves
      } else if (selfLoop.contains(reg.getOperation()) ||
                 !stageSemOf(reg)) {
        result = buildChain(rv, delay, sigId);
      } else if (delay + 1 > kMaxDelay) {
        ++stats.deepDrop;
        result = std::nullopt;
      } else {
        auto stage = stageSemOf(reg);
        result = liftCone(reg.getNext(), delay + 1,
                          extendSig(sigId, *stage), current);
      }
    } else if (isBoundaryStateOp(def) || !isLiftableOp(def)) {
      result = buildChain(rv, delay, sigId);
    } else if (mergeOnly) {
      result = std::nullopt;
    } else {
      llvm::SmallVector<Value, 4> lifted;
      bool ok = true;
      for (Value operand : def->getOperands()) {
        auto handle = liftCone(operand, delay, sigId, current);
        if (!handle) {
          ok = false;
          break;
        }
        lifted.push_back(*handle);
      }
      if (!ok) {
        result = std::nullopt;
      } else {
        OpBuilder builder(rv.getContext());
        Operation *after = nullptr;
        for (Value handle : lifted) {
          Operation *def = handle.getDefiningOp();
          if (def && (!after || after->isBeforeInBlock(def)))
            after = def;
        }
        setBuilderAfter(builder, after);
        IRMapping mapping;
        for (auto [operand, handle] :
             llvm::zip_first(def->getOperands(), lifted))
          mapping.map(operand, handle);
        Operation *clone = builder.clone(*def, mapping);
        llvm::SmallVector<StringAttr> drop;
        for (NamedAttribute attr : clone->getAttrs()) {
          llvm::StringRef name = attr.getName().strref();
          if (name == "pyc.name" || name == "pyc.debug_keep" ||
              name == "pyc.observable" || name.starts_with("pyc.probe") ||
              name.starts_with("pyc.trace"))
            drop.push_back(attr.getName());
        }
        for (StringAttr name : drop)
          clone->removeAttr(name);
        clone->setAttr("pyc.optimized_by",
                       builder.getStringAttr(kOptimizedBy));
        ++stats.clones;
        result = clone->getResult(0);
      }
    }

    if (result)
      okMemo[okKey] = *result;
    else
      failMemo.insert({current.getOperation(), okKey});
    return result;
  }

  void rewrite() {
    for (pyc::RegOp reg : regs) {
      if (selfLoop.contains(reg.getOperation()))
        continue;
      auto stage = stageSemOf(reg);
      if (!stage)
        continue;
      unsigned sigId = internSig(Sig{*stage});
      auto handle = liftCone(reg.getNext(), 1, sigId, reg);
      if (!handle) {
        ++stats.failed;
        continue;
      }
      if (*handle == reg.getQ())
        continue;
      OpBuilder builder(reg.getContext());
      builder.setInsertionPoint(reg);
      remapStateOpIdentity(builder, reg, *handle);
      reg.getQ().replaceAllUsesWith(*handle);
      reg.erase();
      // The handle is materialized after its dependencies, which can sit
      // later in the block than the sink's existing users; move that user
      // cone below the handle so every use stays dominated.
      if (Operation *handleDef = handle->getDefiningOp())
        sinkUsersBelow(handleDef);
      ++stats.sinksRewritten;
    }
  }
};

struct ForkMergeRetimePass
    : public PassWrapper<ForkMergeRetimePass, OperationPass<func::FuncOp>> {
  MLIR_DEFINE_EXPLICIT_INTERNAL_INLINE_TYPE_ID(ForkMergeRetimePass)

  StringRef getArgument() const override { return "pyc-fork-merge-retime"; }
  StringRef getDescription() const override {
    return "DFS-merge retiming: share the common register stages of each "
           "fork upstream and leave extra stages on the branch edge";
  }

  void runOnOperation() override {
    ForkStats stats = ForkMergeRetime(getOperation()).run();
    func::FuncOp function = getOperation();
    setI64Attr(function, "pyc.stats.fork_merge_sinks_rewritten",
               stats.sinksRewritten);
    setI64Attr(function, "pyc.stats.fork_merge_regs_created",
               stats.regsCreated);
    setI64Attr(function, "pyc.stats.fork_merge_clones", stats.clones);
    setI64Attr(function, "pyc.stats.fork_merge_failed", stats.failed);
    setI64Attr(function, "pyc.stats.fork_merge_deep_drop", stats.deepDrop);
    setI64Attr(function, "pyc.stats.fork_merge_budget_fallback",
               stats.budgetFallback);
  }
};

} // namespace

std::unique_ptr<::mlir::Pass> createForkMergeRetimePass() {
  return std::make_unique<ForkMergeRetimePass>();
}

void runForkMergeRetime(func::FuncOp function) {
  ForkMergeRetime(function).run();
}

static PassRegistration<ForkMergeRetimePass> forkMergeRetimePass;

} // namespace pyc

// Fork-merge retiming: collapse parallel register copies.
//
// Davinci's frontend emits many `cycle_balance` registers that sample the
// same value with the same clock/reset/enable/init — up to 111 copies of one
// 64-bit signal. They are literally the same flip-flop, so all but one can be
// deleted and the survivor reused. That is the "common stages of a fork merge
// into one" half of docs/reg_upstream_dfs_merge_plan.md, restricted to the
// case that needs no new IR: no chain is materialized and no cone is lifted,
// so path delays and every input-to-output register count are untouched.
//
// Guards, all conservative:
//   * the data input must not be another register's q (a register that
//     follows another register is not a duplicate of it);
//   * enable is compared after resolving aliases/wires, constants by value;
//   * init must be a constant of the register's own width;
//   * hold loops (next cone reads own q) are left alone.
//
// Lifting a register across a combinational op is deliberately not done here:
// the materialized chains need post-hoc reordering that repeatedly broke
// dominance on the PE clusters. The merge alone already removes most of the
// copy explosion (scoreboard 26026 -> 235 on the dumped IR).

#include "pyc/Transforms/Passes.h"
#include "pyc/Transforms/StateOptimization.h"

#include "pyc/Dialect/PYC/PYCOps.h"

#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/IR/Builders.h"
#include "mlir/Pass/Pass.h"
#include "llvm/ADT/DenseSet.h"
#include "llvm/ADT/SmallPtrSet.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/StringMap.h"
#include "llvm/Support/raw_ostream.h"

#include <optional>
#include <string>

using namespace mlir;

namespace pyc {
namespace {

struct MergeStats {
  std::int64_t merged = 0;
  std::int64_t groups = 0;
};

static std::optional<unsigned> scalarWidth(Type type) {
  if (auto integer = dyn_cast<IntegerType>(type))
    return integer.getWidth();
  return std::nullopt;
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

// Textual identity of a value: SSA id for real values, literal for constants.
static void appendValueKey(llvm::raw_ostream &os, Value value) {
  Value resolved = resolve(value);
  if (auto constant = constantValue(resolved)) {
    os << "c" << constant->getBitWidth() << "x" << *constant;
    return;
  }
  os << resolved;
}

static bool isStateBoundary(Operation *def) {
  return isa<pyc::RegOp, pyc::DelayLineOp, pyc::DelayTapOp, pyc::SyncMemOp,
             pyc::SyncMemDPOp, pyc::ByteMemOp, pyc::FifoOp, pyc::AsyncFifoOp,
             pyc::CdcSyncOp, pyc::InstanceOp>(def);
}

static bool coneReadsOwnQ(pyc::RegOp reg) {
  Value q = reg.getQ();
  llvm::DenseSet<Value> seen;
  llvm::SmallVector<Value, 8> work{reg.getNext()};
  while (!work.empty()) {
    Value value = resolve(work.pop_back_val());
    if (value == q)
      return true;
    if (!seen.insert(value).second)
      continue;
    Operation *def = value.getDefiningOp();
    if (!def || isStateBoundary(def))
      continue;
    for (Value operand : def->getOperands())
      work.push_back(operand);
  }
  return false;
}

class ForkMergeRetime {
public:
  explicit ForkMergeRetime(func::FuncOp function) : function(function) {}

  MergeStats run() {
    llvm::SmallVector<pyc::RegOp, 16> regs;
    llvm::DenseSet<Value> registerQ;
    function.walk([&](pyc::RegOp reg) {
      regs.push_back(reg);
      registerQ.insert(reg.getQ());
    });

    llvm::StringMap<pyc::RegOp> owner;
    llvm::SmallVector<pyc::RegOp, 16> victims;
    for (pyc::RegOp reg : regs) {
      if (coneReadsOwnQ(reg))
        continue;
      Value data = resolve(reg.getNext());
      if (registerQ.contains(data))
        continue; // following a register is not a duplicate of it
      auto init = constantValue(reg.getInit());
      auto width = scalarWidth(reg.getQ().getType());
      if (!init || !width || init->getBitWidth() != *width)
        continue;

      std::string key = keyOf(reg);
      auto found = owner.find(key);
      if (found == owner.end()) {
        owner[key] = reg;
        ++stats.groups;
        continue;
      }
      victims.push_back(reg);
      victims.back()->setAttr(
          "pyc.fork_merge.survivor",
          FlatSymbolRefAttr::get(reg.getContext(), key));
    }

    for (pyc::RegOp reg : victims) {
      auto attr = reg->getAttrOfType<FlatSymbolRefAttr>(
          "pyc.fork_merge.survivor");
      if (!attr)
        continue;
      auto found = owner.find(attr.getValue());
      if (found == owner.end() || found->second == reg)
        continue;
      pyc::RegOp survivor = found->second;
      OpBuilder builder(reg.getContext());
      builder.setInsertionPoint(reg);
      remapStateOpIdentity(builder, reg, survivor.getQ());
      reg.getQ().replaceAllUsesWith(survivor.getQ());
      reg.erase();
      ++stats.merged;
    }
    return stats;
  }

private:
  func::FuncOp function;
  MergeStats stats;

  static std::string keyOf(pyc::RegOp reg) {
    auto init = constantValue(reg.getInit());
    std::string key;
    llvm::raw_string_ostream os(key);
    os << scalarWidth(reg.getQ().getType()).value_or(0) << ':';
    appendValueKey(os, reg.getNext());
    os << '|' << reg.getClk() << '|' << reg.getRst() << '|';
    appendValueKey(os, reg.getEn());
    if (init)
      os << '|' << init->getBitWidth() << 'x' << *init;
    else
      os << '|';
    os.flush();
    return key;
  }
};

struct ForkMergeRetimePass
    : public PassWrapper<ForkMergeRetimePass, OperationPass<func::FuncOp>> {
  MLIR_DEFINE_EXPLICIT_INTERNAL_INLINE_TYPE_ID(ForkMergeRetimePass)

  StringRef getArgument() const override { return "pyc-fork-merge-retime"; }
  StringRef getDescription() const override {
    return "Merge parallel register copies that sample the same value with "
           "the same clock/reset/enable/init into a single register";
  }

  void runOnOperation() override {
    MergeStats stats = ForkMergeRetime(getOperation()).run();
    func::FuncOp function = getOperation();
    setI64Attr(function, "pyc.stats.fork_merge_merged", stats.merged);
    setI64Attr(function, "pyc.stats.fork_merge_groups", stats.groups);
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

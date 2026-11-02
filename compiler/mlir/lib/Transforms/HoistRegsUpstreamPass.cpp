// Slide a register one combinational op upstream so that op joins the
// consumers of q. A multi-input op gets one register per non-constant input
// (option B in docs/reg_upstream_retime_plan.md): the path delay of this
// branch stays the same, and other branches are untouched. The whole cone is
// not crossed in one step; that would register every leaf.

#include "pyc/Transforms/Passes.h"
#include "pyc/Transforms/StateOptimization.h"

#include "pyc/Dialect/PYC/PYCOps.h"

#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/IR/Builders.h"
#include "mlir/IR/IRMapping.h"
#include "mlir/Pass/Pass.h"
#include "llvm/ADT/DenseSet.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/ADT/SmallPtrSet.h"
#include "llvm/ADT/SmallVector.h"

#include <optional>

using namespace mlir;

namespace pyc {
namespace {

constexpr llvm::StringLiteral kHoistedBy = "hoist_regs_upstream";

struct HoistStats {
  int64_t regsHoisted = 0;
  int64_t opsMoved = 0;
  int64_t blockedInit = 0;
};

static std::optional<unsigned> scalarWidth(Type type) {
  if (auto integer = dyn_cast<IntegerType>(type))
    return integer.getWidth();
  return std::nullopt;
}

static bool isHoistableOp(Operation *op) {
  return isa<pyc::AddOp, pyc::SubOp, pyc::MulOp, pyc::AndOp, pyc::OrOp,
             pyc::XorOp, pyc::NotOp, pyc::MuxOp, pyc::EqOp, pyc::UltOp,
             pyc::SltOp, pyc::TruncOp, pyc::ZextOp, pyc::SextOp, pyc::ExtractOp,
             pyc::ShliOp, pyc::LshriOp, pyc::AshriOp, pyc::ShlOp, pyc::LshrOp,
             pyc::AshrOp, pyc::ConcatOp>(op);
}

static bool isStateOp(Operation *op) {
  return isa<pyc::RegOp, pyc::DelayLineOp, pyc::DelayTapOp, pyc::SyncMemOp,
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

static bool isConstOne(Value value) {
  auto constant = constantValue(value);
  return constant && constant->isOne();
}

// Single-driver wires and aliases are names, not gates. Stop on a
// multi-driver wire so the caller treats it as an opaque value.
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

static bool combDependsOn(Value value, Value query,
                          llvm::DenseSet<Value> &seen) {
  if (!value || !seen.insert(value).second)
    return false;
  if (value == query)
    return true;
  Operation *def = value.getDefiningOp();
  if (!def || isStateOp(def))
    return false;
  if (auto alias = dyn_cast<pyc::AliasOp>(def))
    return combDependsOn(alias.getIn(), query, seen);
  if (isa<pyc::WireOp>(def)) {
    for (Operation *user : value.getUsers()) {
      auto assign = dyn_cast<pyc::AssignOp>(user);
      if (assign && assign.getDst() == value &&
          combDependsOn(assign.getSrc(), query, seen))
        return true;
    }
    return false;
  }
  if (constantValue(value))
    return false;
  return llvm::any_of(def->getOperands(), [&](Value operand) {
    return combDependsOn(operand, query, seen);
  });
}

static bool hasCombUser(Value value, const llvm::DenseSet<Operation *> &skip) {
  llvm::DenseSet<Value> seen;
  llvm::SmallVector<Value> work{value};
  while (!work.empty()) {
    Value current = work.pop_back_val();
    if (!seen.insert(current).second)
      continue;
    for (Operation *user : current.getUsers()) {
      if (skip.contains(user))
        continue;
      if (auto alias = dyn_cast<pyc::AliasOp>(user)) {
        work.push_back(alias.getResult());
        continue;
      }
      if (auto assign = dyn_cast<pyc::AssignOp>(user)) {
        if (assign.getSrc() == current)
          work.push_back(assign.getDst());
        continue;
      }
      if (isHoistableOp(user))
        return true;
    }
  }
  return false;
}

// Same constant rules as RetimePipelinesPass::evaluateConeOp. Kept local so
// a failed fold skips the rewrite instead of changing that pass.
static std::optional<llvm::APInt>
evaluateOp(Operation *op, llvm::ArrayRef<llvm::APInt> args) {
  if (op->getNumResults() != 1 || args.size() != op->getNumOperands())
    return std::nullopt;
  auto width = scalarWidth(op->getResult(0).getType());
  if (!width)
    return std::nullopt;
  auto fit = [&](llvm::APInt value) { return value.zextOrTrunc(*width); };
  if (isa<pyc::AddOp>(op))
    return fit(args[0] + args[1]);
  if (isa<pyc::SubOp>(op))
    return fit(args[0] - args[1]);
  if (isa<pyc::MulOp>(op))
    return fit(args[0] * args[1]);
  if (isa<pyc::AndOp>(op))
    return fit(args[0] & args[1]);
  if (isa<pyc::OrOp>(op))
    return fit(args[0] | args[1]);
  if (isa<pyc::XorOp>(op))
    return fit(args[0] ^ args[1]);
  if (isa<pyc::NotOp>(op))
    return fit(~args[0]);
  if (isa<pyc::MuxOp>(op))
    return fit(args[0].isZero() ? args[2] : args[1]);
  if (isa<pyc::EqOp>(op))
    return llvm::APInt(1, args[0] == args[1]);
  if (isa<pyc::UltOp>(op))
    return llvm::APInt(1, args[0].ult(args[1]));
  if (isa<pyc::SltOp>(op))
    return llvm::APInt(1, args[0].slt(args[1]));
  if (isa<pyc::TruncOp>(op))
    return args[0].trunc(*width);
  if (isa<pyc::ZextOp>(op))
    return args[0].zext(*width);
  if (isa<pyc::SextOp>(op))
    return args[0].sext(*width);
  if (auto extract = dyn_cast<pyc::ExtractOp>(op)) {
    auto lsb = static_cast<uint64_t>(extract.getLsbAttr().getInt());
    if (lsb >= args[0].getBitWidth())
      return llvm::APInt(*width, 0);
    return args[0].lshr(static_cast<unsigned>(lsb)).trunc(*width);
  }
  auto logicalShift = [&](bool left, uint64_t amount) {
    if (amount >= args[0].getBitWidth())
      return llvm::APInt(*width, 0);
    return fit(left ? args[0] << static_cast<unsigned>(amount)
                    : args[0].lshr(static_cast<unsigned>(amount)));
  };
  auto arithmeticShift = [&](uint64_t amount) {
    if (args[0].getBitWidth() == 0)
      return llvm::APInt(*width, 0);
    amount = std::min<uint64_t>(amount, args[0].getBitWidth() - 1);
    return fit(args[0].ashr(static_cast<unsigned>(amount)));
  };
  if (auto shift = dyn_cast<pyc::ShliOp>(op))
    return logicalShift(true, static_cast<uint64_t>(shift.getAmountAttr().getInt()));
  if (auto shift = dyn_cast<pyc::LshriOp>(op))
    return logicalShift(false,
                        static_cast<uint64_t>(shift.getAmountAttr().getInt()));
  if (auto shift = dyn_cast<pyc::AshriOp>(op))
    return arithmeticShift(
        static_cast<uint64_t>(shift.getAmountAttr().getInt()));
  auto shiftAmount = [&](const llvm::APInt &amount) -> std::optional<uint64_t> {
    if (amount.getActiveBits() > 64)
      return std::nullopt;
    return amount.getZExtValue();
  };
  if (isa<pyc::ShlOp>(op)) {
    auto amount = shiftAmount(args[1]);
    return amount ? std::optional<llvm::APInt>(logicalShift(true, *amount))
                  : std::nullopt;
  }
  if (isa<pyc::LshrOp>(op)) {
    auto amount = shiftAmount(args[1]);
    return amount ? std::optional<llvm::APInt>(logicalShift(false, *amount))
                  : std::nullopt;
  }
  if (isa<pyc::AshrOp>(op)) {
    auto amount = shiftAmount(args[1]);
    return amount ? std::optional<llvm::APInt>(arithmeticShift(*amount))
                  : std::nullopt;
  }
  if (isa<pyc::ConcatOp>(op)) {
    llvm::APInt result(*width, 0);
    for (const llvm::APInt &arg : args) {
      result = result.shl(arg.getBitWidth());
      result |= arg.zextOrTrunc(*width);
    }
    return result;
  }
  return std::nullopt;
}

static bool evalMatches(Operation *op, llvm::ArrayRef<llvm::APInt> args,
                        const llvm::APInt &expected) {
  auto got = evaluateOp(op, args);
  return got && *got == expected;
}

// A handful of structural guesses. Not a search over the input space.
static std::optional<llvm::SmallVector<llvm::APInt>>
solveInits(Operation *op, ValueRange operands,
           llvm::ArrayRef<Value> variables, const llvm::APInt &expected) {
  llvm::SmallVector<std::optional<unsigned>> slot(operands.size());
  for (unsigned i = 0; i < operands.size(); ++i) {
    auto found = llvm::find(variables, operands[i]);
    if (found == variables.end())
      continue;
    slot[i] = static_cast<unsigned>(found - variables.begin());
  }
  llvm::SmallVector<llvm::APInt> fixedConstants;
  for (unsigned i = 0; i < operands.size(); ++i) {
    if (slot[i])
      continue;
    auto known = constantValue(resolve(operands[i]));
    auto width = scalarWidth(operands[i].getType());
    if (!known || !width)
      return std::nullopt;
    fixedConstants.push_back(known->zextOrTrunc(*width));
  }
  auto widths = [&](unsigned var) -> unsigned {
    return *scalarWidth(variables[var].getType());
  };
  auto accept = [&](llvm::ArrayRef<llvm::APInt> guess)
      -> std::optional<llvm::SmallVector<llvm::APInt>> {
    llvm::SmallVector<llvm::APInt> args;
    unsigned constant = 0;
    for (unsigned i = 0; i < operands.size(); ++i) {
      if (slot[i])
        args.push_back(guess[*slot[i]].zextOrTrunc(widths(*slot[i])));
      else
        args.push_back(fixedConstants[constant++]);
    }
    if (!evalMatches(op, args, expected))
      return std::nullopt;
    return llvm::SmallVector<llvm::APInt>(guess.begin(), guess.end());
  };
  const unsigned n = variables.size();
  llvm::SmallVector<llvm::APInt> guess;
  auto zeros = [&]() {
    guess.clear();
    for (unsigned i = 0; i < n; ++i)
      guess.push_back(llvm::APInt(widths(i), 0));
  };
  zeros();
  if (auto solved = accept(guess))
    return solved;
  for (unsigned i = 0; i < n; ++i) {
    zeros();
    guess[i] = expected.zextOrTrunc(widths(i));
    if (auto solved = accept(guess))
      return solved;
    zeros();
    guess[i] = llvm::APInt(widths(i), 1);
    if (auto solved = accept(guess))
      return solved;
    zeros();
    guess[i] = llvm::APInt::getAllOnes(widths(i));
    if (auto solved = accept(guess))
      return solved;
  }
  guess.clear();
  for (unsigned i = 0; i < n; ++i)
    guess.push_back(llvm::APInt::getAllOnes(widths(i)));
  if (auto solved = accept(guess))
    return solved;
  if (n == 1) {
    guess = {~expected.zextOrTrunc(widths(0))};
    if (auto solved = accept(guess))
      return solved;
  }
  if (auto mux = dyn_cast<pyc::MuxOp>(op)) {
    auto indexOf = [&](unsigned operand) -> std::optional<unsigned> {
      return slot[operand];
    };
    auto sel = indexOf(0);
    auto armA = indexOf(1);
    auto armB = indexOf(2);
    auto paint = [&](std::optional<unsigned> slot, llvm::APInt value,
                     bool isSel) {
      if (!slot)
        return;
      guess[*slot] = isSel ? llvm::APInt(widths(*slot), value.getZExtValue())
                           : value.zextOrTrunc(widths(*slot));
    };
    zeros();
    paint(sel, llvm::APInt(1, 1), true);
    paint(armA, expected, false);
    if (auto solved = accept(guess))
      return solved;
    zeros();
    paint(sel, llvm::APInt(1, 0), true);
    paint(armB, expected, false);
    if (auto solved = accept(guess))
      return solved;
    (void)mux;
  }
  return std::nullopt;
}

struct Peel {
  Value data;
  llvm::SmallVector<pyc::MuxOp> muxes;
  llvm::SmallVector<Value> enableConds;
  llvm::SmallVector<bool> enableNegated;
};

static std::optional<Peel> peelHold(pyc::RegOp reg) {
  Peel peel;
  peel.data = resolve(reg.getNext());
  Value q = reg.getQ();
  for (unsigned guard = 0; guard < 8; ++guard) {
    auto mux = peel.data.getDefiningOp<pyc::MuxOp>();
    if (!mux)
      break;
    auto selWidth = scalarWidth(mux.getSel().getType());
    if (!selWidth || *selWidth != 1)
      break;
    Value heldA = resolve(mux.getA());
    Value heldB = resolve(mux.getB());
    if (heldB == q) {
      peel.enableConds.push_back(mux.getSel());
      peel.enableNegated.push_back(false);
      peel.muxes.push_back(mux);
      peel.data = resolve(mux.getA());
    } else if (heldA == q) {
      peel.enableConds.push_back(mux.getSel());
      peel.enableNegated.push_back(true);
      peel.muxes.push_back(mux);
      peel.data = resolve(mux.getB());
    } else {
      break;
    }
  }
  return peel;
}

static Operation *later(Operation *current, Operation *next) {
  if (!next)
    return current;
  if (!current || current->getBlock() != next->getBlock())
    return next;
  return current->isBeforeInBlock(next) ? next : current;
}

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

static Value materializeEnable(OpBuilder &builder, Location loc, Value enable,
                               const Peel &peel) {
  for (auto [cond, negated] : llvm::zip(peel.enableConds, peel.enableNegated)) {
    Value bit = cond;
    if (negated)
      bit = builder.create<pyc::NotOp>(loc, bit.getType(), bit);
    if (isConstOne(enable))
      enable = bit;
    else if (!isConstOne(bit))
      enable = builder.create<pyc::AndOp>(loc, enable.getType(), enable, bit);
  }
  return enable;
}

static Value ensureConstant(OpBuilder &builder, Location loc, llvm::APInt value) {
  Block *block = builder.getInsertionBlock();
  for (auto it = block->begin(); it != builder.getInsertionPoint(); ++it) {
    auto constant = dyn_cast<pyc::ConstantOp>(&*it);
    if (!constant)
      continue;
    llvm::APInt known = constant.getValueAttr().getValue();
    if (known.getBitWidth() == value.getBitWidth() && known == value)
      return constant.getResult();
  }
  auto type = IntegerType::get(builder.getContext(), value.getBitWidth());
  return builder
      .create<pyc::ConstantOp>(loc, type, IntegerAttr::get(type, value))
      .getResult();
}

static bool hoistOne(pyc::RegOp reg, HoistStats &stats,
                     llvm::DenseSet<Operation *> &initBlocked) {
  if (initBlocked.contains(reg.getOperation()))
    return false;
  if (!scalarWidth(reg.getQ().getType()))
    return false;
  auto peeled = peelHold(reg);
  if (!peeled)
    return false;
  Operation *root = peeled->data.getDefiningOp();
  if (!root || root->getBlock() != reg->getBlock() || !isHoistableOp(root))
    return false;
  if (!scalarWidth(root->getResult(0).getType()))
    return false;

  llvm::DenseSet<Operation *> skipped;
  for (pyc::MuxOp mux : peeled->muxes)
    skipped.insert(mux.getOperation());
  if (!hasCombUser(reg.getQ(), skipped))
    return false;

  llvm::SmallVector<Value> variables;
  for (Value operand : root->getOperands()) {
    if (constantValue(resolve(operand)))
      continue;
    if (!scalarWidth(operand.getType()))
      return false;
    llvm::DenseSet<Value> seen;
    if (combDependsOn(operand, reg.getQ(), seen))
      return false;
    if (!llvm::is_contained(variables, operand))
      variables.push_back(operand);
  }
  if (variables.empty())
    return false;

  auto oldInit = constantValue(resolve(reg.getInit()));
  if (!oldInit || oldInit->getBitWidth() !=
                      scalarWidth(reg.getQ().getType()).value_or(0)) {
    ++stats.blockedInit;
    initBlocked.insert(reg.getOperation());
    return false;
  }
  auto inits = solveInits(root, root->getOperands(), variables, *oldInit);
  if (!inits) {
    ++stats.blockedInit;
    initBlocked.insert(reg.getOperation());
    return false;
  }

  Operation *insertAfter = reg;
  insertAfter = later(insertAfter, root);
  for (Value operand : root->getOperands())
    insertAfter = later(insertAfter, operand.getDefiningOp());
  for (Value cond : peeled->enableConds)
    insertAfter = later(insertAfter, cond.getDefiningOp());
  OpBuilder builder(reg.getContext());
  builder.setInsertionPointAfter(insertAfter);

  Value enable =
      materializeEnable(builder, reg.getLoc(), reg.getEn(), *peeled);
  IRMapping mapping;
  for (auto [var, operand] : llvm::enumerate(variables)) {
    Value init = ensureConstant(builder, reg.getLoc(), (*inits)[var]);
    auto created = builder.create<pyc::RegOp>(
        reg.getLoc(), operand.getType(), reg.getClk(), reg.getRst(), enable,
        operand, init);
    created->setAttr("pyc.optimized_by", builder.getStringAttr(kHoistedBy));
    if (auto generated = reg->getAttrOfType<StringAttr>("pyc.generated"))
      created->setAttr("pyc.generated", generated);
    mapping.map(operand, created.getQ());
  }
  Operation *moved = builder.clone(*root, mapping);
  // The clone is the delayed value. Observation names stay on the original
  // op, which still denotes the pre-register result.
  llvm::SmallVector<StringAttr> dropAttrs;
  for (NamedAttribute attr : moved->getAttrs()) {
    StringRef name = attr.getName().strref();
    if (name == "pyc.name" || name == "pyc.debug_keep" ||
        name == "pyc.observable" || name.starts_with("pyc.probe") ||
        name.starts_with("pyc.trace"))
      dropAttrs.push_back(attr.getName());
  }
  for (StringAttr name : dropAttrs)
    moved->removeAttr(name);
  Value delayed = moved->getResult(0);
  remapStateOpIdentity(builder, reg, delayed);
  reg.getQ().replaceAllUsesWith(delayed);
  reg.erase();
  // A hold mux often reaches the register through a wire assign. Once the
  // register is gone, that assign is the only user; leaving it would keep a
  // dead copy of the pre-hoist next cone.
  for (pyc::MuxOp mux : peeled->muxes) {
    llvm::SmallVector<Operation *> users(mux->user_begin(), mux->user_end());
    for (Operation *user : users) {
      auto assign = dyn_cast<pyc::AssignOp>(user);
      if (!assign)
        continue;
      Value wire = assign.getDst();
      bool onlyThisAssign = true;
      for (Operation *wireUser : wire.getUsers()) {
        if (wireUser != assign)
          onlyThisAssign = false;
      }
      if (onlyThisAssign)
        assign.erase();
    }
    if (mux->use_empty())
      mux.erase();
  }
  if (root->use_empty() && !hasExternalObservationIdentity(root))
    root->erase();
  sinkUsersBelow(moved);

  ++stats.regsHoisted;
  ++stats.opsMoved;
  return true;
}

static HoistStats hoistUpstream(func::FuncOp function) {
  HoistStats stats;
  llvm::DenseSet<Operation *> initBlocked;
  unsigned budget = 0;
  function.walk([&](Operation *) { ++budget; });
  if (budget == 0)
    budget = 1;
  for (unsigned round = 0; round < budget; ++round) {
    llvm::SmallVector<pyc::RegOp> regs;
    function.walk([&](pyc::RegOp reg) { regs.push_back(reg); });
    bool hoisted = false;
    for (pyc::RegOp reg : regs) {
      if (hoistOne(reg, stats, initBlocked))
        hoisted = true;
    }
    if (!hoisted)
      break;
  }
  setI64Attr(function, "pyc.stats.hoist_regs_upstream", stats.regsHoisted);
  setI64Attr(function, "pyc.stats.hoist_ops_moved", stats.opsMoved);
  setI64Attr(function, "pyc.stats.hoist_blocked_init", stats.blockedInit);
  return stats;
}

struct HoistRegsUpstreamPass
    : public PassWrapper<HoistRegsUpstreamPass, OperationPass<func::FuncOp>> {
  MLIR_DEFINE_EXPLICIT_INTERNAL_INLINE_TYPE_ID(HoistRegsUpstreamPass)

  StringRef getArgument() const override { return "pyc-hoist-regs-upstream"; }
  StringRef getDescription() const override {
    return "Move registers one combinational op upstream, duplicating a "
           "register onto each non-constant input, so the op joins downstream "
           "combinational logic";
  }

  void runOnOperation() override { hoistUpstream(getOperation()); }
};

} // namespace

std::unique_ptr<::mlir::Pass> createHoistRegsUpstreamPass() {
  return std::make_unique<HoistRegsUpstreamPass>();
}

void runHoistRegsUpstream(func::FuncOp function) { hoistUpstream(function); }

static PassRegistration<HoistRegsUpstreamPass> hoistRegsUpstreamPass;

} // namespace pyc

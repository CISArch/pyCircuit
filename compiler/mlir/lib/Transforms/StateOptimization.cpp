#include "pyc/Transforms/StateOptimization.h"

#include "mlir/IR/BuiltinAttributes.h"
#include "llvm/ADT/DenseSet.h"
#include "llvm/ADT/Hashing.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/StringRef.h"

using namespace mlir;

namespace pyc {

namespace {

static bool isObservationAttrName(llvm::StringRef name) {
  return name == "pyc.name" || name == "pyc.debug_keep" ||
         name == "pyc.observable" || name.starts_with("pyc.probe") ||
         name.starts_with("pyc.trace");
}

static std::size_t opaqueHash(const void *ptr) {
  return static_cast<std::size_t>(llvm::hash_value(ptr));
}

// Semantic hash of a value (resolved through aliases; constants by literal).
static std::size_t semanticValueHash(Value value) {
  value = stripStateAliases(value);
  if (auto constant = value.getDefiningOp<pyc::ConstantOp>()) {
    Attribute literal = constant->getAttr("value");
    return static_cast<std::size_t>(llvm::hash_combine(
        value.getType().getAsOpaquePointer(), literal.getAsOpaquePointer(), 1));
  }
  return static_cast<std::size_t>(llvm::hash_combine(
      value.getType().getAsOpaquePointer(), value.getAsOpaquePointer(), 0));
}

} // namespace

bool isStatefulConsumer(Operation *op) {
  return isa<pyc::RegOp, pyc::DelayLineOp, pyc::FifoOp,
             pyc::ByteMemOp, pyc::SyncMemOp, pyc::SyncMemDPOp,
             pyc::AsyncFifoOp, pyc::CdcSyncOp, pyc::InstanceOp>(op);
}

bool isCycleBalanceGenerated(Operation *op) {
  if (!op)
    return false;
  auto generated = op->getAttrOfType<StringAttr>("pyc.generated");
  return generated && generated.getValue() == "cycle_balance";
}

bool hasExternalObservationIdentity(Operation *op) {
  if (!op)
    return false;
  const bool skipCycleBalanceName = isCycleBalanceGenerated(op);
  for (NamedAttribute attr : op->getAttrs()) {
    llvm::StringRef name = attr.getName().strref();
    if (!isObservationAttrName(name))
      continue;
    if (name == "pyc.name" && skipCycleBalanceName)
      continue;
    return true;
  }
  return false;
}

bool stateHasExternalObservation(Operation *state, Value q) {
  if (hasExternalObservationIdentity(state))
    return true;
  llvm::SmallVector<Value> worklist{q};
  llvm::DenseSet<Value> seen;
  while (!worklist.empty()) {
    Value value = worklist.pop_back_val();
    if (!seen.insert(value).second)
      continue;
    for (Operation *user : value.getUsers()) {
      auto alias = dyn_cast<pyc::AliasOp>(user);
      if (!alias)
        continue;
      if (hasExternalObservationIdentity(alias))
        return true;
      worklist.push_back(alias.getResult());
    }
  }
  return false;
}

void copyExternalObservationAttrs(Operation *from, Operation *to) {
  if (!from || !to)
    return;
  const bool skipCycleBalanceName = isCycleBalanceGenerated(from);
  for (NamedAttribute attr : from->getAttrs()) {
    llvm::StringRef name = attr.getName().strref();
    if (!isObservationAttrName(name))
      continue;
    if (name == "pyc.name" && skipCycleBalanceName)
      continue;
    to->setAttr(attr.getName(), attr.getValue());
  }
}

pyc::AliasOp materializeObservationAlias(OpBuilder &builder, Location loc,
                                         Value source,
                                         Operation *attrSource) {
  auto alias =
      builder.create<pyc::AliasOp>(loc, source.getType(), source);
  copyExternalObservationAttrs(attrSource, alias);
  return alias;
}

void remapStateOpIdentity(OpBuilder &builder, Operation *oldState,
                          Value newSource) {
  if (!oldState || !newSource || !hasExternalObservationIdentity(oldState))
    return;
  materializeObservationAlias(builder, oldState->getLoc(), newSource,
                              oldState);
}

Value stripStateAliases(Value value) {
  while (auto alias = value.getDefiningOp<pyc::AliasOp>())
    value = alias.getIn();
  return value;
}

bool equivalentStateValue(Value lhs, Value rhs) {
  lhs = stripStateAliases(lhs);
  rhs = stripStateAliases(rhs);
  if (lhs == rhs)
    return true;
  if (lhs.getType() != rhs.getType())
    return false;
  auto lhsConstant = lhs.getDefiningOp<pyc::ConstantOp>();
  auto rhsConstant = rhs.getDefiningOp<pyc::ConstantOp>();
  if (!lhsConstant || !rhsConstant)
    return false;
  return lhsConstant->getAttr("value") == rhsConstant->getAttr("value");
}

std::optional<StateChainLink>
matchStateChainPredecessor(pyc::RegOp consumer, pyc::RegOp keyReg) {
  Value value = consumer.getNext();
  StateChainLink link;
  while (auto alias = value.getDefiningOp<pyc::AliasOp>()) {
    link.aliasesFromConsumerToProducer.push_back(alias);
    value = alias.getIn();
  }

  auto predecessor = value.getDefiningOp<pyc::RegOp>();
  if (!predecessor)
    return std::nullopt;
  if (predecessor.getQ().getType() != keyReg.getQ().getType() ||
      !equivalentStateValue(predecessor.getClk(), keyReg.getClk()) ||
      !equivalentStateValue(predecessor.getRst(), keyReg.getRst()) ||
      !equivalentStateValue(predecessor.getEn(), keyReg.getEn()) ||
      !equivalentStateValue(predecessor.getInit(), keyReg.getInit()))
    return std::nullopt;

  Value expectedProducer = predecessor.getQ();
  auto hasRequiredUser = [&](Value value, Operation *required) {
    for (Operation *user : value.getUsers()) {
      if (user != required && isStatefulConsumer(user))
        return false;
    }
    return llvm::is_contained(value.getUsers(), required);
  };
  for (pyc::AliasOp alias :
       llvm::reverse(link.aliasesFromConsumerToProducer)) {
    if (!hasRequiredUser(expectedProducer, alias.getOperation()))
      return std::nullopt;
    expectedProducer = alias.getResult();
  }
  if (!hasRequiredUser(expectedProducer, consumer.getOperation()))
    return std::nullopt;

  link.predecessor = predecessor;
  return link;
}

bool equivalentDelayLineState(pyc::DelayLineOp lhs, pyc::DelayLineOp rhs) {
  auto lhsDepth = lhs->getAttrOfType<IntegerAttr>("depth");
  auto rhsDepth = rhs->getAttrOfType<IntegerAttr>("depth");
  return lhsDepth && rhsDepth && lhsDepth == rhsDepth &&
         lhs.getQ().getType() == rhs.getQ().getType() &&
         equivalentStateValue(lhs.getClk(), rhs.getClk()) &&
         equivalentStateValue(lhs.getRst(), rhs.getRst()) &&
         equivalentStateValue(lhs.getEn(), rhs.getEn()) &&
         equivalentStateValue(lhs.getNext(), rhs.getNext()) &&
         equivalentStateValue(lhs.getInit(), rhs.getInit());
}

std::size_t delayLineStateHash(pyc::DelayLineOp delay) {
  auto depth = delay->getAttrOfType<IntegerAttr>("depth");
  return static_cast<std::size_t>(llvm::hash_combine(
      opaqueHash(delay.getQ().getType().getAsOpaquePointer()),
      depth ? depth.getInt() : 0,
      semanticValueHash(delay.getClk()), semanticValueHash(delay.getRst()),
      semanticValueHash(delay.getEn()), semanticValueHash(delay.getNext()),
      semanticValueHash(delay.getInit())));
}

} // namespace pyc

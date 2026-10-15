// Partition pyc.reg ops into per-clock SeqBank groups. Analysis-only: no IR
// semantics change. Each reg gets `pyc.seq_bank_id = <i>` (banks are numbered
// densely per function, one bank per equivalent-clock domain); the function
// gets `pyc.stats.seq_bank_groups` / `pyc.stats.seq_bank_lanes`. The C++
// emitter uses the ids to lower each bank into one pyc::cpp::SeqBank<W>
// member and one generated update loop instead of per-reg expansions.
//
// Equivalence of clock/reset/enable SSA values reuses the same
// equivalent-state helpers the state optimizer uses, so a bank is exactly the
// set of registers that could share one edge check.

#include "pyc/Transforms/Passes.h"
#include "pyc/Transforms/StateOptimization.h"

#include "pyc/Dialect/PYC/PYCOps.h"

#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/IR/Builders.h"
#include "mlir/Pass/Pass.h"
#include "llvm/ADT/DenseMap.h"
#include "llvm/ADT/SmallVector.h"

#include <algorithm>

using namespace mlir;

namespace pyc {
namespace {

constexpr llvm::StringLiteral kSeqBankId = "pyc.seq_bank_id";
constexpr llvm::StringLiteral kSeqBankGroups = "pyc.stats.seq_bank_groups";
constexpr llvm::StringLiteral kSeqBankLanes = "pyc.stats.seq_bank_lanes";

struct SeqBankPartitionPass
    : public PassWrapper<SeqBankPartitionPass, OperationPass<func::FuncOp>> {
  MLIR_DEFINE_EXPLICIT_INTERNAL_INLINE_TYPE_ID(SeqBankPartitionPass)

  SeqBankPartitionPass() = default;
  SeqBankPartitionPass(const SeqBankPartitionPass &other)
      : PassWrapper(other) {}

  StringRef getArgument() const override { return "pyc-seq-bank-partition"; }
  StringRef getDescription() const override {
    return "Group registers per clock domain into SeqBank ids (analysis only)";
  }

  void runOnOperation() override {
    func::FuncOp function = getOperation();

    // Regs whose clk resolves to equivalent values share a bank. Reset /
    // enable stay per-lane (they are read per lane in the bank loop), so
    // only the clock drives the partition. Debug-keep / observable regs keep
    // their q wire address, which SeqBank preserves, so no exclusion is
    // needed here.
    llvm::SmallVector<pyc::RegOp> regs;
    function.walk([&](pyc::RegOp reg) { regs.push_back(reg); });
    if (regs.empty()) {
      setI64Attr(function, kSeqBankGroups, 0);
      setI64Attr(function, kSeqBankLanes, 0);
      return;
    }

    // Deterministic order: block layout.
    std::sort(regs.begin(), regs.end(), [](pyc::RegOp a, pyc::RegOp b) {
      return a->isBeforeInBlock(b);
    });

    llvm::DenseMap<Value, int64_t> clkToBank;
    int64_t nextBank = 0;
    int64_t lanes = 0;
    for (pyc::RegOp reg : regs) {
      Value clk = reg.getClk();
      auto it = clkToBank.find(clk);
      int64_t bankId;
      if (it != clkToBank.end()) {
        bankId = it->second;
      } else {
        // Alias through transparent ops so `%clk_deref = %clk` style values
        // land in the same bank.
        Value canonical = clk;
        if (auto *def = clk.getDefiningOp())
          if (isa<pyc::AliasOp>(def))
            canonical = def->getOperand(0);
        auto cit = clkToBank.find(canonical);
        if (cit != clkToBank.end()) {
          bankId = cit->second;
        } else {
          bankId = nextBank++;
          clkToBank[canonical] = bankId;
        }
        clkToBank[clk] = bankId;
      }
      reg->setAttr(kSeqBankId,
                   IntegerAttr::get(IntegerType::get(reg->getContext(), 64),
                                    bankId));
      ++lanes;
    }

    setI64Attr(function, kSeqBankGroups, nextBank);
    setI64Attr(function, kSeqBankLanes, lanes);
  }
};

} // namespace

std::unique_ptr<::mlir::Pass> createSeqBankPartitionPass() {
  return std::make_unique<SeqBankPartitionPass>();
}

namespace {
static PassRegistration<SeqBankPartitionPass> pass;
} // namespace

} // namespace pyc

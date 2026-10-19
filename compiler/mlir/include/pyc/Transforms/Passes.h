#pragma once

#include <memory>

#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Pass/Pass.h"

namespace pyc {

std::unique_ptr<::mlir::Pass> createCombCanonicalizePass();
std::unique_ptr<::mlir::Pass> createInlineFunctionsPass();
std::unique_ptr<::mlir::Pass> createFuseCombPass();
std::unique_ptr<::mlir::Pass> createEliminateWiresPass();
std::unique_ptr<::mlir::Pass> createCombineDelayChainsPass();
std::unique_ptr<::mlir::Pass> createPackI1RegsPass();
std::unique_ptr<::mlir::Pass> createLowerSCFToPYCStaticPass();
std::unique_ptr<::mlir::Pass> createCheckFrontendContractPass();
std::unique_ptr<::mlir::Pass> createCheckHierarchyDisciplinePass();
std::unique_ptr<::mlir::Pass> createCheckNoDynamicPass();
std::unique_ptr<::mlir::Pass> createCheckCombCyclesPass();
std::unique_ptr<::mlir::Pass> createCheckClockDomainsPass();
std::unique_ptr<::mlir::Pass> createChangeDrivenSchedulePass();
std::unique_ptr<::mlir::Pass> createCheckFlatTypesPass();
std::unique_ptr<::mlir::Pass> createPrunePortsPass();
std::unique_ptr<::mlir::Pass> createEliminateDeadStatePass();
std::unique_ptr<::mlir::Pass> createEliminateDeadInstancesPass();
std::unique_ptr<::mlir::Pass> createSLPPackWiresPass();
std::unique_ptr<::mlir::Pass> createCheckLogicDepthPass(unsigned logicDepth);
std::unique_ptr<::mlir::Pass> createCollectCompileStatsPass();
std::unique_ptr<::mlir::Pass> createFlattenInstancesPass();
/// C++ emit prep: sets module comb chunk size and runs member placement.
std::unique_ptr<::mlir::Pass> createCppPlacementPass(unsigned combChunkNodes);
std::unique_ptr<::mlir::Pass> createVectorUnrollPass();

/// Phase runners shared with the unified StateOptimizePass. Defined next to
/// the passes whose cores they drive.
void runDelayChainFormAndShare(::mlir::func::FuncOp function);
void runEliminateDeadState(::mlir::func::FuncOp function);

/// Unified C++-only structural state optimization pipeline: one func-level
/// pass that runs the state rewrites in a fixed order.
std::unique_ptr<::mlir::Pass> createStateOptimizePass();

} // namespace pyc

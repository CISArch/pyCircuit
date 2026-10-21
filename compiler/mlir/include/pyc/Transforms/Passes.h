#pragma once

#include <memory>
#include <string>

#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Pass/Pass.h"

namespace pyc {

std::unique_ptr<::mlir::Pass> createCombCanonicalizePass();
std::unique_ptr<::mlir::Pass> createInlineFunctionsPass();
std::unique_ptr<::mlir::Pass> createFuseCombPass();
std::unique_ptr<::mlir::Pass> createEliminateWiresPass();
std::unique_ptr<::mlir::Pass> createCombineDelayChainsPass();
std::unique_ptr<::mlir::Pass> createRetimePipelinesPass();
std::unique_ptr<::mlir::Pass> createPackI1RegsPass();
/// After C++ state opt remaps identities, drop pyc.name values that are not
/// in the runtime observation demand set (@probe source, trace fields, or
/// debug_keep/observable/probe*/trace*).
std::unique_ptr<::mlir::Pass>
createApplyObservationDemandPass(std::string probePlanPath = {},
                                 std::string traceCodegenPlanPath = {});
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
/// C++ emit prep: sets module comb chunk size and runs member placement.
/// Named values stay on the struct so probes and VCD sampling keep stable
/// addresses. A trace codegen plan, when given, must name fields that exist.
std::unique_ptr<::mlir::Pass>
createCppPlacementPass(unsigned combChunkNodes,
                       std::string traceCodegenPlanPath = {});
std::unique_ptr<::mlir::Pass> createVectorUnrollPass();

/// Phase runners shared with the unified StateOptimizePass. Defined next to
/// the passes whose cores they drive.
void runDelayChainMergeRound(::mlir::func::FuncOp function);
void runRetimePipelines(::mlir::func::FuncOp function);
void runDelayChainFormAndShare(::mlir::func::FuncOp function);
void runEliminateDeadState(::mlir::func::FuncOp function);
void runPackStateLanes(::mlir::func::FuncOp function, unsigned maxWidth);

/// Unified C++-only structural state optimization pipeline: one func-level
/// pass that runs the state rewrites in a fixed order.
struct StateOptimizeTunables {
  unsigned packMaxWidth = 1024; // 0 disables lane packing
};
std::unique_ptr<::mlir::Pass>
createStateOptimizePass(const StateOptimizeTunables &tunables = {});

/// Packs same-control integer reg / delay-line lanes into one wider state op;
/// lane values come back as `pyc.state_pack_lsb`-tagged extracts.
std::unique_ptr<::mlir::Pass> createPackStateLanesPass(unsigned maxWidth = 1024);

/// Analysis-only: tag each pyc.reg / scalar pyc.delay_line with
/// `pyc.loop_id` (one loop per equivalent clock domain) plus function-level
/// stats; the C++ emitter lowers each loop into one pyc::cpp::RegLoop<W> /
/// DelayLoop<W> update loop.
std::unique_ptr<::mlir::Pass> createStateLoopPartitionPass();

} // namespace pyc

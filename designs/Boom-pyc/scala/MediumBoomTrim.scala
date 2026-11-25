// 裁剪版 MediumBOOM elaboration 配置。
//
// 目标：保留完整 MediumBOOM tile（WithNMediumBooms：fetchWidth=4、2 发射、
// TAGE-L BPD、FPU、64 项 ROB、80/64 物理寄存器、4 路 I$/D$），裁掉全部
// v2p v1 无法处理的部分：
//   - 无 MMIO / Slave AXI 端口、无外部中断（WithNExtTopInterrupts(0)，
//     消除 IntSyncCrossingSource 跨时钟域中断同步）
//   - 无 BootROM / MaskROM / Debug（避免 AsyncResetReg / DTM/JTAG）
//   - 单一 implicit clock/reset：TestHarness 将 io_clocks 全接同一时钟
//   - 仅保留内存 AXI4 端口（BOOM 取指/访存的唯一通道）
//
// tile 边界用 WithCoherentBusTopology（与 rocket-chip DefaultConfig 一致，
// 单核无 L2 时只含权限管理包装，不生成 InclusiveCache）。
package boomtrim

import org.chipsalliance.cde.config.Config

import freechips.rocketchip.subsystem.{HasTilesExternalResetVectorKey, InSubsystem, WithNExtTopInterrupts, WithNoMMIOPort, WithNoSlavePort}
import freechips.rocketchip.devices.debug.DebugModuleKey
import freechips.rocketchip.devices.tilelink.BootROMLocated
import freechips.rocketchip.system.BaseConfig

class MediumBoomTrimConfig extends Config(
  new boom.v4.common.WithNMediumBooms(1) ++
    new freechips.rocketchip.subsystem.WithCoherentBusTopology ++
    new WithNoMMIOPort ++
    new WithNoSlavePort ++
    new WithNExtTopInterrupts(0) ++
    // 裁掉默认 BootROM（BaseSubsystemConfig 默认挂 ./bootrom/bootrom.img）。
    // BootROM 是 tile reset vector 的唯一驱动源；裁掉后把 reset vector 改为
    // 顶层输入端口（每 tile 一个 UInt 输入），由仿真 TB 驱动。
    // 同时裁掉默认 Debug 模块（DMI/JTAG 端口需要 harness 驱动，v1 无法处理）。
    new Config((site, here, up) => {
      case BootROMLocated(InSubsystem) => Nil
      case HasTilesExternalResetVectorKey => true
      case DebugModuleKey => None
    }) ++
    new BaseConfig
)

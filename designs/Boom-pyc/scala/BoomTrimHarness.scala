// 裁剪版 TestHarness：替代 freechips.rocketchip.system.TestHarness。
//
// 差异：
//   - 单一 implicit clock/reset（io_clocks 全接同一时钟，同步复位）
//   - 无 Debug/DTM（裁剪 config 未挂 debug，无需 ndreset 异步复位混合）
//   - 显式驱动顶层 reset_vector 输入端口（HasTilesExternalResetVectorKey=true
//     的产物；0x80000000 为 BOOM 默认复位地址）
//   - 仅挂 SimAXIMem 内存模型（MMIO/Slave 端口已被 config 裁掉）
package boomtrim

import chisel3._

import org.chipsalliance.cde.config.Parameters
import org.chipsalliance.diplomacy.lazymodule.LazyModule

import freechips.rocketchip.system.{ExampleRocketSystem, SimAXIMem}
import freechips.rocketchip.util.DontTouch

class BoomTrimHarness(implicit p: Parameters) extends Module with DontTouch {
  // 顶层必须有输出端口：firtool 的 IMCP+DCE 会把无输出（无观测效应）的
  // 电路整体抽空。暴露 mem AXI AR 通道（取指/访存必经路径），使
  // BoomCore→Frontend→ICache/DCache→TL→AXI 全链路保持存活。
  val io = IO(new Bundle {
    val mem_araddr = Output(UInt(64.W))
    val mem_arvalid = Output(Bool())
  })

  val ldut = LazyModule(new ExampleRocketSystem)
  val dut = Module(ldut.module)

  ldut.io_clocks.get.elements.values.foreach(_.clock := clock)
  ldut.io_clocks.get.elements.values.foreach(_.reset := reset.asBool)

  // BOOM 默认复位地址（与 chipyard 内存映射一致）
  dut.reset_vector.foreach(_ := 0x80000000L.U)

  dut.tieOffInterrupts()
  SimAXIMem.connectMem(ldut)
  dut.dontTouchPorts()

  val axi = ldut.mem_axi4.head
  io.mem_araddr := axi.ar.bits.addr
  io.mem_arvalid := axi.ar.valid
}

// 独立的 elaborate 入口：与 freechips.rocketchip.diplomacy.Main 逻辑相同，
// 但用裸 main(args) 替代 mainargs 解析（本机 classpath 中 mainargs 版本
// 与 diplomacy.Main 编译产物行为不匹配，子命令无法识别）。
//
// 用法：boomtrim.ElaborateMain <dir> <top-class> <config-class> [more configs…]
package boomtrim

import chisel3.RawModule
import chisel3.stage.ChiselGeneratorAnnotation
import chisel3.stage.phases.{Elaborate, Convert}
import firrtl.AnnotationSeq
import firrtl.options.TargetDirAnnotation
import org.chipsalliance.diplomacy.lazymodule.LazyModule
import org.chipsalliance.cde.config.{Config, Parameters}

object ElaborateMain {
  def main(args: Array[String]): Unit = {
    val dir = args(0)
    val top = args(1)
    val configs = args.drop(2)
    var topName: String = null
    val gen = () =>
      Class
        .forName(top)
        .getConstructor(classOf[Parameters])
        .newInstance(new Config(configs.foldRight(Parameters.empty) {
          case (currentName, config) =>
            val currentConfig = Class.forName(currentName).getDeclaredConstructor().newInstance().asInstanceOf[Config]
            currentConfig ++ config
        })) match {
          case m: RawModule => m
          case lm: LazyModule => LazyModule(lm).module
        }

    val annos = (try Seq(new Elaborate, new Convert).foldLeft(
      Seq(TargetDirAnnotation(dir), ChiselGeneratorAnnotation(() => gen())): AnnotationSeq
    ) { case (as, phase) => phase.transform(as) }
    catch { case e: java.lang.reflect.InvocationTargetException =>
      e.getCause.printStackTrace()
      sys.exit(1)
    })
      .flatMap {
        case firrtl.stage.FirrtlCircuitAnnotation(circuit) =>
          topName = circuit.main
          os.write.over(os.Path(dir) / s"${circuit.main}.fir", circuit.serialize)
          None
        case _: chisel3.stage.ChiselCircuitAnnotation => None
        case _: chisel3.stage.DesignAnnotation[_] => None
        case a => Some(a)
      }
    os.write(os.Path(dir) / s"$topName.anno.json",
      firrtl.annotations.JsonProtocol.serialize(annos))
    println(s"elaborated $topName -> $dir/${topName}.fir")
  }
}

cmake_minimum_required(VERSION 3.20)
project(pyc_tb LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(PYC_TB_SOURCES
  "/home/ldz/pycircuit-workspace/pyCircuit-ext-module/out/e2e/sim/device/cpp/ext_dct8_top/ext_dct8_top.cpp"
  "/home/ldz/pycircuit-workspace/pyCircuit-ext-module/designs/examples/ext_dct8/ext/dct8.cpp"
  "/home/ldz/pycircuit-workspace/pyCircuit-ext-module/out/e2e/sim/tb/tb_ext_dct8_top.cpp"
)

add_executable(pyc_tb ${PYC_TB_SOURCES})
target_include_directories(pyc_tb PRIVATE
  "/home/ldz/pycircuit-workspace/pyCircuit-ext-module/out/e2e/sim/device/cpp"
  "/home/ldz/pycircuit-workspace/pyCircuit-ext-module/runtime"
  "/home/ldz/pycircuit-workspace/pyCircuit-ext-module/out/e2e/sim/device/cpp/ext_dct8_top"
)
list(PREPEND CMAKE_PREFIX_PATH "/home/ldz/pycircuit-workspace/pyCircuit-ext-module/.pycircuit_out/toolchain/install")
find_package(pycircuit CONFIG REQUIRED PATHS "/home/ldz/pycircuit-workspace/pyCircuit-ext-module/.pycircuit_out/toolchain/install/share/pycircuit/cmake" NO_DEFAULT_PATH)
target_link_libraries(pyc_tb PRIVATE pycircuit::pyc4_runtime)


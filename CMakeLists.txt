cmake_minimum_required(VERSION 3.20)
project(Computer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(Computer
    src/Gates/Basic.cpp
    src/Combinational/Adder.cpp
    src/Combinational/Selector.cpp
    src/Combinational/Comparator.cpp
    src/Combinational/Shifter.cpp
    src/Combinational/Logic.cpp
    src/Combinational/Decoder.cpp
    src/Combinational/ControlSignal.cpp

    src/CPU/ALU.cpp

    src/Sequential/Latch.cpp
    src/Sequential/FlipFlop.cpp
    src/Sequential/Register.cpp
    src/Sequential/RegisterFile.cpp
    src/Sequential/Memory.cpp
    src/Sequential/ControlUnit.cpp
    src/Sequential/ProgramCounter.cpp

    src/utils.cpp

    src/CPU/CPU.cpp
    test.cpp
)

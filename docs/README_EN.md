# 16-bit CPU Project

A Complete 16-bit CPU Simulator Built from Gate Level

[KOR VER](README.md)

---

## 📋 Table of Contents
- [Project Overview](#project-overview)
- [Key Features](#key-features)
- [System Architecture](#system-architecture)
- [Instruction Set](#instruction-set)
- [Project Structure](#project-structure)
- [Build and Run](#build-and-run)
- [Usage Examples](#usage-examples)
- [Testing](#testing)
- [Future Plans](#future-plans)

---

## 🎯 Project Overview

This project is a complete 16-bit CPU hardware simulator implemented in C++ **from the gate level up**.

### Core Constraints
- ❌ **No C++ Operators**: No `+`, `-`, `*`, `/`, `&`, `|`, `^`, `if`, `switch`, etc.
- ✅ **Gates Only**: Everything built using AND, OR, NOT, XOR, NAND, NOR gates
- ✅ **True Hardware Simulation**: Follows actual digital circuit behavior

### Design Philosophy
Understand and implement how real computer hardware works, starting from the gate level.

---

## ✨ Key Features

### Complete Hardware Stack
```
CPU (Complete)
├── Control Unit
│   ├── Instruction Decoder
│   └── Control Signal Generator
├── Datapath
│   ├── ALU (16 operations)
│   ├── Register File (8 registers)
│   ├── Program Counter
│   └── Memory (64KB)
└── Gates
```

### Implemented Components

#### 1. Basic Gates
- AND, OR, NOT, NAND, NOR, XOR

#### 2. Combinational Logic
- **Arithmetic**: Adder, Subtractor, Incrementor, Decrementor
- **Selectors**: MUX, DMUX (2-way, 4-way, 8-way, 16-way)
- **Comparators**: Equal, LessThan, GreaterThan
- **Shifters**: Shift Left, Shift Right
- **Logic Operations**: 16-bit AND, OR, XOR, NOT
- **Decoder**: Instruction Decoder
- **Control Signal Generator**: Control signals for 16 instructions

#### 3. Sequential Logic
- **Latches**: SR Latch, D Latch
- **Flip-Flops**: D FlipFlop, JK FlipFlop, T FlipFlop
- **Registers**: 16-bit Register, Counter
- **Register File**: 8 x 16-bit registers
- **Memory**: 64KB (65,536 x 16-bit)
- **Control Unit**: Fetch-Decode-Execute control
- **Program Counter**: PC management and jump handling

#### 4. CPU
- **ALU**: 16 operations supported
- **Integrated CPU**: Complete Fetch-Decode-Execute cycle

---

## 🏗️ System Architecture

### CPU Architecture
```
┌─────────────────────────────────────────────────────────┐
│                         CPU                             │
├─────────────────────────────────────────────────────────┤
│  ┌──────────────┐         ┌─────────────────────────┐   │
│  │   Program    │────────►│    Control Unit         │   │
│  │   Counter    │         │  ┌─────────────────┐    │   │
│  └──────────────┘         │  │ IR (Instruction │    │   │
│         │                 │  │   Register)     │    │   │
│         │                 │  └─────────────────┘    │   │
│         │                 │         │               │   │
│         ▼                 │         ▼               │   │
│  ┌──────────────┐         │  ┌─────────────────┐    │   │
│  │   Memory     │◄────────┤  │    Decoder      │    │   │
│  │   (64KB)     │         │  └─────────────────┘    │   │
│  └──────────────┘         │         │               │   │
│         │                 │         ▼               │   │
│         │                 │  ┌─────────────────┐    │   │
│         │                 │  │ Control Signals │    │   │
│         │                 │  └─────────────────┘    │   │
│         │                 └─────────────────────────┘   │
│         ▼                           │                   │
│  ┌──────────────┐                   │                   │
│  │  Register    │◄───────────────── ┤                   │
│  │  File (8)    │                   │                   │
│  └──────────────┘                   │                   │
│         │                           │                   │
│         └───────────┬───────────────┘                   │
│                     ▼                                   │
│              ┌──────────────┐                           │
│              │     ALU      │                           │
│              │  (16 ops)    │                           │
│              └──────────────┘                           │
└─────────────────────────────────────────────────────────┘
```

### Instruction Execution Cycle
```
1. Fetch     : Memory[PC] → Instruction Register
2. Decode    : IR → Control Signals
3. Execute   : ALU operation or memory access
4. Write Back: Store result in register
5. Update PC : Increment PC or jump
```

---

## 📜 Instruction Set

### Instruction Formats

**R-Type** (Register operations):
```
[opcode: 4bit][dest: 3bit][src1: 3bit][src2: 3bit][unused: 3bit]
```

**I-Type** (Immediate):
```
[opcode: 4bit][dest: 3bit][src: 3bit][immediate: 6bit]
```

**J-Type** (Jump):
```
[opcode: 4bit][address: 12bit]
```

### Instruction List (16 instructions)

| Opcode | Mnemonic | Type | Syntax | Description |
|--------|----------|------|--------|-------------|
| 0000 | LOAD | I | `LOAD Rd, Rs, offset` | Rd = Memory[Rs + offset] |
| 0001 | STORE | I | `STORE Rd, Rs, offset` | Memory[Rd + offset] = Rs |
| 0010 | MOV | R | `MOV Rd, Rs` | Rd = Rs |
| 0011 | ADD | R | `ADD Rd, Rs1, Rs2` | Rd = Rs1 + Rs2 |
| 0100 | ADDI | I | `ADDI Rd, Rs, imm` | Rd = Rs + imm |
| 0101 | SUB | R | `SUB Rd, Rs1, Rs2` | Rd = Rs1 - Rs2 |
| 0110 | AND | R | `AND Rd, Rs1, Rs2` | Rd = Rs1 & Rs2 |
| 0111 | OR | R | `OR Rd, Rs1, Rs2` | Rd = Rs1 \| Rs2 |
| 1000 | XOR | R | `XOR Rd, Rs1, Rs2` | Rd = Rs1 ^ Rs2 |
| 1001 | NOT | R | `NOT Rd, Rs` | Rd = ~Rs |
| 1010 | SHL | R | `SHL Rd, Rs` | Rd = Rs << 1 |
| 1011 | SHR | R | `SHR Rd, Rs` | Rd = Rs >> 1 |
| 1100 | JMP | J | `JMP address` | PC = address |
| 1101 | JZ | J | `JZ address` | if (zero_flag) PC = address |
| 1110 | JNZ | J | `JNZ address` | if (!zero_flag) PC = address |
| 1111 | HALT | J | `HALT` | Stop CPU |

### Registers
- **8 General Purpose Registers**: R0 ~ R7
- **R0**: Always 0 (Zero Register)

---

## 📁 Project Structure

```
16bit-CPU/
├── include/
│   ├── types.hpp              # Basic type definitions
│   ├── utils.hpp              # Utility functions
│   ├── Gates.hpp              # Basic gates
│   ├── Combinational/         # Combinational circuits
│   │   ├── Adder.hpp
│   │   ├── Selector.hpp
│   │   ├── Comparator.hpp
│   │   ├── Shifter.hpp
│   │   ├── Logic.hpp
│   │   ├── Decoder.hpp
│   │   └── ControlSignal.hpp
│   ├── Sequential/            # Sequential circuits
│   │   ├── Latch.hpp
│   │   ├── FlipFlop.hpp
│   │   ├── Register.hpp
│   │   ├── RegisterFile.hpp
│   │   ├── Memory.hpp
│   │   ├── ControlUnit.hpp
│   │   └── ProgramCounter.hpp
│   └── CPU/
│       ├── ALU.hpp
│       └── CPU.hpp
├── src/                       # Implementation files
│   ├── Combinational/
│   ├── Sequential/
│   └── CPU/
└── tests/                     # Test files
    ├── test_CPU.cpp
    ├── test_ALU.cpp
    └── ...
```

---

## 🔧 Build and Run

### Requirements
- C++17 or higher
- CMake 3.10+ (optional)
- GCC or Clang

### Build
```bash
# Direct compilation
g++ -std=c++17 -I./include src/**/*.cpp tests/test_CPU.cpp -o test_cpu

# Run
./test_cpu
```

### Test Results
```
=== CPU Test Suite ===

Test 1 (Reset): PASS
Test 2 (ADDI): PASS
Test 3 (ADD): PASS
Test 4 (SUB): PASS
Test 5 (AND): PASS
Test 6 (OR): PASS
Test 7 (XOR): PASS
Test 8 (NOT): PASS
Test 9 (SHL): PASS
Test 10 (SHR): PASS
Test 11 (MOV): PASS
Test 12 (STORE & LOAD): PASS
Test 13 (JMP): PASS
Test 14 (JZ): PASS
Test 15 (JNZ): PASS
Test 16 (HALT): PASS
Test 17 (Loop): PASS
Test 18 (Fibonacci): PASS

=== Test Results ===
Passed: 18 / 18
All tests passed!
```

---

## 💡 Usage Examples

### Example 1: Simple Addition
```cpp
#include "CPU.hpp"
#include "utils.hpp"

int main() {
    // Create program: R3 = 10 + 20
    std::vector<Bit16> program;
    program.push_back(makeIType(0b0100, 1, 0, 10)); // ADDI R1, R0, 10
    program.push_back(makeIType(0b0100, 2, 0, 20)); // ADDI R2, R0, 20
    program.push_back(makeRType(0b0011, 3, 1, 2));  // ADD R3, R1, R2
    program.push_back(makeJType(0b1111, 0));        // HALT
    
    // Initialize and run CPU
    CPU::CPU cpu;
    cpu.reset();
    cpu.loadProgram(program);
    
    while (!cpu.isHalted()) {
        cpu.clock();
    }
    
    // Check result
    Bit16 r3 = cpu.readRegister(3);
    std::cout << "R3 = " << utils::BitToInt<16>(r3) << std::endl;  // 30
    
    return 0;
}
```

### Example 2: Loop (Sum from 1 to 5)
```cpp
// Program: sum = 1 + 2 + 3 + 4 + 5
std::vector<Bit16> program;
program.push_back(makeIType(0b0100, 1, 0, 0));  // R1 = 0 (sum)
program.push_back(makeIType(0b0100, 2, 0, 5));  // R2 = 5 (target)
program.push_back(makeIType(0b0100, 3, 0, 1));  // R3 = 1 (increment)
// Loop:
program.push_back(makeRType(0b0011, 1, 1, 3));  // R1 = R1 + R3
program.push_back(makeRType(0b0101, 4, 1, 2));  // R4 = R1 - R2
program.push_back(makeJType(0b1110, 3));        // JNZ Loop
program.push_back(makeJType(0b1111, 0));        // HALT

// R1 = 15
```

### Example 3: Fibonacci Sequence
```cpp
// Program: Calculate F(5)
std::vector<Bit16> program;
program.push_back(makeIType(0b0100, 1, 0, 0));  // R1 = 0 (F0)
program.push_back(makeIType(0b0100, 2, 0, 1));  // R2 = 1 (F1)
program.push_back(makeIType(0b0100, 4, 0, 1));  // R4 = 1 (counter)
program.push_back(makeIType(0b0100, 5, 0, 6));  // R5 = 6 (target)
// Loop:
program.push_back(makeRType(0b0011, 3, 1, 2));  // R3 = R1 + R2
program.push_back(makeRType(0b0010, 1, 2, 0));  // R1 = R2
program.push_back(makeRType(0b0010, 2, 3, 0));  // R2 = R3
program.push_back(makeIType(0b0100, 6, 0, 1));  // R6 = 1
program.push_back(makeRType(0b0011, 4, 4, 6));  // R4 = R4 + 1
program.push_back(makeRType(0b0101, 7, 4, 5));  // R7 = R4 - R5
program.push_back(makeJType(0b1110, 4));        // JNZ Loop
program.push_back(makeJType(0b1111, 0));        // HALT

// R3 = 5
```

---

## 🧪 Testing

### Test Structure
- **Unit Tests**: Independent tests for each component
- **Integration Tests**: Complete CPU operation tests
- **Program Tests**: Real program execution tests

### Test Coverage
- ✅ All gate operations
- ✅ All combinational circuits
- ✅ All sequential circuits
- ✅ All 16 instructions
- ✅ Control flow (Jump, Branch)
- ✅ Memory read/write
- ✅ Complex programs (Loop, Fibonacci)

---

## 🎓 Learning Points

What you can learn from this project:

1. **Digital Logic Circuits**
   - Gate-level design
   - Combinational vs Sequential circuits
   - Clock signals and timing

2. **Computer Architecture**
   - Internal CPU operation
   - Fetch-Decode-Execute cycle
   - Control unit and datapath

3. **Instruction Set Architecture (ISA)**
   - Instruction encoding
   - Register vs Memory architecture
   - Control flow handling

4. **Hardware Simulation**
   - Abstraction levels
   - Implementing high-level operations with gates only
   - Hardware constraints

---

## 🚀 Future Plans

### Short-term Goals
- [ ] **Assembler**: Assembly → Machine code converter
- [ ] **More Example Programs**: Sorting, searching, math operations, etc.
- [ ] **Debugger**: Step-by-step execution and state inspection

### Mid-term Goals
- [ ] **Pipelining**: 5-stage pipeline
- [ ] **Cache**: Add L1 cache
- [ ] **Interrupts**: Interrupt handling mechanism

### Long-term Goals
- [ ] **Multi-cycle Processor**: More realistic timing
- [ ] **Out-of-Order Execution**: Performance optimization
- [ ] **MMU**: Virtual memory management

---

## 📝 Design Principles

### 1. Gates Only
All operations are implemented using only basic gates (AND, OR, NOT, etc.).

```cpp
// ❌ Forbidden
int result = a + b;

// ✅ Allowed
bool sum = gate::XOR(a, b);
bool carry = gate::AND(a, b);
```

### 2. Hardware Fidelity
Recreates actual hardware behavior as faithfully as possible.

- Clock signals
- Timing (setup/hold time)
- State storage (Latch, FlipFlop)

### 3. Hierarchical Design
Implement sequentially from lower levels.

```
Gates → Combinational Logic → Sequential Logic → CPU
```

---

## 📄 License

This project is free to use for educational purposes.

---

## 👤 Author

16-bit CPU Project - A Complete CPU Simulator Built from Gate Level
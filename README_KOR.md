# 16비트 CPU 프로젝트

게이트 레벨부터 구현한 완전한 16비트 CPU 시뮬레이터

[English Version](README_EN.md)

---

## 📋 목차
- [프로젝트 개요](#프로젝트-개요)
- [주요 특징](#주요-특징)
- [시스템 아키텍처](#시스템-아키텍처)
- [명령어 세트](#명령어-세트)
- [프로젝트 구조](#프로젝트-구조)
- [빌드 및 실행](#빌드-및-실행)
- [사용 예제](#사용-예제)
- [테스트](#테스트)
- [향후 계획](#향후-계획)

---

## 🎯 프로젝트 개요

이 프로젝트는 **게이트 레벨부터 시작하여** 완전한 16비트 CPU를 C++로 구현한 하드웨어 시뮬레이터입니다.

### 핵심 제약사항
- ❌ **C++ 연산자 사용 금지**: `+`, `-`, `*`, `/`, `&`, `|`, `^`, `if`, `switch` 등
- ✅ **게이트만 사용**: AND, OR, NOT, XOR, NAND, NOR 게이트로만 구현
- ✅ **진정한 하드웨어 시뮬레이션**: 실제 디지털 회로 동작 방식을 따름

### 설계 철학
실제 컴퓨터 하드웨어가 어떻게 동작하는지 게이트 레벨부터 이해하고 구현합니다.

---

## ✨ 주요 특징

### 완전한 하드웨어 스택
```
CPU (완성)
├── Control Unit (제어 장치)
│   ├── Instruction Decoder
│   └── Control Signal Generator
├── Datapath (데이터 경로)
│   ├── ALU (16개 연산)
│   ├── Register File (8개 레지스터)
│   ├── Program Counter
│   └── Memory (64KB)
└── Gates (기본 게이트)
```

### 구현된 컴포넌트

#### 1. 기본 게이트
- AND, OR, NOT, NAND, NOR, XOR

#### 2. 조합 회로 (Combinational Logic)
- **산술 연산**: Adder, Subtractor, Incrementor, Decrementor
- **선택기**: MUX, DMUX (2-way, 4-way, 8-way, 16-way)
- **비교기**: Equal, LessThan, GreaterThan
- **시프터**: Shift Left, Shift Right
- **논리 연산**: 16비트 AND, OR, XOR, NOT
- **디코더**: 명령어 디코더
- **제어 신호 생성기**: 16개 명령어에 대한 제어 신호

#### 3. 순차 회로 (Sequential Logic)
- **래치**: SR Latch, D Latch
- **플립플롭**: D FlipFlop, JK FlipFlop, T FlipFlop
- **레지스터**: 16비트 레지스터, 카운터
- **레지스터 파일**: 8개의 16비트 레지스터
- **메모리**: 64KB (65,536 x 16비트)
- **제어 장치**: Fetch-Decode-Execute 제어
- **프로그램 카운터**: PC 관리 및 점프 처리

#### 4. CPU
- **ALU**: 16개 연산 지원
- **통합 CPU**: 완전한 Fetch-Decode-Execute 사이클

---

## 🏗️ 시스템 아키텍처

### CPU 아키텍처
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

### 명령어 실행 사이클
```
1. Fetch     : Memory[PC] → Instruction Register
2. Decode    : IR → Control Signals
3. Execute   : ALU 연산 또는 메모리 접근
4. Write Back: 결과를 레지스터에 저장
5. Update PC : PC 증가 또는 점프
```

---

## 📜 명령어 세트

### 명령어 포맷

**R-타입** (레지스터 연산):
```
[opcode: 4bit][dest: 3bit][src1: 3bit][src2: 3bit][unused: 3bit]
```

**I-타입** (즉시값):
```
[opcode: 4bit][dest: 3bit][src: 3bit][immediate: 6bit]
```

**J-타입** (점프):
```
[opcode: 4bit][address: 12bit]
```

### 명령어 목록 (16개)

| Opcode | 명령어 | 타입 | 문법 | 설명 |
|--------|--------|------|------|------|
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
| 1111 | HALT | J | `HALT` | CPU 정지 |

### 레지스터
- **8개 범용 레지스터**: R0 ~ R7
- **R0**: 항상 0 (Zero Register)

---

## 📁 프로젝트 구조

```
16bit-CPU/
├── include/
│   ├── types.hpp              # 기본 타입 정의
│   ├── utils.hpp              # 유틸리티 함수
│   ├── Gates.hpp              # 기본 게이트
│   ├── Combinational/         # 조합 회로
│   │   ├── Adder.hpp
│   │   ├── Selector.hpp
│   │   ├── Comparator.hpp
│   │   ├── Shifter.hpp
│   │   ├── Logic.hpp
│   │   ├── Decoder.hpp
│   │   └── ControlSignal.hpp
│   ├── Sequential/            # 순차 회로
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
├── src/                       # 구현 파일
│   ├── Combinational/
│   ├── Sequential/
│   └── CPU/
└── tests/                     # 테스트 파일
    ├── test_CPU.cpp
    ├── test_ALU.cpp
    └── ...
```

---

## 🔧 빌드 및 실행

### 요구사항
- C++17 이상
- CMake 3.10 이상 (선택사항)
- GCC 또는 Clang

### 빌드
```bash
# 직접 컴파일
g++ -std=c++17 -I./include src/**/*.cpp tests/test_CPU.cpp -o test_cpu

# 실행
./test_cpu
```

### 테스트 결과
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

## 💡 사용 예제

### 예제 1: 간단한 덧셈
```cpp
#include "CPU.hpp"
#include "utils.hpp"

int main() {
    // 프로그램 생성: R3 = 10 + 20
    std::vector<Bit16> program;
    program.push_back(makeIType(0b0100, 1, 0, 10)); // ADDI R1, R0, 10
    program.push_back(makeIType(0b0100, 2, 0, 20)); // ADDI R2, R0, 20
    program.push_back(makeRType(0b0011, 3, 1, 2));  // ADD R3, R1, R2
    program.push_back(makeJType(0b1111, 0));        // HALT
    
    // CPU 초기화 및 실행
    CPU::CPU cpu;
    cpu.reset();
    cpu.loadProgram(program);
    
    while (!cpu.isHalted()) {
        cpu.clock();
    }
    
    // 결과 확인
    Bit16 r3 = cpu.readRegister(3);
    std::cout << "R3 = " << utils::BitToInt<16>(r3) << std::endl;  // 30
    
    return 0;
}
```

### 예제 2: 루프 (1부터 5까지 합계)
```cpp
// 프로그램: sum = 1 + 2 + 3 + 4 + 5
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

### 예제 3: 피보나치 수열
```cpp
// 프로그램: F(5) 계산
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

## 🧪 테스트

### 테스트 구성
- **단위 테스트**: 각 컴포넌트별 독립 테스트
- **통합 테스트**: CPU 전체 동작 테스트
- **프로그램 테스트**: 실제 프로그램 실행 테스트

### 테스트 커버리지
- ✅ 모든 게이트 연산
- ✅ 모든 조합 회로
- ✅ 모든 순차 회로
- ✅ 16개 명령어 전체
- ✅ 제어 흐름 (Jump, Branch)
- ✅ 메모리 읽기/쓰기
- ✅ 복잡한 프로그램 (Loop, Fibonacci)

---

## 🎓 학습 포인트

이 프로젝트를 통해 학습할 수 있는 내용:

1. **디지털 논리 회로**
   - 게이트 레벨 설계
   - 조합 회로 vs 순차 회로
   - 클럭 신호와 타이밍

2. **컴퓨터 구조**
   - CPU 내부 동작 원리
   - Fetch-Decode-Execute 사이클
   - 제어 장치와 데이터 경로

3. **명령어 세트 아키텍처 (ISA)**
   - 명령어 인코딩
   - 레지스터 vs 메모리 아키텍처
   - 제어 흐름 처리

4. **하드웨어 시뮬레이션**
   - 추상화 레벨
   - 게이트만으로 고수준 연산 구현
   - 하드웨어 제약사항

---

## 🚀 향후 계획

### 단기 목표
- [ ] **어셈블러 구현**: 어셈블리 → 기계어 변환기
- [ ] **더 많은 예제 프로그램**: 정렬, 탐색, 수학 연산 등
- [ ] **디버거**: 단계별 실행 및 상태 확인

### 중기 목표
- [ ] **파이프라이닝**: 5단계 파이프라인
- [ ] **캐시**: L1 캐시 추가
- [ ] **인터럽트**: 인터럽트 처리 메커니즘

### 장기 목표
- [ ] **멀티 사이클 프로세서**: 더 현실적인 타이밍
- [ ] **Out-of-Order 실행**: 성능 최적화
- [ ] **MMU**: 가상 메모리 관리

---

## 📝 설계 원칙

### 1. 게이트만 사용
모든 연산은 기본 게이트(AND, OR, NOT 등)만으로 구현됩니다.

```cpp
// ❌ 금지
int result = a + b;

// ✅ 허용
bool sum = gate::XOR(a, b);
bool carry = gate::AND(a, b);
```

### 2. 하드웨어 충실성
실제 하드웨어 동작을 최대한 충실하게 재현합니다.

- 클럭 신호
- 타이밍 (setup/hold time)
- 상태 저장 (Latch, FlipFlop)

### 3. 계층적 설계
하위 레벨부터 순차적으로 구현합니다.

```
Gates → Combinational Logic → Sequential Logic → CPU
```


## 📄 라이선스

이 프로젝트는 교육 목적으로 자유롭게 사용할 수 있습니다.

---

## 👤 작성자

16비트 CPU 프로젝트 - 게이트 레벨부터 구현한 완전한 CPU 시뮬레이터

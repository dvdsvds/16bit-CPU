#pragma once

#include "Combinational/ControlSignal.hpp"
#include "Sequential/ControlUnit.hpp"
#include "Sequential/ProgramCounter.hpp"
#include "Sequential/RegisterFile.hpp"
#include "Sequential/Memory.hpp"
#include "CPU/ALU.hpp"

#include <vector>

namespace CPU {
    class CPU {
        private:
            sequential::ControlUnit cu;
            sequential::ProgramCounter pc;
            sequential::RegisterFile rf;
            sequential::Memory mem;

            bool halted;
            bool zf;

        public:
            void clock();
            void reset();
            void loadProgram(const std::vector<Bit16>& program);
            bool isHalted();
            Bit16 readRegister(size_t index) const;
            Bit16 readMemory(const Bit16& addr) const;
            Bit16 getPC() const;       
    };
}
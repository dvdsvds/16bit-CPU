#pragma once

#include "types.hpp"
#include "Sequential/Register.hpp"
#include "Combinational/Comparator.hpp"

namespace sequential {
    class RegisterFile {
        private:
            std::array<Register16, BIT8> registerArray;

        public:
            struct RegisterFileResult {
                Bit16 data1;
                Bit16 data2;
            };

            void write(Bit3 addr, const Bit16& data, bool enable, bool clock);
            RegisterFileResult read(Bit3 addr1, Bit3 addr2) const; 
    };
}
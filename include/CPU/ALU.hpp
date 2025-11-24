#pragma once

#include "types.hpp"

namespace ALU {
    struct ALUResult {
        Bit16 result;
        bool zf = false;
        bool nf = false;
        bool cf = false;
        bool of = false;
    };

    ALUResult ALU(const Bit16& a, const Bit16& b, Bit4 opcode);
}
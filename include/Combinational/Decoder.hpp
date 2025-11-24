#pragma once

#include "types.hpp"
#include "Gates/Basic.hpp"

namespace decoder {
    struct Decoder {
        Bit4 opcode;
        Bit3 dest;
        Bit3 src1;
        Bit3 src2;
        Bit6 immediate;
        Bit12 address;
    };

    Decoder decode(const Bit16& ins);
}
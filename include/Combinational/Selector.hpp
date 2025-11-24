#pragma once

#include <cstdint>
#include "Gates/Basic.hpp"

namespace selector {
    Bit16 MUX(const Bit16& a, const Bit16& b, bool sel);
    Bit16 MUX4(const std::array<Bit16, BIT4>& inputs, Bit2 sel);
    Bit16 MUX8(const std::array<Bit16, BIT8>& inputs, Bit3 sel);
    Bit16 MUX16(const std::array<Bit16, BIT16>& inputs, Bit4 sel);

    struct DMUXResult {
        Bit16 a;
        Bit16 b;
    };

    DMUXResult DMUX(const Bit16& in, bool sel);
}
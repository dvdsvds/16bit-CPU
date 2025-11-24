#pragma once

#include "types.hpp"
#include "Gates/Basic.hpp"

namespace logic {
    Bit16 AND(const Bit16& a, const Bit16& b);
    Bit16 OR(const Bit16& a, const Bit16& b);
    Bit16 XOR(const Bit16& a, const Bit16& b);
    Bit16 NOT(const Bit16& a);
    Bit16 NAND(const Bit16& a, const Bit16& b);
    Bit16 NOR(const Bit16& a, const Bit16& b);
}
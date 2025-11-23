#pragma once
#include "types.hpp"
#include "Combinational/Comparator.hpp"

namespace shifter {
    struct Shift {
        Bit16 result;
        bool carry_out = false;
    };

    Shift SHL(const Bit16& in);
    Shift SHR(const Bit16& in);
}
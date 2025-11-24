#pragma once

#include "Gates/Basic.hpp"
#include "Combinational/Logic.hpp"
#include "types.hpp"
#include "utils.hpp"

namespace adder {
    struct Adder {
        bool sum;
        bool carry;
    };

    Adder HalfAdder(bool a, bool b);
    Adder FullAdder(bool a, bool b, bool carry);

    struct Adder16 {
        Bit16 sum;
        bool carry_out = false;
    };

    Adder16 RippleCarryAdder(const Bit16& a, const Bit16& b);
    Adder16 Incrementor(const Bit16& input);

    struct SubResult {
        Bit16 difference;
        bool borrow = false;
    };

    SubResult Subtractor(const Bit16& a, const Bit16& b);
    Adder16 Decrementor(const Bit16& input);

    Bit16 Negator(const Bit16& input);
}

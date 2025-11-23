#include "Combinational/Adder.hpp"

namespace adder {
    const Bit16 one = utils::IntToBit16(1);

    Adder HalfAdder(bool a, bool b) {
        Adder result;

        result.sum = gate::XOR(a, b);
        result.carry = gate::AND(a, b);

        return result;
    }

    Adder FullAdder(bool a, bool b, bool carry) {
        Adder ha1 = HalfAdder(a, b);
        Adder ha2 = HalfAdder(ha1.sum, carry);

        Adder result;
        result.sum = ha2.sum;
        result.carry = gate::OR(ha1.carry, ha2.carry);

        return result;
    }

    Adder16 RippleCarryAdder(const Bit16& a, const Bit16& b) {
        Adder16 rca = {};
        Adder result;
        for(size_t i = 0; i < BIT16; ++i) {
            result = FullAdder(a[i], b[i], rca.carry_out);
            rca.sum[i] = result.sum;
            rca.carry_out = result.carry;
        }

        return rca;
    }

    Adder16 Incrementor(const Bit16& input) {
        return RippleCarryAdder(input, one);
    }

    SubResult Subtractor(const Bit16& a, const Bit16& b) {
        Bit16 notb = {};
        for(int i = 0; i < BIT16; ++i) {
            notb[i] = gate::NOT(b[i]);
        }

        Bit16 twos_complement = Incrementor(notb).sum;
        Adder16 result = RippleCarryAdder(a, twos_complement);

        SubResult sub;
        sub.difference = result.sum;
        sub.borrow = gate::NOT(result.carry_out);

        return sub;
    }

    Adder16 Decrementor(const Bit16& input) {
        SubResult sub = Subtractor(input, one);
        Adder16 result;

        result.sum = sub.difference;
        result.carry_out = sub.borrow;

        return result;
    }

    Bit16 Negator(const Bit16& input) {
        Bit16 bits = logic::NOT(input);
        return RippleCarryAdder(bits, one).sum;
    }
} 

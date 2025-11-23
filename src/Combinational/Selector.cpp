#include "Combinational/Selector.hpp"

namespace selector {
    Bit16 MUX(const Bit16& a, const Bit16& b, bool sel) {
        Bit16 result = {};
        for(size_t i = 0; i < BIT16; ++i) {
            result[i] = gate::OR(gate::AND(gate::NOT(sel), a[i]), gate::AND(sel, b[i]));
        }
        return result;
    }

    Bit16 MUX4(const std::array<Bit16, BIT4>& inputs, Bit2 sel) {
        return MUX(MUX(inputs[0], inputs[1], sel[0]), MUX(inputs[2], inputs[3], sel[0]), sel[1]);
    }

    Bit16 MUX8(const std::array<Bit16, BIT8>& inputs, Bit3 sel) {
        Bit2 sel_low;
        sel_low[0] = sel[0];
        sel_low[1] = sel[1];

        Bit16 first = MUX4({inputs[0], inputs[1], inputs[2], inputs[3]}, {sel[0], sel[1]});
        Bit16 second = MUX4({inputs[4], inputs[5], inputs[6], inputs[7]}, {sel[0], sel[1]});

        return MUX(first, second, sel[2]);
    }

    Bit16 MUX16(const std::array<Bit16, BIT16>& inputs, Bit4 sel) {
        Bit3 sel_low;
        sel_low[0] = sel[0];
        sel_low[1] = sel[1];
        sel_low[2] = sel[2];

        Bit16 first = MUX8({inputs[0], inputs[1], inputs[2], inputs[3], inputs[4], inputs[5], inputs[6], inputs[7]}, {sel[0], sel[1], sel[2]});
        Bit16 second = MUX8({inputs[8], inputs[9], inputs[10], inputs[11],inputs[12], inputs[13], inputs[14], inputs[15]}, {sel[0], sel[1], sel[2]});

        return MUX(first, second, sel[3]);
    }

    DMUXResult DMUX(const Bit16& in, bool sel) {
        DMUXResult result = {};

        for(size_t i = 0; i < BIT16; ++i) {
            result.a[i] = gate::AND(gate::NOT(sel), in[i]); 
            result.b[i] = gate::AND(sel, in[i]);

        }

        return result;
    }
}
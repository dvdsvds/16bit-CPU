#include "Combinational/Shifter.hpp"

namespace shifter {
    Shift SHL(const Bit16& in) {
        Shift s;
        s.result[0] = 0;
        
        for(size_t i = 1; i < BIT16; ++i) {
            s.result[i] = in[i - 1];
        }

        s.carry_out = in[BIT16 - 1];

        return s;
    }

    Shift SHR(const Bit16& in) {
        Shift s;
        s.result[BIT16 - 1] = 0;

        for(size_t i = 0; i < BIT16 - 1; ++i) {
            s.result[i] = in[i + 1];
        }
        
        s.carry_out = in[0];
        return s;
    }
}
#include "Combinational/Decoder.hpp"

namespace decoder {
    Decoder decode(const Bit16& ins) {
        Decoder d;
        d.opcode[BIT3] = ins[BIT16 - 1];
        d.opcode[BIT3 - 1] = ins[BIT16 - 2];
        d.opcode[BIT3 - 2] = ins[BIT16 - 3];
        d.opcode[BIT3 - 3] = ins[BIT16 - 4];

        d.dest[BIT2] = ins[BIT12 - 1];
        d.dest[BIT2 - 1] = ins[BIT12 - 2];
        d.dest[BIT2 - 2] = ins[BIT12 - 3];

        d.src1[BIT2] = ins[BIT8];
        d.src1[BIT2 - 1] = ins[BIT8 - 1];
        d.src1[BIT2 - 2] = ins[BIT8 - 2];

        d.src2[BIT2] = ins[BIT6 - 1];
        d.src2[BIT2 - 1] = ins[BIT6 - 2];
        d.src2[BIT2 - 2] = ins[BIT6 - 3];

        for(size_t i = 0; i < BIT6; ++i) {
            d.immediate[i] = ins[i];
        }

        for(size_t i = 0; i < BIT12; ++i) {
            d.address[i] = ins[i];
        }
        return d;
    }
}

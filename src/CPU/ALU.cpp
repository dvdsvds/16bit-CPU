#include "CPU/ALU.hpp"
#include "Gates/Basic.hpp"
#include "Combinational/Logic.hpp"
#include "Combinational/Adder.hpp"
#include "Combinational/Selector.hpp"
#include "Combinational/Comparator.hpp"
#include "Combinational/Shifter.hpp"

namespace ALU {
    ALUResult ALU(const Bit16& a, const Bit16& b, Bit4 opcode) {
        std::array<Bit16, BIT16> results;
        results[0] = adder::RippleCarryAdder(a, b).sum;
        results[1] = adder::Incrementor(a).sum;
        results[2] = adder::Subtractor(a, b).difference;
        results[3] = adder::Decrementor(a).sum;
        results[4] = adder::Negator(a);
        results[5] = logic::AND(a, b);
        results[6] = logic::OR(a, b);
        results[7] = logic::XOR(a, b);
        results[8] = logic::NOT(a);
        results[9] = logic::NAND(a, b);
        results[10] = logic::NOR(a, b);
        results[11] = shifter::SHL(a).result;
        results[12] = shifter::SHR(a).result;
        results[13] = a;
        results[14] = b;
        results[15] = Bit16{};

        Bit16 final = selector::MUX16(results, opcode);

        bool z = false;
        for(size_t i = 0; i < BIT16; ++i) {
            z = gate::OR(z, final[i]); 
        }

        bool zf = gate::NOT(z);
        bool nf = final[BIT16 - 1];
        bool cf = false;
        bool of = false;

        return ALUResult(final, zf, nf, cf, of);
    }
}
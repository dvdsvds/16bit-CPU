#include "Combinational/ControlSignal.hpp"

namespace control_signal {
    ControlSignal generator(const Bit4& opcode) {
        // 0000, 0010
        bool is_load = gate::AND(gate::AND(gate::NOT(opcode[3]), gate::NOT(opcode[2])), gate::AND(gate::NOT(opcode[1]), gate::NOT(opcode[0])));
        bool is_store = gate::AND(gate::AND(gate::NOT(opcode[3]), gate::NOT(opcode[2])), gate::AND(gate::NOT(opcode[1]), opcode[0]));
        bool is_move = gate::AND(gate::AND(gate::NOT(opcode[3]), gate::NOT(opcode[2])), gate::AND(opcode[1], gate::NOT(opcode[0])));
        // 0011, 0101
        bool is_add = gate::AND(gate::AND(gate::NOT(opcode[3]), gate::NOT(opcode[2])), gate::AND(opcode[1], opcode[0]));
        bool is_addi = gate::AND(gate::AND(gate::NOT(opcode[3]), opcode[2]), gate::AND(gate::NOT(opcode[1]), gate::NOT(opcode[0])));
        bool is_sub = gate::AND(gate::AND(gate::NOT(opcode[3]), opcode[2]), gate::AND(gate::NOT(opcode[1]), opcode[0]));
        // 0110, 1001
        bool is_and = gate::AND(gate::AND(gate::NOT(opcode[3]), opcode[2]), gate::AND(opcode[1], gate::NOT(opcode[0])));
        bool is_or = gate::AND(gate::AND(gate::NOT(opcode[3]), opcode[2]), gate::AND(opcode[1], opcode[0]));
        bool is_xor = gate::AND(gate::AND(opcode[3], gate::NOT(opcode[2])), gate::AND(gate::NOT(opcode[1]), gate::NOT(opcode[0])));
        bool is_not = gate::AND(gate::AND(opcode[3], gate::NOT(opcode[2])), gate::AND(gate::NOT(opcode[1]), opcode[0]));
        // 1010, 1011
        bool is_shl = gate::AND(gate::AND(opcode[3], gate::NOT(opcode[2])), gate::AND(opcode[1], gate::NOT(opcode[0])));
        bool is_shr = gate::AND(gate::AND(opcode[3], gate::NOT(opcode[2])), gate::AND(opcode[1], opcode[0]));
        bool is_jmp = gate::AND(gate::AND(opcode[3], opcode[2]), gate::AND(gate::NOT(opcode[1]), gate::NOT(opcode[0])));
        bool is_jz = gate::AND(gate::AND(opcode[3], opcode[2]), gate::AND(gate::NOT(opcode[1]), opcode[0]));
        bool is_jnz = gate::AND(gate::AND(opcode[3], opcode[2]), gate::AND(opcode[1], gate::NOT(opcode[0])));
        bool is_halt = gate::AND(gate::AND(opcode[3], opcode[2]), gate::AND(opcode[1], opcode[0]));

        ControlSignal cs;

        cs.reg_write_enable = gate::OR(gate::OR(gate::OR(gate::OR(gate::OR(is_load, is_move), gate::OR(is_add, is_addi)), gate::OR(gate::OR(is_sub, is_and), gate::OR(is_or, is_xor))), gate::OR(is_not, is_shl)), is_shr);
        cs.mem_read = is_load;
        cs.mem_write = is_store;
        cs.is_jump = is_jmp;
        cs.is_jz = is_jz;
        cs.is_jnz = is_jnz;
        cs.is_branch = gate::OR(is_jz, is_jnz);
        cs.use_immediate = gate::OR(gate::OR(is_load, is_store), is_addi);

        cs.alu_opcode[0] = gate::OR(gate::OR(is_and, is_xor), gate::OR(is_shl, is_move));
        cs.alu_opcode[1] = gate::OR(gate::OR(is_sub, is_or), gate::OR(is_shl, is_xor));
        cs.alu_opcode[2] = gate::OR(gate::OR(gate::OR(is_and, is_or), gate::OR(is_xor, is_shr)), is_move);
        cs.alu_opcode[3] = gate::OR(gate::OR(is_not, is_shl), gate::OR(is_shr, is_move));
        return cs;
    }
}
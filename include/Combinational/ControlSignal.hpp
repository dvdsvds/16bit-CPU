#pragma once
#include "types.hpp"
#include "Combinational/Selector.hpp"
#include "Combinational/Decoder.hpp"

namespace control_signal {
    struct ControlSignal {
        Bit4 alu_opcode;
        bool reg_write_enable = false;
        bool mem_read = false;
        bool mem_write = false;
        bool is_jump = false;
        bool is_branch = false;
        bool is_jz = false;
        bool is_jnz = false;
        bool use_immediate = false;
    };

    ControlSignal generator(const Bit4& opcode);
}
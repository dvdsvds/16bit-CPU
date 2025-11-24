#pragma once

#include "Sequential/Register.hpp"
#include "Combinational/Adder.hpp"
#include "Combinational/Selector.hpp"

namespace sequential {
    class ProgramCounter {
        private:
            Register16 reg;

        public:
            void update(const Bit16& new_addr, bool load_signal, bool clock);
            Bit16 read() const;
    };
}
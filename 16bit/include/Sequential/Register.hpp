#pragma once

#include "types.hpp"
#include "Sequential/FlipFlop.hpp"
#include "Combinational/Selector.hpp"
#include "Combinational/Adder.hpp"

namespace sequential {
    class Register16 {
        private:
            std::array<DFlipFlop, BIT16> DArray;

        public:
            void set(const Bit16& data, bool load_signal, bool clock_signal);
            Bit16 read() const;
    };

    class Counter16 {
        private:
            Register16 reg;

        public:
            void set(const Bit16& data, bool load_signal, bool inc_signal, bool reset_signal, bool clock_signal);
            Bit16 read() const;
    };
}
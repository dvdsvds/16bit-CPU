#include "Sequential/ProgramCounter.hpp"

namespace sequential {
    void ProgramCounter::update(const Bit16& new_addr, bool load_signal, bool clock) {
        Bit16 curr = reg.read();
        Bit16 inc = adder::Incrementor(curr).sum;

        Bit16 selected = selector::MUX(inc, new_addr, load_signal);
        reg.set(selected, true, clock);
    }

    Bit16 ProgramCounter::read() const {
        return reg.read();
    }
}
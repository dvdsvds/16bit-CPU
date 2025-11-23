#include "Sequential/Register.hpp"

namespace sequential {
    void Register16::set(const Bit16& data, bool load_signal, bool clock_signal) {
        Bit16 current_value = read();
        Bit16 selected_value = selector::MUX(current_value, data, load_signal);

        for(size_t i = 0; i < BIT16; ++i) {
            DArray[i].set(selected_value[i], clock_signal);
        }
    }

    Bit16 Register16::read() const {
        Bit16 result = {};
        for(size_t i = 0; i < BIT16; ++i) {
            result[i] = DArray[i].getQ();
        }

        return result;
    }

    void Counter16::set(const Bit16& data, bool load_signal, bool inc_signal, bool reset_signal, bool clock_signal) {
        Bit16 current_value = reg.read();
        Bit16 inc_value = adder::Incrementor(current_value).sum;
        Bit16 zero = utils::IntToBit16(0);

        Bit16 s1 = selector::MUX(current_value, inc_value, inc_signal);
        Bit16 s2 = selector::MUX(s1, data, load_signal);
        Bit16 s3 = selector::MUX(s2, zero, reset_signal);

        reg.set(s3, true, clock_signal);
    }

    Bit16 Counter16::read() const {
        return reg.read();
    }
}
#pragma once

#include "Combinational/ControlSignal.hpp"
#include "Combinational/Decoder.hpp"
#include "Sequential/Register.hpp"

namespace sequential {
    class ControlUnit {
        private:
            Register16 IR;
        public:
            void loadInst(const Bit16& inst, bool clock);
            control_signal::ControlSignal getControlSignal() const;
            decoder::Decoder getDecodedInst() const;
    };
}
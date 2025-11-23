#include "Sequential/ControlUnit.hpp"

namespace sequential {
    void ControlUnit::loadInst(const Bit16& inst, bool clock) {
        IR.set(inst, true, clock);
    }

    control_signal::ControlSignal ControlUnit::getControlSignal() const {
        Bit16 inst = IR.read();
        decoder::Decoder decode = decoder::decode(inst);

        return control_signal::generator(decode.opcode);
    }

    decoder::Decoder ControlUnit::getDecodedInst() const {
        Bit16 inst = IR.read();
        return decoder::decode(inst); 
    }
}
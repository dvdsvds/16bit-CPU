#include "Sequential/FlipFlop.hpp"

namespace sequential {
    void DFlipFlop::set(bool D, bool clock) {
        master.set(D, gate::NOT(clock));
        slave.set(master.getQ(), clock);
    }

    bool DFlipFlop::getQ() const {
        return slave.getQ();
    }
}

#pragma once

#include "Sequential/Latch.hpp"

namespace sequential {
    class DFlipFlop {
        private:
            DLatch master;
            DLatch slave;

        public:
            void set(bool D, bool clock);
            bool getQ() const;
    };
}
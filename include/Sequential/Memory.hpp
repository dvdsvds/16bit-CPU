#pragma once

#include "Sequential/Register.hpp"
#include "Combinational/Comparator.hpp"
#include "Combinational/Selector.hpp"
#include "Gates/Basic.hpp"
#include "utils.hpp"
#include <memory>

namespace sequential {
    class Memory {
        private:
            std::unique_ptr<std::array<Register16, CELL16>> memory;

        public:
            Memory();
            void write(const Bit16& addr, const Bit16& data, bool enable, bool clock);
            Bit16 read(const Bit16& addr) const;
    };
}
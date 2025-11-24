#include "Sequential/Memory.hpp"

namespace sequential {
    Memory::Memory() : memory(std::make_unique<std::array<Register16, CELL16>>()) {}

    void Memory::write(const Bit16& addr, const Bit16& data, bool enable, bool clock) {
        for(size_t i = 0; i < CELL16; ++i) {
            Bit16 cur_addr = utils::IntToBit16(i);

            bool match = comparator::Equal16(cur_addr, addr);
            bool result = gate::AND(match, enable);

            (*memory)[i].set(data, result, clock);
        }
    }

    Bit16 Memory::read(const Bit16& addr) const {
        Bit16 result = {};
        for(size_t i = 0; i < CELL16; ++i) {
            Bit16 idx = utils::IntToBit16(i);
            bool match = comparator::Equal16(idx, addr);
            result = selector::MUX(result, (*memory)[i].read(), match);
        }

        return result;
    }
} 
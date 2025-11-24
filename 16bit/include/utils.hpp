#pragma once
#include "types.hpp"
#include "Gates/Basic.hpp"

namespace utils {
    bool getBit(const Bit16& bits, int pos);
    Bit16 setBit(const Bit16& bits, int pos, bool value);

    template<size_t N>
    int BitToInt(const std::array<bool, N>& bits) {
        int result = 0;
        for(size_t i = 0; i < N; ++i) {
            if(bits[i]) {
                result += (1 << i);
            }
        }
        return result;
    }

    Bit16 IntToBit16(int value);
    Bit3 IntToBit3(int value);
}
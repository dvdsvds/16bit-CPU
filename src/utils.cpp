#include "utils.hpp"

namespace utils {
    bool getBit(const Bit16& bits, int pos) {
        return bits[pos];
    }

    Bit16 setBit(const Bit16& bits, int pos, bool value) {
        Bit16 result = bits;
        result[pos] = value;

        return result;
    }

    Bit16 IntToBit16(int value) {
        Bit16 result = {};
        for(size_t i = 0; i < BIT16; ++i) {
            result[i] = (value >> i) & 1;
        }
        return result;
    }

    Bit3 IntToBit3(int value) {
        Bit3 result = {};
        for(size_t i = 0; i < BIT3; ++i) {
            result[i] = (value >> i) & 1;
        }
        return result;
    }
}
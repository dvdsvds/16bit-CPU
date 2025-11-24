#include "Combinational/Comparator.hpp"

using namespace gate;

namespace comparator {
    bool NotEqual(bool a, bool b) {
        return XOR(a, b);
    }

    bool Equal(bool a, bool b) {
        return XNOR(a, b);
    }

    bool Equal16(const Bit16& a, const Bit16& b) {
        bool result = true;
        for(size_t i = 0; i < BIT16; ++i) {
            bool s = gate::XNOR(a[i], b[i]);
            result = gate::AND(result, s);
        }

        return result;
    }

    bool LessThan(bool a, bool b) {
        return AND(NOT(a), b);
    }

    bool GreaterThan(bool a, bool b) {
        return AND(a, NOT(b));
    }
}
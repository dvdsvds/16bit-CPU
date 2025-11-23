#include "Combinational/Logic.hpp"

namespace logic {
    Bit16 AND(const Bit16& a, const Bit16& b) {
        Bit16 result = {};
        
        for(int i = 0; i < BIT16; ++i) {
            result[i] = gate::AND(a[i], b[i]);
        }

        return result;
    }

    Bit16 OR(const Bit16& a, const Bit16& b) {
        Bit16 result = {};
        
        for(int i = 0; i < BIT16; ++i) {
            result[i] = gate::OR(a[i], b[i]);
        }

        return result;
    }

    Bit16 XOR(const Bit16& a, const Bit16& b) {
        Bit16 result = {};
        
        for(int i = 0; i < BIT16; ++i) {
            result[i] = gate::XOR(a[i], b[i]);
        }

        return result;
    }

    Bit16 NOT(const Bit16& a) {
        Bit16 result = {};
        
        for(int i = 0; i < BIT16; ++i) {
            result[i] = gate::NOT(a[i]);
        }

        return result;
    }

    Bit16 NAND(const Bit16& a, const Bit16& b) {
        Bit16 result = {};
        
        for(int i = 0; i < BIT16; ++i) {
            result[i] = gate::NAND(a[i], b[i]);
        }

        return result;
    }

    Bit16 NOR(const Bit16& a, const Bit16& b) {
        Bit16 result = {};
        
        for(int i = 0; i < BIT16; ++i) {
            result[i] = gate::NOR(a[i], b[i]);
        }

        return result;
    }
}
#include "Gates/Basic.hpp"

namespace gate {
    bool AND(bool a, bool b) {
        if(a) {
            if(b) return true;
            else return false;
        } else {
            return false;
        }
    }

    bool OR(bool a, bool b) {
        if(a) {
            if(b) return true;
            else return true;
        } else {
            if(b) return true;
            else return 0;
        }
    }

    bool XOR(bool a, bool b) {
        if(a) {
            if(b) return 0;
            else return true;
        } else {
            if(b) return true;
            else return 0;
        }
    }

    bool NOT(bool a) {
        if(a) {
            return false;
        }
        return true;
    }

    bool NAND(bool a, bool b) {
        return NOT(AND(a, b));
    }

    bool XNOR(bool a, bool b) {
        return NOT(XOR(a, b));
    }

    bool NOR(bool a, bool b) {
        return NOT(OR(a, b));
    }
}
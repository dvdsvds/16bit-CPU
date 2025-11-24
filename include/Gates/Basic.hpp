#pragma once

#include <cstdint>
#include "types.hpp"

namespace gate {
    bool AND(bool a, bool b);
    bool OR(bool a, bool b);
    bool XOR(bool a, bool b);
    bool XNOR(bool a, bool b);
    bool NOT(bool a);
    bool NAND(bool a, bool b);
    bool NOR(bool a, bool b);
}
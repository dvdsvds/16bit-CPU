#include "Gates/Basic.hpp"
#include "types.hpp"

namespace comparator {
    bool NotEqual(bool a, bool b);
    bool Equal(bool a, bool b);
    bool Equal16(const Bit16& a, const Bit16& b);
    bool LessThan(bool a, bool b);
    bool GreaterThan(bool a, bool b);
}
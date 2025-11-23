#pragma once

#include <array>
#include <cstddef>

constexpr size_t BIT16 = 16;
constexpr size_t BIT12 = 12;
constexpr size_t BIT8 = 8;
constexpr size_t BIT6 = 6;
constexpr size_t BIT4 = 4;
constexpr size_t BIT3 = 3;
constexpr size_t BIT2 = 2;
constexpr size_t CELL16 = 65536;

using Bit16 = std::array<bool, BIT16>;
using Bit12 = std::array<bool, BIT12>;
using Bit8 = std::array<bool, BIT8>;
using Bit6 = std::array<bool, BIT6>;
using Bit4 = std::array<bool, BIT4>;
using Bit3 = std::array<bool, BIT3>;
using Bit2 = std::array<bool, BIT2>;

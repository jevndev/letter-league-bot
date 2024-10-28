#pragma once

#include <array>
#include <cstddef>

namespace Tiles {
enum class MultiplierType { LETTER, WORD };

struct Multiplier {
  unsigned short amount;
  MultiplierType type;
};

constexpr Multiplier operator""_L(const unsigned long long amount) {
  return Multiplier{static_cast<unsigned short>(amount),
                    MultiplierType::LETTER};
}

constexpr Multiplier operator""_W(const unsigned long long amount) {
  return Multiplier{static_cast<unsigned short>(amount), MultiplierType::WORD};
}

static constexpr Multiplier NIL =
    Multiplier{.amount = 1, .type = MultiplierType::LETTER};
}; // namespace Tiles

namespace Blocks {
using namespace Tiles;

// clang-format off
static constexpr std::array BLOCK_1 = {
    NIL, 2_L, NIL, NIL, NIL, 2_L, NIL,
    2_W, NIL, NIL, NIL, NIL, NIL, 2_W,
    NIL, NIL, 3_L, NIL, 3_L, NIL, NIL,
    NIL, 2_W, NIL, NIL, NIL, 2_W, NIL,
    NIL, NIL, 3_L, NIL, 3_L, NIL, NIL,
    2_W, NIL, NIL, NIL, NIL, NIL, 2_W,
    NIL, 2_L, NIL, NIL, NIL, 2_L, NIL
};

static constexpr std::array BLOCK_2 = {
    NIL, NIL, 2_L, NIL, 2_L, NIL, NIL,
    2_W, NIL, NIL, NIL, NIL, NIL, 2_W,
    NIL, NIL, NIL, 2_L, NIL, NIL, NIL,
    NIL, NIL, NIL, 2_W, NIL, NIL, NIL,
    NIL, NIL, NIL, 2_L, NIL, NIL, NIL,
    2_W, NIL, NIL, NIL, NIL, NIL, 2_W,
    NIL, NIL, 2_L, NIL, 2_L, NIL, NIL,
};

static constexpr std::array BLOCK_3 = {
    NIL, NIL, 2_L, NIL, 2_L, NIL, NIL,
    NIL, 2_W, NIL, NIL, NIL, 2_W, NIL,
    2_L, NIL, 3_L, NIL, 3_L, NIL, 2_L,
    NIL, NIL, NIL, 3_W, NIL, NIL, NIL,
    2_L, NIL, 3_L, NIL, 3_L, NIL, 2_L,
    NIL, 2_W, NIL, NIL, NIL, 2_W, NIL,
    NIL, NIL, 2_L, NIL, 2_L, NIL, NIL,
};

static constexpr std::array BLOCK_4 = {
    NIL, 2_L, NIL, NIL, NIL, 2_L, NIL,
    2_L, NIL, NIL, NIL, NIL, NIL, 2_L,
    NIL, NIL, NIL, NIL, NIL, NIL, NIL,
    NIL, NIL, 2_L, 2_W, 2_L, NIL, NIL,
    NIL, NIL, NIL, NIL, NIL, NIL, NIL,
    2_L, NIL, NIL, NIL, NIL, NIL, 2_L,
    NIL, 2_L, NIL, NIL, NIL, 2_L, NIL
};
// clang-format on

} // namespace Blocks

Tiles::Multiplier getMultiplerOfTileLocation(const int i, const int j) {}

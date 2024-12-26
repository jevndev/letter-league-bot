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

static constexpr std::array BLOCK = {
    NIL, NIL, 2_W, NIL, NIL, NIL, 2_W, NIL, NIL, NIL, 2_W, NIL,
    NIL, 3_L, NIL, NIL, NIL, NIL, 2_L, NIL, NIL, NIL, NIL, 3_L,
    NIL, NIL, NIL, 2_W, NIL, NIL, NIL, NIL, NIL, 2_W, NIL, NIL,
    2_L, NIL, 2_L, NIL, NIL, 2_L, NIL, 2_L, NIL, NIL, 2_L, NIL,
    NIL, NIL, NIL, NIL, 2_W, NIL, NIL, NIL, 2_W, NIL, NIL, NIL,
    2_W, NIL, NIL, 2_L, NIL, 3_L, NIL, 3_L, NIL, 2_L, NIL, NIL,
    NIL, NIL, NIL, NIL, NIL, NIL, 3_W, NIL, NIL, NIL, NIL, 2_L,
    2_L, NIL, NIL, 2_L, NIL, 3_L, NIL, 3_L, NIL, 2_L, NIL, NIL,
    NIL, NIL, NIL, NIL, 2_W, NIL, NIL, NIL, 2_W, NIL, NIL, NIL,
    NIL, NIL, 2_L, NIL, NIL, 2_L, NIL, 2_L, NIL, NIL, 2_L, NIL,
    NIL, NIL, NIL, 2_W, NIL, NIL, NIL, NIL, NIL, 2_W, NIL, NIL,
    NIL, 3_L, NIL, NIL, NIL, NIL, 2_L, NIL, NIL, NIL, NIL, 3_L,
};

static constexpr auto BLOCK_WIDTH = 12;
static_assert(BLOCK_WIDTH * BLOCK_WIDTH == std::size(BLOCK));

// clang-format on

} // namespace Blocks

Tiles::Multiplier getMultiplerOfTileLocation(const int i, const int j) {}

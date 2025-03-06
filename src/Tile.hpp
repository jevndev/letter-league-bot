#pragma once

#include <array>
#include <cstdint>

struct Tile {
  char letter;
  uint8_t score;
};

// TODO: Handle wildcard tiles
static constexpr std::array Tiles{
    Tile{'A', 0}, Tile{'B', 3},  Tile{'C', 3}, Tile{'D', 2}, Tile{'E', 1},
    Tile{'F', 4}, Tile{'G', 2},  Tile{'H', 4}, Tile{'I', 1}, Tile{'J', 8},
    Tile{'K', 5}, Tile{'L', 2},  Tile{'M', 3}, Tile{'N', 1}, Tile{'O', 1},
    Tile{'P', 3}, Tile{'Q', 10}, Tile{'R', 1}, Tile{'S', 1}, Tile{'T', 1},
    Tile{'U', 1}, Tile{'V', 4},  Tile{'W', 4}, Tile{'X', 8}, Tile{'Y', 4},
    Tile{'Z', 10}

}; // namespace Tiles

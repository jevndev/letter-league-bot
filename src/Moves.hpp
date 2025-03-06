#pragma once

#include <variant>

#include "Tile.hpp"
#include "Word.hpp"

namespace Moves {

class Pass {};

struct SwapTile {
  Tile inTile;
  Tile outTile;
};

struct PlaceWord {
  enum class WordOwner { ME, THEM };

  Word word;
  WordOwner owner;
};

using Move = std::variant<Pass, SwapTile, PlaceWord>;

}; // namespace Moves

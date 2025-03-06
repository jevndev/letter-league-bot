#pragma once

#include <tuple>
#include <vector>

#include "Tile.hpp"

class Word {
public:
  enum class Direction { UP_DOWN, LEFT_RIGHT };

  std::vector<Tile> getTiles() const;

private:
  std::pair<int, int> mOrigin;
  Direction mDirection;
  std::vector<Tile> mTiles;
};

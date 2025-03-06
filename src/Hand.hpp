#pragma once

#include <vector>

#include "Tile.hpp"
#include "Word.hpp"

class Hand {
public:
  void removeWord(const Word &word);

private:
  std::vector<Tile> mTiles;
};

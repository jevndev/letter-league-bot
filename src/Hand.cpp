#include "Hand.hpp"

#include <algorithm>

void Hand::removeWord(const Word &word) {
  for (const auto &tile : word.getTiles()) {
    const auto it = std::ranges::find(mTiles, tile);
    if (it != mTiles.end()) {
      mTiles.erase(it);
    }
  }
}

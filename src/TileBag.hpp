#pragma once

#include <array>
#include <unordered_map>

#include "Tile.hpp"

class TileBag {
public:
  TileBag(const std::unordered_map<Tile, std::size_t> &mInitialTileCounts);
  void takeTile(const Tile &tileOut);
  void doTileSwap(const Tile &tileIn, const Tile &tileOut);

private:
  std::size_t hash(const Tile &tile) const;
  std::array<std::size_t, Tiles.size()> mTileCounts;
};

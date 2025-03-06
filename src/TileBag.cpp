#include "TileBag.hpp"

#include <cassert>

TileBag::TileBag(
    const std::unordered_map<Tile, std::size_t> &mInitialTileCounts) {
  for (const auto &[tile, count] : mInitialTileCounts) {
    mTileCounts[TileBag::hash(tile)] = count;
  }
}

void TileBag::takeTile(const Tile &tileOut) {
  const auto outHash = hash(tileOut);
  assert(mTileCounts[outHash] > 0);

  mTileCounts[outHash]--;
};

void TileBag::doTileSwap(const Tile &tileIn, const Tile &tileOut) {
  takeTile(tileOut);
  const auto inHash = hash(tileIn);
  mTileCounts[inHash]++;
}

std::size_t TileBag::hash(const Tile &tile) const {
  const auto hash = static_cast<std::size_t>(tile.letter);
  assert(hash < mTileCounts.size());
  return hash;
}

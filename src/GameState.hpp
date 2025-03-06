#pragma once

#include <vector>

#include "Hand.hpp"
#include "Moves.hpp"
#include "TileBag.hpp"
#include "Word.hpp"

class GameState {
public:
  void applyMove(const Moves::Move &move);

private:
  void apply(const Moves::Pass &move);
  void apply(const Moves::SwapTile &move);
  void apply(const Moves::PlaceWord &move);

  TileBag mTileBag;

  Hand mBotHand;
  Hand mOtherHand; // TODO: Support more than one opponent

  std::vector<Word> mWordsOnBoard;
};

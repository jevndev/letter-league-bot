#include "GameState.hpp"

void GameState::applyMove(const Moves::Move &move) {
  std::visit([this](const auto &move) { apply(move); }, move);
}

void GameState::apply(const Moves::Pass &move) {
  // do nothing :)
}

void GameState::apply(const Moves::SwapTile &move) {
  mTileBag.doTileSwap(move.inTile, move.outTile);
}

void GameState::apply(const Moves::PlaceWord &move) {
  mWordsOnBoard.push_back(move.word);
  switch (move.owner) {
  case Moves::PlaceWord::WordOwner::ME: {
    mBotHand.removeWord(move.word);
  } break;
  case Moves::PlaceWord::WordOwner::THEM: {
    mOtherHand.removeWord(move.word);
  } break;
  default:
    break;
  };
}

#pragma once

#include <vector>

#include "MoveGeneration.hpp"
#include "MoveScoring.hpp"
#include "Moves.hpp"

namespace Bot {
class Bot {
public:
  Bot(const MoveScoring::MoveScorer &moveScorer,
      const MoveGeneration::MoveGenerator &moveGenerator)
      : scorer{moveScorer}, generator{moveGenerator} {};
  void initializeGameState();
  void updateBoardState();
  bool okay() const;
  std::vector<Moves::Move> generateMoves();

private:
  MoveScoring::MoveScorer scorer;
  MoveGeneration::MoveGenerator generator;
};
} // namespace Bot

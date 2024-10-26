#pragma once

#include <vector>

#include "Moves.hpp"

namespace Bot {
class Bot {
public:
  void initializeGameState();
  void updateBoardState();
  bool okay() const;
  std::vector<Moves::Move> generateMoves();

private:
};
} // namespace Bot

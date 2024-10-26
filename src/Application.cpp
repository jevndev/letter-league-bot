#include "Application.hpp"

namespace Application {

std::error_condition App::run() {
  bot.initializeGameState();
  while (bot.okay()) {
    const auto moves = bot.generateMoves();

    bot.updateBoardState();
  }

  return std::error_condition{};
}

} // namespace Application

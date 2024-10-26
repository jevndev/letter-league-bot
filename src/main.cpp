#include "Application.hpp"

#include "Bot.hpp"
#include "MoveGeneration.hpp"
#include "MoveScoring.hpp"

int main(int argc, char const *argv[]) {
  MoveGeneration::MoveGenerator generator{};
  MoveScoring::MoveScorer scorer{};
  Bot::Bot bot{scorer, generator};
  Application::App app{bot};
  const auto result = app.run();
  return result.value();
}

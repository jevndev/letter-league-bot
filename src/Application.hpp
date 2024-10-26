#pragma once

#include "Bot.hpp"

#include <system_error>

namespace Application {
class App {
public:
  App(const Bot::Bot &bot) : bot{bot} {};
  std::error_condition run();

private:
  Bot::Bot bot;
};
} // namespace Application

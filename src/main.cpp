#include "Application.hpp"

#include "Bot.hpp"
int main(int argc, char const *argv[]) {
  Bot::Bot bot{};
  Application::App app{bot};
  const auto result = app.run();
  return result.value();
}

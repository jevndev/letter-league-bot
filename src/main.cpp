#include "Application.hpp"

int main(int argc, char const *argv[]) {
  Application::App app{};
  const auto result = app.run();
  return result.value();
}

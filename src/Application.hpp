#pragma once

#include <system_error>

namespace Application {
class App {
public:
  std::error_condition run();

private:
};
} // namespace Application

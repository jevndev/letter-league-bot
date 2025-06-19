#include <cstddef>
#include <filesystem>
#include <fstream>
#include <printf.h>
#include <string>
#include <string_view>
#include <vector>

enum class Direction { RIGHT, DOWN };

struct Location {
  uint8_t m_x;
  uint8_t m_y;
};

std::vector<std::string> getWordList(const std::filesystem::path &path) {
  std::vector<std::string> words;
  std::ifstream file(path);
  if (!file.is_open()) {
    throw std::runtime_error("Failed to open file");
  }

  std::string buffer;
  while (file >> buffer) {
    words.emplace_back(buffer);
  }

  return words;
}

int main() {
  const auto words =
      getWordList(std::filesystem::path("./english-words/words_alpha.txt"));

  std::printf("Loaded %zu words\n", words.size());
}

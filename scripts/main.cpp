#include <array>
#include <assert.h>
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <printf.h>
#include <random>
#include <ranges>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

enum class Direction : uint8_t { RIGHT, DOWN };

// Coordinate system is
// +---------> x
// |
// |
// |
// v
// y
struct RelativeLocation {
  int8_t m_x;
  int8_t m_y;

  [[nodiscard]] RelativeLocation operator-(const RelativeLocation &rhs) const {
    // Just pretending I never roll over. The type I use here only needs to be
    // able to fit the length of a word in the first N-1 bits. Since it's an
    // int8 that gives me
    // 127 characters of wiggle room
    return RelativeLocation{static_cast<int8_t>(m_x - rhs.m_x),
                            static_cast<int8_t>(m_y - rhs.m_y)};
  }

  friend std::ostream &operator<<(std::ostream &os,
                                  const RelativeLocation &location) {
    os << "[" << static_cast<int>(location.m_x) << ","
       << static_cast<int>(location.m_y) << "]";
    return os;
  };
};

struct WordWithDirection {
  std::string_view m_word;
  Direction m_direction;

  // Since we know the string views should be pointing to the same underlying
  // data if they represent the same word, this can be optimized to just do the
  // pointer comparison.
  [[nodiscard]] bool operator==(const WordWithDirection &rhs) const = default;

  friend std::ostream &operator<<(std::ostream &os,
                                  const WordWithDirection &word) {
    os << "(" << word.m_word << ","
       << (word.m_direction == Direction::DOWN ? "Down" : "Right") << ")";

    return os;
  };
};

namespace std {
template <> struct hash<WordWithDirection> {
  static constexpr auto s_svHash = std::hash<std::string_view>();
  [[nodiscard]] std::size_t operator()(const WordWithDirection &word) const {
    return s_svHash(word.m_word) + static_cast<uint8_t>(word.m_direction);
  }
};
} // namespace std

struct WordPlacement {
  WordWithDirection m_word;
  RelativeLocation m_origin;

  friend std::ostream &operator<<(std::ostream &os,
                                  const WordPlacement &placement) {
    os << "{" << placement.m_word << "," << placement.m_origin << "}";
    return os;
  };
};

using CharacterToLetterMap =
    std::unordered_map<char, std::vector<RelativeLocation>>;

// This can be precomputed for every word if it becomes a bottleneck. Also can
// be represented as an array with the letter as the hash. Might be faster.
auto getLocationsOfLetters(const WordWithDirection &word) noexcept {
  CharacterToLetterMap map;
  uint8_t i = 0;
  for (const auto c : word.m_word) {
    if (word.m_direction == Direction::DOWN) {
      map[c].emplace_back(0, i);
    } else {
      map[c].emplace_back(i, 0);
    }
    i++;
  }

  return map;
}

using WordToLetterLocationMap =
    std::unordered_map<WordWithDirection, CharacterToLetterMap>;

std::vector<WordPlacement>
getPlacementsForWord(const WordWithDirection &word,
                     const WordToLetterLocationMap &allWordLetterLocations) {
  std::vector<WordPlacement> output;
  const auto myWordLetterLocations = allWordLetterLocations.at(word);

  for (const auto &[potentialWord, potentialWordLetterLocations] :
       allWordLetterLocations) {

    for (const auto &[letter, locations] : myWordLetterLocations) {
      const auto pLocationsOfThisLetterEntry =
          potentialWordLetterLocations.find(letter);

      if (pLocationsOfThisLetterEntry != potentialWordLetterLocations.end()) {
        // We have intersections. Need to generate placements for all of them

        for (const auto &letterLocationInPotentialWord :
             pLocationsOfThisLetterEntry->second) {
          for (const auto &letterLocationInThisWord : locations) {
            if (potentialWord.m_direction != word.m_direction) {
              // Easy case, they only overlap at the intersection

              output.emplace_back(potentialWord,
                                  letterLocationInThisWord -
                                      letterLocationInPotentialWord);

            } else {
              // TODO:
              // Hard case. Need to verify that the overlap not only doesn't
              // place different letters in the same place, but also need to be
              // sure that the placement results in a new valid word

              // Right now I'm going to do the incorrect answer of ignoring this
              // condition

              output.emplace_back(potentialWord,
                                  letterLocationInThisWord -
                                      letterLocationInPotentialWord);
            }
          }
        }
      }
    }
  }

  return output;
};

auto generateLetterLocationMaps(const std::vector<std::string> &words) {
  WordToLetterLocationMap letterLocationMaps;
  for (const auto &word : words) {
    for (const auto &direction : {Direction::DOWN, Direction::RIGHT}) {
      const auto wordWithDirection = WordWithDirection{word, direction};
      assert(!letterLocationMaps.contains(wordWithDirection));
      letterLocationMaps[wordWithDirection] =
          getLocationsOfLetters(wordWithDirection);
    }
  }
  return letterLocationMaps;
}

auto getValidPlacementsForWords(const std::vector<std::string> &words) {

  const auto letterLocationMaps = generateLetterLocationMaps(words);

  std::unordered_map<WordWithDirection, std::vector<WordPlacement>> resultMap{};
  for (const auto &[word, map] : letterLocationMaps) {
    resultMap[word] = getPlacementsForWord(word, letterLocationMaps);
  }

  return resultMap;
}

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

void writeWordMap(
    const std::filesystem::path &path,
    const std::unordered_map<WordWithDirection, std::vector<WordPlacement>>
        &placementMap) {

  std::ofstream file{path};

  if (!file.is_open()) {
    throw std::runtime_error("Failed to open file");
  }

  for (const auto &[word, validPlacements] : placementMap) {
    file << word << ":";

    assert(placementMap.size() > 0);

    for (const auto &placement : validPlacements) {
      file << placement << ",";
    }

    file << "\n";
  }
}

std::vector<std::string> getNRandomWords(const std::vector<std::string> &words,
                                         const std::size_t n) {
  if (n > words.size()) {
    throw std::invalid_argument(
        "Requested more words than available in the list");
  }

  std::vector<std::string> randomWords;
  std::unordered_set<std::size_t> selectedIndices;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<std::size_t> dist(0, words.size() - 1);

  while (randomWords.size() < n) {
    auto index = dist(gen);
    if (selectedIndices.insert(index).second) {
      randomWords.emplace_back(words[index]);
    }
  }

  return randomWords;
}

int main() {
  const auto allWords =
      getWordList(std::filesystem::path("./english-words/words_alpha.txt"));

  const auto words = getNRandomWords(allWords, 10);

  std::printf("Loaded %zu words\n", words.size());

  const auto wordMap = getValidPlacementsForWords(words);

  std::printf("Finished Building Wordmap\n");

  writeWordMap(std::filesystem::path("out.txt"), wordMap);

  return 0;
}

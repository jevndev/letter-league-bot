#include <array>
#include <gtest/gtest.h>

#include "Board.hpp"

// Dummy test case
TEST(board, INDICIES_TILE_HORIZONTALLY_AFTER_BOARD_WIDTH) {
  const auto &firstBlock = Blocks::BLOCK;
  std::array<Tiles::Multiplier, std::size(firstBlock)> secondBlock;

  for (std::size_t i = 0; i < Blocks::BLOCK_WIDTH; i++) {
    for (std::size_t j = 0; j < Blocks::BLOCK_WIDTH; j++) {
      secondBlock[i + j * Blocks::BLOCK_WIDTH] =
          getMultiplerOfTileLocation(i + Blocks::BLOCK_WIDTH, j);
    }
  }

  ASSERT_EQ(firstBlock, secondBlock);
}

TEST(board, INDICIES_TILE_VERTICALLY_AFTER_BOARD_WIDTH) {
  const auto &firstBlock = Blocks::BLOCK;
  std::array<Tiles::Multiplier, std::size(firstBlock)> secondBlock;

  for (std::size_t i = 0; i < Blocks::BLOCK_WIDTH; i++) {
    for (std::size_t j = 0; j < Blocks::BLOCK_WIDTH; j++) {
      secondBlock[i + j * Blocks::BLOCK_WIDTH] =
          getMultiplerOfTileLocation(i + Blocks::BLOCK_WIDTH, j);
    }
  }

  ASSERT_EQ(firstBlock, secondBlock);
}

TEST(board, INDICIES_TILE_HORIZONTALLY_IN_NEGATIVE_DIRECTION) {
  const auto &firstBlock = Blocks::BLOCK;
  std::array<Tiles::Multiplier, std::size(firstBlock)> secondBlock;

  for (std::size_t i = 0; i < Blocks::BLOCK_WIDTH; i++) {
    for (std::size_t j = 0; j < Blocks::BLOCK_WIDTH; j++) {
      secondBlock[i + j * Blocks::BLOCK_WIDTH] =
          getMultiplerOfTileLocation(i, j - Blocks::BLOCK_WIDTH);
    }
  }

  ASSERT_EQ(firstBlock, secondBlock);
}

TEST(board, INDICIES_TILE_VERTICALLY_IN_NEGATIVE_DIRECTION) {
  const auto &firstBlock = Blocks::BLOCK;
  std::array<Tiles::Multiplier, std::size(firstBlock)> secondBlock;

  for (std::size_t i = 0; i < Blocks::BLOCK_WIDTH; i++) {
    for (std::size_t j = 0; j < Blocks::BLOCK_WIDTH; j++) {
      secondBlock[i + j * Blocks::BLOCK_WIDTH] =
          getMultiplerOfTileLocation(i - Blocks::BLOCK_WIDTH, j);
    }
  }

  ASSERT_EQ(firstBlock, secondBlock);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

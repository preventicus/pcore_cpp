#include <vector>
#include "PcoreAbsoluteBlock.h"
#include "gtest/gtest.h"
TEST(runUnitTest, compareEmptyAndFullBlocks) {
  std::vector<int32_t> values1 = {};
  std::vector<int32_t> values2 = {1, 2, 3};

  PcoreAbsoluteBlock block1 = PcoreAbsoluteBlock(values1);
  PcoreAbsoluteBlock block2 = PcoreAbsoluteBlock(values2);

  EXPECT_FALSE(block1.isEqual(block2));
}

TEST(runUnitTest, compareshortAndFullBlocks) {
  std::vector<int32_t> values1 = {1};
  std::vector<int32_t> values2 = {1, 2, 3};

  PcoreAbsoluteBlock block1 = PcoreAbsoluteBlock(values1);
  PcoreAbsoluteBlock block2 = PcoreAbsoluteBlock(values2);

  EXPECT_FALSE(block1.isEqual(block2));
}

TEST(runUnitTest, compareMediumAndFullBlocks) {
  std::vector<int32_t> values1 = {1, 2};
  std::vector<int32_t> values2 = {1, 2, 3};

  PcoreAbsoluteBlock block1 = PcoreAbsoluteBlock(values1);
  PcoreAbsoluteBlock block2 = PcoreAbsoluteBlock(values2);

  EXPECT_FALSE(block1.isEqual(block2));
}

TEST(runUnitTest, compareSameContentBlocks) {
  std::vector<int32_t> values1 = {1, 2, 3};
  std::vector<int32_t> values2 = {1, 2, 3};

  PcoreAbsoluteBlock block1 = PcoreAbsoluteBlock(values1);
  PcoreAbsoluteBlock block2 = PcoreAbsoluteBlock(values2);

  EXPECT_TRUE(block1.isEqual(block2));
}

TEST(runUnitTest, compareFullandEmptyBlocks) {
  std::vector<int32_t> values1 = {1, 2, 3};
  std::vector<int32_t> values2 = {};

  PcoreAbsoluteBlock block1 = PcoreAbsoluteBlock(values1);
  PcoreAbsoluteBlock block2 = PcoreAbsoluteBlock(values2);

  EXPECT_FALSE(block1.isEqual(block2));
}

TEST(runUnitTest, compareFullandShortBlocks) {
  std::vector<int32_t> values1 = {1, 2, 3};
  std::vector<int32_t> values2 = {1};

  PcoreAbsoluteBlock block1 = PcoreAbsoluteBlock(values1);
  PcoreAbsoluteBlock block2 = PcoreAbsoluteBlock(values2);

  EXPECT_FALSE(block1.isEqual(block2));
}

TEST(runUnitTest, compareLongWithMediumBlocks) {
  std::vector<int32_t> values1 = {1, 2, 3};
  std::vector<int32_t> values2 = {1, 2};

  PcoreAbsoluteBlock block1 = PcoreAbsoluteBlock(values1);
  PcoreAbsoluteBlock block2 = PcoreAbsoluteBlock(values2);

  EXPECT_FALSE(block1.isEqual(block2));
}
TEST(runUnitTest, compareEmptyWithEmptyBlocks) {
  std::vector<int32_t> values1 = {};
  std::vector<int32_t> values2 = {};

  PcoreAbsoluteBlock block1 = PcoreAbsoluteBlock(values1);
  PcoreAbsoluteBlock block2 = PcoreAbsoluteBlock(values2);

  EXPECT_TRUE(block1.isEqual(block2));
}
TEST(runUnitTest, compareZeroWithZeroBlocks) {
  std::vector<int32_t> values1 = {0};
  std::vector<int32_t> values2 = {0};

  PcoreAbsoluteBlock block1 = PcoreAbsoluteBlock(values1);
  PcoreAbsoluteBlock block2 = PcoreAbsoluteBlock(values2);

  EXPECT_TRUE(block1.isEqual(block2));
}
TEST(runUnitTest, compareEmptyWithZeroBlocks) {
  std::vector<int32_t> values1 = {};
  std::vector<int32_t> values2 = {0};

  PcoreAbsoluteBlock block1 = PcoreAbsoluteBlock(values1);
  PcoreAbsoluteBlock block2 = PcoreAbsoluteBlock(values2);

  EXPECT_FALSE(block1.isEqual(block2));
}

#include <vector>
#include "AbsoluteBlock.h"
#include "gtest/gtest.h"
TEST(runUnitTest, TestGetAndSetValues) {
  std::vector<int32_t> values = {1, 2, 3};
  AbsoluteBlock block = AbsoluteBlock(values);
  EXPECT_EQ(block.getValues(), values);
}

TEST(runUnitTest, TestGetAndSetEmptyValues) {
  std::vector<int32_t> values = {};
  AbsoluteBlock block = AbsoluteBlock(values);

  EXPECT_EQ(block.getValues(), values);
}

TEST(runUnitTest, TestGetAndSet0Values) {
  std::vector<int32_t> values = {0};
  AbsoluteBlock block = AbsoluteBlock(values);
  EXPECT_EQ(block.getValues(), values);
}

TEST(runUnitTest, CompareEmptyAndFullBlocks) {
  std::vector<int32_t> values1 = {};
  std::vector<int32_t> values2 = {1, 2, 3};

  AbsoluteBlock block1 = AbsoluteBlock(values1);
  AbsoluteBlock block2 = AbsoluteBlock(values2);

  EXPECT_FALSE(block1.isEqual(block2));
}

TEST(runUnitTest, CompareShortAndFullBlocks) {
  std::vector<int32_t> values1 = {1};
  std::vector<int32_t> values2 = {1, 2, 3};

  AbsoluteBlock block1 = AbsoluteBlock(values1);
  AbsoluteBlock block2 = AbsoluteBlock(values2);

  EXPECT_FALSE(block1.isEqual(block2));
}

TEST(runUnitTest, CompareSameContentBlocks) {
  std::vector<int32_t> values1 = {1, 2, 3};
  std::vector<int32_t> values2 = {1, 2, 3};

  AbsoluteBlock block1 = AbsoluteBlock(values1);
  AbsoluteBlock block2 = AbsoluteBlock(values2);

  EXPECT_TRUE(block1.isEqual(block2));
}

TEST(runUnitTest, CompareFullandEmptyBlocks) {
  std::vector<int32_t> values1 = {1, 2, 3};
  std::vector<int32_t> values2 = {};

  AbsoluteBlock block1 = AbsoluteBlock(values1);
  AbsoluteBlock block2 = AbsoluteBlock(values2);

  EXPECT_FALSE(block1.isEqual(block2));
}

TEST(runUnitTest, CompareFullandShortBlocks) {
  std::vector<int32_t> values1 = {1, 2, 3};
  std::vector<int32_t> values2 = {1};

  AbsoluteBlock block1 = AbsoluteBlock(values1);
  AbsoluteBlock block2 = AbsoluteBlock(values2);

  EXPECT_FALSE(block1.isEqual(block2));
}

TEST(runUnitTest, CompareLongWithMediumBlocks) {
  std::vector<int32_t> values1 = {1, 2, 3};
  std::vector<int32_t> values2 = {1, 2};

  AbsoluteBlock block1 = AbsoluteBlock(values1);
  AbsoluteBlock block2 = AbsoluteBlock(values2);

  EXPECT_FALSE(block1.isEqual(block2));
}

TEST(runUnitTest, CompareEmptyWithEmptyBlocks) {
  std::vector<int32_t> values1 = {};
  std::vector<int32_t> values2 = {};

  AbsoluteBlock block1 = AbsoluteBlock(values1);
  AbsoluteBlock block2 = AbsoluteBlock(values2);

  EXPECT_TRUE(block1.isEqual(block2));
}

TEST(runUnitTest, CompareZeroWithZeroBlocks) {
  std::vector<int32_t> values1 = {0};
  std::vector<int32_t> values2 = {0};

  AbsoluteBlock block1 = AbsoluteBlock(values1);
  AbsoluteBlock block2 = AbsoluteBlock(values2);

  EXPECT_TRUE(block1.isEqual(block2));
}

TEST(runUnitTest, CompareEmptyWithZeroBlocks) {
  std::vector<int32_t> values1 = {};
  std::vector<int32_t> values2 = {0};

  AbsoluteBlock block1 = AbsoluteBlock(values1);
  AbsoluteBlock block2 = AbsoluteBlock(values2);

  EXPECT_FALSE(block1.isEqual(block2));
}

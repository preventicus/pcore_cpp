#include <vector>
#include "PcoreAbsoluteBlock.h"
#include "gtest/gtest.h"
TEST(runUnitTest, TestGetAndSetValues) {
  PcoreAbsoluteBlock block1;
  std::vector<int32_t> values1 = {1, 2, 3};
  block1.setValues(values1);
  EXPECT_EQ(block1.getValues(), values1);
}

TEST(runUnitTest, TestGetAndSetEmptyValues) {
  PcoreAbsoluteBlock block1;
  std::vector<int32_t> values1 = {};
  block1.setValues(values1);
  EXPECT_EQ(block1.getValues(), values1);
}

TEST(runUnitTest, TestGetAndSet0Values) {
  PcoreAbsoluteBlock block1;
  std::vector<int32_t> values1 = {0};
  block1.setValues(values1);
  EXPECT_EQ(block1.getValues(), values1);
}

TEST(runUnitTest, CompareEmptyAndFullBlocks) {
  std::vector<int32_t> values1 = {};
  std::vector<int32_t> values2 = {1, 2, 3};

  PcoreAbsoluteBlock block1;
  block1.setValues(values1);
  PcoreAbsoluteBlock block2;
  block2.setValues(values2);

  EXPECT_FALSE(block1.isEqual(block2));
}

TEST(runUnitTest, CompareShortAndFullBlocks) {
  std::vector<int32_t> values1 = {1};
  std::vector<int32_t> values2 = {1, 2, 3};

  PcoreAbsoluteBlock block1;
  block1.setValues(values1);
  PcoreAbsoluteBlock block2;
  block2.setValues(values2);

  EXPECT_FALSE(block1.isEqual(block2));
}

TEST(runUnitTest, CompareSameContentBlocks) {
  std::vector<int32_t> values1 = {1, 2, 3};
  std::vector<int32_t> values2 = {1, 2, 3};

  PcoreAbsoluteBlock block1;
  block1.setValues(values1);
  PcoreAbsoluteBlock block2;
  block2.setValues(values2);

  EXPECT_TRUE(block1.isEqual(block2));
}

TEST(runUnitTest, CompareFullandEmptyBlocks) {
  std::vector<int32_t> values1 = {1, 2, 3};
  std::vector<int32_t> values2 = {};

  PcoreAbsoluteBlock block1;
  block1.setValues(values1);
  PcoreAbsoluteBlock block2;
  block2.setValues(values2);

  EXPECT_FALSE(block1.isEqual(block2));
}

TEST(runUnitTest, CompareFullandShortBlocks) {
  std::vector<int32_t> values1 = {1, 2, 3};
  std::vector<int32_t> values2 = {1};

  PcoreAbsoluteBlock block1;
  block1.setValues(values1);
  PcoreAbsoluteBlock block2;
  block2.setValues(values2);

  EXPECT_FALSE(block1.isEqual(block2));
}

TEST(runUnitTest, CompareLongWithMediumBlocks) {
  std::vector<int32_t> values1 = {1, 2, 3};
  std::vector<int32_t> values2 = {1, 2};

  PcoreAbsoluteBlock block1;
  block1.setValues(values1);
  PcoreAbsoluteBlock block2;
  block2.setValues(values2);

  EXPECT_FALSE(block1.isEqual(block2));
}

TEST(runUnitTest, CompareEmptyWithEmptyBlocks) {
  std::vector<int32_t> values1 = {};
  std::vector<int32_t> values2 = {};

  PcoreAbsoluteBlock block1;
  block1.setValues(values1);
  PcoreAbsoluteBlock block2;
  block2.setValues(values2);

  EXPECT_TRUE(block1.isEqual(block2));
}

TEST(runUnitTest, CompareZeroWithZeroBlocks) {
  std::vector<int32_t> values1 = {0};
  std::vector<int32_t> values2 = {0};

  PcoreAbsoluteBlock block1;
  block1.setValues(values1);
  PcoreAbsoluteBlock block2;
  block2.setValues(values2);

  EXPECT_TRUE(block1.isEqual(block2));
}

TEST(runUnitTest, CompareEmptyWithZeroBlocks) {
  std::vector<int32_t> values1 = {};
  std::vector<int32_t> values2 = {0};

  PcoreAbsoluteBlock block1;
  block1.setValues(values1);
  PcoreAbsoluteBlock block2;
  block2.setValues(values2);

  EXPECT_FALSE(block1.isEqual(block2));
}

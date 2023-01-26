#include <gtest/gtest.h>
#include "DifferentialBlock.h"

TEST(runUnitTests, TestSetAndGetDiffValues) {
  std::vector<int32_t> diffValues = {30, 32, 54};
  DifferentialBlock dBlock;
  dBlock.setDiffValues(diffValues);
  EXPECT_EQ(dBlock.getDiffValues(), diffValues);
}

TEST(runUnitTests, TestSetAndGetWithEmptyDiffValues) {
  std::vector<int32_t> diffValues = {};
  DifferentialBlock dBlock;
  dBlock.setDiffValues(diffValues);
  EXPECT_EQ(dBlock.getDiffValues(), diffValues);
}

TEST(runUnitTests, CompareDiffValuesEqual) {
  std::vector<int32_t> diffValues1 = {30, 32, 54};
  DifferentialBlock dBlock1;
  dBlock1.setDiffValues(diffValues1);
  std::vector<int32_t> diffValues2 = {30, 32, 54};
  DifferentialBlock dBlock2;
  dBlock2.setDiffValues(diffValues2);
  EXPECT_TRUE(dBlock1.isEqual(dBlock2));
}

TEST(runUnitTests, CompareDiffValuesDifferent) {
  std::vector<int32_t> diffValues1 = {30, 32, 54};
  DifferentialBlock dBlock1;
  dBlock1.setDiffValues(diffValues1);
  std::vector<int32_t> diffValues2 = {33, 32, 54};
  DifferentialBlock dBlock2;
  dBlock2.setDiffValues(diffValues2);
  EXPECT_FALSE(dBlock1.isEqual(dBlock2));
}

TEST(runUnitTests, CompareDiffValuesEmpty) {
  std::vector<int32_t> diffValues1 = {};
  DifferentialBlock dBlock1;
  dBlock1.setDiffValues(diffValues1);
  std::vector<int32_t> diffValues2 = {};
  DifferentialBlock dBlock2;
  dBlock2.setDiffValues(diffValues2);
  EXPECT_TRUE(dBlock1.isEqual(dBlock2));
}

TEST(runUnitTests, CompareDiffValues0) {
  std::vector<int32_t> diffValues1 = {0};
  DifferentialBlock dBlock1;
  dBlock1.setDiffValues(diffValues1);
  std::vector<int32_t> diffValues2 = {0};
  DifferentialBlock dBlock2;
  dBlock2.setDiffValues(diffValues2);
  EXPECT_TRUE(dBlock1.isEqual(dBlock2));
}

TEST(runUnitTest, CompareDiffValuesFullAndEmpty) {
  std::vector<int32_t> diffValues1 = {30, 32, 54};
  DifferentialBlock dBlock1;
  dBlock1.setDiffValues(diffValues1);
  std::vector<int32_t> diffValues2 = {};
  DifferentialBlock dBlock2;
  dBlock2.setDiffValues(diffValues2);
  EXPECT_FALSE(dBlock1.isEqual(dBlock2));
}

TEST(runUnitTests, TestSerializeAndDeserialize) {
  DifferentialBlock dBlock1;
  std::vector<int32_t> diffValues = {30, 32, 54};
  dBlock1.setDiffValues(diffValues);
  ProtobufBlock protobufBlocks = dBlock1.serialize();
  DifferentialBlock dBlock2;
  dBlock2.deserialize(protobufBlocks);
  EXPECT_TRUE(dBlock1.isEqual(dBlock2));
}

TEST(runUnitTests, TestSerializeAndDeserializeWithEmptyVector) {
  DifferentialBlock dBlock1;
  std::vector<int32_t> diffValues = {};
  dBlock1.setDiffValues(diffValues);
  ProtobufBlock protobufBlocks = dBlock1.serialize();
  DifferentialBlock dBlock2;
  dBlock2.deserialize(protobufBlocks);
  EXPECT_TRUE(dBlock1.isEqual(dBlock2));
}

TEST(runUnitTests, TestSerializeAndDeserializeWith0) {
  DifferentialBlock dBlock1;
  std::vector<int32_t> diffValues = {0};
  dBlock1.setDiffValues(diffValues);
  ProtobufBlock protobufBlocks = dBlock1.serialize();
  DifferentialBlock dBlock2;
  dBlock2.deserialize(protobufBlocks);
  EXPECT_TRUE(dBlock1.isEqual(dBlock2));
}

TEST(runUnitTests, TestSerializeAndDeserializeWithNegativeAndPositiveDiffValues) {
  DifferentialBlock dBlock1;
  std::vector<int32_t> diffValues = {-23, 234, -13};
  dBlock1.setDiffValues(diffValues);
  ProtobufBlock protobufBlocks = dBlock1.serialize();
  DifferentialBlock dBlock2;
  dBlock2.deserialize(protobufBlocks);
  EXPECT_TRUE(dBlock1.isEqual(dBlock2));
}

TEST(runUnitTests, TestSerializeAndDeserializeWithEmptyVectorOneDiffValues) {
  DifferentialBlock dBlock1;
  std::vector<int32_t> diffValues = {123};
  dBlock1.setDiffValues(diffValues);
  ProtobufBlock protobufBlocks = dBlock1.serialize();
  DifferentialBlock dBlock2;
  dBlock2.deserialize(protobufBlocks);
  EXPECT_TRUE(dBlock1.isEqual(dBlock2));
}

TEST(runUnitTests, TestSerializeAndDeserializeWithOneNegativeDiffValues) {
  DifferentialBlock dBlock1;
  std::vector<int32_t> diffValues = {-123};
  dBlock1.setDiffValues(diffValues);
  ProtobufBlock protobufBlocks = dBlock1.serialize();
  DifferentialBlock dBlock2;
  dBlock2.deserialize(protobufBlocks);
  EXPECT_TRUE(dBlock1.isEqual(dBlock2));
}

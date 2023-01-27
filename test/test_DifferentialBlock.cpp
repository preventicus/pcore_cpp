#include <gtest/gtest.h>
#include "DifferentialBlock.h"

TEST(runUnitTests, TestSetAndGetDiffValues) {
  std::vector<int32_t> diffValues = {30, 32, 54};
  DifferentialBlock dBlock = DifferentialBlock(diffValues);
  EXPECT_EQ(dBlock.getDiffValues(), diffValues);
}

TEST(runUnitTests, TestSetAndGetWithEmptyDiffValues) {
  std::vector<int32_t> diffValues = {};
  DifferentialBlock dBlock = DifferentialBlock(diffValues);
  EXPECT_EQ(dBlock.getDiffValues(), diffValues);
}

TEST(runUnitTests, CompareDiffValuesEqual) {
  std::vector<int32_t> diffValues1 = {30, 32, 54};
  DifferentialBlock dBlock1 = DifferentialBlock(diffValues1);
  std::vector<int32_t> diffValues2 = {30, 32, 54};
  DifferentialBlock dBlock2 = DifferentialBlock(diffValues2);
  EXPECT_TRUE(dBlock1.isEqual(dBlock2));
}

TEST(runUnitTests, CompareDiffValuesDifferent) {
  std::vector<int32_t> diffValues1 = {30, 32, 54};
  DifferentialBlock dBlock1 = DifferentialBlock(diffValues1);
  std::vector<int32_t> diffValues2 = {33, 32, 54};
  DifferentialBlock dBlock2 = DifferentialBlock(diffValues2);
  EXPECT_FALSE(dBlock1.isEqual(dBlock2));
}

TEST(runUnitTests, CompareDiffValuesEmpty) {
  std::vector<int32_t> diffValues1 = {};
  DifferentialBlock dBlock1 = DifferentialBlock(diffValues1);
  std::vector<int32_t> diffValues2 = {};
  DifferentialBlock dBlock2 = DifferentialBlock(diffValues2);
  EXPECT_TRUE(dBlock1.isEqual(dBlock2));
}

TEST(runUnitTests, CompareDiffValues0) {
  std::vector<int32_t> diffValues1 = {0};
  DifferentialBlock dBlock1 = DifferentialBlock(diffValues1);
  std::vector<int32_t> diffValues2 = {0};
  DifferentialBlock dBlock2 = DifferentialBlock(diffValues2);
  EXPECT_TRUE(dBlock1.isEqual(dBlock2));
}

TEST(runUnitTest, CompareDiffValuesFullAndEmpty) {
  std::vector<int32_t> diffValues1 = {30, 32, 54};
  DifferentialBlock dBlock1 = DifferentialBlock(diffValues1);
  std::vector<int32_t> diffValues2 = {};
  DifferentialBlock dBlock2 = DifferentialBlock(diffValues2);
  EXPECT_FALSE(dBlock1.isEqual(dBlock2));
}

TEST(runUnitTests, TestSerializeAndDeserialize) {
  std::vector<int32_t> diffValues = {30, 32, 54};
  DifferentialBlock dBlock1 = DifferentialBlock(diffValues);
  ProtobufBlock protobufBlocks = dBlock1.serialize();
  DifferentialBlock dBlock2 = DifferentialBlock(protobufBlocks);
  EXPECT_TRUE(dBlock1.isEqual(dBlock2));
}

TEST(runUnitTests, TestSerializeAndDeserializeWithEmptyVector) {
  std::vector<int32_t> diffValues = {};
  DifferentialBlock dBlock1 = DifferentialBlock(diffValues);
  ProtobufBlock protobufBlocks = dBlock1.serialize();
  DifferentialBlock dBlock2 = DifferentialBlock(protobufBlocks);
  EXPECT_TRUE(dBlock1.isEqual(dBlock2));
}

TEST(runUnitTests, TestSerializeAndDeserializeWith0) {
  std::vector<int32_t> diffValues = {0};
  DifferentialBlock dBlock1 = DifferentialBlock(diffValues);
  ProtobufBlock protobufBlocks = dBlock1.serialize();
  DifferentialBlock dBlock2 = DifferentialBlock(protobufBlocks);
  EXPECT_TRUE(dBlock1.isEqual(dBlock2));
}

TEST(runUnitTests, TestSerializeAndDeserializeWithNegativeAndPositiveDiffValues) {
  std::vector<int32_t> diffValues = {-23, 234, -13};
  DifferentialBlock dBlock1 = DifferentialBlock(diffValues);
  ProtobufBlock protobufBlocks = dBlock1.serialize();
  DifferentialBlock dBlock2 = DifferentialBlock(protobufBlocks);
  EXPECT_TRUE(dBlock1.isEqual(dBlock2));
}

TEST(runUnitTests, TestSerializeAndDeserializeWithEmptyVectorOneDiffValues) {
  std::vector<int32_t> diffValues = {123};
  DifferentialBlock dBlock1 = DifferentialBlock(diffValues);
  ProtobufBlock protobufBlocks = dBlock1.serialize();
  DifferentialBlock dBlock2 = DifferentialBlock(protobufBlocks);
  EXPECT_TRUE(dBlock1.isEqual(dBlock2));
}

TEST(runUnitTests, TestSerializeAndDeserializeWithOneNegativeDiffValues) {
  std::vector<int32_t> diffValues = {-123};
  DifferentialBlock dBlock1 = DifferentialBlock(diffValues);
  ProtobufBlock protobufBlocks = dBlock1.serialize();
  DifferentialBlock dBlock2 = DifferentialBlock(protobufBlocks);
  EXPECT_TRUE(dBlock1.isEqual(dBlock2));
}

TEST(runUnitTest, CompareTwoDeserializedDiffValues) {
  std::vector<int32_t> diffValues1 = {-123};
  std::vector<int32_t> diffValues2 = {-123};
  DifferentialBlock dBlock1 = DifferentialBlock(diffValues1);
  DifferentialBlock dBlock2 = DifferentialBlock(diffValues2);
  ProtobufBlock protobufBlocks1 = dBlock1.serialize();
  ProtobufBlock protobufBlocks2 = dBlock2.serialize();
  DifferentialBlock dBlock3 = DifferentialBlock(protobufBlocks1);
  DifferentialBlock dBlock4 = DifferentialBlock(protobufBlocks2);
  EXPECT_TRUE(dBlock3.isEqual(dBlock4));
}
#include <gtest/gtest.h>
#include "DeserializedDifferntialBlock.h"

TEST(runUnitTests, TestSetAndGetDiffValues) {
  std::vector<int32_t> diffValues = {30, 32, 54};
  DeserializedDifferentialBlock dBlock;
  dBlock.setDiffValues(diffValues);
  EXPECT_EQ(dBlock.getDiffValues(), diffValues);
}

TEST(runUnitTests, TestSetAndGetWithEmptyDiffValues) {
  std::vector<int32_t> diffValues = {};
  DeserializedDifferentialBlock dBlock;
  dBlock.setDiffValues(diffValues);
  EXPECT_EQ(dBlock.getDiffValues(), diffValues);
}

TEST(runUnitTests, CompareDiffValuesEqual) {
  std::vector<int32_t> diffValues1 = {30, 32, 54};
  DeserializedDifferentialBlock dBlock1;
  dBlock1.setDiffValues(diffValues1);
  std::vector<int32_t> diffValues2 = {30, 32, 54};
  DeserializedDifferentialBlock dBlock2;
  dBlock2.setDiffValues(diffValues2);
  EXPECT_TRUE(dBlock1.isEqual(dBlock2));
}

TEST(runUnitTests, CompareDiffValuesDifferent) {
  std::vector<int32_t> diffValues1 = {30, 32, 54};
  DeserializedDifferentialBlock dBlock1;
  dBlock1.setDiffValues(diffValues1);
  std::vector<int32_t> diffValues2 = {33, 32, 54};
  DeserializedDifferentialBlock dBlock2;
  dBlock2.setDiffValues(diffValues2);
  EXPECT_FALSE(dBlock1.isEqual(dBlock2));
}

TEST(runUnitTests, CompareDiffValuesEmpty) {
  std::vector<int32_t> diffValues1 = {};
  DeserializedDifferentialBlock dBlock1;
  dBlock1.setDiffValues(diffValues1);
  std::vector<int32_t> diffValues2 = {};
  DeserializedDifferentialBlock dBlock2;
  dBlock2.setDiffValues(diffValues2);
  EXPECT_TRUE(dBlock1.isEqual(dBlock2));
}

TEST(runUnitTests, CompareDiffValues0) {
  std::vector<int32_t> diffValues1 = {0};
  DeserializedDifferentialBlock dBlock1;
  dBlock1.setDiffValues(diffValues1);
  std::vector<int32_t> diffValues2 = {0};
  DeserializedDifferentialBlock dBlock2;
  dBlock2.setDiffValues(diffValues2);
  EXPECT_TRUE(dBlock1.isEqual(dBlock2));
}

TEST(runUnitTest, CompareDiffValuesFullAndEmpty) {
  std::vector<int32_t> diffValues1 = {30, 32, 54};
  DeserializedDifferentialBlock dBlock1;
  dBlock1.setDiffValues(diffValues1);
  std::vector<int32_t> diffValues2 = {};
  DeserializedDifferentialBlock dBlock2;
  dBlock2.setDiffValues(diffValues2);
  EXPECT_FALSE(dBlock1.isEqual(dBlock2));
}

TEST(runUnitTests, TestSerializeAndDeserialize) {
  DeserializedDifferentialBlock dBlock1;
  std::vector<int32_t> diffValues = {30, 32, 54};
  dBlock1.setDiffValues(diffValues);
  SerializedBlock blocks = dBlock1.serialize();
  DeserializedDifferentialBlock dBlock2;
  dBlock2.deserialized(blocks);
  EXPECT_TRUE(dBlock1.isEqual(dBlock2));
}

TEST(runUnitTests, TestSerializeAndDeserializeWithEmptyVector) {
  DeserializedDifferentialBlock dBlock1;
  std::vector<int32_t> diffValues = {};
  dBlock1.setDiffValues(diffValues);
  SerializedBlock blocks = dBlock1.serialize();
  DeserializedDifferentialBlock dBlock2;
  dBlock2.deserialized(blocks);
  EXPECT_TRUE(dBlock1.isEqual(dBlock2));
}

TEST(runUnitTests, TestSerializeAndDeserializeWith0) {
  DeserializedDifferentialBlock dBlock1;
  std::vector<int32_t> diffValues = {0};
  dBlock1.setDiffValues(diffValues);
  SerializedBlock blocks = dBlock1.serialize();
  DeserializedDifferentialBlock dBlock2;
  dBlock2.deserialized(blocks);
  EXPECT_TRUE(dBlock1.isEqual(dBlock2));
}

TEST(runUnitTests, TestSerializeAndDeserializeWithNegativeAndPositiveDiffValues) {
  DeserializedDifferentialBlock dBlock1;
  std::vector<int32_t> diffValues = {-23, 234, -13};
  dBlock1.setDiffValues(diffValues);
  SerializedBlock blocks = dBlock1.serialize();
  DeserializedDifferentialBlock dBlock2;
  dBlock2.deserialized(blocks);
  EXPECT_TRUE(dBlock1.isEqual(dBlock2));
}

TEST(runUnitTests, TestSerializeAndDeserializeWithEmptyVectorOneDiffValues) {
  DeserializedDifferentialBlock dBlock1;
  std::vector<int32_t> diffValues = {123};
  dBlock1.setDiffValues(diffValues);
  SerializedBlock blocks = dBlock1.serialize();
  DeserializedDifferentialBlock dBlock2;
  dBlock2.deserialized(blocks);
  EXPECT_TRUE(dBlock1.isEqual(dBlock2));
}

TEST(runUnitTests, TestSerializeAndDeserializeWithOneNegativeDiffValues) {
  DeserializedDifferentialBlock dBlock1;
  std::vector<int32_t> diffValues = {-123};
  dBlock1.setDiffValues(diffValues);
  SerializedBlock blocks = dBlock1.serialize();
  DeserializedDifferentialBlock dBlock2;
  dBlock2.deserialized(blocks);
  EXPECT_TRUE(dBlock1.isEqual(dBlock2));
}

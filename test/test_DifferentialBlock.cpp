#include <gtest/gtest.h>
#include "DifferentialBlock.h"

class DifferentialBlockTest : public ::testing::Test {
 protected:
  DifferentialBlock differentialBlockNormal1;
  DifferentialBlock differentialBlockNormal2;
  DifferentialBlock differentialBlockWithNegativeValues1;
  DifferentialBlock differentialBlockWithNegativeValues2;
  DifferentialBlock differentialBlockOneNegativeValue1;
  DifferentialBlock differentialBlockOneNegativeValue2;
  DifferentialBlock differentialBlockOnePositiveValue1;
  DifferentialBlock differentialBlockOnePositiveValue2;
  DifferentialBlock differentialBlock0Value1;
  DifferentialBlock differentialBlock0Value2;
  DifferentialBlock differentialBlockEmptyValue1;
  DifferentialBlock differentialBlockEmptyValue2;
  std::vector<int32_t> DiffValuesNormal = {30, 32, 54};
  std::vector<int32_t> DiffValuesNormalNeagtive = {-23, -234, -13};
  std::vector<int32_t> DiffValuesOneNegative = {-123};
  std::vector<int32_t> DiffValuesOnePositive = {123};
  std::vector<int32_t> DiffValues0 = {0};
  std::vector<int32_t> DiffValuesEmpty = {};

  virtual void SetUp() {
    this->differentialBlockNormal1 = DifferentialBlock(this->DiffValuesNormal);
    this->differentialBlockNormal2 = DifferentialBlock(this->DiffValuesNormal);
    this->differentialBlockWithNegativeValues1 = DifferentialBlock(this->DiffValuesNormalNeagtive);
    this->differentialBlockWithNegativeValues2 = DifferentialBlock(this->DiffValuesNormalNeagtive);
    this->differentialBlockOneNegativeValue1 = DifferentialBlock(this->DiffValuesOneNegative);
    this->differentialBlockOneNegativeValue2 = DifferentialBlock(this->DiffValuesOneNegative);
    this->differentialBlockOnePositiveValue1 = DifferentialBlock(this->DiffValuesOnePositive);
    this->differentialBlockOnePositiveValue2 = DifferentialBlock(this->DiffValuesOnePositive);
    this->differentialBlock0Value1 = DifferentialBlock(this->DiffValues0);
    this->differentialBlock0Value2 = DifferentialBlock(this->DiffValues0);
    this->differentialBlockEmptyValue1 = DifferentialBlock(this->DiffValuesEmpty);
    this->differentialBlockEmptyValue2 = DifferentialBlock(this->DiffValuesEmpty);
  }
};

TEST_F(DifferentialBlockTest, TestSetAndGetDiffValues) {
  EXPECT_EQ(this->differentialBlockNormal1.getDiffValues(), this->DiffValuesNormal);
}

TEST_F(DifferentialBlockTest, TestSetAndGetWithEmptyDiffValues) {
  EXPECT_EQ(this->differentialBlockEmptyValue1.getDiffValues(), this->DiffValuesEmpty);
}

TEST_F(DifferentialBlockTest, TestSetAndGetWithDiffValues0) {
  EXPECT_EQ(this->differentialBlock0Value1.getDiffValues(), this->DiffValues0);
}

TEST_F(DifferentialBlockTest, TestSetAndGetWithNegativeDiffValues) {
  EXPECT_EQ(this->differentialBlockWithNegativeValues1.getDiffValues(), this->DiffValuesNormalNeagtive);
}

TEST_F(DifferentialBlockTest, CompareDiffValuesEqual) {
  EXPECT_TRUE(this->differentialBlockNormal2.isEqual(this->differentialBlockNormal1));
}

TEST_F(DifferentialBlockTest, CompareDiffValuesDifferent) {
  EXPECT_FALSE(this->differentialBlockOnePositiveValue1.isEqual(this->differentialBlock0Value1));
}

TEST_F(DifferentialBlockTest, CompareDiffValuesEmpty) {
  EXPECT_TRUE(this->differentialBlockEmptyValue1.isEqual(this->differentialBlockEmptyValue2));
}

TEST_F(DifferentialBlockTest, CompareDiffValues0) {
  EXPECT_TRUE(this->differentialBlock0Value1.isEqual(this->differentialBlock0Value2));
}

TEST_F(DifferentialBlockTest, CompareDiffNegativeValues) {
  EXPECT_TRUE(this->differentialBlockOneNegativeValue1.isEqual(this->differentialBlockOneNegativeValue2));
}

TEST_F(DifferentialBlockTest, TestSerializeAndDeserialize) {
  ProtobufBlock protobufBlocks = this->differentialBlockNormal1.serialize();
  DifferentialBlock dBlock = DifferentialBlock(protobufBlocks);
  EXPECT_TRUE(this->differentialBlockNormal1.isEqual(dBlock));
}

TEST_F(DifferentialBlockTest, TestSerializeAndDeserializeWithEmptyVector) {
  ProtobufBlock protobufBlocks = this->differentialBlockEmptyValue1.serialize();
  DifferentialBlock dBlock = DifferentialBlock(protobufBlocks);
  EXPECT_TRUE(this->differentialBlockEmptyValue1.isEqual(dBlock));
}

TEST_F(DifferentialBlockTest, TestSerializeAndDeserializeWithNegativeAndPositiveDiffValues) {
  ProtobufBlock protobufBlocks = this->differentialBlockWithNegativeValues1.serialize();
  DifferentialBlock dBlock = DifferentialBlock(protobufBlocks);
  EXPECT_TRUE(this->differentialBlockWithNegativeValues1.isEqual(dBlock));
}

TEST_F(DifferentialBlockTest, TestSerializeAndDeserializeWithOneNegativeDiffValues) {
  ProtobufBlock protobufBlocks = this->differentialBlockOneNegativeValue1.serialize();
  DifferentialBlock dBlock = DifferentialBlock(protobufBlocks);
  EXPECT_TRUE(this->differentialBlockOneNegativeValue1.isEqual(dBlock));
}

TEST_F(DifferentialBlockTest, TestSerializeAndDeserializeWithOnePositiveDiffValues) {
  ProtobufBlock protobufBlocks = this->differentialBlockOnePositiveValue1.serialize();
  DifferentialBlock dBlock = DifferentialBlock(protobufBlocks);
  EXPECT_TRUE(this->differentialBlockOnePositiveValue1.isEqual(dBlock));
}

TEST_F(DifferentialBlockTest, CompareTwoDeserializedDiffValues) {
  ProtobufBlock protobufBlocks1 = this->differentialBlockWithNegativeValues1.serialize();
  ProtobufBlock protobufBlocks2 = this->differentialBlockWithNegativeValues2.serialize();
  DifferentialBlock baseDBlock = DifferentialBlock(protobufBlocks1);
  DifferentialBlock comparableDBlock = DifferentialBlock(protobufBlocks2);
  EXPECT_TRUE(baseDBlock.isEqual(comparableDBlock));
}
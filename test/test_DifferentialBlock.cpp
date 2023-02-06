/*

Created by Jakob Glück 2023

Copyright © 2023 PREVENTICUS GmbH

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors
   may be used to endorse or promote products derived from this software without
   specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/
#include <gtest/gtest.h>
#include "DifferentialBlock.h"

class DifferentialBlockTest : public ::testing::Test {
 protected:
  std::vector<int32_t> diffValuesNormal = {30, 32, 54};
  std::vector<int32_t> diffValuesNormalNeagtive = {-23, -234, -13};
  std::vector<int32_t> diffValuesOneNegative = {-123};
  std::vector<int32_t> diffValuesOnePositive = {123};
  std::vector<int32_t> diffValues0 = {0};
  std::vector<int32_t> diffValuesEmpty = {};
  DifferentialBlock differentialBlockNormal1 = DifferentialBlock(diffValuesNormal);
  DifferentialBlock differentialBlockNormal2 = DifferentialBlock(diffValuesNormal);
  DifferentialBlock differentialBlockWithNegativeValues1 = DifferentialBlock(diffValuesNormalNeagtive);
  DifferentialBlock differentialBlockWithNegativeValues2 = DifferentialBlock(diffValuesNormalNeagtive);
  DifferentialBlock differentialBlockOneNegativeValue1 = DifferentialBlock(diffValuesOneNegative);
  DifferentialBlock differentialBlockOneNegativeValue2 = DifferentialBlock(diffValuesOneNegative);
  DifferentialBlock differentialBlockOnePositiveValue1 = DifferentialBlock(diffValuesOnePositive);
  DifferentialBlock differentialBlockOnePositiveValue2 = DifferentialBlock(diffValuesOnePositive);
  DifferentialBlock differentialBlock0Value1 = DifferentialBlock(diffValues0);
  DifferentialBlock differentialBlock0Value2 = DifferentialBlock(diffValues0);
  DifferentialBlock differentialBlockEmptyValue1 = DifferentialBlock(diffValuesEmpty);
  DifferentialBlock differentialBlockEmptyValue2 = DifferentialBlock(diffValuesEmpty);
};

TEST_F(DifferentialBlockTest, TestGetDiffValues) {
  EXPECT_EQ(this->differentialBlockNormal1.getDiffValues(), this->diffValuesNormal);
}

TEST_F(DifferentialBlockTest, TestGetWithEmptyDiffValues) {
  EXPECT_EQ(this->differentialBlockEmptyValue1.getDiffValues(), this->diffValuesEmpty);
}

TEST_F(DifferentialBlockTest, TestGetWithDiffValues0) {
  EXPECT_EQ(this->differentialBlock0Value1.getDiffValues(), this->diffValues0);
}

TEST_F(DifferentialBlockTest, TestGetWithNegativeDiffValues) {
  EXPECT_EQ(this->differentialBlockWithNegativeValues1.getDiffValues(), this->diffValuesNormalNeagtive);
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

TEST_F(DifferentialBlockTest, CompareDiffNegativeDiffValues) {
  EXPECT_TRUE(this->differentialBlockOneNegativeValue1.isEqual(this->differentialBlockOneNegativeValue2));
}

TEST_F(DifferentialBlockTest, TestSerializeAndDeserializeForNormalDiffvalues) {
  ProtobufDifferentialBlock protobufDifferentialBlocks;
  this->differentialBlockNormal1.serialize(&protobufDifferentialBlocks);
  DifferentialBlock dBlock = DifferentialBlock(protobufDifferentialBlocks);
  EXPECT_TRUE(this->differentialBlockNormal1.isEqual(dBlock));
}

TEST_F(DifferentialBlockTest, TestSerializeAndDeserializeWithEmptyDiffValues) {
  ProtobufDifferentialBlock protobufDifferentialBlocks;
  this->differentialBlockEmptyValue1.serialize(&protobufDifferentialBlocks);
  DifferentialBlock dBlock = DifferentialBlock(protobufDifferentialBlocks);
  EXPECT_TRUE(this->differentialBlockEmptyValue1.isEqual(dBlock));
}

TEST_F(DifferentialBlockTest, TestSerializeAndDeserializeWithNegativeAndPositiveDiffValues) {
  ProtobufDifferentialBlock protobufDifferentialBlocks;
  this->differentialBlockWithNegativeValues1.serialize(&protobufDifferentialBlocks);
  DifferentialBlock dBlock = DifferentialBlock(protobufDifferentialBlocks);
  EXPECT_TRUE(this->differentialBlockWithNegativeValues1.isEqual(dBlock));
}

TEST_F(DifferentialBlockTest, TestSerializeAndDeserializeWithOneNegativeDiffValues) {
  ProtobufDifferentialBlock protobufDifferentialBlocks;
  this->differentialBlockOneNegativeValue1.serialize(&protobufDifferentialBlocks);
  DifferentialBlock dBlock = DifferentialBlock(protobufDifferentialBlocks);
  EXPECT_TRUE(this->differentialBlockOneNegativeValue1.isEqual(dBlock));
}

TEST_F(DifferentialBlockTest, TestSerializeAndDeserializeWithOnePositiveDiffValues) {
  ProtobufDifferentialBlock protobufDifferentialBlocks;
  this->differentialBlockOnePositiveValue1.serialize(&protobufDifferentialBlocks);
  DifferentialBlock dBlock = DifferentialBlock(protobufDifferentialBlocks);
  EXPECT_TRUE(this->differentialBlockOnePositiveValue1.isEqual(dBlock));
}

TEST_F(DifferentialBlockTest, CompareTwoDeserializedDiffValues) {
  ProtobufDifferentialBlock protobufDifferentialBlocks1;
  this->differentialBlockWithNegativeValues1.serialize(&protobufDifferentialBlocks1);
  ProtobufDifferentialBlock protobufDifferentialBlocks2;
  this->differentialBlockWithNegativeValues2.serialize(&protobufDifferentialBlocks2);
  DifferentialBlock baseDBlock = DifferentialBlock(protobufDifferentialBlocks1);
  DifferentialBlock comparableDBlock = DifferentialBlock(protobufDifferentialBlocks2);
  EXPECT_TRUE(baseDBlock.isEqual(comparableDBlock));
}

TEST_F(DifferentialBlockTest, CheckDifferentialBlockPtr) {
  ProtobufDifferentialBlock protobufData;
  this->differentialBlockNormal1.serialize(&protobufData);
  DifferentialBlock differentialBlock = DifferentialBlock(protobufData);
  ProtobufDifferentialBlock* protobufDataPtr = &protobufData;
  DifferentialBlock* ptr = &differentialBlock;
  EXPECT_FALSE(ptr == nullptr);
  EXPECT_FALSE(protobufDataPtr == nullptr);
}

TEST_F(DifferentialBlockTest, CheckDifferentialBlockNullPtr) {
  ProtobufDifferentialBlock* protobufData = nullptr;
  EXPECT_THROW(this->differentialBlockNormal1.serialize(protobufData), std::invalid_argument);
}
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
#include "DifferentialBlockExampleFactory.h"

class DifferentialBlockTest : public ::testing::Test {
 protected:
  DifferentialValues differentialValuesEmpty = DifferentialValuesExampleFactory::differentialValuesEmpty();
  DifferentialValues differentialValuesOneElement = DifferentialValuesExampleFactory::differentialValuesOneElement();
  DifferentialValues differentialValuesWithThreePositiveElements = DifferentialValuesExampleFactory::differentialValuesWithThreePositiveElements();
  DifferentialValues differentialValuesWithThreeNegativeElements = DifferentialValuesExampleFactory::differentialValuesWithThreeNegativeElements();
  DifferentialValues differentialValuesWithThreeMixedElements = DifferentialValuesExampleFactory::differentialValuesWithThreeMixedElements();
};

TEST_F(DifferentialBlockTest, TestGetWithDifferentialBlockWithThreePositiveDifferentialValues) {
  DifferentialBlock differentialBlock = DifferentialBlockExampleFactory::differentialBlockWithThreePositiveDifferentialValues();
  EXPECT_EQ(differentialBlock.getDifferentialValues(), this->differentialValuesWithThreePositiveElements);
}

TEST_F(DifferentialBlockTest, TestGetWithDifferentialBlockWithEmptyDifferentialValues) {
  DifferentialBlock differentialBlock = DifferentialBlockExampleFactory::differentialBlockWithEmptyDifferentialValues();
  EXPECT_EQ(differentialBlock.getDifferentialValues(), this->differentialValuesEmpty);
}

TEST_F(DifferentialBlockTest, CompareEqualBocks) {
  DifferentialBlock differentialBlock1 = DifferentialBlockExampleFactory::differentialBlockWithThreeMixedDifferentialValues();
  DifferentialBlock differentialBlock2 = DifferentialBlockExampleFactory::differentialBlockWithThreeMixedDifferentialValues();
  EXPECT_TRUE(differentialBlock1.isEqual(differentialBlock2));
}

TEST_F(DifferentialBlockTest, CompareNotEqualBlocks) {
  DifferentialBlock differentialBlock1 = DifferentialBlockExampleFactory::differentialBlockWithThreeMixedDifferentialValues();
  DifferentialBlock differentialBlock2 = DifferentialBlockExampleFactory::differentialBlockWithThreeNegativeDifferentialValues();
  EXPECT_FALSE(differentialBlock1.isEqual(differentialBlock2));
}

TEST_F(DifferentialBlockTest, CompareEmptyWithEmptyBlock) {
  DifferentialBlock differentialBlock1 = DifferentialBlockExampleFactory::differentialBlockWithEmptyDifferentialValues();
  DifferentialBlock differentialBlock2 = DifferentialBlockExampleFactory::differentialBlockWithEmptyDifferentialValues();
  EXPECT_TRUE(differentialBlock1.isEqual(differentialBlock2));
}

TEST_F(DifferentialBlockTest, CompareEmptyWithNormalBlock) {
  DifferentialBlock differentialBlock1 = DifferentialBlockExampleFactory::differentialBlockWithThreeMixedDifferentialValues();
  DifferentialBlock differentialBlock2 = DifferentialBlockExampleFactory::differentialBlockWithEmptyDifferentialValues();
  EXPECT_FALSE(differentialBlock1.isEqual(differentialBlock2));
}

TEST_F(DifferentialBlockTest, CompareBlocksWithDifferentSize) {
  DifferentialBlock differentialBlock1 = DifferentialBlockExampleFactory::differentialBlockWithThreeMixedDifferentialValues();
  DifferentialBlock differentialBlock2 = DifferentialBlockExampleFactory::differentialBlockWithOneDifferentialValues();
  EXPECT_FALSE(differentialBlock1.isEqual(differentialBlock2));
}

TEST_F(DifferentialBlockTest, TestSerializeNoThrow) {
  DifferentialBlock differentialBlock = DifferentialBlockExampleFactory::differentialBlockWithThreeMixedDifferentialValues();
  ProtobufDifferentialBlock protobufDifferentialBlocks;
  EXPECT_NO_THROW(differentialBlock.serialize(&protobufDifferentialBlocks));
}

TEST_F(DifferentialBlockTest, TestSerializeThrow) {
  DifferentialBlock differentialBlock = DifferentialBlockExampleFactory::differentialBlockWithThreeMixedDifferentialValues();
  ProtobufDifferentialBlock* protobufData = nullptr;
  EXPECT_THROW(differentialBlock.serialize(protobufData), std::invalid_argument);
}

TEST_F(DifferentialBlockTest, TestSerializeWithDifferentialBlockWithThreePositiveDifferentialValues) {
  DifferentialBlock differentialBlock1 = DifferentialBlockExampleFactory::differentialBlockWithThreePositiveDifferentialValues();
  ProtobufDifferentialBlock protobufDifferentialBlocks;
  differentialBlock1.serialize(&protobufDifferentialBlocks);
  DifferentialBlock differentialBlock2 = DifferentialBlock(protobufDifferentialBlocks);
  EXPECT_TRUE(differentialBlock1.isEqual(differentialBlock2));
}

TEST_F(DifferentialBlockTest, TestSerializeWithDifferentialBlockWithEmptyDifferentialValues) {
  DifferentialBlock differentialBlock1 = DifferentialBlockExampleFactory::differentialBlockWithEmptyDifferentialValues();
  ProtobufDifferentialBlock protobufDifferentialBlocks;
  differentialBlock1.serialize(&protobufDifferentialBlocks);
  DifferentialBlock differentialBlock2 = DifferentialBlock(protobufDifferentialBlocks);
  EXPECT_TRUE(differentialBlock1.isEqual(differentialBlock2));
}

TEST_F(DifferentialBlockTest, TestSerializeWithDifferentialBlockWithOneDifferentialValues) {
  DifferentialBlock differentialBlock1 = DifferentialBlockExampleFactory::differentialBlockWithOneDifferentialValues();
  ProtobufDifferentialBlock protobufDifferentialBlocks;
  differentialBlock1.serialize(&protobufDifferentialBlocks);
  DifferentialBlock differentialBlock2 = DifferentialBlock(protobufDifferentialBlocks);
  EXPECT_TRUE(differentialBlock1.isEqual(differentialBlock2));
}

TEST_F(DifferentialBlockTest, TestSerializeWithDifferentialBlockWithThreeNegativeDifferentialValues) {
  DifferentialBlock differentialBlock1 = DifferentialBlockExampleFactory::differentialBlockWithThreeNegativeDifferentialValues();
  ProtobufDifferentialBlock protobufDifferentialBlocks;
  differentialBlock1.serialize(&protobufDifferentialBlocks);
  DifferentialBlock differentialBlock2 = DifferentialBlock(protobufDifferentialBlocks);
  EXPECT_TRUE(differentialBlock1.isEqual(differentialBlock2));
}

TEST_F(DifferentialBlockTest, TestSerializeWithDifferentialBlockWithThreeMixedDifferentialValues) {
  DifferentialBlock differentialBlock1 = DifferentialBlockExampleFactory::differentialBlockWithThreeMixedDifferentialValues();
  ProtobufDifferentialBlock protobufDifferentialBlocks;
  differentialBlock1.serialize(&protobufDifferentialBlocks);
  DifferentialBlock differentialBlock2 = DifferentialBlock(protobufDifferentialBlocks);
  EXPECT_TRUE(differentialBlock1.isEqual(differentialBlock2));
}

TEST_F(DifferentialBlockTest, TestToJsonWith) {
  DifferentialBlock differentialBlock = DifferentialBlockExampleFactory::differentialBlockWithThreePositiveDifferentialValues();
  DifferentialBlockJson differentialBlockJson1 = differentialBlock.toJson();
  DifferentialValuesJson differentialValuesJson = DifferentialValuesExampleFactory::buildDifferentialValuesJson(this->differentialValuesWithThreePositiveElements);
  DifferentialBlockJson differentialBlockJson2 = DifferentialBlockExampleFactory::buildDifferentialBlockJson(differentialValuesJson);
  EXPECT_TRUE(differentialBlockJson1 == differentialBlockJson2);
}

TEST_F(DifferentialBlockTest, TestToJsonWith) {
  DifferentialBlock differentialBlock = DifferentialBlockExampleFactory::differentialBlockWithThreeMixedDifferentialValues();
  DifferentialBlockJson differentialBlockJson1 = differentialBlock.toJson();
  DifferentialValuesJson differentialValuesJson = DifferentialValuesExampleFactory::buildDifferentialValuesJson(this->differentialValuesWithThreeMixedElements);
  DifferentialBlockJson differentialBlockJson2 = DifferentialBlockExampleFactory::buildDifferentialBlockJson(differentialValuesJson);
  EXPECT_TRUE(differentialBlockJson1 == differentialBlockJson2);
}

TEST_F(DifferentialBlockTest, TestToJsonWith) {
  DifferentialBlock differentialBlock = DifferentialBlockExampleFactory::differentialBlockWithThreeNegativeDifferentialValues();
  DifferentialBlockJson differentialBlockJson1 = differentialBlock.toJson();
  DifferentialValuesJson differentialValuesJson = DifferentialValuesExampleFactory::buildDifferentialValuesJson(this->differentialValuesWithThreeNegativeElements);
  DifferentialBlockJson differentialBlockJson2 = DifferentialBlockExampleFactory::buildDifferentialBlockJson(differentialValuesJson);
  EXPECT_TRUE(differentialBlockJson1 == differentialBlockJson2);
}

TEST_F(DifferentialBlockTest, TestToJsonWith) {
  DifferentialBlock differentialBlock = DifferentialBlockExampleFactory::differentialBlockWithEmptyDifferentialValues();
  DifferentialBlockJson differentialBlockJson1 = differentialBlock.toJson();
  DifferentialValuesJson differentialValuesJson = DifferentialValuesExampleFactory::buildDifferentialValuesJson(this->differentialValuesEmpty);
  DifferentialBlockJson differentialBlockJson2 = DifferentialBlockExampleFactory::buildDifferentialBlockJson(differentialValuesJson);
  EXPECT_TRUE(differentialBlockJson1 == differentialBlockJson2);
}

TEST_F(DifferentialBlockTest, TestToJsonWith) {
  DifferentialBlock differentialBlock = DifferentialBlockExampleFactory::differentialBlockWithOneDifferentialValues();
  DifferentialBlockJson differentialBlockJson1 = differentialBlock.toJson();
  DifferentialValuesJson differentialValuesJson = DifferentialValuesExampleFactory::buildDifferentialValuesJson(this->differentialValuesOneElement);
  DifferentialBlockJson differentialBlockJson2 = DifferentialBlockExampleFactory::buildDifferentialBlockJson(differentialValuesJson);
  EXPECT_TRUE(differentialBlockJson1 == differentialBlockJson2);
}
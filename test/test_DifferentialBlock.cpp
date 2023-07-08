/*

Created by Jakob Glueck, Steve Merschel 2023

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

TEST(DifferentialBlockTest, TestGetWithDifferentialBlockWithThreePositiveDifferentialValues) {
  DifferentialBlock differentialBlock = DifferentialBlockExampleFactory::differentialBlockWithThreePositiveDifferentialValues();
  DifferentialValues differentialValues = DifferentialValuesExampleFactory::differentialValuesWithThreePositiveElements();
  EXPECT_EQ(differentialBlock.getDifferentialValues(), differentialValues);
}

TEST(DifferentialBlockTest, TestGetWithDifferentialBlockWithEmptyDifferentialValues) {
  DifferentialBlock differentialBlock = DifferentialBlockExampleFactory::differentialBlockWithEmptyDifferentialValues();
  DifferentialValues differentialValues = DifferentialValuesExampleFactory::differentialValuesEmpty();
  EXPECT_EQ(differentialBlock.getDifferentialValues(), differentialValues);
}

TEST(DifferentialBlockTest, TestIsEqualWithDifferentialBlockWithThreeMixedDifferentialValues) {
  DifferentialBlock differentialBlock1 = DifferentialBlockExampleFactory::differentialBlockWithThreeMixedDifferentialValues();
  DifferentialBlock differentialBlock2 = DifferentialBlockExampleFactory::differentialBlockWithThreeMixedDifferentialValues();
  EXPECT_TRUE(differentialBlock1.isEqual(differentialBlock2));
}

TEST(DifferentialBlockTest, TestIsEqualWithdifferentialBlockWithThreeMixedDifferentialValuesAndThreeNegativeDifferentialValues) {
  DifferentialBlock differentialBlock1 = DifferentialBlockExampleFactory::differentialBlockWithThreeMixedDifferentialValues();
  DifferentialBlock differentialBlock2 = DifferentialBlockExampleFactory::differentialBlockWithThreeNegativeDifferentialValues();
  EXPECT_FALSE(differentialBlock1.isEqual(differentialBlock2));
}

TEST(DifferentialBlockTest, TestIsEmptyWithEmptyBlock) {
  DifferentialBlock differentialBlock1 = DifferentialBlockExampleFactory::differentialBlockWithEmptyDifferentialValues();
  DifferentialBlock differentialBlock2 = DifferentialBlockExampleFactory::differentialBlockWithEmptyDifferentialValues();
  EXPECT_TRUE(differentialBlock1.isEqual(differentialBlock2));
}

TEST(DifferentialBlockTest, TestIsEmptyWithDifferentialBlockWithThreeMixedDifferentialValuesAndEmptyBlock) {
  DifferentialBlock differentialBlock1 = DifferentialBlockExampleFactory::differentialBlockWithThreeMixedDifferentialValues();
  DifferentialBlock differentialBlock2 = DifferentialBlockExampleFactory::differentialBlockWithEmptyDifferentialValues();
  EXPECT_FALSE(differentialBlock1.isEqual(differentialBlock2));
}

TEST(DifferentialBlockTest, TestIsBlocksWithDifferentSize) {
  DifferentialBlock differentialBlock1 = DifferentialBlockExampleFactory::differentialBlockWithThreeMixedDifferentialValues();
  DifferentialBlock differentialBlock2 = DifferentialBlockExampleFactory::differentialBlockWithOneDifferentialValues();
  EXPECT_FALSE(differentialBlock1.isEqual(differentialBlock2));
}

TEST(DifferentialBlockTest, TestSerializeNoThrow) {
  DifferentialBlock differentialBlock = DifferentialBlockExampleFactory::differentialBlockWithThreeMixedDifferentialValues();
  ProtobufDifferentialBlock protobufDifferentialBlocks;
  EXPECT_NO_THROW(differentialBlock.serialize(&protobufDifferentialBlocks));
}

TEST(DifferentialBlockTest, TestSerializeThrow) {
  DifferentialBlock differentialBlock = DifferentialBlockExampleFactory::differentialBlockWithThreeMixedDifferentialValues();
  ProtobufDifferentialBlock* protobufData = nullptr;
  EXPECT_THROW(differentialBlock.serialize(protobufData), std::invalid_argument);
}

TEST(DifferentialBlockTest, TestSerializeWithDifferentialBlockWithThreePositiveDifferentialValues) {
  DifferentialBlock differentialBlock1 = DifferentialBlockExampleFactory::differentialBlockWithThreePositiveDifferentialValues();
  ProtobufDifferentialBlock protobufDifferentialBlocks;
  differentialBlock1.serialize(&protobufDifferentialBlocks);
  DifferentialBlock differentialBlock2 = DifferentialBlock(protobufDifferentialBlocks);
  EXPECT_TRUE(differentialBlock1.isEqual(differentialBlock2));
}

TEST(DifferentialBlockTest, TestSerializeWithDifferentialBlockWithEmptyDifferentialValues) {
  DifferentialBlock differentialBlock1 = DifferentialBlockExampleFactory::differentialBlockWithEmptyDifferentialValues();
  ProtobufDifferentialBlock protobufDifferentialBlocks;
  differentialBlock1.serialize(&protobufDifferentialBlocks);
  DifferentialBlock differentialBlock2 = DifferentialBlock(protobufDifferentialBlocks);
  EXPECT_TRUE(differentialBlock1.isEqual(differentialBlock2));
}

TEST(DifferentialBlockTest, TestSerializeWithDifferentialBlockWithOneDifferentialValues) {
  DifferentialBlock differentialBlock1 = DifferentialBlockExampleFactory::differentialBlockWithOneDifferentialValues();
  ProtobufDifferentialBlock protobufDifferentialBlocks;
  differentialBlock1.serialize(&protobufDifferentialBlocks);
  DifferentialBlock differentialBlock2 = DifferentialBlock(protobufDifferentialBlocks);
  EXPECT_TRUE(differentialBlock1.isEqual(differentialBlock2));
}

TEST(DifferentialBlockTest, TestSerializeWithDifferentialBlockWithThreeNegativeDifferentialValues) {
  DifferentialBlock differentialBlock1 = DifferentialBlockExampleFactory::differentialBlockWithThreeNegativeDifferentialValues();
  ProtobufDifferentialBlock protobufDifferentialBlocks;
  differentialBlock1.serialize(&protobufDifferentialBlocks);
  DifferentialBlock differentialBlock2 = DifferentialBlock(protobufDifferentialBlocks);
  EXPECT_TRUE(differentialBlock1.isEqual(differentialBlock2));
}

TEST(DifferentialBlockTest, TestSerializeWithDifferentialBlockWithThreeMixedDifferentialValues) {
  DifferentialBlock differentialBlock1 = DifferentialBlockExampleFactory::differentialBlockWithThreeMixedDifferentialValues();
  ProtobufDifferentialBlock protobufDifferentialBlocks;
  differentialBlock1.serialize(&protobufDifferentialBlocks);
  DifferentialBlock differentialBlock2 = DifferentialBlock(protobufDifferentialBlocks);
  EXPECT_TRUE(differentialBlock1.isEqual(differentialBlock2));
}

TEST(DifferentialBlockTest, TestToJsonWithDifferentialBlockWithThreePositiveDifferentialValues) {
  DifferentialBlock differentialBlock = DifferentialBlockExampleFactory::differentialBlockWithThreePositiveDifferentialValues();
  DifferentialBlockJson differentialBlockJson1 = differentialBlock.toJson();
  DifferentialBlockJson differentialBlockJson2 = DifferentialBlockExampleFactory::buildDifferentialBlockJson(differentialBlock);
  EXPECT_TRUE(differentialBlockJson1.toStyledString() == differentialBlockJson2.toStyledString());
}

TEST(DifferentialBlockTest, TestToJsonWithDifferentialBlockWithThreeMixedDifferentialValues) {
  DifferentialBlock differentialBlock = DifferentialBlockExampleFactory::differentialBlockWithThreeMixedDifferentialValues();
  DifferentialBlockJson differentialBlockJson1 = differentialBlock.toJson();
  DifferentialBlockJson differentialBlockJson2 = DifferentialBlockExampleFactory::buildDifferentialBlockJson(differentialBlock);
  EXPECT_TRUE(differentialBlockJson1.toStyledString() == differentialBlockJson2.toStyledString());
}

TEST(DifferentialBlockTest, TestToJsonWithDifferentialBlockWithThreeNegativeDifferentialValues) {
  DifferentialBlock differentialBlock = DifferentialBlockExampleFactory::differentialBlockWithThreeNegativeDifferentialValues();
  DifferentialBlockJson differentialBlockJson1 = differentialBlock.toJson();
  DifferentialBlockJson differentialBlockJson2 = DifferentialBlockExampleFactory::buildDifferentialBlockJson(differentialBlock);
  EXPECT_TRUE(differentialBlockJson1.toStyledString() == differentialBlockJson2.toStyledString());
}

TEST(DifferentialBlockTest, TestToJsonWithDifferentialBlockWithEmptyDifferentialValues) {
  DifferentialBlock differentialBlock = DifferentialBlockExampleFactory::differentialBlockWithEmptyDifferentialValues();
  DifferentialBlockJson differentialBlockJson1 = differentialBlock.toJson();
  DifferentialBlockJson differentialBlockJson2 = DifferentialBlockExampleFactory::buildDifferentialBlockJson(differentialBlock);
  EXPECT_TRUE(differentialBlockJson1.toStyledString() == differentialBlockJson2.toStyledString());
}

TEST(DifferentialBlockTest, TestToJsonWithDifferentialBlockWithOneDifferentialValues) {
  DifferentialBlock differentialBlock = DifferentialBlockExampleFactory::differentialBlockWithOneDifferentialValues();
  DifferentialBlockJson differentialBlockJson1 = differentialBlock.toJson();
  DifferentialBlockJson differentialBlockJson2 = DifferentialBlockExampleFactory::buildDifferentialBlockJson(differentialBlock);
  EXPECT_TRUE(differentialBlockJson1.toStyledString() == differentialBlockJson2.toStyledString());
}

TEST(DifferentialBlockTest, TestIsSetWithDifferentialBlockWithOneDifferentialValues) {
  DifferentialBlock differentialBlock = DifferentialBlockExampleFactory::differentialBlockWithOneDifferentialValues();
  EXPECT_TRUE(differentialBlock.isSet());
}

TEST(DifferentialBlockTest, TestIsSetWithDifferentialBlockWithEmptyDifferentialValues) {
  DifferentialBlock differentialBlock = DifferentialBlockExampleFactory::differentialBlockWithEmptyDifferentialValues();
  EXPECT_FALSE(differentialBlock.isSet());
}
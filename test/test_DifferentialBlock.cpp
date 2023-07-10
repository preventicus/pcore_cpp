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
  auto differentialBlock = DifferentialBlockExampleFactory::differentialBlockWithThreePositiveDifferentialValues();
  auto differentialValues = DifferentialValuesExampleFactory::differentialValuesWithThreePositiveElements();
  EXPECT_EQ(differentialBlock.getDifferentialValues(), differentialValues);
}

TEST(DifferentialBlockTest, TestGetWithDifferentialBlockWithEmptyDifferentialValues) {
  auto differentialBlock = DifferentialBlockExampleFactory::differentialBlockWithEmptyDifferentialValues();
  auto differentialValues = DifferentialValuesExampleFactory::differentialValuesEmpty();
  EXPECT_EQ(differentialBlock.getDifferentialValues(), differentialValues);
}

TEST(DifferentialBlockTest, TestIsEqualWithDifferentialBlockWithThreeMixedDifferentialValues) {
  auto differentialBlock1 = DifferentialBlockExampleFactory::differentialBlockWithThreeMixedDifferentialValues();
  auto differentialBlock2 = DifferentialBlockExampleFactory::differentialBlockWithThreeMixedDifferentialValues();
  EXPECT_TRUE(differentialBlock1 == differentialBlock2);
}

TEST(DifferentialBlockTest, TestIsEqualWithdifferentialBlockWithThreeMixedDifferentialValuesAndThreeNegativeDifferentialValues) {
  auto differentialBlock1 = DifferentialBlockExampleFactory::differentialBlockWithThreeMixedDifferentialValues();
  auto differentialBlock2 = DifferentialBlockExampleFactory::differentialBlockWithThreeNegativeDifferentialValues();
  EXPECT_FALSE(differentialBlock1 == differentialBlock2);
}

TEST(DifferentialBlockTest, TestIsEqualWithEmptyBlock) {
  auto differentialBlock1 = DifferentialBlockExampleFactory::differentialBlockWithEmptyDifferentialValues();
  auto differentialBlock2 = DifferentialBlockExampleFactory::differentialBlockWithEmptyDifferentialValues();
  EXPECT_TRUE(differentialBlock1 == differentialBlock2);
}

TEST(DifferentialBlockTest, TestIsEqualWithDifferentialBlockWithThreeMixedDifferentialValuesAndEmptyBlock) {
  auto differentialBlock1 = DifferentialBlockExampleFactory::differentialBlockWithThreeMixedDifferentialValues();
  auto differentialBlock2 = DifferentialBlockExampleFactory::differentialBlockWithEmptyDifferentialValues();
  EXPECT_FALSE(differentialBlock1 == differentialBlock2);
}

TEST(DifferentialBlockTest, TestIsEqualWithBlocksWithDifferentSize) {
  auto differentialBlock1 = DifferentialBlockExampleFactory::differentialBlockWithThreeMixedDifferentialValues();
  auto differentialBlock2 = DifferentialBlockExampleFactory::differentialBlockWithOneDifferentialValues();
  EXPECT_FALSE(differentialBlock1 == differentialBlock2);
}

TEST(DifferentialBlockTest, TestIsNotEqualWithDifferentialBlockWithThreeMixedDifferentialValues) {
  auto differentialBlock1 = DifferentialBlockExampleFactory::differentialBlockWithThreeMixedDifferentialValues();
  auto differentialBlock2 = DifferentialBlockExampleFactory::differentialBlockWithThreeMixedDifferentialValues();
  EXPECT_FALSE(differentialBlock1 != differentialBlock2);
}

TEST(DifferentialBlockTest, TestIsNotEqualWithdifferentialBlockWithThreeMixedDifferentialValuesAndThreeNegativeDifferentialValues) {
  auto differentialBlock1 = DifferentialBlockExampleFactory::differentialBlockWithThreeMixedDifferentialValues();
  auto differentialBlock2 = DifferentialBlockExampleFactory::differentialBlockWithThreeNegativeDifferentialValues();
  EXPECT_TRUE(differentialBlock1 != differentialBlock2);
}

TEST(DifferentialBlockTest, TestIsNotEqualWithEmptyBlock) {
  auto differentialBlock1 = DifferentialBlockExampleFactory::differentialBlockWithEmptyDifferentialValues();
  auto differentialBlock2 = DifferentialBlockExampleFactory::differentialBlockWithEmptyDifferentialValues();
  EXPECT_FALSE(differentialBlock1 != differentialBlock2);
}

TEST(DifferentialBlockTest, TestIsNotEqualWithDifferentialBlockWithThreeMixedDifferentialValuesAndEmptyBlock) {
  auto differentialBlock1 = DifferentialBlockExampleFactory::differentialBlockWithThreeMixedDifferentialValues();
  auto differentialBlock2 = DifferentialBlockExampleFactory::differentialBlockWithEmptyDifferentialValues();
  EXPECT_TRUE(differentialBlock1 != differentialBlock2);
}

TEST(DifferentialBlockTest, TestIsNotEqualWithBlocksWithDifferentSize) {
  auto differentialBlock1 = DifferentialBlockExampleFactory::differentialBlockWithThreeMixedDifferentialValues();
  auto differentialBlock2 = DifferentialBlockExampleFactory::differentialBlockWithOneDifferentialValues();
  EXPECT_TRUE(differentialBlock1 != differentialBlock2);
}

TEST(DifferentialBlockTest, TestSerializeNoThrow) {
  auto differentialBlock = DifferentialBlockExampleFactory::differentialBlockWithThreeMixedDifferentialValues();
  DifferentialBlockProtobuf differentialBlockProtobuf;
  EXPECT_NO_THROW(differentialBlock.serialize(&differentialBlockProtobuf));
}

TEST(DifferentialBlockTest, TestSerializeThrow) {
  auto differentialBlock = DifferentialBlockExampleFactory::differentialBlockWithThreeMixedDifferentialValues();
  DifferentialBlockProtobuf* differentialBlockProtobuf = nullptr;
  EXPECT_THROW(differentialBlock.serialize(differentialBlockProtobuf), std::invalid_argument);
}

TEST(DifferentialBlockTest, TestSerializeWithDifferentialBlockWithThreePositiveDifferentialValues) {
  auto differentialBlock1 = DifferentialBlockExampleFactory::differentialBlockWithThreePositiveDifferentialValues();
  DifferentialBlockProtobuf differentialBlockProtobuf;
  differentialBlock1.serialize(&differentialBlockProtobuf);
  auto differentialBlock2 = DifferentialBlock(differentialBlockProtobuf);
  EXPECT_TRUE(differentialBlock1 == differentialBlock2);
}

TEST(DifferentialBlockTest, TestSerializeWithDifferentialBlockWithEmptyDifferentialValues) {
  auto differentialBlock1 = DifferentialBlockExampleFactory::differentialBlockWithEmptyDifferentialValues();
  DifferentialBlockProtobuf differentialBlockProtobuf;
  differentialBlock1.serialize(&differentialBlockProtobuf);
  auto differentialBlock2 = DifferentialBlock(differentialBlockProtobuf);
  EXPECT_TRUE(differentialBlock1 == differentialBlock2);
}

TEST(DifferentialBlockTest, TestSerializeWithDifferentialBlockWithOneDifferentialValues) {
  auto differentialBlock1 = DifferentialBlockExampleFactory::differentialBlockWithOneDifferentialValues();
  DifferentialBlockProtobuf differentialBlockProtobuf;
  differentialBlock1.serialize(&differentialBlockProtobuf);
  auto differentialBlock2 = DifferentialBlock(differentialBlockProtobuf);
  EXPECT_TRUE(differentialBlock1 == differentialBlock2);
}

TEST(DifferentialBlockTest, TestSerializeWithDifferentialBlockWithThreeNegativeDifferentialValues) {
  auto differentialBlock1 = DifferentialBlockExampleFactory::differentialBlockWithThreeNegativeDifferentialValues();
  DifferentialBlockProtobuf differentialBlockProtobuf;
  differentialBlock1.serialize(&differentialBlockProtobuf);
  auto differentialBlock2 = DifferentialBlock(differentialBlockProtobuf);
  EXPECT_TRUE(differentialBlock1 == differentialBlock2);
}

TEST(DifferentialBlockTest, TestSerializeWithDifferentialBlockWithThreeMixedDifferentialValues) {
  auto differentialBlock1 = DifferentialBlockExampleFactory::differentialBlockWithThreeMixedDifferentialValues();
  DifferentialBlockProtobuf differentialBlockProtobuf;
  differentialBlock1.serialize(&differentialBlockProtobuf);
  auto differentialBlock2 = DifferentialBlock(differentialBlockProtobuf);
  EXPECT_TRUE(differentialBlock1 == differentialBlock2);
}

TEST(DifferentialBlockTest, TestToJsonWithDifferentialBlockWithThreePositiveDifferentialValues) {
  auto differentialBlock = DifferentialBlockExampleFactory::differentialBlockWithThreePositiveDifferentialValues();
  auto differentialBlockJson1 = differentialBlock.toJson();
  auto differentialBlockJson2 = DifferentialBlockExampleFactory::buildDifferentialBlockJson(differentialBlock);
  EXPECT_TRUE(differentialBlockJson1.toStyledString() == differentialBlockJson2.toStyledString());
}

TEST(DifferentialBlockTest, TestToJsonWithDifferentialBlockWithThreeMixedDifferentialValues) {
  auto differentialBlock = DifferentialBlockExampleFactory::differentialBlockWithThreeMixedDifferentialValues();
  auto differentialBlockJson1 = differentialBlock.toJson();
  auto differentialBlockJson2 = DifferentialBlockExampleFactory::buildDifferentialBlockJson(differentialBlock);
  EXPECT_TRUE(differentialBlockJson1.toStyledString() == differentialBlockJson2.toStyledString());
}

TEST(DifferentialBlockTest, TestToJsonWithDifferentialBlockWithThreeNegativeDifferentialValues) {
  auto differentialBlock = DifferentialBlockExampleFactory::differentialBlockWithThreeNegativeDifferentialValues();
  auto differentialBlockJson1 = differentialBlock.toJson();
  auto differentialBlockJson2 = DifferentialBlockExampleFactory::buildDifferentialBlockJson(differentialBlock);
  EXPECT_TRUE(differentialBlockJson1.toStyledString() == differentialBlockJson2.toStyledString());
}

TEST(DifferentialBlockTest, TestToJsonWithDifferentialBlockWithEmptyDifferentialValues) {
  auto differentialBlock = DifferentialBlockExampleFactory::differentialBlockWithEmptyDifferentialValues();
  auto differentialBlockJson1 = differentialBlock.toJson();
  auto differentialBlockJson2 = DifferentialBlockExampleFactory::buildDifferentialBlockJson(differentialBlock);
  EXPECT_TRUE(differentialBlockJson1.toStyledString() == differentialBlockJson2.toStyledString());
}

TEST(DifferentialBlockTest, TestToJsonWithDifferentialBlockWithOneDifferentialValues) {
  auto differentialBlock = DifferentialBlockExampleFactory::differentialBlockWithOneDifferentialValues();
  auto differentialBlockJson1 = differentialBlock.toJson();
  auto differentialBlockJson2 = DifferentialBlockExampleFactory::buildDifferentialBlockJson(differentialBlock);
  EXPECT_TRUE(differentialBlockJson1.toStyledString() == differentialBlockJson2.toStyledString());
}

TEST(DifferentialBlockTest, TestIsSetWithDifferentialBlockWithOneDifferentialValues) {
  auto differentialBlock = DifferentialBlockExampleFactory::differentialBlockWithOneDifferentialValues();
  EXPECT_TRUE(differentialBlock.isSet());
}

TEST(DifferentialBlockTest, TestIsSetWithDifferentialBlockWithEmptyDifferentialValues) {
  auto differentialBlock = DifferentialBlockExampleFactory::differentialBlockWithEmptyDifferentialValues();
  EXPECT_FALSE(differentialBlock.isSet());
}
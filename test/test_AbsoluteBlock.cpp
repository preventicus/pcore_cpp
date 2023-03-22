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

#include "AbsoluteBlockExampleFactory.h"
#include "gtest/gtest.h"

class AbsoluteBlockTest : public ::testing::Test {
 protected:
};

TEST_F(AbsoluteBlockTest, TestGetWithAbsoluteBlockWithThreePositiveAbsoluteValues) {
  AbsoluteBlock absoluteBlock = AbsoluteBlockExampleFactory::absoluteBlockWithThreePositiveAbsoluteValues();
  AbsoluteValues absoluteValues = AbsoluteValuesExampleFactory::absoluteValuesWithThreePositiveElements();
  EXPECT_EQ(absoluteBlock.getAbsoluteValues(), absoluteValues);
}

TEST_F(AbsoluteBlockTest, TestGetWithAbsoluteBlockWithEmptyAbsoluteValue) {
  AbsoluteBlock absoluteBlock = AbsoluteBlockExampleFactory::absoluteBlockWithEmptyAbsoluteValue();
  AbsoluteValues absoluteValues = AbsoluteValuesExampleFactory::absoluteValuesEmpty();
  EXPECT_EQ(absoluteBlock.getAbsoluteValues(), absoluteValues);
}

TEST_F(AbsoluteBlockTest, CompareEqualNormalBlocks) {
  AbsoluteBlock absoluteBlock1 = AbsoluteBlockExampleFactory::absoluteBlockWithThreeMixedAbsoluteValues();
  AbsoluteBlock absoluteBlock2 = AbsoluteBlockExampleFactory::absoluteBlockWithThreeMixedAbsoluteValues();
  EXPECT_TRUE(absoluteBlock1.isEqual(absoluteBlock2));
}

TEST_F(AbsoluteBlockTest, CompareNotEqualNormalBlocks) {
  AbsoluteBlock absoluteBlock1 = AbsoluteBlockExampleFactory::absoluteBlockWithThreeMixedAbsoluteValues();
  AbsoluteBlock absoluteBlock2 = AbsoluteBlockExampleFactory::absoluteBlockWithThreeNegativeAbsoluteValues();
  EXPECT_FALSE(absoluteBlock1.isEqual(absoluteBlock2));
}

TEST_F(AbsoluteBlockTest, CompareEmptyWithEmptyBlocks) {
  AbsoluteBlock absoluteBlock1 = AbsoluteBlockExampleFactory::absoluteBlockWithEmptyAbsoluteValue();
  AbsoluteBlock absoluteBlock2 = AbsoluteBlockExampleFactory::absoluteBlockWithEmptyAbsoluteValue();
  EXPECT_TRUE(absoluteBlock1.isEqual(absoluteBlock2));
}

TEST_F(AbsoluteBlockTest, CompareEmptyWithAbsoluteBlocks) {
  AbsoluteBlock absoluteBlock1 = AbsoluteBlockExampleFactory::absoluteBlockWithThreeMixedAbsoluteValues();
  AbsoluteBlock absoluteBlock2 = AbsoluteBlockExampleFactory::absoluteBlockWithEmptyAbsoluteValue();
  EXPECT_FALSE(absoluteBlock1.isEqual(absoluteBlock2));
}

TEST_F(AbsoluteBlockTest, CompareBlocksWithDifferentSize) {
  AbsoluteBlock absoluteBlock1 = AbsoluteBlockExampleFactory::absoluteBlockWithThreeMixedAbsoluteValues();
  AbsoluteBlock absoluteBlock2 = AbsoluteBlockExampleFactory::absoluteBlockWithOneAbsoluteValue();
  EXPECT_FALSE(absoluteBlock1.isEqual(absoluteBlock2));
}

TEST_F(AbsoluteBlockTest, TestToJsonWithAbsoluteValuesWithThreePositiveElements) {
  AbsoluteBlock absoluteBlock = AbsoluteBlockExampleFactory::absoluteBlockWithThreePositiveAbsoluteValues();
  AbsoluteBlockJson absoluteBlockJson1 = absoluteBlock.toJson();
  AbsoluteBlockJson absoluteBlockJson2 = AbsoluteBlockExampleFactory::buildAbsoluteBlockJson(absoluteBlock);
  EXPECT_TRUE(absoluteBlockJson1 == absoluteBlockJson2);
}

TEST_F(AbsoluteBlockTest, TestToJsonWithAbsoluteValuesEmpty) {
  AbsoluteBlock absoluteBlock = AbsoluteBlockExampleFactory::absoluteBlockWithEmptyAbsoluteValue();
  AbsoluteBlockJson absoluteBlockJson1 = absoluteBlock.toJson();
  AbsoluteBlockJson absoluteBlockJson2 = AbsoluteBlockExampleFactory::buildAbsoluteBlockJson(absoluteBlock);
  EXPECT_TRUE(absoluteBlockJson1 == absoluteBlockJson2);
}

TEST_F(AbsoluteBlockTest, TestToJsonWithAbsoluteValuesWithOneElement) {
  AbsoluteBlock absoluteBlock = AbsoluteBlockExampleFactory::absoluteBlockWithOneAbsoluteValue();
  AbsoluteBlockJson absoluteBlockJson1 = absoluteBlock.toJson();
  AbsoluteBlockJson absoluteBlockJson2 = AbsoluteBlockExampleFactory::buildAbsoluteBlockJson(absoluteBlock);
  EXPECT_TRUE(absoluteBlockJson1 == absoluteBlockJson2);
}

TEST_F(AbsoluteBlockTest, TestToJsonWithAbsoluteValuesWithThreeMixedElements) {
  AbsoluteBlock absoluteBlock = AbsoluteBlockExampleFactory::absoluteBlockWithThreeMixedAbsoluteValues();
  AbsoluteBlockJson absoluteBlockJson1 = absoluteBlock.toJson();
  AbsoluteBlockJson absoluteBlockJson2 = AbsoluteBlockExampleFactory::buildAbsoluteBlockJson(absoluteBlock);
  EXPECT_TRUE(absoluteBlockJson1 == absoluteBlockJson2);
}

TEST_F(AbsoluteBlockTest, TestToJsonWithAbsoluteValuesWithThreeNegativeElements) {
  AbsoluteBlock absoluteBlock = AbsoluteBlockExampleFactory::absoluteBlockWithThreeNegativeAbsoluteValues();
  AbsoluteBlockJson absoluteBlockJson1 = absoluteBlock.toJson();
  AbsoluteBlockJson absoluteBlockJson2 = AbsoluteBlockExampleFactory::buildAbsoluteBlockJson(absoluteBlock);
  EXPECT_TRUE(absoluteBlockJson1 == absoluteBlockJson2);
}

TEST_F(AbsoluteBlockTest, TestIsSetWithAbsoluteBlockWithOneAbsoluteValue) {
  AbsoluteBlock absoluteBlock = AbsoluteBlockExampleFactory::absoluteBlockWithOneAbsoluteValue();
  EXPECT_TRUE(absoluteBlock.isSet());
}

TEST_F(AbsoluteBlockTest, TestIsSetWithAbsoluteBlockWithEmptyAbsoluteValue) {
  AbsoluteBlock absoluteBlock = AbsoluteBlockExampleFactory::absoluteBlockWithEmptyAbsoluteValue();
  EXPECT_FALSE(absoluteBlock.isSet());
}

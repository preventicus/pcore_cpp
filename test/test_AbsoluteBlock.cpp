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

#include "AbsoluteBlockExampleFactory.h"
#include "gtest/gtest.h"

TEST(AbsoluteBlockTest, TestGetWithAbsoluteBlockWithThreePositiveAbsoluteValues) {
  auto absoluteBlock = AbsoluteBlockExampleFactory::absoluteBlockWithThreePositiveAbsoluteValues();
  auto absoluteValues = AbsoluteValuesExampleFactory::absoluteValuesWithThreePositiveElements();
  EXPECT_EQ(absoluteBlock.getAbsoluteValues(), absoluteValues);
}

TEST(AbsoluteBlockTest, TestGetWithAbsoluteBlockNotSet) {
  auto absoluteBlock = AbsoluteBlockExampleFactory::absoluteBlockNotSet();
  auto absoluteValues = AbsoluteValuesExampleFactory::absoluteValuesNotSet();
  EXPECT_EQ(absoluteBlock.getAbsoluteValues(), absoluteValues);
}

TEST(AbsoluteBlockTest, TestIsEqualWithThreeMixedAbsoluteValues) {
  auto absoluteBlock1 = AbsoluteBlockExampleFactory::absoluteBlockWithThreeMixedAbsoluteValues();
  auto absoluteBlock2 = AbsoluteBlockExampleFactory::absoluteBlockWithThreeMixedAbsoluteValues();
  EXPECT_TRUE(absoluteBlock1 == absoluteBlock2);
}

TEST(AbsoluteBlockTest, TestIsEqualWithThreeMixedAbsoluteValuesAndThreeNegativeAbsoluteValues) {
  auto absoluteBlock1 = AbsoluteBlockExampleFactory::absoluteBlockWithThreeMixedAbsoluteValues();
  auto absoluteBlock2 = AbsoluteBlockExampleFactory::absoluteBlockWithThreeNegativeAbsoluteValues();
  EXPECT_FALSE(absoluteBlock1 == absoluteBlock2);
}

TEST(AbsoluteBlockTest, TestIsEqualWithAbsoluteBlockNotSet) {
  auto absoluteBlock1 = AbsoluteBlockExampleFactory::absoluteBlockNotSet();
  auto absoluteBlock2 = AbsoluteBlockExampleFactory::absoluteBlockNotSet();
  EXPECT_TRUE(absoluteBlock1 == absoluteBlock2);
}

TEST(AbsoluteBlockTest, TestIsEqualWithThreeMixedAbsoluteValuesAndAbsoluteBlockNotSet) {
  auto absoluteBlock1 = AbsoluteBlockExampleFactory::absoluteBlockWithThreeMixedAbsoluteValues();
  auto absoluteBlock2 = AbsoluteBlockExampleFactory::absoluteBlockNotSet();
  EXPECT_FALSE(absoluteBlock1 == absoluteBlock2);
}

TEST(AbsoluteBlockTest, TestIsEqualWithThreeMixedAbsoluteValuesAndOneAbsoluteValue) {
  auto absoluteBlock1 = AbsoluteBlockExampleFactory::absoluteBlockWithThreeMixedAbsoluteValues();
  auto absoluteBlock2 = AbsoluteBlockExampleFactory::absoluteBlockWithOneAbsoluteValue();
  EXPECT_FALSE(absoluteBlock1 == absoluteBlock2);
}

TEST(AbsoluteBlockTest, TestIsNotEqualWithThreeMixedAbsoluteValues) {
  auto absoluteBlock1 = AbsoluteBlockExampleFactory::absoluteBlockWithThreeMixedAbsoluteValues();
  auto absoluteBlock2 = AbsoluteBlockExampleFactory::absoluteBlockWithThreeMixedAbsoluteValues();
  EXPECT_FALSE(absoluteBlock1 != absoluteBlock2);
}

TEST(AbsoluteBlockTest, TestIsNotEqualWithThreeMixedAbsoluteValuesAndThreeNegativeAbsoluteValues) {
  auto absoluteBlock1 = AbsoluteBlockExampleFactory::absoluteBlockWithThreeMixedAbsoluteValues();
  auto absoluteBlock2 = AbsoluteBlockExampleFactory::absoluteBlockWithThreeNegativeAbsoluteValues();
  EXPECT_TRUE(absoluteBlock1 != absoluteBlock2);
}

TEST(AbsoluteBlockTest, TestIsNotEqualWithAbsoluteBlockNotSet) {
  auto absoluteBlock1 = AbsoluteBlockExampleFactory::absoluteBlockNotSet();
  auto absoluteBlock2 = AbsoluteBlockExampleFactory::absoluteBlockNotSet();
  EXPECT_FALSE(absoluteBlock1 != absoluteBlock2);
}

TEST(AbsoluteBlockTest, TestIsNotEqualWithAbsoluteBlockWithThreeMixedAbsoluteValuesAndAbsoluteBlockNotSet) {
  auto absoluteBlock1 = AbsoluteBlockExampleFactory::absoluteBlockWithThreeMixedAbsoluteValues();
  auto absoluteBlock2 = AbsoluteBlockExampleFactory::absoluteBlockNotSet();
  EXPECT_TRUE(absoluteBlock1 != absoluteBlock2);
}

TEST(AbsoluteBlockTest, TestIsNotEqualWithThreeMixedAbsoluteValuesAndOneAbsoluteValue) {
  auto absoluteBlock1 = AbsoluteBlockExampleFactory::absoluteBlockWithThreeMixedAbsoluteValues();
  auto absoluteBlock2 = AbsoluteBlockExampleFactory::absoluteBlockWithOneAbsoluteValue();
  EXPECT_TRUE(absoluteBlock1 != absoluteBlock2);
}

TEST(AbsoluteBlockTest, TestToJsonWithAbsoluteValuesWithThreePositiveElements) {
  auto absoluteBlock = AbsoluteBlockExampleFactory::absoluteBlockWithThreePositiveAbsoluteValues();
  auto absoluteBlockJson1 = absoluteBlock.toJson();
  auto absoluteBlockJson2 = AbsoluteBlockExampleFactory::buildAbsoluteBlockJson(absoluteBlock);
  EXPECT_TRUE(absoluteBlockJson1.toStyledString() == absoluteBlockJson2.toStyledString());
}

TEST(AbsoluteBlockTest, TestToJsonWithAbsoluteBlockNotSet) {
  auto absoluteBlock = AbsoluteBlockExampleFactory::absoluteBlockNotSet();
  auto absoluteBlockJson1 = absoluteBlock.toJson();
  auto absoluteBlockJson2 = AbsoluteBlockExampleFactory::buildAbsoluteBlockJson(absoluteBlock);
  EXPECT_TRUE(absoluteBlockJson1.toStyledString() == absoluteBlockJson2.toStyledString());
}

TEST(AbsoluteBlockTest, TestToJsonWithAbsoluteValuesWithOneElement) {
  auto absoluteBlock = AbsoluteBlockExampleFactory::absoluteBlockWithOneAbsoluteValue();
  auto absoluteBlockJson1 = absoluteBlock.toJson();
  auto absoluteBlockJson2 = AbsoluteBlockExampleFactory::buildAbsoluteBlockJson(absoluteBlock);
  EXPECT_TRUE(absoluteBlockJson1.toStyledString() == absoluteBlockJson2.toStyledString());
}

TEST(AbsoluteBlockTest, TestToJsonWithAbsoluteValuesWithThreeMixedElements) {
  auto absoluteBlock = AbsoluteBlockExampleFactory::absoluteBlockWithThreeMixedAbsoluteValues();
  auto absoluteBlockJson1 = absoluteBlock.toJson();
  auto absoluteBlockJson2 = AbsoluteBlockExampleFactory::buildAbsoluteBlockJson(absoluteBlock);
  EXPECT_TRUE(absoluteBlockJson1.toStyledString() == absoluteBlockJson2.toStyledString());
}

TEST(AbsoluteBlockTest, TestToJsonWithAbsoluteValuesWithThreeNegativeElements) {
  auto absoluteBlock = AbsoluteBlockExampleFactory::absoluteBlockWithThreeNegativeAbsoluteValues();
  auto absoluteBlockJson1 = absoluteBlock.toJson();
  auto absoluteBlockJson2 = AbsoluteBlockExampleFactory::buildAbsoluteBlockJson(absoluteBlock);
  EXPECT_TRUE(absoluteBlockJson1.toStyledString() == absoluteBlockJson2.toStyledString());
}

TEST(AbsoluteBlockTest, TestIsSetWithAbsoluteBlockWithOneAbsoluteValue) {
  auto absoluteBlock = AbsoluteBlockExampleFactory::absoluteBlockWithOneAbsoluteValue();
  EXPECT_TRUE(absoluteBlock.isSet());
}

TEST(AbsoluteBlockTest, TestIsSetWithAbsoluteBlockNotSet) {
  auto absoluteBlock = AbsoluteBlockExampleFactory::absoluteBlockNotSet();
  EXPECT_FALSE(absoluteBlock.isSet());
}

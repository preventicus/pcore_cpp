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
  AbsoluteValues absoluteValuesNormal = AbsoluteValuesExampleFactory::absoluteValuesNormal();
  AbsoluteValues absoluteValuesEmpty = AbsoluteValuesExampleFactory::absoluteValuesEmpty();
  AbsoluteValues absoluteValuesOneElement = AbsoluteValuesExampleFactory::absoluteValuesOneElement();
  AbsoluteValues absoluteValuesNormalNegative = AbsoluteValuesExampleFactory::absoluteValuesNormalNegative();
};

TEST_F(AbsoluteBlockTest, TestGetAbsoluteValues) {
  AbsoluteBlock absoluteBlock = AbsoluteBlock(this->absoluteValuesNormal);
  EXPECT_EQ(absoluteBlock.getAbsoluteValues(), this->absoluteValuesNormal);
}

TEST_F(AbsoluteBlockTest, TestGetEmptyAbsoluteValues) {
  AbsoluteBlock absoluteBlock = AbsoluteBlock(this->absoluteValuesEmpty);
  EXPECT_EQ(absoluteBlock.getAbsoluteValues(), this->absoluteValuesEmpty);
}

TEST_F(AbsoluteBlockTest, CompareEqualNormalBlocks) {
  AbsoluteBlock absoluteBlock1 = AbsoluteBlock(this->absoluteValuesNormal);
  AbsoluteBlock absoluteBlock2 = AbsoluteBlock(this->absoluteValuesNormal);
  EXPECT_TRUE(absoluteBlock1.isEqual(absoluteBlock2));
}

TEST_F(AbsoluteBlockTest, CompareNotEqualNormalBlocks) {
  AbsoluteBlock absoluteBlock1 = AbsoluteBlock(this->absoluteValuesNormal);
  AbsoluteBlock absoluteBlock2 = AbsoluteBlock(this->absoluteValuesNormalNegative);
  EXPECT_FALSE(absoluteBlock1.isEqual(absoluteBlock2));
}

TEST_F(AbsoluteBlockTest, CompareEmptyWithEmptyBlocks) {
  AbsoluteBlock absoluteBlock1 = AbsoluteBlock(this->absoluteValuesEmpty);
  AbsoluteBlock absoluteBlock2 = AbsoluteBlock(this->absoluteValuesEmpty);
  EXPECT_TRUE(absoluteBlock1.isEqual(absoluteBlock2));
}

TEST_F(AbsoluteBlockTest, CompareEmptyWithNormalBlocks) {
  AbsoluteBlock absoluteBlock1 = AbsoluteBlock(this->absoluteValuesNormal);
  AbsoluteBlock absoluteBlock2 = AbsoluteBlock(this->absoluteValuesEmpty);
  EXPECT_FALSE(absoluteBlock1.isEqual(absoluteBlock2));
}

TEST_F(AbsoluteBlockTest, CompareBlocksWithDifferentSize) {
  AbsoluteBlock absoluteBlock1 = AbsoluteBlock(this->absoluteValuesNormal);
  AbsoluteBlock absoluteBlock2 = AbsoluteBlock(this->absoluteValuesOneElement);
  EXPECT_FALSE(absoluteBlock1.isEqual(absoluteBlock2));
}

TEST_F(AbsoluteBlockTest, TestToJson) {
  AbsoluteBlock absoluteBlockN1 = AbsoluteBlock(this->absoluteValuesNormal);
  AbsoluteBlock absoluteBlockE1 = AbsoluteBlock(this->absoluteValuesEmpty);
  AbsoluteBlock absoluteBlockO1 = AbsoluteBlock(this->absoluteValuesOneElement);
  AbsoluteBlock absoluteBlockNN1 = AbsoluteBlock(this->absoluteValuesNormalNegative);
  AbsoluteBlockJson absoluteBlockJsonN1 = absoluteBlockN1.toJson();
  AbsoluteBlockJson absoluteBlockJsonE1 = absoluteBlockE1.toJson();
  AbsoluteBlockJson absoluteBlockJsonO1 = absoluteBlockO1.toJson();
  AbsoluteBlockJson absoluteBlockJsonNN1 = absoluteBlockNN1.toJson();
  AbsoluteValuesJson absoluteValuesJsonN = AbsoluteValuesExampleFactory::buildAbsoluteValuesJson(this->absoluteValuesNormal);
  AbsoluteValuesJson absoluteValuesJsonE = AbsoluteValuesExampleFactory::buildAbsoluteValuesJson(this->absoluteValuesEmpty);
  AbsoluteValuesJson absoluteValuesJsonO = AbsoluteValuesExampleFactory::buildAbsoluteValuesJson(this->absoluteValuesOneElement);
  AbsoluteValuesJson absoluteValuesJsonNN = AbsoluteValuesExampleFactory::buildAbsoluteValuesJson(this->absoluteValuesNormalNegative);
  AbsoluteBlockJson absoluteBlockJsonN2 = AbsoluteBlockExampleFactory::buildAbsoluteBlockJson(absoluteValuesJsonN);
  AbsoluteBlockJson absoluteBlockJsonE2 = AbsoluteBlockExampleFactory::buildAbsoluteBlockJson(absoluteValuesJsonE);
  AbsoluteBlockJson absoluteBlockJsonO2 = AbsoluteBlockExampleFactory::buildAbsoluteBlockJson(absoluteValuesJsonO);
  AbsoluteBlockJson absoluteBlockJsonNN2 = AbsoluteBlockExampleFactory::buildAbsoluteBlockJson(absoluteValuesJsonNN);
  EXPECT_TRUE(absoluteBlockJsonN1 == absoluteBlockJsonN2);
  EXPECT_TRUE(absoluteBlockJsonE1 == absoluteBlockJsonE2);
  EXPECT_TRUE(absoluteBlockJsonO1 == absoluteBlockJsonO2);
  EXPECT_TRUE(absoluteBlockJsonNN1 == absoluteBlockJsonNN2);
}
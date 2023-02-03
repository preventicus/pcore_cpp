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
#include <vector>
#include "AbsoluteBlock.h"
#include "gtest/gtest.h"
class AbsoluteBlockTest : public ::testing::Test {
 protected:
  AbsoluteBlock absoluteBlockNormal1;
  AbsoluteBlock absoluteBlockNormal2;
  AbsoluteBlock absoluteBlockTwoElement1;
  AbsoluteBlock absoluteBlockTwoElement2;
  AbsoluteBlock absoluteBlockOneElement1;
  AbsoluteBlock absoluteBlockOneElement2;
  AbsoluteBlock absoluteBlock0Element1;
  AbsoluteBlock absoluteBlock0Element2;
  AbsoluteBlock absoluteBlockEmpty1;
  AbsoluteBlock absoluteBlockEmpty2;
  std::vector<int32_t> valuesNormal = {1, 2, 3};
  std::vector<int32_t> valuesTwoElements = {1, 2};
  std::vector<int32_t> valuesOneElement = {1};
  std::vector<int32_t> values0Element = {0};
  std::vector<int32_t> valuesEmpty = {};
  virtual void SetUp() {
    this->absoluteBlockNormal1 = AbsoluteBlock(this->valuesNormal);
    this->absoluteBlockNormal2 = AbsoluteBlock(this->valuesNormal);
    this->absoluteBlockTwoElement1 = AbsoluteBlock(this->valuesTwoElements);
    this->absoluteBlockTwoElement2 = AbsoluteBlock(this->valuesTwoElements);
    this->absoluteBlockOneElement1 = AbsoluteBlock(this->valuesOneElement);
    this->absoluteBlockOneElement2 = AbsoluteBlock(this->valuesOneElement);
    this->absoluteBlock0Element1 = AbsoluteBlock(this->values0Element);
    this->absoluteBlock0Element2 = AbsoluteBlock(this->values0Element);
    this->absoluteBlockEmpty1 = AbsoluteBlock(this->valuesEmpty);
    this->absoluteBlockEmpty2 = AbsoluteBlock(this->valuesEmpty);
  }
};

TEST_F(AbsoluteBlockTest, TestGetValues) {
  EXPECT_EQ(this->absoluteBlockNormal1.getValues(), this->valuesNormal);
}

TEST_F(AbsoluteBlockTest, TestGetEmptyValues) {
  EXPECT_EQ(this->absoluteBlockEmpty1.getValues(), this->valuesEmpty);
}

TEST_F(AbsoluteBlockTest, TestGet0Values) {
  EXPECT_EQ(this->absoluteBlock0Element1.getValues(), this->values0Element);
}

TEST_F(AbsoluteBlockTest, CompareEmptyAndFullBlocks) {
  EXPECT_FALSE(this->absoluteBlockNormal1.isEqual(this->absoluteBlockEmpty1));
}

TEST_F(AbsoluteBlockTest, CompareShortAndFullBlocks) {
  EXPECT_FALSE(this->absoluteBlockOneElement1.isEqual(this->absoluteBlockNormal1));
}

TEST_F(AbsoluteBlockTest, CompareSameContentBlocks) {
  EXPECT_TRUE(this->absoluteBlockNormal1.isEqual(this->absoluteBlockNormal2));
}

TEST_F(AbsoluteBlockTest, CompareFullAndShortBlocks) {
  EXPECT_FALSE(this->absoluteBlockNormal1.isEqual(this->absoluteBlockOneElement1));
}

TEST_F(AbsoluteBlockTest, CompareLongWithMediumBlocks) {
  EXPECT_FALSE(this->absoluteBlockNormal1.isEqual(this->absoluteBlockTwoElement1));
}

TEST_F(AbsoluteBlockTest, CompareEmptyWithEmptyBlocks) {
  EXPECT_TRUE(this->absoluteBlockEmpty1.isEqual(this->absoluteBlockEmpty2));
}

TEST_F(AbsoluteBlockTest, CompareZeroWithZeroBlocks) {
  EXPECT_TRUE(this->absoluteBlock0Element1.isEqual(this->absoluteBlock0Element2));
}

TEST_F(AbsoluteBlockTest, CompareEmptyWithZeroBlocks) {
  EXPECT_FALSE(this->absoluteBlock0Element1.isEqual(this->absoluteBlockEmpty1));
}

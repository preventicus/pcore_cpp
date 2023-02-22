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
  AbsoluteBlock absoluteBlockNormal1 = AbsoluteBlockExampleFactory::absoluteBlockNormal();
  AbsoluteBlock absoluteBlockNormal2 = AbsoluteBlockExampleFactory::absoluteBlockNormal();
  AbsoluteBlock absoluteBlockWithTwoElement1 = AbsoluteBlockExampleFactory::absoluteBlockTwoElement();
  AbsoluteBlock absoluteBlockWithTwoElement2 = AbsoluteBlockExampleFactory::absoluteBlockTwoElement();
  AbsoluteBlock absoluteBlockWithOneElement1 = AbsoluteBlockExampleFactory::absoluteBlockOneElement();
  AbsoluteBlock absoluteBlockWithOneElement2 = AbsoluteBlockExampleFactory::absoluteBlockOneElement();
  AbsoluteBlock absoluteBlockWith0Element1 = AbsoluteBlockExampleFactory::absoluteBlock0Element();
  AbsoluteBlock absoluteBlockWith0Element2 = AbsoluteBlockExampleFactory::absoluteBlock0Element();
  AbsoluteBlock absoluteBlockEmpty1 = AbsoluteBlockExampleFactory::absoluteBlockEmpty();
  AbsoluteBlock absoluteBlockEmpty2 = AbsoluteBlockExampleFactory::absoluteBlockEmpty();
};

TEST_F(AbsoluteBlockTest, TestGetValues) {
  EXPECT_EQ(this->absoluteBlockNormal1.getAbsoluteValues(), AbsoluteBlockExampleFactory::absoluteValuesNormal());
}

TEST_F(AbsoluteBlockTest, TestGetEmptyValues) {
  EXPECT_EQ(this->absoluteBlockEmpty1.getAbsoluteValues(), AbsoluteBlockExampleFactory::absoluteValuesEmpty());
}

TEST_F(AbsoluteBlockTest, TestGet0Values) {
  EXPECT_EQ(this->absoluteBlockWith0Element1.getAbsoluteValues(), AbsoluteBlockExampleFactory::absoluteValues0Element());
}

TEST_F(AbsoluteBlockTest, CompareEmptyAndFullBlocks) {
  EXPECT_FALSE(this->absoluteBlockNormal1.isEqual(this->absoluteBlockEmpty1));
}

TEST_F(AbsoluteBlockTest, CompareShortAndFullBlocks) {
  EXPECT_FALSE(this->absoluteBlockWithOneElement1.isEqual(this->absoluteBlockNormal1));
}

TEST_F(AbsoluteBlockTest, CompareSameContentBlocks) {
  EXPECT_TRUE(this->absoluteBlockNormal1.isEqual(this->absoluteBlockNormal2));
}

TEST_F(AbsoluteBlockTest, CompareFullAndShortBlocks) {
  EXPECT_FALSE(this->absoluteBlockNormal1.isEqual(this->absoluteBlockWithOneElement1));
}

TEST_F(AbsoluteBlockTest, CompareLongWithMediumBlocks) {
  EXPECT_FALSE(this->absoluteBlockNormal1.isEqual(this->absoluteBlockWithTwoElement1));
}

TEST_F(AbsoluteBlockTest, CompareEmptyWithEmptyBlocks) {
  EXPECT_TRUE(this->absoluteBlockEmpty1.isEqual(this->absoluteBlockEmpty2));
}

TEST_F(AbsoluteBlockTest, CompareZeroWithZeroBlocks) {
  EXPECT_TRUE(this->absoluteBlockWith0Element1.isEqual(this->absoluteBlockWith0Element2));
}

TEST_F(AbsoluteBlockTest, CompareEmptyWithZeroBlocks) {
  EXPECT_FALSE(this->absoluteBlockWith0Element1.isEqual(this->absoluteBlockEmpty1));
}

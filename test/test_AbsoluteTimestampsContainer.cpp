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
#include "AbsoluteTimestampsContainerExampleFactory.h"

class AbsoluteTimestampsContainerTest : public ::testing::Test {
 protected:
  AbsoluteTimestampsContainer absoluteTimestampsNormal1 = AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsNormal();
  AbsoluteTimestampsContainer absoluteTimestampsNormal2 = AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsNormal();
  AbsoluteTimestampsContainer absoluteTimestampsWithTwoElement1 = AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsTwoElement();
  AbsoluteTimestampsContainer absoluteTimestampsWithTwoElement2 = AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsTwoElement();
  AbsoluteTimestampsContainer absoluteTimestampsWithOneElement1 = AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsOneElement();
  AbsoluteTimestampsContainer absoluteTimestampsWithOneElement2 = AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsOneElement();
  AbsoluteTimestampsContainer absoluteTimestampsWith01 = AbsoluteTimestampsContainerExampleFactory::absoluteTimestamps0();
  AbsoluteTimestampsContainer absoluteTimestampsWith02 = AbsoluteTimestampsContainerExampleFactory::absoluteTimestamps0();
  AbsoluteTimestampsContainer absoluteTimestampsEmpty1 = AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsEmpty();
  AbsoluteTimestampsContainer absoluteTimestampsEmpty2 = AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsEmpty();
};

TEST_F(AbsoluteTimestampsContainerTest, TestGetUnixTimestamps) {
  EXPECT_EQ(this->absoluteTimestampsNormal1.getUnixTimestamps(), AbsoluteTimestampsContainerExampleFactory::unixTimestampsNormal_ms());
}

TEST_F(AbsoluteTimestampsContainerTest, TestGetEmptyUnixTimestamps) {
  EXPECT_EQ(this->absoluteTimestampsEmpty1.getUnixTimestamps(), AbsoluteTimestampsContainerExampleFactory::unixTimestampsEmpty_ms());
}

TEST_F(AbsoluteTimestampsContainerTest, TestGet0UnixTimestamps) {
  EXPECT_EQ(this->absoluteTimestampsWith01.getUnixTimestamps(), AbsoluteTimestampsContainerExampleFactory::unixTimestamps0_ms());
}

TEST_F(AbsoluteTimestampsContainerTest, CompareEmptyAndFullBlocks) {
  EXPECT_FALSE(this->absoluteTimestampsNormal1.isEqual(this->absoluteTimestampsEmpty1));
}

TEST_F(AbsoluteTimestampsContainerTest, CompareShortAndFullBlocks) {
  EXPECT_FALSE(this->absoluteTimestampsWithOneElement1.isEqual(this->absoluteTimestampsNormal1));
}

TEST_F(AbsoluteTimestampsContainerTest, CompareSameContentBlocks) {
  EXPECT_TRUE(this->absoluteTimestampsNormal1.isEqual(this->absoluteTimestampsNormal2));
}

TEST_F(AbsoluteTimestampsContainerTest, CompareFullAndOneBlocks) {
  EXPECT_FALSE(this->absoluteTimestampsNormal1.isEqual(this->absoluteTimestampsWithOneElement1));
}

TEST_F(AbsoluteTimestampsContainerTest, CompareFullAndShortBlocks) {
  EXPECT_FALSE(this->absoluteTimestampsNormal1.isEqual(this->absoluteTimestampsWithOneElement1));
}

TEST_F(AbsoluteTimestampsContainerTest, CompareEmptyWithEmptyBlocks) {
  EXPECT_TRUE(this->absoluteTimestampsEmpty1.isEqual(this->absoluteTimestampsEmpty2));
}

TEST_F(AbsoluteTimestampsContainerTest, CompareZeroWithZeroBlocks) {
  EXPECT_TRUE(this->absoluteTimestampsWith01.isEqual(this->absoluteTimestampsWith02));
}

TEST_F(AbsoluteTimestampsContainerTest, CompareEmptyWithZeroBlocks) {
  EXPECT_FALSE(this->absoluteTimestampsWith01.isEqual(this->absoluteTimestampsEmpty1));
}

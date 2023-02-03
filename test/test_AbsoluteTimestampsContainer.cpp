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
#include <vector>
#include "AbsoluteTimestampsContainer.h"
class AbsoluteTimestampsTest : public ::testing::Test {
 protected:
  AbsoluteTimestampsContainer absoluteTimestampsNormal1;
  AbsoluteTimestampsContainer absoluteTimestampsNormal2;
  AbsoluteTimestampsContainer absoluteTimestampsTwoElement1;
  AbsoluteTimestampsContainer absoluteTimestampsTwoElement2;
  AbsoluteTimestampsContainer absoluteTimestampsOneElement1;
  AbsoluteTimestampsContainer absoluteTimestampsOneElement2;
  AbsoluteTimestampsContainer absoluteTimestamps01;
  AbsoluteTimestampsContainer absoluteTimestamps02;
  AbsoluteTimestampsContainer absoluteTimestampsEmpty1;
  AbsoluteTimestampsContainer absoluteTimestampsEmpty2;
  std::vector<uint64_t> unixTimestampsNormal_ms = {1, 2, 3};
  std::vector<uint64_t> unixTimestampsTwoElements_ms = {1, 2};
  std::vector<uint64_t> unixTimestampsOneElement_ms = {1};
  std::vector<uint64_t> unixTimestamps0_ms = {0};
  std::vector<uint64_t> unixTimestampsEmpty_ms = {};
  virtual void SetUp() {
    this->absoluteTimestampsNormal1 = AbsoluteTimestampsContainer(this->unixTimestampsNormal_ms);
    this->absoluteTimestampsNormal2 = AbsoluteTimestampsContainer(this->unixTimestampsNormal_ms);
    this->absoluteTimestampsTwoElement1 = AbsoluteTimestampsContainer(this->unixTimestampsTwoElements_ms);
    this->absoluteTimestampsTwoElement2 = AbsoluteTimestampsContainer(this->unixTimestampsTwoElements_ms);
    this->absoluteTimestampsOneElement1 = AbsoluteTimestampsContainer(this->unixTimestampsOneElement_ms);
    this->absoluteTimestampsOneElement2 = AbsoluteTimestampsContainer(this->unixTimestampsOneElement_ms);
    this->absoluteTimestamps01 = AbsoluteTimestampsContainer(this->unixTimestamps0_ms);
    this->absoluteTimestamps02 = AbsoluteTimestampsContainer(this->unixTimestamps0_ms);
    this->absoluteTimestampsEmpty1 = AbsoluteTimestampsContainer(this->unixTimestampsEmpty_ms);
    this->absoluteTimestampsEmpty2 = AbsoluteTimestampsContainer(this->unixTimestampsEmpty_ms);
  }
};

TEST_F(AbsoluteTimestampsTest, TestGetUnixTimestamps) {
  EXPECT_EQ(this->absoluteTimestampsNormal1.getUnixTimestamps(), this->unixTimestampsNormal_ms);
}

TEST_F(AbsoluteTimestampsTest, TestGetEmptyUnixTimestamps) {
  EXPECT_EQ(this->absoluteTimestampsEmpty1.getUnixTimestamps(), this->unixTimestampsEmpty_ms);
}

TEST_F(AbsoluteTimestampsTest, TestGet0UnixTimestamps) {
  EXPECT_EQ(this->absoluteTimestamps01.getUnixTimestamps(), this->unixTimestamps0_ms);
}

TEST_F(AbsoluteTimestampsTest, CompareEmptyAndFullBlocks) {
  EXPECT_FALSE(this->absoluteTimestampsNormal1.isEqual(this->absoluteTimestampsEmpty1));
}

TEST_F(AbsoluteTimestampsTest, CompareShortAndFullBlocks) {
  EXPECT_FALSE(this->absoluteTimestampsOneElement1.isEqual(this->absoluteTimestampsNormal1));
}

TEST_F(AbsoluteTimestampsTest, CompareSameContentBlocks) {
  EXPECT_TRUE(this->absoluteTimestampsNormal1.isEqual(this->absoluteTimestampsNormal2));
}

TEST_F(AbsoluteTimestampsTest, CompareFullAndOneBlocks) {
  EXPECT_FALSE(this->absoluteTimestampsNormal1.isEqual(this->absoluteTimestampsOneElement1));
}

TEST_F(AbsoluteTimestampsTest, CompareFullAndShortBlocks) {
  EXPECT_FALSE(this->absoluteTimestampsNormal1.isEqual(this->absoluteTimestampsOneElement1));
}

TEST_F(AbsoluteTimestampsTest, CompareEmptyWithEmptyBlocks) {
  EXPECT_TRUE(this->absoluteTimestampsEmpty1.isEqual(this->absoluteTimestampsEmpty2));
}

TEST_F(AbsoluteTimestampsTest, CompareZeroWithZeroBlocks) {
  EXPECT_TRUE(this->absoluteTimestamps01.isEqual(this->absoluteTimestamps02));
}

TEST_F(AbsoluteTimestampsTest, CompareEmptyWithZeroBlocks) {
  EXPECT_FALSE(this->absoluteTimestamps01.isEqual(this->absoluteTimestampsEmpty1));
}

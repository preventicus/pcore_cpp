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
#include "UnixTimestampsExampleFactory.h"

class AbsoluteTimestampsContainerTest : public ::testing::Test {
 protected:
  UnixTimestamps unixTimestampsNormal1_ms = UnixTimestampsExampleFactory::unixTimestampsNormal1_ms();
  UnixTimestamps unixTimestampsNormal2_ms = UnixTimestampsExampleFactory::unixTimestampsNormal2_ms();
  UnixTimestamps unixTimestampsEmpty_ms = UnixTimestampsExampleFactory::unixTimestampsEmpty_ms();
  UnixTimestamps unixTimestampsTwoElements_ms = UnixTimestampsExampleFactory::unixTimestampsTwoElements_ms();
};

TEST_F(AbsoluteTimestampsContainerTest, TestGetUnixTimestamps) {
  AbsoluteTimestampsContainer absoluteTimestampsContainer =
      AbsoluteTimestampsContainerExampleFactory::buildAbsoluteTimestampsContainer(this->unixTimestampsNormal1_ms);
  EXPECT_EQ(absoluteTimestampsContainer.getUnixTimestamps(), this->unixTimestampsNormal1_ms);
}

TEST_F(AbsoluteTimestampsContainerTest, TestGetEmptyUnixTimestamps) {
  AbsoluteTimestampsContainer absoluteTimestampsContainer =
      AbsoluteTimestampsContainerExampleFactory::buildAbsoluteTimestampsContainer(this->unixTimestampsEmpty_ms);
  EXPECT_EQ(absoluteTimestampsContainer.getUnixTimestamps(), this->unixTimestampsEmpty_ms);
}

TEST_F(AbsoluteTimestampsContainerTest, CompareEqualNormalContainer) {
  AbsoluteTimestampsContainer absoluteTimestampsContainer1 =
      AbsoluteTimestampsContainerExampleFactory::buildAbsoluteTimestampsContainer(this->unixTimestampsNormal1_ms);
  AbsoluteTimestampsContainer absoluteTimestampsContainer2 =
      AbsoluteTimestampsContainerExampleFactory::buildAbsoluteTimestampsContainer(this->unixTimestampsNormal1_ms);
  EXPECT_TRUE(absoluteTimestampsContainer1.isEqual(absoluteTimestampsContainer2));
}

TEST_F(AbsoluteTimestampsContainerTest, CompareNotEqualNormalContainer) {
  AbsoluteTimestampsContainer absoluteTimestampsContainer1 =
      AbsoluteTimestampsContainerExampleFactory::buildAbsoluteTimestampsContainer(this->unixTimestampsNormal1_ms);
  AbsoluteTimestampsContainer absoluteTimestampsContainer2 =
      AbsoluteTimestampsContainerExampleFactory::buildAbsoluteTimestampsContainer(this->unixTimestampsNormal2_ms);
  EXPECT_FALSE(absoluteTimestampsContainer1.isEqual(absoluteTimestampsContainer2));
}

TEST_F(AbsoluteTimestampsContainerTest, CompareEmptyWithEmptyContainer) {
  AbsoluteTimestampsContainer absoluteTimestampsContainer1 =
      AbsoluteTimestampsContainerExampleFactory::buildAbsoluteTimestampsContainer(this->unixTimestampsEmpty_ms);
  AbsoluteTimestampsContainer absoluteTimestampsContainer2 =
      AbsoluteTimestampsContainerExampleFactory::buildAbsoluteTimestampsContainer(this->unixTimestampsEmpty_ms);
  EXPECT_TRUE(absoluteTimestampsContainer1.isEqual(absoluteTimestampsContainer2));
}

TEST_F(AbsoluteTimestampsContainerTest, CompareEmptyAndNormalContainer) {
  AbsoluteTimestampsContainer absoluteTimestampsContainer1 =
      AbsoluteTimestampsContainerExampleFactory::buildAbsoluteTimestampsContainer(this->unixTimestampsEmpty_ms);
  AbsoluteTimestampsContainer absoluteTimestampsContainer2 =
      AbsoluteTimestampsContainerExampleFactory::buildAbsoluteTimestampsContainer(this->unixTimestampsNormal2_ms);
  EXPECT_FALSE(absoluteTimestampsContainer1.isEqual(absoluteTimestampsContainer2));
}

TEST_F(AbsoluteTimestampsContainerTest, CompareContainersWithDifferentSize) {
  AbsoluteTimestampsContainer absoluteTimestampsContainer1 =
      AbsoluteTimestampsContainerExampleFactory::buildAbsoluteTimestampsContainer(this->unixTimestampsTwoElements_ms);
  AbsoluteTimestampsContainer absoluteTimestampsContainer2 =
      AbsoluteTimestampsContainerExampleFactory::buildAbsoluteTimestampsContainer(this->unixTimestampsNormal2_ms);
  EXPECT_FALSE(absoluteTimestampsContainer1.isEqual(absoluteTimestampsContainer2));
}

TEST_F(AbsoluteTimestampsContainerTest, TestToJsonWithNormalContainer) {
  AbsoluteTimestampsContainer absoluteTimestampsContainer =
      AbsoluteTimestampsContainerExampleFactory::buildAbsoluteTimestampsContainer(this->unixTimestampsNormal1_ms);
  AbsoluteTimestampsContainerJson absoluteTimestampsContainerJson1 = absoluteTimestampsContainer.toJson();
  UnixTimestampsJson unixTimestampsJson = UnixTimestampsExampleFactory::buildUnixTimestampsJson(this->unixTimestampsNormal1_ms);
  AbsoluteTimestampsContainerJson absoluteTimestampsContainerJson2 =
      AbsoluteTimestampsContainerExampleFactory::buildAbsoluteTimestampsContainerJson(unixTimestampsJson);
  EXPECT_TRUE(absoluteTimestampsContainerJson1 == absoluteTimestampsContainerJson2);
}
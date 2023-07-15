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
#include "AbsoluteTimestampsContainerExampleFactory.h"
#include "UnixTimestampsExampleFactory.h"

TEST(AbsoluteTimestampsContainerTest, TestGetUnixTimestampsWithThreeBigTimestamps) {
  auto absoluteTimestampsContainer = AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsContainerWithThreeBigTimestamps();
  auto unixTimestamps = UnixTimestampsExampleFactory::unixTimestampsWithThreeBigTimestamps_ms();
  EXPECT_EQ(absoluteTimestampsContainer.getUnixTimestamps_ms(), unixTimestamps);
}

TEST(AbsoluteTimestampsContainerTest, TestGetUnixTimestampsWithAbsoluteTimestampsNotSet) {
  auto absoluteTimestampsContainer = AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsContainerNotSet();
  auto unixTimestamps = UnixTimestampsExampleFactory::unixTimestampsNotSet_ms();
  EXPECT_EQ(absoluteTimestampsContainer.getUnixTimestamps_ms(), unixTimestamps);
}

TEST(AbsoluteTimestampsContainerTest, TestIsEqualWithThreeBigTimestampsAndThreeBigTimestamps) {
  auto absoluteTimestampsContainer1 = AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsContainerWithThreeBigTimestamps();
  auto absoluteTimestampsContainer2 = AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsContainerWithThreeBigTimestamps();
  EXPECT_TRUE(absoluteTimestampsContainer1 == absoluteTimestampsContainer2);
}

TEST(AbsoluteTimestampsContainerTest, TestIsEqualWithThreeBigTimestampsAndThreeSmallTimestamps) {
  auto absoluteTimestampsContainer1 = AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsContainerWithThreeBigTimestamps();
  auto absoluteTimestampsContainer2 = AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsContainerWithThreeSmallTimestamps();
  EXPECT_FALSE(absoluteTimestampsContainer1 == absoluteTimestampsContainer2);
}

TEST(AbsoluteTimestampsContainerTest, TestIsEqualWithAbsoluteTimestampsContainerNotSet) {
  auto absoluteTimestampsContainer1 = AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsContainerNotSet();
  auto absoluteTimestampsContainer2 = AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsContainerNotSet();
  EXPECT_TRUE(absoluteTimestampsContainer1 == absoluteTimestampsContainer2);
}

TEST(AbsoluteTimestampsContainerTest, TestIsEqualWithAbsoluteTimestampsContainerNotSetAndWithThreeSmallTimestamps) {
  auto absoluteTimestampsContainer1 = AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsContainerNotSet();
  auto absoluteTimestampsContainer2 = AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsContainerWithThreeSmallTimestamps();
  EXPECT_FALSE(absoluteTimestampsContainer1 == absoluteTimestampsContainer2);
}

TEST(AbsoluteTimestampsContainerTest, TestIsEqualWithThreeBigTimestampsAndOneBigTimestamp) {
  auto absoluteTimestampsContainer1 = AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsContainerWithThreeBigTimestamps();
  auto absoluteTimestampsContainer2 = AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsContainerWithOneBigTimestamp();
  EXPECT_FALSE(absoluteTimestampsContainer1 == absoluteTimestampsContainer2);
}

TEST(AbsoluteTimestampsContainerTest, TestIsNotEqualWithThreeBigTimestampsAndThreeBigTimestamps) {
  auto absoluteTimestampsContainer1 = AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsContainerWithThreeBigTimestamps();
  auto absoluteTimestampsContainer2 = AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsContainerWithThreeBigTimestamps();
  EXPECT_FALSE(absoluteTimestampsContainer1 != absoluteTimestampsContainer2);
}

TEST(AbsoluteTimestampsContainerTest, TestIsNotEqualWithThreeBigTimestampsAndThreeSmallTimestamps) {
  auto absoluteTimestampsContainer1 = AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsContainerWithThreeBigTimestamps();
  auto absoluteTimestampsContainer2 = AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsContainerWithThreeSmallTimestamps();
  EXPECT_TRUE(absoluteTimestampsContainer1 != absoluteTimestampsContainer2);
}

TEST(AbsoluteTimestampsContainerTest, TestIsNotEqualWithAbsoluteTimestampsContainerNotSet) {
  auto absoluteTimestampsContainer1 = AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsContainerNotSet();
  auto absoluteTimestampsContainer2 = AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsContainerNotSet();
  EXPECT_FALSE(absoluteTimestampsContainer1 != absoluteTimestampsContainer2);
}

TEST(AbsoluteTimestampsContainerTest, TestIsNotEqualWithAbsoluteTimestampsContainerNotSetAndAbsoluteTimestampsContainerWithThreeSmallTimestamps) {
  auto absoluteTimestampsContainer1 = AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsContainerNotSet();
  auto absoluteTimestampsContainer2 = AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsContainerWithThreeSmallTimestamps();
  EXPECT_TRUE(absoluteTimestampsContainer1 != absoluteTimestampsContainer2);
}

TEST(AbsoluteTimestampsContainerTest, TestIsNotEqualWithThreeBigTimestampsAndOneBigTimestamp) {
  auto absoluteTimestampsContainer1 = AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsContainerWithThreeBigTimestamps();
  auto absoluteTimestampsContainer2 = AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsContainerWithOneBigTimestamp();
  EXPECT_TRUE(absoluteTimestampsContainer1 != absoluteTimestampsContainer2);
}

TEST(AbsoluteTimestampsContainerTest, TestToJsonWithThreeBigTimestamps) {
  auto absoluteTimestampsContainer = AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsContainerWithThreeBigTimestamps();
  auto absoluteTimestampsContainerJson1 =
      AbsoluteTimestampsContainerExampleFactory::buildAbsoluteTimestampsContainerJson(absoluteTimestampsContainer);
  auto absoluteTimestampsContainerJson2 = absoluteTimestampsContainer.toJson();
  EXPECT_TRUE(absoluteTimestampsContainerJson1.toStyledString() == absoluteTimestampsContainerJson2.toStyledString());
}

TEST(AbsoluteTimestampsContainerTest, TestToJsonWithAbsoluteTimestampsContainerNotSet) {
  auto absoluteTimestampsContainer = AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsContainerNotSet();
  auto absoluteTimestampsContainerJson1 =
      AbsoluteTimestampsContainerExampleFactory::buildAbsoluteTimestampsContainerJson(absoluteTimestampsContainer);
  auto absoluteTimestampsContainerJson2 = absoluteTimestampsContainer.toJson();
  EXPECT_TRUE(absoluteTimestampsContainerJson1.toStyledString() == absoluteTimestampsContainerJson2.toStyledString());
}

TEST(AbsoluteTimestampsContainerTest, TestToJsonWithThreeSmallTimestamps) {
  auto absoluteTimestampsContainer = AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsContainerWithThreeSmallTimestamps();
  auto absoluteTimestampsContainerJson1 =
      AbsoluteTimestampsContainerExampleFactory::buildAbsoluteTimestampsContainerJson(absoluteTimestampsContainer);
  auto absoluteTimestampsContainerJson2 = absoluteTimestampsContainer.toJson();
  EXPECT_TRUE(absoluteTimestampsContainerJson1.toStyledString() == absoluteTimestampsContainerJson2.toStyledString());
}

TEST(AbsoluteTimestampsContainerTest, TestToJsonWithOneBigTimestamp) {
  auto absoluteTimestampsContainer = AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsContainerWithOneBigTimestamp();
  auto absoluteTimestampsContainerJson1 =
      AbsoluteTimestampsContainerExampleFactory::buildAbsoluteTimestampsContainerJson(absoluteTimestampsContainer);
  auto absoluteTimestampsContainerJson2 = absoluteTimestampsContainer.toJson();
  EXPECT_TRUE(absoluteTimestampsContainerJson1.toStyledString() == absoluteTimestampsContainerJson2.toStyledString());
}

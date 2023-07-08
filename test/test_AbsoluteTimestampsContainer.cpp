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
  AbsoluteTimestampsContainer absoluteTimestampsContainer =
      AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsContainerWithThreeBigTimestamps();
  UnixTimestamps unixTimestamps = UnixTimestampsExampleFactory::unixTimestampsWithThreeBigTimestamps_ms();
  EXPECT_EQ(absoluteTimestampsContainer.getUnixTimestamps(), unixTimestamps);
}

TEST(AbsoluteTimestampsContainerTest, TestGetUnixTimestampsWithAbsoluteTimestampsEmpty) {
  AbsoluteTimestampsContainer absoluteTimestampsContainer =
      AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsContainerWithTimestampsEmpty();
  UnixTimestamps unixTimestamps = UnixTimestampsExampleFactory::unixTimestampsEmpty_ms();
  EXPECT_EQ(absoluteTimestampsContainer.getUnixTimestamps(), unixTimestamps);
}

TEST(AbsoluteTimestampsContainerTest, TestIsEqualWithThreeBigTimestampsAndThreeBigTimestamps) {
  AbsoluteTimestampsContainer absoluteTimestampsContainer1 =
      AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsContainerWithThreeBigTimestamps();
  AbsoluteTimestampsContainer absoluteTimestampsContainer2 =
      AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsContainerWithThreeBigTimestamps();
  EXPECT_TRUE(absoluteTimestampsContainer1.isEqual(absoluteTimestampsContainer2));
}

TEST(AbsoluteTimestampsContainerTest, TestIsEqualWithThreeBigTimestampsAndThreeSmallTimestamps) {
  AbsoluteTimestampsContainer absoluteTimestampsContainer1 =
      AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsContainerWithThreeBigTimestamps();
  AbsoluteTimestampsContainer absoluteTimestampsContainer2 =
      AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsContainerWithThreeSmallTimestamps();
  EXPECT_FALSE(absoluteTimestampsContainer1.isEqual(absoluteTimestampsContainer2));
}

TEST(AbsoluteTimestampsContainerTest, TestIsEqualWithEmptyContainerAndEmptyContainer) {
  AbsoluteTimestampsContainer absoluteTimestampsContainer1 =
      AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsContainerWithTimestampsEmpty();
  AbsoluteTimestampsContainer absoluteTimestampsContainer2 =
      AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsContainerWithTimestampsEmpty();
  EXPECT_TRUE(absoluteTimestampsContainer1.isEqual(absoluteTimestampsContainer2));
}

TEST(AbsoluteTimestampsContainerTest, TestIsEqualWithEmptyContainerAndWithThreeSmallTimestamps) {
  AbsoluteTimestampsContainer absoluteTimestampsContainer1 =
      AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsContainerWithTimestampsEmpty();
  AbsoluteTimestampsContainer absoluteTimestampsContainer2 =
      AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsContainerWithThreeSmallTimestamps();
  EXPECT_FALSE(absoluteTimestampsContainer1.isEqual(absoluteTimestampsContainer2));
}

TEST(AbsoluteTimestampsContainerTest, TestIsEqualWithThreeBigTimestampsAndOneBigTimestamp) {
  AbsoluteTimestampsContainer absoluteTimestampsContainer1 =
      AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsContainerWithThreeBigTimestamps();
  AbsoluteTimestampsContainer absoluteTimestampsContainer2 =
      AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsContainerWithOneBigTimestamp();
  EXPECT_FALSE(absoluteTimestampsContainer1.isEqual(absoluteTimestampsContainer2));
}

TEST(AbsoluteTimestampsContainerTest, TestToJsonWithThreeBigTimestamps) {
  AbsoluteTimestampsContainer absoluteTimestampsContainer =
      AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsContainerWithThreeBigTimestamps();
  AbsoluteTimestampsContainerJson absoluteTimestampsContainerJson1 =
      AbsoluteTimestampsContainerExampleFactory::buildAbsoluteTimestampsContainerJson(absoluteTimestampsContainer);
  AbsoluteTimestampsContainerJson absoluteTimestampsContainerJson2 = absoluteTimestampsContainer.toJson();
  EXPECT_TRUE(absoluteTimestampsContainerJson1.toStyledString() == absoluteTimestampsContainerJson2.toStyledString());
}

TEST(AbsoluteTimestampsContainerTest, TestToJsonWithTimestampsEmpty) {
  AbsoluteTimestampsContainer absoluteTimestampsContainer =
      AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsContainerWithTimestampsEmpty();
  AbsoluteTimestampsContainerJson absoluteTimestampsContainerJson1 =
      AbsoluteTimestampsContainerExampleFactory::buildAbsoluteTimestampsContainerJson(absoluteTimestampsContainer);
  AbsoluteTimestampsContainerJson absoluteTimestampsContainerJson2 = absoluteTimestampsContainer.toJson();
  EXPECT_TRUE(absoluteTimestampsContainerJson1.toStyledString() == absoluteTimestampsContainerJson2.toStyledString());
}

TEST(AbsoluteTimestampsContainerTest, TestToJsonWithThreeSmallTimestamps) {
  AbsoluteTimestampsContainer absoluteTimestampsContainer =
      AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsContainerWithThreeSmallTimestamps();
  AbsoluteTimestampsContainerJson absoluteTimestampsContainerJson1 =
      AbsoluteTimestampsContainerExampleFactory::buildAbsoluteTimestampsContainerJson(absoluteTimestampsContainer);
  AbsoluteTimestampsContainerJson absoluteTimestampsContainerJson2 = absoluteTimestampsContainer.toJson();
  EXPECT_TRUE(absoluteTimestampsContainerJson1.toStyledString() == absoluteTimestampsContainerJson2.toStyledString());
}

TEST(AbsoluteTimestampsContainerTest, TestToJsonWithOneBigTimestamp) {
  AbsoluteTimestampsContainer absoluteTimestampsContainer =
      AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsContainerWithOneBigTimestamp();
  AbsoluteTimestampsContainerJson absoluteTimestampsContainerJson1 =
      AbsoluteTimestampsContainerExampleFactory::buildAbsoluteTimestampsContainerJson(absoluteTimestampsContainer);
  AbsoluteTimestampsContainerJson absoluteTimestampsContainerJson2 = absoluteTimestampsContainer.toJson();
  EXPECT_TRUE(absoluteTimestampsContainerJson1.toStyledString() == absoluteTimestampsContainerJson2.toStyledString());
}

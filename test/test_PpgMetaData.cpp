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
#include "PpgMetaDataExampleFactory.h"

TEST(PpgMetaDataTest, TestSetAndGetColor) {
  PpgMetaData ppgMetaData = PpgMetaDataExampleFactory::ppgMetDataWithColorGreen();
  EXPECT_EQ(ppgMetaData.getColor(), ProtobufColor::COLOR_GREEN);
  EXPECT_EQ(ppgMetaData.getWavelength(), 0);
}

TEST(PpgMetaDataTest, TestSetAndGetWavelength) {
  PpgMetaData ppgMetaData = PpgMetaDataExampleFactory::ppgMetaDataWithWavelength255();
  EXPECT_EQ(ppgMetaData.getColor(), ProtobufColor::COLOR_NONE);
  EXPECT_EQ(ppgMetaData.getWavelength(), 255);
}

TEST(PpgMetaDataTest, TestSetAndGetEmptyConstructor) {
  PpgMetaData ppgMetaData = PpgMetaDataExampleFactory::ppgMetaDataNotSet();
  EXPECT_EQ(ppgMetaData.getColor(), ProtobufColor::COLOR_NONE);
  EXPECT_EQ(ppgMetaData.getWavelength(), 0);
}

TEST(PpgMetaDataTest, TestIsSetWithPpgMetaDataWithWavelength255) {
  PpgMetaData ppgMetaData = PpgMetaDataExampleFactory::ppgMetaDataWithWavelength255();
  EXPECT_TRUE(ppgMetaData.isSet());
}

TEST(PpgMetaDataTest, TestIsSetWithPpgMetDataWithColorRed) {
  PpgMetaData ppgMetaData = PpgMetaDataExampleFactory::ppgMetDataWithColorRed();
  EXPECT_TRUE(ppgMetaData.isSet());
}

TEST(PpgMetaDataTest, TestIsSetWithPpgMetDataWithColorGreen) {
  PpgMetaData ppgMetaData = PpgMetaDataExampleFactory::ppgMetDataWithColorGreen();
  EXPECT_TRUE(ppgMetaData.isSet());
}

TEST(PpgMetaDataTest, TestIsSetWithPpgMetDataWithColorBlue) {
  PpgMetaData ppgMetaData = PpgMetaDataExampleFactory::ppgMetDataWithColorBlue();
  EXPECT_TRUE(ppgMetaData.isSet());
}

TEST(PpgMetaDataTest, TestIsSetWithPpgMetaDataNotSet) {
  PpgMetaData ppgMetaData = PpgMetaDataExampleFactory::ppgMetaDataNotSet();
  EXPECT_FALSE(ppgMetaData.isSet());
}

TEST(PpgMetaDataTest, TestIsEqualPpgMetDataWithColorRed) {
  PpgMetaData ppgMetaData1 = PpgMetaDataExampleFactory::ppgMetDataWithColorRed();
  PpgMetaData ppgMetaData2 = PpgMetaDataExampleFactory::ppgMetDataWithColorRed();
  EXPECT_TRUE(ppgMetaData1.isEqual(ppgMetaData2));
}

TEST(PpgMetaDataTest, TestIsEqualPpgMetDataWithColorGreen) {
  PpgMetaData ppgMetaData1 = PpgMetaDataExampleFactory::ppgMetDataWithColorGreen();
  PpgMetaData ppgMetaData2 = PpgMetaDataExampleFactory::ppgMetDataWithColorGreen();
  EXPECT_TRUE(ppgMetaData1.isEqual(ppgMetaData2));
}

TEST(PpgMetaDataTest, TestIsEqualPpgMetDataWithColorBlue) {
  PpgMetaData ppgMetaData1 = PpgMetaDataExampleFactory::ppgMetDataWithColorBlue();
  PpgMetaData ppgMetaData2 = PpgMetaDataExampleFactory::ppgMetDataWithColorBlue();
  EXPECT_TRUE(ppgMetaData1.isEqual(ppgMetaData2));
}

TEST(PpgMetaDataTest, TestIsEqualPpgMetDataWithWavelength255) {
  PpgMetaData ppgMetaData1 = PpgMetaDataExampleFactory::ppgMetaDataWithWavelength255();
  PpgMetaData ppgMetaData2 = PpgMetaDataExampleFactory::ppgMetaDataWithWavelength255();
  EXPECT_TRUE(ppgMetaData1.isEqual(ppgMetaData2));
}

TEST(PpgMetaDataTest, TestIsEqualWithDifferentColor) {
  PpgMetaData ppgMetaData1 = PpgMetaDataExampleFactory::ppgMetDataWithColorGreen();
  PpgMetaData ppgMetaData2 = PpgMetaDataExampleFactory::ppgMetDataWithColorRed();
  EXPECT_FALSE(ppgMetaData1.isEqual(ppgMetaData2));
}

TEST(PpgMetaDataTest, TestIsEqualWithDifferentWavelength) {
  PpgMetaData ppgMetaData1 = PpgMetaDataExampleFactory::ppgMetaDataWithWavelength255();
  PpgMetaData ppgMetaData2 = PpgMetaDataExampleFactory::ppgMetaDataWithWavelength100();
  EXPECT_FALSE(ppgMetaData1.isEqual(ppgMetaData2));
}

TEST(PpgMetaDataTest, TestIsEqualWithPpgMetaDataNotSet) {
  PpgMetaData ppgMetaData1 = PpgMetaDataExampleFactory::ppgMetaDataNotSet();
  PpgMetaData ppgMetaData2 = PpgMetaDataExampleFactory::ppgMetaDataNotSet();
  EXPECT_TRUE(ppgMetaData1.isEqual(ppgMetaData2));
}

TEST(PpgMetaDataTest, TestIsEqualWithColorAndWavelength) {
  PpgMetaData ppgMetaData1 = PpgMetaDataExampleFactory::ppgMetDataWithColorGreen();
  PpgMetaData ppgMetaData2 = PpgMetaDataExampleFactory::ppgMetaDataWithWavelength100();
  EXPECT_FALSE(ppgMetaData1.isEqual(ppgMetaData2));
}

TEST(PpgMetaDataTest, TestSerizlizeWithPpgMetaDataWithWavelength255) {
  PpgMetaData ppgMetaData1 = PpgMetaDataExampleFactory::ppgMetaDataWithWavelength255();
  ProtobufPpgMetaData protobufPpgMetaData;
  ppgMetaData1.serialize(&protobufPpgMetaData);
  PpgMetaData ppgMetaData2 = PpgMetaData(protobufPpgMetaData);
  EXPECT_TRUE(ppgMetaData1.isEqual(ppgMetaData2));
}

TEST(PpgMetaDataTest, TestSerizlizeWithPpgMetDataWithColorRed) {
  PpgMetaData ppgMetaData1 = PpgMetaDataExampleFactory::ppgMetDataWithColorRed();
  ProtobufPpgMetaData protobufPpgMetaData;
  ppgMetaData1.serialize(&protobufPpgMetaData);
  PpgMetaData ppgMetaData2 = PpgMetaData(protobufPpgMetaData);
  EXPECT_TRUE(ppgMetaData1.isEqual(ppgMetaData2));
}

TEST(PpgMetaDataTest, TestSerizlizeWithPpgMetDataWithColorGreen) {
  PpgMetaData ppgMetaData1 = PpgMetaDataExampleFactory::ppgMetDataWithColorGreen();
  ProtobufPpgMetaData protobufPpgMetaData;
  ppgMetaData1.serialize(&protobufPpgMetaData);
  PpgMetaData ppgMetaData2 = PpgMetaData(protobufPpgMetaData);
  EXPECT_TRUE(ppgMetaData1.isEqual(ppgMetaData2));
}

TEST(PpgMetaDataTest, TestSerizlizeWithPpgMetDataWithColorBlue) {
  PpgMetaData ppgMetaData1 = PpgMetaDataExampleFactory::ppgMetDataWithColorBlue();
  ProtobufPpgMetaData protobufPpgMetaData;
  ppgMetaData1.serialize(&protobufPpgMetaData);
  PpgMetaData ppgMetaData2 = PpgMetaData(protobufPpgMetaData);
  EXPECT_TRUE(ppgMetaData1.isEqual(ppgMetaData2));
}

TEST(PpgMetaDataTest, TestSerializeNoThrow) {
  PpgMetaData ppgMetaDataG1 = PpgMetaDataExampleFactory::ppgMetDataWithColorGreen();
  ProtobufPpgMetaData protobufData;
  EXPECT_NO_THROW(ppgMetaDataG1.serialize(&protobufData));
}

TEST(PpgMetaDataTest, TestSerializeThrow) {
  PpgMetaData ppgMetaDataG1 = PpgMetaDataExampleFactory::ppgMetDataWithColorGreen();
  ProtobufPpgMetaData* protobufData = nullptr;
  EXPECT_THROW(ppgMetaDataG1.serialize(protobufData), std::invalid_argument);
}

TEST(PpgMetaDataTest, TestToJsonWithPpgMetaDataWithWavelength255) {
  PpgMetaData ppgMetaData = PpgMetaDataExampleFactory::ppgMetaDataWithWavelength255();
  PpgMetaDataJson ppgMetaDataJson1 = ppgMetaData.toJson();
  PpgMetaDataJson ppgMetaDataJson2 = PpgMetaDataExampleFactory::buildPpgMetaDataJson(ppgMetaData);
  EXPECT_TRUE(ppgMetaDataJson1.toStyledString() == ppgMetaDataJson2.toStyledString());
}

TEST(PpgMetaDataTest, TestToJsonWithPpgMetDataWithColorRed) {
  PpgMetaData ppgMetaData = PpgMetaDataExampleFactory::ppgMetDataWithColorRed();
  PpgMetaDataJson ppgMetaDataJson1 = ppgMetaData.toJson();
  PpgMetaDataJson ppgMetaDataJson2 = PpgMetaDataExampleFactory::buildPpgMetaDataJson(ppgMetaData);
  EXPECT_TRUE(ppgMetaDataJson1.toStyledString() == ppgMetaDataJson2.toStyledString());
}

TEST(PpgMetaDataTest, TestToJsonWithPpgMetDataWithColorGreen) {
  PpgMetaData ppgMetaData = PpgMetaDataExampleFactory::ppgMetDataWithColorGreen();
  PpgMetaDataJson ppgMetaDataJson1 = ppgMetaData.toJson();
  PpgMetaDataJson ppgMetaDataJson2 = PpgMetaDataExampleFactory::buildPpgMetaDataJson(ppgMetaData);
  EXPECT_TRUE(ppgMetaDataJson1.toStyledString() == ppgMetaDataJson2.toStyledString());
}

TEST(PpgMetaDataTest, TestToJsonWithPpgMetDataWithColorBlue) {
  PpgMetaData ppgMetaData = PpgMetaDataExampleFactory::ppgMetDataWithColorBlue();
  PpgMetaDataJson ppgMetaDataJson1 = ppgMetaData.toJson();
  PpgMetaDataJson ppgMetaDataJson2 = PpgMetaDataExampleFactory::buildPpgMetaDataJson(ppgMetaData);
  EXPECT_TRUE(ppgMetaDataJson1.toStyledString() == ppgMetaDataJson2.toStyledString());
}

TEST(PpgMetaDataTest, TestHasColorWithPpgMetDataWithColorBlue) {
  PpgMetaData ppgMetaData = PpgMetaDataExampleFactory::ppgMetDataWithColorBlue();
  EXPECT_TRUE(ppgMetaData.hasColor());
}

TEST(PpgMetaDataTest, TestHasColorWithPpgMetaDataWithColorNone) {
  PpgMetaData ppgMetaData = PpgMetaDataExampleFactory::ppgMetaDataWithColorNone();
  EXPECT_FALSE(ppgMetaData.hasColor());
}

TEST(PpgMetaDataTest, TestHasColorWithPpgMetaDataWithWavelength255) {
  PpgMetaData ppgMetaData = PpgMetaDataExampleFactory::ppgMetaDataWithWavelength255();
  EXPECT_TRUE(ppgMetaData.hasWavelength());
}

TEST(PpgMetaDataTest, TestHasColorWithPpgMetaDataWithWavelength0) {
  PpgMetaData ppgMetaData = PpgMetaDataExampleFactory::ppgMetaDataWithWavelength0();
  EXPECT_FALSE(ppgMetaData.hasWavelength());
}
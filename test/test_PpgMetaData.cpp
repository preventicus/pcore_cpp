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
#include "Exceptions.h"
#include "PpgMetaDataExampleFactory.h"

////////////////////////////////////////////////////////////////
//                        Test Getter                         //
////////////////////////////////////////////////////////////////

TEST(PpgMetaDataTest, TestGetColorWithPpgMetDataWithColorGreen) {
  auto ppgMetaData = PpgMetaDataExampleFactory::ppgMetDataWithColorGreen();
  EXPECT_EQ(ppgMetaData.getLight<ColorProtobuf>(), ColorProtobuf::COLOR_GREEN);
}

TEST(PpgMetaDataTest, TestGetWavelengthWithPpgMetaDataWithWavelength255) {
  auto ppgMetaData = PpgMetaDataExampleFactory::ppgMetaDataWithWavelength255();
  EXPECT_EQ(ppgMetaData.getLight<Wavelength>(), 255);
}

TEST(PpgMetaDataTest, TestGetColorWithPpgMetaDataNotSet) {
  auto ppgMetaData = PpgMetaDataExampleFactory::ppgMetaDataNotSet();
  EXPECT_EQ(ppgMetaData.getLight<ColorProtobuf>(), std::nullopt);
}

TEST(PpgMetaDataTest, TestGetWavelengthWithPpgMetaDataNotSet) {
  auto ppgMetaData = PpgMetaDataExampleFactory::ppgMetaDataNotSet();
  EXPECT_EQ(ppgMetaData.getLight<Wavelength>(), std::nullopt);
}

////////////////////////////////////////////////////////////////
//                        Test isEqual                        //
////////////////////////////////////////////////////////////////

TEST(PpgMetaDataTest, TestIsEqualPpgMetDataWithColorRed) {
  auto ppgMetaData1 = PpgMetaDataExampleFactory::ppgMetDataWithColorRed();
  auto ppgMetaData2 = PpgMetaDataExampleFactory::ppgMetDataWithColorRed();
  EXPECT_TRUE(ppgMetaData1 == ppgMetaData2);
}

TEST(PpgMetaDataTest, TestIsEqualPpgMetDataWithColorGreen) {
  auto ppgMetaData1 = PpgMetaDataExampleFactory::ppgMetDataWithColorGreen();
  auto ppgMetaData2 = PpgMetaDataExampleFactory::ppgMetDataWithColorGreen();
  EXPECT_TRUE(ppgMetaData1 == ppgMetaData2);
}

TEST(PpgMetaDataTest, TestIsEqualPpgMetDataWithColorBlue) {
  auto ppgMetaData1 = PpgMetaDataExampleFactory::ppgMetDataWithColorBlue();
  auto ppgMetaData2 = PpgMetaDataExampleFactory::ppgMetDataWithColorBlue();
  EXPECT_TRUE(ppgMetaData1 == ppgMetaData2);
}

TEST(PpgMetaDataTest, TestIsEqualPpgMetDataWithWavelength255) {
  auto ppgMetaData1 = PpgMetaDataExampleFactory::ppgMetaDataWithWavelength255();
  auto ppgMetaData2 = PpgMetaDataExampleFactory::ppgMetaDataWithWavelength255();
  EXPECT_TRUE(ppgMetaData1 == ppgMetaData2);
}

TEST(PpgMetaDataTest, TestIsEqualWithPpgMetDataWithColorGreenAndPpgMetDataWithColorRed) {
  auto ppgMetaData1 = PpgMetaDataExampleFactory::ppgMetDataWithColorGreen();
  auto ppgMetaData2 = PpgMetaDataExampleFactory::ppgMetDataWithColorRed();
  EXPECT_FALSE(ppgMetaData1 == ppgMetaData2);
}

TEST(PpgMetaDataTest, TestIsEqualWithPpgMetaDataWithWavelength255AndPpgMetaDataWithWavelength100) {
  auto ppgMetaData1 = PpgMetaDataExampleFactory::ppgMetaDataWithWavelength255();
  auto ppgMetaData2 = PpgMetaDataExampleFactory::ppgMetaDataWithWavelength100();
  EXPECT_FALSE(ppgMetaData1 == ppgMetaData2);
}

TEST(PpgMetaDataTest, TestIsEqualWithPpgMetaDataNotSet) {
  auto ppgMetaData1 = PpgMetaDataExampleFactory::ppgMetaDataNotSet();
  auto ppgMetaData2 = PpgMetaDataExampleFactory::ppgMetaDataNotSet();
  EXPECT_TRUE(ppgMetaData1 == ppgMetaData2);
}

TEST(PpgMetaDataTest, TestIsEqualWithPpgMetDataWithColorGreenAndPpgMetaDataWithWavelength100) {
  auto ppgMetaData1 = PpgMetaDataExampleFactory::ppgMetDataWithColorGreen();
  auto ppgMetaData2 = PpgMetaDataExampleFactory::ppgMetaDataWithWavelength100();
  EXPECT_FALSE(ppgMetaData1 == ppgMetaData2);
}

////////////////////////////////////////////////////////////////
//                      Test isNotEqual                       //
////////////////////////////////////////////////////////////////

TEST(PpgMetaDataTest, TestIsNotEqualPpgMetDataWithColorRed) {
  auto ppgMetaData1 = PpgMetaDataExampleFactory::ppgMetDataWithColorRed();
  auto ppgMetaData2 = PpgMetaDataExampleFactory::ppgMetDataWithColorRed();
  EXPECT_FALSE(ppgMetaData1 != ppgMetaData2);
}

TEST(PpgMetaDataTest, TestIsNotEqualPpgMetDataWithColorGreen) {
  auto ppgMetaData1 = PpgMetaDataExampleFactory::ppgMetDataWithColorGreen();
  auto ppgMetaData2 = PpgMetaDataExampleFactory::ppgMetDataWithColorGreen();
  EXPECT_FALSE(ppgMetaData1 != ppgMetaData2);
}

TEST(PpgMetaDataTest, TestIsNotEqualPpgMetDataWithColorBlue) {
  auto ppgMetaData1 = PpgMetaDataExampleFactory::ppgMetDataWithColorBlue();
  auto ppgMetaData2 = PpgMetaDataExampleFactory::ppgMetDataWithColorBlue();
  EXPECT_FALSE(ppgMetaData1 != ppgMetaData2);
}

TEST(PpgMetaDataTest, TestIsNotEqualPpgMetDataWithWavelength255) {
  auto ppgMetaData1 = PpgMetaDataExampleFactory::ppgMetaDataWithWavelength255();
  auto ppgMetaData2 = PpgMetaDataExampleFactory::ppgMetaDataWithWavelength255();
  EXPECT_FALSE(ppgMetaData1 != ppgMetaData2);
}

TEST(PpgMetaDataTest, TestIsNotEqualWithPpgMetDataWithColorGreenAndPpgMetDataWithColorRed) {
  auto ppgMetaData1 = PpgMetaDataExampleFactory::ppgMetDataWithColorGreen();
  auto ppgMetaData2 = PpgMetaDataExampleFactory::ppgMetDataWithColorRed();
  EXPECT_TRUE(ppgMetaData1 != ppgMetaData2);
}

TEST(PpgMetaDataTest, TestIsNotEqualWithPpgMetaDataWithWavelength255AndPpgMetaDataWithWavelength100) {
  auto ppgMetaData1 = PpgMetaDataExampleFactory::ppgMetaDataWithWavelength255();
  auto ppgMetaData2 = PpgMetaDataExampleFactory::ppgMetaDataWithWavelength100();
  EXPECT_TRUE(ppgMetaData1 != ppgMetaData2);
}

TEST(PpgMetaDataTest, TestIsNotEqualWithPpgMetaDataNotSet) {
  auto ppgMetaData1 = PpgMetaDataExampleFactory::ppgMetaDataNotSet();
  auto ppgMetaData2 = PpgMetaDataExampleFactory::ppgMetaDataNotSet();
  EXPECT_FALSE(ppgMetaData1 != ppgMetaData2);
}

TEST(PpgMetaDataTest, TestIsNotEqualWithppgMetDataWithColorGreenAndPpgMetaDataWithWavelength100) {
  auto ppgMetaData1 = PpgMetaDataExampleFactory::ppgMetDataWithColorGreen();
  auto ppgMetaData2 = PpgMetaDataExampleFactory::ppgMetaDataWithWavelength100();
  EXPECT_TRUE(ppgMetaData1 != ppgMetaData2);
}

////////////////////////////////////////////////////////////////
//                        Test toJson                         //
////////////////////////////////////////////////////////////////

TEST(PpgMetaDataTest, TestToJsonWithPpgMetaDataWithWavelength255) {
  auto ppgMetaData = PpgMetaDataExampleFactory::ppgMetaDataWithWavelength255();
  auto ppgMetaDataJson1 = ppgMetaData.toJson();
  auto ppgMetaDataJson2 = PpgMetaDataExampleFactory::buildPpgMetaDataJson(ppgMetaData);
  EXPECT_TRUE(ppgMetaDataJson1.toStyledString() == ppgMetaDataJson2.toStyledString());
}

TEST(PpgMetaDataTest, TestToJsonWithPpgMetDataWithColorRed) {
  auto ppgMetaData = PpgMetaDataExampleFactory::ppgMetDataWithColorRed();
  auto ppgMetaDataJson1 = ppgMetaData.toJson();
  auto ppgMetaDataJson2 = PpgMetaDataExampleFactory::buildPpgMetaDataJson(ppgMetaData);
  EXPECT_TRUE(ppgMetaDataJson1.toStyledString() == ppgMetaDataJson2.toStyledString());
}

TEST(PpgMetaDataTest, TestToJsonWithPpgMetDataWithColorGreen) {
  auto ppgMetaData = PpgMetaDataExampleFactory::ppgMetDataWithColorGreen();
  auto ppgMetaDataJson1 = ppgMetaData.toJson();
  auto ppgMetaDataJson2 = PpgMetaDataExampleFactory::buildPpgMetaDataJson(ppgMetaData);
  EXPECT_TRUE(ppgMetaDataJson1.toStyledString() == ppgMetaDataJson2.toStyledString());
}

TEST(PpgMetaDataTest, TestToJsonWithPpgMetDataWithColorBlue) {
  auto ppgMetaData = PpgMetaDataExampleFactory::ppgMetDataWithColorBlue();
  auto ppgMetaDataJson1 = ppgMetaData.toJson();
  auto ppgMetaDataJson2 = PpgMetaDataExampleFactory::buildPpgMetaDataJson(ppgMetaData);
  EXPECT_TRUE(ppgMetaDataJson1.toStyledString() == ppgMetaDataJson2.toStyledString());
}

TEST(PpgMetaDataTest, TestToJsonWithPpgMetDataNotSet) {
  auto ppgMetaData = PpgMetaDataExampleFactory::ppgMetaDataNotSet();
  auto ppgMetaDataJson1 = ppgMetaData.toJson();
  auto ppgMetaDataJson2 = PpgMetaDataExampleFactory::buildPpgMetaDataJson(ppgMetaData);
  EXPECT_TRUE(ppgMetaDataJson1.toStyledString() == ppgMetaDataJson2.toStyledString());
}

////////////////////////////////////////////////////////////////
//                        Test isSet                          //
////////////////////////////////////////////////////////////////

TEST(PpgMetaDataTest, TestIsSetWithPpgMetaDataWithWavelength255) {
  auto ppgMetaData = PpgMetaDataExampleFactory::ppgMetaDataWithWavelength255();
  EXPECT_TRUE(ppgMetaData.isSet());
}

TEST(PpgMetaDataTest, TestIsSetWithPpgMetDataWithColorRed) {
  auto ppgMetaData = PpgMetaDataExampleFactory::ppgMetDataWithColorRed();
  EXPECT_TRUE(ppgMetaData.isSet());
}

TEST(PpgMetaDataTest, TestIsSetWithPpgMetDataWithColorGreen) {
  auto ppgMetaData = PpgMetaDataExampleFactory::ppgMetDataWithColorGreen();
  EXPECT_TRUE(ppgMetaData.isSet());
}

TEST(PpgMetaDataTest, TestIsSetWithPpgMetDataWithColorBlue) {
  auto ppgMetaData = PpgMetaDataExampleFactory::ppgMetDataWithColorBlue();
  EXPECT_TRUE(ppgMetaData.isSet());
}

TEST(PpgMetaDataTest, TestIsSetWithPpgMetaDataNotSet) {
  auto ppgMetaData = PpgMetaDataExampleFactory::ppgMetaDataNotSet();
  EXPECT_FALSE(ppgMetaData.isSet());
}

////////////////////////////////////////////////////////////////
//                       Test serialize                       //
////////////////////////////////////////////////////////////////

TEST(PpgMetaDataTest, TestSerizlizeWithPpgMetaDataWithWavelength255) {
  auto ppgMetaData1 = PpgMetaDataExampleFactory::ppgMetaDataWithWavelength255();
  PpgMetaDataProtobuf ppgMetaDataProtobuf;
  ppgMetaData1.serialize(&ppgMetaDataProtobuf);
  auto ppgMetaData2 = PpgMetaData(ppgMetaDataProtobuf);
  EXPECT_TRUE(ppgMetaData1 == ppgMetaData2);
}

TEST(PpgMetaDataTest, TestSerizlizeWithPpgMetaDataNotSet) {
  auto ppgMetaData1 = PpgMetaDataExampleFactory::ppgMetaDataNotSet();
  PpgMetaDataProtobuf ppgMetaDataProtobuf;
  ppgMetaData1.serialize(&ppgMetaDataProtobuf);
  auto ppgMetaData2 = PpgMetaData(ppgMetaDataProtobuf);
  EXPECT_TRUE(ppgMetaData1 == ppgMetaData2);
}

TEST(PpgMetaDataTest, TestSerizlizeWithPpgMetDataWithColorRed) {
  auto ppgMetaData1 = PpgMetaDataExampleFactory::ppgMetDataWithColorRed();
  PpgMetaDataProtobuf ppgMetaDataProtobuf;
  ppgMetaData1.serialize(&ppgMetaDataProtobuf);
  auto ppgMetaData2 = PpgMetaData(ppgMetaDataProtobuf);
  EXPECT_TRUE(ppgMetaData1 == ppgMetaData2);
}

TEST(PpgMetaDataTest, TestSerizlizeWithPpgMetDataWithColorGreen) {
  auto ppgMetaData1 = PpgMetaDataExampleFactory::ppgMetDataWithColorGreen();
  PpgMetaDataProtobuf ppgMetaDataProtobuf;
  ppgMetaData1.serialize(&ppgMetaDataProtobuf);
  auto ppgMetaData2 = PpgMetaData(ppgMetaDataProtobuf);
  EXPECT_TRUE(ppgMetaData1 == ppgMetaData2);
}

TEST(PpgMetaDataTest, TestSerizlizeWithPpgMetDataWithColorBlue) {
  auto ppgMetaData1 = PpgMetaDataExampleFactory::ppgMetDataWithColorBlue();
  PpgMetaDataProtobuf ppgMetaDataProtobuf;
  ppgMetaData1.serialize(&ppgMetaDataProtobuf);
  auto ppgMetaData2 = PpgMetaData(ppgMetaDataProtobuf);
  EXPECT_TRUE(ppgMetaData1 == ppgMetaData2);
}

TEST(PpgMetaDataTest, TestSerializeNoThrow) {
  auto ppgMetaDataG1 = PpgMetaDataExampleFactory::ppgMetDataWithColorGreen();
  PpgMetaDataProtobuf ppgMetaDataProtobuf;
  EXPECT_NO_THROW(ppgMetaDataG1.serialize(&ppgMetaDataProtobuf));
}

TEST(PpgMetaDataTest, TestSerializeThrowDueToNullPointer) {
  auto ppgMetaDataG1 = PpgMetaDataExampleFactory::ppgMetDataWithColorGreen();
  PpgMetaDataProtobuf* ppgMetaDataProtobuf = nullptr;
  EXPECT_THROW(ppgMetaDataG1.serialize(ppgMetaDataProtobuf), NullPointerException);
}

////////////////////////////////////////////////////////////////
//                     Test switchDataForm                    //
////////////////////////////////////////////////////////////////

TEST(PpgMetaDataTest, TestSwitchDataFormWithPpgMetaDataNotSet) {
  auto ppgMetaData = PpgMetaDataExampleFactory::ppgMetaDataNotSet();
  EXPECT_THROW(ppgMetaData.switchDataForm(), ShouldNotBeCalledException);
}

////////////////////////////////////////////////////////////////
//                      Test has Methods                      //
////////////////////////////////////////////////////////////////

TEST(PpgMetaDataTest, TestHasColorWithPpgMetDataWithColorBlue) {
  auto ppgMetaData = PpgMetaDataExampleFactory::ppgMetDataWithColorBlue();
  EXPECT_TRUE(ppgMetaData.hasLight<ColorProtobuf>());
}

TEST(PpgMetaDataTest, TestHasColorWithPpgMetaDataWithColorNone) {
  auto ppgMetaData = PpgMetaDataExampleFactory::ppgMetaDataWithColorNone();
  EXPECT_FALSE(ppgMetaData.hasLight<ColorProtobuf>());
}

TEST(PpgMetaDataTest, TestHasColorWithPpgMetaDataWithWavelength255) {
  auto ppgMetaData = PpgMetaDataExampleFactory::ppgMetaDataWithWavelength255();
  EXPECT_TRUE(ppgMetaData.hasLight<Wavelength>());
}

TEST(PpgMetaDataTest, TestHasColorWithPpgMetaDataWithWavelength0) {
  auto ppgMetaData = PpgMetaDataExampleFactory::ppgMetaDataWithWavelength0();
  EXPECT_FALSE(ppgMetaData.hasLight<Wavelength>());
}
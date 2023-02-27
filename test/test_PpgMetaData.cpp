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
#include "PpgMetaDataExampleFactory.h"

class PpgMetaDataTest : public ::testing::Test {
 protected:
  Wavelength wavelengthNormal1_nm = PpgMetaDataExampleFactory::wavelengthNormal1_nm();
  Wavelength wavelengthNormal2_nm = PpgMetaDataExampleFactory::wavelengthNormal2_nm();
  Wavelength wavelengthNotSet_nm = PpgMetaDataExampleFactory::wavelengthNotSet_mn();

  PpgMetaData ppgMetDataWithColorGreen1 = PpgMetaDataExampleFactory::ppgMetDataWithColorGreen();
  PpgMetaData ppgMetDataWithColorGreen2 = PpgMetaDataExampleFactory::ppgMetDataWithColorGreen();
  PpgMetaData ppgMetDataWithColorBlue1 = PpgMetaDataExampleFactory::ppgMetDataWithColorBlue();
  PpgMetaData ppgMetDataWithColorBlue2 = PpgMetaDataExampleFactory::ppgMetDataWithColorBlue();
  PpgMetaData ppgMetDataWithColorRed1 = PpgMetaDataExampleFactory::ppgMetDataWithColorRed();
  PpgMetaData ppgMetDataWithColorRed2 = PpgMetaDataExampleFactory::ppgMetDataWithColorRed();
  PpgMetaData ppgMetDataWithWavelength1 = PpgMetaDataExampleFactory::ppgMetDataWithWavelength();
  PpgMetaData ppgMetDataWithWavelength2 = PpgMetaDataExampleFactory::ppgMetDataWithWavelength();
  PpgMetaData PpgMetaDataNotSet1 = PpgMetaDataExampleFactory::ppgMetaDataNotSet();
  PpgMetaData PpgMetaDataNotSet2 = PpgMetaDataExampleFactory::ppgMetaDataNotSet();
};

TEST_F(PpgMetaDataTest, TestSetAndGetColor) {
  PpgMetaData ppgMetaData = PpgMetaData(ProtobufColor::COLOR_GREEN);
  EXPECT_EQ(ppgMetaData.getColor(), ProtobufColor::COLOR_GREEN);
  EXPECT_EQ(ppgMetaData.getWavelength(), this->wavelengthNotSet_nm);
}

TEST_F(PpgMetaDataTest, TestSetAndGetWavelength) {
  PpgMetaData ppgMetaData = PpgMetaData(this->wavelengthNormal1_nm);
  EXPECT_EQ(ppgMetaData.getColor(), ProtobufColor::COLOR_NONE);
  EXPECT_EQ(ppgMetaData.getWavelength(), this->wavelengthNormal1_nm);
}

TEST_F(PpgMetaDataTest, TestSetAndGetEmptyConstructor) {
  PpgMetaData ppgMetaData = PpgMetaData();
  EXPECT_EQ(ppgMetaData.getColor(), ProtobufColor::COLOR_NONE);
  EXPECT_EQ(ppgMetaData.getWavelength(), this->wavelengthNotSet_nm);
}

TEST_F(PpgMetaDataTest, TestIsSet) {
  PpgMetaData ppgMetaDataW = PpgMetaData(this->wavelengthNormal1_nm);
  PpgMetaData ppgMetaDataR = PpgMetaData(ProtobufColor::COLOR_RED);
  PpgMetaData ppgMetaDataG = PpgMetaData(ProtobufColor::COLOR_GREEN);
  PpgMetaData ppgMetaDataB = PpgMetaData(ProtobufColor::COLOR_BLUE);
  EXPECT_TRUE(ppgMetaDataW.isSet());
  EXPECT_TRUE(ppgMetaDataR.isSet());
  EXPECT_TRUE(ppgMetaDataG.isSet());
  EXPECT_TRUE(ppgMetaDataB.isSet());
}

TEST_F(PpgMetaDataTest, TestIsNotSet) {
  PpgMetaData ppgMetaData = PpgMetaData();
  EXPECT_FALSE(ppgMetaData.isSet());
}

TEST_F(PpgMetaDataTest, CompareEqualColor) {
  PpgMetaData ppgMetaDataR1 = PpgMetaData(ProtobufColor::COLOR_RED);
  PpgMetaData ppgMetaDataR2 = PpgMetaData(ProtobufColor::COLOR_RED);
  PpgMetaData ppgMetaDataG1 = PpgMetaData(ProtobufColor::COLOR_GREEN);
  PpgMetaData ppgMetaDataG2 = PpgMetaData(ProtobufColor::COLOR_GREEN);
  PpgMetaData ppgMetaDataB1 = PpgMetaData(ProtobufColor::COLOR_BLUE);
  PpgMetaData ppgMetaDataB2 = PpgMetaData(ProtobufColor::COLOR_BLUE);
  EXPECT_TRUE(ppgMetaDataR1.isEqual(ppgMetaDataR2));
  EXPECT_TRUE(ppgMetaDataG1.isEqual(ppgMetaDataG2));
  EXPECT_TRUE(ppgMetaDataB1.isEqual(ppgMetaDataB2));
}

TEST_F(PpgMetaDataTest, CompareEqualWavelength) {
  PpgMetaData ppgMetaData1 = PpgMetaData(this->wavelengthNormal1_nm);
  PpgMetaData ppgMetaData2 = PpgMetaData(this->wavelengthNormal1_nm);
  EXPECT_TRUE(ppgMetaData1.isEqual(ppgMetaData2));
}

TEST_F(PpgMetaDataTest, CompareDifferentColor) {
  PpgMetaData ppgMetaData1 = PpgMetaData(ProtobufColor::COLOR_GREEN);
  PpgMetaData ppgMetaData2 = PpgMetaData(ProtobufColor::COLOR_RED);
  EXPECT_FALSE(ppgMetaData1.isEqual(ppgMetaData2));
}

TEST_F(PpgMetaDataTest, CompareDifferentWavelength) {
  PpgMetaData ppgMetaData1 = PpgMetaData(this->wavelengthNormal1_nm);
  PpgMetaData ppgMetaData2 = PpgMetaData(this->wavelengthNormal2_nm);
  EXPECT_FALSE(ppgMetaData1.isEqual(ppgMetaData2));
}

TEST_F(PpgMetaDataTest, CompareEqualNotSet) {
  PpgMetaData ppgMetaData1 = PpgMetaData();
  PpgMetaData ppgMetaData2 = PpgMetaData();
  EXPECT_TRUE(ppgMetaData1.isEqual(ppgMetaData2));
}

TEST_F(PpgMetaDataTest, CompareColorWithWavelength) {
  PpgMetaData ppgMetaData1 = PpgMetaData(ProtobufColor::COLOR_GREEN);
  PpgMetaData ppgMetaData2 = PpgMetaData(this->wavelengthNormal2_nm);
  EXPECT_FALSE(ppgMetaData1.isEqual(ppgMetaData2));
}

TEST_F(PpgMetaDataTest, TestSerizlize) {
  PpgMetaData ppgMetaDataW1 = PpgMetaData(this->wavelengthNormal1_nm);
  PpgMetaData ppgMetaDataR1 = PpgMetaData(ProtobufColor::COLOR_RED);
  PpgMetaData ppgMetaDataG1 = PpgMetaData(ProtobufColor::COLOR_GREEN);
  PpgMetaData ppgMetaDataB1 = PpgMetaData(ProtobufColor::COLOR_BLUE);
  ProtobufPpgMetaData protobufPpgMetaDataW1;
  ProtobufPpgMetaData protobufPpgMetaDataR1;
  ProtobufPpgMetaData protobufPpgMetaDataG1;
  ProtobufPpgMetaData protobufPpgMetaDataB1;
  ppgMetaDataW1.serialize(&protobufPpgMetaDataW1);
  ppgMetaDataR1.serialize(&protobufPpgMetaDataR1);
  ppgMetaDataG1.serialize(&protobufPpgMetaDataG1);
  ppgMetaDataB1.serialize(&protobufPpgMetaDataB1);
  PpgMetaData ppgMetaDataW2 = PpgMetaData(protobufPpgMetaDataW1);
  PpgMetaData ppgMetaDataR2 = PpgMetaData(protobufPpgMetaDataR1);
  PpgMetaData ppgMetaDataG2 = PpgMetaData(protobufPpgMetaDataG1);
  PpgMetaData ppgMetaDataB2 = PpgMetaData(protobufPpgMetaDataB1);
  EXPECT_TRUE(ppgMetaDataW1.isEqual(ppgMetaDataW2));
  EXPECT_TRUE(ppgMetaDataR1.isEqual(ppgMetaDataR2));
  EXPECT_TRUE(ppgMetaDataG1.isEqual(ppgMetaDataG2));
  EXPECT_TRUE(ppgMetaDataB1.isEqual(ppgMetaDataB2));
}

TEST_F(PpgMetaDataTest, TestSerializeNoThrow) {
  PpgMetaData ppgMetaDataG1 = PpgMetaData(ProtobufColor::COLOR_GREEN);
  ProtobufPpgMetaData protobufData;
  EXPECT_NO_THROW(ppgMetaDataG1.serialize(&protobufData));
}

TEST_F(PpgMetaDataTest, TestSerializeThrow) {
  PpgMetaData ppgMetaDataG1 = PpgMetaData(ProtobufColor::COLOR_GREEN);
  ProtobufPpgMetaData* protobufData = nullptr;
  EXPECT_THROW(ppgMetaDataG1.serialize(protobufData), std::invalid_argument);
}

TEST_F(PpgMetaDataTest, TestToJson) {
  PpgMetaData ppgMetaDataW1 = PpgMetaData(this->wavelengthNormal1_nm);
  PpgMetaData ppgMetaDataR1 = PpgMetaData(ProtobufColor::COLOR_RED);
  PpgMetaData ppgMetaDataG1 = PpgMetaData(ProtobufColor::COLOR_GREEN);
  PpgMetaData ppgMetaDataB1 = PpgMetaData(ProtobufColor::COLOR_BLUE);
  PpgMetaDataJson ppgMetaDataJsonW1 = ppgMetaDataW1.toJson();
  PpgMetaDataJson ppgMetaDataJsonR1 = ppgMetaDataR1.toJson();
  PpgMetaDataJson ppgMetaDataJsonG1 = ppgMetaDataG1.toJson();
  PpgMetaDataJson ppgMetaDataJsonB1 = ppgMetaDataB1.toJson();
  PpgMetaDataJson ppgMetaDataJsonW2 = PpgMetaDataExampleFactory::buildPpgMetaDataJson(this->wavelengthNormal1_nm);
  PpgMetaDataJson ppgMetaDataJsonR2 = PpgMetaDataExampleFactory::buildPpgMetaDataJson(ProtobufColor::COLOR_RED);
  PpgMetaDataJson ppgMetaDataJsonG2 = PpgMetaDataExampleFactory::buildPpgMetaDataJson(ProtobufColor::COLOR_GREEN);
  PpgMetaDataJson ppgMetaDataJsonB2 = PpgMetaDataExampleFactory::buildPpgMetaDataJson(ProtobufColor::COLOR_BLUE);
  EXPECT_TRUE(ppgMetaDataJsonW1 == ppgMetaDataJsonW2);
  EXPECT_TRUE(ppgMetaDataJsonR1 == ppgMetaDataJsonR2);
  EXPECT_TRUE(ppgMetaDataJsonG1 == ppgMetaDataJsonG2);
  EXPECT_TRUE(ppgMetaDataJsonB1 == ppgMetaDataJsonB2);
}
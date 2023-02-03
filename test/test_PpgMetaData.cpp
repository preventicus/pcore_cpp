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
#include "PpgMetaData.h"

class PpgMetaDataTest : public ::testing::Test {
 protected:
  PpgMetaData ppgMetDataWithColorGreen1;
  PpgMetaData ppgMetDataWithColorGreen2;
  PpgMetaData ppgMetDataWithColorBlue1;
  PpgMetaData ppgMetDataWithColorBlue2;
  PpgMetaData ppgMetDataWithColorRed1;
  PpgMetaData ppgMetDataWithColorRed2;
  PpgMetaData ppgMetDataWithWavelength1;
  PpgMetaData ppgMetDataWithWavelength2;
  PpgMetaData PpgMetaDataBothNotSet1;
  PpgMetaData PpgMetaDataBothNotSet2;
  uint32_t normalWavelength_nm = 255;
  uint32_t noWavelength_nm = 0;
  virtual void SetUp() {
    this->ppgMetDataWithColorGreen1 = PpgMetaData(ProtobufColor::COLOR_GREEN, this->noWavelength_nm);
    this->ppgMetDataWithColorGreen2 = PpgMetaData(ProtobufColor::COLOR_GREEN, this->noWavelength_nm);
    this->ppgMetDataWithColorBlue1 = PpgMetaData(ProtobufColor::COLOR_BLUE, this->noWavelength_nm);
    this->ppgMetDataWithColorBlue2 = PpgMetaData(ProtobufColor::COLOR_BLUE, this->noWavelength_nm);
    this->ppgMetDataWithColorRed1 = PpgMetaData(ProtobufColor::COLOR_RED, this->noWavelength_nm);
    this->ppgMetDataWithColorRed2 = PpgMetaData(ProtobufColor::COLOR_RED, this->noWavelength_nm);
    this->ppgMetDataWithWavelength1 = PpgMetaData(ProtobufColor::COLOR_NONE, this->normalWavelength_nm);
    this->ppgMetDataWithWavelength2 = PpgMetaData(ProtobufColor::COLOR_NONE, this->normalWavelength_nm);
    this->PpgMetaDataBothNotSet1 = PpgMetaData(ProtobufColor::COLOR_NONE, this->noWavelength_nm);
    this->PpgMetaDataBothNotSet2 = PpgMetaData(ProtobufColor::COLOR_NONE, this->noWavelength_nm);
  }
};

TEST_F(PpgMetaDataTest, TestGetColor) {
  EXPECT_EQ(this->ppgMetDataWithColorGreen1.getColor(), ProtobufColor::COLOR_GREEN);
  EXPECT_EQ(this->ppgMetDataWithColorGreen1.getWavelength(), this->noWavelength_nm);
}

TEST_F(PpgMetaDataTest, TestGetWavelength) {
  EXPECT_EQ(ppgMetDataWithWavelength1.getColor(), ProtobufColor::COLOR_NONE);
  EXPECT_EQ(ppgMetDataWithWavelength1.getWavelength(), this->normalWavelength_nm);
}

TEST_F(PpgMetaDataTest, TestThrowEXceptionWavelengthAndColor) {
  EXPECT_THROW(PpgMetaData ppg = PpgMetaData(ProtobufColor::COLOR_GREEN, this->normalWavelength_nm), std::invalid_argument);
}

TEST_F(PpgMetaDataTest, TestNotThrowExceptionWavelengthAndColor) {
  EXPECT_NO_THROW(PpgMetaData ppg = PpgMetaData(ProtobufColor::COLOR_GREEN, this->noWavelength_nm));
}

TEST_F(PpgMetaDataTest, TestIsNotSet) {
  EXPECT_EQ(this->PpgMetaDataBothNotSet1.isSet(), false);
}

TEST_F(PpgMetaDataTest, TestIsSet) {
  EXPECT_EQ(this->ppgMetDataWithColorBlue1.isSet(), true);
}

TEST_F(PpgMetaDataTest, CompareEqualColorGreenAndEqualWavelength) {
  EXPECT_TRUE(this->ppgMetDataWithWavelength1.isEqual(this->ppgMetDataWithWavelength2));
}

TEST_F(PpgMetaDataTest, CompareEqualColorGreenAndDifferentWavelength) {
  EXPECT_FALSE(this->ppgMetDataWithWavelength1.isEqual(this->ppgMetDataWithColorGreen1));
}

TEST_F(PpgMetaDataTest, CompareDifferentColorAndEqualWavelength) {
  EXPECT_FALSE(this->ppgMetDataWithColorBlue1.isEqual(this->ppgMetDataWithColorGreen1));
}

TEST_F(PpgMetaDataTest, CompareSetWavelength) {
  EXPECT_TRUE(this->ppgMetDataWithColorRed1.isEqual(this->ppgMetDataWithColorRed2));
}

TEST_F(PpgMetaDataTest, CompareSerializeAndDeserializeMethodColorGreen) {
  ProtobufPpgMetaData protobufPpgMetaData;
  this->ppgMetDataWithColorGreen1.serialize(&protobufPpgMetaData);
  PpgMetaData ppg = PpgMetaData(protobufPpgMetaData);
  EXPECT_TRUE(this->ppgMetDataWithColorGreen1.isEqual(ppg));
}

TEST_F(PpgMetaDataTest, CompareSerializeAndDeserializeMethodDifferentColor) {
  ProtobufPpgMetaData protobufPpgMetaData1;
  this->ppgMetDataWithColorBlue1.serialize(&protobufPpgMetaData1);
  PpgMetaData basePpg = PpgMetaData(protobufPpgMetaData1);
  ProtobufPpgMetaData protobufPpgMetaData2;
  this->ppgMetDataWithColorGreen1.serialize(&protobufPpgMetaData2);
  PpgMetaData comparablePpg = PpgMetaData(protobufPpgMetaData2);
  EXPECT_FALSE(basePpg.isEqual(comparablePpg));
}

TEST_F(PpgMetaDataTest, CompareSerializeAndDeserializeMethodSameColor) {
  ProtobufPpgMetaData protobufPpgMetaData1;
  this->ppgMetDataWithColorBlue1.serialize(&protobufPpgMetaData1);
  PpgMetaData basePpg = PpgMetaData(protobufPpgMetaData1);
  ProtobufPpgMetaData protobufPpgMetaData2;
  this->ppgMetDataWithColorBlue2.serialize(&protobufPpgMetaData2);
  PpgMetaData comparablePpg = PpgMetaData(protobufPpgMetaData2);
  EXPECT_TRUE(basePpg.isEqual(comparablePpg));
}

TEST_F(PpgMetaDataTest, CompareSerializeAndDeserializeMethodDifferentWavelength) {
  ProtobufPpgMetaData protobufPpgMetaData1;
  this->ppgMetDataWithWavelength1.serialize(&protobufPpgMetaData1);
  PpgMetaData basePpg = PpgMetaData(protobufPpgMetaData1);
  ProtobufPpgMetaData protobufPpgMetaData2;
  this->PpgMetaDataBothNotSet1.serialize(&protobufPpgMetaData2);
  PpgMetaData comparablePpg = PpgMetaData(protobufPpgMetaData2);
  EXPECT_FALSE(basePpg.isEqual(comparablePpg));
}

TEST_F(PpgMetaDataTest, CompareSerializeAndDeserializeMethodSameWavelength) {
  ProtobufPpgMetaData protobufPpgMetaData1;
  this->ppgMetDataWithWavelength1.serialize(&protobufPpgMetaData1);
  PpgMetaData basePpg = PpgMetaData(protobufPpgMetaData1);
  ProtobufPpgMetaData protobufPpgMetaData2;
  this->ppgMetDataWithWavelength2.serialize(&protobufPpgMetaData2);
  PpgMetaData comparablePpg = PpgMetaData(protobufPpgMetaData2);
  EXPECT_TRUE(basePpg.isEqual(comparablePpg));
}

TEST_F(PpgMetaDataTest, CheckPpgPtr) {
  ProtobufPpgMetaData protobufData;
  this->ppgMetDataWithColorGreen1.serialize(&protobufData);
  PpgMetaData ppg = PpgMetaData(protobufData);
  ProtobufPpgMetaData* protobufDataPtr = &protobufData;
  PpgMetaData* ptr = &ppg;
  EXPECT_FALSE(ptr == nullptr);
  EXPECT_FALSE(protobufDataPtr == nullptr);
}

TEST_F(PpgMetaDataTest, CheckNullPpgPtr) {
  ProtobufPpgMetaData* protobufData = nullptr;
  EXPECT_THROW(this->ppgMetDataWithColorGreen1.serialize(protobufData), std::invalid_argument);
}
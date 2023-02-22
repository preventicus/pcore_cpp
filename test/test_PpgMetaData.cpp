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
  uint32_t noWavelength_mn = PpgMetaDataExampleFactory::noWavelength_nm();

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

TEST_F(PpgMetaDataTest, TestGetColor) {
  EXPECT_EQ(ppgMetDataWithColorGreen1.getColor(), ProtobufColor::COLOR_GREEN);
  EXPECT_EQ(ppgMetDataWithColorGreen1.getWavelength(), this->noWavelength_mn);
}

TEST_F(PpgMetaDataTest, TestGetWavelength) {
  EXPECT_EQ(ppgMetDataWithWavelength1.getColor(), ProtobufColor::COLOR_NONE);
  EXPECT_EQ(ppgMetDataWithWavelength1.getWavelength(), PpgMetaDataExampleFactory::normalWavelength_nm());
}

TEST_F(PpgMetaDataTest, TestEmptyConstructor) {
  EXPECT_EQ(PpgMetaDataNotSet1.getColor(), ProtobufColor::COLOR_NONE);
  EXPECT_EQ(PpgMetaDataNotSet1.getWavelength(), this->noWavelength_mn);
}

TEST_F(PpgMetaDataTest, TestIsNotSet) {
  EXPECT_EQ(this->PpgMetaDataNotSet1.isSet(), false);
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

TEST_F(PpgMetaDataTest, CompareEqualColorGreen) {
  EXPECT_TRUE(this->ppgMetDataWithColorGreen1.isEqual(this->ppgMetDataWithColorGreen2));
}

TEST_F(PpgMetaDataTest, CompareNotSetPpgMetData) {
  EXPECT_TRUE(this->PpgMetaDataNotSet1.isEqual(this->PpgMetaDataNotSet2));
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
  this->PpgMetaDataNotSet1.serialize(&protobufPpgMetaData2);
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
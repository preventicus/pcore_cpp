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
#include "DataExampleFactory.h"

class DataTest : public ::testing::Test {
 protected:
  Data normalDataWithAccMetaData1 = DataExampleFactory::normalData();
  Data normalDataWithAccMetaData2 = DataExampleFactory::normalData();
  Data comparableDataPpgMetaData1 = DataExampleFactory::comparableData();
  Data comparableDataPpgMetaData2 = DataExampleFactory::comparableData();
};

TEST_F(DataTest, TestGetMethodData) {
  Raw raw = this->normalDataWithAccMetaData1.getRaw();
  Raw comparableRaw = RawExampleFactory::normalRaw();
  EXPECT_TRUE(raw.isEqual(comparableRaw));
  Header header = HeaderExampleFactory::normalHeaderWithPositiveTimeZoneOffset_min();
  EXPECT_TRUE(this->normalDataWithAccMetaData1.getHeader().isEqual(header));
}

TEST_F(DataTest, CompareEqualNormalData) {
  EXPECT_TRUE(this->normalDataWithAccMetaData1.isEqual(this->normalDataWithAccMetaData2));
}

TEST_F(DataTest, CompareDifferentData) {
  EXPECT_FALSE(this->comparableDataPpgMetaData1.isEqual(this->normalDataWithAccMetaData1));
}

TEST_F(DataTest, CompareEqualComparableData) {
  EXPECT_TRUE(this->comparableDataPpgMetaData1.isEqual(this->comparableDataPpgMetaData2));
}

TEST_F(DataTest, TestSerializeAndDeserializeData) {
  ProtobufData protobufData;
  this->normalDataWithAccMetaData1.serialize(&protobufData);
  Data data = Data(protobufData);
  EXPECT_TRUE(this->normalDataWithAccMetaData1.isEqual(data));
}

TEST_F(DataTest, TestSerializeAndDeserializeComparableData) {
  ProtobufData protobufData;
  this->comparableDataPpgMetaData1.serialize(&protobufData);
  Data data = Data(protobufData);
  EXPECT_TRUE(this->comparableDataPpgMetaData1.isEqual(data));
}

TEST_F(DataTest, TestSerializeAndDeserializeTwoComparableData) {
  ProtobufData protobufData1;
  this->comparableDataPpgMetaData1.serialize(&protobufData1);
  Data standardData = Data(protobufData1);
  ProtobufData protobufData2;
  this->comparableDataPpgMetaData2.serialize(&protobufData2);
  Data comparableData = Data(protobufData2);
  EXPECT_TRUE(standardData.isEqual(comparableData));
}

TEST_F(DataTest, TestSerializeAndDeserializeTwoNormalData) {
  ProtobufData protobufData1;
  this->normalDataWithAccMetaData1.serialize(&protobufData1);
  Data standardData = Data(protobufData1);
  ProtobufData protobufData2;
  this->normalDataWithAccMetaData2.serialize(&protobufData2);
  Data comparableData = Data(protobufData2);
  EXPECT_TRUE(standardData.isEqual(comparableData));
}

TEST_F(DataTest, CheckDataPtr) {
  ProtobufData protobufData;
  EXPECT_NO_THROW(this->comparableDataPpgMetaData1.serialize(&protobufData));
}

TEST_F(DataTest, CheckDataNullPtr) {
  ProtobufData* protobufData = nullptr;
  EXPECT_THROW(this->comparableDataPpgMetaData1.serialize(protobufData), std::invalid_argument);
}
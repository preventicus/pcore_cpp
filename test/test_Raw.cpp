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
#include "RawExampleFactory.h"

class RawTest : public ::testing::Test {
 protected:
  Raw normalRawWithAccMetaData1 = RawExampleFactory::normalRaw();
  Raw normalRawWithAccMetaData2 = RawExampleFactory::normalRaw();
  Raw comparableRawWithPpgMetaData1 = RawExampleFactory::comparableRaw();
  Raw comparableRawWithPpgMetaData2 = RawExampleFactory::comparableRaw();
};

TEST_F(RawTest, TestGetMethodeRaw) {
  std::vector<Sensor> sensors = this->normalRawWithAccMetaData1.getSensors();
  std::vector<Sensor> comparableSensors = SensorExampleFactory::normalVectorWithSensors();
  for (size_t i = 0; i < sensors.size(); i++) {
    EXPECT_TRUE(sensors[i].isEqual(comparableSensors[i]));
  }
}

TEST_F(RawTest, CompareEqualNormalRaw) {
  EXPECT_TRUE(this->normalRawWithAccMetaData1.isEqual(this->normalRawWithAccMetaData2));
}

TEST_F(RawTest, CompareDifferentRaw) {
  EXPECT_FALSE(this->normalRawWithAccMetaData1.isEqual(this->comparableRawWithPpgMetaData1));
}

TEST_F(RawTest, CompareEqualComparableRaw) {
  EXPECT_TRUE(this->comparableRawWithPpgMetaData1.isEqual(this->comparableRawWithPpgMetaData2));
}

TEST_F(RawTest, TestSerializeAndDeserializeNormalRaw) {
  ProtobufRaw protobufRaw;
  this->normalRawWithAccMetaData1.serialize(&protobufRaw);
  Raw raw = Raw(protobufRaw);
  EXPECT_TRUE(this->normalRawWithAccMetaData1.isEqual(raw));
}

TEST_F(RawTest, TestSerializeAndDeserializeComparableRaw) {
  ProtobufRaw protobufRaw;
  this->comparableRawWithPpgMetaData1.serialize(&protobufRaw);
  Raw raw = Raw(protobufRaw);
  EXPECT_TRUE(this->comparableRawWithPpgMetaData1.isEqual(raw));
}

TEST_F(RawTest, TestSerializeAndDeserializeEqualDifferentRaw) {
  ProtobufRaw protobufRaw1;
  this->normalRawWithAccMetaData1.serialize(&protobufRaw1);
  Raw raw1 = Raw(protobufRaw1);
  ProtobufRaw protobufRaw2;
  this->normalRawWithAccMetaData1.serialize(&protobufRaw2);
  Raw raw2 = Raw(protobufRaw2);
  EXPECT_TRUE(raw1.isEqual(raw2));
}

TEST_F(RawTest, TestSerializeAndDeserializeTwoDifferentRaw) {
  ProtobufRaw protobufRaw1;
  this->normalRawWithAccMetaData1.serialize(&protobufRaw1);
  Raw raw1 = Raw(protobufRaw1);
  ProtobufRaw protobufRaw2;
  this->comparableRawWithPpgMetaData1.serialize(&protobufRaw2);
  Raw raw2 = Raw(protobufRaw2);
  EXPECT_FALSE(raw1.isEqual(raw2));
}

TEST_F(RawTest, CheckRawPtr) {
  ProtobufRaw protobufRaw1;
  EXPECT_NO_THROW(this->normalRawWithAccMetaData1.serialize(&protobufRaw1));
}

TEST_F(RawTest, CheckRawNullPtr) {
  ProtobufRaw* protobufRaw1 = nullptr;
  EXPECT_THROW(this->normalRawWithAccMetaData1.serialize(protobufRaw1), std::invalid_argument);
}
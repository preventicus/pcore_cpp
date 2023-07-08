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
#include "RawExampleFactory.h"

class RawTest : public ::testing::Test {
 protected:
};

TEST_F(RawTest, TestGetSensorWithSensorPpgWithTwoChannelsInDifferentialForm) {
  Sensor sensor = SensorExampleFactory::sensorPpgWithTwoChannelsInDifferentialForm();
  Raw raw = RawExampleFactory::rawWithOneSensorsPpgWithTwoChannelsInDifferentialForm();
  Sensors sensors = raw.getSensors();
  EXPECT_EQ(sensors.size(), 1);
  EXPECT_TRUE(sensors[0].isEqual(sensor));
}

TEST_F(RawTest, TestIsEqualWithRawWithOneSensorAccWithTwoChannelsInAbsoluteForm) {
  Raw raw1 = RawExampleFactory::rawWithOneSensorAccWithTwoChannelsInAbsoluteForm();
  Raw raw2 = RawExampleFactory::rawWithOneSensorAccWithTwoChannelsInAbsoluteForm();
  EXPECT_TRUE(raw1.isEqual(raw2));
}

TEST_F(RawTest, TestIsEqualWithRawEmpty) {
  Raw raw1 = RawExampleFactory::rawEmpty();
  Raw raw2 = RawExampleFactory::rawEmpty();
  EXPECT_TRUE(raw1.isEqual(raw2));
}

TEST_F(RawTest, TestIsEqualWithRawWithOneSensorAndRawWithTwoSensors) {
  Raw raw1 = RawExampleFactory::rawWithTwoSensorsPpgWithTwoChannelsInDifferentialForm();
  Raw raw2 = RawExampleFactory::rawWithOneSensorsPpgWithTwoChannelsInDifferentialForm();
  EXPECT_FALSE(raw1.isEqual(raw2));
}

TEST_F(RawTest, TestIsEqualWithRawEmptyAndRawWithOneSensors) {
  Raw raw1 = RawExampleFactory::rawEmpty();
  Raw raw2 = RawExampleFactory::rawWithOneSensorsPpgWithTwoChannelsInDifferentialForm();
  EXPECT_FALSE(raw1.isEqual(raw2));
}

TEST_F(RawTest, TestIsEqualWithRawWithOneSensorAccWithTwoChannelsInAbsoluteFormAndRawWithOneSensorsPpgWithTwoChannelsInDifferentialForm) {
  Raw raw1 = RawExampleFactory::rawWithOneSensorAccWithTwoChannelsInAbsoluteForm();
  Raw raw2 = RawExampleFactory::rawWithOneSensorsPpgWithTwoChannelsInDifferentialForm();
  EXPECT_FALSE(raw1.isEqual(raw2));
}

TEST_F(RawTest, TestSerializeWithRawWithOneSensorsPpgWithTwoChannelsInDifferentialForm) {
  Raw raw1 = RawExampleFactory::rawWithOneSensorsPpgWithTwoChannelsInDifferentialForm();
  ProtobufRaw protobufRaw;
  raw1.serialize(&protobufRaw);
  Raw raw2 = Raw(protobufRaw);
  EXPECT_TRUE(raw1.isEqual(raw2));
}

TEST_F(RawTest, TestSerializeWithRawWithTwoSensorsPpgWithTwoChannelsInDifferentialForm) {
  Raw raw1 = RawExampleFactory::rawWithTwoSensorsPpgWithTwoChannelsInDifferentialForm();
  ProtobufRaw protobufRaw;
  raw1.serialize(&protobufRaw);
  Raw raw2 = Raw(protobufRaw);
  EXPECT_TRUE(raw1.isEqual(raw2));
}

TEST_F(RawTest, TestSerializeWithRawWithOneSensorsAccWithTwoChannelsInDifferentialForm) {
  Raw raw1 = RawExampleFactory::rawWithOneSensorAccWithTwoChannelsInDifferentialForm();
  ProtobufRaw protobufRaw;
  raw1.serialize(&protobufRaw);
  Raw raw2 = Raw(protobufRaw);
  EXPECT_TRUE(raw1.isEqual(raw2));
}

TEST_F(RawTest, TestSerializeWithRawEmpty) {
  Raw raw1 = RawExampleFactory::rawEmpty();
  ProtobufRaw protobufRaw;
  raw1.serialize(&protobufRaw);
  Raw raw2 = Raw(protobufRaw);
  EXPECT_TRUE(raw1.isEqual(raw2));
}

TEST_F(RawTest, TestSerializeNoThrow) {
  Raw raw = RawExampleFactory::rawWithTwoSensorsPpgWithTwoChannelsInDifferentialForm();
  ProtobufRaw protobufRaw;
  EXPECT_NO_THROW(raw.serialize(&protobufRaw));
}

TEST_F(RawTest, TestSerializeThrow) {
  Raw raw = RawExampleFactory::rawEmpty();
  ProtobufRaw* protobufRaw = nullptr;
  EXPECT_THROW(raw.serialize(protobufRaw), std::invalid_argument);
}

TEST_F(RawTest, TestSwitchDataFormWithRawForSwitschDataFormTestInAbsoluteForm) {
  Raw raw = RawExampleFactory::rawForSwitchDataFormTestInAbsoluteForm();
  raw.switchDataForm(DataForm::DATA_FORM_ABSOLUTE);
  Raw rawInDifferentialForm = RawExampleFactory::rawForSwitchDataFormTestInDifferentialForm();
  EXPECT_TRUE(raw.isEqual(rawInDifferentialForm));
}

TEST_F(RawTest, TestSwitchDataFormWith) {
  Raw raw = RawExampleFactory::rawForSwitchDataFormTestInDifferentialForm();
  raw.switchDataForm(DataForm::DATA_FORM_DIFFERENTIAL);
  Raw rawInAbsoluteForm = RawExampleFactory::rawForSwitchDataFormTestInAbsoluteForm();
  EXPECT_TRUE(raw.isEqual(rawInAbsoluteForm));
}
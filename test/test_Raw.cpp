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

TEST(RawTest, TestGetSensorWithSensorPpgWithTwoChannelsInDifferentialForm) {
  auto sensor = SensorExampleFactory::sensorPpgWithTwoChannelsInDifferentialForm();
  auto raw = RawExampleFactory::rawWithOneSensorsPpgWithTwoChannelsInDifferentialForm();
  auto sensors = raw.getSensors();
  EXPECT_EQ(sensors.size(), 1);
  EXPECT_TRUE(sensors[0] == sensor);
}

TEST(RawTest, TestIsEqualWithRawWithOneSensorAccWithTwoChannelsInAbsoluteForm) {
  auto raw1 = RawExampleFactory::rawWithOneSensorAccWithTwoChannelsInAbsoluteForm();
  auto raw2 = RawExampleFactory::rawWithOneSensorAccWithTwoChannelsInAbsoluteForm();
  EXPECT_TRUE(raw1 == raw2);
}

TEST(RawTest, TestIsEqualWithRawEmpty) {
  auto raw1 = RawExampleFactory::rawEmpty();
  auto raw2 = RawExampleFactory::rawEmpty();
  EXPECT_TRUE(raw1 == raw2);
}

TEST(RawTest, TestIsEqualWithRawWithOneSensorAndRawWithTwoSensors) {
  auto raw1 = RawExampleFactory::rawWithTwoSensorsPpgWithTwoChannelsInDifferentialForm();
  auto raw2 = RawExampleFactory::rawWithOneSensorsPpgWithTwoChannelsInDifferentialForm();
  EXPECT_FALSE(raw1 == raw2);
}

TEST(RawTest, TestIsEqualWithRawEmptyAndRawWithOneSensors) {
  auto raw1 = RawExampleFactory::rawEmpty();
  auto raw2 = RawExampleFactory::rawWithOneSensorsPpgWithTwoChannelsInDifferentialForm();
  EXPECT_FALSE(raw1 == raw2);
}

TEST(RawTest, TestIsEqualWithRawWithOneSensorAccWithTwoChannelsInAbsoluteFormAndRawWithOneSensorsPpgWithTwoChannelsInDifferentialForm) {
  auto raw1 = RawExampleFactory::rawWithOneSensorAccWithTwoChannelsInAbsoluteForm();
  auto raw2 = RawExampleFactory::rawWithOneSensorsPpgWithTwoChannelsInDifferentialForm();
  EXPECT_FALSE(raw1 == raw2);
}

TEST(RawTest, TestIsNotEqualWithRawWithOneSensorAccWithTwoChannelsInAbsoluteForm) {
  auto raw1 = RawExampleFactory::rawWithOneSensorAccWithTwoChannelsInAbsoluteForm();
  auto raw2 = RawExampleFactory::rawWithOneSensorAccWithTwoChannelsInAbsoluteForm();
  EXPECT_FALSE(raw1 != raw2);
}

TEST(RawTest, TestIsNotEqualWithRawEmpty) {
  auto raw1 = RawExampleFactory::rawEmpty();
  auto raw2 = RawExampleFactory::rawEmpty();
  EXPECT_FALSE(raw1 != raw2);
}

TEST(RawTest, TestIsNotEqualWithRawWithOneSensorAndRawWithTwoSensors) {
  auto raw1 = RawExampleFactory::rawWithTwoSensorsPpgWithTwoChannelsInDifferentialForm();
  auto raw2 = RawExampleFactory::rawWithOneSensorsPpgWithTwoChannelsInDifferentialForm();
  EXPECT_TRUE(raw1 != raw2);
}

TEST(RawTest, TestIsNotEqualWithRawEmptyAndRawWithOneSensors) {
  auto raw1 = RawExampleFactory::rawEmpty();
  auto raw2 = RawExampleFactory::rawWithOneSensorsPpgWithTwoChannelsInDifferentialForm();
  EXPECT_TRUE(raw1 != raw2);
}

TEST(RawTest, TestIsNotEqualWithRawWithOneSensorAccWithTwoChannelsInAbsoluteFormAndRawWithOneSensorsPpgWithTwoChannelsInDifferentialForm) {
  auto raw1 = RawExampleFactory::rawWithOneSensorAccWithTwoChannelsInAbsoluteForm();
  auto raw2 = RawExampleFactory::rawWithOneSensorsPpgWithTwoChannelsInDifferentialForm();
  EXPECT_TRUE(raw1 != raw2);
}

TEST(RawTest, TestSerializeWithRawWithOneSensorsPpgWithTwoChannelsInDifferentialForm) {
  auto raw1 = RawExampleFactory::rawWithOneSensorsPpgWithTwoChannelsInDifferentialForm();
  RawProtobuf rawProtobuf;
  raw1.serialize(&rawProtobuf);
  auto raw2 = Raw(rawProtobuf);
  EXPECT_TRUE(raw1 == raw2);
}

TEST(RawTest, TestSerializeWithRawWithTwoSensorsPpgWithTwoChannelsInDifferentialForm) {
  auto raw1 = RawExampleFactory::rawWithTwoSensorsPpgWithTwoChannelsInDifferentialForm();
  RawProtobuf rawProtobuf;
  raw1.serialize(&rawProtobuf);
  auto raw2 = Raw(rawProtobuf);
  EXPECT_TRUE(raw1 == raw2);
}

TEST(RawTest, TestSerializeWithRawWithOneSensorsAccWithTwoChannelsInDifferentialForm) {
  auto raw1 = RawExampleFactory::rawWithOneSensorAccWithTwoChannelsInDifferentialForm();
  RawProtobuf rawProtobuf;
  raw1.serialize(&rawProtobuf);
  auto raw2 = Raw(rawProtobuf);
  EXPECT_TRUE(raw1 == raw2);
}

TEST(RawTest, TestSerializeWithRawEmpty) {
  auto raw1 = RawExampleFactory::rawEmpty();
  RawProtobuf rawProtobuf;
  raw1.serialize(&rawProtobuf);
  auto raw2 = Raw(rawProtobuf);
  EXPECT_TRUE(raw1 == raw2);
}

TEST(RawTest, TestSerializeNoThrow) {
  auto raw = RawExampleFactory::rawWithTwoSensorsPpgWithTwoChannelsInDifferentialForm();
  RawProtobuf rawProtobuf;
  EXPECT_NO_THROW(raw.serialize(&rawProtobuf));
}

TEST(RawTest, TestSerializeThrow) {
  auto raw = RawExampleFactory::rawEmpty();
  RawProtobuf* rawProtobuf = nullptr;
  EXPECT_THROW(raw.serialize(rawProtobuf), std::invalid_argument);
}

TEST(RawTest, TestSwitchDataFormWithRawForSwitschDataFormTestInAbsoluteForm) {
  auto raw = RawExampleFactory::rawForSwitchDataFormTestInAbsoluteForm();
  raw.switchDataForm(DataForm::DATA_FORM_ABSOLUTE);
  auto rawInDifferentialForm = RawExampleFactory::rawForSwitchDataFormTestInDifferentialForm();
  EXPECT_TRUE(raw == rawInDifferentialForm);
}

TEST(RawTest, TestSwitchDataFormWith) {
  auto raw = RawExampleFactory::rawForSwitchDataFormTestInDifferentialForm();
  raw.switchDataForm(DataForm::DATA_FORM_DIFFERENTIAL);
  auto rawInAbsoluteForm = RawExampleFactory::rawForSwitchDataFormTestInAbsoluteForm();
  EXPECT_TRUE(raw == rawInAbsoluteForm);
}
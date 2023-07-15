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

TEST(RawTest, TestGetSensorWithSensorNotSet) {
  auto sensor = SensorExampleFactory::sensorNotSet();
  auto raw = RawExampleFactory::rawNotSet();
  auto sensors = raw.getSensors();
  EXPECT_TRUE(sensors.empty());
}

TEST(RawTest, TestGetDataFormWithRawWithSensorPpgWithTwoChannelsInDifferentialForm) {
  auto raw = RawExampleFactory::rawWithOneSensorsPpgWithTwoChannelsInDifferentialForm();
  EXPECT_TRUE(raw.getDataFrom() == DataForm::DATA_FORM_DIFFERENTIAL);
}

TEST(RawTest, TestGetDataFormWithRawWithOneSensorsPpgWithTwoChannelsInAbsoluteForm) {
  auto raw = RawExampleFactory::rawWithOneSensorsPpgWithTwoChannelsInAbsoluteForm();
  EXPECT_TRUE(raw.getDataFrom() == DataForm::DATA_FORM_ABSOLUTE);
}

TEST(RawTest, TestGetDataFormWithRawNotSet) {
  auto raw = RawExampleFactory::rawNotSet();
  EXPECT_TRUE(raw.getDataFrom() == DataForm::DATA_FORM_NONE);
}

TEST(RawTest, TestIsEqualWithRawWithOneSensorAccWithTwoChannelsInAbsoluteForm) {
  auto raw1 = RawExampleFactory::rawWithOneSensorAccWithTwoChannelsInAbsoluteForm();
  auto raw2 = RawExampleFactory::rawWithOneSensorAccWithTwoChannelsInAbsoluteForm();
  EXPECT_TRUE(raw1 == raw2);
}

TEST(RawTest, TestIsEqualWithRawNotSet) {
  auto raw1 = RawExampleFactory::rawNotSet();
  auto raw2 = RawExampleFactory::rawNotSet();
  EXPECT_TRUE(raw1 == raw2);
}

TEST(RawTest, TestIsEqualWithRawWithTwoSensorsPpgWithTwoChannelsInDifferentialFormAndRawWithOneSensorsPpgWithTwoChannelsInDifferentialForm) {
  auto raw1 = RawExampleFactory::rawWithTwoSensorsPpgWithTwoChannelsInDifferentialForm();
  auto raw2 = RawExampleFactory::rawWithOneSensorsPpgWithTwoChannelsInDifferentialForm();
  EXPECT_FALSE(raw1 == raw2);
}

TEST(RawTest, TestIsEqualWithrawNotSetAndRawWithOneSensorsPpgWithTwoChannelsInDifferentialForm) {
  auto raw1 = RawExampleFactory::rawNotSet();
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

TEST(RawTest, TestIsNotEqualWithRawNotSet) {
  auto raw1 = RawExampleFactory::rawNotSet();
  auto raw2 = RawExampleFactory::rawNotSet();
  EXPECT_FALSE(raw1 != raw2);
}

TEST(RawTest, TestIsNotEqualWithRawWithTwoSensorsPpgWithTwoChannelsInDifferentialFormAndRawWithOneSensorsPpgWithTwoChannelsInDifferentialForm) {
  auto raw1 = RawExampleFactory::rawWithTwoSensorsPpgWithTwoChannelsInDifferentialForm();
  auto raw2 = RawExampleFactory::rawWithOneSensorsPpgWithTwoChannelsInDifferentialForm();
  EXPECT_TRUE(raw1 != raw2);
}

TEST(RawTest, TestIsNotEqualWithRawNotSetAndRawWithOneSensorsPpgWithTwoChannelsInDifferentialForm) {
  auto raw1 = RawExampleFactory::rawNotSet();
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

TEST(RawTest, TestSerializeWithRawNotSet) {
  auto raw1 = RawExampleFactory::rawNotSet();
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
  auto raw = RawExampleFactory::rawNotSet();
  RawProtobuf* rawProtobuf = nullptr;
  EXPECT_THROW(raw.serialize(rawProtobuf), std::invalid_argument);
}

TEST(RawTest, TestSwitchDataFormWithRawForSwitschDataFormTestInAbsoluteForm) {
  auto raw = RawExampleFactory::rawForSwitchDataFormTestInAbsoluteForm();
  raw.switchDataForm();
  auto rawInDifferentialForm = RawExampleFactory::rawForSwitchDataFormTestInDifferentialForm();
  EXPECT_TRUE(raw == rawInDifferentialForm);
}

TEST(RawTest, TestSwitchDataFormWithRawForSwitchDataFormTestInDifferentialForm) {
  auto raw = RawExampleFactory::rawForSwitchDataFormTestInDifferentialForm();
  raw.switchDataForm();
  auto rawInAbsoluteForm = RawExampleFactory::rawForSwitchDataFormTestInAbsoluteForm();
  EXPECT_TRUE(raw == rawInAbsoluteForm);
}

TEST(RawTest, TestSwitchDataFormWithRawNotSet) {
  auto raw = RawExampleFactory::rawNotSet();
  raw.switchDataForm();
  EXPECT_FALSE(raw.isSet());
}

TEST(RawTest, TestToJsonWithRawNotSet) {
  auto raw = RawExampleFactory::rawNotSet();
  auto rawJson1 = RawExampleFactory::buildRawJson(raw);
  auto rawJson2 = raw.toJson();
  EXPECT_TRUE(rawJson1.toStyledString() == rawJson2.toStyledString());
}

TEST(RawTest, TestToJsonWithRawWithOneSensorsPpgWithTwoChannelsInDifferentialForm) {
  auto raw = RawExampleFactory::rawWithOneSensorsPpgWithTwoChannelsInDifferentialForm();
  auto rawJson1 = RawExampleFactory::buildRawJson(raw);
  auto rawJson2 = raw.toJson();
  EXPECT_TRUE(rawJson1.toStyledString() == rawJson2.toStyledString());
}

TEST(RawTest, TestToJsonWithRawWithOneSensorAccWithTwoChannelsInAbsoluteForm) {
  auto raw = RawExampleFactory::rawWithOneSensorAccWithTwoChannelsInAbsoluteForm();
  auto rawJson1 = RawExampleFactory::buildRawJson(raw);
  auto rawJson2 = raw.toJson();
  EXPECT_TRUE(rawJson1.toStyledString() == rawJson2.toStyledString());
}

TEST(RawTest, TestToJsonWithRawWithTwoSensorsPpgWithTwoChannelsInDifferentialForm) {
  auto raw = RawExampleFactory::rawWithTwoSensorsPpgWithTwoChannelsInDifferentialForm();
  auto rawJson1 = RawExampleFactory::buildRawJson(raw);
  auto rawJson2 = raw.toJson();
  EXPECT_TRUE(rawJson1.toStyledString() == rawJson2.toStyledString());
}

TEST(RawTest, TestToJsonWithRawWithOneSensorsPpgWithTwoChannelsInAbsoluteForm) {
  auto raw = RawExampleFactory::rawWithOneSensorsPpgWithTwoChannelsInAbsoluteForm();
  auto rawJson1 = RawExampleFactory::buildRawJson(raw);
  auto rawJson2 = raw.toJson();
  EXPECT_TRUE(rawJson1.toStyledString() == rawJson2.toStyledString());
}

TEST(RawTest, TestToJsonWithRawWithOneSensorAccWithTwoChannelsInDifferentialForm) {
  auto raw = RawExampleFactory::rawWithOneSensorAccWithTwoChannelsInDifferentialForm();
  auto rawJson1 = RawExampleFactory::buildRawJson(raw);
  auto rawJson2 = raw.toJson();
  EXPECT_TRUE(rawJson1.toStyledString() == rawJson2.toStyledString());
}
/*

Created by Jakob Glueck, Steve Merschel 2023

Copyright © 2023 PREVENTICUS GmbH

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors
   may be used to endorse or promote products derived from this software
without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#include <gtest/gtest.h>

#include "SensorExampleFactory.h"

TEST(SensorTest, TestGetChannelsMethodWithSensorAccWithTwoChannelsInAbsoluteForm) {
  auto sensor = SensorExampleFactory::sensorAccWithTwoChannelsInAbsoluteForm();
  Channels channels1;
  channels1.emplace_back(ChannelExampleFactory::channelWithAbsoluteBlockAndAccMetaData());
  channels1.emplace_back(ChannelExampleFactory::channelWithAbsoluteBlockAndAccMetaData());
  auto channels2 = sensor.getChannels();
  for (size_t i = 0; i < channels1.size(); i++) {
    EXPECT_TRUE(channels1[i] == channels2[i]);
  }
}

TEST(SensorTest, TestGetSensorTypeMethodWithSensorAccWithTwoChannelsInAbsoluteForm) {
  auto sensor = SensorExampleFactory::sensorAccWithTwoChannelsInAbsoluteForm();
  EXPECT_EQ(sensor.getSensorType(), ProtobufSensorType::SENSOR_TYPE_ACC);
}

TEST(SensorTest, TestGetAbsoluteTimestampsMethodWithSensorAccWithTwoChannelsInAbsoluteForm) {
  auto sensor = SensorExampleFactory::sensorAccWithTwoChannelsInAbsoluteForm();
  auto absoluteTimestampsContainer1 = AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsContainerWithThreeBigTimestamps();
  auto absoluteTimestampsContainer2 = sensor.getAbsoluteTimestamps();
  EXPECT_TRUE(absoluteTimestampsContainer1 == absoluteTimestampsContainer2);
}

TEST(SensorTest, TestGetDifferentialTimestampsMethodWithSensorAccWithTwoChannelsInAbsoluteForm) {
  auto sensor = SensorExampleFactory::sensorAccWithTwoChannelsInAbsoluteForm();
  auto differentialTimestampsContainer1 = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerEmpty();
  auto differentialTimestampsContainer2 = sensor.getDifferentialTimestamps();
  EXPECT_TRUE(differentialTimestampsContainer1 == differentialTimestampsContainer2);
}

TEST(SensorTest, TestGetDifferentialTimestampsMethodWithSensorAccWithTwoChannelsInDifferentialForm) {
  auto sensor = SensorExampleFactory::sensorAccWithTwoChannelsInDifferentialForm();
  auto differentialTimestampsContainer1 = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithThreeBlocks();
  auto differentialTimestampsContainer2 = sensor.getDifferentialTimestamps();
  EXPECT_TRUE(differentialTimestampsContainer1 == differentialTimestampsContainer2);
}

TEST(SensorTest, TestGetAbsoluteTimestampsMethodWithSensorAccWithTwoChannelsInDifferentialForm) {
  auto sensor = SensorExampleFactory::sensorAccWithTwoChannelsInDifferentialForm();
  auto absoluteTimestampsContainer1 = AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsContainerWithTimestampsEmpty();
  auto absoluteTimestampsContainer2 = sensor.getAbsoluteTimestamps();
  EXPECT_TRUE(absoluteTimestampsContainer1 == absoluteTimestampsContainer2);
}

TEST(SensorTest, TestGetFirstUnixTimestampWithSensorAccWithTwoChannelsInDifferentialForm) {
  auto sensor = SensorExampleFactory::sensorAccWithTwoChannelsInDifferentialForm();
  auto firstUnixTimestamp1_ms = sensor.getFirstUnixTimestamp(DataForm::DATA_FORM_DIFFERENTIAL);
  auto firstUnixTimestamp2_ms = UnixTimestampsExampleFactory::firstTimestamp_ms();
  EXPECT_TRUE(firstUnixTimestamp1_ms == firstUnixTimestamp2_ms);
}

TEST(SensorTest, TestGetFirstUnixTimestampWithSensorAccWithTwoChannelsInAbsoluteForm) {
  auto sensor = SensorExampleFactory::sensorAccWithTwoChannelsInAbsoluteForm();
  auto firstUnixTimestamp1_ms = sensor.getFirstUnixTimestamp(DataForm::DATA_FORM_ABSOLUTE);
  auto firstUnixTimestamp2_ms = UnixTimestampsExampleFactory::firstTimestamp_ms();
  EXPECT_TRUE(firstUnixTimestamp1_ms == firstUnixTimestamp2_ms);
}

TEST(SensorTest, TestGetFirstUnixTimestampThrowRuntimeError) {
  auto sensor = SensorExampleFactory::sensorEmpty();
  EXPECT_THROW(std::ignore = sensor.getFirstUnixTimestamp(DataForm::DATA_FORM_ABSOLUTE), std::runtime_error);
}

TEST(SensorTest, TestGetFirstUnixTimestampThrowInvalideArgument) {
  auto sensor = SensorExampleFactory::sensorEmpty();
  EXPECT_THROW(std::ignore = sensor.getFirstUnixTimestamp(DataForm::DATA_FORM_NONE), std::invalid_argument);
}

TEST(SensorTest, TestGetLastUnixTimestampWithSensorAccWithTwoChannelsInAbsoluteForm) {
  auto sensor = SensorExampleFactory::sensorAccWithTwoChannelsInAbsoluteForm();
  auto lastUnixTimestamp1_ms = sensor.getLastUnixTimestamp(DataForm::DATA_FORM_ABSOLUTE);
  auto lastUnixTimestamp2_ms = UnixTimestampsExampleFactory::lastTimestamp_ms();
  EXPECT_TRUE(lastUnixTimestamp1_ms == lastUnixTimestamp2_ms);
}

TEST(SensorTest, TestGetLastUnixTimestampWithSensorAccWithTwoChannelsInDifferentialForm) {
  auto sensor = SensorExampleFactory::sensorAccWithTwoChannelsInDifferentialForm();
  auto lastUnixTimestamp1_ms = sensor.getLastUnixTimestamp(DataForm::DATA_FORM_DIFFERENTIAL);
  auto lastUnixTimestamp2_ms = UnixTimestampsExampleFactory::lastTimestamp_ms();
  EXPECT_TRUE(lastUnixTimestamp1_ms == lastUnixTimestamp2_ms);
}

TEST(SensorTest, TestGetLastUnixTimestampThrowRuntimeError) {
  auto sensor = SensorExampleFactory::sensorEmpty();
  EXPECT_THROW(std::ignore = sensor.getLastUnixTimestamp(DataForm::DATA_FORM_ABSOLUTE), std::runtime_error);
}

TEST(SensorTest, TestGetLastUnixTimestampThrowInvalidArgument) {
  auto sensor = SensorExampleFactory::sensorAccWithTwoChannelsInAbsoluteForm();
  EXPECT_THROW(std::ignore = sensor.getLastUnixTimestamp(DataForm::DATA_FORM_NONE), std::invalid_argument);
}

TEST(SensorTest, TestGetDurationWithSensorAccWithTwoChannelsInDifferentialForm) {
  auto sensor = SensorExampleFactory::sensorAccWithTwoChannelsInDifferentialForm();
  auto duration = sensor.getDuration(DataForm::DATA_FORM_DIFFERENTIAL);
  auto firstUnixTimestamp_ms = UnixTimestampsExampleFactory::firstTimestamp_ms();
  auto lastUnixTimestamp_ms = UnixTimestampsExampleFactory::lastTimestamp_ms();
  EXPECT_EQ(duration, lastUnixTimestamp_ms - firstUnixTimestamp_ms);
}

TEST(SensorTest, TestGetDurationWithSensorAccWithTwoChannelsInAbsoluteForm) {
  auto sensor = SensorExampleFactory::sensorAccWithTwoChannelsInAbsoluteForm();
  auto duration = sensor.getDuration(DataForm::DATA_FORM_ABSOLUTE);
  auto firstUnixTimestamp_ms = UnixTimestampsExampleFactory::firstTimestamp_ms();
  auto lastUnixTimestamp_ms = UnixTimestampsExampleFactory::lastTimestamp_ms();
  EXPECT_EQ(duration, lastUnixTimestamp_ms - firstUnixTimestamp_ms);
}

TEST(SensorTest, TestIsEqualWithSensorAccWithTwoChannelsInDifferentialForm) {
  auto sensor1 = SensorExampleFactory::sensorAccWithTwoChannelsInDifferentialForm();
  auto sensor2 = SensorExampleFactory::sensorAccWithTwoChannelsInDifferentialForm();
  EXPECT_TRUE(sensor1 == sensor2);
}

TEST(SensorTest, TestIsEqualWithSensorEmpty) {
  auto sensor1 = SensorExampleFactory::sensorEmpty();
  auto sensor2 = SensorExampleFactory::sensorEmpty();
  EXPECT_TRUE(sensor1 == sensor2);
}

TEST(SensorTest, TestIsEqualWithSensorEmptyAndSensorAccWithTwoChannelsInAbsoluteForm) {
  auto sensor1 = SensorExampleFactory::sensorEmpty();
  auto sensor2 = SensorExampleFactory::sensorAccWithTwoChannelsInAbsoluteForm();
  EXPECT_FALSE(sensor1 == sensor2);
}

TEST(SensorTest, TestIsEqualWithSensorAccWithTwoChannelsInDifferentialFormAndSensorAccWithTwoChannelsInAbsoluteForm) {
  auto sensor1 = SensorExampleFactory::sensorAccWithTwoChannelsInDifferentialForm();
  auto sensor2 = SensorExampleFactory::sensorAccWithTwoChannelsInAbsoluteForm();
  EXPECT_FALSE(sensor1 == sensor2);
}

TEST(SensorTest, TestIsEqualWithSensorAccWithTwoChannelsInDifferentialFormAndSensorPpgWithTwoChannelsInDifferentialForm) {
  auto sensor1 = SensorExampleFactory::sensorAccWithTwoChannelsInDifferentialForm();
  auto sensor2 = SensorExampleFactory::sensorPpgWithTwoChannelsInDifferentialForm();
  EXPECT_FALSE(sensor1 == sensor2);
}

TEST(SensorTest, TestIsEqualWithSensorPpgWithOneChannelsInAbsoluteFormAndSensorPpgWithTwoChannelsInAbsoluteForm) {
  auto sensor1 = SensorExampleFactory::sensorPpgWithOneChannelsInAbsoluteForm();
  auto sensor2 = SensorExampleFactory::sensorPpgWithTwoChannelsInAbsoluteForm();
  EXPECT_FALSE(sensor1 == sensor2);
}

TEST(SensorTest, TestIsNotEqualWithSensorAccWithTwoChannelsInDifferentialForm) {
  auto sensor1 = SensorExampleFactory::sensorAccWithTwoChannelsInDifferentialForm();
  auto sensor2 = SensorExampleFactory::sensorAccWithTwoChannelsInDifferentialForm();
  EXPECT_FALSE(sensor1 != sensor2);
}

TEST(SensorTest, TestIsNotEqualWithSensorEmpty) {
  auto sensor1 = SensorExampleFactory::sensorEmpty();
  auto sensor2 = SensorExampleFactory::sensorEmpty();
  EXPECT_FALSE(sensor1 != sensor2);
}

TEST(SensorTest, TestIsNotEqualWithSensorEmptyAndSensorAccWithTwoChannelsInAbsoluteForm) {
  auto sensor1 = SensorExampleFactory::sensorEmpty();
  auto sensor2 = SensorExampleFactory::sensorAccWithTwoChannelsInAbsoluteForm();
  EXPECT_TRUE(sensor1 != sensor2);
}

TEST(SensorTest, TestIsNotEqualWithSensorAccWithTwoChannelsInDifferentialFormAndSensorAccWithTwoChannelsInAbsoluteForm) {
  auto sensor1 = SensorExampleFactory::sensorAccWithTwoChannelsInDifferentialForm();
  auto sensor2 = SensorExampleFactory::sensorAccWithTwoChannelsInAbsoluteForm();
  EXPECT_TRUE(sensor1 != sensor2);
}

TEST(SensorTest, TestIsNotEqualWithSensorAccWithTwoChannelsInDifferentialFormAndSensorPpgWithTwoChannelsInDifferentialForm) {
  auto sensor1 = SensorExampleFactory::sensorAccWithTwoChannelsInDifferentialForm();
  auto sensor2 = SensorExampleFactory::sensorPpgWithTwoChannelsInDifferentialForm();
  EXPECT_TRUE(sensor1 != sensor2);
}

TEST(SensorTest, TestIsNotEqualWithSensorPpgWithOneChannelsInAbsoluteFormAndSensorPpgWithTwoChannelsInAbsoluteForm) {
  auto sensor1 = SensorExampleFactory::sensorPpgWithOneChannelsInAbsoluteForm();
  auto sensor2 = SensorExampleFactory::sensorPpgWithTwoChannelsInAbsoluteForm();
  EXPECT_TRUE(sensor1 != sensor2);
}

TEST(SensorTest, TestToJsonWithSensorPpgWithTwoChannelsInAbsoluteForm) {
  auto sensor = SensorExampleFactory::sensorPpgWithTwoChannelsInAbsoluteForm();
  auto sensorJson1 = SensorExampleFactory::buildSensorJson(sensor, DataForm::DATA_FORM_ABSOLUTE);
  auto sensorJson2 = sensor.toJson(DataForm::DATA_FORM_ABSOLUTE);
  EXPECT_TRUE(sensorJson1.toStyledString() == sensorJson2.toStyledString());
}

TEST(SensorTest, TestToJsonWithSensorEmpty) {
  auto sensor = SensorExampleFactory::sensorEmpty();
  auto sensorJson1 = SensorExampleFactory::buildSensorJson(sensor, DataForm::DATA_FORM_NONE);
  auto sensorJson2 = sensor.toJson(DataForm::DATA_FORM_NONE);
  EXPECT_TRUE(sensorJson1.toStyledString() == sensorJson2.toStyledString());
}

TEST(SensorTest, TestToJsonWithSensorAccWithTwoChannelsInDifferentialForm) {
  auto sensor = SensorExampleFactory::sensorAccWithTwoChannelsInDifferentialForm();
  auto sensorJson1 = SensorExampleFactory::buildSensorJson(sensor, DataForm::DATA_FORM_DIFFERENTIAL);
  auto sensorJson2 = sensor.toJson(DataForm::DATA_FORM_DIFFERENTIAL);
  EXPECT_TRUE(sensorJson1.toStyledString() == sensorJson2.toStyledString());
}

TEST(SensorTest, TestToJsonWithSensorAccWithTwoChannelsInAbsoluteForm) {
  auto sensor = SensorExampleFactory::sensorAccWithTwoChannelsInAbsoluteForm();
  auto sensorJson1 = SensorExampleFactory::buildSensorJson(sensor, DataForm::DATA_FORM_ABSOLUTE);
  auto sensorJson2 = sensor.toJson(DataForm::DATA_FORM_ABSOLUTE);
  EXPECT_TRUE(sensorJson1.toStyledString() == sensorJson2.toStyledString());
}

TEST(SensorTest, TestToJsonWithSensorPpgWithTwoChannelsInDifferentialForm) {
  auto sensor = SensorExampleFactory::sensorPpgWithTwoChannelsInDifferentialForm();
  auto sensorJson1 = SensorExampleFactory::buildSensorJson(sensor, DataForm::DATA_FORM_DIFFERENTIAL);
  auto sensorJson2 = sensor.toJson(DataForm::DATA_FORM_DIFFERENTIAL);
  EXPECT_TRUE(sensorJson1.toStyledString() == sensorJson2.toStyledString());
}

TEST(SensorTest, TestToJsonWithSensorPpgWithOneChannelsInAbsoluteForm) {
  auto sensor = SensorExampleFactory::sensorPpgWithOneChannelsInAbsoluteForm();
  auto sensorJson1 = SensorExampleFactory::buildSensorJson(sensor, DataForm::DATA_FORM_ABSOLUTE);
  auto sensorJson2 = sensor.toJson(DataForm::DATA_FORM_ABSOLUTE);
  EXPECT_TRUE(sensorJson1.toStyledString() == sensorJson2.toStyledString());
}

TEST(SensorTest, TestSerizlizeWithSensorAccWithTwoChannelsInDifferentialForm) {
  auto sensor1 = SensorExampleFactory::sensorAccWithTwoChannelsInDifferentialForm();
  ProtobufSensor protobufSensor;
  sensor1.serialize(&protobufSensor);
  auto sensor2 = Sensor(protobufSensor);
  EXPECT_TRUE(sensor1 == sensor2);
}

TEST(SensorTest, TestSerizlizeWithSensorEmpty) {
  auto sensor1 = SensorExampleFactory::sensorEmpty();
  ProtobufSensor protobufSensor;
  sensor1.serialize(&protobufSensor);
  auto sensor2 = Sensor(protobufSensor);
  EXPECT_TRUE(sensor1 == sensor2);
}

TEST(SensorTest, TestSerizlizeWithSensorPpgWithTwoChannelsInDifferentialForm) {
  auto sensor1 = SensorExampleFactory::sensorPpgWithTwoChannelsInDifferentialForm();
  ProtobufSensor protobufSensor;
  sensor1.serialize(&protobufSensor);
  auto sensor2 = Sensor(protobufSensor);
  EXPECT_TRUE(sensor1 == sensor2);
}

TEST(SensorTest, TestSerializeNoThrow) {
  auto sensor = SensorExampleFactory::sensorPpgWithTwoChannelsInDifferentialForm();
  ProtobufSensor protobufSensor;
  EXPECT_NO_THROW(sensor.serialize(&protobufSensor));
}

TEST(SensorTest, TestSerializeThrow) {
  auto sensor = SensorExampleFactory::sensorEmpty();
  ProtobufSensor* protobufSensor = nullptr;
  EXPECT_THROW(sensor.serialize(protobufSensor), std::invalid_argument);
}

TEST(SensorTest, TestSwitchDataFormWithSensorForSwitchDataFromTestInAbsoluteForm) {
  auto sensor = SensorExampleFactory::sensorForSwitchDataFromTestInAbsoluteForm();
  auto sensorInDifferentialForm = SensorExampleFactory::sensorForSwitchDataFromTestInDifferentialForm();
  sensor.switchDataForm(DataForm::DATA_FORM_ABSOLUTE);
  EXPECT_TRUE(sensor == sensorInDifferentialForm);
}

TEST(SensorTest, TestSwitchDataFormWithSensorForSwitchDataFromTestInDifferentialForm) {
  auto sensor = SensorExampleFactory::sensorForSwitchDataFromTestInDifferentialForm();
  auto sensorInAbsoluteForm = SensorExampleFactory::sensorForSwitchDataFromTestInAbsoluteForm();
  sensor.switchDataForm(DataForm::DATA_FORM_DIFFERENTIAL);
  EXPECT_TRUE(sensor == sensorInAbsoluteForm);
}

TEST(SensorTest, TestSwitchDataFormWithSensorEmpty) {
  auto sensor = SensorExampleFactory::sensorEmpty();
  EXPECT_THROW(sensor.switchDataForm(DataForm::DATA_FORM_NONE), std::runtime_error);
}

TEST(SensorTest, TestSenorTypeFromString) {
  EXPECT_EQ(Sensor::senorTypeFromString("SENSOR_TYPE_PPG"), ProtobufSensorType::SENSOR_TYPE_PPG);
  EXPECT_EQ(Sensor::senorTypeFromString("SENSOR_TYPE_ACC"), ProtobufSensorType::SENSOR_TYPE_ACC);
  EXPECT_EQ(Sensor::senorTypeFromString("SENSOR_TYPE_NONE"), ProtobufSensorType::SENSOR_TYPE_NONE);
}

TEST(SensorTest, TestSenorTypeToString) {
  EXPECT_EQ(Sensor::senorTypeToString(ProtobufSensorType::SENSOR_TYPE_PPG), "SENSOR_TYPE_PPG");
  EXPECT_EQ(Sensor::senorTypeToString(ProtobufSensorType::SENSOR_TYPE_ACC), "SENSOR_TYPE_ACC");
  EXPECT_EQ(Sensor::senorTypeToString(ProtobufSensorType::SENSOR_TYPE_NONE), "SENSOR_TYPE_NONE");
}
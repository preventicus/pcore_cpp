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

class SensorTest : public ::testing::Test {
 protected:
};

TEST_F(SensorTest, TestGetChannelsMethodWithSensorAccWithTwoChannelsInAbsoluteForm) {
  Sensor sensor = SensorExampleFactory::sensorAccWithTwoChannelsInAbsoluteForm();
  Channels channels1;
  channels1.push_back(ChannelExampleFactory::channelWithAbsoluteBlockAndAccMetaData());
  channels1.push_back(ChannelExampleFactory::channelWithAbsoluteBlockAndAccMetaData());
  Channels channels2 = sensor.getChannels();
  for (size_t i = 0; i < channels1.size(); i++) {
    EXPECT_TRUE(channels1[i].isEqual(channels2[i]));
  }
}

TEST_F(SensorTest, TestGetSensorTypeMethodWithSensorAccWithTwoChannelsInAbsoluteForm) {
  Sensor sensor = SensorExampleFactory::sensorAccWithTwoChannelsInAbsoluteForm();
  EXPECT_EQ(sensor.getSensorType(), ProtobufSensorType::SENSOR_TYPE_ACC);
}

TEST_F(SensorTest, TestGetAbsoluteTimestampsMethodWithSensorAccWithTwoChannelsInAbsoluteForm) {
  Sensor sensor = SensorExampleFactory::sensorAccWithTwoChannelsInAbsoluteForm();
  AbsoluteTimestampsContainer absoluteTimestampsContainer1 =
      AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsContainerWithThreeBigTimestamps();
  AbsoluteTimestampsContainer absoluteTimestampsContainer2 = sensor.getAbsoluteTimestamps();
  EXPECT_TRUE(absoluteTimestampsContainer1.isEqual(absoluteTimestampsContainer2));
}

TEST_F(SensorTest, TestGetDifferentialTimestampsMethodWithSensorAccWithTwoChannelsInAbsoluteForm) {
  Sensor sensor = SensorExampleFactory::sensorAccWithTwoChannelsInAbsoluteForm();
  DifferentialTimestampsContainer differentialTimestampsContainer1 =
      DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerEmpty();
  DifferentialTimestampsContainer differentialTimestampsContainer2 = sensor.getDifferentialTimestamps();
  EXPECT_TRUE(differentialTimestampsContainer1.isEqual(differentialTimestampsContainer2));
}

TEST_F(SensorTest, TestGetDifferentialTimestampsMethodWithSensorAccWithTwoChannelsInDifferentialForm) {
  Sensor sensor = SensorExampleFactory::sensorAccWithTwoChannelsInDifferentialForm();
  DifferentialTimestampsContainer differentialTimestampsContainer1 =
      DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithThreeBlocks();
  DifferentialTimestampsContainer differentialTimestampsContainer2 = sensor.getDifferentialTimestamps();
  EXPECT_TRUE(differentialTimestampsContainer1.isEqual(differentialTimestampsContainer2));
}

TEST_F(SensorTest, TestGetAbsoluteTimestampsMethodWithSensorAccWithTwoChannelsInDifferentialForm) {
  Sensor sensor = SensorExampleFactory::sensorAccWithTwoChannelsInDifferentialForm();
  AbsoluteTimestampsContainer absoluteTimestampsContainer1 =
      AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsContainerWithTimestampsEmpty();
  AbsoluteTimestampsContainer absoluteTimestampsContainer2 = sensor.getAbsoluteTimestamps();
  EXPECT_TRUE(absoluteTimestampsContainer1.isEqual(absoluteTimestampsContainer2));
}

TEST_F(SensorTest, TestGetFirstUnixTimestampWithSensorAccWithTwoChannelsInDifferentialForm) {
  Sensor sensor = SensorExampleFactory::sensorAccWithTwoChannelsInDifferentialForm();
  UnixTimestamp firstUnixTimestamp1_ms = sensor.getFirstUnixTimestamp(DataForm::DATA_FORM_DIFFERENTIAL);
  UnixTimestamp firstUnixTimestamp2_ms = UnixTimestampsExampleFactory::firstTimestamp_ms();
  EXPECT_TRUE(firstUnixTimestamp1_ms == firstUnixTimestamp2_ms);
}

TEST_F(SensorTest, TestGetFirstUnixTimestampWithSensorAccWithTwoChannelsInAbsoluteForm) {
  Sensor sensor = SensorExampleFactory::sensorAccWithTwoChannelsInAbsoluteForm();
  UnixTimestamp firstUnixTimestamp1_ms = sensor.getFirstUnixTimestamp(DataForm::DATA_FORM_ABSOLUTE);
  UnixTimestamp firstUnixTimestamp2_ms = UnixTimestampsExampleFactory::firstTimestamp_ms();
  EXPECT_TRUE(firstUnixTimestamp1_ms == firstUnixTimestamp2_ms);
}

TEST_F(SensorTest, TestGetFirstUnixTimestampThrowRuntimeError) {
  Sensor sensor = SensorExampleFactory::sensorEmpty();
  EXPECT_THROW(sensor.getFirstUnixTimestamp(DataForm::DATA_FORM_ABSOLUTE), std::runtime_error);
}

TEST_F(SensorTest, TestGetFirstUnixTimestampThrowInvalideArgument) {
  Sensor sensor = SensorExampleFactory::sensorEmpty();
  EXPECT_THROW(sensor.getFirstUnixTimestamp(DataForm::DATA_FORM_NONE), std::invalid_argument);
}

TEST_F(SensorTest, TestGetLastUnixTimestampWithSensorAccWithTwoChannelsInAbsoluteForm) {
  Sensor sensor = SensorExampleFactory::sensorAccWithTwoChannelsInAbsoluteForm();
  UnixTimestamp lastUnixTimestamp1_ms = sensor.getLastUnixTimestamp(DataForm::DATA_FORM_ABSOLUTE);
  UnixTimestamp lastUnixTimestamp2_ms = UnixTimestampsExampleFactory::lastTimestamp_ms();
  EXPECT_TRUE(lastUnixTimestamp1_ms == lastUnixTimestamp2_ms);
}

TEST_F(SensorTest, TestGetLastUnixTimestampWithSensorAccWithTwoChannelsInDifferentialForm) {
  Sensor sensor = SensorExampleFactory::sensorAccWithTwoChannelsInDifferentialForm();
  UnixTimestamp lastUnixTimestamp1_ms = sensor.getLastUnixTimestamp(DataForm::DATA_FORM_DIFFERENTIAL);
  UnixTimestamp lastUnixTimestamp2_ms = UnixTimestampsExampleFactory::lastTimestamp_ms();
  EXPECT_TRUE(lastUnixTimestamp1_ms == lastUnixTimestamp2_ms);
}

TEST_F(SensorTest, TestGetLastUnixTimestampThrowRuntimeError) {
  Sensor sensor = SensorExampleFactory::sensorEmpty();
  EXPECT_THROW(sensor.getLastUnixTimestamp(DataForm::DATA_FORM_ABSOLUTE), std::runtime_error);
}

TEST_F(SensorTest, TestGetLastUnixTimestampThrowInvalidArgument) {
  Sensor sensor = SensorExampleFactory::sensorAccWithTwoChannelsInAbsoluteForm();
  EXPECT_THROW(sensor.getLastUnixTimestamp(DataForm::DATA_FORM_NONE), std::invalid_argument);
}

TEST_F(SensorTest, TestGetDurationWithSensorAccWithTwoChannelsInDifferentialForm) {
  Sensor sensor = SensorExampleFactory::sensorAccWithTwoChannelsInDifferentialForm();
  Duration duration = sensor.getDuration(DataForm::DATA_FORM_DIFFERENTIAL);
  UnixTimestamp firstUnixTimestamp_ms = UnixTimestampsExampleFactory::firstTimestamp_ms();
  UnixTimestamp lastUnixTimestamp_ms = UnixTimestampsExampleFactory::lastTimestamp_ms();
  EXPECT_EQ(duration, lastUnixTimestamp_ms - firstUnixTimestamp_ms);
}

TEST_F(SensorTest, TestGetDurationWithSensorAccWithTwoChannelsInAbsoluteForm) {
  Sensor sensor = SensorExampleFactory::sensorAccWithTwoChannelsInAbsoluteForm();
  Duration duration = sensor.getDuration(DataForm::DATA_FORM_ABSOLUTE);
  UnixTimestamp firstUnixTimestamp_ms = UnixTimestampsExampleFactory::firstTimestamp_ms();
  UnixTimestamp lastUnixTimestamp_ms = UnixTimestampsExampleFactory::lastTimestamp_ms();
  EXPECT_EQ(duration, lastUnixTimestamp_ms - firstUnixTimestamp_ms);
}

TEST_F(SensorTest, TestIsEqualWithSensorAccWithTwoChannelsInDifferentialForm) {
  Sensor sensor1 = SensorExampleFactory::sensorAccWithTwoChannelsInDifferentialForm();
  Sensor sensor2 = SensorExampleFactory::sensorAccWithTwoChannelsInDifferentialForm();
  EXPECT_TRUE(sensor1.isEqual(sensor2));
}

TEST_F(SensorTest, TestIsEqualWithSensorEmpty) {
  Sensor sensor1 = SensorExampleFactory::sensorEmpty();
  Sensor sensor2 = SensorExampleFactory::sensorEmpty();
  EXPECT_TRUE(sensor1.isEqual(sensor2));
}

TEST_F(SensorTest, TestIsEqualWithSensorEmptyAndSensorAccWithTwoChannelsInAbsoluteForm) {
  Sensor sensor1 = SensorExampleFactory::sensorEmpty();
  Sensor sensor2 = SensorExampleFactory::sensorAccWithTwoChannelsInAbsoluteForm();
  EXPECT_FALSE(sensor1.isEqual(sensor2));
}

TEST_F(SensorTest, TestIsEqualWithSensorAccWithTwoChannelsInDifferentialFormAndSensorAccWithTwoChannelsInAbsoluteForm) {
  Sensor sensor1 = SensorExampleFactory::sensorAccWithTwoChannelsInDifferentialForm();
  Sensor sensor2 = SensorExampleFactory::sensorAccWithTwoChannelsInAbsoluteForm();
  EXPECT_FALSE(sensor1.isEqual(sensor2));
}

TEST_F(SensorTest, TestIsEqualWithSensorAccWithTwoChannelsInDifferentialFormAndSensorPpgWithTwoChannelsInDifferentialForm) {
  Sensor sensor1 = SensorExampleFactory::sensorAccWithTwoChannelsInDifferentialForm();
  Sensor sensor2 = SensorExampleFactory::sensorPpgWithTwoChannelsInDifferentialForm();
  EXPECT_FALSE(sensor1.isEqual(sensor2));
}

TEST_F(SensorTest, TestIsEqualWithSensorPpgWithOneChannelsInAbsoluteFormAndSensorPpgWithTwoChannelsInAbsoluteForm) {
  Sensor sensor1 = SensorExampleFactory::sensorPpgWithOneChannelsInAbsoluteForm();
  Sensor sensor2 = SensorExampleFactory::sensorPpgWithTwoChannelsInAbsoluteForm();
  EXPECT_FALSE(sensor1.isEqual(sensor2));
}

TEST_F(SensorTest, TestToJsonWithSensorPpgWithTwoChannelsInAbsoluteForm) {
  Sensor sensor = SensorExampleFactory::sensorPpgWithTwoChannelsInAbsoluteForm();
  SensorJson sensorJson1 = SensorExampleFactory::buildSensorJson(sensor, DataForm::DATA_FORM_ABSOLUTE);
  SensorJson sensorJson2 = sensor.toJson(DataForm::DATA_FORM_ABSOLUTE);
  EXPECT_TRUE(sensorJson1.toStyledString() == sensorJson2.toStyledString());
}

TEST_F(SensorTest, TestToJsonWithSensorEmpty) {
  Sensor sensor = SensorExampleFactory::sensorEmpty();
  SensorJson sensorJson1 = SensorExampleFactory::buildSensorJson(sensor, DataForm::DATA_FORM_NONE);
  SensorJson sensorJson2 = sensor.toJson(DataForm::DATA_FORM_NONE);
  std::cout << sensorJson1.toStyledString() << std::endl;
  std::cout << sensorJson2.toStyledString() << std::endl;
  EXPECT_TRUE(sensorJson1.toStyledString() == sensorJson2.toStyledString());
}

TEST_F(SensorTest, TestToJsonWithSensorAccWithTwoChannelsInDifferentialForm) {
  Sensor sensor = SensorExampleFactory::sensorAccWithTwoChannelsInDifferentialForm();
  SensorJson sensorJson1 = SensorExampleFactory::buildSensorJson(sensor, DataForm::DATA_FORM_DIFFERENTIAL);
  SensorJson sensorJson2 = sensor.toJson(DataForm::DATA_FORM_DIFFERENTIAL);
  EXPECT_TRUE(sensorJson1.toStyledString() == sensorJson2.toStyledString());
}

TEST_F(SensorTest, TestToJsonWithSensorAccWithTwoChannelsInAbsoluteForm) {
  Sensor sensor = SensorExampleFactory::sensorAccWithTwoChannelsInAbsoluteForm();
  SensorJson sensorJson1 = SensorExampleFactory::buildSensorJson(sensor, DataForm::DATA_FORM_ABSOLUTE);
  SensorJson sensorJson2 = sensor.toJson(DataForm::DATA_FORM_ABSOLUTE);
  EXPECT_TRUE(sensorJson1.toStyledString() == sensorJson2.toStyledString());
}

TEST_F(SensorTest, TestToJsonWithSensorPpgWithTwoChannelsInDifferentialForm) {
  Sensor sensor = SensorExampleFactory::sensorPpgWithTwoChannelsInDifferentialForm();
  SensorJson sensorJson1 = SensorExampleFactory::buildSensorJson(sensor, DataForm::DATA_FORM_DIFFERENTIAL);
  SensorJson sensorJson2 = sensor.toJson(DataForm::DATA_FORM_DIFFERENTIAL);
  EXPECT_TRUE(sensorJson1.toStyledString() == sensorJson2.toStyledString());
}

TEST_F(SensorTest, TestToJsonWithSensorPpgWithOneChannelsInAbsoluteForm) {
  Sensor sensor = SensorExampleFactory::sensorPpgWithOneChannelsInAbsoluteForm();
  SensorJson sensorJson1 = SensorExampleFactory::buildSensorJson(sensor, DataForm::DATA_FORM_ABSOLUTE);
  SensorJson sensorJson2 = sensor.toJson(DataForm::DATA_FORM_ABSOLUTE);
  EXPECT_TRUE(sensorJson1.toStyledString() == sensorJson2.toStyledString());
}

TEST_F(SensorTest, TestSerizlizeWithSensorAccWithTwoChannelsInDifferentialForm) {
  Sensor sensor1 = SensorExampleFactory::sensorAccWithTwoChannelsInDifferentialForm();
  ProtobufSensor protobufSensor;
  sensor1.serialize(&protobufSensor);
  Sensor sensor2 = Sensor(protobufSensor);
  EXPECT_TRUE(sensor1.isEqual(sensor2));
}

TEST_F(SensorTest, TestSerizlizeWithSensorEmpty) {
  Sensor sensor1 = SensorExampleFactory::sensorEmpty();
  ProtobufSensor protobufSensor;
  sensor1.serialize(&protobufSensor);
  Sensor sensor2 = Sensor(protobufSensor);
  EXPECT_TRUE(sensor1.isEqual(sensor2));
}

TEST_F(SensorTest, TestSerizlizeWithSensorPpgWithTwoChannelsInDifferentialForm) {
  Sensor sensor1 = SensorExampleFactory::sensorPpgWithTwoChannelsInDifferentialForm();
  ProtobufSensor protobufSensor;
  sensor1.serialize(&protobufSensor);
  Sensor sensor2 = Sensor(protobufSensor);
  EXPECT_TRUE(sensor1.isEqual(sensor2));
}

TEST_F(SensorTest, TestSerializeNoThrow) {
  Sensor sensor = SensorExampleFactory::sensorPpgWithTwoChannelsInDifferentialForm();
  ProtobufSensor protobufSensor;
  EXPECT_NO_THROW(sensor.serialize(&protobufSensor));
}

TEST_F(SensorTest, TestSerializeThrow) {
  Sensor sensor = SensorExampleFactory::sensorEmpty();
  ProtobufSensor* protobufSensor = nullptr;
  EXPECT_THROW(sensor.serialize(protobufSensor), std::invalid_argument);
}

TEST_F(SensorTest, TestSwitchDataFormWithSensorForSwitchDataFromTestInAbsoluteForm) {
  Sensor sensor = SensorExampleFactory::sensorForSwitchDataFromTestInAbsoluteForm();
  Sensor sensorInDifferentialForm = SensorExampleFactory::sensorForSwitchDataFromTestInDifferentialForm();
  sensor.switchDataForm(DataForm::DATA_FORM_ABSOLUTE);
  EXPECT_TRUE(sensor.isEqual(sensorInDifferentialForm));
}

TEST_F(SensorTest, TestSwitchDataFormWithSensorForSwitchDataFromTestInDifferentialForm) {
  Sensor sensor = SensorExampleFactory::sensorForSwitchDataFromTestInDifferentialForm();
  Sensor sensorInAbsoluteForm = SensorExampleFactory::sensorForSwitchDataFromTestInAbsoluteForm();
  sensor.switchDataForm(DataForm::DATA_FORM_DIFFERENTIAL);
  EXPECT_TRUE(sensor.isEqual(sensorInAbsoluteForm));
}

TEST_F(SensorTest, TestSwitchDataFormWithSensorEmpty) {
  Sensor sensor = SensorExampleFactory::sensorEmpty();
  EXPECT_THROW(sensor.switchDataForm(DataForm::DATA_FORM_NONE), std::runtime_error);
}

TEST_F(SensorTest, TestSenorTypeFromString) {
  EXPECT_EQ(Sensor::senorTypeFromString("SENSOR_TYPE_PPG"), ProtobufSensorType::SENSOR_TYPE_PPG);
  EXPECT_EQ(Sensor::senorTypeFromString("SENSOR_TYPE_ACC"), ProtobufSensorType::SENSOR_TYPE_ACC);
  EXPECT_EQ(Sensor::senorTypeFromString("SENSOR_TYPE_NONE"), ProtobufSensorType::SENSOR_TYPE_NONE);
}

TEST_F(SensorTest, TestSenorTypeToString) {
  EXPECT_EQ(Sensor::senorTypeToString(ProtobufSensorType::SENSOR_TYPE_PPG), "SENSOR_TYPE_PPG");
  EXPECT_EQ(Sensor::senorTypeToString(ProtobufSensorType::SENSOR_TYPE_ACC), "SENSOR_TYPE_ACC");
  EXPECT_EQ(Sensor::senorTypeToString(ProtobufSensorType::SENSOR_TYPE_NONE), "SENSOR_TYPE_NONE");
}
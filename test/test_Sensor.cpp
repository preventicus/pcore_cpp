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

TEST(SensorTest, TestGetChannelsWithSensorAccWithTwoChannelsInAbsoluteForm) {
  auto sensor = SensorExampleFactory::sensorAccWithTwoChannelsInAbsoluteForm();
  Channels channels1;
  channels1.emplace_back(ChannelExampleFactory::channelWithAbsoluteBlockAndAccMetaData());
  channels1.emplace_back(ChannelExampleFactory::channelWithAbsoluteBlockAndAccMetaData());
  auto channels2 = sensor.getChannels();
  for (size_t i = 0; i < channels1.size(); i++) {
    EXPECT_TRUE(channels1[i] == channels2[i]);
  }
}

TEST(SensorTest, TestGetChannelsWithSensorNotSet) {
  auto sensor = SensorExampleFactory::sensorNotSet();
  EXPECT_TRUE(sensor.getChannels().empty());
}

TEST(SensorTest, TestGetSensorTypeWithSensorAccWithTwoChannelsInAbsoluteForm) {
  auto sensor = SensorExampleFactory::sensorAccWithTwoChannelsInAbsoluteForm();
  EXPECT_EQ(sensor.getSensorType(), SensorTypeProtobuf::SENSOR_TYPE_ACC);
}

TEST(SensorTest, TestGetSensorTypeWithSensorPpgWithTwoChannelsInAbsoluteForm) {
  auto sensor = SensorExampleFactory::sensorPpgWithTwoChannelsInAbsoluteForm();
  EXPECT_EQ(sensor.getSensorType(), SensorTypeProtobuf::SENSOR_TYPE_PPG);
}

TEST(SensorTest, TestGetSensorTypeWithSensorNotSet) {
  auto sensor = SensorExampleFactory::sensorNotSet();
  EXPECT_EQ(sensor.getSensorType(), SensorTypeProtobuf::SENSOR_TYPE_NONE);
}

TEST(SensorTest, TestGetDataFormWithSensorNotSet) {
  auto sensor = SensorExampleFactory::sensorNotSet();
  EXPECT_EQ(sensor.getDataFrom(), DataForm::DATA_FORM_NONE);
}

TEST(SensorTest, TestGetDataFormWithSensorAccWithTwoChannelsInDifferentialForm) {
  auto sensor = SensorExampleFactory::sensorAccWithTwoChannelsInDifferentialForm();
  EXPECT_EQ(sensor.getDataFrom(), DataForm::DATA_FORM_DIFFERENTIAL);
}

TEST(SensorTest, TestGetDataFormWithSensorAccWithTwoChannelsInAbsoluteForm) {
  auto sensor = SensorExampleFactory::sensorAccWithTwoChannelsInAbsoluteForm();
  EXPECT_EQ(sensor.getDataFrom(), DataForm::DATA_FORM_ABSOLUTE);
}

TEST(SensorTest, TestGetAbsoluteTimestampsContainerWithSensorAccWithTwoChannelsInAbsoluteForm) {
  auto sensor = SensorExampleFactory::sensorAccWithTwoChannelsInAbsoluteForm();
  auto absoluteTimestampsContainer1 = AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsContainerWithThreeBigTimestamps();
  auto absoluteTimestampsContainer2 = sensor.getAbsoluteTimestampsContainer();
  EXPECT_TRUE(absoluteTimestampsContainer1 == absoluteTimestampsContainer2);
}

TEST(SensorTest, TestGetAbsoluteTimestampsContainerWithSensorNotSet) {
  auto sensor = SensorExampleFactory::sensorNotSet();
  auto absoluteTimestampsContainer1 = AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsContainerNotSet();
  auto absoluteTimestampsContainer2 = sensor.getAbsoluteTimestampsContainer();
  EXPECT_TRUE(absoluteTimestampsContainer1 == absoluteTimestampsContainer2);
}

TEST(SensorTest, TestGetAbsoluteTimestampsWithSensorAccWithTwoChannelsInDifferentialForm) {
  auto sensor = SensorExampleFactory::sensorAccWithTwoChannelsInDifferentialForm();
  auto absoluteTimestampsContainer1 = AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsContainerNotSet();
  auto absoluteTimestampsContainer2 = sensor.getAbsoluteTimestampsContainer();
  EXPECT_TRUE(absoluteTimestampsContainer1 == absoluteTimestampsContainer2);
}

TEST(SensorTest, TestGetDifferentialTimestampsContainerWithSensorAccWithTwoChannelsInAbsoluteForm) {
  auto sensor = SensorExampleFactory::sensorAccWithTwoChannelsInAbsoluteForm();
  auto differentialTimestampsContainer1 = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerNotSet();
  auto differentialTimestampsContainer2 = sensor.getDifferentialTimestampsContainer();
  EXPECT_TRUE(differentialTimestampsContainer1 == differentialTimestampsContainer2);
}

TEST(SensorTest, TestGetDifferentialTimestampsWithSensorNotSet) {
  auto sensor = SensorExampleFactory::sensorNotSet();
  auto differentialTimestampsContainer1 = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerNotSet();
  auto differentialTimestampsContainer2 = sensor.getDifferentialTimestampsContainer();
  EXPECT_TRUE(differentialTimestampsContainer1 == differentialTimestampsContainer2);
}

TEST(SensorTest, TestGetDifferentialTimestampsWithSensorAccWithTwoChannelsInDifferentialForm) {
  auto sensor = SensorExampleFactory::sensorAccWithTwoChannelsInDifferentialForm();
  auto differentialTimestampsContainer1 = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithThreeBlocks();
  auto differentialTimestampsContainer2 = sensor.getDifferentialTimestampsContainer();
  EXPECT_TRUE(differentialTimestampsContainer1 == differentialTimestampsContainer2);
}

TEST(SensorTest, TestGetFirstUnixTimestampWithSensorAccWithTwoChannelsInDifferentialForm) {
  auto sensor = SensorExampleFactory::sensorAccWithTwoChannelsInDifferentialForm();
  auto firstUnixTimestamp1InMs = sensor.getFirstUnixTimestampInMs();
  auto firstUnixTimestamp2InMs = UnixTimestampsExampleFactory::firstTimestampInMs();
  EXPECT_TRUE(firstUnixTimestamp1InMs == firstUnixTimestamp2InMs);
}

TEST(SensorTest, TestGetFirstUnixTimestampWithSensorAccWithTwoChannelsInAbsoluteForm) {
  auto sensor = SensorExampleFactory::sensorAccWithTwoChannelsInAbsoluteForm();
  auto firstUnixTimestamp1InMs = sensor.getFirstUnixTimestampInMs();
  auto firstUnixTimestamp2InMs = UnixTimestampsExampleFactory::firstTimestampInMs();
  EXPECT_TRUE(firstUnixTimestamp1InMs == firstUnixTimestamp2InMs);
}

TEST(SensorTest, TestGetFirstUnixTimestampThrowRuntimeError) {
  auto sensor = SensorExampleFactory::sensorNotSet();
  EXPECT_THROW(std::ignore = sensor.getFirstUnixTimestampInMs(), std::runtime_error);
}

TEST(SensorTest, TestGetFirstUnixTimestampThrowInvalideArgument) {
  auto sensor = SensorExampleFactory::sensorNotSet();
  EXPECT_THROW(std::ignore = sensor.getFirstUnixTimestampInMs(), std::runtime_error);
}

TEST(SensorTest, TestGetLastUnixTimestampWithSensorAccWithTwoChannelsInAbsoluteForm) {
  auto sensor = SensorExampleFactory::sensorAccWithTwoChannelsInAbsoluteForm();
  auto lastUnixTimestamp1InMs = sensor.getLastUnixTimestampInMs();
  auto lastUnixTimestamp2InMs = UnixTimestampsExampleFactory::lastTimestampInMs();
  EXPECT_TRUE(lastUnixTimestamp1InMs == lastUnixTimestamp2InMs);
}

TEST(SensorTest, TestGetLastUnixTimestampWithSensorAccWithTwoChannelsInDifferentialForm) {
  auto sensor = SensorExampleFactory::sensorAccWithTwoChannelsInDifferentialForm();
  auto lastUnixTimestamp1InMs = sensor.getLastUnixTimestampInMs();
  auto lastUnixTimestamp2InMs = UnixTimestampsExampleFactory::lastTimestampInMs();
  EXPECT_TRUE(lastUnixTimestamp1InMs == lastUnixTimestamp2InMs);
}

TEST(SensorTest, TestGetLastUnixTimestampThrowRuntimeError) {
  auto sensor = SensorExampleFactory::sensorNotSet();
  EXPECT_THROW(std::ignore = sensor.getLastUnixTimestampInMs(), std::runtime_error);
}

TEST(SensorTest, TestGetLastUnixTimestampThrowInvalidArgument) {
  auto sensor = SensorExampleFactory::sensorNotSet();
  EXPECT_THROW(std::ignore = sensor.getLastUnixTimestampInMs(), std::runtime_error);
}

TEST(SensorTest, TestGetDurationWithSensorAccWithTwoChannelsInDifferentialForm) {
  auto sensor = SensorExampleFactory::sensorAccWithTwoChannelsInDifferentialForm();
  auto duration = sensor.getDurationInMs();
  auto firstUnixTimestampInMs = UnixTimestampsExampleFactory::firstTimestampInMs();
  auto lastUnixTimestampInMs = UnixTimestampsExampleFactory::lastTimestampInMs();
  EXPECT_EQ(duration, lastUnixTimestampInMs - firstUnixTimestampInMs);
}

TEST(SensorTest, TestGetDurationWithSensorAccWithTwoChannelsInAbsoluteForm) {
  auto sensor = SensorExampleFactory::sensorAccWithTwoChannelsInAbsoluteForm();
  auto duration = sensor.getDurationInMs();
  auto firstUnixTimestampInMs = UnixTimestampsExampleFactory::firstTimestampInMs();
  auto lastUnixTimestampInMs = UnixTimestampsExampleFactory::lastTimestampInMs();
  EXPECT_EQ(duration, lastUnixTimestampInMs - firstUnixTimestampInMs);
}

TEST(SensorTest, TestGetDurationWithSensorNotSet) {
  auto sensor = SensorExampleFactory::sensorNotSet();
  EXPECT_THROW(std::ignore = sensor.getDurationInMs(), std::runtime_error);
}

TEST(SensorTest, TestIsEqualWithSensorAccWithTwoChannelsInDifferentialForm) {
  auto sensor1 = SensorExampleFactory::sensorAccWithTwoChannelsInDifferentialForm();
  auto sensor2 = SensorExampleFactory::sensorAccWithTwoChannelsInDifferentialForm();
  EXPECT_TRUE(sensor1 == sensor2);
}

TEST(SensorTest, TestIsEqualWithSensorNotSet) {
  auto sensor1 = SensorExampleFactory::sensorNotSet();
  auto sensor2 = SensorExampleFactory::sensorNotSet();
  EXPECT_TRUE(sensor1 == sensor2);
}

TEST(SensorTest, TestIsEqualWithSensorNotSetAndSensorAccWithTwoChannelsInAbsoluteForm) {
  auto sensor1 = SensorExampleFactory::sensorNotSet();
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

TEST(SensorTest, TestIsNotEqualWithSensorNotSet) {
  auto sensor1 = SensorExampleFactory::sensorNotSet();
  auto sensor2 = SensorExampleFactory::sensorNotSet();
  EXPECT_FALSE(sensor1 != sensor2);
}

TEST(SensorTest, TestIsNotEqualWithSensorNotSetAndSensorAccWithTwoChannelsInAbsoluteForm) {
  auto sensor1 = SensorExampleFactory::sensorNotSet();
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
  auto sensorJson1 = SensorExampleFactory::buildSensorJson(sensor);
  auto sensorJson2 = sensor.toJson();
  EXPECT_TRUE(sensorJson1.toStyledString() == sensorJson2.toStyledString());
}

TEST(SensorTest, TestToJsonWithSensorNotSet) {
  auto sensor = SensorExampleFactory::sensorNotSet();
  auto sensorJson1 = SensorExampleFactory::buildSensorJson(sensor);
  auto sensorJson2 = sensor.toJson();
  EXPECT_TRUE(sensorJson1.toStyledString() == sensorJson2.toStyledString());
}

TEST(SensorTest, TestToJsonWithSensorAccWithTwoChannelsInDifferentialForm) {
  auto sensor = SensorExampleFactory::sensorAccWithTwoChannelsInDifferentialForm();
  auto sensorJson1 = SensorExampleFactory::buildSensorJson(sensor);
  auto sensorJson2 = sensor.toJson();
  EXPECT_TRUE(sensorJson1.toStyledString() == sensorJson2.toStyledString());
}

TEST(SensorTest, TestToJsonWithSensorAccWithTwoChannelsInAbsoluteForm) {
  auto sensor = SensorExampleFactory::sensorAccWithTwoChannelsInAbsoluteForm();
  auto sensorJson1 = SensorExampleFactory::buildSensorJson(sensor);
  auto sensorJson2 = sensor.toJson();
  EXPECT_TRUE(sensorJson1.toStyledString() == sensorJson2.toStyledString());
}

TEST(SensorTest, TestToJsonWithSensorPpgWithTwoChannelsInDifferentialForm) {
  auto sensor = SensorExampleFactory::sensorPpgWithTwoChannelsInDifferentialForm();
  auto sensorJson1 = SensorExampleFactory::buildSensorJson(sensor);
  auto sensorJson2 = sensor.toJson();
  EXPECT_TRUE(sensorJson1.toStyledString() == sensorJson2.toStyledString());
}

TEST(SensorTest, TestToJsonWithSensorPpgWithOneChannelsInAbsoluteForm) {
  auto sensor = SensorExampleFactory::sensorPpgWithOneChannelsInAbsoluteForm();
  auto sensorJson1 = SensorExampleFactory::buildSensorJson(sensor);
  auto sensorJson2 = sensor.toJson();
  EXPECT_TRUE(sensorJson1.toStyledString() == sensorJson2.toStyledString());
}

TEST(SensorTest, TestSerializeWithSensorAccWithTwoChannelsInDifferentialForm) {
  auto sensor1 = SensorExampleFactory::sensorAccWithTwoChannelsInDifferentialForm();
  SensorProtobuf sensorProtobuf;
  sensor1.serialize(&sensorProtobuf);
  auto sensor2 = Sensor(sensorProtobuf);
  EXPECT_TRUE(sensor1 == sensor2);
}

TEST(SensorTest, TestSerializeWithSensorNotSet) {
  auto sensor1 = SensorExampleFactory::sensorNotSet();
  SensorProtobuf sensorProtobuf;
  sensor1.serialize(&sensorProtobuf);
  auto sensor2 = Sensor(sensorProtobuf);
  EXPECT_TRUE(sensor1 == sensor2);
}

TEST(SensorTest, TestSerializeWithSensorPpgWithTwoChannelsInDifferentialForm) {
  auto sensor1 = SensorExampleFactory::sensorPpgWithTwoChannelsInDifferentialForm();
  SensorProtobuf sensorProtobuf;
  sensor1.serialize(&sensorProtobuf);
  auto sensor2 = Sensor(sensorProtobuf);
  EXPECT_TRUE(sensor1 == sensor2);
}

TEST(SensorTest, TestSerializeNoThrow) {
  auto sensor = SensorExampleFactory::sensorPpgWithTwoChannelsInDifferentialForm();
  SensorProtobuf sensorProtobuf;
  EXPECT_NO_THROW(sensor.serialize(&sensorProtobuf));
}

TEST(SensorTest, TestSerializeThrow) {
  auto sensor = SensorExampleFactory::sensorNotSet();
  SensorProtobuf* sensorProtobuf = nullptr;
  EXPECT_THROW(sensor.serialize(sensorProtobuf), std::invalid_argument);
}

TEST(SensorTest, TestSwitchDataFormWithSensorForSwitchDataFromTestInAbsoluteForm) {
  auto sensor = SensorExampleFactory::sensorForSwitchDataFromTestInAbsoluteForm();
  auto sensorInDifferentialForm = SensorExampleFactory::sensorForSwitchDataFromTestInDifferentialForm();
  sensor.switchDataForm();
  EXPECT_TRUE(sensor == sensorInDifferentialForm);
}

TEST(SensorTest, TestSwitchDataFormWithSensorForSwitchDataFromTestInDifferentialForm) {
  auto sensor = SensorExampleFactory::sensorForSwitchDataFromTestInDifferentialForm();
  auto sensorInAbsoluteForm = SensorExampleFactory::sensorForSwitchDataFromTestInAbsoluteForm();
  sensor.switchDataForm();
  EXPECT_TRUE(sensor == sensorInAbsoluteForm);
}

TEST(SensorTest, TestSwitchDataFormWithSensorNotSet) {
  auto sensor = SensorExampleFactory::sensorNotSet();
  sensor.switchDataForm();
  EXPECT_FALSE(sensor.isSet());
}

TEST(SensorTest, TestIsSetWithSensorNotSet) {
  auto sensor = SensorExampleFactory::sensorNotSet();
  EXPECT_FALSE(sensor.isSet());
}

TEST(SensorTest, TestIsSetWithSensorAccWithTwoChannelsInDifferentialForm) {
  auto sensor = SensorExampleFactory::sensorAccWithTwoChannelsInDifferentialForm();
  EXPECT_TRUE(sensor.isSet());
}

TEST(SensorTest, TestIsSetWithSensorNoneWithZeroChannelsInAbsoluteForm) {
  auto sensor = SensorExampleFactory::sensorNoneWithZeroChannelsInAbsoluteForm();
  EXPECT_TRUE(sensor.isSet());
}

TEST(SensorTest, TestIsSetWithSensorNoneWithZeroChannelsInDifferentialForm) {
  auto sensor = SensorExampleFactory::sensorNoneWithZeroChannelsInDifferentialForm();
  EXPECT_TRUE(sensor.isSet());
}

TEST(SensorTest, TestIsSetWithSensorAccWithZeroChannelsInDifferentialForm) {
  auto sensor = SensorExampleFactory::sensorAccWithZeroChannelsInDifferentialForm();
  EXPECT_TRUE(sensor.isSet());
}

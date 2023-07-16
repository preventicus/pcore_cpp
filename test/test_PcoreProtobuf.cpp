/*

Created by Steve Merschel 2023

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
#include "ChannelExampleFactory.h"
#include "PcoreProtobuf.h"
#include "Sensor.h"
#include "SensorExampleFactory.h"

TEST(PcoreProtobuf, TestSenorTypeFromString) {
  EXPECT_EQ(PcoreProtobuf::Convert::senorTypeFromString("SENSOR_TYPE_PPG"), SensorTypeProtobuf::SENSOR_TYPE_PPG);
  EXPECT_EQ(PcoreProtobuf::Convert::senorTypeFromString("SENSOR_TYPE_ACC"), SensorTypeProtobuf::SENSOR_TYPE_ACC);
  EXPECT_EQ(PcoreProtobuf::Convert::senorTypeFromString("SENSOR_TYPE_NONE"), SensorTypeProtobuf::SENSOR_TYPE_NONE);
}

TEST(PcoreProtobuf, TestSenorTypeToString) {
  EXPECT_EQ(PcoreProtobuf::Convert::senorTypeToString(SensorTypeProtobuf::SENSOR_TYPE_PPG), "SENSOR_TYPE_PPG");
  EXPECT_EQ(PcoreProtobuf::Convert::senorTypeToString(SensorTypeProtobuf::SENSOR_TYPE_ACC), "SENSOR_TYPE_ACC");
  EXPECT_EQ(PcoreProtobuf::Convert::senorTypeToString(SensorTypeProtobuf::SENSOR_TYPE_NONE), "SENSOR_TYPE_NONE");
}

TEST(PcoreProtobuf, TestColorProtobufToString) {
  EXPECT_EQ(PcoreProtobuf::Convert::colorProtobufToString(ColorProtobuf::COLOR_BLUE), "COLOR_BLUE");
  EXPECT_EQ(PcoreProtobuf::Convert::colorProtobufToString(ColorProtobuf::COLOR_GREEN), "COLOR_GREEN");
  EXPECT_EQ(PcoreProtobuf::Convert::colorProtobufToString(ColorProtobuf::COLOR_RED), "COLOR_RED");
  EXPECT_EQ(PcoreProtobuf::Convert::colorProtobufToString(ColorProtobuf::COLOR_NONE), "COLOR_NONE");
}

TEST(PcoreProtobuf, TestColorProtobufFromString) {
  EXPECT_EQ(PcoreProtobuf::Convert::colorProtobufFromString("COLOR_BLUE"), ColorProtobuf::COLOR_BLUE);
  EXPECT_EQ(PcoreProtobuf::Convert::colorProtobufFromString("COLOR_GREEN"), ColorProtobuf::COLOR_GREEN);
  EXPECT_EQ(PcoreProtobuf::Convert::colorProtobufFromString("COLOR_RED"), ColorProtobuf::COLOR_RED);
  EXPECT_EQ(PcoreProtobuf::Convert::colorProtobufFromString("COLOR_NONE"), ColorProtobuf::COLOR_NONE);
}

TEST(PcoreProtobuf, TestNormProtobufFromString) {
  EXPECT_EQ(PcoreProtobuf::Convert::normProtobufFromString("NORM_EUCLIDEAN_DIFFERENCES_NORM"), NormProtobuf::NORM_EUCLIDEAN_DIFFERENCES_NORM);
  EXPECT_EQ(PcoreProtobuf::Convert::normProtobufFromString("NORM_NONE"), NormProtobuf::NORM_NONE);
}

TEST(PcoreProtobuf, TestNormProtobufToString) {
  EXPECT_EQ(PcoreProtobuf::Convert::normProtobufToString(NormProtobuf::NORM_EUCLIDEAN_DIFFERENCES_NORM), "NORM_EUCLIDEAN_DIFFERENCES_NORM");
  EXPECT_EQ(PcoreProtobuf::Convert::normProtobufToString(NormProtobuf::NORM_NONE), "NORM_NONE");
}

TEST(PcoreProtobuf, TestCoordinateProtobufToString) {
  EXPECT_EQ(PcoreProtobuf::Convert::coordinateProtobufToString(CoordinateProtobuf::COORDINATE_X), "COORDINATE_X");
  EXPECT_EQ(PcoreProtobuf::Convert::coordinateProtobufToString(CoordinateProtobuf::COORDINATE_Y), "COORDINATE_Y");
  EXPECT_EQ(PcoreProtobuf::Convert::coordinateProtobufToString(CoordinateProtobuf::COORDINATE_Z), "COORDINATE_Z");
  EXPECT_EQ(PcoreProtobuf::Convert::coordinateProtobufToString(CoordinateProtobuf::COORDINATE_NONE), "COORDINATE_NONE");
}

TEST(PcoreProtobuf, TestCoordinateProtobufFromString) {
  EXPECT_EQ(PcoreProtobuf::Convert::coordinateProtobufFromString("COORDINATE_X"), CoordinateProtobuf::COORDINATE_X);
  EXPECT_EQ(PcoreProtobuf::Convert::coordinateProtobufFromString("COORDINATE_Y"), CoordinateProtobuf::COORDINATE_Y);
  EXPECT_EQ(PcoreProtobuf::Convert::coordinateProtobufFromString("COORDINATE_Z"), CoordinateProtobuf::COORDINATE_Z);
  EXPECT_EQ(PcoreProtobuf::Convert::coordinateProtobufFromString("COORDINATE_NONE"), CoordinateProtobuf::COORDINATE_NONE);
}

TEST(PcoreProtobuf, TestProtobufToVectorWithChannel) {
  Channels channelsExpected;
  channelsExpected.emplace_back(ChannelExampleFactory::channelWithDifferentialBlocksAndPpgMetaData());
  channelsExpected.emplace_back(ChannelExampleFactory::channelWithDifferentialBlocksAndPpgMetaData());

  SensorProtobuf sensorProtobuf;
  auto* channelProtobuf1 = sensorProtobuf.add_channels();
  channelsExpected[0].serialize(channelProtobuf1);

  auto* channelProtobuf2 = sensorProtobuf.add_channels();
  channelsExpected[1].serialize(channelProtobuf2);

  auto channelsResult = PcoreProtobuf::Convert::protobufToVector<Channel>(sensorProtobuf.channels());

  EXPECT_TRUE(channelsExpected.size() == channelsResult.size());

  for (size_t i = 0; i < channelsExpected.size(); i++) {
    EXPECT_TRUE(channelsExpected[i] == channelsResult[i]);
  }
}

TEST(PcoreProtobuf, TestProtobufToVectorWithSensor) {
  Sensors sensorsExpected;
  sensorsExpected.emplace_back(SensorExampleFactory::sensorAccWithTwoChannelsInDifferentialForm());
  sensorsExpected.emplace_back(SensorExampleFactory::sensorPpgWithTwoChannelsInDifferentialForm());
  sensorsExpected.emplace_back(SensorExampleFactory::sensorAccWithZeroChannelsInDifferentialForm());

  RawProtobuf rawProtobuf;
  auto* sensorProtobuf1 = rawProtobuf.add_sensors();
  sensorsExpected[0].serialize(sensorProtobuf1);

  auto* sensorProtobuf2 = rawProtobuf.add_sensors();
  sensorsExpected[1].serialize(sensorProtobuf2);

  auto* sensorProtobuf3 = rawProtobuf.add_sensors();
  sensorsExpected[2].serialize(sensorProtobuf3);

  auto sensorsResult = PcoreProtobuf::Convert::protobufToVector<Sensor>(rawProtobuf.sensors());

  EXPECT_TRUE(sensorsExpected.size() == sensorsResult.size());

  for (size_t i = 0; i < sensorsExpected.size(); i++) {
    EXPECT_TRUE(sensorsExpected[i] == sensorsResult[i]);
  }
}

TEST(PcoreProtobuf, TestProtobufToVectorWithTimeDifference) {
  TimestampsDifferences timestampsDifferencesExpected;
  timestampsDifferencesExpected.emplace_back(0);
  timestampsDifferencesExpected.emplace_back(10);
  timestampsDifferencesExpected.emplace_back(20);

  BlockDifferences blockDifferencesExpected;
  blockDifferencesExpected.push_back(1);
  blockDifferencesExpected.push_back(67);
  blockDifferencesExpected.push_back(21);

  DifferentialTimestampContainerProtobuf differentialTimestampContainerProtobuf;
  differentialTimestampContainerProtobuf.add_block_differences_ms(blockDifferencesExpected[0]);
  differentialTimestampContainerProtobuf.add_block_differences_ms(blockDifferencesExpected[1]);
  differentialTimestampContainerProtobuf.add_block_differences_ms(blockDifferencesExpected[2]);

  differentialTimestampContainerProtobuf.add_timestamps_differences_ms(timestampsDifferencesExpected[0]);
  differentialTimestampContainerProtobuf.add_timestamps_differences_ms(timestampsDifferencesExpected[1]);
  differentialTimestampContainerProtobuf.add_timestamps_differences_ms(timestampsDifferencesExpected[2]);

  auto timestampsDifferencesResult =
      PcoreProtobuf::Convert::protobufToVector<TimeDifference>(differentialTimestampContainerProtobuf.timestamps_differences_ms());

  EXPECT_TRUE(timestampsDifferencesResult.size() == timestampsDifferencesExpected.size());
  for (size_t i = 0; i < timestampsDifferencesResult.size(); i++) {
    EXPECT_TRUE(timestampsDifferencesExpected[i] == timestampsDifferencesResult[i]);
  }

  auto blockDifferencesResult =
      PcoreProtobuf::Convert::protobufToVector<TimeDifference>(differentialTimestampContainerProtobuf.block_differences_ms());

  EXPECT_TRUE(blockDifferencesResult.size() == blockDifferencesExpected.size());
  for (size_t i = 0; i < blockDifferencesResult.size(); i++) {
    EXPECT_TRUE(blockDifferencesExpected[i] == blockDifferencesResult[i]);
  }
}

TEST(PcoreProtobuf, TestProtobufToVectorWithDifferentalValue) {
  DifferentialValues differentialValuesExpected = DifferentialValuesExampleFactory::differentialValuesWithThreeMixedElements();

  DifferentialBlockProtobuf differentialBlockProtobuf;
  differentialBlockProtobuf.add_differential_values(differentialValuesExpected[0]);
  differentialBlockProtobuf.add_differential_values(differentialValuesExpected[1]);
  differentialBlockProtobuf.add_differential_values(differentialValuesExpected[2]);

  auto differentialValuesResult = PcoreProtobuf::Convert::protobufToVector<DifferentialValue>(differentialBlockProtobuf.differential_values());

  EXPECT_TRUE(differentialValuesExpected.size() == differentialValuesResult.size());
  for (size_t i = 0; i < differentialValuesExpected.size(); i++) {
    EXPECT_TRUE(differentialValuesExpected[i] == differentialValuesResult[i]);
  }
}

TEST(PcoreProtobuf, TestProtobufToVectorWithDifferentalBlock) {
  DifferentialBlocks differentialBlocksExpected;
  differentialBlocksExpected.push_back(DifferentialBlockExampleFactory::differentialBlockWithThreeMixedDifferentialValues());
  differentialBlocksExpected.push_back(DifferentialBlockExampleFactory::differentialBlockWithOneDifferentialValues());
  differentialBlocksExpected.push_back(DifferentialBlockExampleFactory::differentialBlockWithThreePositiveDifferentialValues());

  ChannelProtobuf channelProtobuf;
  auto* differentialBlock1 = channelProtobuf.add_differential_blocks();
  differentialBlocksExpected[0].serialize(differentialBlock1);

  auto* differentialBlock2 = channelProtobuf.add_differential_blocks();
  differentialBlocksExpected[1].serialize(differentialBlock2);

  auto* differentialBlock3 = channelProtobuf.add_differential_blocks();
  differentialBlocksExpected[2].serialize(differentialBlock3);

  auto differentialBlocksResult = PcoreProtobuf::Convert::protobufToVector<DifferentialBlock>(channelProtobuf.differential_blocks());

  EXPECT_TRUE(differentialBlocksExpected.size() == differentialBlocksResult.size());
  for (size_t i = 0; i < differentialBlocksExpected.size(); i++) {
    EXPECT_TRUE(differentialBlocksExpected[i] == differentialBlocksResult[i]);
  }
}
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
#include "AbsoluteBlockExampleFactory.h"
#include "ChannelExampleFactory.h"
#include "DifferencesExampleFactory.h"
#include "DifferentialBlockExampleFactory.h"
#include "DifferentialValuesExampleFactory.h"
#include "PcoreJson.h"
#include "RawExampleFactory.h"
#include "SensorExampleFactory.h"
#include "VersionExampleFactory.h"



TEST(PcoreJson, TestDataFormFromString) {
  EXPECT_EQ(PcoreJson::Convert::dataFormFromString("DATA_FORM_ABSOLUTE"), DataForm::DATA_FORM_ABSOLUTE);
  EXPECT_EQ(PcoreJson::Convert::dataFormFromString("DATA_FORM_DIFFERENTIAL"), DataForm::DATA_FORM_DIFFERENTIAL);
  EXPECT_EQ(PcoreJson::Convert::dataFormFromString("DATA_FORM_NONE"), DataForm::DATA_FORM_NONE);
}

TEST(PcoreJson, TestDataFormToString) {
  EXPECT_EQ(PcoreJson::Convert::dataFormToString(DataForm::DATA_FORM_ABSOLUTE), "DATA_FORM_ABSOLUTE");
  EXPECT_EQ(PcoreJson::Convert::dataFormToString(DataForm::DATA_FORM_DIFFERENTIAL), "DATA_FORM_DIFFERENTIAL");
  EXPECT_EQ(PcoreJson::Convert::dataFormToString(DataForm::DATA_FORM_NONE), "DATA_FORM_NONE");
}

TEST(PcoreJson, TestJsonToValueWithVersion) {
  Version version = VersionExampleFactory::versionWithMajor2Minor1Patch0();
  VersionJson versionJson = version.toJson();
  EXPECT_EQ(PcoreJson::Convert::jsonToValue<Major>(versionJson, PcoreJson::Key::major), version.getMajor());
  EXPECT_EQ(PcoreJson::Convert::jsonToValue<Minor>(versionJson, PcoreJson::Key::minor), version.getMinor());
  EXPECT_EQ(PcoreJson::Convert::jsonToValue<Patch>(versionJson, PcoreJson::Key::patch), version.getPatch());
}

TEST(PcoreJson, TestJsonToVectorWithDifferentialBlock) {
  auto channel = ChannelExampleFactory::channelWithDifferentialBlocksAndPpgMetaData();
  auto differentialBlocksExpected = channel.getDifferentialBlocks();
  auto channelJson = ChannelExampleFactory::buildChannelJson(channel);
  auto differentialBlocksResult = PcoreJson::Convert::jsonToVector<DifferentialBlock>(channelJson, PcoreJson::Key::differential_blocks);

  EXPECT_TRUE(differentialBlocksExpected.size() == differentialBlocksResult.size());
  for (size_t i = 0; i < differentialBlocksExpected.size(); i++) {
    EXPECT_TRUE(differentialBlocksExpected[i] == differentialBlocksResult[i]);
  }
}

TEST(PcoreJson, TestJsonToVectorWithAbsoluteValue) {
  auto absoluteBlock = AbsoluteBlockExampleFactory::absoluteBlockWithThreeMixedAbsoluteValues();
  auto absoluteValuesExpected = absoluteBlock.getAbsoluteValues();
  auto absoluteBlockJson = AbsoluteBlockExampleFactory::buildAbsoluteBlockJson(absoluteBlock);
  auto absoluteValuesResult = PcoreJson::Convert::jsonToVector<AbsoluteValue>(absoluteBlockJson, PcoreJson::Key::absolute_values);

  EXPECT_TRUE(absoluteValuesExpected.size() == absoluteValuesResult.size());
  for (size_t i = 0; i < absoluteValuesExpected.size(); i++) {
    EXPECT_TRUE(absoluteValuesExpected[i] == absoluteValuesResult[i]);
  }
}

TEST(PcoreJson, TestJsonToVectorWithUnixTimestamp) {
  auto absoluteTimestampsContainer = AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsContainerWithThreeBigTimestamps();
  auto unixTimestampExpected = absoluteTimestampsContainer.getUnixTimestampsInMs();
  auto absoluteTimestampsContainerJson = AbsoluteTimestampsContainerExampleFactory::buildAbsoluteTimestampsContainerJson(absoluteTimestampsContainer);
  auto unixTimestampResult = PcoreJson::Convert::jsonToVector<UnixTimestamp>(absoluteTimestampsContainerJson, PcoreJson::Key::unix_timestamps_ms);

  EXPECT_TRUE(unixTimestampExpected.size() == unixTimestampResult.size());
  for (size_t i = 0; i < unixTimestampExpected.size(); i++) {
    EXPECT_TRUE(unixTimestampExpected[i] == unixTimestampResult[i]);
  }
}

TEST(PcoreJson, TestJsonToVectorWithDifferentialValue) {
  auto differentialBlock = DifferentialBlockExampleFactory::differentialBlockWithThreeMixedDifferentialValues();
  auto differentialValuesExpected = differentialBlock.getDifferentialValues();
  auto differentialBlockJson = DifferentialBlockExampleFactory::buildDifferentialBlockJson(differentialBlock);
  auto differentialValuesResult = PcoreJson::Convert::jsonToVector<DifferentialValue>(differentialBlockJson, PcoreJson::Key::differential_values);

  EXPECT_TRUE(differentialValuesExpected.size() == differentialValuesResult.size());
  for (size_t i = 0; i < differentialValuesExpected.size(); i++) {
    EXPECT_TRUE(differentialValuesExpected[i] == differentialValuesResult[i]);
  }
}

TEST(PcoreJson, TestJsonToVectorWithTimeDifference) {
  auto differentialTimestampsContainer = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithBigBlocks();
  auto blocksDifferencesExpected = differentialTimestampsContainer.getBlocksDifferencesInMs();
  auto timestampsDifferencesExpected = differentialTimestampsContainer.getTimestampsDifferencesInMs();
  auto differentialTimestampsContainerJson =
      DifferentialTimestampsContainerExampleFactory::buildDifferentialTimestampsContainerJson(differentialTimestampsContainer);
  auto blocksDifferencesResult =
      PcoreJson::Convert::jsonToVector<TimeDifference>(differentialTimestampsContainerJson, PcoreJson::Key::blocks_differences_ms);
  auto timestampsDifferencesResult =
      PcoreJson::Convert::jsonToVector<TimeDifference>(differentialTimestampsContainerJson, PcoreJson::Key::timestamps_differences_ms);
  EXPECT_TRUE(blocksDifferencesExpected.size() == blocksDifferencesResult.size());
  for (size_t i = 0; i < blocksDifferencesExpected.size(); i++) {
    EXPECT_TRUE(blocksDifferencesExpected[i] == blocksDifferencesResult[i]);
  }

  EXPECT_TRUE(timestampsDifferencesExpected.size() == timestampsDifferencesResult.size());
  for (size_t i = 0; i < timestampsDifferencesExpected.size(); i++) {
    EXPECT_TRUE(timestampsDifferencesExpected[i] == timestampsDifferencesResult[i]);
  }
}

TEST(PcoreJson, TestJsonToVectorWithSensor) {
  auto raw = RawExampleFactory::rawWithTwoSensorsPpgWithTwoChannelsInDifferentialForm();
  auto sensorsExpected = raw.getSensors();
  auto rawJson = RawExampleFactory::buildRawJson(raw);
  auto sensorsResult = PcoreJson::Convert::jsonToVector<Sensor>(rawJson, PcoreJson::Key::sensors, DataForm::DATA_FORM_DIFFERENTIAL);

  EXPECT_TRUE(sensorsExpected.size() == sensorsResult.size());
  for (size_t i = 0; i < sensorsExpected.size(); i++) {
    EXPECT_TRUE(sensorsExpected[i] == sensorsResult[i]);
  }
}

TEST(PcoreJson, TestJsonToVectorWithChannel) {
  auto sensor = SensorExampleFactory::sensorPpgWithTwoChannelsInDifferentialForm();
  auto channelsExpected = sensor.getChannels();
  auto sensorJson = SensorExampleFactory::buildSensorJson(sensor);
  auto channelsResult = PcoreJson::Convert::jsonToVector<Channel>(sensorJson, PcoreJson::Key::channels, SensorTypeProtobuf::SENSOR_TYPE_PPG,
                                                                  DataForm::DATA_FORM_DIFFERENTIAL);

  EXPECT_TRUE(channelsExpected.size() == channelsResult.size());
  for (size_t i = 0; i < channelsExpected.size(); i++) {
    EXPECT_TRUE(channelsExpected[i] == channelsResult[i]);
  }
}

TEST(PcoreJson, TestVectorToJsonWithAbsoluteValues) {
  auto absoluteValues = AbsoluteValuesExampleFactory::absoluteValuesWithThreeMixedElements();
  auto absoluteBlockJsonExpected = AbsoluteValuesExampleFactory::buildAbsoluteValuesJson(absoluteValues);
  auto absoluteValuesJsonResult = PcoreJson::Convert::vectorToJson(absoluteValues);
  EXPECT_TRUE(absoluteBlockJsonExpected.toStyledString() == absoluteValuesJsonResult.toStyledString());
}

TEST(PcoreJson, TestVectorToJsonWithUnixTimestamps) {
  auto unixTimestamps = UnixTimestampsExampleFactory::unixTimestampsWithThreeBigTimestampsInMs();
  auto unixTimestampsJsonExpected = UnixTimestampsExampleFactory::buildUnixTimestampsJson(unixTimestamps);
  auto unixTimestampsJsonResult = PcoreJson::Convert::vectorToJson(unixTimestamps);
  EXPECT_TRUE(unixTimestampsJsonExpected.toStyledString() == unixTimestampsJsonResult.toStyledString());
}

TEST(PcoreJson, TestVectorToJsonWithDifferentialBlock) {
  DifferentialBlocks differentialBlocks;
  differentialBlocks.emplace_back(DifferentialBlockExampleFactory::differentialBlockWithThreeMixedDifferentialValues());
  auto differentialBlocksJsonExpected = DifferentialBlockExampleFactory::buildDifferentialBlocksJson(differentialBlocks);
  auto differentialBlocksJsonResult = PcoreJson::Convert::vectorToJson(differentialBlocks);
  EXPECT_TRUE(differentialBlocksJsonExpected.toStyledString() == differentialBlocksJsonResult.toStyledString());
}

TEST(PcoreJson, TestVectorToJsonWithDifferentialValues) {
  auto differentialValues = DifferentialValuesExampleFactory::differentialValuesWithThreeMixedElements();
  auto differentialValuesJsonExpected = DifferentialValuesExampleFactory::buildDifferentialValuesJson(differentialValues);
  auto differentialValuesJsonResult = PcoreJson::Convert::vectorToJson(differentialValues);
  EXPECT_TRUE(differentialValuesJsonExpected.toStyledString() == differentialValuesJsonResult.toStyledString());
}

TEST(PcoreJson, TestVectorToJsonWithBlocksDifferences) {
  auto blocksDifferences = DifferencesExampleFactory::blocksDifferencesWithThreeBigDifferences();
  auto blocksDifferencesJsonExpected = DifferencesExampleFactory::buildBlocksDifferencesJson(blocksDifferences);
  auto blocksDifferencesJsonResult = PcoreJson::Convert::vectorToJson(blocksDifferences);
  EXPECT_TRUE(blocksDifferencesJsonExpected.toStyledString() == blocksDifferencesJsonResult.toStyledString());
}

TEST(PcoreJson, TestVectorToJsonWithTimestampsDifferences) {
  auto timestampsDifferences = DifferencesExampleFactory::timestampsDifferencesWithThreeBigDifferences();
  auto timestampsDifferencesJsonExpected = DifferencesExampleFactory::buildTimestampsDifferencesJson(timestampsDifferences);
  auto timestampsDifferencesJsonResult = PcoreJson::Convert::vectorToJson(timestampsDifferences);
  EXPECT_TRUE(timestampsDifferencesJsonExpected.toStyledString() == timestampsDifferencesJsonResult.toStyledString());
}

TEST(PcoreJson, TestVectorToJsonWithSensor) {
  Sensors sensors;
  sensors.emplace_back(SensorExampleFactory::sensorPpgWithTwoChannelsInDifferentialForm());
  auto sensorsJsonExpected = SensorExampleFactory::buildSensorsJson(sensors);
  auto sensorsJsonResult = PcoreJson::Convert::vectorToJson(sensors);
  EXPECT_TRUE(sensorsJsonExpected.toStyledString() == sensorsJsonResult.toStyledString());
}

TEST(PcoreJson, TestVectorToJsonWithChannels) {
  Channels channels;
  channels.emplace_back(ChannelExampleFactory::channelWithDifferentialBlocksAndPpgMetaData());
  auto channelsJsonExpected = ChannelExampleFactory::buildChannelsJson(channels);
  auto channelsJsonResult = PcoreJson::Convert::vectorToJson(channels);
  EXPECT_TRUE(channelsJsonExpected.toStyledString() == channelsJsonResult.toStyledString());
}
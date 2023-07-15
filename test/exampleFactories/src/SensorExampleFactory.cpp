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

#include "SensorExampleFactory.h"
#include "PcoreJson.h"

Sensor SensorExampleFactory::sensorPpgWithTwoChannelsInAbsoluteForm() {
  Channels channels;
  channels.emplace_back(ChannelExampleFactory::channelWithAbsoluteBlockAndPpgMetaData());
  channels.emplace_back(ChannelExampleFactory::channelWithAbsoluteBlockAndPpgMetaData());
  auto absoluteTimestampsContainer = AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsContainerWithThreeBigTimestamps();
  return Sensor(channels, absoluteTimestampsContainer, SensorTypeProtobuf::SENSOR_TYPE_PPG);
}

Sensor SensorExampleFactory::sensorPpgWithOneChannelsInAbsoluteForm() {
  Channels channels;
  channels.emplace_back(ChannelExampleFactory::channelWithAbsoluteBlockAndPpgMetaData());
  auto absoluteTimestampsContainer = AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsContainerWithThreeBigTimestamps();
  return Sensor(channels, absoluteTimestampsContainer, SensorTypeProtobuf::SENSOR_TYPE_PPG);
}

Sensor SensorExampleFactory::sensorAccWithTwoChannelsInAbsoluteForm() {
  Channels channels;
  channels.emplace_back(ChannelExampleFactory::channelWithAbsoluteBlockAndAccMetaData());
  channels.emplace_back(ChannelExampleFactory::channelWithAbsoluteBlockAndAccMetaData());
  auto absoluteTimestampsContainer = AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsContainerWithThreeBigTimestamps();
  return Sensor(channels, absoluteTimestampsContainer, SensorTypeProtobuf::SENSOR_TYPE_ACC);
}

Sensor SensorExampleFactory::sensorPpgWithTwoChannelsInDifferentialForm() {
  Channels channels;
  channels.emplace_back(ChannelExampleFactory::channelWithDifferentialBlocksAndPpgMetaData());
  channels.emplace_back(ChannelExampleFactory::channelWithDifferentialBlocksAndPpgMetaData());
  auto differentialTimestampsContainer = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithThreeBlocks();
  return Sensor(channels, differentialTimestampsContainer, SensorTypeProtobuf::SENSOR_TYPE_PPG);
}

Sensor SensorExampleFactory::sensorAccWithTwoChannelsInDifferentialForm() {
  Channels channels;
  channels.emplace_back(ChannelExampleFactory::channelWithDifferentialBlocksAndAccMetaData());
  channels.emplace_back(ChannelExampleFactory::channelWithDifferentialBlocksAndAccMetaData());
  auto differentialTimestampsContainer = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithThreeBlocks();
  return Sensor(channels, differentialTimestampsContainer, SensorTypeProtobuf::SENSOR_TYPE_ACC);
}

Sensor SensorExampleFactory::sensorNotSet() {
  return Sensor();
}

Sensor SensorExampleFactory::sensorForSwitchDataFromTestInAbsoluteForm() {
  Channels channels;
  channels.emplace_back(ChannelExampleFactory::channelWithAbsoluteValuesForSwitchDataFormTest());
  auto absoluteTimestampsContainer = AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsContainerWithTimestampsForSwitchDataFormTest();
  return Sensor(channels, absoluteTimestampsContainer, SensorTypeProtobuf::SENSOR_TYPE_PPG);
}

Sensor SensorExampleFactory::sensorForSwitchDataFromTestInDifferentialForm() {
  Channels channels;
  channels.emplace_back(ChannelExampleFactory::channelWithDifferentialValuesForSwitchDataFormTest());
  auto differentialTimestampsContainer = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerForSwitchDataFormTest();
  return Sensor(channels, differentialTimestampsContainer, SensorTypeProtobuf::SENSOR_TYPE_PPG);
}

SensorJson SensorExampleFactory::buildSensorJson(const Sensor& sensor) {
  SensorJson sensorJson;
  if (!sensor.isSet()) {
    return sensorJson;
  }
  ChannelsJson channelsJson;
  switch (sensor.getDataFrom()) {
    case DataForm::DATA_FORM_ABSOLUTE: {
      auto absoluteTimestampsContainer = sensor.getAbsoluteTimestampsContainer();
      sensorJson[PcoreJson::Key::absolute_timestamps_container] =
          AbsoluteTimestampsContainerExampleFactory::buildAbsoluteTimestampsContainerJson(absoluteTimestampsContainer);
      break;
    }
    case DataForm::DATA_FORM_DIFFERENTIAL: {
      auto differentialTimestampsContainer = sensor.getDifferentialTimestampsContainer();
      sensorJson[PcoreJson::Key::differential_timestamps_container] =
          DifferentialTimestampsContainerExampleFactory::buildDifferentialTimestampsContainerJson(differentialTimestampsContainer);
      break;
    }
    case DATA_FORM_NONE:
      return sensorJson;
  }
  Channels channels = sensor.getChannels();
  for (auto& channel : channels) {
    channelsJson.append(ChannelExampleFactory::buildChannelJson(channel));
  }
  sensorJson[PcoreJson::Key::channels] = channelsJson;
  sensorJson[PcoreJson::Key::sensor_type] = PcoreProtobuf::Convert::senorTypeToString(sensor.getSensorType());
  return sensorJson;
}

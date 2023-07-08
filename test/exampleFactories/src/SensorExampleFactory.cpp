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

Sensor SensorExampleFactory::sensorPpgWithTwoChannelsInAbsoluteForm() {
  Channels channels;
  channels.push_back(ChannelExampleFactory::channelWithAbsoluteBlockAndPpgMetaData());
  channels.push_back(ChannelExampleFactory::channelWithAbsoluteBlockAndPpgMetaData());
  AbsoluteTimestampsContainer absoluteTimestampsContainer =
      AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsContainerWithThreeBigTimestamps();
  return Sensor(channels, absoluteTimestampsContainer, ProtobufSensorType::SENSOR_TYPE_PPG);
}

Sensor SensorExampleFactory::sensorPpgWithOneChannelsInAbsoluteForm() {
  Channels channels;
  channels.push_back(ChannelExampleFactory::channelWithAbsoluteBlockAndPpgMetaData());
  AbsoluteTimestampsContainer absoluteTimestampsContainer =
      AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsContainerWithThreeBigTimestamps();
  return Sensor(channels, absoluteTimestampsContainer, ProtobufSensorType::SENSOR_TYPE_PPG);
}

Sensor SensorExampleFactory::sensorAccWithTwoChannelsInAbsoluteForm() {
  Channels channels;
  channels.push_back(ChannelExampleFactory::channelWithAbsoluteBlockAndAccMetaData());
  channels.push_back(ChannelExampleFactory::channelWithAbsoluteBlockAndAccMetaData());
  AbsoluteTimestampsContainer absoluteTimestampsContainer =
      AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsContainerWithThreeBigTimestamps();
  return Sensor(channels, absoluteTimestampsContainer, ProtobufSensorType::SENSOR_TYPE_ACC);
}

Sensor SensorExampleFactory::sensorPpgWithTwoChannelsInDifferentialForm() {
  Channels channels;
  channels.push_back(ChannelExampleFactory::channelWithDifferentialBlocksAndPpgMetaData());
  channels.push_back(ChannelExampleFactory::channelWithDifferentialBlocksAndPpgMetaData());
  DifferentialTimestampsContainer differentialTimestampsContainer =
      DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithThreeBlocks();
  return Sensor(channels, differentialTimestampsContainer, ProtobufSensorType::SENSOR_TYPE_PPG);
}

Sensor SensorExampleFactory::sensorAccWithTwoChannelsInDifferentialForm() {
  Channels channels;
  channels.push_back(ChannelExampleFactory::channelWithDifferentialBlocksAndAccMetaData());
  channels.push_back(ChannelExampleFactory::channelWithDifferentialBlocksAndAccMetaData());
  DifferentialTimestampsContainer differentialTimestampsContainer =
      DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithThreeBlocks();
  return Sensor(channels, differentialTimestampsContainer, ProtobufSensorType::SENSOR_TYPE_ACC);
}

Sensor SensorExampleFactory::sensorEmpty() {
  return Sensor();
}

Sensor SensorExampleFactory::sensorForSwitchDataFromTestInAbsoluteForm() {
  Channels channels;
  channels.push_back(ChannelExampleFactory::channelWithAbsoluteValuesForTestSwitchTo());
  AbsoluteTimestampsContainer absoluteTimestampsContainer =
      AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsContainerWithTimestampsForSwitchDataFormTest();
  return Sensor(channels, absoluteTimestampsContainer, ProtobufSensorType::SENSOR_TYPE_PPG);
}

Sensor SensorExampleFactory::sensorForSwitchDataFromTestInDifferentialForm() {
  Channels channels;
  channels.push_back(ChannelExampleFactory::channelWithDifferentialValuesForTestSwitchTo());
  DifferentialTimestampsContainer differentialTimestampsContainer =
      DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerForSwitchDataFormTest();
  return Sensor(channels, differentialTimestampsContainer, ProtobufSensorType::SENSOR_TYPE_PPG);
}

SensorJson SensorExampleFactory::buildSensorJson(Sensor sensor, DataForm dataForm) {
  SensorJson sensorJson;
  ChannelsJson channelsJson;
  switch (dataForm) {
    case DataForm::DATA_FORM_ABSOLUTE: {
      AbsoluteTimestampsContainer absoluteTimestampsContainer = sensor.getAbsoluteTimestamps();
      sensorJson["absolute_timestamps_container"] =
          AbsoluteTimestampsContainerExampleFactory::buildAbsoluteTimestampsContainerJson(absoluteTimestampsContainer);
      break;
    }
    case DataForm::DATA_FORM_DIFFERENTIAL: {
      DifferentialTimestampsContainer differentialTimestampsContainer = sensor.getDifferentialTimestamps();
      sensorJson["differential_timestamps_container"] =
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
  sensorJson["channels"] = channelsJson;
  sensorJson["sensor_type"] = Sensor::senorTypeToString(sensor.getSensorType());
  return sensorJson;
}

// Sensor SensorExampleFactory::normalSensor() {
//   Channels normalVectorChannel = ChannelExampleFactory::normalVectorWithChannel();
//   DifferentialTimestampsContainer normalDifferentialTimestamps = DifferentialTimestampsContainerExampleFactory::normalDifferentialTimestamps();
//   return Sensor(normalVectorChannel, normalDifferentialTimestamps, ProtobufSensorType::SENSOR_TYPE_ACC);
// }
//
// Sensor SensorExampleFactory::comparableSensor() {
//   Channels comparableVectorChannel = ChannelExampleFactory::comparableVectorWithChannel();
//   AbsoluteTimestampsContainer absoluteTimestamps = AbsoluteTimestampsContainerExampleFactory::normalAbsoluteTimestamps();
//   return Sensor(comparableVectorChannel, absoluteTimestamps, ProtobufSensorType::SENSOR_TYPE_PPG);
// }
//
// Sensor SensorExampleFactory::sensorWithOneUnixAndOneValue() {
//   Channels comparableVectorChannel = ChannelExampleFactory::normalVectorWithOneValueBlock();
//   AbsoluteTimestampsContainer absoluteTimestamps = AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsOneElement();
//   return Sensor(comparableVectorChannel, absoluteTimestamps, ProtobufSensorType::SENSOR_TYPE_PPG);
// }
//
// Sensor SensorExampleFactory::sensorWithNUllUnixAndNUllValue() {
//   Channels comparableVectorChannel = ChannelExampleFactory::normalVectorWithNUllValueBlock();
//   AbsoluteTimestampsContainer absoluteTimestamps = AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsContainerWithTimestampsEmpty();
//   return Sensor(comparableVectorChannel, absoluteTimestamps, ProtobufSensorType::SENSOR_TYPE_PPG);
// }
//
// Sensor SensorExampleFactory::sensorWithOneUnixAndOneValueInLastBlock() {
//   Channels comparableVectorChannel = ChannelExampleFactory::normalVectorWithOneValueInLastBlock();
//   AbsoluteTimestampsContainer absoluteTimestamps = AbsoluteTimestampsContainerExampleFactory::absoluteUNixTimestampBlockWithOneUnixInLastBlock();
//   return Sensor(comparableVectorChannel, absoluteTimestamps, ProtobufSensorType::SENSOR_TYPE_PPG);
// }
//
// Sensor SensorExampleFactory::sensorWithEqualTimestampsInterval() {
//   Channels comparableVectorChannel = ChannelExampleFactory::normalVectorWithEqualTimestampIntervals();
//   AbsoluteTimestampsContainer absoluteTimestamps = AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsBlockWithEqualTimestampIntervals();
//   return Sensor(comparableVectorChannel, absoluteTimestamps, ProtobufSensorType::SENSOR_TYPE_PPG);
// }
//
// Sensor SensorExampleFactory::absoluteJsonDataPpgSensor() {
//   Channels comparableVectorChannel = ChannelExampleFactory::normalVectorWithAbsoluteJsonDataPpgChannel();
//   AbsoluteTimestampsContainer absoluteTimestamps = AbsoluteTimestampsContainerExampleFactory::absoluteJsonDataTimestampsContainerPgg();
//   return Sensor(comparableVectorChannel, absoluteTimestamps, ProtobufSensorType::SENSOR_TYPE_PPG);
// }
//
// Sensor SensorExampleFactory::absoluteJsonDataAccSensor() {
//   Channels comparableVectorChannel = ChannelExampleFactory::normalVectorWithAbsoluteJsonDataAccChannel();
//   AbsoluteTimestampsContainer absoluteTimestamps = AbsoluteTimestampsContainerExampleFactory::absoluteJsonDataTimestampsContainerAcc();
//   return Sensor(comparableVectorChannel, absoluteTimestamps, ProtobufSensorType::SENSOR_TYPE_ACC);
// }
//
// Sensor SensorExampleFactory::differentialJsonDataPpgSensor() {
//   Channels comparableVectorChannel = ChannelExampleFactory::normalVectorWithDifferentialJsonDataPpgChannel();
//   DifferentialTimestampsContainer differentialTimestampsContainer =
//       DifferentialTimestampsContainerExampleFactory::differentiaJsonDataTimestampsContainerPpg();
//   return Sensor(comparableVectorChannel, differentialTimestampsContainer, ProtobufSensorType::SENSOR_TYPE_PPG);
// }
//
// Sensor SensorExampleFactory::differentialJsonDataAccSensor() {
//   Channels comparableVectorChannel = ChannelExampleFactory::normalVectorWithDifferentialJsonDataAccChannel();
//   DifferentialTimestampsContainer differentialTimestampsContainer =
//       DifferentialTimestampsContainerExampleFactory::differentiaJsonDataTimestampsContainerAcc();
//   return Sensor(comparableVectorChannel, differentialTimestampsContainer, ProtobufSensorType::SENSOR_TYPE_ACC);
// }
//
// Sensors SensorExampleFactory::normalVectorWithSensors() {
//   Sensors sensors = {SensorExampleFactory::normalSensor()};
//   return sensors;
// }
//
// Sensors SensorExampleFactory::comparableVectorWithSensors() {
//   Sensors sensors = {SensorExampleFactory::comparableSensor()};
//   return sensors;
// }
//
// Sensors SensorExampleFactory::vectorWithAbsoluteJsonDataSensor() {
//   Sensors sensors = {SensorExampleFactory::absoluteJsonDataPpgSensor(), SensorExampleFactory::absoluteJsonDataAccSensor()};
//   return sensors;
// }
//
// Sensors SensorExampleFactory::vectorWithDifferentialJsonDataSensor() {
//   Sensors sensors = {SensorExampleFactory::differentialJsonDataPpgSensor(), SensorExampleFactory::differentialJsonDataAccSensor()};
//   return sensors;
// }
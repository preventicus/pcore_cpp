/*

Created by Jakob Glück 2023

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

#include "Sensor.h"

using ChannelsJson = Json::Value;

Sensor::Sensor(Channels& channels, DifferentialTimestampsContainer& differentialTimestampsContainer, ProtobufSensorType sensorType)
    : sensorType(sensorType), channels(channels), differentialTimestampsContainer(differentialTimestampsContainer) {
  this->absoluteTimestampsContainer = this->calculateAbsoluteTimestamps(differentialTimestampsContainer);
}

Sensor::Sensor(Channels& channels, AbsoluteTimestampsContainer& absoluteTimestampsContainer, ProtobufSensorType sensorType)
    : sensorType(sensorType), channels(channels), absoluteTimestampsContainer(absoluteTimestampsContainer) {
  BlockIdxs blockIdx = this->findBlockIdxs();
  this->differentialTimestampsContainer = this->calculateDifferentialTimestamps(absoluteTimestampsContainer, blockIdx);
}

Sensor::Sensor(SensorJson& sensorJson, DataForm dataForm) {
  SensorTypeString sensorTypeString = sensorJson["sensor_type"].asString();
  this->sensorType = Sensor::senorTypeFromString(sensorTypeString);
  ChannelsJson channelsJson = sensorJson["channels"];
  Channels channels;
  channels.reserve(channelsJson.size());

  switch (dataForm) {
    case DataForm::DATA_FORM_ABSOLUTE: {
      AbsoluteTimestampsContainer absoluteTimestampsContainer = AbsoluteTimestampsContainer(sensorJson["absolute_timestamps_container"]);
      this->absoluteTimestampsContainer = absoluteTimestampsContainer;
      BlockIdxs blockIdxs = this->findBlockIdxs();
      this->differentialTimestampsContainer = this->calculateDifferentialTimestamps(absoluteTimestampsContainer, blockIdxs);
      for (auto& channelJson : channelsJson) {
        channels.push_back(Channel(channelJson, this->sensorType, blockIdxs));
      }
      this->channels = channels;
      break;
    }
    case DataForm::DATA_FORM_DIFFERENTIAL: {
      for (auto& channelJson : channelsJson) {
        channels.push_back(Channel(channelJson, this->sensorType));
      }
      this->channels = channels;
      DifferentialTimestampsContainer differentialTimestampsContainer =
          DifferentialTimestampsContainer(sensorJson["differential_timestamps_container"]);
      this->differentialTimestampsContainer = differentialTimestampsContainer;
      this->absoluteTimestampsContainer = this->calculateAbsoluteTimestamps(differentialTimestampsContainer);
      break;
    }
    default: {
      std::runtime_error("dataForm is NONE");
    }
  }
}

Sensor::Sensor(const ProtobufSensor& protobufSensor) {
  this->deserialize(protobufSensor);
}

Sensor::Sensor() {
  this->channels = Channels{};
  this->absoluteTimestampsContainer = AbsoluteTimestampsContainer();
  this->differentialTimestampsContainer = DifferentialTimestampsContainer();
  this->sensorType = ProtobufSensorType::SENSOR_TYPE_NONE;
}

ProtobufSensorType Sensor::getSensorType() {
  return this->sensorType;
}

Channels Sensor::getChannels() {
  return this->channels;
}

DifferentialTimestampsContainer Sensor::getDifferentialTimestamps() {
  return this->differentialTimestampsContainer;
}

AbsoluteTimestampsContainer Sensor::getAbsoluteTimestamps() {
  return this->absoluteTimestampsContainer;
}

bool Sensor::isEqual(Sensor& sensor) {
  if (this->channels.size() != sensor.channels.size()) {
    return false;
  }
  for (size_t i = 0; i < this->channels.size(); i++) {
    if (!this->channels[i].isEqual(sensor.channels[i])) {
      return false;
    }
  }
  return this->sensorType == sensor.sensorType && this->differentialTimestampsContainer.isEqual(sensor.differentialTimestampsContainer) &&
         this->absoluteTimestampsContainer.isEqual(sensor.absoluteTimestampsContainer);
}

void Sensor::serialize(ProtobufSensor* protobufSensor) {
  if (protobufSensor == nullptr) {
    throw std::invalid_argument("Error in serialize: protobufSensor is a null pointer");
  }
  for (auto& channel : this->channels) {
    ProtobufChannel* protobufChannel = protobufSensor->add_channels();
    channel.serialize(protobufChannel);
  }

  protobufSensor->set_sensor_type(this->sensorType);
  ProtobufDifferentialTimestampContainer protobufDifferentialTimestampContainer;
  this->differentialTimestampsContainer.serialize(&protobufDifferentialTimestampContainer);
  protobufSensor->mutable_differential_timestamps_container()->CopyFrom(protobufDifferentialTimestampContainer);
}

UnixTimestamp Sensor::getFirstUnixTimestamp() {
  return this->differentialTimestampsContainer.getFirstUnixTimestamp();
}

UnixTimestamp Sensor::getLastUnixTimestamp() {
  const TimestampsIntervals timestampsIntervals_ms = this->differentialTimestampsContainer.getTimestampsIntervals();
  const BlockIntervals blockIntervals_ms = this->differentialTimestampsContainer.getBlockIntervals();
  DifferentialBlocks differentialBlocksOfFirstChannel = this->channels[0].getDifferentialBlocks();
  const size_t nLastBlock = differentialBlocksOfFirstChannel[differentialBlocksOfFirstChannel.size() - 1].getDifferentialValues().size();
  UnixTimestamp absoluteUnixTimestamp = this->getFirstUnixTimestamp();
  for (auto& blockInterval_ms : blockIntervals_ms) {
    absoluteUnixTimestamp += blockInterval_ms;
  }
  return absoluteUnixTimestamp + timestampsIntervals_ms[timestampsIntervals_ms.size() - 1] * (nLastBlock - 1);
}

Duration Sensor::getDuration() {
  return this->getLastUnixTimestamp() - this->getFirstUnixTimestamp();
}

BlockIdxs Sensor::findBlockIdxs() {
  BlockIdxs blockIdxs = {};
  if (this->absoluteTimestampsContainer.getUnixTimestamps().size() == 0) {
    return blockIdxs;
  }
  Interval referenceTimeDifference = 0;
  bool isNewBlock = true;
  blockIdxs.push_back(0);
  UnixTimestamps absoluteUnixTimestamps = this->absoluteTimestampsContainer.getUnixTimestamps();
  for (size_t i = 1; i < absoluteUnixTimestamps.size(); i++) {
    Interval timeDifference = absoluteUnixTimestamps[i] - absoluteUnixTimestamps[i - 1];
    if (isNewBlock) {
      referenceTimeDifference = timeDifference;
      isNewBlock = false;
    }
    if (timeDifference != referenceTimeDifference) {
      blockIdxs.push_back(i);
      isNewBlock = true;
    }
  }
  return blockIdxs;
}

AbsoluteTimestampsContainer Sensor::calculateAbsoluteTimestamps(DifferentialTimestampsContainer& differentialTimestampsContainer) {
  UnixTimestamps unixTimestamps_ms = {};
  DifferentialBlocks differentialBlocksOfFirstChannel = this->channels[0].getDifferentialBlocks();
  TimestampsIntervals timestampsIntervals_ms = differentialTimestampsContainer.getTimestampsIntervals();
  BlockIntervals blockIntervals_ms = differentialTimestampsContainer.getBlockIntervals();
  UnixTimestamp absoluteUnixTimestamp = differentialTimestampsContainer.getFirstUnixTimestamp();

  for (size_t i = 0; i < blockIntervals_ms.size(); i++) {
    absoluteUnixTimestamp += blockIntervals_ms[i];
    for (size_t j = 0; j < differentialBlocksOfFirstChannel[i].getDifferentialValues().size(); j++) {
      unixTimestamps_ms.push_back(absoluteUnixTimestamp + j * timestampsIntervals_ms[i]);
    }
  }
  return AbsoluteTimestampsContainer(unixTimestamps_ms);
}

DifferentialTimestampsContainer Sensor::calculateDifferentialTimestamps(AbsoluteTimestampsContainer& absoluteTimestampsContainer,
                                                                        BlockIdxs& blockIdxs) {
  DifferentialTimestampsContainer differentialTimestampsContainer;
  size_t numberOfBlocks = blockIdxs.size();
  BlockIntervals blockIntervals_ms = {};
  TimestampsIntervals timestampsIntervals_ms = {};
  UnixTimestamp firstUnixTimestamp_ms = 0;

  /*
   * blockIdxs.size = 0 -> no timestamps are included
                            return default Values for emptyBlock
   * blockIdxs.size = 1 -> case 1 : just one Block with one timestamps
                            return firstTimestamps, BlockIntervals_ms = {0}, timestampsInterval_ms{0}
   *                       case 2 : one Block with certain amount of timestmaps with same timedifferences
                            return firstTimestamps, BlockInterval_ms  = {0}, timetsampsIntervals_ms with one value (BestCase)
   * blockIdxs.size > 1 -> case 1: normal condition (Last block hold at least 2 Timestamps)
                            return calculate differentialTimestamps
   *                       case 2: the last Block hold just one Timestamp
                            return calculate differentialTimestamps  + last timestampsInterval_ms.pushback(0)
  */
  if (numberOfBlocks == 0) {
    differentialTimestampsContainer = DifferentialTimestampsContainer(firstUnixTimestamp_ms, blockIntervals_ms, timestampsIntervals_ms);
    return differentialTimestampsContainer;
  }

  UnixTimestamps absoluteUnixTimestamps = absoluteTimestampsContainer.getUnixTimestamps();
  firstUnixTimestamp_ms = absoluteUnixTimestamps[0];
  if (numberOfBlocks == 1) {
    Interval timestampsInterval = absoluteUnixTimestamps[1] - firstUnixTimestamp_ms;
    timestampsIntervals_ms.push_back(absoluteUnixTimestamps.size() == 1 ? 0 : timestampsInterval);
    blockIntervals_ms.push_back(0);
    differentialTimestampsContainer = DifferentialTimestampsContainer(firstUnixTimestamp_ms, blockIntervals_ms, timestampsIntervals_ms);
    return differentialTimestampsContainer;
  }

  blockIntervals_ms.push_back(0);
  timestampsIntervals_ms.push_back(absoluteUnixTimestamps[1] - firstUnixTimestamp_ms);
  for (size_t i = 1; i < blockIdxs.size() - 1; i++) {
    const BlockIdx previousBlockIdx = blockIdxs[i - 1];
    const BlockIdx currentBlockIdx = blockIdxs[i];
    timestampsIntervals_ms.push_back(absoluteUnixTimestamps[currentBlockIdx + 1] - absoluteUnixTimestamps[currentBlockIdx]);
    blockIntervals_ms.push_back(absoluteUnixTimestamps[currentBlockIdx] - absoluteUnixTimestamps[previousBlockIdx]);
  }
  blockIntervals_ms.push_back(absoluteUnixTimestamps[blockIdxs[numberOfBlocks - 1]] - absoluteUnixTimestamps[blockIdxs[numberOfBlocks - 2]]);
  timestampsIntervals_ms.push_back(absoluteUnixTimestamps.size() - 1 == blockIdxs[numberOfBlocks - 1]
                                       ? 0
                                       : absoluteUnixTimestamps[blockIdxs[numberOfBlocks - 1] + 1] -
                                             absoluteUnixTimestamps[blockIdxs[numberOfBlocks - 1]]);
  differentialTimestampsContainer = DifferentialTimestampsContainer(firstUnixTimestamp_ms, blockIntervals_ms, timestampsIntervals_ms);
  return differentialTimestampsContainer;
}

SensorJson Sensor::toJson(DataForm dataForm) {
  SensorJson sensorJson;
  ChannelsJson channelsJson(Json::arrayValue);

  for (auto& channel : this->channels) {
    channelsJson.append(channel.toJson(dataForm, this->sensorType));
  }
  sensorJson["channels"] = channelsJson;

  switch (dataForm) {
    case DataForm::DATA_FORM_ABSOLUTE: {
      sensorJson["absolute_timestamps_container"] = this->absoluteTimestampsContainer.toJson();
      break;
    }
    case DataForm::DATA_FORM_DIFFERENTIAL: {
      sensorJson["differential_timestamps_container"] = this->differentialTimestampsContainer.toJson();
      break;
    }
    default: {
      throw std::runtime_error("dataForm is not set");
    }
  }
  sensorJson["sensor_type"] = Sensor::senorTypeToString(this->sensorType);
  return sensorJson;
}

void Sensor::deserialize(const ProtobufSensor& protobufSensor) {
  Channels channels;
  for (auto& channel : protobufSensor.channels()) {
    channels.push_back(Channel(channel));
  }
  this->channels = channels;
  this->sensorType = protobufSensor.sensor_type();
  this->differentialTimestampsContainer = DifferentialTimestampsContainer(protobufSensor.differential_timestamps_container());
  this->absoluteTimestampsContainer = this->calculateAbsoluteTimestamps(this->differentialTimestampsContainer);
}

ProtobufSensorType Sensor::senorTypeFromString(SensorTypeString& senorTypeString) {
  if (senorTypeString == "SENSOR_TYPE_PPG") {
    return ProtobufSensorType::SENSOR_TYPE_PPG;
  } else if (senorTypeString == "SENSOR_TYPE_ACC") {
    return ProtobufSensorType::SENSOR_TYPE_ACC;
  } else {
    return ProtobufSensorType::SENSOR_TYPE_NONE;
  }
}

SensorTypeString Sensor::senorTypeToString(ProtobufSensorType protobufSensorType) {
  switch (protobufSensorType) {
    case ProtobufSensorType::SENSOR_TYPE_ACC: {
      return "SENSOR_TYPE_ACC";
    }
    case ProtobufSensorType::SENSOR_TYPE_PPG: {
      return "SENSOR_TYPE_PPG";
    }
    default: {
      return "SENSOR_TYPE_NONE";
    }
  }
}

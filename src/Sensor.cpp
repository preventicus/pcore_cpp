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

Sensor::Sensor(std::vector<Channel> channels, DifferentialTimestampsContainer differentialTimestampsContainer, ProtobufSensorType protobufSensorType)
    : protobufSensorType(protobufSensorType), channels(channels), differentialTimestampsContainer(differentialTimestampsContainer) {
  this->absoluteTimestampsContainer = this->calculateAbsoluteTimestamps(differentialTimestampsContainer);
}

Sensor::Sensor(std::vector<Channel> channels, AbsoluteTimestampsContainer absoluteTimestampsContainer, ProtobufSensorType protobufSensorType)
    : protobufSensorType(protobufSensorType), channels(channels), absoluteTimestampsContainer(absoluteTimestampsContainer) {
  std::vector<size_t> blockIdxs = this->findBlocksIdxs();
  this->differentialTimestampsContainer = this->calculateDifferentialTimestamps(absoluteTimestampsContainer, blockIdxs);
}

Sensor::Sensor(Json::Value& sensor, DataForm dataForm) {
  Json::Value channelsJson = sensor["channels"];
  std::vector<Channel> channels;
  channels.reserve(channelsJson.size());
  switch (dataForm) {
    case DataForm::DIFFERENTIAL: {
      this->protobufSensorType = this->toEnum(sensor["sensor_type"]);
      for (auto& channelJson : channelsJson) {
        channels.push_back(Channel(channelJson, this->protobufSensorType));
      }
      this->channels = channels;

      DifferentialTimestampsContainer differentialTimestampsContainer = DifferentialTimestampsContainer(sensor["differential_timestamps_container"]);
      this->differentialTimestampsContainer = differentialTimestampsContainer;
      this->absoluteTimestampsContainer = this->calculateAbsoluteTimestamps(differentialTimestampsContainer);
      break;
    }
    case DataForm::ABSOLUTE: {
      this->protobufSensorType = this->toEnum(sensor["sensor_type"]);
      AbsoluteTimestampsContainer absoluteTimestampsContainer = AbsoluteTimestampsContainer(sensor["absolute_timestamps_container"]);
      this->absoluteTimestampsContainer = absoluteTimestampsContainer;
      std::vector<size_t> blockIdxs = this->findBlocksIdxs();
      this->differentialTimestampsContainer = this->calculateDifferentialTimestamps(absoluteTimestampsContainer, blockIdxs);
      for (auto& channelJson : channelsJson) {
        channels.push_back(Channel(channelJson, this->protobufSensorType, blockIdxs));
      }
      this->channels = channels;
      break;
    }
    default: {
      break;
    }
  }
}

Sensor::Sensor(const ProtobufSensor& protobufSensor) {
  this->deserialize(protobufSensor);
}

Sensor::Sensor() {
  this->channels = std::vector<Channel>{};
  this->absoluteTimestampsContainer = AbsoluteTimestampsContainer();
  this->differentialTimestampsContainer = DifferentialTimestampsContainer();
  this->protobufSensorType = ProtobufSensorType::SENSOR_TYPE_NONE;
}

ProtobufSensorType Sensor::getSensorType() {
  return this->protobufSensorType;
}

std::vector<Channel> Sensor::getChannels() {
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
  return this->protobufSensorType == sensor.protobufSensorType &&
         this->differentialTimestampsContainer.isEqual(sensor.differentialTimestampsContainer) &&
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
  protobufSensor->set_sensor_type(this->protobufSensorType);
  ProtobufDifferentialTimestampContainer protobufTimestampContainer;
  this->differentialTimestampsContainer.serialize(&protobufTimestampContainer);
  protobufSensor->mutable_differential_timestamps_container()->CopyFrom(protobufTimestampContainer);
}

uint64_t Sensor::getFirstTimestamp() {
  return this->differentialTimestampsContainer.getFirstTimestamp();
}

uint64_t Sensor::getLastTimestamp() {
  const std::vector<uint32_t> timestampIntervals_ms = this->differentialTimestampsContainer.getTimestampsIntervals();
  const std::vector<uint32_t> blockIntervals_ms = this->differentialTimestampsContainer.getBlockIntervals();
  std::vector<DifferentialBlock> firstChannelBlocks = this->channels[0].getDifferentialBlocks();
  const size_t nLastBlock = firstChannelBlocks[firstChannelBlocks.size() - 1].getDifferentialValues().size();
  long h = 0;
  for (auto& BlockIntervals : blockIntervals_ms) {
    h += BlockIntervals;
  }
  return this->getFirstTimestamp() + h + timestampIntervals_ms[timestampIntervals_ms.size() - 1] * (nLastBlock - 1);
}

uint64_t Sensor::getDuration() {
  return this->getLastTimestamp() - this->getFirstTimestamp();
}

std::vector<size_t> Sensor::findBlocksIdxs() {
  std::vector<size_t> blocksIdxs = {};
  if (this->absoluteTimestampsContainer.getUnixTimestamps().size() == 0) {
    return blocksIdxs;
  }
  uint64_t referenceTimeDifference = 0;
  bool isNewBlock = true;
  blocksIdxs.push_back(0);
  std::vector<uint64_t> absoluteUnixTimestamps = this->absoluteTimestampsContainer.getUnixTimestamps();
  for (size_t i = 1; i < absoluteUnixTimestamps.size(); i++) {
    uint64_t timeDifference = absoluteUnixTimestamps[i] - absoluteUnixTimestamps[i - 1];
    if (isNewBlock) {
      referenceTimeDifference = timeDifference;
      isNewBlock = false;
    }
    if (timeDifference != referenceTimeDifference) {
      blocksIdxs.push_back(i);
      isNewBlock = true;
    }
  }
  return blocksIdxs;
}

AbsoluteTimestampsContainer Sensor::calculateAbsoluteTimestamps(DifferentialTimestampsContainer differentialTimestamps) {
  std::vector<uint64_t> unixTimestamps_ms = {};

  std::vector<DifferentialBlock> firstChannelBlocks = this->channels[0].getDifferentialBlocks();
  uint64_t firstTimestamp_ms = differentialTimestamps.getFirstTimestamp();
  std::vector<uint32_t> timestamps_intervals_ms = differentialTimestamps.getTimestampsIntervals();
  std::vector<uint32_t> blockIntervals_ms = differentialTimestamps.getBlockIntervals();

  uint64_t sumTimeStampIntervals = 0;

  for (size_t i = 0; i < timestamps_intervals_ms.size(); i++) {
    sumTimeStampIntervals += blockIntervals_ms[i];
    for (size_t j = 0; j < firstChannelBlocks[i].getDifferentialValues().size(); j++) {
      unixTimestamps_ms.push_back(firstTimestamp_ms + sumTimeStampIntervals + j * timestamps_intervals_ms[i]);
    }
  }
  return AbsoluteTimestampsContainer(unixTimestamps_ms);
}

DifferentialTimestampsContainer Sensor::calculateDifferentialTimestamps(AbsoluteTimestampsContainer absoluteTimestamps,
                                                                        std::vector<size_t> blocksIdxs) {
  DifferentialTimestampsContainer differentialTimestampsContainer;
  size_t numberOfBlocks = blocksIdxs.size();
  std::vector<uint64_t> absoluteUnixTimestamps_ms = absoluteTimestamps.getUnixTimestamps();
  std::vector<uint32_t> blockIntervals_ms = {};
  std::vector<uint32_t> timestampIntervals_ms = {};
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
    uint64_t firstTimestamp_ms = 0;
    return DifferentialTimestampsContainer(firstTimestamp_ms, blockIntervals_ms, timestampIntervals_ms);
  }
  uint64_t firstTimestamp_ms = absoluteTimestamps.getUnixTimestamps()[0];
  blockIntervals_ms.push_back(0);
  if (numberOfBlocks == 1) {
    int32_t timestampsInterval_ms = absoluteUnixTimestamps_ms[1] - firstTimestamp_ms;
    timestampIntervals_ms.push_back(absoluteUnixTimestamps_ms.size() == 1 ? 0 : timestampsInterval_ms);
    differentialTimestampsContainer = DifferentialTimestampsContainer(firstTimestamp_ms, blockIntervals_ms, timestampIntervals_ms);
    return differentialTimestampsContainer;
  }
  timestampIntervals_ms.push_back(absoluteUnixTimestamps_ms[1] - firstTimestamp_ms);
  for (size_t i = 1; i < blocksIdxs.size() - 1; i++) {
    const size_t prevIdx = blocksIdxs[i - 1];
    const size_t idx = blocksIdxs[i];
    timestampIntervals_ms.push_back(absoluteUnixTimestamps_ms[idx + 1] - absoluteUnixTimestamps_ms[idx]);
    blockIntervals_ms.push_back(absoluteUnixTimestamps_ms[idx] - absoluteUnixTimestamps_ms[prevIdx]);
  }
  blockIntervals_ms.push_back(
      absoluteUnixTimestamps_ms[blocksIdxs[numberOfBlocks - 1]] -
      absoluteUnixTimestamps_ms[blocksIdxs[numberOfBlocks - 2]]);  // the same blockInterval_ms applies to both of the following conditions
  int32_t timestampsInterval =
      absoluteUnixTimestamps_ms[blocksIdxs[numberOfBlocks - 1] + 1] - absoluteUnixTimestamps_ms[blocksIdxs[numberOfBlocks - 1]];
  timestampIntervals_ms.push_back(absoluteUnixTimestamps_ms.size() - 1 == blocksIdxs[numberOfBlocks - 1]
                                      ? 0
                                      : timestampsInterval);  // if the condition is true, last block hold one timestamp -> Case 2 t
  differentialTimestampsContainer = DifferentialTimestampsContainer(firstTimestamp_ms, blockIntervals_ms, timestampIntervals_ms);
  return differentialTimestampsContainer;
}

Json::Value Sensor::toJson(DataForm dataForm) {
  Json::Value sensor;
  Json::Value channels(Json::arrayValue);
  Json::Value sensorType(Json::stringValue);
  for (auto& channel : this->channels) {
    channels.append(channel.toJson(dataForm, this->protobufSensorType));
  }
  switch (dataForm) {
    case DataForm::ABSOLUTE: {
      sensor["absolute_timestamps_container"] = this->absoluteTimestampsContainer.toJson();
      break;
    }
    case DataForm::DIFFERENTIAL: {
      sensor["differential_timestamps_container"] = this->differentialTimestampsContainer.toJson();
    }
    default: {
      break;
    }
  }
  sensor["channels"] = channels;
  sensor["sensor_type"] = this->toString(this->protobufSensorType);
  return sensor;
}

void Sensor::deserialize(const ProtobufSensor& protobufSensor) {
  std::vector<Channel> channels{};
  for (auto& channel : protobufSensor.channels()) {
    channels.push_back(Channel(channel));
  }
  this->channels = channels;
  this->protobufSensorType = protobufSensor.sensor_type();
  this->differentialTimestampsContainer = DifferentialTimestampsContainer(protobufSensor.differential_timestamps_container());
  this->absoluteTimestampsContainer = this->calculateAbsoluteTimestamps(this->differentialTimestampsContainer);
}

std::string Sensor::toString(ProtobufSensorType protobufSensorType) {
  switch (protobufSensorType) {
    case ProtobufSensorType::SENSOR_TYPE_ACC: {
      return "SENSOR_TYPE_ACC";
    }
    case ProtobufSensorType::SENSOR_TYPE_PPG: {
      return "SENSOR_TYPE_PPG";
    }
    default: {
      break;
    }
  }
}

ProtobufSensorType Sensor::toEnum(Json::Value protobufSensorType) {
  ProtobufSensorType sensorType;
  if (protobufSensorType.asString() == "SENSOR_TYPE_PPG") {
    sensorType = ProtobufSensorType::SENSOR_TYPE_PPG;
  }
  if (protobufSensorType.asString() == "SENSOR_TYPE_ACC") {
    sensorType = ProtobufSensorType::SENSOR_TYPE_ACC;
  }
  return sensorType;
}
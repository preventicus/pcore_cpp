/*

Created by Jakob Glück 2023

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
#include "Sensor.h"

Sensor::Sensor(std::vector<Channel> channels, DifferentialTimestampsContainer differentialTimestampsContainer, ProtobufSensortype sensorType)
    : sensorType(sensorType), channels(channels), differentialTimestampsContainer(differentialTimestampsContainer) {
  this->channels = channels;
  this->sensorType = sensorType;
  this->absoluteTimestampsContainer = {};
  this->differentialTimestampsContainer = differentialTimestampsContainer;
}

Sensor::Sensor(std::vector<Channel> channels, AbsoluteTimestampsContainer absoluteTimestampsContainer, ProtobufSensortype sensorType)
    : sensorType(sensorType), channels(channels), absoluteTimestampsContainer(absoluteTimestampsContainer) {
  this->channels = channels;
  this->sensorType = sensorType;
  this->absoluteTimestampsContainer = absoluteTimestampsContainer;
  this->differentialTimestampsContainer = {};
}
Sensor::Sensor(const ProtobufSensor& protobufSensor) {
  this->deserialize(protobufSensor);
}

Sensor::Sensor() {
  this->channels = std::vector<Channel>{};
  this->absoluteTimestampsContainer = AbsoluteTimestampsContainer();
  this->differentialTimestampsContainer = DifferentialTimestampsContainer();
  this->sensorType = ProtobufType::SENSOR_TYPE_NONE;
}

ProtobufSensortype Sensor::getSensorType() {
  return this->sensorType;
}

std::vector<Channel> Sensor::getChannels() {
  return this->channels;
}

DataForm Sensor::getTimestampForm() {
  DataForm dataForm = NOT_SET;
  for (auto& channel : this->getChannels()) {
    dataForm = channel.getDataform();
  }
  return dataForm;
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

void Sensor::switchToDifferentialForm() {
  std::vector<size_t> blockIdx = this->findBlocksIdxs();
  this->differentialTimestampsContainer = this->cutUnixInDifferentialTimestamps(blockIdx);
  for (auto& channel : this->channels) {
    channel.switchInDifferentialFrom(blockIdx);
  }
}

void Sensor::switchInAbsoluteFrom() {
  this->absoluteTimestampsContainer = this->calcAbsoluteTimestampsFrom();
  for (auto& channel : this->channels) {
    channel.switchInAbsoluteFrom();
  }
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
  ProtobufDifferentialTimestampContainer protobufTimestampContainer;
  this->differentialTimestampsContainer.serialize(&protobufTimestampContainer);
  protobufSensor->mutable_differential_timestamps_container()->CopyFrom(protobufTimestampContainer);
}

uint32_t Sensor::firstTimestamp() {
  return this->differentialTimestampsContainer.getFirstTimestamp();
}

uint32_t Sensor::lastTimestamp() {
  const std::vector<uint32_t> timestampIntervals_ms = this->differentialTimestampsContainer.getTimestampsIntervals();
  const std::vector<uint32_t> blockIntervals_ms = this->differentialTimestampsContainer.getBlockIntervals();
  std::vector<DifferentialBlock> firstChannelBlocks = this->channels[0].getDifferentialBlocks();
  const size_t nLastBlock = firstChannelBlocks[firstChannelBlocks.size() - 1].getDiffValues().size();
  long h = 0;
  for (auto& BlockIntervals : blockIntervals_ms) {
    h += BlockIntervals;
  }
  return Sensor::firstTimestamp() + h + timestampIntervals_ms[timestampIntervals_ms.size() - 1] * nLastBlock;
}

uint32_t Sensor::duration() {
  return Sensor::lastTimestamp() - Sensor::firstTimestamp();
}

void Sensor::deserialize(const ProtobufSensor& protobufSensor) {
  std::vector<Channel> channels{};
  for (auto& channel : protobufSensor.channels()) {
    channels.push_back(Channel(channel));
  }
  this->channels = channels;
  this->sensorType = protobufSensor.sensor_type();
  this->differentialTimestampsContainer = DifferentialTimestampsContainer(protobufSensor.differential_timestamps_container());
}

std::vector<size_t> Sensor::findBlocksIdxs() {
  uint64_t referenceTimeDifference = 0;
  bool isNewBlock = true;
  std::vector<size_t> blocksIdxs = {0};
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

AbsoluteTimestampsContainer Sensor::calcAbsoluteTimestampsFrom() {
  std::vector<DifferentialBlock> firstChannelBlocks = this->channels[0].getDifferentialBlocks();
  std::vector<uint64_t> unixTimestamps_ms = {};
  std::vector<uint32_t> differentialTimestampsInterval = this->differentialTimestampsContainer.getTimestampsIntervals();
  std::vector<uint32_t> differentialBlockInterval = this->differentialTimestampsContainer.getBlockIntervals();
  const uint64_t firstTimestamp_ms = this->differentialTimestampsContainer.getFirstTimestamp();
  uint32_t sumBlockInterval = 0;
  for (size_t i = 0; i < differentialTimestampsInterval.size(); i++) {
    sumBlockInterval += differentialBlockInterval[i];
    for (size_t j = 0; j < firstChannelBlocks[i].getDiffValues().size(); j++) {
      unixTimestamps_ms.push_back(firstTimestamp_ms + sumBlockInterval + j * differentialTimestampsInterval[i]);
    }
  }
  return AbsoluteTimestampsContainer(unixTimestamps_ms);
}

DifferentialTimestampsContainer Sensor::cutUnixInDifferentialTimestamps(std::vector<size_t> blocksIdxs) {
  std::vector<uint64_t> absoluteUnixtimestamps = this->absoluteTimestampsContainer.getUnixTimestamps();
  uint64_t firstTimestamp_ms = this->absoluteTimestampsContainer.getUnixTimestamps()[0];
  std::vector<uint32_t> blockIntervals_ms = {};
  std::vector<uint32_t> timestampIntervals_ms = {};
  blockIntervals_ms.push_back(0);
  timestampIntervals_ms.push_back(absoluteUnixtimestamps[1] - firstTimestamp_ms);
  for (size_t i = 1; i < blocksIdxs.size(); i++) {
    const size_t prevIdx = blocksIdxs[i - 1];
    const size_t idx = blocksIdxs[i];
    timestampIntervals_ms.push_back(absoluteUnixtimestamps[idx + 1] - absoluteUnixtimestamps[idx]);
    blockIntervals_ms.push_back(absoluteUnixtimestamps[idx] - absoluteUnixtimestamps[prevIdx]);
  }
  return DifferentialTimestampsContainer(firstTimestamp_ms, blockIntervals_ms, timestampIntervals_ms);
}
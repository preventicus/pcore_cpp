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

Sensor::Sensor(std::vector<Channel> channels,
               DifferentialTimestampsContainer differentialTimestamps,
               AbsoluteTimestampsContainer absoluteTimestamps,
               ProtobufSensortype sensorType)
    : sensorType(sensorType), channels(channels), differentialTimestamps(differentialTimestamps), absoluteTimestamps(absoluteTimestamps) {}

Sensor::Sensor(const ProtobufSensor& protobufSensor) {
  this->deserialize(protobufSensor);
}

Sensor::Sensor() {
  this->channels = std::vector<Channel>{};
  this->absoluteTimestamps = AbsoluteTimestampsContainer();
  this->differentialTimestamps = DifferentialTimestampsContainer();
  this->sensorType = ProtobufType::SENSOR_TYPE_NONE;
}

ProtobufSensortype Sensor::getSensorType() {
  return this->sensorType;
}

std::vector<Channel> Sensor::getChannels() {
  return this->channels;
}

DataForm Sensor::getTimestampForm() {
  return DataForm::DIFFERENTIAL;
}

DifferentialTimestampsContainer Sensor::getDifferentialTimestamps() {
  return this->differentialTimestamps;
}

AbsoluteTimestampsContainer Sensor::getAbsoluteTimestamps() {
  return this->absoluteTimestamps;
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
  return this->sensorType == sensor.sensorType && this->differentialTimestamps.isEqual(sensor.differentialTimestamps) &&
         this->absoluteTimestamps.isEqual(sensor.absoluteTimestamps);
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
  this->differentialTimestamps.serialize(&protobufTimestampContainer);
  protobufSensor->mutable_differential_timestamps_container()->CopyFrom(protobufTimestampContainer);
}

void Sensor::deserialize(const ProtobufSensor& protobufSensor) {
  std::vector<Channel> channels{};
  for (auto& channel : protobufSensor.channels()) {
    channels.push_back(Channel(channel));
  }
  this->channels = channels;
  this->sensorType = protobufSensor.sensor_type();
  this->differentialTimestamps = DifferentialTimestampsContainer(protobufSensor.differential_timestamps_container());
}

uint32_t Sensor::firstTimestamp() {
  return this->differentialTimestamps.getFirstTimestamp();
}

uint32_t Sensor::lastTimestamp() {
  const std::vector<uint32_t> timestampIntervals_ms = this->differentialTimestamps.getTimestampsIntervals();
  const std::vector<uint32_t> blockIntervals_ms = this->differentialTimestamps.getBlockIntervals();
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

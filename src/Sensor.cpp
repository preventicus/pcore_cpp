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

#include "Sensor.h"

#include <utility>

Sensor::Sensor(Channels channels, DifferentialTimestampsContainer differentialTimestampsContainer, ProtobufSensorType sensorType)
    : sensorType(sensorType), channels(std::move(channels)), differentialTimestampsContainer(std::move(differentialTimestampsContainer)) {}

Sensor::Sensor(Channels channels, AbsoluteTimestampsContainer absoluteTimestampsContainer, ProtobufSensorType sensorType)
    : sensorType(sensorType), channels(std::move(channels)), absoluteTimestampsContainer(std::move(absoluteTimestampsContainer)) {}

Sensor::Sensor(const SensorJson& sensorJson, DataForm dataForm)
    : sensorType(Sensor::senorTypeFromString(sensorJson["sensor_type"].asString())),
      channels([&]() {
        ChannelsJson channelsJson = sensorJson["channels"];
        Channels channels;
        channels.reserve(channelsJson.size());
        for (auto& channelJson : channelsJson) {
          channels.emplace_back(Channel(channelJson, this->sensorType, dataForm));
        }
        return channels;
      }()),
      differentialTimestampsContainer([&]() {
        switch (dataForm) {
          case DataForm::DATA_FORM_ABSOLUTE: {
            return DifferentialTimestampsContainer();
          }
          case DataForm::DATA_FORM_DIFFERENTIAL: {
            return DifferentialTimestampsContainer(sensorJson["differential_timestamps_container"]);
          }
          default: {
            throw std::runtime_error("dataForm is NONE");
          }
        }
      }()),
      absoluteTimestampsContainer([&]() {
        switch (dataForm) {
          case DataForm::DATA_FORM_ABSOLUTE: {
            return AbsoluteTimestampsContainer(sensorJson["absolute_timestamps_container"]);
          }
          case DataForm::DATA_FORM_DIFFERENTIAL: {
            return AbsoluteTimestampsContainer();
          }
          default: {
            throw std::runtime_error("dataForm is NONE");
          }
        }
      }()) {}

Sensor::Sensor(const ProtobufSensor& protobufSensor)
    : sensorType(protobufSensor.sensor_type()),
      channels([&]() {
        Channels channels;
        for (auto& channel : protobufSensor.channels()) {
          channels.emplace_back(Channel(channel));
        }
        return channels;
      }()),
      differentialTimestampsContainer(DifferentialTimestampsContainer(protobufSensor.differential_timestamps_container())),
      absoluteTimestampsContainer(AbsoluteTimestampsContainer()) {}

Sensor::Sensor()
    : sensorType(ProtobufSensorType::SENSOR_TYPE_NONE),
      channels({}),
      differentialTimestampsContainer(DifferentialTimestampsContainer()),
      absoluteTimestampsContainer(AbsoluteTimestampsContainer()) {}

ProtobufSensorType Sensor::getSensorType() const {
  return this->sensorType;
}

Channels Sensor::getChannels() const {
  return this->channels;
}

DifferentialTimestampsContainer Sensor::getDifferentialTimestamps() const {
  return this->differentialTimestampsContainer;
}

AbsoluteTimestampsContainer Sensor::getAbsoluteTimestamps() const {
  return this->absoluteTimestampsContainer;
}

bool Sensor::operator==(const Sensor& sensor) const {
  if (this->channels.size() != sensor.channels.size()) {
    return false;
  }
  const auto numberOfChannels = this->channels.size();
  for (size_t i = 0; i < numberOfChannels; i++) {
    if (this->channels[i] != sensor.channels[i]) {
      return false;
    }
  }
  return this->sensorType == sensor.sensorType && this->differentialTimestampsContainer == sensor.differentialTimestampsContainer &&
         this->absoluteTimestampsContainer == sensor.absoluteTimestampsContainer;
}

bool Sensor::operator!=(const Sensor& sensor) const {
  return !(*this == sensor);
}

// bool Sensor::isSet() {
//   return this->channels.empty() && this->sensorType == ProtobufSensorType::SENSOR_TYPE_NONE && ( !this->absoluteTimestampsContainer.isSet() &&
//   !this->differentialTimestampsContainer.isSet() );
// }

void Sensor::serialize(ProtobufSensor* protobufSensor) const {
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

void Sensor::switchDataForm(const DataForm currentDataForm) {
  switch (currentDataForm) {
    case DataForm::DATA_FORM_DIFFERENTIAL: {
      this->absoluteTimestampsContainer = this->calculateAbsoluteTimestamps(this->differentialTimestampsContainer);
      this->differentialTimestampsContainer = DifferentialTimestampsContainer();
      for (auto& channel : this->channels) {
        channel.switchDataForm();
      }
      break;
    }
    case DataForm::DATA_FORM_ABSOLUTE: {
      BlockIdxs blockIdxs = this->findBlockIdxs();
      this->differentialTimestampsContainer = this->calculateDifferentialTimestamps(this->absoluteTimestampsContainer, blockIdxs);
      this->absoluteTimestampsContainer = AbsoluteTimestampsContainer();
      for (auto& channel : this->channels) {
        channel.switchDataForm(blockIdxs);
      }
      break;
    }
    default: {
      throw std::runtime_error("CurrentDataForm is NONE");
    }
  }
}

UnixTimestamp Sensor::getFirstUnixTimestamp(const DataForm dataForm) const {
  switch (dataForm) {
    case DataForm::DATA_FORM_ABSOLUTE: {
      UnixTimestamps unixTimestamps = this->absoluteTimestampsContainer.getUnixTimestamps();
      if (unixTimestamps.empty()) {  // TODO use is set methode of absoluteTimestampsContainer
        throw std::runtime_error("absoluteTimestampsContainer is not set");
      } else {
        return unixTimestamps[0];  // TODO add firsttimestamp in absoluteTimestampsContainer
      }
    }
    case DataForm::DATA_FORM_DIFFERENTIAL: {
      // TODO use isSet methode
      return this->differentialTimestampsContainer.getFirstUnixTimestamp();
    }
    case DataForm::DATA_FORM_NONE: {
      throw std::invalid_argument("dataForm is none");
    }
  }
}

UnixTimestamp Sensor::getLastUnixTimestamp(const DataForm dataForm) const {
  switch (dataForm) {
    case DataForm::DATA_FORM_ABSOLUTE: {
      UnixTimestamps unixTimestamps = this->absoluteTimestampsContainer.getUnixTimestamps();
      if (unixTimestamps.empty()) {  // TODO use is set methode of absoluteTimestampsContainer
        throw std::runtime_error("absoluteTimestampsContainer is not set");
      } else {
        return unixTimestamps.back();  // TODO add firsttimestamp in absoluteTimestampsContainer
      }
    }
    case DataForm::DATA_FORM_DIFFERENTIAL: {
      // TODO use isSet methode
      const auto timestampsIntervals_ms = this->differentialTimestampsContainer.getTimestampsIntervals();
      const auto blockIntervals_ms = this->differentialTimestampsContainer.getBlockIntervals();
      const auto differentialBlocksOfFirstChannel = this->channels[0].getDifferentialBlocks();
      const auto nLastBlock = differentialBlocksOfFirstChannel[differentialBlocksOfFirstChannel.size() - 1].getDifferentialValues().size();
      auto absoluteUnixTimestamp = this->getFirstUnixTimestamp(dataForm);
      for (auto& blockInterval_ms : blockIntervals_ms) {
        absoluteUnixTimestamp += blockInterval_ms;
      }
      return absoluteUnixTimestamp + timestampsIntervals_ms[timestampsIntervals_ms.size() - 1] * (nLastBlock - 1);
    }
    case DataForm::DATA_FORM_NONE: {
      throw std::invalid_argument("dataForm is none");
    }
  }
}

Duration Sensor::getDuration(const DataForm dataForm) const {
  return this->getLastUnixTimestamp(dataForm) - this->getFirstUnixTimestamp(dataForm);
}

BlockIdxs Sensor::findBlockIdxs() const {
  BlockIdxs blockIdxs = {};
  if (this->absoluteTimestampsContainer.getUnixTimestamps().size() == 0) {  // TODO use is set
    return blockIdxs;
  }
  Interval referenceTimeDifference = 0;
  bool isNewBlock = true;
  blockIdxs.push_back(0);
  const auto absoluteUnixTimestamps = this->absoluteTimestampsContainer.getUnixTimestamps();
  const auto numberOfElements = absoluteUnixTimestamps.size();
  for (size_t i = 1; i < numberOfElements; i++) {
    const Interval timeDifference = absoluteUnixTimestamps[i] - absoluteUnixTimestamps[i - 1];
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

AbsoluteTimestampsContainer Sensor::calculateAbsoluteTimestamps(const DifferentialTimestampsContainer& differentialTimestampsContainer) const {
  const auto differentialBlocksOfFirstChannel = this->channels[0].getDifferentialBlocks();
  const auto timestampsIntervals_ms = differentialTimestampsContainer.getTimestampsIntervals();
  const auto blockIntervals_ms = differentialTimestampsContainer.getBlockIntervals();
  auto absoluteUnixTimestamp = differentialTimestampsContainer.getFirstUnixTimestamp();

  size_t numberOfElements = 0;
  for (auto& differentialBlockOfFirstChannel : differentialBlocksOfFirstChannel) {
    numberOfElements += differentialBlockOfFirstChannel.getDifferentialValues().size();
  }
  UnixTimestamps unixTimestamps_ms = {};
  unixTimestamps_ms.reserve(numberOfElements);

  const auto numberOfBlockIntervals = blockIntervals_ms.size();
  for (size_t i = 0; i < numberOfBlockIntervals; i++) {
    absoluteUnixTimestamp += blockIntervals_ms[i];
    const auto numberOfDifferentialValues = differentialBlocksOfFirstChannel[i].getDifferentialValues().size();
    for (size_t j = 0; j < numberOfDifferentialValues; j++) {
      unixTimestamps_ms.emplace_back(absoluteUnixTimestamp + j * timestampsIntervals_ms[i]);
    }
  }
  return AbsoluteTimestampsContainer(unixTimestamps_ms);
}

DifferentialTimestampsContainer Sensor::calculateDifferentialTimestamps(const AbsoluteTimestampsContainer& absoluteTimestampsContainer,
                                                                        const BlockIdxs& blockIdxs) const {
  const auto numberOfBlocks = blockIdxs.size();
  BlockIntervals blockIntervals_ms = {};
  TimestampsIntervals timestampsIntervals_ms = {};
  UnixTimestamp firstUnixTimestamp_ms = 0;

  /*
   * blockIdxs.size = 0 -> no timestamps are included
                            return default Values for emptyBlock
   * blockIdxs.size = 1 -> case 1 : just one Block with one timestamps
                            return firstTimestamps, BlockIntervals_ms = {0}, timestampsInterval_ms{0}
   *                       case 2 : one Block with certain amount of timestamps with same time differences
                            return firstTimestamps, BlockInterval_ms  = {0}, timestampsIntervals_ms with one value (BestCase)
   * blockIdxs.size > 1 -> case 1: normal condition (Last block hold at least 2 Timestamps)
                            return calculate differentialTimestamps
   *                       case 2: the last Block hold just one Timestamp
                            return calculate differentialTimestamps  + last timestampsInterval_ms.pushback(0)
  */
  if (numberOfBlocks == 0) {
    return DifferentialTimestampsContainer(firstUnixTimestamp_ms, blockIntervals_ms, timestampsIntervals_ms);
  }

  const auto absoluteUnixTimestamps = absoluteTimestampsContainer.getUnixTimestamps();
  firstUnixTimestamp_ms = absoluteUnixTimestamps[0];
  if (numberOfBlocks == 1) {
    Interval timestampsInterval = absoluteUnixTimestamps[1] - firstUnixTimestamp_ms;
    timestampsIntervals_ms.emplace_back(absoluteUnixTimestamps.size() == 1 ? 0 : timestampsInterval);
    blockIntervals_ms.push_back(0);
    return DifferentialTimestampsContainer(firstUnixTimestamp_ms, blockIntervals_ms, timestampsIntervals_ms);
  }

  blockIntervals_ms.push_back(0);
  timestampsIntervals_ms.emplace_back(absoluteUnixTimestamps[1] - firstUnixTimestamp_ms);
  const auto numberOfIntervals = blockIdxs.size() - 1;
  for (size_t i = 1; i < numberOfIntervals; i++) {
    const BlockIdx previousBlockIdx = blockIdxs[i - 1];
    const BlockIdx currentBlockIdx = blockIdxs[i];
    timestampsIntervals_ms.emplace_back(absoluteUnixTimestamps[currentBlockIdx + 1] - absoluteUnixTimestamps[currentBlockIdx]);
    blockIntervals_ms.emplace_back(absoluteUnixTimestamps[currentBlockIdx] - absoluteUnixTimestamps[previousBlockIdx]);
  }
  blockIntervals_ms.emplace_back(absoluteUnixTimestamps[blockIdxs[numberOfBlocks - 1]] - absoluteUnixTimestamps[blockIdxs[numberOfBlocks - 2]]);
  timestampsIntervals_ms.emplace_back(absoluteUnixTimestamps.size() - 1 == blockIdxs[numberOfBlocks - 1]
                                          ? 0
                                          : absoluteUnixTimestamps[blockIdxs[numberOfBlocks - 1] + 1] -
                                                absoluteUnixTimestamps[blockIdxs[numberOfBlocks - 1]]);
  return DifferentialTimestampsContainer(firstUnixTimestamp_ms, blockIntervals_ms, timestampsIntervals_ms);
}

SensorJson Sensor::toJson(const DataForm dataForm) const {
  SensorJson sensorJson;
  ChannelsJson channelsJson(Json::arrayValue);

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
      return sensorJson;
    }
  }

  for (auto& channel : this->channels) {
    channelsJson.append(channel.toJson(dataForm, this->sensorType));
  }

  sensorJson["channels"] = channelsJson;
  sensorJson["sensor_type"] = Sensor::senorTypeToString(this->sensorType);
  return sensorJson;
}

ProtobufSensorType Sensor::senorTypeFromString(const SensorTypeString senorTypeString) {
  if (senorTypeString == "SENSOR_TYPE_PPG") {
    return ProtobufSensorType::SENSOR_TYPE_PPG;
  } else if (senorTypeString == "SENSOR_TYPE_ACC") {
    return ProtobufSensorType::SENSOR_TYPE_ACC;
  } else {
    return ProtobufSensorType::SENSOR_TYPE_NONE;
  }
}

SensorTypeString Sensor::senorTypeToString(const ProtobufSensorType protobufSensorType) {
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

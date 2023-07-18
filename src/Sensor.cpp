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
#include "PcoreJson.h"
#include "PcoreProtobuf.h"
Sensor::Sensor(Channels channels, DifferentialTimestampsContainer differentialTimestampsContainer, SensorTypeProtobuf sensorTypeProtobuf)
    : sensorType(sensorTypeProtobuf),
      channels(std::move(channels)),
      differentialTimestampsContainer(std::move(differentialTimestampsContainer)),
      dataForm(DataForm::DATA_FORM_DIFFERENTIAL) {}

Sensor::Sensor(Channels channels, AbsoluteTimestampsContainer absoluteTimestampsContainer, SensorTypeProtobuf sensorTypeProtobuf)
    : sensorType(sensorTypeProtobuf),
      channels(std::move(channels)),
      absoluteTimestampsContainer(std::move(absoluteTimestampsContainer)),
      dataForm(DataForm::DATA_FORM_ABSOLUTE) {
  this->dataForm = DataForm::DATA_FORM_ABSOLUTE;
}

Sensor::Sensor(const SensorJson& sensorJson, DataForm dataForm)
    : sensorType(PcoreProtobuf::Convert::senorTypeFromString(sensorJson[PcoreJson::Key::sensor_type].asString())),
      channels(PcoreJson::Convert::jsonToVector<Channel>(sensorJson, PcoreJson::Key::channels, this->sensorType, dataForm)),
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
      }()),
      dataForm(dataForm) {}

Sensor::Sensor(const SensorProtobuf& sensorProtobuf)
    : sensorType(sensorProtobuf.sensor_type()),
      channels(PcoreProtobuf::Convert::protobufToVector<Channel>(sensorProtobuf.channels())),
      differentialTimestampsContainer(DifferentialTimestampsContainer(sensorProtobuf.differential_timestamps_container())),
      absoluteTimestampsContainer(AbsoluteTimestampsContainer()),
      dataForm([&]() {
        if (sensorProtobuf.channels().empty() && sensorProtobuf.sensor_type() == SensorTypeProtobuf::SENSOR_TYPE_NONE) {
          return DataForm::DATA_FORM_NONE;
        }
        return DataForm::DATA_FORM_DIFFERENTIAL;
      }()) {}

Sensor::Sensor()
    : sensorType(SensorTypeProtobuf::SENSOR_TYPE_NONE),
      channels({}),
      differentialTimestampsContainer(DifferentialTimestampsContainer()),
      absoluteTimestampsContainer(AbsoluteTimestampsContainer()),
      dataForm(DataForm::DATA_FORM_NONE) {}

SensorTypeProtobuf Sensor::getSensorType() const {
  return this->sensorType;
}

Channels Sensor::getChannels() const {
  return this->channels;
}

DataForm Sensor::getDataFrom() const {
  return this->dataForm;
}

DifferentialTimestampsContainer Sensor::getDifferentialTimestampsContainer() const {
  return this->differentialTimestampsContainer;
}

AbsoluteTimestampsContainer Sensor::getAbsoluteTimestampsContainer() const {
  return this->absoluteTimestampsContainer;
}

bool Sensor::operator==(const IPCore<SensorProtobuf>& sensor) const {
  const auto* derived = dynamic_cast<const Sensor*>(&sensor);
  if (derived == nullptr) {
    return false;
  }
  const auto numberOfChannels = this->channels.size();
  if (numberOfChannels != derived->channels.size()) {
    return false;
  }
  for (size_t i = 0; i < numberOfChannels; i++) {
    if (this->channels[i] != derived->channels[i]) {
      return false;
    }
  }
  // clang-format off
  return this->sensorType == derived->sensorType
      && this->differentialTimestampsContainer == derived->differentialTimestampsContainer
      && this->absoluteTimestampsContainer == derived->absoluteTimestampsContainer
      && this->dataForm == derived->dataForm;  // TODO unittest for dataForm
  // clang-format on
}

bool Sensor::operator!=(const IPCore<SensorProtobuf>& sensor) const {
  return !(*this == sensor);
}

bool Sensor::isSet() const {
  for (const auto& channel : this->channels) {
    if (channel.isSet()) {
      return true;
    }
  }
  // clang-format off
  return this->sensorType != SensorTypeProtobuf::SENSOR_TYPE_NONE
      || this->absoluteTimestampsContainer.isSet()
      || this->differentialTimestampsContainer.isSet();
  // clang-format on
}

void Sensor::serialize(SensorProtobuf* sensorProtobuf) const {
  if (sensorProtobuf == nullptr) {
    throw std::invalid_argument("Error in serialize: sensorProtobuf is a null pointer");
  }
  if (!this->isSet()) {
    return;
  }
  if (this->dataForm != DataForm::DATA_FORM_DIFFERENTIAL) {
    throw std::runtime_error("Serialize is only possible for differential data form");
  }
  for (const auto& channel : this->channels) {
    auto* channelProtobuf = sensorProtobuf->add_channels();
    channel.serialize(channelProtobuf);
  }
  sensorProtobuf->set_sensor_type(this->sensorType);
  DifferentialTimestampContainerProtobuf differentialTimestampContainerProtobuf;
  this->differentialTimestampsContainer.serialize(&differentialTimestampContainerProtobuf);
  sensorProtobuf->mutable_differential_timestamps_container()->CopyFrom(differentialTimestampContainerProtobuf);
}

void Sensor::switchDataForm() {
  if (!this->isSet()) {
    return;
  }
  switch (this->dataForm) {
    case DataForm::DATA_FORM_DIFFERENTIAL: {
      this->absoluteTimestampsContainer = this->calculateAbsoluteTimestamps(this->differentialTimestampsContainer);
      this->differentialTimestampsContainer = DifferentialTimestampsContainer();
      for (auto& channel : this->channels) {
        channel.switchDataForm();
      }
      this->dataForm = DataForm::DATA_FORM_ABSOLUTE;
      break;
    }
    case DataForm::DATA_FORM_ABSOLUTE: {
      BlockIdxs blockIdxs = this->findBlockIdxs();
      this->differentialTimestampsContainer = this->calculateDifferentialTimestamps(this->absoluteTimestampsContainer, blockIdxs);
      this->absoluteTimestampsContainer = AbsoluteTimestampsContainer();
      for (auto& channel : this->channels) {
        channel.switchDataForm(blockIdxs);
      }
      this->dataForm = DataForm::DATA_FORM_DIFFERENTIAL;
      break;
    }
    default: {
      throw std::runtime_error("dataForm is NONE");  // should not happen, since it is intercepted by isSet guard above
    }
  }
}

UnixTimestamp Sensor::getFirstUnixTimestampInMs() const {
  switch (this->dataForm) {
    case DataForm::DATA_FORM_ABSOLUTE: {
      if (this->absoluteTimestampsContainer.isSet()) {
        return this->absoluteTimestampsContainer.getFirstUnixTimestampInMs();
      } else {
        throw std::runtime_error("absoluteTimestampsContainer is not set");
      }
    }
    case DataForm::DATA_FORM_DIFFERENTIAL: {
      if (this->differentialTimestampsContainer.isSet()) {
        return this->differentialTimestampsContainer.getFirstUnixTimestampInMs();
      } else {
        throw std::runtime_error("differentialTimestampsContainer is not set");
      }
    }
    case DataForm::DATA_FORM_NONE: {
      throw std::runtime_error("dataForm is none");
    }
  }
}

UnixTimestamp Sensor::getLastUnixTimestampInMs() const {
  switch (this->dataForm) {
    case DataForm::DATA_FORM_ABSOLUTE: {
      if (this->absoluteTimestampsContainer.isSet()) {
        return absoluteTimestampsContainer.getLastUnixTimestampInMs();
      } else {
        throw std::runtime_error("absoluteTimestampsContainer is not set");
      }
    }
    case DataForm::DATA_FORM_DIFFERENTIAL: {
      if (this->differentialTimestampsContainer.isSet()) {
        const auto differentialBlocksOfFirstChannel = this->channels.front().getDifferentialBlocks();
        const auto numberOfElementsInLastBlock = differentialBlocksOfFirstChannel.back().getDifferentialValues().size();
        const auto firstUnixTimestampInLastBlock = this->calculateFirstUnixTimestampInLastBlock();
        return this->differentialTimestampsContainer.getLastUnixTimestampInMs(firstUnixTimestampInLastBlock, numberOfElementsInLastBlock);
      } else {
        throw std::runtime_error("differentialTimestampsContainer is not set");
      }
    }
    case DataForm::DATA_FORM_NONE: {
      throw std::runtime_error("dataForm is none");
    }
  }
}

Duration Sensor::getDurationInMs() const {
  return this->getLastUnixTimestampInMs() - this->getFirstUnixTimestampInMs();
}

BlockIdxs Sensor::findBlockIdxs() const {
  BlockIdxs blockIdxs;
  if (!this->absoluteTimestampsContainer.isSet()) {
    return blockIdxs;
  }
  TimeDifference referenceTimeDifference = 0;
  bool isNewBlock = true;
  blockIdxs.push_back(0);
  const auto absoluteUnixTimestamps = this->absoluteTimestampsContainer.getUnixTimestampsInMs();
  const auto numberOfElements = absoluteUnixTimestamps.size();
  for (size_t i = 1; i < numberOfElements; i++) {
    const TimeDifference timeDifference = absoluteUnixTimestamps[i] - absoluteUnixTimestamps[i - 1];
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
  if (this->channels.empty()) {
    return AbsoluteTimestampsContainer();
  }
  const auto differentialBlocksOfFirstChannel = this->channels.front().getDifferentialBlocks();
  const auto timestampsDifferencesInMs = differentialTimestampsContainer.getTimestampsDifferencesInMs();
  const auto blocksDifferencesInMs = differentialTimestampsContainer.getBlocksDifferencesInMs();
  auto absoluteUnixTimestamp = differentialTimestampsContainer.getFirstUnixTimestampInMs();

  size_t numberOfElements = 0;
  for (const auto& differentialBlockOfFirstChannel : differentialBlocksOfFirstChannel) {
    numberOfElements += differentialBlockOfFirstChannel.getDifferentialValues().size();
  }
  UnixTimestamps unixTimestampsInMs;
  unixTimestampsInMs.reserve(numberOfElements);

  const auto numberOfBlocksDifferences = blocksDifferencesInMs.size();
  for (size_t i = 0; i < numberOfBlocksDifferences; i++) {
    absoluteUnixTimestamp += blocksDifferencesInMs[i];
    const auto numberOfDifferentialValues = differentialBlocksOfFirstChannel[i].getDifferentialValues().size();
    for (size_t j = 0; j < numberOfDifferentialValues; j++) {
      unixTimestampsInMs.emplace_back(absoluteUnixTimestamp + j * timestampsDifferencesInMs[i]);
    }
  }
  return AbsoluteTimestampsContainer(unixTimestampsInMs);
}

DifferentialTimestampsContainer Sensor::calculateDifferentialTimestamps(const AbsoluteTimestampsContainer& absoluteTimestampsContainer,
                                                                        const BlockIdxs& blockIdxs) const {
  const auto numberOfBlocks = blockIdxs.size();
  BlocksDifferences blocksDifferencesInMs;
  TimestampsDifferences timestampsDifferencesInMs;
  UnixTimestamp firstUnixTimestampInMs = 0;

  /*
   * blockIdxs.size = 0 -> no timestamps are included
                            return default Values for not set Block
   * blockIdxs.size = 1 -> case 1 : just one Block with one timestamps
                            return firstTimestamps, BlocksDifferencesInMs = {0}, timestampsDifferenceInMs{0}
   *                       case 2 : one Block with certain amount of timestamps with same time differences
                            return firstTimestamps, BlocksDifferenceInMs  = {0}, timestampsDifferencesInMs with one value (BestCase)
   * blockIdxs.size > 1 -> case 1: normal condition (Last block hold at least 2 Timestamps)
                            return calculate differentialTimestamps
   *                       case 2: the last Block hold just one Timestamp
                            return calculate differentialTimestamps  + last timestampsDifferenceInMs.pushback(0)
  */
  if (numberOfBlocks == 0) {
    return DifferentialTimestampsContainer(firstUnixTimestampInMs, blocksDifferencesInMs, timestampsDifferencesInMs);
  }

  const auto absoluteUnixTimestamps = absoluteTimestampsContainer.getUnixTimestampsInMs();
  firstUnixTimestampInMs = absoluteUnixTimestamps.front();
  if (numberOfBlocks == 1) {
    TimeDifference timestampsDifference = absoluteUnixTimestamps[1] - firstUnixTimestampInMs;
    timestampsDifferencesInMs.emplace_back(absoluteUnixTimestamps.size() == 1 ? 0 : timestampsDifference);
    blocksDifferencesInMs.push_back(0);
    return DifferentialTimestampsContainer(firstUnixTimestampInMs, blocksDifferencesInMs, timestampsDifferencesInMs);
  }

  blocksDifferencesInMs.push_back(0);
  timestampsDifferencesInMs.emplace_back(absoluteUnixTimestamps[1] - firstUnixTimestampInMs);
  const auto numberOfDifferences = blockIdxs.size() - 1;
  for (size_t i = 1; i < numberOfDifferences; i++) {
    const BlockIdx previousBlockIdx = blockIdxs[i - 1];
    const BlockIdx currentBlockIdx = blockIdxs[i];
    timestampsDifferencesInMs.emplace_back(absoluteUnixTimestamps[currentBlockIdx + 1] - absoluteUnixTimestamps[currentBlockIdx]);
    blocksDifferencesInMs.emplace_back(absoluteUnixTimestamps[currentBlockIdx] - absoluteUnixTimestamps[previousBlockIdx]);
  }
  const auto lastBlockIdx = blockIdxs.back();
  blocksDifferencesInMs.emplace_back(absoluteUnixTimestamps[lastBlockIdx] - absoluteUnixTimestamps[blockIdxs[numberOfBlocks - 2]]);
  timestampsDifferencesInMs.emplace_back(
      absoluteUnixTimestamps.size() - 1 == lastBlockIdx ? 0 : absoluteUnixTimestamps[lastBlockIdx + 1] - absoluteUnixTimestamps[lastBlockIdx]);
  return DifferentialTimestampsContainer(firstUnixTimestampInMs, blocksDifferencesInMs, timestampsDifferencesInMs);
}

SensorJson Sensor::toJson() const {
  SensorJson sensorJson;
  if (!this->isSet()) {
    return sensorJson;
  }
  switch (this->dataForm) {
    case DataForm::DATA_FORM_ABSOLUTE: {
      sensorJson[PcoreJson::Key::absolute_timestamps_container] = this->absoluteTimestampsContainer.toJson();
      break;
    }
    case DataForm::DATA_FORM_DIFFERENTIAL: {
      sensorJson[PcoreJson::Key::differential_timestamps_container] = this->differentialTimestampsContainer.toJson();
      break;
    }
    default: {
      return sensorJson;
    }
  }
  sensorJson[PcoreJson::Key::channels] = PcoreJson::Convert::vectorToJson(this->channels);
  sensorJson[PcoreJson::Key::sensor_type] = PcoreProtobuf::Convert::senorTypeToString(this->sensorType);
  return sensorJson;
}

UnixTimestamp Sensor::calculateFirstUnixTimestampInLastBlock() const {
  const auto blocksDifferencesInMs = this->differentialTimestampsContainer.getBlocksDifferencesInMs();
  auto firstUnixTimestampInLastBlockInMs = this->getFirstUnixTimestampInMs();
  for (const auto& blocksDifferenceInMs : blocksDifferencesInMs) {
    firstUnixTimestampInLastBlockInMs += blocksDifferenceInMs;
  }
  return firstUnixTimestampInLastBlockInMs;
}
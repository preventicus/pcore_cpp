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
#include "Exceptions.h"
#include "PcoreJson.h"
#include "PcoreProtobuf.h"

////////////////////////////////////////////////////////////////
//                       Constructors                         //
////////////////////////////////////////////////////////////////
Sensor::Sensor(Channels channels, DifferentialTimestampsContainer differentialTimestampsContainer, SensorTypeProtobuf sensorTypeProtobuf) noexcept
    : sensorType(sensorTypeProtobuf), channels(std::move(channels)), timestamps(std::move(differentialTimestampsContainer)) {}

Sensor::Sensor(Channels channels, AbsoluteTimestampsContainer absoluteTimestampsContainer, SensorTypeProtobuf sensorTypeProtobuf) noexcept
    : sensorType(sensorTypeProtobuf), channels(std::move(channels)), timestamps(std::move(absoluteTimestampsContainer)) {}

Sensor::Sensor(const SensorJson& sensorJson, DataForm dataForm)
    : sensorType(PcoreProtobuf::Convert::senorTypeFromString(sensorJson[PcoreJson::Key::sensor_type].asString())),
      channels(PcoreJson::Convert::jsonToVector<Channel>(sensorJson, PcoreJson::Key::channels)),
      timestamps([&]() -> Timestamps {
        switch (dataForm) {
          case DataForm::DATA_FORM_ABSOLUTE: {
            return AbsoluteTimestampsContainer(sensorJson[PcoreJson::Key::absolute_timestamps_container]);
          }
          case DataForm::DATA_FORM_DIFFERENTIAL: {
            return DifferentialTimestampsContainer(sensorJson[PcoreJson::Key::differential_timestamps_container]);
          }
          default: {
            return std::nullopt;
          }
        }
      }()) {}

Sensor::Sensor(const SensorProtobuf& sensorProtobuf) noexcept
    : sensorType(sensorProtobuf.sensor_type()),
      channels(PcoreProtobuf::Convert::protobufToVector<Channel>(sensorProtobuf.channels())),
      timestamps([&]() -> Timestamps {
        if (sensorProtobuf.has_differential_timestamps_container()) {
          return DifferentialTimestampsContainer(sensorProtobuf.differential_timestamps_container());
        }
        return std::nullopt;
      }()) {}

Sensor::Sensor() noexcept : sensorType(SensorTypeProtobuf::SENSOR_TYPE_NONE), channels({}), timestamps(std::nullopt) {}

////////////////////////////////////////////////////////////////
//                          Getter                            //
////////////////////////////////////////////////////////////////

SensorTypeProtobuf Sensor::getSensorType() const noexcept {
  return this->sensorType;
}

Channels Sensor::getChannels() const noexcept {
  return this->channels;
}

template <typename T>
std::optional<T> Sensor::getTimestamps() const noexcept {
  if (!this->timestamps.has_value()) {
    return std::nullopt;
  }
  if (!std::holds_alternative<T>(*this->timestamps)) {
    return std::nullopt;
  }
  return std::get<T>(*this->timestamps);
}

template <typename T>
bool Sensor::hasTimestamps() const noexcept {
  if (!this->timestamps.has_value()) {
    return false;
  }
  if (!std::holds_alternative<T>(*this->timestamps)) {
    return false;
  }
  return std::get<T>(*this->timestamps).isSet();
}

DataForm Sensor::getDataFrom() const noexcept {
  if (!this->timestamps.has_value()) {
    return DataForm::DATA_FORM_NONE;
  } else if (std::holds_alternative<DifferentialTimestampsContainer>(*this->timestamps)) {
    return DataForm::DATA_FORM_DIFFERENTIAL;
  } else {
    return DataForm::DATA_FORM_ABSOLUTE;
  }
}

UnixTimestamp Sensor::getFirstUnixTimestampInMs() const noexcept {
  switch (this->getDataFrom()) {
    case DataForm::DATA_FORM_ABSOLUTE: {
      return this->getTimestamps<AbsoluteTimestampsContainer>()->getFirstUnixTimestampInMs();
    }
    case DataForm::DATA_FORM_DIFFERENTIAL: {
      return this->getTimestamps<DifferentialTimestampsContainer>()->getFirstUnixTimestampInMs();
    }
    case DataForm::DATA_FORM_NONE: {
      return 0;
    }
  }
}

UnixTimestamp Sensor::getLastUnixTimestampInMs() const noexcept {
  switch (this->getDataFrom()) {
    case DataForm::DATA_FORM_ABSOLUTE: {
      return this->getTimestamps<AbsoluteTimestampsContainer>()->getLastUnixTimestampInMs();
    }
    case DataForm::DATA_FORM_DIFFERENTIAL: {
      if (this->channels.empty()) {
        return 0;
      }
      const auto differentialBlocksOfFirstChannel = this->channels.front().getValues<DifferentialBlocks>();
      if (!differentialBlocksOfFirstChannel.has_value()) {
        return 0;
      }
      if (differentialBlocksOfFirstChannel->empty()) {
        return 0;
      }
      const auto numberOfElementsInLastBlock = differentialBlocksOfFirstChannel->back().getDifferentialValues().size();
      const auto firstUnixTimestampInLastBlock = this->calculateFirstUnixTimestampInLastBlock();
      return this->getTimestamps<DifferentialTimestampsContainer>()->getLastUnixTimestampInMs(firstUnixTimestampInLastBlock,
                                                                                              numberOfElementsInLastBlock);
    }
    case DataForm::DATA_FORM_NONE: {
      return 0;
    }
  }
}

Duration Sensor::getDurationInMs() const noexcept {
  return this->getLastUnixTimestampInMs() - this->getFirstUnixTimestampInMs();
}

////////////////////////////////////////////////////////////////
//                      IPCore Methods                        //
////////////////////////////////////////////////////////////////

bool Sensor::isSet() const noexcept {
  for (const auto& channel : this->channels) {
    if (channel.isSet()) {
      return true;
    }
  }
  // clang-format off
  return this->sensorType != SensorTypeProtobuf::SENSOR_TYPE_NONE
      || this->hasTimestamps<AbsoluteTimestampsContainer>()
      || this->hasTimestamps<DifferentialTimestampsContainer>();
  // clang-format on
}

SensorJson Sensor::toJson() const noexcept {
  SensorJson sensorJson;
  if (!this->isSet()) {
    return sensorJson;
  }
  switch (this->getDataFrom()) {
    case DataForm::DATA_FORM_ABSOLUTE: {
      sensorJson[PcoreJson::Key::absolute_timestamps_container] = this->getTimestamps<AbsoluteTimestampsContainer>()->toJson();
      break;
    }
    case DataForm::DATA_FORM_DIFFERENTIAL: {
      sensorJson[PcoreJson::Key::differential_timestamps_container] = this->getTimestamps<DifferentialTimestampsContainer>()->toJson();
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

void Sensor::serialize(SensorProtobuf* sensorProtobuf) const {
  if (sensorProtobuf == nullptr) {
    throw NullPointerException("Sensor::serialize", "sensorProtobuf");
  }
  if (!this->isSet()) {
    return;
  }
  if (this->getDataFrom() != DataForm::DATA_FORM_DIFFERENTIAL) {
    throw WrongDataFormException("Sensor::serialize", "only for differential data form");
  }
  for (const auto& channel : this->channels) {
    auto* channelProtobuf = sensorProtobuf->add_channels();
    channel.serialize(channelProtobuf);
  }
  sensorProtobuf->set_sensor_type(this->sensorType);
  if (this->hasTimestamps<DifferentialTimestampsContainer>()) {
    DifferentialTimestampContainerProtobuf differentialTimestampContainerProtobuf;
    this->getTimestamps<DifferentialTimestampsContainer>()->serialize(&differentialTimestampContainerProtobuf);
    sensorProtobuf->mutable_differential_timestamps_container()->CopyFrom(differentialTimestampContainerProtobuf);
  }
}

void Sensor::switchDataForm() noexcept {
  if (!this->isSet()) {
    return;
  }
  switch (this->getDataFrom()) {
    case DataForm::DATA_FORM_DIFFERENTIAL: {
      this->timestamps = this->calculateAbsoluteTimestamps(*this->getTimestamps<DifferentialTimestampsContainer>());
      for (auto& channel : this->channels) {
        channel.switchDataForm();
      }
      return;
    }
    case DataForm::DATA_FORM_ABSOLUTE: {
      BlockIdxs blockIdxs = this->findBlockIdxs();
      this->timestamps = this->calculateDifferentialTimestamps(*this->getTimestamps<AbsoluteTimestampsContainer>(), blockIdxs);
      for (auto& channel : this->channels) {
        channel.switchDataForm(blockIdxs);
      }
      return;
    }
    default: {
      return;
    }
  }
}

bool Sensor::operator==(const IPCore<SensorProtobuf>& sensor) const noexcept {
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
  if (this->timestamps.has_value() != timestamps.has_value()) {
    return false;
  }
  bool isEqualTimestamps = !this->timestamps.has_value() && !derived->timestamps.has_value();
  if (this->timestamps.has_value() && derived->timestamps.has_value()) {
    isEqualTimestamps = *this->timestamps == *derived->timestamps;
  }
  return this->sensorType == derived->sensorType && isEqualTimestamps;
}

bool Sensor::operator!=(const IPCore<SensorProtobuf>& sensor) const noexcept {
  return !(*this == sensor);
}

////////////////////////////////////////////////////////////////
//                     Calculate Methode                      //
////////////////////////////////////////////////////////////////
AbsoluteTimestampsContainer Sensor::calculateAbsoluteTimestamps(
    const DifferentialTimestampsContainer& differentialTimestampsContainer) const noexcept {
  if (this->channels.empty()) {
    return AbsoluteTimestampsContainer();
  }
  const auto differentialBlocksOfFirstChannel = this->channels.front().getValues<DifferentialBlocks>();
  if (!differentialBlocksOfFirstChannel.has_value()) {
    return AbsoluteTimestampsContainer();
  }
  const auto timestampsDifferencesInMs = differentialTimestampsContainer.getTimestampsDifferencesInMs();
  const auto blocksDifferencesInMs = differentialTimestampsContainer.getBlocksDifferencesInMs();
  auto absoluteUnixTimestamp = differentialTimestampsContainer.getFirstUnixTimestampInMs();

  size_t numberOfElements = 0;
  for (const auto& differentialBlockOfFirstChannel : *differentialBlocksOfFirstChannel) {
    numberOfElements += differentialBlockOfFirstChannel.getDifferentialValues().size();
  }
  UnixTimestamps unixTimestampsInMs;
  unixTimestampsInMs.reserve(numberOfElements);

  const auto numberOfBlocksDifferences = blocksDifferencesInMs.size();
  for (size_t i = 0; i < numberOfBlocksDifferences; i++) {
    absoluteUnixTimestamp += blocksDifferencesInMs[i];
    const auto numberOfDifferentialValues = (*differentialBlocksOfFirstChannel)[i].getDifferentialValues().size();
    for (size_t j = 0; j < numberOfDifferentialValues; j++) {
      unixTimestampsInMs.emplace_back(absoluteUnixTimestamp + j * timestampsDifferencesInMs[i]);
    }
  }
  return AbsoluteTimestampsContainer(unixTimestampsInMs);
}

DifferentialTimestampsContainer Sensor::calculateDifferentialTimestamps(const AbsoluteTimestampsContainer& absoluteTimestampsContainer,
                                                                        const BlockIdxs& blockIdxs) const noexcept {
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

BlockIdxs Sensor::findBlockIdxs() const noexcept {
  BlockIdxs blockIdxs;
  if (!this->hasTimestamps<AbsoluteTimestampsContainer>()) {
    return blockIdxs;
  }
  TimeDifference referenceTimeDifferenceInMs = 0;
  bool isNewBlock = true;
  blockIdxs.push_back(0);
  const auto absoluteUnixTimestampsInMs = this->getTimestamps<AbsoluteTimestampsContainer>()->getUnixTimestampsInMs();
  const auto numberOfElements = absoluteUnixTimestampsInMs.size();
  for (size_t i = 1; i < numberOfElements; i++) {
    const TimeDifference timeDifferenceInMs = absoluteUnixTimestampsInMs[i] - absoluteUnixTimestampsInMs[i - 1];
    if (isNewBlock) {
      referenceTimeDifferenceInMs = timeDifferenceInMs;
      isNewBlock = false;
    }
    if (timeDifferenceInMs != referenceTimeDifferenceInMs) {
      blockIdxs.push_back(i);
      isNewBlock = true;
    }
  }
  return blockIdxs;
}

UnixTimestamp Sensor::calculateFirstUnixTimestampInLastBlock() const noexcept {
  const auto blocksDifferencesInMs = this->getTimestamps<DifferentialTimestampsContainer>()->getBlocksDifferencesInMs();
  auto firstUnixTimestampInLastBlockInMs = this->getFirstUnixTimestampInMs();
  for (const auto& blocksDifferenceInMs : blocksDifferencesInMs) {
    firstUnixTimestampInLastBlockInMs += blocksDifferenceInMs;
  }
  return firstUnixTimestampInLastBlockInMs;
}
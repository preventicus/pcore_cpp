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

#include "Channel.h"
#include <utility>
#include "Exceptions.h"
#include "PcoreJson.h"
#include "PcoreProtobuf.h"

////////////////////////////////////////////////////////////////
//                       Constructors                         //
////////////////////////////////////////////////////////////////
Channel::Channel(AccMetaData accMetaData, AbsoluteBlock absoluteBlock) noexcept
    : metaData(std::move(accMetaData)), values(std::move(absoluteBlock)) {}

Channel::Channel(PpgMetaData ppgMetaData, AbsoluteBlock absoluteBlock) noexcept
    : metaData(std::move(ppgMetaData)), values(std::move(absoluteBlock)) {}

Channel::Channel(AccMetaData accMetaData, DifferentialBlocks differentialBlocks) noexcept
    : metaData(std::move(accMetaData)), values(std::move(differentialBlocks)) {}

Channel::Channel(PpgMetaData ppgMetaData, DifferentialBlocks differentialBlocks) noexcept
    : metaData(std::move(ppgMetaData)), values(std::move(differentialBlocks)) {}

Channel::Channel(const ChannelJson& channelJson) noexcept
    : metaData([&]() -> MetaData {
        if (channelJson.isMember(PcoreJson::Key::ppg_metadata)) {
          return PpgMetaData(channelJson[PcoreJson::Key::ppg_metadata]);
        } else if (channelJson.isMember(PcoreJson::Key::acc_metadata)) {
          return AccMetaData(channelJson[PcoreJson::Key::acc_metadata]);
        } else {
          return std::nullopt;
        }
      }()),
      values([&]() -> Values {
        if (channelJson.isMember(PcoreJson::Key::differential_blocks)) {
          return PcoreJson::Convert::jsonToVector<DifferentialBlock>(channelJson, PcoreJson::Key::differential_blocks);
        } else if (channelJson.isMember(PcoreJson::Key::absolute_block)) {
          return AbsoluteBlock(channelJson[PcoreJson::Key::absolute_block]);
        } else {
          return std::nullopt;
        }
      }()) {}

Channel::Channel(const ChannelProtobuf& channelProtobuf) noexcept
    : metaData([&]() -> MetaData {
        if (channelProtobuf.has_acc_metadata()) {
          return AccMetaData(channelProtobuf.acc_metadata());
        } else if (channelProtobuf.has_ppg_metadata()) {
          return PpgMetaData(channelProtobuf.ppg_metadata());
        } else {
          return std::nullopt;
        }
      }()),
      values([&]() -> Values {
        auto differentialBlocksProtobuf = channelProtobuf.differential_blocks();
        if (differentialBlocksProtobuf.empty()) {
          return std::nullopt;
        }
        return PcoreProtobuf::Convert::protobufToVector<DifferentialBlock>(differentialBlocksProtobuf);
      }()) {}

Channel::Channel() noexcept : metaData(std::nullopt), values(std::nullopt) {}

////////////////////////////////////////////////////////////////
//                          Getter                            //
////////////////////////////////////////////////////////////////

template <typename V>
std::optional<V> Channel::getValues() const noexcept {
  if (!this->values.has_value()) {
    return std::nullopt;
  }
  if (!std::holds_alternative<V>(*this->values)) {
    return std::nullopt;
  }
  return std::get<V>(*this->values);
}

template <typename M>
std::optional<M> Channel::getMetaData() const noexcept {
  if (!this->metaData.has_value()) {
    return std::nullopt;
  }
  if (!std::holds_alternative<M>(*this->metaData)) {
    return std::nullopt;
  }
  return std::get<M>(*this->metaData);
}

template <typename V>
bool Channel::hasValues() const noexcept {
  if (!this->values.has_value()) {
    return false;
  }
  if (!std::holds_alternative<V>(*this->values)) {
    return false;
  }
  if constexpr (std::is_same_v<V, DifferentialBlocks>) {
    return !std::get<V>(*this->values).empty();
  } else {
    return std::get<V>(*this->values).isSet();
  }
}

template <typename M>
bool Channel::hasMetaData() const noexcept {
  if (!this->metaData.has_value()) {
    return false;
  }
  if (!std::holds_alternative<M>(*this->metaData)) {
    return false;
  }
  return std::get<M>(*this->metaData).isSet();
}

SensorTypeProtobuf Channel::getSensorType() const noexcept {
  if (!this->metaData.has_value()) {
    return SensorTypeProtobuf::SENSOR_TYPE_NONE;
  } else if (std::holds_alternative<AccMetaData>(*this->metaData)) {
    return SensorTypeProtobuf::SENSOR_TYPE_ACC;
  } else {
    return SensorTypeProtobuf::SENSOR_TYPE_PPG;
  }
}

DataForm Channel::getDataForm() const noexcept {
  if (!this->values.has_value()) {
    return DataForm::DATA_FORM_NONE;
  } else if (std::holds_alternative<AbsoluteBlock>(*this->values)) {
    return DataForm::DATA_FORM_ABSOLUTE;
  } else {
    return DataForm::DATA_FORM_DIFFERENTIAL;
  }
}

////////////////////////////////////////////////////////////////
//                      IPCore Methods                        //
////////////////////////////////////////////////////////////////
bool Channel::isSet() const noexcept {
  if (this->hasValues<DifferentialBlocks>()) {
    auto differentialBlocks = *this->getValues<DifferentialBlocks>();
    for (const auto& differentialBlock : differentialBlocks) {
      if (differentialBlock.isSet()) {
        return true;
      }
    }
  }
  // clang-format off
  return this->hasMetaData<PpgMetaData>()
      || this->hasMetaData<AccMetaData>()
      || this->hasValues<AbsoluteBlock>();
  // clang-format on
}

ChannelJson Channel::toJson() const noexcept {
  ChannelJson channelJson;
  if (!this->isSet()) {
    return channelJson;
  }
  switch (this->getDataForm()) {
    case DataForm::DATA_FORM_ABSOLUTE: {
      channelJson[PcoreJson::Key::absolute_block] = this->getValues<AbsoluteBlock>()->toJson();
      switch (this->getSensorType()) {
        case SensorTypeProtobuf::SENSOR_TYPE_PPG: {
          channelJson[PcoreJson::Key::ppg_metadata] = this->getMetaData<PpgMetaData>()->toJson();
          break;
        }
        case SensorTypeProtobuf::SENSOR_TYPE_ACC: {
          channelJson[PcoreJson::Key::acc_metadata] = this->getMetaData<AccMetaData>()->toJson();
          break;
        }
        default: {
          return channelJson;
        }
      }
      break;
    }
    case DataForm::DATA_FORM_DIFFERENTIAL: {
      channelJson[PcoreJson::Key::differential_blocks] = PcoreJson::Convert::vectorToJson(*this->getValues<DifferentialBlocks>());
      switch (this->getSensorType()) {
        case SensorTypeProtobuf::SENSOR_TYPE_PPG: {
          channelJson[PcoreJson::Key::ppg_metadata] = this->getMetaData<PpgMetaData>()->toJson();
          break;
        }
        case SensorTypeProtobuf::SENSOR_TYPE_ACC: {
          channelJson[PcoreJson::Key::acc_metadata] = this->getMetaData<AccMetaData>()->toJson();
          break;
        }
        default: {
          return channelJson;
        }
      }
      break;
    }
    default: {
      return channelJson;
    }
  }
  return channelJson;
}

void Channel::serialize(ChannelProtobuf* channelProtobuf) const {
  if (channelProtobuf == nullptr) {
    throw NullPointerException("Channel::serialize", "channelProtobuf");
  }
  if (!this->isSet()) {
    return;
  }
  if (this->getDataForm() != DataForm::DATA_FORM_DIFFERENTIAL) {
    throw WrongDataFormException("Channel::serialize", "only for differential data form");
  }
  this->serializeValues(channelProtobuf);
  this->serializeMetaData(channelProtobuf);
}

void Channel::switchDataForm(const BlockIdxs& blockIdxs) noexcept {
  if (!this->isSet()) {
    return;
  }
  this->values = this->calculateDifferentialBlocks(*this->getValues<AbsoluteBlock>(), blockIdxs);
}

void Channel::switchDataForm() noexcept {
  if (!this->isSet()) {
    return;
  }
  this->values = this->calculateAbsoluteBlock(*this->getValues<DifferentialBlocks>());
}

bool Channel::operator==(const IPCore<ChannelProtobuf>& channel) const noexcept {
  const auto* derived = dynamic_cast<const Channel*>(&channel);
  if (derived == nullptr) {
    return false;
  }
  return this->metaData == derived->metaData && this->values == derived->values;
}

bool Channel::operator!=(const IPCore<ChannelProtobuf>& channel) const noexcept {
  return !(*this == channel);
}

////////////////////////////////////////////////////////////////
//                     Calculate Methode                      //
////////////////////////////////////////////////////////////////

DifferentialBlocks Channel::calculateDifferentialBlocks(const AbsoluteBlock& absoluteBlock, const BlockIdxs& blockIdxs) const noexcept {
  DifferentialBlocks differentialBlocks;
  const auto numberOfBlocks = blockIdxs.size();
  /*
  * blockIdxs.size = 0 -> no values are included
                            return default value for not set Block
  * blockIdxs.size = 1 -> case 1 : just one Block with one value
                            return DifferentialBlock with one absoluteValue
  *                       case 2 : one Block with certain amount of value
                            return normal calculated differentialBlock
  * blockIdxs.size > 1 -> case 1: normal condition (Last block hold at least 2 values)
                            return calculate differentialBlock
  *                       case 2: the last Block hold just one value
                            return normal calculate differentialBlock  + last included differentialValue is a absoluteValue
  */
  if (numberOfBlocks == 0) {
    return differentialBlocks;
  }
  const auto absoluteValues = absoluteBlock.getAbsoluteValues();
  const auto numberOfAbsoluteValues = absoluteValues.size();
  BlockIdx fromBlockIdx = 0;
  BlockIdx toBlockIdx = numberOfAbsoluteValues > 1 ? numberOfAbsoluteValues - 1 : 0;
  if (numberOfBlocks == 1) {
    differentialBlocks.emplace_back(
        this->createDifferentialBlock(fromBlockIdx, toBlockIdx,
                                      absoluteValues));  // toIdx = 0  would create a DifferentialBlock with a absoluteValue.
    return differentialBlocks;
  }

  for (size_t i = 0; i < numberOfBlocks - 1; i++) {  // calculate DifferentialBlocks for all blockIdxs except last Idx
    fromBlockIdx = blockIdxs[i];
    toBlockIdx = blockIdxs[i + 1] - 1;
    differentialBlocks.emplace_back(this->createDifferentialBlock(fromBlockIdx, toBlockIdx, absoluteValues));
  }
  const auto lastBlockIdx = blockIdxs.back();
  fromBlockIdx = numberOfAbsoluteValues - 1 == lastBlockIdx ? numberOfAbsoluteValues - 1 : lastBlockIdx;
  toBlockIdx = numberOfAbsoluteValues - 1;
  differentialBlocks.emplace_back(this->createDifferentialBlock(fromBlockIdx, toBlockIdx, absoluteValues));
  return differentialBlocks;
}

DifferentialBlock Channel::createDifferentialBlock(const BlockIdx fromBlockIdx,
                                                   const BlockIdx toBlockIdx,
                                                   const AbsoluteValues& absoluteValues) const noexcept {
  DifferentialValues differentialValues;
  differentialValues.push_back(absoluteValues[fromBlockIdx]);
  for (size_t i = fromBlockIdx + 1; i <= toBlockIdx; i++) {
    differentialValues.emplace_back(absoluteValues[i] - absoluteValues[i - 1]);
  }
  return DifferentialBlock(differentialValues);
}

AbsoluteBlock Channel::calculateAbsoluteBlock(const DifferentialBlocks& differentialBlocks) noexcept {
  AbsoluteValues absoluteValues;
  size_t numberOfElements = 0;
  for (const auto& differentialBlock : differentialBlocks) {
    numberOfElements += differentialBlock.getDifferentialValues().size();
  }
  absoluteValues.reserve(numberOfElements);
  for (const auto& differentialBlock : differentialBlocks) {
    AbsoluteValue absoluteValue = 0;
    for (const auto& differentialValue : differentialBlock.getDifferentialValues()) {
      absoluteValue += differentialValue;
      absoluteValues.push_back(absoluteValue);
    }
  }
  return AbsoluteBlock(absoluteValues);
}

void Channel::serializeValues(ChannelProtobuf* channelProtobuf) const noexcept {
  auto differentialBlocks = this->getValues<DifferentialBlocks>();
  if (!differentialBlocks.has_value()) {
    return;
  }
  for (const auto& differentialBlock : *differentialBlocks) {
    auto* differentialBlockProtobuf = channelProtobuf->add_differential_blocks();
    differentialBlock.serialize(differentialBlockProtobuf);
  }
}

void Channel::serializeMetaData(ChannelProtobuf* channelProtobuf) const noexcept {
  switch (this->getSensorType()) {
    case SensorTypeProtobuf::SENSOR_TYPE_PPG: {
      PpgMetaDataProtobuf ppgMetaDataProtobuf;
      this->getMetaData<PpgMetaData>()->serialize(&ppgMetaDataProtobuf);
      channelProtobuf->mutable_ppg_metadata()->CopyFrom(ppgMetaDataProtobuf);
      break;
    }
    case SensorTypeProtobuf::SENSOR_TYPE_ACC: {
      AccMetaDataProtobuf accMetaDataProtobuf;
      this->getMetaData<AccMetaData>()->serialize(&accMetaDataProtobuf);
      channelProtobuf->mutable_acc_metadata()->CopyFrom(accMetaDataProtobuf);
      break;
    }
    default: {
      return;
    }
  }
}

bool Channel::operator==(const Values& values) const noexcept {
  if (this->values.has_value() != values.has_value()) {
    return false;
  }
  if (!this->values.has_value() && !values.has_value()) {
    return true;
  }

  if (std::holds_alternative<DifferentialBlocks>(*this->values) && std::holds_alternative<DifferentialBlocks>(*values)) {
    auto thisDifferentialBlocks = *this->getValues<DifferentialBlocks>();
    auto derivedDifferentialBlocks = std::get<DifferentialBlocks>(*values);

    const auto numberOfElements = thisDifferentialBlocks.size();
    if (numberOfElements != derivedDifferentialBlocks.size()) {
      return false;
    }
    for (size_t i = 0; i < numberOfElements; i++) {
      if (thisDifferentialBlocks[i] != derivedDifferentialBlocks[i]) {
        return false;
      }
    }
    return true;

  } else if (std::holds_alternative<AbsoluteBlock>(*this->values) && std::holds_alternative<AbsoluteBlock>(*values)) {
    auto thisAbsoluteBlock = *this->getValues<AbsoluteBlock>();
    auto derivedAbsoluteBlock = std::get<AbsoluteBlock>(*values);
    return thisAbsoluteBlock == derivedAbsoluteBlock;
  } else {
    return false;
  }
}
bool Channel::operator==(const MetaData& metaData) const noexcept {
  if (this->metaData.has_value() != metaData.has_value()) {
    return false;
  }
  bool isEqualMetaData = !this->metaData.has_value() && !metaData.has_value();
  if (this->metaData.has_value() && metaData.has_value()) {
    isEqualMetaData = *this->metaData == *metaData;
  }
  return isEqualMetaData;
}
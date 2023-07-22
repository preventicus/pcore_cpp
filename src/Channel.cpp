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
    : metaData(std::move(accMetaData)),
      differentialBlocks(DifferentialBlocks()),
      absoluteBlock(std::move(absoluteBlock)),
      dataForm(DataForm::DATA_FORM_ABSOLUTE) {}

Channel::Channel(PpgMetaData ppgMetaData, AbsoluteBlock absoluteBlock) noexcept
    : metaData(std::move(ppgMetaData)),
      differentialBlocks(DifferentialBlocks()),
      absoluteBlock(std::move(absoluteBlock)),
      dataForm(DataForm::DATA_FORM_ABSOLUTE) {}

Channel::Channel(AccMetaData accMetaData, DifferentialBlocks differentialBlocks) noexcept
    : metaData(std::move(accMetaData)),
      differentialBlocks(std::move(differentialBlocks)),
      absoluteBlock(AbsoluteBlock()),
      dataForm(DataForm::DATA_FORM_DIFFERENTIAL) {}

Channel::Channel(PpgMetaData ppgMetaData, DifferentialBlocks differentialBlocks) noexcept
    : metaData(std::move(ppgMetaData)),
      differentialBlocks(std::move(differentialBlocks)),
      absoluteBlock(AbsoluteBlock()),
      dataForm(DataForm::DATA_FORM_DIFFERENTIAL) {}

Channel::Channel(const ChannelJson& channelJson, SensorTypeProtobuf sensorTypeProtobuf, DataForm dataForm)
    : metaData([&]() -> MetaData {
        if (channelJson.isMember(PcoreJson::Key::ppg_metadata)) {
          return PpgMetaData(channelJson[PcoreJson::Key::ppg_metadata]);
        } else if (channelJson.isMember(PcoreJson::Key::acc_metadata)) {
          return AccMetaData(channelJson[PcoreJson::Key::acc_metadata]);
        } else {
          return std::nullopt;
        }
      }()),
      differentialBlocks([&]() {
        switch (dataForm) {
          case DATA_FORM_ABSOLUTE: {
            return DifferentialBlocks();
          }
          case DATA_FORM_DIFFERENTIAL: {
            return PcoreJson::Convert::jsonToVector<DifferentialBlock>(channelJson, PcoreJson::Key::differential_blocks);
          }
          default: {
            throw DataFormIsNoneException("Channel");
          }
        }
      }()),
      absoluteBlock([&]() {
        switch (dataForm) {
          case DATA_FORM_ABSOLUTE: {
            return AbsoluteBlock(channelJson[PcoreJson::Key::absolute_block]);
          }
          case DATA_FORM_DIFFERENTIAL: {
            return AbsoluteBlock();
          }
          default: {
            throw DataFormIsNoneException("Channel");
          }
        }
      }()),
      dataForm(dataForm) {
  if (sensorTypeProtobuf == SensorTypeProtobuf::SENSOR_TYPE_NONE) {
    throw SensorTypeIsNoneException("Channel");
  }
}

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
      differentialBlocks(PcoreProtobuf::Convert::protobufToVector<DifferentialBlock>(channelProtobuf.differential_blocks())),
      absoluteBlock(AbsoluteBlock()),
      dataForm([&]() {
        if (channelProtobuf.has_ppg_metadata() || channelProtobuf.has_acc_metadata() || !channelProtobuf.differential_blocks().empty()) {
          return DataForm::DATA_FORM_DIFFERENTIAL;
        } else {
          return DataForm::DATA_FORM_NONE;
        }
      }()) {}

Channel::Channel() noexcept
    : metaData(std::nullopt), differentialBlocks(DifferentialBlocks()), absoluteBlock(AbsoluteBlock()), dataForm(DataForm::DATA_FORM_NONE) {}

////////////////////////////////////////////////////////////////
//                          Getter                            //
////////////////////////////////////////////////////////////////
DifferentialBlocks Channel::getDifferentialBlocks() const noexcept {
  return this->differentialBlocks;
}

AbsoluteBlock Channel::getAbsoluteBlock() const noexcept {
  return this->absoluteBlock;
}

std::optional<AccMetaData> Channel::getAccMetaData() const noexcept {
  if (!this->metaData.has_value()) {
    return std::nullopt;
  }
  if (!std::holds_alternative<AccMetaData>(*this->metaData)) {
    return std::nullopt;
  }
  return std::get<AccMetaData>(*this->metaData);
}

std::optional<PpgMetaData> Channel::getPpgMetaData() const noexcept {
  if (!this->metaData.has_value()) {
    return std::nullopt;
  }
  if (!std::holds_alternative<PpgMetaData>(*this->metaData)) {
    return std::nullopt;
  }
  return std::get<PpgMetaData>(*this->metaData);
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
  return this->dataForm;
}

bool Channel::hasAccMetaData() const noexcept {
  if (!this->metaData.has_value()) {
    return false;
  }
  if (!std::holds_alternative<AccMetaData>(*this->metaData)) {
    return false;
  }
  return std::get<AccMetaData>(*this->metaData).isSet();
  ;
}

bool Channel::hasPpgMetaData() const noexcept {
  if (!this->metaData.has_value()) {
    return false;
  }
  if (!std::holds_alternative<PpgMetaData>(*this->metaData)) {
    return false;
  }
  return std::get<PpgMetaData>(*this->metaData).isSet();
}

bool Channel::hasDifferentialBlocks() const noexcept {
  return !this->differentialBlocks.empty();
}

bool Channel::hasAbsoluteBlock() const noexcept {
  return this->absoluteBlock.isSet();
}

////////////////////////////////////////////////////////////////
//                      IPCore Methods                        //
////////////////////////////////////////////////////////////////
bool Channel::isSet() const noexcept {
  for (const auto& differentialBlock : this->differentialBlocks) {
    if (differentialBlock.isSet()) {
      return true;
    }
  }
  // clang-format off
  return this->hasPpgMetaData()
      || this->hasAccMetaData()
      || this->absoluteBlock.isSet()
      || this->getSensorType() != SensorTypeProtobuf::SENSOR_TYPE_NONE
      || this->dataForm != DataForm::DATA_FORM_NONE;
  // clang-format on
}

ChannelJson Channel::toJson() const noexcept {
  ChannelJson channelJson;
  if (!this->isSet()) {
    return channelJson;
  }
  switch (this->dataForm) {
    case DataForm::DATA_FORM_ABSOLUTE: {
      channelJson[PcoreJson::Key::absolute_block] = this->absoluteBlock.toJson();
      switch (this->getSensorType()) {
        case SensorTypeProtobuf::SENSOR_TYPE_PPG: {
          channelJson[PcoreJson::Key::ppg_metadata] = this->getPpgMetaData()->toJson();
          break;
        }
        case SensorTypeProtobuf::SENSOR_TYPE_ACC: {
          channelJson[PcoreJson::Key::acc_metadata] = this->getAccMetaData()->toJson();
          break;
        }
        default: {
          return channelJson;
        }
      }
      break;
    }
    case DataForm::DATA_FORM_DIFFERENTIAL: {
      channelJson[PcoreJson::Key::differential_blocks] = PcoreJson::Convert::vectorToJson(this->differentialBlocks);
      switch (this->getSensorType()) {
        case SensorTypeProtobuf::SENSOR_TYPE_PPG: {
          channelJson[PcoreJson::Key::ppg_metadata] = this->getPpgMetaData()->toJson();
          break;
        }
        case SensorTypeProtobuf::SENSOR_TYPE_ACC: {
          channelJson[PcoreJson::Key::acc_metadata] = this->getAccMetaData()->toJson();
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
  if (this->dataForm != DataForm::DATA_FORM_DIFFERENTIAL) {
    throw WrongDataFormException("Channel::serialize", "only for differential data form");
  }
  for (const auto& differentialBlock : this->differentialBlocks) {
    auto* differentialBlockProtobuf = channelProtobuf->add_differential_blocks();
    differentialBlock.serialize(differentialBlockProtobuf);
  }
  switch (this->getSensorType()) {
    case SensorTypeProtobuf::SENSOR_TYPE_PPG: {
      PpgMetaDataProtobuf ppgMetaDataProtobuf;
      this->getPpgMetaData()->serialize(&ppgMetaDataProtobuf);
      channelProtobuf->mutable_ppg_metadata()->CopyFrom(ppgMetaDataProtobuf);
      break;
    }
    case SensorTypeProtobuf::SENSOR_TYPE_ACC: {
      AccMetaDataProtobuf accMetaDataProtobuf;
      this->getAccMetaData()->serialize(&accMetaDataProtobuf);
      channelProtobuf->mutable_acc_metadata()->CopyFrom(accMetaDataProtobuf);
      break;
    }
    default: {
      return;
    }
  }
}

void Channel::switchDataForm(const BlockIdxs& blockIdxs) noexcept {
  if (!this->isSet()) {
    return;
  }
  this->differentialBlocks = this->calculateDifferentialBlocks(this->absoluteBlock, blockIdxs);
  this->absoluteBlock = AbsoluteBlock();
  this->dataForm = DataForm::DATA_FORM_DIFFERENTIAL;
}

void Channel::switchDataForm() noexcept {
  if (!this->isSet()) {
    return;
  }
  this->absoluteBlock = this->calculateAbsoluteBlock(this->differentialBlocks);
  this->differentialBlocks = DifferentialBlocks();
  this->dataForm = DataForm::DATA_FORM_ABSOLUTE;
}

bool Channel::operator==(const IPCore<ChannelProtobuf>& channel) const noexcept {
  const auto* derived = dynamic_cast<const Channel*>(&channel);
  if (derived == nullptr) {
    return false;
  }
  const auto numberOfElements = this->differentialBlocks.size();
  if (numberOfElements != derived->differentialBlocks.size()) {
    return false;
  }
  for (size_t i = 0; i < numberOfElements; i++) {
    if (this->differentialBlocks[i] != derived->differentialBlocks[i]) {
      return false;
    }
  }
  if (this->metaData.has_value() != derived->metaData.has_value()) {
    return false;
  }
  bool isEqualMetaData = !this->metaData.has_value() && !derived->metaData.has_value();
  if (this->metaData.has_value() && derived->metaData.has_value()) {
    isEqualMetaData = *this->metaData == *derived->metaData;
  }

  // clang-format off
  return isEqualMetaData
      && this->absoluteBlock == derived->absoluteBlock
      && this->getSensorType() == derived->getSensorType()
      && this->dataForm == derived->dataForm;
  // clang-format off
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

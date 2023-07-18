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
#include "PcoreJson.h"
#include "PcoreProtobuf.h"

Channel::Channel(AccMetaData accMetaData, AbsoluteBlock absoluteBlock)
    : ppgMetaData(PpgMetaData()),
      accMetaData(std::move(accMetaData)),
      differentialBlocks(DifferentialBlocks()),
      absoluteBlock(std::move(absoluteBlock)),
      sensorType(SensorTypeProtobuf::SENSOR_TYPE_ACC),
      dataForm(DataForm::DATA_FORM_ABSOLUTE) {}

Channel::Channel(PpgMetaData ppgMetaData, AbsoluteBlock absoluteBlock)
    : ppgMetaData(std::move(ppgMetaData)),
      accMetaData(AccMetaData()),
      differentialBlocks(DifferentialBlocks()),
      absoluteBlock(std::move(absoluteBlock)),
      sensorType(SensorTypeProtobuf::SENSOR_TYPE_PPG),
      dataForm(DataForm::DATA_FORM_ABSOLUTE) {}

Channel::Channel(AccMetaData accMetaData, DifferentialBlocks differentialBlocks)
    : ppgMetaData(PpgMetaData()),
      accMetaData(std::move(accMetaData)),
      differentialBlocks(std::move(differentialBlocks)),
      absoluteBlock(AbsoluteBlock()),
      sensorType(SensorTypeProtobuf::SENSOR_TYPE_ACC),
      dataForm(DataForm::DATA_FORM_DIFFERENTIAL) {}

Channel::Channel(PpgMetaData ppgMetaData, DifferentialBlocks differentialBlocks)
    : ppgMetaData(std::move(ppgMetaData)),
      accMetaData(AccMetaData()),
      differentialBlocks(std::move(differentialBlocks)),
      absoluteBlock(AbsoluteBlock()),
      sensorType(SensorTypeProtobuf::SENSOR_TYPE_PPG),
      dataForm(DataForm::DATA_FORM_DIFFERENTIAL) {}

Channel::Channel(const ChannelJson& channelJson, SensorTypeProtobuf sensorTypeProtobuf, DataForm dataForm)
    : ppgMetaData(sensorTypeProtobuf == SensorTypeProtobuf::SENSOR_TYPE_PPG ? PpgMetaData(channelJson[PcoreJson::Key::ppg_metadata]) : PpgMetaData()),
      accMetaData(sensorTypeProtobuf == SensorTypeProtobuf::SENSOR_TYPE_ACC ? AccMetaData(channelJson[PcoreJson::Key::acc_metadata]) : AccMetaData()),
      differentialBlocks([&]() {
        switch (dataForm) {
          case DATA_FORM_ABSOLUTE: {
            return DifferentialBlocks();
          }
          case DATA_FORM_DIFFERENTIAL: {
            return PcoreJson::Convert::jsonToVector<DifferentialBlock>(channelJson, PcoreJson::Key::differential_blocks);
          }
          default: {
            throw std::runtime_error("DataForm is NONE");
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
            throw std::runtime_error("DataForm is NONE");
          }
        }
      }()),
      sensorType(sensorTypeProtobuf),
      dataForm(dataForm) {
  if (sensorTypeProtobuf == SensorTypeProtobuf::SENSOR_TYPE_NONE) {
    throw std::runtime_error("SensorType is not set");
  }
}

Channel::Channel(const ChannelProtobuf& channelProtobuf)
    : ppgMetaData(PpgMetaData(channelProtobuf.ppg_metadata())),
      accMetaData(AccMetaData(channelProtobuf.acc_metadata())),
      differentialBlocks(PcoreProtobuf::Convert::protobufToVector<DifferentialBlock>(channelProtobuf.differential_blocks())),
      absoluteBlock(AbsoluteBlock()),
      sensorType([&]() {
        if (channelProtobuf.has_acc_metadata()) {
          return SensorTypeProtobuf::SENSOR_TYPE_ACC;
        } else if (channelProtobuf.has_ppg_metadata()) {
          return SensorTypeProtobuf::SENSOR_TYPE_PPG;
        } else {
          return SensorTypeProtobuf::SENSOR_TYPE_NONE;
        }
      }()),
      dataForm([&]() {
        if (channelProtobuf.has_ppg_metadata() || channelProtobuf.has_acc_metadata() || !channelProtobuf.differential_blocks().empty()) {
          return DataForm::DATA_FORM_DIFFERENTIAL;
        } else {
          return DataForm::DATA_FORM_NONE;
        }
      }()) {}

Channel::Channel()
    : ppgMetaData(PpgMetaData()),
      accMetaData(AccMetaData()),
      differentialBlocks(DifferentialBlocks()),
      absoluteBlock(AbsoluteBlock()),
      sensorType(SensorTypeProtobuf::SENSOR_TYPE_NONE),
      dataForm(DataForm::DATA_FORM_NONE) {}

DifferentialBlocks Channel::getDifferentialBlocks() const {
  return this->differentialBlocks;
}

AbsoluteBlock Channel::getAbsoluteBlock() const {
  return this->absoluteBlock;
}

AccMetaData Channel::getAccMetaData() const {
  return this->accMetaData;
}

PpgMetaData Channel::getPpgMetaData() const {
  return this->ppgMetaData;
}

SensorTypeProtobuf Channel::getSensorType() const {
  return this->sensorType;
}

DataForm Channel::getDataForm() const {
  return this->dataForm;
}

bool Channel::operator==(const IPCore<ChannelProtobuf>& channel) const {
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
  // clang-format off
  return this->accMetaData == derived->accMetaData
      && this->ppgMetaData == derived->ppgMetaData
      && this->absoluteBlock == derived->absoluteBlock
      && this->sensorType == derived->sensorType
      && this->dataForm == derived->dataForm;
  // clang-format off
}

bool Channel::operator!=(const IPCore<ChannelProtobuf>& channel) const {
  return !(*this == channel);
}

bool Channel::hasAccMetaData() const {
  return this->accMetaData.isSet();
}

bool Channel::hasPpgMetaData() const {
  return this->ppgMetaData.isSet();
}

bool Channel::hasDifferentialBlocks() const {
  return !this->differentialBlocks.empty();
}

bool Channel::hasAbsoluteBlock() const {
  return this->absoluteBlock.isSet();
}

void Channel::serialize(ChannelProtobuf* channelProtobuf) const {
  if (channelProtobuf == nullptr) {
    throw std::invalid_argument("Error in serialize: differentialBlockProtobuf is a null pointer");
  }
  if (!this->isSet()) {
    return;
  }
  if (this->dataForm != DataForm::DATA_FORM_DIFFERENTIAL) {
    throw std::runtime_error("Serialize is only possible for differential data form");
  }
  if (this->hasAccMetaData() && this->hasPpgMetaData()) {
    throw std::invalid_argument("just one type of MetaData can be initialized");
  }
  if (this->hasAccMetaData()) {
    AccMetaDataProtobuf accMetaDataProtobuf;
    this->accMetaData.serialize(&accMetaDataProtobuf);
    channelProtobuf->mutable_acc_metadata()->CopyFrom(accMetaDataProtobuf);
  } else if (this->hasPpgMetaData()) {
    PpgMetaDataProtobuf ppgMetaDataProtobuf;
    this->ppgMetaData.serialize(&ppgMetaDataProtobuf);
    channelProtobuf->mutable_ppg_metadata()->CopyFrom(ppgMetaDataProtobuf);
  } else {
    throw std::invalid_argument("SensorType is not set");
  }
  for (const auto& differentialBlock : this->differentialBlocks) {
    auto* differentialBlockProtobuf = channelProtobuf->add_differential_blocks();
    differentialBlock.serialize(differentialBlockProtobuf);
  }
}

void Channel::switchDataForm(const BlockIdxs& blockIdxs) {
  if (!this->isSet()) {
    return;
  }
  this->differentialBlocks = this->calculateDifferentialBlocks(this->absoluteBlock, blockIdxs);
  this->absoluteBlock = AbsoluteBlock();
  this->dataForm = DataForm::DATA_FORM_DIFFERENTIAL;
}

void Channel::switchDataForm() {
  if (!this->isSet()) {
    return;
  }
  this->absoluteBlock = this->calculateAbsoluteBlock(this->differentialBlocks);
  this->differentialBlocks = DifferentialBlocks();
  this->dataForm = DataForm::DATA_FORM_ABSOLUTE;
}

bool Channel::isSet() const {
  for (const auto& differentialBlock : this->differentialBlocks) {
    if (differentialBlock.isSet()) {
      return true;
    }
  }
  // clang-format off
  return this->ppgMetaData.isSet()
      || this->accMetaData.isSet()
      || this->absoluteBlock.isSet()
      || this->sensorType != SensorTypeProtobuf::SENSOR_TYPE_NONE
      || this->dataForm != DataForm::DATA_FORM_NONE;
  // clang-format on
}

DifferentialBlocks Channel::calculateDifferentialBlocks(const AbsoluteBlock& absoluteBlock, const BlockIdxs& blockIdxs) const {
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
                                                   const AbsoluteValues& absoluteValues) const {
  DifferentialValues differentialValues;
  differentialValues.push_back(absoluteValues[fromBlockIdx]);
  for (size_t i = fromBlockIdx + 1; i <= toBlockIdx; i++) {
    differentialValues.emplace_back(absoluteValues[i] - absoluteValues[i - 1]);
  }
  return DifferentialBlock(differentialValues);
}

AbsoluteBlock Channel::calculateAbsoluteBlock(const DifferentialBlocks& differentialBlocks) const {
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

ChannelJson Channel::toJson() const {
  ChannelJson channelJson;
  if (!this->isSet()) {
    return channelJson;
  }
  switch (this->dataForm) {
    case DataForm::DATA_FORM_ABSOLUTE: {
      channelJson[PcoreJson::Key::absolute_block] = this->absoluteBlock.toJson();
      switch (this->sensorType) {
        case SensorTypeProtobuf::SENSOR_TYPE_PPG: {
          channelJson[PcoreJson::Key::ppg_metadata] = this->ppgMetaData.toJson();
          break;
        }
        case SensorTypeProtobuf::SENSOR_TYPE_ACC: {
          channelJson[PcoreJson::Key::acc_metadata] = this->accMetaData.toJson();
          break;
        }
        default: {
          throw std::runtime_error("sensorTypeProtobuf is not set");
        }
      }
      break;
    }
    case DataForm::DATA_FORM_DIFFERENTIAL: {
      channelJson[PcoreJson::Key::differential_blocks] = PcoreJson::Convert::vectorToJson(this->differentialBlocks);
      switch (this->sensorType) {
        case SensorTypeProtobuf::SENSOR_TYPE_PPG: {
          channelJson[PcoreJson::Key::ppg_metadata] = this->ppgMetaData.toJson();
          break;
        }
        case SensorTypeProtobuf::SENSOR_TYPE_ACC: {
          channelJson[PcoreJson::Key::acc_metadata] = this->accMetaData.toJson();
          break;
        }
        default: {
          throw std::runtime_error("sensorTypeProtobuf is not set");
        }
      }
      break;
    }
    default: {
      throw std::runtime_error("dataForm is not set");
    }
  }
  return channelJson;
}

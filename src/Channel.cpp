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

Channel::Channel(const AccMetaData& accMetaData, AbsoluteBlock absoluteBlock)
    : ppgMetaData(PpgMetaData()), accMetaData(accMetaData), differentialBlocks(DifferentialBlocks()), absoluteBlock(std::move(absoluteBlock)) {}

Channel::Channel(const PpgMetaData& ppgMetaData, AbsoluteBlock absoluteBlock)
    : ppgMetaData(ppgMetaData), accMetaData(AccMetaData()), differentialBlocks(DifferentialBlocks()), absoluteBlock(std::move(absoluteBlock)) {}

Channel::Channel(const AccMetaData& accMetaData, DifferentialBlocks differentialBlocks)
    : ppgMetaData(PpgMetaData()), accMetaData(accMetaData), differentialBlocks(std::move(differentialBlocks)), absoluteBlock(AbsoluteBlock()) {}

Channel::Channel(const PpgMetaData& ppgMetaData, DifferentialBlocks differentialBlocks)
    : ppgMetaData(ppgMetaData), accMetaData(AccMetaData()), differentialBlocks(std::move(differentialBlocks)), absoluteBlock(AbsoluteBlock()) {}

Channel::Channel(const ChannelJson& channelJson, ProtobufSensorType protobufSensorType, DataForm dataForm)
    : ppgMetaData(protobufSensorType == ProtobufSensorType::SENSOR_TYPE_PPG ? PpgMetaData(channelJson[PcoreJsonKey::ppg_metadata]) : PpgMetaData()),
      accMetaData(protobufSensorType == ProtobufSensorType::SENSOR_TYPE_ACC ? AccMetaData(channelJson[PcoreJsonKey::acc_metadata]) : AccMetaData()),
      differentialBlocks([&]() {
        switch (dataForm) {
          case DATA_FORM_ABSOLUTE: {
            return DifferentialBlocks();
          }
          case DATA_FORM_DIFFERENTIAL: {
            DifferentialBlocksJson differentialBlocksJson = channelJson[PcoreJsonKey::differential_blocks];
            DifferentialBlocks differentialBlocks;
            differentialBlocks.reserve(differentialBlocksJson.size());
            for (auto& differentialBlockJson : differentialBlocksJson) {
              differentialBlocks.emplace_back(DifferentialBlock(differentialBlockJson));
            }
            return differentialBlocks;
          }
          default: {
            throw std::runtime_error("DataForm is NONE");
          }
        }
      }()),
      absoluteBlock([&]() {
        switch (dataForm) {
          case DATA_FORM_ABSOLUTE: {
            return AbsoluteBlock(channelJson[PcoreJsonKey::absolute_block]);
          }
          case DATA_FORM_DIFFERENTIAL: {
            return AbsoluteBlock();
          }
          default: {
            throw std::runtime_error("DataForm is NONE");
          }
        }
      }()) {
  if (protobufSensorType == ProtobufSensorType::SENSOR_TYPE_NONE) {
    throw std::runtime_error("SensorType is not set");
  }
}

Channel::Channel(const ProtobufChannel& protobufChannel)
    : ppgMetaData(PpgMetaData(protobufChannel.ppg_metadata())),
      accMetaData(AccMetaData(protobufChannel.acc_metadata())),
      differentialBlocks([&]() {
        auto protobufDifferentialBlocks = protobufChannel.differential_blocks();
        DifferentialBlocks differentialBlocks{};
        differentialBlocks.reserve(protobufDifferentialBlocks.size());
        for (auto& protobufDifferentialBlock : protobufDifferentialBlocks) {
          differentialBlocks.emplace_back(DifferentialBlock(protobufDifferentialBlock));
        }
        return differentialBlocks;
      }()),
      absoluteBlock(AbsoluteBlock()) {}

Channel::Channel()
    : ppgMetaData(PpgMetaData()), accMetaData(AccMetaData()), differentialBlocks(DifferentialBlocks()), absoluteBlock(AbsoluteBlock()) {}

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

bool Channel::operator==(const Channel& channel) const {
  if (this->differentialBlocks.size() != channel.differentialBlocks.size()) {
    return false;
  }
  const auto numberOfElements = this->differentialBlocks.size();
  for (size_t i = 0; i < numberOfElements; i++) {
    if (this->differentialBlocks[i] != channel.differentialBlocks[i]) {
      return false;
    }
  }
  return this->accMetaData == channel.accMetaData && this->ppgMetaData == channel.ppgMetaData && this->absoluteBlock == channel.absoluteBlock;
}

bool Channel::operator!=(const Channel& channel) const {
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

void Channel::serialize(ProtobufChannel* protobufChannel) const {
  if (protobufChannel == nullptr) {
    throw std::invalid_argument("Error in serialize: protobufDifferentialBlock is a null pointer");
  }
  if (accMetaData.isSet() == ppgMetaData.isSet()) {
    throw std::invalid_argument("just one type of MetaData can be initialized");
  }
  if (this->accMetaData.isSet()) {
    ProtobufAccMetaData protobufAccMetaData;
    this->accMetaData.serialize(&protobufAccMetaData);
    protobufChannel->mutable_acc_metadata()->CopyFrom(protobufAccMetaData);
  } else if (this->ppgMetaData.isSet()) {
    ProtobufPpgMetaData protobufPpgMetaData;
    this->ppgMetaData.serialize(&protobufPpgMetaData);
    protobufChannel->mutable_ppg_metadata()->CopyFrom(protobufPpgMetaData);
  }
  for (auto& differentialBlock : this->differentialBlocks) {
    ProtobufDifferentialBlock* protobufDifferentialBlock = protobufChannel->add_differential_blocks();
    differentialBlock.serialize(protobufDifferentialBlock);
  }
}

void Channel::switchDataForm(const BlockIdxs& blockIdxs) {
  this->differentialBlocks = this->calculateDifferentialBlocks(this->absoluteBlock, blockIdxs);
  this->absoluteBlock = AbsoluteBlock();
}

void Channel::switchDataForm() {
  this->absoluteBlock = this->calculateAbsoluteBlock(this->differentialBlocks);
  this->differentialBlocks = DifferentialBlocks();
}

DifferentialBlocks Channel::calculateDifferentialBlocks(const AbsoluteBlock& absoluteBlock, const BlockIdxs& blockIdxs) const {
  DifferentialBlocks differentialBlocks = {};
  const auto numberOfBlocks = blockIdxs.size();
  /*
  * blockIdxs.size = 0 -> no values are included
                            return default value for emptyBlock
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
  DifferentialValues differentialValues = {};
  differentialValues.push_back(absoluteValues[fromBlockIdx]);
  for (size_t i = fromBlockIdx + 1; i <= toBlockIdx; i++) {
    differentialValues.emplace_back(absoluteValues[i] - absoluteValues[i - 1]);
  }
  return DifferentialBlock(differentialValues);
}

AbsoluteBlock Channel::calculateAbsoluteBlock(const DifferentialBlocks& differentialBlocks) const {
  AbsoluteValues absoluteValues = {};
  size_t numberOfElements = 0;
  for (auto& differentialBlock : differentialBlocks) {
    numberOfElements += differentialBlock.getDifferentialValues().size();
  }
  absoluteValues.reserve(numberOfElements);
  for (auto& differentialBlock : differentialBlocks) {
    AbsoluteValue absoluteValue = 0;
    for (auto& differentialValue : differentialBlock.getDifferentialValues()) {
      absoluteValue += differentialValue;
      absoluteValues.push_back(absoluteValue);
    }
  }
  return AbsoluteBlock(absoluteValues);
}

ChannelJson Channel::toJson(const DataForm currentDataForm, const ProtobufSensorType protobufSensorType) const {
  ChannelJson channelJson;
  switch (currentDataForm) {
    case DataForm::DATA_FORM_ABSOLUTE: {
      AbsoluteBlockJson absoluteBlockJson(this->absoluteBlock.toJson());
      channelJson[PcoreJsonKey::absolute_block] = absoluteBlockJson;
      switch (protobufSensorType) {
        case ProtobufSensorType::SENSOR_TYPE_PPG: {
          channelJson[PcoreJsonKey::ppg_metadata] = this->ppgMetaData.toJson();
          break;
        }
        case ProtobufSensorType::SENSOR_TYPE_ACC: {
          channelJson[PcoreJsonKey::acc_metadata] = this->accMetaData.toJson();
          break;
        }
        default: {
          throw std::runtime_error("protobufSensorType is not set");
        }
      }
      break;
    }
    case DataForm::DATA_FORM_DIFFERENTIAL: {
      DifferentialBlocksJson differentialBlocksJson(Json::arrayValue);
      for (auto& differentialBlock : this->differentialBlocks) {
        differentialBlocksJson.append(differentialBlock.toJson());
      }
      channelJson[PcoreJsonKey::differential_blocks] = differentialBlocksJson;
      switch (protobufSensorType) {
        case ProtobufSensorType::SENSOR_TYPE_PPG: {
          channelJson[PcoreJsonKey::ppg_metadata] = this->ppgMetaData.toJson();
          break;
        }
        case ProtobufSensorType::SENSOR_TYPE_ACC: {
          channelJson[PcoreJsonKey::acc_metadata] = this->accMetaData.toJson();
          break;
        }
        default: {
          throw std::runtime_error("protobufSensorType is not set");
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

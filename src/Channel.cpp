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

Channel::Channel(AccMetaData& accMetaData, AbsoluteBlock& absoluteBlock)
    : ppgMetaData(PpgMetaData()), accMetaData(accMetaData), differentialBlocks(DifferentialBlocks()), absoluteBlock(absoluteBlock) {}

Channel::Channel(PpgMetaData& ppgMetaData, AbsoluteBlock& absoluteBlock)
    : ppgMetaData(ppgMetaData), accMetaData(AccMetaData()), differentialBlocks(DifferentialBlocks()), absoluteBlock(absoluteBlock) {}

Channel::Channel(AccMetaData& accMetaData, DifferentialBlocks& differentialBlocks)
    : ppgMetaData(PpgMetaData()), accMetaData(accMetaData), differentialBlocks(differentialBlocks), absoluteBlock(AbsoluteBlock()) {}

Channel::Channel(PpgMetaData& ppgMetaData, DifferentialBlocks& differentialBlocks)
    : ppgMetaData(ppgMetaData), accMetaData(AccMetaData()), differentialBlocks(differentialBlocks), absoluteBlock(AbsoluteBlock()) {}

Channel::Channel(ChannelJson& channelJson, ProtobufSensorType protobufSensorType, DataForm dataForm)
    : ppgMetaData(protobufSensorType == ProtobufSensorType::SENSOR_TYPE_PPG ? PpgMetaData(channelJson["ppg_metadata"]) : PpgMetaData()),
      accMetaData(protobufSensorType == ProtobufSensorType::SENSOR_TYPE_ACC ? AccMetaData(channelJson["acc_metadata"]) : AccMetaData()),
      differentialBlocks([&]() {
        switch (dataForm) {
          case DATA_FORM_ABSOLUTE: {
            return DifferentialBlocks();
          }
          case DATA_FORM_DIFFERENTIAL: {
            DifferentialBlocksJson differentialBlocksJson = channelJson["differential_blocks"];
            DifferentialBlocks differentialBlocks;
            differentialBlocks.reserve(differentialBlocksJson.size());
            for (auto& differentialBlockJson : differentialBlocksJson) {
              differentialBlocks.push_back(DifferentialBlock(differentialBlockJson));
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
            return AbsoluteBlock(channelJson["absolute_block"]);
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
    throw std::runtime_error("Sensortype is not set");
  }
}

Channel::Channel(const ProtobufChannel& protobufChannel)
    : ppgMetaData(PpgMetaData(protobufChannel.ppg_metadata())),
      accMetaData(AccMetaData(protobufChannel.acc_metadata())),
      differentialBlocks([&]() {
        DifferentialBlocks differentialBlocks{};
        for (auto& protobufDifferentialBlock : protobufChannel.differential_blocks()) {
          differentialBlocks.push_back(DifferentialBlock(protobufDifferentialBlock));
        }
        return differentialBlocks;
      }()),
      absoluteBlock(AbsoluteBlock()) {}

Channel::Channel()
    : ppgMetaData(PpgMetaData()), accMetaData(AccMetaData()), differentialBlocks(DifferentialBlocks()), absoluteBlock(AbsoluteBlock()) {}

DifferentialBlocks Channel::getDifferentialBlocks() {
  return this->differentialBlocks;
}

AbsoluteBlock Channel::getAbsoluteBlock() {
  return this->absoluteBlock;
}

AccMetaData Channel::getAccMetaData() {
  return this->accMetaData;
}

PpgMetaData Channel::getPpgMetaData() {
  return this->ppgMetaData;
}

bool Channel::isEqual(Channel& channel) {
  if (this->differentialBlocks.size() != channel.differentialBlocks.size()) {
    return false;
  }
  for (size_t i = 0; i < this->differentialBlocks.size(); i++) {
    if (!this->differentialBlocks[i].isEqual(channel.differentialBlocks[i])) {
      return false;
    }
  }
  return this->accMetaData.isEqual(channel.accMetaData) && this->ppgMetaData.isEqual(channel.ppgMetaData) &&
         this->absoluteBlock.isEqual(channel.absoluteBlock);
}

bool Channel::hasAccMetaData() {
  return this->accMetaData.isSet();
}

bool Channel::hasPpgMetaData() {
  return this->ppgMetaData.isSet();
}

bool Channel::hasDifferentialBlocks() {
  return !this->differentialBlocks.empty();
}

bool Channel::hasAbsoluteBlock() {
  return this->absoluteBlock.isSet();
}

void Channel::serialize(ProtobufChannel* protobufChannel) {
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

void Channel::switchDataForm(BlockIdxs& blockIdxs) {
  this->differentialBlocks = this->calculateDifferentialBlocks(this->absoluteBlock, blockIdxs);
  this->absoluteBlock = AbsoluteBlock();
}

void Channel::switchDataForm() {
  this->absoluteBlock = this->calculateAbsoluteBlock(this->differentialBlocks);
  this->differentialBlocks = DifferentialBlocks();
}

DifferentialBlocks Channel::calculateDifferentialBlocks(AbsoluteBlock& absoluteBlock, BlockIdxs& blockIdxs) {
  DifferentialBlocks differentialBlocks = {};
  size_t numberOfBlocks = blockIdxs.size();
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
  AbsoluteValues absoluteValues = absoluteBlock.getAbsoluteValues();
  size_t numberOfAbsoluteValues = absoluteValues.size();
  BlockIdx fromBlockIdx = 0;
  BlockIdx toBlockIdx = numberOfAbsoluteValues > 1 ? numberOfAbsoluteValues - 1 : 0;
  if (numberOfBlocks == 1) {
    differentialBlocks.push_back(this->createDifferentialBlock(fromBlockIdx, toBlockIdx,
                                                               absoluteValues));  // toIdx = 0  would create a DifferentialBlock with a absoluteValue.
    return differentialBlocks;
  }

  for (size_t i = 0; i < numberOfBlocks - 1; i++) {  // calculate DifferentialBlocks for all blockIdxs except last Idx
    fromBlockIdx = blockIdxs[i];
    toBlockIdx = blockIdxs[i + 1] - 1;
    differentialBlocks.push_back(this->createDifferentialBlock(fromBlockIdx, toBlockIdx, absoluteValues));
  }
  fromBlockIdx = numberOfAbsoluteValues - 1 == blockIdxs[numberOfBlocks - 1] ? numberOfAbsoluteValues - 1 : blockIdxs[numberOfBlocks - 1];
  toBlockIdx = numberOfAbsoluteValues - 1;
  differentialBlocks.push_back(this->createDifferentialBlock(fromBlockIdx, toBlockIdx, absoluteValues));
  return differentialBlocks;
}

DifferentialBlock Channel::createDifferentialBlock(BlockIdx fromBlockIdx, BlockIdx toBlockIdx, AbsoluteValues& absoluteValues) {
  DifferentialValues differentialValues = {};
  differentialValues.push_back(absoluteValues[fromBlockIdx]);
  for (size_t i = fromBlockIdx + 1; i <= toBlockIdx; i++) {
    differentialValues.push_back(absoluteValues[i] - absoluteValues[i - 1]);
  }
  return DifferentialBlock(differentialValues);
}

AbsoluteBlock Channel::calculateAbsoluteBlock(DifferentialBlocks& differentialBlocks) {
  AbsoluteValues absoluteValues = {};
  for (auto& differentialBlock : differentialBlocks) {
    AbsoluteValue absoluteValue = 0;
    for (auto& differentialValue : differentialBlock.getDifferentialValues()) {
      absoluteValue += differentialValue;
      absoluteValues.push_back(absoluteValue);
    }
  }
  return AbsoluteBlock(absoluteValues);
}

ChannelJson Channel::toJson(DataForm dataForm, ProtobufSensorType protobufSensorType) {
  ChannelJson channelJson;
  switch (dataForm) {
    case DataForm::DATA_FORM_ABSOLUTE: {
      AbsoluteBlockJson absoluteBlockJson(this->absoluteBlock.toJson());
      channelJson["absolute_block"] = absoluteBlockJson;
      switch (protobufSensorType) {
        case ProtobufSensorType::SENSOR_TYPE_PPG: {
          channelJson["ppg_metadata"] = this->ppgMetaData.toJson();
          break;
        }
        case ProtobufSensorType::SENSOR_TYPE_ACC: {
          channelJson["acc_metadata"] = this->accMetaData.toJson();
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
      channelJson["differential_blocks"] = differentialBlocksJson;
      switch (protobufSensorType) {
        case ProtobufSensorType::SENSOR_TYPE_PPG: {
          channelJson["ppg_metadata"] = this->ppgMetaData.toJson();
          break;
        }
        case ProtobufSensorType::SENSOR_TYPE_ACC: {
          channelJson["acc_metadata"] = this->accMetaData.toJson();
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

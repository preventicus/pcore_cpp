/*

Created by Jakob Glück 2023

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

using DifferentialBlocksJson = Json::Value;
using DifferentialBlocks = std::vector<DifferentialBlock>;

Channel::Channel(AccMetaData& accMetaData, AbsoluteBlock& absoluteBlock, BlockIdxs& blockIdxs) {
  this->absoluteBlock = absoluteBlock;
  this->differentialBlocks = this->calculateDifferentialBlocks(absoluteBlock, blockIdxs);
  this->accMetaData = accMetaData;
  this->ppgMetaData = PpgMetaData();
}

Channel::Channel(PpgMetaData& ppgMetaData, AbsoluteBlock& absoluteBlock, BlockIdxs& blockIdxs) {
  this->absoluteBlock = absoluteBlock;
  this->differentialBlocks = this->calculateDifferentialBlocks(absoluteBlock, blockIdxs);
  this->ppgMetaData = ppgMetaData;
  this->accMetaData = AccMetaData();
}

Channel::Channel(AccMetaData& accMetaData, DifferentialBlocks& differentialBlocks) {
  this->differentialBlocks = differentialBlocks;
  this->absoluteBlock = this->calculateAbsoluteBlock(differentialBlocks);
  this->accMetaData = accMetaData;
  this->ppgMetaData = PpgMetaData();
}

Channel::Channel(PpgMetaData& ppgMetaData, DifferentialBlocks& differentialBlocks) {
  this->differentialBlocks = differentialBlocks;
  this->absoluteBlock = this->calculateAbsoluteBlock(differentialBlocks);
  this->ppgMetaData = ppgMetaData;
  this->accMetaData = AccMetaData();
}

Channel::Channel(ChannelJson& channelJson, ProtobufSensorType protobufSensorType, BlockIdxs& blockIdxs) {
  switch (protobufSensorType) {
    case ProtobufSensorType::SENSOR_TYPE_PPG: {
      this->ppgMetaData = PpgMetaData(channelJson["ppg_metadata"]);
      this->accMetaData = AccMetaData();
      break;
    }
    case ProtobufSensorType::SENSOR_TYPE_ACC: {
      this->accMetaData = AccMetaData(channelJson["acc_metadata"]);
      this->ppgMetaData = PpgMetaData();
      break;
    }
    default: {
      throw std::runtime_error("Sensortype is not set");
    }
  }

  AbsoluteBlock absoluteBlock = AbsoluteBlock(channelJson["absolute_block"]);
  this->absoluteBlock = absoluteBlock;
  this->differentialBlocks = this->calculateDifferentialBlocks(absoluteBlock, blockIdxs);
}

Channel::Channel(ChannelJson& channelJson, ProtobufSensorType protobufSensorType) {
  switch (protobufSensorType) {
    case ProtobufSensorType::SENSOR_TYPE_PPG: {
      this->ppgMetaData = PpgMetaData(channelJson["ppg_metadata"]);
      this->accMetaData = AccMetaData();
      break;
    }
    case ProtobufSensorType::SENSOR_TYPE_ACC: {
      this->accMetaData = AccMetaData(channelJson["acc_metadata"]);
      this->ppgMetaData = PpgMetaData();
      break;
    }
    default: {
      throw std::runtime_error("Sensortype is not set");
    }
  }

  DifferentialBlocksJson differentialBlocksJson = channelJson["differential_blocks"];
  DifferentialBlocks differentialBlocks;
  differentialBlocks.reserve(differentialBlocksJson.size());
  for (auto& differentialBlockJson : differentialBlocksJson) {
    differentialBlocks.push_back(DifferentialBlock(differentialBlockJson));
  }
  this->differentialBlocks = differentialBlocks;
  this->absoluteBlock = this->calculateAbsoluteBlock(differentialBlocks);
}

Channel::Channel(const ProtobufChannel& protobufChannel) {
  this->deserialize(protobufChannel);
}

Channel::Channel() {
  this->accMetaData = AccMetaData();
  this->ppgMetaData = PpgMetaData();
  this->absoluteBlock = AbsoluteBlock();
  this->differentialBlocks = DifferentialBlocks{};
}

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
  size_t numberOfAbsoluteValues = absoluteBlock.getAbsoluteValues().size();
  BlockIdx fromBlockIdx = 0;
  BlockIdx toBlockIdx = 0;
  if (numberOfBlocks == 1) {
    toBlockIdx = numberOfAbsoluteValues > 1 ? numberOfAbsoluteValues - 1 : 0;
    differentialBlocks.push_back(
        this->createDifferentialBlock(fromBlockIdx, toBlockIdx));  // toIdx = 0  would create a DifferentialBlock with a absoluteValue.
    return differentialBlocks;
  }

  for (size_t i = 0; i < numberOfBlocks - 1; i++) {  // calculate DifferentialBlocks for all blockIdxs except last Idx
    fromBlockIdx = blockIdxs[i];
    toBlockIdx = blockIdxs[i + 1] - 1;
    differentialBlocks.push_back(this->createDifferentialBlock(fromBlockIdx, toBlockIdx));
  }
  fromBlockIdx = numberOfAbsoluteValues - 1 == blockIdxs[numberOfBlocks - 1] ? numberOfAbsoluteValues - 1 : blockIdxs[numberOfBlocks - 1];
  toBlockIdx = numberOfAbsoluteValues - 1;
  differentialBlocks.push_back(this->createDifferentialBlock(fromBlockIdx, toBlockIdx));
  return differentialBlocks;
}

DifferentialBlock Channel::createDifferentialBlock(BlockIdx fromBlockIdx, BlockIdx toBlockIdx) {
  DifferentialValues differentialValues = {};
  AbsoluteValues absoluteValues = this->absoluteBlock.getAbsoluteValues();
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
    case DataForm::ABSOLUTE: {
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
    case DataForm::DIFFERENTIAL: {
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

void Channel::deserialize(const ProtobufChannel& protobufChannel) {
  DifferentialBlocks differentialBlocks{};
  for (auto& protobufDifferentialBlock : protobufChannel.differential_blocks()) {
    differentialBlocks.push_back(DifferentialBlock(protobufDifferentialBlock));
  }
  this->absoluteBlock = this->calculateAbsoluteBlock(differentialBlocks);
  this->differentialBlocks = differentialBlocks;
  this->accMetaData = AccMetaData(protobufChannel.acc_metadata());
  this->ppgMetaData = PpgMetaData(protobufChannel.ppg_metadata());
}
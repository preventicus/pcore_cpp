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

Channel::Channel(AccMetaData& accMetaData, AbsoluteBlock absoluteBlock, std::vector<size_t> blockIdxs) {
  this->absoluteBlock = absoluteBlock;
  this->differentialBlocks = this->calculateDifferentialBlocks(absoluteBlock, blockIdxs);
  this->accMetaData = accMetaData;
  this->ppgMetaData = PpgMetaData();
}

Channel::Channel(PpgMetaData& ppgMetaData, AbsoluteBlock absoluteBlock, std::vector<size_t> blockIdxs) {
  this->absoluteBlock = absoluteBlock;
  this->differentialBlocks = this->calculateDifferentialBlocks(absoluteBlock, blockIdxs);
  this->ppgMetaData = ppgMetaData;
  this->accMetaData = AccMetaData();
}

Channel::Channel(AccMetaData& accMetaData, std::vector<DifferentialBlock>& differentialBlocks) {
  this->differentialBlocks = differentialBlocks;
  this->absoluteBlock = this->calculateAbsoluteBlock(differentialBlocks);
  this->accMetaData = accMetaData;
  this->ppgMetaData = PpgMetaData();
}

Channel::Channel(PpgMetaData& ppgMetaData, std::vector<DifferentialBlock>& differentialBlocks) {
  this->differentialBlocks = differentialBlocks;
  this->absoluteBlock = this->calculateAbsoluteBlock(differentialBlocks);
  this->ppgMetaData = ppgMetaData;
  this->accMetaData = AccMetaData();
}

Channel::Channel(Json::Value& channel, ProtobufSensorType sensorType, std::vector<size_t> blockIdxs) {
  AbsoluteBlock absoluteBlock = AbsoluteBlock(channel["absolute_block"]);
  this->absoluteBlock = absoluteBlock;
  this->differentialBlocks = this->calculateDifferentialBlocks(absoluteBlock, blockIdxs);
  switch (sensorType) {
    case ProtobufSensorType::SENSOR_TYPE_PPG: {
      this->ppgMetaData = PpgMetaData(channel["ppg_metadata"]);
      this->accMetaData = AccMetaData();
      break;
    }
    case ProtobufSensorType::SENSOR_TYPE_ACC: {
      this->accMetaData = AccMetaData(channel["acc_metadata"]);
      this->ppgMetaData = PpgMetaData();
      break;
    }
    default: {
      break;
    }
  }
}

Channel::Channel(Json::Value& channel, ProtobufSensorType sensorType) {
  Json::Value jsonDifferentialBlocks = channel["differential_blocks"];
  std::vector<DifferentialBlock> differentialBlocks;
  differentialBlocks.reserve(jsonDifferentialBlocks.size());
  for (auto& jsonDifferentialBlock : jsonDifferentialBlocks) {
    differentialBlocks.push_back(jsonDifferentialBlock);
  }
  this->differentialBlocks = differentialBlocks;
  this->absoluteBlock = this->calculateAbsoluteBlock(differentialBlocks);
  switch (sensorType) {
    case ProtobufSensorType::SENSOR_TYPE_PPG: {
      this->ppgMetaData = PpgMetaData(channel["ppg_metadata"]);
      this->accMetaData = AccMetaData();
      break;
    }
    case ProtobufSensorType::SENSOR_TYPE_ACC: {
      this->accMetaData = AccMetaData(channel["acc_metadata"]);
      this->ppgMetaData = PpgMetaData();
      break;
    }
    default: {
      break;
    }
  }
}

Channel::Channel(const ProtobufChannel& protobufChannel) {
  this->deserialize(protobufChannel);
}

Channel::Channel() {
  this->accMetaData = AccMetaData();
  this->ppgMetaData = PpgMetaData();
  this->absoluteBlock = AbsoluteBlock();
  this->differentialBlocks = std::vector<DifferentialBlock>{};
}

std::vector<DifferentialBlock> Channel::getDifferentialBlocks() {
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
    ProtobufAccMetaData protobufaccMetaData;
    this->accMetaData.serialize(&protobufaccMetaData);
    protobufChannel->mutable_acc_metadata()->CopyFrom(protobufaccMetaData);
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

std::vector<DifferentialBlock> Channel::calculateDifferentialBlocks(AbsoluteBlock absoluteBlock, std::vector<size_t> blocksIdxs) {
  std::vector<DifferentialBlock> differentialBlocks = {};
  size_t numberOfBlocks = blocksIdxs.size();
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
  size_t absoluteValuesSize = absoluteBlock.getAbsoluteValues().size();
  if (numberOfBlocks == 1) {
    size_t fromIdx = 0;
    size_t toIdx = absoluteValuesSize > 1 ? absoluteValuesSize - 1 : 0;
    DifferentialBlock differentialBlock =
        DifferentialBlock(this->createDifferentialBlock(fromIdx, toIdx));  // toIdx = 0  would create a DifferentialBlock with a absoluteValue.
    differentialBlocks.push_back(differentialBlock);
    return differentialBlocks;
  }
  size_t fromIdx = 0;
  size_t toIdx = 0;
  for (size_t i = 0; i < numberOfBlocks - 1; i++) {  // calculate DifferentialBlocks for all blockIdxs except last Idx
    fromIdx = blocksIdxs[i];
    toIdx = blocksIdxs[i + 1] - 1;
    differentialBlocks.push_back(this->createDifferentialBlock(fromIdx, toIdx));
  }
  fromIdx = absoluteValuesSize - 1 == blocksIdxs[numberOfBlocks - 1]
                ? absoluteValuesSize - 1
                : blocksIdxs[numberOfBlocks - 1];  // If the condition is true, the last block hold one value. ->case 2
  toIdx = absoluteValuesSize - 1;
  differentialBlocks.push_back(this->createDifferentialBlock(fromIdx, toIdx));
  return differentialBlocks;
}

DifferentialBlock Channel::createDifferentialBlock(size_t fromIdx, size_t toIdx) {
  std::vector<int32_t> differentialValues = {};
  std::vector<int32_t> absoluteValues = this->absoluteBlock.getAbsoluteValues();
  differentialValues.push_back(absoluteValues[fromIdx]);
  for (size_t i = fromIdx + 1; i <= toIdx; i++) {
    differentialValues.push_back(absoluteValues[i] - absoluteValues[i - 1]);
  }
  return DifferentialBlock(differentialValues);
}

AbsoluteBlock Channel::calculateAbsoluteBlock(std::vector<DifferentialBlock> differentialBlocks) {
  std::vector<int32_t> absoluteValues = {};
  for (auto& differentialBlock : differentialBlocks) {
    int32_t sumValue = 0;
    for (auto& differentialValue : differentialBlock.getDifferentialValues()) {
      sumValue += differentialValue;
      absoluteValues.push_back(sumValue);
    }
  }
  return AbsoluteBlock(absoluteValues);
}

Json::Value Channel::toJson(DataForm dataForm, ProtobufSensorType protobufSensorType) {
  Json::Value channel;
  Json::Value differentialBlocks(Json::arrayValue);
  for (auto& differentialBlock : this->differentialBlocks) {
    differentialBlocks.append(differentialBlock.toJson());
  }
  Json::Value absoluteBlocks(this->absoluteBlock.toJson());
  Json::Value metaData;
  switch (dataForm) {
    case DataForm::ABSOLUTE: {
      if (protobufSensorType == ProtobufSensorType::SENSOR_TYPE_PPG) {
        metaData = this->ppgMetaData.toJson();
        channel["ppg_metadata"] = metaData;
      }
      if (protobufSensorType == ProtobufSensorType::SENSOR_TYPE_ACC) {
        metaData = this->accMetaData.toJson();
        channel["acc_metadata"] = metaData;
      }
      channel["absolute_block"] = absoluteBlocks;
      return channel;
    }
    case DataForm::DIFFERENTIAL: {
      if (protobufSensorType == ProtobufSensorType::SENSOR_TYPE_PPG) {
        metaData = this->ppgMetaData.toJson();
        channel["ppg_metadata"] = metaData;
      }
      if (protobufSensorType == ProtobufSensorType::SENSOR_TYPE_ACC) {
        metaData = this->accMetaData.toJson();
        channel["acc_metadata"] = metaData;
      }
      channel["differential_blocks"] = differentialBlocks;
      return channel;
    }
    default: {
      break;
    }
  }
}

void Channel::deserialize(const ProtobufChannel& protobufChannel) {
  std::vector<DifferentialBlock> differentialBlocks{};
  for (auto& protobufDifferentialBlock : protobufChannel.differential_blocks()) {
    differentialBlocks.push_back(DifferentialBlock(protobufDifferentialBlock));
  }
  this->absoluteBlock = this->calculateAbsoluteBlock(differentialBlocks);
  this->differentialBlocks = differentialBlocks;
  this->accMetaData = AccMetaData(protobufChannel.acc_metadata());
  this->ppgMetaData = PpgMetaData(protobufChannel.ppg_metadata());
}
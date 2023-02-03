/*

Created by Jakob Glück 2023

Copyright © 2023 PREVENTICUS GmbH

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors
   may be used to endorse or promote products derived from this software without
   specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#include "Channel.h"

Channel::Channel(DataForm dataForm,
                 std::vector<DifferentialBlock>& differentialBlocks,
                 AbsoluteBlock& absoluteBlock,
                 AccMetaData& accMetadata,
                 PpgMetaData& ppgMetaData) {
  if (accMetadata.isSet() == ppgMetaData.isSet()) {
    throw std::invalid_argument("one type of MetaData has to be initialized");
  }
  this->absoluteBlock = absoluteBlock;
  this->differentialBlocks = differentialBlocks;
  this->accMetadata = accMetadata;
  this->ppgMetaData = ppgMetaData;
  this->dataForm = dataForm;
}

Channel::Channel(const ProtobufChannel& protobufChannel) {
  this->deserialize(protobufChannel);
}

Channel::Channel() {
  this->accMetadata = AccMetaData();
  this->ppgMetaData = PpgMetaData();
  this->absoluteBlock = AbsoluteBlock();
  this->dataForm = DataForm::NOT_SET;
  this->differentialBlocks = std::vector<DifferentialBlock>{};
};

std::vector<DifferentialBlock> Channel::getDifferentialBlocks() {
  return this->differentialBlocks;
}

AbsoluteBlock Channel::getAbsoluteBlock() {
  return this->absoluteBlock;
}

AccMetaData Channel::getAccMetaData() {
  return this->accMetadata;
}

PpgMetaData Channel::getPpgMetData() {
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
  return this->accMetadata.isEqual(channel.accMetadata) && this->ppgMetaData.isEqual(channel.ppgMetaData) &&
         this->absoluteBlock.isEqual(channel.absoluteBlock);
}

DataForm Channel::getDataform() {
  return this->dataForm;
}

void Channel::serialize(ProtobufChannel* protobufChannel) {
  if (protobufChannel == nullptr) {
    throw std::invalid_argument("Error in serialize: protobufDifferentialBlock is a null pointer");
  }
  if (this->accMetadata.isSet()) {
    ProtobufAccMetaData protobufAccMetadata;
    this->accMetadata.serialize(&protobufAccMetadata);
    protobufChannel->mutable_acc_metadata()->CopyFrom(protobufAccMetadata);
  } else if (this->ppgMetaData.isSet()) {
    ProtobufPpgMetaData protobufPpgMetaData;
    this->ppgMetaData.serialize(&protobufPpgMetaData);
    protobufChannel->mutable_ppg_metadata()->CopyFrom(protobufPpgMetaData);
  }
  for (size_t i = 0; i < this->differentialBlocks.size(); i++) {
    ProtobufDifferentialBlock* protobufDifferentialBlock = protobufChannel->add_differential_blocks();
    this->differentialBlocks[i].serialize(protobufDifferentialBlock);
  }
}

void Channel::deserialize(const ProtobufChannel& protobufChannel) {
  std::vector<DifferentialBlock> differentialBlocks{};
  for (size_t i = 0; i < protobufChannel.differential_blocks_size(); i++) {
    differentialBlocks.push_back(DifferentialBlock(protobufChannel.differential_blocks(i)));
  }
  this->differentialBlocks = differentialBlocks;
  this->accMetadata = AccMetaData(protobufChannel.acc_metadata());
  this->ppgMetaData = PpgMetaData(protobufChannel.ppg_metadata());
  this->dataForm = DataForm::DIFFERENTIAL;
}

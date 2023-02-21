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
#include "DifferentialTimestampsContainer.h"

DifferentialTimestampsContainer::DifferentialTimestampsContainer(uint64_t firstTimestamp_ms,
                                                                 std::vector<uint32_t>& blockIntervals_ms,
                                                                 std::vector<uint32_t>& timestampsIntervals_ms)
    : firstTimestamp_ms(firstTimestamp_ms), blockIntervals_ms(blockIntervals_ms), timestampsIntervals_ms(timestampsIntervals_ms) {}

DifferentialTimestampsContainer::DifferentialTimestampsContainer(const ProtobufDifferentialTimestampContainer& protobufDifferentialTimestamps) {
  this->deserialize(protobufDifferentialTimestamps);
}

DifferentialTimestampsContainer::DifferentialTimestampsContainer(Json::Value& differentialTimestampsContainer) {
  Json::Value jsonBlockIntervals_ms = differentialTimestampsContainer["block_intervals_ms"];
  Json::Value jsonTimestampIntervals_ms = differentialTimestampsContainer["timestamps_intervals_ms"];
  std::vector<uint32_t> blockIntervals_ms = {};
  std::vector<uint32_t> timestampIntervals_ms = {};

  blockIntervals_ms.reserve(jsonBlockIntervals_ms.size());
  timestampIntervals_ms.reserve(jsonTimestampIntervals_ms.size());
  for (auto& jsonBlockInterval_ms : jsonBlockIntervals_ms) {
    blockIntervals_ms.push_back(jsonBlockInterval_ms.asUInt());
  }
  for (auto& jsonTimestampInterval_ms : jsonTimestampIntervals_ms) {
    timestampIntervals_ms.push_back(jsonTimestampInterval_ms.asUInt());
  }
  this->blockIntervals_ms = blockIntervals_ms;
  this->timestampsIntervals_ms = timestampIntervals_ms;
  this->firstTimestamp_ms = differentialTimestampsContainer["first_timestamp_ms"].asUInt64();
}

DifferentialTimestampsContainer::DifferentialTimestampsContainer() {
  this->blockIntervals_ms = {};
  this->timestampsIntervals_ms = {};
  this->firstTimestamp_ms = 0;
}

uint64_t DifferentialTimestampsContainer::getFirstTimestamp() {
  return this->firstTimestamp_ms;
}

std::vector<uint32_t> DifferentialTimestampsContainer::getBlockIntervals() {
  return this->blockIntervals_ms;
}

std::vector<uint32_t> DifferentialTimestampsContainer::getTimestampsIntervals() {
  return this->timestampsIntervals_ms;
}

bool DifferentialTimestampsContainer::isEqual(DifferentialTimestampsContainer& differentialTimestamps) {
  return this->firstTimestamp_ms == differentialTimestamps.firstTimestamp_ms && this->blockIntervals_ms == differentialTimestamps.blockIntervals_ms &&
         this->timestampsIntervals_ms == differentialTimestamps.timestampsIntervals_ms;
}

uint32_t DifferentialTimestampsContainer::calculateFirstTimestampInBlock(uint32_t blockIdx) {
  if (this->blockIntervals_ms.size() <= blockIdx) {  // toDo : FOR-325
    throw std::invalid_argument("blockIdx is higher than number of blockIntervals");
  }
  uint64_t firstTimestamp = this->firstTimestamp_ms;
  std::vector<uint32_t> blockintervals_ms = this->blockIntervals_ms;
  for (size_t i = 1; i <= blockIdx; i++) {
    firstTimestamp += blockintervals_ms[i];
  }
  return firstTimestamp;
}

uint32_t DifferentialTimestampsContainer::calculateLastTimestampInBlock(uint32_t blockIdx,
                                                                        uint32_t firstTimestampInBlock_ms,
                                                                        DifferentialBlock differentialBlock) {
  return firstTimestampInBlock_ms + differentialBlock.getDifferentialValues().size() * this->timestampsIntervals_ms[blockIdx];
}

Json::Value DifferentialTimestampsContainer::toJson() {
  Json::Value differentialTimestampsContainer;
  Json::Value firstTimestamp_ms(Json::uintValue);
  Json::Value blockIntervals_ms(Json::arrayValue);
  Json::Value timestampsIntervals_ms(Json::arrayValue);
  for (auto& blockInterval_ms : this->blockIntervals_ms) {
    blockIntervals_ms.append(blockInterval_ms);
  }
  for (auto& timestampsInterval_ms : this->timestampsIntervals_ms) {
    timestampsIntervals_ms.append(timestampsInterval_ms);
  }
  firstTimestamp_ms = this->firstTimestamp_ms;
  differentialTimestampsContainer["first_timestamp_ms"] = firstTimestamp_ms;
  differentialTimestampsContainer["block_intervals_ms"] = blockIntervals_ms;
  differentialTimestampsContainer["timestamps_intervals_ms"] = timestampsIntervals_ms;
  return differentialTimestampsContainer;
}

void DifferentialTimestampsContainer::serialize(ProtobufDifferentialTimestampContainer* protobufDifferentialTimestampContainer) {
  if (protobufDifferentialTimestampContainer == nullptr) {
    throw std::invalid_argument("Error in serialize: protobufDifferentialTimestampContainer is a null pointer");
  }
  for (auto& blockInterval_ms : this->blockIntervals_ms) {
    protobufDifferentialTimestampContainer->add_block_intervals_ms(blockInterval_ms);
  }
  for (auto& timestampsInterval_ms : this->timestampsIntervals_ms) {
    protobufDifferentialTimestampContainer->add_timestamps_intervals_ms(timestampsInterval_ms);
  }
  protobufDifferentialTimestampContainer->set_first_timestamp_ms(this->firstTimestamp_ms);
}

void DifferentialTimestampsContainer::deserialize(const ProtobufDifferentialTimestampContainer& protobufDifferentialTimestampContainer) {
  this->firstTimestamp_ms = protobufDifferentialTimestampContainer.first_timestamp_ms();
  for (auto& protobufBlockInterval : protobufDifferentialTimestampContainer.block_intervals_ms()) {
    this->blockIntervals_ms.push_back(protobufBlockInterval);
  }
  for (auto& protobufTimestampsInterval : protobufDifferentialTimestampContainer.timestamps_intervals_ms()) {
    this->timestampsIntervals_ms.push_back(protobufTimestampsInterval);
  }
}
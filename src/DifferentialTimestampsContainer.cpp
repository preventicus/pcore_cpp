/*

Created by Jakob Glueck, Steve Merschel 2023

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

#include <utility>

DifferentialTimestampsContainer::DifferentialTimestampsContainer(UnixTimestamp firstUnixTimestamp_ms,
                                                                 BlockDifferences blockDifferences_ms,
                                                                 TimestampsDifferences timestampsDifferences_ms)
    : firstUnixTimestamp_ms(firstUnixTimestamp_ms),
      blockDifferences_ms(std::move(blockDifferences_ms)),
      timestampsDifferences_ms(std::move(timestampsDifferences_ms)) {}

DifferentialTimestampsContainer::DifferentialTimestampsContainer(const ProtobufDifferentialTimestampContainer& protobufDifferentialTimestampContainer)
    : firstUnixTimestamp_ms(protobufDifferentialTimestampContainer.first_unix_timestamp_ms()),
      blockDifferences_ms([&]() {
        auto protobufBlockDifferences_ms = protobufDifferentialTimestampContainer.block_differences_ms();
        BlockDifferences blockDifferences_ms = {};
        blockDifferences_ms.reserve(protobufBlockDifferences_ms.size());
        for (auto& protobufBlockDifference_ms : protobufBlockDifferences_ms) {
          blockDifferences_ms.push_back(protobufBlockDifference_ms);
        }
        return blockDifferences_ms;
      }()),
      timestampsDifferences_ms([&]() {
        auto protoBufTimestampsDifferences_ms = protobufDifferentialTimestampContainer.timestamps_differences_ms();
        TimestampsDifferences timestampsDifferences_ms = {};
        timestampsDifferences_ms.reserve(protoBufTimestampsDifferences_ms.size());
        for (auto& protobufTimestampsDifference_ms : protoBufTimestampsDifferences_ms) {
          timestampsDifferences_ms.push_back(protobufTimestampsDifference_ms);
        }
        return timestampsDifferences_ms;
      }()) {}

DifferentialTimestampsContainer::DifferentialTimestampsContainer(const DifferentialTimestampsContainerJson& differentialTimestampsContainerJson)
    : firstUnixTimestamp_ms([&]() {
        if (differentialTimestampsContainerJson["first_unix_timestamp_ms"].asInt64() < 0) {
          throw std::invalid_argument("firstUnixTimestamp_ms is negative in json");
        }
        return differentialTimestampsContainerJson["first_unix_timestamp_ms"].asUInt64();
      }()),
      blockDifferences_ms([&]() {
        BlockDifferencesJson blockDifferencesJson = differentialTimestampsContainerJson["block_differences_ms"];
        BlockDifferences blockDifferences_ms = {};
        blockDifferences_ms.reserve(blockDifferencesJson.size());
        for (auto& blockDifferenceJson : blockDifferencesJson) {
          blockDifferences_ms.emplace_back(blockDifferenceJson.asUInt());
        }
        return blockDifferences_ms;
      }()),
      timestampsDifferences_ms([&]() {
        TimestampsDifferencesJson timestampsDifferencesJson = differentialTimestampsContainerJson["timestamps_differences_ms"];
        TimestampsDifferences timestampsDifferences_ms = {};
        timestampsDifferences_ms.reserve(timestampsDifferencesJson.size());
        for (auto& timestampsDifferenceJson : timestampsDifferencesJson) {
          timestampsDifferences_ms.emplace_back(timestampsDifferenceJson.asUInt());
        }
        return timestampsDifferences_ms;
      }()) {}

DifferentialTimestampsContainer::DifferentialTimestampsContainer()
    : firstUnixTimestamp_ms(0), blockDifferences_ms({}), timestampsDifferences_ms({}) {}

UnixTimestamp DifferentialTimestampsContainer::getFirstUnixTimestamp_ms() const {
  return this->firstUnixTimestamp_ms;
}

BlockDifferences DifferentialTimestampsContainer::getBlockDifferences_ms() const {
  return this->blockDifferences_ms;
}

TimestampsDifferences DifferentialTimestampsContainer::getTimestampsDifferences_ms() const {
  return this->timestampsDifferences_ms;
}

bool DifferentialTimestampsContainer::operator==(const DifferentialTimestampsContainer& differentialTimestampsContainer) const {
  return this->firstUnixTimestamp_ms == differentialTimestampsContainer.firstUnixTimestamp_ms &&
         this->blockDifferences_ms == differentialTimestampsContainer.blockDifferences_ms &&
         this->timestampsDifferences_ms == differentialTimestampsContainer.timestampsDifferences_ms;
}

bool DifferentialTimestampsContainer::operator!=(const DifferentialTimestampsContainer& differentialTimestampsContainer) const {
  return this->firstUnixTimestamp_ms != differentialTimestampsContainer.firstUnixTimestamp_ms ||
         this->blockDifferences_ms != differentialTimestampsContainer.blockDifferences_ms ||
         this->timestampsDifferences_ms != differentialTimestampsContainer.timestampsDifferences_ms;
}

UnixTimestamp DifferentialTimestampsContainer::calculateFirstUnixTimestampInBlock(const BlockIdx& blockIdx) const {
  if (this->blockDifferences_ms.size() <= blockIdx) {  // toDo : FOR-325
    throw std::invalid_argument("blockIdx is higher than number of blockDifferences");
  }
  UnixTimestamp firstUnixTimestampInBlock_ms = this->firstUnixTimestamp_ms;
  for (size_t i = 1; i <= blockIdx; i++) {
    firstUnixTimestampInBlock_ms += this->blockDifferences_ms[i];
  }
  return firstUnixTimestampInBlock_ms;
}

UnixTimestamp DifferentialTimestampsContainer::calculateLastUnixTimestampInBlock(const BlockIdx& blockIdx,
                                                                                 const UnixTimestamp firstUnixTimestampInBlock_ms,
                                                                                 const DifferentialBlock& lastDifferentialBlock) const {
  if (this->timestampsDifferences_ms.size() <= blockIdx) {
    throw std::invalid_argument("blockIdx is bigger than size of timestampsDifference");
  }
  return firstUnixTimestampInBlock_ms + lastDifferentialBlock.getDifferentialValues().size() * this->timestampsDifferences_ms[blockIdx];
}

DifferentialTimestampsContainerJson DifferentialTimestampsContainer::toJson() const {
  DifferentialTimestampsContainerJson differentialTimestampsContainerJson;
  UnixTimestampJson firstUnixTimestampJson(Json::uintValue);
  BlockDifferencesJson blockDifferencesJson(Json::arrayValue);
  TimestampsDifferencesJson timestampsDifferencesJson(Json::arrayValue);
  for (auto& blockDifference_ms : this->blockDifferences_ms) {
    blockDifferencesJson.append(blockDifference_ms);
  }
  for (auto& timestampsDifference : this->timestampsDifferences_ms) {
    timestampsDifferencesJson.append(timestampsDifference);
  }
  firstUnixTimestampJson = this->firstUnixTimestamp_ms;
  differentialTimestampsContainerJson["first_unix_timestamp_ms"] = firstUnixTimestampJson;
  differentialTimestampsContainerJson["block_differences_ms"] = blockDifferencesJson;
  differentialTimestampsContainerJson["timestamps_differences_ms"] = timestampsDifferencesJson;
  return differentialTimestampsContainerJson;
}

void DifferentialTimestampsContainer::serialize(ProtobufDifferentialTimestampContainer* protobufDifferentialTimestampContainer) const {
  if (protobufDifferentialTimestampContainer == nullptr) {
    throw std::invalid_argument("Error in serialize: protobufDifferentialTimestampContainer is a null pointer");
  }
  for (auto& blockDifference_ms : this->blockDifferences_ms) {
    protobufDifferentialTimestampContainer->add_block_differences_ms(blockDifference_ms);
  }
  for (auto& timestampsDifference_ms : this->timestampsDifferences_ms) {
    protobufDifferentialTimestampContainer->add_timestamps_differences_ms(timestampsDifference_ms);
  }
  protobufDifferentialTimestampContainer->set_first_unix_timestamp_ms(this->firstUnixTimestamp_ms);
}

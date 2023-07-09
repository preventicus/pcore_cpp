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

DifferentialTimestampsContainer::DifferentialTimestampsContainer(UnixTimestamp firstUnixTimestamp_ms,
                                                                 BlockIntervals& blockIntervals_ms,
                                                                 TimestampsIntervals& timestampsIntervals_ms)
    : firstUnixTimestamp_ms(firstUnixTimestamp_ms), blockIntervals_ms(blockIntervals_ms), timestampsIntervals_ms(timestampsIntervals_ms) {}

DifferentialTimestampsContainer::DifferentialTimestampsContainer(const ProtobufDifferentialTimestampContainer& protobufDifferentialTimestampContainer)
    : firstUnixTimestamp_ms(protobufDifferentialTimestampContainer.first_timestamp_ms()),
      blockIntervals_ms([&]() {
        auto protobufBlockIntervals_ms = protobufDifferentialTimestampContainer.block_intervals_ms();
        BlockIntervals blockIntervals_ms = {};
        blockIntervals_ms.reserve(protobufBlockIntervals_ms.size());
        for (auto& protobufBlockInterval_ms : protobufBlockIntervals_ms) {
          blockIntervals_ms.push_back(protobufBlockInterval_ms);
        }
        return blockIntervals_ms;
      }()),
      timestampsIntervals_ms([&]() {
        auto protoBufTimestampsIntervals_ms = protobufDifferentialTimestampContainer.timestamps_intervals_ms();
        TimestampsIntervals timestampsIntervals_ms = {};
        timestampsIntervals_ms.reserve(protoBufTimestampsIntervals_ms.size());
        for (auto& protobufTimestampsInterval_ms : protoBufTimestampsIntervals_ms) {
          timestampsIntervals_ms.push_back(protobufTimestampsInterval_ms);
        }
        return timestampsIntervals_ms;
      }()) {}

DifferentialTimestampsContainer::DifferentialTimestampsContainer(DifferentialTimestampsContainerJson& differentialTimestampsContainerJson)
    : firstUnixTimestamp_ms([&]() {
        if (differentialTimestampsContainerJson["first_timestamp_ms"].asInt64() < 0) {
          throw std::invalid_argument("firstUnixTimestamp_ms is negative in json");
        }
        return differentialTimestampsContainerJson["first_timestamp_ms"].asUInt64();
      }()),
      blockIntervals_ms([&]() {
        BlockIntervalsJson blockIntervalsJson = differentialTimestampsContainerJson["block_intervals_ms"];
        BlockIntervals blockIntervals_ms = {};
        blockIntervals_ms.reserve(blockIntervalsJson.size());
        for (auto& blockIntervalJson : blockIntervalsJson) {
          blockIntervals_ms.emplace_back(blockIntervalJson.asUInt());
        }
        return blockIntervals_ms;
      }()),
      timestampsIntervals_ms([&]() {
        TimestampsIntervalsJson timestampsIntervalsJson = differentialTimestampsContainerJson["timestamps_intervals_ms"];
        TimestampsIntervals timestampsIntervals_ms = {};
        timestampsIntervals_ms.reserve(timestampsIntervalsJson.size());
        for (auto& timestampsIntervalJson : timestampsIntervalsJson) {
          timestampsIntervals_ms.emplace_back(timestampsIntervalJson.asUInt());
        }
        return timestampsIntervals_ms;
      }()) {}

DifferentialTimestampsContainer::DifferentialTimestampsContainer() : firstUnixTimestamp_ms(0), blockIntervals_ms({}), timestampsIntervals_ms({}) {}

UnixTimestamp DifferentialTimestampsContainer::getFirstUnixTimestamp() const {
  return this->firstUnixTimestamp_ms;
}

BlockIntervals DifferentialTimestampsContainer::getBlockIntervals() const {
  return this->blockIntervals_ms;
}

TimestampsIntervals DifferentialTimestampsContainer::getTimestampsIntervals() const {
  return this->timestampsIntervals_ms;
}

bool DifferentialTimestampsContainer::operator==(const DifferentialTimestampsContainer& differentialTimestampsContainer) const {
  return this->firstUnixTimestamp_ms == differentialTimestampsContainer.firstUnixTimestamp_ms &&
         this->blockIntervals_ms == differentialTimestampsContainer.blockIntervals_ms &&
         this->timestampsIntervals_ms == differentialTimestampsContainer.timestampsIntervals_ms;
}

bool DifferentialTimestampsContainer::operator!=(const DifferentialTimestampsContainer& differentialTimestampsContainer) const {
  return this->firstUnixTimestamp_ms != differentialTimestampsContainer.firstUnixTimestamp_ms ||
         this->blockIntervals_ms != differentialTimestampsContainer.blockIntervals_ms ||
         this->timestampsIntervals_ms != differentialTimestampsContainer.timestampsIntervals_ms;
}

UnixTimestamp DifferentialTimestampsContainer::calculateFirstUnixTimestampInBlock(const BlockIdx& blockIdx) const {
  if (this->blockIntervals_ms.size() <= blockIdx) {  // toDo : FOR-325
    throw std::invalid_argument("blockIdx is higher than number of blockIntervals");
  }
  UnixTimestamp firstUnixTimestampInBlock_ms = this->firstUnixTimestamp_ms;
  for (size_t i = 1; i <= blockIdx; i++) {
    firstUnixTimestampInBlock_ms += this->blockIntervals_ms[i];
  }
  return firstUnixTimestampInBlock_ms;
}

UnixTimestamp DifferentialTimestampsContainer::calculateLastUnixTimestampInBlock(const BlockIdx& blockIdx,
                                                                                 const UnixTimestamp firstUnixTimestampInBlock_ms,
                                                                                 const DifferentialBlock& lastDifferentialBlock) const {
  if (this->timestampsIntervals_ms.size() <= blockIdx) {
    throw std::invalid_argument("blockIdx is bigger than size of timestampsInterval");
  }
  return firstUnixTimestampInBlock_ms + lastDifferentialBlock.getDifferentialValues().size() * this->timestampsIntervals_ms[blockIdx];
}

DifferentialTimestampsContainerJson DifferentialTimestampsContainer::toJson() const {
  DifferentialTimestampsContainerJson differentialTimestampsContainerJson;
  UnixTimestampJson firstUnixTimestampJson(Json::uintValue);
  BlockIntervalsJson blockIntervalsJson(Json::arrayValue);
  TimestampsIntervalsJson timestampsIntervalsJson(Json::arrayValue);
  for (auto& blockInterval_ms : this->blockIntervals_ms) {
    blockIntervalsJson.append(blockInterval_ms);
  }
  for (auto& timestampsInterval : this->timestampsIntervals_ms) {
    timestampsIntervalsJson.append(timestampsInterval);
  }
  firstUnixTimestampJson = this->firstUnixTimestamp_ms;
  differentialTimestampsContainerJson["first_timestamp_ms"] = firstUnixTimestampJson;
  differentialTimestampsContainerJson["block_intervals_ms"] = blockIntervalsJson;
  differentialTimestampsContainerJson["timestamps_intervals_ms"] = timestampsIntervalsJson;
  return differentialTimestampsContainerJson;
}

void DifferentialTimestampsContainer::serialize(ProtobufDifferentialTimestampContainer* protobufDifferentialTimestampContainer) const {
  if (protobufDifferentialTimestampContainer == nullptr) {
    throw std::invalid_argument("Error in serialize: protobufDifferentialTimestampContainer is a null pointer");
  }
  for (auto& blockInterval_ms : this->blockIntervals_ms) {
    protobufDifferentialTimestampContainer->add_block_intervals_ms(blockInterval_ms);
  }
  for (auto& timestampsInterval_ms : this->timestampsIntervals_ms) {
    protobufDifferentialTimestampContainer->add_timestamps_intervals_ms(timestampsInterval_ms);
  }
  protobufDifferentialTimestampContainer->set_first_timestamp_ms(this->firstUnixTimestamp_ms);
}

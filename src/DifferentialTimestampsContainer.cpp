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
#include "PcoreJson.h"
#include "PcoreProtobuf.h"

DifferentialTimestampsContainer::DifferentialTimestampsContainer(UnixTimestamp firstUnixTimestamp_ms,
                                                                 BlockDifferences blockDifferences_ms,
                                                                 TimestampsDifferences timestampsDifferences_ms)
    : firstUnixTimestamp_ms(firstUnixTimestamp_ms),
      blockDifferences_ms(std::move(blockDifferences_ms)),
      timestampsDifferences_ms(std::move(timestampsDifferences_ms)) {}

DifferentialTimestampsContainer::DifferentialTimestampsContainer(
    const DifferentialTimestampContainerProtobuf& differentialTimestampsContainerProtobuf)
    : firstUnixTimestamp_ms(differentialTimestampsContainerProtobuf.first_unix_timestamp_ms()),
      blockDifferences_ms(PcoreProtobuf::Convert::ProtoBuf2Vector<TimeDifference>(differentialTimestampsContainerProtobuf.block_differences_ms())),
      timestampsDifferences_ms(
          PcoreProtobuf::Convert::ProtoBuf2Vector<TimeDifference>(differentialTimestampsContainerProtobuf.timestamps_differences_ms())) {}

DifferentialTimestampsContainer::DifferentialTimestampsContainer(const DifferentialTimestampsContainerJson& differentialTimestampsContainerJson)
    : firstUnixTimestamp_ms([&]() {
        if (differentialTimestampsContainerJson[PcoreJson::Key::first_unix_timestamp_ms].asInt64() < 0) {
          throw std::invalid_argument("firstUnixTimestamp_ms is negative in json");
        }
        return differentialTimestampsContainerJson[PcoreJson::Key::first_unix_timestamp_ms].asUInt64();
      }()),
      blockDifferences_ms(PcoreJson::Convert::Json2Vector<TimeDifference>(differentialTimestampsContainerJson, PcoreJson::Key::block_differences_ms)),
      timestampsDifferences_ms(
          PcoreJson::Convert::Json2Vector<TimeDifference>(differentialTimestampsContainerJson, PcoreJson::Key::timestamps_differences_ms)) {}

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
  UnixTimestampJson firstUnixTimestampJson(Json::uintValue);
  firstUnixTimestampJson = this->firstUnixTimestamp_ms;
  DifferentialTimestampsContainerJson differentialTimestampsContainerJson;
  differentialTimestampsContainerJson[PcoreJson::Key::first_unix_timestamp_ms] = firstUnixTimestampJson;
  differentialTimestampsContainerJson[PcoreJson::Key::block_differences_ms] = PcoreJson::Convert::Vector2Json(this->blockDifferences_ms);
  ;
  differentialTimestampsContainerJson[PcoreJson::Key::timestamps_differences_ms] = PcoreJson::Convert::Vector2Json(this->timestampsDifferences_ms);
  return differentialTimestampsContainerJson;
}

void DifferentialTimestampsContainer::serialize(DifferentialTimestampContainerProtobuf* differentialTimestampsContainerProtobuf) const {
  if (differentialTimestampsContainerProtobuf == nullptr) {
    throw std::invalid_argument("Error in serialize: differentialTimestampsContainerProtobuf is a null pointer");
  }
  for (auto& blockDifference_ms : this->blockDifferences_ms) {
    differentialTimestampsContainerProtobuf->add_block_differences_ms(blockDifference_ms);
  }
  for (auto& timestampsDifference_ms : this->timestampsDifferences_ms) {
    differentialTimestampsContainerProtobuf->add_timestamps_differences_ms(timestampsDifference_ms);
  }
  differentialTimestampsContainerProtobuf->set_first_unix_timestamp_ms(this->firstUnixTimestamp_ms);
}

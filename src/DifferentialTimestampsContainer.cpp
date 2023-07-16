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

DifferentialTimestampsContainer::DifferentialTimestampsContainer(UnixTimestamp firstUnixTimestampInMs,
                                                                 BlocksDifferences blocksDifferencesInMs,
                                                                 TimestampsDifferences timestampsDifferencesInMs)
    : firstUnixTimestampInMs(firstUnixTimestampInMs),
      blocksDifferencesInMs(std::move(blocksDifferencesInMs)),
      timestampsDifferencesInMs(std::move(timestampsDifferencesInMs)) {}

DifferentialTimestampsContainer::DifferentialTimestampsContainer(
    const DifferentialTimestampContainerProtobuf& differentialTimestampsContainerProtobuf)
    : firstUnixTimestampInMs(differentialTimestampsContainerProtobuf.first_unix_timestamp_ms()),
      blocksDifferencesInMs(
          PcoreProtobuf::Convert::protobufToVector<TimeDifference>(differentialTimestampsContainerProtobuf.blocks_differences_ms())),
      timestampsDifferencesInMs(
          PcoreProtobuf::Convert::protobufToVector<TimeDifference>(differentialTimestampsContainerProtobuf.timestamps_differences_ms())) {}

DifferentialTimestampsContainer::DifferentialTimestampsContainer(const DifferentialTimestampsContainerJson& differentialTimestampsContainerJson)
    : firstUnixTimestampInMs([&]() {
        if (differentialTimestampsContainerJson[PcoreJson::Key::first_unix_timestamp_ms].asInt64() < 0) {
          throw std::invalid_argument("firstUnixTimestampInMs is negative in json");
        }
        return differentialTimestampsContainerJson[PcoreJson::Key::first_unix_timestamp_ms].asUInt64();
      }()),
      blocksDifferencesInMs(
          PcoreJson::Convert::jsonToVector<TimeDifference>(differentialTimestampsContainerJson, PcoreJson::Key::blocks_differences_ms)),
      timestampsDifferencesInMs(
          PcoreJson::Convert::jsonToVector<TimeDifference>(differentialTimestampsContainerJson, PcoreJson::Key::timestamps_differences_ms)) {}

DifferentialTimestampsContainer::DifferentialTimestampsContainer()
    : firstUnixTimestampInMs(0), blocksDifferencesInMs({}), timestampsDifferencesInMs({}) {}

UnixTimestamp DifferentialTimestampsContainer::getFirstUnixTimestampInMs() const {
  return this->firstUnixTimestampInMs;
}

UnixTimestamp DifferentialTimestampsContainer::getLastUnixTimestampInMs(UnixTimestamp firstUnixTimestampInLastBlock,
                                                                        size_t numberOfElementsInLastBlock) const {
  return firstUnixTimestampInLastBlock + this->timestampsDifferencesInMs.back() * (numberOfElementsInLastBlock - 1);
}

BlocksDifferences DifferentialTimestampsContainer::getBlocksDifferencesInMs() const {
  return this->blocksDifferencesInMs;
}

TimestampsDifferences DifferentialTimestampsContainer::getTimestampsDifferencesInMs() const {
  return this->timestampsDifferencesInMs;
}

bool DifferentialTimestampsContainer::operator==(const IPCore<DifferentialTimestampContainerProtobuf>& differentialTimestampsContainer) const {
  if (const auto* derived = dynamic_cast<const DifferentialTimestampsContainer*>(&differentialTimestampsContainer)) {
    return this->firstUnixTimestampInMs == derived->firstUnixTimestampInMs && this->blocksDifferencesInMs == derived->blocksDifferencesInMs &&
           this->timestampsDifferencesInMs == derived->timestampsDifferencesInMs;
  }
  return false;
}

bool DifferentialTimestampsContainer::operator!=(const IPCore<DifferentialTimestampContainerProtobuf>& differentialTimestampsContainer) const {
  return !(*this == differentialTimestampsContainer);
}

UnixTimestamp DifferentialTimestampsContainer::calculateFirstUnixTimestampInBlock(const BlockIdx& blockIdx) const {
  if (this->blocksDifferencesInMs.size() <= blockIdx) {  // toDo : FOR-325
    throw std::invalid_argument("blockIdx is higher than number of blocksDifferences");
  }
  UnixTimestamp firstUnixTimestampInBlockInMs = this->firstUnixTimestampInMs;
  for (size_t i = 1; i <= blockIdx; i++) {
    firstUnixTimestampInBlockInMs += this->blocksDifferencesInMs[i];
  }
  return firstUnixTimestampInBlockInMs;
}

UnixTimestamp DifferentialTimestampsContainer::calculateLastUnixTimestampInBlock(const BlockIdx& blockIdx,
                                                                                 const UnixTimestamp firstUnixTimestampInBlockInMs,
                                                                                 const DifferentialBlock& lastDifferentialBlock) const {
  if (this->timestampsDifferencesInMs.size() <= blockIdx) {
    throw std::invalid_argument("blockIdx is bigger than size of timestampsDifference");
  }
  return firstUnixTimestampInBlockInMs + lastDifferentialBlock.getDifferentialValues().size() * this->timestampsDifferencesInMs[blockIdx];
}

DifferentialTimestampsContainerJson DifferentialTimestampsContainer::toJson() const {
  DifferentialTimestampsContainerJson differentialTimestampsContainerJson;
  if (!this->isSet()) {
    return differentialTimestampsContainerJson;
  }
  UnixTimestampJson firstUnixTimestampJson(Json::uintValue);
  firstUnixTimestampJson = this->firstUnixTimestampInMs;
  differentialTimestampsContainerJson[PcoreJson::Key::first_unix_timestamp_ms] = firstUnixTimestampJson;
  differentialTimestampsContainerJson[PcoreJson::Key::blocks_differences_ms] = PcoreJson::Convert::vectorToJson(this->blocksDifferencesInMs);
  differentialTimestampsContainerJson[PcoreJson::Key::timestamps_differences_ms] = PcoreJson::Convert::vectorToJson(this->timestampsDifferencesInMs);
  return differentialTimestampsContainerJson;
}

void DifferentialTimestampsContainer::serialize(DifferentialTimestampContainerProtobuf* differentialTimestampsContainerProtobuf) const {
  if (differentialTimestampsContainerProtobuf == nullptr) {
    throw std::invalid_argument("Error in serialize: differentialTimestampsContainerProtobuf is a null pointer");
  }
  if (!this->isSet()) {
    return;
  }
  for (const auto& blocksDifferenceInMs : this->blocksDifferencesInMs) {
    differentialTimestampsContainerProtobuf->add_blocks_differences_ms(blocksDifferenceInMs);
  }
  for (const auto& timestampsDifferenceInMs : this->timestampsDifferencesInMs) {
    differentialTimestampsContainerProtobuf->add_timestamps_differences_ms(timestampsDifferenceInMs);
  }
  differentialTimestampsContainerProtobuf->set_first_unix_timestamp_ms(this->firstUnixTimestampInMs);
}

void DifferentialTimestampsContainer::switchDataForm() {
  throw std::runtime_error("should not be called");
}

bool DifferentialTimestampsContainer::isSet() const {
  // clang-format off
  return this->firstUnixTimestampInMs != 0
     || !this->blocksDifferencesInMs.empty()
     || !this->timestampsDifferencesInMs.empty();
  // clang-format on
}

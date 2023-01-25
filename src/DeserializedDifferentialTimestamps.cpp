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
#include "DeserializedDifferentialTimestamps.h"

void DeserializedDifferentialTimestamps::setFirstTimestamp(uint64_t firstTimestamp_ms) {
  this->firstTimestamp_ms = firstTimestamp_ms;
}

void DeserializedDifferentialTimestamps::setBlockIntervals(std::vector<uint32_t> blockIntervals_ms) {
  this->blockIntervals_ms = blockIntervals_ms;
}

void DeserializedDifferentialTimestamps::setTimestampsIntervals(std::vector<uint32_t> timestampsIntervals_ms) {
  this->timestampsIntervals_ms = timestampsIntervals_ms;
}

uint64_t DeserializedDifferentialTimestamps::getFirstTimestamp() {
  return this->firstTimestamp_ms;
}

std::vector<uint32_t> DeserializedDifferentialTimestamps::getBlockIntervals() {
  return this->blockIntervals_ms;
}

std::vector<uint32_t> DeserializedDifferentialTimestamps::getTimestampsIntervals() {
  return this->timestampsIntervals_ms;
}

bool DeserializedDifferentialTimestamps::isEqual(DeserializedDifferentialTimestamps& timestamps) {
  return this->firstTimestamp_ms == timestamps.firstTimestamp_ms && this->blockIntervals_ms == timestamps.blockIntervals_ms &&
         this->timestampsIntervals_ms == timestamps.timestampsIntervals_ms;
}

uint32_t DeserializedDifferentialTimestamps::calculateFirstTimestampInBlock(uint32_t blockIdx) {
  if (this->blockIntervals_ms.size() <= blockIdx) {  // // TODO FOR-333
    throw std::invalid_argument("blockIdx is higher than number of blockIntervals");
  }
  int const firstTimestamp_ms = this->firstTimestamp_ms;
  std::vector<uint32_t> const blockIntervals_ms = this->blockIntervals_ms;
  long firstTimestampInBlock_ms = firstTimestamp_ms;
  for (size_t i = 1; i <= blockIdx; i++) {
    firstTimestampInBlock_ms += blockIntervals_ms[i];
  }
  return firstTimestampInBlock_ms;
}

uint32_t DeserializedDifferentialTimestamps::calculateLastTimestampInBlock(uint32_t blockIdx,
                                                                           uint32_t firstTimestampInBlock_ms,
                                                                           DeserializedDifferentialBlock deserializedDifferentialBlock) {
  return firstTimestampInBlock_ms + deserializedDifferentialBlock.getDiffValues().size() * this->timestampsIntervals_ms[blockIdx];
}

SerializedTimestampContainer DeserializedDifferentialTimestamps::serialize() {
  SerializedTimestampContainer serializedTimestampContainer;
  for (size_t i = 0; i < this->blockIntervals_ms.size(); i++) {
    serializedTimestampContainer.add_block_intervals(this->blockIntervals_ms[i]);
  }
  for (size_t j = 0; j < this->timestampsIntervals_ms.size(); j++) {
    serializedTimestampContainer.add_timestamps_intervals(this->timestampsIntervals_ms[j]);
  }
  serializedTimestampContainer.set_first_timestamp(this->firstTimestamp_ms);

  return serializedTimestampContainer;
}

void DeserializedDifferentialTimestamps::deserialize(SerializedTimestampContainer& serializedTimestampContainer) {
  this->firstTimestamp_ms = serializedTimestampContainer.first_timestamp();
  for (size_t i = 0; i < serializedTimestampContainer.block_intervals_size(); i++) {
    this->blockIntervals_ms.push_back(serializedTimestampContainer.block_intervals(i));
  }
  for (size_t j = 0; j < serializedTimestampContainer.timestamps_intervals_size(); j++) {
    this->timestampsIntervals_ms.push_back(serializedTimestampContainer.timestamps_intervals(j));
  }
}
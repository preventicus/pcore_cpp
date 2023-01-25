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

void DeserializedDifferentialTimestamps::setFirstTimestamp(uint64_t first_timestamp_ms) {
  this->first_timestamp_ms = first_timestamp_ms;
}

void DeserializedDifferentialTimestamps::setBlockIntervals(std::vector<uint32_t> block_intervals_ms) {
  this->block_intervals_ms = block_intervals_ms;
}

void DeserializedDifferentialTimestamps::setTimestampsIntervals(std::vector<uint32_t> timestamps_intervals_ms) {
  this->timestamps_intervals_ms = timestamps_intervals_ms;
}

uint64_t DeserializedDifferentialTimestamps::getFirstTimestamp() {
  return this->first_timestamp_ms;
}

std::vector<uint32_t> DeserializedDifferentialTimestamps::getBlockIntervals() {
  return this->block_intervals_ms;
}

std::vector<uint32_t> DeserializedDifferentialTimestamps::getTimestampsIntervals() {
  return this->timestamps_intervals_ms;
}

bool DeserializedDifferentialTimestamps::isEqual(DeserializedDifferentialTimestamps& timestamps) {
  return this->first_timestamp_ms == timestamps.first_timestamp_ms && this->block_intervals_ms == timestamps.block_intervals_ms &&
         this->timestamps_intervals_ms == timestamps.timestamps_intervals_ms;
}

uint32_t DeserializedDifferentialTimestamps::calculateFirstTimestampInBlock(uint32_t blockIdx) {
  if (this->block_intervals_ms.size() <= blockIdx) {  // // TODO FOR-333
    throw std::invalid_argument("blockIdx is higher than number of block_intervals");
  }
  int const first_timestamp = this->first_timestamp_ms;
  std::vector<uint32_t> const block_intervals = this->block_intervals_ms;
  long firstTimestampInBlock = first_timestamp;
  for (size_t i = 1; i <= blockIdx; i++) {
    firstTimestampInBlock += block_intervals[i];
  }
  return firstTimestampInBlock;
}

uint32_t DeserializedDifferentialTimestamps::calculateLastTimestampInBlock(uint32_t blockIdx,
                                                                           uint32_t firstTimestampInBlock,
                                                                           DeserializedDifferentialBlock deserializedDifferentialBlock) {
  return firstTimestampInBlock + deserializedDifferentialBlock.getDiffValues().size() * this->timestamps_intervals_ms[blockIdx];
}

SerializedTimestampContainer DeserializedDifferentialTimestamps::serialize() {
  SerializedTimestampContainer serializedTimestampContainer;
  for (size_t i = 0; i < this->block_intervals_ms.size(); i++) {
    serializedTimestampContainer.add_block_intervals(this->block_intervals_ms[i]);
  }
  for (size_t j = 0; j < this->timestamps_intervals_ms.size(); j++) {
    serializedTimestampContainer.add_timestamps_intervals(this->timestamps_intervals_ms[j]);
  }
  serializedTimestampContainer.set_first_timestamp(this->first_timestamp_ms);

  return serializedTimestampContainer;
}

void DeserializedDifferentialTimestamps::deserialize(SerializedTimestampContainer& serializedTimestampContainer) {
  this->first_timestamp_ms = serializedTimestampContainer.first_timestamp();
  for (size_t i = 0; i < serializedTimestampContainer.block_intervals_size(); i++) {
    this->block_intervals_ms.push_back(serializedTimestampContainer.block_intervals(i));
  }
  for (size_t j = 0; j < serializedTimestampContainer.timestamps_intervals_size(); j++) {
    this->timestamps_intervals_ms.push_back(serializedTimestampContainer.timestamps_intervals(j));
  }
}
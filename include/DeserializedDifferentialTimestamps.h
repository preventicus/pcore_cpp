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
#include <iostream>
#include <stdexcept>
#include <vector>
#include "DeserializedDifferntialBlock.h"
#include "protobuf/pcore_external.pb.h"
using SerializedTimestampContainer =
    com::preventicus::pcore::Raw_Sensor_TimestampsContainer;

class DeserializedDifferentialTimestamps {
 public:
  void setFirstTimestamp(uint64_t& first_timestamp_ms);
  void setBlockIntervals(std::vector<uint32_t>& block_intervals_ms);
  void setTimestampsIntervals(std::vector<uint32_t>& timestamps_intervals_ms);
  uint64_t getFirstTimestamp();
  std::vector<uint32_t> getBlockIntervals();
  std::vector<uint32_t> getTimestampsIntervals();
  bool isEqual(DeserializedDifferentialTimestamps& timestamps);
  uint32_t calculateFirstTimestampInBlock(uint32_t blockIdx);
  uint32_t calculateLastTimestampInBlock(
      uint32_t blockIdx,
      uint32_t firstTimestampInBlock,
      DeserializedDifferentialBlock deserializedDifferentialBlock);
  SerializedTimestampContainer serialize();
  void deserialize(
      SerializedTimestampContainer& serializedDifferentialTimestamps);

 private:
  uint64_t first_timestamp_ms;
  std::vector<uint32_t> block_intervals_ms;
  std::vector<uint32_t> timestamps_intervals_ms;
  DeserializedDifferentialBlock deserializedDifferentialBlock;
};
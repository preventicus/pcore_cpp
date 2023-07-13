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

#pragma once
#include <vector>
#include "BlockIdx.h"
#include "DifferentialBlock.h"
#include "IPCore.h"
#include "UnixTimestamp.h"
#include "protobuf/pcore_raw.pb.h"

using namespace PCore;

using DifferentialTimestampContainerProtobuf = com::preventicus::pcore::Raw_Sensor_DifferentialTimestampsContainer;
using TimeDifference = uint32_t;
using BlockDifferences = std::vector<TimeDifference>;
using TimestampsDifferences = std::vector<TimeDifference>;
using DifferentialTimestampsContainerJson = Json::Value;

using UnixTimestampJson = Json::Value;
using BlockDifferencesJson = Json::Value;
using TimestampsDifferencesJson = Json::Value;

namespace PCore {
class DifferentialTimestampsContainer final : public IPCore<DifferentialTimestampContainerProtobuf> {
 public:
  explicit DifferentialTimestampsContainer(UnixTimestamp firstUnixTimestamp_ms,
                                           BlockDifferences blockDifferences_ms,
                                           TimestampsDifferences timestampsDifferences_ms);
  explicit DifferentialTimestampsContainer(const DifferentialTimestampContainerProtobuf& differentialTimestampsContainerProtobuf);
  explicit DifferentialTimestampsContainer(const DifferentialTimestampsContainerJson& differentialTimestampsContainerJson);
  explicit DifferentialTimestampsContainer();

  [[nodiscard]] UnixTimestamp getFirstUnixTimestamp_ms() const;
  [[nodiscard]] UnixTimestamp getLastUnixTimestamp_ms(UnixTimestamp firstUnixTimestampInLastBlock, size_t numberOfElementsInLastBlock) const;
  [[nodiscard]] BlockDifferences getBlockDifferences_ms() const;
  [[nodiscard]] TimestampsDifferences getTimestampsDifferences_ms() const;

  [[nodiscard]] DifferentialTimestampsContainerJson toJson() const final;
  [[nodiscard]] UnixTimestamp calculateFirstUnixTimestampInBlock(const BlockIdx& blockIdx) const;
  [[nodiscard]] UnixTimestamp calculateLastUnixTimestampInBlock(const BlockIdx& blockIdx,
                                                                UnixTimestamp firstUnixTimestampInBlock_ms,
                                                                const DifferentialBlock& lastDifferentialBlock) const;

  void serialize(DifferentialTimestampContainerProtobuf* differentialTimestampsContainerProtobuf) const final;
  void switchDataForm() final;
  [[nodiscard]] bool isSet() const final;

  bool operator==(const IPCore<DifferentialTimestampContainerProtobuf>& differentialTimestampsContainer) const final;
  bool operator!=(const IPCore<DifferentialTimestampContainerProtobuf>& differentialTimestampsContainer) const final;

 private:
  UnixTimestamp firstUnixTimestamp_ms;
  BlockDifferences blockDifferences_ms;
  TimestampsDifferences timestampsDifferences_ms;
};
}  // namespace PCore
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

#pragma once
#include "DifferentialTimestampsContainer.h"

class DifferentialTimestampsContainerExampleFactory {
 public:
  static uint64_t normalFirstTimestamp_ms();
  static uint64_t zeroFirstTimestamp_ms();
  static uint64_t expectedFirstTimestamps();
  static uint64_t lastTimestamp();
  static uint64_t duration();

  static std::vector<uint32_t> normalBlockIntervals_ms();
  static std::vector<uint32_t> zeroBlockIntervals_ms();
  static std::vector<uint32_t> normalBlockIntervals_msWithOneUnixInLastBlock();
  static std::vector<uint32_t> emptyBlockIntervals_ms();
  static std::vector<uint32_t> expectedBlockInterval();

  static std::vector<uint32_t> normalTimestampsIntervals_ms();
  static std::vector<uint32_t> normalTimestampsIntervals_msWithOneUnixInLastBlock();
  static std::vector<uint32_t> normalTimestampsIntervals_msWithEqualDifferences();
  static std::vector<uint32_t> zeroTimestampsIntervals_ms();
  static std::vector<uint32_t> emptyTimestampsIntervals_ms();
  static std::vector<uint32_t> expectedTimestampInterval();

  static DifferentialTimestampsContainer differentialTimestampsWithNormalTimestamps();
  static DifferentialTimestampsContainer differentialTimestampsWith0Timestamps();
  static DifferentialTimestampsContainer differentialTimestampsWithEmptyTimestamps();
  static DifferentialTimestampsContainer normalDifferentialTimestamps();
  static DifferentialTimestampsContainer differentiaJsonDataTimestampsContainerPpg();
  static DifferentialTimestampsContainer differentiaJsonDataTimestampsContainerAcc();
};
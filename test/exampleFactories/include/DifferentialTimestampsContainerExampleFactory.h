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

#include "Sensor.h"

class DifferentialTimestampsContainerExampleFactory {
 public:
  static UnixTimestamp normalFirstUnixTimestamp_ms();
  static UnixTimestamp zeroFirstUnixTimestamp_ms();
  static UnixTimestamp expectedFirstUnixTimestamps();
  static UnixTimestamp lastUnixTimestamp_ms();

  static Duration duration();

  static BlockIntervals normalBlockIntervals_ms();
  static BlockIntervals zeroBlockIntervals_ms();
  static BlockIntervals normalBlockIntervals_msWithOneUnixInLastBlock();
  static BlockIntervals emptyBlockIntervals_ms();
  static BlockIntervals expectedBlockInterval();

  static TimestampsIntervals normalTimestampsIntervals_ms();
  static TimestampsIntervals normalTimestampsIntervals_msWithOneUnixInLastBlock();
  static TimestampsIntervals normalTimestampsIntervals_msWithEqualDifferences();
  static TimestampsIntervals zeroTimestampsIntervals_ms();
  static TimestampsIntervals emptyTimestampsIntervals_ms();
  static TimestampsIntervals expectedTimestampInterval();

  static DifferentialTimestampsContainer differentialTimestampsWithNormalTimestamps();
  static DifferentialTimestampsContainer differentialTimestampsWith0Timestamps();
  static DifferentialTimestampsContainer differentialTimestampsWithEmptyTimestamps();
  static DifferentialTimestampsContainer normalDifferentialTimestamps();
  static DifferentialTimestampsContainer differentiaJsonDataTimestampsContainerPpg();
  static DifferentialTimestampsContainer differentiaJsonDataTimestampsContainerAcc();
};
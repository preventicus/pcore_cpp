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

#include "DifferentialTimestampsContainerExampleFactory.h"
#include "IntervalsExampleFactory.h"
#include "UnixTimestampsExampleFactory.h"

DifferentialTimestampsContainer DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithThreeBlocks() {
  auto firstUnixTimestamp_ms = UnixTimestampsExampleFactory::firstTimestamp_ms();
  auto blockIntervals = IntervalsExampleFactory::blockIntervalsWithThreeMixedIntervals();
  auto timestampsIntervals = IntervalsExampleFactory::timestampsIntervalsWithThreeZeroIntervals();

  return DifferentialTimestampsContainer(firstUnixTimestamp_ms, blockIntervals, timestampsIntervals);
}

DifferentialTimestampsContainer DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerEmpty() {
  return DifferentialTimestampsContainer();
}

DifferentialTimestampsContainer DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithTwoBlocks() {
  auto firstUnixTimestamp_ms = UnixTimestampsExampleFactory::firstTimestamp_ms();
  auto blockIntervals = IntervalsExampleFactory::blockIntervalsWithTwoMixedIntervals();
  auto timestampsIntervals = IntervalsExampleFactory::timestampsIntervalsWithTwoMixedIntervals();
  return DifferentialTimestampsContainer(firstUnixTimestamp_ms, blockIntervals, timestampsIntervals);
}

DifferentialTimestampsContainer DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithBigBlocks() {
  auto firstUnixTimestamp_ms = UnixTimestampsExampleFactory::firstTimestamp_ms();
  auto blockIntervals = IntervalsExampleFactory::blockIntervalsWithThreeBigIntervals();
  auto timestampsIntervals = IntervalsExampleFactory::timestampsIntervalsWithThreeBigIntervals();
  return DifferentialTimestampsContainer(firstUnixTimestamp_ms, blockIntervals, timestampsIntervals);
}

DifferentialTimestampsContainer DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerForSwitchDataFormTest() {
  auto firstUnixTimestamp_ms = UnixTimestampsExampleFactory::firstUnixTimestampForSwitchDataFormTest_ms();
  auto blockIntervals = IntervalsExampleFactory::blockIntervalsForSwitchDataFormTest();
  auto timestampsIntervals = IntervalsExampleFactory::timestampsIntervalsForSwitchDataFromTest();
  return DifferentialTimestampsContainer(firstUnixTimestamp_ms, blockIntervals, timestampsIntervals);
}

DifferentialTimestampsContainerJson DifferentialTimestampsContainerExampleFactory::buildDifferentialTimestampsContainerJson(
    DifferentialTimestampsContainer differentialTimestampsContainer) {
  auto blockIntervals = differentialTimestampsContainer.getBlockIntervals();
  auto timestampsIntervals = differentialTimestampsContainer.getTimestampsIntervals();
  auto blockIntervalsJson = IntervalsExampleFactory::buildBlockIntervalsJson(blockIntervals);
  auto timestampsIntervalsJson = IntervalsExampleFactory::buildTimestampsIntervalsJson(timestampsIntervals);
  DifferentialTimestampsContainerJson differentialTimestampsContainerJson;
  differentialTimestampsContainerJson["first_timestamp_ms"] = differentialTimestampsContainer.getFirstUnixTimestamp();
  differentialTimestampsContainerJson["block_intervals_ms"] = blockIntervalsJson;
  differentialTimestampsContainerJson["timestamps_intervals_ms"] = timestampsIntervalsJson;
  return differentialTimestampsContainerJson;
}

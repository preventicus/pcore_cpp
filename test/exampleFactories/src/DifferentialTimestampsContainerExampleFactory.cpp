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
  UnixTimestamp firstUnixTimestamp_ms = UnixTimestampsExampleFactory::firstTimestamp_ms();
  BlockIntervals blockIntervals = IntervalsExampleFactory::blockIntervalsWithThreeMixedIntervals();
  TimestampsIntervals timestampsIntervals = IntervalsExampleFactory::timestampsIntervalsWithThreeZeroIntervals();

  return DifferentialTimestampsContainer(firstUnixTimestamp_ms, blockIntervals, timestampsIntervals);
}

DifferentialTimestampsContainer DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerEmpty() {
  return DifferentialTimestampsContainer();
}

DifferentialTimestampsContainer DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithTwoBlocks() {
  UnixTimestamp firstUnixTimestamp_ms = UnixTimestampsExampleFactory::firstTimestamp_ms();
  BlockIntervals blockIntervals = IntervalsExampleFactory::blockIntervalsWithTwoMixedIntervals();
  TimestampsIntervals timestampsIntervals = IntervalsExampleFactory::timestampsIntervalsWithTwoMixedIntervals();
  return DifferentialTimestampsContainer(firstUnixTimestamp_ms, blockIntervals, timestampsIntervals);
}

DifferentialTimestampsContainer DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithBigBlocks() {
  UnixTimestamp firstUnixTimestamp_ms = UnixTimestampsExampleFactory::firstTimestamp_ms();
  BlockIntervals blockIntervals = IntervalsExampleFactory::blockIntervalsWithThreeBigIntervals();
  TimestampsIntervals timestampsIntervals = IntervalsExampleFactory::timestampsIntervalsWithThreeBigIntervals();
  return DifferentialTimestampsContainer(firstUnixTimestamp_ms, blockIntervals, timestampsIntervals);
}

DifferentialTimestampsContainer DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerForSwitchDataFormTest() {
  UnixTimestamp firstUnixTimestamp_ms = UnixTimestampsExampleFactory::firstUnixTimestampForSwitchDataFormTest_ms();
  BlockIntervals blockIntervals = IntervalsExampleFactory::blockIntervalsForSwitchDataFormTest();
  TimestampsIntervals timestampsIntervals = IntervalsExampleFactory::timestampsIntervalsForSwitchDataFromTest();
  return DifferentialTimestampsContainer(firstUnixTimestamp_ms, blockIntervals, timestampsIntervals);
}

DifferentialTimestampsContainerJson DifferentialTimestampsContainerExampleFactory::buildDifferentialTimestampsContainerJson(
    DifferentialTimestampsContainer differentialTimestampsContainer) {
  BlockIntervals blockIntervals = differentialTimestampsContainer.getBlockIntervals();
  TimestampsIntervals timestampsIntervals = differentialTimestampsContainer.getTimestampsIntervals();
  BlockIntervalsJson blockIntervalsJson = IntervalsExampleFactory::buildBlockIntervalsJson(blockIntervals);
  TimestampsIntervalsJson timestampsIntervalsJson = IntervalsExampleFactory::buildTimestampsIntervalsJson(timestampsIntervals);
  DifferentialTimestampsContainerJson differentialTimestampsContainerJson;
  differentialTimestampsContainerJson["first_timestamp_ms"] = differentialTimestampsContainer.getFirstUnixTimestamp();
  differentialTimestampsContainerJson["block_intervals_ms"] = blockIntervalsJson;
  differentialTimestampsContainerJson["timestamps_intervals_ms"] = timestampsIntervalsJson;
  return differentialTimestampsContainerJson;
}

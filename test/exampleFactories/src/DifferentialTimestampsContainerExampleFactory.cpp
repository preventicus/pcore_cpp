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
#include "DifferencesExampleFactory.h"
#include "PcoreJson.h"
#include "UnixTimestampsExampleFactory.h"

DifferentialTimestampsContainer DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithThreeBlocks() {
  auto firstUnixTimestamp_ms = UnixTimestampsExampleFactory::firstTimestamp_ms();
  auto blockDifferences = DifferencesExampleFactory::blockDifferencesWithThreeMixedDifferences();
  auto timestampsDifferences = DifferencesExampleFactory::timestampsDifferencesWithThreeZeroDifferences();

  return DifferentialTimestampsContainer(firstUnixTimestamp_ms, blockDifferences, timestampsDifferences);
}

DifferentialTimestampsContainer DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerNotSet() {
  return DifferentialTimestampsContainer();
}

DifferentialTimestampsContainer DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithTwoBlocks() {
  auto firstUnixTimestamp_ms = UnixTimestampsExampleFactory::firstTimestamp_ms();
  auto blockDifferences = DifferencesExampleFactory::blockDifferencesWithTwoMixedDifferences();
  auto timestampsDifferences = DifferencesExampleFactory::timestampsDifferencesWithTwoMixedDifferences();
  return DifferentialTimestampsContainer(firstUnixTimestamp_ms, blockDifferences, timestampsDifferences);
}

DifferentialTimestampsContainer DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithBigBlocks() {
  auto firstUnixTimestamp_ms = UnixTimestampsExampleFactory::firstTimestamp_ms();
  auto blockDifferences = DifferencesExampleFactory::blockDifferencesWithThreeBigDifferences();
  auto timestampsDifferences = DifferencesExampleFactory::timestampsDifferencesWithThreeBigDifferences();
  return DifferentialTimestampsContainer(firstUnixTimestamp_ms, blockDifferences, timestampsDifferences);
}

DifferentialTimestampsContainer DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerForSwitchDataFormTest() {
  auto firstUnixTimestamp_ms = UnixTimestampsExampleFactory::firstUnixTimestampForSwitchDataFormTest_ms();
  auto blockDifferences = DifferencesExampleFactory::blockDifferencesForSwitchDataFormTest();
  auto timestampsDifferences = DifferencesExampleFactory::timestampsDifferencesForSwitchDataFromTest();
  return DifferentialTimestampsContainer(firstUnixTimestamp_ms, blockDifferences, timestampsDifferences);
}

DifferentialTimestampsContainer DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithFirstUnixTimeStampNotSet() {
  auto firstUnixTimestamp_ms = UnixTimestampsExampleFactory::firstTimestampNotSet_ms();
  auto blockDifferences = DifferencesExampleFactory::blockDifferencesForSwitchDataFormTest();
  auto timestampsDifferences = DifferencesExampleFactory::timestampsDifferencesForSwitchDataFromTest();
  return DifferentialTimestampsContainer(firstUnixTimestamp_ms, blockDifferences, timestampsDifferences);
}

DifferentialTimestampsContainer
DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithFirstUnixTimeStampNotSetAndBlockDifferencesNotSet() {
  auto firstUnixTimestamp_ms = UnixTimestampsExampleFactory::firstTimestampNotSet_ms();
  auto blockDifferences = DifferencesExampleFactory::blockDifferencesNotSet();
  auto timestampsDifferences = DifferencesExampleFactory::timestampsDifferencesForSwitchDataFromTest();
  return DifferentialTimestampsContainer(firstUnixTimestamp_ms, blockDifferences, timestampsDifferences);
}

DifferentialTimestampsContainerJson DifferentialTimestampsContainerExampleFactory::buildDifferentialTimestampsContainerJson(
    const DifferentialTimestampsContainer& differentialTimestampsContainer) {
  DifferentialTimestampsContainerJson differentialTimestampsContainerJson;
  if (!differentialTimestampsContainer.isSet()) {
    return differentialTimestampsContainerJson;
  }
  auto blockDifferences = differentialTimestampsContainer.getBlockDifferences_ms();
  auto timestampsDifferences = differentialTimestampsContainer.getTimestampsDifferences_ms();
  auto blockDifferencesJson = DifferencesExampleFactory::buildBlockDifferencesJson(blockDifferences);
  auto timestampsDifferencesJson = DifferencesExampleFactory::buildTimestampsDifferencesJson(timestampsDifferences);
  differentialTimestampsContainerJson[PcoreJson::Key::first_unix_timestamp_ms] = differentialTimestampsContainer.getFirstUnixTimestamp_ms();
  differentialTimestampsContainerJson[PcoreJson::Key::block_differences_ms] = blockDifferencesJson;
  differentialTimestampsContainerJson[PcoreJson::Key::timestamps_differences_ms] = timestampsDifferencesJson;
  return differentialTimestampsContainerJson;
}

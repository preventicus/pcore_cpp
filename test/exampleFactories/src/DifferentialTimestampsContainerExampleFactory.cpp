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
  auto firstUnixTimestampInMs = UnixTimestampsExampleFactory::firstTimestampInMs();
  auto blocksDifferences = DifferencesExampleFactory::blocksDifferencesWithThreeMixedDifferences();
  auto timestampsDifferences = DifferencesExampleFactory::timestampsDifferencesWithThreeZeroDifferences();

  return DifferentialTimestampsContainer(firstUnixTimestampInMs, blocksDifferences, timestampsDifferences);
}

DifferentialTimestampsContainer DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerNotSet() {
  return DifferentialTimestampsContainer();
}

DifferentialTimestampsContainer DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithTwoBlocks() {
  auto firstUnixTimestampInMs = UnixTimestampsExampleFactory::firstTimestampInMs();
  auto blocksDifferences = DifferencesExampleFactory::blocksDifferencesWithTwoMixedDifferences();
  auto timestampsDifferences = DifferencesExampleFactory::timestampsDifferencesWithTwoMixedDifferences();
  return DifferentialTimestampsContainer(firstUnixTimestampInMs, blocksDifferences, timestampsDifferences);
}

DifferentialTimestampsContainer DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithBigBlocks() {
  auto firstUnixTimestampInMs = UnixTimestampsExampleFactory::firstTimestampInMs();
  auto blocksDifferences = DifferencesExampleFactory::blocksDifferencesWithThreeBigDifferences();
  auto timestampsDifferences = DifferencesExampleFactory::timestampsDifferencesWithThreeBigDifferences();
  return DifferentialTimestampsContainer(firstUnixTimestampInMs, blocksDifferences, timestampsDifferences);
}

DifferentialTimestampsContainer DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerForSwitchDataFormTest() {
  auto firstUnixTimestampInMs = UnixTimestampsExampleFactory::firstUnixTimestampForSwitchDataFormTestInMs();
  auto blocksDifferences = DifferencesExampleFactory::blocksDifferencesForSwitchDataFormTest();
  auto timestampsDifferences = DifferencesExampleFactory::timestampsDifferencesForSwitchDataFromTest();
  return DifferentialTimestampsContainer(firstUnixTimestampInMs, blocksDifferences, timestampsDifferences);
}

DifferentialTimestampsContainer DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithFirstUnixTimeStampNotSet() {
  auto firstUnixTimestampInMs = UnixTimestampsExampleFactory::firstTimestampNotSetInMs();
  auto blocksDifferences = DifferencesExampleFactory::blocksDifferencesForSwitchDataFormTest();
  auto timestampsDifferences = DifferencesExampleFactory::timestampsDifferencesForSwitchDataFromTest();
  return DifferentialTimestampsContainer(firstUnixTimestampInMs, blocksDifferences, timestampsDifferences);
}

DifferentialTimestampsContainer
DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithFirstUnixTimeStampNotSetAndBlocksDifferencesNotSet() {
  auto firstUnixTimestampInMs = UnixTimestampsExampleFactory::firstTimestampNotSetInMs();
  auto blocksDifferences = DifferencesExampleFactory::blocksDifferencesNotSet();
  auto timestampsDifferences = DifferencesExampleFactory::timestampsDifferencesForSwitchDataFromTest();
  return DifferentialTimestampsContainer(firstUnixTimestampInMs, blocksDifferences, timestampsDifferences);
}

DifferentialTimestampsContainerJson DifferentialTimestampsContainerExampleFactory::buildDifferentialTimestampsContainerJson(
    const DifferentialTimestampsContainer& differentialTimestampsContainer) {
  DifferentialTimestampsContainerJson differentialTimestampsContainerJson;
  if (!differentialTimestampsContainer.isSet()) {
    return differentialTimestampsContainerJson;
  }
  auto blocksDifferences = differentialTimestampsContainer.getBlocksDifferencesInMs();
  auto timestampsDifferences = differentialTimestampsContainer.getTimestampsDifferencesInMs();
  auto blocksDifferencesJson = DifferencesExampleFactory::buildBlocksDifferencesJson(blocksDifferences);
  auto timestampsDifferencesJson = DifferencesExampleFactory::buildTimestampsDifferencesJson(timestampsDifferences);
  differentialTimestampsContainerJson[PcoreJson::Key::first_unix_timestamp_ms] = differentialTimestampsContainer.getFirstUnixTimestampInMs();
  differentialTimestampsContainerJson[PcoreJson::Key::blocks_differences_ms] = blocksDifferencesJson;
  differentialTimestampsContainerJson[PcoreJson::Key::timestamps_differences_ms] = timestampsDifferencesJson;
  return differentialTimestampsContainerJson;
}

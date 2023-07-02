/*

Created by Steve Merschel 2023

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

#include "IntervalsExampleFactory.h"

BlockIntervals IntervalsExampleFactory::blockIntervalsWithThreeMixedIntervals() {
  return {0, 8, 5};
}

TimestampsIntervals IntervalsExampleFactory::timestampsIntervalsWithThreeZeroIntervals() {
  return {0, 0, 0};
}

BlockIntervals IntervalsExampleFactory::blockIntervalsEmpty() {
  return {};
}

TimestampsIntervals IntervalsExampleFactory::timestampsIntervalsEmpty() {
  return {};
}

BlockIntervals IntervalsExampleFactory::blockIntervalsWithTwoMixedIntervals() {
  return {0, 1};
}

TimestampsIntervals IntervalsExampleFactory::timestampsIntervalsWithTwoMixedIntervals() {
  return {30, 29};
}

BlockIntervals IntervalsExampleFactory::blockIntervalsWithThreeBigIntervals() {
  return {0, 5000, 74389};
}

TimestampsIntervals IntervalsExampleFactory::timestampsIntervalsWithThreeBigIntervals() {
  return {30823, 3139, 297238};
}

BlockIntervals IntervalsExampleFactory::blockIntervalsForSwitchDataFormTest() {
  return {0, 441, 359};
}

TimestampsIntervals IntervalsExampleFactory::timestampsIntervalsForSwitchDataFromTest() {
  return {40, 40, 40};
}

TimestampsIntervalsJson IntervalsExampleFactory::buildTimestampsIntervalsJson(TimestampsIntervals timestampsIntervals) {
  TimestampsIntervalsJson timestampsIntervalsJson(Json::arrayValue);
  for (auto& timestampsInterval : timestampsIntervals) {
    timestampsIntervalsJson.append(timestampsInterval);
  }
  return timestampsIntervalsJson;
}

BlockIntervalsJson IntervalsExampleFactory::buildBlockIntervalsJson(BlockIntervals blockIntervals) {
  BlockIntervalsJson blockIntervalsJson(Json::arrayValue);
  for (auto& blockInterval_ms : blockIntervals) {
    blockIntervalsJson.append(blockInterval_ms);
  }
  return blockIntervalsJson;
}
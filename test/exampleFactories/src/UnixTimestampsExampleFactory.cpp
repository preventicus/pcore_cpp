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

#include "UnixTimestampsExampleFactory.h"

UnixTimestamps UnixTimestampsExampleFactory::unixTimestampsWithThreeSmallTimestamps_ms() {
  return {1, 2, 3};
}

UnixTimestamps UnixTimestampsExampleFactory::unixTimestampsWithThreeBigTimestamps_ms() {
  return {1675732789987, 1675732789995, 1675732790000};
}

UnixTimestamps UnixTimestampsExampleFactory::unixTimestampsWithOneBigTimestamp_ms() {
  return {1675732789987};
}

UnixTimestamps UnixTimestampsExampleFactory::unixTimestampsWithTimestamp0_ms() {
  return {0};
}

UnixTimestamps UnixTimestampsExampleFactory::unixTimestampsNotSet_ms() {
  return {};
}

UnixTimestamps UnixTimestampsExampleFactory::unixTimestampsWithFiveDifferentialTimestamps_ms() {
  return {5, 0, 7, 200, 1};
}

UnixTimestamp UnixTimestampsExampleFactory::firstTimestamp_ms() {
  return 1675732789987;
}

UnixTimestamp UnixTimestampsExampleFactory::firstTimestampNotSet_ms() {
  return 0;
}

UnixTimestamp UnixTimestampsExampleFactory::lastTimestamp_ms() {
  return 1675732790000;
}

UnixTimestamps UnixTimestampsExampleFactory::unixTimestampsForSwitchDataFormTest_ms() {
  return {1677696136587, 1677696136627, 1677696136667, 1677696136707, 1677696136747, 1677696136787, 1677696136827, 1677696136867, 1677696136907,
          1677696136947, 1677696136987, 1677696137028, 1677696137068, 1677696137108, 1677696137148, 1677696137188, 1677696137228, 1677696137268,
          1677696137308, 1677696137348, 1677696137387, 1677696137427, 1677696137467, 1677696137507, 1677696137547, 1677696137587, 1677696137627};
}

UnixTimestamp UnixTimestampsExampleFactory::firstUnixTimestampForSwitchDataFormTest_ms() {
  return 1677696136587;
}

UnixTimestampsJson UnixTimestampsExampleFactory::buildUnixTimestampsJson(const UnixTimestamps& unixTimestamps_ms) {
  UnixTimestampsJson unixTimestampsJson(Json::arrayValue);
  for (auto& unixTimestamp_ms : unixTimestamps_ms) {
    unixTimestampsJson.append(unixTimestamp_ms);
  }
  return unixTimestampsJson;
}

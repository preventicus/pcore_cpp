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

#include "DifferentialTimestampsContainerExampleFactory.h"

UnixTimestamp DifferentialTimestampsContainerExampleFactory::normalFirstUnixTimestamp_ms() {
  return 10;
}

UnixTimestamp DifferentialTimestampsContainerExampleFactory::zeroFirstUnixTimestamp_ms() {
  return 0;
}

UnixTimestamp DifferentialTimestampsContainerExampleFactory::lastUnixTimestamp_ms() {
  return 1675732791427;
}

Duration DifferentialTimestampsContainerExampleFactory::duration() {
  return 1440;
}

BlockIntervals DifferentialTimestampsContainerExampleFactory::normalBlockIntervals_ms() {
  return {0, 113, 23, 34};
}

BlockIntervals DifferentialTimestampsContainerExampleFactory::zeroBlockIntervals_ms() {
  return {0};
}

BlockIntervals DifferentialTimestampsContainerExampleFactory::normalBlockIntervals_msWithOneUnixInLastBlock() {
  return {0, 300};
}

BlockIntervals DifferentialTimestampsContainerExampleFactory::emptyBlockIntervals_ms() {
  return {};
}

TimestampsIntervals DifferentialTimestampsContainerExampleFactory::normalTimestampsIntervals_ms() {
  return {134, 31, 124};
}

TimestampsIntervals DifferentialTimestampsContainerExampleFactory::normalTimestampsIntervals_msWithOneUnixInLastBlock() {
  return {40, 0};
}

TimestampsIntervals DifferentialTimestampsContainerExampleFactory::normalTimestampsIntervals_msWithEqualDifferences() {
  return {40};
}

TimestampsIntervals DifferentialTimestampsContainerExampleFactory::zeroTimestampsIntervals_ms() {
  return {0};
}

TimestampsIntervals DifferentialTimestampsContainerExampleFactory::emptyTimestampsIntervals_ms() {
  return {};
}

DifferentialTimestampsContainer DifferentialTimestampsContainerExampleFactory::differentialTimestampsWithNormalTimestamps() {
  UnixTimestamp firstUnixTimestamp_ms = DifferentialTimestampsContainerExampleFactory::normalFirstUnixTimestamp_ms();
  BlockIntervals blockInterval_ms = DifferentialTimestampsContainerExampleFactory::normalBlockIntervals_ms();
  TimestampsIntervals timestampsInterval_ms = DifferentialTimestampsContainerExampleFactory::normalTimestampsIntervals_ms();
  return DifferentialTimestampsContainer(firstUnixTimestamp_ms, blockInterval_ms, timestampsInterval_ms);
}

DifferentialTimestampsContainer DifferentialTimestampsContainerExampleFactory::differentialTimestampsWith0Timestamps() {
  UnixTimestamp firstUnixTimestamp_ms = DifferentialTimestampsContainerExampleFactory::zeroFirstUnixTimestamp_ms();
  BlockIntervals blockInterval_ms = DifferentialTimestampsContainerExampleFactory::zeroBlockIntervals_ms();
  TimestampsIntervals timestampsInterval_ms = DifferentialTimestampsContainerExampleFactory::zeroTimestampsIntervals_ms();
  return DifferentialTimestampsContainer(firstUnixTimestamp_ms, blockInterval_ms, timestampsInterval_ms);
}

DifferentialTimestampsContainer DifferentialTimestampsContainerExampleFactory::differentialTimestampsWithEmptyTimestamps() {
  UnixTimestamp firstUnixTimestamp_ms = DifferentialTimestampsContainerExampleFactory::zeroFirstUnixTimestamp_ms();
  BlockIntervals blockInterval_ms = DifferentialTimestampsContainerExampleFactory::emptyBlockIntervals_ms();
  TimestampsIntervals timestampsInterval_ms = DifferentialTimestampsContainerExampleFactory::emptyTimestampsIntervals_ms();
  return DifferentialTimestampsContainer(firstUnixTimestamp_ms, blockInterval_ms, timestampsInterval_ms);
}

BlockIntervals DifferentialTimestampsContainerExampleFactory::expectedBlockInterval() {
  return {0, 480, 400, 480};
}

TimestampsIntervals DifferentialTimestampsContainerExampleFactory::expectedTimestampInterval() {
  return {40, 40, 80, 40};
}

UnixTimestamp DifferentialTimestampsContainerExampleFactory::expectedFirstUnixTimestamps() {
  return 1675732789987;
}

DifferentialTimestampsContainer DifferentialTimestampsContainerExampleFactory::normalDifferentialTimestamps() {
  UnixTimestamp firstUnixTimestamp_ms = DifferentialTimestampsContainerExampleFactory::expectedFirstUnixTimestamps();
  BlockIntervals blockInterval = DifferentialTimestampsContainerExampleFactory::expectedBlockInterval();
  TimestampsIntervals timestampsInterval = DifferentialTimestampsContainerExampleFactory::expectedTimestampInterval();
  return DifferentialTimestampsContainer(firstUnixTimestamp_ms, blockInterval, timestampsInterval);
}

DifferentialTimestampsContainer DifferentialTimestampsContainerExampleFactory::differentiaJsonDataTimestampsContainerPpg() {
  UnixTimestamp firstUnixTimestamp_ms = 1675416424341;
  BlockIntervals blockInterval = {30, 30, 30, 30};
  TimestampsIntervals timestampsInterval = {28, 30, 22, 30};
  return DifferentialTimestampsContainer(firstUnixTimestamp_ms, blockInterval, timestampsInterval);
}

DifferentialTimestampsContainer DifferentialTimestampsContainerExampleFactory::differentiaJsonDataTimestampsContainerAcc() {
  UnixTimestamp firstUnixTimestamp_ms = 1675416424301;
  BlockIntervals blockInterval = {30, 31, 30};
  TimestampsIntervals timestampsInterval = {31, 30, 30};
  return DifferentialTimestampsContainer(firstUnixTimestamp_ms, blockInterval, timestampsInterval);
}
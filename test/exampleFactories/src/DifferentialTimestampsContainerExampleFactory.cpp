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

uint64_t DifferentialTimestampsContainerExampleFactory::normalFirstTimestamp_ms() {
  return 10;
}

uint64_t DifferentialTimestampsContainerExampleFactory::zeroFirstTimestamp_ms() {
  return 0;
}

uint64_t DifferentialTimestampsContainerExampleFactory::lastTimestamp() {
  return 1675732791427;
}

uint64_t DifferentialTimestampsContainerExampleFactory::duration() {
  return 1440;
}

std::vector<uint32_t> DifferentialTimestampsContainerExampleFactory::normalBlockIntervals_ms() {
  return {0, 113, 23, 34};
}

std::vector<uint32_t> DifferentialTimestampsContainerExampleFactory::zeroBlockIntervals_ms() {
  return {0};
}

std::vector<uint32_t> DifferentialTimestampsContainerExampleFactory::normalBlockIntervals_msWithOneUnixInLastBlock() {
  return {0, 300};
}

std::vector<uint32_t> DifferentialTimestampsContainerExampleFactory::emptyBlockIntervals_ms() {
  return {};
}

std::vector<uint32_t> DifferentialTimestampsContainerExampleFactory::normalTimestampsIntervals_ms() {
  return {134, 31, 124};
}

std::vector<uint32_t> DifferentialTimestampsContainerExampleFactory::normalTimestampsIntervals_msWithOneUnixInLastBlock() {
  return {40, 0};
}

std::vector<uint32_t> DifferentialTimestampsContainerExampleFactory::normalTimestampsIntervals_msWithEqualDifferences() {
  return {40};
}

std::vector<uint32_t> DifferentialTimestampsContainerExampleFactory::zeroTimestampsIntervals_ms() {
  return {0};
}

std::vector<uint32_t> DifferentialTimestampsContainerExampleFactory::emptyTimestampsIntervals_ms() {
  return {};
}

DifferentialTimestampsContainer DifferentialTimestampsContainerExampleFactory::differentialTimestampsWithNormalTimestamps() {
  uint64_t firstTimestamp_ms = DifferentialTimestampsContainerExampleFactory::normalFirstTimestamp_ms();
  std::vector<uint32_t> blockInterval_ms = DifferentialTimestampsContainerExampleFactory::normalBlockIntervals_ms();
  std::vector<uint32_t> timestampsInterval_ms = DifferentialTimestampsContainerExampleFactory::normalTimestampsIntervals_ms();
  return DifferentialTimestampsContainer(firstTimestamp_ms, blockInterval_ms, timestampsInterval_ms);
}

DifferentialTimestampsContainer DifferentialTimestampsContainerExampleFactory::differentialTimestampsWith0Timestamps() {
  uint64_t firstTimestamp_ms = DifferentialTimestampsContainerExampleFactory::zeroFirstTimestamp_ms();
  std::vector<uint32_t> blockInterval_ms = DifferentialTimestampsContainerExampleFactory::zeroBlockIntervals_ms();
  std::vector<uint32_t> timestampsInterval_ms = DifferentialTimestampsContainerExampleFactory::zeroTimestampsIntervals_ms();
  return DifferentialTimestampsContainer(firstTimestamp_ms, blockInterval_ms, timestampsInterval_ms);
}

DifferentialTimestampsContainer DifferentialTimestampsContainerExampleFactory::differentialTimestampsWithEmptyTimestamps() {
  uint64_t firstTimestamp_ms = DifferentialTimestampsContainerExampleFactory::zeroFirstTimestamp_ms();
  std::vector<uint32_t> blockInterval_ms = DifferentialTimestampsContainerExampleFactory::emptyBlockIntervals_ms();
  std::vector<uint32_t> timestampsInterval_ms = DifferentialTimestampsContainerExampleFactory::emptyTimestampsIntervals_ms();
  return DifferentialTimestampsContainer(firstTimestamp_ms, blockInterval_ms, timestampsInterval_ms);
}

std::vector<uint32_t> DifferentialTimestampsContainerExampleFactory::expectedBlockInterval() {
  return {0, 480, 400, 480};
}

std::vector<uint32_t> DifferentialTimestampsContainerExampleFactory::expectedTimestampInterval() {
  return {40, 40, 80, 40};
}

uint64_t DifferentialTimestampsContainerExampleFactory::expectedFirstTimestamps() {
  return 1675732789987;
}

DifferentialTimestampsContainer DifferentialTimestampsContainerExampleFactory::normalDifferentialTimestamps() {
  uint64_t firstTimestamp = DifferentialTimestampsContainerExampleFactory::expectedFirstTimestamps();
  std::vector<uint32_t> blockIntervals_ms = DifferentialTimestampsContainerExampleFactory::expectedBlockInterval();
  std::vector<uint32_t> timestampsIntervals_ms = DifferentialTimestampsContainerExampleFactory::expectedTimestampInterval();
  return DifferentialTimestampsContainer(firstTimestamp, blockIntervals_ms, timestampsIntervals_ms);
}

DifferentialTimestampsContainer DifferentialTimestampsContainerExampleFactory::differentiaJsonDataTimestampsContainerPpg() {
  uint64_t firstTimestamp = 1675416424341;
  std::vector<uint32_t> blockIntervals_ms = {30, 30, 30, 30};
  std::vector<uint32_t> timestampsIntervals_ms = {28, 30, 22, 30};
  return DifferentialTimestampsContainer(firstTimestamp, blockIntervals_ms, timestampsIntervals_ms);
}

DifferentialTimestampsContainer DifferentialTimestampsContainerExampleFactory::differentiaJsonDataTimestampsContainerAcc() {
  uint64_t firstTimestamp = 1675416424301;
  std::vector<uint32_t> blockIntervals_ms = {30, 31, 30};
  std::vector<uint32_t> timestampsIntervals_ms = {31, 30, 30};
  return DifferentialTimestampsContainer(firstTimestamp, blockIntervals_ms, timestampsIntervals_ms);
}
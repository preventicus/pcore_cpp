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

#include "AbsoluteTimestampsContainerExampleFactory.h"

std::vector<uint64_t> AbsoluteTimestampsContainerExampleFactory::unixTimestampsNormal_ms() {
  return {1, 2, 3};
}

std::vector<uint64_t> AbsoluteTimestampsContainerExampleFactory::unixTimestampsTwoElements_ms() {
  return {1, 2};
}

std::vector<uint64_t> AbsoluteTimestampsContainerExampleFactory::unixTimestampsOneElement_ms() {
  return {1};
}

std::vector<uint64_t> AbsoluteTimestampsContainerExampleFactory::unixTimestamps0_ms() {
  return {0};
}

std::vector<uint64_t> AbsoluteTimestampsContainerExampleFactory::unixTimestampsEmpty_ms() {
  return {};
}

AbsoluteTimestampsContainer AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsNormal() {
  std::vector<uint64_t> unixTimestamps = AbsoluteTimestampsContainerExampleFactory::unixTimestampsNormal_ms();
  return AbsoluteTimestampsContainer(unixTimestamps);
}

AbsoluteTimestampsContainer AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsTwoElement() {
  std::vector<uint64_t> unixTimestamps = AbsoluteTimestampsContainerExampleFactory::unixTimestampsTwoElements_ms();
  return AbsoluteTimestampsContainer(unixTimestamps);
}

AbsoluteTimestampsContainer AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsOneElement() {
  std::vector<uint64_t> unixTimestamps = AbsoluteTimestampsContainerExampleFactory::unixTimestampsTwoElements_ms();
  return AbsoluteTimestampsContainer(unixTimestamps);
}

AbsoluteTimestampsContainer AbsoluteTimestampsContainerExampleFactory::absoluteTimestamps0() {
  std::vector<uint64_t> unixTimestamps = AbsoluteTimestampsContainerExampleFactory::unixTimestamps0_ms();
  return AbsoluteTimestampsContainer(unixTimestamps);
}

AbsoluteTimestampsContainer AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsEmpty() {
  std::vector<uint64_t> unixTimestamps = AbsoluteTimestampsContainerExampleFactory::unixTimestampsEmpty_ms();
  return AbsoluteTimestampsContainer(unixTimestamps);
}

std::vector<uint64_t> AbsoluteTimestampsContainerExampleFactory::normalUnixTimestamps_ms() {
  return {1675732789987, 1675732790027, 1675732790067, 1675732790107, 1675732790147, 1675732790187, 1675732790227, 1675732790267, 1675732790307,
          1675732790347, 1675732790467, 1675732790507, 1675732790547, 1675732790587, 1675732790627, 1675732790667, 1675732790707, 1675732790747,
          1675732790867, 1675732790947, 1675732791027, 1675732791107, 1675732791187, 1675732791347, 1675732791387, 1675732791427};
}

AbsoluteTimestampsContainer AbsoluteTimestampsContainerExampleFactory::normalAbsoluteTimestamps() {
  std::vector<uint64_t> unixTimestamps = AbsoluteTimestampsContainerExampleFactory::normalUnixTimestamps_ms();
  return AbsoluteTimestampsContainer(unixTimestamps);
}

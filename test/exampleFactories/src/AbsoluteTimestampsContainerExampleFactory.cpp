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

AbsoluteTimestampsContainer AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsNormal() {
  UnixTimestamps unixTimestamps = UnixTimestampsExampleFactory::unixTimestampsNormal1_ms();
  return AbsoluteTimestampsContainer(unixTimestamps);
}

AbsoluteTimestampsContainer AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsTwoElement() {
  UnixTimestamps unixTimestamps = UnixTimestampsExampleFactory::unixTimestampsTwoElements_ms();
  return AbsoluteTimestampsContainer(unixTimestamps);
}

AbsoluteTimestampsContainer AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsOneElement() {
  UnixTimestamps unixTimestamps = UnixTimestampsExampleFactory::unixTimestampsOneElement_ms();
  return AbsoluteTimestampsContainer(unixTimestamps);
}

AbsoluteTimestampsContainer AbsoluteTimestampsContainerExampleFactory::absoluteTimestamps0() {
  UnixTimestamps unixTimestamps = UnixTimestampsExampleFactory::unixTimestamps0_ms();
  return AbsoluteTimestampsContainer(unixTimestamps);
}

AbsoluteTimestampsContainer AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsEmpty() {
  UnixTimestamps unixTimestamps = UnixTimestampsExampleFactory::unixTimestampsEmpty_ms();
  return AbsoluteTimestampsContainer(unixTimestamps);
}

AbsoluteTimestampsContainer AbsoluteTimestampsContainerExampleFactory::normalAbsoluteTimestamps() {
  UnixTimestamps unixTimestamps = UnixTimestampsExampleFactory::normalUnixTimestamps_ms();
  return AbsoluteTimestampsContainer(unixTimestamps);
}

AbsoluteTimestampsContainer AbsoluteTimestampsContainerExampleFactory::absoluteUNixTimestampBlockWithOneUnixInLastBlock() {
  UnixTimestamps unixTimestamps = UnixTimestampsExampleFactory::absoluteTimestampWithOneUnixInLastBlock();
  return AbsoluteTimestampsContainer(unixTimestamps);
}

AbsoluteTimestampsContainer AbsoluteTimestampsContainerExampleFactory::absoluteJsonDataTimestampsContainerPgg() {
  UnixTimestamps unixTimestamps = UnixTimestampsExampleFactory::absoluteJsonDataUNixTimestampsPpg();
  return AbsoluteTimestampsContainer(unixTimestamps);
}

AbsoluteTimestampsContainer AbsoluteTimestampsContainerExampleFactory::absoluteJsonDataTimestampsContainerAcc() {
  UnixTimestamps unixTimestamps = UnixTimestampsExampleFactory::absoluteJsonDataUNixTimestampsAcc();
  return AbsoluteTimestampsContainer(unixTimestamps);
}

AbsoluteTimestampsContainer AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsBlockWithEqualTimestampIntervals() {
  UnixTimestamps unixTimestamps = UnixTimestampsExampleFactory::absoluteTimestampWithEqualTimestampIntervals();
  return AbsoluteTimestampsContainer(unixTimestamps);
}

AbsoluteTimestampsContainer AbsoluteTimestampsContainerExampleFactory::buildAbsoluteTimestampsContainer(UnixTimestamps& unixTimestamps) {
  return AbsoluteTimestampsContainer(unixTimestamps);
}

AbsoluteTimestampsContainerJson AbsoluteTimestampsContainerExampleFactory::buildAbsoluteTimestampsContainerJson(
    UnixTimestampsJson& unixTimestampsJson) {
  AbsoluteTimestampsContainerJson absoluteTimestampsContainerJson;
  absoluteTimestampsContainerJson["unix_timestamps_ms"] = unixTimestampsJson;
  return absoluteTimestampsContainerJson;
}
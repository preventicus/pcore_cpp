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
#include "DeserializedHeader.h"

void DeserializedHeader::setTimeZoneOffset(int32_t timeZoneOffset_min) {  // TODO FOR-333
  if (timeZoneOffset_min < 841 && timeZoneOffset_min > -721) {
    this->timeZoneOffset_min = timeZoneOffset_min;
  } else {
    throw std::out_of_range("Out of range");
  }
}

void DeserializedHeader::setVersion(DeserializedVersion version) {
  this->version = version;
}

int DeserializedHeader::getTimeZoneOffset() {
  return this->timeZoneOffset_min;
}

DeserializedVersion DeserializedHeader::getVersion() {
  return this->version;
}

bool DeserializedHeader::isEqual(DeserializedHeader& deserializedHeader) {
  return this->timeZoneOffset_min == deserializedHeader.timeZoneOffset_min;
}

SerializedHeader DeserializedHeader::serialize() {
  SerializedHeader serializedHeader;
  serializedHeader.set_time_zone_offset(this->timeZoneOffset_min);
  SerializedVersion serializedVersion = this->version.serialize();
  serializedHeader.mutable_pcore_version()->CopyFrom(serializedVersion);
  return serializedHeader;
}

void DeserializedHeader::deserialize(SerializedHeader& serializedHeader) {
  this->timeZoneOffset_min = serializedHeader.time_zone_offset();
  SerializedVersion serializedVersion = serializedHeader.pcore_version();
  this->version.setMajor(serializedVersion.major());
  this->version.setMinor(serializedVersion.minor());
  this->version.setPatch(serializedVersion.patch());
}

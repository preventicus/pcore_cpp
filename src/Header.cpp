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
#include "Header.h"

Header::Header(Version& version, int32_t timeZoneOffset_min) {
  if (timeZoneOffset_min < 841 && timeZoneOffset_min > -721) {
    this->timeZoneOffset_min = timeZoneOffset_min;
    this->version = version;
  } else {
    throw std::out_of_range("Out of range");
  }
}

Header::Header(const ProtobufHeader& protobufHeader) {
  this->deserialize(protobufHeader);
}

Header::Header() {}

int Header::getTimeZoneOffset() {
  return this->timeZoneOffset_min;
}

Version Header::getVersion() {
  return this->version;
}

bool Header::isEqual(Header& header) {
  return this->timeZoneOffset_min == header.timeZoneOffset_min;
}

ProtobufHeader Header::serialize() {
  ProtobufHeader protobufHeader;
  protobufHeader.set_time_zone_offset_min(this->timeZoneOffset_min);
  ProtobufVersion protobufVersion = this->version.serialize();
  protobufHeader.mutable_pcore_version()->CopyFrom(protobufVersion);
  return protobufHeader;
}

void Header::deserialize(const ProtobufHeader& protobufHeader) {
  this->timeZoneOffset_min = protobufHeader.time_zone_offset_min();
  ProtobufVersion protobufVersion = protobufHeader.pcore_version();
}

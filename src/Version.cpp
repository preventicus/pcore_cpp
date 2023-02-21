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

#include "Version.h"

Version::Version(uint32_t major, uint32_t minor, uint32_t patch) : major(major), minor(minor), patch(patch) {}

Version::Version(Json::Value& version) {
  this->major = version["major"].asUInt();
  this->minor = version["minor"].asUInt();
  this->patch = version["patch"].asUInt();
}

Version::Version(const ProtobufVersion& protobufVersion) {
  this->deserialize(protobufVersion);
}

Version::Version() {
  this->major = 0;
  this->minor = 0;
  this->patch = 0;
}

uint32_t Version::getMajor() {
  return this->major;
}

uint32_t Version::getMinor() {
  return this->minor;
}

uint32_t Version::getPatch() {
  return this->patch;
}

bool Version::isEqual(Version& version) {
  return this->major == version.major && this->minor == version.minor && this->patch == version.patch;
}

void Version::serialize(ProtobufVersion* protobufVersion) {
  if (protobufVersion == nullptr) {
    throw std::invalid_argument("Error in serialize: protobufVersion is a null pointer");
  }
  protobufVersion->set_major(this->major);
  protobufVersion->set_minor(this->minor);
  protobufVersion->set_patch(this->patch);
}

Json::Value Version::toJson() {
  Json::Value version;
  Json::Value major(this->major);
  Json::Value minor(this->minor);
  Json::Value patch(this->patch);
  version["major"] = major;
  version["minor"] = minor;
  version["patch"] = patch;
  return version;
}

void Version::deserialize(const ProtobufVersion& protobufVersion) {
  this->major = protobufVersion.major();
  this->minor = protobufVersion.minor();
  this->patch = protobufVersion.patch();
}

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

#include "Version.h"

Version::Version(Major major, Minor minor, Patch patch) : major(major), minor(minor), patch(patch) {}

Version::Version(VersionJson& versionJson)
    : major(this->getVersionPartsFromJson(versionJson, "major")),
      minor(this->getVersionPartsFromJson(versionJson, "minor")),
      patch(this->getVersionPartsFromJson(versionJson, "patch")) {}

Version::Version(const ProtobufVersion& protobufVersion)
    : major(protobufVersion.major()), minor(protobufVersion.minor()), patch(protobufVersion.patch()) {}

Version::Version() : major(0), minor(0), patch(0) {}

Major Version::getMajor() {
  return this->major;
}

Minor Version::getMinor() {
  return this->minor;
}

Patch Version::getPatch() {
  return this->patch;
}

bool Version::operator==(const Version& version) const {
  return this->major == version.major && this->minor == version.minor && this->patch == version.patch;
}

bool Version::operator!=(const Version& version) const {
  return this->major != version.major || this->minor != version.minor || this->patch != version.patch;
}

void Version::serialize(ProtobufVersion* protobufVersion) {
  if (protobufVersion == nullptr) {
    throw std::invalid_argument("Error in serialize: protobufVersion is a null pointer");
  }
  protobufVersion->set_major(this->major);
  protobufVersion->set_minor(this->minor);
  protobufVersion->set_patch(this->patch);
}

VersionJson Version::toJson() {
  MajorJson majorJson(this->major);
  MinorJson minorJson(this->minor);
  PatchJson patchJson(this->patch);
  VersionJson versionJson;
  versionJson["major"] = majorJson;
  versionJson["minor"] = minorJson;
  versionJson["patch"] = patchJson;
  return versionJson;
}

Major Version::getVersionPartsFromJson(VersionJson& versionJson, std::string jsonKey) {
  if (versionJson[jsonKey].asInt() < 0) {
    throw std::invalid_argument(jsonKey + " is negative in json.");
  }
  return versionJson[jsonKey].asUInt();
}
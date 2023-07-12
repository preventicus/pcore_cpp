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
#include "PcoreJson.h"

using namespace PCore;

Version::Version(Major major, Minor minor, Patch patch) : major(major), minor(minor), patch(patch) {}

Version::Version(const VersionJson& versionJson)
    : major(PcoreJson::Convert::jsonToValue<Major>(versionJson, PcoreJson::Key::major)),
      minor(PcoreJson::Convert::jsonToValue<Minor>(versionJson, PcoreJson::Key::minor)),
      patch(PcoreJson::Convert::jsonToValue<Patch>(versionJson, PcoreJson::Key::patch)) {}

Version::Version(const VersionProtobuf& versionProtobuf)
    : major(versionProtobuf.major()), minor(versionProtobuf.minor()), patch(versionProtobuf.patch()) {}

Version::Version() : major(0), minor(0), patch(0) {}

Major Version::getMajor() const {
  return this->major;
}

Minor Version::getMinor() const {
  return this->minor;
}

Patch Version::getPatch() const {
  return this->patch;
}

bool Version::operator==(const IPCore<VersionProtobuf>& version) const {
  if (const auto* derived = dynamic_cast<const Version*>(&version)) {
    return this->major == derived->major && this->minor == derived->minor && this->patch == derived->patch;
  }
  return false;
}

bool Version::operator!=(const IPCore<VersionProtobuf>& version) const {
  return !(*this == version);
}

void Version::serialize(VersionProtobuf* versionProtobuf) const {
  if (versionProtobuf == nullptr) {
    throw std::invalid_argument("Error in serialize: versionProtobuf is a null pointer");
  }
  versionProtobuf->set_major(this->major);
  versionProtobuf->set_minor(this->minor);
  versionProtobuf->set_patch(this->patch);
}

void Version::switchDataForm() {
  throw std::runtime_error("should not be called");  // TODO unittest
}

VersionJson Version::toJson() const {
  MajorJson majorJson(this->major);
  MinorJson minorJson(this->minor);
  PatchJson patchJson(this->patch);
  VersionJson versionJson;
  versionJson[PcoreJson::Key::major] = majorJson;
  versionJson[PcoreJson::Key::minor] = minorJson;
  versionJson[PcoreJson::Key::patch] = patchJson;
  return versionJson;
}

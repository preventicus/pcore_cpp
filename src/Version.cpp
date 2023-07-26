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
#include "Exceptions.h"
#include "PcoreJson.h"

using namespace PCore;

////////////////////////////////////////////////////////////////
//                       Constructors                         //
////////////////////////////////////////////////////////////////

Version::Version(Major major, Minor minor, Patch patch) noexcept : major(major), minor(minor), patch(patch) {}

Version::Version(const VersionJson& versionJson)
    : major(PcoreJson::Convert::jsonToValue<Major>(versionJson, PcoreJson::Key::major)),
      minor(PcoreJson::Convert::jsonToValue<Minor>(versionJson, PcoreJson::Key::minor)),
      patch(PcoreJson::Convert::jsonToValue<Patch>(versionJson, PcoreJson::Key::patch)) {}

Version::Version(const VersionProtobuf& versionProtobuf) noexcept
    : major(versionProtobuf.major()), minor(versionProtobuf.minor()), patch(versionProtobuf.patch()) {}

Version::Version() noexcept : major(0), minor(0), patch(0) {}

////////////////////////////////////////////////////////////////
//                          Getter                            //
////////////////////////////////////////////////////////////////

Major Version::getMajor() const noexcept {
  return this->major;
}

Minor Version::getMinor() const noexcept {
  return this->minor;
}

Patch Version::getPatch() const noexcept {
  return this->patch;
}

////////////////////////////////////////////////////////////////
//                      IPCore Methods                        //
////////////////////////////////////////////////////////////////

bool Version::isSet() const noexcept {
  // clang-format off
  return this->major != 0
      || this->minor != 0
      || this->patch != 0;
  // clang-format on
}

VersionJson Version::toJson() const noexcept {
  VersionJson versionJson;
  if (!this->isSet()) {
    return versionJson;
  }
  MajorJson majorJson(Json::uintValue);
  MinorJson minorJson(Json::uintValue);
  PatchJson patchJson(Json::uintValue);
  majorJson = this->major;
  minorJson = this->minor;
  patchJson = this->patch;
  versionJson[PcoreJson::Key::major] = majorJson;
  versionJson[PcoreJson::Key::minor] = minorJson;
  versionJson[PcoreJson::Key::patch] = patchJson;
  return versionJson;
}

void Version::serialize(VersionProtobuf* versionProtobuf) const {
  if (versionProtobuf == nullptr) {
    throw NullPointerException("Version::serialize", "versionProtobuf");
  }
  if (!this->isSet()) {
    return;
  }
  versionProtobuf->set_major(this->major);
  versionProtobuf->set_minor(this->minor);
  versionProtobuf->set_patch(this->patch);
}

void Version::switchDataForm() {
  throw ShouldNotBeCalledException("Version::switchDataForm");
}

bool Version::operator==(const IPCore<VersionProtobuf>& version) const noexcept {
  if (const auto* derived = dynamic_cast<const Version*>(&version)) {
    return this->major == derived->major && this->minor == derived->minor && this->patch == derived->patch;
  }
  return false;
}

bool Version::operator!=(const IPCore<VersionProtobuf>& version) const noexcept {
  return !(*this == version);
}
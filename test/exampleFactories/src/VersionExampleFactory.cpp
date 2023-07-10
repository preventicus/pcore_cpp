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

#include "VersionExampleFactory.h"
#include "PcoreJson.h"

Major VersionExampleFactory::majorOne() {
  return 1;
}

Minor VersionExampleFactory::minorOne() {
  return 1;
}

Patch VersionExampleFactory::patchOne() {
  return 1;
}

Major VersionExampleFactory::majorTwo() {
  return 2;
}

Minor VersionExampleFactory::minorTwo() {
  return 2;
}

Patch VersionExampleFactory::patchTwo() {
  return 2;
}

Major VersionExampleFactory::majorZero() {
  return 0;
}

Minor VersionExampleFactory::minorZero() {
  return 0;
}

Patch VersionExampleFactory::patchZero() {
  return 0;
}

Version VersionExampleFactory::versionWithMajor1Minor1Patch0() {
  return Version(VersionExampleFactory::majorOne(), VersionExampleFactory::minorOne(), VersionExampleFactory::patchZero());
}

Version VersionExampleFactory::versionWithMajor1Minor2Patch0() {
  return Version(VersionExampleFactory::majorOne(), VersionExampleFactory::minorTwo(), VersionExampleFactory::patchZero());
}

Version VersionExampleFactory::versionWithMajor1Minor1Patch1() {
  return Version(VersionExampleFactory::majorOne(), VersionExampleFactory::minorOne(), VersionExampleFactory::patchOne());
}

Version VersionExampleFactory::versionWithMajor0Minor0Patch0() {
  return Version(VersionExampleFactory::majorZero(), VersionExampleFactory::minorZero(), VersionExampleFactory::patchZero());
}

Version VersionExampleFactory::versionWithMajor2Minor1Patch0() {
  return Version(VersionExampleFactory::majorTwo(), VersionExampleFactory::minorOne(), VersionExampleFactory::patchZero());
}

Version VersionExampleFactory::versionEmpty() {
  return Version();
}

VersionJson VersionExampleFactory::buildVersionJson(Version version) {
  MajorJson majorJson(version.getMajor());
  MinorJson minorJson(version.getMinor());
  PatchJson patchJson(version.getPatch());
  VersionJson versionJson;
  versionJson[PcoreJson::Key::major] = majorJson;
  versionJson[PcoreJson::Key::minor] = minorJson;
  versionJson[PcoreJson::Key::patch] = patchJson;
  return versionJson;
}

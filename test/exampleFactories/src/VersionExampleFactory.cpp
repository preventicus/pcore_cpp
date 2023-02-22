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

#include "VersionExampleFactory.h"

uint32_t VersionExampleFactory::majorOne() {
  return 1;
}

uint32_t VersionExampleFactory::minorOne() {
  return 1;
}

uint32_t VersionExampleFactory::patchOne() {
  return 1;
}

uint32_t VersionExampleFactory::majorTwo() {
  return 2;
}

uint32_t VersionExampleFactory::minorTwo() {
  return 2;
}

uint32_t VersionExampleFactory::patchTwo() {
  return 2;
}

uint32_t VersionExampleFactory::majorZero() {
  return 0;
}

uint32_t VersionExampleFactory::minorZero() {
  return 0;
}

uint32_t VersionExampleFactory::patchZero() {
  return 0;
}

Version VersionExampleFactory::normalVersion() {
  return Version(VersionExampleFactory::majorOne(), VersionExampleFactory::minorOne(), VersionExampleFactory::patchOne());
}

Version VersionExampleFactory::startVersion() {
  return Version(VersionExampleFactory::majorZero(), VersionExampleFactory::minorZero(), VersionExampleFactory::patchZero());
}

Version VersionExampleFactory::highVersion() {
  return Version(VersionExampleFactory::majorTwo(), VersionExampleFactory::minorTwo(), VersionExampleFactory::patchTwo());
}

Version VersionExampleFactory::randomVersion() {
  return Version(VersionExampleFactory::majorTwo(), VersionExampleFactory::minorOne(), VersionExampleFactory::patchZero());
}

Version VersionExampleFactory::absoluteJsonDataVersion() {
  return Version(VersionExampleFactory::majorOne(), VersionExampleFactory::minorOne(), VersionExampleFactory::patchZero());
}

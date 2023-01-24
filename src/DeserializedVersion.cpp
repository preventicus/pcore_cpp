/*

Created by Jakob Glück 2022

Copyright © 2022 PREVENTICUS GmbH

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

#include "DeserializedVersion.h"

DeserializedVersion::DeserializedVersion() {
  this->major = 0;
  this->minor = 0;
  this->patch = 0;
}

void DeserializedVersion::setMajor(uint32_t major) {
  this->major = major;
}

void DeserializedVersion::setMinor(uint32_t minor) {
  this->minor = minor;
}

void DeserializedVersion::setPatch(uint32_t patch) {
  this->patch = patch;
}

uint32_t DeserializedVersion::getMajor() {
  return this->major;
}

uint32_t DeserializedVersion::getMinor() {
  return this->minor;
}

uint32_t DeserializedVersion::getPatch() {
  return this->patch;
}

bool DeserializedVersion::isEqual(DeserializedVersion& deserializedVersion) {
  return this->major == deserializedVersion.major &&
         this->minor == deserializedVersion.minor &&
         this->patch == deserializedVersion.patch;
}

SerializedVersion DeserializedVersion::serialize() {
  SerializedVersion serializedVersion;
  serializedVersion.set_major(this->major);
  serializedVersion.set_minor(this->minor);
  serializedVersion.set_patch(this->patch);
  return serializedVersion;
}

void DeserializedVersion::deserialize(SerializedVersion& serializedVersion) {
  this->major = serializedVersion.major();
  this->minor = serializedVersion.minor();
  this->patch = serializedVersion.patch();
}
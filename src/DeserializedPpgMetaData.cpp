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
#include "DeserializedPpgMetaData.h"

DeserializedPpgMetaData::DeserializedPpgMetaData() {
  this->color = Color::COLOR_NONE;
  this->wavelength_nm = 0;
}

void DeserializedPpgMetaData::setColor(Color color) {
  this->wavelength_nm = 0;
  this->color = color;
}

void DeserializedPpgMetaData::setWavelength(uint32_t wavelength) {
  this->color = Color::COLOR_NONE;
  this->wavelength_nm = wavelength;
}

Color DeserializedPpgMetaData::getColor() {
  return this->color;
}

uint32_t DeserializedPpgMetaData::getWavelength() {
  return this->wavelength_nm;
}

bool DeserializedPpgMetaData::isEqual(DeserializedPpgMetaData& deserializedPpgMetaData) {
  return this->color == deserializedPpgMetaData.color && this->wavelength_nm == deserializedPpgMetaData.wavelength_nm;
}

SerializedPpgMetaData DeserializedPpgMetaData::serialize() {
  SerializedPpgMetaData serializedPpgMetaData = SerializedPpgMetaData();
  if (this->color != Color::COLOR_NONE) {
    serializedPpgMetaData.set_color(this->color);
  }
  if (this->wavelength_nm != 0) {
    serializedPpgMetaData.set_wavelength(this->wavelength_nm);
  }
  return serializedPpgMetaData;
}

void DeserializedPpgMetaData::deserialize(SerializedPpgMetaData& serializedPpgMetaData) {
  this->color = serializedPpgMetaData.color();
  this->wavelength_nm = serializedPpgMetaData.wavelength();
}
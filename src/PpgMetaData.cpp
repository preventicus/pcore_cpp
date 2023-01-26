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
#include "PpgMetaData.h"

PpgMetaData::PpgMetaData() {
  this->color = ProtobufColor::COLOR_NONE;
  this->wavelength_nm = 0;
}

void PpgMetaData::setColor(ProtobufColor color) {
  this->wavelength_nm = 0;
  this->color = color;
}

void PpgMetaData::setWavelength(uint32_t wavelength) {
  this->color = ProtobufColor::COLOR_NONE;
  this->wavelength_nm = wavelength;
}

ProtobufColor PpgMetaData::getColor() {
  return this->color;
}

uint32_t PpgMetaData::getWavelength() {
  return this->wavelength_nm;
}

bool PpgMetaData::isEqual(PpgMetaData& ppgMetaData) {
  return this->color == ppgMetaData.color && this->wavelength_nm == ppgMetaData.wavelength_nm;
}

ProtobufPpgMetaData PpgMetaData::serialize() {
  ProtobufPpgMetaData protobufPpgMetaData = ProtobufPpgMetaData();
  if (this->color != ProtobufColor::COLOR_NONE) {
    protobufPpgMetaData.set_color(this->color);
  }
  if (this->wavelength_nm != 0) {
    protobufPpgMetaData.set_wavelength(this->wavelength_nm);
  }
  return protobufPpgMetaData;
}

void PpgMetaData::deserialize(ProtobufPpgMetaData& protobufPpgMetaData) {
  this->color = protobufPpgMetaData.color();
  this->wavelength_nm = protobufPpgMetaData.wavelength();
}
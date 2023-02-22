/*

Created by Jakob Glück 2023

Copyright © 2023 PREVENTICUS GmbH

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors
   may be used to endorse or promote products derived from this software
without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#include "PpgMetaData.h"

PpgMetaData::PpgMetaData(ProtobufColor color) {
  this->color = color;
  this->wavelength_nm = 0;
}

PpgMetaData::PpgMetaData(uint32_t wavelength_nm) {
  this->wavelength_nm = wavelength_nm;
  this->color = ProtobufColor::COLOR_NONE;
}

PpgMetaData::PpgMetaData(Json::Value& ppgMetaData) {
  if (ppgMetaData["wavelength_nm"].asUInt() != 0 && ppgMetaData["color"].asString() != "") {
    throw std::invalid_argument("just one enum type of PpgMetaData can be initialized");
  }
  if (ppgMetaData["wavelength_nm"].asUInt() != 0) {
    if (ppgMetaData["wavelength_nm"].asUInt() < 0) {
      throw std::invalid_argument("wavelength_nm  not allowed to be less than zero");
    }
    Json::Value wavelength = ppgMetaData["wavelength_nm"];
    this->wavelength_nm = wavelength.asUInt();
    this->color = ProtobufColor::COLOR_NONE;
  }
  if (ppgMetaData["color"].asString() != "") {
    this->color = this->toEnum(ppgMetaData["color"]);
    this->wavelength_nm = 0;
  }
}

PpgMetaData::PpgMetaData(const ProtobufPpgMetaData& protobufPpgMetaData) {
  this->deserialize(protobufPpgMetaData);
}

PpgMetaData::PpgMetaData() {
  this->color = ProtobufColor::COLOR_NONE;
  this->wavelength_nm = 0;
}

ProtobufColor PpgMetaData::getColor() {
  return this->color;
}

uint32_t PpgMetaData::getWavelength() {
  return this->wavelength_nm;
}

bool PpgMetaData::isSet() {
  return !(this->color == ProtobufColor::COLOR_NONE && this->wavelength_nm == 0);
}

bool PpgMetaData::isEqual(PpgMetaData& ppgMetaData) {
  return this->color == ppgMetaData.color && this->wavelength_nm == ppgMetaData.wavelength_nm;
}

Json::Value PpgMetaData::toJson() {
  Json::Value ppgMetaData;
  Json::Value wavelength_nm(this->wavelength_nm);
  if (this->wavelength_nm != 0) {
    ppgMetaData["wavelength_nm"] = wavelength_nm;
  }
  if (this->color != ProtobufColor::COLOR_NONE) {
    ppgMetaData["color"] = this->toString(this->color);
  }
  return ppgMetaData;
}

void PpgMetaData::serialize(ProtobufPpgMetaData* protobufPpgMetaData) {
  if (protobufPpgMetaData == nullptr) {
    throw std::invalid_argument("Error in serialize: protobufPpgMetaData is a null pointer");
  }
  if (this->color != ProtobufColor::COLOR_NONE && this->wavelength_nm != 0) {
    throw std::invalid_argument("one parameter has to be initialized");
  }
  if (this->color != ProtobufColor::COLOR_NONE) {
    protobufPpgMetaData->set_color(this->color);
  }
  if (this->wavelength_nm != 0) {
    protobufPpgMetaData->set_wavelength_nm(this->wavelength_nm);
  }
}

void PpgMetaData::deserialize(const ProtobufPpgMetaData& protobufPpgMetaData) {
  this->color = protobufPpgMetaData.color();
  this->wavelength_nm = protobufPpgMetaData.wavelength_nm();
}

std::string PpgMetaData::toString(ProtobufColor color) {
  std::string jsonColor;
  switch (color) {
    case ProtobufColor::COLOR_RED: {
      jsonColor = "COLOR_RED";
    }
    case ProtobufColor::COLOR_BLUE: {
      jsonColor = "COLOR_BLUE";
    }
    case ProtobufColor::COLOR_GREEN: {
      jsonColor = "COLOR_GREEN";
    }
    default: {
      break;
    }
  }
  return jsonColor;
}

ProtobufColor PpgMetaData::toEnum(Json::Value color) {
  ProtobufColor protobufColor;
  if (color.asString() == "COLOR_RED") {
    protobufColor = ProtobufColor::COLOR_RED;
  }
  if (color.asString() == "COLOR_BLUE") {
    protobufColor = ProtobufColor::COLOR_BLUE;
  }
  if (color.asString() == "COLOR_GREEN") {
    protobufColor = ProtobufColor::COLOR_GREEN;
  }
  return protobufColor;
}
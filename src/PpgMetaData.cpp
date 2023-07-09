/*

Created by Jakob Glueck, Steve Merschel 2023

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

using WavelegthJson = Json::Value;

PpgMetaData::PpgMetaData(ProtobufColor color) : color(color), wavelength_nm(0) {}

PpgMetaData::PpgMetaData(Wavelength wavelength_nm) : color(ProtobufColor::COLOR_NONE), wavelength_nm(wavelength_nm) {}

PpgMetaData::PpgMetaData(PpgMetaDataJson& ppgMetaDataJson)
    : color(PpgMetaData::protobufColorFromString(ppgMetaDataJson["color"].asString())), wavelength_nm([&]() {
        if (ppgMetaDataJson["wavelength_nm"].asInt() < 0) {
          throw std::invalid_argument("wavelength_nm is negative in json.");
        }
        return ppgMetaDataJson["wavelength_nm"].asUInt();
      }()) {
  if (this->wavelength_nm != 0 & this->color != ProtobufColor::COLOR_NONE) {
    throw std::invalid_argument("just one enum type of PpgMetaData can be initialized");
  }
}

PpgMetaData::PpgMetaData(const ProtobufPpgMetaData& protobufPpgMetaData)
    : color(protobufPpgMetaData.color()), wavelength_nm(protobufPpgMetaData.wavelength_nm()) {}

PpgMetaData::PpgMetaData() : color(ProtobufColor::COLOR_NONE), wavelength_nm(0) {}

ProtobufColor PpgMetaData::getColor() const {
  return this->color;
}

Wavelength PpgMetaData::getWavelength() const {
  return this->wavelength_nm;
}

bool PpgMetaData::hasColor() const {
  return this->color != ProtobufColor::COLOR_NONE;
}

bool PpgMetaData::hasWavelength() const {
  return this->wavelength_nm > 0;
}

bool PpgMetaData::isSet() const {
  return !(this->color == ProtobufColor::COLOR_NONE && this->wavelength_nm == 0);
}

bool PpgMetaData::operator==(const PpgMetaData& ppgMetaData) const {
  return this->color == ppgMetaData.color && this->wavelength_nm == ppgMetaData.wavelength_nm;
}

bool PpgMetaData::operator!=(const PpgMetaData& ppgMetaData) const {
  return this->color != ppgMetaData.color || this->wavelength_nm != ppgMetaData.wavelength_nm;
}

PpgMetaDataJson PpgMetaData::toJson() const {
  PpgMetaDataJson ppgMetaDataJson;
  WavelegthJson wavelengthJson(this->wavelength_nm);
  if (this->wavelength_nm != 0) {
    ppgMetaDataJson["wavelength_nm"] = wavelengthJson;
  }
  if (this->color != ProtobufColor::COLOR_NONE) {
    ppgMetaDataJson["color"] = PpgMetaData::protobufColorToString(this->color);
  }
  return ppgMetaDataJson;
}

void PpgMetaData::serialize(ProtobufPpgMetaData* protobufPpgMetaData) const {
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

ProtobufColorString PpgMetaData::protobufColorToString(const ProtobufColor protobufColor) {
  switch (protobufColor) {
    case ProtobufColor::COLOR_RED: {
      return "COLOR_RED";
    }
    case ProtobufColor::COLOR_BLUE: {
      return "COLOR_BLUE";
    }
    case ProtobufColor::COLOR_GREEN: {
      return "COLOR_GREEN";
    }
    default: {
      return "COLOR_NONE";
    }
  }
}

ProtobufColor PpgMetaData::protobufColorFromString(const ProtobufColorString protobufColorString) {
  if (protobufColorString == "COLOR_RED") {
    return ProtobufColor::COLOR_RED;
  } else if (protobufColorString == "COLOR_BLUE") {
    return ProtobufColor::COLOR_BLUE;
  } else if (protobufColorString == "COLOR_GREEN") {
    return ProtobufColor::COLOR_GREEN;
  } else {
    return ProtobufColor::COLOR_NONE;
  }
}
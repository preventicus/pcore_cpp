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
#include "PcoreJson.h"

using namespace PCore;

using WavelegthJson = Json::Value;

PpgMetaData::PpgMetaData(ColorProtobuf colorProtobuf) : color(colorProtobuf), wavelength_nm(0) {}

PpgMetaData::PpgMetaData(Wavelength wavelength_nm) : color(ColorProtobuf::COLOR_NONE), wavelength_nm(wavelength_nm) {}

PpgMetaData::PpgMetaData(const PpgMetaDataJson& ppgMetaDataJson)
    : color(PpgMetaData::colorProtobufFromString(ppgMetaDataJson[PcoreJson::Key::color].asString())), wavelength_nm([&]() {
        if (ppgMetaDataJson[PcoreJson::Key::wavelength_nm].asInt() < 0) {
          throw std::invalid_argument("wavelength_nm is negative in json.");
        }
        return ppgMetaDataJson[PcoreJson::Key::wavelength_nm].asUInt();
      }()) {
  if (this->wavelength_nm != 0 & this->color != ColorProtobuf::COLOR_NONE) {
    throw std::invalid_argument("just one enum type of PpgMetaData can be initialized");
  }
}

PpgMetaData::PpgMetaData(const PpgMetaDataProtobuf& ppgMetaDataProtobuf)
    : color(ppgMetaDataProtobuf.color()), wavelength_nm(ppgMetaDataProtobuf.wavelength_nm()) {}

PpgMetaData::PpgMetaData() : color(ColorProtobuf::COLOR_NONE), wavelength_nm(0) {}

ColorProtobuf PpgMetaData::getColor() const {
  return this->color;
}

Wavelength PpgMetaData::getWavelength_nm() const {
  return this->wavelength_nm;
}

bool PpgMetaData::hasColor() const {
  return this->color != ColorProtobuf::COLOR_NONE;
}

bool PpgMetaData::hasWavelength() const {
  return this->wavelength_nm > 0;
}

bool PpgMetaData::isSet() const {
  return !(this->color == ColorProtobuf::COLOR_NONE && this->wavelength_nm == 0);
}

bool PpgMetaData::operator==(const IPCore<PpgMetaDataProtobuf>& ppgMetaData) const {
  if (const auto* derived = dynamic_cast<const PpgMetaData*>(&ppgMetaData)) {
    return this->color == derived->color && this->wavelength_nm == derived->wavelength_nm;
  }
  return false;
}

bool PpgMetaData::operator!=(const IPCore<PpgMetaDataProtobuf>& ppgMetaData) const {
  return !(*this == ppgMetaData);
}

PpgMetaDataJson PpgMetaData::toJson() const {
  PpgMetaDataJson ppgMetaDataJson;
  WavelegthJson wavelengthJson(this->wavelength_nm);
  if (this->wavelength_nm != 0) {
    ppgMetaDataJson[PcoreJson::Key::wavelength_nm] = wavelengthJson;
  }
  if (this->color != ColorProtobuf::COLOR_NONE) {
    ppgMetaDataJson[PcoreJson::Key::color] = PpgMetaData::colorProtobufToString(this->color);
  }
  return ppgMetaDataJson;
}

void PpgMetaData::serialize(PpgMetaDataProtobuf* ppgMetaDataProtobuf) const {
  if (ppgMetaDataProtobuf == nullptr) {
    throw std::invalid_argument("Error in serialize: ppgMetaDataProtobuf is a null pointer");
  }
  if (this->color != ColorProtobuf::COLOR_NONE && this->wavelength_nm != 0) {
    throw std::invalid_argument("one parameter has to be initialized");
  }
  if (this->color != ColorProtobuf::COLOR_NONE) {
    ppgMetaDataProtobuf->set_color(this->color);
  }
  if (this->wavelength_nm != 0) {
    ppgMetaDataProtobuf->set_wavelength_nm(this->wavelength_nm);
  }
}

void PpgMetaData::switchDataForm() {
  throw std::runtime_error("should not be called");  // TODO unittest
}

ColorStringProtobuf PpgMetaData::colorProtobufToString(ColorProtobuf colorProtobuf) {
  switch (colorProtobuf) {
    case ColorProtobuf::COLOR_RED: {
      return "COLOR_RED";
    }
    case ColorProtobuf::COLOR_BLUE: {
      return "COLOR_BLUE";
    }
    case ColorProtobuf::COLOR_GREEN: {
      return "COLOR_GREEN";
    }
    default: {
      return "COLOR_NONE";
    }
  }
}

ColorProtobuf PpgMetaData::colorProtobufFromString(ColorStringProtobuf colorStringProtobuf) {
  if (colorStringProtobuf == "COLOR_RED") {
    return ColorProtobuf::COLOR_RED;
  } else if (colorStringProtobuf == "COLOR_BLUE") {
    return ColorProtobuf::COLOR_BLUE;
  } else if (colorStringProtobuf == "COLOR_GREEN") {
    return ColorProtobuf::COLOR_GREEN;
  } else {
    return ColorProtobuf::COLOR_NONE;
  }
}
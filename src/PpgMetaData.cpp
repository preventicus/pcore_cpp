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

////////////////////////////////////////////////////////////////
//                       Constructors                         //
////////////////////////////////////////////////////////////////
PpgMetaData::PpgMetaData(ColorProtobuf colorProtobuf) : color(colorProtobuf), wavelengthInNm(0) {}

PpgMetaData::PpgMetaData(Wavelength wavelengthInNm) : color(ColorProtobuf::COLOR_NONE), wavelengthInNm(wavelengthInNm) {}

PpgMetaData::PpgMetaData(const PpgMetaDataJson& ppgMetaDataJson)
    : color(PcoreProtobuf::Convert::colorProtobufFromString(ppgMetaDataJson[PcoreJson::Key::color].asString())), wavelengthInNm([&]() {
        if (ppgMetaDataJson[PcoreJson::Key::wavelength_nm].asInt() < 0) {
          throw std::invalid_argument("wavelengthInNm is negative in json.");
        }
        return ppgMetaDataJson[PcoreJson::Key::wavelength_nm].asUInt();
      }()) {
  if (this->hasColor() && this->hasWavelength()) {
    throw std::invalid_argument("just one enum type of PpgMetaData can be initialized");
  }
}

PpgMetaData::PpgMetaData(const PpgMetaDataProtobuf& ppgMetaDataProtobuf)
    : color(ppgMetaDataProtobuf.color()), wavelengthInNm(ppgMetaDataProtobuf.wavelength_nm()) {}

PpgMetaData::PpgMetaData() : color(ColorProtobuf::COLOR_NONE), wavelengthInNm(0) {}

////////////////////////////////////////////////////////////////
//                          Getter                            //
////////////////////////////////////////////////////////////////
ColorProtobuf PpgMetaData::getColor() const {
  return this->color;
}

Wavelength PpgMetaData::getWavelengthInNm() const {
  return this->wavelengthInNm;
}

bool PpgMetaData::hasColor() const {
  return this->color != ColorProtobuf::COLOR_NONE;
}

bool PpgMetaData::hasWavelength() const {
  return this->wavelengthInNm > 0;
}

////////////////////////////////////////////////////////////////
//                      IPCore Methods                        //
////////////////////////////////////////////////////////////////

bool PpgMetaData::isSet() const {
  return this->hasColor() || this->hasWavelength();
}

PpgMetaDataJson PpgMetaData::toJson() const {
  PpgMetaDataJson ppgMetaDataJson;
  if (!this->isSet()) {
    return ppgMetaDataJson;
  }
  if (this->hasWavelength()) {
    WavelegthJson wavelengthJson(Json::uintValue);
    wavelengthJson = this->wavelengthInNm;
    ppgMetaDataJson[PcoreJson::Key::wavelength_nm] = wavelengthJson;
  }
  if (this->hasColor()) {
    ppgMetaDataJson[PcoreJson::Key::color] = PcoreProtobuf::Convert::colorProtobufToString(this->color);
  }
  return ppgMetaDataJson;
}

void PpgMetaData::serialize(PpgMetaDataProtobuf* ppgMetaDataProtobuf) const {
  if (ppgMetaDataProtobuf == nullptr) {
    throw std::invalid_argument("Error in serialize: ppgMetaDataProtobuf is a null pointer");
  }
  if (!this->isSet()) {
    return;
  }
  if (this->hasColor() && this->hasWavelength()) {
    throw std::invalid_argument("only one parameter has to be initialized");
  }
  if (this->hasColor()) {
    ppgMetaDataProtobuf->set_color(this->color);
  }
  if (this->hasWavelength()) {
    ppgMetaDataProtobuf->set_wavelength_nm(this->wavelengthInNm);
  }
}

void PpgMetaData::switchDataForm() {
  throw std::runtime_error("should not be called");
}

bool PpgMetaData::operator==(const IPCore<PpgMetaDataProtobuf>& ppgMetaData) const {
  if (const auto* derived = dynamic_cast<const PpgMetaData*>(&ppgMetaData)) {
    return this->color == derived->color && this->wavelengthInNm == derived->wavelengthInNm;
  }
  return false;
}

bool PpgMetaData::operator!=(const IPCore<PpgMetaDataProtobuf>& ppgMetaData) const {
  return !(*this == ppgMetaData);
}
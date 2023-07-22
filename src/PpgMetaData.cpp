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
#include "Exceptions.h"
#include "PcoreJson.h"

using namespace PCore;

using WavelegthJson = Json::Value;

////////////////////////////////////////////////////////////////
//                       Constructors                         //
////////////////////////////////////////////////////////////////
PpgMetaData::PpgMetaData(ColorProtobuf colorProtobuf) noexcept : light(colorProtobuf) {}

PpgMetaData::PpgMetaData(Wavelength wavelengthInNm) noexcept : light(wavelengthInNm) {}

PpgMetaData::PpgMetaData(const PpgMetaDataJson& ppgMetaDataJson)
    : light([&]() -> Light {
        if (ppgMetaDataJson.isMember(PcoreJson::Key::wavelength_nm)) {
          if (ppgMetaDataJson[PcoreJson::Key::wavelength_nm].asInt() < 0) {
            throw WrongValueException("PpgMetaData", "wavelengthInNm is negative in json.");
          }
          return ppgMetaDataJson[PcoreJson::Key::wavelength_nm].asUInt();
        } else if (ppgMetaDataJson.isMember(PcoreJson::Key::color)) {
          return PcoreProtobuf::Convert::colorProtobufFromString(ppgMetaDataJson[PcoreJson::Key::color].asString());
        } else {
          return std::nullopt;
        }
      }()) {
  if (this->hasLight<ColorProtobuf>() && this->hasLight<Wavelength>()) {
    throw OnlyOneParameterAllowedException("PpgMetaData", "Color", "Wavelength");
  }
}

PpgMetaData::PpgMetaData(const PpgMetaDataProtobuf& ppgMetaDataProtobuf) noexcept
    : light([&]() -> Light {
        if (ppgMetaDataProtobuf.has_color()) {
          return ppgMetaDataProtobuf.color();
        } else if (ppgMetaDataProtobuf.has_wavelength_nm()) {
          return ppgMetaDataProtobuf.wavelength_nm();
        } else {
          return std::nullopt;
        }
      }()) {}

PpgMetaData::PpgMetaData() noexcept : light(std::nullopt) {}

////////////////////////////////////////////////////////////////
//                          Getter                            //
////////////////////////////////////////////////////////////////

template <typename L>
[[nodiscard]] std::optional<L> PpgMetaData::getLight() const noexcept {
  if (!this->light.has_value()) {
    return std::nullopt;
  }
  if (!std::holds_alternative<L>(*this->light)) {
    return std::nullopt;
  }
  return std::get<L>(*this->light);
}

template <typename L>
[[nodiscard]] bool PpgMetaData::hasLight() const noexcept {
  if (!this->light.has_value()) {
    return false;
  }
  if (!std::holds_alternative<L>(*this->light)) {
    return false;
  }
  if constexpr (std::is_same_v<L, Wavelength>) {
    return std::get<L>(*this->light) != 0;
  } else {
    return std::get<L>(*this->light) != ColorProtobuf::COLOR_NONE;
  }
}

////////////////////////////////////////////////////////////////
//                      IPCore Methods                        //
////////////////////////////////////////////////////////////////

bool PpgMetaData::isSet() const noexcept {
  return this->hasLight<ColorProtobuf>() || this->hasLight<Wavelength>();
}

PpgMetaDataJson PpgMetaData::toJson() const noexcept {
  PpgMetaDataJson ppgMetaDataJson;
  if (!this->isSet()) {
    return ppgMetaDataJson;
  }
  if (this->hasLight<Wavelength>()) {
    WavelegthJson wavelengthJson(Json::uintValue);
    wavelengthJson = *this->getLight<Wavelength>();
    ppgMetaDataJson[PcoreJson::Key::wavelength_nm] = wavelengthJson;
  }
  if (this->hasLight<ColorProtobuf>()) {
    ppgMetaDataJson[PcoreJson::Key::color] = PcoreProtobuf::Convert::colorProtobufToString(*this->getLight<ColorProtobuf>());
  }
  return ppgMetaDataJson;
}

void PpgMetaData::serialize(PpgMetaDataProtobuf* ppgMetaDataProtobuf) const {
  if (ppgMetaDataProtobuf == nullptr) {
    throw NullPointerException("PpgMetaData::serialize", "ppgMetaDataProtobuf");
  }
  if (!this->isSet()) {
    return;
  }
  if (this->hasLight<ColorProtobuf>() && this->hasLight<Wavelength>()) {
    throw OnlyOneParameterAllowedException("PpgMetaData::serialize", "Color", "Wavelength");
  }
  if (this->hasLight<ColorProtobuf>()) {
    ppgMetaDataProtobuf->set_color(*this->getLight<ColorProtobuf>());
  }
  if (this->hasLight<Wavelength>()) {
    ppgMetaDataProtobuf->set_wavelength_nm(*this->getLight<Wavelength>());
  }
}

void PpgMetaData::switchDataForm() {
  throw ShouldNotBeCalledException("PpgMetaData::switchDataForm");
}

bool PpgMetaData::operator==(const IPCore<PpgMetaDataProtobuf>& ppgMetaData) const noexcept {
  if (const auto* derived = dynamic_cast<const PpgMetaData*>(&ppgMetaData)) {
    if (this->light.has_value() != derived->light.has_value()) {
      return false;
    }
    if (!this->light.has_value() && !derived->light.has_value()) {
      return true;
    }
    return this->light == derived->light;
  }
  return false;
}

bool PpgMetaData::operator!=(const IPCore<PpgMetaDataProtobuf>& ppgMetaData) const noexcept {
  return !(*this == ppgMetaData);
}
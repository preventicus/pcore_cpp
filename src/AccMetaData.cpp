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

#include "AccMetaData.h"
#include "Exceptions.h"
#include "PcoreJson.h"

using namespace PCore;

////////////////////////////////////////////////////////////////
//                       Constructors                         //
////////////////////////////////////////////////////////////////
AccMetaData::AccMetaData(CoordinateProtobuf coordinate) noexcept : type(coordinate) {}

AccMetaData::AccMetaData(NormProtobuf norm) noexcept : type(norm) {}

AccMetaData::AccMetaData(const AccMetaDataJson& accMetaDataJson)
    : type([&]() -> Type {
        if (accMetaDataJson.isMember(PcoreJson::Key::coordinate)) {
          return PcoreProtobuf::Convert::coordinateProtobufFromString(accMetaDataJson[PcoreJson::Key::coordinate].asString());
        } else if (accMetaDataJson.isMember(PcoreJson::Key::norm)) {
          return PcoreProtobuf::Convert::normProtobufFromString(accMetaDataJson[PcoreJson::Key::norm].asString());
        } else {
          return std::nullopt;
        }
      }()) {
  if (this->hasType<NormProtobuf>() && this->hasType<CoordinateProtobuf>())
    throw OnlyOneParameterAllowedException("AccMetaData", "Norm", "Coordinate");
}

AccMetaData::AccMetaData(const AccMetaDataProtobuf& accMetaDataProtobuf) noexcept
    : type([&]() -> Type {
        if (accMetaDataProtobuf.has_coordinate()) {
          return accMetaDataProtobuf.coordinate();
        } else if (accMetaDataProtobuf.has_norm()) {
          return accMetaDataProtobuf.norm();
        } else {
          return std::nullopt;
        }
      }()) {}

AccMetaData::AccMetaData() noexcept : type(std::nullopt) {}

////////////////////////////////////////////////////////////////
//                          Getter                            //
////////////////////////////////////////////////////////////////
template <typename T>
std::optional<T> AccMetaData::getType() const noexcept {
  if (!this->type.has_value()) {
    return std::nullopt;
  }
  if (!std::holds_alternative<T>(*this->type)) {
    return std::nullopt;
  }
  return std::get<T>(*this->type);
}

template <typename T>
bool AccMetaData::hasType() const noexcept {
  if (!this->type.has_value()) {
    return false;
  }
  if (!std::holds_alternative<T>(*this->type)) {
    return false;
  }
  if constexpr (std::is_same_v<T, NormProtobuf>) {
    return std::get<T>(*this->type) != NormProtobuf::NORM_NONE;
  } else {
    return std::get<T>(*this->type) != CoordinateProtobuf::COORDINATE_NONE;
  }
}

////////////////////////////////////////////////////////////////
//                      IPCore Methods                        //
////////////////////////////////////////////////////////////////

bool AccMetaData::isSet() const noexcept {
  return this->hasType<NormProtobuf>() || this->hasType<CoordinateProtobuf>();
}

Json::Value AccMetaData::toJson() const noexcept {
  AccMetaDataJson accMetaDataJson;
  if (!this->isSet()) {
    return accMetaDataJson;
  }
  if (this->hasType<NormProtobuf>()) {
    accMetaDataJson[PcoreJson::Key::norm] = PcoreProtobuf::Convert::normProtobufToString(*this->getType<NormProtobuf>());
  }
  if (this->hasType<CoordinateProtobuf>()) {
    accMetaDataJson[PcoreJson::Key::coordinate] = PcoreProtobuf::Convert::coordinateProtobufToString(*this->getType<CoordinateProtobuf>());
  }
  return accMetaDataJson;
}

void AccMetaData::serialize(AccMetaDataProtobuf* accMetaDataProtobuf) const {
  if (accMetaDataProtobuf == nullptr) {
    throw NullPointerException("AccMetaData::serialize", "accMetaDataProtobuf");
  }
  if (!this->isSet()) {
    return;
  }
  if (this->hasType<CoordinateProtobuf>() && this->hasType<NormProtobuf>()) {
    throw OnlyOneParameterAllowedException("AccMetaData::serialize", "Coordinate", "Norm");
  }
  if (this->hasType<CoordinateProtobuf>()) {
    accMetaDataProtobuf->set_coordinate(*this->getType<CoordinateProtobuf>());
  }
  if (this->hasType<NormProtobuf>()) {
    accMetaDataProtobuf->set_norm(*this->getType<NormProtobuf>());
  }
}

void AccMetaData::switchDataForm() {
  throw ShouldNotBeCalledException("AccMetaData::switchDataForm");
}

bool AccMetaData::operator==(const IPCore<AccMetaDataProtobuf>& accMetaData) const noexcept {
  if (const auto* derived = dynamic_cast<const AccMetaData*>(&accMetaData)) {
    if (this->type.has_value() != derived->type.has_value()) {
      return false;
    }
    if (!this->type.has_value() && !derived->type.has_value()) {
      return true;
    }
    return this->type == derived->type;
  }
  return false;
}

bool AccMetaData::operator!=(const IPCore<AccMetaDataProtobuf>& accMetaData) const noexcept {
  return !(*this == accMetaData);
}
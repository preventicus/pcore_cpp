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
#include "PcoreJson.h"
using namespace PCore;

AccMetaData::AccMetaData(CoordinateProtobuf coordinate) : coordinate(coordinate), norm(NormProtobuf::NORM_NONE) {}

AccMetaData::AccMetaData(NormProtobuf norm) : coordinate(CoordinateProtobuf::COORDINATE_NONE), norm(norm) {}

AccMetaData::AccMetaData(const AccMetaDataJson& accMetaDataJson)
    : coordinate(PcoreProtobuf::Convert::coordinateProtobufFromString(accMetaDataJson[PcoreJson::Key::coordinate].asString())),
      norm(PcoreProtobuf::Convert::normProtobufFromString(accMetaDataJson[PcoreJson::Key::norm].asString())) {
  if (this->hasNorm() && this->hasCoordinate()) {
    throw std::invalid_argument("just one enum type of AccMetaData can be initialized");
  }
}

AccMetaData::AccMetaData(const AccMetaDataProtobuf& accMetaDataProtobuf)
    : coordinate(accMetaDataProtobuf.coordinate()), norm(accMetaDataProtobuf.norm()) {}

AccMetaData::AccMetaData() : coordinate(CoordinateProtobuf::COORDINATE_NONE), norm(NormProtobuf::NORM_NONE) {}

CoordinateProtobuf AccMetaData::getCoordinate() const {
  return this->coordinate;
}

NormProtobuf AccMetaData::getNorm() const {
  return this->norm;
}

bool AccMetaData::hasNorm() const {
  return this->norm != NormProtobuf::NORM_NONE;
}

bool AccMetaData::hasCoordinate() const {
  return this->coordinate != CoordinateProtobuf::COORDINATE_NONE;
}

bool AccMetaData::isSet() const {
  return this->hasNorm() || this->hasCoordinate();
}

bool AccMetaData::operator==(const IPCore<AccMetaDataProtobuf>& accMetaData) const {
  if (const auto* derived = dynamic_cast<const AccMetaData*>(&accMetaData)) {
    return this->coordinate == derived->coordinate && this->norm == derived->norm;
  }
  return false;
}

bool AccMetaData::operator!=(const IPCore<AccMetaDataProtobuf>& accMetaData) const {
  return !(*this == accMetaData);
}

void AccMetaData::serialize(AccMetaDataProtobuf* accMetaDataProtobuf) const {
  if (accMetaDataProtobuf == nullptr) {
    throw std::invalid_argument("accMetaDataProtobuf is a null pointer");
  }
  if (!this->isSet()) {
    return;
  }
  if (this->hasCoordinate() && this->hasNorm()) {
    throw std::invalid_argument("only one enum type has to be initialized");
  }
  if (this->hasCoordinate()) {
    accMetaDataProtobuf->set_coordinate(this->coordinate);
  }
  if (this->hasNorm()) {
    accMetaDataProtobuf->set_norm(this->norm);
  }
}

void AccMetaData::switchDataForm() {
  throw std::runtime_error("should not be called");
}

Json::Value AccMetaData::toJson() const {
  AccMetaDataJson accMetaDataJson;
  if (!this->isSet()) {
    return accMetaDataJson;
  }
  if (this->hasNorm()) {
    accMetaDataJson[PcoreJson::Key::norm] = PcoreProtobuf::Convert::normProtobufToString(this->norm);
  }
  if (this->hasCoordinate()) {
    accMetaDataJson[PcoreJson::Key::coordinate] = PcoreProtobuf::Convert::coordinateProtobufToString(this->coordinate);
  }
  return accMetaDataJson;
}

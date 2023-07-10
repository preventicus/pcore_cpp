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

AccMetaData::AccMetaData(CoordinateProtobuf coordinate) : coordinate(coordinate), norm(NormProtobuf::NORM_NONE) {}

AccMetaData::AccMetaData(NormProtobuf norm) : coordinate(CoordinateProtobuf::COORDINATE_NONE), norm(norm) {}

AccMetaData::AccMetaData(const AccMetaDataJson& accMetaDataJson)
    : coordinate(AccMetaData::coordinateProtobufFromString(accMetaDataJson[PcoreJsonKey::coordinate].asString())),
      norm(AccMetaData::normProtobufFromString(accMetaDataJson[PcoreJsonKey::norm].asString())) {
  if (this->norm != NormProtobuf::NORM_NONE & this->coordinate != CoordinateProtobuf::COORDINATE_NONE) {
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

bool AccMetaData::operator==(const AccMetaData& accMetaData) const {
  return this->coordinate == accMetaData.coordinate && this->norm == accMetaData.norm;
}

bool AccMetaData::operator!=(const AccMetaData& accMetaData) const {
  return this->coordinate != accMetaData.coordinate || this->norm != accMetaData.norm;
}

void AccMetaData::serialize(AccMetaDataProtobuf* accMetaDataProtobuf) const {
  if (accMetaDataProtobuf == nullptr) {
    throw std::invalid_argument("accMetaDataProtobuf is a null pointer");
  }
  if (coordinate != CoordinateProtobuf::COORDINATE_NONE && norm != NormProtobuf::NORM_NONE) {
    throw std::invalid_argument("one enum type has to be initialized");
  }
  if (this->coordinate != CoordinateProtobuf::COORDINATE_NONE) {
    accMetaDataProtobuf->set_coordinate(this->coordinate);
  }
  if (this->norm != NormProtobuf::NORM_NONE) {
    accMetaDataProtobuf->set_norm(this->norm);
  }
}

Json::Value AccMetaData::toJson() const {
  AccMetaDataJson accMetaDataJson;
  if (this->norm != NormProtobuf::NORM_NONE) {
    accMetaDataJson[PcoreJsonKey::norm] = AccMetaData::normProtobufToString(this->norm);
  }
  if (this->coordinate != CoordinateProtobuf::COORDINATE_NONE) {
    accMetaDataJson[PcoreJsonKey::coordinate] = AccMetaData::coordinateProtobufToString(this->coordinate);
  }
  return accMetaDataJson;
}

CoordinateProtobufString AccMetaData::coordinateProtobufToString(CoordinateProtobuf coordinateProtobuf) {
  switch (coordinateProtobuf) {
    case CoordinateProtobuf::COORDINATE_X: {
      return "COORDINATE_X";
    }
    case CoordinateProtobuf::COORDINATE_Y: {
      return "COORDINATE_Y";
    }
    case CoordinateProtobuf::COORDINATE_Z: {
      return "COORDINATE_Z";
    }
    default: {
      return "COORDINATE_NONE";
    }
  }
}

CoordinateProtobuf AccMetaData::coordinateProtobufFromString(CoordinateProtobufString coordinateProtobufString) {
  if (coordinateProtobufString == "COORDINATE_X") {
    return CoordinateProtobuf::COORDINATE_X;
  } else if (coordinateProtobufString == "COORDINATE_Y") {
    return CoordinateProtobuf::COORDINATE_Y;
  } else if (coordinateProtobufString == "COORDINATE_Z") {
    return CoordinateProtobuf::COORDINATE_Z;
  } else {
    return CoordinateProtobuf::COORDINATE_NONE;
  }
}

NormStringProtobuf AccMetaData::normProtobufToString(NormProtobuf normProtobuf) {
  switch (normProtobuf) {
    case NormProtobuf::NORM_EUCLIDEAN_DIFFERENCES_NORM: {
      return "NORM_EUCLIDEAN_DIFFERENCES_NORM";
    }
    default: {
      return "NORM_NONE";
    }
  }
}

NormProtobuf AccMetaData::normProtobufFromString(NormStringProtobuf normProtobufString) {
  if (normProtobufString == "NORM_EUCLIDEAN_DIFFERENCES_NORM") {
    return NormProtobuf::NORM_EUCLIDEAN_DIFFERENCES_NORM;
  } else {
    return NormProtobuf::NORM_NONE;
  }
}
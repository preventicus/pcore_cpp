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

AccMetaData::AccMetaData(ProtobufCoordinate coordinate) : coordinate(coordinate), norm(ProtobufNorm::NORM_NONE) {}

AccMetaData::AccMetaData(ProtobufNorm norm) : coordinate(ProtobufCoordinate::COORDINATE_NONE), norm(norm) {}

AccMetaData::AccMetaData(const AccMetaDataJson& accMetaDataJson)
    : coordinate(AccMetaData::protobufCoordinateFromString(accMetaDataJson[PcoreJsonKey::coordinate].asString())),
      norm(AccMetaData::protobufNormFromString(accMetaDataJson[PcoreJsonKey::norm].asString())) {
  if (this->norm != ProtobufNorm::NORM_NONE & this->coordinate != ProtobufCoordinate::COORDINATE_NONE) {
    throw std::invalid_argument("just one enum type of AccMetaData can be initialized");
  }
}

AccMetaData::AccMetaData(const ProtobufAccMetaData& protobufAccMetaData)
    : coordinate(protobufAccMetaData.coordinate()), norm(protobufAccMetaData.norm()) {}

AccMetaData::AccMetaData() : coordinate(ProtobufCoordinate::COORDINATE_NONE), norm(ProtobufNorm::NORM_NONE) {}

ProtobufCoordinate AccMetaData::getCoordinate() const {
  return this->coordinate;
}

ProtobufNorm AccMetaData::getNorm() const {
  return this->norm;
}

bool AccMetaData::hasNorm() const {
  return this->norm != ProtobufNorm::NORM_NONE;
}

bool AccMetaData::hasCoordinate() const {
  return this->coordinate != ProtobufCoordinate::COORDINATE_NONE;
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

void AccMetaData::serialize(ProtobufAccMetaData* protobufAccMetaData) const {
  if (protobufAccMetaData == nullptr) {
    throw std::invalid_argument("protobufAccMetaData is a null pointer");
  }
  if (coordinate != ProtobufCoordinate::COORDINATE_NONE && norm != ProtobufNorm::NORM_NONE) {
    throw std::invalid_argument("one enum type has to be initialized");
  }
  if (this->coordinate != ProtobufCoordinate::COORDINATE_NONE) {
    protobufAccMetaData->set_coordinate(this->coordinate);
  }
  if (this->norm != ProtobufNorm::NORM_NONE) {
    protobufAccMetaData->set_norm(this->norm);
  }
}

Json::Value AccMetaData::toJson() const {
  AccMetaDataJson accMetaDataJson;
  if (this->norm != ProtobufNorm::NORM_NONE) {
    accMetaDataJson[PcoreJsonKey::norm] = AccMetaData::protobufNormToString(this->norm);
  }
  if (this->coordinate != ProtobufCoordinate::COORDINATE_NONE) {
    accMetaDataJson[PcoreJsonKey::coordinate] = AccMetaData::protobufCoordinateToString(this->coordinate);
  }
  return accMetaDataJson;
}

ProtobufCoordinateString AccMetaData::protobufCoordinateToString(const ProtobufCoordinate protobufCoordinate) {
  switch (protobufCoordinate) {
    case ProtobufCoordinate::COORDINATE_X: {
      return "COORDINATE_X";
    }
    case ProtobufCoordinate::COORDINATE_Y: {
      return "COORDINATE_Y";
    }
    case ProtobufCoordinate::COORDINATE_Z: {
      return "COORDINATE_Z";
    }
    default: {
      return "COORDINATE_NONE";
    }
  }
}

ProtobufCoordinate AccMetaData::protobufCoordinateFromString(const ProtobufCoordinateString protobufCoordinateString) {
  if (protobufCoordinateString == "COORDINATE_X") {
    return ProtobufCoordinate::COORDINATE_X;
  } else if (protobufCoordinateString == "COORDINATE_Y") {
    return ProtobufCoordinate::COORDINATE_Y;
  } else if (protobufCoordinateString == "COORDINATE_Z") {
    return ProtobufCoordinate::COORDINATE_Z;
  } else {
    return ProtobufCoordinate::COORDINATE_NONE;
  }
}

ProtobufNormString AccMetaData::protobufNormToString(const ProtobufNorm protobufNorm) {
  switch (protobufNorm) {
    case ProtobufNorm::NORM_EUCLIDEAN_DIFFERENCES_NORM: {
      return "NORM_EUCLIDEAN_DIFFERENCES_NORM";
    }
    default: {
      return "NORM_NONE";
    }
  }
}

ProtobufNorm AccMetaData::protobufNormFromString(const ProtobufNormString protobufNormString) {
  if (protobufNormString == "NORM_EUCLIDEAN_DIFFERENCES_NORM") {
    return ProtobufNorm::NORM_EUCLIDEAN_DIFFERENCES_NORM;
  } else {
    return ProtobufNorm::NORM_NONE;
  }
}
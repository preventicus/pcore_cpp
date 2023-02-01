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
#include "AccMetaData.h"

AccMetaData::AccMetaData(ProtobufCoordinate coordinate, ProtobufNorm norm) {
  if (coordinate != ProtobufCoordinate::COORDINATE_NONE && norm != ProtobufNorm::NORM_NONE) {
    throw std::invalid_argument("one enum type has to be initialized");
  }
  this->coordinate = coordinate;
  this->norm = norm;
}

AccMetaData::AccMetaData(const ProtobufAccMetaData& protobufAccMetaData) {
  this->deserialize(protobufAccMetaData);
}

AccMetaData::AccMetaData(){};

ProtobufCoordinate AccMetaData::getCoordinate() {
  return this->coordinate;
}
ProtobufNorm AccMetaData::getNorm() {
  return this->norm;
}

bool AccMetaData::isSet() {
  return !(this->coordinate == ProtobufCoordinate::COORDINATE_NONE && this->norm == ProtobufNorm::NORM_NONE);
}

bool AccMetaData::isEqual(AccMetaData& AccMetaData) {
  return this->coordinate == AccMetaData.coordinate && this->norm == AccMetaData.norm;
}

ProtobufAccMetaData AccMetaData::serialize() {
  ProtobufAccMetaData protobufAccMetaData;
  if (this->coordinate != ProtobufCoordinate::COORDINATE_NONE) {
    protobufAccMetaData.set_coordinate(this->coordinate);
  }
  if (this->norm != ProtobufNorm::NORM_NONE) {
    protobufAccMetaData.set_norm(this->norm);
  }
  return protobufAccMetaData;
}

void AccMetaData::deserialize(const ProtobufAccMetaData& protobufAccMetaData) {
  this->norm = protobufAccMetaData.norm();
  this->coordinate = protobufAccMetaData.coordinate();
}

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
AccMetaData::AccMetaData(CoordinateProtobuf coordinate) noexcept : coordinate(coordinate), norm(NormProtobuf::NORM_NONE) {}

AccMetaData::AccMetaData(NormProtobuf norm) noexcept : coordinate(CoordinateProtobuf::COORDINATE_NONE), norm(norm) {}

AccMetaData::AccMetaData(const AccMetaDataJson& accMetaDataJson)
    : coordinate(PcoreProtobuf::Convert::coordinateProtobufFromString(accMetaDataJson[PcoreJson::Key::coordinate].asString())),
      norm(PcoreProtobuf::Convert::normProtobufFromString(accMetaDataJson[PcoreJson::Key::norm].asString())) {
  if (this->hasNorm() && this->hasCoordinate())
    throw OnlyOneParameterAllowedException("AccMetaData", "Norm", "Coordinate");
}

AccMetaData::AccMetaData(const AccMetaDataProtobuf& accMetaDataProtobuf) noexcept
    : coordinate(accMetaDataProtobuf.coordinate()), norm(accMetaDataProtobuf.norm()) {}

AccMetaData::AccMetaData() noexcept : coordinate(CoordinateProtobuf::COORDINATE_NONE), norm(NormProtobuf::NORM_NONE) {}

////////////////////////////////////////////////////////////////
//                          Getter                            //
////////////////////////////////////////////////////////////////
CoordinateProtobuf AccMetaData::getCoordinate() const noexcept {
  return this->coordinate;
}

NormProtobuf AccMetaData::getNorm() const noexcept {
  return this->norm;
}

bool AccMetaData::hasNorm() const noexcept {
  return this->norm != NormProtobuf::NORM_NONE;
}

bool AccMetaData::hasCoordinate() const noexcept {
  return this->coordinate != CoordinateProtobuf::COORDINATE_NONE;
}

////////////////////////////////////////////////////////////////
//                      IPCore Methods                        //
////////////////////////////////////////////////////////////////

bool AccMetaData::isSet() const noexcept {
  return this->hasNorm() || this->hasCoordinate();
}

Json::Value AccMetaData::toJson() const noexcept {
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

void AccMetaData::serialize(AccMetaDataProtobuf* accMetaDataProtobuf) const {
  if (accMetaDataProtobuf == nullptr) {
    throw NullPointerException("AccMetaData::serialize", "accMetaDataProtobuf");
  }
  if (!this->isSet()) {
    return;
  }
  if (this->hasCoordinate() && this->hasNorm()) {
    throw OnlyOneParameterAllowedException("AccMetaData::serialize", "Coordinate", "Norm");
  }
  if (this->hasCoordinate()) {
    accMetaDataProtobuf->set_coordinate(this->coordinate);
  }
  if (this->hasNorm()) {
    accMetaDataProtobuf->set_norm(this->norm);
  }
}

void AccMetaData::switchDataForm() {
  throw ShouldNotBeCalledException("AccMetaData::switchDataForm");
}

bool AccMetaData::operator==(const IPCore<AccMetaDataProtobuf>& accMetaData) const noexcept {
  if (const auto* derived = dynamic_cast<const AccMetaData*>(&accMetaData)) {
    return this->coordinate == derived->coordinate && this->norm == derived->norm;
  }
  return false;
}

bool AccMetaData::operator!=(const IPCore<AccMetaDataProtobuf>& accMetaData) const noexcept {
  return !(*this == accMetaData);
}
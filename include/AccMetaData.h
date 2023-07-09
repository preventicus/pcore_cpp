/*

Created by Jakob Glueck, Steve Merschel 2023

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

#pragma once
#include "json/json.h"
#include "protobuf/pcore_coordinate.pb.h"
#include "protobuf/pcore_norm.pb.h"
#include "protobuf/pcore_raw.pb.h"

using ProtobufAccMetaData = com::preventicus::pcore::Raw_Sensor_Channel_AccMetadata;
using ProtobufCoordinate = com::preventicus::pcore::Coordinate;
using ProtobufNorm = com::preventicus::pcore::Norm;
using AccMetaDataJson = Json::Value;
using ProtobufCoordinateString = std::string;
using ProtobufNormString = std::string;

class AccMetaData final {
 public:
  explicit AccMetaData(ProtobufNorm norm);
  explicit AccMetaData(ProtobufCoordinate coordinate);
  explicit AccMetaData(const ProtobufAccMetaData& protobufAccMetaData);
  explicit AccMetaData(const AccMetaDataJson& accMetaDataJson);
  AccMetaData();

  ProtobufCoordinate getCoordinate() const;
  ProtobufNorm getNorm() const;
  bool hasNorm() const;
  bool hasCoordinate() const;
  bool isSet() const;
  AccMetaDataJson toJson() const;
  void serialize(ProtobufAccMetaData* protobufAccMetaData) const;

  bool operator==(const AccMetaData& accMetaData) const;
  bool operator!=(const AccMetaData& accMetaData) const;

  static ProtobufCoordinate protobufCoordinateFromString(ProtobufCoordinateString protobufCoordinateString);
  static ProtobufCoordinateString protobufCoordinateToString(ProtobufCoordinate protobufCoordinate);
  static ProtobufNorm protobufNormFromString(ProtobufNormString protobufNormString);
  static ProtobufNormString protobufNormToString(ProtobufNorm protobufNorm);

 private:
  ProtobufCoordinate coordinate;
  ProtobufNorm norm;
};

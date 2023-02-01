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
#ifndef ACCMETADATA_H
#define ACCMETADATA_H
#include <iostream>
#include "protobuf/pcore_coordinate.pb.h"
#include "protobuf/pcore_external.pb.h"
#include "protobuf/pcore_norm.pb.h"

using ProtobufAccMetaData = com::preventicus::pcore::Raw_Sensor_Channel_AccMetadata;
using ProtobufCoordinate = com::preventicus::pcore::Coordinate;
using ProtobufNorm = com::preventicus::pcore::Norm;

class AccMetaData {
 public:
  AccMetaData(ProtobufCoordinate coordinate, ProtobufNorm norm);
  AccMetaData(const ProtobufAccMetaData& protobufAccMetaData);
  AccMetaData();
  ProtobufCoordinate getCoordinate();
  ProtobufNorm getNorm();
  bool isSet();
  bool isEqual(AccMetaData& AccMetaData);
  ProtobufAccMetaData serialize();

 private:
  void deserialize(const ProtobufAccMetaData& protobufAccMetaData);
  ProtobufCoordinate coordinate;
  ProtobufNorm norm;
};

#endif  // ACCMETADATA_H
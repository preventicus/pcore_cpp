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

#include "AccMetaDataExampleFactory.h"
#include "AccMetaData.h"
#include "PcoreJson.h"
#include "PcoreProtobuf.h"

AccMetaDataJson AccMetaDataExampleFactory::buildAccMetaDataJson(const AccMetaData& accMetaData) {
  AccMetaDataJson accMetaDataJson;
  if (!accMetaData.isSet()) {
    return accMetaDataJson;
  }
  if (accMetaData.hasType<CoordinateProtobuf>()) {
    accMetaDataJson[PcoreJson::Key::coordinate] = PcoreProtobuf::Convert::coordinateProtobufToString(*accMetaData.getType<CoordinateProtobuf>());
  } else if (accMetaData.hasType<NormProtobuf>()) {
    accMetaDataJson[PcoreJson::Key::norm] = PcoreProtobuf::Convert::normProtobufToString(*accMetaData.getType<NormProtobuf>());
  }
  return accMetaDataJson;
}

AccMetaData AccMetaDataExampleFactory::accMetaDataWithNormEuclideanDifferencesNorm() {
  return AccMetaData(NormProtobuf::NORM_EUCLIDEAN_DIFFERENCES_NORM);
}

AccMetaData AccMetaDataExampleFactory::accMetaDataWithNormNone() {
  return AccMetaData(NormProtobuf::NORM_NONE);
}

AccMetaData AccMetaDataExampleFactory::accMetaDataWithCoordinateX() {
  return AccMetaData(CoordinateProtobuf::COORDINATE_X);
}

AccMetaData AccMetaDataExampleFactory::accMetaDataWithCoordinateY() {
  return AccMetaData(CoordinateProtobuf::COORDINATE_Y);
}

AccMetaData AccMetaDataExampleFactory::accMetaDataWithCoordinateZ() {
  return AccMetaData(CoordinateProtobuf::COORDINATE_Z);
}

AccMetaData AccMetaDataExampleFactory::accMetaDataWithCoordinateNone() {
  return AccMetaData(CoordinateProtobuf::COORDINATE_NONE);
}

AccMetaData AccMetaDataExampleFactory::accMetaDataNotSet() {
  return AccMetaData();
}

/*

Created by Steve Merschel 2023

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
#include <string>
#include "protobuf/pcore_color.pb.h"
#include "protobuf/pcore_coordinate.pb.h"
#include "protobuf/pcore_norm.pb.h"
#include "protobuf/pcore_raw.pb.h"
#include "protobuf/pcore_sensor_type.pb.h"

using SensorProtobuf = com::preventicus::pcore::Raw_Sensor;
using SensorTypeProtobuf = com::preventicus::pcore::SensorType;
using SensorTypeString = std::string;
using CoordinateProtobufString = std::string;
using CoordinateProtobuf = com::preventicus::pcore::Coordinate;
using NormStringProtobuf = std::string;
using NormProtobuf = com::preventicus::pcore::Norm;
using ColorStringProtobuf = std::string;
using ColorProtobuf = com::preventicus::pcore::Color;

namespace PcoreProtobuf {
class Convert {
 public:
  template <typename T, typename P, typename... Args>
  static std::vector<T> protobufToVector(P values, const Args&... args) {
    std::vector<T> vector;
    vector.reserve(values.size());

    if constexpr (std::is_same_v<T, int32_t> || std::is_same_v<T, uint32_t> || std::is_same_v<T, uint64_t>) {
      for (auto& value : values) {
        vector.push_back(value);
      }
    } else {
      for (auto& value : values) {
        vector.emplace_back(T(value, args...));
      }
    }
    return vector;
  }

  static CoordinateProtobufString coordinateProtobufToString(CoordinateProtobuf coordinateProtobuf) {
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

  static CoordinateProtobuf coordinateProtobufFromString(const CoordinateProtobufString& coordinateProtobufString) {
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

  static NormStringProtobuf normProtobufToString(NormProtobuf normProtobuf) {
    switch (normProtobuf) {
      case NormProtobuf::NORM_EUCLIDEAN_DIFFERENCES_NORM: {
        return "NORM_EUCLIDEAN_DIFFERENCES_NORM";
      }
      default: {
        return "NORM_NONE";
      }
    }
  }

  static NormProtobuf normProtobufFromString(const NormStringProtobuf& normProtobufString) {
    if (normProtobufString == "NORM_EUCLIDEAN_DIFFERENCES_NORM") {
      return NormProtobuf::NORM_EUCLIDEAN_DIFFERENCES_NORM;
    } else {
      return NormProtobuf::NORM_NONE;
    }
  }

  static ColorStringProtobuf colorProtobufToString(ColorProtobuf colorProtobuf) {
    switch (colorProtobuf) {
      case ColorProtobuf::COLOR_RED: {
        return "COLOR_RED";
      }
      case ColorProtobuf::COLOR_BLUE: {
        return "COLOR_BLUE";
      }
      case ColorProtobuf::COLOR_GREEN: {
        return "COLOR_GREEN";
      }
      default: {
        return "COLOR_NONE";
      }
    }
  }

  static ColorProtobuf colorProtobufFromString(const ColorStringProtobuf& colorStringProtobuf) {
    if (colorStringProtobuf == "COLOR_RED") {
      return ColorProtobuf::COLOR_RED;
    } else if (colorStringProtobuf == "COLOR_BLUE") {
      return ColorProtobuf::COLOR_BLUE;
    } else if (colorStringProtobuf == "COLOR_GREEN") {
      return ColorProtobuf::COLOR_GREEN;
    } else {
      return ColorProtobuf::COLOR_NONE;
    }
  }

  static SensorTypeProtobuf senorTypeFromString(const SensorTypeString& senorTypeString) {
    if (senorTypeString == "SENSOR_TYPE_PPG") {
      return SensorTypeProtobuf::SENSOR_TYPE_PPG;
    } else if (senorTypeString == "SENSOR_TYPE_ACC") {
      return SensorTypeProtobuf::SENSOR_TYPE_ACC;
    } else {
      return SensorTypeProtobuf::SENSOR_TYPE_NONE;
    }
  }

  static SensorTypeString senorTypeToString(const SensorTypeProtobuf sensorTypeProtobuf) {
    switch (sensorTypeProtobuf) {
      case SensorTypeProtobuf::SENSOR_TYPE_ACC: {
        return "SENSOR_TYPE_ACC";
      }
      case SensorTypeProtobuf::SENSOR_TYPE_PPG: {
        return "SENSOR_TYPE_PPG";
      }
      default: {
        return "SENSOR_TYPE_NONE";
      }
    }
  }
};
}  // namespace PcoreProtobuf

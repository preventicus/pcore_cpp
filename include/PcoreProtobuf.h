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

/**
 * @typedef SensorProtobuf
 * @brief Alias for the Protobuf representation of a sensor.
 */
using SensorProtobuf = com::preventicus::pcore::Raw_Sensor;

/**
 * @typedef SensorTypeProtobuf
 * @brief Alias for the Protobuf representation of a sensor type.
 */
using SensorTypeProtobuf = com::preventicus::pcore::SensorType;

/**
 * @typedef SensorTypeString
 * @brief Alias for a string representing a sensor type.
 */
using SensorTypeString = std::string;

/**
 * @typedef CoordinateProtobufString
 * @brief Alias for a string representing a coordinate in the Protobuf representation.
 */
using CoordinateProtobufString = std::string;

/**
 * @typedef CoordinateProtobuf
 * @brief Alias for the Protobuf representation of a coordinate.
 */
using CoordinateProtobuf = com::preventicus::pcore::Coordinate;

/**
 * @typedef NormStringProtobuf
 * @brief Alias for a string representing a norm in the Protobuf representation.
 */
using NormStringProtobuf = std::string;

/**
 * @typedef NormProtobuf
 * @brief Alias for the Protobuf representation of a norm.
 */
using NormProtobuf = com::preventicus::pcore::Norm;

/**
 * @typedef ColorStringProtobuf
 * @brief Alias for a string representing a color in the Protobuf representation.
 */
using ColorStringProtobuf = std::string;

/**
 * @typedef ColorProtobuf
 * @brief Alias for the Protobuf representation of a color.
 */
using ColorProtobuf = com::preventicus::pcore::Color;

namespace PcoreProtobuf {

/**
 * @class Convert
 * @brief A helper class that provides conversion functions between Protobuf enums and strings.
 */
class Convert {
 public:
  template <typename T, typename P, typename... Args>
  static std::vector<T> protobufToVector(P values, const Args&... args) noexcept {
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

  /**
   * @brief Convert a Protobuf coordinate to its string representation.
   * @param coordinateProtobuf The Protobuf coordinate to convert.
   * @return The string representation of the Protobuf coordinate.
   */
  static CoordinateProtobufString coordinateProtobufToString(CoordinateProtobuf coordinateProtobuf) noexcept {
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

  /**
   * @brief Convert a string representation of a coordinate to its Protobuf enum value.
   * @param coordinateProtobufString The string representation of the coordinate.
   * @return The Protobuf coordinate enum value.
   */
  static CoordinateProtobuf coordinateProtobufFromString(const CoordinateProtobufString& coordinateProtobufString) noexcept {
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

  /**
   * @brief Convert a Protobuf norm to its string representation.
   * @param normProtobuf The Protobuf norm to convert.
   * @return The string representation of the Protobuf norm.
   */
  static NormStringProtobuf normProtobufToString(NormProtobuf normProtobuf) noexcept {
    switch (normProtobuf) {
      case NormProtobuf::NORM_EUCLIDEAN_DIFFERENCES_NORM: {
        return "NORM_EUCLIDEAN_DIFFERENCES_NORM";
      }
      default: {
        return "NORM_NONE";
      }
    }
  }

  /**
   * @brief Convert a string representation of a norm to its Protobuf enum value.
   * @param normProtobufString The string representation of the norm.
   * @return The Protobuf norm enum value.
   */
  static NormProtobuf normProtobufFromString(const NormStringProtobuf& normProtobufString) noexcept {
    if (normProtobufString == "NORM_EUCLIDEAN_DIFFERENCES_NORM") {
      return NormProtobuf::NORM_EUCLIDEAN_DIFFERENCES_NORM;
    } else {
      return NormProtobuf::NORM_NONE;
    }
  }

  /**
   * @brief Convert a Protobuf color to its string representation.
   * @param colorProtobuf The Protobuf color to convert.
   * @return The string representation of the Protobuf color.
   */
  static ColorStringProtobuf colorProtobufToString(ColorProtobuf colorProtobuf) noexcept {
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

  /**
   * @brief Convert a string representation of a color to its Protobuf enum value.
   * @param colorStringProtobuf The string representation of the color.
   * @return The Protobuf color enum value.
   */
  static ColorProtobuf colorProtobufFromString(const ColorStringProtobuf& colorStringProtobuf) noexcept {
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

  /**
   * @brief Convert a string representation of a sensor type to its Protobuf enum value.
   * @param sensorTypeString The string representation of the sensor type.
   * @return The Protobuf sensor type enum value.
   */
  static SensorTypeProtobuf senorTypeFromString(const SensorTypeString& senorTypeString) noexcept {
    if (senorTypeString == "SENSOR_TYPE_PPG") {
      return SensorTypeProtobuf::SENSOR_TYPE_PPG;
    } else if (senorTypeString == "SENSOR_TYPE_ACC") {
      return SensorTypeProtobuf::SENSOR_TYPE_ACC;
    } else {
      return SensorTypeProtobuf::SENSOR_TYPE_NONE;
    }
  }

  /**
   * @brief Convert a Protobuf sensor type to its string representation.
   * @param sensorTypeProtobuf The Protobuf sensor type to convert.
   * @return The string representation of the Protobuf sensor type.
   */
  static SensorTypeString senorTypeToString(const SensorTypeProtobuf sensorTypeProtobuf) noexcept {
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

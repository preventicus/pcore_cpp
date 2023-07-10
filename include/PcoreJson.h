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

using JsonKey = std::string;

namespace PcoreJson {
namespace Key {
const JsonKey data = "data";
const JsonKey header = "header";
const JsonKey time_zone_offset_min = "time_zone_offset_min";
const JsonKey pcore_version = "pcore_version";
const JsonKey major = "major";
const JsonKey minor = "minor";
const JsonKey patch = "patch";
const JsonKey data_form = "data_form";
const JsonKey raw = "raw";
const JsonKey sensors = "sensors";
const JsonKey channels = "channels";
const JsonKey ppg_metadata = "ppg_metadata";
const JsonKey wavelength_nm = "wavelength_nm";
const JsonKey color = "color";
const JsonKey absolute_block = "absolute_block";
const JsonKey absolute_values = "absolute_values";
const JsonKey absolute_timestamps_container = "absolute_timestamps_container";
const JsonKey unix_timestamps_ms = "unix_timestamps_ms";
const JsonKey sensor_type = "sensor_type";
const JsonKey differential_blocks = "differential_blocks";
const JsonKey differential_values = "differential_values";
const JsonKey differential_timestamps_container = "differential_timestamps_container";
const JsonKey first_unix_timestamp_ms = "first_unix_timestamp_ms";
const JsonKey block_differences_ms = "block_differences_ms";
const JsonKey timestamps_differences_ms = "timestamps_differences_ms";
const JsonKey acc_metadata = "acc_metadata";
const JsonKey coordinate = "coordinate";
const JsonKey norm = "norm";
}  // namespace Key

class Convert {
 public:
  template <typename T, typename... Args>
  static std::vector<T> Json2Vector(const Json::Value& jsonValue, const JsonKey& jsonKey, const Args&... args) {
    Json::Value values = jsonValue[jsonKey];
    std::vector<T> vector;
    vector.reserve(values.size());

    if constexpr (std::is_same_v<T, int32_t>) {
      for (auto& value : values) {
        vector.emplace_back(value.asInt());
      }
    } else if constexpr (std::is_same_v<T, uint32_t>) {
      for (auto& value : values) {
        vector.emplace_back(value.asUInt());
      }
    } else if constexpr ((std::is_same_v<T, uint64_t>)) {
      for (auto& value : values) {
        vector.emplace_back(value.asUInt64());
      }
    } else {
      for (auto& value : values) {
        vector.emplace_back(T(value, args...));
      }
    }
    return vector;
  }

  template <typename T, typename... Args>
  static Json::Value Vector2Json(std::vector<T> vector, Args&... args) {
    Json::Value jsonValues(Json::arrayValue);

    if constexpr (std::is_same_v<T, int32_t>) {
      for (auto& element : vector) {
        jsonValues.append(element);
      }
    } else if constexpr (std::is_same_v<T, uint32_t>) {
      for (auto& element : vector) {
        jsonValues.append(element);
      }
    } else if constexpr ((std::is_same_v<T, uint64_t>)) {
      for (auto& element : vector) {
        jsonValues.append(element);
      }
    } else {
      for (auto& element : vector) {
        jsonValues.append(element.toJson(args...));
      }
    }
    return jsonValues;
  }

  template <typename T>
  static T Json2Value(const Json::Value& jsonValue, const JsonKey& jsonKey) {
    if constexpr (std::is_same_v<T, int32_t>) {
      return jsonValue[jsonKey].asInt();
    } else if constexpr (std::is_same_v<T, uint32_t>) {
      if (jsonValue[jsonKey].asInt() < 0) {
        throw std::invalid_argument(jsonKey + " is negative in json.");
      }
      return jsonValue[jsonKey].asUInt();
    }
  }
};
}  // namespace PcoreJson

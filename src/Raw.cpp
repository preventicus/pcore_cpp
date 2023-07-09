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

#include "Raw.h"

Raw::Raw(Sensors& sensors) : sensors(sensors) {}

Raw::Raw(const ProtobufRaw& protobufRaw)
    : sensors([&]() {
        auto protobufSensors = protobufRaw.sensors();
        Sensors sensors{};
        sensors.reserve(protobufSensors.size());
        for (auto& protobufSensor : protobufSensors) {
          sensors.emplace_back(Sensor(protobufSensor));
        }
        return sensors;
      }()) {}

Raw::Raw(RawJson& rawJson, DataForm dataForm)
    : sensors([&]() {
        Sensors sensors;
        SensorsJson sensorsJson = rawJson["sensors"];
        sensors.reserve(sensorsJson.size());
        for (auto& sensorJson : sensorsJson) {
          sensors.emplace_back(Sensor(sensorJson, dataForm));
        }
        return sensors;
      }()) {}

Raw::Raw() : sensors({}) {}

Sensors Raw::getSensors() const {
  return this->sensors;
}

bool Raw::operator==(const Raw& raw) const {
  if (this->sensors.size() != raw.sensors.size()) {
    return false;
  }
  for (size_t i = 0; i < this->sensors.size(); i++) {
    if (this->sensors[i] != raw.sensors[i]) {
      return false;
    }
  }
  return true;
}

bool Raw::operator!=(const Raw& raw) const {
  return !(*this == raw);
}

void Raw::serialize(ProtobufRaw* protobufRaw) const {
  if (protobufRaw == nullptr) {
    throw std::invalid_argument("protobufRaw is a null pointer");
  }
  for (auto& sensor : this->sensors) {
    ProtobufSensor* protobufSensor = protobufRaw->add_sensors();
    sensor.serialize(protobufSensor);
  }
}

void Raw::switchDataForm(const DataForm currentDataForm) {
  for (auto& sensor : this->sensors) {
    sensor.switchDataForm(currentDataForm);
  }
}

RawJson Raw::toJson(const DataForm dataForm) const {
  RawJson rawJson;
  SensorsJson sensorsJson(Json::arrayValue);
  for (auto& sensor : this->sensors) {
    sensorsJson.append(sensor.toJson(dataForm));
  }
  rawJson["sensors"] = sensorsJson;
  return rawJson;
}

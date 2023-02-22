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

#include "Raw.h"

Raw::Raw(std::vector<Sensor> sensors) : sensors(sensors) {}

Raw::Raw(const ProtobufRaw& protobufRaw) {
  this->deserialize(protobufRaw);
}

Raw::Raw(Json::Value& raw, DataForm dataForm) {
  std::vector<Sensor> sensors;
  Json::Value rawSensorsJson = raw["sensors"];
  Json::Value::ArrayIndex n = raw["sensors"].size();
  sensors.reserve(n);
  for (auto& sensor : rawSensorsJson) {
    sensors.push_back(Sensor(sensor, dataForm));
  }
  this->sensors = sensors;
}

Raw::Raw() {
  this->sensors = std::vector<Sensor>{};
}

std::vector<Sensor> Raw::getSensors() {
  return this->sensors;
}

bool Raw::isEqual(Raw& raw) {
  if (this->sensors.size() != raw.sensors.size()) {
    return false;
  }
  for (size_t i = 0; i < this->sensors.size(); i++) {
    if (!this->sensors[i].isEqual(raw.sensors[i])) {
      return false;
    }
  }
  return true;
}

void Raw::serialize(ProtobufRaw* protobufRaw) {
  if (protobufRaw == nullptr) {
    throw std::invalid_argument("protobufRaw is a null pointer");
  }
  for (auto& sensor : this->sensors) {
    ProtobufSensor* protobufSensor = protobufRaw->add_sensors();
    sensor.serialize(protobufSensor);
  }
}

Json::Value Raw::toJson(DataForm dataForm) {
  Json::Value sensors(Json::arrayValue);
  Json::Value raw;
  for (auto& sensor : this->sensors) {
    sensors.append(sensor.toJson(dataForm));
  }
  raw["sensors"] = sensors;
  return raw;
}

void Raw::deserialize(const ProtobufRaw& protobufRaw) {
  std::vector<Sensor> sensors{};
  for (auto& protobufSensor : protobufRaw.sensors()) {
    sensors.push_back(Sensor(protobufSensor));
  }
  this->sensors = sensors;
}

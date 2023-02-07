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

Raw::Raw(std::vector<Sensor> sensor) : sensor(sensor) {}

Raw::Raw(const ProtobufRaw& protobufRaw) {
  this->deserialize(protobufRaw);
}

Raw::Raw() {
  this->sensor = std::vector<Sensor>{};
}

std::vector<Sensor> Raw::getSensor() {
  return this->sensor;
}

bool Raw::isEqual(Raw& raw) {
  if (this->sensor.size() != raw.sensor.size()) {
    return false;
  }
  for (size_t i = 0; i < this->sensor.size(); i++) {
    if (!this->sensor[i].isEqual(raw.sensor[i])) {
      return false;
    }
  }
  return true;
}

void Raw::serialize(ProtobufRaw* protobufRaw) {
  if (protobufRaw == nullptr) {
    throw std::invalid_argument("protobufRaw is a null pointer");
  }
  for (auto& sensors : this->sensor) {
    ProtobufSensor* protobufSensor = protobufRaw->add_sensors();
    sensors.serialize(protobufSensor);
  }
}

void Raw::deserialize(const ProtobufRaw& protobufRaw) {
  std::vector<Sensor> sensor{};
  for (auto& protobufSensor : protobufRaw.sensors()) {
    sensor.push_back(Sensor(protobufSensor));
  }
  this->sensor = sensor;
}

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
#include <utility>
#include "PcoreJson.h"
#include "PcoreProtobuf.h"

Raw::Raw(Sensors sensors, DataForm dataForm) : sensors(std::move(sensors)), dataForm(dataForm) {}

Raw::Raw(const RawProtobuf& rawProtobuf)
    : sensors(PcoreProtobuf::Convert::protoBufToVector<Sensor>(rawProtobuf.sensors())), dataForm([&]() {
        if (rawProtobuf.sensors().empty()) {
          return DataForm::DATA_FORM_NONE;
        }
        return DataForm::DATA_FORM_DIFFERENTIAL;
      }()) {}

Raw::Raw(const RawJson& rawJson, DataForm dataForm)
    : sensors(PcoreJson::Convert::jsonToVector<Sensor>(rawJson, PcoreJson::Key::sensors, dataForm)), dataForm(dataForm) {}

Raw::Raw() : sensors({}), dataForm(DataForm::DATA_FORM_NONE) {}

Sensors Raw::getSensors() const {
  return this->sensors;
}

DataForm Raw::getDataFrom() const {  // TODO unit tests
  return this->dataForm;
}

bool Raw::operator==(const IPCore<RawProtobuf>& raw) const {
  const auto* derived = dynamic_cast<const Raw*>(&raw);
  if (derived == nullptr) {
    return false;
  }
  const auto numberOfSensors = this->sensors.size();
  if (numberOfSensors != derived->sensors.size()) {
    return false;
  }
  for (size_t i = 0; i < numberOfSensors; i++) {
    if (this->sensors[i] != derived->sensors[i]) {
      return false;
    }
  }
  return this->dataForm == derived->dataForm;  // TODO unittests for dataform
}

bool Raw::operator!=(const IPCore<RawProtobuf>& raw) const {
  return !(*this == raw);
}

void Raw::serialize(RawProtobuf* rawProtobuf) const {
  if (rawProtobuf == nullptr) {
    throw std::invalid_argument("rawProtobuf is a null pointer");
  }
  if (!this->isSet()) {
    return;
  }
  for (const auto& sensor : this->sensors) {
    auto* sensorProtobuf = rawProtobuf->add_sensors();
    sensor.serialize(sensorProtobuf);
  }
}

void Raw::switchDataForm() {
  if (!this->isSet()) {
    return;
  }
  for (auto& sensor : this->sensors) {
    sensor.switchDataForm();
  }
  switch (this->dataForm) {
    case DataForm::DATA_FORM_DIFFERENTIAL: {
      this->dataForm = DataForm::DATA_FORM_ABSOLUTE;
      break;
    }
    case DataForm::DATA_FORM_ABSOLUTE: {
      this->dataForm = DataForm::DATA_FORM_DIFFERENTIAL;
      break;
    }
    case DataForm::DATA_FORM_NONE: {
      throw std::runtime_error("dataForm is NONE");  // should not happen, since it is intercepted by isSet guard above
    }
  }
}

RawJson Raw::toJson() const {
  RawJson rawJson;
  if (!this->isSet()) {
    return rawJson;
  }
  rawJson[PcoreJson::Key::sensors] = PcoreJson::Convert::vectorToJson(this->sensors);
  return rawJson;
}

bool Raw::isSet() const {
  for (const auto& sensor : this->sensors) {
    if (sensor.isSet()) {
      return true;
    }
  }
  return this->dataForm != DataForm::DATA_FORM_NONE;
}

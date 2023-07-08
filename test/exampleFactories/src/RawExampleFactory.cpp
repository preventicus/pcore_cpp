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

#include "RawExampleFactory.h"

Raw RawExampleFactory::rawWithOneSensorAccWithTwoChannelsInAbsoluteForm() {
  Sensors sensors;
  sensors.push_back(SensorExampleFactory::sensorAccWithTwoChannelsInAbsoluteForm());
  return Raw(sensors);
}

Raw RawExampleFactory::rawWithOneSensorsPpgWithTwoChannelsInAbsoluteForm() {
  Sensors sensors;
  sensors.push_back(SensorExampleFactory::sensorPpgWithTwoChannelsInAbsoluteForm());
  return Raw(sensors);
}

Raw RawExampleFactory::rawWithOneSensorAccWithTwoChannelsInDifferentialForm() {
  Sensors sensors;
  sensors.push_back(SensorExampleFactory::sensorAccWithTwoChannelsInDifferentialForm());
  return Raw(sensors);
}

Raw RawExampleFactory::rawWithOneSensorsPpgWithTwoChannelsInDifferentialForm() {
  Sensors sensors;
  sensors.push_back(SensorExampleFactory::sensorPpgWithTwoChannelsInDifferentialForm());
  return Raw(sensors);
}

Raw RawExampleFactory::rawWithTwoSensorsPpgWithTwoChannelsInDifferentialForm() {
  Sensors sensors;
  sensors.push_back(SensorExampleFactory::sensorPpgWithTwoChannelsInDifferentialForm());
  sensors.push_back(SensorExampleFactory::sensorPpgWithTwoChannelsInDifferentialForm());
  return Raw(sensors);
}

Raw RawExampleFactory::rawEmpty() {
  return Raw();
}

Raw RawExampleFactory::rawForSwitchDataFormTestInAbsoluteForm() {
  Sensors sensors;
  sensors.push_back(SensorExampleFactory::sensorForSwitchDataFromTestInAbsoluteForm());
  return Raw(sensors);
}

Raw RawExampleFactory::rawForSwitchDataFormTestInDifferentialForm() {
  Sensors sensors;
  sensors.push_back(SensorExampleFactory::sensorForSwitchDataFromTestInDifferentialForm());
  return Raw(sensors);
}

RawJson RawExampleFactory::buildRawJson(Raw raw, DataForm dataForm) {
  RawJson rawJson;
  SensorsJson sensorsJson(Json::arrayValue);
  auto sensors = raw.getSensors();
  for (auto& sensor : sensors) {
    SensorJson sensorJson = SensorExampleFactory::buildSensorJson(sensor, dataForm);
    sensorsJson.append(sensorJson);
  }
  rawJson["sensors"] = sensorsJson;
  return rawJson;
}

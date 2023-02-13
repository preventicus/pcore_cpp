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

#include "SensorExampleFactory.h"

Sensor SensorExampleFactory::normalSensor() {
  std::vector<Channel> normalVectorChannel = ChannelExampleFactory::normalVectorWithChannel();
  DifferentialTimestampsContainer normalDifferentialTimestamps = DifferentialTimestampsContainerExampleFactory::normalDifferentialTimestamps();
  return Sensor(normalVectorChannel, normalDifferentialTimestamps, ProtobufSensortype::SENSOR_TYPE_ACC);
}

Sensor SensorExampleFactory::comparableSensor() {
  std::vector<Channel> comparableVectorChannel = ChannelExampleFactory::comparableVectorWithChannel();
  AbsoluteTimestampsContainer absoluteTimestamps = AbsoluteTimestampsContainerExampleFactory::normalAbsoluteTimestamps();
  return Sensor(comparableVectorChannel, absoluteTimestamps, ProtobufSensortype::SENSOR_TYPE_PPG);
}

std::vector<Sensor> SensorExampleFactory::normalVectorWithSensors() {
  std::vector<Sensor> sensor = {SensorExampleFactory::normalSensor()};
  return sensor;
}

std::vector<Sensor> SensorExampleFactory::comparableVectorWithSensors() {
  std::vector<Sensor> sensor = {SensorExampleFactory::comparableSensor()};
  return sensor;
}

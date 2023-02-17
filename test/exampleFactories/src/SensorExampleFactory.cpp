/*

Created by Jakob Glück 2023

Copyright © 2023 PREVENTICUS GmbH

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors
   may be used to endorse or promote products derived from this software
without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#include "SensorExampleFactory.h"

Sensor SensorExampleFactory::normalSensor() {
  std::vector<Channel> normalVectorChannel = ChannelExampleFactory::normalVectorWithChannel();
  DifferentialTimestampsContainer normalDifferentialTimestamps = DifferentialTimestampsContainerExampleFactory::normalDifferentialTimestamps();
  return Sensor(normalVectorChannel, normalDifferentialTimestamps, ProtobufSensorType::SENSOR_TYPE_ACC);
}

Sensor SensorExampleFactory::comparableSensor() {
  std::vector<Channel> comparableVectorChannel = ChannelExampleFactory::comparableVectorWithChannel();
  AbsoluteTimestampsContainer absoluteTimestamps = AbsoluteTimestampsContainerExampleFactory::normalAbsoluteTimestamps();
  return Sensor(comparableVectorChannel, absoluteTimestamps, ProtobufSensorType::SENSOR_TYPE_PPG);
}

Sensor SensorExampleFactory::sensorWithOneUnixAndOneValue() {
  std::vector<Channel> comparableVectorChannel = ChannelExampleFactory::normalVectorWithOneValueBlock();
  AbsoluteTimestampsContainer absoluteTimestamps = AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsOneElement();
  return Sensor(comparableVectorChannel, absoluteTimestamps, ProtobufSensorType::SENSOR_TYPE_PPG);
}

Sensor SensorExampleFactory::sensorWithNUllUnixAndNUllValue() {
  std::vector<Channel> comparableVectorChannel = ChannelExampleFactory::normalVectorWithNUllValueBlock();
  AbsoluteTimestampsContainer absoluteTimestamps = AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsEmpty();
  return Sensor(comparableVectorChannel, absoluteTimestamps, ProtobufSensorType::SENSOR_TYPE_PPG);
}

Sensor SensorExampleFactory::sensorWithOneUnixAndOneValueInLastBlock() {
  std::vector<Channel> comparableVectorChannel = ChannelExampleFactory::normalVectorWithOneValueInLastBlock();
  AbsoluteTimestampsContainer absoluteTimestamps = AbsoluteTimestampsContainerExampleFactory::absoluteUNixTimestampBlockWithOneUnixInLastBlock();
  return Sensor(comparableVectorChannel, absoluteTimestamps, ProtobufSensorType::SENSOR_TYPE_PPG);
}

Sensor SensorExampleFactory::sensorWithEqualTimestampsInterval() {
  std::vector<Channel> comparableVectorChannel = ChannelExampleFactory::normalVectorWithEqualTimestampIntervals();
  AbsoluteTimestampsContainer absoluteTimestamps = AbsoluteTimestampsContainerExampleFactory::absoluteTimestampsBlockWithEqualTimestampIntervals();
  return Sensor(comparableVectorChannel, absoluteTimestamps, ProtobufSensorType::SENSOR_TYPE_PPG);
}

Sensor SensorExampleFactory::absoluteJsonDataPpgSensor() {
  std::vector<Channel> comparableVectorChannel = ChannelExampleFactory::normalVectorWithAbsoluteJsonDataPpgChannel();
  AbsoluteTimestampsContainer absoluteTimestamps = AbsoluteTimestampsContainerExampleFactory::absoluteJsonDataTimestampsContainerPgg();
  return Sensor(comparableVectorChannel, absoluteTimestamps, ProtobufSensorType::SENSOR_TYPE_PPG);
}

Sensor SensorExampleFactory::absoluteJsonDataAccSensor() {
  std::vector<Channel> comparableVectorChannel = ChannelExampleFactory::normalVectorWithAbsoluteJsonDataAccChannel();
  AbsoluteTimestampsContainer absoluteTimestamps = AbsoluteTimestampsContainerExampleFactory::absoluteJsonDataTimestampsContainerAcc();
  return Sensor(comparableVectorChannel, absoluteTimestamps, ProtobufSensorType::SENSOR_TYPE_ACC);
}

Sensor SensorExampleFactory::differentialJsonDataPpgSensor() {
  std::vector<Channel> comparableVectorChannel = ChannelExampleFactory::normalVectorWithDifferentialJsonDataPpgChannel();
  DifferentialTimestampsContainer differentialTimestampsContainer =
      DifferentialTimestampsContainerExampleFactory::differentiaJsonDataTimestampsContainerPpg();
  return Sensor(comparableVectorChannel, differentialTimestampsContainer, ProtobufSensorType::SENSOR_TYPE_PPG);
}

Sensor SensorExampleFactory::differentialJsonDataAccSensor() {
  std::vector<Channel> comparableVectorChannel = ChannelExampleFactory::normalVectorWithDifferentialJsonDataAccChannel();
  DifferentialTimestampsContainer differentialTimestampsContainer =
      DifferentialTimestampsContainerExampleFactory::differentiaJsonDataTimestampsContainerAcc();
  return Sensor(comparableVectorChannel, differentialTimestampsContainer, ProtobufSensorType::SENSOR_TYPE_ACC);
}

std::vector<Sensor> SensorExampleFactory::normalVectorWithSensors() {
  std::vector<Sensor> sensor = {SensorExampleFactory::normalSensor()};
  return sensor;
}

std::vector<Sensor> SensorExampleFactory::comparableVectorWithSensors() {
  std::vector<Sensor> sensor = {SensorExampleFactory::comparableSensor()};
  return sensor;
}

std::vector<Sensor> SensorExampleFactory::vectorWithAbsoluteJsonDataSensor() {
  std::vector<Sensor> sensor = {SensorExampleFactory::absoluteJsonDataPpgSensor(), SensorExampleFactory::absoluteJsonDataAccSensor()};
  return sensor;
}

std::vector<Sensor> SensorExampleFactory::vectorWithDifferentialJsonDataSensor() {
  std::vector<Sensor> sensor = {SensorExampleFactory::differentialJsonDataPpgSensor(), SensorExampleFactory::differentialJsonDataAccSensor()};
  return sensor;
}
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
#ifndef SENSOR_H
#define SENSOR_H

#include "AbsoluteTimestamps.h"
#include "Channel.h"
#include "DataFormat.h"
#include "DifferentialBlock.h"
#include "DifferentialTimestamps.h"
#include "protobuf/pcore_external.pb.h"
#include "protobuf/pcore_sensor_type.pb.h"

using ProtobufSensor = com::preventicus::pcore::Raw_Sensor;
using ProtobufSensortype = com::preventicus::pcore::SensorType;
using ProtobufTimestampContainer = com::preventicus::pcore::Raw_Sensor::TimestampsContainer;

class Sensor {
 public:
  Sensor(std::vector<Channel> channels,
         DifferentialTimestamps differentialTimestamps,
         AbsoluteTimestamps absoluteTimestamps,
         ProtobufSensortype sensorType);
  Sensor(const ProtobufSensor& protobufSensor);
  Sensor();
  ProtobufSensortype getSensorType();
  DataForm getTimestampForm();
  std::vector<Channel> getChannels();
  DifferentialTimestamps getDifferentialTimestamps();
  AbsoluteTimestamps getAbsoluteTimestamps();
  uint64_t calculateBlockIntervalsSumFor(size_t idxBlock);
  bool isEqual(Sensor& Sensor);
  void serialize(ProtobufSensor* protobufSensor);
  uint32_t firstTimestamp();
  uint32_t lastTimestamp();
  uint32_t duration();

 private:
  void deserialize(const ProtobufSensor& protobufSensor);
  ProtobufSensortype sensorType;
  std::vector<Channel> channels;
  DifferentialTimestamps differentialTimestamps;
  AbsoluteTimestamps absoluteTimestamps;
};

#endif  // SENSOR_H
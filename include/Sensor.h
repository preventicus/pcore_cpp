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

#pragma once
#include "AbsoluteTimestampsContainer.h"
#include "Channel.h"
#include "DifferentialTimestampsContainer.h"
#include "protobuf/pcore_raw.pb.h"
#include "protobuf/pcore_sensor_type.pb.h"

using ProtobufSensor = com::preventicus::pcore::Raw_Sensor;

class Sensor final {
 public:
  Sensor(std::vector<Channel> channels, DifferentialTimestampsContainer differentialTimestampsContainer, ProtobufSensorType protobufSensorType);
  Sensor(std::vector<Channel> channels, AbsoluteTimestampsContainer absoluteTimestampsContainer, ProtobufSensorType protobufSensorType);
  Sensor(Json::Value& sensor, DataForm dataForm);
  Sensor(const ProtobufSensor& protobufSensor);
  Sensor();

  ProtobufSensorType getSensorType();
  std::vector<Channel> getChannels();
  DifferentialTimestampsContainer getDifferentialTimestamps();
  AbsoluteTimestampsContainer getAbsoluteTimestamps();
  uint64_t getFirstTimestamp();
  uint64_t getLastTimestamp();
  uint64_t getDuration();

  bool isEqual(Sensor& Sensor);
  Json::Value toJson(DataForm dataForm);
  void serialize(ProtobufSensor* protobufSensor);

 private:
  AbsoluteTimestampsContainer calculateAbsoluteTimestamps(DifferentialTimestampsContainer differentialTimestamps);
  DifferentialTimestampsContainer calculateDifferentialTimestamps(AbsoluteTimestampsContainer absoluteTimestamps, std::vector<size_t> blocksIdxs);
  std::vector<size_t> findBlocksIdxs();

  std::string toString(ProtobufSensorType protobufSensorType);
  ProtobufSensorType toEnum(Json::Value protobufSensorType);
  void deserialize(const ProtobufSensor& protobufSensor);

  ProtobufSensorType protobufSensorType;
  std::vector<Channel> channels;
  DifferentialTimestampsContainer differentialTimestampsContainer;
  AbsoluteTimestampsContainer absoluteTimestampsContainer;
};

/*

Created by Jakob Glueck, Steve Merschel 2023

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
#include "IPCore.h"
#include "protobuf/pcore_raw.pb.h"
#include "protobuf/pcore_sensor_type.pb.h"

using namespace PCore;

using SensorProtobuf = com::preventicus::pcore::Raw_Sensor;
using Channels = std::vector<Channel>;
using SensorTypeString = std::string;
using SensorJson = Json::Value;
using Duration = uint64_t;
using ChannelsJson = Json::Value;

namespace PCore {
class Sensor final : public IPCore<SensorProtobuf> {
 public:
  explicit Sensor(Channels channels, DifferentialTimestampsContainer differentialTimestampsContainer, SensorTypeProtobuf sensorTypeProtobuf);
  explicit Sensor(Channels channels, AbsoluteTimestampsContainer absoluteTimestampsContainer, SensorTypeProtobuf sensorTypeProtobuf);
  explicit Sensor(const SensorJson& sensorJson, DataForm dataForm);
  explicit Sensor(const SensorProtobuf& sensorProtobuf);
  Sensor();

  [[nodiscard]] SensorTypeProtobuf getSensorType() const;
  [[nodiscard]] Channels getChannels() const;
  [[nodiscard]] DifferentialTimestampsContainer getDifferentialTimestampsContainer() const;
  [[nodiscard]] AbsoluteTimestampsContainer getAbsoluteTimestampsContainer() const;
  [[nodiscard]] UnixTimestamp getFirstUnixTimestamp_ms(DataForm currentDataForm) const;
  [[nodiscard]] UnixTimestamp getLastUnixTimestamp_ms(DataForm currentDataForm) const;
  [[nodiscard]] Duration getDuration_ms(DataForm currentDataForm) const;
  [[nodiscard]] DataForm getDataFrom() const;

  // bool isSet();
  [[nodiscard]] SensorJson toJson() const final;
  void serialize(SensorProtobuf* sensorProtobuf) const final;
  void switchDataForm() final;

  static SensorTypeProtobuf senorTypeFromString(SensorTypeString senorTypeString);
  static SensorTypeString senorTypeToString(SensorTypeProtobuf sensorTypeProtobuf);

  bool operator==(const Sensor& sensor) const;
  bool operator!=(const Sensor& sensor) const;

 private:
  [[nodiscard]] AbsoluteTimestampsContainer calculateAbsoluteTimestamps(const DifferentialTimestampsContainer& differentialTimestampsContainer) const;
  [[nodiscard]] DifferentialTimestampsContainer calculateDifferentialTimestamps(const AbsoluteTimestampsContainer& absoluteTimestampsContainer,
                                                                                const BlockIdxs& blockIdxs) const;
  [[nodiscard]] BlockIdxs findBlockIdxs() const;

  SensorTypeProtobuf sensorType;
  Channels channels;
  DifferentialTimestampsContainer differentialTimestampsContainer;
  AbsoluteTimestampsContainer absoluteTimestampsContainer;
  DataForm dataForm;
};
}  // namespace PCore
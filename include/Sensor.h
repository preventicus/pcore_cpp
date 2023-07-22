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

using namespace PCore;

using Channels = std::vector<Channel>;

using SensorJson = Json::Value;
using Duration = uint64_t;
using ChannelsJson = Json::Value;
using Timestamps = std::optional<std::variant<AbsoluteTimestampsContainer, DifferentialTimestampsContainer>>;

namespace PCore {
class Sensor final : public IPCore<SensorProtobuf> {
 public:
  ////////////////////////////////////////////////////////////////
  //                       Constructors                         //
  ////////////////////////////////////////////////////////////////
  explicit Sensor(Channels channels, DifferentialTimestampsContainer differentialTimestampsContainer, SensorTypeProtobuf sensorTypeProtobuf) noexcept;
  explicit Sensor(Channels channels, AbsoluteTimestampsContainer absoluteTimestampsContainer, SensorTypeProtobuf sensorTypeProtobuf) noexcept;
  explicit Sensor(const SensorJson& sensorJson, DataForm dataForm);
  explicit Sensor(const SensorProtobuf& sensorProtobuf) noexcept;
  explicit Sensor() noexcept;

  ////////////////////////////////////////////////////////////////
  //                          Getter                            //
  ////////////////////////////////////////////////////////////////
  [[nodiscard]] SensorTypeProtobuf getSensorType() const noexcept;
  [[nodiscard]] Channels getChannels() const noexcept;
  template <typename T>
  [[nodiscard]] std::optional<T> getTimestamps() const noexcept;
  template <typename T>
  [[nodiscard]] bool hasTimestamps() const noexcept;
  [[nodiscard]] DataForm getDataFrom() const noexcept;
  [[nodiscard]] UnixTimestamp getFirstUnixTimestampInMs() const noexcept;
  [[nodiscard]] UnixTimestamp getLastUnixTimestampInMs() const noexcept;
  [[nodiscard]] Duration getDurationInMs() const noexcept;

  ////////////////////////////////////////////////////////////////
  //                     Interface Methode                      //
  ////////////////////////////////////////////////////////////////
  [[nodiscard]] bool isSet() const noexcept final;
  [[nodiscard]] SensorJson toJson() const noexcept final;
  void serialize(SensorProtobuf* sensorProtobuf) const final;
  void switchDataForm() noexcept final;

  bool operator==(const IPCore<SensorProtobuf>& sensor) const noexcept final;
  bool operator!=(const IPCore<SensorProtobuf>& sensor) const noexcept final;

 private:
  ////////////////////////////////////////////////////////////////
  //                      IPCore Methods                        //
  ////////////////////////////////////////////////////////////////
  [[nodiscard]] AbsoluteTimestampsContainer calculateAbsoluteTimestamps(
      const DifferentialTimestampsContainer& differentialTimestampsContainer) const noexcept;
  [[nodiscard]] DifferentialTimestampsContainer calculateDifferentialTimestamps(const AbsoluteTimestampsContainer& absoluteTimestampsContainer,
                                                                                const BlockIdxs& blockIdxs) const noexcept;
  [[nodiscard]] BlockIdxs findBlockIdxs() const noexcept;
  [[nodiscard]] UnixTimestamp calculateFirstUnixTimestampInLastBlock() const noexcept;

  ////////////////////////////////////////////////////////////////
  //                          Members                           //
  ////////////////////////////////////////////////////////////////
  SensorTypeProtobuf sensorType;
  Channels channels;
  Timestamps timestamps;
};
}  // namespace PCore
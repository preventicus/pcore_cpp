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

#pragma once
#include "PcoreJsonKey.h"
#include "json/json.h"
#include "protobuf/pcore_color.pb.h"
#include "protobuf/pcore_raw.pb.h"

using ProtobufColor = com::preventicus::pcore::Color;
using ProtobufPpgMetaData = com::preventicus::pcore::Raw_Sensor_Channel_PpgMetadata;
using Wavelength = uint32_t;
using PpgMetaDataJson = Json::Value;
using ProtobufColorString = std::string;

class PpgMetaData final {
 public:
  explicit PpgMetaData(ProtobufColor color);
  explicit PpgMetaData(Wavelength wavelength_nm);
  explicit PpgMetaData(const ProtobufPpgMetaData& protobufPpgMetaData);
  explicit PpgMetaData(const PpgMetaDataJson& ppgMetaData);
  PpgMetaData();

  [[nodiscard]] ProtobufColor getColor() const;
  [[nodiscard]] Wavelength getWavelength_nm() const;
  [[nodiscard]] bool hasColor() const;
  [[nodiscard]] bool hasWavelength() const;
  [[nodiscard]] bool isSet() const;
  [[nodiscard]] PpgMetaDataJson toJson() const;

  void serialize(ProtobufPpgMetaData* protobufPpgMetaData) const;

  static ProtobufColorString protobufColorToString(ProtobufColor protobufColor);
  static ProtobufColor protobufColorFromString(ProtobufColorString protobufColorString);

  bool operator==(const PpgMetaData& ppgMetaData) const;
  bool operator!=(const PpgMetaData& ppgMetaData) const;

 private:
  ProtobufColor color;
  Wavelength wavelength_nm;
};

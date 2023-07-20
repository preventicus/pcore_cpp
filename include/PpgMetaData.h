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
#include "IPCore.h"
#include "PcoreProtobuf.h"
#include "json/json.h"

using PpgMetaDataProtobuf = com::preventicus::pcore::Raw_Sensor_Channel_PpgMetadata;
using Wavelength = uint32_t;
using PpgMetaDataJson = Json::Value;

namespace PCore {
class PpgMetaData final : public IPCore<PpgMetaDataProtobuf> {
 public:
  ////////////////////////////////////////////////////////////////
  //                       Constructors                         //
  ////////////////////////////////////////////////////////////////
  explicit PpgMetaData(ColorProtobuf colorProtobuf) noexcept;
  explicit PpgMetaData(Wavelength wavelengthInNm) noexcept;
  explicit PpgMetaData(const PpgMetaDataProtobuf& ppgMetaDataProtobuf) noexcept;
  explicit PpgMetaData(const PpgMetaDataJson& ppgMetaDataJson);
  explicit PpgMetaData() noexcept;

  ////////////////////////////////////////////////////////////////
  //                          Getter                            //
  ////////////////////////////////////////////////////////////////
  [[nodiscard]] ColorProtobuf getColor() const noexcept;
  [[nodiscard]] Wavelength getWavelengthInNm() const noexcept;
  [[nodiscard]] bool hasColor() const noexcept;
  [[nodiscard]] bool hasWavelength() const noexcept;

  ////////////////////////////////////////////////////////////////
  //                      IPCore Methods                        //
  ////////////////////////////////////////////////////////////////
  [[nodiscard]] bool isSet() const noexcept final;
  [[nodiscard]] PpgMetaDataJson toJson() const noexcept final;
  void serialize(PpgMetaDataProtobuf* ppgMetaDataProtobuf) const final;
  void switchDataForm() final;

  bool operator==(const IPCore<PpgMetaDataProtobuf>& ppgMetaData) const noexcept final;
  bool operator!=(const IPCore<PpgMetaDataProtobuf>& ppgMetaData) const noexcept final;

 private:
  ////////////////////////////////////////////////////////////////
  //                          Members                           //
  ////////////////////////////////////////////////////////////////
  ColorProtobuf color;
  Wavelength wavelengthInNm;
};
}  // namespace PCore
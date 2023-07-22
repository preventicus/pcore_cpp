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

#include "AbsoluteBlock.h"
#include "AccMetaData.h"
#include "BlockIdx.h"
#include "DataForm.h"
#include "DifferentialBlock.h"
#include "IPCore.h"
#include "PpgMetaData.h"
#include "protobuf/pcore_raw.pb.h"

using namespace PCore;

using ChannelProtobuf = com::preventicus::pcore::Raw_Sensor_Channel;
using BlockIdxs = std::vector<BlockIdx>;
using DifferentialBlocks = std::vector<DifferentialBlock>;
using ChannelJson = Json::Value;
using DifferentialBlocksJson = Json::Value;
using DifferentialBlocks = std::vector<DifferentialBlock>;
using MetaData = std::optional<std::variant<AccMetaData, PpgMetaData>>;

namespace PCore {
class Channel final : public IPCore<ChannelProtobuf> {
 public:
  ////////////////////////////////////////////////////////////////
  //                       Constructors                         //
  ////////////////////////////////////////////////////////////////
  explicit Channel(AccMetaData accMetaData, AbsoluteBlock absoluteBlock) noexcept;
  explicit Channel(PpgMetaData ppgMetaData, AbsoluteBlock absoluteBlock) noexcept;
  explicit Channel(PpgMetaData ppgMetaData, DifferentialBlocks differentialBlocks) noexcept;
  explicit Channel(AccMetaData accMetaData, DifferentialBlocks differentialBlocks) noexcept;
  explicit Channel(const ChannelJson& channelJson, SensorTypeProtobuf sensorTypeProtobuf, DataForm dataForm);
  explicit Channel(const ChannelProtobuf& channelProtobuf) noexcept;
  explicit Channel() noexcept;

  ////////////////////////////////////////////////////////////////
  //                          Getter                            //
  ////////////////////////////////////////////////////////////////
  [[nodiscard]] DifferentialBlocks getDifferentialBlocks() const noexcept;
  [[nodiscard]] AbsoluteBlock getAbsoluteBlock() const noexcept;
  [[nodiscard]] std::optional<AccMetaData> getAccMetaData() const noexcept;
  [[nodiscard]] std::optional<PpgMetaData> getPpgMetaData() const noexcept;
  [[nodiscard]] SensorTypeProtobuf getSensorType() const noexcept;
  [[nodiscard]] DataForm getDataForm() const noexcept;
  [[nodiscard]] bool hasAccMetaData() const noexcept;
  [[nodiscard]] bool hasPpgMetaData() const noexcept;
  [[nodiscard]] bool hasDifferentialBlocks() const noexcept;
  [[nodiscard]] bool hasAbsoluteBlock() const noexcept;

  ////////////////////////////////////////////////////////////////
  //                      IPCore Methods                        //
  ////////////////////////////////////////////////////////////////
  [[nodiscard]] bool isSet() const noexcept final;
  [[nodiscard]] ChannelJson toJson() const noexcept final;
  void serialize(ChannelProtobuf* channelProtobuf) const final;
  void switchDataForm(const BlockIdxs& blockIdxs) noexcept;
  void switchDataForm() noexcept final;

  bool operator==(const IPCore<ChannelProtobuf>& channel) const noexcept final;
  bool operator!=(const IPCore<ChannelProtobuf>& channel) const noexcept final;

 private:
  ////////////////////////////////////////////////////////////////
  //                     Calculate Methode                      //
  ////////////////////////////////////////////////////////////////
  [[nodiscard]] DifferentialBlocks calculateDifferentialBlocks(const AbsoluteBlock& absoluteBlock, const BlockIdxs& blockIdxs) const noexcept;
  [[nodiscard]] DifferentialBlock createDifferentialBlock(BlockIdx fromBlockIdx,
                                                          BlockIdx toBlockIdx,
                                                          const AbsoluteValues& absoluteValues) const noexcept;
  [[nodiscard]] AbsoluteBlock calculateAbsoluteBlock(const DifferentialBlocks& differentialBlocks) noexcept;

  ////////////////////////////////////////////////////////////////
  //                          Members                           //
  ////////////////////////////////////////////////////////////////
  MetaData metaData;
  DifferentialBlocks differentialBlocks;
  AbsoluteBlock absoluteBlock;
  DataForm dataForm;
};
}  // namespace PCore
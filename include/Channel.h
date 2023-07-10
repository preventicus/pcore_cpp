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
#include "PpgMetaData.h"
#include "protobuf/pcore_raw.pb.h"

using namespace PCore;

using ChannelProtobuf = com::preventicus::pcore::Raw_Sensor_Channel;
using SensorTypeProtobuf = com::preventicus::pcore::SensorType;
using BlockIdxs = std::vector<BlockIdx>;
using DifferentialBlocks = std::vector<DifferentialBlock>;
using ChannelJson = Json::Value;
using DifferentialBlocksJson = Json::Value;
using DifferentialBlocks = std::vector<DifferentialBlock>;

namespace PCore {
class Channel final {
 public:
  explicit Channel(const AccMetaData& accMetadata, AbsoluteBlock absoluteBlock);
  explicit Channel(const PpgMetaData& ppgMetaData, AbsoluteBlock absoluteBlock);
  explicit Channel(const PpgMetaData& ppgMetaData, DifferentialBlocks differentialBlocks);
  explicit Channel(const AccMetaData& accMetaData, DifferentialBlocks differentialBlocks);
  explicit Channel(const ChannelJson& channelJson, SensorTypeProtobuf sensorTypeProtobuf, DataForm dataForm);
  explicit Channel(const ChannelProtobuf& channelProtobuf);
  Channel();

  [[nodiscard]] DifferentialBlocks getDifferentialBlocks() const;
  [[nodiscard]] AbsoluteBlock getAbsoluteBlock() const;
  [[nodiscard]] AccMetaData getAccMetaData() const;
  [[nodiscard]] PpgMetaData getPpgMetaData() const;

  [[nodiscard]] bool hasAccMetaData() const;
  [[nodiscard]] bool hasPpgMetaData() const;
  [[nodiscard]] bool hasDifferentialBlocks() const;
  [[nodiscard]] bool hasAbsoluteBlock() const;

  bool operator==(const Channel& channel) const;
  bool operator!=(const Channel& channel) const;

  [[nodiscard]] ChannelJson toJson(DataForm dataForm, SensorTypeProtobuf sensorTypeProtobuf) const;
  void serialize(ChannelProtobuf* channelProtobuf) const;
  void switchDataForm(const BlockIdxs& blockIdxs);
  void switchDataForm();

 private:
  [[nodiscard]] DifferentialBlocks calculateDifferentialBlocks(const AbsoluteBlock& absoluteBlock, const BlockIdxs& blockIdxs) const;
  [[nodiscard]] DifferentialBlock createDifferentialBlock(BlockIdx fromBlockIdx, BlockIdx toBlockIdx, const AbsoluteValues& absoluteValues) const;
  [[nodiscard]] AbsoluteBlock calculateAbsoluteBlock(const DifferentialBlocks& differentialBlocks) const;

  PpgMetaData ppgMetaData;
  AccMetaData accMetaData;
  DifferentialBlocks differentialBlocks;
  AbsoluteBlock absoluteBlock;
};
}  // namespace PCore
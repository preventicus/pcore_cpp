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

using ProtobufChannel = com::preventicus::pcore::Raw_Sensor_Channel;
using ProtobufSensorType = com::preventicus::pcore::SensorType;
using BlockIdxs = std::vector<BlockIdx>;
using DifferentialBlocks = std::vector<DifferentialBlock>;
using ChannelJson = Json::Value;
using DifferentialBlocksJson = Json::Value;
using DifferentialBlocks = std::vector<DifferentialBlock>;

class Channel final {
 public:
  explicit Channel(AccMetaData& accMetadata, AbsoluteBlock& absoluteBlock);
  explicit Channel(PpgMetaData& ppgMetaData, AbsoluteBlock& absoluteBlock);
  explicit Channel(PpgMetaData& ppgMetaData, DifferentialBlocks& differentialBlocks);
  explicit Channel(AccMetaData& accMetaData, DifferentialBlocks& differentialBlocks);
  explicit Channel(ChannelJson& channelJson, ProtobufSensorType protobufSensorType, DataForm dataForm);
  explicit Channel(const ProtobufChannel& protobufChannel);
  Channel();

  DifferentialBlocks getDifferentialBlocks();
  AbsoluteBlock getAbsoluteBlock();
  AccMetaData getAccMetaData();
  PpgMetaData getPpgMetaData();

  bool isEqual(Channel& channel);
  bool hasAccMetaData();
  bool hasPpgMetaData();
  bool hasDifferentialBlocks();
  bool hasAbsoluteBlock();

  ChannelJson toJson(DataForm dataForm, ProtobufSensorType protobufSensorType);
  void serialize(ProtobufChannel* protobufChannel);
  void switchDataForm(BlockIdxs& blockIdxs);
  void switchDataForm();

 private:
  DifferentialBlocks calculateDifferentialBlocks(AbsoluteBlock& absoluteBlock, BlockIdxs& blockIdxs);
  DifferentialBlock createDifferentialBlock(BlockIdx fromBlockIdx, BlockIdx toBlockIdx, AbsoluteValues& absoluteValues);
  AbsoluteBlock calculateAbsoluteBlock(DifferentialBlocks& differentialBlocks);

  PpgMetaData ppgMetaData;
  AccMetaData accMetaData;
  DifferentialBlocks differentialBlocks;
  AbsoluteBlock absoluteBlock;
};

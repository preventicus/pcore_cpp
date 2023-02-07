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
#pragma once
#include "AbsoluteBlock.h"
#include "AccMetaData.h"
#include "DataFormat.h"
#include "DifferentialBlock.h"
#include "DifferentialTimestampsContainer.h"
#include "PpgMetaData.h"

#include "protobuf/pcore_raw.pb.h"
using ProtobufChannel = com::preventicus::pcore::Raw_Sensor_Channel;
using ProtobufType = com::preventicus::pcore::SensorType;

class Channel final {
 public:
  Channel(DataForm dataForm, AbsoluteBlock& absoluteBlock, AccMetaData& accMetadata, PpgMetaData& ppgMetaData);
  Channel(DataForm dataForm, std::vector<DifferentialBlock>& differentialBlocks, AccMetaData& accMetadata, PpgMetaData& ppgMetaData);
  Channel(const ProtobufChannel& protobufChannel);
  Channel();
  std::vector<DifferentialBlock> getDifferentialBlocks();
  AbsoluteBlock getAbsoluteBlock();
  AccMetaData getAccMetaData();
  PpgMetaData getPpgMetData();
  bool isEqual(Channel& channel);
  DataForm getDataform();
  void switchInAbsoluteFrom();
  void switchInDifferentialFrom(std::vector<size_t> blocksIdxs);
  void serialize(ProtobufChannel* protobufChannel);

 private:
  std::vector<DifferentialBlock> cutValuesInDifferentialBlocks(std::vector<size_t> blocksIdxs);
  DifferentialBlock createDifferentialBlock(size_t fromIdx, size_t toIdx);
  AbsoluteBlock calculateAbsoluteForm();
  void deserialize(const ProtobufChannel& protobufChannel);
  PpgMetaData ppgMetaData;
  AccMetaData accMetadata;
  std::vector<DifferentialBlock> differentialBlocks;
  AbsoluteBlock absoluteBlock;
  DataForm dataForm;
};

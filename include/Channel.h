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
#include "AbsoluteBlock.h"
#include "AccMetaData.h"
#include "DataFormat.h"
#include "DifferentialBlock.h"
#include "PpgMetaData.h"
#include "protobuf/pcore_raw.pb.h"

using ProtobufChannel = com::preventicus::pcore::Raw_Sensor_Channel;
using ProtobufSensorType = com::preventicus::pcore::SensorType;

class Channel final {
 public:
  Channel(AccMetaData& accMetaData, AbsoluteBlock absoluteBlock, std::vector<size_t> blockIdxs);
  Channel(PpgMetaData& ppgMetaData, AbsoluteBlock absoluteBlock, std::vector<size_t> blockIdxs);
  Channel(PpgMetaData& ppgMetaData, std::vector<DifferentialBlock>& differentialBlocks);
  Channel(AccMetaData& accMetaData, std::vector<DifferentialBlock>& differentialBlocks);
  Channel(Json::Value& channel, ProtobufSensorType sensorType, std::vector<size_t> blockIdxs);
  Channel(Json::Value& channel, ProtobufSensorType sensorType);
  Channel(const ProtobufChannel& protobufChannel);
  Channel();

  std::vector<DifferentialBlock> getDifferentialBlocks();
  AbsoluteBlock getAbsoluteBlock();
  AccMetaData getAccMetaData();
  PpgMetaData getPpgMetaData();

  bool isEqual(Channel& channel);
  Json::Value toJson(DataForm dataForm, ProtobufSensorType protobufSensorType);
  void serialize(ProtobufChannel* protobufChannel);

 private:
  std::vector<DifferentialBlock> calculateDifferentialBlocks(AbsoluteBlock absoluteBlock, std::vector<size_t> blockIdxs);
  DifferentialBlock createDifferentialBlock(size_t fromIdx, size_t toIdx);
  AbsoluteBlock calculateAbsoluteBlock(std::vector<DifferentialBlock> differentialBlocks);

  void deserialize(const ProtobufChannel& protobufChannel);

  PpgMetaData ppgMetaData;
  AccMetaData accMetaData;
  std::vector<DifferentialBlock> differentialBlocks;
  AbsoluteBlock absoluteBlock;
};

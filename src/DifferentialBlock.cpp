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

#include "DifferentialBlock.h"

DifferentialBlock::DifferentialBlock(std::vector<int32_t>& differentialValues) : differentialValues(differentialValues) {}

DifferentialBlock::DifferentialBlock(const ProtobufDifferentialBlock& protobufDifferentialBlock) {
  this->deserialize(protobufDifferentialBlock);
}

DifferentialBlock::DifferentialBlock(Json::Value& differentialBlock) {
  Json::Value jsonDifferentialBlock = differentialBlock["differential_values"];
  std::vector<int32_t> differentialValues = {};
  differentialValues.reserve(jsonDifferentialBlock.size());
  for (Json::Value::ArrayIndex i = 0; i < jsonDifferentialBlock.size(); i++) {
    differentialValues.push_back(jsonDifferentialBlock[i].asInt());
  }
  this->differentialValues = differentialValues;
}

DifferentialBlock::DifferentialBlock() {
  this->differentialValues = {};
}

std::vector<int32_t> DifferentialBlock::getDifferentialValues() {
  return this->differentialValues;
}

bool DifferentialBlock::isEqual(DifferentialBlock& differentialBlock) {
  return this->differentialValues == differentialBlock.differentialValues;
}

void DifferentialBlock::serialize(ProtobufDifferentialBlock* protobufDifferentialBlock) {
  if (protobufDifferentialBlock == nullptr) {
    throw std::invalid_argument("Error in serialize: protobufDifferentialBlock is a null pointer");
  }
  for (auto& differentialValues : this->differentialValues) {
    protobufDifferentialBlock->add_differential_values(differentialValues);
  }
}

Json::Value DifferentialBlock::toJson() {
  Json::Value differentialBlock;
  Json::Value differentialValues(Json::arrayValue);
  for (auto& i : this->differentialValues) {
    differentialValues.append(i);
  }
  differentialBlock["differential_values"] = differentialValues;
  return differentialBlock;
}

void DifferentialBlock::deserialize(const ProtobufDifferentialBlock& protobufDifferentialBlock) {
  for (auto& protobufDifferentialValues : protobufDifferentialBlock.differential_values()) {
    this->differentialValues.push_back(protobufDifferentialValues);
  }
}
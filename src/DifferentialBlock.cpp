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

#include "DifferentialBlock.h"
#include <utility>

DifferentialBlock::DifferentialBlock(DifferentialValues differentialValues) : differentialValues(std::move(differentialValues)) {}

DifferentialBlock::DifferentialBlock(const DifferentialBlockProtobuf& differentialBlockProtobuf)
    : differentialValues([&]() {
        auto differentialValuesProtobuf = differentialBlockProtobuf.differential_values();
        DifferentialValues differentialValues = {};
        differentialValues.reserve(differentialValuesProtobuf.size());
        for (auto& differentialValueProtobuf : differentialValuesProtobuf) {
          this->differentialValues.push_back(differentialValueProtobuf);
        }
        return differentialValues;
      }()) {}

DifferentialBlock::DifferentialBlock(const DifferentialBlockJson& differentialBlockJson)
    : differentialValues([&]() {
        DifferentialValuesJson differentialValuesJson = differentialBlockJson[PcoreJsonKey::differential_values];
        DifferentialValues differentialValues = {};
        differentialValues.reserve(differentialValuesJson.size());
        for (auto& differentialValueJson : differentialValuesJson) {
          differentialValues.emplace_back(differentialValueJson.asInt());
        }
        return differentialValues;
      }()) {}

DifferentialBlock::DifferentialBlock() : differentialValues({}){};

DifferentialValues DifferentialBlock::getDifferentialValues() const {
  return this->differentialValues;
}

bool DifferentialBlock::isSet() const {
  return !this->differentialValues.empty();
}

bool DifferentialBlock::operator==(const DifferentialBlock& differentialBlock) const {
  return this->differentialValues == differentialBlock.differentialValues;
}

bool DifferentialBlock::operator!=(const DifferentialBlock& differentialBlock) const {
  return this->differentialValues != differentialBlock.differentialValues;
}

void DifferentialBlock::serialize(DifferentialBlockProtobuf* differentialBlockProtobuf) const {
  if (differentialBlockProtobuf == nullptr) {
    throw std::invalid_argument("Error in serialize: differentialBlockProtobuf is a null pointer");
  }
  for (auto& differentialValue : this->differentialValues) {
    differentialBlockProtobuf->add_differential_values(differentialValue);
  }
}

DifferentialBlockJson DifferentialBlock::toJson() const {
  DifferentialValuesJson differentialValuesJson(Json::arrayValue);
  for (auto& differentialValue : this->differentialValues) {
    differentialValuesJson.append(differentialValue);
  }
  DifferentialBlockJson differentialBlockJson;
  differentialBlockJson[PcoreJsonKey::differential_values] = differentialValuesJson;
  return differentialBlockJson;
}

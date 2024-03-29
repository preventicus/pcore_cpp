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
#include "Exceptions.h"
#include "PcoreJson.h"
#include "PcoreProtobuf.h"

////////////////////////////////////////////////////////////////
//                       Constructors                         //
////////////////////////////////////////////////////////////////
DifferentialBlock::DifferentialBlock(DifferentialValues differentialValues) noexcept : differentialValues(std::move(differentialValues)) {}

DifferentialBlock::DifferentialBlock(const DifferentialBlockProtobuf& differentialBlockProtobuf) noexcept
    : differentialValues(PcoreProtobuf::Convert::protobufToVector<DifferentialValue>(differentialBlockProtobuf.differential_values())) {}

DifferentialBlock::DifferentialBlock(const DifferentialBlockJson& differentialBlockJson) noexcept
    : differentialValues(PcoreJson::Convert::jsonToVector<DifferentialValue>(differentialBlockJson, PcoreJson::Key::differential_values)) {}

DifferentialBlock::DifferentialBlock() noexcept : differentialValues({}){};

////////////////////////////////////////////////////////////////
//                          Getter                            //
////////////////////////////////////////////////////////////////
DifferentialValues DifferentialBlock::getDifferentialValues() const noexcept {
  return this->differentialValues;
}

////////////////////////////////////////////////////////////////
//                      IPCore Methods                        //
////////////////////////////////////////////////////////////////
bool DifferentialBlock::isSet() const noexcept {
  return !this->differentialValues.empty();
}

DifferentialBlockJson DifferentialBlock::toJson() const noexcept {
  DifferentialBlockJson differentialBlockJson;
  if (!this->isSet()) {
    return differentialBlockJson;
  }
  differentialBlockJson[PcoreJson::Key::differential_values] = PcoreJson::Convert::vectorToJson(this->differentialValues);
  return differentialBlockJson;
}

void DifferentialBlock::serialize(DifferentialBlockProtobuf* differentialBlockProtobuf) const {
  if (differentialBlockProtobuf == nullptr) {
    throw NullPointerException("DifferentialBlock::serialize", "differentialBlockProtobuf");
  }
  if (!this->isSet()) {
    return;
  }
  for (const auto& differentialValue : this->differentialValues) {
    differentialBlockProtobuf->add_differential_values(differentialValue);
  }
}

void DifferentialBlock::switchDataForm() {
  throw ShouldNotBeCalledException("DifferentialBlock::switchDataForm");
}

bool DifferentialBlock::operator==(const IPCore<DifferentialBlockProtobuf>& differentialBlock) const noexcept {
  if (const auto* derived = dynamic_cast<const DifferentialBlock*>(&differentialBlock)) {
    return this->differentialValues == derived->differentialValues;
  }
  return false;
}

bool DifferentialBlock::operator!=(const IPCore<DifferentialBlockProtobuf>& differentialBlock) const noexcept {
  return !(*this == differentialBlock);
}
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

#include "AbsoluteBlock.h"
#include <utility>
#include "PcoreJson.h"

using namespace PCore;

AbsoluteBlock::AbsoluteBlock(AbsoluteValues absoluteValues) : absoluteValues(std::move(absoluteValues)) {}

AbsoluteBlock::AbsoluteBlock(const AbsoluteBlockJson& absoluteBlockJson)
    : absoluteValues(PcoreJson::Convert::jsonToVector<AbsoluteValue>(absoluteBlockJson, PcoreJson::Key::absolute_values)) {}

AbsoluteBlock::AbsoluteBlock() : absoluteValues({}) {}

AbsoluteValues AbsoluteBlock::getAbsoluteValues() const {
  return this->absoluteValues;
}

bool AbsoluteBlock::isSet() const {
  return !this->absoluteValues.empty();
}

bool AbsoluteBlock::operator==(const AbsoluteBlock& absoluteBlock) const {
  return this->absoluteValues == absoluteBlock.absoluteValues;
}

bool AbsoluteBlock::operator!=(const AbsoluteBlock& absoluteBlock) const {
  return this->absoluteValues != absoluteBlock.absoluteValues;
}

AbsoluteBlockJson AbsoluteBlock::toJson() const {
  AbsoluteBlockJson absoluteBlockJson;
  if (!isSet()) {
    return absoluteBlockJson;
  }
  absoluteBlockJson[PcoreJson::Key::absolute_values] = PcoreJson::Convert::vectorToJson(this->absoluteValues);
  return absoluteBlockJson;
}
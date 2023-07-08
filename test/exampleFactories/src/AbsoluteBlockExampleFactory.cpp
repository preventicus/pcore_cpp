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

#include "AbsoluteBlockExampleFactory.h"

AbsoluteBlock AbsoluteBlockExampleFactory::absoluteBlockWithThreePositiveAbsoluteValues() {
  auto absoluteValues = AbsoluteValuesExampleFactory::absoluteValuesWithThreePositiveElements();
  return AbsoluteBlock(absoluteValues);
}

AbsoluteBlock AbsoluteBlockExampleFactory::absoluteBlockWithThreeMixedAbsoluteValues() {
  auto absoluteValues = AbsoluteValuesExampleFactory::absoluteValuesWithThreeMixedElements();
  return AbsoluteBlock(absoluteValues);
}

AbsoluteBlock AbsoluteBlockExampleFactory::absoluteBlockWithThreeNegativeAbsoluteValues() {
  auto absoluteValues = AbsoluteValuesExampleFactory::absoluteValuesWithThreeNegativeElements();
  return AbsoluteBlock(absoluteValues);
}

AbsoluteBlock AbsoluteBlockExampleFactory::absoluteBlockWithOneAbsoluteValue() {
  auto absoluteValues = AbsoluteValuesExampleFactory::absoluteValuesWithOneElement();
  return AbsoluteBlock(absoluteValues);
}

AbsoluteBlock AbsoluteBlockExampleFactory::absoluteBlockWithEmptyAbsoluteValue() {
  auto absoluteValues = AbsoluteValuesExampleFactory::absoluteValuesEmpty();
  return AbsoluteBlock(absoluteValues);
}

AbsoluteBlock AbsoluteBlockExampleFactory::absoluteBlockForTestSwitchTo() {
  auto absoluteValues = AbsoluteValuesExampleFactory::absoluteValuesForTestSwitchTo();
  return AbsoluteBlock(absoluteValues);
}

AbsoluteBlockJson AbsoluteBlockExampleFactory::buildAbsoluteBlockJson(AbsoluteBlock absoluteBlock) {
  AbsoluteBlockJson absoluteBlockJson;
  if (absoluteBlock.isSet()) {
    auto absoluteValues = absoluteBlock.getAbsoluteValues();
    auto absoluteValuesJson = AbsoluteValuesExampleFactory::buildAbsoluteValuesJson(absoluteValues);
    absoluteBlockJson["absolute_values"] = absoluteValuesJson;
  }
  return absoluteBlockJson;
}

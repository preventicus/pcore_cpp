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

#include "AbsoluteBlockExampleFactory.h"

AbsoluteBlock AbsoluteBlockExampleFactory::absoluteBlockWithThreePositiveAbsoluteValues() {
  AbsoluteValues absoluteValues = AbsoluteValuesExampleFactory::absoluteValuesWithThreePositiveElements();
  return AbsoluteBlock(absoluteValues);
}

AbsoluteBlock AbsoluteBlockExampleFactory::absoluteBlockWithThreeMixedAbsoluteValues() {
  AbsoluteValues absoluteValues = AbsoluteValuesExampleFactory::absoluteValuesWithThreeMixedElements();
  return AbsoluteBlock(absoluteValues);
}

AbsoluteBlock AbsoluteBlockExampleFactory::absoluteBlockWithThreeNegativeAbsoluteValues() {
  AbsoluteValues absoluteValues = AbsoluteValuesExampleFactory::absoluteValuesWithThreeNegativeElements();
  return AbsoluteBlock(absoluteValues);
}

AbsoluteBlock AbsoluteBlockExampleFactory::absoluteBlockWithOneAbsoluteValue() {
  AbsoluteValues absoluteValues = AbsoluteValuesExampleFactory::absoluteValuesWithOneElement();
  return AbsoluteBlock(absoluteValues);
}

AbsoluteBlock AbsoluteBlockExampleFactory::absoluteBlockWithEmptyAbsoluteValue() {
  AbsoluteValues absoluteValues = AbsoluteValuesExampleFactory::absoluteValuesEmpty();
  return AbsoluteBlock(absoluteValues);
}

AbsoluteBlock AbsoluteBlockExampleFactory::absoluteBlock() {
  AbsoluteValues absoluteValues = AbsoluteValuesExampleFactory::absoluteValues();
  return AbsoluteBlock(absoluteValues);
}
AbsoluteBlock AbsoluteBlockExampleFactory::absoluteBlockWithOneValueInLastBlock() {
  AbsoluteValues absoluteValues = AbsoluteValuesExampleFactory::absoluteValuesWithOneValueInLastBlock();
  return AbsoluteBlock(absoluteValues);
}

AbsoluteBlock AbsoluteBlockExampleFactory::absoluteBlockForTestSwitchTo() {
    AbsoluteValues absoluteValues = AbsoluteValuesExampleFactory::absoluteValuesForTestSwitchTo();
    return AbsoluteBlock(absoluteValues);
}




// -------------------------------------JSON-----------------------

//AbsoluteBlockJson AbsoluteBlockExampleFactory::buildAbsoluteBlockJson(AbsoluteValuesJson& absoluteValuesJson) {
//  AbsoluteBlockJson absoluteBlockJson;
//  absoluteBlockJson["absolute_values"] = absoluteValuesJson;
//  return absoluteBlockJson;
//}

static AbsoluteBlockJson buildAbsoluteBlockJson(AbsoluteBlock& absoluteBlock) {
  AbsoluteBlockJson absoluteBlockJson;
  if(absoluteBlock.isSet()) {
    absoluteBlockJson["absolute_values"] = absoluteBlock.getAbsoluteValues();
  }
  return absoluteBlockJson;
}

AbsoluteBlock AbsoluteBlockExampleFactory::absoluteJsonDataBlockPpg1() {
  AbsoluteValues absoluteValues = AbsoluteValuesExampleFactory::absoluteJsonDataValuesPpg1();
  return AbsoluteBlock(absoluteValues);
}

AbsoluteBlock AbsoluteBlockExampleFactory::absoluteJsonDataBlockPpg2() {
  AbsoluteValues absoluteValues = AbsoluteValuesExampleFactory::absoluteJsonDataValuesPpg2();
  return AbsoluteBlock(absoluteValues);
}

AbsoluteBlock AbsoluteBlockExampleFactory::absoluteJsonDataBlockAcc() {
  AbsoluteValues absoluteValues = AbsoluteValuesExampleFactory::absoluteJsonDataValuesAcc();
  return AbsoluteBlock(absoluteValues);
}

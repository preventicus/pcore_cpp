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

AbsoluteValues AbsoluteBlockExampleFactory::absoluteValuesNormal() {
  return {1, 2, 3};
}

AbsoluteValues AbsoluteBlockExampleFactory::absoluteValuesTwoElements() {
  return {1, 2};
}

AbsoluteValues AbsoluteBlockExampleFactory::absoluteValuesOneElement() {
  return {12};
}

AbsoluteValues AbsoluteBlockExampleFactory::absoluteValues0Element() {
  return {0};
}

AbsoluteValues AbsoluteBlockExampleFactory::absoluteValuesEmpty() {
  return {};
}

AbsoluteBlock AbsoluteBlockExampleFactory::absoluteBlockNormal() {
  AbsoluteValues absoluteValues = AbsoluteBlockExampleFactory::absoluteValuesNormal();
  return AbsoluteBlock(absoluteValues);
}

AbsoluteBlock AbsoluteBlockExampleFactory::absoluteBlockTwoElement() {
  AbsoluteValues absoluteValues = AbsoluteBlockExampleFactory::absoluteValuesTwoElements();
  return AbsoluteBlock(absoluteValues);
}

AbsoluteBlock AbsoluteBlockExampleFactory::absoluteBlockOneElement() {
  AbsoluteValues absoluteValues = AbsoluteBlockExampleFactory::absoluteValuesOneElement();
  return AbsoluteBlock(absoluteValues);
}

AbsoluteBlock AbsoluteBlockExampleFactory::absoluteBlock0Element() {
  AbsoluteValues absoluteValues = AbsoluteBlockExampleFactory::absoluteValues0Element();
  return AbsoluteBlock(absoluteValues);
}

AbsoluteBlock AbsoluteBlockExampleFactory::absoluteBlockEmpty() {
  AbsoluteValues absoluteValues = AbsoluteBlockExampleFactory::absoluteValuesEmpty();
  return AbsoluteBlock(absoluteValues);
}

AbsoluteValues AbsoluteBlockExampleFactory::absoluteValues() {
  return {38763, 38771, 38780, 38793, 38784, 38780, 38780, 38783, 38790, 38782, 46321, 46327, 46318,
          46316, 46313, 46313, 46313, 46336, 58772, 58774, 58775, 58776, 58773, 19982, 19982, 19978};
}

AbsoluteValues AbsoluteBlockExampleFactory::absoluteValuesWithOneValueInLastBlock() {
  return {38763, 38771, 38780, 38793, 38784, 38780, 38780};
}

AbsoluteBlock AbsoluteBlockExampleFactory::absoluteBlock() {
  AbsoluteValues absoluteValues = AbsoluteBlockExampleFactory::absoluteValues();
  return AbsoluteBlock(absoluteValues);
}
AbsoluteBlock AbsoluteBlockExampleFactory::absoluteBlockWithOneValueInLastBlock() {
  AbsoluteValues absoluteValues = AbsoluteBlockExampleFactory::absoluteValuesWithOneValueInLastBlock();
  return AbsoluteBlock(absoluteValues);
}

// -------------------------------------JSON-----------------------

AbsoluteValues AbsoluteBlockExampleFactory::absoluteJsonDataValuesPpg1() {
  return {30021, 30023, 30027, 30022, 30020, 30020, 30030};
}

AbsoluteValues AbsoluteBlockExampleFactory::absoluteJsonDataValuesPpg2() {
  return {54834, 54830, 54836, 54842, 54841, 54841, 54830};
}

AbsoluteValues AbsoluteBlockExampleFactory::absoluteJsonDataValuesAcc() {
  return {548, 34, 234, 3435, 433, 454};
}

AbsoluteBlock AbsoluteBlockExampleFactory::absoluteJsonDataBlockPpg1() {
  AbsoluteValues absoluteValues = AbsoluteBlockExampleFactory::absoluteJsonDataValuesPpg1();
  return AbsoluteBlock(absoluteValues);
}

AbsoluteBlock AbsoluteBlockExampleFactory::absoluteJsonDataBlockPpg2() {
  AbsoluteValues absoluteValues = AbsoluteBlockExampleFactory::absoluteJsonDataValuesPpg2();
  return AbsoluteBlock(absoluteValues);
}

AbsoluteBlock AbsoluteBlockExampleFactory::absoluteJsonDataBlockAcc() {
  AbsoluteValues absoluteValues = AbsoluteBlockExampleFactory::absoluteJsonDataValuesAcc();
  return AbsoluteBlock(absoluteValues);
}

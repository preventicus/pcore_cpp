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

std::vector<int32_t> AbsoluteBlockExampleFactory::absoluteValuesNormal() {
  return {1, 2, 3};
}

std::vector<int32_t> AbsoluteBlockExampleFactory::absoluteValuesTwoElements() {
  return {1, 2};
}

std::vector<int32_t> AbsoluteBlockExampleFactory::absoluteValuesOneElement() {
  return {12};
}

std::vector<int32_t> AbsoluteBlockExampleFactory::absoluteValues0Element() {
  return {0};
}

std::vector<int32_t> AbsoluteBlockExampleFactory::absoluteValuesEmpty() {
  return {};
}

AbsoluteBlock AbsoluteBlockExampleFactory::absoluteBlockNormal() {
  std::vector<int32_t> absoluteBlock = AbsoluteBlockExampleFactory::absoluteValuesNormal();
  return AbsoluteBlock(absoluteBlock);
}

AbsoluteBlock AbsoluteBlockExampleFactory::absoluteBlockTwoElement() {
  std::vector<int32_t> absoluteBlock = AbsoluteBlockExampleFactory::absoluteValuesTwoElements();
  return AbsoluteBlock(absoluteBlock);
}

AbsoluteBlock AbsoluteBlockExampleFactory::absoluteBlockOneElement() {
  std::vector<int32_t> absoluteBlock = AbsoluteBlockExampleFactory::absoluteValuesOneElement();
  return AbsoluteBlock(absoluteBlock);
}

AbsoluteBlock AbsoluteBlockExampleFactory::absoluteBlock0Element() {
  std::vector<int32_t> absoluteBlock = AbsoluteBlockExampleFactory::absoluteValues0Element();
  return AbsoluteBlock(absoluteBlock);
}

AbsoluteBlock AbsoluteBlockExampleFactory::absoluteBlockEmpty() {
  std::vector<int32_t> absoluteBlock = AbsoluteBlockExampleFactory::absoluteValuesEmpty();
  return AbsoluteBlock(absoluteBlock);
}

std::vector<int32_t> AbsoluteBlockExampleFactory::absoluteValues() {
  return {38763, 38771, 38780, 38793, 38784, 38780, 38780, 38783, 38790, 38782, 46321, 46327, 46318,
          46316, 46313, 46313, 46313, 46336, 58772, 58774, 58775, 58776, 58773, 19982, 19982, 19978};
}

std::vector<int32_t> AbsoluteBlockExampleFactory::absoluteValuesWithOneValueInLastBlock() {
  return {38763, 38771, 38780, 38793, 38784, 38780, 38780};
}

AbsoluteBlock AbsoluteBlockExampleFactory::absoluteBlock() {
  std::vector<int32_t> absoluteValues = AbsoluteBlockExampleFactory::absoluteValues();
  AbsoluteBlock absoluteBlock = AbsoluteBlock(absoluteValues);
  return absoluteBlock;
}
AbsoluteBlock AbsoluteBlockExampleFactory::absoluteBlockWithOneValueInLastBlock() {
  std::vector<int32_t> absoluteValues = AbsoluteBlockExampleFactory::absoluteValuesWithOneValueInLastBlock();
  AbsoluteBlock absoluteBlock = AbsoluteBlock(absoluteValues);
  return absoluteBlock;
}

// -------------------------------------JSON-----------------------

std::vector<int32_t> AbsoluteBlockExampleFactory::absoluteJsonDataValuesPpg1() {
  return {30021, 30023, 30027, 30022, 30020, 30020, 30030};
}

std::vector<int32_t> AbsoluteBlockExampleFactory::absoluteJsonDataValuesPpg2() {
  return {54834, 54830, 54836, 54842, 54841, 54841, 54830};
}

std::vector<int32_t> AbsoluteBlockExampleFactory::absoluteJsonDataValuesAcc() {
  return {548, 34, 234, 3435, 433, 454};
}

AbsoluteBlock AbsoluteBlockExampleFactory::absoluteJsonDataBlockPpg1() {
  std::vector<int32_t> absoluteValues = AbsoluteBlockExampleFactory::absoluteJsonDataValuesPpg1();
  AbsoluteBlock absoluteBlock = AbsoluteBlock(absoluteValues);
  return absoluteBlock;
}

AbsoluteBlock AbsoluteBlockExampleFactory::absoluteJsonDataBlockPpg2() {
  std::vector<int32_t> absoluteValues = AbsoluteBlockExampleFactory::absoluteJsonDataValuesPpg2();
  AbsoluteBlock absoluteBlock = AbsoluteBlock(absoluteValues);
  return absoluteBlock;
}

AbsoluteBlock AbsoluteBlockExampleFactory::absoluteJsonDataBlockAcc() {
  std::vector<int32_t> absoluteValues = AbsoluteBlockExampleFactory::absoluteJsonDataValuesAcc();
  AbsoluteBlock absoluteBlock = AbsoluteBlock(absoluteValues);
  return absoluteBlock;
}

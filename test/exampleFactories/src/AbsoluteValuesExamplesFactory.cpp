/*

Created by Steve Merschel 2023

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

#include "AbsoluteValuesExampleFactory.h"
#include "PcoreJson.h"

AbsoluteValues AbsoluteValuesExampleFactory::absoluteValuesWithThreePositiveElements() {
  return {1, 2, 3};
}

AbsoluteValues AbsoluteValuesExampleFactory::absoluteValuesWithThreeMixedElements() {
  return {3, -1, 2};
}

AbsoluteValues AbsoluteValuesExampleFactory::absoluteValuesWithThreeNegativeElements() {
  return {-7, -1, -2};
}

AbsoluteValues AbsoluteValuesExampleFactory::absoluteValuesWithOneElement() {
  return {12};
}

AbsoluteValues AbsoluteValuesExampleFactory::absoluteValuesEmpty() {
  return {};
}

AbsoluteValues AbsoluteValuesExampleFactory::absoluteValuesForSwitchDataFormTest() {
  return {1000,  9415, 10093, 2411,  -6568, -8589, -1794, 7570, 10894, 5121,  -4440, -9000, -4366, 5202,
          10906, 7503, -1879, -8614, -6510, 2499,  10129, 9367, 911,   -7462, -8056, -324,  8626};
}

AbsoluteValues AbsoluteValuesExampleFactory::absoluteValues() {
  return {38763, 38771, 38780, 38793, 38784, 38780, 38780, 38783, 38790, 38782, 46321, 46327, 46318,
          46316, 46313, 46313, 46313, 46336, 58772, 58774, 58775, 58776, 58773, 19982, 19982, 19978};
}

AbsoluteValues AbsoluteValuesExampleFactory::absoluteValuesWithOneValueInLastBlock() {
  return {38763, 38771, 38780, 38793, 38784, 38780, 38780};
}

AbsoluteValues AbsoluteValuesExampleFactory::absoluteJsonDataValuesPpg1() {
  return {30021, 30023, 30027, 30022, 30020, 30020, 30030};
}

AbsoluteValues AbsoluteValuesExampleFactory::absoluteJsonDataValuesPpg2() {
  return {54834, 54830, 54836, 54842, 54841, 54841, 54830};
}

AbsoluteValues AbsoluteValuesExampleFactory::absoluteJsonDataValuesAcc() {
  return {548, 34, 234, 3435, 433, 454};
}

AbsoluteValuesJson AbsoluteValuesExampleFactory::buildAbsoluteValuesJson(const AbsoluteValues& absoluteValues) {
  AbsoluteValuesJson absoluteValuesJson(Json::arrayValue);
  for (const auto& absoluteValue : absoluteValues) {
    absoluteValuesJson.append(absoluteValue);
  }
  return absoluteValuesJson;
}
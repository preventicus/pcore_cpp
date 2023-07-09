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

#include "DifferentialBlockExampleFactory.h"

DifferentialBlock DifferentialBlockExampleFactory::differentialBlockWithThreePositiveDifferentialValues() {
  auto differentialValues = DifferentialValuesExampleFactory::differentialValuesWithThreePositiveElements();
  return DifferentialBlock(differentialValues);
}

DifferentialBlock DifferentialBlockExampleFactory::differentialBlockWithThreeMixedDifferentialValues() {
  auto differentialValues = DifferentialValuesExampleFactory::differentialValuesWithThreeMixedElements();
  return DifferentialBlock(differentialValues);
}

DifferentialBlock DifferentialBlockExampleFactory::differentialBlockWithThreeNegativeDifferentialValues() {
  auto differentialValues = DifferentialValuesExampleFactory::differentialValuesWithThreeNegativeElements();
  return DifferentialBlock(differentialValues);
}

DifferentialBlock DifferentialBlockExampleFactory::differentialBlockWithOneDifferentialValues() {
  auto differentialValues = DifferentialValuesExampleFactory::differentialValuesOneElement();
  return DifferentialBlock(differentialValues);
}

DifferentialBlock DifferentialBlockExampleFactory::differentialBlockWithEmptyDifferentialValues() {
  auto differentialValues = DifferentialValuesExampleFactory::differentialValuesEmpty();
  return DifferentialBlock(differentialValues);
}

DifferentialBlocks DifferentialBlockExampleFactory::differentialBlocksWithThreeMixedDifferentialBlocks() {
  return {DifferentialBlockExampleFactory::differentialBlockWithThreePositiveDifferentialValues(),
          DifferentialBlockExampleFactory::differentialBlockWithThreeMixedDifferentialValues(),
          DifferentialBlockExampleFactory::differentialBlockWithThreeNegativeDifferentialValues()};
}

DifferentialBlocks DifferentialBlockExampleFactory::differentialBlocksForSwitchDataFormTest() {
  DifferentialValues differentialValues1 = {1000, 8415, 678, -7682, -8979, -2021, 6795, 9364, 3324, -5773, -9561};
  DifferentialValues differentialValues2 = {-9000, 4634, 9568, 5704, -3403, -9382, -6735, 2104, 9009};
  DifferentialValues differentialValues3 = {10129, -762, -8456, -8373, -594, 7732, 8950};

  return {DifferentialBlock(differentialValues1), DifferentialBlock(differentialValues2), DifferentialBlock(differentialValues3)};
}

DifferentialBlocks DifferentialBlockExampleFactory::differentialBlocksForTestSerialize() {
  DifferentialValues differentialValues1 = {3894, 34, -2389, 0, 43, -983};
  DifferentialValues differentialValues2 = {473, 8934, 8348, 237, 384327873};

  return {DifferentialBlock(differentialValues1), DifferentialBlock(differentialValues2)};
}

DifferentialBlocksJson DifferentialBlockExampleFactory::buildDifferentialBlocksJson(DifferentialBlocks differentialBlocks) {
  DifferentialBlocksJson differentialBlocksJson;
  for (auto& differentialBlock : differentialBlocks) {
    differentialBlocksJson.append(DifferentialBlockExampleFactory::buildDifferentialBlockJson(differentialBlock));
  }
  return differentialBlocksJson;
}

DifferentialBlockJson DifferentialBlockExampleFactory::buildDifferentialBlockJson(DifferentialBlock differentialBlock) {
  auto differentialValues = differentialBlock.getDifferentialValues();
  auto differentialValuesJson = DifferentialValuesExampleFactory::buildDifferentialValuesJson(differentialValues);
  DifferentialBlockJson differentialBlockJson;
  differentialBlockJson[PcoreJsonKey::differential_values] = differentialValuesJson;
  return differentialBlockJson;
}
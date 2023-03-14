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

#include "DifferentialBlockExampleFactory.h"

//DifferentialValues DifferentialBlockExampleFactory::expectedDifferentialValues1() {
//  return {38763, 8, 9, 13, -9, -4, 0, 3, 7, -8};
//}
//
//DifferentialValues DifferentialBlockExampleFactory::expectedDifferentialValues2() {
//  return {46321, 6, -9, -2, -3, 0, 0, 23};
//}
//
//DifferentialValues DifferentialBlockExampleFactory::expectedDifferentialValues3() {
//  return {58772, 2, 1, 1, -3};
//}
//
//DifferentialValues DifferentialBlockExampleFactory::expectedDifferentialValues4() {
//  return {19982, 0, -4};
//}

DifferentialBlock DifferentialBlockExampleFactory::differentialBlockWithThreePositiveDifferentialValues() {
  DifferentialValues differentialValues = DifferentialValuesExampleFactory::differentialValuesWithThreePositiveElements();
  return DifferentialBlock(differentialValues);
}

DifferentialBlock DifferentialBlockExampleFactory::differentialBlockWithThreeMixedDifferentialValues() {
  DifferentialValues differentialValues = DifferentialValuesExampleFactory::differentialValuesWithThreeMixedElements();
  return DifferentialBlock(differentialValues);
}

DifferentialBlock DifferentialBlockExampleFactory::differentialBlockWithThreeNegativeDifferentialValues() {
  DifferentialValues differentialValues = DifferentialValuesExampleFactory::differentialValuesWithThreeNegativeElements();
  return DifferentialBlock(differentialValues);
}

DifferentialBlock DifferentialBlockExampleFactory::differentialBlockWithOneDifferentialValues() {
  DifferentialValues differentialValues = DifferentialValuesExampleFactory::differentialValuesOneElement();
  return DifferentialBlock(differentialValues);
}

DifferentialBlock DifferentialBlockExampleFactory::differentialBlockWithEmptyDifferentialValues() {
  DifferentialValues differentialValues = DifferentialValuesExampleFactory::differentialValuesEmpty();
  return DifferentialBlock(differentialValues);
}

DifferentialBlocks DifferentialBlockExampleFactory::differentialBlocksWithThreeMixedDifferentialBlocks() {
  return {DifferentialBlockExampleFactory::differentialBlockWithThreePositiveDifferentialValues(),
          DifferentialBlockExampleFactory::differentialBlockWithThreeMixedDifferentialValues(),
          DifferentialBlockExampleFactory::differentialBlockWithThreeNegativeDifferentialValues()};
}

//DifferentialBlock DifferentialBlockExampleFactory::expectedDifferentialBlock1() {
//  DifferentialValues differentialValues = DifferentialBlockExampleFactory::expectedDifferentialValues1();
//  return DifferentialBlock(differentialValues);
//}
//
//DifferentialBlock DifferentialBlockExampleFactory::expectedDifferentialBlock2() {
//  DifferentialValues differentialValues = DifferentialBlockExampleFactory::expectedDifferentialValues2();
//  return DifferentialBlock(differentialValues);
//}
//
//DifferentialBlock DifferentialBlockExampleFactory::expectedDifferentialBlock3() {
//  DifferentialValues differentialValues = DifferentialBlockExampleFactory::expectedDifferentialValues3();
//  return DifferentialBlock(differentialValues);
//}
//
//DifferentialBlock DifferentialBlockExampleFactory::expectedDifferentialBlock4() {
//  DifferentialValues differentialValues = DifferentialBlockExampleFactory::expectedDifferentialValues4();
//  return DifferentialBlock(differentialValues);
//}
//
//DifferentialBlocks DifferentialBlockExampleFactory::normalDifferentialBlocks() {
//  DifferentialBlock differentialBlock1 = DifferentialBlockExampleFactory::expectedDifferentialBlock1();
//  DifferentialBlock differentialBlock2 = DifferentialBlockExampleFactory::expectedDifferentialBlock2();
//  DifferentialBlock differentialBlock3 = DifferentialBlockExampleFactory::expectedDifferentialBlock3();
//  DifferentialBlock differentialBlock4 = DifferentialBlockExampleFactory::expectedDifferentialBlock4();
//  DifferentialBlocks normalDifferentialBlocks = {differentialBlock1, differentialBlock2, differentialBlock3, differentialBlock4};
//  return normalDifferentialBlocks;
//}

//DifferentialBlocks DifferentialBlockExampleFactory::differentialJsonDataBlockPpg1() {
//  DifferentialValues differentialValues1 = {30021, -4, 3, 2, 1, -9, 0, 0, 2, 1};
//  DifferentialValues differentialValues2 = {60432, 0, 0, 3, 1, -3, 2, 6, 5, 1, 6, 4, 2};
//  DifferentialValues differentialValues3 = {20123, 40, -93, 3, 0, 57, 48, -84};
//  DifferentialValues differentialValues4 = {93432, 4, 32, -30, 0, 0, 3, 9, -20};
//
//  DifferentialBlock differentialBlock1 = DifferentialBlock(differentialValues1);
//  DifferentialBlock differentialBlock2 = DifferentialBlock(differentialValues2);
//  DifferentialBlock differentialBlock3 = DifferentialBlock(differentialValues3);
//  DifferentialBlock differentialBlock4 = DifferentialBlock(differentialValues4);
//  DifferentialBlocks normalDifferentialBlocks = {differentialBlock1, differentialBlock2, differentialBlock3, differentialBlock4};
//  return normalDifferentialBlocks;
//}
//
//DifferentialBlocks DifferentialBlockExampleFactory::differentialJsonDataBlockPpg2() {
//  DifferentialValues differentialValues1 = {606433, 5, 4, 2, 45, 6, 7, 3, 4, 7};
//  DifferentialValues differentialValues2 = {489424, -49, -4, 3, 0, 0, 0, 4, 2, 7, 56, 3, 0};
//  DifferentialValues differentialValues3 = {32332, 0, 0, 3, 2, 1, 3, -9};
//  DifferentialValues differentialValues4 = {33732, 93, 3, 1, -9, 6, 3, 0, 7};
//
//  DifferentialBlock differentialBlock1 = DifferentialBlock(differentialValues1);
//  DifferentialBlock differentialBlock2 = DifferentialBlock(differentialValues2);
//  DifferentialBlock differentialBlock3 = DifferentialBlock(differentialValues3);
//  DifferentialBlock differentialBlock4 = DifferentialBlock(differentialValues4);
//  DifferentialBlocks normalDifferentialBlocks = {differentialBlock1, differentialBlock2, differentialBlock3, differentialBlock4};
//  return normalDifferentialBlocks;
//}
//
//DifferentialBlocks DifferentialBlockExampleFactory::differentialJsonDataBlockAcc() {
//  DifferentialValues differentialValues1 = {434, 0, 5, 43, 3, 7, 5, 34, 2};
//  DifferentialValues differentialValues2 = {342, 6, 54, 33, 3, 2, 4, -9};
//  DifferentialValues differentialValues3 = {453, 6, 4, -9, -5, 2, 54};
//
//  DifferentialBlock differentialBlock1 = DifferentialBlock(differentialValues1);
//  DifferentialBlock differentialBlock2 = DifferentialBlock(differentialValues2);
//  DifferentialBlock differentialBlock3 = DifferentialBlock(differentialValues3);
//  DifferentialBlocks normalDifferentialBlocks = {differentialBlock1, differentialBlock2, differentialBlock3};
//  return normalDifferentialBlocks;
//}

DifferentialBlocks DifferentialBlockExampleFactory::differentialBlocksForTestSwitchTo() {
  DifferentialValues differentialValues1 = {1000, 8415, 678, -7682, -8979, -2021, 6795, 9364, 3324, -5773, -9561};
  DifferentialValues differentialValues2 = {-9000, 4634, 9568, 5704, -3403, -9382, -6735, 2104, 9009};
  DifferentialValues differentialValues3 = {10129, -762, -8456, -8373, -594, 7732, 8950};

  return {DifferentialBlock(differentialValues1),
          DifferentialBlock(differentialValues2),
          DifferentialBlock(differentialValues3)};
}

DifferentialBlocks DifferentialBlockExampleFactory::differentialBlocksForTestSerialize() {
  DifferentialValues differentialValues1 = {3894, 34, -2389, 0, 43, -983};
  DifferentialValues differentialValues2 = {473, 8934, 8348, 237, 384327873};

  return {DifferentialBlock(differentialValues1),
          DifferentialBlock(differentialValues2)};
}

DifferentialBlockJson DifferentialBlockExampleFactory::buildDifferentialBlockJson(DifferentialValuesJson differentialValuesJson) {
  DifferentialBlockJson differentialBlockJson;
  differentialBlockJson["differential_values"] = differentialValuesJson;
  return differentialBlockJson;
}
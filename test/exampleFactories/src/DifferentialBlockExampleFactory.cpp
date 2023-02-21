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

std::vector<int32_t> DifferentialBlockExampleFactory::differentialValuesNormal() {
  return {30, 32, 54};
}

std::vector<int32_t> DifferentialBlockExampleFactory::differentialValuesNormalNeagtive() {
  return {-23, -234, -13};
}

std::vector<int32_t> DifferentialBlockExampleFactory::differentialValuesOneNegative() {
  return {-123};
}

std::vector<int32_t> DifferentialBlockExampleFactory::differentialValuesOnePositive() {
  return {123};
}

std::vector<int32_t> DifferentialBlockExampleFactory::differentialValues0() {
  return {0};
}

std::vector<int32_t> DifferentialBlockExampleFactory::differentialValuesEmpty() {
  return {};
}

DifferentialBlock DifferentialBlockExampleFactory::differentialBlockNormal() {
  std::vector<int32_t> differentialBlock = DifferentialBlockExampleFactory::differentialValuesNormal();
  return DifferentialBlock(differentialBlock);
}

DifferentialBlock DifferentialBlockExampleFactory::differentialBlockWithNegativeValues() {
  std::vector<int32_t> differentialBlock = DifferentialBlockExampleFactory::differentialValuesNormalNeagtive();
  return DifferentialBlock(differentialBlock);
}

DifferentialBlock DifferentialBlockExampleFactory::differentialBlockOneNegativeValue() {
  std::vector<int32_t> differentialBlock = DifferentialBlockExampleFactory::differentialValuesOneNegative();
  return DifferentialBlock(differentialBlock);
}

DifferentialBlock DifferentialBlockExampleFactory::differentialBlockOnePositiveValue() {
  std::vector<int32_t> differentialBlock = DifferentialBlockExampleFactory::differentialValuesOnePositive();
  return DifferentialBlock(differentialBlock);
}

DifferentialBlock DifferentialBlockExampleFactory::differentialBlock0Value() {
  std::vector<int32_t> differentialBlock = DifferentialBlockExampleFactory::differentialValues0();
  return DifferentialBlock(differentialBlock);
}

DifferentialBlock DifferentialBlockExampleFactory::differentialBlockEmptyValue() {
  std::vector<int32_t> differentialBlock = DifferentialBlockExampleFactory::differentialValuesEmpty();
  return DifferentialBlock(differentialBlock);
}

std::vector<int32_t> DifferentialBlockExampleFactory::expectedDifferentialValues1() {
  return {38763, 8, 9, 13, -9, -4, 0, 3, 7, -8};
}

std::vector<int32_t> DifferentialBlockExampleFactory::expectedDifferentialValues2() {
  return {46321, 6, -9, -2, -3, 0, 0, 23};
}

std::vector<int32_t> DifferentialBlockExampleFactory::expectedDifferentialValues3() {
  return {58772, 2, 1, 1, -3};
}

std::vector<int32_t> DifferentialBlockExampleFactory::expectedDifferentialValues4() {
  return {19982, 0, -4};
}

DifferentialBlock DifferentialBlockExampleFactory::expectedDifferentialBlock1() {
  std::vector<int32_t> differentialBlock = DifferentialBlockExampleFactory::expectedDifferentialValues1();
  return DifferentialBlock(differentialBlock);
}

DifferentialBlock DifferentialBlockExampleFactory::expectedDifferentialBlock2() {
  std::vector<int32_t> differentialBlock = DifferentialBlockExampleFactory::expectedDifferentialValues2();
  return DifferentialBlock(differentialBlock);
}

DifferentialBlock DifferentialBlockExampleFactory::expectedDifferentialBlock3() {
  std::vector<int32_t> differentialBlock = DifferentialBlockExampleFactory::expectedDifferentialValues3();
  return DifferentialBlock(differentialBlock);
}

DifferentialBlock DifferentialBlockExampleFactory::expectedDifferentialBlock4() {
  std::vector<int32_t> differentialBlock = DifferentialBlockExampleFactory::expectedDifferentialValues4();
  return DifferentialBlock(differentialBlock);
}

std::vector<DifferentialBlock> DifferentialBlockExampleFactory::normalDifferentialBlocks() {
  DifferentialBlock differentialBlock1 = DifferentialBlockExampleFactory::expectedDifferentialBlock1();
  DifferentialBlock differentialBlock2 = DifferentialBlockExampleFactory::expectedDifferentialBlock2();
  DifferentialBlock differentialBlock3 = DifferentialBlockExampleFactory::expectedDifferentialBlock3();
  DifferentialBlock differentialBlock4 = DifferentialBlockExampleFactory::expectedDifferentialBlock4();
  std::vector<DifferentialBlock> normalDifferentialBlocks = {differentialBlock1, differentialBlock2, differentialBlock3, differentialBlock4};
  return normalDifferentialBlocks;
}

std::vector<DifferentialBlock> DifferentialBlockExampleFactory::differentialJsonDataBlockPpg1() {
  std::vector<int32_t> differentialValues1 = {30021, -4, 3, 2, 1, -9, 0, 0, 2, 1};
  std::vector<int32_t> differentialValues2 = {60432, 0, 0, 3, 1, -3, 2, 6, 5, 1, 6, 4, 2};
  std::vector<int32_t> differentialValues3 = {20123, 40, -93, 3, 0, 57, 48, -84};
  std::vector<int32_t> differentialValues4 = {93432, 4, 32, -30, 0, 0, 3, 9, -20};

  DifferentialBlock differentialBlock1 = DifferentialBlock(differentialValues1);
  DifferentialBlock differentialBlock2 = DifferentialBlock(differentialValues2);
  DifferentialBlock differentialBlock3 = DifferentialBlock(differentialValues3);
  DifferentialBlock differentialBlock4 = DifferentialBlock(differentialValues4);
  std::vector<DifferentialBlock> normalDifferentialBlocks = {differentialBlock1, differentialBlock2, differentialBlock3, differentialBlock4};
  return normalDifferentialBlocks;
}

std::vector<DifferentialBlock> DifferentialBlockExampleFactory::differentialJsonDataBlockPpg2() {
  std::vector<int32_t> differentialValues1 = {606433, 5, 4, 2, 45, 6, 7, 3, 4, 7};
  std::vector<int32_t> differentialValues2 = {489424, -49, -4, 3, 0, 0, 0, 4, 2, 7, 56, 3, 0};
  std::vector<int32_t> differentialValues3 = {32332, 0, 0, 3, 2, 1, 3, -9};
  std::vector<int32_t> differentialValues4 = {33732, 93, 3, 1, -9, 6, 3, 0, 7};

  DifferentialBlock differentialBlock1 = DifferentialBlock(differentialValues1);
  DifferentialBlock differentialBlock2 = DifferentialBlock(differentialValues2);
  DifferentialBlock differentialBlock3 = DifferentialBlock(differentialValues3);
  DifferentialBlock differentialBlock4 = DifferentialBlock(differentialValues4);
  std::vector<DifferentialBlock> normalDifferentialBlocks = {differentialBlock1, differentialBlock2, differentialBlock3, differentialBlock4};
  return normalDifferentialBlocks;
}

std::vector<DifferentialBlock> DifferentialBlockExampleFactory::differentialJsonDataBlockAcc() {
  std::vector<int32_t> differentialValues1 = {434, 0, 5, 43, 3, 7, 5, 34, 2};
  std::vector<int32_t> differentialValues2 = {342, 6, 54, 33, 3, 2, 4, -9};
  std::vector<int32_t> differentialValues3 = {453, 6, 4, -9, -5, 2, 54};

  DifferentialBlock differentialBlock1 = DifferentialBlock(differentialValues1);
  DifferentialBlock differentialBlock2 = DifferentialBlock(differentialValues2);
  DifferentialBlock differentialBlock3 = DifferentialBlock(differentialValues3);
  std::vector<DifferentialBlock> normalDifferentialBlocks = {differentialBlock1, differentialBlock2, differentialBlock3};
  return normalDifferentialBlocks;
}
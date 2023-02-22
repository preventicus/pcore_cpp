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

#pragma once
#include "DifferentialBlock.h"
#include "Channel.h"

class DifferentialBlockExampleFactory {
 public:
  static DifferentialValues differentialValuesNormal();
  static DifferentialValues differentialValuesNormalNeagtive();
  static DifferentialValues differentialValuesOneNegative();
  static DifferentialValues differentialValuesOnePositive();
  static DifferentialValues differentialValues0();
  static DifferentialValues differentialValuesEmpty();

  static DifferentialValues expectedDifferentialValues1();
  static DifferentialValues expectedDifferentialValues2();
  static DifferentialValues expectedDifferentialValues3();
  static DifferentialValues expectedDifferentialValues4();

  static DifferentialBlock differentialBlockNormal();
  static DifferentialBlock differentialBlockWithNegativeValues();
  static DifferentialBlock differentialBlockOneNegativeValue();
  static DifferentialBlock differentialBlockOnePositiveValue();
  static DifferentialBlock differentialBlock0Value();
  static DifferentialBlock differentialBlockEmptyValue();

  static DifferentialBlock expectedDifferentialBlock1();
  static DifferentialBlock expectedDifferentialBlock2();
  static DifferentialBlock expectedDifferentialBlock3();
  static DifferentialBlock expectedDifferentialBlock4();

  static std::vector<DifferentialBlock> normalDifferentialBlocks();
  static std::vector<DifferentialBlock> differentialJsonDataBlockPpg1();
  static std::vector<DifferentialBlock> differentialJsonDataBlockPpg2();
  static std::vector<DifferentialBlock> differentialJsonDataBlockAcc();
};
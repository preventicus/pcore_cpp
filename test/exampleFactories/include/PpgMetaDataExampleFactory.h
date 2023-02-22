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
#include "PpgMetaData.h"

class PpgMetaDataExampleFactory {
 public:
  static uint32_t normalWavelength_nm();
  static uint32_t comparableWavelength_nm();
  static uint32_t noWavelength_nm();
  static uint32_t absoluteJsonDataWavelength_nm1();
  static uint32_t absoluteJsonDataWavelength_nm2();

  static PpgMetaData ppgMetDataWithColorGreen();
  static PpgMetaData ppgMetDataWithColorBlue();
  static PpgMetaData ppgMetDataWithColorRed();

  static PpgMetaData ppgMetDataWithWavelength();
  static PpgMetaData ppgMetDataWithComparableWavelength();
  static PpgMetaData absoluteJsonDataPpg1();
  static PpgMetaData absoluteJsonDataPpg2();

  static PpgMetaData ppgMetaDataNotSet();
};
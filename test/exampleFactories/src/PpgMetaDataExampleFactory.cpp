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

#include "PpgMetaDataExampleFactory.h"

Wavelength PpgMetaDataExampleFactory::normalWavelength_nm() {
  return 255;
}

Wavelength PpgMetaDataExampleFactory::comparableWavelength_nm() {
  return 100;
}

Wavelength PpgMetaDataExampleFactory::absoluteJsonDataWavelength_nm1() {
  return 450;
}

Wavelength PpgMetaDataExampleFactory::absoluteJsonDataWavelength_nm2() {
  return 660;
}

Wavelength PpgMetaDataExampleFactory::noWavelength_nm() {
  return 0;
}

PpgMetaData PpgMetaDataExampleFactory::ppgMetDataWithColorGreen() {
  return PpgMetaData(ProtobufColor::COLOR_GREEN);
}

PpgMetaData PpgMetaDataExampleFactory::ppgMetDataWithColorBlue() {
  return PpgMetaData(ProtobufColor::COLOR_BLUE);
}

PpgMetaData PpgMetaDataExampleFactory::ppgMetDataWithColorRed() {
  return PpgMetaData(ProtobufColor::COLOR_RED);
}

PpgMetaData PpgMetaDataExampleFactory::ppgMetDataWithWavelength() {
  return PpgMetaData(PpgMetaDataExampleFactory::normalWavelength_nm());
}

PpgMetaData PpgMetaDataExampleFactory::ppgMetDataWithComparableWavelength() {
  return PpgMetaData(PpgMetaDataExampleFactory::comparableWavelength_nm());
}

PpgMetaData PpgMetaDataExampleFactory::absoluteJsonDataPpg1() {
  return PpgMetaData(PpgMetaDataExampleFactory::absoluteJsonDataWavelength_nm1());
}

PpgMetaData PpgMetaDataExampleFactory::absoluteJsonDataPpg2() {
  return PpgMetaData(PpgMetaDataExampleFactory::absoluteJsonDataWavelength_nm2());
}

PpgMetaData PpgMetaDataExampleFactory::ppgMetaDataNotSet() {
  return PpgMetaData();
}
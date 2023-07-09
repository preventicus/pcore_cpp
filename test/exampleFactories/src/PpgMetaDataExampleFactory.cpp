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

#include "PpgMetaDataExampleFactory.h"

PpgMetaData PpgMetaDataExampleFactory::ppgMetDataWithColorGreen() {
  return PpgMetaData(ProtobufColor::COLOR_GREEN);
}

PpgMetaData PpgMetaDataExampleFactory::ppgMetDataWithColorBlue() {
  return PpgMetaData(ProtobufColor::COLOR_BLUE);
}

PpgMetaData PpgMetaDataExampleFactory::ppgMetDataWithColorRed() {
  return PpgMetaData(ProtobufColor::COLOR_RED);
}

PpgMetaData PpgMetaDataExampleFactory::ppgMetaDataWithColorNone() {
  return PpgMetaData(ProtobufColor::COLOR_NONE);
}

PpgMetaData PpgMetaDataExampleFactory::ppgMetaDataWithWavelength0() {
  return PpgMetaData(0);
}

PpgMetaData PpgMetaDataExampleFactory::ppgMetaDataWithWavelength255() {
  return PpgMetaData(255);
}

PpgMetaData PpgMetaDataExampleFactory::ppgMetaDataWithWavelength100() {
  return PpgMetaData(100);
}

PpgMetaData PpgMetaDataExampleFactory::ppgMetaDataNotSet() {
  return PpgMetaData();
}

PpgMetaDataJson PpgMetaDataExampleFactory::buildPpgMetaDataJson(PpgMetaData ppgMetaData) {
  PpgMetaDataJson ppgMetaDataJson;
  if (ppgMetaData.hasWavelength()) {
    ppgMetaDataJson["wavelength_nm"] = ppgMetaData.getWavelength_nm();
  } else if (ppgMetaData.hasColor()) {
    ppgMetaDataJson["color"] = PpgMetaData::protobufColorToString(ppgMetaData.getColor());
  }
  return ppgMetaDataJson;
}

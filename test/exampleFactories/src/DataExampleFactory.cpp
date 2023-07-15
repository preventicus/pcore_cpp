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

#include "DataExampleFactory.h"
#include "PcoreJson.h"

Data DataExampleFactory::dataWithRawWithTwoSensorsPpgAndHeaderWithTimeZoneOffsetPositive() {
  auto raw = RawExampleFactory::rawWithTwoSensorsPpgWithTwoChannelsInDifferentialForm();
  auto header = HeaderExampleFactory::headerWithVersionWithMajor2Minor1Patch0AndTimeZoneOffsetPositiveAndDataFormDifferential();
  return Data(raw, header);
}

Data DataExampleFactory::dataWithRawWithTwoSensorsPpgAndHeaderWithTimeZoneOffsetNegative() {
  auto raw = RawExampleFactory::rawWithTwoSensorsPpgWithTwoChannelsInDifferentialForm();
  auto header = HeaderExampleFactory::headerWithVersionWithMajor2Minor1Patch0AndTimeZoneOffsetNegativeAndDataFormDifferential();
  return Data(raw, header);
}

Data DataExampleFactory::dataWithRawWithOneSensorsPpgAndHeaderWithTimeZoneOffsetNegative() {
  auto raw = RawExampleFactory::rawWithOneSensorsPpgWithTwoChannelsInDifferentialForm();
  auto header = HeaderExampleFactory::headerWithVersionWithMajor2Minor1Patch0AndTimeZoneOffsetPositiveAndDataFormDifferential();
  return Data(raw, header);
}

Data DataExampleFactory::dataNotSet() {
  return Data();
}

Data DataExampleFactory::dataWithRawForSwitchDataFormTestInAbsoluteForm() {
  auto raw = RawExampleFactory::rawForSwitchDataFormTestInAbsoluteForm();
  auto header = HeaderExampleFactory::headerWithVersionWithMajor2Minor1Patch0AndTimeZoneOffsetPositiveAndDataFormAbsolute();
  return Data(raw, header);
}

Data DataExampleFactory::dataWithRawForSwitchDataFormTestInDifferentialForm() {
  auto raw = RawExampleFactory::rawForSwitchDataFormTestInDifferentialForm();
  auto header = HeaderExampleFactory::headerWithVersionWithMajor2Minor1Patch0AndTimeZoneOffsetPositiveAndDataFormDifferential();
  return Data(raw, header);
}

Json::Value DataExampleFactory::buildDataJson(const Data& data) {
  DataJson dataJson;
  if (!data.isSet()) {
    return dataJson;
  }
  auto header = data.getHeader();
  auto raw = data.getRaw();
  dataJson[PcoreJson::Key::header] = HeaderExampleFactory::buildHeaderJson(header);
  dataJson[PcoreJson::Key::raw] = RawExampleFactory::buildRawJson(raw);
  Json::Value json;
  json[PcoreJson::Key::data] = dataJson;
  return json;
}

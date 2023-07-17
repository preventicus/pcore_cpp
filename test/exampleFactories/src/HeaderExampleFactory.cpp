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

#include "HeaderExampleFactory.h"
#include "PcoreJson.h"

TimeZoneOffset HeaderExampleFactory::timeZoneOffsetPositiveInMin() {
  return 120;
}

TimeZoneOffset HeaderExampleFactory::timeZoneOffsetNegativeInMin() {
  return -120;
}

TimeZoneOffset HeaderExampleFactory::timeZoneOffsetNotSetInMin() {
  return 0;
}

TimeZoneOffset HeaderExampleFactory::timeZoneOffsetMaxValueInMin() {
  return 840;
}

TimeZoneOffset HeaderExampleFactory::timeZoneOffsetMinValueInMin() {
  return -720;
}

TimeZoneOffset HeaderExampleFactory::timeZoneOffsetPositiveInvalidInMin() {
  return 1000;
}

TimeZoneOffset HeaderExampleFactory::timeZoneOffsetNegativeInvalidInMin() {
  return -1000;
}

Header HeaderExampleFactory::headerWithVersionWithMajor2Minor1Patch0AndTimeZoneOffsetPositiveAndDataFormAbsolute() {
  auto version = VersionExampleFactory::versionWithMajor2Minor1Patch0();
  auto timeZoneOffsetInMin = HeaderExampleFactory::timeZoneOffsetPositiveInMin();
  return Header(version, timeZoneOffsetInMin, DataForm::DATA_FORM_ABSOLUTE);
}

Header HeaderExampleFactory::headerWithVersionWithMajor2Minor1Patch0AndTimeZoneOffsetPositiveAndDataFormDifferential() {
  auto version = VersionExampleFactory::versionWithMajor2Minor1Patch0();
  auto timeZoneOffsetInMin = HeaderExampleFactory::timeZoneOffsetPositiveInMin();
  return Header(version, timeZoneOffsetInMin, DataForm::DATA_FORM_DIFFERENTIAL);
}

Header HeaderExampleFactory::headerWithVersionWithMajor0Minor0Patch0AndTimeZoneOffsetPositiveAndDataFormAbsolute() {
  auto version = VersionExampleFactory::versionWithMajor0Minor0Patch0();
  auto timeZoneOffsetInMin = HeaderExampleFactory::timeZoneOffsetPositiveInMin();
  return Header(version, timeZoneOffsetInMin, DataForm::DATA_FORM_ABSOLUTE);
}

Header HeaderExampleFactory::headerWithVersionWithMajor2Minor1Patch0AndTimeZoneOffsetNegativeAndDataFormAbsolute() {
  auto version = VersionExampleFactory::versionWithMajor2Minor1Patch0();
  auto timeZoneOffsetInMin = HeaderExampleFactory::timeZoneOffsetNegativeInMin();
  return Header(version, timeZoneOffsetInMin, DataForm::DATA_FORM_ABSOLUTE);
}

Header HeaderExampleFactory::headerWithVersionWithMajor2Minor1Patch0AndTimeZoneOffsetNegativeAndDataFormDifferential() {
  auto version = VersionExampleFactory::versionWithMajor2Minor1Patch0();
  auto timeZoneOffsetInMin = HeaderExampleFactory::timeZoneOffsetNegativeInMin();
  return Header(version, timeZoneOffsetInMin, DataForm::DATA_FORM_DIFFERENTIAL);
}

Header HeaderExampleFactory::headerWithVersionNotSetAndTimeZoneOffsetNotSetAndDataFormDifferential() {
  auto version = VersionExampleFactory::versionNotSet();
  auto timeZoneOffsetInMin = HeaderExampleFactory::timeZoneOffsetNotSetInMin();
  return Header(version, timeZoneOffsetInMin, DataForm::DATA_FORM_DIFFERENTIAL);
}

Header HeaderExampleFactory::headerWithVersionWithMajor1Minor2Patch0AndTimeZoneOffsetNotSetAndDataFormDifferential() {
  auto version = VersionExampleFactory::versionWithMajor1Minor2Patch0();
  auto timeZoneOffsetInMin = HeaderExampleFactory::timeZoneOffsetNotSetInMin();
  return Header(version, timeZoneOffsetInMin, DataForm::DATA_FORM_DIFFERENTIAL);
}

Header HeaderExampleFactory::headerNotSet() {
  return Header();
}

HeaderJson HeaderExampleFactory::buildHeaderJson(const Header& header) {
  HeaderJson headerJson;
  if (!header.isSet()) {
    return headerJson;
  }
  TimeZoneOffsetJson timeZoneOffsetJson(Json::intValue);
  timeZoneOffsetJson = header.getTimeZoneOffsetInMin();
  headerJson[PcoreJson::Key::time_zone_offset_min] = timeZoneOffsetJson;
  headerJson[PcoreJson::Key::pcore_version] = VersionExampleFactory::buildVersionJson(header.getPcoreVersion());
  headerJson[PcoreJson::Key::data_form] = PcoreJson::Convert::dataFormToString(header.getDataForm());
  return headerJson;
}

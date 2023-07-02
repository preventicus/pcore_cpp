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

TimeZoneOffset HeaderExampleFactory::timeZoneOffsetPositive_min() {
  return 120;
}

TimeZoneOffset HeaderExampleFactory::timeZoneOffsetNegative_min() {
  return -120;
}

TimeZoneOffset HeaderExampleFactory::timeZoneOffsetEmpty_min() {
  return 0;
}

TimeZoneOffset HeaderExampleFactory::timeZoneOffsetMaxValue_min() {
  return 840;
}

TimeZoneOffset HeaderExampleFactory::timeZoneOffsetMinValue_min() {
  return -720;
}

TimeZoneOffset HeaderExampleFactory::timeZoneOffsetPositiveInvalid_min() {
  return 1000;
}

TimeZoneOffset HeaderExampleFactory::timeZoneOffsetNegativeInvalid_min() {
  return -1000;
}

Header HeaderExampleFactory::headerWithVersionWithMajor2Minor1Patch0AndTimeZoneOffsetPositiveAndDataFormAbsolute() {
  Version version = VersionExampleFactory::versionWithMajor2Minor1Patch0();
  TimeZoneOffset timeZoneOffset_min = HeaderExampleFactory::timeZoneOffsetPositive_min();
  return Header(version, timeZoneOffset_min, DataForm::DATA_FORM_ABSOLUTE);
}

Header HeaderExampleFactory::headerWithVersionWithMajor2Minor1Patch0AndTimeZoneOffsetPositiveAndDataFormDifferential() {
  Version version = VersionExampleFactory::versionWithMajor2Minor1Patch0();
  TimeZoneOffset timeZoneOffset_min = HeaderExampleFactory::timeZoneOffsetPositive_min();
  return Header(version, timeZoneOffset_min, DataForm::DATA_FORM_DIFFERENTIAL);
}

Header HeaderExampleFactory::headerWithVersionWithMajor0Minor0Patch0AndTimeZoneOffsetPositiveAndDataFormAbsolute() {
  Version version = VersionExampleFactory::versionWithMajor0Minor0Patch0();
  TimeZoneOffset timeZoneOffset_min = HeaderExampleFactory::timeZoneOffsetPositive_min();
  return Header(version, timeZoneOffset_min, DataForm::DATA_FORM_ABSOLUTE);
}

Header HeaderExampleFactory::headerWithVersionWithMajor2Minor1Patch0AndTimeZoneOffsetNegativeAndDataFormAbsolute() {
  Version version = VersionExampleFactory::versionWithMajor2Minor1Patch0();
  TimeZoneOffset timeZoneOffset_min = HeaderExampleFactory::timeZoneOffsetNegative_min();
  return Header(version, timeZoneOffset_min, DataForm::DATA_FORM_ABSOLUTE);
}

Header HeaderExampleFactory::headerWithVersionWithMajor2Minor1Patch0AndTimeZoneOffsetNegativeAndDataFormDifferential() {
  Version version = VersionExampleFactory::versionWithMajor2Minor1Patch0();
  TimeZoneOffset timeZoneOffset_min = HeaderExampleFactory::timeZoneOffsetNegative_min();
  return Header(version, timeZoneOffset_min, DataForm::DATA_FORM_DIFFERENTIAL);
}

Header HeaderExampleFactory::headerEmpty() {
  return Header();
}

HeaderJson HeaderExampleFactory::buildHeaderJson(Header header) {
  HeaderJson headerJson;
  TimeZoneOffsetJson timeZoneOffset_min(header.getTimeZoneOffset());
  headerJson["time_zone_offset_min"] = timeZoneOffset_min;
  headerJson["version"] = VersionExampleFactory::buildVersionJson(header.getVersion());
  headerJson["data_form"] = Header::dataFormToString(header.getDataForm());
  return headerJson;
}

//
// Header HeaderExampleFactory::normalHeaderWithPositiveTimeZoneOffset_min() {
//  Version version = VersionExampleFactory::randomVersion();
//  return Header(version, HeaderExampleFactory::positiveTimeZoneOffset_min(), DataForm::DATA_FORM_DIFFERENTIAL);
//}
//
// Header HeaderExampleFactory::normalHeaderWithNegativeTimeZoneOffset_min() {
//  Version version = VersionExampleFactory::randomVersion();
//  return Header(version, HeaderExampleFactory::negativeTimeZoneOffset_min(), DataForm::DATA_FORM_DIFFERENTIAL);
//}
//
// Header HeaderExampleFactory::normalHeaderWithNoTimeZoneOffset_min() {
//  Version version = VersionExampleFactory::randomVersion();
//  return Header(version, HeaderExampleFactory::noTimeZoneOffset_min(), DataForm::DATA_FORM_DIFFERENTIAL);
//}
//
// Header HeaderExampleFactory::headerWithMaxTimeZoneOffset_min() {
//  Version version = VersionExampleFactory::randomVersion();
//  return Header(version, HeaderExampleFactory::maxTimeZoneOffset_min(), DataForm::DATA_FORM_DIFFERENTIAL);
//}
//
// Header HeaderExampleFactory::headerWithMinTimeZoneOffset_min() {
//  Version version = VersionExampleFactory::randomVersion();
//  return Header(version, HeaderExampleFactory::minTimeZoneOffset_min(), DataForm::DATA_FORM_DIFFERENTIAL);
//}
//
// Header HeaderExampleFactory::absoluteJsonDataHeader() {
//  Version version = VersionExampleFactory::absoluteJsonDataVersion();
//  return Header(version, HeaderExampleFactory::noTimeZoneOffset_min(), DataForm::DATA_FORM_DIFFERENTIAL);
//}

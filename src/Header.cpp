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

#include "Header.h"

#include <utility>
#include "PcoreJson.h"

////////////////////////////////////////////////////////////////
//                       Constructors                         //
////////////////////////////////////////////////////////////////
Header::Header(Version version, TimeZoneOffset timeZoneOffsetInMin, DataForm dataForm)
    : timeZoneOffsetInMin(timeZoneOffsetInMin), pcoreVersion(std::move(version)), dataForm(dataForm) {
  this->checkTimeZoneOffset();
}

Header::Header(const HeaderProtobuf& headerProtobuf)
    : timeZoneOffsetInMin(headerProtobuf.time_zone_offset_min()), pcoreVersion(Version(headerProtobuf.pcore_version())), dataForm([&]() {
        if (headerProtobuf.has_pcore_version()) {
          return DataForm::DATA_FORM_DIFFERENTIAL;
        } else {
          return DataForm::DATA_FORM_NONE;
        }
      }()) {
  this->checkTimeZoneOffset();
}

Header::Header(const HeaderJson& headerJson)
    : timeZoneOffsetInMin(headerJson[PcoreJson::Key::time_zone_offset_min].asInt()),
      pcoreVersion(Version(headerJson[PcoreJson::Key::pcore_version])),
      dataForm(PcoreJson::Convert::dataFormFromString(headerJson[PcoreJson::Key::data_form].asString())) {
  this->checkTimeZoneOffset();
}

Header::Header() : timeZoneOffsetInMin(0), pcoreVersion(Version()), dataForm(DataForm::DATA_FORM_NONE) {}

////////////////////////////////////////////////////////////////
//                          Getter                            //
////////////////////////////////////////////////////////////////

TimeZoneOffset Header::getTimeZoneOffsetInMin() const {
  return this->timeZoneOffsetInMin;
}

Version Header::getPcoreVersion() const {
  return this->pcoreVersion;
}

DataForm Header::getDataForm() const {
  return this->dataForm;
}

////////////////////////////////////////////////////////////////
//                      IPCore Methods                        //
////////////////////////////////////////////////////////////////

bool Header::isSet() const {
  // clang-format off
  return this->timeZoneOffsetInMin != 0
      || this->pcoreVersion.isSet()
      || this->dataForm != DataForm::DATA_FORM_NONE;
  // clang-format on
}

HeaderJson Header::toJson() const {
  HeaderJson headerJson;
  if (!this->isSet()) {
    return headerJson;
  }
  TimeZoneOffsetJson timeZoneOffsetJson(Json::intValue);
  timeZoneOffsetJson = this->timeZoneOffsetInMin;
  headerJson[PcoreJson::Key::time_zone_offset_min] = timeZoneOffsetJson;
  headerJson[PcoreJson::Key::pcore_version] = this->pcoreVersion.toJson();
  headerJson[PcoreJson::Key::data_form] = PcoreJson::Convert::dataFormToString(this->dataForm);
  return headerJson;
}

void Header::serialize(HeaderProtobuf* headerProtobuf) const {
  if (headerProtobuf == nullptr) {
    throw std::invalid_argument("Error in serialize: headerProtobuf is a null pointer");
  }
  if (!this->isSet()) {
    return;
  }
  headerProtobuf->set_time_zone_offset_min(this->timeZoneOffsetInMin);
  VersionProtobuf versionProtobuf;
  this->pcoreVersion.serialize(&versionProtobuf);
  headerProtobuf->mutable_pcore_version()->CopyFrom(versionProtobuf);
}

void Header::switchDataForm() {
  if (!this->isSet()) {
    return;
  }
  switch (this->dataForm) {
    case DataForm::DATA_FORM_DIFFERENTIAL: {
      this->dataForm = DATA_FORM_ABSOLUTE;
      break;
    }
    case DataForm::DATA_FORM_ABSOLUTE: {
      this->dataForm = DATA_FORM_DIFFERENTIAL;
      break;
    }
    default: {
      throw std::runtime_error("DataForm is NONE");  // should not happen, since it is intercepted by isSet guard above
    }
  }
}

bool Header::operator==(const IPCore<HeaderProtobuf>& header) const {
  if (const auto* derived = dynamic_cast<const Header*>(&header)) {
    return this->timeZoneOffsetInMin == derived->timeZoneOffsetInMin && this->pcoreVersion == derived->pcoreVersion &&
           this->dataForm == derived->dataForm;
  }
  return false;
}

bool Header::operator!=(const IPCore<HeaderProtobuf>& header) const {
  return !(*this == header);
}

////////////////////////////////////////////////////////////////
//                       Helper Methods                       //
////////////////////////////////////////////////////////////////

void Header::checkTimeZoneOffset() const {
  if (840 < this->timeZoneOffsetInMin || this->timeZoneOffsetInMin < -720) {
    throw std::invalid_argument("timeZoneOffset must be between -720 and 840");
  }
}

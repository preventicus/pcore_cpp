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

Header::Header(Version& version, TimeZoneOffset timeZoneOffset_min, DataForm dataForm)
    : timeZoneOffset_min(timeZoneOffset_min), version(version), dataForm(dataForm) {
  this->checkTimeZoneOffset();
}

Header::Header(const ProtobufHeader& protobufHeader)
    : timeZoneOffset_min(protobufHeader.time_zone_offset_min()),
      version(Version(protobufHeader.pcore_version())),
      dataForm(DataForm::DATA_FORM_DIFFERENTIAL) {
  this->checkTimeZoneOffset();
}

Header::Header(HeaderJson& headerJson)
    : timeZoneOffset_min(headerJson["time_zone_offset_min"].asInt()),
      version(Version(headerJson["version"])),
      dataForm(Header::dataFormFromString(headerJson["data_form"].asString())) {
  this->checkTimeZoneOffset();
}

Header::Header() : timeZoneOffset_min(0), version(Version()), dataForm(DataForm::DATA_FORM_NONE) {}

TimeZoneOffset Header::getTimeZoneOffset() {
  return this->timeZoneOffset_min;
}

Version Header::getVersion() {
  return this->version;
}

DataForm Header::getDataForm() {
  return this->dataForm;
}

bool Header::operator==(const Header& header) const {
  return this->timeZoneOffset_min == header.timeZoneOffset_min && this->version == header.version && this->dataForm == header.dataForm;
}

bool Header::operator!=(const Header& header) const {
  return this->timeZoneOffset_min != header.timeZoneOffset_min || this->version != header.version || this->dataForm != header.dataForm;
}

void Header::serialize(ProtobufHeader* protobufHeader) {
  if (protobufHeader == nullptr) {
    throw std::invalid_argument("Error in serialize: protobufHeader is a null pointer");
  }
  protobufHeader->set_time_zone_offset_min(this->timeZoneOffset_min);
  ProtobufVersion protobufVersion;
  this->version.serialize(&protobufVersion);
  protobufHeader->mutable_pcore_version()->CopyFrom(protobufVersion);
}

void Header::switchDataForm() {
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
      throw std::runtime_error("DataForm is NONE");
    }
  }
}

HeaderJson Header::toJson(DataForm dataForm) {
  HeaderJson headerJson;
  TimeZoneOffsetJson timeZoneOffset_min(this->timeZoneOffset_min);
  headerJson["time_zone_offset_min"] = timeZoneOffset_min;
  headerJson["version"] = this->version.toJson();
  headerJson["data_form"] = Header::dataFormToString(dataForm);
  return headerJson;
}

void Header::checkTimeZoneOffset() {
  if (840 < this->timeZoneOffset_min || this->timeZoneOffset_min < -720) {
    throw std::invalid_argument("timeZoneOffset must be between -720 and 840");
  }
}

DataForm Header::dataFormFromString(DataFormString dataFormString) {
  if (dataFormString == "DATA_FORM_ABSOLUTE") {
    return DataForm::DATA_FORM_ABSOLUTE;
  } else if (dataFormString == "DATA_FORM_DIFFERENTIAL") {
    return DataForm::DATA_FORM_DIFFERENTIAL;
  } else {
    return DataForm::DATA_FORM_NONE;
  }
}

DataFormString Header::dataFormToString(DataForm dataForm) {
  switch (dataForm) {
    case DataForm::DATA_FORM_ABSOLUTE: {
      return "DATA_FORM_ABSOLUTE";
    }
    case DataForm::DATA_FORM_DIFFERENTIAL: {
      return "DATA_FORM_DIFFERENTIAL";
    }
    default: {
      return "DATA_FORM_NONE";
    }
  }
}
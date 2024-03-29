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

#include "Data.h"
#include <utility>
#include "Exceptions.h"
#include "PcoreJson.h"

////////////////////////////////////////////////////////////////
//                       Constructors                         //
////////////////////////////////////////////////////////////////
Data::Data(Raw raw, Header header) noexcept : header(std::move(header)), raw(std::move(raw)) {}

Data::Data(const DataProtobuf& DataProtobuf) noexcept : header(Header(DataProtobuf.header())), raw(Raw(DataProtobuf.raw())) {}

Data::Data(const DataJson& dataJson)
    : header(Header(dataJson[PcoreJson::Key::header])), raw(Raw(dataJson[PcoreJson::Key::raw], header.getDataForm())) {}

Data::Data() noexcept : header(Header()), raw(Raw()) {}

////////////////////////////////////////////////////////////////
//                          Getter                            //
////////////////////////////////////////////////////////////////
Raw Data::getRaw() const noexcept {
  return this->raw;
}

Header Data::getHeader() const noexcept {
  return this->header;
}

////////////////////////////////////////////////////////////////
//                      IPCore Methods                        //
////////////////////////////////////////////////////////////////
bool Data::isSet() const noexcept {
  return this->raw.isSet() || this->header.isSet();
}

Json::Value Data::toJson() const noexcept {
  DataJson data;
  if (!this->isSet()) {
    return data;
  }
  data[PcoreJson::Key::header] = this->header.toJson();
  data[PcoreJson::Key::raw] = this->raw.toJson();
  Json::Value json;
  json[PcoreJson::Key::data] = data;
  return json;
}

void Data::serialize(DataProtobuf* dataProtobuf) const {
  if (dataProtobuf == nullptr) {
    throw NullPointerException("Data::serialize", "dataProtobuf");
  }
  if (!this->isSet()) {
    return;
  }
  if (this->getHeader().getDataForm() != DataForm::DATA_FORM_DIFFERENTIAL) {
    throw WrongDataFormException("Data::serialize", "only for differential data form");
  }
  HeaderProtobuf headerProtobuf;
  this->header.serialize(&headerProtobuf);
  dataProtobuf->mutable_header()->CopyFrom(headerProtobuf);
  RawProtobuf rawProtobuf;
  this->raw.serialize(&rawProtobuf);
  dataProtobuf->mutable_raw()->CopyFrom(rawProtobuf);
}

void Data::switchDataForm() noexcept {
  if (!this->isSet()) {
    return;
  }
  this->raw.switchDataForm();
  this->header.switchDataForm();
}

bool Data::operator==(const IPCore<DataProtobuf>& data) const noexcept {
  if (const auto* derived = dynamic_cast<const Data*>(&data)) {
    return this->header == derived->header && this->raw == derived->raw;
  }
  return false;
}

bool Data::operator!=(const IPCore<DataProtobuf>& data) const noexcept {
  return !(*this == data);
}

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

Data::Data(Raw raw, const Header& header) : header(header), raw(std::move(raw)) {}

Data::Data(const DataProtobuf& DataProtobuf) : header(Header(DataProtobuf.header())), raw(Raw(DataProtobuf.raw())) {}

Data::Data(const DataJson& dataJson) : header(Header(dataJson[PcoreJsonKey::header])), raw(Raw(dataJson[PcoreJsonKey::raw], header.getDataForm())) {}

Data::Data() : header(Header()), raw(Raw()) {}

Raw Data::getRaw() const {
  return this->raw;
}

Header Data::getHeader() const {
  return this->header;
}

bool Data::operator==(const Data& data) const {
  return this->header == data.header && this->raw == data.raw;
}

bool Data::operator!=(const Data& data) const {
  return this->header != data.header || this->raw != data.raw;
}

void Data::serialize(DataProtobuf* dataProtobuf) const {
  if (dataProtobuf == nullptr) {
    throw std::invalid_argument("Error in serialize: dataProtobuf is a null pointer");
  }
  HeaderProtobuf headerProtobuf;
  this->header.serialize(&headerProtobuf);
  dataProtobuf->mutable_header()->CopyFrom(headerProtobuf);
  RawProtobuf rawProtobuf;
  this->raw.serialize(&rawProtobuf);
  dataProtobuf->mutable_raw()->CopyFrom(rawProtobuf);
}

void Data::switchDataForm() {
  DataForm currentDataForm = this->header.getDataForm();
  this->raw.switchDataForm(currentDataForm);
  this->header.switchDataForm();
}

Json::Value Data::toJson() const {
  DataJson data;
  data[PcoreJsonKey::header] = this->header.toJson();
  data[PcoreJsonKey::raw] = this->raw.toJson(this->header.getDataForm());
  Json::Value json;
  json[PcoreJsonKey::data] = data;
  return json;
}

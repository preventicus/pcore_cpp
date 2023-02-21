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

#include "Data.h"

Data::Data(Raw raw, Header header) : raw(raw), header(header) {}

Data::Data(const ProtobufData& protobufData) {
  this->deserialize(protobufData);
}

Data::Data(Json::Value& data) {
  Json::Value headerJson = data["header"];
  switch (this->toEnum(headerJson["data_form"])) {
    case DataForm::ABSOLUTE: {
      this->raw = Raw(data["raw"], this->toEnum(headerJson["data_form"]));
      this->header = Header(headerJson);
      break;
    }
    case DataForm::DIFFERENTIAL: {
      this->raw = Raw(data["raw"], this->toEnum(headerJson["data_form"]));
      this->header = Header(headerJson);
      break;
    }
    default: {
      break;
    }
  }
}

Data::Data() {
  this->raw = Raw();
  this->header = Header();
}

Raw Data::getRaw() {
  return this->raw;
}

Header Data::getHeader() {
  return this->header;
}

bool Data::isEqual(Data& data) {
  return this->header.isEqual(data.header) && this->raw.isEqual(data.raw);
}

void Data::serialize(ProtobufData* protobufData) {
  if (protobufData == nullptr) {
    throw std::invalid_argument("Error in serialize: protobufData is a null pointer");
  }
  ProtobufHeader protobufHeader;
  this->header.serialize(&protobufHeader);
  protobufData->mutable_header()->CopyFrom(protobufHeader);
  ProtobufRaw protobufRaw;
  this->raw.serialize(&protobufRaw);
  protobufData->mutable_raw()->CopyFrom(protobufRaw);
}

Json::Value Data::toJson(DataForm dataForm) {
  Json::Value data;
  Json::Value json;
  data["header"] = this->header.toJson(dataForm);
  data["raw"] = this->raw.toJson(dataForm);
  json["data"] = data;
  return json;
}

void Data::deserialize(const ProtobufData& protobufData) {
  this->header = Header(protobufData.header());
  this->raw = Raw(protobufData.raw());
}

DataForm Data::toEnum(Json::Value string) {
  if (string.asString() == "ABSOLUTE") {
    return DataForm::ABSOLUTE;
  }
  if (string.asString() == "DIFFERENTIAL") {
    return DataForm::DIFFERENTIAL;
  }
}
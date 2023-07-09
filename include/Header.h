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

#pragma once
#include "DataForm.h"
#include "PcoreJsonKey.h"
#include "Version.h"
#include "protobuf/pcore.pb.h"

using ProtobufHeader = com::preventicus::pcore::Data_Header;
using TimeZoneOffset = int32_t;
using HeaderJson = Json::Value;
using DataFormString = std::string;
using TimeZoneOffsetJson = Json::Value;

class Header final {
 public:
  explicit Header(const Version& version, TimeZoneOffset timeZoneOffset_min, DataForm dataForm);
  explicit Header(const ProtobufHeader& protobufHeader);
  explicit Header(const HeaderJson& header);
  Header();

  [[nodiscard]] TimeZoneOffset getTimeZoneOffset() const;
  [[nodiscard]] Version getPcoreVersion() const;
  [[nodiscard]] DataForm getDataForm() const;

  [[nodiscard]] HeaderJson toJson() const;
  void serialize(ProtobufHeader* protobufHeader) const;
  void switchDataForm();

  static DataForm dataFormFromString(DataFormString dataFormString);
  static DataFormString dataFormToString(DataForm dataForm);

  bool operator==(const Header& header) const;
  bool operator!=(const Header& header) const;

 private:
  void checkTimeZoneOffset() const;
  TimeZoneOffset timeZoneOffset_min;
  Version pcoreVersion;
  DataForm dataForm;
};

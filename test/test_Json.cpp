/*

Created by Jakob Glueck, Steve Merschel 2023

Copyright © 2023 PREVENTICUS GmbH

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors
   may be used to endorse or promote products derived from this software
without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#include <gtest/gtest.h>
#include <fstream>
#include "Data.h"

TEST(JsonTest, TestToJsonAbsoluteForm) {
  std::ifstream file("./../../test/JsonTestData/absolute_pcore.json");
  Json::Value inputJson;
  file >> inputJson;

  auto dataFromJson = Data(inputJson[PcoreJson::Key::data]);
  dataFromJson.switchDataForm();
  DataProtobuf dataProtobuf;
  dataFromJson.serialize(&dataProtobuf);

  auto dataFromProtobuf = Data(dataProtobuf);
  dataFromProtobuf.switchDataForm();
  auto outputJson = dataFromProtobuf.toJson();

  EXPECT_TRUE(inputJson.toStyledString() == outputJson.toStyledString());
}

TEST(JsonTest, TestToJsonDifferentialForm) {
  std::ifstream file("./../../test/JsonTestData/differential_pcore.json");
  Json::Value inputJson;
  file >> inputJson;
  DataProtobuf dataProtobuf;
  Data(inputJson[PcoreJson::Key::data]).serialize(&dataProtobuf);
  auto outputJson = Data(dataProtobuf).toJson();
  EXPECT_TRUE(inputJson.toStyledString() == outputJson.toStyledString());
}
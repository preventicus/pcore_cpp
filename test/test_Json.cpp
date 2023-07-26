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
#include <filesystem>
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

Json::Value calcCain(Json::Value inputJson) {
  //  JsonInAbsoluteForm <------+
  //   | 1.                     |
  //   v                        |
  //  DataInAbsoluteForm        |
  //   | 2.                     |
  //   v                        |
  //  DataInDifferentialForm    |
  //   | 3.                     |
  //   v                        |
  //  JsonInDifferentialForm    |
  //   | 4.                     | 8.
  //   v                        |
  //  DataInDifferentialForm    |
  //   | 5.                     |
  //   v                        |
  //  Protobuf                  |
  //   | 6.                     |
  //   v                        |
  //  DataInDifferentialForm    |
  //   | 7.                     |
  //   v                        |
  //   DataInAbsoluteForm ------+

  // 1.
  auto data = Data(inputJson[PcoreJson::Key::data]);
  // 2.
  data.switchDataForm();
  // 3.
  auto json = data.toJson();
  // 4.
  data = Data(json[PcoreJson::Key::data]);
  // 5.
  DataProtobuf dataProtobuf;
  data.serialize(&dataProtobuf);
  // 6.
  data = Data(dataProtobuf);
  // 7.
  data.switchDataForm();
  // 8.
  return data.toJson();
}

TEST(JsonTest, TestToJsonRealisticData) {
  std::string folderPath = "./../../test/JsonTestData/realisticData";

  for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
    if (entry.path().extension() == ".json") {
      std::ifstream inputFile(entry.path().string());
      if (inputFile) {
        Json::Value inputJson1;
        inputFile >> inputJson1;
        auto inputJson2 = calcCain(inputJson1);
        EXPECT_TRUE(inputJson1.toStyledString() == inputJson2.toStyledString());
        inputFile.close();
      }
    }
  }
}

TEST(JsonTest, TestToJsonPessimalData) {
  std::string folderPath = "./../../test/JsonTestData/pessimalData";

  for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
    if (entry.path().extension() == ".json") {
      std::ifstream inputFile(entry.path().string());
      if (inputFile) {
        Json::Value inputJson1;
        inputFile >> inputJson1;
        auto inputJson2 = calcCain(inputJson1);
        EXPECT_TRUE(inputJson1.toStyledString() == inputJson2.toStyledString());
        inputFile.close();
      }
    }
  }
}

TEST(JsonTest, TestToJsonOptimalData) {
  std::string folderPath = "./../../test/JsonTestData/optimalData";

  for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
    if (entry.path().extension() == ".json") {
      std::ifstream inputFile(entry.path().string());
      if (inputFile) {
        Json::Value inputJson1;
        inputFile >> inputJson1;
        auto inputJson2 = calcCain(inputJson1);
        EXPECT_TRUE(inputJson1.toStyledString() == inputJson2.toStyledString());
        inputFile.close();
      }
    }
  }
}

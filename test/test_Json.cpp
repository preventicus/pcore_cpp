#include <gtest/gtest.h>
#include <fstream>
#include "Data.h"
#include "DataExampleFactory.h"
class JsonTest : public ::testing::Test {
 protected:
  std::string getJsonPath(std::string nameFromJson) { return "./../../test/JsonTestData/" + nameFromJson + ".json"; }
};

TEST_F(JsonTest, JsonObjectWithAbsoluteDataForm) {
  std::ifstream file("/Users/jakobglueck/workspace/protobuf-cpp/test/JsonTestData/absolute_pcore.json");
  Json::Value json;
  file >> json;
  Data pcoreAbsoluteData = Data(json["data"]);
  Data absoluteJsonData = DataExampleFactory::absoluteJsonData();
  EXPECT_TRUE(pcoreAbsoluteData.isEqual(absoluteJsonData));
}

TEST_F(JsonTest, JsonObjectWithDifferentialDataForm) {
  std::ifstream file("/Users/jakobglueck/workspace/protobuf-cpp/test/JsonTestData/differential_pcore.json");
  Json::Value json;
  file >> json;
  Data pcoreDifferentialData = Data(json["data"]);
  Data differentialJsonData = DataExampleFactory::differentialJsonData();
  EXPECT_TRUE(pcoreDifferentialData.isEqual(differentialJsonData));
}

TEST_F(JsonTest, TestToJsonAbsoluteForm) {
  std::ifstream file("/Users/jakobglueck/workspace/protobuf-cpp/test/JsonTestData/absolute_pcore.json");
  Json::Value json;
  file >> json;
  Data pcoreAbsoluteData = Data(json["data"]);
  Data comparableabsoluteData = Data(json["data"]);
  comparableabsoluteData.toJson(DataForm::ABSOLUTE);
  EXPECT_TRUE(pcoreAbsoluteData.isEqual(comparableabsoluteData));
}

TEST_F(JsonTest, TestToJsonDifferentialForm) {
  std::ifstream file("/Users/jakobglueck/workspace/protobuf-cpp/test/JsonTestData/differential_pcore.json");
  Json::Value json;
  file >> json;
  Data differentialJsonData = Data(json["data"]);
  Data comparableDifferentialJsonData = Data(json["data"]);
  comparableDifferentialJsonData.toJson(DataForm::DIFFERENTIAL);
  EXPECT_TRUE(differentialJsonData.isEqual(comparableDifferentialJsonData));
}
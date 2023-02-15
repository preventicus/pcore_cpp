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
  Data comparableAbsoluteData = Data(json["data"]);
  Json::Value data = comparableAbsoluteData.toJson(DataForm::ABSOLUTE);
//  std::cout<< "Complete JSON data: " << std::endl << data << std::endl;
  EXPECT_EQ(json["data"], data["data"]);
  EXPECT_EQ(json["data"]["header"], data["data"]["header"]);
  EXPECT_EQ(json["data"]["header"]["time_zone_offset_min"], data["data"]["header"]["time_zone_offset_min"]);
  EXPECT_EQ(json["data"]["header"]["version"]["major"], data["data"]["header"]["version"]["major"]);
  EXPECT_EQ(json["data"]["header"]["version"]["minor"], data["data"]["header"]["version"]["minor"]);
  EXPECT_EQ(json["data"]["header"]["version"]["patch"], data["data"]["header"]["version"]["patch"]);
  EXPECT_EQ(json["data"]["header"]["data_form"], data["data"]["header"]["data_form"]);
  EXPECT_EQ(json["data"]["raw"], data["data"]["raw"]);
  EXPECT_EQ(json["data"]["raw"]["sensors"].size(), data["data"]["raw"]["sensors"].size());
  for(Json::Value::ArrayIndex i = 0; i <json["data"]["raw"]["sensors"].size(); i++){
    EXPECT_EQ(json["data"]["raw"]["sensors"][i] , data["data"]["raw"]["sensors"][i]);
    for(Json::Value::ArrayIndex j = 0; j < json["data"]["raw"]["sensors"][i]["channels"].size(); j++) {
      EXPECT_EQ(json["data"]["raw"]["sensors"][i]["channels"][j], data["data"]["raw"]["sensors"][i]["channels"][j]);
      EXPECT_EQ(json["data"]["raw"]["sensors"][i]["channels"][j]["ppg_metadata"], data["data"]["raw"]["sensors"][i]["channels"][j]["ppg_metadata"]);
      EXPECT_EQ(json["data"]["raw"]["sensors"][i]["channels"][j]["acc_metadata"], data["data"]["raw"]["sensors"][i]["channels"][j]["acc_metadata"]);
      EXPECT_EQ(json["data"]["raw"]["sensors"][i]["channels"][j]["absolute_block"],
                data["data"]["raw"]["sensors"][i]["channels"][j]["absolute_block"]);
      for (Json::Value::ArrayIndex k = 0; k < json["data"]["raw"]["sensors"][i]["channels"][j]["absolute_block"]["absolute_values"].size(); k++) {
        EXPECT_EQ(json["data"]["raw"]["sensors"][i]["channels"][j]["absolute_block"]["absolute_values"][k],
                  data["data"]["raw"]["sensors"][i]["channels"][j]["absolute_block"]["absolute_values"][k]);
      }
      for (Json::Value::ArrayIndex l = 0; l < json["data"]["raw"]["sensors"][i]["channels"][j]["differential_blocks"].size(); l++) {
        EXPECT_EQ(json["data"]["raw"]["sensors"][i]["channels"][j]["differential_blocks"][l],
                  data["data"]["raw"]["sensors"][i]["channels"][j]["differential_blocks"][l]);
        for (Json::Value::ArrayIndex m = 0; m < json["data"]["raw"]["sensors"][i]["channels"][j]["differential_blocks"][l]["diff_values"].size();
             l++) {
          EXPECT_EQ(json["data"]["raw"]["sensors"][i]["channels"][j]["differential_blocks"][l]["diff_values"][m],
                    data["data"]["raw"]["sensors"][i]["channels"][j]["differential_blocks"][l]["diff_values"][m]);
        }
      }
    }
  EXPECT_EQ(json["data"]["raw"]["sensors"][i]["absolute_timestamps_container"], data["data"]["raw"]["sensors"][i]["absolute_timestamps_container"]);
  for(Json::Value::ArrayIndex n = 0; n < json["data"]["raw"]["sensors"][i]["absolute_timestamps_container"]["unix_timestamps_ms"].size(); n++){
    EXPECT_EQ(json["data"]["raw"]["sensors"][i]["absolute_timestamps_container"]["unix_timestamps_ms"][n],data["data"]["raw"]["sensors"][i]["absolute_timestamps_container"]["unix_timestamps_ms"][n]);
  }
  EXPECT_EQ(json["data"]["raw"]["sensors"][i]["differential_timestamps_container"], data["data"]["raw"]["sensors"][i]["differential_timestamps_container"]);
  EXPECT_EQ(json["data"]["raw"]["sensors"][i]["differential_timestamps_container"]["first_timestamp_ms"], data["data"]["raw"]["sensors"][i]["differential_timestamps_container"]["first_timestamp_ms"]);
  for(Json::Value::ArrayIndex o = 0; o <json["data"]["raw"]["sensors"][i]["differential_timestamps_container"]["block_intervals_ms"].size();o++){
    EXPECT_EQ(json["data"]["raw"]["sensors"][i]["differential_timestamps_container"]["block_intervals_ms"][o],data["data"]["raw"]["sensors"][i]["differential_timestamps_container"]["block_intervals_ms"][o]);
  }
  for(Json::Value::ArrayIndex p = 0; p <json["data"]["raw"]["sensors"][i]["differential_timestamps_container"]["block_intervals_ms"].size();p++){
    EXPECT_EQ(json["data"]["raw"]["sensors"][i]["differential_timestamps_container"]["timestamps_intervals_ms"][p],data["data"]["raw"]["sensors"][i]["differential_timestamps_container"]["timestamps_intervals_ms"][p]);
  }
  EXPECT_EQ(json["data"]["raw"]["sensors"][i]["sensor_type"], data["data"]["raw"]["sensors"][i]["sensor_type"]);
  }
}

TEST_F(JsonTest, TestToJsonDifferentialForm) {
  std::ifstream file("/Users/jakobglueck/workspace/protobuf-cpp/test/JsonTestData/differential_pcore.json");
  Json::Value json;
  file >> json;
  Data differentialJsonData = Data(json["data"]);
  Data comparableDifferentialJsonData = Data(json["data"]);
  Json::Value data = comparableDifferentialJsonData.toJson(DataForm::DIFFERENTIAL);
  EXPECT_EQ(json["data"], data["data"]);
  EXPECT_EQ(json["data"]["header"], data["data"]["header"]);
  EXPECT_EQ(json["data"]["header"]["time_zone_offset_min"], data["data"]["header"]["time_zone_offset_min"]);
  EXPECT_EQ(json["data"]["header"]["version"]["major"], data["data"]["header"]["version"]["major"]);
  EXPECT_EQ(json["data"]["header"]["version"]["minor"], data["data"]["header"]["version"]["minor"]);
  EXPECT_EQ(json["data"]["header"]["version"]["patch"], data["data"]["header"]["version"]["patch"]);
  EXPECT_EQ(json["data"]["header"]["data_form"], data["data"]["header"]["data_form"]);
  EXPECT_EQ(json["data"]["raw"], data["data"]["raw"]);
  EXPECT_EQ(json["data"]["raw"]["sensors"].size(), data["data"]["raw"]["sensors"].size());
  for(Json::Value::ArrayIndex i = 0; i <json["data"]["raw"]["sensors"].size(); i++){
  EXPECT_EQ(json["data"]["raw"]["sensors"][i] , data["data"]["raw"]["sensors"][i]);
  for(Json::Value::ArrayIndex j = 0; j < json["data"]["raw"]["sensors"][i]["channels"].size(); j++) {
    EXPECT_EQ(json["data"]["raw"]["sensors"][i]["channels"][j], data["data"]["raw"]["sensors"][i]["channels"][j]);
    EXPECT_EQ(json["data"]["raw"]["sensors"][i]["channels"][j]["ppg_metadata"], data["data"]["raw"]["sensors"][i]["channels"][j]["ppg_metadata"]);
    EXPECT_EQ(json["data"]["raw"]["sensors"][i]["channels"][j]["acc_metadata"], data["data"]["raw"]["sensors"][i]["channels"][j]["acc_metadata"]);
    EXPECT_EQ(json["data"]["raw"]["sensors"][i]["channels"][j]["absolute_block"],
              data["data"]["raw"]["sensors"][i]["channels"][j]["absolute_block"]);
    for (Json::Value::ArrayIndex k = 0; k < json["data"]["raw"]["sensors"][i]["channels"][j]["absolute_block"]["absolute_values"].size(); k++) {
        EXPECT_EQ(json["data"]["raw"]["sensors"][i]["channels"][j]["absolute_block"]["absolute_values"][k],
                  data["data"]["raw"]["sensors"][i]["channels"][j]["absolute_block"]["absolute_values"][k]);
    }
    for (Json::Value::ArrayIndex l = 0; l < json["data"]["raw"]["sensors"][i]["channels"][j]["differential_blocks"].size(); l++) {
        EXPECT_EQ(json["data"]["raw"]["sensors"][i]["channels"][j]["differential_blocks"][l],
                  data["data"]["raw"]["sensors"][i]["channels"][j]["differential_blocks"][l]);
        for (Json::Value::ArrayIndex m = 0; m < json["data"]["raw"]["sensors"][i]["channels"][j]["differential_blocks"][l]["diff_values"].size();
             l++) {
          EXPECT_EQ(json["data"]["raw"]["sensors"][i]["channels"][j]["differential_blocks"][l]["diff_values"][m],
                    data["data"]["raw"]["sensors"][i]["channels"][j]["differential_blocks"][l]["diff_values"][m]);
        }
    }
  }
  EXPECT_EQ(json["data"]["raw"]["sensors"][i]["absolute_timestamps_container"], data["data"]["raw"]["sensors"][i]["absolute_timestamps_container"]);
  for(Json::Value::ArrayIndex n = 0; n < json["data"]["raw"]["sensors"][i]["absolute_timestamps_container"]["unix_timestamps_ms"].size(); n++){
    EXPECT_EQ(json["data"]["raw"]["sensors"][i]["absolute_timestamps_container"]["unix_timestamps_ms"][n],data["data"]["raw"]["sensors"][i]["absolute_timestamps_container"]["unix_timestamps_ms"][n]);
  }
  EXPECT_EQ(json["data"]["raw"]["sensors"][i]["differential_timestamps_container"], data["data"]["raw"]["sensors"][i]["differential_timestamps_container"]);
  EXPECT_EQ(json["data"]["raw"]["sensors"][i]["differential_timestamps_container"]["first_timestamp_ms"], data["data"]["raw"]["sensors"][i]["differential_timestamps_container"]["first_timestamp_ms"]);
  for(Json::Value::ArrayIndex o = 0; o <json["data"]["raw"]["sensors"][i]["differential_timestamps_container"]["block_intervals_ms"].size();o++){
    EXPECT_EQ(json["data"]["raw"]["sensors"][i]["differential_timestamps_container"]["block_intervals_ms"][o],data["data"]["raw"]["sensors"][i]["differential_timestamps_container"]["block_intervals_ms"][o]);
  }
  for(Json::Value::ArrayIndex p = 0; p <json["data"]["raw"]["sensors"][i]["differential_timestamps_container"]["block_intervals_ms"].size();p++){
    EXPECT_EQ(json["data"]["raw"]["sensors"][i]["differential_timestamps_container"]["timestamps_intervals_ms"][p],data["data"]["raw"]["sensors"][i]["differential_timestamps_container"]["timestamps_intervals_ms"][p]);
  }
  EXPECT_EQ(json["data"]["raw"]["sensors"][i]["sensor_type"], data["data"]["raw"]["sensors"][i]["sensor_type"]);
  }
}
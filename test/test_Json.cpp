#include <gtest/gtest.h>
#include <fstream>
#include "Data.h"
#include "DataExampleFactory.h"
class JsonTest : public ::testing::Test {
 protected:
  std::string static getJsonPath(std::string nameFromJson) { return "./../../test/JsonTestData/" + nameFromJson; }
};

TEST_F(JsonTest, JsonObjectWithAbsoluteDataForm) {
  std::ifstream file(JsonTest::getJsonPath("absolute_pcore.json"));
  Json::Value inputJson;
  file >> inputJson;
  Data pcoreAbsoluteData = Data(inputJson["data"]);
  Data outputJson = DataExampleFactory::absoluteJsonData();
  EXPECT_TRUE(pcoreAbsoluteData.isEqual(outputJson));
}

TEST_F(JsonTest, JsonObjectWithDifferentialDataForm) {
  std::ifstream file(JsonTest::getJsonPath("differential_pcore.json"));
  Json::Value inputJson;
  file >> inputJson;
  Data pcoreDifferentialData = Data(inputJson["data"]);
  Data outputJson = DataExampleFactory::differentialJsonData();
  EXPECT_TRUE(pcoreDifferentialData.isEqual(outputJson));
}

TEST_F(JsonTest, TestToJsonAbsoluteForm) {
  std::ifstream file(JsonTest::getJsonPath("absolute_pcore.json"));
  Json::Value inputJson;
  file >> inputJson;
  Data absoluteData = Data(inputJson["data"]);
  Json::Value outputJson = absoluteData.toJson(DataForm::ABSOLUTE);

  EXPECT_EQ(inputJson["data"]["header"]["version"]["major"].asUInt(), outputJson["data"]["header"]["version"]["major"].asUInt64());
  EXPECT_EQ(inputJson["data"]["header"]["time_zone_offset_min"].asUInt(), outputJson["data"]["header"]["time_zone_offset_min"].asUInt());
  EXPECT_EQ(inputJson["data"]["header"]["version"]["major"].asUInt(), outputJson["data"]["header"]["version"]["major"].asUInt64());
  EXPECT_EQ(inputJson["data"]["header"]["version"]["minor"].asUInt(), outputJson["data"]["header"]["version"]["minor"].asUInt());
  EXPECT_EQ(inputJson["data"]["header"]["version"]["patch"].asUInt(), outputJson["data"]["header"]["version"]["patch"].asUInt());
  EXPECT_EQ(inputJson["data"]["header"]["data_form"].asString(), outputJson["data"]["header"]["data_form"].asString());
  EXPECT_EQ(inputJson["data"]["raw"]["sensors"].size(), outputJson["data"]["raw"]["sensors"].size());
  for (Json::Value::ArrayIndex i = 0; i < inputJson["data"]["raw"]["sensors"].size(); i++) {
    for (Json::Value::ArrayIndex j = 0; j < inputJson["data"]["raw"]["sensors"][i]["channels"].size(); j++) {
      EXPECT_EQ(inputJson["data"]["raw"]["sensors"][i]["channels"][j]["ppg_metadata"]["color"].asString(),
                outputJson["data"]["raw"]["sensors"][i]["channels"][j]["ppg_metadata"]["color"].asString());
      EXPECT_EQ(inputJson["data"]["raw"]["sensors"][i]["channels"][j]["ppg_metadata"]["wavelength_nm"].asInt(),
                outputJson["data"]["raw"]["sensors"][i]["channels"][j]["ppg_metadata"]["wavelength_nm"].asInt());
      EXPECT_EQ(inputJson["data"]["raw"]["sensors"][i]["channels"][j]["acc_metadata"]["norm"].asString(),
                outputJson["data"]["raw"]["sensors"][i]["channels"][j]["acc_metadata"]["norm"].asString());
      EXPECT_EQ(inputJson["data"]["raw"]["sensors"][i]["channels"][j]["acc_metadata"]["coordinate"].asString(),
                outputJson["data"]["raw"]["sensors"][i]["channels"][j]["acc_metadata"]["coordinate"].asString());
      for (Json::Value::ArrayIndex k = 0; k < inputJson["data"]["raw"]["sensors"][i]["channels"][j]["absolute_block"]["absolute_values"].size(); k++) {
        EXPECT_EQ(inputJson["data"]["raw"]["sensors"][i]["channels"][j]["absolute_block"]["absolute_values"][k].asInt(),
                  outputJson["data"]["raw"]["sensors"][i]["channels"][j]["absolute_block"]["absolute_values"][k].asInt());
      }
      for (Json::Value::ArrayIndex l = 0; l < inputJson["data"]["raw"]["sensors"][i]["channels"][j]["differential_blocks"].size(); l++) {
        for (Json::Value::ArrayIndex m = 0;
             m < inputJson["data"]["raw"]["sensors"][i]["channels"][j]["differential_blocks"][l]["differential_values"].size(); l++) {
          EXPECT_EQ(inputJson["data"]["raw"]["sensors"][i]["channels"][j]["differential_blocks"][l]["differential_values"][m].asInt(),
                    outputJson["data"]["raw"]["sensors"][i]["channels"][j]["differential_blocks"][l]["differential_values"][m].asInt());
        }
      }
    }
    for (Json::Value::ArrayIndex n = 0; n < inputJson["data"]["raw"]["sensors"][i]["absolute_timestamps_container"]["unix_timestamps_ms"].size(); n++) {
      EXPECT_EQ(inputJson["data"]["raw"]["sensors"][i]["absolute_timestamps_container"]["unix_timestamps_ms"][n].asUInt64(),
                outputJson["data"]["raw"]["sensors"][i]["absolute_timestamps_container"]["unix_timestamps_ms"][n].asUInt64());
    }

    EXPECT_EQ(inputJson["data"]["raw"]["sensors"][i]["differential_timestamps_container"]["first_timestamp_ms"].asUInt64(),
              outputJson["data"]["raw"]["sensors"][i]["differential_timestamps_container"]["first_timestamp_ms"].asUInt64());
    for (Json::Value::ArrayIndex o = 0; o < inputJson["data"]["raw"]["sensors"][i]["differential_timestamps_container"]["block_intervals_ms"].size();
         o++) {
      EXPECT_EQ(inputJson["data"]["raw"]["sensors"][i]["differential_timestamps_container"]["block_intervals_ms"][o].asUInt(),
                outputJson["data"]["raw"]["sensors"][i]["differential_timestamps_container"]["block_intervals_ms"][o].asUInt());
    }
    for (Json::Value::ArrayIndex p = 0; p < inputJson["data"]["raw"]["sensors"][i]["differential_timestamps_container"]["timestamps_intervals_ms"].size();
         p++) {
      EXPECT_EQ(inputJson["data"]["raw"]["sensors"][i]["differential_timestamps_container"]["timestamps_intervals_ms"][p].asUInt(),
                outputJson["data"]["raw"]["sensors"][i]["differential_timestamps_container"]["timestamps_intervals_ms"][p].asUInt());
    }
    EXPECT_EQ(inputJson["data"]["raw"]["sensors"][i]["sensor_type"].asString(), inputJson["data"]["raw"]["sensors"][i]["sensor_type"].asString());
  }
}

TEST_F(JsonTest, TestToJsonDifferentialForm) {
  std::ifstream file(JsonTest::getJsonPath("differential_pcore.json"));
  Json::Value inputJson;
  file >> inputJson;
  Data differentialJsonData = Data(inputJson["data"]);
  Json::Value outputJson = differentialJsonData.toJson(DataForm::DIFFERENTIAL);

  EXPECT_EQ(inputJson["data"]["header"]["version"]["major"].asUInt(), outputJson["data"]["header"]["version"]["major"].asUInt64());
  EXPECT_EQ(inputJson["data"]["header"]["time_zone_offset_min"].asUInt(), outputJson["data"]["header"]["time_zone_offset_min"].asUInt());
  EXPECT_EQ(inputJson["data"]["header"]["version"]["major"].asUInt(), outputJson["data"]["header"]["version"]["major"].asUInt64());
  EXPECT_EQ(inputJson["data"]["header"]["version"]["minor"].asUInt(), outputJson["data"]["header"]["version"]["minor"].asUInt());
  EXPECT_EQ(inputJson["data"]["header"]["version"]["patch"].asUInt(), outputJson["data"]["header"]["version"]["patch"].asUInt());
  EXPECT_EQ(inputJson["data"]["header"]["data_form"].asString(), outputJson["data"]["header"]["data_form"].asString());
  EXPECT_EQ(inputJson["data"]["raw"]["sensors"].size(), outputJson["data"]["raw"]["sensors"].size());
  for (Json::Value::ArrayIndex i = 0; i < inputJson["data"]["raw"]["sensors"].size(); i++) {
    for (Json::Value::ArrayIndex j = 0; j < inputJson["data"]["raw"]["sensors"][i]["channels"].size(); j++) {
      EXPECT_EQ(inputJson["data"]["raw"]["sensors"][i]["channels"][j]["ppg_metadata"]["color"].asString(),
                outputJson["data"]["raw"]["sensors"][i]["channels"][j]["ppg_metadata"]["color"].asString());
      EXPECT_EQ(inputJson["data"]["raw"]["sensors"][i]["channels"][j]["ppg_metadata"]["wavelength_nm"].asInt(),
                outputJson["data"]["raw"]["sensors"][i]["channels"][j]["ppg_metadata"]["wavelength_nm"].asInt());
      EXPECT_EQ(inputJson["data"]["raw"]["sensors"][i]["channels"][j]["acc_metadata"]["norm"].asString(),
                outputJson["data"]["raw"]["sensors"][i]["channels"][j]["acc_metadata"]["norm"].asString());
      EXPECT_EQ(inputJson["data"]["raw"]["sensors"][i]["channels"][j]["acc_metadata"]["coordinate"].asString(),
                outputJson["data"]["raw"]["sensors"][i]["channels"][j]["acc_metadata"]["coordinate"].asString());
      for (Json::Value::ArrayIndex k = 0; k < inputJson["data"]["raw"]["sensors"][i]["channels"][j]["absolute_block"]["absolute_values"].size(); k++) {
        EXPECT_EQ(inputJson["data"]["raw"]["sensors"][i]["channels"][j]["absolute_block"]["absolute_values"][k].asInt(),
                  outputJson["data"]["raw"]["sensors"][i]["channels"][j]["absolute_block"]["absolute_values"][k].asInt());
      }
      for (Json::Value::ArrayIndex l = 0; l < inputJson["data"]["raw"]["sensors"][i]["channels"][j]["differential_blocks"].size(); l++) {
        for (Json::Value::ArrayIndex m = 0; m < inputJson["data"]["raw"]["sensors"][i]["channels"][j]["differential_blocks"][l]["diff_values"].size();
             l++) {
          EXPECT_EQ(inputJson["data"]["raw"]["sensors"][i]["channels"][j]["differential_blocks"][l]["differential_values"][m].asInt(),
                    outputJson["data"]["raw"]["sensors"][i]["channels"][j]["differential_blocks"][l]["differential_values"][m].asInt());
        }
      }
      EXPECT_EQ(inputJson["data"]["raw"]["sensors"][i]["channels"][j]["acc_metadata"]["norm"].asString(),
                outputJson["data"]["raw"]["sensors"][i]["channels"][j]["acc_metadata"]["norm"].asString());
      EXPECT_EQ(inputJson["data"]["raw"]["sensors"][i]["channels"][j]["acc_metadata"]["coordinate"].asString(),
                outputJson["data"]["raw"]["sensors"][i]["channels"][j]["acc_metadata"]["coordinate"].asString());
      for (Json::Value::ArrayIndex k = 0; k < inputJson["data"]["raw"]["sensors"][i]["channels"][j]["absolute_block"]["absolute_values"].size(); k++) {
        EXPECT_EQ(inputJson["data"]["raw"]["sensors"][i]["channels"][j]["absolute_block"]["absolute_values"][k].asInt(),
                  outputJson["data"]["raw"]["sensors"][i]["channels"][j]["absolute_block"]["absolute_values"][k].asInt());
      }
      for (Json::Value::ArrayIndex l = 0; l < inputJson["data"]["raw"]["sensors"][i]["channels"][j]["differential_blocks"].size(); l++) {
        for (Json::Value::ArrayIndex m = 0;
             m < inputJson["data"]["raw"]["sensors"][i]["channels"][j]["differential_blocks"][l]["differential_values"].size(); l++) {
          EXPECT_EQ(inputJson["data"]["raw"]["sensors"][i]["channels"][j]["differential_blocks"][l]["differential_values"][m].asInt(),
                    outputJson["data"]["raw"]["sensors"][i]["channels"][j]["differential_blocks"][l]["differential_values"][m].asInt());
        }
      }
    }
    for (Json::Value::ArrayIndex n = 0; n < inputJson["data"]["raw"]["sensors"][i]["absolute_timestamps_container"]["unix_timestamps_ms"].size(); n++) {
      EXPECT_EQ(inputJson["data"]["raw"]["sensors"][i]["absolute_timestamps_container"]["unix_timestamps_ms"][n].asUInt64(),
                outputJson["data"]["raw"]["sensors"][i]["absolute_timestamps_container"]["unix_timestamps_ms"][n].asUInt64());
    }

    EXPECT_EQ(inputJson["data"]["raw"]["sensors"][i]["differential_timestamps_container"]["first_timestamp_ms"].asUInt64(),
              outputJson["data"]["raw"]["sensors"][i]["differential_timestamps_container"]["first_timestamp_ms"].asUInt64());
    for (Json::Value::ArrayIndex o = 0; o < inputJson["data"]["raw"]["sensors"][i]["differential_timestamps_container"]["block_intervals_ms"].size();
         o++) {
      EXPECT_EQ(inputJson["data"]["raw"]["sensors"][i]["differential_timestamps_container"]["block_intervals_ms"][o].asUInt(),
                outputJson["data"]["raw"]["sensors"][i]["differential_timestamps_container"]["block_intervals_ms"][o].asUInt());
    }
    for (Json::Value::ArrayIndex p = 0; p < inputJson["data"]["raw"]["sensors"][i]["differential_timestamps_container"]["timestamps_intervals_ms"].size();
         p++) {
      EXPECT_EQ(inputJson["data"]["raw"]["sensors"][i]["differential_timestamps_container"]["timestamps_intervals_ms"][p].asUInt(),
                outputJson["data"]["raw"]["sensors"][i]["differential_timestamps_container"]["timestamps_intervals_ms"][p].asUInt());
    }
    EXPECT_EQ(inputJson["data"]["raw"]["sensors"][i]["sensor_type"].asString(), outputJson["data"]["raw"]["sensors"][i]["sensor_type"].asString());
  }
}
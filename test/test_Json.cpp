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

  ProtobufData data;
  Data(inputJson["data"]).serialize(&data);
  Json::Value outputJson = Data(data).toJson(DataForm::ABSOLUTE);
  Json::Value inputJsonHeader = inputJson["data"]["header"];
  Json::Value outputJsonHeader = outputJson["data"]["header"];
  Json::Value inputJsonVersion = inputJsonHeader["version"];
  Json::Value outputJsonVersion = inputJsonHeader["version"];
  EXPECT_EQ(inputJsonVersion["major"].asUInt(), outputJsonVersion["major"].asUInt64());
  EXPECT_EQ(inputJsonHeader["time_zone_offset_min"].asUInt(), outputJsonHeader["time_zone_offset_min"].asUInt());
  EXPECT_EQ(inputJsonVersion["major"].asUInt(), outputJsonVersion["major"].asUInt64());
  EXPECT_EQ(inputJsonVersion["minor"].asUInt(), outputJsonVersion["minor"].asUInt());
  EXPECT_EQ(inputJsonVersion["patch"].asUInt(), outputJsonVersion["patch"].asUInt());
  EXPECT_EQ(inputJsonHeader["data_form"].asString(), outputJsonHeader["data_form"].asString());
  for (Json::Value::ArrayIndex i = 0; i < inputJson["data"]["raw"]["sensors"].size(); i++) {
    Json::Value inputJsonSensor = inputJson["data"]["raw"]["sensors"][i];
    Json::Value outputJsonSensor = outputJson["data"]["raw"]["sensors"][i];
    for (Json::Value::ArrayIndex ii = 0; ii < inputJsonSensor["channels"].size(); ii++) {
      Json::Value inputJsonChannel = inputJson["data"]["raw"]["sensors"][i]["channels"][ii];
      Json::Value outputJsonChannel = outputJson["data"]["raw"]["sensors"][i]["channels"][ii];
      EXPECT_EQ(inputJsonChannel["ppg_metadata"]["color"].asString(), outputJsonChannel["ppg_metadata"]["color"].asString());
      EXPECT_EQ(inputJsonChannel["ppg_metadata"]["wavelength_nm"].asInt(), outputJsonChannel["ppg_metadata"]["wavelength_nm"].asInt());
      EXPECT_EQ(inputJsonChannel["acc_metadata"]["norm"].asString(), outputJsonChannel["acc_metadata"]["norm"].asString());
      EXPECT_EQ(inputJsonChannel["acc_metadata"]["coordinate"].asString(), outputJsonChannel["acc_metadata"]["coordinate"].asString());
      for (Json::Value::ArrayIndex iii = 0; iii < inputJsonChannel["absolute_block"]["absolute_values"].size(); iii++) {
        EXPECT_EQ(inputJsonChannel["absolute_block"]["absolute_values"][iii].asInt(),
                  outputJsonChannel["absolute_block"]["absolute_values"][iii].asInt());
      }
      for (Json::Value::ArrayIndex iii = 0; iii < inputJsonChannel["differential_blocks"].size(); iii++) {
        Json::Value inputJsonDifferentialBlock = inputJson["data"]["raw"]["sensors"][i]["channels"][ii]["differential_blocks"][iii];
        Json::Value outputJsonDifferentialBlock = outputJson["data"]["raw"]["sensors"][i]["channels"][ii]["differential_blocks"][iii];
        for (Json::Value::ArrayIndex iv = 0; iv < inputJsonDifferentialBlock["differential_values"].size(); iv++) {
          EXPECT_EQ(inputJsonDifferentialBlock["differential_values"][iv].asInt(), outputJsonDifferentialBlock["differential_values"][iv].asInt());
        }
      }
    }
    for (Json::Value::ArrayIndex ii = 0; ii < inputJsonSensor["absolute_timestamps_container"]["unix_timestamps_ms"].size(); ii++) {
      EXPECT_EQ(inputJsonSensor["absolute_timestamps_container"]["unix_timestamps_ms"][ii].asUInt64(),
                outputJsonSensor["absolute_timestamps_container"]["unix_timestamps_ms"][ii].asUInt64());
    }
    Json::Value inputJsonDifferentialTimestampsContainer = inputJsonSensor["differential_timestamps_container"];
    Json::Value outputJsonDifferentialTimestampsContainer = outputJsonSensor["differential_timestamps_container"];
    EXPECT_EQ(inputJsonDifferentialTimestampsContainer["first_timestamp_ms"].asUInt64(),
              outputJsonDifferentialTimestampsContainer["first_timestamp_ms"].asUInt64());
    for (Json::Value::ArrayIndex ii = 0; ii < inputJsonDifferentialTimestampsContainer["block_intervals_ms"].size(); ii++) {
      EXPECT_EQ(inputJsonDifferentialTimestampsContainer["block_intervals_ms"][ii].asUInt(),
                outputJsonDifferentialTimestampsContainer["block_intervals_ms"][ii].asUInt());
    }
    for (Json::Value::ArrayIndex ii = 0; ii < inputJsonDifferentialTimestampsContainer["timestamps_intervals_ms"].size(); ii++) {
      EXPECT_EQ(inputJsonDifferentialTimestampsContainer["timestamps_intervals_ms"][ii].asUInt(),
                outputJsonDifferentialTimestampsContainer["timestamps_intervals_ms"][ii].asUInt());
    }
    EXPECT_EQ(inputJsonSensor["sensor_type"].asString(), outputJsonSensor["sensor_type"].asString());
  }
}

TEST_F(JsonTest, TestToJsonDifferentialForm) {
  std::ifstream file(JsonTest::getJsonPath("differential_pcore.json"));
  Json::Value inputJson;
  file >> inputJson;

  ProtobufData data;
  Data(inputJson["data"]).serialize(&data);
  Json::Value outputJson = Data(data).toJson(DataForm::DIFFERENTIAL);
  std::cout << outputJson << std::endl;
  Json::Value inputJsonHeader = inputJson["data"]["header"];
  Json::Value outputJsonHeader = outputJson["data"]["header"];
  Json::Value inputJsonVersion = inputJsonHeader["version"];
  Json::Value outputJsonVersion = inputJsonHeader["version"];
  EXPECT_EQ(inputJsonVersion["major"].asUInt(), outputJsonVersion["major"].asUInt64());
  EXPECT_EQ(inputJsonHeader["time_zone_offset_min"].asUInt(), outputJsonHeader["time_zone_offset_min"].asUInt());
  EXPECT_EQ(inputJsonVersion["major"].asUInt(), outputJsonVersion["major"].asUInt64());
  EXPECT_EQ(inputJsonVersion["minor"].asUInt(), outputJsonVersion["minor"].asUInt());
  EXPECT_EQ(inputJsonVersion["patch"].asUInt(), outputJsonVersion["patch"].asUInt());
  EXPECT_EQ(inputJsonHeader["data_form"].asString(), outputJsonHeader["data_form"].asString());
  for (Json::Value::ArrayIndex i = 0; i < inputJson["data"]["raw"]["sensors"].size(); i++) {
    Json::Value inputJsonSensor = inputJson["data"]["raw"]["sensors"][i];
    Json::Value outputJsonSensor = outputJson["data"]["raw"]["sensors"][i];
    for (Json::Value::ArrayIndex ii = 0; ii < inputJsonSensor["channels"].size(); ii++) {
      Json::Value inputJsonChannel = inputJson["data"]["raw"]["sensors"][i]["channels"][ii];
      Json::Value outputJsonChannel = outputJson["data"]["raw"]["sensors"][i]["channels"][ii];
      EXPECT_EQ(inputJsonChannel["ppg_metadata"]["color"].asString(), outputJsonChannel["ppg_metadata"]["color"].asString());
      EXPECT_EQ(inputJsonChannel["ppg_metadata"]["wavelength_nm"].asInt(), outputJsonChannel["ppg_metadata"]["wavelength_nm"].asInt());
      EXPECT_EQ(inputJsonChannel["acc_metadata"]["norm"].asString(), outputJsonChannel["acc_metadata"]["norm"].asString());
      EXPECT_EQ(inputJsonChannel["acc_metadata"]["coordinate"].asString(), outputJsonChannel["acc_metadata"]["coordinate"].asString());
      for (Json::Value::ArrayIndex iii = 0; iii < inputJsonChannel["absolute_block"]["absolute_values"].size(); iii++) {
        EXPECT_EQ(inputJsonChannel["absolute_block"]["absolute_values"][iii].asInt(),
                  outputJsonChannel["absolute_block"]["absolute_values"][iii].asInt());
      }
      for (Json::Value::ArrayIndex iii = 0; iii < inputJsonChannel["differential_blocks"].size(); iii++) {
        Json::Value inputJsonDifferentialBlock = inputJson["data"]["raw"]["sensors"][i]["channels"][ii]["differential_blocks"][iii];
        Json::Value outputJsonDifferentialBlock = outputJson["data"]["raw"]["sensors"][i]["channels"][ii]["differential_blocks"][iii];
        for (Json::Value::ArrayIndex iv = 0; iv < inputJsonDifferentialBlock["differential_values"].size(); iv++) {
          EXPECT_EQ(inputJsonDifferentialBlock["differential_values"][iv].asInt(), outputJsonDifferentialBlock["differential_values"][iv].asInt());
        }
      }
    }
    for (Json::Value::ArrayIndex ii = 0; ii < inputJsonSensor["absolute_timestamps_container"]["unix_timestamps_ms"].size(); ii++) {
      EXPECT_EQ(inputJsonSensor["absolute_timestamps_container"]["unix_timestamps_ms"][ii].asUInt64(),
                outputJsonSensor["absolute_timestamps_container"]["unix_timestamps_ms"][ii].asUInt64());
    }
    Json::Value inputJsonDifferentialTimestampsContainer = inputJsonSensor["differential_timestamps_container"];
    Json::Value outputJsonDifferentialTimestampsContainer = outputJsonSensor["differential_timestamps_container"];
    EXPECT_EQ(inputJsonDifferentialTimestampsContainer["first_timestamp_ms"].asUInt64(),
              outputJsonDifferentialTimestampsContainer["first_timestamp_ms"].asUInt64());
    for (Json::Value::ArrayIndex ii = 0; ii < inputJsonDifferentialTimestampsContainer["block_intervals_ms"].size(); ii++) {
      EXPECT_EQ(inputJsonDifferentialTimestampsContainer["block_intervals_ms"][ii].asUInt(),
                outputJsonDifferentialTimestampsContainer["block_intervals_ms"][ii].asUInt());
    }
    for (Json::Value::ArrayIndex ii = 0; ii < inputJsonDifferentialTimestampsContainer["timestamps_intervals_ms"].size(); ii++) {
      EXPECT_EQ(inputJsonDifferentialTimestampsContainer["timestamps_intervals_ms"][ii].asUInt(),
                outputJsonDifferentialTimestampsContainer["timestamps_intervals_ms"][ii].asUInt());
    }
    EXPECT_EQ(inputJsonSensor["sensor_type"].asString(), outputJsonSensor["sensor_type"].asString());
  }
}
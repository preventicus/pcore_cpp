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
  Json::Value json;
  file >> json;
  Data pcoreAbsoluteData = Data(json["data"]);
  Data absoluteJsonData = DataExampleFactory::absoluteJsonData();
  EXPECT_TRUE(pcoreAbsoluteData.isEqual(absoluteJsonData));
}

TEST_F(JsonTest, JsonObjectWithDifferentialDataForm) {
  std::ifstream file(JsonTest::getJsonPath("differential_pcore.json"));
  Json::Value json;
  file >> json;
  Data pcoreDifferentialData = Data(json["data"]);
  Data differentialJsonData = DataExampleFactory::differentialJsonData();
  EXPECT_TRUE(pcoreDifferentialData.isEqual(differentialJsonData));
}

TEST_F(JsonTest, TestToJsonAbsoluteForm) {
  std::ifstream file(JsonTest::getJsonPath("absolute_pcore.json"));
  Json::Value json;
  file >> json;
  Data absoluteData = Data(json["data"]);
  Json::Value data = absoluteData.toJson(DataForm::ABSOLUTE);

  std::ofstream file_id;
  file_id.open(JsonTest::getJsonPath("absolute_example.json"));
  Json::StyledWriter styledWriter;
  file_id << styledWriter.write(data);
  file_id.close();

  EXPECT_EQ(json["data"]["header"]["version"]["major"].asUInt(), data["data"]["header"]["version"]["major"].asUInt64());
  EXPECT_EQ(json["data"]["header"]["time_zone_offset_min"].asUInt(), data["data"]["header"]["time_zone_offset_min"].asUInt());
  EXPECT_EQ(json["data"]["header"]["version"]["major"].asUInt(), data["data"]["header"]["version"]["major"].asUInt64());
  EXPECT_EQ(json["data"]["header"]["version"]["minor"].asUInt(), data["data"]["header"]["version"]["minor"].asUInt());
  EXPECT_EQ(json["data"]["header"]["version"]["patch"].asUInt(), data["data"]["header"]["version"]["patch"].asUInt());
  EXPECT_EQ(json["data"]["header"]["data_form"].asString(), data["data"]["header"]["data_form"].asString());
  EXPECT_EQ(json["data"]["raw"]["sensors"].size(), data["data"]["raw"]["sensors"].size());
  for (Json::Value::ArrayIndex i = 0; i < json["data"]["raw"]["sensors"].size(); i++) {
    for (Json::Value::ArrayIndex j = 0; j < json["data"]["raw"]["sensors"][i]["channels"].size(); j++) {
      EXPECT_EQ(json["data"]["raw"]["sensors"][i]["channels"][j]["ppg_metadata"]["color"].asString(),
                data["data"]["raw"]["sensors"][i]["channels"][j]["ppg_metadata"]["color"].asString());
      EXPECT_EQ(json["data"]["raw"]["sensors"][i]["channels"][j]["ppg_metadata"]["wavelength_nm"].asInt(),
                data["data"]["raw"]["sensors"][i]["channels"][j]["ppg_metadata"]["wavelength_nm"].asInt());
      EXPECT_EQ(json["data"]["raw"]["sensors"][i]["channels"][j]["acc_metadata"]["norm"].asString(),
                data["data"]["raw"]["sensors"][i]["channels"][j]["acc_metadata"]["norm"].asString());
      EXPECT_EQ(json["data"]["raw"]["sensors"][i]["channels"][j]["acc_metadata"]["coordinate"].asString(),
                data["data"]["raw"]["sensors"][i]["channels"][j]["acc_metadata"]["coordinate"].asString());
      for (Json::Value::ArrayIndex k = 0; k < json["data"]["raw"]["sensors"][i]["channels"][j]["absolute_block"]["absolute_values"].size(); k++) {
        EXPECT_EQ(json["data"]["raw"]["sensors"][i]["channels"][j]["absolute_block"]["absolute_values"][k].asInt(),
                  data["data"]["raw"]["sensors"][i]["channels"][j]["absolute_block"]["absolute_values"][k].asInt());
      }
      for (Json::Value::ArrayIndex l = 0; l < json["data"]["raw"]["sensors"][i]["channels"][j]["differential_blocks"].size(); l++) {
        for (Json::Value::ArrayIndex m = 0;
             m < json["data"]["raw"]["sensors"][i]["channels"][j]["differential_blocks"][l]["differential_values"].size(); l++) {
          EXPECT_EQ(json["data"]["raw"]["sensors"][i]["channels"][j]["differential_blocks"][l]["differential_values"][m].asInt(),
                    data["data"]["raw"]["sensors"][i]["channels"][j]["differential_blocks"][l]["differential_values"][m].asInt());
        }
      }
    }
    for (Json::Value::ArrayIndex n = 0; n < json["data"]["raw"]["sensors"][i]["absolute_timestamps_container"]["unix_timestamps_ms"].size(); n++) {
      EXPECT_EQ(json["data"]["raw"]["sensors"][i]["absolute_timestamps_container"]["unix_timestamps_ms"][n].asUInt64(),
                data["data"]["raw"]["sensors"][i]["absolute_timestamps_container"]["unix_timestamps_ms"][n].asUInt64());
    }

    EXPECT_EQ(json["data"]["raw"]["sensors"][i]["differential_timestamps_container"]["first_timestamp_ms"].asUInt64(),
              data["data"]["raw"]["sensors"][i]["differential_timestamps_container"]["first_timestamp_ms"].asUInt64());
    for (Json::Value::ArrayIndex o = 0; o < json["data"]["raw"]["sensors"][i]["differential_timestamps_container"]["block_intervals_ms"].size();
         o++) {
      EXPECT_EQ(json["data"]["raw"]["sensors"][i]["differential_timestamps_container"]["block_intervals_ms"][o].asUInt(),
                data["data"]["raw"]["sensors"][i]["differential_timestamps_container"]["block_intervals_ms"][o].asUInt());
    }
    for (Json::Value::ArrayIndex p = 0; p < json["data"]["raw"]["sensors"][i]["differential_timestamps_container"]["timestamps_intervals_ms"].size();
         p++) {
      EXPECT_EQ(json["data"]["raw"]["sensors"][i]["differential_timestamps_container"]["timestamps_intervals_ms"][p].asUInt(),
                data["data"]["raw"]["sensors"][i]["differential_timestamps_container"]["timestamps_intervals_ms"][p].asUInt());
    }
    EXPECT_EQ(json["data"]["raw"]["sensors"][i]["sensor_type"].asString(), data["data"]["raw"]["sensors"][i]["sensor_type"].asString());
  }
}

TEST_F(JsonTest, TestToJsonDifferentialForm) {
  std::ifstream file(JsonTest::getJsonPath("differential_pcore.json"));
  Json::Value json;
  file >> json;
  Data differentialJsonData = Data(json["data"]);
  Json::Value data = differentialJsonData.toJson(DataForm::DIFFERENTIAL);

  std::ofstream file_id;
  file_id.open(JsonTest::getJsonPath("differential_example.json"));
  Json::StyledWriter styledWriter;
  file_id << styledWriter.write(data);
  file_id.close();
  EXPECT_EQ(json["data"]["header"]["version"]["major"].asUInt(), data["data"]["header"]["version"]["major"].asUInt64());
  EXPECT_EQ(json["data"]["header"]["time_zone_offset_min"].asUInt(), data["data"]["header"]["time_zone_offset_min"].asUInt());
  EXPECT_EQ(json["data"]["header"]["version"]["major"].asUInt(), data["data"]["header"]["version"]["major"].asUInt64());
  EXPECT_EQ(json["data"]["header"]["version"]["minor"].asUInt(), data["data"]["header"]["version"]["minor"].asUInt());
  EXPECT_EQ(json["data"]["header"]["version"]["patch"].asUInt(), data["data"]["header"]["version"]["patch"].asUInt());
  EXPECT_EQ(json["data"]["header"]["data_form"].asString(), data["data"]["header"]["data_form"].asString());
  EXPECT_EQ(json["data"]["raw"]["sensors"].size(), data["data"]["raw"]["sensors"].size());
  for (Json::Value::ArrayIndex i = 0; i < json["data"]["raw"]["sensors"].size(); i++) {
    for (Json::Value::ArrayIndex j = 0; j < json["data"]["raw"]["sensors"][i]["channels"].size(); j++) {
        EXPECT_EQ(json["data"]["raw"]["sensors"][i]["channels"][j]["ppg_metadata"]["color"].asString(),
                  data["data"]["raw"]["sensors"][i]["channels"][j]["ppg_metadata"]["color"].asString());
        EXPECT_EQ(json["data"]["raw"]["sensors"][i]["channels"][j]["ppg_metadata"]["wavelength_nm"].asInt(),
                  data["data"]["raw"]["sensors"][i]["channels"][j]["ppg_metadata"]["wavelength_nm"].asInt());
        EXPECT_EQ(json["data"]["raw"]["sensors"][i]["channels"][j]["acc_metadata"]["norm"].asString(),
                  data["data"]["raw"]["sensors"][i]["channels"][j]["acc_metadata"]["norm"].asString());
        EXPECT_EQ(json["data"]["raw"]["sensors"][i]["channels"][j]["acc_metadata"]["coordinate"].asString(),
                  data["data"]["raw"]["sensors"][i]["channels"][j]["acc_metadata"]["coordinate"].asString());
        for (Json::Value::ArrayIndex k = 0; k < json["data"]["raw"]["sensors"][i]["channels"][j]["absolute_block"]["absolute_values"].size(); k++) {
          EXPECT_EQ(json["data"]["raw"]["sensors"][i]["channels"][j]["absolute_block"]["absolute_values"][k].asInt(),
                    data["data"]["raw"]["sensors"][i]["channels"][j]["absolute_block"]["absolute_values"][k].asInt());
        }
        for (Json::Value::ArrayIndex l = 0; l < json["data"]["raw"]["sensors"][i]["channels"][j]["differential_blocks"].size(); l++) {
          for (Json::Value::ArrayIndex m = 0; m < json["data"]["raw"]["sensors"][i]["channels"][j]["differential_blocks"][l]["diff_values"].size();
               l++) {
            EXPECT_EQ(json["data"]["raw"]["sensors"][i]["channels"][j]["differential_blocks"][l]["differential_values"][m].asInt(),
                      data["data"]["raw"]["sensors"][i]["channels"][j]["differential_blocks"][l]["differential_values"][m].asInt());
          }
        }
      EXPECT_EQ(json["data"]["raw"]["sensors"][i]["channels"][j]["acc_metadata"]["norm"].asString(),
                data["data"]["raw"]["sensors"][i]["channels"][j]["acc_metadata"]["norm"].asString());
      EXPECT_EQ(json["data"]["raw"]["sensors"][i]["channels"][j]["acc_metadata"]["coordinate"].asString(),
                data["data"]["raw"]["sensors"][i]["channels"][j]["acc_metadata"]["coordinate"].asString());
      for (Json::Value::ArrayIndex k = 0; k < json["data"]["raw"]["sensors"][i]["channels"][j]["absolute_block"]["absolute_values"].size(); k++) {
        EXPECT_EQ(json["data"]["raw"]["sensors"][i]["channels"][j]["absolute_block"]["absolute_values"][k].asInt(),
                  data["data"]["raw"]["sensors"][i]["channels"][j]["absolute_block"]["absolute_values"][k].asInt());
      }
      for (Json::Value::ArrayIndex l = 0; l < json["data"]["raw"]["sensors"][i]["channels"][j]["differential_blocks"].size(); l++) {
        for (Json::Value::ArrayIndex m = 0;
             m < json["data"]["raw"]["sensors"][i]["channels"][j]["differential_blocks"][l]["differential_values"].size(); l++) {
          EXPECT_EQ(json["data"]["raw"]["sensors"][i]["channels"][j]["differential_blocks"][l]["differential_values"][m].asInt(),
                    data["data"]["raw"]["sensors"][i]["channels"][j]["differential_blocks"][l]["differential_values"][m].asInt());
        }
      }
    }
    for (Json::Value::ArrayIndex n = 0; n < json["data"]["raw"]["sensors"][i]["absolute_timestamps_container"]["unix_timestamps_ms"].size(); n++) {
      EXPECT_EQ(json["data"]["raw"]["sensors"][i]["absolute_timestamps_container"]["unix_timestamps_ms"][n].asUInt64(),
                data["data"]["raw"]["sensors"][i]["absolute_timestamps_container"]["unix_timestamps_ms"][n].asUInt64());
    }

    EXPECT_EQ(json["data"]["raw"]["sensors"][i]["differential_timestamps_container"]["first_timestamp_ms"].asUInt64(),
              data["data"]["raw"]["sensors"][i]["differential_timestamps_container"]["first_timestamp_ms"].asUInt64());
    for (Json::Value::ArrayIndex o = 0; o < json["data"]["raw"]["sensors"][i]["differential_timestamps_container"]["block_intervals_ms"].size();
         o++) {
      EXPECT_EQ(json["data"]["raw"]["sensors"][i]["differential_timestamps_container"]["block_intervals_ms"][o].asUInt(),
                data["data"]["raw"]["sensors"][i]["differential_timestamps_container"]["block_intervals_ms"][o].asUInt());
    }
    for (Json::Value::ArrayIndex p = 0; p < json["data"]["raw"]["sensors"][i]["differential_timestamps_container"]["timestamps_intervals_ms"].size();
         p++) {
      EXPECT_EQ(json["data"]["raw"]["sensors"][i]["differential_timestamps_container"]["timestamps_intervals_ms"][p].asUInt(),
                data["data"]["raw"]["sensors"][i]["differential_timestamps_container"]["timestamps_intervals_ms"][p].asUInt());
    }
    EXPECT_EQ(json["data"]["raw"]["sensors"][i]["sensor_type"].asString(), data["data"]["raw"]["sensors"][i]["sensor_type"].asString());
  }
}
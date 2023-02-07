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
#include <gtest/gtest.h>
#include "Raw.h"

class RawTest : public ::testing::Test {
 protected:
  Raw normalRaw1;
  Raw normalRaw2;
  Raw comparableRaw1;
  Raw comparableRaw2;

  uint32_t notSetWavelength_nm = 0;
  AccMetaData setcoordinateAccMetaDataCoordinate = AccMetaData(ProtobufCoordinate::COORDINATE_X, ProtobufNorm::NORM_NONE);
  PpgMetaData notSetPpgMetaData1 = PpgMetaData(ProtobufColor::COLOR_NONE, notSetWavelength_nm);
  std::vector<int32_t> values1 = {};
  AbsoluteBlock normalAbsoluteBlock1 = AbsoluteBlock(values1);
  std::vector<int32_t> diffValues1 = {12, 15, 20};
  DifferentialBlock diffBlock1 = DifferentialBlock(diffValues1);
  std::vector<DifferentialBlock> normalDifferentialBlocks = {diffBlock1};
  DataForm dataform1 = DataForm::DIFFERENTIAL;
  Channel channelAccMetaDataSetCoordinate = Channel(this->dataform1,
                                                    this->normalDifferentialBlocks,
                                                    this->normalAbsoluteBlock1,
                                                    this->setcoordinateAccMetaDataCoordinate,
                                                    this->notSetPpgMetaData1);
  std::vector<Channel> normalVectorChannel = {channelAccMetaDataSetCoordinate};  // initialize base Channel

  AccMetaData setcoordinateAccMetaDataNorm = AccMetaData(ProtobufCoordinate::COORDINATE_NONE, ProtobufNorm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
  PpgMetaData notSetPpgMetaData2 = PpgMetaData(ProtobufColor::COLOR_NONE, notSetWavelength_nm);
  std::vector<int32_t> values2 = {};
  AbsoluteBlock normalAbsoluteBlock2 = AbsoluteBlock(values2);
  std::vector<int32_t> diffValues2 = {12, 15, 20};
  DifferentialBlock diffBlock2 = DifferentialBlock(diffValues2);
  std::vector<DifferentialBlock> compareDifferentialBlocks = {diffBlock2};
  DataForm dataform2 = DataForm::DIFFERENTIAL;
  Channel channelAccMetaDataSetNorm = Channel(this->dataform2,
                                              this->compareDifferentialBlocks,
                                              this->normalAbsoluteBlock2,
                                              this->setcoordinateAccMetaDataNorm,
                                              this->notSetPpgMetaData2);
  std::vector<Channel> compareVectorChannel = {channelAccMetaDataSetNorm};  // initialize compare channel

  std::vector<uint64_t> normalUnixTimestamps_ms = {};
  std::vector<uint64_t> compareUnixTimestamps_ms = {};
  AbsoluteTimestampsContainer normalAbsoluteTimestamps = AbsoluteTimestampsContainer(normalUnixTimestamps_ms);
  AbsoluteTimestampsContainer compareAbsoluteTimestamps = AbsoluteTimestampsContainer(compareUnixTimestamps_ms);
  ProtobufSensortype normalType = ProtobufSensortype::SENSOR_TYPE_ACC;
  ProtobufSensortype compareType = ProtobufSensortype::SENSOR_TYPE_PPG;
  uint64_t normalFirst_timestamp_ms = 1690921;
  uint64_t compareFirst_timestamp_ms = 161;
  std::vector<uint32_t> normalBlock_intervals_ms = {12, 113, 23, 34};
  std::vector<uint32_t> compareBlock_intervals_ms = {12, 1, 2, 34};
  std::vector<uint32_t> normalTimestamps_intervals_ms = {134, 31, 124};
  std::vector<uint32_t> compareTimestamps_intervals_ms = {14, 31, 124};
  DifferentialTimestampsContainer normaldifferentialTimestamps =
      DifferentialTimestampsContainer(this->normalFirst_timestamp_ms,
                                      this->normalBlock_intervals_ms,
                                      this->normalTimestamps_intervals_ms);  // initialize TimestampContainer as base
  DifferentialTimestampsContainer comparedifferentialTimestamps =
      DifferentialTimestampsContainer(this->compareFirst_timestamp_ms,
                                      this->compareBlock_intervals_ms,
                                      this->compareTimestamps_intervals_ms);  // initialize ctimestampContainer as comparison
  Sensor normalSensor1 = Sensor(this->normalVectorChannel, this->normaldifferentialTimestamps, this->normalAbsoluteTimestamps, this->normalType);
  Sensor compareSensor1 = Sensor(this->compareVectorChannel, this->comparedifferentialTimestamps, this->compareAbsoluteTimestamps, this->compareType);
  std::vector<Sensor> compareSensor = {compareSensor1};
  std::vector<Sensor> normalSensor = {normalSensor1};
  virtual void SetUp() {
    this->normalRaw1 = (this->normalSensor);
    this->normalRaw2 = (this->normalSensor);
    this->comparableRaw1 = (this->compareSensor);
    this->comparableRaw2 = (this->compareSensor);
  }
};

TEST_F(RawTest, TestGetMethodeRaw) {
  for (auto& sensor : this->normalRaw1.getSensor()) {
    EXPECT_EQ(sensor.getAbsoluteTimestamps().getUnixTimestamps(), this->normalAbsoluteTimestamps.getUnixTimestamps());
    EXPECT_EQ(sensor.getSensorType(), this->normalType);
    EXPECT_EQ(sensor.getTimestampForm(), DataForm::DIFFERENTIAL);
    EXPECT_EQ(sensor.getDifferentialTimestamps().getBlockIntervals(), this->normalBlock_intervals_ms);
    EXPECT_EQ(sensor.getDifferentialTimestamps().getFirstTimestamp(), this->normalFirst_timestamp_ms);
    EXPECT_EQ(sensor.getDifferentialTimestamps().getTimestampsIntervals(), this->normalTimestamps_intervals_ms);
    for (auto& channels : sensor.getChannels()) {
      EXPECT_EQ(channels.getAbsoluteBlock().getValues(), this->normalAbsoluteBlock1.getValues());
      EXPECT_EQ(channels.getDataform(), this->dataform1);
      EXPECT_EQ(channels.getAccMetaData().getCoordinate(), ProtobufCoordinate::COORDINATE_X);
      EXPECT_EQ(channels.getAccMetaData().getNorm(), ProtobufNorm::NORM_NONE);
      EXPECT_EQ(channels.getPpgMetData().getColor(), ProtobufColor::COLOR_NONE);
      EXPECT_EQ(channels.getPpgMetData().getWavelength(), this->notSetWavelength_nm);
      for (auto& differentialBlocks : channels.getDifferentialBlocks()) {
        EXPECT_EQ(differentialBlocks.getDiffValues(), this->diffValues1);
      }
    }
  }
}

TEST_F(RawTest, CompareEqualNormalRaw) {
  EXPECT_TRUE(this->normalRaw1.isEqual(this->normalRaw2));
}

TEST_F(RawTest, CompareDifferentRaw) {
  EXPECT_FALSE(this->normalRaw1.isEqual(this->comparableRaw1));
}

TEST_F(RawTest, CompareEqualComparableRaw) {
  EXPECT_TRUE(this->comparableRaw1.isEqual(this->comparableRaw2));
}

TEST_F(RawTest, TestSerializeAndDeserializeNormalRaw) {
  ProtobufRaw protobufRaw;
  this->normalRaw1.serialize(&protobufRaw);
  Raw raw = Raw(protobufRaw);
  EXPECT_TRUE(this->normalRaw1.isEqual(raw));
}

TEST_F(RawTest, TestSerializeAndDeserializeComparableRaw) {
  ProtobufRaw protobufRaw;
  this->comparableRaw1.serialize(&protobufRaw);
  Raw raw = Raw(protobufRaw);
  EXPECT_TRUE(this->comparableRaw1.isEqual(raw));
}

TEST_F(RawTest, TestSerializeAndDeserializeEqualDifferentRaw) {
  ProtobufRaw protobufRaw1;
  this->normalRaw1.serialize(&protobufRaw1);
  Raw raw1 = Raw(protobufRaw1);
  ProtobufRaw protobufRaw2;
  this->normalRaw1.serialize(&protobufRaw2);
  Raw raw2 = Raw(protobufRaw2);
  EXPECT_TRUE(raw1.isEqual(raw2));
}

TEST_F(RawTest, TestSerializeAndDeserializeTwoDifferentRaw) {
  ProtobufRaw protobufRaw1;
  this->normalRaw1.serialize(&protobufRaw1);
  Raw raw1 = Raw(protobufRaw1);
  ProtobufRaw protobufRaw2;
  this->comparableRaw1.serialize(&protobufRaw2);
  Raw raw2 = Raw(protobufRaw2);
  EXPECT_FALSE(raw1.isEqual(raw2));
}

TEST_F(RawTest, CheckRawPtr) {
  ProtobufRaw protobufRaw1;
  EXPECT_NO_THROW(this->normalRaw1.serialize(&protobufRaw1));
}

TEST_F(RawTest, CheckRawNullPtr) {
  ProtobufRaw* protobufRaw1 = nullptr;
  EXPECT_THROW(this->normalRaw1.serialize(protobufRaw1), std::invalid_argument);
}
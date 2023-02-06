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
#include "Sensor.h"

class SensorTest : public ::testing::Test {
 protected:
  uint32_t notSetWavelength_nm = 0;
  AccMetaData setCoordinateAccMetaDataCoordinate = AccMetaData(ProtobufCoordinate::COORDINATE_X, ProtobufNorm::NORM_NONE);
  PpgMetaData notSetPpgMetaData1 = PpgMetaData(ProtobufColor::COLOR_NONE, notSetWavelength_nm);
  std::vector<int32_t> values1 = {};
  AbsoluteBlock normalAbsoluteBlock1 = AbsoluteBlock(values1);
  std::vector<int32_t> diffValues1 = {12, 15, 20};
  DifferentialBlock diffBlock1 = DifferentialBlock(diffValues1);
  std::vector<DifferentialBlock> normalDifferentialBlocks1 = {diffBlock1};
  DataForm dataForm1 = DataForm::DIFFERENTIAL;
  Channel channelAccMetaDataSetCoordinate = Channel(this->dataForm1,
                                                    this->normalDifferentialBlocks1,
                                                    this->normalAbsoluteBlock1,
                                                    this->setCoordinateAccMetaDataCoordinate,
                                                    this->notSetPpgMetaData1);
  std::vector<Channel> normalVectorChannel = {channelAccMetaDataSetCoordinate};  // initialize Standard Channel

  AccMetaData setcoordinateAccMetaDataNorm = AccMetaData(ProtobufCoordinate::COORDINATE_NONE, ProtobufNorm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
  PpgMetaData notSetPpgMetaData2 = PpgMetaData(ProtobufColor::COLOR_NONE, notSetWavelength_nm);
  std::vector<int32_t> values2 = {};
  AbsoluteBlock normalAbsoluteBlock2 = AbsoluteBlock(values2);
  std::vector<int32_t> diffValues2 = {15, 25, 20};
  DifferentialBlock diffBlock2 = DifferentialBlock(diffValues2);
  std::vector<DifferentialBlock> comparableDifferentialBlocks = {diffBlock2};
  DataForm dataform2 = DataForm::DIFFERENTIAL;
  Channel channelAccMetaDataSetNorm = Channel(this->dataform2,
                                              this->comparableDifferentialBlocks,
                                              this->normalAbsoluteBlock2,
                                              this->setcoordinateAccMetaDataNorm,
                                              this->notSetPpgMetaData2);
  std::vector<Channel> comparableVectorChannel = {channelAccMetaDataSetNorm};  // initialize comparable channel

  std::vector<uint64_t> normalUnix_ms = {};
  std::vector<uint64_t> comparableUnix_ms = {};
  AbsoluteTimestampsContainer normalAbsoluteTimestamps = AbsoluteTimestampsContainer(normalUnix_ms);
  AbsoluteTimestampsContainer comparableAbsoluteTimestamps = AbsoluteTimestampsContainer(comparableUnix_ms);
  ProtobufSensortype normalSensorType = ProtobufSensortype::SENSOR_TYPE_ACC;
  ProtobufSensortype comparableSensorType = ProtobufSensortype::SENSOR_TYPE_ACC;
  uint64_t normalFirstTimestamp_ms = 1690921;
  uint64_t comparableFirstTimestamp_ms = 161;
  std::vector<uint32_t> normalBlockIntervals_ms = {12, 113, 23, 34};
  std::vector<uint32_t> comparableBlockIntervals_ms = {12, 1, 2, 34};
  std::vector<uint32_t> normalTimestampsIntervals_ms = {134, 31, 124};
  std::vector<uint32_t> comparableTimestampsIntervals_ms = {14, 31, 124};
  DifferentialTimestampsContainer normalDifferentialTimestamps =
      DifferentialTimestampsContainer(this->normalFirstTimestamp_ms,
                                      this->normalBlockIntervals_ms,
                                      this->normalTimestampsIntervals_ms);  // initialize TimestampContainer as Standard
  DifferentialTimestampsContainer comparableDifferentialTimestamps =
      DifferentialTimestampsContainer(this->comparableFirstTimestamp_ms,
                                      this->comparableBlockIntervals_ms,
                                      this->comparableTimestampsIntervals_ms);  // initialize ctimestampContainer as comparison
  Sensor normalSensor1 = Sensor(normalVectorChannel, normalDifferentialTimestamps, normalAbsoluteTimestamps, normalSensorType);
  Sensor normalSensor2 = Sensor(normalVectorChannel, normalDifferentialTimestamps, normalAbsoluteTimestamps, normalSensorType);
  Sensor comparableSensor1 = Sensor(comparableVectorChannel, comparableDifferentialTimestamps, comparableAbsoluteTimestamps, comparableSensorType);
  Sensor comparableSensor2 = Sensor(comparableVectorChannel, comparableDifferentialTimestamps, comparableAbsoluteTimestamps, comparableSensorType);
};

TEST_F(SensorTest, TestConstruktor) {
  EXPECT_NO_THROW(Sensor normalSensor1 =
                      Sensor(this->normalVectorChannel, this->normalDifferentialTimestamps, this->normalAbsoluteTimestamps, this->normalSensorType));
}

TEST_F(SensorTest, TestGetMethodStandardSensor) {
  for (size_t i = 0; i < this->comparableSensor1.getChannels().size(); i++) {
    EXPECT_TRUE(this->normalSensor1.getChannels()[i].isEqual(this->normalVectorChannel[i]));
  }
  EXPECT_TRUE(this->normalSensor1.getDifferentialTimestamps().isEqual(this->normalDifferentialTimestamps));
  EXPECT_TRUE(this->normalSensor1.getAbsoluteTimestamps().isEqual(this->normalAbsoluteTimestamps));
  EXPECT_EQ(this->normalSensor1.getSensorType(), this->normalSensorType);
}

TEST_F(SensorTest, TestGetMethodComparableSensor) {
  for (size_t i = 0; i < this->comparableSensor1.getChannels().size(); i++) {
    EXPECT_TRUE(this->comparableSensor1.getChannels()[i].isEqual(this->comparableVectorChannel[i]));
  }
  EXPECT_TRUE(this->comparableSensor1.getDifferentialTimestamps().isEqual(this->comparableDifferentialTimestamps));
  EXPECT_TRUE(this->comparableSensor1.getAbsoluteTimestamps().isEqual(this->comparableAbsoluteTimestamps));
  EXPECT_EQ(this->comparableSensor1.getSensorType(), this->comparableSensorType);
}

TEST_F(SensorTest, ComparableEqualNormalSensor) {
  EXPECT_TRUE(this->normalSensor1.isEqual(this->normalSensor2));
}

TEST_F(SensorTest, ComparableEqualComparableSensor) {
  EXPECT_TRUE(this->comparableSensor1.isEqual(this->comparableSensor2));
}

TEST_F(SensorTest, ComparableDifferentSensor) {
  EXPECT_FALSE(this->comparableSensor1.isEqual(this->normalSensor1));
}

TEST_F(SensorTest, ComparableDifferentComparableSensor) {
  EXPECT_FALSE(this->comparableSensor2.isEqual(this->normalSensor1));
}

TEST_F(SensorTest, TestCalculateBlockIntervalsSumFor) {
  EXPECT_EQ(this->normalSensor1.calculateBlockIntervalsSumFor(2), 125);
}

TEST_F(SensorTest, TestSerializeAndDeserializeMethodStandardSensor) {
  ProtobufSensor protobufSensor;
  this->normalSensor1.serialize(&protobufSensor);
  Sensor sensor2 = Sensor(protobufSensor);
  EXPECT_TRUE(this->normalSensor1.isEqual(sensor2));
}

TEST_F(SensorTest, TestSerializeAndDeserializeMethodComparableSensor) {
  ProtobufSensor protobufSensor;
  this->comparableSensor1.serialize(&protobufSensor);
  Sensor sensor2 = Sensor(protobufSensor);
  EXPECT_TRUE(this->comparableSensor1.isEqual(sensor2));
}

TEST_F(SensorTest, TestMethodFirstTimestamp) {
  EXPECT_EQ(this->normalSensor1.firstTimestamp(), this->normalFirstTimestamp_ms);
}

TEST_F(SensorTest, TestMethodLastTimestamp) {
  EXPECT_EQ(this->normalSensor1.lastTimestamp(), 1691475);
}

TEST_F(SensorTest, TestMethodDuration) {
  EXPECT_EQ(this->normalSensor1.duration(), 554);
}

TEST_F(SensorTest, CheckSensorPtr) {
  ProtobufSensor protobufSensor;
  EXPECT_NO_THROW(this->comparableSensor1.serialize(&protobufSensor));
}

TEST_F(SensorTest, CheckSensorNullPtr) {
  ProtobufSensor* protobufSensor = nullptr;
  EXPECT_THROW(this->comparableSensor1.serialize(protobufSensor), std::invalid_argument);
}

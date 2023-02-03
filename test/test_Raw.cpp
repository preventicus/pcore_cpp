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

  std::vector<uint64_t> normalUnix_ms = {};
  std::vector<uint64_t> compareUnix_ms = {};
  AbsoluteTimestamps normalAbsoluteTimestamps = AbsoluteTimestamps(normalUnix_ms);
  AbsoluteTimestamps compareAbsoluteTimestamps = AbsoluteTimestamps(compareUnix_ms);
  ProtobufSensortype normalType = ProtobufSensortype::SENSOR_TYPE_ACC;
  ProtobufSensortype compareType = ProtobufSensortype::SENSOR_TYPE_PPG;
  uint64_t normalFirst_timestamp_ms = 1690921;
  uint64_t compareFirst_timestamp_ms = 161;
  std::vector<uint32_t> normalBlock_intervals_ms = {12, 113, 23, 34};
  std::vector<uint32_t> compareBlock_intervals_ms = {12, 1, 2, 34};
  std::vector<uint32_t> normalTimestamps_intervals_ms = {134, 31, 124};
  std::vector<uint32_t> compareTimestamps_intervals_ms = {14, 31, 124};
  DifferentialTimestamps normaldifferentialTimestamps =
      DifferentialTimestamps(this->normalFirst_timestamp_ms,
                             this->normalBlock_intervals_ms,
                             this->normalTimestamps_intervals_ms);  // initialize TimestampContainer as base
  DifferentialTimestamps comparedifferentialTimestamps =
      DifferentialTimestamps(this->compareFirst_timestamp_ms,
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
  for (size_t i = 0; i < this->normalRaw1.getSensor().size(); i++) {
    EXPECT_EQ(this->normalRaw1.getSensor()[i].getAbsoluteTimestamps().getUnix(), this->normalAbsoluteTimestamps.getUnix());
    EXPECT_EQ(this->normalRaw1.getSensor()[i].getSensorType(), this->normalType);
    EXPECT_EQ(this->normalRaw1.getSensor()[i].getTimestampForm(), DataForm::DIFFERENTIAL);
    EXPECT_EQ(this->normalRaw1.getSensor()[i].getDifferentialTimestamps().getBlockIntervals(), this->normalBlock_intervals_ms);
    EXPECT_EQ(this->normalRaw1.getSensor()[i].getDifferentialTimestamps().getFirstTimestamp(), this->normalFirst_timestamp_ms);
    EXPECT_EQ(this->normalRaw1.getSensor()[i].getDifferentialTimestamps().getTimestampsIntervals(), this->normalTimestamps_intervals_ms);
    for (size_t j = 0; j < this->normalRaw1.getSensor()[i].getChannels().size(); j++) {
      EXPECT_EQ(this->normalRaw1.getSensor()[i].getChannels()[j].getAbsoluteBlock().getValues(), this->normalAbsoluteBlock1.getValues());
      EXPECT_EQ(this->normalRaw1.getSensor()[i].getChannels()[j].getDataform(), this->dataform1);
      EXPECT_EQ(this->normalRaw1.getSensor()[i].getChannels()[j].getAccMetaData().getCoordinate(), ProtobufCoordinate::COORDINATE_X);
      EXPECT_EQ(this->normalRaw1.getSensor()[i].getChannels()[j].getAccMetaData().getNorm(), ProtobufNorm::NORM_NONE);
      EXPECT_EQ(this->normalRaw1.getSensor()[i].getChannels()[j].getPpgMetData().getColor(), ProtobufColor::COLOR_NONE);
      EXPECT_EQ(this->normalRaw1.getSensor()[i].getChannels()[j].getPpgMetData().getWavelength(), this->notSetWavelength_nm);
      for (size_t k = 0; k < this->normalRaw1.getSensor()[i].getChannels()[j].getDifferentialBlocks().size(); k++) {
        EXPECT_EQ(this->normalRaw1.getSensor()[i].getChannels()[j].getDifferentialBlocks()[k].getDiffValues(), this->diffValues1);
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
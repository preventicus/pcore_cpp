#include <gtest/gtest.h>
#include "Data.h"

class DataTest : public ::testing::Test {
 protected:
  Data normalData1;
  Data normalData2;
  Data comparableData1;
  Data comparableData2;

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
  std::vector<Channel> normalVectorChannel = {channelAccMetaDataSetCoordinate};  // initialize standard Channel

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
                             this->normalTimestamps_intervals_ms);  // initialize TimestampContainer as standard
  DifferentialTimestamps comparedifferentialTimestamps =
      DifferentialTimestamps(this->compareFirst_timestamp_ms,
                             this->compareBlock_intervals_ms,
                             this->compareTimestamps_intervals_ms);  // initialize ctimestampContainer as comparison
  Sensor normalSensor1 = Sensor(this->normalVectorChannel, this->normaldifferentialTimestamps, this->normalAbsoluteTimestamps, this->normalType);
  Sensor compareSensor1 = Sensor(this->compareVectorChannel, this->comparedifferentialTimestamps, this->compareAbsoluteTimestamps, this->compareType);
  std::vector<Sensor> compareSensor = {compareSensor1};
  std::vector<Sensor> normalSensor = {normalSensor1};
  Raw normalRaw1 = (this->normalSensor);  // initialize Raw
  Raw compareRaw1 = (this->compareSensor);

  uint32_t majorOne = 1;
  uint32_t minorTwo = 2;
  uint32_t patchZero = 0;
  Version version = Version(majorOne, minorTwo, patchZero);
  int32_t positiveTimeZoneOffset_min = 120;
  int32_t negativeTimeZoneOffset_min = -120;
  int32_t invalidTimeZoneOffset_min = 1000;
  Header normalHeaderWitchPositiveTimeZoneOffset_min1 = Header(this->version, this->positiveTimeZoneOffset_min);  // initialize Header
  Header normalHeaderWitchNegativeTimeZoneOffset_min1 = Header(this->version, this->negativeTimeZoneOffset_min);
  virtual void SetUp() {
    this->normalData1 = Data(this->normalRaw1, this->normalHeaderWitchPositiveTimeZoneOffset_min1);
    this->normalData2 = Data(this->normalRaw1, this->normalHeaderWitchPositiveTimeZoneOffset_min1);
    this->comparableData1 = Data(this->compareRaw1, this->normalHeaderWitchNegativeTimeZoneOffset_min1);
    this->comparableData2 = Data(this->compareRaw1, this->normalHeaderWitchNegativeTimeZoneOffset_min1);
  }
};

TEST_F(DataTest, TestExceptionIsNotThrownForKonstruktor) {
  EXPECT_NO_THROW(Data normalData1 = Data(this->normalRaw1, this->normalHeaderWitchPositiveTimeZoneOffset_min1));
}

TEST_F(DataTest, TestGetMethodData) {
  for (int i = 0; i < this->normalData1.getRaw().getSensor().size(); i++) {
    EXPECT_EQ(this->normalData1.getRaw().getSensor()[i].calculateBlockIntervalsSumFor(2), 125);
    EXPECT_EQ(this->normalData1.getRaw().getSensor()[i].firstTimestamp(), 1690921);
    EXPECT_EQ(this->normalData1.getRaw().getSensor()[i].duration(), 554);
    EXPECT_EQ(this->normalData1.getRaw().getSensor()[i].lastTimestamp(), 1691475);
    EXPECT_EQ(this->normalData1.getRaw().getSensor()[i].getSensorType(), ProtobufSensortype::SENSOR_TYPE_ACC);
    EXPECT_EQ(this->normalData1.getRaw().getSensor()[i].getTimestampForm(), DataForm::DIFFERENTIAL);
    EXPECT_EQ(this->normalData1.getRaw().getSensor()[i].getDifferentialTimestamps().getBlockIntervals(), this->normalBlock_intervals_ms);
    EXPECT_EQ(this->normalData1.getRaw().getSensor()[i].getDifferentialTimestamps().getTimestampsIntervals(), this->normalTimestamps_intervals_ms);
    EXPECT_EQ(this->normalData1.getRaw().getSensor()[i].getAbsoluteTimestamps().getUnix(), this->normalUnix_ms);
  }
  EXPECT_EQ(this->normalData1.getHeader().getTimeZoneOffset(), this->positiveTimeZoneOffset_min);
  EXPECT_EQ(this->normalData1.getHeader().getVersion().getMajor(), this->version.getMajor());
  EXPECT_EQ(this->normalData1.getHeader().getVersion().getMinor(), this->version.getMinor());
  EXPECT_EQ(this->normalData1.getHeader().getVersion().getPatch(), this->version.getPatch());
}

TEST_F(DataTest, CompareEqualNormalData) {
  Header invalidHeader;
  EXPECT_TRUE(this->normalData1.isEqual(this->normalData2));
}

TEST_F(DataTest, CompareDifferentData) {
  EXPECT_FALSE(this->comparableData1.isEqual(this->normalData1));
}

TEST_F(DataTest, CompareEqualComparableData) {
  EXPECT_TRUE(this->comparableData1.isEqual(this->comparableData2));
}

TEST_F(DataTest, TestSerializeAndDeserializeData) {
  ProtobufData protobufData;
  this->normalData1.serialize(&protobufData);
  Data data = Data(protobufData);
  EXPECT_TRUE(this->normalData1.isEqual(data));
}

TEST_F(DataTest, TestSerializeAndDeserializeComparableData) {
  ProtobufData protobufData;
  this->comparableData1.serialize(&protobufData);
  Data data = Data(protobufData);
  EXPECT_TRUE(this->comparableData1.isEqual(data));
}

TEST_F(DataTest, TestSerializeAndDeserializeTwoComparableData) {
  ProtobufData protobufData1;
  this->comparableData1.serialize(&protobufData1);
  Data standardData = Data(protobufData1);
  ProtobufData protobufData2;
  this->comparableData2.serialize(&protobufData2);
  Data comparableData = Data(protobufData2);
  EXPECT_TRUE(standardData.isEqual(comparableData));
}

TEST_F(DataTest, TestSerializeAndDeserializeTwoNormalData) {
  ProtobufData protobufData1;
  this->normalData1.serialize(&protobufData1);
  Data standardData = Data(protobufData1);
  ProtobufData protobufData2;
  this->normalData2.serialize(&protobufData2);
  Data comparableData = Data(protobufData2);
  EXPECT_TRUE(standardData.isEqual(comparableData));
}

TEST_F(DataTest, CheckDataPtr) {
  ProtobufData protobufData;
  EXPECT_NO_THROW(this->comparableData1.serialize(&protobufData));
}

TEST_F(DataTest, CheckDataNullPtr) {
  ProtobufData* protobufData = nullptr;
  EXPECT_THROW(this->comparableData1.serialize(protobufData), std::invalid_argument);
}
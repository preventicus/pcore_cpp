#include <gtest/gtest.h>
#include "Data.h"

class CalculateAbsoluteAndDifferentialDataFormTest : public ::testing::Test {
 protected:
  int32_t notSetWavelength_nm = 0;
  AccMetaData setCoordinateAccMetaDataCoordinate = AccMetaData(ProtobufCoordinate::COORDINATE_X, ProtobufNorm::NORM_NONE);
  PpgMetaData notSetPpgMetaData1 = PpgMetaData();
  DataForm dataForm1 = DataForm::DIFFERENTIAL;
  DataForm dataForm2 = DataForm::ABSOLUTE;
  std::vector<int32_t> values = {38763, 38771, 38780, 38793, 38784, 38780, 38780, 38783, 38790, 38782, 46321, 46327, 46318,
                                 46316, 46313, 46313, 46313, 46336, 58772, 58774, 58775, 58776, 58773, 19982, 19982, 19978};
  AbsoluteBlock absoluteBlock = AbsoluteBlock(values);

  std::vector<int32_t> expectedDifferentialBlock1 = {38763, 8, 9, 13, -9, -4, 0, 3, 7, -8};
  std::vector<int32_t> expectedDifferentialBlock2 = {46321, 6, -9, -2, -3, 0, 0, 23};
  std::vector<int32_t> expectedDifferentialBlock3 = {58772, 2, 1, 1, -3};
  std::vector<int32_t> expectedDifferentialBlock4 = {19982, 0, -4};
  std::vector<DifferentialBlock> normalDifferentialBlocks = {expectedDifferentialBlock1, expectedDifferentialBlock2, expectedDifferentialBlock3,
                                                             expectedDifferentialBlock4};
  Channel channelWithAbsoluteValues = Channel(this->dataForm2,
                                              this->absoluteBlock,
                                              this->setCoordinateAccMetaDataCoordinate,
                                              this->notSetPpgMetaData1);  // absoluteChannel for AlgorithmTest
  Channel channelWithDifferentialValues = Channel(this->dataForm1,
                                                  this->normalDifferentialBlocks,
                                                  this->setCoordinateAccMetaDataCoordinate,
                                                  this->notSetPpgMetaData1);  // differentialChannel for AlgorithmTest

  std::vector<Channel> normalVectorChannelwithAbsoluteValues = {this->channelWithAbsoluteValues};
  std::vector<Channel> normalVectorChannelWithDifferentialValues = {this->channelWithDifferentialValues};

  std::vector<uint64_t> expectedUnixTimestamps = {
      1675732789987, 1675732790027, 1675732790067, 1675732790107, 1675732790147, 1675732790187, 1675732790227, 1675732790267, 1675732790307,
      1675732790347, 1675732790467, 1675732790507, 1675732790547, 1675732790587, 1675732790627, 1675732790667, 1675732790707, 1675732790747,
      1675732790867, 1675732790947, 1675732791027, 1675732791107, 1675732791187, 1675732791347, 1675732791387, 1675732791427};
  AbsoluteTimestampsContainer absoluteTimestampsContainerWithAbsoluteTimestamps =
      AbsoluteTimestampsContainer(this->expectedUnixTimestamps);  // absoluteTimestamps for AlgorithmTest

  std::vector<uint32_t> expectedBlockInterval = {0, 480, 400, 480};
  std::vector<uint32_t> expectedTimestampInterval = {40, 40, 80, 40};
  uint64_t expectedFirstTimestamps = 1675732789987;
  ProtobufSensortype sensorType = ProtobufSensortype::SENSOR_TYPE_ACC;
  DifferentialTimestampsContainer differentialTimestampsContainerWithAbsoluteUnixTimestamps =
      DifferentialTimestampsContainer(this->expectedFirstTimestamps,
                                      this->expectedBlockInterval,
                                      this->expectedTimestampInterval);  // differentialTimestamps for AlgorithmTest
  Sensor sensorWithAbsoluteValues =
      Sensor(this->normalVectorChannelwithAbsoluteValues, this->absoluteTimestampsContainerWithAbsoluteTimestamps, this->sensorType);
  Sensor sensorWithDifferentialValues =
      Sensor(this->normalVectorChannelWithDifferentialValues, this->differentialTimestampsContainerWithAbsoluteUnixTimestamps, this->sensorType);
  std::vector<Sensor> absoluteSensor = {this->sensorWithAbsoluteValues};
  std::vector<Sensor> differentialSensor = {this->sensorWithDifferentialValues};
  Raw absoluteRaw = Raw(this->absoluteSensor);
  Raw differentialRaw = Raw(this->differentialSensor);

  uint32_t majorOne = 1;
  uint32_t minorTwo = 2;
  uint32_t patchZero = 0;
  Version version = Version(this->majorOne, this->minorTwo, this->patchZero);
  int32_t timeZoneOffset_min = 120;
  Header header = Header(this->version, this->timeZoneOffset_min);
  Data absoluteData = Data(this->absoluteRaw, this->header);
  Data differentialData = Data(this->differentialRaw, this->header);
};

TEST_F(CalculateAbsoluteAndDifferentialDataFormTest, TestAlgorithmForAbsoluteValues) {
  this->absoluteData.switchInDifferentialForm();
  for (auto& sensor : this->absoluteData.getRaw().getSensors()) {
    for (auto& channel : sensor.getChannels()) {
      for (size_t i = 0; i < channel.getDifferentialBlocks().size(); i++) {
        EXPECT_TRUE(channel.getDifferentialBlocks()[i].isEqual(this->normalDifferentialBlocks[i]));
      }
    }
  }
}

TEST_F(CalculateAbsoluteAndDifferentialDataFormTest, TestAlgorithmForAbsoluteTimestamps) {
  this->absoluteData.switchInDifferentialForm();
  for (auto& sensor : this->absoluteData.getRaw().getSensors()) {
    EXPECT_TRUE(sensor.getDifferentialTimestamps().isEqual(this->differentialTimestampsContainerWithAbsoluteUnixTimestamps));
  }
}

TEST_F(CalculateAbsoluteAndDifferentialDataFormTest, TestAlgorithmForDifferentialValues) {
  this->differentialData.switchInAbsoluteFrom();
  for (auto& sensor : this->differentialData.getRaw().getSensors()) {
    for (auto& channel : sensor.getChannels()) {
      EXPECT_TRUE(channel.getAbsoluteBlock().isEqual(this->absoluteBlock));
    }
  }
}

TEST_F(CalculateAbsoluteAndDifferentialDataFormTest, TestAlgorithmForDifferentialTimestamps) {
  this->differentialData.switchInAbsoluteFrom();
  for (auto& sensor : this->differentialData.getRaw().getSensors()) {
    EXPECT_TRUE(sensor.getAbsoluteTimestamps().isEqual(this->absoluteTimestampsContainerWithAbsoluteTimestamps));
  }
}

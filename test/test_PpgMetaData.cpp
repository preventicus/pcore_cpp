#include <gtest/gtest.h>
#include "PpgMetaData.h"

class PpgMetaDataTest : public ::testing::Test {
 protected:
  PpgMetaData ppgMetDataWithColorGreen1;
  PpgMetaData ppgMetDataWithColorGreen2;
  PpgMetaData ppgMetDataWithColorBlue1;
  PpgMetaData ppgMetDataWithColorBlue2;
  PpgMetaData ppgMetDataWithcolorRed1;
  PpgMetaData ppgMetDataWithcolorRed2;
  PpgMetaData ppgMetDataWithWavelength1;
  PpgMetaData ppgMetDataWithWavelength2;
  PpgMetaData accMetaDataBothNotSet1;
  PpgMetaData accMetaDataBothNotSet2;
  uint32_t normalWavelength_nm = 255;
  uint32_t noWavelength_nm = 0;
  virtual void SetUp() {
    this->ppgMetDataWithColorGreen1 = PpgMetaData(ProtobufColor::COLOR_GREEN, this->noWavelength_nm);
    this->ppgMetDataWithColorGreen2 = PpgMetaData(ProtobufColor::COLOR_GREEN, this->noWavelength_nm);
    this->ppgMetDataWithColorBlue1 = PpgMetaData(ProtobufColor::COLOR_BLUE, this->noWavelength_nm);
    this->ppgMetDataWithColorBlue2 = PpgMetaData(ProtobufColor::COLOR_BLUE, this->noWavelength_nm);
    this->ppgMetDataWithcolorRed1 = PpgMetaData(ProtobufColor::COLOR_RED, this->noWavelength_nm);
    this->ppgMetDataWithcolorRed2 = PpgMetaData(ProtobufColor::COLOR_RED, this->noWavelength_nm);
    this->ppgMetDataWithWavelength1 = PpgMetaData(ProtobufColor::COLOR_NONE, this->normalWavelength_nm);
    this->ppgMetDataWithWavelength2 = PpgMetaData(ProtobufColor::COLOR_NONE, this->normalWavelength_nm);
    this->accMetaDataBothNotSet1 = PpgMetaData(ProtobufColor::COLOR_NONE, this->noWavelength_nm);
    this->accMetaDataBothNotSet2 = PpgMetaData(ProtobufColor::COLOR_NONE, this->noWavelength_nm);
  }
};

TEST_F(PpgMetaDataTest, TestSetAndGetColor) {
  EXPECT_EQ(this->ppgMetDataWithColorGreen1.getColor(), ProtobufColor::COLOR_GREEN);
  EXPECT_EQ(this->ppgMetDataWithColorGreen1.getWavelength(), this->noWavelength_nm);
}

TEST_F(PpgMetaDataTest, TestSetAndGetWavelength) {
  EXPECT_EQ(ppgMetDataWithWavelength1.getColor(), ProtobufColor::COLOR_NONE);
  EXPECT_EQ(ppgMetDataWithWavelength1.getWavelength(), this->normalWavelength_nm);
}

TEST_F(PpgMetaDataTest, TestThrowWavelengthAndColor) {
  EXPECT_THROW(PpgMetaData ppg = PpgMetaData(ProtobufColor::COLOR_GREEN, this->normalWavelength_nm), std::invalid_argument);
}

TEST_F(PpgMetaDataTest, TestNotThrowWavelengthAndColor) {
  EXPECT_NO_THROW(PpgMetaData ppg = PpgMetaData(ProtobufColor::COLOR_GREEN, this->noWavelength_nm));
}

TEST_F(PpgMetaDataTest, TestIsNotSet) {
  EXPECT_EQ(this->accMetaDataBothNotSet1.isSet(), false);
}

TEST_F(PpgMetaDataTest, TestIsSet) {
  EXPECT_EQ(this->ppgMetDataWithColorBlue1.isSet(), true);
}

TEST_F(PpgMetaDataTest, CompareEqualColorGreenAndEqualWavelength) {
  EXPECT_TRUE(this->ppgMetDataWithWavelength1.isEqual(this->ppgMetDataWithWavelength2));
}

TEST_F(PpgMetaDataTest, CompareEqualColorGreenAndDifferentWavelength) {
  EXPECT_FALSE(this->ppgMetDataWithWavelength1.isEqual(this->ppgMetDataWithColorGreen1));
}

TEST_F(PpgMetaDataTest, CompareDifferentColorAndEqualWavelength) {
  EXPECT_FALSE(this->ppgMetDataWithColorBlue1.isEqual(this->ppgMetDataWithColorGreen1));
}

TEST_F(PpgMetaDataTest, CompareSetWavelength) {
  EXPECT_TRUE(this->ppgMetDataWithcolorRed1.isEqual(this->ppgMetDataWithcolorRed2));
}

TEST_F(PpgMetaDataTest, CompareSerializeAndDeserializeMethodeColorGreen) {
  ProtobufPpgMetaData protobufPpgMetaData = this->ppgMetDataWithColorGreen1.serialize();
  PpgMetaData ppg2 = PpgMetaData(protobufPpgMetaData);
  EXPECT_TRUE(this->ppgMetDataWithColorGreen1.isEqual(ppg2));
}

TEST_F(PpgMetaDataTest, CompareSerializeAndDeserializeMethodeDifferentColor) {
  ProtobufPpgMetaData protobufPpgMetaData1 = this->ppgMetDataWithColorBlue1.serialize();
  PpgMetaData ppg3 = PpgMetaData(protobufPpgMetaData1);
  ProtobufPpgMetaData protobufPpgMetaData2 = this->ppgMetDataWithColorGreen1.serialize();
  PpgMetaData ppg4 = PpgMetaData(protobufPpgMetaData2);
  EXPECT_FALSE(ppg3.isEqual(ppg4));
}

TEST_F(PpgMetaDataTest, CompareSerializeAndDeserializeMethodeSameColor) {
  ProtobufPpgMetaData protobufPpgMetaData1 = this->ppgMetDataWithColorBlue1.serialize();
  PpgMetaData ppg3 = PpgMetaData(protobufPpgMetaData1);
  ProtobufPpgMetaData protobufPpgMetaData2 = this->ppgMetDataWithColorBlue2.serialize();
  PpgMetaData ppg4 = PpgMetaData(protobufPpgMetaData2);
  EXPECT_TRUE(ppg3.isEqual(ppg4));
}

TEST_F(PpgMetaDataTest, CompareSerializeAndDeserializeMethodeDifferentWavelength) {
  ProtobufPpgMetaData protobufPpgMetaData1 = this->ppgMetDataWithWavelength1.serialize();
  PpgMetaData ppg3 = PpgMetaData(protobufPpgMetaData1);
  ProtobufPpgMetaData protobufPpgMetaData2 = this->accMetaDataBothNotSet1.serialize();
  PpgMetaData ppg4 = PpgMetaData(protobufPpgMetaData2);
  EXPECT_FALSE(ppg3.isEqual(ppg4));
}

TEST_F(PpgMetaDataTest, CompareSerializeAndDeserializeMethodeSameWavelength) {
  ProtobufPpgMetaData protobufPpgMetaData1 = this->ppgMetDataWithWavelength1.serialize();
  PpgMetaData ppg3 = PpgMetaData(protobufPpgMetaData1);
  ProtobufPpgMetaData protobufPpgMetaData2 = this->ppgMetDataWithWavelength2.serialize();
  PpgMetaData ppg4 = PpgMetaData(protobufPpgMetaData2);
  EXPECT_TRUE(ppg3.isEqual(ppg4));
}
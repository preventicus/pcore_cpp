#include <gtest/gtest.h>
#include "PpgMetaData.h"

TEST(runUnitTest, TestSetAndGetColor) {
  PpgMetaData ppg = PpgMetaData(ProtobufColor::COLOR_GREEN, 0);
  EXPECT_EQ(ppg.getColor(), ProtobufColor::COLOR_GREEN);
  EXPECT_EQ(ppg.getWavelength(), 0);
}

TEST(runUnitTest, TestSetAndGetWavelength) {
  uint32_t wavelength_nm = 255;
  PpgMetaData ppg = PpgMetaData(ProtobufColor::COLOR_NONE, wavelength_nm);
  EXPECT_EQ(ppg.getColor(), ProtobufColor::COLOR_NONE);
  EXPECT_EQ(ppg.getWavelength(), wavelength_nm);
}

TEST(runUnitTest, TestSetAndGetWavelengthAndColor) {
  uint32_t wavelength_nm = 255;
  EXPECT_THROW(PpgMetaData ppg = PpgMetaData(ProtobufColor::COLOR_GREEN, wavelength_nm), std::invalid_argument);
}

TEST(runUnitTest, TestGet) {
  uint32_t wavelength_nm = 0;
  EXPECT_THROW(PpgMetaData ppg = PpgMetaData(ProtobufColor::COLOR_NONE, wavelength_nm), std::invalid_argument);
}

TEST(runUnitTest, CompareEqualColorGreenAndEqualWavelength) {
  uint32_t wavelength_nm1 = 255;
  uint32_t wavelength_nm2 = 255;
  PpgMetaData ppg1 = PpgMetaData(ProtobufColor::COLOR_NONE, wavelength_nm1);
  PpgMetaData ppg2 = PpgMetaData(ProtobufColor::COLOR_NONE, wavelength_nm2);
  EXPECT_TRUE(ppg1.isEqual(ppg2));
}

TEST(runUnitTest, CompareEqualColorGreenAndDifferentWavelength) {
  uint32_t wavelength_nm1 = 255;
  uint32_t wavelength_nm2 = 200;
  PpgMetaData ppg1 = PpgMetaData(ProtobufColor::COLOR_NONE, wavelength_nm1);
  PpgMetaData ppg2 = PpgMetaData(ProtobufColor::COLOR_NONE, wavelength_nm2);
  EXPECT_FALSE(ppg1.isEqual(ppg2));
}

TEST(runUnitTest, CompareDifferentColorAndEqualWavelength) {
  uint32_t wavelength_nm1 = 0;
  uint32_t wavelength_nm2 = 0;
  PpgMetaData ppg1 = PpgMetaData(ProtobufColor::COLOR_GREEN, wavelength_nm1);
  PpgMetaData ppg2 = PpgMetaData(ProtobufColor::COLOR_RED, wavelength_nm2);
  EXPECT_FALSE(ppg1.isEqual(ppg2));
}

TEST(runUnitTest, CompareSetWavelength) {
  uint32_t wavelength_nm1 = 0;
  uint32_t wavelength_nm2 = 0;
  PpgMetaData ppg1 = PpgMetaData(ProtobufColor::COLOR_GREEN, wavelength_nm1);
  PpgMetaData ppg2 = PpgMetaData(ProtobufColor::COLOR_GREEN, wavelength_nm2);
  EXPECT_TRUE(ppg1.isEqual(ppg2));
}

TEST(runUnitTest, CompareSerializeAndDeserializeMethodeColorGreen) {
  uint32_t wavelength_nm = 0;
  PpgMetaData ppg1 = PpgMetaData(ProtobufColor::COLOR_GREEN, wavelength_nm);
  ProtobufPpgMetaData protobufPpgMetaData = ppg1.serialize();
  PpgMetaData ppg2 = PpgMetaData(protobufPpgMetaData);
  EXPECT_TRUE(ppg1.isEqual(ppg2));
}

TEST(runUnitTest, CompareSerializeAndDeserializeMethodeDifferentColor) {
  uint32_t wavelength_nm = 0;
  PpgMetaData ppg1 = PpgMetaData(ProtobufColor::COLOR_GREEN, wavelength_nm);
  PpgMetaData ppg2 = PpgMetaData(ProtobufColor::COLOR_BLUE, wavelength_nm);
  ProtobufPpgMetaData protobufPpgMetaData1 = ppg1.serialize();
  PpgMetaData ppg3 = PpgMetaData(protobufPpgMetaData1);
  ProtobufPpgMetaData protobufPpgMetaData2 = ppg2.serialize();
  PpgMetaData ppg4 = PpgMetaData(protobufPpgMetaData2);
  EXPECT_FALSE(ppg3.isEqual(ppg4));
}

TEST(runUnitTest, CompareSerializeAndDeserializeMethodeSameColor) {
  uint32_t wavelength_nm = 0;
  PpgMetaData ppg1 = PpgMetaData(ProtobufColor::COLOR_GREEN, wavelength_nm);
  PpgMetaData ppg2 = PpgMetaData(ProtobufColor::COLOR_GREEN, wavelength_nm);
  ProtobufPpgMetaData protobufPpgMetaData1 = ppg1.serialize();
  PpgMetaData ppg3 = PpgMetaData(protobufPpgMetaData1);
  ProtobufPpgMetaData protobufPpgMetaData2 = ppg2.serialize();
  PpgMetaData ppg4 = PpgMetaData(protobufPpgMetaData2);
  EXPECT_TRUE(ppg3.isEqual(ppg4));
}

TEST(runUnitTest, CompareSerializeAndDeserializeMethodeDifferentWavelength) {
  uint32_t wavelength_nm1 = 255;
  uint32_t wavelength_nm2 = 500;
  PpgMetaData ppg1 = PpgMetaData(ProtobufColor::COLOR_NONE, wavelength_nm1);
  PpgMetaData ppg2 = PpgMetaData(ProtobufColor::COLOR_NONE, wavelength_nm2);
  ProtobufPpgMetaData protobufPpgMetaData1 = ppg1.serialize();
  PpgMetaData ppg3 = PpgMetaData(protobufPpgMetaData1);
  ProtobufPpgMetaData protobufPpgMetaData2 = ppg2.serialize();
  PpgMetaData ppg4 = PpgMetaData(protobufPpgMetaData2);
  EXPECT_FALSE(ppg3.isEqual(ppg4));
}
TEST(runUnitTest, CompareSerializeAndDeserializeMethodeSameWavelength) {
  uint32_t wavelength_nm1 = 255;
  uint32_t wavelength_nm2 = 255;
  PpgMetaData ppg1 = PpgMetaData(ProtobufColor::COLOR_NONE, wavelength_nm1);
  PpgMetaData ppg2 = PpgMetaData(ProtobufColor::COLOR_NONE, wavelength_nm2);
  ProtobufPpgMetaData protobufPpgMetaData1 = ppg1.serialize();
  PpgMetaData ppg3 = PpgMetaData(protobufPpgMetaData1);
  ProtobufPpgMetaData protobufPpgMetaData2 = ppg2.serialize();
  PpgMetaData ppg4 = PpgMetaData(protobufPpgMetaData2);
  EXPECT_TRUE(ppg3.isEqual(ppg4));
}
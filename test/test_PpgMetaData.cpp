#include <gtest/gtest.h>
#include "PpgMetaData.h"

TEST(runUnitTest, TestSetAndGetColor) {
  PpgMetaData Ppg1;
  Ppg1.setColor(ProtobufColor::COLOR_GREEN);
  EXPECT_EQ(Ppg1.getColor(), ProtobufColor::COLOR_GREEN);
  EXPECT_EQ(Ppg1.getWavelength(), 0);
}

TEST(runUnitTest, TestSetAndGetWavelength) {
  uint32_t wavelength_nm = 255;
  PpgMetaData Ppg1;
  Ppg1.setWavelength(wavelength_nm);
  EXPECT_EQ(Ppg1.getColor(), ProtobufColor::COLOR_NONE);
  EXPECT_EQ(Ppg1.getWavelength(), wavelength_nm);
}

TEST(runUnitTest, TestSetAndGetWavelengthAndColor) {
  PpgMetaData Ppg1;
  uint32_t wavelength_nm = 255;
  Ppg1.setWavelength(wavelength_nm);
  Ppg1.setColor(ProtobufColor::COLOR_GREEN);
  EXPECT_EQ(Ppg1.getColor(), ProtobufColor::COLOR_GREEN);
  EXPECT_EQ(Ppg1.getWavelength(), 0);
}

TEST(runUnitTest, TestGet) {
  PpgMetaData Ppg1;
  EXPECT_EQ(Ppg1.getWavelength(), 0);
  EXPECT_EQ(Ppg1.getColor(), ProtobufColor::COLOR_NONE);
}

TEST(runUnitTest, CompareEqualColorGreenAndEqualWavelength) {
  PpgMetaData Ppg1;
  uint32_t wavelength_nm1 = 255;
  uint32_t wavelength_nm2 = 255;
  Ppg1.setColor(ProtobufColor::COLOR_GREEN);
  Ppg1.setWavelength(wavelength_nm1);
  PpgMetaData Ppg2;
  Ppg2.setColor(ProtobufColor::COLOR_GREEN);
  Ppg2.setWavelength(wavelength_nm2);
  EXPECT_TRUE(Ppg1.isEqual(Ppg2));
}

TEST(runUnitTest, CompareEqualColorGreenAndDifferentWavelength) {
  PpgMetaData Ppg1;
  uint32_t wavelength_nm1 = 255;
  uint32_t wavelength_nm2 = 200;
  Ppg1.setColor(ProtobufColor::COLOR_GREEN);
  Ppg1.setWavelength(wavelength_nm1);
  PpgMetaData Ppg2;
  Ppg2.setColor(ProtobufColor::COLOR_GREEN);
  Ppg2.setWavelength(wavelength_nm2);
  EXPECT_FALSE(Ppg1.isEqual(Ppg2));
}

TEST(runUnitTest, CompareDifferentColorAndEqualWavelength) {
  PpgMetaData Ppg1;
  uint32_t wavelength_nm1 = 255;
  uint32_t wavelength_nm2 = 255;
  Ppg1.setColor(ProtobufColor::COLOR_GREEN);
  Ppg1.setWavelength(wavelength_nm1);
  PpgMetaData Ppg2;
  Ppg2.setColor(ProtobufColor::COLOR_RED);
  Ppg2.setWavelength(wavelength_nm2);
  EXPECT_TRUE(Ppg1.isEqual(Ppg2));
}

TEST(runUnitTest, CompareSetWavelength) {
  PpgMetaData Ppg1;
  uint32_t wavelength_nm1 = 255;
  uint32_t wavelength_nm2 = 255;
  Ppg1.setWavelength(wavelength_nm1);
  PpgMetaData Ppg2;
  Ppg2.setWavelength(wavelength_nm2);
  EXPECT_TRUE(Ppg1.isEqual(Ppg2));
}

TEST(runUnitTest, CompareSet0Wavelength) {
  PpgMetaData Ppg1;
  uint32_t wavelength_nm1 = 0;
  uint32_t wavelength_nm2 = 0;
  Ppg1.setWavelength(wavelength_nm1);
  PpgMetaData Ppg2;
  Ppg2.setWavelength(wavelength_nm2);
  EXPECT_TRUE(Ppg1.isEqual(Ppg2));
}

TEST(runUnitTest, CompareSerializeAndDeserializeMethodeColorGreen) {
  PpgMetaData Ppg1;
  Ppg1.setColor(ProtobufColor::COLOR_GREEN);
  ProtobufPpgMetaData protobufPpgData = Ppg1.serialize();
  PpgMetaData Ppg2;
  Ppg2.deserialize(protobufPpgData);
  EXPECT_TRUE(Ppg1.isEqual(Ppg2));
}

TEST(runUnitTest, CompareSerializeAndDeserializeMethodeColorBlue) {
  PpgMetaData Ppg1;
  Ppg1.setColor(ProtobufColor::COLOR_BLUE);
  ProtobufPpgMetaData protobufPpgData = Ppg1.serialize();
  PpgMetaData Ppg2;
  Ppg2.deserialize(protobufPpgData);
  EXPECT_TRUE(Ppg1.isEqual(Ppg2));
}

TEST(runUnitTest, CompareSerializeAndDeserializeMethodeColorRed) {
  PpgMetaData Ppg1;
  Ppg1.setColor(ProtobufColor::COLOR_RED);
  ProtobufPpgMetaData protobufPpgData = Ppg1.serialize();
  PpgMetaData Ppg2;
  Ppg2.deserialize(protobufPpgData);
  EXPECT_TRUE(Ppg1.isEqual(Ppg2));
}

TEST(runUnitTest, CompareSerializeAndDeserializeMethodeWavelength) {
  PpgMetaData Ppg1;
  uint32_t wavelength_nm = 255;
  Ppg1.setWavelength(wavelength_nm);
  ProtobufPpgMetaData protobufPpgData = Ppg1.serialize();
  PpgMetaData Ppg2;
  Ppg2.deserialize(protobufPpgData);
  EXPECT_TRUE(Ppg1.isEqual(Ppg2));
}

TEST(runUnitTest, CompareSerializeAndDeserializeMethodeNotSet) {
  PpgMetaData Ppg1;
  ProtobufPpgMetaData protobufPpgData = Ppg1.serialize();
  PpgMetaData Ppg2;
  Ppg2.deserialize(protobufPpgData);
  EXPECT_TRUE(Ppg1.isEqual(Ppg2));
}

TEST(runUnitTest, CompareSerializeAndDeserializeMethodeColorSetFirst) {
  PpgMetaData Ppg1;
  uint32_t wavelength_nm = 255;
  Ppg1.setColor(ProtobufColor::COLOR_GREEN);
  Ppg1.setWavelength(wavelength_nm);
  ProtobufPpgMetaData protobufPpgData = Ppg1.serialize();
  PpgMetaData Ppg2;
  Ppg2.deserialize(protobufPpgData);
  EXPECT_TRUE(Ppg1.isEqual(Ppg2));
  EXPECT_EQ(Ppg2.getColor(), ProtobufColor::COLOR_NONE);
  EXPECT_EQ(Ppg2.getWavelength(), wavelength_nm);
}

TEST(runUnitTest, CompareSerializeAndDeserializeMethodeWavelengthSetFirst) {
  PpgMetaData Ppg1;
  uint32_t wavelength_nm = 255;
  Ppg1.setWavelength(wavelength_nm);
  Ppg1.setColor(ProtobufColor::COLOR_GREEN);
  ProtobufPpgMetaData protobufPpgData = Ppg1.serialize();
  PpgMetaData Ppg2;
  Ppg2.deserialize(protobufPpgData);
  EXPECT_TRUE(Ppg1.isEqual(Ppg2));
  EXPECT_EQ(Ppg2.getColor(), ProtobufColor::COLOR_GREEN);
  EXPECT_EQ(Ppg2.getWavelength(), 0);
}

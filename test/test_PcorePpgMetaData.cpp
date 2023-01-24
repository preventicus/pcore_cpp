#include <gtest/gtest.h>
#include "DeserializedPpgMetaData.h"

TEST(runUnitTest, TestSetAndGetColor) {
  DeserializedPpgMetaData Ppg1;
  Ppg1.setColor(Color::COLOR_GREEN);
  EXPECT_EQ(Ppg1.getColor(), Color::COLOR_GREEN);
  EXPECT_EQ(Ppg1.getWavelength(), 0);
}

TEST(runUnitTest, TestSetAndGetWavelength) {
  uint32_t wavelength_nm = 255;
  DeserializedPpgMetaData Ppg1;
  Ppg1.setWavelength(wavelength_nm);
  EXPECT_EQ(Ppg1.getColor(), Color::COLOR_NONE);
  EXPECT_EQ(Ppg1.getWavelength(), wavelength_nm);
}

TEST(runUnitTest, TestSetAndGetWavelengthAndColor) {
  DeserializedPpgMetaData Ppg1;
  uint32_t wavelength_nm = 255;
  Ppg1.setWavelength(wavelength_nm);
  Ppg1.setColor(Color::COLOR_GREEN);
  EXPECT_EQ(Ppg1.getColor(), Color::COLOR_GREEN);
  EXPECT_EQ(Ppg1.getWavelength(), 0);
}

TEST(runUnitTest, TestGet) {
  DeserializedPpgMetaData Ppg1;
  EXPECT_EQ(Ppg1.getWavelength(), 0);
  EXPECT_EQ(Ppg1.getColor(), Color::COLOR_NONE);
}

TEST(runUnitTest, CompareEqualColorGreenAndEqualWavelength) {
  DeserializedPpgMetaData Ppg1;
  uint32_t wavelength_nm1 = 255;
  uint32_t wavelength_nm2 = 255;
  Ppg1.setColor(Color::COLOR_GREEN);
  Ppg1.setWavelength(wavelength_nm1);
  DeserializedPpgMetaData Ppg2;
  Ppg2.setColor(Color::COLOR_GREEN);
  Ppg2.setWavelength(wavelength_nm2);
  EXPECT_TRUE(Ppg1.isEqual(Ppg2));
}

TEST(runUnitTest, CompareEqualColorGreenAndDifferentWavelength) {
  DeserializedPpgMetaData Ppg1;
  uint32_t wavelength_nm1 = 255;
  uint32_t wavelength_nm2 = 200;
  Ppg1.setColor(Color::COLOR_GREEN);
  Ppg1.setWavelength(wavelength_nm1);
  DeserializedPpgMetaData Ppg2;
  Ppg2.setColor(Color::COLOR_GREEN);
  Ppg2.setWavelength(wavelength_nm2);
  EXPECT_FALSE(Ppg1.isEqual(Ppg2));
}

TEST(runUnitTest, CompareDifferentColorAndEqualWavelength) {
  DeserializedPpgMetaData Ppg1;
  uint32_t wavelength_nm1 = 255;
  uint32_t wavelength_nm2 = 255;
  Ppg1.setColor(Color::COLOR_GREEN);
  Ppg1.setWavelength(wavelength_nm1);
  DeserializedPpgMetaData Ppg2;
  Ppg2.setColor(Color::COLOR_RED);
  Ppg2.setWavelength(wavelength_nm2);
  EXPECT_TRUE(Ppg1.isEqual(Ppg2));
}

TEST(runUnitTest, CompareSetWavelength) {
  DeserializedPpgMetaData Ppg1;
  uint32_t wavelength_nm1 = 255;
  uint32_t wavelength_nm2 = 255;
  Ppg1.setWavelength(wavelength_nm1);
  DeserializedPpgMetaData Ppg2;
  Ppg2.setWavelength(wavelength_nm2);
  EXPECT_TRUE(Ppg1.isEqual(Ppg2));
}

TEST(runUnitTest, CompareSet0Wavelength) {
  DeserializedPpgMetaData Ppg1;
  uint32_t wavelength_nm1 = 0;
  uint32_t wavelength_nm2 = 0;
  Ppg1.setWavelength(wavelength_nm1);
  DeserializedPpgMetaData Ppg2;
  Ppg2.setWavelength(wavelength_nm2);
  EXPECT_TRUE(Ppg1.isEqual(Ppg2));
}

TEST(runUnitTest, CompareSerializeAndDeserializeMethodeColorGreen) {
  DeserializedPpgMetaData Ppg1;
  Ppg1.setColor(Color::COLOR_GREEN);
  SerializedPpgMetaData serializedPpgData = Ppg1.serialize();
  DeserializedPpgMetaData Ppg2;
  Ppg2.deserialize(serializedPpgData);
  EXPECT_TRUE(Ppg1.isEqual(Ppg2));
}

TEST(runUnitTest, CompareSerializeAndDeserializeMethodeColorBlue) {
  DeserializedPpgMetaData Ppg1;
  Ppg1.setColor(Color::COLOR_BLUE);
  SerializedPpgMetaData serializedPpgData = Ppg1.serialize();
  DeserializedPpgMetaData Ppg2;
  Ppg2.deserialize(serializedPpgData);
  EXPECT_TRUE(Ppg1.isEqual(Ppg2));
}

TEST(runUnitTest, CompareSerializeAndDeserializeMethodeColorRed) {
  DeserializedPpgMetaData Ppg1;
  Ppg1.setColor(Color::COLOR_RED);
  SerializedPpgMetaData serializedPpgData = Ppg1.serialize();
  DeserializedPpgMetaData Ppg2;
  Ppg2.deserialize(serializedPpgData);
  EXPECT_TRUE(Ppg1.isEqual(Ppg2));
}

TEST(runUnitTest, CompareSerializeAndDeserializeMethodeWavelength) {
  DeserializedPpgMetaData Ppg1;
  uint32_t wavelength_nm = 255;
  Ppg1.setWavelength(wavelength_nm);
  SerializedPpgMetaData serializedPpgData = Ppg1.serialize();
  DeserializedPpgMetaData Ppg2;
  Ppg2.deserialize(serializedPpgData);
  EXPECT_TRUE(Ppg1.isEqual(Ppg2));
}

TEST(runUnitTest, CompareSerializeAndDeserializeMethodeNotSet) {
  DeserializedPpgMetaData Ppg1;
  SerializedPpgMetaData serializedPpgData = Ppg1.serialize();
  DeserializedPpgMetaData Ppg2;
  Ppg2.deserialize(serializedPpgData);
  EXPECT_TRUE(Ppg1.isEqual(Ppg2));
}

TEST(runUnitTest, CompareSerializeAndDeserializeMethodeColorSetFirst) {
  DeserializedPpgMetaData Ppg1;
  uint32_t wavelength_nm = 255;
  Ppg1.setColor(Color::COLOR_GREEN);
  Ppg1.setWavelength(wavelength_nm);
  SerializedPpgMetaData serializedPpgData = Ppg1.serialize();
  DeserializedPpgMetaData Ppg2;
  Ppg2.deserialize(serializedPpgData);
  EXPECT_TRUE(Ppg1.isEqual(Ppg2));
  EXPECT_EQ(Ppg2.getColor(), Color::COLOR_NONE);
  EXPECT_EQ(Ppg2.getWavelength(), wavelength_nm);
}

TEST(runUnitTest, CompareSerializeAndDeserializeMethodeWavelengthSetFirst) {
  DeserializedPpgMetaData Ppg1;
  uint32_t wavelength_nm = 255;
  Ppg1.setWavelength(wavelength_nm);
  Ppg1.setColor(Color::COLOR_GREEN);
  SerializedPpgMetaData serializedPpgData = Ppg1.serialize();
  DeserializedPpgMetaData Ppg2;
  Ppg2.deserialize(serializedPpgData);
  EXPECT_TRUE(Ppg1.isEqual(Ppg2));
  EXPECT_EQ(Ppg2.getColor(), Color::COLOR_GREEN);
  EXPECT_EQ(Ppg2.getWavelength(), 0);
}

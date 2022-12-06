#include <gtest/gtest.h>
#include "DeserializedAccMetaData.h"

TEST(runUnitTest, SetCoordAndCheck) {
  DeserializedAccMetaData acc1;
  acc1.setCoordinate(Coordinate::COORDINATE_X);
  EXPECT_EQ(acc1.getCoordinate(), Coordinate::COORDINATE_X);
  EXPECT_EQ(acc1.getNorm(), Norm::NORM_NONE);
}
TEST(runUnitTest, SetNormAndCheck) {
  DeserializedAccMetaData acc1;
  acc1.setNorm(Norm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
  EXPECT_EQ(acc1.getCoordinate(), Coordinate::COORDINATE_NONE);
  EXPECT_EQ(acc1.getNorm(), Norm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
}
TEST(runUnitTest, setBoth) {
  DeserializedAccMetaData acc1;
  acc1.setNorm(Norm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
  acc1.setCoordinate(Coordinate::COORDINATE_X);
  EXPECT_EQ(acc1.getCoordinate(), Coordinate::COORDINATE_X);
  EXPECT_EQ(acc1.getNorm(), Norm::NORM_NONE);
}
TEST(runUnitTest, testGet) {
  DeserializedAccMetaData acc1;
  EXPECT_EQ(acc1.getCoordinate(), Coordinate::COORDINATE_NONE);
  EXPECT_EQ(acc1.getNorm(), Norm::NORM_NONE);
}
TEST(runUnitTest, CompareEqualCoordinateX) {
  DeserializedAccMetaData acc1;
  acc1.setCoordinate(Coordinate::COORDINATE_X);
  DeserializedAccMetaData acc2;
  acc2.setCoordinate(Coordinate::COORDINATE_X);
  EXPECT_TRUE(acc1.isEqual(&acc2));
}
TEST(runUnitTest, CompareEqualCoordinateY) {
  DeserializedAccMetaData acc1;
  acc1.setCoordinate(Coordinate::COORDINATE_Y);
  DeserializedAccMetaData acc2;
  acc2.setCoordinate(Coordinate::COORDINATE_Y);
  EXPECT_TRUE(acc1.isEqual(&acc2));
}
TEST(runUnitTest, CompareEqualCoordinateZ) {
  DeserializedAccMetaData acc1;
  acc1.setCoordinate(Coordinate::COORDINATE_Z);
  DeserializedAccMetaData acc2;
  acc2.setCoordinate(Coordinate::COORDINATE_Z);
  EXPECT_TRUE(acc1.isEqual(&acc2));
}
TEST(runUnitTest, CompareEqualNormNone) {
  DeserializedAccMetaData acc1;
  acc1.setNorm(Norm::NORM_NONE);
  DeserializedAccMetaData acc2;
  acc2.setNorm(Norm::NORM_NONE);
  EXPECT_TRUE(acc1.isEqual(&acc2));
}
TEST(runUnitTest, CompareEqualNormEUCLID) {
  DeserializedAccMetaData acc1;
  acc1.setNorm(Norm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
  DeserializedAccMetaData acc2;
  acc2.setNorm(Norm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
  EXPECT_TRUE(acc1.isEqual(&acc2));
}
TEST(runUnitTest, CompareCoordinateXAndEqualNormEUCLID) {
  DeserializedAccMetaData acc1;
  acc1.setNorm(Norm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
  acc1.setCoordinate(Coordinate::COORDINATE_X);
  DeserializedAccMetaData acc2;
  acc2.setNorm(Norm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
  EXPECT_FALSE(acc1.isEqual(&acc2));
}
TEST(runUnitTest, CompareCoordinateXAndEqualNormEUCLID2) {
  DeserializedAccMetaData acc1;
  acc1.setNorm(Norm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
  DeserializedAccMetaData acc2;
  acc2.setNorm(Norm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
  acc2.setCoordinate(Coordinate::COORDINATE_X);
  EXPECT_FALSE(acc1.isEqual(&acc2));
}
TEST(runUnitTest, CompareEqualCoordinateXAndEqualNormEUCLID) {
  DeserializedAccMetaData acc1;
  acc1.setNorm(Norm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
  acc1.setCoordinate(Coordinate::COORDINATE_X);
  DeserializedAccMetaData acc2;
  acc2.setNorm(Norm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
  acc2.setCoordinate(Coordinate::COORDINATE_X);
  EXPECT_TRUE(acc1.isEqual(&acc2));
}
TEST(runUnitTest, CompareDifferentCoordinateAndEqualNormEUCLID) {
  DeserializedAccMetaData acc1;
  acc1.setNorm(Norm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
  acc1.setCoordinate(Coordinate::COORDINATE_Y);
  DeserializedAccMetaData acc2;
  acc2.setNorm(Norm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
  acc2.setCoordinate(Coordinate::COORDINATE_X);
  EXPECT_FALSE(acc1.isEqual(&acc2));
}
TEST(runUnitTest, CompareDifferentCoordinateAndEqualNormEUCLID2) {
  DeserializedAccMetaData acc1;
  acc1.setNorm(Norm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
  acc1.setCoordinate(Coordinate::COORDINATE_Y);
  DeserializedAccMetaData acc2;
  acc2.setNorm(Norm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
  acc2.setCoordinate(Coordinate::COORDINATE_Z);
  EXPECT_FALSE(acc1.isEqual(&acc2));
}
TEST(runUnitTest, serializeMethodeCoord) {
  DeserializedAccMetaData acc1;
  acc1.setCoordinate(Coordinate::COORDINATE_X);
  SerializedAccMetaData serializedData = acc1.serialize();
  DeserializedAccMetaData acc2;
  acc2.deserialized(&serializedData);
  EXPECT_TRUE(acc1.isEqual(&acc2));
}
TEST(runUnitTest, serializeMethodeNorm) {
  DeserializedAccMetaData acc1;
  acc1.setNorm(Norm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
  SerializedAccMetaData serializedData = acc1.serialize();
  DeserializedAccMetaData acc2;
  acc2.deserialized(&serializedData);
  EXPECT_TRUE(acc1.isEqual(&acc2));
}
TEST(runUnitTest, serializeMethodeBoth) {
  DeserializedAccMetaData acc1;
  acc1.setCoordinate(Coordinate::COORDINATE_X);
  acc1.setNorm(Norm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
  SerializedAccMetaData serializedData = acc1.serialize();
  DeserializedAccMetaData acc2;
  acc2.deserialized(&serializedData);
  EXPECT_TRUE(acc1.isEqual(&acc2));
  EXPECT_EQ(acc2.getNorm(), Norm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
  EXPECT_EQ(acc2.getCoordinate(), Coordinate::COORDINATE_NONE);
}
TEST(runUnitTest, serializeMethodeBoth2) {
  DeserializedAccMetaData acc1;
  acc1.setCoordinate(Coordinate::COORDINATE_Y);
  acc1.setNorm(Norm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
  SerializedAccMetaData serializedData = acc1.serialize();
  DeserializedAccMetaData acc2;
  acc2.deserialized(&serializedData);
  EXPECT_TRUE(acc1.isEqual(&acc2));
  EXPECT_EQ(acc2.getNorm(), Norm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
  EXPECT_EQ(acc2.getCoordinate(), Coordinate::COORDINATE_NONE);
}
TEST(runUnitTest, serializeMethodeBoth3) {
  DeserializedAccMetaData acc1;
  acc1.setCoordinate(Coordinate::COORDINATE_Z);
  acc1.setNorm(Norm::NORM_NONE);
  SerializedAccMetaData serializedData = acc1.serialize();
  DeserializedAccMetaData acc2;
  acc2.deserialized(&serializedData);
  EXPECT_TRUE(acc1.isEqual(&acc2));
  EXPECT_EQ(acc2.getNorm(), Norm::NORM_NONE);
  EXPECT_EQ(acc2.getCoordinate(), Coordinate::COORDINATE_NONE);
}
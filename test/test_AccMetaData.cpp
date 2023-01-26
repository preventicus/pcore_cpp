#include <gtest/gtest.h>
#include "AccMetaData.h"

TEST(runUnitTest, SetCoordAndCheck) {
  AccMetaData acc1;
  acc1.setCoordinate(ProtobufCoordinate::COORDINATE_X);
  EXPECT_EQ(acc1.getCoordinate(), ProtobufCoordinate::COORDINATE_X);
  EXPECT_EQ(acc1.getNorm(), ProtobufNorm::NORM_NONE);
}
TEST(runUnitTest, SetNormAndCheck) {
  AccMetaData acc1;
  acc1.setNorm(ProtobufNorm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
  EXPECT_EQ(acc1.getCoordinate(), ProtobufCoordinate::COORDINATE_NONE);
  EXPECT_EQ(acc1.getNorm(), ProtobufNorm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
}
TEST(runUnitTest, setBoth) {
  AccMetaData acc1;
  acc1.setNorm(ProtobufNorm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
  acc1.setCoordinate(ProtobufCoordinate::COORDINATE_X);
  EXPECT_EQ(acc1.getCoordinate(), ProtobufCoordinate::COORDINATE_X);
  EXPECT_EQ(acc1.getNorm(), ProtobufNorm::NORM_NONE);
}
TEST(runUnitTest, testGet) {
  AccMetaData acc1;
  EXPECT_EQ(acc1.getCoordinate(), ProtobufCoordinate::COORDINATE_NONE);
  EXPECT_EQ(acc1.getNorm(), ProtobufNorm::NORM_NONE);
}
TEST(runUnitTest, CompareEqualCoordinateX) {
  AccMetaData acc1;
  acc1.setCoordinate(ProtobufCoordinate::COORDINATE_X);
  AccMetaData acc2;
  acc2.setCoordinate(ProtobufCoordinate::COORDINATE_X);
  EXPECT_TRUE(acc1.isEqual(acc2));
}
TEST(runUnitTest, CompareEqualCoordinateY) {
  AccMetaData acc1;
  acc1.setCoordinate(ProtobufCoordinate::COORDINATE_Y);
  AccMetaData acc2;
  acc2.setCoordinate(ProtobufCoordinate::COORDINATE_Y);
  EXPECT_TRUE(acc1.isEqual(acc2));
}
TEST(runUnitTest, CompareEqualCoordinateZ) {
  AccMetaData acc1;
  acc1.setCoordinate(ProtobufCoordinate::COORDINATE_Z);
  AccMetaData acc2;
  acc2.setCoordinate(ProtobufCoordinate::COORDINATE_Z);
  EXPECT_TRUE(acc1.isEqual(acc2));
}
TEST(runUnitTest, CompareEqualNormNone) {
  AccMetaData acc1;
  acc1.setNorm(ProtobufNorm::NORM_NONE);
  AccMetaData acc2;
  acc2.setNorm(ProtobufNorm::NORM_NONE);
  EXPECT_TRUE(acc1.isEqual(acc2));
}
TEST(runUnitTest, CompareEqualNormEUCLID) {
  AccMetaData acc1;
  acc1.setNorm(ProtobufNorm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
  AccMetaData acc2;
  acc2.setNorm(ProtobufNorm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
  EXPECT_TRUE(acc1.isEqual(acc2));
}
TEST(runUnitTest, CompareCoordinateXAndEqualNormEUCLID) {
  AccMetaData acc1;
  acc1.setNorm(ProtobufNorm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
  acc1.setCoordinate(ProtobufCoordinate::COORDINATE_X);
  AccMetaData acc2;
  acc2.setNorm(ProtobufNorm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
  EXPECT_FALSE(acc1.isEqual(acc2));
}
TEST(runUnitTest, CompareCoordinateXAndEqualNormEUCLID2) {
  AccMetaData acc1;
  acc1.setNorm(ProtobufNorm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
  AccMetaData acc2;
  acc2.setNorm(ProtobufNorm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
  acc2.setCoordinate(ProtobufCoordinate::COORDINATE_X);
  EXPECT_FALSE(acc1.isEqual(acc2));
}
TEST(runUnitTest, CompareEqualCoordinateXAndEqualNormEUCLID) {
  AccMetaData acc1;
  acc1.setNorm(ProtobufNorm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
  acc1.setCoordinate(ProtobufCoordinate::COORDINATE_X);
  AccMetaData acc2;
  acc2.setNorm(ProtobufNorm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
  acc2.setCoordinate(ProtobufCoordinate::COORDINATE_X);
  EXPECT_TRUE(acc1.isEqual(acc2));
}
TEST(runUnitTest, CompareDifferentCoordinateAndEqualNormEUCLID) {
  AccMetaData acc1;
  acc1.setNorm(ProtobufNorm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
  acc1.setCoordinate(ProtobufCoordinate::COORDINATE_Y);
  AccMetaData acc2;
  acc2.setNorm(ProtobufNorm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
  acc2.setCoordinate(ProtobufCoordinate::COORDINATE_X);
  EXPECT_FALSE(acc1.isEqual(acc2));
}
TEST(runUnitTest, CompareDifferentCoordinateAndEqualNormEUCLID2) {
  AccMetaData acc1;
  acc1.setNorm(ProtobufNorm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
  acc1.setCoordinate(ProtobufCoordinate::COORDINATE_Y);
  AccMetaData acc2;
  acc2.setNorm(ProtobufNorm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
  acc2.setCoordinate(ProtobufCoordinate::COORDINATE_Z);
  EXPECT_FALSE(acc1.isEqual(acc2));
}
TEST(runUnitTest, serializeMethodeCoord) {
  AccMetaData acc1;
  acc1.setCoordinate(ProtobufCoordinate::COORDINATE_X);
  ProtobufAccMetaData protobufData = acc1.serialize();
  AccMetaData acc2;
  acc2.deserialize(protobufData);
  EXPECT_TRUE(acc1.isEqual(acc2));
}
TEST(runUnitTest, serializeMethodeNorm) {
  AccMetaData acc1;
  acc1.setNorm(ProtobufNorm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
  ProtobufAccMetaData protobufData = acc1.serialize();
  AccMetaData acc2;
  acc2.deserialize(protobufData);
  EXPECT_TRUE(acc1.isEqual(acc2));
}
TEST(runUnitTest, serializeMethodeBoth) {
  AccMetaData acc1;
  acc1.setCoordinate(ProtobufCoordinate::COORDINATE_X);
  acc1.setNorm(ProtobufNorm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
  ProtobufAccMetaData protobufData = acc1.serialize();
  AccMetaData acc2;
  acc2.deserialize(protobufData);
  EXPECT_TRUE(acc1.isEqual(acc2));
  EXPECT_EQ(acc2.getNorm(), ProtobufNorm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
  EXPECT_EQ(acc2.getCoordinate(), ProtobufCoordinate::COORDINATE_NONE);
}
TEST(runUnitTest, serializeMethodeBoth2) {
  AccMetaData acc1;
  acc1.setCoordinate(ProtobufCoordinate::COORDINATE_Y);
  acc1.setNorm(ProtobufNorm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
  ProtobufAccMetaData protobufData = acc1.serialize();
  AccMetaData acc2;
  acc2.deserialize(protobufData);
  EXPECT_TRUE(acc1.isEqual(acc2));
  EXPECT_EQ(acc2.getNorm(), ProtobufNorm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
  EXPECT_EQ(acc2.getCoordinate(), ProtobufCoordinate::COORDINATE_NONE);
}
TEST(runUnitTest, serializeMethodeBoth3) {
  AccMetaData acc1;
  acc1.setCoordinate(ProtobufCoordinate::COORDINATE_Z);
  acc1.setNorm(ProtobufNorm::NORM_NONE);
  ProtobufAccMetaData protobufData = acc1.serialize();
  AccMetaData acc2;
  acc2.deserialize(protobufData);
  EXPECT_TRUE(acc1.isEqual(acc2));
  EXPECT_EQ(acc2.getNorm(), ProtobufNorm::NORM_NONE);
  EXPECT_EQ(acc2.getCoordinate(), ProtobufCoordinate::COORDINATE_NONE);
}
#include <gtest/gtest.h>
#include "AccMetaData.h"

TEST(runUnitTest, SetCoordAndCheck) {
  AccMetaData acc1 = AccMetaData(ProtobufCoordinate::COORDINATE_X, ProtobufNorm::NORM_NONE);
  EXPECT_EQ(acc1.getCoordinate(), ProtobufCoordinate::COORDINATE_X);
  EXPECT_EQ(acc1.getNorm(), ProtobufNorm::NORM_NONE);
}
TEST(runUnitTest, SetNormAndCheck) {
  AccMetaData acc1 = AccMetaData(ProtobufCoordinate::COORDINATE_NONE, ProtobufNorm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
  EXPECT_EQ(acc1.getCoordinate(), ProtobufCoordinate::COORDINATE_NONE);
  EXPECT_EQ(acc1.getNorm(), ProtobufNorm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
}
TEST(runUnitTest, setBoth) {
  EXPECT_THROW(AccMetaData acc1 = AccMetaData(ProtobufCoordinate::COORDINATE_X, ProtobufNorm::NORM_EUCLIDEAN_DIFFERENCES_NORM),
               std::invalid_argument);
}
TEST(runUnitTest, testGet) {
  EXPECT_THROW(AccMetaData acc1 = AccMetaData(ProtobufCoordinate::COORDINATE_NONE, ProtobufNorm::NORM_NONE), std::invalid_argument);
}
TEST(runUnitTest, CompareEqualCoordinateX) {
  AccMetaData acc1 = AccMetaData(ProtobufCoordinate::COORDINATE_X, ProtobufNorm::NORM_NONE);
  AccMetaData acc2 = AccMetaData(ProtobufCoordinate::COORDINATE_X, ProtobufNorm::NORM_NONE);
  EXPECT_TRUE(acc1.isEqual(acc2));
}
TEST(runUnitTest, CompareEqualCoordinateY) {
  AccMetaData acc1 = AccMetaData(ProtobufCoordinate::COORDINATE_Y, ProtobufNorm::NORM_NONE);
  AccMetaData acc2 = AccMetaData(ProtobufCoordinate::COORDINATE_Y, ProtobufNorm::NORM_NONE);
  EXPECT_TRUE(acc1.isEqual(acc2));
}

TEST(runUnitTest, CompareEqualCoordinateZ) {
  AccMetaData acc1 = AccMetaData(ProtobufCoordinate::COORDINATE_Z, ProtobufNorm::NORM_NONE);
  AccMetaData acc2 = AccMetaData(ProtobufCoordinate::COORDINATE_Z, ProtobufNorm::NORM_NONE);
  EXPECT_TRUE(acc1.isEqual(acc2));
}

TEST(runUnitTest, CompareEqualNormEUCLID) {
  AccMetaData acc1 = AccMetaData(ProtobufCoordinate::COORDINATE_NONE, ProtobufNorm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
  AccMetaData acc2 = AccMetaData(ProtobufCoordinate::COORDINATE_NONE, ProtobufNorm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
  EXPECT_TRUE(acc1.isEqual(acc2));
}

TEST(runUnitTest, serializeMethodeCoord) {
  AccMetaData acc1 = AccMetaData(ProtobufCoordinate::COORDINATE_X, ProtobufNorm::NORM_NONE);
  ProtobufAccMetaData protobufData = acc1.serialize();
  AccMetaData acc2 = AccMetaData(protobufData);
  EXPECT_TRUE(acc1.isEqual(acc2));
}

TEST(runUnitTest, serializeMethodeNorm) {
  AccMetaData acc1 = AccMetaData(ProtobufCoordinate::COORDINATE_NONE, ProtobufNorm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
  ProtobufAccMetaData protobufData = acc1.serialize();
  AccMetaData acc2 = AccMetaData(protobufData);
  EXPECT_TRUE(acc1.isEqual(acc2));
}

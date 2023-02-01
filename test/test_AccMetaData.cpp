#include <gTest/gTest.h>
#include "AccMetaData.h"

class AccMetaDataTest : public ::testing::Test {
 protected:
  AccMetaData accMetDataWithCoordinateX1;
  AccMetaData accMetDataWithCoordinateX2;
  AccMetaData accMetDataWithCoordinateY1;
  AccMetaData accMetDataWithCoordinateY2;
  AccMetaData accMetDataWithCoordinateZ1;
  AccMetaData accMetDataWithCoordinateZ2;
  AccMetaData accMetDataWithEuclidianDifferenceNorm1;
  AccMetaData accMetDataWithEuclidianDifferenceNorm2;
  AccMetaData accMetaDataBothNotSet1;
  AccMetaData accMetaDataBothNotSet2;
  virtual void SetUp() {
    this->accMetDataWithCoordinateX1 = AccMetaData(ProtobufCoordinate::COORDINATE_X, ProtobufNorm::NORM_NONE);
    this->accMetDataWithCoordinateX2 = AccMetaData(ProtobufCoordinate::COORDINATE_X, ProtobufNorm::NORM_NONE);
    this->accMetDataWithCoordinateY1 = AccMetaData(ProtobufCoordinate::COORDINATE_Y, ProtobufNorm::NORM_NONE);
    this->accMetDataWithCoordinateY2 = AccMetaData(ProtobufCoordinate::COORDINATE_Y, ProtobufNorm::NORM_NONE);
    this->accMetDataWithCoordinateZ1 = AccMetaData(ProtobufCoordinate::COORDINATE_Z, ProtobufNorm::NORM_NONE);
    this->accMetDataWithCoordinateZ2 = AccMetaData(ProtobufCoordinate::COORDINATE_Z, ProtobufNorm::NORM_NONE);
    this->accMetDataWithEuclidianDifferenceNorm1 = AccMetaData(ProtobufCoordinate::COORDINATE_NONE, ProtobufNorm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
    this->accMetDataWithEuclidianDifferenceNorm2 = AccMetaData(ProtobufCoordinate::COORDINATE_NONE, ProtobufNorm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
    this->accMetaDataBothNotSet1 = AccMetaData(ProtobufCoordinate::COORDINATE_NONE, ProtobufNorm::NORM_NONE);
    this->accMetaDataBothNotSet2 = AccMetaData(ProtobufCoordinate::COORDINATE_NONE, ProtobufNorm::NORM_NONE);
  }
};

TEST_F(AccMetaDataTest, SetCoordAndCheck) {
  EXPECT_EQ(this->accMetDataWithCoordinateX1.getCoordinate(), ProtobufCoordinate::COORDINATE_X);
  EXPECT_EQ(this->accMetDataWithCoordinateX1.getNorm(), ProtobufNorm::NORM_NONE);
}

TEST_F(AccMetaDataTest, SetNormAndCheck) {
  EXPECT_EQ(this->accMetDataWithEuclidianDifferenceNorm1.getCoordinate(), ProtobufCoordinate::COORDINATE_NONE);
  EXPECT_EQ(accMetDataWithEuclidianDifferenceNorm1.getNorm(), ProtobufNorm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
}

TEST_F(AccMetaDataTest, SetBoth) {
  EXPECT_THROW(AccMetaData acc1 = AccMetaData(ProtobufCoordinate::COORDINATE_X, ProtobufNorm::NORM_EUCLIDEAN_DIFFERENCES_NORM),
               std::invalid_argument);
}

TEST_F(AccMetaDataTest, TestNoThrow) {
  EXPECT_NO_THROW(AccMetaData acc1 = AccMetaData(ProtobufCoordinate::COORDINATE_NONE, ProtobufNorm::NORM_NONE));
}

TEST_F(AccMetaDataTest, TestThrow) {
  EXPECT_THROW(AccMetaData acc1 = AccMetaData(ProtobufCoordinate::COORDINATE_X, ProtobufNorm::NORM_EUCLIDEAN_DIFFERENCES_NORM),
               std::invalid_argument);
}

TEST_F(AccMetaDataTest, CompareEqualCoordinateX) {
  EXPECT_TRUE(this->accMetDataWithCoordinateX1.isEqual(this->accMetDataWithCoordinateX2));
}

TEST_F(AccMetaDataTest, CompareEqualCoordinateY) {
  EXPECT_TRUE(this->accMetDataWithCoordinateY1.isEqual(this->accMetDataWithCoordinateY2));
}

TEST_F(AccMetaDataTest, CompareEqualCoordinateZ) {
  EXPECT_TRUE(this->accMetDataWithCoordinateZ1.isEqual(this->accMetDataWithCoordinateZ2));
}

TEST_F(AccMetaDataTest, CompareDifferentCoordinate) {
  EXPECT_FALSE(this->accMetDataWithCoordinateZ1.isEqual(this->accMetDataWithCoordinateY1));
}

TEST_F(AccMetaDataTest, CompareEqualNormEUCLID) {
  EXPECT_TRUE(this->accMetDataWithEuclidianDifferenceNorm1.isEqual(this->accMetDataWithEuclidianDifferenceNorm2));
}

TEST_F(AccMetaDataTest, CompareEqualNotSet) {
  EXPECT_TRUE(this->accMetaDataBothNotSet1.isEqual(this->accMetaDataBothNotSet2));
}

TEST_F(AccMetaDataTest, TestIsSetMethode) {
  EXPECT_EQ(this->accMetDataWithCoordinateX1.isSet(), true);
}

TEST_F(AccMetaDataTest, TestIsSetMethodeFalse) {
  EXPECT_EQ(this->accMetaDataBothNotSet1.isSet(), false);
}

TEST_F(AccMetaDataTest, serializeMethodeCoord) {
  ProtobufAccMetaData protobufData = this->accMetDataWithCoordinateX1.serialize();
  AccMetaData acc = AccMetaData(protobufData);
  EXPECT_TRUE(this->accMetDataWithCoordinateX1.isEqual(acc));
}

TEST_F(AccMetaDataTest, serializeMethodeNorm) {
  ProtobufAccMetaData protobufData = this->accMetDataWithEuclidianDifferenceNorm1.serialize();
  AccMetaData acc = AccMetaData(protobufData);
  EXPECT_TRUE(this->accMetDataWithEuclidianDifferenceNorm1.isEqual(acc));
}

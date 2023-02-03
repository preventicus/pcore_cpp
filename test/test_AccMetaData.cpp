/*

Created by Jakob Glück 2023

Copyright © 2023 PREVENTICUS GmbH

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors
   may be used to endorse or promote products derived from this software without
   specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/
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

TEST_F(AccMetaDataTest, TestIsSetMethod) {
  EXPECT_EQ(this->accMetDataWithCoordinateX1.isSet(), true);
}

TEST_F(AccMetaDataTest, TestIsSetMethodFalse) {
  EXPECT_EQ(this->accMetaDataBothNotSet1.isSet(), false);
}

TEST_F(AccMetaDataTest, serializeMethodCoord) {
  ProtobufAccMetaData protobufData;
  this->accMetDataWithCoordinateX1.serialize(&protobufData);
  AccMetaData acc = AccMetaData(protobufData);
  EXPECT_TRUE(this->accMetDataWithCoordinateX1.isEqual(acc));
}

TEST_F(AccMetaDataTest, serializeMethodNorm) {
  ProtobufAccMetaData protobufData;
  this->accMetDataWithEuclidianDifferenceNorm1.serialize(&protobufData);
  AccMetaData acc = AccMetaData(protobufData);
  EXPECT_TRUE(this->accMetDataWithEuclidianDifferenceNorm1.isEqual(acc));
}

TEST_F(AccMetaDataTest, CheckAccPtr) {
  ProtobufAccMetaData protobufData;
  this->accMetDataWithEuclidianDifferenceNorm1.serialize(&protobufData);
  AccMetaData acc = AccMetaData(protobufData);
  ProtobufAccMetaData* protobufDataPtr = &protobufData;
  AccMetaData* ptr = &acc;
  EXPECT_FALSE(ptr == nullptr);
  EXPECT_FALSE(protobufDataPtr == nullptr);
}

TEST_F(AccMetaDataTest, CheckAccNullPtr) {
  ProtobufAccMetaData* protobufData = nullptr;
  EXPECT_THROW(this->accMetDataWithEuclidianDifferenceNorm1.serialize(protobufData), std::invalid_argument);
}
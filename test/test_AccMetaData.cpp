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
#include "AccMetaDataExampleFactory.h"

class AccMetaDataTest : public ::testing::Test {
 protected:
  AccMetaData accMetaDataWithCoordinateX1 = AccMetaDataExampleFactory::accMetaDataWithCoordinateX();
  AccMetaData accMetaDataWithCoordinateX2 = AccMetaDataExampleFactory::accMetaDataWithCoordinateX();
  AccMetaData accMetaDataWithCoordinateY1 = AccMetaDataExampleFactory::accMetaDataWithCoordinateY();
  AccMetaData accMetaDataWithCoordinateY2 = AccMetaDataExampleFactory::accMetaDataWithCoordinateY();
  AccMetaData accMetaDataWithCoordinateZ1 = AccMetaDataExampleFactory::accMetaDataWithCoordinateZ();
  AccMetaData accMetaDataWithCoordinateZ2 = AccMetaDataExampleFactory::accMetaDataWithCoordinateZ();
  AccMetaData accMetaDataWithEuclideanDifferenceNorm1 = AccMetaDataExampleFactory::accMetaDataWithEuclideanDifferenceNorm();
  AccMetaData accMetaDataWithEuclideanDifferenceNorm2 = AccMetaDataExampleFactory::accMetaDataWithEuclideanDifferenceNorm();
  AccMetaData accMetaDataNotSet1 = AccMetaDataExampleFactory::accMetaDataNotSet();
  AccMetaData accMetaDataNotSet2 = AccMetaDataExampleFactory::accMetaDataNotSet();
};

TEST_F(AccMetaDataTest, SetCoordAndCheck) {
  EXPECT_EQ(this->accMetaDataWithCoordinateX1.getCoordinate(), ProtobufCoordinate::COORDINATE_X);
  EXPECT_EQ(this->accMetaDataWithCoordinateX1.getNorm(), ProtobufNorm::NORM_NONE);
}

TEST_F(AccMetaDataTest, SetNormAndCheck) {
  EXPECT_EQ(this->accMetaDataWithEuclideanDifferenceNorm1.getCoordinate(), ProtobufCoordinate::COORDINATE_NONE);
  EXPECT_EQ(accMetaDataWithEuclideanDifferenceNorm1.getNorm(), ProtobufNorm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
}

TEST_F(AccMetaDataTest, SetEmptyConstructor) {
  EXPECT_EQ(this->accMetaDataNotSet1.getCoordinate(), ProtobufCoordinate::COORDINATE_NONE);
  EXPECT_EQ(this->accMetaDataNotSet1.getNorm(), ProtobufNorm::NORM_NONE);
}

TEST_F(AccMetaDataTest, CompareEqualCoordinateX) {
  EXPECT_TRUE(this->accMetaDataWithCoordinateX1.isEqual(this->accMetaDataWithCoordinateX2));
}

TEST_F(AccMetaDataTest, CompareEqualCoordinateY) {
  EXPECT_TRUE(this->accMetaDataWithCoordinateY1.isEqual(this->accMetaDataWithCoordinateY2));
}

TEST_F(AccMetaDataTest, CompareEqualCoordinateZ) {
  EXPECT_TRUE(this->accMetaDataWithCoordinateZ1.isEqual(this->accMetaDataWithCoordinateZ2));
}

TEST_F(AccMetaDataTest, CompareDifferentCoordinate) {
  EXPECT_FALSE(this->accMetaDataWithCoordinateZ1.isEqual(this->accMetaDataWithCoordinateY1));
}

TEST_F(AccMetaDataTest, CompareEqualNormEUCLID) {
  EXPECT_TRUE(this->accMetaDataWithEuclideanDifferenceNorm1.isEqual(this->accMetaDataWithEuclideanDifferenceNorm2));
}

TEST_F(AccMetaDataTest, CompareEqualNotSet) {
  EXPECT_TRUE(this->accMetaDataNotSet1.isEqual(this->accMetaDataNotSet2));
}

TEST_F(AccMetaDataTest, TestIsSetMethod) {
  EXPECT_EQ(this->accMetaDataWithCoordinateX1.isSet(), true);
}

TEST_F(AccMetaDataTest, TestIsSetMethodFalse) {
  EXPECT_EQ(this->accMetaDataNotSet1.isSet(), false);
}

TEST_F(AccMetaDataTest, serializeMethodCoord) {
  ProtobufAccMetaData protobufData;
  this->accMetaDataWithCoordinateX1.serialize(&protobufData);
  AccMetaData acc = AccMetaData(protobufData);
  EXPECT_TRUE(this->accMetaDataWithCoordinateX1.isEqual(acc));
}

TEST_F(AccMetaDataTest, serializeMethodNorm) {
  ProtobufAccMetaData protobufData;
  this->accMetaDataWithEuclideanDifferenceNorm1.serialize(&protobufData);
  AccMetaData acc = AccMetaData(protobufData);
  EXPECT_TRUE(this->accMetaDataWithEuclideanDifferenceNorm1.isEqual(acc));
}

TEST_F(AccMetaDataTest, CheckAccPtr) {
  ProtobufAccMetaData protobufData;
  this->accMetaDataWithEuclideanDifferenceNorm1.serialize(&protobufData);
  AccMetaData acc = AccMetaData(protobufData);
  ProtobufAccMetaData* protobufDataPtr = &protobufData;
  AccMetaData* ptr = &acc;
  EXPECT_FALSE(ptr == nullptr);
  EXPECT_FALSE(protobufDataPtr == nullptr);
}

TEST_F(AccMetaDataTest, CheckAccNullPtr) {
  ProtobufAccMetaData* protobufData = nullptr;
  EXPECT_THROW(this->accMetaDataWithEuclideanDifferenceNorm1.serialize(protobufData), std::invalid_argument);
}
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
};

TEST_F(AccMetaDataTest, TestSetAndGetCoordinate) {
  AccMetaData accMetaData = AccMetaData(ProtobufCoordinate::COORDINATE_X);
  EXPECT_EQ(accMetaData.getCoordinate(), ProtobufCoordinate::COORDINATE_X);
  EXPECT_EQ(accMetaData.getNorm(), ProtobufNorm::NORM_NONE);
}

TEST_F(AccMetaDataTest, TestSetAndGetNorm) {
  AccMetaData accMetaData = AccMetaData(ProtobufNorm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
  EXPECT_EQ(accMetaData.getCoordinate(), ProtobufCoordinate::COORDINATE_NONE);
  EXPECT_EQ(accMetaData.getNorm(), ProtobufNorm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
}

TEST_F(AccMetaDataTest, TestSetAndGetEmptyConstructor) {
  AccMetaData accMetaData = AccMetaData();
  EXPECT_EQ(accMetaData.getCoordinate(), ProtobufCoordinate::COORDINATE_NONE);
  EXPECT_EQ(accMetaData.getNorm(), ProtobufNorm::NORM_NONE);
}

TEST_F(AccMetaDataTest, CompareEqualCoordinate) {
  AccMetaData accMetaDataX1 = AccMetaData(ProtobufCoordinate::COORDINATE_X);
  AccMetaData accMetaDataX2 = AccMetaData(ProtobufCoordinate::COORDINATE_X);
  AccMetaData accMetaDataY1 = AccMetaData(ProtobufCoordinate::COORDINATE_Y);
  AccMetaData accMetaDataY2 = AccMetaData(ProtobufCoordinate::COORDINATE_Y);
  AccMetaData accMetaDataZ1 = AccMetaData(ProtobufCoordinate::COORDINATE_Z);
  AccMetaData accMetaDataZ2 = AccMetaData(ProtobufCoordinate::COORDINATE_Z);
  EXPECT_TRUE(accMetaDataX1.isEqual(accMetaDataX2));
  EXPECT_TRUE(accMetaDataY1.isEqual(accMetaDataY2));
  EXPECT_TRUE(accMetaDataZ1.isEqual(accMetaDataZ2));
}

TEST_F(AccMetaDataTest, CompareDifferentCoordinate) {
  AccMetaData accMetaData1 = AccMetaData(ProtobufCoordinate::COORDINATE_X);
  AccMetaData accMetaData2 = AccMetaData(ProtobufCoordinate::COORDINATE_Z);
  EXPECT_FALSE(accMetaData1.isEqual(accMetaData2));
}

TEST_F(AccMetaDataTest, CompareCoordinateWithNorm) {
  AccMetaData accMetaData1 = AccMetaData(ProtobufCoordinate::COORDINATE_X);
  AccMetaData accMetaData2 = AccMetaData(ProtobufNorm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
  EXPECT_FALSE(accMetaData1.isEqual(accMetaData2));
}

TEST_F(AccMetaDataTest, CompareEqualNormEUCLID) {
  AccMetaData accMetaData1 = AccMetaData(ProtobufNorm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
  AccMetaData accMetaData2 = AccMetaData(ProtobufNorm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
  EXPECT_TRUE(accMetaData1.isEqual(accMetaData2));
}

TEST_F(AccMetaDataTest, CompareEqualNotSet) {
  AccMetaData accMetaData1 = AccMetaData();
  AccMetaData accMetaData2 = AccMetaData();
  EXPECT_TRUE(accMetaData1.isEqual(accMetaData2));
}

TEST_F(AccMetaDataTest, TestIsSet) {
  AccMetaData accMetaDataX = AccMetaData(ProtobufCoordinate::COORDINATE_X);
  AccMetaData accMetaDataY = AccMetaData(ProtobufCoordinate::COORDINATE_Y);
  AccMetaData accMetaDataZ = AccMetaData(ProtobufCoordinate::COORDINATE_Z);
  AccMetaData accMetaDataN = AccMetaData(ProtobufNorm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
  EXPECT_TRUE(accMetaDataX.isSet());
  EXPECT_TRUE(accMetaDataY.isSet());
  EXPECT_TRUE(accMetaDataZ.isSet());
  EXPECT_TRUE(accMetaDataN.isSet());
}

TEST_F(AccMetaDataTest, TestIsNotSet) {
  AccMetaData accMetaData = AccMetaData();
  EXPECT_FALSE(accMetaData.isSet());
}

TEST_F(AccMetaDataTest, TestSerialize) {
  AccMetaData accMetaDataX1 = AccMetaData(ProtobufCoordinate::COORDINATE_X);
  AccMetaData accMetaDataY1 = AccMetaData(ProtobufCoordinate::COORDINATE_Y);
  AccMetaData accMetaDataZ1 = AccMetaData(ProtobufCoordinate::COORDINATE_Z);
  AccMetaData accMetaDataN1 = AccMetaData(ProtobufNorm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
  ProtobufAccMetaData protobufAccMetaDataX1;
  ProtobufAccMetaData protobufAccMetaDataY1;
  ProtobufAccMetaData protobufAccMetaDataZ1;
  ProtobufAccMetaData protobufAccMetaDataN1;
  accMetaDataX1.serialize(&protobufAccMetaDataX1);
  accMetaDataY1.serialize(&protobufAccMetaDataY1);
  accMetaDataZ1.serialize(&protobufAccMetaDataZ1);
  accMetaDataN1.serialize(&protobufAccMetaDataN1);
  AccMetaData accMetaDataX2 = AccMetaData(protobufAccMetaDataX1);
  AccMetaData accMetaDataY2 = AccMetaData(protobufAccMetaDataY1);
  AccMetaData accMetaDataZ2 = AccMetaData(protobufAccMetaDataZ1);
  AccMetaData accMetaDataN2 = AccMetaData(protobufAccMetaDataN1);
  EXPECT_TRUE(accMetaDataX1.isEqual(accMetaDataX2));
  EXPECT_TRUE(accMetaDataY1.isEqual(accMetaDataY2));
  EXPECT_TRUE(accMetaDataZ1.isEqual(accMetaDataZ2));
  EXPECT_TRUE(accMetaDataN1.isEqual(accMetaDataN2));
}

TEST_F(AccMetaDataTest, TestSerializeNoThrow) {
  AccMetaData accMetaData = AccMetaData(ProtobufCoordinate::COORDINATE_X);
  ProtobufAccMetaData protobufData;
  EXPECT_NO_THROW(accMetaData.serialize(&protobufData));
}

TEST_F(AccMetaDataTest, TestSerializeThrow) {
  AccMetaData accMetaData = AccMetaData(ProtobufCoordinate::COORDINATE_X);
  ProtobufAccMetaData* protobufData = nullptr;
  EXPECT_THROW(accMetaData.serialize(protobufData), std::invalid_argument);
}

TEST_F(AccMetaDataTest, TestToJson) {
  AccMetaData accMetaDataX1 = AccMetaData(ProtobufCoordinate::COORDINATE_X);
  AccMetaData accMetaDataY1 = AccMetaData(ProtobufCoordinate::COORDINATE_Y);
  AccMetaData accMetaDataZ1 = AccMetaData(ProtobufCoordinate::COORDINATE_Z);
  AccMetaData accMetaDataN1 = AccMetaData(ProtobufNorm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
  AccMetaDataJson accMetaDataJsonX1 = accMetaDataX1.toJson();
  AccMetaDataJson accMetaDataJsonY1 = accMetaDataY1.toJson();
  AccMetaDataJson accMetaDataJsonZ1 = accMetaDataZ1.toJson();
  AccMetaDataJson accMetaDataJsonN1 = accMetaDataN1.toJson();
  AccMetaDataJson accMetaDataJsonX2 = AccMetaDataExampleFactory::buildAccMetaDataJson(ProtobufCoordinate::COORDINATE_X);
  AccMetaDataJson accMetaDataJsonY2 = AccMetaDataExampleFactory::buildAccMetaDataJson(ProtobufCoordinate::COORDINATE_Y);
  AccMetaDataJson accMetaDataJsonZ2 = AccMetaDataExampleFactory::buildAccMetaDataJson(ProtobufCoordinate::COORDINATE_Z);
  AccMetaDataJson accMetaDataJsonN2 = AccMetaDataExampleFactory::buildAccMetaDataJson(ProtobufNorm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
  EXPECT_TRUE(accMetaDataJsonX1 == accMetaDataJsonX2);
  EXPECT_TRUE(accMetaDataJsonY1 == accMetaDataJsonY2);
  EXPECT_TRUE(accMetaDataJsonZ1 == accMetaDataJsonZ2);
  EXPECT_TRUE(accMetaDataJsonN1 == accMetaDataJsonN2);
}
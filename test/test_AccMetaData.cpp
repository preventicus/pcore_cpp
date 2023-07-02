/*

Created by Jakob Glueck, Steve Merschel 2023

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
  AccMetaData accMetaData = AccMetaDataExampleFactory::accMetaDataWithCoordinateX();
  EXPECT_EQ(accMetaData.getCoordinate(), ProtobufCoordinate::COORDINATE_X);
  EXPECT_EQ(accMetaData.getNorm(), ProtobufNorm::NORM_NONE);
}

TEST_F(AccMetaDataTest, TestSetAndGetNorm) {
  AccMetaData accMetaData = AccMetaDataExampleFactory::accMetaDataWithNormEuclideanDifferencesNorm();
  EXPECT_EQ(accMetaData.getCoordinate(), ProtobufCoordinate::COORDINATE_NONE);
  EXPECT_EQ(accMetaData.getNorm(), ProtobufNorm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
}

TEST_F(AccMetaDataTest, TestSetAndGetEmptyConstructor) {
  AccMetaData accMetaData = AccMetaDataExampleFactory::accMetaDataNotSet();
  EXPECT_EQ(accMetaData.getCoordinate(), ProtobufCoordinate::COORDINATE_NONE);
  EXPECT_EQ(accMetaData.getNorm(), ProtobufNorm::NORM_NONE);
}

TEST_F(AccMetaDataTest, TestIsEqualCoordinateWithAccMetaDataWithCoordinateX) {
  AccMetaData accMetaData1 = AccMetaDataExampleFactory::accMetaDataWithCoordinateX();
  AccMetaData accMetaData2 = AccMetaDataExampleFactory::accMetaDataWithCoordinateX();
  EXPECT_TRUE(accMetaData1.isEqual(accMetaData2));
}

TEST_F(AccMetaDataTest, TestIsEqualCoordinateWithAccMetaDataWithCoordinateY) {
  AccMetaData accMetaData1 = AccMetaDataExampleFactory::accMetaDataWithCoordinateY();
  AccMetaData accMetaData2 = AccMetaDataExampleFactory::accMetaDataWithCoordinateY();
  EXPECT_TRUE(accMetaData1.isEqual(accMetaData2));
}

TEST_F(AccMetaDataTest, TestIsEqualCoordinateWithAccMetaDataWithCoordinateZ) {
  AccMetaData accMetaData1 = AccMetaDataExampleFactory::accMetaDataWithCoordinateZ();
  AccMetaData accMetaData2 = AccMetaDataExampleFactory::accMetaDataWithCoordinateZ();
  EXPECT_TRUE(accMetaData1.isEqual(accMetaData2));
}

TEST_F(AccMetaDataTest, TestIsNotEqualCoordinate) {
  AccMetaData accMetaData1 = AccMetaDataExampleFactory::accMetaDataWithCoordinateX();
  AccMetaData accMetaData2 = AccMetaDataExampleFactory::accMetaDataWithCoordinateZ();
  EXPECT_FALSE(accMetaData1.isEqual(accMetaData2));
}

TEST_F(AccMetaDataTest, TestIsCoordinateWithNorm) {
  AccMetaData accMetaData1 = AccMetaDataExampleFactory::accMetaDataWithCoordinateX();
  AccMetaData accMetaData2 = AccMetaDataExampleFactory::accMetaDataWithNormEuclideanDifferencesNorm();
  EXPECT_FALSE(accMetaData1.isEqual(accMetaData2));
}

TEST_F(AccMetaDataTest, TestIsEqualNormEuclidean) {
  AccMetaData accMetaData1 = AccMetaDataExampleFactory::accMetaDataWithNormEuclideanDifferencesNorm();
  AccMetaData accMetaData2 = AccMetaDataExampleFactory::accMetaDataWithNormEuclideanDifferencesNorm();
  EXPECT_TRUE(accMetaData1.isEqual(accMetaData2));
}

TEST_F(AccMetaDataTest, TestIsEqualNotSet) {
  AccMetaData accMetaData1 = AccMetaDataExampleFactory::accMetaDataNotSet();
  AccMetaData accMetaData2 = AccMetaDataExampleFactory::accMetaDataNotSet();
  EXPECT_TRUE(accMetaData1.isEqual(accMetaData2));
}

TEST_F(AccMetaDataTest, TestIsSetWithAccMetaDataWithCoordinateX) {
  AccMetaData accMetaData = AccMetaDataExampleFactory::accMetaDataWithCoordinateX();
  EXPECT_TRUE(accMetaData.isSet());
}

TEST_F(AccMetaDataTest, TestIsSetWithAccMetaDataWithCoordinateY) {
  AccMetaData accMetaData = AccMetaDataExampleFactory::accMetaDataWithCoordinateY();
  EXPECT_TRUE(accMetaData.isSet());
}

TEST_F(AccMetaDataTest, TestIsSetWithAccMetaDataWithCoordinateZ) {
  AccMetaData accMetaData = AccMetaDataExampleFactory::accMetaDataWithCoordinateZ();
  EXPECT_TRUE(accMetaData.isSet());
}

TEST_F(AccMetaDataTest, TestIsSetWithAccMetaDataWithNormEuclideanDifferencesNorm) {
  AccMetaData accMetaData = AccMetaDataExampleFactory::accMetaDataWithNormEuclideanDifferencesNorm();
  EXPECT_TRUE(accMetaData.isSet());
}

TEST_F(AccMetaDataTest, TestIsSetWithAccMetaDataNotSet) {
  AccMetaData accMetaData = AccMetaDataExampleFactory::accMetaDataNotSet();
  EXPECT_FALSE(accMetaData.isSet());
}

TEST_F(AccMetaDataTest, TestSerializeWithAccMetaDataWithCoordinateX) {
  AccMetaData accMetaData1 = AccMetaDataExampleFactory::accMetaDataWithCoordinateX();
  ProtobufAccMetaData protobufAccMetaData;
  accMetaData1.serialize(&protobufAccMetaData);
  AccMetaData accMetaData2 = AccMetaData(protobufAccMetaData);
  EXPECT_TRUE(accMetaData1.isEqual(accMetaData2));
}

TEST_F(AccMetaDataTest, TestSerializeWithAccMetaDataWithCoordinateY) {
  AccMetaData accMetaData1 = AccMetaDataExampleFactory::accMetaDataWithCoordinateY();
  ProtobufAccMetaData protobufAccMetaData;
  accMetaData1.serialize(&protobufAccMetaData);
  AccMetaData accMetaData2 = AccMetaData(protobufAccMetaData);
  EXPECT_TRUE(accMetaData1.isEqual(accMetaData2));
}

TEST_F(AccMetaDataTest, TestSerializeWithAccMetaDataWithCoordinateZ) {
  AccMetaData accMetaData1 = AccMetaDataExampleFactory::accMetaDataWithCoordinateZ();
  ProtobufAccMetaData protobufAccMetaData;
  accMetaData1.serialize(&protobufAccMetaData);
  AccMetaData accMetaData2 = AccMetaData(protobufAccMetaData);
  EXPECT_TRUE(accMetaData1.isEqual(accMetaData2));
}

TEST_F(AccMetaDataTest, TestSerializeWithAccMetaDataWithNormEuclideanDifferencesNorm) {
  AccMetaData accMetaData1 = AccMetaDataExampleFactory::accMetaDataWithNormEuclideanDifferencesNorm();
  ProtobufAccMetaData protobufAccMetaData;
  accMetaData1.serialize(&protobufAccMetaData);
  AccMetaData accMetaData2 = AccMetaData(protobufAccMetaData);
  EXPECT_TRUE(accMetaData1.isEqual(accMetaData2));
}

TEST_F(AccMetaDataTest, TestSerializeNoThrow) {
  AccMetaData accMetaData = AccMetaDataExampleFactory::accMetaDataWithCoordinateX();
  ProtobufAccMetaData protobufData;
  EXPECT_NO_THROW(accMetaData.serialize(&protobufData));
}

TEST_F(AccMetaDataTest, TestSerializeThrow) {
  AccMetaData accMetaData = AccMetaDataExampleFactory::accMetaDataWithCoordinateX();
  ProtobufAccMetaData* protobufData = nullptr;
  EXPECT_THROW(accMetaData.serialize(protobufData), std::invalid_argument);
}

TEST_F(AccMetaDataTest, TestToJsonWithAccMetaDataWithCoordinateX) {
  AccMetaData accMetaData = AccMetaDataExampleFactory::accMetaDataWithCoordinateX();
  AccMetaDataJson accMetaDataJson1 = accMetaData.toJson();
  AccMetaDataJson accMetaDataJson2 = AccMetaDataExampleFactory::buildAccMetaDataJson(accMetaData);
  EXPECT_TRUE(accMetaDataJson1.toStyledString() == accMetaDataJson2.toStyledString());
}

TEST_F(AccMetaDataTest, TestToJsonWithAccMetaDataWithCoordinateY) {
  AccMetaData accMetaData = AccMetaDataExampleFactory::accMetaDataWithCoordinateY();
  AccMetaDataJson accMetaDataJson1 = accMetaData.toJson();
  AccMetaDataJson accMetaDataJson2 = AccMetaDataExampleFactory::buildAccMetaDataJson(accMetaData);
  EXPECT_TRUE(accMetaDataJson1.toStyledString() == accMetaDataJson2.toStyledString());
}

TEST_F(AccMetaDataTest, TestToJsonWithAccMetaDataWithCoordinateZ) {
  AccMetaData accMetaData = AccMetaDataExampleFactory::accMetaDataWithCoordinateZ();
  AccMetaDataJson accMetaDataJson1 = accMetaData.toJson();
  AccMetaDataJson accMetaDataJson2 = AccMetaDataExampleFactory::buildAccMetaDataJson(accMetaData);
  EXPECT_TRUE(accMetaDataJson1.toStyledString() == accMetaDataJson2.toStyledString());
}

TEST_F(AccMetaDataTest, TestToJsonWithAccMetaDataWithNormEuclideanDifferencesNorm) {
  AccMetaData accMetaData = AccMetaDataExampleFactory::accMetaDataWithNormEuclideanDifferencesNorm();
  AccMetaDataJson accMetaDataJson1 = accMetaData.toJson();
  AccMetaDataJson accMetaDataJson2 = AccMetaDataExampleFactory::buildAccMetaDataJson(accMetaData);
  EXPECT_TRUE(accMetaDataJson1.toStyledString() == accMetaDataJson2.toStyledString());
}

TEST_F(AccMetaDataTest, TestHasNormWithAccMetaDataWithNormEuclideanDifferencesNorm) {
  AccMetaData accMetaData = AccMetaDataExampleFactory::accMetaDataWithNormEuclideanDifferencesNorm();
  EXPECT_TRUE(accMetaData.hasNorm());
}

TEST_F(AccMetaDataTest, TestHasNormWithAccMetaDataWithNormNone) {
  AccMetaData accMetaData = AccMetaDataExampleFactory::accMetaDataWithNormNone();
  EXPECT_FALSE(accMetaData.hasNorm());
}

TEST_F(AccMetaDataTest, TestHasCoordinateWithAccMetaDataWithCoordinateY) {
  AccMetaData accMetaData = AccMetaDataExampleFactory::accMetaDataWithCoordinateY();
  EXPECT_TRUE(accMetaData.hasCoordinate());
}

TEST_F(AccMetaDataTest, TestHasCoordinateWithAccMetaDataWithCoordinateNone) {
  AccMetaData accMetaData = AccMetaDataExampleFactory::accMetaDataWithCoordinateNone();
  EXPECT_FALSE(accMetaData.hasCoordinate());
}

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

TEST(AccMetaDataTest, TestSetAndGetCoordinate) {
  auto accMetaData = AccMetaDataExampleFactory::accMetaDataWithCoordinateX();
  EXPECT_EQ(accMetaData.getCoordinate(), ProtobufCoordinate::COORDINATE_X);
  EXPECT_EQ(accMetaData.getNorm(), ProtobufNorm::NORM_NONE);
}

TEST(AccMetaDataTest, TestSetAndGetNorm) {
  auto accMetaData = AccMetaDataExampleFactory::accMetaDataWithNormEuclideanDifferencesNorm();
  EXPECT_EQ(accMetaData.getCoordinate(), ProtobufCoordinate::COORDINATE_NONE);
  EXPECT_EQ(accMetaData.getNorm(), ProtobufNorm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
}

TEST(AccMetaDataTest, TestSetAndGetEmptyConstructor) {
  auto accMetaData = AccMetaDataExampleFactory::accMetaDataNotSet();
  EXPECT_EQ(accMetaData.getCoordinate(), ProtobufCoordinate::COORDINATE_NONE);
  EXPECT_EQ(accMetaData.getNorm(), ProtobufNorm::NORM_NONE);
}

TEST(AccMetaDataTest, TestIsEqualCoordinateWithAccMetaDataWithCoordinateX) {
  auto accMetaData1 = AccMetaDataExampleFactory::accMetaDataWithCoordinateX();
  auto accMetaData2 = AccMetaDataExampleFactory::accMetaDataWithCoordinateX();
  EXPECT_TRUE(accMetaData1.isEqual(accMetaData2));
}

TEST(AccMetaDataTest, TestIsEqualCoordinateWithAccMetaDataWithCoordinateY) {
  auto accMetaData1 = AccMetaDataExampleFactory::accMetaDataWithCoordinateY();
  auto accMetaData2 = AccMetaDataExampleFactory::accMetaDataWithCoordinateY();
  EXPECT_TRUE(accMetaData1.isEqual(accMetaData2));
}

TEST(AccMetaDataTest, TestIsEqualCoordinateWithAccMetaDataWithCoordinateZ) {
  auto accMetaData1 = AccMetaDataExampleFactory::accMetaDataWithCoordinateZ();
  auto accMetaData2 = AccMetaDataExampleFactory::accMetaDataWithCoordinateZ();
  EXPECT_TRUE(accMetaData1.isEqual(accMetaData2));
}

TEST(AccMetaDataTest, TestIsNotEqualCoordinate) {
  auto accMetaData1 = AccMetaDataExampleFactory::accMetaDataWithCoordinateX();
  auto accMetaData2 = AccMetaDataExampleFactory::accMetaDataWithCoordinateZ();
  EXPECT_FALSE(accMetaData1.isEqual(accMetaData2));
}

TEST(AccMetaDataTest, TestIsCoordinateWithNorm) {
  auto accMetaData1 = AccMetaDataExampleFactory::accMetaDataWithCoordinateX();
  auto accMetaData2 = AccMetaDataExampleFactory::accMetaDataWithNormEuclideanDifferencesNorm();
  EXPECT_FALSE(accMetaData1.isEqual(accMetaData2));
}

TEST(AccMetaDataTest, TestIsEqualNormEuclidean) {
  auto accMetaData1 = AccMetaDataExampleFactory::accMetaDataWithNormEuclideanDifferencesNorm();
  auto accMetaData2 = AccMetaDataExampleFactory::accMetaDataWithNormEuclideanDifferencesNorm();
  EXPECT_TRUE(accMetaData1.isEqual(accMetaData2));
}

TEST(AccMetaDataTest, TestIsEqualNotSet) {
  auto accMetaData1 = AccMetaDataExampleFactory::accMetaDataNotSet();
  auto accMetaData2 = AccMetaDataExampleFactory::accMetaDataNotSet();
  EXPECT_TRUE(accMetaData1.isEqual(accMetaData2));
}

TEST(AccMetaDataTest, TestIsSetWithAccMetaDataWithCoordinateX) {
  auto accMetaData = AccMetaDataExampleFactory::accMetaDataWithCoordinateX();
  EXPECT_TRUE(accMetaData.isSet());
}

TEST(AccMetaDataTest, TestIsSetWithAccMetaDataWithCoordinateY) {
  auto accMetaData = AccMetaDataExampleFactory::accMetaDataWithCoordinateY();
  EXPECT_TRUE(accMetaData.isSet());
}

TEST(AccMetaDataTest, TestIsSetWithAccMetaDataWithCoordinateZ) {
  auto accMetaData = AccMetaDataExampleFactory::accMetaDataWithCoordinateZ();
  EXPECT_TRUE(accMetaData.isSet());
}

TEST(AccMetaDataTest, TestIsSetWithAccMetaDataWithNormEuclideanDifferencesNorm) {
  auto accMetaData = AccMetaDataExampleFactory::accMetaDataWithNormEuclideanDifferencesNorm();
  EXPECT_TRUE(accMetaData.isSet());
}

TEST(AccMetaDataTest, TestIsSetWithAccMetaDataNotSet) {
  auto accMetaData = AccMetaDataExampleFactory::accMetaDataNotSet();
  EXPECT_FALSE(accMetaData.isSet());
}

TEST(AccMetaDataTest, TestSerializeWithAccMetaDataWithCoordinateX) {
  auto accMetaData1 = AccMetaDataExampleFactory::accMetaDataWithCoordinateX();
  ProtobufAccMetaData protobufAccMetaData;
  accMetaData1.serialize(&protobufAccMetaData);
  auto accMetaData2 = AccMetaData(protobufAccMetaData);
  EXPECT_TRUE(accMetaData1.isEqual(accMetaData2));
}

TEST(AccMetaDataTest, TestSerializeWithAccMetaDataWithCoordinateY) {
  auto accMetaData1 = AccMetaDataExampleFactory::accMetaDataWithCoordinateY();
  ProtobufAccMetaData protobufAccMetaData;
  accMetaData1.serialize(&protobufAccMetaData);
  auto accMetaData2 = AccMetaData(protobufAccMetaData);
  EXPECT_TRUE(accMetaData1.isEqual(accMetaData2));
}

TEST(AccMetaDataTest, TestSerializeWithAccMetaDataWithCoordinateZ) {
  auto accMetaData1 = AccMetaDataExampleFactory::accMetaDataWithCoordinateZ();
  ProtobufAccMetaData protobufAccMetaData;
  accMetaData1.serialize(&protobufAccMetaData);
  auto accMetaData2 = AccMetaData(protobufAccMetaData);
  EXPECT_TRUE(accMetaData1.isEqual(accMetaData2));
}

TEST(AccMetaDataTest, TestSerializeWithAccMetaDataWithNormEuclideanDifferencesNorm) {
  auto accMetaData1 = AccMetaDataExampleFactory::accMetaDataWithNormEuclideanDifferencesNorm();
  ProtobufAccMetaData protobufAccMetaData;
  accMetaData1.serialize(&protobufAccMetaData);
  auto accMetaData2 = AccMetaData(protobufAccMetaData);
  EXPECT_TRUE(accMetaData1.isEqual(accMetaData2));
}

TEST(AccMetaDataTest, TestSerializeNoThrow) {
  auto accMetaData = AccMetaDataExampleFactory::accMetaDataWithCoordinateX();
  ProtobufAccMetaData protobufData;
  EXPECT_NO_THROW(accMetaData.serialize(&protobufData));
}

TEST(AccMetaDataTest, TestSerializeThrow) {
  auto accMetaData = AccMetaDataExampleFactory::accMetaDataWithCoordinateX();
  ProtobufAccMetaData* protobufData = nullptr;
  EXPECT_THROW(accMetaData.serialize(protobufData), std::invalid_argument);
}

TEST(AccMetaDataTest, TestToJsonWithAccMetaDataWithCoordinateX) {
  auto accMetaData = AccMetaDataExampleFactory::accMetaDataWithCoordinateX();
  auto accMetaDataJson1 = accMetaData.toJson();
  auto accMetaDataJson2 = AccMetaDataExampleFactory::buildAccMetaDataJson(accMetaData);
  EXPECT_TRUE(accMetaDataJson1.toStyledString() == accMetaDataJson2.toStyledString());
}

TEST(AccMetaDataTest, TestToJsonWithAccMetaDataWithCoordinateY) {
  auto accMetaData = AccMetaDataExampleFactory::accMetaDataWithCoordinateY();
  auto accMetaDataJson1 = accMetaData.toJson();
  auto accMetaDataJson2 = AccMetaDataExampleFactory::buildAccMetaDataJson(accMetaData);
  EXPECT_TRUE(accMetaDataJson1.toStyledString() == accMetaDataJson2.toStyledString());
}

TEST(AccMetaDataTest, TestToJsonWithAccMetaDataWithCoordinateZ) {
  auto accMetaData = AccMetaDataExampleFactory::accMetaDataWithCoordinateZ();
  auto accMetaDataJson1 = accMetaData.toJson();
  auto accMetaDataJson2 = AccMetaDataExampleFactory::buildAccMetaDataJson(accMetaData);
  EXPECT_TRUE(accMetaDataJson1.toStyledString() == accMetaDataJson2.toStyledString());
}

TEST(AccMetaDataTest, TestToJsonWithAccMetaDataWithNormEuclideanDifferencesNorm) {
  auto accMetaData = AccMetaDataExampleFactory::accMetaDataWithNormEuclideanDifferencesNorm();
  auto accMetaDataJson1 = accMetaData.toJson();
  auto accMetaDataJson2 = AccMetaDataExampleFactory::buildAccMetaDataJson(accMetaData);
  EXPECT_TRUE(accMetaDataJson1.toStyledString() == accMetaDataJson2.toStyledString());
}

TEST(AccMetaDataTest, TestHasNormWithAccMetaDataWithNormEuclideanDifferencesNorm) {
  auto accMetaData = AccMetaDataExampleFactory::accMetaDataWithNormEuclideanDifferencesNorm();
  EXPECT_TRUE(accMetaData.hasNorm());
}

TEST(AccMetaDataTest, TestHasNormWithAccMetaDataWithNormNone) {
  auto accMetaData = AccMetaDataExampleFactory::accMetaDataWithNormNone();
  EXPECT_FALSE(accMetaData.hasNorm());
}

TEST(AccMetaDataTest, TestHasCoordinateWithAccMetaDataWithCoordinateY) {
  auto accMetaData = AccMetaDataExampleFactory::accMetaDataWithCoordinateY();
  EXPECT_TRUE(accMetaData.hasCoordinate());
}

TEST(AccMetaDataTest, TestHasCoordinateWithAccMetaDataWithCoordinateNone) {
  auto accMetaData = AccMetaDataExampleFactory::accMetaDataWithCoordinateNone();
  EXPECT_FALSE(accMetaData.hasCoordinate());
}

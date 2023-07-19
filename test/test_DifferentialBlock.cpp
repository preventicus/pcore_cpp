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

#include <gtest/gtest.h>
#include "DifferentialBlockExampleFactory.h"

////////////////////////////////////////////////////////////////
//                        Test Getter                         //
////////////////////////////////////////////////////////////////

TEST(DifferentialBlockTest, TestGetWithDifferentialBlockWithThreePositiveDifferentialValues) {
  auto differentialBlock = DifferentialBlockExampleFactory::differentialBlockWithThreePositiveDifferentialValues();
  auto differentialValues = DifferentialValuesExampleFactory::differentialValuesWithThreePositiveElements();
  EXPECT_EQ(differentialBlock.getDifferentialValues(), differentialValues);
}

TEST(DifferentialBlockTest, TestGetWithDifferentialBlockNotSet) {
  auto differentialBlock = DifferentialBlockExampleFactory::differentialBlockNotSet();
  auto differentialValues = DifferentialValuesExampleFactory::differentialValuesNotSet();
  EXPECT_EQ(differentialBlock.getDifferentialValues(), differentialValues);
}

////////////////////////////////////////////////////////////////
//                        Test isEqual                        //
////////////////////////////////////////////////////////////////

TEST(DifferentialBlockTest, TestIsEqualWithDifferentialBlockWithThreeMixedDifferentialValues) {
  auto differentialBlock1 = DifferentialBlockExampleFactory::differentialBlockWithThreeMixedDifferentialValues();
  auto differentialBlock2 = DifferentialBlockExampleFactory::differentialBlockWithThreeMixedDifferentialValues();
  EXPECT_TRUE(differentialBlock1 == differentialBlock2);
}

TEST(DifferentialBlockTest, TestIsEqualWithDifferentialBlockWithThreeMixedDifferentialValuesAndDifferentialBlockWithThreeNegativeDifferentialValues) {
  auto differentialBlock1 = DifferentialBlockExampleFactory::differentialBlockWithThreeMixedDifferentialValues();
  auto differentialBlock2 = DifferentialBlockExampleFactory::differentialBlockWithThreeNegativeDifferentialValues();
  EXPECT_FALSE(differentialBlock1 == differentialBlock2);
}

TEST(DifferentialBlockTest, TestIsEqualWithDifferentialBlockNotSet) {
  auto differentialBlock1 = DifferentialBlockExampleFactory::differentialBlockNotSet();
  auto differentialBlock2 = DifferentialBlockExampleFactory::differentialBlockNotSet();
  EXPECT_TRUE(differentialBlock1 == differentialBlock2);
}

TEST(DifferentialBlockTest, TestIsEqualWithDifferentialBlockWithThreeMixedDifferentialValuesAndDifferentialBlockNotSet) {
  auto differentialBlock1 = DifferentialBlockExampleFactory::differentialBlockWithThreeMixedDifferentialValues();
  auto differentialBlock2 = DifferentialBlockExampleFactory::differentialBlockNotSet();
  EXPECT_FALSE(differentialBlock1 == differentialBlock2);
}

TEST(DifferentialBlockTest, TestIsEqualWithDifferentialBlockWithThreeMixedDifferentialValuesAndDifferentialBlockWithOneDifferentialValues) {
  auto differentialBlock1 = DifferentialBlockExampleFactory::differentialBlockWithThreeMixedDifferentialValues();
  auto differentialBlock2 = DifferentialBlockExampleFactory::differentialBlockWithOneDifferentialValues();
  EXPECT_FALSE(differentialBlock1 == differentialBlock2);
}

////////////////////////////////////////////////////////////////
//                      Test isNotEqual                       //
////////////////////////////////////////////////////////////////

TEST(DifferentialBlockTest, TestIsNotEqualWithDifferentialBlockWithThreeMixedDifferentialValues) {
  auto differentialBlock1 = DifferentialBlockExampleFactory::differentialBlockWithThreeMixedDifferentialValues();
  auto differentialBlock2 = DifferentialBlockExampleFactory::differentialBlockWithThreeMixedDifferentialValues();
  EXPECT_FALSE(differentialBlock1 != differentialBlock2);
}

TEST(DifferentialBlockTest, TestIsNotEqualWithdifferentialBlockWithThreeMixedDifferentialValuesAndThreeNegativeDifferentialValues) {
  auto differentialBlock1 = DifferentialBlockExampleFactory::differentialBlockWithThreeMixedDifferentialValues();
  auto differentialBlock2 = DifferentialBlockExampleFactory::differentialBlockWithThreeNegativeDifferentialValues();
  EXPECT_TRUE(differentialBlock1 != differentialBlock2);
}

TEST(DifferentialBlockTest, TestIsNotEqualWithDifferentialBlockNotSet) {
  auto differentialBlock1 = DifferentialBlockExampleFactory::differentialBlockNotSet();
  auto differentialBlock2 = DifferentialBlockExampleFactory::differentialBlockNotSet();
  EXPECT_FALSE(differentialBlock1 != differentialBlock2);
}

TEST(DifferentialBlockTest, TestIsNotEqualWithDifferentialBlockWithThreeMixedDifferentialValuesAndDifferentialBlockNotSet) {
  auto differentialBlock1 = DifferentialBlockExampleFactory::differentialBlockWithThreeMixedDifferentialValues();
  auto differentialBlock2 = DifferentialBlockExampleFactory::differentialBlockNotSet();
  EXPECT_TRUE(differentialBlock1 != differentialBlock2);
}

TEST(DifferentialBlockTest, TestIsNotEqualWithDifferentialBlockWithThreeMixedDifferentialValuesAndDifferentialBlockWithOneDifferentialValues) {
  auto differentialBlock1 = DifferentialBlockExampleFactory::differentialBlockWithThreeMixedDifferentialValues();
  auto differentialBlock2 = DifferentialBlockExampleFactory::differentialBlockWithOneDifferentialValues();
  EXPECT_TRUE(differentialBlock1 != differentialBlock2);
}

////////////////////////////////////////////////////////////////
//                        Test toJson                         //
////////////////////////////////////////////////////////////////

TEST(DifferentialBlockTest, TestToJsonWithDifferentialBlockWithThreePositiveDifferentialValues) {
  auto differentialBlock = DifferentialBlockExampleFactory::differentialBlockWithThreePositiveDifferentialValues();
  auto differentialBlockJson1 = differentialBlock.toJson();
  auto differentialBlockJson2 = DifferentialBlockExampleFactory::buildDifferentialBlockJson(differentialBlock);
  EXPECT_TRUE(differentialBlockJson1.toStyledString() == differentialBlockJson2.toStyledString());
}

TEST(DifferentialBlockTest, TestToJsonWithDifferentialBlockWithThreeMixedDifferentialValues) {
  auto differentialBlock = DifferentialBlockExampleFactory::differentialBlockWithThreeMixedDifferentialValues();
  auto differentialBlockJson1 = differentialBlock.toJson();
  auto differentialBlockJson2 = DifferentialBlockExampleFactory::buildDifferentialBlockJson(differentialBlock);
  EXPECT_TRUE(differentialBlockJson1.toStyledString() == differentialBlockJson2.toStyledString());
}

TEST(DifferentialBlockTest, TestToJsonWithDifferentialBlockWithThreeNegativeDifferentialValues) {
  auto differentialBlock = DifferentialBlockExampleFactory::differentialBlockWithThreeNegativeDifferentialValues();
  auto differentialBlockJson1 = differentialBlock.toJson();
  auto differentialBlockJson2 = DifferentialBlockExampleFactory::buildDifferentialBlockJson(differentialBlock);
  EXPECT_TRUE(differentialBlockJson1.toStyledString() == differentialBlockJson2.toStyledString());
}

TEST(DifferentialBlockTest, TestToJsonWithDifferentialBlockNotSet) {
  auto differentialBlock = DifferentialBlockExampleFactory::differentialBlockNotSet();
  auto differentialBlockJson1 = differentialBlock.toJson();
  auto differentialBlockJson2 = DifferentialBlockExampleFactory::buildDifferentialBlockJson(differentialBlock);
  EXPECT_TRUE(differentialBlockJson1.toStyledString() == differentialBlockJson2.toStyledString());
}

TEST(DifferentialBlockTest, TestToJsonWithDifferentialBlockWithOneDifferentialValues) {
  auto differentialBlock = DifferentialBlockExampleFactory::differentialBlockWithOneDifferentialValues();
  auto differentialBlockJson1 = differentialBlock.toJson();
  auto differentialBlockJson2 = DifferentialBlockExampleFactory::buildDifferentialBlockJson(differentialBlock);
  EXPECT_TRUE(differentialBlockJson1.toStyledString() == differentialBlockJson2.toStyledString());
}

////////////////////////////////////////////////////////////////
//                        Test isSet                          //
////////////////////////////////////////////////////////////////

TEST(DifferentialBlockTest, TestIsSetWithDifferentialBlockWithOneDifferentialValues) {
  auto differentialBlock = DifferentialBlockExampleFactory::differentialBlockWithOneDifferentialValues();
  EXPECT_TRUE(differentialBlock.isSet());
}

TEST(DifferentialBlockTest, TestIsSetWithDifferentialBlockNotSet) {
  auto differentialBlock = DifferentialBlockExampleFactory::differentialBlockNotSet();
  EXPECT_FALSE(differentialBlock.isSet());
}

////////////////////////////////////////////////////////////////
//                       Test serialize                       //
////////////////////////////////////////////////////////////////

TEST(DifferentialBlockTest, TestSerializeNoThrow) {
  auto differentialBlock = DifferentialBlockExampleFactory::differentialBlockWithThreeMixedDifferentialValues();
  DifferentialBlockProtobuf differentialBlockProtobuf;
  EXPECT_NO_THROW(differentialBlock.serialize(&differentialBlockProtobuf));
}

TEST(DifferentialBlockTest, TestSerializeThrowDueToNullPointer) {
  auto differentialBlock = DifferentialBlockExampleFactory::differentialBlockWithThreeMixedDifferentialValues();
  DifferentialBlockProtobuf* differentialBlockProtobuf = nullptr;
  EXPECT_THROW(differentialBlock.serialize(differentialBlockProtobuf), std::invalid_argument);
}

TEST(DifferentialBlockTest, TestSerializeWithDifferentialBlockWithThreePositiveDifferentialValues) {
  auto differentialBlock1 = DifferentialBlockExampleFactory::differentialBlockWithThreePositiveDifferentialValues();
  DifferentialBlockProtobuf differentialBlockProtobuf;
  differentialBlock1.serialize(&differentialBlockProtobuf);
  auto differentialBlock2 = DifferentialBlock(differentialBlockProtobuf);
  EXPECT_TRUE(differentialBlock1 == differentialBlock2);
}

TEST(DifferentialBlockTest, TestSerializeWithDifferentialBlockNotSet) {
  auto differentialBlock1 = DifferentialBlockExampleFactory::differentialBlockNotSet();
  DifferentialBlockProtobuf differentialBlockProtobuf;
  differentialBlock1.serialize(&differentialBlockProtobuf);
  auto differentialBlock2 = DifferentialBlock(differentialBlockProtobuf);
  EXPECT_TRUE(differentialBlock1 == differentialBlock2);
}

TEST(DifferentialBlockTest, TestSerializeWithDifferentialBlockWithOneDifferentialValues) {
  auto differentialBlock1 = DifferentialBlockExampleFactory::differentialBlockWithOneDifferentialValues();
  DifferentialBlockProtobuf differentialBlockProtobuf;
  differentialBlock1.serialize(&differentialBlockProtobuf);
  auto differentialBlock2 = DifferentialBlock(differentialBlockProtobuf);
  EXPECT_TRUE(differentialBlock1 == differentialBlock2);
}

TEST(DifferentialBlockTest, TestSerializeWithDifferentialBlockWithThreeNegativeDifferentialValues) {
  auto differentialBlock1 = DifferentialBlockExampleFactory::differentialBlockWithThreeNegativeDifferentialValues();
  DifferentialBlockProtobuf differentialBlockProtobuf;
  differentialBlock1.serialize(&differentialBlockProtobuf);
  auto differentialBlock2 = DifferentialBlock(differentialBlockProtobuf);
  EXPECT_TRUE(differentialBlock1 == differentialBlock2);
}

TEST(DifferentialBlockTest, TestSerializeWithDifferentialBlockWithThreeMixedDifferentialValues) {
  auto differentialBlock1 = DifferentialBlockExampleFactory::differentialBlockWithThreeMixedDifferentialValues();
  DifferentialBlockProtobuf differentialBlockProtobuf;
  differentialBlock1.serialize(&differentialBlockProtobuf);
  auto differentialBlock2 = DifferentialBlock(differentialBlockProtobuf);
  EXPECT_TRUE(differentialBlock1 == differentialBlock2);
}

////////////////////////////////////////////////////////////////
//                     Test switchDataForm                    //
////////////////////////////////////////////////////////////////

TEST(DifferentialBlockTest, TestSwitchDataFormWithDifferentialBlockNotSet) {
  auto differentialBlock = DifferentialBlockExampleFactory::differentialBlockNotSet();
  EXPECT_THROW(differentialBlock.switchDataForm(), std::runtime_error);
}

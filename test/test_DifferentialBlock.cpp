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

#include <gtest/gtest.h>
#include "DifferentialBlockExampleFactory.h"

class DifferentialBlockTest : public ::testing::Test {
 protected:
  DifferentialValues differentialValuesNormal = DifferentialValuesExampleFactory::differentialValuesNormal();
  DifferentialValues differentialValuesNormalNegative = DifferentialValuesExampleFactory::differentialValuesNormalNegative();
  DifferentialValues differentialValuesEmpty = DifferentialValuesExampleFactory::differentialValuesEmpty();
  DifferentialValues differentialValuesOneElement = DifferentialValuesExampleFactory::differentialValuesOneElement();
};

TEST_F(DifferentialBlockTest, TestGetDifferentialValues) {
  DifferentialBlock differentialBlock = DifferentialBlock(this->differentialValuesNormal);
  EXPECT_EQ(differentialBlock.getDifferentialValues(), this->differentialValuesNormal);
}

TEST_F(DifferentialBlockTest, TestGetEmptyDifferentialValues) {
  DifferentialBlock differentialBlock = DifferentialBlock(this->differentialValuesEmpty);
  EXPECT_EQ(differentialBlock.getDifferentialValues(), this->differentialValuesEmpty);
}

TEST_F(DifferentialBlockTest, CompareEqualBocks) {
  DifferentialBlock differentialBlock1 = DifferentialBlock(this->differentialValuesNormal);
  DifferentialBlock differentialBlock2 = DifferentialBlock(this->differentialValuesNormal);
  EXPECT_TRUE(differentialBlock1.isEqual(differentialBlock2));
}

TEST_F(DifferentialBlockTest, CompareNotEqualBlocks) {
  DifferentialBlock differentialBlock1 = DifferentialBlock(this->differentialValuesNormal);
  DifferentialBlock differentialBlock2 = DifferentialBlock(this->differentialValuesNormalNegative);
  EXPECT_FALSE(differentialBlock1.isEqual(differentialBlock2));
}

TEST_F(DifferentialBlockTest, CompareEmptyWithEmptyBlock) {
  DifferentialBlock differentialBlock1 = DifferentialBlock(this->differentialValuesEmpty);
  DifferentialBlock differentialBlock2 = DifferentialBlock(this->differentialValuesEmpty);
  EXPECT_TRUE(differentialBlock1.isEqual(differentialBlock2));
}

TEST_F(DifferentialBlockTest, CompareEmptyWithNormalBlock) {
  DifferentialBlock differentialBlock1 = DifferentialBlock(this->differentialValuesNormal);
  DifferentialBlock differentialBlock2 = DifferentialBlock(this->differentialValuesEmpty);
  EXPECT_FALSE(differentialBlock1.isEqual(differentialBlock2));
}

TEST_F(DifferentialBlockTest, CompareBlocksWithDifferentSize) {
  DifferentialBlock differentialBlock1 = DifferentialBlock(this->differentialValuesNormal);
  DifferentialBlock differentialBlock2 = DifferentialBlock(this->differentialValuesOneElement);
  EXPECT_FALSE(differentialBlock1.isEqual(differentialBlock2));
}

TEST_F(DifferentialBlockTest, TestSerializeNoThrow) {
  DifferentialBlock differentialBlock = DifferentialBlock(this->differentialValuesNormal);
  ProtobufDifferentialBlock protobufDifferentialBlocks;
  EXPECT_NO_THROW(differentialBlock.serialize(&protobufDifferentialBlocks));
}

TEST_F(DifferentialBlockTest, TestSerializeThrow) {
  DifferentialBlock differentialBlock = DifferentialBlock(this->differentialValuesNormal);
  ProtobufDifferentialBlock* protobufData = nullptr;
  EXPECT_THROW(differentialBlock.serialize(protobufData), std::invalid_argument);
}

TEST_F(DifferentialBlockTest, TestSerialize) {
  DifferentialBlock differentialBlockN1 = DifferentialBlock(this->differentialValuesNormal);
  DifferentialBlock differentialBlockE1 = DifferentialBlock(this->differentialValuesEmpty);
  DifferentialBlock differentialBlockO1 = DifferentialBlock(this->differentialValuesOneElement);
  DifferentialBlock differentialBlockNN1 = DifferentialBlock(this->differentialValuesNormalNegative);
  ProtobufDifferentialBlock protobufDifferentialBlocksN;
  ProtobufDifferentialBlock protobufDifferentialBlocksE;
  ProtobufDifferentialBlock protobufDifferentialBlocksO;
  ProtobufDifferentialBlock protobufDifferentialBlocksNN;
  differentialBlockN1.serialize(&protobufDifferentialBlocksN);
  differentialBlockE1.serialize(&protobufDifferentialBlocksE);
  differentialBlockO1.serialize(&protobufDifferentialBlocksO);
  differentialBlockNN1.serialize(&protobufDifferentialBlocksNN);
  DifferentialBlock differentialBlockN2 = DifferentialBlock(protobufDifferentialBlocksN);
  DifferentialBlock differentialBlockE2 = DifferentialBlock(protobufDifferentialBlocksE);
  DifferentialBlock differentialBlockO2 = DifferentialBlock(protobufDifferentialBlocksO);
  DifferentialBlock differentialBlockNN2 = DifferentialBlock(protobufDifferentialBlocksNN);
  EXPECT_TRUE(differentialBlockN1.isEqual(differentialBlockN2));
  EXPECT_TRUE(differentialBlockE1.isEqual(differentialBlockE2));
  EXPECT_TRUE(differentialBlockO1.isEqual(differentialBlockO2));
  EXPECT_TRUE(differentialBlockNN1.isEqual(differentialBlockNN2));
}

TEST_F(DifferentialBlockTest, TestToJson) {
  DifferentialBlock differentialBlockN1 = DifferentialBlock(this->differentialValuesNormal);
  DifferentialBlock differentialBlockE1 = DifferentialBlock(this->differentialValuesEmpty);
  DifferentialBlock differentialBlockO1 = DifferentialBlock(this->differentialValuesOneElement);
  DifferentialBlock differentialBlockNN1 = DifferentialBlock(this->differentialValuesNormalNegative);
  DifferentialBlockJson differentialBlockJsonN1 = differentialBlockN1.toJson();
  DifferentialBlockJson differentialBlockJsonE1 = differentialBlockE1.toJson();
  DifferentialBlockJson differentialBlockJsonO1 = differentialBlockO1.toJson();
  DifferentialBlockJson differentialBlockJsonNN1 = differentialBlockNN1.toJson();
  DifferentialValuesJson differentialValuesJsonN = DifferentialValuesExampleFactory::buildDifferentialValuesJson(this->differentialValuesNormal);
  DifferentialValuesJson differentialValuesJsonE = DifferentialValuesExampleFactory::buildDifferentialValuesJson(this->differentialValuesEmpty);
  DifferentialValuesJson differentialValuesJsonO = DifferentialValuesExampleFactory::buildDifferentialValuesJson(this->differentialValuesOneElement);
  DifferentialValuesJson differentialValuesJsonNN =
      DifferentialValuesExampleFactory::buildDifferentialValuesJson(this->differentialValuesNormalNegative);
  DifferentialBlockJson differentialBlockJsonN2 = DifferentialBlockExampleFactory::buildDifferentialBlockJson(differentialValuesJsonN);
  DifferentialBlockJson differentialBlockJsonE2 = DifferentialBlockExampleFactory::buildDifferentialBlockJson(differentialValuesJsonE);
  DifferentialBlockJson differentialBlockJsonO2 = DifferentialBlockExampleFactory::buildDifferentialBlockJson(differentialValuesJsonO);
  DifferentialBlockJson differentialBlockJsonNN2 = DifferentialBlockExampleFactory::buildDifferentialBlockJson(differentialValuesJsonNN);
  EXPECT_TRUE(differentialBlockJsonN1 == differentialBlockJsonN2);
  EXPECT_TRUE(differentialBlockJsonE1 == differentialBlockJsonE2);
  EXPECT_TRUE(differentialBlockJsonO1 == differentialBlockJsonO2);
  EXPECT_TRUE(differentialBlockJsonNN1 == differentialBlockJsonNN2);
}
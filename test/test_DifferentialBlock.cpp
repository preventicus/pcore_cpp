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
  DifferentialBlock differentialBlockNormal1 = DifferentialBlockExampleFactory::differentialBlockNormal();
  DifferentialBlock differentialBlockNormal2 = DifferentialBlockExampleFactory::differentialBlockNormal();
  DifferentialBlock differentialBlockWithNegativeValues1 = DifferentialBlockExampleFactory::differentialBlockWithNegativeValues();
  DifferentialBlock differentialBlockWithNegativeValues2 = DifferentialBlockExampleFactory::differentialBlockWithNegativeValues();
  DifferentialBlock differentialBlockWithOneNegativeValue1 = DifferentialBlockExampleFactory::differentialBlockOneNegativeValue();
  DifferentialBlock differentialBlockWithOneNegativeValue2 = DifferentialBlockExampleFactory::differentialBlockOneNegativeValue();
  DifferentialBlock differentialBlockWithOnePositiveValue1 = DifferentialBlockExampleFactory::differentialBlockOnePositiveValue();
  DifferentialBlock differentialBlockWithOnePositiveValue2 = DifferentialBlockExampleFactory::differentialBlockOnePositiveValue();
  DifferentialBlock differentialBlockWith0Value1 = DifferentialBlockExampleFactory::differentialBlock0Value();
  DifferentialBlock differentialBlockWith0Value2 = DifferentialBlockExampleFactory::differentialBlock0Value();
  DifferentialBlock differentialBlockEmpty1 = DifferentialBlockExampleFactory::differentialBlockEmptyValue();
  DifferentialBlock differentialBlockEmpty2 = DifferentialBlockExampleFactory::differentialBlockEmptyValue();
};

TEST_F(DifferentialBlockTest, TestGetDifferentialValues) {
  EXPECT_EQ(this->differentialBlockNormal1.getDifferentialValues(), DifferentialBlockExampleFactory::differentialValuesNormal());
}

TEST_F(DifferentialBlockTest, TestGetWithEmptyDifferentialValues) {
  EXPECT_EQ(this->differentialBlockEmpty1.getDifferentialValues(), DifferentialBlockExampleFactory::differentialValuesEmpty());
}

TEST_F(DifferentialBlockTest, TestGetWithDifferentialValues0) {
  EXPECT_EQ(this->differentialBlockWith0Value1.getDifferentialValues(), DifferentialBlockExampleFactory::differentialValues0());
}

TEST_F(DifferentialBlockTest, TestGetWithNegativeDifferentialValues) {
  EXPECT_EQ(this->differentialBlockWithNegativeValues1.getDifferentialValues(), DifferentialBlockExampleFactory::differentialValuesNormalNeagtive());
}

TEST_F(DifferentialBlockTest, CompareDifferentialValuesEqual) {
  EXPECT_TRUE(this->differentialBlockNormal2.isEqual(this->differentialBlockNormal1));
}

TEST_F(DifferentialBlockTest, CompareDifferentialValuesDifferent) {
  EXPECT_FALSE(this->differentialBlockWithOnePositiveValue1.isEqual(this->differentialBlockWith0Value1));
}

TEST_F(DifferentialBlockTest, CompareDifferentialValuesEmpty) {
  EXPECT_TRUE(this->differentialBlockEmpty1.isEqual(this->differentialBlockEmpty2));
}

TEST_F(DifferentialBlockTest, CompareDifferentialValues0) {
  EXPECT_TRUE(this->differentialBlockWith0Value1.isEqual(this->differentialBlockWith0Value2));
}

TEST_F(DifferentialBlockTest, CompareDiffNegativeDifferentialValues) {
  EXPECT_TRUE(this->differentialBlockWithOneNegativeValue1.isEqual(this->differentialBlockWithOneNegativeValue2));
}

TEST_F(DifferentialBlockTest, TestSerializeAndDeserializeForNormalDifferentialvalues) {
  ProtobufDifferentialBlock protobufDifferentialBlocks;
  this->differentialBlockNormal1.serialize(&protobufDifferentialBlocks);
  DifferentialBlock dBlock = DifferentialBlock(protobufDifferentialBlocks);
  EXPECT_TRUE(this->differentialBlockNormal1.isEqual(dBlock));
}

TEST_F(DifferentialBlockTest, TestSerializeAndDeserializeWithEmptyDifferentialValues) {
  ProtobufDifferentialBlock protobufDifferentialBlocks;
  this->differentialBlockEmpty1.serialize(&protobufDifferentialBlocks);
  DifferentialBlock dBlock = DifferentialBlock(protobufDifferentialBlocks);
  EXPECT_TRUE(this->differentialBlockEmpty1.isEqual(dBlock));
}

TEST_F(DifferentialBlockTest, TestSerializeAndDeserializeWithNegativeAndPositiveDifferentialValues) {
  ProtobufDifferentialBlock protobufDifferentialBlocks;
  this->differentialBlockWithNegativeValues1.serialize(&protobufDifferentialBlocks);
  DifferentialBlock dBlock = DifferentialBlock(protobufDifferentialBlocks);
  EXPECT_TRUE(this->differentialBlockWithNegativeValues1.isEqual(dBlock));
}

TEST_F(DifferentialBlockTest, TestSerializeAndDeserializeWithOneNegativeDifferentialValues) {
  ProtobufDifferentialBlock protobufDifferentialBlocks;
  this->differentialBlockWithOneNegativeValue1.serialize(&protobufDifferentialBlocks);
  DifferentialBlock dBlock = DifferentialBlock(protobufDifferentialBlocks);
  EXPECT_TRUE(this->differentialBlockWithOneNegativeValue1.isEqual(dBlock));
}

TEST_F(DifferentialBlockTest, TestSerializeAndDeserializeWithOnePositiveDifferentialValues) {
  ProtobufDifferentialBlock protobufDifferentialBlocks;
  this->differentialBlockWithOnePositiveValue1.serialize(&protobufDifferentialBlocks);
  DifferentialBlock dBlock = DifferentialBlock(protobufDifferentialBlocks);
  EXPECT_TRUE(this->differentialBlockWithOnePositiveValue1.isEqual(dBlock));
}

TEST_F(DifferentialBlockTest, CompareTwoDeserializedDifferentialValues) {
  ProtobufDifferentialBlock protobufDifferentialBlocks1;
  this->differentialBlockWithNegativeValues1.serialize(&protobufDifferentialBlocks1);
  ProtobufDifferentialBlock protobufDifferentialBlocks2;
  this->differentialBlockWithNegativeValues2.serialize(&protobufDifferentialBlocks2);
  DifferentialBlock baseDBlock = DifferentialBlock(protobufDifferentialBlocks1);
  DifferentialBlock comparableDBlock = DifferentialBlock(protobufDifferentialBlocks2);
  EXPECT_TRUE(baseDBlock.isEqual(comparableDBlock));
}

TEST_F(DifferentialBlockTest, CheckDifferentialBlockPtr) {
  ProtobufDifferentialBlock protobufData;
  this->differentialBlockNormal1.serialize(&protobufData);
  DifferentialBlock differentialBlock = DifferentialBlock(protobufData);
  ProtobufDifferentialBlock* protobufDataPtr = &protobufData;
  DifferentialBlock* ptr = &differentialBlock;
  EXPECT_FALSE(ptr == nullptr);
  EXPECT_FALSE(protobufDataPtr == nullptr);
}

TEST_F(DifferentialBlockTest, CheckDifferentialBlockNullPtr) {
  ProtobufDifferentialBlock* protobufData = nullptr;
  EXPECT_THROW(this->differentialBlockNormal1.serialize(protobufData), std::invalid_argument);
}
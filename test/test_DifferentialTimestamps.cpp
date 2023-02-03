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
#include "DifferentialTimestamps.h"

class DifferentialTimestampsTest : public ::testing::Test {
 protected:
  DifferentialTimestamps differentialTimestampsWithNormalTimestamps1;
  DifferentialTimestamps differentialTimestampsWithNormalTimestamps2;
  DifferentialTimestamps differentialTimestampsWith0Timestamps1;
  DifferentialTimestamps differentialTimestampsWith0Timestamps2;
  DifferentialTimestamps differentialTimestampsEmptyTimestamps1;
  DifferentialTimestamps differentialTimestampsEmptyTimestamps2;
  uint64_t normalFirstTimestamp_ms = 10;
  uint64_t zeroFirstTimestamp_ms = 0;
  std::vector<uint32_t> normalBlockIntervals_ms = {0, 113, 23, 34};  // first block_intervall[0] is always null - one loop less is needed
  std::vector<uint32_t> zeroBlockIntervals_ms = {0};                 // first block_intervall[0] is always null - one loop less is needed
  std::vector<uint32_t> emptyBlockIntervals_ms = {};
  std::vector<uint32_t> normalTimestampsIntervals_ms = {134, 31, 124};
  std::vector<uint32_t> zeroTimestampsIntervals_ms = {0};
  std::vector<uint32_t> emptyTimestampsIntervals_ms = {};

  virtual void SetUp() {
    this->differentialTimestampsWithNormalTimestamps1 =
        DifferentialTimestamps(this->normalFirstTimestamp_ms, this->normalBlockIntervals_ms, this->normalTimestampsIntervals_ms);
    this->differentialTimestampsWithNormalTimestamps2 =
        DifferentialTimestamps(this->normalFirstTimestamp_ms, this->normalBlockIntervals_ms, this->normalTimestampsIntervals_ms);
    this->differentialTimestampsWith0Timestamps1 =
        DifferentialTimestamps(this->zeroFirstTimestamp_ms, this->zeroBlockIntervals_ms, this->zeroTimestampsIntervals_ms);
    this->differentialTimestampsWith0Timestamps2 =
        DifferentialTimestamps(this->zeroFirstTimestamp_ms, this->zeroBlockIntervals_ms, this->zeroTimestampsIntervals_ms);
    this->differentialTimestampsEmptyTimestamps1 =
        DifferentialTimestamps(this->zeroFirstTimestamp_ms, this->emptyBlockIntervals_ms, this->emptyTimestampsIntervals_ms);
    this->differentialTimestampsEmptyTimestamps2 =
        DifferentialTimestamps(this->zeroFirstTimestamp_ms, this->emptyBlockIntervals_ms, this->emptyTimestampsIntervals_ms);
  }
};

TEST_F(DifferentialTimestampsTest, TestGetMethodTimestampsContainer) {
  EXPECT_EQ(this->differentialTimestampsWithNormalTimestamps1.getFirstTimestamp(), this->normalFirstTimestamp_ms);
  EXPECT_EQ(this->differentialTimestampsWithNormalTimestamps1.getBlockIntervals(), this->normalBlockIntervals_ms);
  EXPECT_EQ(this->differentialTimestampsWithNormalTimestamps1.getTimestampsIntervals(), this->normalTimestampsIntervals_ms);
}

TEST_F(DifferentialTimestampsTest, TestGetTimestampsContainerFirstTimestamp0) {
  EXPECT_EQ(this->differentialTimestampsWith0Timestamps1.getFirstTimestamp(), this->zeroFirstTimestamp_ms);
  EXPECT_EQ(this->differentialTimestampsWith0Timestamps1.getBlockIntervals(), this->zeroBlockIntervals_ms);
  EXPECT_EQ(this->differentialTimestampsWith0Timestamps1.getTimestampsIntervals(), this->zeroTimestampsIntervals_ms);
}

TEST_F(DifferentialTimestampsTest, TestGetEmptyTimestampsContainer) {
  EXPECT_EQ(this->differentialTimestampsEmptyTimestamps1.getFirstTimestamp(), this->zeroFirstTimestamp_ms);
  EXPECT_EQ(this->differentialTimestampsEmptyTimestamps1.getBlockIntervals(), this->emptyBlockIntervals_ms);
  EXPECT_EQ(this->differentialTimestampsEmptyTimestamps1.getTimestampsIntervals(), this->emptyTimestampsIntervals_ms);
}

TEST_F(DifferentialTimestampsTest, CompareEqualTimestamps) {
  EXPECT_TRUE(this->differentialTimestampsWithNormalTimestamps1.isEqual(this->differentialTimestampsWithNormalTimestamps2));
}

TEST_F(DifferentialTimestampsTest, CompareEqualZeroTimestamps) {
  EXPECT_TRUE(this->differentialTimestampsWith0Timestamps1.isEqual(this->differentialTimestampsWith0Timestamps2));
}

TEST_F(DifferentialTimestampsTest, CompareEqualEmptyTimestamps) {
  EXPECT_TRUE(this->differentialTimestampsEmptyTimestamps1.isEqual(this->differentialTimestampsEmptyTimestamps2));
}

TEST_F(DifferentialTimestampsTest, CompareDifferentTimestampsIntervals) {
  EXPECT_FALSE(this->differentialTimestampsWithNormalTimestamps1.isEqual(this->differentialTimestampsWith0Timestamps1));
}

TEST_F(DifferentialTimestampsTest, TestSerializeAndDeserializeEqualTimestamps) {
  ProtobufDifferentialTimestampContainer protobufDifferentialTimestampContainer;
  this->differentialTimestampsWithNormalTimestamps1.serialize(&protobufDifferentialTimestampContainer);
  DifferentialTimestamps differentialTimestamps = DifferentialTimestamps(protobufDifferentialTimestampContainer);
  EXPECT_TRUE(this->differentialTimestampsWithNormalTimestamps1.isEqual(differentialTimestamps));
}

TEST_F(DifferentialTimestampsTest, TestSerializeAndDeserializeBetweenTwoDifferentTimestamps) {
  ProtobufDifferentialTimestampContainer protobufDifferentialTimestampContainer1;
  this->differentialTimestampsWithNormalTimestamps1.serialize(&protobufDifferentialTimestampContainer1);
  ProtobufDifferentialTimestampContainer protobufDifferentialTimestampContainer2;
  this->differentialTimestampsWith0Timestamps1.serialize(&protobufDifferentialTimestampContainer2);
  DifferentialTimestamps baseDifferentialTimestamps = DifferentialTimestamps(protobufDifferentialTimestampContainer1);
  DifferentialTimestamps comparableDifferentialTimestamps = DifferentialTimestamps(protobufDifferentialTimestampContainer2);
  EXPECT_FALSE(baseDifferentialTimestamps.isEqual(comparableDifferentialTimestamps));
}

TEST_F(DifferentialTimestampsTest, TestSerializeAndDeserializeBetweenTwoTimestamps) {
  ProtobufDifferentialTimestampContainer protobufDifferentialTimestampContainer1;
  this->differentialTimestampsWithNormalTimestamps1.serialize(&protobufDifferentialTimestampContainer1);
  ProtobufDifferentialTimestampContainer protobufDifferentialTimestampContainer2;
  this->differentialTimestampsWithNormalTimestamps2.serialize(&protobufDifferentialTimestampContainer2);
  DifferentialTimestamps baseDifferentialTimestamps = DifferentialTimestamps(protobufDifferentialTimestampContainer1);
  DifferentialTimestamps comparableDifferentialTimestamps = DifferentialTimestamps(protobufDifferentialTimestampContainer2);
  EXPECT_TRUE(baseDifferentialTimestamps.isEqual(comparableDifferentialTimestamps));
}

TEST_F(DifferentialTimestampsTest, TestSerializeAndDeserializeBetweenTwoZeroTimestamps) {
  ProtobufDifferentialTimestampContainer protobufDifferentialTimestampContainer1;
  this->differentialTimestampsWith0Timestamps1.serialize(&protobufDifferentialTimestampContainer1);
  ProtobufDifferentialTimestampContainer protobufDifferentialTimestampContainer2;
  this->differentialTimestampsWith0Timestamps2.serialize(&protobufDifferentialTimestampContainer2);
  DifferentialTimestamps baseDifferentialTimestamps = DifferentialTimestamps(protobufDifferentialTimestampContainer1);
  DifferentialTimestamps comparableDifferentialTimestamps = DifferentialTimestamps(protobufDifferentialTimestampContainer2);
  EXPECT_TRUE(baseDifferentialTimestamps.isEqual(comparableDifferentialTimestamps));
}

TEST_F(DifferentialTimestampsTest, TestSerializeAndDeserializeBetweenTwoEmptyTimestamps) {
  ProtobufDifferentialTimestampContainer protobufDifferentialTimestampContainer1;
  this->differentialTimestampsEmptyTimestamps1.serialize(&protobufDifferentialTimestampContainer1);
  ProtobufDifferentialTimestampContainer protobufDifferentialTimestampContainer2;
  this->differentialTimestampsEmptyTimestamps2.serialize(&protobufDifferentialTimestampContainer2);
  DifferentialTimestamps baseDifferentialTimestamps = DifferentialTimestamps(protobufDifferentialTimestampContainer1);
  DifferentialTimestamps comparableDifferentialTimestamps = DifferentialTimestamps(protobufDifferentialTimestampContainer2);
  EXPECT_TRUE(baseDifferentialTimestamps.isEqual(comparableDifferentialTimestamps));
}

TEST_F(DifferentialTimestampsTest, TestCalculateFirstTimestampInBlock) {
  uint32_t blockIdx = 2;
  EXPECT_EQ(this->differentialTimestampsWithNormalTimestamps1.calculateFirstTimestampInBlock(blockIdx), 146);
}

TEST_F(DifferentialTimestampsTest, TestCalculateLastTimestampInBlock) {
  uint32_t blockIdx = 2;
  uint32_t firstTimestampInBlock = 146;  // reference to the UnitTest before
  std::vector<int32_t> diffValues = {30, 32, 54};
  DifferentialBlock differentialBlock = DifferentialBlock(diffValues);
  EXPECT_EQ(this->differentialTimestampsWithNormalTimestamps1.calculateLastTimestampInBlock(blockIdx, firstTimestampInBlock, differentialBlock), 518);
}

TEST_F(DifferentialTimestampsTest, TestCalculateLastTimestampInBlock0) {
  uint32_t blockIdx = 0;
  uint32_t firstTimestampInBlock = 150;
  std::vector<int32_t> diffValues = {30, 32, 54};
  DifferentialBlock differentialBlock = DifferentialBlock(diffValues);
  EXPECT_EQ(this->differentialTimestampsWithNormalTimestamps1.calculateLastTimestampInBlock(blockIdx, firstTimestampInBlock, differentialBlock), 552);
}

TEST_F(DifferentialTimestampsTest, TestCalculateLastTimestampInBlockException) {
  uint32_t blockIdx = 10;
  std::vector<int32_t> diffValues = {30, 32, 54};
  DifferentialBlock differentialBlock = DifferentialBlock(diffValues);
  EXPECT_THROW(this->differentialTimestampsWithNormalTimestamps1.calculateFirstTimestampInBlock(blockIdx), std::invalid_argument);
}

TEST_F(DifferentialTimestampsTest, CheckDifferentialTimestampsPtr) {
  ProtobufDifferentialTimestampContainer protobufData;
  this->differentialTimestampsWithNormalTimestamps1.serialize(&protobufData);
  DifferentialTimestamps timestampContainer = DifferentialTimestamps(protobufData);
  ProtobufDifferentialTimestampContainer* protobufDataPtr = &protobufData;
  DifferentialTimestamps* ptr = &timestampContainer;
  EXPECT_FALSE(ptr == nullptr);
  EXPECT_FALSE(protobufDataPtr == nullptr);
}

TEST_F(DifferentialTimestampsTest, CheckDifferentialTimestampsNullPtr) {
  ProtobufDifferentialTimestampContainer* protobufData = nullptr;
  EXPECT_THROW(this->differentialTimestampsWithNormalTimestamps1.serialize(protobufData), std::invalid_argument);
}
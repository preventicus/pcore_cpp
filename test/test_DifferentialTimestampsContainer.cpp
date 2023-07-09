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
#include "DifferentialTimestampsContainerExampleFactory.h"
#include "IntervalsExampleFactory.h"
#include "UnixTimestampsExampleFactory.h"

TEST(DifferentialTimestampsTest, TestGetFirstTimestamp) {
  auto firstTimestamp1_ms = UnixTimestampsExampleFactory::firstTimestamp_ms();
  auto differentialTimestampsContainer = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithThreeBlocks();
  auto firstTimestamp2_ms = differentialTimestampsContainer.getFirstUnixTimestamp();
  EXPECT_EQ(firstTimestamp1_ms, firstTimestamp2_ms);
}

TEST(DifferentialTimestampsTest, TestGetBlockIntervals) {
  auto blockIntervals1 = IntervalsExampleFactory::blockIntervalsWithThreeMixedIntervals();
  auto differentialTimestampsContainer = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithThreeBlocks();
  auto blockIntervals2 = differentialTimestampsContainer.getBlockIntervals();
  EXPECT_EQ(blockIntervals1, blockIntervals2);
}

TEST(DifferentialTimestampsTest, TestGetTimestampsIntervals) {
  auto timestampsIntervals1 = IntervalsExampleFactory::timestampsIntervalsWithThreeZeroIntervals();
  auto differentialTimestampsContainer = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithThreeBlocks();
  auto timestampsIntervals2 = differentialTimestampsContainer.getTimestampsIntervals();
  EXPECT_EQ(timestampsIntervals1, timestampsIntervals2);
}

TEST(DifferentialTimestampsTest, TestIsEqualWithDifferentialTimestampsContainerWithThreeBlocks) {
  auto differentialTimestampsContainer1 = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithThreeBlocks();
  auto differentialTimestampsContainer2 = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithThreeBlocks();
  EXPECT_TRUE(differentialTimestampsContainer1 == differentialTimestampsContainer2);
}

TEST(DifferentialTimestampsTest, TestIsEqualWithDifferentialTimestampsContainerEmpty) {
  auto differentialTimestampsContainer1 = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerEmpty();
  auto differentialTimestampsContainer2 = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerEmpty();
  EXPECT_TRUE(differentialTimestampsContainer1 == differentialTimestampsContainer2);
}

TEST(DifferentialTimestampsTest, TestIsEqualWithDifferentialTimestampsContainerEmptyAndDifferentialTimestampsContainerWithThreeBlocks) {
  auto differentialTimestampsContainer1 = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerEmpty();
  auto differentialTimestampsContainer2 = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithThreeBlocks();
  EXPECT_FALSE(differentialTimestampsContainer1 == differentialTimestampsContainer2);
}

TEST(DifferentialTimestampsTest, TestIsEqualWithDifferentialTimestampsContainerWithTwoBlocksAndDifferentialTimestampsContainerWithThreeBlocks) {
  auto differentialTimestampsContainer1 = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithTwoBlocks();
  auto differentialTimestampsContainer2 = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithThreeBlocks();
  EXPECT_FALSE(differentialTimestampsContainer1 == differentialTimestampsContainer2);
}

TEST(DifferentialTimestampsTest, TestIsEqualWithDifferentialTimestampsContainerWithBigBlocksAndDifferentialTimestampsContainerWithThreeBlocks) {
  auto differentialTimestampsContainer1 = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithBigBlocks();
  auto differentialTimestampsContainer2 = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithThreeBlocks();
  EXPECT_FALSE(differentialTimestampsContainer1 == differentialTimestampsContainer2);
}

TEST(DifferentialTimestampsTest, TestIsNotEqualWithDifferentialTimestampsContainerWithThreeBlocks) {
  auto differentialTimestampsContainer1 = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithThreeBlocks();
  auto differentialTimestampsContainer2 = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithThreeBlocks();
  EXPECT_FALSE(differentialTimestampsContainer1 != differentialTimestampsContainer2);
}

TEST(DifferentialTimestampsTest, TestIsNotEqualWithDifferentialTimestampsContainerEmpty) {
  auto differentialTimestampsContainer1 = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerEmpty();
  auto differentialTimestampsContainer2 = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerEmpty();
  EXPECT_FALSE(differentialTimestampsContainer1 != differentialTimestampsContainer2);
}

TEST(DifferentialTimestampsTest, TestIsNotEqualWithDifferentialTimestampsContainerEmptyAndDifferentialTimestampsContainerWithThreeBlocks) {
  auto differentialTimestampsContainer1 = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerEmpty();
  auto differentialTimestampsContainer2 = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithThreeBlocks();
  EXPECT_TRUE(differentialTimestampsContainer1 != differentialTimestampsContainer2);
}

TEST(DifferentialTimestampsTest, TestIsNotEqualWithDifferentialTimestampsContainerWithTwoBlocksAndDifferentialTimestampsContainerWithThreeBlocks) {
  auto differentialTimestampsContainer1 = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithTwoBlocks();
  auto differentialTimestampsContainer2 = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithThreeBlocks();
  EXPECT_TRUE(differentialTimestampsContainer1 != differentialTimestampsContainer2);
}

TEST(DifferentialTimestampsTest, TestIsNotEqualWithDifferentialTimestampsContainerWithBigBlocksAndDifferentialTimestampsContainerWithThreeBlocks) {
  auto differentialTimestampsContainer1 = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithBigBlocks();
  auto differentialTimestampsContainer2 = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithThreeBlocks();
  EXPECT_TRUE(differentialTimestampsContainer1 != differentialTimestampsContainer2);
}

TEST(DifferentialTimestampsTest, TestSerializeWithDifferentialTimestampsContainerWithThreeBlocks) {
  auto differentialTimestampsContainer1 = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithThreeBlocks();
  ProtobufDifferentialTimestampContainer protobufDifferentialTimestampContainer;
  differentialTimestampsContainer1.serialize(&protobufDifferentialTimestampContainer);
  auto differentialTimestampsContainer2 = DifferentialTimestampsContainer(protobufDifferentialTimestampContainer);
  EXPECT_TRUE(differentialTimestampsContainer1 == differentialTimestampsContainer2);
}

TEST(DifferentialTimestampsTest, TestSerializeWithDifferentialTimestampsContainerEmpty) {
  auto differentialTimestampsContainer1 = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerEmpty();
  ProtobufDifferentialTimestampContainer protobufDifferentialTimestampContainer;
  differentialTimestampsContainer1.serialize(&protobufDifferentialTimestampContainer);
  auto differentialTimestampsContainer2 = DifferentialTimestampsContainer(protobufDifferentialTimestampContainer);
  EXPECT_TRUE(differentialTimestampsContainer1 == differentialTimestampsContainer2);
}

TEST(DifferentialTimestampsTest, TestSerializeNoThrow) {
  auto differentialTimestampsContainer = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerEmpty();
  ProtobufDifferentialTimestampContainer protobufData;
  EXPECT_NO_THROW(differentialTimestampsContainer.serialize(&protobufData));
}

TEST(DifferentialTimestampsTest, TestSerializeThrow) {
  auto differentialTimestampsContainer = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerEmpty();
  ProtobufDifferentialTimestampContainer* protobufData = nullptr;
  EXPECT_THROW(differentialTimestampsContainer.serialize(protobufData), std::invalid_argument);
}

TEST(DifferentialTimestampsTest, TestToJsonWithDifferentialTimestampsContainerEmpty) {
  auto differentialTimestampsContainer = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerEmpty();
  auto differentialTimestampsContainerJson1 =
      DifferentialTimestampsContainerExampleFactory::buildDifferentialTimestampsContainerJson(differentialTimestampsContainer);
  auto differentialTimestampsContainerJson2 = differentialTimestampsContainer.toJson();
  EXPECT_TRUE(differentialTimestampsContainerJson1.toStyledString() == differentialTimestampsContainerJson2.toStyledString());
}

TEST(DifferentialTimestampsTest, TestToJsonWithDifferentialTimestampsContainerWithThreeBlocks) {
  auto differentialTimestampsContainer = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithThreeBlocks();
  auto differentialTimestampsContainerJson1 =
      DifferentialTimestampsContainerExampleFactory::buildDifferentialTimestampsContainerJson(differentialTimestampsContainer);
  auto differentialTimestampsContainerJson2 = differentialTimestampsContainer.toJson();
  EXPECT_TRUE(differentialTimestampsContainerJson1.toStyledString() == differentialTimestampsContainerJson2.toStyledString());
}

TEST(DifferentialTimestampsTest, TestToJsonWithDifferentialTimestampsContainerWithTwoBlocks) {
  auto differentialTimestampsContainer = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithTwoBlocks();
  auto differentialTimestampsContainerJson1 =
      DifferentialTimestampsContainerExampleFactory::buildDifferentialTimestampsContainerJson(differentialTimestampsContainer);
  auto differentialTimestampsContainerJson2 = differentialTimestampsContainer.toJson();
  EXPECT_TRUE(differentialTimestampsContainerJson1.toStyledString() == differentialTimestampsContainerJson2.toStyledString());
}

TEST(DifferentialTimestampsTest, TestToJsonWithDifferentialTimestampsContainerWithBigBlocks) {
  auto differentialTimestampsContainer = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithBigBlocks();
  auto differentialTimestampsContainerJson1 =
      DifferentialTimestampsContainerExampleFactory::buildDifferentialTimestampsContainerJson(differentialTimestampsContainer);
  auto differentialTimestampsContainerJson2 = differentialTimestampsContainer.toJson();
  EXPECT_TRUE(differentialTimestampsContainerJson1.toStyledString() == differentialTimestampsContainerJson2.toStyledString());
}

TEST(DifferentialTimestampsTest, TestCalculateFirstUnixTimestampInBlockWithDifferentialTimestampsContainerWithThreeBlocks) {
  auto differentialTimestampsContainer = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithThreeBlocks();
  auto firstUnixTimestamp_ms = differentialTimestampsContainer.getFirstUnixTimestamp();
  auto blockIntervals = differentialTimestampsContainer.getBlockIntervals();

  BlockIdx blockIdx0 = 0;
  auto firstUnixTimestampInBlock0 = firstUnixTimestamp_ms;
  EXPECT_EQ(differentialTimestampsContainer.calculateFirstUnixTimestampInBlock(blockIdx0), firstUnixTimestampInBlock0);

  BlockIdx blockIdx1 = 1;
  auto firstUnixTimestampInBlock1 = firstUnixTimestamp_ms + blockIntervals[1];
  EXPECT_EQ(differentialTimestampsContainer.calculateFirstUnixTimestampInBlock(blockIdx1), firstUnixTimestampInBlock1);

  BlockIdx blockIdx2 = 2;
  auto firstUnixTimestampInBlock2 = firstUnixTimestamp_ms + blockIntervals[1] + blockIntervals[2];
  EXPECT_EQ(differentialTimestampsContainer.calculateFirstUnixTimestampInBlock(blockIdx2), firstUnixTimestampInBlock2);
}

TEST(DifferentialTimestampsTest, TestCalculateFirstUnixTimestampInBlockWithDifferentialTimestampsContainerEmpty) {
  auto differentialTimestampsContainer = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerEmpty();
  BlockIdx blockIdx = 0;
  EXPECT_THROW(differentialTimestampsContainer.calculateFirstUnixTimestampInBlock(blockIdx), std::invalid_argument);
}

TEST(DifferentialTimestampsTest, TestCalculateFirstUnixTimestampInBlockThrowInvalidArgument) {
  auto differentialTimestampsContainer = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithThreeBlocks();
  BlockIdx blockIdx = differentialTimestampsContainer.getBlockIntervals().size() + 1;
  EXPECT_THROW(differentialTimestampsContainer.calculateFirstUnixTimestampInBlock(blockIdx), std::invalid_argument);
}

TEST(DifferentialTimestampsTest, TestCalculateLastUnixTimestampInBlockWithDifferentialTimestampsContainerWithThreeBlocks) {
  auto differentialTimestampsContainer = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithThreeBlocks();
  auto differentialBlock = DifferentialBlockExampleFactory::differentialBlockWithThreeMixedDifferentialValues();
  auto timestampsIntervals = differentialTimestampsContainer.getTimestampsIntervals();

  BlockIdx blockIdx0 = 0;
  auto firstTimestampInBlock0 = differentialTimestampsContainer.calculateFirstUnixTimestampInBlock(blockIdx0);
  auto lastTimeStampInBlock0 = firstTimestampInBlock0 + differentialBlock.getDifferentialValues().size() * timestampsIntervals[blockIdx0];
  EXPECT_EQ(differentialTimestampsContainer.calculateLastUnixTimestampInBlock(blockIdx0, firstTimestampInBlock0, differentialBlock),
            lastTimeStampInBlock0);

  BlockIdx blockIdx1 = 1;
  auto firstTimestampInBlock1 = differentialTimestampsContainer.calculateFirstUnixTimestampInBlock(blockIdx1);
  auto lastTimeStampInBlock1 = firstTimestampInBlock1 + differentialBlock.getDifferentialValues().size() * timestampsIntervals[blockIdx1];
  EXPECT_EQ(differentialTimestampsContainer.calculateLastUnixTimestampInBlock(blockIdx1, firstTimestampInBlock1, differentialBlock),
            lastTimeStampInBlock1);

  BlockIdx blockIdx2 = 2;
  auto firstTimestampInBlock2 = differentialTimestampsContainer.calculateFirstUnixTimestampInBlock(blockIdx2);
  auto lastTimeStampInBlock2 = firstTimestampInBlock2 + differentialBlock.getDifferentialValues().size() * timestampsIntervals[blockIdx2];
  EXPECT_EQ(differentialTimestampsContainer.calculateLastUnixTimestampInBlock(blockIdx2, firstTimestampInBlock2, differentialBlock),
            lastTimeStampInBlock2);
}

TEST(DifferentialTimestampsTest, TestCalculateLastUnixTimestampInBlockWithDifferentialTimestampsContainerEmpty) {
  auto differentialTimestampsContainer = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerEmpty();
  auto differentialBlock = DifferentialBlockExampleFactory::differentialBlockWithEmptyDifferentialValues();
  BlockIdx blockIdx = 0;
  auto firstUnixTimestampInBlock = 0;
  EXPECT_THROW(differentialTimestampsContainer.calculateLastUnixTimestampInBlock(blockIdx, firstUnixTimestampInBlock, differentialBlock),
               std::invalid_argument);
}

TEST(DifferentialTimestampsTest, TestCalculateLastUnixTimestampInBlockThrowInvalidArgument) {
  auto differentialTimestampsContainer = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithThreeBlocks();
  auto differentialBlock = DifferentialBlockExampleFactory::differentialBlockWithThreeMixedDifferentialValues();
  BlockIdx blockIdx = differentialTimestampsContainer.getBlockIntervals().size() + 1;
  auto firstUnixTimestampInBlock = 0;
  EXPECT_THROW(differentialTimestampsContainer.calculateLastUnixTimestampInBlock(blockIdx, firstUnixTimestampInBlock, differentialBlock),
               std::invalid_argument);
}

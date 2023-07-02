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

class DifferentialTimestampsTest : public ::testing::Test {
 protected:
};

TEST_F(DifferentialTimestampsTest, TestGetFirstTimestamp) {
  UnixTimestamp firstTimestamp1_ms = UnixTimestampsExampleFactory::firstTimestamp_ms();
  DifferentialTimestampsContainer differentialTimestampsContainer =
      DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithThreeBlocks();
  UnixTimestamp firstTimestamp2_ms = differentialTimestampsContainer.getFirstUnixTimestamp();
  EXPECT_EQ(firstTimestamp1_ms, firstTimestamp2_ms);
}

TEST_F(DifferentialTimestampsTest, TestGetBlockIntervals) {
  BlockIntervals blockIntervals1 = IntervalsExampleFactory::blockIntervalsWithThreeMixedIntervals();
  DifferentialTimestampsContainer differentialTimestampsContainer =
      DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithThreeBlocks();
  BlockIntervals blockIntervals2 = differentialTimestampsContainer.getBlockIntervals();
  EXPECT_EQ(blockIntervals1, blockIntervals2);
}

TEST_F(DifferentialTimestampsTest, TestGetTimestampsIntervals) {
  TimestampsIntervals timestampsIntervals1 = IntervalsExampleFactory::timestampsIntervalsWithThreeZeroIntervals();
  DifferentialTimestampsContainer differentialTimestampsContainer =
      DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithThreeBlocks();
  TimestampsIntervals timestampsIntervals2 = differentialTimestampsContainer.getTimestampsIntervals();
  EXPECT_EQ(timestampsIntervals1, timestampsIntervals2);
}

TEST_F(DifferentialTimestampsTest, TestIsEqualWithDifferentialTimestampsContainerWithThreeBlocks) {
  DifferentialTimestampsContainer differentialTimestampsContainer1 =
      DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithThreeBlocks();
  DifferentialTimestampsContainer differentialTimestampsContainer2 =
      DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithThreeBlocks();
  EXPECT_TRUE(differentialTimestampsContainer1.isEqual(differentialTimestampsContainer2));
}

TEST_F(DifferentialTimestampsTest, TestIsEqualWithDifferentialTimestampsContainerEmpty) {
  DifferentialTimestampsContainer differentialTimestampsContainer1 =
      DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerEmpty();
  DifferentialTimestampsContainer differentialTimestampsContainer2 =
      DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerEmpty();
  EXPECT_TRUE(differentialTimestampsContainer1.isEqual(differentialTimestampsContainer2));
}

TEST_F(DifferentialTimestampsTest, TestIsEqualWithDifferentialTimestampsContainerEmptyAndDifferentialTimestampsContainerWithThreeBlocks) {
  DifferentialTimestampsContainer differentialTimestampsContainer1 =
      DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerEmpty();
  DifferentialTimestampsContainer differentialTimestampsContainer2 =
      DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithThreeBlocks();
  EXPECT_FALSE(differentialTimestampsContainer1.isEqual(differentialTimestampsContainer2));
}

TEST_F(DifferentialTimestampsTest, TestIsEqualWithDifferentialTimestampsContainerWithTwoBlocksAndDifferentialTimestampsContainerWithThreeBlocks) {
  DifferentialTimestampsContainer differentialTimestampsContainer1 =
      DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithTwoBlocks();
  DifferentialTimestampsContainer differentialTimestampsContainer2 =
      DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithThreeBlocks();
  EXPECT_FALSE(differentialTimestampsContainer1.isEqual(differentialTimestampsContainer2));
}

TEST_F(DifferentialTimestampsTest, TestIsEqualWithDifferentialTimestampsContainerWithBigBlocksAndDifferentialTimestampsContainerWithThreeBlocks) {
  DifferentialTimestampsContainer differentialTimestampsContainer1 =
      DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithBigBlocks();
  DifferentialTimestampsContainer differentialTimestampsContainer2 =
      DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithThreeBlocks();
  EXPECT_FALSE(differentialTimestampsContainer1.isEqual(differentialTimestampsContainer2));
}

TEST_F(DifferentialTimestampsTest, TestSerializeWithDifferentialTimestampsContainerWithThreeBlocks) {
  DifferentialTimestampsContainer differentialTimestampsContainer1 =
      DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithThreeBlocks();
  ProtobufDifferentialTimestampContainer protobufDifferentialTimestampContainer;
  differentialTimestampsContainer1.serialize(&protobufDifferentialTimestampContainer);
  DifferentialTimestampsContainer differentialTimestampsContainer2 = DifferentialTimestampsContainer(protobufDifferentialTimestampContainer);
  EXPECT_TRUE(differentialTimestampsContainer1.isEqual(differentialTimestampsContainer2));
}

TEST_F(DifferentialTimestampsTest, TestSerializeWithDifferentialTimestampsContainerEmpty) {
  DifferentialTimestampsContainer differentialTimestampsContainer1 =
      DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerEmpty();
  ProtobufDifferentialTimestampContainer protobufDifferentialTimestampContainer;
  differentialTimestampsContainer1.serialize(&protobufDifferentialTimestampContainer);
  DifferentialTimestampsContainer differentialTimestampsContainer2 = DifferentialTimestampsContainer(protobufDifferentialTimestampContainer);
  EXPECT_TRUE(differentialTimestampsContainer1.isEqual(differentialTimestampsContainer2));
}

TEST_F(DifferentialTimestampsTest, TestSerializeNoThrow) {
  DifferentialTimestampsContainer differentialTimestampsContainer =
      DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerEmpty();
  ProtobufDifferentialTimestampContainer protobufData;
  EXPECT_NO_THROW(differentialTimestampsContainer.serialize(&protobufData));
}

TEST_F(DifferentialTimestampsTest, TestSerializeThrow) {
  DifferentialTimestampsContainer differentialTimestampsContainer =
      DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerEmpty();
  ProtobufDifferentialTimestampContainer* protobufData = nullptr;
  EXPECT_THROW(differentialTimestampsContainer.serialize(protobufData), std::invalid_argument);
}

TEST_F(DifferentialTimestampsTest, TestToJsonWithDifferentialTimestampsContainerEmpty) {
  DifferentialTimestampsContainer differentialTimestampsContainer =
      DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerEmpty();
  DifferentialTimestampsContainerJson differentialTimestampsContainerJson1 =
      DifferentialTimestampsContainerExampleFactory::buildDifferentialTimestampsContainerJson(differentialTimestampsContainer);
  DifferentialTimestampsContainerJson differentialTimestampsContainerJson2 = differentialTimestampsContainer.toJson();
  EXPECT_TRUE(differentialTimestampsContainerJson1.toStyledString() == differentialTimestampsContainerJson2.toStyledString());
}

TEST_F(DifferentialTimestampsTest, TestToJsonWithDifferentialTimestampsContainerWithThreeBlocks) {
  DifferentialTimestampsContainer differentialTimestampsContainer =
      DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithThreeBlocks();
  DifferentialTimestampsContainerJson differentialTimestampsContainerJson1 =
      DifferentialTimestampsContainerExampleFactory::buildDifferentialTimestampsContainerJson(differentialTimestampsContainer);
  DifferentialTimestampsContainerJson differentialTimestampsContainerJson2 = differentialTimestampsContainer.toJson();
  EXPECT_TRUE(differentialTimestampsContainerJson1.toStyledString() == differentialTimestampsContainerJson2.toStyledString());
}

TEST_F(DifferentialTimestampsTest, TestToJsonWithDifferentialTimestampsContainerWithTwoBlocks) {
  DifferentialTimestampsContainer differentialTimestampsContainer =
      DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithTwoBlocks();
  DifferentialTimestampsContainerJson differentialTimestampsContainerJson1 =
      DifferentialTimestampsContainerExampleFactory::buildDifferentialTimestampsContainerJson(differentialTimestampsContainer);
  DifferentialTimestampsContainerJson differentialTimestampsContainerJson2 = differentialTimestampsContainer.toJson();
  EXPECT_TRUE(differentialTimestampsContainerJson1.toStyledString() == differentialTimestampsContainerJson2.toStyledString());
}

TEST_F(DifferentialTimestampsTest, TestToJsonWithDifferentialTimestampsContainerWithBigBlocks) {
  DifferentialTimestampsContainer differentialTimestampsContainer =
      DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithBigBlocks();
  DifferentialTimestampsContainerJson differentialTimestampsContainerJson1 =
      DifferentialTimestampsContainerExampleFactory::buildDifferentialTimestampsContainerJson(differentialTimestampsContainer);
  DifferentialTimestampsContainerJson differentialTimestampsContainerJson2 = differentialTimestampsContainer.toJson();
  EXPECT_TRUE(differentialTimestampsContainerJson1.toStyledString() == differentialTimestampsContainerJson2.toStyledString());
}

TEST_F(DifferentialTimestampsTest, TestCalculateFirstUnixTimestampInBlockWithDifferentialTimestampsContainerWithThreeBlocks) {
  DifferentialTimestampsContainer differentialTimestampsContainer =
      DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithThreeBlocks();
  UnixTimestamp firstUnixTimestamp_ms = differentialTimestampsContainer.getFirstUnixTimestamp();
  BlockIntervals blockIntervals = differentialTimestampsContainer.getBlockIntervals();

  BlockIdx blockIdx0 = 0;
  UnixTimestamp firstUnixTimestampInBlock0 = firstUnixTimestamp_ms;
  EXPECT_EQ(differentialTimestampsContainer.calculateFirstUnixTimestampInBlock(blockIdx0), firstUnixTimestampInBlock0);

  BlockIdx blockIdx1 = 1;
  UnixTimestamp firstUnixTimestampInBlock1 = firstUnixTimestamp_ms + blockIntervals[1];
  EXPECT_EQ(differentialTimestampsContainer.calculateFirstUnixTimestampInBlock(blockIdx1), firstUnixTimestampInBlock1);

  BlockIdx blockIdx2 = 2;
  UnixTimestamp firstUnixTimestampInBlock2 = firstUnixTimestamp_ms + blockIntervals[1] + blockIntervals[2];
  EXPECT_EQ(differentialTimestampsContainer.calculateFirstUnixTimestampInBlock(blockIdx2), firstUnixTimestampInBlock2);
}

TEST_F(DifferentialTimestampsTest, TestCalculateFirstUnixTimestampInBlockWithDifferentialTimestampsContainerEmpty) {
  DifferentialTimestampsContainer differentialTimestampsContainer =
      DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerEmpty();
  BlockIdx blockIdx = 0;
  EXPECT_THROW(differentialTimestampsContainer.calculateFirstUnixTimestampInBlock(blockIdx), std::invalid_argument);
}

TEST_F(DifferentialTimestampsTest, TestCalculateFirstUnixTimestampInBlockThrowInvalidArgument) {
  DifferentialTimestampsContainer differentialTimestampsContainer =
      DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithThreeBlocks();
  BlockIdx blockIdx = differentialTimestampsContainer.getBlockIntervals().size() + 1;
  EXPECT_THROW(differentialTimestampsContainer.calculateFirstUnixTimestampInBlock(blockIdx), std::invalid_argument);
}

TEST_F(DifferentialTimestampsTest, TestCalculateLastUnixTimestampInBlockWithDifferentialTimestampsContainerWithThreeBlocks) {
  DifferentialTimestampsContainer differentialTimestampsContainer =
      DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithThreeBlocks();
  DifferentialBlock differentialBlock = DifferentialBlockExampleFactory::differentialBlockWithThreeMixedDifferentialValues();
  TimestampsIntervals timestampsIntervals = differentialTimestampsContainer.getTimestampsIntervals();

  BlockIdx blockIdx0 = 0;
  UnixTimestamp firstTimestampInBlock0 = differentialTimestampsContainer.calculateFirstUnixTimestampInBlock(blockIdx0);
  UnixTimestamp lastTimeStampInBlock0 = firstTimestampInBlock0 + differentialBlock.getDifferentialValues().size() * timestampsIntervals[blockIdx0];
  EXPECT_EQ(differentialTimestampsContainer.calculateLastUnixTimestampInBlock(blockIdx0, firstTimestampInBlock0, differentialBlock),
            lastTimeStampInBlock0);

  BlockIdx blockIdx1 = 1;
  UnixTimestamp firstTimestampInBlock1 = differentialTimestampsContainer.calculateFirstUnixTimestampInBlock(blockIdx1);
  UnixTimestamp lastTimeStampInBlock1 = firstTimestampInBlock1 + differentialBlock.getDifferentialValues().size() * timestampsIntervals[blockIdx1];
  EXPECT_EQ(differentialTimestampsContainer.calculateLastUnixTimestampInBlock(blockIdx1, firstTimestampInBlock1, differentialBlock),
            lastTimeStampInBlock1);

  BlockIdx blockIdx2 = 2;
  UnixTimestamp firstTimestampInBlock2 = differentialTimestampsContainer.calculateFirstUnixTimestampInBlock(blockIdx2);
  UnixTimestamp lastTimeStampInBlock2 = firstTimestampInBlock2 + differentialBlock.getDifferentialValues().size() * timestampsIntervals[blockIdx2];
  EXPECT_EQ(differentialTimestampsContainer.calculateLastUnixTimestampInBlock(blockIdx2, firstTimestampInBlock2, differentialBlock),
            lastTimeStampInBlock2);
}

TEST_F(DifferentialTimestampsTest, TestCalculateLastUnixTimestampInBlockWithDifferentialTimestampsContainerEmpty) {
  DifferentialTimestampsContainer differentialTimestampsContainer =
      DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerEmpty();
  DifferentialBlock differentialBlock = DifferentialBlockExampleFactory::differentialBlockWithEmptyDifferentialValues();
  BlockIdx blockIdx = 0;
  UnixTimestamp firstUnixTimestampInBlock = 0;
  EXPECT_THROW(differentialTimestampsContainer.calculateLastUnixTimestampInBlock(blockIdx, firstUnixTimestampInBlock, differentialBlock),
               std::invalid_argument);
}

TEST_F(DifferentialTimestampsTest, TestCalculateLastUnixTimestampInBlockThrowInvalidArgument) {
  DifferentialTimestampsContainer differentialTimestampsContainer =
      DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithThreeBlocks();
  DifferentialBlock differentialBlock = DifferentialBlockExampleFactory::differentialBlockWithThreeMixedDifferentialValues();
  BlockIdx blockIdx = differentialTimestampsContainer.getBlockIntervals().size() + 1;
  UnixTimestamp firstUnixTimestampInBlock = 0;
  EXPECT_THROW(differentialTimestampsContainer.calculateLastUnixTimestampInBlock(blockIdx, firstUnixTimestampInBlock, differentialBlock),
               std::invalid_argument);
}

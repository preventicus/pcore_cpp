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
#include "DifferencesExampleFactory.h"
#include "DifferentialBlockExampleFactory.h"
#include "DifferentialTimestampsContainerExampleFactory.h"
#include "UnixTimestampsExampleFactory.h"

TEST(DifferentialTimestampsTest, TestGetFirstTimestampWithDifferentialTimestampsContainerWithThreeBlocks) {
  auto firstTimestamp1_ms = UnixTimestampsExampleFactory::firstTimestamp_ms();
  auto differentialTimestampsContainer = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithThreeBlocks();
  auto firstTimestamp2_ms = differentialTimestampsContainer.getFirstUnixTimestamp_ms();
  EXPECT_EQ(firstTimestamp1_ms, firstTimestamp2_ms);
}

TEST(DifferentialTimestampsTest, TestGetFirstTimestampWithDifferentialTimestampsContainerNotSet) {
  auto firstTimestamp1_ms = UnixTimestampsExampleFactory::firstTimestampNotSet_ms();
  auto differentialTimestampsContainer = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerNotSet();
  auto firstTimestamp2_ms = differentialTimestampsContainer.getFirstUnixTimestamp_ms();
  EXPECT_EQ(firstTimestamp1_ms, firstTimestamp2_ms);
}

TEST(DifferentialTimestampsTest, TestGetBlocksDifferencesWithDifferentialTimestampsContainerWithThreeBlocks) {
  auto blocksDifferences1 = DifferencesExampleFactory::blocksDifferencesWithThreeMixedDifferences();
  auto differentialTimestampsContainer = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithThreeBlocks();
  auto blocksDifferences2 = differentialTimestampsContainer.getBlocksDifferences_ms();
  EXPECT_EQ(blocksDifferences1, blocksDifferences2);
}

TEST(DifferentialTimestampsTest, TestGetBlocksDifferencesWithDifferentialTimestampsContainerNotSet) {
  auto blocksDifferences1 = DifferencesExampleFactory::blocksDifferencesNotSet();
  auto differentialTimestampsContainer = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerNotSet();
  auto blocksDifferences2 = differentialTimestampsContainer.getBlocksDifferences_ms();
  EXPECT_EQ(blocksDifferences1, blocksDifferences2);
}

TEST(DifferentialTimestampsTest, TestGetTimestampsDifferencesWithDifferentialTimestampsContainerWithThreeBlocks) {
  auto timestampsDifferences1 = DifferencesExampleFactory::timestampsDifferencesWithThreeZeroDifferences();
  auto differentialTimestampsContainer = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithThreeBlocks();
  auto timestampsDifferences2 = differentialTimestampsContainer.getTimestampsDifferences_ms();
  EXPECT_EQ(timestampsDifferences1, timestampsDifferences2);
}

TEST(DifferentialTimestampsTest, TestGetTimestampsDifferentialTimestampsContainerNotSet) {
  auto timestampsDifferences1 = DifferencesExampleFactory::timestampsDifferencesNotSet();
  auto differentialTimestampsContainer = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerNotSet();
  auto timestampsDifferences2 = differentialTimestampsContainer.getTimestampsDifferences_ms();
  EXPECT_EQ(timestampsDifferences1, timestampsDifferences2);
}

TEST(DifferentialTimestampsTest, TestIsEqualWithDifferentialTimestampsContainerWithThreeBlocks) {
  auto differentialTimestampsContainer1 = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithThreeBlocks();
  auto differentialTimestampsContainer2 = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithThreeBlocks();
  EXPECT_TRUE(differentialTimestampsContainer1 == differentialTimestampsContainer2);
}

TEST(DifferentialTimestampsTest, TestIsEqualWithDifferentialTimestampsContainerNotSet) {
  auto differentialTimestampsContainer1 = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerNotSet();
  auto differentialTimestampsContainer2 = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerNotSet();
  EXPECT_TRUE(differentialTimestampsContainer1 == differentialTimestampsContainer2);
}

TEST(DifferentialTimestampsTest, TestIsEqualWithDifferentialTimestampsContainerNotSetAndDifferentialTimestampsContainerWithThreeBlocks) {
  auto differentialTimestampsContainer1 = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerNotSet();
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

TEST(DifferentialTimestampsTest, TestIsNotEqualWithDifferentialTimestampsContainerNotSet) {
  auto differentialTimestampsContainer1 = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerNotSet();
  auto differentialTimestampsContainer2 = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerNotSet();
  EXPECT_FALSE(differentialTimestampsContainer1 != differentialTimestampsContainer2);
}

TEST(DifferentialTimestampsTest, TestIsNotEqualWithDifferentialTimestampsContainerNotSetAndDifferentialTimestampsContainerWithThreeBlocks) {
  auto differentialTimestampsContainer1 = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerNotSet();
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
  DifferentialTimestampContainerProtobuf differentialTimestampContainerProtobuf;
  differentialTimestampsContainer1.serialize(&differentialTimestampContainerProtobuf);
  auto differentialTimestampsContainer2 = DifferentialTimestampsContainer(differentialTimestampContainerProtobuf);
  EXPECT_TRUE(differentialTimestampsContainer1 == differentialTimestampsContainer2);
}

TEST(DifferentialTimestampsTest, TestSerializeWithDifferentialTimestampsContainerNotSet) {
  auto differentialTimestampsContainer1 = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerNotSet();
  DifferentialTimestampContainerProtobuf differentialTimestampContainerProtobuf;
  differentialTimestampsContainer1.serialize(&differentialTimestampContainerProtobuf);
  auto differentialTimestampsContainer2 = DifferentialTimestampsContainer(differentialTimestampContainerProtobuf);
  EXPECT_TRUE(differentialTimestampsContainer1 == differentialTimestampsContainer2);
}

TEST(DifferentialTimestampsTest, TestSerializeNoThrow) {
  auto differentialTimestampsContainer = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerNotSet();
  DifferentialTimestampContainerProtobuf differentialTimestampContainerProtobuf;
  EXPECT_NO_THROW(differentialTimestampsContainer.serialize(&differentialTimestampContainerProtobuf));
}

TEST(DifferentialTimestampsTest, TestSerializeThrow) {
  auto differentialTimestampsContainer = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerNotSet();
  DifferentialTimestampContainerProtobuf* differentialTimestampContainerProtobuf = nullptr;
  EXPECT_THROW(differentialTimestampsContainer.serialize(differentialTimestampContainerProtobuf), std::invalid_argument);
}

TEST(DifferentialTimestampsTest, TestToJsonWithDifferentialTimestampsContainerNotSet) {
  auto differentialTimestampsContainer = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerNotSet();
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
  auto firstUnixTimestamp_ms = differentialTimestampsContainer.getFirstUnixTimestamp_ms();
  auto blocksDifferences = differentialTimestampsContainer.getBlocksDifferences_ms();

  BlockIdx blockIdx0 = 0;
  auto firstUnixTimestampInBlock0 = firstUnixTimestamp_ms;
  EXPECT_EQ(differentialTimestampsContainer.calculateFirstUnixTimestampInBlock(blockIdx0), firstUnixTimestampInBlock0);

  BlockIdx blockIdx1 = 1;
  auto firstUnixTimestampInBlock1 = firstUnixTimestamp_ms + blocksDifferences[1];
  EXPECT_EQ(differentialTimestampsContainer.calculateFirstUnixTimestampInBlock(blockIdx1), firstUnixTimestampInBlock1);

  BlockIdx blockIdx2 = 2;
  auto firstUnixTimestampInBlock2 = firstUnixTimestamp_ms + blocksDifferences[1] + blocksDifferences[2];
  EXPECT_EQ(differentialTimestampsContainer.calculateFirstUnixTimestampInBlock(blockIdx2), firstUnixTimestampInBlock2);
}

TEST(DifferentialTimestampsTest, TestCalculateFirstUnixTimestampInBlockWithDifferentialTimestampsContainerNotSet) {
  auto differentialTimestampsContainer = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerNotSet();
  BlockIdx blockIdx = 0;
  EXPECT_THROW(std::ignore = differentialTimestampsContainer.calculateFirstUnixTimestampInBlock(blockIdx), std::invalid_argument);
}

TEST(DifferentialTimestampsTest, TestCalculateFirstUnixTimestampInBlockThrowInvalidArgument) {
  auto differentialTimestampsContainer = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithThreeBlocks();
  BlockIdx blockIdx = differentialTimestampsContainer.getBlocksDifferences_ms().size() + 1;
  EXPECT_THROW(std::ignore = differentialTimestampsContainer.calculateFirstUnixTimestampInBlock(blockIdx), std::invalid_argument);
}

TEST(DifferentialTimestampsTest, TestCalculateLastUnixTimestampInBlockWithDifferentialTimestampsContainerWithThreeBlocks) {
  auto differentialTimestampsContainer = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithThreeBlocks();
  auto differentialBlock = DifferentialBlockExampleFactory::differentialBlockWithThreeMixedDifferentialValues();
  auto timestampsDifferences = differentialTimestampsContainer.getTimestampsDifferences_ms();

  BlockIdx blockIdx0 = 0;
  auto firstTimestampInBlock0 = differentialTimestampsContainer.calculateFirstUnixTimestampInBlock(blockIdx0);
  auto lastTimeStampInBlock0 = firstTimestampInBlock0 + differentialBlock.getDifferentialValues().size() * timestampsDifferences[blockIdx0];
  EXPECT_EQ(differentialTimestampsContainer.calculateLastUnixTimestampInBlock(blockIdx0, firstTimestampInBlock0, differentialBlock),
            lastTimeStampInBlock0);

  BlockIdx blockIdx1 = 1;
  auto firstTimestampInBlock1 = differentialTimestampsContainer.calculateFirstUnixTimestampInBlock(blockIdx1);
  auto lastTimeStampInBlock1 = firstTimestampInBlock1 + differentialBlock.getDifferentialValues().size() * timestampsDifferences[blockIdx1];
  EXPECT_EQ(differentialTimestampsContainer.calculateLastUnixTimestampInBlock(blockIdx1, firstTimestampInBlock1, differentialBlock),
            lastTimeStampInBlock1);

  BlockIdx blockIdx2 = 2;
  auto firstTimestampInBlock2 = differentialTimestampsContainer.calculateFirstUnixTimestampInBlock(blockIdx2);
  auto lastTimeStampInBlock2 = firstTimestampInBlock2 + differentialBlock.getDifferentialValues().size() * timestampsDifferences[blockIdx2];
  EXPECT_EQ(differentialTimestampsContainer.calculateLastUnixTimestampInBlock(blockIdx2, firstTimestampInBlock2, differentialBlock),
            lastTimeStampInBlock2);
}

TEST(DifferentialTimestampsTest, TestCalculateLastUnixTimestampInBlockWithDifferentialTimestampsContainerNotSet) {
  auto differentialTimestampsContainer = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerNotSet();
  auto differentialBlock = DifferentialBlockExampleFactory::differentialBlockNotSet();
  BlockIdx blockIdx = 0;
  auto firstUnixTimestampInBlock = 0;
  EXPECT_THROW(
      std::ignore = differentialTimestampsContainer.calculateLastUnixTimestampInBlock(blockIdx, firstUnixTimestampInBlock, differentialBlock),
      std::invalid_argument);
}

TEST(DifferentialTimestampsTest, TestCalculateLastUnixTimestampInBlockThrowInvalidArgument) {
  auto differentialTimestampsContainer = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithThreeBlocks();
  auto differentialBlock = DifferentialBlockExampleFactory::differentialBlockWithThreeMixedDifferentialValues();
  BlockIdx blockIdx = differentialTimestampsContainer.getBlocksDifferences_ms().size() + 1;
  auto firstUnixTimestampInBlock = 0;
  EXPECT_THROW(
      std::ignore = differentialTimestampsContainer.calculateLastUnixTimestampInBlock(blockIdx, firstUnixTimestampInBlock, differentialBlock),
      std::invalid_argument);
}

TEST(DifferentialTimestampsTest, TestSwitchDataFormWithDifferentialTimestampsContainerNotSet) {
  auto differentialTimestampsContainer = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerNotSet();
  EXPECT_THROW(differentialTimestampsContainer.switchDataForm(), std::runtime_error);
}

TEST(DifferentialTimestampsTest, TestIsSetWithDifferentialTimestampsContainerNotSet) {
  auto differentialTimestampsContainer = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerNotSet();
  EXPECT_FALSE(differentialTimestampsContainer.isSet());
}

TEST(DifferentialTimestampsTest, TestIsSetWithDifferentialTimestampsContainerWithThreeBlocks) {
  auto differentialTimestampsContainer = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithThreeBlocks();
  EXPECT_TRUE(differentialTimestampsContainer.isSet());
}

TEST(DifferentialTimestampsTest, TestIsSetWithDifferentialTimestampsContainerWithFirstUnixTimeStampNotSet) {
  auto differentialTimestampsContainer = DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithFirstUnixTimeStampNotSet();
  EXPECT_TRUE(differentialTimestampsContainer.isSet());
}

TEST(DifferentialTimestampsTest, TestIsSetWithDifferentialTimestampsContainerWithFirstUnixTimeStampNotSetAndBlocksDifferencesNotSet) {
  auto differentialTimestampsContainer =
      DifferentialTimestampsContainerExampleFactory::differentialTimestampsContainerWithFirstUnixTimeStampNotSetAndBlocksDifferencesNotSet();
  EXPECT_TRUE(differentialTimestampsContainer.isSet());
}

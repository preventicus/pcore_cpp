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
#include "Channel.h"
#include "ChannelExampleFactory.h"

TEST(ChannelTest, TestGetPpgMetaData) {
  Channel channel = ChannelExampleFactory::channelWithAbsoluteBlockAndPpgMetaData();
  PpgMetaData ppgMetaData = PpgMetaDataExampleFactory::ppgMetaDataWithWavelength255();
  EXPECT_TRUE(channel.getPpgMetaData().isEqual(ppgMetaData));
}

TEST(ChannelTest, TestGetAccMetaData) {
  Channel channel = ChannelExampleFactory::channelWithAbsoluteBlockAndAccMetaData();
  AccMetaData accMetaData = AccMetaDataExampleFactory::accMetaDataWithNormEuclideanDifferencesNorm();
  EXPECT_TRUE(channel.getAccMetaData().isEqual(accMetaData));
}

TEST(ChannelTest, TestGetDifferentialBlocks) {
  Channel channel = ChannelExampleFactory::channelWithDifferentialBlocksAndAccMetaData();
  DifferentialBlocks actualDifferentialBlocks = channel.getDifferentialBlocks();
  DifferentialBlocks expectedDifferentialBlocks = DifferentialBlockExampleFactory::differentialBlocksWithThreeMixedDifferentialBlocks();
  EXPECT_EQ(actualDifferentialBlocks.size(), expectedDifferentialBlocks.size());
  for (size_t i = 0; i < actualDifferentialBlocks.size(); i++) {
    EXPECT_TRUE(actualDifferentialBlocks[i].isEqual(expectedDifferentialBlocks[i]));
  }
}

TEST(ChannelTest, TestGetAbsoluteBlock) {
  Channel channel = ChannelExampleFactory::channelWithAbsoluteBlockAndPpgMetaData();
  AbsoluteBlock actualAbsoluteBlock = channel.getAbsoluteBlock();
  AbsoluteBlock expectedAbsoluteValues = AbsoluteBlockExampleFactory::absoluteBlockWithThreeMixedAbsoluteValues();
  EXPECT_TRUE(actualAbsoluteBlock.isEqual(expectedAbsoluteValues));
}

TEST(ChannelTest, TestIsEqualWithChannelWithAbsoluteBlockAndAccMetaData) {
  Channel channel1 = ChannelExampleFactory::channelWithAbsoluteBlockAndAccMetaData();
  Channel channel2 = ChannelExampleFactory::channelWithAbsoluteBlockAndAccMetaData();
  EXPECT_TRUE(channel1.isEqual(channel2));
}

TEST(ChannelTest, TestIsEqualWithChannelWithAbsoluteBlockAndPpgMetaData) {
  Channel channel1 = ChannelExampleFactory::channelWithAbsoluteBlockAndPpgMetaData();
  Channel channel2 = ChannelExampleFactory::channelWithAbsoluteBlockAndPpgMetaData();
  EXPECT_TRUE(channel1.isEqual(channel2));
}

TEST(ChannelTest, TestIsEqualWithChannelWithDifferentialBlocksAndAccMetaData) {
  Channel channel1 = ChannelExampleFactory::channelWithDifferentialBlocksAndAccMetaData();
  Channel channel2 = ChannelExampleFactory::channelWithDifferentialBlocksAndAccMetaData();
  EXPECT_TRUE(channel1.isEqual(channel2));
}

TEST(ChannelTest, TestIsEqualWithChannelWithDifferentialBlocksAndPpgMetaData) {
  Channel channel1 = ChannelExampleFactory::channelWithAbsoluteBlockAndPpgMetaData();
  Channel channel2 = ChannelExampleFactory::channelWithAbsoluteBlockAndPpgMetaData();
  EXPECT_TRUE(channel1.isEqual(channel2));
}

TEST(ChannelTest, TestIsEqualWithNotEqualAbsoluteBlockInMetaData) {
  Channel channel1 = ChannelExampleFactory::channelWithAbsoluteBlockAndPpgMetaData();
  Channel channel2 = ChannelExampleFactory::channelWithAbsoluteBlockAndAccMetaData();
  EXPECT_FALSE(channel1.isEqual(channel2));
}

TEST(ChannelTest, TestIsEqualWithAbsoluteBlockAndDifferentialBlocks) {
  Channel channel1 = ChannelExampleFactory::channelWithAbsoluteBlockAndPpgMetaData();
  Channel channel2 = ChannelExampleFactory::channelWithDifferentialBlocksAndPpgMetaData();
  EXPECT_FALSE(channel1.isEqual(channel2));
}

TEST(ChannelTest, TestIsEqualWithNotEqualInBlocksAndMetaData) {
  Channel channel1 = ChannelExampleFactory::channelWithAbsoluteBlockAndAccMetaData();
  Channel channel2 = ChannelExampleFactory::channelWithDifferentialBlocksAndPpgMetaData();
  EXPECT_FALSE(channel1.isEqual(channel2));
}

TEST(ChannelTest, TestIsEqualWithNotEqualInAbsoluteBlock) {
  Channel channel1 = ChannelExampleFactory::channelWithAbsoluteBlockForNotEqualTest();
  Channel channel2 = ChannelExampleFactory::channelWithAbsoluteBlockAndPpgMetaData();
  EXPECT_FALSE(channel1.isEqual(channel2));
}

TEST(ChannelTest, TestIsEqualWithNotEqualInDifferentialBlock) {
  Channel channel1 = ChannelExampleFactory::channelWithDifferentialBlocksForNotEqualTest();
  Channel channel2 = ChannelExampleFactory::channelWithDifferentialBlocksAndPpgMetaData();
  EXPECT_FALSE(channel1.isEqual(channel2));
}

TEST(ChannelTest, TestIsEqualChannelEmpty) {
  Channel channel1 = Channel();
  Channel channel2 = Channel();
  EXPECT_TRUE(channel1.isEqual(channel2));
}

TEST(ChannelTest, TestSwitchTo) {
  BlockIdxs blockIdxs = {0, 11, 20};
  Channel channelWithAbsoluteBlock = ChannelExampleFactory::channelWithAbsoluteValuesForTestSwitchTo();
  channelWithAbsoluteBlock.switchDataForm(blockIdxs);
  AbsoluteBlock absoluteBlockEmpty = AbsoluteBlock();
  EXPECT_TRUE(channelWithAbsoluteBlock.getAbsoluteBlock().isEqual(absoluteBlockEmpty));
  DifferentialBlocks expectedDifferentialBlocks = DifferentialBlockExampleFactory::differentialBlocksForTestSwitchTo();
  DifferentialBlocks actualDifferentialBlocks = channelWithAbsoluteBlock.getDifferentialBlocks();
  size_t actualDifferentialBlocksSize = actualDifferentialBlocks.size();
  EXPECT_EQ(actualDifferentialBlocksSize, expectedDifferentialBlocks.size());
  for (size_t i = 0; i < actualDifferentialBlocksSize; i++) {
    EXPECT_TRUE(actualDifferentialBlocks[i].isEqual(expectedDifferentialBlocks[i]));
  }

  Channel channelWithDifferentialBlocks = ChannelExampleFactory::channelWithDifferentialValuesForTestSwitchTo();
  channelWithDifferentialBlocks.switchDataForm();
  EXPECT_EQ(channelWithDifferentialBlocks.getDifferentialBlocks().size(), 0);
  AbsoluteBlock expectedAbsoluteBlock = AbsoluteBlockExampleFactory::absoluteBlockForTestSwitchTo();
  AbsoluteBlock actualAbsoluteBlock = channelWithDifferentialBlocks.getAbsoluteBlock();
  EXPECT_TRUE(actualAbsoluteBlock.isEqual(expectedAbsoluteBlock));
}

TEST(ChannelTest, TestSerializeWithChannelWithDifferentialValuesAndAccMetaData) {
  Channel channel = ChannelExampleFactory::channelWithDifferentialBlocksAndAccMetaData();
  ProtobufChannel protobufChannel;
  channel.serialize(&protobufChannel);
  EXPECT_TRUE(Channel(protobufChannel).isEqual(channel));
}

TEST(ChannelTest, TestSerializeWithChannelWithDifferentialValuesAndPpgMetaData) {
  Channel channel = ChannelExampleFactory::channelWithDifferentialBlocksAndPpgMetaData();
  ProtobufChannel protobufChannel;
  channel.serialize(&protobufChannel);
  EXPECT_TRUE(Channel(protobufChannel).isEqual(channel));
}

TEST(ChannelTest, TestSerializeThrowNullPtr) {
  Channel channel = ChannelExampleFactory::channelEmpty();
  ProtobufChannel* protobufChannel = nullptr;
  EXPECT_THROW(channel.serialize(protobufChannel), std::invalid_argument);
}

TEST(ChannelTest, TestSerializeThrowChannelEmpty) {
  Channel channel = ChannelExampleFactory::channelEmpty();
  ProtobufChannel protobufChannel;
  EXPECT_THROW(channel.serialize(&protobufChannel), std::invalid_argument);
}

TEST(ChannelTest, TestSerializeNoThrow) {
  Channel channel = ChannelExampleFactory::channelWithAbsoluteBlockAndPpgMetaData();
  ProtobufChannel protobufChannel;
  EXPECT_NO_THROW(channel.serialize(&protobufChannel));
}

TEST(ChannelTest, TestToJsonWithDifferentialBlocksAndAccMetaData) {
  Channel channel = ChannelExampleFactory::channelWithDifferentialBlocksAndAccMetaData();
  ChannelJson channelJson1 = channel.toJson(DataForm::DATA_FORM_DIFFERENTIAL, ProtobufSensorType::SENSOR_TYPE_ACC);
  ChannelJson channelJson2 = ChannelExampleFactory::buildChannelJson(channel);
  EXPECT_TRUE(channelJson1.toStyledString() == channelJson2.toStyledString());
}

TEST(ChannelTest, TestToJsonWithDifferentialBlocksAndPpgMetaData) {
  Channel channel = ChannelExampleFactory::channelWithDifferentialBlocksAndPpgMetaData();
  ChannelJson channelJson1 = channel.toJson(DataForm::DATA_FORM_DIFFERENTIAL, ProtobufSensorType::SENSOR_TYPE_PPG);
  ChannelJson channelJson2 = ChannelExampleFactory::buildChannelJson(channel);
  EXPECT_TRUE(channelJson1.toStyledString() == channelJson2.toStyledString());
}

TEST(ChannelTest, TestToJsonWithAbsoluteBlockAndAccMetaData) {
  Channel channel = ChannelExampleFactory::channelWithAbsoluteBlockAndAccMetaData();
  ChannelJson channelJson1 = channel.toJson(DataForm::DATA_FORM_ABSOLUTE, ProtobufSensorType::SENSOR_TYPE_ACC);
  ChannelJson channelJson2 = ChannelExampleFactory::buildChannelJson(channel);
  EXPECT_TRUE(channelJson1.toStyledString() == channelJson2.toStyledString());
}

TEST(ChannelTest, TestToJsonWithAbsoluteBlockAndPpgMetaData) {
  Channel channel = ChannelExampleFactory::channelWithAbsoluteBlockAndPpgMetaData();
  ChannelJson channelJson1 = channel.toJson(DataForm::DATA_FORM_ABSOLUTE, ProtobufSensorType::SENSOR_TYPE_PPG);
  ChannelJson channelJson2 = ChannelExampleFactory::buildChannelJson(channel);
  EXPECT_TRUE(channelJson1.toStyledString() == channelJson2.toStyledString());
}

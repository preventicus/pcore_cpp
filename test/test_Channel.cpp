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
#include "Channel.h"
#include "ChannelExampleFactory.h"

class ChannelTest : public ::testing::Test {
 protected:
};

TEST_F(ChannelTest, TestGetPpgMetaData) {
  Channel channel = ChannelExampleFactory::channelWithAbsoluteBlockAndPpgMetaData();
  PpgMetaData ppgMetaData = PpgMetaDataExampleFactory::ppgMetaDataWithWavelength255();
  EXPECT_TRUE(channel.getPpgMetaData().isEqual(ppgMetaData));
}

TEST_F(ChannelTest, TestGetAccMetaData) {
  Channel channel = ChannelExampleFactory::channelWithAbsoluteBlockAndAccMetaData();
  AccMetaData accMetaData = AccMetaDataExampleFactory::accMetaDataWithNormEuclideanDifferencesNorm();
  EXPECT_TRUE(channel.getAccMetaData().isEqual(accMetaData));
}

TEST_F(ChannelTest, TestGetDifferentialBlocks) {
  Channel channel = ChannelExampleFactory::channelWithDifferentialBlocksAndAccMetaData();
  DifferentialBlocks actualDifferentialBlocks = channel.getDifferentialBlocks();
  DifferentialBlocks expectedDifferentialBlocks = DifferentialBlockExampleFactory::differentialBlocksWithThreeMixedDifferentialBlocks();
  EXPECT_EQ(actualDifferentialBlocks.size(), expectedDifferentialBlocks.size());
  for (size_t i = 0; i < actualDifferentialBlocks.size(); i++) {
    EXPECT_TRUE(actualDifferentialBlocks[i].isEqual(expectedDifferentialBlocks[i]));
  }
}

TEST_F(ChannelTest, TestGetAbsoluteBlock) {
  Channel channel = ChannelExampleFactory::channelWithAbsoluteBlockAndPpgMetaData();
  AbsoluteBlock actualAbsoluteBlock = channel.getAbsoluteBlock();
  AbsoluteBlock expectedAbsoluteValues = AbsoluteBlockExampleFactory::absoluteBlockWithThreeMixedAbsoluteValues();
  EXPECT_TRUE(actualAbsoluteBlock.isEqual(expectedAbsoluteValues));
}

TEST_F(ChannelTest, CompareEqualChannelWithAbsoluteBlockAndAccMetaData) {
  Channel channel1 = ChannelExampleFactory::channelWithAbsoluteBlockAndAccMetaData();
  Channel channel2 = ChannelExampleFactory::channelWithAbsoluteBlockAndAccMetaData();
  EXPECT_TRUE(channel1.isEqual(channel2));
}

TEST_F(ChannelTest, CompareEqualChannelWithAbsoluteBlockAndPpgMetaData) {
  Channel channel1 = ChannelExampleFactory::channelWithAbsoluteBlockAndPpgMetaData();
  Channel channel2 = ChannelExampleFactory::channelWithAbsoluteBlockAndPpgMetaData();
  EXPECT_TRUE(channel1.isEqual(channel2));
}

TEST_F(ChannelTest, CompareEqualChannelWithDifferentialBlocksAndAccMetaData) {
  Channel channel1 = ChannelExampleFactory::channelWithDifferentialBlocksAndAccMetaData();
  Channel channel2 = ChannelExampleFactory::channelWithDifferentialBlocksAndAccMetaData();
  EXPECT_TRUE(channel1.isEqual(channel2));
}

TEST_F(ChannelTest, CompareEqualChannelWithDifferentialBlocksAndPpgMetaData) {
  Channel channel1 = ChannelExampleFactory::channelWithAbsoluteBlockAndPpgMetaData();
  Channel channel2 = ChannelExampleFactory::channelWithAbsoluteBlockAndPpgMetaData();
  EXPECT_TRUE(channel1.isEqual(channel2));
}

TEST_F(ChannelTest, CompareNotEqualInMetaData) {
  Channel channel1 = ChannelExampleFactory::channelWithAbsoluteBlockAndPpgMetaData();
  Channel channel2 = ChannelExampleFactory::channelWithAbsoluteBlockAndAccMetaData();
  EXPECT_FALSE(channel1.isEqual(channel2));
}

TEST_F(ChannelTest, CompareNotEqualInBlocks) {
  Channel channel1 = ChannelExampleFactory::channelWithAbsoluteBlockAndPpgMetaData();
  Channel channel2 = ChannelExampleFactory::channelWithDifferentialBlocksAndPpgMetaData();
  EXPECT_FALSE(channel1.isEqual(channel2));
}

TEST_F(ChannelTest, CompareNotEqualInBlocksAndMetaData) {
  Channel channel1 = ChannelExampleFactory::channelWithAbsoluteBlockAndAccMetaData();
  Channel channel2 = ChannelExampleFactory::channelWithDifferentialBlocksAndPpgMetaData();
  EXPECT_FALSE(channel1.isEqual(channel2));
}

TEST_F(ChannelTest, CompareNotEqualInAbsoluteBlock) {
  Channel channel1 = ChannelExampleFactory::channelWithAbsoluteBlockForNotEquallTest();
  Channel channel2 = ChannelExampleFactory::channelWithAbsoluteBlockAndPpgMetaData();
  EXPECT_FALSE(channel1.isEqual(channel2));
}

TEST_F(ChannelTest, CompareNotEqualInDifferentialBlock) {
  Channel channel1 = ChannelExampleFactory::channelWithDifferentialBlocksForNotEqualTest();
  Channel channel2 = ChannelExampleFactory::channelWithDifferentialBlocksAndPpgMetaData();
  EXPECT_FALSE(channel1.isEqual(channel2));
}

TEST_F(ChannelTest, CompareEmptyWithEmptyChannel) {
  Channel channel1 = Channel();
  Channel channel2 = Channel();
  EXPECT_TRUE(channel1.isEqual(channel2));
}

TEST_F(ChannelTest, TestSwitchTo) {
    BlockIdxs blockIdxs = {0, 11, 20};
    Channel channelWithAbsoluteBlock = ChannelExampleFactory::channelWithAbsoluteValuesForTestSwitchTo();
    channelWithAbsoluteBlock.switchDataForm(blockIdxs);
    AbsoluteBlock absoluteBlockEmpty = AbsoluteBlock();
    EXPECT_TRUE( channelWithAbsoluteBlock.getAbsoluteBlock().isEqual(absoluteBlockEmpty) );
    DifferentialBlocks expectedDifferentialBlocks = DifferentialBlockExampleFactory::differentialBlocksForTestSwitchTo();
    DifferentialBlocks actualDifferentialBlocks = channelWithAbsoluteBlock.getDifferentialBlocks();
    size_t actualDifferentialBlocksSize = actualDifferentialBlocks.size();
    EXPECT_EQ(actualDifferentialBlocksSize, expectedDifferentialBlocks.size());
    for (size_t i = 0; i < actualDifferentialBlocksSize; i++ ) {
      EXPECT_TRUE(actualDifferentialBlocks[i].isEqual(expectedDifferentialBlocks[i]));
    }

    Channel channelWithDifferentialBlocks = ChannelExampleFactory::channelWithDifferentialValuesForTestSwitchTo();
    channelWithDifferentialBlocks.switchDataForm();
    EXPECT_EQ( channelWithDifferentialBlocks.getDifferentialBlocks().size(), 0);
    AbsoluteBlock expectedAbsoluteBlock = AbsoluteBlockExampleFactory::absoluteBlockForTestSwitchTo();
    AbsoluteBlock actualAbsoluteBlock = channelWithDifferentialBlocks.getAbsoluteBlock();
    EXPECT_TRUE(actualAbsoluteBlock.isEqual(expectedAbsoluteBlock));
}

TEST_F(ChannelTest, TestSerializeWithChannelWithAbsoluteValuesAndAccMetaData) {
    Channel channel = ChannelExampleFactory::channelWithAbsoluteBlockAndAccMetaData();
    ProtobufChannel protobufChannel;
    channel.serialize(&protobufChannel);
    EXPECT_TRUE(Channel(protobufChannel).isEqual(channel));
}

TEST_F(ChannelTest, TestSerializeWithChannelWithAbsoluteValuesAndPpgMetaData) {
    Channel channel = ChannelExampleFactory::channelWithAbsoluteBlockAndPpgMetaData();
    ProtobufChannel protobufChannel;
    channel.serialize(&protobufChannel);
    EXPECT_TRUE(Channel(protobufChannel).isEqual(channel));
}

TEST_F(ChannelTest, TestSerializeWithChannelWithDifferentialValuesAndAccMetaData) {
    Channel channel = ChannelExampleFactory::channelWithDifferentialBlocksAndAccMetaData();
    ProtobufChannel protobufChannel;
    channel.serialize(&protobufChannel);
    EXPECT_TRUE(Channel(protobufChannel).isEqual(channel));
}

TEST_F(ChannelTest, TestSerializeWithChannelWithDifferentialValuesAndPpgMetaData) {
    Channel channel = ChannelExampleFactory::channelWithDifferentialBlocksAndPpgMetaData();
    ProtobufChannel protobufChannel;
    channel.serialize(&protobufChannel);
    EXPECT_TRUE(Channel(protobufChannel).isEqual(channel));
}

TEST_F(ChannelTest, TestSerializeThrow) {
    Channel channel = Channel();
    ProtobufChannel* protobufChannel = nullptr;
    EXPECT_THROW(channel.serialize(protobufChannel), std::invalid_argument);
}

TEST_F(ChannelTest, TestSerializeNoThrow) {
    Channel channel = Channel();
    ProtobufChannel protobufChannel;
    EXPECT_NO_THROW(channel.serialize(&protobufChannel));
}

TEST_F(ChannelTest, TestToJson) {

}


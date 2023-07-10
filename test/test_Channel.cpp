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
  auto channel = ChannelExampleFactory::channelWithAbsoluteBlockAndPpgMetaData();
  auto ppgMetaData = PpgMetaDataExampleFactory::ppgMetaDataWithWavelength255();
  EXPECT_TRUE(channel.getPpgMetaData() == ppgMetaData);
}

TEST(ChannelTest, TestGetAccMetaData) {
  auto channel = ChannelExampleFactory::channelWithAbsoluteBlockAndAccMetaData();
  auto accMetaData = AccMetaDataExampleFactory::accMetaDataWithNormEuclideanDifferencesNorm();
  EXPECT_TRUE(channel.getAccMetaData() == accMetaData);
}

TEST(ChannelTest, TestGetDifferentialBlocks) {
  auto channel = ChannelExampleFactory::channelWithDifferentialBlocksAndAccMetaData();
  auto actualDifferentialBlocks = channel.getDifferentialBlocks();
  auto expectedDifferentialBlocks = DifferentialBlockExampleFactory::differentialBlocksWithThreeMixedDifferentialBlocks();
  EXPECT_EQ(actualDifferentialBlocks.size(), expectedDifferentialBlocks.size());
  for (size_t i = 0; i < actualDifferentialBlocks.size(); i++) {
    EXPECT_TRUE(actualDifferentialBlocks[i] == expectedDifferentialBlocks[i]);
  }
}

TEST(ChannelTest, TestGetAbsoluteBlock) {
  auto channel = ChannelExampleFactory::channelWithAbsoluteBlockAndPpgMetaData();
  auto actualAbsoluteBlock = channel.getAbsoluteBlock();
  auto expectedAbsoluteValues = AbsoluteBlockExampleFactory::absoluteBlockWithThreeMixedAbsoluteValues();
  EXPECT_TRUE(actualAbsoluteBlock == expectedAbsoluteValues);
}

TEST(ChannelTest, TestIsEqualWithChannelWithAbsoluteBlockAndAccMetaData) {
  auto channel1 = ChannelExampleFactory::channelWithAbsoluteBlockAndAccMetaData();
  auto channel2 = ChannelExampleFactory::channelWithAbsoluteBlockAndAccMetaData();
  EXPECT_TRUE(channel1 == channel2);
}

TEST(ChannelTest, TestIsEqualWithChannelWithAbsoluteBlockAndPpgMetaData) {
  auto channel1 = ChannelExampleFactory::channelWithAbsoluteBlockAndPpgMetaData();
  auto channel2 = ChannelExampleFactory::channelWithAbsoluteBlockAndPpgMetaData();
  EXPECT_TRUE(channel1 == channel2);
}

TEST(ChannelTest, TestIsEqualWithChannelWithDifferentialBlocksAndAccMetaData) {
  auto channel1 = ChannelExampleFactory::channelWithDifferentialBlocksAndAccMetaData();
  auto channel2 = ChannelExampleFactory::channelWithDifferentialBlocksAndAccMetaData();
  EXPECT_TRUE(channel1 == channel2);
}

TEST(ChannelTest, TestIsEqualWithChannelWithDifferentialBlocksAndPpgMetaData) {
  auto channel1 = ChannelExampleFactory::channelWithAbsoluteBlockAndPpgMetaData();
  auto channel2 = ChannelExampleFactory::channelWithAbsoluteBlockAndPpgMetaData();
  EXPECT_TRUE(channel1 == channel2);
}

TEST(ChannelTest, TestIsEqualWithNotEqualAbsoluteBlockInMetaData) {
  auto channel1 = ChannelExampleFactory::channelWithAbsoluteBlockAndPpgMetaData();
  auto channel2 = ChannelExampleFactory::channelWithAbsoluteBlockAndAccMetaData();
  EXPECT_FALSE(channel1 == channel2);
}

TEST(ChannelTest, TestIsEqualWithAbsoluteBlockAndDifferentialBlocks) {
  auto channel1 = ChannelExampleFactory::channelWithAbsoluteBlockAndPpgMetaData();
  auto channel2 = ChannelExampleFactory::channelWithDifferentialBlocksAndPpgMetaData();
  EXPECT_FALSE(channel1 == channel2);
}

TEST(ChannelTest, TestIsEqualWithNotEqualInBlocksAndMetaData) {
  auto channel1 = ChannelExampleFactory::channelWithAbsoluteBlockAndAccMetaData();
  auto channel2 = ChannelExampleFactory::channelWithDifferentialBlocksAndPpgMetaData();
  EXPECT_FALSE(channel1 == channel2);
}

TEST(ChannelTest, TestIsEqualWithNotEqualInAbsoluteBlock) {
  auto channel1 = ChannelExampleFactory::channelWithAbsoluteBlockForNotEqualTest();
  auto channel2 = ChannelExampleFactory::channelWithAbsoluteBlockAndPpgMetaData();
  EXPECT_FALSE(channel1 == channel2);
}

TEST(ChannelTest, TestIsEqualWithNotEqualInDifferentialBlock) {
  auto channel1 = ChannelExampleFactory::channelWithDifferentialBlocksForNotEqualTest();
  auto channel2 = ChannelExampleFactory::channelWithDifferentialBlocksAndPpgMetaData();
  EXPECT_FALSE(channel1 == channel2);
}

TEST(ChannelTest, TestIsEqualChannelEmpty) {
  auto channel1 = Channel();
  auto channel2 = Channel();
  EXPECT_TRUE(channel1 == channel2);
}

TEST(ChannelTest, TestIsNotEqualWithChannelWithAbsoluteBlockAndAccMetaData) {
  auto channel1 = ChannelExampleFactory::channelWithAbsoluteBlockAndAccMetaData();
  auto channel2 = ChannelExampleFactory::channelWithAbsoluteBlockAndAccMetaData();
  EXPECT_FALSE(channel1 != channel2);
}

TEST(ChannelTest, TestIsNotEqualWithChannelWithAbsoluteBlockAndPpgMetaData) {
  auto channel1 = ChannelExampleFactory::channelWithAbsoluteBlockAndPpgMetaData();
  auto channel2 = ChannelExampleFactory::channelWithAbsoluteBlockAndPpgMetaData();
  EXPECT_FALSE(channel1 != channel2);
}

TEST(ChannelTest, TestIsNotEqualWithChannelWithDifferentialBlocksAndAccMetaData) {
  auto channel1 = ChannelExampleFactory::channelWithDifferentialBlocksAndAccMetaData();
  auto channel2 = ChannelExampleFactory::channelWithDifferentialBlocksAndAccMetaData();
  EXPECT_FALSE(channel1 != channel2);
}

TEST(ChannelTest, TestIsNotEqualWithChannelWithDifferentialBlocksAndPpgMetaData) {
  auto channel1 = ChannelExampleFactory::channelWithAbsoluteBlockAndPpgMetaData();
  auto channel2 = ChannelExampleFactory::channelWithAbsoluteBlockAndPpgMetaData();
  EXPECT_FALSE(channel1 != channel2);
}

TEST(ChannelTest, TestIsNotEqualWithNotEqualAbsoluteBlockInMetaData) {
  auto channel1 = ChannelExampleFactory::channelWithAbsoluteBlockAndPpgMetaData();
  auto channel2 = ChannelExampleFactory::channelWithAbsoluteBlockAndAccMetaData();
  EXPECT_TRUE(channel1 != channel2);
}

TEST(ChannelTest, TestIsNotEqualWithAbsoluteBlockAndDifferentialBlocks) {
  auto channel1 = ChannelExampleFactory::channelWithAbsoluteBlockAndPpgMetaData();
  auto channel2 = ChannelExampleFactory::channelWithDifferentialBlocksAndPpgMetaData();
  EXPECT_TRUE(channel1 != channel2);
}

TEST(ChannelTest, TestIsNotEqualWithNotEqualInBlocksAndMetaData) {
  auto channel1 = ChannelExampleFactory::channelWithAbsoluteBlockAndAccMetaData();
  auto channel2 = ChannelExampleFactory::channelWithDifferentialBlocksAndPpgMetaData();
  EXPECT_TRUE(channel1 != channel2);
}

TEST(ChannelTest, TestIsNotEqualWithNotEqualInAbsoluteBlock) {
  auto channel1 = ChannelExampleFactory::channelWithAbsoluteBlockForNotEqualTest();
  auto channel2 = ChannelExampleFactory::channelWithAbsoluteBlockAndPpgMetaData();
  EXPECT_TRUE(channel1 != channel2);
}

TEST(ChannelTest, TestIsNotEqualWithNotEqualInDifferentialBlock) {
  auto channel1 = ChannelExampleFactory::channelWithDifferentialBlocksForNotEqualTest();
  auto channel2 = ChannelExampleFactory::channelWithDifferentialBlocksAndPpgMetaData();
  EXPECT_TRUE(channel1 != channel2);
}

TEST(ChannelTest, TestIsNotEqualChannelEmpty) {
  auto channel1 = Channel();
  auto channel2 = Channel();
  EXPECT_FALSE(channel1 != channel2);
}

TEST(ChannelTest, TestSwitchDataForm) {
  BlockIdxs blockIdxs = {0, 11, 20};
  auto channelWithAbsoluteBlock = ChannelExampleFactory::channelWithAbsoluteValuesForSwitchDataFormTest();
  channelWithAbsoluteBlock.switchDataForm(blockIdxs);
  auto absoluteBlockEmpty = AbsoluteBlock();
  EXPECT_TRUE(channelWithAbsoluteBlock.getAbsoluteBlock() == absoluteBlockEmpty);
  auto expectedDifferentialBlocks = DifferentialBlockExampleFactory::differentialBlocksForSwitchDataFormTest();
  auto actualDifferentialBlocks = channelWithAbsoluteBlock.getDifferentialBlocks();
  auto actualDifferentialBlocksSize = actualDifferentialBlocks.size();
  EXPECT_EQ(actualDifferentialBlocksSize, expectedDifferentialBlocks.size());
  for (size_t i = 0; i < actualDifferentialBlocksSize; i++) {
    EXPECT_TRUE(actualDifferentialBlocks[i] == expectedDifferentialBlocks[i]);
  }

  auto channelWithDifferentialBlocks = ChannelExampleFactory::channelWithDifferentialValuesForSwitchDataFormTest();
  channelWithDifferentialBlocks.switchDataForm();
  EXPECT_EQ(channelWithDifferentialBlocks.getDifferentialBlocks().size(), 0);
  auto expectedAbsoluteBlock = AbsoluteBlockExampleFactory::absoluteBlockForSwitchDataFormTest();
  auto actualAbsoluteBlock = channelWithDifferentialBlocks.getAbsoluteBlock();
  EXPECT_TRUE(actualAbsoluteBlock == expectedAbsoluteBlock);
}

TEST(ChannelTest, TestSerializeWithChannelWithDifferentialValuesAndAccMetaData) {
  auto channel = ChannelExampleFactory::channelWithDifferentialBlocksAndAccMetaData();
  ChannelProtobuf channelProtobuf;
  channel.serialize(&channelProtobuf);
  EXPECT_TRUE(Channel(channelProtobuf) == channel);
}

TEST(ChannelTest, TestSerializeWithChannelWithDifferentialValuesAndPpgMetaData) {
  auto channel = ChannelExampleFactory::channelWithDifferentialBlocksAndPpgMetaData();
  ChannelProtobuf channelProtobuf;
  channel.serialize(&channelProtobuf);
  EXPECT_TRUE(Channel(channelProtobuf) == channel);
}

TEST(ChannelTest, TestSerializeThrowNullPtr) {
  auto channel = ChannelExampleFactory::channelEmpty();
  ChannelProtobuf* channelProtobuf = nullptr;
  EXPECT_THROW(channel.serialize(channelProtobuf), std::invalid_argument);
}

TEST(ChannelTest, TestSerializeThrowChannelEmpty) {
  auto channel = ChannelExampleFactory::channelEmpty();
  ChannelProtobuf channelProtobuf;
  EXPECT_THROW(channel.serialize(&channelProtobuf), std::invalid_argument);
}

TEST(ChannelTest, TestSerializeNoThrow) {
  auto channel = ChannelExampleFactory::channelWithAbsoluteBlockAndPpgMetaData();
  ChannelProtobuf channelProtobuf;
  EXPECT_NO_THROW(channel.serialize(&channelProtobuf));
}

TEST(ChannelTest, TestToJsonWithDifferentialBlocksAndAccMetaData) {
  auto channel = ChannelExampleFactory::channelWithDifferentialBlocksAndAccMetaData();
  auto channelJson1 = channel.toJson(DataForm::DATA_FORM_DIFFERENTIAL, SensorTypeProtobuf::SENSOR_TYPE_ACC);
  auto channelJson2 = ChannelExampleFactory::buildChannelJson(channel);
  EXPECT_TRUE(channelJson1.toStyledString() == channelJson2.toStyledString());
}

TEST(ChannelTest, TestToJsonWithDifferentialBlocksAndPpgMetaData) {
  auto channel = ChannelExampleFactory::channelWithDifferentialBlocksAndPpgMetaData();
  auto channelJson1 = channel.toJson(DataForm::DATA_FORM_DIFFERENTIAL, SensorTypeProtobuf::SENSOR_TYPE_PPG);
  auto channelJson2 = ChannelExampleFactory::buildChannelJson(channel);
  EXPECT_TRUE(channelJson1.toStyledString() == channelJson2.toStyledString());
}

TEST(ChannelTest, TestToJsonWithAbsoluteBlockAndAccMetaData) {
  auto channel = ChannelExampleFactory::channelWithAbsoluteBlockAndAccMetaData();
  auto channelJson1 = channel.toJson(DataForm::DATA_FORM_ABSOLUTE, SensorTypeProtobuf::SENSOR_TYPE_ACC);
  auto channelJson2 = ChannelExampleFactory::buildChannelJson(channel);
  EXPECT_TRUE(channelJson1.toStyledString() == channelJson2.toStyledString());
}

TEST(ChannelTest, TestToJsonWithAbsoluteBlockAndPpgMetaData) {
  auto channel = ChannelExampleFactory::channelWithAbsoluteBlockAndPpgMetaData();
  auto channelJson1 = channel.toJson(DataForm::DATA_FORM_ABSOLUTE, SensorTypeProtobuf::SENSOR_TYPE_PPG);
  auto channelJson2 = ChannelExampleFactory::buildChannelJson(channel);
  EXPECT_TRUE(channelJson1.toStyledString() == channelJson2.toStyledString());
}

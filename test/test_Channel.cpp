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
  AbsoluteBlock comparableAbsoluteBlock = AbsoluteBlockExampleFactory::absoluteBlock();
  std::vector<DifferentialBlock> comparableDifferentialBlocks = DifferentialBlockExampleFactory::normalDifferentialBlocks();

  Channel channelAccMetaDataWithCoordinateX1 = ChannelExampleFactory::channelWithAccMetaDataWithCoordinateX();
  Channel channelAccMetaDataWithCoordinateX2 = ChannelExampleFactory::channelWithAccMetaDataWithCoordinateX();
  Channel channelAccMetaDataWithCoordinateY = ChannelExampleFactory::channelWithAccMetaDataWithCoordinateY();
  Channel channelAccMetaDataWithNorm1 = ChannelExampleFactory::channelWithAccMetaDataWithNorm();
  Channel channelAccMetaDataWithNorm2 = ChannelExampleFactory::channelWithAccMetaDataWithNorm();
  Channel channelPpgMetaDataWithWavelength1 = ChannelExampleFactory::channelWithPpgMetaDataWithWavelength();
  Channel channelPpgMetaDataWithWavelength2 = ChannelExampleFactory::channelWithPpgMetaDataWithWavelength();
  Channel channelPpgMetaDataWithColor1 = ChannelExampleFactory::channelWithPpgMetaDataWithColor();
  Channel channelPpgMetaDataWithColor2 = ChannelExampleFactory::channelWithPpgMetaDataWithColor();
  Channel channelPpgMetaDataWithComparableWavelength = ChannelExampleFactory::channelWithPpgMetaDataWithComparableWavelength();
};

TEST_F(ChannelTest, TestGetMethodPpg) {
  PpgMetaData ppgMetaData = PpgMetaDataExampleFactory::ppgMetDataWithColorGreen();
  EXPECT_TRUE(this->channelPpgMetaDataWithColor1.getPpgMetaData().isEqual(ppgMetaData));
  AccMetaData accMetaData = AccMetaDataExampleFactory::accMetaDataNotSet();
  EXPECT_TRUE(this->channelPpgMetaDataWithColor1.getAccMetaData().isEqual(accMetaData));
  EXPECT_TRUE(this->channelPpgMetaDataWithColor1.getAbsoluteBlock().isEqual(this->comparableAbsoluteBlock));
  std::vector<DifferentialBlock> differentialBlocks = this->channelPpgMetaDataWithColor1.getDifferentialBlocks();
  for (size_t i = 0; i < differentialBlocks.size(); i++) {
    EXPECT_TRUE(differentialBlocks[i].isEqual(this->comparableDifferentialBlocks[i]));
  }
}

TEST_F(ChannelTest, TestGetMethodAcc) {
  AccMetaData accMetaData = AccMetaDataExampleFactory::accMetaDataWithCoordinateX();
  EXPECT_TRUE(this->channelAccMetaDataWithCoordinateX1.getAccMetaData().isEqual(accMetaData));
  PpgMetaData ppgMetaData = PpgMetaDataExampleFactory::ppgMetaDataNotSet();
  EXPECT_TRUE(this->channelAccMetaDataWithCoordinateX1.getPpgMetaData().isEqual(ppgMetaData));
  AbsoluteBlock absoluteBlock = AbsoluteBlockExampleFactory::absoluteBlock();
  EXPECT_TRUE(this->channelAccMetaDataWithCoordinateX1.getAbsoluteBlock().isEqual(this->comparableAbsoluteBlock));
  std::vector<DifferentialBlock> differentialBlocks = this->channelAccMetaDataWithCoordinateX1.getDifferentialBlocks();
  for (size_t i = 0; i < differentialBlocks.size(); i++) {
    EXPECT_TRUE(differentialBlocks[i].isEqual(this->comparableDifferentialBlocks[i]));
  }
}

TEST_F(ChannelTest, CompareEqualChannelWithAccCoordinate) {
  EXPECT_TRUE(this->channelAccMetaDataWithCoordinateX1.isEqual(this->channelAccMetaDataWithCoordinateX2));
}

TEST_F(ChannelTest, CompareEqualChannelWithAccNorm) {
  EXPECT_TRUE(this->channelAccMetaDataWithNorm1.isEqual(this->channelAccMetaDataWithNorm2));
}

TEST_F(ChannelTest, CompareEqualChannelWithPpgWavelength) {
  EXPECT_TRUE(this->channelPpgMetaDataWithWavelength1.isEqual(this->channelPpgMetaDataWithWavelength2));
}

TEST_F(ChannelTest, CompareEqualChannelWithPpgColor) {
  EXPECT_TRUE(this->channelPpgMetaDataWithColor1.isEqual(this->channelPpgMetaDataWithColor2));
}

TEST_F(ChannelTest, CompareDifferentChannelWithAccNormAndCoordinate) {
  EXPECT_FALSE(this->channelAccMetaDataWithCoordinateX1.isEqual(this->channelAccMetaDataWithNorm1));
}

TEST_F(ChannelTest, CompareDifferentChannelWithPpgColorAndWavelength) {
  EXPECT_FALSE(this->channelPpgMetaDataWithColor1.isEqual(this->channelPpgMetaDataWithWavelength1));
}

TEST_F(ChannelTest, CompareDifferentChannelWithWavelength) {
  EXPECT_FALSE(this->channelPpgMetaDataWithComparableWavelength.isEqual(this->channelPpgMetaDataWithWavelength1));
}

TEST_F(ChannelTest, CompareDifferentChannelWithCoordinate) {
  EXPECT_FALSE(this->channelAccMetaDataWithCoordinateX1.isEqual(this->channelAccMetaDataWithCoordinateY));
}

TEST_F(ChannelTest, TestSerializeAndDeserializeMethodPpgColor) {
  ProtobufChannel protobufChannel;
  this->channelPpgMetaDataWithColor1.serialize(&protobufChannel);
  Channel channel2 = Channel(protobufChannel);
  EXPECT_TRUE(this->channelPpgMetaDataWithColor1.isEqual(channel2));
}

TEST_F(ChannelTest, TestSerializeAndDeserializeMethodPpgWavelength) {
  ProtobufChannel protobufChannel;
  this->channelPpgMetaDataWithWavelength1.serialize(&protobufChannel);
  Channel channel2 = Channel(protobufChannel);
  EXPECT_TRUE(this->channelPpgMetaDataWithWavelength1.isEqual(channel2));
}

TEST_F(ChannelTest, TestSerializeAndDeserializeMethodAccNorm) {
  ProtobufChannel protobufChannel;
  this->channelAccMetaDataWithNorm1.serialize(&protobufChannel);
  Channel channel2 = Channel(protobufChannel);
  EXPECT_TRUE(this->channelAccMetaDataWithNorm1.isEqual(channel2));
}

TEST_F(ChannelTest, TestSerializeAndDeserializeMethodCoordinate) {
  ProtobufChannel protobufChannel;
  this->channelAccMetaDataWithCoordinateX1.serialize(&protobufChannel);
  Channel channel2 = Channel(protobufChannel);
  EXPECT_TRUE(this->channelAccMetaDataWithCoordinateX1.isEqual(channel2));
}

TEST_F(ChannelTest, CheckChannelPtr) {
  ProtobufChannel protobufChannel;
  EXPECT_NO_THROW(this->channelAccMetaDataWithNorm1.serialize(&protobufChannel));
}

TEST_F(ChannelTest, CheckChannelNullPtr) {
  ProtobufChannel* protobufChannel = nullptr;
  EXPECT_THROW(this->channelAccMetaDataWithNorm1.serialize(protobufChannel), std::invalid_argument);
}
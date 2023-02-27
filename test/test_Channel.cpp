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
  Channel channelWithNormalAbsoluteBlocksAndAccMetaDataWithCoordinateX =
      ChannelExampleFactory::channelWithNormalAbsoluteBlocksAndAccMetaDataWithCoordinateX();
  Channel channelWithNormalDifferentialBlocksAndPpgMetaDataWithNormalWavelength1 =
      ChannelExampleFactory::channelWithNormalDifferentialBlocksAndPpgMetaDataWithNormalWavelength1();
  Channel channelWithNormalAbsoluteBlocksAndAccMetaDataWithNorm1 = ChannelExampleFactory::channelWithNormalAbsoluteBlocksAndAccMetaDataWithNorm();
  Channel channelWithNormalAbsoluteBlocksAndAccMetaDataWithNorm2 = ChannelExampleFactory::channelWithNormalAbsoluteBlocksAndAccMetaDataWithNorm();
  Channel channelWithNormalNegativeAbsoluteBlocksAndAccMetaDataWithNorm =
      ChannelExampleFactory::channelWithNormalNegativeAbsoluteBlocksAndAccMetaDataWithNorm();
  Channel channelWithOneElementAbsoluteBlocksAndAccMetaDataWithNorm =
      ChannelExampleFactory::channelWithOneElementAbsoluteBlocksAndAccMetaDataWithNorm();
  Channel channelWithNormalDifferentialBlocksAndPpgMetaDataWithNormalWavelength2 =
      ChannelExampleFactory::channelWithNormalDifferentialBlocksAndPpgMetaDataWithNormalWavelength2();
  Channel channelWithNormalNegativeDifferentialBlocksAndPpgMetaDataWithNormalWavelength1 = ChannelExampleFactory::channelWithNormalNegativeDifferentialBlocksAndPpgMetaDataWithNormalWavelength1();

};

TEST_F(ChannelTest, TestGetPpgMetaData) {
  PpgMetaData ppgMetaData1 = this->channelWithNormalDifferentialBlocksAndPpgMetaDataWithNormalWavelength1.getPpgMetaData();
  PpgMetaData ppgMetaData2 = PpgMetaData(PpgMetaDataExampleFactory::wavelengthNormal1_nm());
  EXPECT_TRUE(ppgMetaData1.isEqual(ppgMetaData2));

  PpgMetaData ppgMetaData3 = this->channelWithNormalAbsoluteBlocksAndAccMetaDataWithNorm1.getPpgMetaData();
  PpgMetaData ppgMetaData4 = PpgMetaData();
  EXPECT_TRUE(ppgMetaData3.isEqual(ppgMetaData4));
}

TEST_F(ChannelTest, TestGetAccMetaData) {
  AccMetaData accMetaData1 = this->channelWithNormalAbsoluteBlocksAndAccMetaDataWithNorm1.getAccMetaData();
  AccMetaData accMetaData2 = AccMetaData(ProtobufNorm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
  EXPECT_TRUE(accMetaData1.isEqual(accMetaData2));

  AccMetaData accMetaData3 = this->channelWithNormalDifferentialBlocksAndPpgMetaDataWithNormalWavelength1.getAccMetaData();
  AccMetaData accMetaData4 = AccMetaData();
  EXPECT_TRUE(accMetaData3.isEqual(accMetaData4));
}

TEST_F(ChannelTest, TestGetDifferentialBlocks) {
  DifferentialBlocks differentialBlocks1 = this->channelWithNormalDifferentialBlocksAndPpgMetaDataWithNormalWavelength1.getDifferentialBlocks();
  DifferentialValues differentialValues = DifferentialValuesExampleFactory::differentialValuesNormal();
  DifferentialBlocks differentialBlocks2 = {DifferentialBlock(differentialValues)};
  EXPECT_EQ(differentialBlocks1.size(), differentialBlocks2.size());
  for (size_t i = 0; i < differentialBlocks1.size(); i++) {
    EXPECT_TRUE(differentialBlocks1[i].isEqual(differentialBlocks2[i]));
  }

  DifferentialBlocks differentialBlocks3 = this->channelWithNormalAbsoluteBlocksAndAccMetaDataWithNorm1.getDifferentialBlocks();
  DifferentialBlocks differentialBlocks4 = {};
  EXPECT_EQ(differentialBlocks1.size(), differentialBlocks2.size());
  for (size_t i = 0; i < differentialBlocks1.size(); i++) {
    EXPECT_TRUE(differentialBlocks1[i].isEqual(differentialBlocks2[i]));
  }
}

TEST_F(ChannelTest, TestGetAbsoluteBlock) {
  AbsoluteBlock absoluteBlock1 = this->channelWithNormalAbsoluteBlocksAndAccMetaDataWithNorm1.getAbsoluteBlock();
  AbsoluteValues absoluteValues = AbsoluteValuesExampleFactory::absoluteValuesNormal();
  AbsoluteBlock absoluteBlock2 = AbsoluteBlock(absoluteValues);
  EXPECT_TRUE(absoluteBlock1.isEqual(absoluteBlock2));

  AbsoluteBlock absoluteBlock3 = this->channelWithNormalDifferentialBlocksAndPpgMetaDataWithNormalWavelength1.getAbsoluteBlock();
  AbsoluteBlock absoluteBlock4 = AbsoluteBlock();
  EXPECT_TRUE(absoluteBlock3.isEqual(absoluteBlock4));
}

TEST_F(ChannelTest, CompareEqualChannels) {
  EXPECT_TRUE(this->channelWithNormalAbsoluteBlocksAndAccMetaDataWithNorm1.isEqual(this->channelWithNormalAbsoluteBlocksAndAccMetaDataWithNorm2));
}

TEST_F(ChannelTest, CompareNotEqualInPpgMetaData) {
  EXPECT_FALSE(this->channelWithNormalDifferentialBlocksAndPpgMetaDataWithNormalWavelength1.isEqual(this->channelWithNormalDifferentialBlocksAndPpgMetaDataWithNormalWavelength2));
}

TEST_F(ChannelTest, CompareNotEqualInAccMetaData) {
  EXPECT_FALSE(this->channelWithNormalAbsoluteBlocksAndAccMetaDataWithNorm1.isEqual(this->channelWithNormalAbsoluteBlocksAndAccMetaDataWithNorm2));
}

TEST_F(ChannelTest, CompareNotEqualInAbsoluteBlock) {
  EXPECT_FALSE(this->channelWithNormalAbsoluteBlocksAndAccMetaDataWithNorm1.isEqual(this->channelWithOneElementAbsoluteBlocksAndAccMetaDataWithNorm));
}

TEST_F(ChannelTest, CompareNotEqualInDifferentialBlocks) {
  EXPECT_FALSE(this->channelWithNormalNegativeDifferentialBlocksAndPpgMetaDataWithNormalWavelength1.isEqual(this->channelWithNormalDifferentialBlocksAndPpgMetaDataWithNormalWavelength1));
}

TEST_F(ChannelTest, CompareEmptyWithEmptyChannel) {
  Channel channel1 = Channel();
  Channel channel2 = Channel();
  EXPECT_TRUE(channel1.isEqual(channel2));
}


// switchTo, Serialize, To Json



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
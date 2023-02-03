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

class ChannelTest : public ::testing::Test {
 protected:
  Channel channelAccMetaDataSetCoordinateX1;
  Channel channelAccMetaDataSetCoordinateX2;
  Channel channelAccMetaDataSetCoordinateY;
  Channel channelAccMetaDataSetNorm1;
  Channel channelAccMetaDataSetNorm2;
  Channel channelPpgMetaDataSetWavelength1;
  Channel channelPpgMetaDataSetWavelength2;
  Channel channelPpgMetaDataSetColor1;
  Channel channelPpgMetaDataSetColor2;
  Channel channelPpgMetaDataSetComparableWavelength;

  uint32_t comparableWavelength_nm = 100;
  uint32_t normalWavelength_nm = 255;
  uint32_t notSetWavelength_nm = 0;
  AccMetaData setCoordinateYAccMetaData = AccMetaData(ProtobufCoordinate::COORDINATE_Y, ProtobufNorm::NORM_NONE);
  AccMetaData setCoordinateXAccMetaData = AccMetaData(ProtobufCoordinate::COORDINATE_X, ProtobufNorm::NORM_NONE);
  AccMetaData setNormAccMetaData = AccMetaData(ProtobufCoordinate::COORDINATE_NONE, ProtobufNorm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
  AccMetaData notSetAccMetaData = AccMetaData(ProtobufCoordinate::COORDINATE_NONE, ProtobufNorm::NORM_NONE);
  PpgMetaData setColorPpgMetaData = PpgMetaData(ProtobufColor::COLOR_BLUE, notSetWavelength_nm);
  PpgMetaData notSetPpgMetaData = PpgMetaData(ProtobufColor::COLOR_NONE, notSetWavelength_nm);
  PpgMetaData setWavelengthPpgMetaData = PpgMetaData(ProtobufColor::COLOR_NONE, normalWavelength_nm);
  PpgMetaData setCompareableWavelengthPpgMetaData = PpgMetaData(ProtobufColor::COLOR_NONE, comparableWavelength_nm);
  std::vector<int32_t> values = {};
  AbsoluteBlock absoluteBlock = AbsoluteBlock(values);
  std::vector<int32_t> diffValues = {12, 15, 20};
  DifferentialBlock diffBlock = DifferentialBlock(diffValues);
  std::vector<DifferentialBlock> differentialBlocks = {diffBlock};
  DataForm dataform = DataForm::DIFFERENTIAL;
  virtual void SetUp() {
    this->channelAccMetaDataSetCoordinateX1 =
        Channel(this->dataform, this->differentialBlocks, this->absoluteBlock, this->setCoordinateXAccMetaData, this->notSetPpgMetaData);
    this->channelAccMetaDataSetCoordinateX2 =
        Channel(this->dataform, this->differentialBlocks, this->absoluteBlock, this->setCoordinateXAccMetaData, this->notSetPpgMetaData);
    this->channelAccMetaDataSetCoordinateY =
        Channel(this->dataform, this->differentialBlocks, this->absoluteBlock, this->setCoordinateYAccMetaData, this->notSetPpgMetaData);
    this->channelAccMetaDataSetNorm1 =
        Channel(this->dataform, this->differentialBlocks, this->absoluteBlock, this->setNormAccMetaData, this->notSetPpgMetaData);
    this->channelAccMetaDataSetNorm2 =
        Channel(this->dataform, this->differentialBlocks, this->absoluteBlock, this->setNormAccMetaData, this->notSetPpgMetaData);
    this->channelPpgMetaDataSetWavelength1 =
        Channel(this->dataform, this->differentialBlocks, this->absoluteBlock, this->notSetAccMetaData, this->setWavelengthPpgMetaData);
    this->channelPpgMetaDataSetWavelength2 =
        Channel(this->dataform, this->differentialBlocks, this->absoluteBlock, this->notSetAccMetaData, this->setWavelengthPpgMetaData);
    this->channelPpgMetaDataSetColor1 =
        Channel(this->dataform, this->differentialBlocks, this->absoluteBlock, this->notSetAccMetaData, this->setColorPpgMetaData);
    this->channelPpgMetaDataSetColor2 =
        Channel(this->dataform, this->differentialBlocks, this->absoluteBlock, this->notSetAccMetaData, this->setColorPpgMetaData);
    this->channelPpgMetaDataSetComparableWavelength =
        Channel(this->dataform, this->differentialBlocks, this->absoluteBlock, this->notSetAccMetaData, this->setCompareableWavelengthPpgMetaData);
  }
};

TEST_F(ChannelTest, CheckIfExceptionIsThrownWhenBothMetadataAreSet) {
  EXPECT_THROW(Channel channel =
                   Channel(this->dataform, this->differentialBlocks, this->absoluteBlock, this->setCoordinateXAccMetaData, this->setColorPpgMetaData),
               std::invalid_argument);
}

TEST_F(ChannelTest, CheckIfExepectionIsNotThrownForAccCoordinate) {
  EXPECT_NO_THROW(Channel channelAccMetaDataSetCoordinate1 = Channel(this->dataform, this->differentialBlocks, this->absoluteBlock,
                                                                     this->setCoordinateXAccMetaData, this->notSetPpgMetaData););
}

TEST_F(ChannelTest, CheckIfExpectionIsNotThrownForAccNorm) {
  EXPECT_NO_THROW(Channel channelAccMetaDataSetNorm1 =
                      Channel(this->dataform, this->differentialBlocks, this->absoluteBlock, this->setNormAccMetaData, this->notSetPpgMetaData););
}

TEST_F(ChannelTest, CheckIfExpectionIsNotThrownForPpgColor) {
  EXPECT_NO_THROW(Channel channelPpgMetaDataSetColor1 =
                      Channel(this->dataform, this->differentialBlocks, this->absoluteBlock, this->notSetAccMetaData, this->setColorPpgMetaData););
}

TEST_F(ChannelTest, CheckIfExpectionIsNotThrownForPpgWavelength) {
  EXPECT_NO_THROW(Channel channelPpgMetaDataSetWavelength1 = Channel(this->dataform, this->differentialBlocks, this->absoluteBlock,
                                                                     this->notSetAccMetaData, this->setWavelengthPpgMetaData););
}

TEST_F(ChannelTest, TestGetMethodPpg) {
  EXPECT_EQ(this->channelPpgMetaDataSetColor1.getPpgMetData().getColor(), this->setColorPpgMetaData.getColor());
  EXPECT_EQ(this->channelPpgMetaDataSetColor1.getPpgMetData().getWavelength(), this->setColorPpgMetaData.getWavelength());
  EXPECT_EQ(this->channelPpgMetaDataSetColor1.getAccMetaData().getCoordinate(), this->notSetAccMetaData.getCoordinate());
  EXPECT_EQ(this->channelPpgMetaDataSetColor1.getAccMetaData().getNorm(), this->notSetAccMetaData.getNorm());
  EXPECT_EQ(this->channelPpgMetaDataSetColor1.getAbsoluteBlock().getValues(), this->absoluteBlock.getValues());
  EXPECT_EQ(this->channelPpgMetaDataSetColor1.getDataform(), this->dataform);
  for (int i = 0; i < this->channelPpgMetaDataSetColor1.getDifferentialBlocks().size(); i++) {
    EXPECT_EQ(this->channelPpgMetaDataSetColor1.getDifferentialBlocks()[i].getDiffValues(), this->differentialBlocks[i].getDiffValues());
  }
}

TEST_F(ChannelTest, TestGetMethodAcc) {
  EXPECT_EQ(this->channelAccMetaDataSetCoordinateX1.getAccMetaData().getCoordinate(), this->setCoordinateXAccMetaData.getCoordinate());
  EXPECT_EQ(this->channelAccMetaDataSetCoordinateX1.getAccMetaData().getNorm(), this->setCoordinateXAccMetaData.getNorm());
  EXPECT_EQ(this->channelAccMetaDataSetCoordinateX1.getPpgMetData().getColor(), this->notSetPpgMetaData.getColor());
  EXPECT_EQ(this->channelAccMetaDataSetCoordinateX1.getPpgMetData().getWavelength(), this->notSetPpgMetaData.getWavelength());
  EXPECT_EQ(this->channelAccMetaDataSetCoordinateX1.getAbsoluteBlock().getValues(), this->absoluteBlock.getValues());
  EXPECT_EQ(this->channelAccMetaDataSetCoordinateX1.getDataform(), this->dataform);
  for (int i = 0; i < this->channelAccMetaDataSetCoordinateX1.getDifferentialBlocks().size(); i++) {
    EXPECT_EQ(this->channelAccMetaDataSetCoordinateX1.getDifferentialBlocks()[i].getDiffValues(), this->differentialBlocks[i].getDiffValues());
  }
}

TEST_F(ChannelTest, CompareEqualChannelWithAccCoordinate) {
  EXPECT_TRUE(this->channelAccMetaDataSetCoordinateX1.isEqual(this->channelAccMetaDataSetCoordinateX2));
}

TEST_F(ChannelTest, CompareEqualChannelWithAccNorm) {
  EXPECT_TRUE(this->channelAccMetaDataSetNorm1.isEqual(this->channelAccMetaDataSetNorm2));
}

TEST_F(ChannelTest, CompareEqualChannelWithPpgWavelength) {
  EXPECT_TRUE(this->channelPpgMetaDataSetWavelength1.isEqual(this->channelPpgMetaDataSetWavelength2));
}

TEST_F(ChannelTest, CompareEqualChannelWithPpgColor) {
  EXPECT_TRUE(this->channelPpgMetaDataSetColor1.isEqual(this->channelPpgMetaDataSetColor2));
}

TEST_F(ChannelTest, CompareDifferentChannelWithAccNormAndCoordinate) {
  EXPECT_FALSE(this->channelAccMetaDataSetCoordinateX1.isEqual(this->channelAccMetaDataSetNorm1));
}

TEST_F(ChannelTest, CompareDifferentChannelWithPpgColorAndWavelength) {
  EXPECT_FALSE(this->channelPpgMetaDataSetColor1.isEqual(this->channelPpgMetaDataSetWavelength1));
}

TEST_F(ChannelTest, CompareDifferentChannelWithWavelength) {
  EXPECT_FALSE(this->channelPpgMetaDataSetComparableWavelength.isEqual(this->channelPpgMetaDataSetWavelength1));
}

TEST_F(ChannelTest, CompareDifferentChannelWithCoordinate) {
  EXPECT_FALSE(this->channelAccMetaDataSetCoordinateX1.isEqual(this->channelAccMetaDataSetCoordinateY));
}

TEST_F(ChannelTest, TestSerializeAndDeserializeMethodPpgColor) {
  ProtobufChannel protobufChannel;
  this->channelPpgMetaDataSetColor1.serialize(&protobufChannel);
  Channel channel2 = Channel(protobufChannel);
  EXPECT_TRUE(this->channelPpgMetaDataSetColor1.isEqual(channel2));
}

TEST_F(ChannelTest, TestSerializeAndDeserializeMethodPpgWavelength) {
  ProtobufChannel protobufChannel;
  this->channelPpgMetaDataSetWavelength1.serialize(&protobufChannel);
  Channel channel2 = Channel(protobufChannel);
  EXPECT_TRUE(this->channelPpgMetaDataSetWavelength1.isEqual(channel2));
}

TEST_F(ChannelTest, TestSerializeAndDeserializeMethodAccNorm) {
  ProtobufChannel protobufChannel;
  this->channelAccMetaDataSetNorm1.serialize(&protobufChannel);
  Channel channel2 = Channel(protobufChannel);
  EXPECT_TRUE(this->channelAccMetaDataSetNorm1.isEqual(channel2));
}

TEST_F(ChannelTest, TestSerializeAndDeserializeMethodCoordinate) {
  ProtobufChannel protobufChannel;
  this->channelAccMetaDataSetCoordinateX1.serialize(&protobufChannel);
  Channel channel2 = Channel(protobufChannel);
  EXPECT_TRUE(this->channelAccMetaDataSetCoordinateX1.isEqual(channel2));
}

TEST_F(ChannelTest, CheckChannelPtr) {
  ProtobufChannel protobufChannel;
  EXPECT_NO_THROW(this->channelAccMetaDataSetNorm1.serialize(&protobufChannel));
}

TEST_F(ChannelTest, CheckChannelNullPtr) {
  ProtobufChannel* protobufChannel = nullptr;
  EXPECT_THROW(this->channelAccMetaDataSetNorm1.serialize(protobufChannel), std::invalid_argument);
}
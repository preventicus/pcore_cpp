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
#include "Exceptions.h"

////////////////////////////////////////////////////////////////
//                        Test Getter                         //
////////////////////////////////////////////////////////////////

TEST(ChannelTest, TestGetPpgMetaDataWithChannelNotSet) {
  auto channel = ChannelExampleFactory::channelNotSet();
  EXPECT_TRUE(channel.getPpgMetaData() == std::nullopt);
}

TEST(ChannelTest, TestGetPpgMetaDataWithChannelWithAbsoluteBlockAndPpgMetaData) {
  auto channel = ChannelExampleFactory::channelWithAbsoluteBlockAndPpgMetaData();
  auto ppgMetaData = PpgMetaDataExampleFactory::ppgMetaDataWithWavelength255();
  EXPECT_TRUE(channel.getPpgMetaData() == ppgMetaData);
}

TEST(ChannelTest, TestGetAccMetaDataWithChannelNotSet) {
  auto channel = ChannelExampleFactory::channelNotSet();
  EXPECT_TRUE(channel.getAccMetaData() == std::nullopt);
}

TEST(ChannelTest, TestGetAccMetaDataWithChannelWithAbsoluteBlockAndAccMetaData) {
  auto channel = ChannelExampleFactory::channelWithAbsoluteBlockAndAccMetaData();
  auto accMetaData = AccMetaDataExampleFactory::accMetaDataWithNormEuclideanDifferencesNorm();
  EXPECT_TRUE(channel.getAccMetaData() == accMetaData);
}

TEST(ChannelTest, TestGetDifferentialBlocksWithChannelWithDifferentialBlocksAndAccMetaData) {
  auto channel = ChannelExampleFactory::channelWithDifferentialBlocksAndAccMetaData();
  auto actualDifferentialBlocks = channel.getDifferentialBlocks();
  auto expectedDifferentialBlocks = DifferentialBlockExampleFactory::differentialBlocksWithThreeMixedDifferentialBlocks();
  EXPECT_EQ(actualDifferentialBlocks.size(), expectedDifferentialBlocks.size());
  for (size_t i = 0; i < actualDifferentialBlocks.size(); i++) {
    EXPECT_TRUE(actualDifferentialBlocks[i] == expectedDifferentialBlocks[i]);
  }
}

TEST(ChannelTest, TestGetAbsoluteBlockWithChannelNotSet) {
  auto channel = ChannelExampleFactory::channelNotSet();
  auto absoluteBlock = AbsoluteBlockExampleFactory::absoluteBlockNotSet();
  EXPECT_TRUE(channel.getAbsoluteBlock() == absoluteBlock);
}

TEST(ChannelTest, TestGetAbsoluteBlockWithChannelWithAbsoluteBlockAndPpgMetaData) {
  auto channel = ChannelExampleFactory::channelWithAbsoluteBlockAndPpgMetaData();
  auto actualAbsoluteBlock = channel.getAbsoluteBlock();
  auto expectedAbsoluteValues = AbsoluteBlockExampleFactory::absoluteBlockWithThreeMixedAbsoluteValues();
  EXPECT_TRUE(actualAbsoluteBlock == expectedAbsoluteValues);
}

TEST(ChannelTest, TestGetDataFormWithChannelNotSet) {
  auto channel = ChannelExampleFactory::channelNotSet();
  EXPECT_TRUE(channel.getDataForm() == DataForm::DATA_FORM_NONE);
}

TEST(ChannelTest, TestGetDataFormWithChannelWithAbsoluteBlockAndPpgMetaData) {
  auto channel = ChannelExampleFactory::channelWithAbsoluteBlockAndPpgMetaData();
  EXPECT_TRUE(channel.getDataForm() == DataForm::DATA_FORM_ABSOLUTE);
}

TEST(ChannelTest, TestGetDataFormWithChannelWithDifferentialBlocksAndPpgMetaData) {
  auto channel = ChannelExampleFactory::channelWithDifferentialBlocksAndPpgMetaData();
  EXPECT_TRUE(channel.getDataForm() == DataForm::DATA_FORM_DIFFERENTIAL);
}

TEST(ChannelTest, TestGetSensorTypeWithChannelNotSet) {
  auto channel = ChannelExampleFactory::channelNotSet();
  EXPECT_TRUE(channel.getSensorType() == SensorTypeProtobuf::SENSOR_TYPE_NONE);
}

TEST(ChannelTest, TestGetSensorTypeWithChannelWithAbsoluteBlockAndAccMetaData) {
  auto channel = ChannelExampleFactory::channelWithAbsoluteBlockAndAccMetaData();
  EXPECT_TRUE(channel.getSensorType() == SensorTypeProtobuf::SENSOR_TYPE_ACC);
}

TEST(ChannelTest, TestGetSensorTypeWithChannelWithAbsoluteBlockAndPpgMetaData) {
  auto channel = ChannelExampleFactory::channelWithAbsoluteBlockAndPpgMetaData();
  EXPECT_TRUE(channel.getSensorType() == SensorTypeProtobuf::SENSOR_TYPE_PPG);
}

////////////////////////////////////////////////////////////////
//                        Test isEqual                        //
////////////////////////////////////////////////////////////////

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

TEST(ChannelTest, TestIsEqualWithchannelWithAbsoluteBlockAndPpgMetaDataAndChannelWithAbsoluteBlockAndAccMetaData) {
  auto channel1 = ChannelExampleFactory::channelWithAbsoluteBlockAndPpgMetaData();
  auto channel2 = ChannelExampleFactory::channelWithAbsoluteBlockAndAccMetaData();
  EXPECT_FALSE(channel1 == channel2);
}

TEST(ChannelTest, TestIsEqualWithChannelWithAbsoluteBlockAndPpgMetaDataAndChannelWithDifferentialBlocksAndPpgMetaData) {
  auto channel1 = ChannelExampleFactory::channelWithAbsoluteBlockAndPpgMetaData();
  auto channel2 = ChannelExampleFactory::channelWithDifferentialBlocksAndPpgMetaData();
  EXPECT_FALSE(channel1 == channel2);
}

TEST(ChannelTest, TestIsEqualWithChannelWithAbsoluteBlockAndAccMetaDataAndChannelWithDifferentialBlocksAndPpgMetaData) {
  auto channel1 = ChannelExampleFactory::channelWithAbsoluteBlockAndAccMetaData();
  auto channel2 = ChannelExampleFactory::channelWithDifferentialBlocksAndPpgMetaData();
  EXPECT_FALSE(channel1 == channel2);
}

TEST(ChannelTest, TestIsEqualWithChannelWithAbsoluteBlockForNotEqualTestAndChannelWithAbsoluteBlockAndPpgMetaData) {
  auto channel1 = ChannelExampleFactory::channelWithAbsoluteBlockForNotEqualTest();
  auto channel2 = ChannelExampleFactory::channelWithAbsoluteBlockAndPpgMetaData();
  EXPECT_FALSE(channel1 == channel2);
}

TEST(ChannelTest, TestIsEqualWithChannelWithDifferentialBlocksForNotEqualTestAndChannelWithDifferentialBlocksAndPpgMetaData) {
  auto channel1 = ChannelExampleFactory::channelWithDifferentialBlocksForNotEqualTest();
  auto channel2 = ChannelExampleFactory::channelWithDifferentialBlocksAndPpgMetaData();
  EXPECT_FALSE(channel1 == channel2);
}

TEST(ChannelTest, TestIsEqualWithChannelWithNotSetAbsoluteBlockAndNoSetMetaData) {
  auto channel1 = ChannelExampleFactory::channelWithNotSetAbsoluteBlockAndNoSetMetaData();
  auto channel2 = ChannelExampleFactory::channelWithNotSetAbsoluteBlockAndNoSetMetaData();
  EXPECT_TRUE(channel1 == channel2);
}

TEST(ChannelTest, TestIsEqualWithChannelWithNotSetAbsoluteBlockAndNoSetMetaDataAndChannelNotSet) {
  auto channel1 = ChannelExampleFactory::channelWithNotSetAbsoluteBlockAndNoSetMetaData();
  auto channel2 = ChannelExampleFactory::channelNotSet();
  EXPECT_FALSE(channel1 == channel2);
}

TEST(ChannelTest, TestIsEqualChannelNotSet) {
  auto channel1 = ChannelExampleFactory::channelNotSet();
  auto channel2 = ChannelExampleFactory::channelNotSet();
  EXPECT_TRUE(channel1 == channel2);
}

////////////////////////////////////////////////////////////////
//                      Test isNotEqual                       //
////////////////////////////////////////////////////////////////

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

TEST(ChannelTest, TestIsNotEqualWithChannelWithAbsoluteBlockAndPpgMetaDataAndChannelWithAbsoluteBlockAndAccMetaData) {
  auto channel1 = ChannelExampleFactory::channelWithAbsoluteBlockAndPpgMetaData();
  auto channel2 = ChannelExampleFactory::channelWithAbsoluteBlockAndAccMetaData();
  EXPECT_TRUE(channel1 != channel2);
}

TEST(ChannelTest, TestIsNotEqualWithChannelWithAbsoluteBlockAndPpgMetaDataAndChannelWithDifferentialBlocksAndPpgMetaData) {
  auto channel1 = ChannelExampleFactory::channelWithAbsoluteBlockAndPpgMetaData();
  auto channel2 = ChannelExampleFactory::channelWithDifferentialBlocksAndPpgMetaData();
  EXPECT_TRUE(channel1 != channel2);
}

TEST(ChannelTest, TestIsNotEqualWithChannelWithAbsoluteBlockAndAccMetaDataAndChannelWithDifferentialBlocksAndPpgMetaData) {
  auto channel1 = ChannelExampleFactory::channelWithAbsoluteBlockAndAccMetaData();
  auto channel2 = ChannelExampleFactory::channelWithDifferentialBlocksAndPpgMetaData();
  EXPECT_TRUE(channel1 != channel2);
}

TEST(ChannelTest, TestIsNotEqualWithChannelWithAbsoluteBlockForNotEqualTestAndChannelWithAbsoluteBlockAndPpgMetaData) {
  auto channel1 = ChannelExampleFactory::channelWithAbsoluteBlockForNotEqualTest();
  auto channel2 = ChannelExampleFactory::channelWithAbsoluteBlockAndPpgMetaData();
  EXPECT_TRUE(channel1 != channel2);
}

TEST(ChannelTest, TestIsNotEqualWithChannelWithDifferentialBlocksForNotEqualTestAndChannelWithDifferentialBlocksAndPpgMetaData) {
  auto channel1 = ChannelExampleFactory::channelWithDifferentialBlocksForNotEqualTest();
  auto channel2 = ChannelExampleFactory::channelWithDifferentialBlocksAndPpgMetaData();
  EXPECT_TRUE(channel1 != channel2);
}

TEST(ChannelTest, TestIsNotEqualWithChannelWithNotSetAbsoluteBlockAndNoSetMetaData) {
  auto channel1 = ChannelExampleFactory::channelWithNotSetAbsoluteBlockAndNoSetMetaData();
  auto channel2 = ChannelExampleFactory::channelWithNotSetAbsoluteBlockAndNoSetMetaData();
  EXPECT_FALSE(channel1 != channel2);
}

TEST(ChannelTest, TestIsNotEqualWithChannelWithNotSetAbsoluteBlockAndNoSetMetaDataAndChannelNotSet) {
  auto channel1 = ChannelExampleFactory::channelWithNotSetAbsoluteBlockAndNoSetMetaData();
  auto channel2 = ChannelExampleFactory::channelNotSet();
  EXPECT_TRUE(channel1 != channel2);
}

TEST(ChannelTest, TestIsNotEqualWithChannelNotSet) {
  auto channel1 = ChannelExampleFactory::channelNotSet();
  auto channel2 = ChannelExampleFactory::channelNotSet();
  EXPECT_FALSE(channel1 != channel2);
}

////////////////////////////////////////////////////////////////
//                        Test toJson                         //
////////////////////////////////////////////////////////////////

TEST(ChannelTest, TestToJsonWithChannelWithDifferentialBlocksAndAccMetaData) {
  auto channel = ChannelExampleFactory::channelWithDifferentialBlocksAndAccMetaData();
  auto channelJson1 = channel.toJson();
  auto channelJson2 = ChannelExampleFactory::buildChannelJson(channel);
  EXPECT_TRUE(channelJson1.toStyledString() == channelJson2.toStyledString());
}

TEST(ChannelTest, TestToJsonWithChannelWithDifferentialBlocksAndPpgMetaData) {
  auto channel = ChannelExampleFactory::channelWithDifferentialBlocksAndPpgMetaData();
  auto channelJson1 = channel.toJson();
  auto channelJson2 = ChannelExampleFactory::buildChannelJson(channel);
  EXPECT_TRUE(channelJson1.toStyledString() == channelJson2.toStyledString());
}

TEST(ChannelTest, TestToJsonWithChannelWithAbsoluteBlockAndAccMetaData) {
  auto channel = ChannelExampleFactory::channelWithAbsoluteBlockAndAccMetaData();
  auto channelJson1 = channel.toJson();
  auto channelJson2 = ChannelExampleFactory::buildChannelJson(channel);
  EXPECT_TRUE(channelJson1.toStyledString() == channelJson2.toStyledString());
}

TEST(ChannelTest, TestToJsonWithChannelWithAbsoluteBlockAndPpgMetaData) {
  auto channel = ChannelExampleFactory::channelWithAbsoluteBlockAndPpgMetaData();
  auto channelJson1 = channel.toJson();
  auto channelJson2 = ChannelExampleFactory::buildChannelJson(channel);
  EXPECT_TRUE(channelJson1.toStyledString() == channelJson2.toStyledString());
}

TEST(ChannelTest, TestToJsonWithChannelNotSet) {
  auto channel = ChannelExampleFactory::channelNotSet();
  auto channelJson1 = channel.toJson();
  auto channelJson2 = ChannelExampleFactory::buildChannelJson(channel);
  EXPECT_TRUE(channelJson1.toStyledString() == channelJson2.toStyledString());
}

////////////////////////////////////////////////////////////////
//                        Test isSet                          //
////////////////////////////////////////////////////////////////

TEST(ChannelTest, TestIsSetWithChannelNotSet) {
  auto channel = ChannelExampleFactory::channelNotSet();
  EXPECT_FALSE(channel.isSet());
}

TEST(ChannelTest, TestIsSetWithChannelWithAbsoluteBlockAndPpgMetaData) {
  auto channel = ChannelExampleFactory::channelWithAbsoluteBlockAndPpgMetaData();
  EXPECT_TRUE(channel.isSet());
}

TEST(ChannelTest, TestIsSetWithChannelWithDifferentialBlocksAndPpgMetaData) {
  auto channel = ChannelExampleFactory::channelWithDifferentialBlocksAndPpgMetaData();
  EXPECT_TRUE(channel.isSet());
}

TEST(ChannelTest, TestIsSetWithChannelWithAbsoluteBlockAndAccMetaData) {
  auto channel = ChannelExampleFactory::channelWithAbsoluteBlockAndAccMetaData();
  EXPECT_TRUE(channel.isSet());
}

TEST(ChannelTest, TestIsSetWithChannelWithNotSetAbsoluteBlockAndNoSetMetaData) {
  auto channel = ChannelExampleFactory::channelWithNotSetAbsoluteBlockAndNoSetMetaData();
  EXPECT_TRUE(channel.isSet());
}

TEST(ChannelTest, TestIsSetWithChannelWithAbsoluteBlockAndNoSetMetaData) {
  auto channel = ChannelExampleFactory::channelWithAbsoluteBlockAndNoSetMetaData();
  EXPECT_TRUE(channel.isSet());
}

////////////////////////////////////////////////////////////////
//                       Test serialize                       //
////////////////////////////////////////////////////////////////

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

TEST(ChannelTest, TestSerializeThrowDueToNullPointer) {
  auto channel = ChannelExampleFactory::channelNotSet();
  ChannelProtobuf* channelProtobuf = nullptr;
  EXPECT_THROW(channel.serialize(channelProtobuf), NullPointerException);
}

TEST(ChannelTest, TestSerializeThrowDueToDataFromAbsolute) {
  auto channel = ChannelExampleFactory::channelWithAbsoluteBlockAndNoSetMetaData();
  ChannelProtobuf channelProtobuf;
  EXPECT_THROW(channel.serialize(&channelProtobuf), WrongDataFormException);
}

TEST(ChannelTest, TestSerializeWithChannelNotSet) {
  auto channel1 = ChannelExampleFactory::channelNotSet();
  ChannelProtobuf channelProtobuf;
  channel1.serialize(&channelProtobuf);
  auto channel2 = Channel(channelProtobuf);
  EXPECT_TRUE(channel1 == channel2);
}

TEST(ChannelTest, TestSerializeNoThrow) {
  auto channel = ChannelExampleFactory::channelWithDifferentialBlocksAndPpgMetaData();
  ChannelProtobuf channelProtobuf;
  EXPECT_NO_THROW(channel.serialize(&channelProtobuf));
}

////////////////////////////////////////////////////////////////
//                     Test switchDataForm                    //
////////////////////////////////////////////////////////////////

TEST(ChannelTest, TestSwitchDataFormWithBlockIdxsWithChannelWithAbsoluteValuesForSwitchDataFormTest) {
  BlockIdxs blockIdxs = {0, 11, 20};
  auto channelWithAbsoluteBlock = ChannelExampleFactory::channelWithAbsoluteValuesForSwitchDataFormTest();
  channelWithAbsoluteBlock.switchDataForm(blockIdxs);
  auto absoluteBlock = AbsoluteBlockExampleFactory::absoluteBlockNotSet();
  EXPECT_TRUE(channelWithAbsoluteBlock.getAbsoluteBlock() == absoluteBlock);
  auto expectedDifferentialBlocks = DifferentialBlockExampleFactory::differentialBlocksForSwitchDataFormTest();
  auto actualDifferentialBlocks = channelWithAbsoluteBlock.getDifferentialBlocks();
  auto actualDifferentialBlocksSize = actualDifferentialBlocks.size();
  EXPECT_EQ(actualDifferentialBlocksSize, expectedDifferentialBlocks.size());
  for (size_t i = 0; i < actualDifferentialBlocksSize; i++) {
    EXPECT_TRUE(actualDifferentialBlocks[i] == expectedDifferentialBlocks[i]);
  }
}

TEST(ChannelTest, TestSwitchDataFormWithChannelWithDifferentialValuesForSwitchDataFormTest) {
  auto channelWithDifferentialBlocks = ChannelExampleFactory::channelWithDifferentialValuesForSwitchDataFormTest();
  channelWithDifferentialBlocks.switchDataForm();
  EXPECT_EQ(channelWithDifferentialBlocks.getDifferentialBlocks().size(), 0);
  auto expectedAbsoluteBlock = AbsoluteBlockExampleFactory::absoluteBlockForSwitchDataFormTest();
  auto actualAbsoluteBlock = channelWithDifferentialBlocks.getAbsoluteBlock();
  EXPECT_TRUE(actualAbsoluteBlock == expectedAbsoluteBlock);
}

TEST(ChannelTest, TestSwitchDataFormWithBlockIdxsWithChannelNotSet) {
  auto channel = ChannelExampleFactory::channelNotSet();
  BlockIdxs blockIdxs = {};
  channel.switchDataForm(blockIdxs);
  EXPECT_FALSE(channel.isSet());
}

TEST(ChannelTest, TestSwitchDataFormWithChannelNotSet) {
  auto channel = ChannelExampleFactory::channelNotSet();
  channel.switchDataForm();
  EXPECT_FALSE(channel.isSet());
}

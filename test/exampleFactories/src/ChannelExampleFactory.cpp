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

#include "ChannelExampleFactory.h"

// Channel ChannelExampleFactory::channelWithNormalAbsoluteBlocksAndAccMetaDataWithNorm() {
//   AccMetaData accMetaData = AccMetaData(ProtobufNorm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
//   AbsoluteValues absoluteValues = AbsoluteValuesExampleFactory::absoluteValuesNormal();
//   AbsoluteBlock absoluteBlock = AbsoluteBlock(absoluteValues);
//   return Channel(accMetaData, absoluteBlock);
// }
//
// Channel ChannelExampleFactory::channelWithNormalAbsoluteBlocksAndAccMetaDataWithCoordinateX() {
//   AccMetaData accMetaData = AccMetaData(ProtobufCoordinate::COORDINATE_X);
//   AbsoluteValues absoluteValues = AbsoluteValuesExampleFactory::absoluteValuesNormal();
//   AbsoluteBlock absoluteBlock = AbsoluteBlock(absoluteValues);
//   return Channel(accMetaData, absoluteBlock);
// }
//
// Channel ChannelExampleFactory::channelWithNormalNegativeAbsoluteBlocksAndAccMetaDataWithNorm() {
//   AccMetaData accMetaData = AccMetaData(ProtobufNorm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
//   AbsoluteValues absoluteValues = AbsoluteValuesExampleFactory::absoluteValuesNormalNegative();
//   AbsoluteBlock absoluteBlock = AbsoluteBlock(absoluteValues);
//   return Channel(accMetaData, absoluteBlock);
// }
//
// Channel ChannelExampleFactory::channelWithOneElementAbsoluteBlocksAndAccMetaDataWithNorm() {
//   AccMetaData accMetaData = AccMetaData(ProtobufNorm::NORM_EUCLIDEAN_DIFFERENCES_NORM);
//   AbsoluteValues absoluteValues = AbsoluteValuesExampleFactory::absoluteValuesWithOneElement();
//   AbsoluteBlock absoluteBlock = AbsoluteBlock(absoluteValues);
//   return Channel(accMetaData, absoluteBlock);
// }
//
// Channel ChannelExampleFactory::channelWithNormalDifferentialBlocksAndPpgMetaDataWithNormalWavelength1() {
//   PpgMetaData ppgMetaData = PpgMetaData(PpgMetaDataExampleFactory::wavelengthNormal1_nm());
//   DifferentialValues differentialValues = DifferentialValuesExampleFactory::differentialValuesNormal();
//   DifferentialBlocks differentialBlocks = {DifferentialBlock(differentialValues)};
//   return Channel(ppgMetaData, differentialBlocks);
// }
//
// Channel ChannelExampleFactory::channelWithNormalDifferentialBlocksAndPpgMetaDataWithNormalWavelength2() {
//   PpgMetaData ppgMetaData = PpgMetaData(PpgMetaDataExampleFactory::wavelengthNormal2_nm());
//   DifferentialValues differentialValues = DifferentialValuesExampleFactory::differentialValuesNormal();
//   DifferentialBlocks differentialBlocks = {DifferentialBlock(differentialValues)};
//   return Channel(ppgMetaData, differentialBlocks);
// }
//
// Channel ChannelExampleFactory::channelWithNormalNegativeDifferentialBlocksAndPpgMetaDataWithNormalWavelength1() {
//   PpgMetaData ppgMetaData = PpgMetaData(PpgMetaDataExampleFactory::wavelengthNormal2_nm());
//   DifferentialValues differentialValues = DifferentialValuesExampleFactory::differentialValuesNormal();
//   DifferentialBlocks differentialBlocks = {DifferentialBlock(differentialValues)};
//   return Channel(ppgMetaData, differentialBlocks);
// }

Channel ChannelExampleFactory::channelWithAbsoluteValuesForTestSwitchTo() {
  PpgMetaData ppgMetaData = PpgMetaData(PpgMetaDataExampleFactory::ppgMetaDataWithWavelength255());
  AbsoluteBlock absoluteBlock = AbsoluteBlockExampleFactory::absoluteBlockForTestSwitchTo();
  return Channel(ppgMetaData, absoluteBlock);
}

Channel ChannelExampleFactory::channelWithDifferentialValuesForTestSwitchTo() {
  PpgMetaData ppgMetaData = PpgMetaData(PpgMetaDataExampleFactory::ppgMetaDataWithWavelength255());
  DifferentialBlocks differentialBlocks = DifferentialBlockExampleFactory::differentialBlocksForTestSwitchTo();
  return Channel(ppgMetaData, differentialBlocks);
}

Channel ChannelExampleFactory::channelWithAbsoluteBlockForNotEqualTest() {
  PpgMetaData ppgMetaData = PpgMetaData(PpgMetaDataExampleFactory::ppgMetaDataWithWavelength255());
  AbsoluteBlock absoluteBlock = AbsoluteBlockExampleFactory::absoluteBlockWithThreeNegativeAbsoluteValues();
  return Channel(ppgMetaData, absoluteBlock);
}

Channel ChannelExampleFactory::channelWithDifferentialBlocksForNotEqualTest() {
  PpgMetaData ppgMetaData = PpgMetaData(PpgMetaDataExampleFactory::ppgMetaDataWithWavelength255());
  DifferentialBlocks differentialBlocks = {DifferentialBlockExampleFactory::differentialBlockWithThreePositiveDifferentialValues()};
  return Channel(ppgMetaData, differentialBlocks);
}

// TestSerializeAndDeserializeMethodPpgColor
// Channel ChannelExampleFactory::channelWithAbsoluteBlocksAndPpgMetaDataForTestSerialize() {
//   PpgMetaData ppgMetaData = PpgMetaDataExampleFactory::ppgMetDataWithColorGreen();
//   DifferentialBlocks differentialBlocks = DifferentialBlockExampleFactory::differentialBlocksForTestSerialize();
//   return Channel(ppgMetaData, differentialBlocks);
// }
//
// Channel ChannelExampleFactory::channelWithAbsoluteBlockAndAccMetaDataForTestSerialize() {
//   AccMetaData accMetaData = AccMetaData()
//   DifferentialBlocks differentialBlocks = DifferentialBlockExampleFactory::differentialBlocksForTestSerialize();
//   DifferentialBlocks differentialBlocks = {};
// }
//
// Channel ChannelExampleFactory::channelWithDifferentialBlocksAndAccMetaDataForTestSerialize() {
//   PpgMetaData ppgMetaData = PpgMetaDataExampleFactory::ppgMetDataWithColorGreen();
//   DifferentialBlocks differentialBlocks = {};
// }
//
// Channel ChannelExampleFactory::channelWithDifferentialBlocksAndPpgMetaDataForTestSerialize() {
//   PpgMetaData ppgMetaData = PpgMetaDataExampleFactory::ppgMetDataWithColorGreen();
//   DifferentialBlocks differentialBlocks = {};
// }
//
// Channel ChannelExampleFactory::channelWithAccMetaDataWithCoordinateX() {
//   // AccMetaData accMetaData = AccMetaDataExampleFactory::accMetaDataWithCoordinateX();
//   DifferentialBlocks differentialBlocks = DifferentialBlockExampleFactory::normalDifferentialBlocks();
//   return Channel();
// }
//
// Channel ChannelExampleFactory::channelWithOneValueBlock() {
//   // AccMetaData accMetaData = AccMetaDataExampleFactory::accMetaDataWithCoordinateX();
//   AbsoluteBlock absoluteBlock = AbsoluteBlockExampleFactory::absoluteBlockOneElement();
//   return Channel();
// }
//
// Channel ChannelExampleFactory::channelWithNUllValueBlock() {
//   // AccMetaData accMetaData = AccMetaDataExampleFactory::accMetaDataWithCoordinateX();
//   AbsoluteBlock absoluteBlock = AbsoluteBlockExampleFactory::absoluteBlockEmpty();
//   return Channel();
// }
//
// Channel ChannelExampleFactory::channelWithAccMetaDataWithCoordinateY() {
//   // AccMetaData accMetaData = AccMetaDataExampleFactory::accMetaDataWithCoordinateY();
//   DifferentialBlocks differentialBlocks = DifferentialBlockExampleFactory::normalDifferentialBlocks();
//   return Channel();
// }
//
// Channel ChannelExampleFactory::channelWithAccMetaDataWithNorm() {
//   // AccMetaData accMetaData = AccMetaDataExampleFactory::accMetaDataWithEuclideanDifferenceNorm();
//   DifferentialBlocks differentialBlocks = DifferentialBlockExampleFactory::normalDifferentialBlocks();
//   return Channel();
// }
//
// Channel ChannelExampleFactory::channelWithPpgMetaDataWithWavelength() {
//   PpgMetaData ppgMetaData = PpgMetaDataExampleFactory::ppgMetDataWithWavelength();
//   DifferentialBlocks differentialBlocks = DifferentialBlockExampleFactory::normalDifferentialBlocks();
//   return Channel(ppgMetaData, differentialBlocks);
// }
//
// Channel ChannelExampleFactory::channelWithPpgMetaDataWithColor() {
//   PpgMetaData ppgMetaData = PpgMetaDataExampleFactory::ppgMetDataWithColorGreen();
//   DifferentialBlocks differentialBlocks = DifferentialBlockExampleFactory::normalDifferentialBlocks();
//   return Channel(ppgMetaData, differentialBlocks);
// }
//
// Channel ChannelExampleFactory::channelWithPpgMetaDataWithComparableWavelength() {
//   PpgMetaData ppgMetaData = PpgMetaDataExampleFactory::ppgMetDataWithComparableWavelength();
//   DifferentialBlocks differentialBlocks = DifferentialBlockExampleFactory::normalDifferentialBlocks();
//   return Channel(ppgMetaData, differentialBlocks);
// }
//
// Channels ChannelExampleFactory::normalVectorWithChannel() {
//   Channels channelAccMetaDataSetCoordinate = {ChannelExampleFactory::channelWithAccMetaDataWithCoordinateX()};
//   return channelAccMetaDataSetCoordinate;
// }
//
// Channel ChannelExampleFactory::channelWithAbsoluteBlocks() {
//   AbsoluteBlock absoluteBlock = AbsoluteBlockExampleFactory::absoluteBlock();
//   // AccMetaData accMetaData = AccMetaDataExampleFactory::accMetaDataWithCoordinateX();
//   return Channel();
// }
//
// Channel ChannelExampleFactory::channelWithAbsoluteJsonDataPpg1() {
//   AbsoluteBlock absoluteBlock = AbsoluteBlockExampleFactory::absoluteJsonDataBlockPpg1();
//   PpgMetaData ppgMetadata = PpgMetaDataExampleFactory::absoluteJsonDataPpg1();
//   return Channel(ppgMetadata, absoluteBlock);
// }
//
// Channel ChannelExampleFactory::channelWithAbsoluteJsonDataPpg2() {
//   AbsoluteBlock absoluteBlock = AbsoluteBlockExampleFactory::absoluteJsonDataBlockPpg2();
//   PpgMetaData ppgMetadata = PpgMetaDataExampleFactory::absoluteJsonDataPpg2();
//   return Channel(ppgMetadata, absoluteBlock);
// }
//
// Channel ChannelExampleFactory::channelWithAbsoluteJsonDataAcc() {
//   AbsoluteBlock absoluteBlock = AbsoluteBlockExampleFactory::absoluteJsonDataBlockAcc();
//   // AccMetaData accMetaData = AccMetaDataExampleFactory::accMetaDataWithEuclideanDifferenceNorm();
//   return Channel();
// }
//
// Channels ChannelExampleFactory::comparableVectorWithChannel() {
//   Channels channelAccMetaDataSetCoordinate = {ChannelExampleFactory::channelWithAbsoluteBlocks()};
//   return channelAccMetaDataSetCoordinate;
// }
//
// Channels ChannelExampleFactory::normalVectorWithAbsoluteJsonDataPpgChannel() {
//   Channels normalVectorWithAbsoluteJsonDataChannel = {ChannelExampleFactory::channelWithAbsoluteJsonDataPpg1(),
//                                                       ChannelExampleFactory::channelWithAbsoluteJsonDataPpg2()};
//   return normalVectorWithAbsoluteJsonDataChannel;
// }
//
// Channels ChannelExampleFactory::normalVectorWithAbsoluteJsonDataAccChannel() {
//   Channels normalVectorWithAbsoluteJsonDataChannel = {ChannelExampleFactory::channelWithAbsoluteJsonDataAcc()};
//   return normalVectorWithAbsoluteJsonDataChannel;
// }
//
// Channel ChannelExampleFactory::channelWithDifferentialJsonDataPpg1() {
//   DifferentialBlocks differentialBlocks = DifferentialBlockExampleFactory::differentialJsonDataBlockPpg1();
//   PpgMetaData ppgMetadata = PpgMetaDataExampleFactory::absoluteJsonDataPpg1();
//   return Channel(ppgMetadata, differentialBlocks);
// }
//
// Channel ChannelExampleFactory::channelWithDifferentialJsonDataPpg2() {
//   DifferentialBlocks differentialBlocks = DifferentialBlockExampleFactory::differentialJsonDataBlockPpg2();
//
//   PpgMetaData ppgMetadata = PpgMetaDataExampleFactory::absoluteJsonDataPpg2();
//   return Channel(ppgMetadata, differentialBlocks);
// }
//
// Channel ChannelExampleFactory::channelWithDifferentialJsonDataAcc() {
//   DifferentialBlocks differentialBlocks = DifferentialBlockExampleFactory::differentialJsonDataBlockAcc();
//   // AccMetaData accMetaData = AccMetaDataExampleFactory::accMetaDataWithEuclideanDifferenceNorm();
//   return Channel();
// }
//
// Channel ChannelExampleFactory::channelWithOneValueInLastBlock() {
//   AbsoluteBlock absoluteBlock = AbsoluteBlockExampleFactory::absoluteBlockWithOneValueInLastBlock();
//   PpgMetaData ppgMetadata = PpgMetaDataExampleFactory::absoluteJsonDataWavelength_nm1();
//   return Channel(ppgMetadata, absoluteBlock);
// }
//
// Channel ChannelExampleFactory::channelWithEqualTimestampIntervals() {
//   AbsoluteBlock absoluteBlock = AbsoluteBlockExampleFactory::absoluteBlockWithOneValueInLastBlock();
//   PpgMetaData ppgMetadata = PpgMetaDataExampleFactory::absoluteJsonDataWavelength_nm1();
//   return Channel(ppgMetadata, absoluteBlock);
// }
//
// Channels ChannelExampleFactory::normalVectorWithDifferentialJsonDataPpgChannel() {
//   Channels normalVectorWithAbsoluteJsonDataChannel = {ChannelExampleFactory::channelWithDifferentialJsonDataPpg1(),
//                                                       ChannelExampleFactory::channelWithDifferentialJsonDataPpg2()};
//   return normalVectorWithAbsoluteJsonDataChannel;
// }
//
// Channels ChannelExampleFactory::normalVectorWithDifferentialJsonDataAccChannel() {
//   Channels normalVectorWithAbsoluteJsonDataChannel = {ChannelExampleFactory::channelWithDifferentialJsonDataAcc()};
//   return normalVectorWithAbsoluteJsonDataChannel;
// }
//
// Channels ChannelExampleFactory::normalVectorWithOneValueBlock() {
//   Channels normalVectorWithOneValueBlock = {ChannelExampleFactory::channelWithOneValueBlock()};
//   return normalVectorWithOneValueBlock;
// }
//
// Channels ChannelExampleFactory::normalVectorWithNUllValueBlock() {
//   Channels normalVectorWithNUllValueBlock = {ChannelExampleFactory::channelWithNUllValueBlock()};
//   return normalVectorWithNUllValueBlock;
// }
//
// Channels ChannelExampleFactory::normalVectorWithOneValueInLastBlock() {
//   Channels normalVectorWithNUllValueBlock = {ChannelExampleFactory::channelWithOneValueInLastBlock()};
//   return normalVectorWithNUllValueBlock;
// }
//
// Channels ChannelExampleFactory::normalVectorWithEqualTimestampIntervals() {
//   Channels normalVectorWithNUllValueBlock = {ChannelExampleFactory::channelWithEqualTimestampIntervals()};
//   return normalVectorWithNUllValueBlock;
// }

Channel ChannelExampleFactory::channelWithAbsoluteBlockAndPpgMetaData() {
  AbsoluteBlock absoluteBlock = AbsoluteBlockExampleFactory::absoluteBlockWithThreeMixedAbsoluteValues();
  PpgMetaData ppgMetaData = PpgMetaDataExampleFactory::ppgMetaDataWithWavelength255();
  return Channel(ppgMetaData, absoluteBlock);
}

Channel ChannelExampleFactory::channelWithAbsoluteBlockAndAccMetaData() {
  AbsoluteBlock absoluteBlock = AbsoluteBlockExampleFactory::absoluteBlockWithThreeMixedAbsoluteValues();
  AccMetaData accMetaData = AccMetaDataExampleFactory::accMetaDataWithNormEuclideanDifferencesNorm();
  return Channel(accMetaData, absoluteBlock);
}

Channel ChannelExampleFactory::channelWithDifferentialBlocksAndAccMetaData() {
  DifferentialBlocks differentialBlocks = DifferentialBlockExampleFactory::differentialBlocksWithThreeMixedDifferentialBlocks();
  AccMetaData accMetaData = AccMetaDataExampleFactory::accMetaDataWithNormEuclideanDifferencesNorm();
  return Channel(accMetaData, differentialBlocks);
}

Channel ChannelExampleFactory::channelWithDifferentialBlocksAndPpgMetaData() {
  DifferentialBlocks differentialBlocks = DifferentialBlockExampleFactory::differentialBlocksWithThreeMixedDifferentialBlocks();
  PpgMetaData ppgMetaData = PpgMetaDataExampleFactory::ppgMetaDataWithWavelength255();
  return Channel(ppgMetaData, differentialBlocks);
}

Channel ChannelExampleFactory::channelEmpty() {
  return Channel();
}

ChannelJson ChannelExampleFactory::buildChannelJson(Channel channel) {
  ChannelJson channelJson;
  if (channel.hasAbsoluteBlock() && channel.hasAccMetaData()) {
    AbsoluteBlock absoluteBlock = channel.getAbsoluteBlock();
    channelJson["absolute_block"] = AbsoluteBlockExampleFactory::buildAbsoluteBlockJson(absoluteBlock);
    AccMetaData accMetaData = channel.getAccMetaData();
    channelJson["acc_metadata"] = AccMetaDataExampleFactory::buildAccMetaDataJson(accMetaData);
  } else if (channel.hasAbsoluteBlock() && channel.hasPpgMetaData()) {
    AbsoluteBlock absoluteBlock = channel.getAbsoluteBlock();
    channelJson["absolute_block"] = AbsoluteBlockExampleFactory::buildAbsoluteBlockJson(absoluteBlock);
    PpgMetaData ppgMetaData = channel.getPpgMetaData();
    channelJson["ppg_metadata"] = PpgMetaDataExampleFactory::buildPpgMetaDataJson(ppgMetaData);
  } else if (channel.hasDifferentialBlocks() && channel.hasAccMetaData()) {
    DifferentialBlocks differentialBlocks = channel.getDifferentialBlocks();
    channelJson["differential_blocks"] = DifferentialBlockExampleFactory::buildDifferentialBlocksJson(differentialBlocks);
    AccMetaData accMetaData = channel.getAccMetaData();
    channelJson["acc_metadata"] = AccMetaDataExampleFactory::buildAccMetaDataJson(accMetaData);
  } else if (channel.hasDifferentialBlocks() && channel.hasPpgMetaData()) {
    DifferentialBlocks differentialBlocks = channel.getDifferentialBlocks();
    channelJson["differential_blocks"] = DifferentialBlockExampleFactory::buildDifferentialBlocksJson(differentialBlocks);
    PpgMetaData ppgMetaData = channel.getPpgMetaData();
    channelJson["ppg_metadata"] = PpgMetaDataExampleFactory::buildPpgMetaDataJson(ppgMetaData);
  }
  return channelJson;
}
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

#include "ChannelExampleFactory.h"

Channel ChannelExampleFactory::channelWithAccMetaDataWithCoordinateX() {
  AccMetaData accMetaData = AccMetaDataExampleFactory::accMetaDataWithCoordinateX();
  std::vector<DifferentialBlock> differentialBlocks = DifferentialBlockExampleFactory::normalDifferentialBlocks();
  return Channel(accMetaData, differentialBlocks);
}

Channel ChannelExampleFactory::channelWithOneValueBlock() {
  std::vector<size_t> blockIdxs = {0};
  AccMetaData accMetaData = AccMetaDataExampleFactory::accMetaDataWithCoordinateX();
  AbsoluteBlock absoluteBlock = AbsoluteBlockExampleFactory::absoluteBlockOneElement();
  return Channel(accMetaData, absoluteBlock, blockIdxs);
}

Channel ChannelExampleFactory::channelWithNUllValueBlock() {
  std::vector<size_t> blockIdxs = {};
  AccMetaData accMetaData = AccMetaDataExampleFactory::accMetaDataWithCoordinateX();
  AbsoluteBlock absoluteBlock = AbsoluteBlockExampleFactory::absoluteBlockEmpty();
  return Channel(accMetaData, absoluteBlock, blockIdxs);
}

Channel ChannelExampleFactory::channelWithAccMetaDataWithCoordinateY() {
  AccMetaData accMetaData = AccMetaDataExampleFactory::accMetaDataWithCoordinateY();
  std::vector<DifferentialBlock> differentialBlocks = DifferentialBlockExampleFactory::normalDifferentialBlocks();
  return Channel(accMetaData, differentialBlocks);
}

Channel ChannelExampleFactory::channelWithAccMetaDataWithNorm() {
  AccMetaData accMetaData = AccMetaDataExampleFactory::accMetaDataWithEuclideanDifferenceNorm();
  std::vector<DifferentialBlock> differentialBlocks = DifferentialBlockExampleFactory::normalDifferentialBlocks();
  return Channel(accMetaData, differentialBlocks);
}

Channel ChannelExampleFactory::channelWithPpgMetaDataWithWavelength() {
  PpgMetaData ppgMetaData = PpgMetaDataExampleFactory::ppgMetDataWithWavelength();
  std::vector<DifferentialBlock> differentialBlocks = DifferentialBlockExampleFactory::normalDifferentialBlocks();
  return Channel(ppgMetaData, differentialBlocks);
}

Channel ChannelExampleFactory::channelWithPpgMetaDataWithColor() {
  PpgMetaData ppgMetaData = PpgMetaDataExampleFactory::ppgMetDataWithColorGreen();
  std::vector<DifferentialBlock> differentialBlocks = DifferentialBlockExampleFactory::normalDifferentialBlocks();
  return Channel(ppgMetaData, differentialBlocks);
}

Channel ChannelExampleFactory::channelWithPpgMetaDataWithComparableWavelength() {
  PpgMetaData ppgMetaData = PpgMetaDataExampleFactory::ppgMetDataWithComparableWavelength();
  std::vector<DifferentialBlock> differentialBlocks = DifferentialBlockExampleFactory::normalDifferentialBlocks();
  return Channel(ppgMetaData, differentialBlocks);
}

Channels ChannelExampleFactory::normalVectorWithChannel() {
  Channels channelAccMetaDataSetCoordinate = {ChannelExampleFactory::channelWithAccMetaDataWithCoordinateX()};
  return channelAccMetaDataSetCoordinate;
}

Channel ChannelExampleFactory::channelWithAbsoluteBlocks() {
  std::vector<size_t> blockIdxs = {0, 10, 18, 23};
  AbsoluteBlock absoluteBlock = AbsoluteBlockExampleFactory::absoluteBlock();
  AccMetaData accMetaData = AccMetaDataExampleFactory::accMetaDataWithCoordinateX();
  return Channel(accMetaData, absoluteBlock, blockIdxs);
}

Channel ChannelExampleFactory::channelWithAbsoluteJsonDataPpg1() {
  std::vector<size_t> blockIdxs = {0, 2, 4, 6};
  AbsoluteBlock absoluteBlock = AbsoluteBlockExampleFactory::absoluteJsonDataBlockPpg1();
  PpgMetaData ppgMetadata = PpgMetaDataExampleFactory::absoluteJsonDataPpg1();
  return Channel(ppgMetadata, absoluteBlock, blockIdxs);
}

Channel ChannelExampleFactory::channelWithAbsoluteJsonDataPpg2() {
  std::vector<size_t> blockIdxs = {0, 2, 4, 6};
  AbsoluteBlock absoluteBlock = AbsoluteBlockExampleFactory::absoluteJsonDataBlockPpg2();
  PpgMetaData ppgMetadata = PpgMetaDataExampleFactory::absoluteJsonDataPpg2();
  return Channel(ppgMetadata, absoluteBlock, blockIdxs);
}

Channel ChannelExampleFactory::channelWithAbsoluteJsonDataAcc() {
  std::vector<size_t> blockIdxs = {0, 2, 4};
  AbsoluteBlock absoluteBlock = AbsoluteBlockExampleFactory::absoluteJsonDataBlockAcc();
  AccMetaData accMetaData = AccMetaDataExampleFactory::accMetaDataWithEuclideanDifferenceNorm();
  return Channel(accMetaData, absoluteBlock, blockIdxs);
}

Channels ChannelExampleFactory::comparableVectorWithChannel() {
  Channels channelAccMetaDataSetCoordinate = {ChannelExampleFactory::channelWithAbsoluteBlocks()};
  return channelAccMetaDataSetCoordinate;
}

Channels ChannelExampleFactory::normalVectorWithAbsoluteJsonDataPpgChannel() {
  Channels normalVectorWithAbsoluteJsonDataChannel = {ChannelExampleFactory::channelWithAbsoluteJsonDataPpg1(),
                                                                  ChannelExampleFactory::channelWithAbsoluteJsonDataPpg2()};
  return normalVectorWithAbsoluteJsonDataChannel;
}

Channels ChannelExampleFactory::normalVectorWithAbsoluteJsonDataAccChannel() {
  Channels normalVectorWithAbsoluteJsonDataChannel = {ChannelExampleFactory::channelWithAbsoluteJsonDataAcc()};
  return normalVectorWithAbsoluteJsonDataChannel;
}

Channel ChannelExampleFactory::channelWithDifferentialJsonDataPpg1() {
  std::vector<DifferentialBlock> differentialBlocks = DifferentialBlockExampleFactory::differentialJsonDataBlockPpg1();
  PpgMetaData ppgMetadata = PpgMetaDataExampleFactory::absoluteJsonDataPpg1();
  return Channel(ppgMetadata, differentialBlocks);
}

Channel ChannelExampleFactory::channelWithDifferentialJsonDataPpg2() {
  std::vector<DifferentialBlock> differentialBlocks = DifferentialBlockExampleFactory::differentialJsonDataBlockPpg2();

  PpgMetaData ppgMetadata = PpgMetaDataExampleFactory::absoluteJsonDataPpg2();
  return Channel(ppgMetadata, differentialBlocks);
}

Channel ChannelExampleFactory::channelWithDifferentialJsonDataAcc() {
  std::vector<DifferentialBlock> differentialBlocks = DifferentialBlockExampleFactory::differentialJsonDataBlockAcc();
  AccMetaData accMetaData = AccMetaDataExampleFactory::accMetaDataWithEuclideanDifferenceNorm();
  return Channel(accMetaData, differentialBlocks);
}

Channel ChannelExampleFactory::channelWithOneValueInLastBlock() {
  std::vector<size_t> blockIdxs = {0, 6};
  AbsoluteBlock absoluteBlock = AbsoluteBlockExampleFactory::absoluteBlockWithOneValueInLastBlock();
  PpgMetaData ppgMetadata = PpgMetaDataExampleFactory::absoluteJsonDataWavelength_nm1();
  return Channel(ppgMetadata, absoluteBlock, blockIdxs);
}

Channel ChannelExampleFactory::channelWithEqualTimestampIntervals() {
  std::vector<size_t> blockIdxs = {0};
  AbsoluteBlock absoluteBlock = AbsoluteBlockExampleFactory::absoluteBlockWithOneValueInLastBlock();
  PpgMetaData ppgMetadata = PpgMetaDataExampleFactory::absoluteJsonDataWavelength_nm1();
  return Channel(ppgMetadata, absoluteBlock, blockIdxs);
}

Channels ChannelExampleFactory::normalVectorWithDifferentialJsonDataPpgChannel() {
  Channels normalVectorWithAbsoluteJsonDataChannel = {ChannelExampleFactory::channelWithDifferentialJsonDataPpg1(),
                                                                  ChannelExampleFactory::channelWithDifferentialJsonDataPpg2()};
  return normalVectorWithAbsoluteJsonDataChannel;
}

Channels ChannelExampleFactory::normalVectorWithDifferentialJsonDataAccChannel() {
  Channels normalVectorWithAbsoluteJsonDataChannel = {ChannelExampleFactory::channelWithDifferentialJsonDataAcc()};
  return normalVectorWithAbsoluteJsonDataChannel;
}

Channels ChannelExampleFactory::normalVectorWithOneValueBlock() {
  Channels normalVectorWithOneValueBlock = {ChannelExampleFactory::channelWithOneValueBlock()};
  return normalVectorWithOneValueBlock;
}

Channels ChannelExampleFactory::normalVectorWithNUllValueBlock() {
  Channels normalVectorWithNUllValueBlock = {ChannelExampleFactory::channelWithNUllValueBlock()};
  return normalVectorWithNUllValueBlock;
}

Channels ChannelExampleFactory::normalVectorWithOneValueInLastBlock() {
  Channels normalVectorWithNUllValueBlock = {ChannelExampleFactory::channelWithOneValueInLastBlock()};
  return normalVectorWithNUllValueBlock;
}

Channels ChannelExampleFactory::normalVectorWithEqualTimestampIntervals() {
  Channels normalVectorWithNUllValueBlock = {ChannelExampleFactory::channelWithEqualTimestampIntervals()};
  return normalVectorWithNUllValueBlock;
}
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

Channel ChannelExampleFactory::channelWithAbsoluteValuesForTestSwitchTo() {
  auto ppgMetaData = PpgMetaData(PpgMetaDataExampleFactory::ppgMetaDataWithWavelength255());
  auto absoluteBlock = AbsoluteBlockExampleFactory::absoluteBlockForTestSwitchTo();
  return Channel(ppgMetaData, absoluteBlock);
}

Channel ChannelExampleFactory::channelWithDifferentialValuesForTestSwitchTo() {
  auto ppgMetaData = PpgMetaData(PpgMetaDataExampleFactory::ppgMetaDataWithWavelength255());
  auto differentialBlocks = DifferentialBlockExampleFactory::differentialBlocksForTestSwitchTo();
  return Channel(ppgMetaData, differentialBlocks);
}

Channel ChannelExampleFactory::channelWithAbsoluteBlockForNotEqualTest() {
  auto ppgMetaData = PpgMetaData(PpgMetaDataExampleFactory::ppgMetaDataWithWavelength255());
  auto absoluteBlock = AbsoluteBlockExampleFactory::absoluteBlockWithThreeNegativeAbsoluteValues();
  return Channel(ppgMetaData, absoluteBlock);
}

Channel ChannelExampleFactory::channelWithDifferentialBlocksForNotEqualTest() {
  auto ppgMetaData = PpgMetaData(PpgMetaDataExampleFactory::ppgMetaDataWithWavelength255());
  DifferentialBlocks differentialBlocks;
  differentialBlocks.push_back(DifferentialBlockExampleFactory::differentialBlockWithThreePositiveDifferentialValues());
  return Channel(ppgMetaData, differentialBlocks);
}

Channel ChannelExampleFactory::channelWithAbsoluteBlockAndPpgMetaData() {
  auto absoluteBlock = AbsoluteBlockExampleFactory::absoluteBlockWithThreeMixedAbsoluteValues();
  auto ppgMetaData = PpgMetaDataExampleFactory::ppgMetaDataWithWavelength255();
  return Channel(ppgMetaData, absoluteBlock);
}

Channel ChannelExampleFactory::channelWithAbsoluteBlockAndAccMetaData() {
  auto absoluteBlock = AbsoluteBlockExampleFactory::absoluteBlockWithThreeMixedAbsoluteValues();
  auto accMetaData = AccMetaDataExampleFactory::accMetaDataWithNormEuclideanDifferencesNorm();
  return Channel(accMetaData, absoluteBlock);
}

Channel ChannelExampleFactory::channelWithDifferentialBlocksAndAccMetaData() {
  auto differentialBlocks = DifferentialBlockExampleFactory::differentialBlocksWithThreeMixedDifferentialBlocks();
  auto accMetaData = AccMetaDataExampleFactory::accMetaDataWithNormEuclideanDifferencesNorm();
  return Channel(accMetaData, differentialBlocks);
}

Channel ChannelExampleFactory::channelWithDifferentialBlocksAndPpgMetaData() {
  auto differentialBlocks = DifferentialBlockExampleFactory::differentialBlocksWithThreeMixedDifferentialBlocks();
  auto ppgMetaData = PpgMetaDataExampleFactory::ppgMetaDataWithWavelength255();
  return Channel(ppgMetaData, differentialBlocks);
}

Channel ChannelExampleFactory::channelEmpty() {
  return Channel();
}

ChannelJson ChannelExampleFactory::buildChannelJson(Channel channel) {
  ChannelJson channelJson;
  if (channel.hasAbsoluteBlock() && channel.hasAccMetaData()) {
    auto absoluteBlock = channel.getAbsoluteBlock();
    channelJson["absolute_block"] = AbsoluteBlockExampleFactory::buildAbsoluteBlockJson(absoluteBlock);
    auto accMetaData = channel.getAccMetaData();
    channelJson["acc_metadata"] = AccMetaDataExampleFactory::buildAccMetaDataJson(accMetaData);
  } else if (channel.hasAbsoluteBlock() && channel.hasPpgMetaData()) {
    auto absoluteBlock = channel.getAbsoluteBlock();
    channelJson["absolute_block"] = AbsoluteBlockExampleFactory::buildAbsoluteBlockJson(absoluteBlock);
    auto ppgMetaData = channel.getPpgMetaData();
    channelJson["ppg_metadata"] = PpgMetaDataExampleFactory::buildPpgMetaDataJson(ppgMetaData);
  } else if (channel.hasDifferentialBlocks() && channel.hasAccMetaData()) {
    auto differentialBlocks = channel.getDifferentialBlocks();
    channelJson["differential_blocks"] = DifferentialBlockExampleFactory::buildDifferentialBlocksJson(differentialBlocks);
    auto accMetaData = channel.getAccMetaData();
    channelJson["acc_metadata"] = AccMetaDataExampleFactory::buildAccMetaDataJson(accMetaData);
  } else if (channel.hasDifferentialBlocks() && channel.hasPpgMetaData()) {
    auto differentialBlocks = channel.getDifferentialBlocks();
    channelJson["differential_blocks"] = DifferentialBlockExampleFactory::buildDifferentialBlocksJson(differentialBlocks);
    auto ppgMetaData = channel.getPpgMetaData();
    channelJson["ppg_metadata"] = PpgMetaDataExampleFactory::buildPpgMetaDataJson(ppgMetaData);
  }
  return channelJson;
}
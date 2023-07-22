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
#include "PcoreJson.h"

Channel ChannelExampleFactory::channelWithAbsoluteValuesForSwitchDataFormTest() {
  auto ppgMetaData = PpgMetaData(PpgMetaDataExampleFactory::ppgMetaDataWithWavelength255());
  auto absoluteBlock = AbsoluteBlockExampleFactory::absoluteBlockForSwitchDataFormTest();
  return Channel(ppgMetaData, absoluteBlock);
}

Channel ChannelExampleFactory::channelWithDifferentialValuesForSwitchDataFormTest() {
  auto ppgMetaData = PpgMetaData(PpgMetaDataExampleFactory::ppgMetaDataWithWavelength255());
  auto differentialBlocks = DifferentialBlockExampleFactory::differentialBlocksForSwitchDataFormTest();
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
  differentialBlocks.emplace_back(DifferentialBlockExampleFactory::differentialBlockWithThreePositiveDifferentialValues());
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

Channel ChannelExampleFactory::channelWithAbsoluteBlockAndNoSetMetaData() {
  auto absoluteBlock = AbsoluteBlockExampleFactory::absoluteBlockWithThreeMixedAbsoluteValues();
  auto ppgMetaData = PpgMetaDataExampleFactory::ppgMetaDataNotSet();
  return Channel(ppgMetaData, absoluteBlock);
}

Channel ChannelExampleFactory::channelWithNotSetAbsoluteBlockAndNoSetMetaData() {
  auto absoluteBlock = AbsoluteBlockExampleFactory::absoluteBlockNotSet();
  auto ppgMetaData = PpgMetaDataExampleFactory::ppgMetaDataNotSet();
  return Channel(ppgMetaData, absoluteBlock);
}

Channel ChannelExampleFactory::channelNotSet() {
  return Channel();
}

ChannelJson ChannelExampleFactory::buildChannelJson(const Channel& channel) {
  ChannelJson channelJson;
  if (!channel.isSet()) {
    return channelJson;
  }
  if (channel.hasValues<AbsoluteBlock>() && channel.hasMetaData<AccMetaData>()) {
    auto absoluteBlock = channel.getValues<AbsoluteBlock>();
    channelJson[PcoreJson::Key::absolute_block] = AbsoluteBlockExampleFactory::buildAbsoluteBlockJson(*absoluteBlock);
    auto accMetaData = channel.getMetaData<AccMetaData>();
    channelJson[PcoreJson::Key::acc_metadata] = AccMetaDataExampleFactory::buildAccMetaDataJson(*accMetaData);
  } else if (channel.hasValues<AbsoluteBlock>() && channel.hasMetaData<PpgMetaData>()) {
    auto absoluteBlock = channel.getValues<AbsoluteBlock>();
    channelJson[PcoreJson::Key::absolute_block] = AbsoluteBlockExampleFactory::buildAbsoluteBlockJson(*absoluteBlock);
    auto ppgMetaData = channel.getMetaData<PpgMetaData>();
    channelJson[PcoreJson::Key::ppg_metadata] = PpgMetaDataExampleFactory::buildPpgMetaDataJson(*ppgMetaData);
  } else if (channel.hasValues<DifferentialBlocks>() && channel.hasMetaData<AccMetaData>()) {
    auto differentialBlocks = channel.getValues<DifferentialBlocks>();
    channelJson[PcoreJson::Key::differential_blocks] = DifferentialBlockExampleFactory::buildDifferentialBlocksJson(*differentialBlocks);
    auto accMetaData = channel.getMetaData<AccMetaData>();
    channelJson[PcoreJson::Key::acc_metadata] = AccMetaDataExampleFactory::buildAccMetaDataJson(*accMetaData);
  } else if (channel.hasValues<DifferentialBlocks>() && channel.hasMetaData<PpgMetaData>()) {
    auto differentialBlocks = channel.getValues<DifferentialBlocks>();
    channelJson[PcoreJson::Key::differential_blocks] = DifferentialBlockExampleFactory::buildDifferentialBlocksJson(*differentialBlocks);
    auto ppgMetaData = channel.getMetaData<PpgMetaData>();
    channelJson[PcoreJson::Key::ppg_metadata] = PpgMetaDataExampleFactory::buildPpgMetaDataJson(*ppgMetaData);
  }
  return channelJson;
}

ChannelsJson ChannelExampleFactory::buildChannelsJson(const Channels& channels) {
  ChannelsJson channelsJson(Json::arrayValue);
  for (const auto& channel : channels) {
    channelsJson.append(ChannelExampleFactory::buildChannelJson(channel));
  }
  return channelsJson;
}
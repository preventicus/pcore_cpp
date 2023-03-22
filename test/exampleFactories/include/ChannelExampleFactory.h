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

#pragma once
#include "AbsoluteBlockExampleFactory.h"
#include "AccMetaDataExampleFactory.h"
#include "Channel.h"
#include "DifferentialBlockExampleFactory.h"
#include "PpgMetaDataExampleFactory.h"

#include "Sensor.h"

class ChannelExampleFactory {
 public:
//  static Channel channelWithAccMetaDataWithCoordinateX();
//  static Channel channelWithAccMetaDataWithCoordinateY();
//  static Channel channelWithAccMetaDataWithNorm();
//
//  static Channel channelWithPpgMetaDataWithWavelength();
//  static Channel channelWithPpgMetaDataWithColor();
//  static Channel channelWithPpgMetaDataWithComparableWavelength();

//  static Channel channelWithAbsoluteBlocks();
//  static Channel channelWithOneValueBlock();
//  static Channel channelWithNUllValueBlock();
//  static Channel channelWithOneValueInLastBlock();
//  static Channel channelWithEqualTimestampIntervals();
//  static Channel channelWithAbsoluteJsonDataPpg1();
//  static Channel channelWithAbsoluteJsonDataPpg2();
//  static Channel channelWithAbsoluteJsonDataAcc();
//  static Channel channelWithDifferentialJsonDataPpg1();
//  static Channel channelWithDifferentialJsonDataPpg2();
//  static Channel channelWithDifferentialJsonDataAcc();
//
//  static Channels normalVectorWithChannel();
//  static Channels comparableVectorWithChannel();
//  static Channels normalVectorWithAbsoluteJsonDataPpgChannel();
//  static Channels normalVectorWithAbsoluteJsonDataAccChannel();
//  static Channels normalVectorWithDifferentialJsonDataPpgChannel();
//  static Channels normalVectorWithDifferentialJsonDataAccChannel();
//  static Channels normalVectorWithOneValueBlock();
//  static Channels normalVectorWithNUllValueBlock();
//  static Channels normalVectorWithOneValueInLastBlock();
//  static Channels normalVectorWithEqualTimestampIntervals();

//  static Channel channelWithNormalAbsoluteBlocksAndAccMetaDataWithNorm();
//  static Channel channelWithNormalAbsoluteBlocksAndAccMetaDataWithCoordinateX();
//  static Channel channelWithNormalNegativeAbsoluteBlocksAndAccMetaDataWithNorm();
//  static Channel channelWithOneElementAbsoluteBlocksAndAccMetaDataWithNorm();
//  static Channel channelWithNormalDifferentialBlocksAndPpgMetaDataWithNormalWavelength1();
//  static Channel channelWithNormalDifferentialBlocksAndPpgMetaDataWithNormalWavelength2();
//  static Channel channelWithNormalNegativeDifferentialBlocksAndPpgMetaDataWithNormalWavelength1();

  static Channel channelWithAbsoluteValuesForTestSwitchTo();
  static Channel channelWithDifferentialValuesForTestSwitchTo();
  static Channel channelWithAbsoluteBlockForNotEquallTest();
  static Channel channelWithDifferentialBlocksForNotEqualTest();
  static Channel channelWithAbsoluteBlockAndPpgMetaData();
  static Channel channelWithAbsoluteBlockAndAccMetaData();
  static Channel channelWithDifferentialBlocksAndPpgMetaData();
  static Channel channelWithDifferentialBlocksAndAccMetaData();

  static ChannelJson buildChannelJson(Channel channel);
};
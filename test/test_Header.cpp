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
#include "Header.h"
class HeaderTest : public ::testing::Test {
 protected:
  uint32_t majorOne = 1;
  uint32_t minorTwo = 2;
  uint32_t patchZero = 0;
  Version version = Version(majorOne, minorTwo, patchZero);
  int32_t positiveTimeZoneOffset_min = 120;
  int32_t negativeTimeZoneOffset_min = -120;
  int32_t noTimeZoneOffset_min = 0;
  int32_t maxTimeZoneOffset_min = 840;
  int32_t minTimeZoneOffset_min = -720;
  Header normalHeaderWitchPositiveTimeZoneOffset_min1 = Header(version, positiveTimeZoneOffset_min);
  Header normalHeaderWitchPositiveTimeZoneOffset_min2 = Header(version, positiveTimeZoneOffset_min);
  Header normalHeaderWitchNegativeTimeZoneOffset_min1 = Header(version, negativeTimeZoneOffset_min);
  Header normalHeaderWitchNegativeTimeZoneOffset_min2 = Header(version, negativeTimeZoneOffset_min);
  Header normalHeaderWitchNoTimeZoneOffset_min1 = Header(version, noTimeZoneOffset_min);
  Header normalHeaderWitchNoTimeZoneOffset_min2 = Header(version, noTimeZoneOffset_min);
  Header headerWitchMaxTimeZoneOffset_min1 = Header(version, maxTimeZoneOffset_min);
  Header headerWitchMaxTimeZoneOffset_min2 = Header(version, maxTimeZoneOffset_min);
  Header headerWitchMinTimeZoneOffset_min1 = Header(version, minTimeZoneOffset_min);
  Header headerWitchMinTimeZoneOffset_min2 = Header(version, minTimeZoneOffset_min);
};

TEST_F(HeaderTest, TestGetMethodWithPositiveOffSetValue) {
  EXPECT_EQ(this->normalHeaderWitchPositiveTimeZoneOffset_min1.getTimeZoneOffset(), this->positiveTimeZoneOffset_min);
}

TEST_F(HeaderTest, TestGetMethodWithNegativeOffSetValue) {
  EXPECT_EQ(this->normalHeaderWitchNegativeTimeZoneOffset_min1.getTimeZoneOffset(), this->negativeTimeZoneOffset_min);
}

TEST_F(HeaderTest, CompareSameTimeZoneOffset) {
  EXPECT_TRUE(this->normalHeaderWitchPositiveTimeZoneOffset_min1.isEqual(this->normalHeaderWitchPositiveTimeZoneOffset_min2));
}

TEST_F(HeaderTest, CompareSameNegativeTimeZoneOffset) {
  EXPECT_TRUE(this->normalHeaderWitchNegativeTimeZoneOffset_min1.isEqual(this->normalHeaderWitchNegativeTimeZoneOffset_min2));
}

TEST_F(HeaderTest, CompareDifferentTimeZoneOffset) {
  EXPECT_FALSE(this->normalHeaderWitchNegativeTimeZoneOffset_min1.isEqual(this->normalHeaderWitchPositiveTimeZoneOffset_min1));
}

TEST_F(HeaderTest, CompareTimeZoneOffsetWith0) {
  EXPECT_FALSE(this->normalHeaderWitchNoTimeZoneOffset_min1.isEqual(this->normalHeaderWitchPositiveTimeZoneOffset_min1));
}

TEST_F(HeaderTest, CompareSameTimeZoneOffsetWith0) {
  EXPECT_TRUE(this->normalHeaderWitchNoTimeZoneOffset_min1.isEqual(this->normalHeaderWitchNoTimeZoneOffset_min2));
}

TEST_F(HeaderTest, CompareSameTimeZoneOffsetWithMaxOffSet) {
  EXPECT_TRUE(this->headerWitchMaxTimeZoneOffset_min1.isEqual(this->headerWitchMaxTimeZoneOffset_min2));
}

TEST_F(HeaderTest, CompareSameTimeZoneOffsetWithMinOffSet) {
  EXPECT_TRUE(this->headerWitchMinTimeZoneOffset_min1.isEqual(this->headerWitchMinTimeZoneOffset_min2));
}

TEST_F(HeaderTest, SerializeAndDeserializeWithNormalTimeZoneOffset) {
  ProtobufHeader protobufHeader;
  this->normalHeaderWitchPositiveTimeZoneOffset_min1.serialize(&protobufHeader);
  Header header2 = Header(protobufHeader);
  EXPECT_TRUE(this->normalHeaderWitchPositiveTimeZoneOffset_min1.isEqual(header2));
}

TEST_F(HeaderTest, SerializeAndDeserializeWith0) {
  ProtobufHeader protobufHeader;
  this->normalHeaderWitchNoTimeZoneOffset_min1.serialize(&protobufHeader);
  Header header2 = Header(protobufHeader);
  EXPECT_TRUE(this->normalHeaderWitchNoTimeZoneOffset_min1.isEqual(header2));
}

TEST_F(HeaderTest, SerializeAndDeserializeWithNegativeValue) {
  ProtobufHeader protobufHeader;
  this->headerWitchMinTimeZoneOffset_min1.serialize(&protobufHeader);
  Header header2 = Header(protobufHeader);
  EXPECT_TRUE(this->headerWitchMinTimeZoneOffset_min1.isEqual(header2));
}

TEST_F(HeaderTest, TestExecptionPositiveOutOfRange) {
  int32_t invalidPositiveTimeZoneOffset_min = 1000;
  EXPECT_THROW(Header invalidHeaderWitchPositiveTimeZoneOffset_min = Header(this->version, invalidPositiveTimeZoneOffset_min), std::out_of_range);
}

TEST_F(HeaderTest, TestExecptionNegativeOutOfRange) {
  int32_t invalidNegativeTimeZoneOffset_min = -1000;
  EXPECT_THROW(Header invalidHeaderWitchNegativeTimeZoneOffset_min = Header(this->version, invalidNegativeTimeZoneOffset_min), std::out_of_range);
}

TEST_F(HeaderTest, CheckHeaderPtr) {
  ProtobufHeader protobufData;
  this->normalHeaderWitchPositiveTimeZoneOffset_min1.serialize(&protobufData);
  Header timestampContainer = Header(protobufData);
  ProtobufHeader* protobufDataPtr = &protobufData;
  Header* ptr = &timestampContainer;
  EXPECT_FALSE(ptr == nullptr);
  EXPECT_FALSE(protobufDataPtr == nullptr);
}

TEST_F(HeaderTest, CheckHeaderNullPtr) {
  ProtobufHeader* protobufData = nullptr;
  EXPECT_THROW(this->normalHeaderWitchPositiveTimeZoneOffset_min1.serialize(protobufData), std::invalid_argument);
}
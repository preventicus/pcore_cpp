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
#include "HeaderExampleFactory.h"

class HeaderTest : public ::testing::Test {
 protected:
  Header normalHeaderWithPositiveTimeZoneOffset_min1 = HeaderExampleFactory::normalHeaderWithPositiveTimeZoneOffset_min();
  Header normalHeaderWithPositiveTimeZoneOffset_min2 = HeaderExampleFactory::normalHeaderWithPositiveTimeZoneOffset_min();
  Header normalHeaderWithNegativeTimeZoneOffset_min1 = HeaderExampleFactory::normalHeaderWithNegativeTimeZoneOffset_min();
  Header normalHeaderWithNegativeTimeZoneOffset_min2 = HeaderExampleFactory::normalHeaderWithNegativeTimeZoneOffset_min();
  Header normalHeaderWithNoTimeZoneOffset_min1 = HeaderExampleFactory::normalHeaderWithNoTimeZoneOffset_min();
  Header normalHeaderWithNoTimeZoneOffset_min2 = HeaderExampleFactory::normalHeaderWithNoTimeZoneOffset_min();
  Header headerWithMaxTimeZoneOffset_min1 = HeaderExampleFactory::headerWithMaxTimeZoneOffset_min();
  Header headerWithMaxTimeZoneOffset_min2 = HeaderExampleFactory::headerWithMaxTimeZoneOffset_min();
  Header headerWithMinTimeZoneOffset_min1 = HeaderExampleFactory::headerWithMinTimeZoneOffset_min();
  Header headerWithMinTimeZoneOffset_min2 = HeaderExampleFactory::headerWithMinTimeZoneOffset_min();
};

TEST_F(HeaderTest, TestGetMethodWithPositiveOffSetValue) {
  EXPECT_EQ(this->normalHeaderWithPositiveTimeZoneOffset_min1.getTimeZoneOffset(), HeaderExampleFactory::positiveTimeZoneOffset_min());
}

TEST_F(HeaderTest, TestGetMethodWithNegativeOffSetValue) {
  EXPECT_EQ(this->normalHeaderWithNegativeTimeZoneOffset_min1.getTimeZoneOffset(), HeaderExampleFactory::negativeTimeZoneOffset_min());
}

TEST_F(HeaderTest, CompareSameTimeZoneOffset) {
  EXPECT_TRUE(this->normalHeaderWithPositiveTimeZoneOffset_min1.isEqual(this->normalHeaderWithPositiveTimeZoneOffset_min2));
}

TEST_F(HeaderTest, CompareSameNegativeTimeZoneOffset) {
  EXPECT_TRUE(this->normalHeaderWithNegativeTimeZoneOffset_min1.isEqual(this->normalHeaderWithNegativeTimeZoneOffset_min2));
}

TEST_F(HeaderTest, CompareDifferentTimeZoneOffset) {
  EXPECT_FALSE(this->normalHeaderWithNegativeTimeZoneOffset_min1.isEqual(this->normalHeaderWithPositiveTimeZoneOffset_min1));
}

TEST_F(HeaderTest, CompareTimeZoneOffsetWith0) {
  EXPECT_FALSE(this->normalHeaderWithNoTimeZoneOffset_min1.isEqual(this->normalHeaderWithPositiveTimeZoneOffset_min1));
}

TEST_F(HeaderTest, CompareSameTimeZoneOffsetWith0) {
  EXPECT_TRUE(this->normalHeaderWithNoTimeZoneOffset_min1.isEqual(this->normalHeaderWithNoTimeZoneOffset_min2));
}

TEST_F(HeaderTest, CompareSameTimeZoneOffsetWithMaxOffSet) {
  EXPECT_TRUE(this->headerWithMaxTimeZoneOffset_min1.isEqual(this->headerWithMaxTimeZoneOffset_min2));
}

TEST_F(HeaderTest, CompareSameTimeZoneOffsetWithMinOffSet) {
  EXPECT_TRUE(this->headerWithMinTimeZoneOffset_min1.isEqual(this->headerWithMinTimeZoneOffset_min2));
}

TEST_F(HeaderTest, SerializeAndDeserializeWithNormalTimeZoneOffset) {
  ProtobufHeader protobufHeader;
  this->normalHeaderWithPositiveTimeZoneOffset_min1.serialize(&protobufHeader);
  Header header = Header(protobufHeader);
  EXPECT_TRUE(this->normalHeaderWithPositiveTimeZoneOffset_min1.isEqual(header));
}

TEST_F(HeaderTest, SerializeAndDeserializeWith0) {
  ProtobufHeader protobufHeader;
  this->normalHeaderWithNoTimeZoneOffset_min1.serialize(&protobufHeader);
  Header header = Header(protobufHeader);
  EXPECT_TRUE(this->normalHeaderWithNoTimeZoneOffset_min1.isEqual(header));
}

TEST_F(HeaderTest, SerializeAndDeserializeWithNegativeValue) {
  ProtobufHeader protobufHeader;
  this->headerWithMinTimeZoneOffset_min1.serialize(&protobufHeader);
  Header header = Header(protobufHeader);
  EXPECT_TRUE(this->headerWithMinTimeZoneOffset_min1.isEqual(header));
}

TEST_F(HeaderTest, TestExecptionPositiveOutOfRange) {
  Version version = VersionExampleFactory::randomVersion();
  int32_t invalidPositiveTimeZoneOffset_min = HeaderExampleFactory::invalidPositiveTimeZoneOffset_min();
  EXPECT_THROW(Header invalidHeaderWithPositiveTimeZoneOffset_min = Header(version, invalidPositiveTimeZoneOffset_min), std::out_of_range);
}

TEST_F(HeaderTest, TestExecptionNegativeOutOfRange) {
  int32_t invalidNegativeTimeZoneOffset_min = HeaderExampleFactory::invalidNegativeTimeZoneOffset_min();
  Version version = VersionExampleFactory::randomVersion();
  EXPECT_THROW(Header invalidHeaderWithNegativeTimeZoneOffset_min = Header(version, invalidNegativeTimeZoneOffset_min), std::out_of_range);
}

TEST_F(HeaderTest, CheckHeaderPtr) {
  ProtobufHeader protobufData;
  this->normalHeaderWithPositiveTimeZoneOffset_min1.serialize(&protobufData);
  Header timestampContainer = Header(protobufData);
  ProtobufHeader* protobufDataPtr = &protobufData;
  Header* ptr = &timestampContainer;
  EXPECT_FALSE(ptr == nullptr);
  EXPECT_FALSE(protobufDataPtr == nullptr);
}

TEST_F(HeaderTest, CheckHeaderNullPtr) {
  ProtobufHeader* protobufData = nullptr;
  EXPECT_THROW(this->normalHeaderWithPositiveTimeZoneOffset_min1.serialize(protobufData), std::invalid_argument);
}
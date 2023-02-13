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
#include "VersionExampleFactory.h"

class VersionTest : public ::testing::Test {
 protected:
  Version normalVersion1 = VersionExampleFactory::normalVersion();
  Version normalVersion2 = VersionExampleFactory::normalVersion();
  Version startVersion1 = VersionExampleFactory::startVersion();
  Version startVersion2 = VersionExampleFactory::startVersion();
  Version highVersion1 = VersionExampleFactory::highVersion();
  Version highVersion2 = VersionExampleFactory::highVersion();
  Version randomVersion1 = VersionExampleFactory::randomVersion();
  Version randomVersion2 = VersionExampleFactory::randomVersion();
};

TEST_F(VersionTest, TestGetMajor) {
  EXPECT_EQ(this->normalVersion1.getMajor(), VersionExampleFactory::majorOne());
}

TEST_F(VersionTest, TestGetMinor) {
  EXPECT_EQ(this->normalVersion1.getMinor(), VersionExampleFactory::minorOne());
}

TEST_F(VersionTest, TestGetPatch) {
  EXPECT_EQ(this->normalVersion1.getPatch(), VersionExampleFactory::patchOne());
}

TEST_F(VersionTest, TestGetAll) {
  EXPECT_EQ(this->randomVersion1.getMajor(), VersionExampleFactory::majorTwo());
  EXPECT_EQ(this->randomVersion1.getMinor(), VersionExampleFactory::minorOne());
  EXPECT_EQ(this->randomVersion1.getPatch(), VersionExampleFactory::patchZero());
}

TEST_F(VersionTest, CompareEqualNormalVersion) {
  EXPECT_TRUE(this->normalVersion1.isEqual(this->normalVersion2));
}

TEST_F(VersionTest, CompareDifferentNormalVersion) {
  EXPECT_FALSE(this->normalVersion1.isEqual(this->startVersion1));
}

TEST_F(VersionTest, CompareEqualStartVersion) {
  EXPECT_TRUE(this->startVersion1.isEqual(startVersion2));
}

TEST_F(VersionTest, CompareRandomAndNormalVersion) {
  EXPECT_FALSE(this->normalVersion1.isEqual(this->randomVersion1));
}

TEST_F(VersionTest, CompareEqualRandomVersion) {
  EXPECT_TRUE(this->randomVersion1.isEqual(this->randomVersion2));
}

TEST_F(VersionTest, CompareEqualHighVersion) {
  EXPECT_TRUE(this->highVersion1.isEqual(this->highVersion2));
}

TEST_F(VersionTest, TestSerializeAndDeserializeNormalVersion) {
  ProtobufVersion protobufVersion;
  this->normalVersion1.serialize(&protobufVersion);
  Version version2 = Version(protobufVersion);
  EXPECT_TRUE(this->normalVersion1.isEqual(version2));
}

TEST_F(VersionTest, TestSerializeAndDeserialize0Version) {
  ProtobufVersion protobufVersion;
  this->startVersion1.serialize(&protobufVersion);
  Version version2 = Version(protobufVersion);
  EXPECT_TRUE(this->startVersion1.isEqual(version2));
}

TEST_F(VersionTest, TestSerializeAndDeserializerandomVersion) {
  ProtobufVersion protobufVersion;
  this->randomVersion1.serialize(&protobufVersion);
  Version version2 = Version(protobufVersion);
  EXPECT_TRUE(this->randomVersion1.isEqual(version2));
}

TEST_F(VersionTest, TestSerializeAndDeserializehighVersion) {
  ProtobufVersion protobufVersion;
  this->highVersion1.serialize(&protobufVersion);
  Version version2 = Version(protobufVersion);
  EXPECT_TRUE(this->highVersion1.isEqual(version2));
}

TEST_F(VersionTest, CheckVersionPtr) {
  ProtobufVersion protobufData;
  this->normalVersion1.serialize(&protobufData);
  Version version = Version(protobufData);
  ProtobufVersion* protobufDataPtr = &protobufData;
  Version* ptr = &version;
  EXPECT_FALSE(ptr == nullptr);
  EXPECT_FALSE(protobufDataPtr == nullptr);
}

TEST_F(VersionTest, CheckVersionNullPtr) {
  ProtobufVersion* protobufData = nullptr;
  EXPECT_THROW(this->normalVersion1.serialize(protobufData), std::invalid_argument);
}
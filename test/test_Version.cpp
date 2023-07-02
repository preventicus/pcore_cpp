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
#include "VersionExampleFactory.h"

class VersionTest : public ::testing::Test {
 protected:
};

TEST_F(VersionTest, TestGetMajor) {
  Version version = VersionExampleFactory::versionWithMajor2Minor1Patch0();
  EXPECT_EQ(version.getMajor(), VersionExampleFactory::majorTwo());
}

TEST_F(VersionTest, TestGetMinor) {
  Version version = VersionExampleFactory::versionWithMajor2Minor1Patch0();
  EXPECT_EQ(version.getMinor(), VersionExampleFactory::minorOne());
}

TEST_F(VersionTest, TestGetPatch) {
  Version version = VersionExampleFactory::versionWithMajor2Minor1Patch0();
  EXPECT_EQ(version.getPatch(), VersionExampleFactory::patchZero());
}

TEST_F(VersionTest, TestIsEqualWithVersionWithMajor2Minor1Patch0) {
  Version version1 = VersionExampleFactory::versionWithMajor2Minor1Patch0();
  Version version2 = VersionExampleFactory::versionWithMajor2Minor1Patch0();
  EXPECT_TRUE(version1.isEqual(version2));
}

TEST_F(VersionTest, TestIsEqualWithVersionEmpty) {
  Version version1 = VersionExampleFactory::versionEmpty();
  Version version2 = VersionExampleFactory::versionEmpty();
  EXPECT_TRUE(version1.isEqual(version2));
}

TEST_F(VersionTest, TestIsEqualWithVersionEmptyAndVersionWithMajor1Minor1Patch0) {
  Version version1 = VersionExampleFactory::versionEmpty();
  Version version2 = VersionExampleFactory::versionWithMajor1Minor1Patch0();
  EXPECT_FALSE(version1.isEqual(version2));
}

TEST_F(VersionTest, TestIsEqualWithVersionWithMajor2Minor1Patch0AndVersionWithMajor1Minor1Patch0) {
  Version version1 = VersionExampleFactory::versionWithMajor2Minor1Patch0();
  Version version2 = VersionExampleFactory::versionWithMajor1Minor1Patch0();
  EXPECT_FALSE(version1.isEqual(version2));
}

TEST_F(VersionTest, TestIsEqualWithVersionWithMajor1Minor1Patch0AndVersionWithMajor1Minor2Patch0) {
  Version version1 = VersionExampleFactory::versionWithMajor1Minor1Patch0();
  Version version2 = VersionExampleFactory::versionWithMajor1Minor2Patch0();
  EXPECT_FALSE(version1.isEqual(version2));
}

TEST_F(VersionTest, TestIsEqualWithVersionWithMajor1Minor1Patch0AndVersionWithMajor1Minor2Patch1) {
  Version version1 = VersionExampleFactory::versionWithMajor1Minor1Patch0();
  Version version2 = VersionExampleFactory::versionWithMajor1Minor1Patch1();
  EXPECT_FALSE(version1.isEqual(version2));
}

TEST_F(VersionTest, TestToJsonWithVersionWithMajor1Minor1Patch0) {
  Version version = VersionExampleFactory::versionWithMajor1Minor1Patch0();
  VersionJson versionJson1 = VersionExampleFactory::buildVersionJson(version);
  VersionJson versionJson2 = version.toJson();
  EXPECT_TRUE(versionJson1.toStyledString() == versionJson2.toStyledString());
}

TEST_F(VersionTest, TestToJsonWithVersionEmpty) {
  Version version = VersionExampleFactory::versionEmpty();
  VersionJson versionJson1 = VersionExampleFactory::buildVersionJson(version);
  VersionJson versionJson2 = version.toJson();
  EXPECT_TRUE(versionJson1.toStyledString() == versionJson2.toStyledString());
}

TEST_F(VersionTest, TestSerializeWithVersionEmpty) {
  Version version1 = VersionExampleFactory::versionEmpty();
  ProtobufVersion protobufData;
  version1.serialize(&protobufData);
  Version version2 = Version(protobufData);
  EXPECT_TRUE(version1.isEqual(version2));
}

TEST_F(VersionTest, TestSerializeWithVersionWithMajor2Minor1Patch0) {
  Version version1 = VersionExampleFactory::versionWithMajor2Minor1Patch0();
  ProtobufVersion protobufData;
  version1.serialize(&protobufData);
  Version version2 = Version(protobufData);
  EXPECT_TRUE(version1.isEqual(version2));
}

TEST_F(VersionTest, TestSerializeNoThrow) {
  Version version = VersionExampleFactory::versionWithMajor0Minor0Patch0();
  ProtobufVersion protobufData;
  EXPECT_NO_THROW(version.serialize(&protobufData));
}

TEST_F(VersionTest, TestSerializeThrow) {
  Version version = VersionExampleFactory::versionEmpty();
  ProtobufVersion* protobufData = nullptr;
  EXPECT_THROW(version.serialize(protobufData), std::invalid_argument);
}

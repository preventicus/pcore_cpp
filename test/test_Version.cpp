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

TEST(VersionTest, TestGetMajorWithVersionWithMajor2Minor1Patch0) {
  auto version = VersionExampleFactory::versionWithMajor2Minor1Patch0();
  EXPECT_EQ(version.getMajor(), VersionExampleFactory::majorTwo());
}

TEST(VersionTest, TestGetMajorWithVersionNotSet) {
  auto version = VersionExampleFactory::versionNotSet();
  EXPECT_EQ(version.getMajor(), VersionExampleFactory::majorZero());
}

TEST(VersionTest, TestGetMinorWithVersionWithMajor2Minor1Patch0) {
  auto version = VersionExampleFactory::versionWithMajor2Minor1Patch0();
  EXPECT_EQ(version.getMinor(), VersionExampleFactory::minorOne());
}

TEST(VersionTest, TestGetMinorWithVersionNotSet) {
  auto version = VersionExampleFactory::versionNotSet();
  EXPECT_EQ(version.getMinor(), VersionExampleFactory::minorZero());
}

TEST(VersionTest, TestGetPatchWithVersionWithMajor2Minor1Patch0) {
  auto version = VersionExampleFactory::versionWithMajor2Minor1Patch0();
  EXPECT_EQ(version.getPatch(), VersionExampleFactory::patchZero());
}

TEST(VersionTest, TestGetPatchWithVersionNotSet) {
  auto version = VersionExampleFactory::versionNotSet();
  EXPECT_EQ(version.getPatch(), VersionExampleFactory::patchZero());
}

TEST(VersionTest, TestIsEqualWithVersionWithMajor2Minor1Patch0) {
  auto version1 = VersionExampleFactory::versionWithMajor2Minor1Patch0();
  auto version2 = VersionExampleFactory::versionWithMajor2Minor1Patch0();
  EXPECT_TRUE(version1 == version2);
}

TEST(VersionTest, TestIsEqualWithVersionNotSet) {
  auto version1 = VersionExampleFactory::versionNotSet();
  auto version2 = VersionExampleFactory::versionNotSet();
  EXPECT_TRUE(version1 == version2);
}

TEST(VersionTest, TestIsEqualWithVersionNotSetAndVersionWithMajor1Minor1Patch0) {
  auto version1 = VersionExampleFactory::versionNotSet();
  auto version2 = VersionExampleFactory::versionWithMajor1Minor1Patch0();
  EXPECT_FALSE(version1 == version2);
}

TEST(VersionTest, TestIsEqualWithVersionWithMajor2Minor1Patch0AndVersionWithMajor1Minor1Patch0) {
  auto version1 = VersionExampleFactory::versionWithMajor2Minor1Patch0();
  auto version2 = VersionExampleFactory::versionWithMajor1Minor1Patch0();
  EXPECT_FALSE(version1 == version2);
}

TEST(VersionTest, TestIsEqualWithVersionWithMajor1Minor1Patch0AndVersionWithMajor1Minor2Patch0) {
  auto version1 = VersionExampleFactory::versionWithMajor1Minor1Patch0();
  auto version2 = VersionExampleFactory::versionWithMajor1Minor2Patch0();
  EXPECT_FALSE(version1 == version2);
}

TEST(VersionTest, TestIsEqualWithVersionWithMajor1Minor1Patch0AndVersionWithMajor1Minor2Patch1) {
  auto version1 = VersionExampleFactory::versionWithMajor1Minor1Patch0();
  auto version2 = VersionExampleFactory::versionWithMajor1Minor1Patch1();
  EXPECT_FALSE(version1 == version2);
}

TEST(VersionTest, TestIsNotEqualWithVersionWithMajor2Minor1Patch0) {
  auto version1 = VersionExampleFactory::versionWithMajor2Minor1Patch0();
  auto version2 = VersionExampleFactory::versionWithMajor2Minor1Patch0();
  EXPECT_FALSE(version1 != version2);
}

TEST(VersionTest, TestIsNotEqualWithVersionNotSet) {
  auto version1 = VersionExampleFactory::versionNotSet();
  auto version2 = VersionExampleFactory::versionNotSet();
  EXPECT_FALSE(version1 != version2);
}

TEST(VersionTest, TestIsNotEqualWithVersionNotSetAndVersionWithMajor1Minor1Patch0) {
  auto version1 = VersionExampleFactory::versionNotSet();
  auto version2 = VersionExampleFactory::versionWithMajor1Minor1Patch0();
  EXPECT_TRUE(version1 != version2);
}

TEST(VersionTest, TestIsNotEqualWithVersionWithMajor2Minor1Patch0AndVersionWithMajor1Minor1Patch0) {
  auto version1 = VersionExampleFactory::versionWithMajor2Minor1Patch0();
  auto version2 = VersionExampleFactory::versionWithMajor1Minor1Patch0();
  EXPECT_TRUE(version1 != version2);
}

TEST(VersionTest, TestIsNotEqualWithVersionWithMajor1Minor1Patch0AndVersionWithMajor1Minor2Patch0) {
  auto version1 = VersionExampleFactory::versionWithMajor1Minor1Patch0();
  auto version2 = VersionExampleFactory::versionWithMajor1Minor2Patch0();
  EXPECT_TRUE(version1 != version2);
}

TEST(VersionTest, TestIsNotEqualWithVersionWithMajor1Minor1Patch0AndVersionWithMajor1Minor2Patch1) {
  auto version1 = VersionExampleFactory::versionWithMajor1Minor1Patch0();
  auto version2 = VersionExampleFactory::versionWithMajor1Minor1Patch1();
  EXPECT_TRUE(version1 != version2);
}

TEST(VersionTest, TestToJsonWithVersionWithMajor1Minor1Patch0) {
  auto version = VersionExampleFactory::versionWithMajor1Minor1Patch0();
  auto versionJson1 = VersionExampleFactory::buildVersionJson(version);
  auto versionJson2 = version.toJson();
  EXPECT_TRUE(versionJson1.toStyledString() == versionJson2.toStyledString());
}

TEST(VersionTest, TestToJsonWithVersionNotSet) {
  auto version = VersionExampleFactory::versionNotSet();
  auto versionJson1 = VersionExampleFactory::buildVersionJson(version);
  auto versionJson2 = version.toJson();
  EXPECT_TRUE(versionJson1.toStyledString() == versionJson2.toStyledString());
}

TEST(VersionTest, TestSerializeWithVersionNotSet) {
  auto version1 = VersionExampleFactory::versionNotSet();
  VersionProtobuf versionProtobuf;
  version1.serialize(&versionProtobuf);
  auto version2 = Version(versionProtobuf);
  EXPECT_TRUE(version1 == version2);
}

TEST(VersionTest, TestSerializeWithVersionWithMajor2Minor1Patch0) {
  auto version1 = VersionExampleFactory::versionWithMajor2Minor1Patch0();
  VersionProtobuf versionProtobuf;
  version1.serialize(&versionProtobuf);
  auto version2 = Version(versionProtobuf);
  EXPECT_TRUE(version1 == version2);
}

TEST(VersionTest, TestSerializeNoThrow) {
  auto version = VersionExampleFactory::versionWithMajor0Minor0Patch0();
  VersionProtobuf versionProtobuf;
  EXPECT_NO_THROW(version.serialize(&versionProtobuf));
}

TEST(VersionTest, TestSerializeThrow) {
  auto version = VersionExampleFactory::versionNotSet();
  VersionProtobuf* versionProtobuf = nullptr;
  EXPECT_THROW(version.serialize(versionProtobuf), std::invalid_argument);
}

TEST(VersionTest, TestSwitchDataFormWithVersionNotSet) {
  auto version = VersionExampleFactory::versionNotSet();
  EXPECT_THROW(version.switchDataForm(), std::runtime_error);
}

TEST(VersionTest, TestIsSetWithVersionNotSet) {
  auto version = VersionExampleFactory::versionNotSet();
  EXPECT_FALSE(version.isSet());
}

TEST(VersionTest, TestIsSetWithVersionVersionWithMajor1Minor2Patch0) {
  auto version = VersionExampleFactory::versionWithMajor1Minor2Patch0();
  EXPECT_TRUE(version.isSet());
}

TEST(VersionTest, TestIsSetWithVersionVersionWithMajor0Minor2Patch0) {
  auto version = VersionExampleFactory::versionWithMajor0Minor2Patch0();
  EXPECT_TRUE(version.isSet());
}

TEST(VersionTest, TestIsSetWithVersionVersionWithMajor0Minor0Patch1) {
  auto version = VersionExampleFactory::versionWithMajor0Minor0Patch1();
  EXPECT_TRUE(version.isSet());
}
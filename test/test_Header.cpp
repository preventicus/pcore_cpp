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
#include "HeaderExampleFactory.h"
#include "PcoreJson.h"

TEST(HeaderTest, TestGetTimeZoneOffsetWithHeaderWithVersionWithMajor0Minor0Patch0AndTimeZoneOffsetPositiveAndDataFormAbsolute) {
  auto header = HeaderExampleFactory::headerWithVersionWithMajor0Minor0Patch0AndTimeZoneOffsetPositiveAndDataFormAbsolute();
  auto timeZoneOffset1_min = HeaderExampleFactory::timeZoneOffsetPositive_min();
  auto timeZoneOffset2_min = header.getTimeZoneOffset();
  EXPECT_TRUE(timeZoneOffset1_min == timeZoneOffset2_min);
}

TEST(HeaderTest, TestGetTimeZoneOffsetWithHeaderNotSet) {
  auto header = HeaderExampleFactory::headerNotSet();
  auto timeZoneOffset1_min = HeaderExampleFactory::timeZoneOffsetNotSet_min();
  auto timeZoneOffset2_min = header.getTimeZoneOffset();
  EXPECT_TRUE(timeZoneOffset1_min == timeZoneOffset2_min);
}

TEST(HeaderTest, TestGetVersionWithHeaderWithVersionWithMajor0Minor0Patch0AndTimeZoneOffsetPositiveAndDataFormAbsolute) {
  auto header = HeaderExampleFactory::headerWithVersionWithMajor0Minor0Patch0AndTimeZoneOffsetPositiveAndDataFormAbsolute();
  auto version1 = VersionExampleFactory::versionWithMajor0Minor0Patch0();
  auto version2 = header.getPcoreVersion();
  EXPECT_TRUE(version1 == version2);
}

TEST(HeaderTest, TestGetVersionWithHeaderNotSet) {
  auto header = HeaderExampleFactory::headerNotSet();
  auto version1 = VersionExampleFactory::versionNotSet();
  auto version2 = header.getPcoreVersion();
  EXPECT_TRUE(version1 == version2);
}

TEST(HeaderTest, TestGetDataFormWithHeaderWithVersionWithMajor0Minor0Patch0AndTimeZoneOffsetPositiveAndDataFormAbsolute) {
  auto header = HeaderExampleFactory::headerWithVersionWithMajor0Minor0Patch0AndTimeZoneOffsetPositiveAndDataFormAbsolute();
  auto dataForm1 = DataForm::DATA_FORM_ABSOLUTE;
  auto dataForm2 = header.getDataForm();
  EXPECT_TRUE(dataForm1 == dataForm2);
}

TEST(HeaderTest, TestGetDataFormWithHeaderWithVersionWithMajor2Minor1Patch0AndTimeZoneOffsetPositiveAndDataFormDifferential) {
  auto header = HeaderExampleFactory::headerWithVersionWithMajor2Minor1Patch0AndTimeZoneOffsetPositiveAndDataFormDifferential();
  auto dataForm1 = DataForm::DATA_FORM_DIFFERENTIAL;
  auto dataForm2 = header.getDataForm();
  EXPECT_TRUE(dataForm1 == dataForm2);
}

TEST(HeaderTest, TestGetDataFormWithHeaderNotSet) {
  auto header = HeaderExampleFactory::headerNotSet();
  auto dataForm1 = DataForm::DATA_FORM_NONE;
  auto dataForm2 = header.getDataForm();
  EXPECT_TRUE(dataForm1 == dataForm2);
}

TEST(HeaderTest, TestIsEqualWithHeaderWithVersionWithMajor0Minor0Patch0AndTimeZoneOffsetPositiveAndDataFormAbsolute) {
  auto header1 = HeaderExampleFactory::headerWithVersionWithMajor0Minor0Patch0AndTimeZoneOffsetPositiveAndDataFormAbsolute();
  auto header2 = HeaderExampleFactory::headerWithVersionWithMajor0Minor0Patch0AndTimeZoneOffsetPositiveAndDataFormAbsolute();
  EXPECT_TRUE(header1 == header2);
}

TEST(HeaderTest, TestIsEqualWithHeaderNotSet) {
  auto header1 = HeaderExampleFactory::headerNotSet();
  auto header2 = HeaderExampleFactory::headerNotSet();
  EXPECT_TRUE(header1 == header2);
}

TEST(HeaderTest, TestIsEqualWithHeaderWithVersionWithMajor0Minor0Patch0AndTimeZoneOffsetPositiveAndDataFormAbsoluteAndHeaderNotSet) {
  auto header1 = HeaderExampleFactory::headerWithVersionWithMajor0Minor0Patch0AndTimeZoneOffsetPositiveAndDataFormAbsolute();
  auto header2 = HeaderExampleFactory::headerNotSet();
  EXPECT_FALSE(header1 == header2);
}

TEST(
    HeaderTest,
    TestIsEqualWithHeaderWithVersionWithMajor0Minor0Patch0AndTimeZoneOffsetPositiveAndDataFormAbsoluteAndHeaderWithVersionWithMajor2Minor1Patch0AndTimeZoneOffsetNegativeAndDataFormAbsolute) {
  auto header1 = HeaderExampleFactory::headerWithVersionWithMajor0Minor0Patch0AndTimeZoneOffsetPositiveAndDataFormAbsolute();
  auto header2 = HeaderExampleFactory::headerWithVersionWithMajor2Minor1Patch0AndTimeZoneOffsetNegativeAndDataFormAbsolute();
  EXPECT_FALSE(header1 == header2);
}

TEST(
    HeaderTest,
    TestIsEqualWithHeaderWithVersionWithMajor2Minor1Patch0AndTimeZoneOffsetPositiveAndDataFormAbsoluteAndHeaderWithVersionWithMajor2Minor1Patch0AndTimeZoneOffsetNegativeAndDataFormAbsolute) {
  auto header1 = HeaderExampleFactory::headerWithVersionWithMajor2Minor1Patch0AndTimeZoneOffsetPositiveAndDataFormAbsolute();
  auto header2 = HeaderExampleFactory::headerWithVersionWithMajor2Minor1Patch0AndTimeZoneOffsetNegativeAndDataFormAbsolute();
  EXPECT_FALSE(header1 == header2);
}

TEST(
    HeaderTest,
    TestIsEqualWithHeaderWithVersionWithMajor2Minor1Patch0AndTimeZoneOffsetPositiveAndDataFormAbsoluteAndHeaderWithVersionWithMajor2Minor1Patch0AndTimeZoneOffsetPositiveAndDataFormDifferential) {
  auto header1 = HeaderExampleFactory::headerWithVersionWithMajor2Minor1Patch0AndTimeZoneOffsetPositiveAndDataFormAbsolute();
  auto header2 = HeaderExampleFactory::headerWithVersionWithMajor2Minor1Patch0AndTimeZoneOffsetPositiveAndDataFormDifferential();
  EXPECT_FALSE(header1 == header2);
}

TEST(HeaderTest, TestIsNotEqualWithHeaderWithVersionWithMajor0Minor0Patch0AndTimeZoneOffsetPositiveAndDataFormAbsolute) {
  auto header1 = HeaderExampleFactory::headerWithVersionWithMajor0Minor0Patch0AndTimeZoneOffsetPositiveAndDataFormAbsolute();
  auto header2 = HeaderExampleFactory::headerWithVersionWithMajor0Minor0Patch0AndTimeZoneOffsetPositiveAndDataFormAbsolute();
  EXPECT_FALSE(header1 != header2);
}

TEST(HeaderTest, TestIsNotEqualWithHeaderNotSet) {
  auto header1 = HeaderExampleFactory::headerNotSet();
  auto header2 = HeaderExampleFactory::headerNotSet();
  EXPECT_FALSE(header1 != header2);
}

TEST(HeaderTest, TestIsNotEqualWithHeaderWithVersionWithMajor0Minor0Patch0AndTimeZoneOffsetPositiveAndDataFormAbsoluteAndHeaderNotSet) {
  auto header1 = HeaderExampleFactory::headerWithVersionWithMajor0Minor0Patch0AndTimeZoneOffsetPositiveAndDataFormAbsolute();
  auto header2 = HeaderExampleFactory::headerNotSet();
  EXPECT_TRUE(header1 != header2);
}

TEST(
    HeaderTest,
    TestIsNotEqualWithHeaderWithVersionWithMajor0Minor0Patch0AndTimeZoneOffsetPositiveAndDataFormAbsoluteAndHeaderWithVersionWithMajor2Minor1Patch0AndTimeZoneOffsetNegativeAndDataFormAbsolute) {
  auto header1 = HeaderExampleFactory::headerWithVersionWithMajor0Minor0Patch0AndTimeZoneOffsetPositiveAndDataFormAbsolute();
  auto header2 = HeaderExampleFactory::headerWithVersionWithMajor2Minor1Patch0AndTimeZoneOffsetNegativeAndDataFormAbsolute();
  EXPECT_TRUE(header1 != header2);
}

TEST(
    HeaderTest,
    TestIsNotEqualWithHeaderWithVersionWithMajor2Minor1Patch0AndTimeZoneOffsetPositiveAndDataFormAbsoluteAndHeaderWithVersionWithMajor2Minor1Patch0AndTimeZoneOffsetNegativeAndDataFormAbsolute) {
  auto header1 = HeaderExampleFactory::headerWithVersionWithMajor2Minor1Patch0AndTimeZoneOffsetPositiveAndDataFormAbsolute();
  auto header2 = HeaderExampleFactory::headerWithVersionWithMajor2Minor1Patch0AndTimeZoneOffsetNegativeAndDataFormAbsolute();
  EXPECT_TRUE(header1 != header2);
}

TEST(
    HeaderTest,
    TestIsNotEqualWithHeaderWithVersionWithMajor2Minor1Patch0AndTimeZoneOffsetPositiveAndDataFormAbsoluteAndHeaderWithVersionWithMajor2Minor1Patch0AndTimeZoneOffsetPositiveAndDataFormDifferential) {
  auto header1 = HeaderExampleFactory::headerWithVersionWithMajor2Minor1Patch0AndTimeZoneOffsetPositiveAndDataFormAbsolute();
  auto header2 = HeaderExampleFactory::headerWithVersionWithMajor2Minor1Patch0AndTimeZoneOffsetPositiveAndDataFormDifferential();
  EXPECT_TRUE(header1 != header2);
}

TEST(HeaderTest, TestToJsonWithHeaderWithVersionWithMajor2Minor1Patch0AndTimeZoneOffsetPositiveAndDataFormAbsolute) {
  auto header = HeaderExampleFactory::headerWithVersionWithMajor2Minor1Patch0AndTimeZoneOffsetPositiveAndDataFormAbsolute();
  auto headerJson1 = HeaderExampleFactory::buildHeaderJson(header);
  auto headerJson2 = header.toJson();
  EXPECT_TRUE(headerJson1.toStyledString() == headerJson2.toStyledString());
}

TEST(HeaderTest, TestToJsonWithHeaderNotSet) {
  auto header = HeaderExampleFactory::headerNotSet();
  auto headerJson1 = HeaderExampleFactory::buildHeaderJson(header);
  auto headerJson2 = header.toJson();
  EXPECT_TRUE(headerJson1.toStyledString() == headerJson2.toStyledString());
}

TEST(HeaderTest, TestSerializeWithHeaderWithVersionWithMajor2Minor1Patch0AndTimeZoneOffsetNegativeAndDataFormDifferential) {
  auto header1 = HeaderExampleFactory::headerWithVersionWithMajor2Minor1Patch0AndTimeZoneOffsetNegativeAndDataFormDifferential();
  HeaderProtobuf headerProtobuf;
  header1.serialize(&headerProtobuf);
  auto header2 = Header(headerProtobuf);
  EXPECT_TRUE(header1 == header2);
}

TEST(HeaderTest, TestSerializeWithHeaderNotSet) {
  auto header1 = HeaderExampleFactory::headerNotSet();
  HeaderProtobuf headerProtobuf;
  header1.serialize(&headerProtobuf);
  auto header2 = Header(headerProtobuf);
  EXPECT_TRUE(header1 == header2);
}

TEST(HeaderTest, TestSerializeNoThrow) {
  auto header = HeaderExampleFactory::headerWithVersionWithMajor2Minor1Patch0AndTimeZoneOffsetPositiveAndDataFormDifferential();
  HeaderProtobuf headerProtobuf;
  EXPECT_NO_THROW(header.serialize(&headerProtobuf));
}

TEST(HeaderTest, TestSerializeThrow) {
  auto header = HeaderExampleFactory::headerNotSet();
  HeaderProtobuf* headerProtobuf = nullptr;
  EXPECT_THROW(header.serialize(headerProtobuf), std::invalid_argument);
}

TEST(HeaderTest, TestSwitchDataFormWithHeaderInAbsoluteForm) {
  auto header = HeaderExampleFactory::headerWithVersionWithMajor2Minor1Patch0AndTimeZoneOffsetPositiveAndDataFormAbsolute();
  header.switchDataForm();
  auto dataFormInDifferentialForm = header.getDataForm();
  EXPECT_TRUE(dataFormInDifferentialForm == DataForm::DATA_FORM_DIFFERENTIAL);
}

TEST(HeaderTest, TestSwitchDataFormWithHeaderWithVersionWithMajor2Minor1Patch0AndTimeZoneOffsetPositiveAndDataFormDifferential) {
  auto header = HeaderExampleFactory::headerWithVersionWithMajor2Minor1Patch0AndTimeZoneOffsetPositiveAndDataFormDifferential();
  header.switchDataForm();
  auto dataFormInAbsoluteForm = header.getDataForm();
  EXPECT_TRUE(dataFormInAbsoluteForm == DataForm::DATA_FORM_ABSOLUTE);
}

TEST(HeaderTest, TestDataFormFromString) {
  EXPECT_EQ(PcoreJson::Convert::dataFormFromString("DATA_FORM_ABSOLUTE"), DataForm::DATA_FORM_ABSOLUTE);
  EXPECT_EQ(PcoreJson::Convert::dataFormFromString("DATA_FORM_DIFFERENTIAL"), DataForm::DATA_FORM_DIFFERENTIAL);
  EXPECT_EQ(PcoreJson::Convert::dataFormFromString("DATA_FORM_NONE"), DataForm::DATA_FORM_NONE);
}

TEST(HeaderTest, TestDataFormToString) {
  EXPECT_EQ(PcoreJson::Convert::dataFormToString(DataForm::DATA_FORM_ABSOLUTE), "DATA_FORM_ABSOLUTE");
  EXPECT_EQ(PcoreJson::Convert::dataFormToString(DataForm::DATA_FORM_DIFFERENTIAL), "DATA_FORM_DIFFERENTIAL");
  EXPECT_EQ(PcoreJson::Convert::dataFormToString(DataForm::DATA_FORM_NONE), "DATA_FORM_NONE");
}

TEST(HeaderTest, TestConstructorThrowWithTimeZoneOffsetPositiveInvalid) {
  auto version = VersionExampleFactory::versionWithMajor0Minor0Patch0();
  auto invalidPositiveTimeZoneOffset_min = HeaderExampleFactory::timeZoneOffsetPositiveInvalid_min();
  EXPECT_THROW(Header(version, invalidPositiveTimeZoneOffset_min, DataForm::DATA_FORM_ABSOLUTE), std::invalid_argument);
}

TEST(HeaderTest, TestConstructorThrowWithTimeZoneOffsetNagativeInvalid) {
  auto version = VersionExampleFactory::versionWithMajor0Minor0Patch0();
  auto invalidPositiveTimeZoneOffset_min = HeaderExampleFactory::timeZoneOffsetNegativeInvalid_min();
  EXPECT_THROW(Header(version, invalidPositiveTimeZoneOffset_min, DataForm::DATA_FORM_ABSOLUTE), std::invalid_argument);
}

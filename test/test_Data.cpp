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
#include "DataExampleFactory.h"

TEST(DataTest, TestGetRaw) {
  auto data = DataExampleFactory::dataWithRawWithOneSensorsPpgAndHeaderWithTimeZoneOffsetNegative();
  auto raw1 = RawExampleFactory::rawWithOneSensorsPpgWithTwoChannelsInDifferentialForm();
  auto raw2 = data.getRaw();
  EXPECT_TRUE(raw1 == raw2);
}

TEST(DataTest, TestGetHeader) {
  auto data = DataExampleFactory::dataWithRawWithOneSensorsPpgAndHeaderWithTimeZoneOffsetNegative();
  auto header1 = HeaderExampleFactory::headerWithVersionWithMajor2Minor1Patch0AndTimeZoneOffsetPositiveAndDataFormDifferential();
  auto header2 = data.getHeader();
  EXPECT_TRUE(header1 == header2);
}

TEST(DataTest, TestIsEqualWithDataWithRawWithTwoSensorsPpgAndHeaderWithTimeZoneOffsetNegative) {
  auto data1 = DataExampleFactory::dataWithRawWithTwoSensorsPpgAndHeaderWithTimeZoneOffsetNegative();
  auto data2 = DataExampleFactory::dataWithRawWithTwoSensorsPpgAndHeaderWithTimeZoneOffsetNegative();
  EXPECT_TRUE(data1 == data2);
}

TEST(DataTest, TestIsEqualWithDataEmpty) {
  auto data1 = DataExampleFactory::dataEmpty();
  auto data2 = DataExampleFactory::dataEmpty();
  EXPECT_TRUE(data1 == data2);
}

TEST(DataTest, TestIsEqualWithDataEmptyAndDataWithRawWithOneSensorsPpgAndHeaderWithTimeZoneOffsetNegative) {
  auto data1 = DataExampleFactory::dataWithRawWithOneSensorsPpgAndHeaderWithTimeZoneOffsetNegative();
  auto data2 = DataExampleFactory::dataEmpty();
  EXPECT_FALSE(data1 == data2);
}

TEST(DataTest, TestIsEqualWithDifferentHeader) {
  auto data1 = DataExampleFactory::dataWithRawWithTwoSensorsPpgAndHeaderWithTimeZoneOffsetNegative();
  auto data2 = DataExampleFactory::dataWithRawWithTwoSensorsPpgAndHeaderWithTimeZoneOffsetPositive();
  EXPECT_FALSE(data1 == data2);
}

TEST(DataTest, TestIsEqualWithDifferentRaw) {
  auto data1 = DataExampleFactory::dataWithRawWithTwoSensorsPpgAndHeaderWithTimeZoneOffsetNegative();
  auto data2 = DataExampleFactory::dataWithRawWithOneSensorsPpgAndHeaderWithTimeZoneOffsetNegative();
  EXPECT_FALSE(data1 == data2);
}

TEST(DataTest, TestIsNotEqualWithDataWithRawWithTwoSensorsPpgAndHeaderWithTimeZoneOffsetNegative) {
  auto data1 = DataExampleFactory::dataWithRawWithTwoSensorsPpgAndHeaderWithTimeZoneOffsetNegative();
  auto data2 = DataExampleFactory::dataWithRawWithTwoSensorsPpgAndHeaderWithTimeZoneOffsetNegative();
  EXPECT_FALSE(data1 != data2);
}

TEST(DataTest, TestIsNotEqualWithDataEmpty) {
  auto data1 = DataExampleFactory::dataEmpty();
  auto data2 = DataExampleFactory::dataEmpty();
  EXPECT_FALSE(data1 != data2);
}

TEST(DataTest, TestIsNotEqualWithDataEmptyAndDataWithRawWithOneSensorsPpgAndHeaderWithTimeZoneOffsetNegative) {
  auto data1 = DataExampleFactory::dataWithRawWithOneSensorsPpgAndHeaderWithTimeZoneOffsetNegative();
  auto data2 = DataExampleFactory::dataEmpty();
  EXPECT_TRUE(data1 != data2);
}

TEST(DataTest, TestIsNotEqualWithDifferentHeader) {
  auto data1 = DataExampleFactory::dataWithRawWithTwoSensorsPpgAndHeaderWithTimeZoneOffsetNegative();
  auto data2 = DataExampleFactory::dataWithRawWithTwoSensorsPpgAndHeaderWithTimeZoneOffsetPositive();
  EXPECT_TRUE(data1 != data2);
}

TEST(DataTest, TestIsNotEqualWithDifferentRaw) {
  auto data1 = DataExampleFactory::dataWithRawWithTwoSensorsPpgAndHeaderWithTimeZoneOffsetNegative();
  auto data2 = DataExampleFactory::dataWithRawWithOneSensorsPpgAndHeaderWithTimeZoneOffsetNegative();
  EXPECT_TRUE(data1 != data2);
}

TEST(DataTest, TestSerializeWithDataWithRawWithTwoSensorsPpgAndHeaderWithTimeZoneOffsetNegative) {
  auto data1 = DataExampleFactory::dataWithRawWithTwoSensorsPpgAndHeaderWithTimeZoneOffsetNegative();
  ProtobufData protobufData;
  data1.serialize(&protobufData);
  auto data2 = Data(protobufData);
  EXPECT_TRUE(data1 == data2);
}

TEST(DataTest, TestSerializeNoThrow) {
  auto data = DataExampleFactory::dataWithRawWithOneSensorsPpgAndHeaderWithTimeZoneOffsetNegative();
  ProtobufData protobufData;
  EXPECT_NO_THROW(data.serialize(&protobufData));
}

TEST(DataTest, TestSerializeThrow) {
  auto data = DataExampleFactory::dataEmpty();
  ProtobufData* protobufData = nullptr;
  EXPECT_THROW(data.serialize(protobufData), std::invalid_argument);
}

TEST(DataTest, TestSwitchDataFormWithDataInAbsoluteForm) {
  auto data = DataExampleFactory::dataWithRawForSwitchDataFormTestInAbsoluteForm();
  data.switchDataForm();
  auto dataInDifferentialForm = DataExampleFactory::dataWithRawForSwitchDataFormTestInDifferentialForm();
  EXPECT_TRUE(data == dataInDifferentialForm);
}

TEST(DataTest, TestSwitchDataFormWithDataInDifferentialForm) {
  auto data = DataExampleFactory::dataWithRawForSwitchDataFormTestInDifferentialForm();
  data.switchDataForm();
  auto dataInAbsoluteForm = DataExampleFactory::dataWithRawForSwitchDataFormTestInAbsoluteForm();
  EXPECT_TRUE(data == dataInAbsoluteForm);
}

TEST(DataTest, TestToJsonWithDataEmpty) {
  auto data = DataExampleFactory::dataEmpty();
  auto dataJson1 = DataExampleFactory::buildDataJson(data);
  auto dataJson2 = data.toJson(DataForm::DATA_FORM_NONE);
  EXPECT_TRUE(dataJson1.toStyledString() == dataJson2.toStyledString());
}

TEST(DataTest, TestToJsonWithDataInAbsoluteForm) {
  auto data = DataExampleFactory::dataWithRawForSwitchDataFormTestInAbsoluteForm();
  auto dataJson1 = DataExampleFactory::buildDataJson(data);
  auto dataJson2 = data.toJson(DataForm::DATA_FORM_ABSOLUTE);
  EXPECT_TRUE(dataJson1.toStyledString() == dataJson2.toStyledString());
}

TEST(DataTest, TestToJsonWithDataInDifferentialForm) {
  auto data = DataExampleFactory::dataWithRawForSwitchDataFormTestInDifferentialForm();
  auto dataJson1 = DataExampleFactory::buildDataJson(data);
  auto dataJson2 = data.toJson(DataForm::DATA_FORM_DIFFERENTIAL);
  EXPECT_TRUE(dataJson1.toStyledString() == dataJson2.toStyledString());
}
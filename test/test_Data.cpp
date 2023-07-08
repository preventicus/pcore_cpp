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
  Data data = DataExampleFactory::dataWithRawWithOneSensorsPpgAndHeaderWithTimeZoneOffsetNegative();
  Raw raw1 = RawExampleFactory::rawWithOneSensorsPpgWithTwoChannelsInDifferentialForm();
  Raw raw2 = data.getRaw();
  EXPECT_TRUE(raw1.isEqual(raw2));
}

TEST(DataTest, TestGetHeader) {
  Data data = DataExampleFactory::dataWithRawWithOneSensorsPpgAndHeaderWithTimeZoneOffsetNegative();
  Header header1 = HeaderExampleFactory::headerWithVersionWithMajor2Minor1Patch0AndTimeZoneOffsetPositiveAndDataFormDifferential();
  Header header2 = data.getHeader();
  EXPECT_TRUE(header1.isEqual(header2));
}

TEST(DataTest, TestIsEqualWithDataWithRawWithTwoSensorsPpgAndHeaderWithTimeZoneOffsetNegative) {
  Data data1 = DataExampleFactory::dataWithRawWithTwoSensorsPpgAndHeaderWithTimeZoneOffsetNegative();
  Data data2 = DataExampleFactory::dataWithRawWithTwoSensorsPpgAndHeaderWithTimeZoneOffsetNegative();
  EXPECT_TRUE(data1.isEqual(data2));
}

TEST(DataTest, TestIsEqualWithDataEmpty) {
  Data data1 = DataExampleFactory::dataEmpty();
  Data data2 = DataExampleFactory::dataEmpty();
  EXPECT_TRUE(data1.isEqual(data2));
}

TEST(DataTest, TestIsEqualWithDataEmptyAndDataWithRawWithOneSensorsPpgAndHeaderWithTimeZoneOffsetNegative) {
  Data data1 = DataExampleFactory::dataWithRawWithOneSensorsPpgAndHeaderWithTimeZoneOffsetNegative();
  Data data2 = DataExampleFactory::dataEmpty();
  EXPECT_FALSE(data1.isEqual(data2));
}

TEST(DataTest, TestIsEqualWithDifferentHeader) {
  Data data1 = DataExampleFactory::dataWithRawWithTwoSensorsPpgAndHeaderWithTimeZoneOffsetNegative();
  Data data2 = DataExampleFactory::dataWithRawWithTwoSensorsPpgAndHeaderWithTimeZoneOffsetPositive();
  EXPECT_FALSE(data1.isEqual(data2));
}

TEST(DataTest, TestIsEqualWithDifferentRaw) {
  Data data1 = DataExampleFactory::dataWithRawWithTwoSensorsPpgAndHeaderWithTimeZoneOffsetNegative();
  Data data2 = DataExampleFactory::dataWithRawWithOneSensorsPpgAndHeaderWithTimeZoneOffsetNegative();
  EXPECT_FALSE(data1.isEqual(data2));
}

TEST(DataTest, TestSerializeWithDataWithRawWithTwoSensorsPpgAndHeaderWithTimeZoneOffsetNegative) {
  Data data1 = DataExampleFactory::dataWithRawWithTwoSensorsPpgAndHeaderWithTimeZoneOffsetNegative();
  ProtobufData protobufData;
  data1.serialize(&protobufData);
  Data data2 = Data(protobufData);
  EXPECT_TRUE(data1.isEqual(data2));
}

TEST(DataTest, TestSerializeNoThrow) {
  Data data = DataExampleFactory::dataWithRawWithOneSensorsPpgAndHeaderWithTimeZoneOffsetNegative();
  ProtobufData protobufData;
  EXPECT_NO_THROW(data.serialize(&protobufData));
}

TEST(DataTest, TestSerializeThrow) {
  Data data = DataExampleFactory::dataEmpty();
  ProtobufData* protobufData = nullptr;
  EXPECT_THROW(data.serialize(protobufData), std::invalid_argument);
}

TEST(DataTest, TestSwitchDataFormWithDataInAbsoluteForm) {
  Data data = DataExampleFactory::dataWithRawForSwitchDataFormTestInAbsoluteForm();
  data.switchDataForm();
  Data dataInDifferentialForm = DataExampleFactory::dataWithRawForSwitchDataFormTestInDifferentialForm();
  EXPECT_TRUE(data.isEqual(dataInDifferentialForm));
}

TEST(DataTest, TestSwitchDataFormWithDataInDifferentialForm) {
  Data data = DataExampleFactory::dataWithRawForSwitchDataFormTestInDifferentialForm();
  data.switchDataForm();
  Data dataInAbsoluteForm = DataExampleFactory::dataWithRawForSwitchDataFormTestInAbsoluteForm();
  EXPECT_TRUE(data.isEqual(dataInAbsoluteForm));
}

TEST(DataTest, TestToJsonWithDataEmpty) {
  Data data = DataExampleFactory::dataEmpty();
  DataJson dataJson1 = DataExampleFactory::buildDataJson(data);
  DataJson dataJson2 = data.toJson(DataForm::DATA_FORM_NONE);
  EXPECT_TRUE(dataJson1.toStyledString() == dataJson2.toStyledString());
}

TEST(DataTest, TestToJsonWithDataInAbsoluteForm) {
  Data data = DataExampleFactory::dataWithRawForSwitchDataFormTestInAbsoluteForm();
  DataJson dataJson1 = DataExampleFactory::buildDataJson(data);
  DataJson dataJson2 = data.toJson(DataForm::DATA_FORM_ABSOLUTE);
  EXPECT_TRUE(dataJson1.toStyledString() == dataJson2.toStyledString());
}

TEST(DataTest, TestToJsonWithDataInDifferentialForm) {
  Data data = DataExampleFactory::dataWithRawForSwitchDataFormTestInDifferentialForm();
  DataJson dataJson1 = DataExampleFactory::buildDataJson(data);
  DataJson dataJson2 = data.toJson(DataForm::DATA_FORM_DIFFERENTIAL);
  EXPECT_TRUE(dataJson1.toStyledString() == dataJson2.toStyledString());
}
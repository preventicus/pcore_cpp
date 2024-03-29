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
#include "Exceptions.h"

////////////////////////////////////////////////////////////////
//                        Test Getter                         //
////////////////////////////////////////////////////////////////

TEST(DataTest, TestGetRawWithDataWithRawWithOneSensorsPpgAndHeaderWithTimeZoneOffsetNegative) {
  auto data = DataExampleFactory::dataWithRawWithOneSensorsPpgAndHeaderWithTimeZoneOffsetNegative();
  auto raw1 = RawExampleFactory::rawWithOneSensorsPpgWithTwoChannelsInDifferentialForm();
  auto raw2 = data.getRaw();
  EXPECT_TRUE(raw1 == raw2);
}

TEST(DataTest, TestGetRawWithDataNotSet) {
  auto data = DataExampleFactory::dataNotSet();
  auto raw1 = RawExampleFactory::rawNotSet();
  auto raw2 = data.getRaw();
  EXPECT_TRUE(raw1 == raw2);
}

TEST(DataTest, TestGetHeaderWithDataWithRawWithOneSensorsPpgAndHeaderWithTimeZoneOffsetNegative) {
  auto data = DataExampleFactory::dataWithRawWithOneSensorsPpgAndHeaderWithTimeZoneOffsetNegative();
  auto header1 = HeaderExampleFactory::headerWithVersionWithMajor2Minor1Patch0AndTimeZoneOffsetPositiveAndDataFormDifferential();
  auto header2 = data.getHeader();
  EXPECT_TRUE(header1 == header2);
}

TEST(DataTest, TestGetHeaderWithDataNotSet) {
  auto data = DataExampleFactory::dataNotSet();
  auto header1 = HeaderExampleFactory::headerNotSet();
  auto header2 = data.getHeader();
  EXPECT_TRUE(header1 == header2);
}

////////////////////////////////////////////////////////////////
//                        Test isEqual                        //
////////////////////////////////////////////////////////////////

TEST(DataTest, TestIsEqualWithDataWithRawWithTwoSensorsPpgAndHeaderWithTimeZoneOffsetNegative) {
  auto data1 = DataExampleFactory::dataWithRawWithTwoSensorsPpgAndHeaderWithTimeZoneOffsetNegative();
  auto data2 = DataExampleFactory::dataWithRawWithTwoSensorsPpgAndHeaderWithTimeZoneOffsetNegative();
  EXPECT_TRUE(data1 == data2);
}

TEST(DataTest, TestIsEqualWithDataNotSet) {
  auto data1 = DataExampleFactory::dataNotSet();
  auto data2 = DataExampleFactory::dataNotSet();
  EXPECT_TRUE(data1 == data2);
}

TEST(DataTest, TestIsEqualWithDataWithRawWithOneSensorsPpgAndHeaderWithTimeZoneOffsetNegativeAndDataNotSet) {
  auto data1 = DataExampleFactory::dataWithRawWithOneSensorsPpgAndHeaderWithTimeZoneOffsetNegative();
  auto data2 = DataExampleFactory::dataNotSet();
  EXPECT_FALSE(data1 == data2);
}

TEST(
    DataTest,
    TestIsEqualWithDataWithRawWithTwoSensorsPpgAndHeaderWithTimeZoneOffsetNegativeAndDataWithRawWithTwoSensorsPpgAndHeaderWithTimeZoneOffsetPositive) {
  auto data1 = DataExampleFactory::dataWithRawWithTwoSensorsPpgAndHeaderWithTimeZoneOffsetNegative();
  auto data2 = DataExampleFactory::dataWithRawWithTwoSensorsPpgAndHeaderWithTimeZoneOffsetPositive();
  EXPECT_FALSE(data1 == data2);
}

TEST(
    DataTest,
    TestIsEqualWithDataWithRawWithTwoSensorsPpgAndHeaderWithTimeZoneOffsetNegativeAndDataWithRawWithOneSensorsPpgAndHeaderWithTimeZoneOffsetNegative) {
  auto data1 = DataExampleFactory::dataWithRawWithTwoSensorsPpgAndHeaderWithTimeZoneOffsetNegative();
  auto data2 = DataExampleFactory::dataWithRawWithOneSensorsPpgAndHeaderWithTimeZoneOffsetNegative();
  EXPECT_FALSE(data1 == data2);
}

////////////////////////////////////////////////////////////////
//                      Test isNotEqual                       //
////////////////////////////////////////////////////////////////

TEST(DataTest, TestIsNotEqualWithdataWithRawWithTwoSensorsPpgAndHeaderWithTimeZoneOffsetNegative) {
  auto data1 = DataExampleFactory::dataWithRawWithTwoSensorsPpgAndHeaderWithTimeZoneOffsetNegative();
  auto data2 = DataExampleFactory::dataWithRawWithTwoSensorsPpgAndHeaderWithTimeZoneOffsetNegative();
  EXPECT_FALSE(data1 != data2);
}

TEST(DataTest, TestIsNotEqualWithDataNotSet) {
  auto data1 = DataExampleFactory::dataNotSet();
  auto data2 = DataExampleFactory::dataNotSet();
  EXPECT_FALSE(data1 != data2);
}

TEST(DataTest, TestIsNotEqualWithDataWithRawWithOneSensorsPpgAndHeaderWithTimeZoneOffsetNegativeAndDataNotSet) {
  auto data1 = DataExampleFactory::dataWithRawWithOneSensorsPpgAndHeaderWithTimeZoneOffsetNegative();
  auto data2 = DataExampleFactory::dataNotSet();
  EXPECT_TRUE(data1 != data2);
}

TEST(
    DataTest,
    TestIsNotEqualWithDataWithRawWithTwoSensorsPpgAndHeaderWithTimeZoneOffsetNegativeAndDataWithRawWithTwoSensorsPpgAndHeaderWithTimeZoneOffsetPositive) {
  auto data1 = DataExampleFactory::dataWithRawWithTwoSensorsPpgAndHeaderWithTimeZoneOffsetNegative();
  auto data2 = DataExampleFactory::dataWithRawWithTwoSensorsPpgAndHeaderWithTimeZoneOffsetPositive();
  EXPECT_TRUE(data1 != data2);
}

TEST(
    DataTest,
    TestIsNotEqualDataWithRawWithTwoSensorsPpgAndHeaderWithTimeZoneOffsetNegativeAndDataWithRawWithOneSensorsPpgAndHeaderWithTimeZoneOffsetNegative) {
  auto data1 = DataExampleFactory::dataWithRawWithTwoSensorsPpgAndHeaderWithTimeZoneOffsetNegative();
  auto data2 = DataExampleFactory::dataWithRawWithOneSensorsPpgAndHeaderWithTimeZoneOffsetNegative();
  EXPECT_TRUE(data1 != data2);
}

////////////////////////////////////////////////////////////////
//                        Test toJson                         //
////////////////////////////////////////////////////////////////

TEST(DataTest, TestToJsonWithDataNotSet) {
  auto data = DataExampleFactory::dataNotSet();
  auto dataJson1 = DataExampleFactory::buildDataJson(data);
  auto dataJson2 = data.toJson();
  EXPECT_TRUE(dataJson1.toStyledString() == dataJson2.toStyledString());
}

TEST(DataTest, TestToJsonWithDataWithRawForSwitchDataFormTestInAbsoluteForm) {
  auto data = DataExampleFactory::dataWithRawForSwitchDataFormTestInAbsoluteForm();
  auto dataJson1 = DataExampleFactory::buildDataJson(data);
  auto dataJson2 = data.toJson();
  EXPECT_TRUE(dataJson1.toStyledString() == dataJson2.toStyledString());
}

TEST(DataTest, TestToJsonWithDataWithRawForSwitchDataFormTestInDifferentialForm) {
  auto data = DataExampleFactory::dataWithRawForSwitchDataFormTestInDifferentialForm();
  auto dataJson1 = DataExampleFactory::buildDataJson(data);
  auto dataJson2 = data.toJson();
  EXPECT_TRUE(dataJson1.toStyledString() == dataJson2.toStyledString());
}

////////////////////////////////////////////////////////////////
//                        Test isSet                          //
////////////////////////////////////////////////////////////////

TEST(DataTest, TestIsSetWithDataNotSet) {
  auto data = DataExampleFactory::dataNotSet();
  EXPECT_FALSE(data.isSet());
}

TEST(DataTest, TestIsSetWithDataWithRawWithTwoSensorsPpgAndHeaderWithTimeZoneOffsetNegative) {
  auto data = DataExampleFactory::dataWithRawWithTwoSensorsPpgAndHeaderWithTimeZoneOffsetNegative();
  EXPECT_TRUE(data.isSet());
}

TEST(DataTest, TestIsSetWithDataWithRawWithZeroSensorsInDifferentialFormAndHeaderNotSet) {
  auto data = DataExampleFactory::dataWithRawWithZeroSensorsInDifferentialFormAndHeaderNotSet();
  EXPECT_TRUE(data.isSet());
}

////////////////////////////////////////////////////////////////
//                       Test serialize                       //
////////////////////////////////////////////////////////////////

TEST(DataTest, TestSerializeWithDataWithRawWithTwoSensorsPpgAndHeaderWithTimeZoneOffsetNegative) {
  auto data1 = DataExampleFactory::dataWithRawWithTwoSensorsPpgAndHeaderWithTimeZoneOffsetNegative();
  DataProtobuf dataProtobuf;
  data1.serialize(&dataProtobuf);
  auto data2 = Data(dataProtobuf);
  EXPECT_TRUE(data1 == data2);
}

TEST(DataTest, TestSerializeNoThrow) {
  auto data = DataExampleFactory::dataWithRawWithOneSensorsPpgAndHeaderWithTimeZoneOffsetNegative();
  DataProtobuf dataProtobuf;
  EXPECT_NO_THROW(data.serialize(&dataProtobuf));
}

TEST(DataTest, TestSerializeThrowDueToNullPointer) {
  auto data = DataExampleFactory::dataNotSet();
  DataProtobuf* dataProtobuf = nullptr;
  EXPECT_THROW(data.serialize(dataProtobuf), NullPointerException);
}

TEST(DataTest, TestSerializeThrowDueToDataFromAbsolute) {
  auto data = DataExampleFactory::dataWithRawForSwitchDataFormTestInAbsoluteForm();
  DataProtobuf dataProtobuf;
  EXPECT_THROW(data.serialize(&dataProtobuf), WrongDataFormException);
}

////////////////////////////////////////////////////////////////
//                     Test switchDataForm                    //
////////////////////////////////////////////////////////////////

TEST(DataTest, TestSwitchDataFormWithDataWithRawForSwitchDataFormTestInAbsoluteForm) {
  auto data = DataExampleFactory::dataWithRawForSwitchDataFormTestInAbsoluteForm();
  data.switchDataForm();
  auto dataInDifferentialForm = DataExampleFactory::dataWithRawForSwitchDataFormTestInDifferentialForm();
  EXPECT_TRUE(data == dataInDifferentialForm);
}

TEST(DataTest, TestSwitchDataFormWithDataWithRawForSwitchDataFormTestInDifferentialForm) {
  auto data = DataExampleFactory::dataWithRawForSwitchDataFormTestInDifferentialForm();
  data.switchDataForm();
  auto dataInAbsoluteForm = DataExampleFactory::dataWithRawForSwitchDataFormTestInAbsoluteForm();
  EXPECT_TRUE(data == dataInAbsoluteForm);
}

TEST(DataTest, TestSwitchDataFormWithDataNotSet) {
  auto data = DataExampleFactory::dataNotSet();
  data.switchDataForm();
  EXPECT_FALSE(data.isSet());
}

#include <gtest/gtest.h>
#include "Header.h"

TEST(runUnitTests, GetSetMethodeWithPositiveValue) {
  Version version = Version(1, 2, 3);
  int32_t timeZoneOffset_min = 120;
  Header header = Header(version, timeZoneOffset_min);
  EXPECT_EQ(header.getTimeZoneOffset(), timeZoneOffset_min);
}

TEST(runUnitTests, GetSetMethodeWithNegativeValue) {
  Version version = Version(1, 2, 3);
  int32_t timeZoneOffset_min = -120;
  Header header = Header(version, timeZoneOffset_min);
  EXPECT_EQ(header.getTimeZoneOffset(), timeZoneOffset_min);
}

TEST(runUnitTests, CompareSameTimeZoneOffset) {
  Version version = Version(1, 2, 3);
  int32_t timeZoneOffset_min1 = 120;
  Header header1 = Header(version, timeZoneOffset_min1);
  int32_t timeZoneOffset_min2 = 120;
  Header header2 = Header(version, timeZoneOffset_min2);
  EXPECT_TRUE(header1.isEqual(header2));
}

TEST(runUnitTests, CompareSameNegativeTimeZoneOffset) {
  Version version = Version(1, 2, 3);
  int32_t timeZoneOffset_min1 = -120;
  Header header1 = Header(version, timeZoneOffset_min1);
  int32_t timeZoneOffset_min2 = -120;
  Header header2 = Header(version, timeZoneOffset_min2);
  EXPECT_TRUE(header1.isEqual(header2));
}

TEST(runUnitTests, CompareDifferentTimeZoneOffset) {
  Version version = Version(1, 2, 3);
  int32_t timeZoneOffset_min1 = 60;
  Header header1 = Header(version, timeZoneOffset_min1);
  int32_t timeZoneOffset_min2 = 120;
  Header header2 = Header(version, timeZoneOffset_min2);
  EXPECT_FALSE(header1.isEqual(header2));
}

TEST(runUnitTests, CompareTimeZoneOffsetWith0) {
  Version version = Version(1, 2, 3);
  int32_t timeZoneOffset_min1 = 60;
  Header header1 = Header(version, timeZoneOffset_min1);
  int32_t timeZoneOffset_min2 = 0;
  Header header2 = Header(version, timeZoneOffset_min2);
  EXPECT_FALSE(header1.isEqual(header2));
}
TEST(runUnitTests, CompareSameTimeZoneOffsetWith0) {
  Version version = Version(1, 2, 3);
  int32_t timeZoneOffset_min1 = 0;
  Header header1 = Header(version, timeZoneOffset_min1);
  int32_t timeZoneOffset_min2 = 0;
  Header header2 = Header(version, timeZoneOffset_min2);
  EXPECT_TRUE(header1.isEqual(header2));
}
TEST(runUnitTests, CompareSameTimeZoneOffsetWithMaxOffSet) {
  Version version = Version(1, 2, 3);
  int32_t timeZoneOffset_min1 = 840;
  Header header1 = Header(version, timeZoneOffset_min1);
  int32_t timeZoneOffset_min2 = 840;
  Header header2 = Header(version, timeZoneOffset_min2);
  EXPECT_TRUE(header1.isEqual(header2));
}
TEST(runUnitTests, SerializeAndDeserialize) {
  Version version = Version(1, 2, 3);
  int32_t timeZoneOffset_min = 120;
  Header header1 = Header(version, timeZoneOffset_min);
  ProtobufHeader protobufHeader = header1.serialize();
  Header header2 = Header(protobufHeader);
  EXPECT_TRUE(header1.isEqual(header2));
}

TEST(runUnitTests, SerializeAndDeserializeWith0) {
  Version version = Version(1, 2, 3);
  int32_t timeZoneOffset_min = 0;
  Header header1 = Header(version, timeZoneOffset_min);
  ProtobufHeader protobufHeader = header1.serialize();
  Header header2 = Header(protobufHeader);
  EXPECT_TRUE(header1.isEqual(header2));
}

TEST(runUnitTests, SerializeAndDeserializeWithNegativeValue) {
  Version version = Version(1, 2, 3);
  int32_t timeZoneOffset_min = -120;
  Header header1 = Header(version, timeZoneOffset_min);
  ProtobufHeader protobufHeader = header1.serialize();
  Header header2 = Header(protobufHeader);
  EXPECT_TRUE(header1.isEqual(header2));
}

TEST(runUnitTests, TestExecptionPositiveOutOfRange) {
  Version version = Version(1, 2, 3);
  int32_t timeZoneOffset_min = 1000;
  EXPECT_THROW(Header header = Header(version, timeZoneOffset_min), std::out_of_range);
}

TEST(runUnitTests, TestExecptionNegativeOutOfRange) {
  Version version = Version(1, 2, 3);
  int32_t timeZoneOffset_min = -1000;
  EXPECT_THROW(Header header = Header(version, timeZoneOffset_min), std::out_of_range);
}

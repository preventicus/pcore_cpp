#include <gtest/gtest.h>
#include "DeserializedHeader.h"

TEST(runUnitTests, GetSetMethodeWithPositiveValue) {
  int32_t timeZoneOffset_min = 120;
  DeserializedHeader header;
  header.setTimeZoneOffset(timeZoneOffset_min);
  EXPECT_EQ(header.getTimeZoneOffset(), timeZoneOffset_min);
}

TEST(runUnitTests, GetSetMethodeWithNegativeValue) {
  int32_t timeZoneOffset_min = -120;
  DeserializedHeader header;
  header.setTimeZoneOffset(timeZoneOffset_min);
  EXPECT_EQ(header.getTimeZoneOffset(), timeZoneOffset_min);
}

TEST(runUnitTests, CompareSameTimeZoneOffset) {
  int32_t timeZoneOffset_min1 = 120;
  DeserializedHeader header1;
  header1.setTimeZoneOffset(timeZoneOffset_min1);
  int32_t timeZoneOffset_min2 = 120;
  DeserializedHeader header2;
  header2.setTimeZoneOffset(timeZoneOffset_min2);
  EXPECT_TRUE(header1.isEqual(header2));
}

TEST(runUnitTests, CompareSameNegativeTimeZoneOffset) {
  int32_t timeZoneOffset_min1 = -120;
  DeserializedHeader header1;
  header1.setTimeZoneOffset(timeZoneOffset_min1);
  int32_t timeZoneOffset_min2 = -120;
  DeserializedHeader header2;
  header2.setTimeZoneOffset(timeZoneOffset_min2);
  EXPECT_TRUE(header1.isEqual(header2));
}

TEST(runUnitTests, CompareDifferentTimeZoneOffset) {
  int32_t timeZoneOffset_min1 = 60;
  DeserializedHeader header1;
  header1.setTimeZoneOffset(timeZoneOffset_min1);
  int32_t timeZoneOffset_min2 = 120;
  DeserializedHeader header2;
  header2.setTimeZoneOffset(timeZoneOffset_min2);
  EXPECT_FALSE(header1.isEqual(header2));
}

TEST(runUnitTests, CompareTimeZoneOffsetWith0) {
  int32_t timeZoneOffset_min1 = 60;
  DeserializedHeader header1;
  header1.setTimeZoneOffset(timeZoneOffset_min1);
  int32_t timeZoneOffset_min2 = 0;
  DeserializedHeader header2;
  header2.setTimeZoneOffset(timeZoneOffset_min2);
  EXPECT_FALSE(header1.isEqual(header2));
}
TEST(runUnitTests, CompareSameTimeZoneOffsetWith0) {
  int32_t timeZoneOffset_min1 = 0;
  DeserializedHeader header1;
  header1.setTimeZoneOffset(timeZoneOffset_min1);
  int32_t timeZoneOffset_min2 = 0;
  DeserializedHeader header2;
  header2.setTimeZoneOffset(timeZoneOffset_min2);
  EXPECT_TRUE(header1.isEqual(header2));
}
TEST(runUnitTests, CompareSameTimeZoneOffsetWithMaxOffSet) {
  int32_t timeZoneOffset_min1 = 840;
  DeserializedHeader header1;
  header1.setTimeZoneOffset(timeZoneOffset_min1);
  int32_t timeZoneOffset_min2 = 840;
  DeserializedHeader header2;
  header2.setTimeZoneOffset(timeZoneOffset_min2);
  EXPECT_TRUE(header1.isEqual(header2));
}
TEST(runUnitTests, SerializeAndDeserialize) {
  int32_t timeZoneOffset_min = 120;
  uint32_t major = 1;
  uint32_t minor = 1;
  uint32_t patch = 2;
  DeserializedVersion version;
  version.setMajor(major);
  version.setMinor(minor);
  version.setPatch(patch);
  DeserializedHeader header1;
  header1.setTimeZoneOffset(timeZoneOffset_min);
  header1.setVersion(version);
  SerializedHeader serializedHeader = header1.serialize();
  DeserializedHeader header2;
  header2.deserialize(serializedHeader);
  EXPECT_TRUE(header1.isEqual(header2));
}

TEST(runUnitTests, SerializeAndDeserializeWith0) {
  int32_t timeZoneOffset_min = 0;
  uint32_t major = 1;
  uint32_t minor = 1;
  uint32_t patch = 2;
  DeserializedVersion version;
  version.setMajor(major);
  version.setMinor(minor);
  version.setPatch(patch);
  DeserializedHeader header1;
  header1.setTimeZoneOffset(timeZoneOffset_min);
  header1.setVersion(version);
  SerializedHeader serializedHeader = header1.serialize();
  DeserializedHeader header2;
  header2.deserialize(serializedHeader);
  EXPECT_TRUE(header1.isEqual(header2));
}

TEST(runUnitTests, SerializeAndDeserializeWithNegativeValue) {
  int32_t timeZoneOffset_min = -120;
  uint32_t major = 1;
  uint32_t minor = 1;
  uint32_t patch = 2;
  DeserializedVersion version;
  version.setMajor(major);
  version.setMinor(minor);
  version.setPatch(patch);
  DeserializedHeader header1;
  header1.setTimeZoneOffset(timeZoneOffset_min);
  header1.setVersion(version);
  SerializedHeader serializedHeader = header1.serialize();
  DeserializedHeader header2;
  header2.deserialize(serializedHeader);
  EXPECT_TRUE(header1.isEqual(header2));
}

TEST(runUnitTests, TestExecptionPositiveOutOfRange) {
  try {
    int32_t timeZoneOffset_min1 = 841;
    DeserializedHeader header1;
    header1.setTimeZoneOffset(timeZoneOffset_min1);
    FAIL() << "Expected std::out_of_range";
  } catch (std::out_of_range const& e) {
    EXPECT_EQ(e.what(), std::string("Out of range"));
  } catch (...) {
    FAIL() << "Expected std::out_of_range";
  }
}

TEST(runUnitTests, TestExecptionNegativeOutOfRange) {
  try {
    int32_t timeZoneOffset_min1 = -721;
    DeserializedHeader header1;
    header1.setTimeZoneOffset(timeZoneOffset_min1);
    FAIL() << "Expected std::out_of_range";
  } catch (std::out_of_range const& e) {
    EXPECT_EQ(e.what(), std::string("Out of range"));
  } catch (...) {
    FAIL() << "Expected std::out_of_range";
  }
}
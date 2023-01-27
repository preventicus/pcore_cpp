#include <gtest/gtest.h>
#include "Version.h"

TEST(runUnitTests, TestGetMajor) {
  uint32_t major = 1;
  uint32_t minor = 0;
  uint32_t patch = 2;
  Version version = Version(major, minor, patch);
  EXPECT_EQ(version.getMajor(), major);
}

TEST(runUnitTests, TestGetMinor) {
  uint32_t major = 1;
  uint32_t minor = 0;
  uint32_t patch = 2;
  Version version = Version(major, minor, patch);
  EXPECT_EQ(version.getMinor(), minor);
}

TEST(runUnitTests, TestGetPatch) {
  uint32_t major = 1;
  uint32_t minor = 0;
  uint32_t patch = 2;
  Version version = Version(major, minor, patch);
  EXPECT_EQ(version.getPatch(), patch);
}

TEST(runUnitTests, TestGetAll) {
  uint32_t major = 1;
  uint32_t minor = 0;
  uint32_t patch = 2;
  Version version = Version(major, minor, patch);
  EXPECT_EQ(version.getMajor(), major);
  EXPECT_EQ(version.getMinor(), minor);
  EXPECT_EQ(version.getPatch(), patch);
}

TEST(runUnitTests, CompareEqualMajorVersion) {
  uint32_t major1 = 1;
  uint32_t major2 = 1;
  uint32_t minor1 = 0;
  uint32_t minor2 = 0;
  uint32_t patch1 = 2;
  uint32_t patch2 = 2;
  Version version1 = Version(major1, minor1, patch1);
  Version version2 = Version(major2, minor2, patch2);
  EXPECT_TRUE(version1.isEqual(version2));
}

TEST(runUnitTests, CompareDifferentMajorVersion) {
  uint32_t major1 = 1;
  uint32_t major2 = 3;
  uint32_t minor1 = 0;
  uint32_t minor2 = 0;
  uint32_t patch1 = 2;
  uint32_t patch2 = 2;
  Version version1 = Version(major1, minor1, patch1);
  Version version2 = Version(major2, minor2, patch2);
  EXPECT_FALSE(version1.isEqual(version2));
}

TEST(runUnitTests, CompareMajorVersion0) {
  uint32_t major1 = 0;
  uint32_t major2 = 0;
  uint32_t minor1 = 0;
  uint32_t minor2 = 0;
  uint32_t patch1 = 2;
  uint32_t patch2 = 2;
  Version version1 = Version(major1, minor1, patch1);
  Version version2 = Version(major2, minor2, patch2);
  EXPECT_TRUE(version1.isEqual(version2));
}

TEST(runUnitTests, Compare0AndNormalMajorVersion) {
  uint32_t major1 = 1;
  uint32_t major2 = 0;
  uint32_t minor1 = 0;
  uint32_t minor2 = 0;
  uint32_t patch1 = 2;
  uint32_t patch2 = 2;
  Version version1 = Version(major1, minor1, patch1);
  Version version2 = Version(major2, minor2, patch2);
  EXPECT_FALSE(version1.isEqual(version2));
}

TEST(runUnitTests, CompareDifferentVersion) {
  uint32_t major1 = 1;
  uint32_t major2 = 1;
  uint32_t minor1 = 2;
  uint32_t minor2 = 2;
  uint32_t patch1 = 0;
  uint32_t patch2 = 5;
  Version version1 = Version(major1, minor1, patch1);
  Version version2 = Version(major2, minor2, patch2);
  EXPECT_FALSE(version1.isEqual(version2));
}

TEST(runUnitTests, TestSerializeAndDeprotobufVersion) {
  uint32_t major1 = 1;
  uint32_t minor1 = 2;
  uint32_t patch1 = 0;
  Version version1 = Version(major1, minor1, patch1);
  ProtobufVersion protobufVersion = version1.serialize();
  Version version2 = Version(protobufVersion);
  EXPECT_TRUE(version1.isEqual(version2));
}

TEST(runUnitTests, TestSerializeAndDeserialized0Version) {
  uint32_t major1 = 0;
  uint32_t minor1 = 0;
  uint32_t patch1 = 0;
  Version version1 = Version(major1, minor1, patch1);
  ProtobufVersion protobufVersion = version1.serialize();
  Version version2 = Version(protobufVersion);
  EXPECT_TRUE(version1.isEqual(version2));
}

#include <gtest/gtest.h>
#include "Version.h"

TEST(runUnitTests, TestGetAndSetMajor) {
  uint32_t major = 1;
  Version version;
  version.setMajor(major);
  EXPECT_EQ(version.getMajor(), major);
}

TEST(runUnitTests, TestGetAndSetMinor) {
  uint32_t minor = 1;
  Version version;
  version.setMinor(minor);
  EXPECT_EQ(version.getMinor(), minor);
}

TEST(runUnitTests, TestGetAndSetPatch) {
  uint32_t patch = 1;
  Version version;
  version.setPatch(patch);
  EXPECT_EQ(version.getPatch(), patch);
}

TEST(runUnitTests, TestGetAndSetAll) {
  uint32_t major = 1;
  uint32_t minor = 0;
  uint32_t patch = 2;
  Version version;
  version.setMajor(major);
  version.setMinor(minor);
  version.setPatch(patch);
  EXPECT_EQ(version.getMajor(), major);
  EXPECT_EQ(version.getMinor(), minor);
  EXPECT_EQ(version.getPatch(), patch);
}

TEST(runUnitTests, CompareEqualMajorVersion) {
  uint32_t major1 = 1;
  uint32_t major2 = 1;
  Version version1;
  version1.setMajor(major1);
  Version version2;
  version2.setMajor(major2);
  EXPECT_TRUE(version1.isEqual(version2));
}

TEST(runUnitTests, CompareDifferentMajorVersion) {
  uint32_t major1 = 1;
  uint32_t major2 = 2;
  Version version1;
  version1.setMajor(major1);
  Version version2;
  version2.setMajor(major2);
  EXPECT_FALSE(version1.isEqual(version2));
}

TEST(runUnitTests, CompareMajorVersion0) {
  uint32_t major1 = 0;
  uint32_t major2 = 0;
  Version version1;
  version1.setMajor(major1);
  Version version2;
  version2.setMajor(major2);
  EXPECT_TRUE(version1.isEqual(version2));
}

TEST(runUnitTests, Compare0AndNormalMajorVersion) {
  uint32_t major1 = 0;
  uint32_t major2 = 1;
  Version version1;
  version1.setMajor(major1);
  Version version2;
  version2.setMajor(major2);
  EXPECT_FALSE(version1.isEqual(version2));
}

TEST(runUnitTests, CompareEqualCompleteVersion) {
  uint32_t major1 = 1;
  uint32_t major2 = 1;
  uint32_t minor1 = 2;
  uint32_t minor2 = 2;
  uint32_t patch1 = 5;
  uint32_t patch2 = 5;
  Version version1;
  version1.setMajor(major1);
  version1.setMinor(minor1);
  version1.setPatch(patch1);
  Version version2;
  version2.setMajor(major2);
  version2.setMinor(minor2);
  version2.setPatch(patch2);
  EXPECT_TRUE(version1.isEqual(version2));
}

TEST(runUnitTests, CompareDifferentVersion) {
  uint32_t major1 = 1;
  uint32_t major2 = 1;
  uint32_t minor1 = 2;
  uint32_t minor2 = 2;
  uint32_t patch1 = 0;
  uint32_t patch2 = 5;
  Version version1;
  version1.setMajor(major1);
  version1.setMinor(minor1);
  version1.setPatch(patch1);
  Version version2;
  version2.setMajor(major2);
  version2.setMinor(minor2);
  version2.setPatch(patch2);
  EXPECT_FALSE(version1.isEqual(version2));
}

TEST(runUnitTests, TestSerializeAndVersion) {
  uint32_t major1 = 1;
  uint32_t minor1 = 2;
  uint32_t patch1 = 0;
  Version version1;
  version1.setMajor(major1);
  version1.setMinor(minor1);
  version1.setPatch(patch1);
  ProtobufVersion protobufVersion = version1.serialize();
  Version version2;
  version2.deserialize(protobufVersion);
  EXPECT_TRUE(version1.isEqual(version2));
}

TEST(runUnitTests, TestSerializeAndDeserialized0Version) {
  uint32_t major1 = 0;
  uint32_t minor1 = 0;
  uint32_t patch1 = 0;
  Version version1;
  version1.setMajor(major1);
  version1.setMinor(minor1);
  version1.setPatch(patch1);
  ProtobufVersion protobufVersion = version1.serialize();
  Version version2;
  version2.deserialize(protobufVersion);
  EXPECT_TRUE(version1.isEqual(version2));
}

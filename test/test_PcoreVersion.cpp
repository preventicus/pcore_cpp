#include <gtest/gtest.h>
#include "DeserializedVersion.h"

TEST(runUnitTests, TestGetAndSetMajor) {
  uint32_t major = 1;
  DeserializedVersion version;
  version.setMajor(major);
  EXPECT_EQ(version.getMajor(), major);
}

TEST(runUnitTests, TestGetAndSetMinor) {
  uint32_t minor = 1;
  DeserializedVersion version;
  version.setMinor(minor);
  EXPECT_EQ(version.getMinor(), minor);
}

TEST(runUnitTests, TestGetAndSetPatch) {
  uint32_t patch = 1;
  DeserializedVersion version;
  version.setPatch(patch);
  EXPECT_EQ(version.getPatch(), patch);
}

TEST(runUnitTests, TestGetAndSetAll) {
  uint32_t major = 1;
  uint32_t minor = 0;
  uint32_t patch = 2;
  DeserializedVersion version;
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
  DeserializedVersion version1;
  version1.setMajor(major1);
  DeserializedVersion version2;
  version2.setMajor(major2);
  EXPECT_TRUE(version1.isEqual(version2));
}

TEST(runUnitTests, CompareDifferentMajorVersion) {
  uint32_t major1 = 1;
  uint32_t major2 = 2;
  DeserializedVersion version1;
  version1.setMajor(major1);
  DeserializedVersion version2;
  version2.setMajor(major2);
  EXPECT_FALSE(version1.isEqual(version2));
}

TEST(runUnitTests, CompareMajorVersion0) {
  uint32_t major1 = 0;
  uint32_t major2 = 0;
  DeserializedVersion version1;
  version1.setMajor(major1);
  DeserializedVersion version2;
  version2.setMajor(major2);
  EXPECT_TRUE(version1.isEqual(version2));
}

TEST(runUnitTests, Compare0AndNormalMajorVersion) {
  uint32_t major1 = 0;
  uint32_t major2 = 1;
  DeserializedVersion version1;
  version1.setMajor(major1);
  DeserializedVersion version2;
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
  DeserializedVersion version1;
  version1.setMajor(major1);
  version1.setMinor(minor1);
  version1.setPatch(patch1);
  DeserializedVersion version2;
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
  DeserializedVersion version1;
  version1.setMajor(major1);
  version1.setMinor(minor1);
  version1.setPatch(patch1);
  DeserializedVersion version2;
  version2.setMajor(major2);
  version2.setMinor(minor2);
  version2.setPatch(patch2);
  EXPECT_FALSE(version1.isEqual(version2));
}

TEST(runUnitTests, TestSerializeAndDeserializedVersion) {
  uint32_t major1 = 1;
  uint32_t minor1 = 2;
  uint32_t patch1 = 0;
  DeserializedVersion version1;
  version1.setMajor(major1);
  version1.setMinor(minor1);
  version1.setPatch(patch1);
  SerializedVersion serializedVersion = version1.serialize();
  DeserializedVersion version2;
  version2.deserialize(serializedVersion);
  EXPECT_TRUE(version1.isEqual(version2));
}

TEST(runUnitTests, TestSerializeAndDeserialized0Version) {
  uint32_t major1 = 0;
  uint32_t minor1 = 0;
  uint32_t patch1 = 0;
  DeserializedVersion version1;
  version1.setMajor(major1);
  version1.setMinor(minor1);
  version1.setPatch(patch1);
  SerializedVersion serializedVersion = version1.serialize();
  DeserializedVersion version2;
  version2.deserialize(serializedVersion);
  EXPECT_TRUE(version1.isEqual(version2));
}

#include <gtest/gtest.h>
#include "Version.h"

class VersionTest : public ::testing::Test {
 protected:
  Version normalVersion1;
  Version normalVersion2;
  Version startVersion1;
  Version startVersion2;
  Version highVersion1;
  Version highVersion2;
  Version randomVersion1;
  Version randomVersion2;
  uint32_t majorOne = 1;
  uint32_t minorOne = 1;
  uint32_t patchOne = 1;
  uint32_t majorTwo = 2;
  uint32_t minorTwo = 2;
  uint32_t patchTwo = 2;
  uint32_t majorZero = 0;
  uint32_t minorZero = 0;
  uint32_t patchZero = 0;
  virtual void SetUp() {
    this->normalVersion1 = Version(this->majorOne, this->minorOne, this->patchOne);
    this->normalVersion2 = Version(this->majorOne, this->minorOne, this->patchOne);
    this->startVersion1 = Version(this->majorZero, this->minorZero, this->patchZero);
    this->startVersion2 = Version(this->majorZero, this->minorZero, this->patchZero);
    this->highVersion1 = Version(this->majorTwo, this->minorTwo, this->patchTwo);
    this->highVersion2 = Version(this->majorTwo, this->minorTwo, this->patchTwo);
    this->randomVersion1 = Version(this->majorTwo, this->minorOne, this->patchZero);
    this->randomVersion2 = Version(this->majorTwo, this->minorOne, this->patchZero);
  }
};

TEST_F(VersionTest, TestGetMajor) {
  EXPECT_EQ(this->normalVersion1.getMajor(), this->majorOne);
}

TEST_F(VersionTest, TestGetMinor) {
  EXPECT_EQ(this->normalVersion1.getMinor(), this->minorOne);
}

TEST_F(VersionTest, TestGetPatch) {
  EXPECT_EQ(this->normalVersion1.getPatch(), this->patchOne);
}

TEST_F(VersionTest, TestGetAll) {
  EXPECT_EQ(this->randomVersion1.getMajor(), this->majorTwo);
  EXPECT_EQ(this->randomVersion1.getMinor(), this->minorOne);
  EXPECT_EQ(this->randomVersion1.getPatch(), this->patchZero);
}

TEST_F(VersionTest, CompareEqualnormalVersion) {
  EXPECT_TRUE(this->normalVersion1.isEqual(this->normalVersion2));
}

TEST_F(VersionTest, CompareDifferentnormalVersion) {
  EXPECT_FALSE(this->normalVersion1.isEqual(this->startVersion1));
}

TEST_F(VersionTest, CompareEqualstartVersion) {
  EXPECT_TRUE(this->startVersion1.isEqual(startVersion2));
}

TEST_F(VersionTest, CompareRandomAndnormalVersion) {
  EXPECT_FALSE(this->normalVersion1.isEqual(this->randomVersion1));
}

TEST_F(VersionTest, CompareEqualrandomVersion) {
  EXPECT_TRUE(this->randomVersion1.isEqual(this->randomVersion2));
}

TEST_F(VersionTest, TestSerializeAndDeprotobufVersion) {
  ProtobufVersion protobufVersion = this->normalVersion1.serialize();
  Version version2 = Version(protobufVersion);
  EXPECT_TRUE(this->normalVersion1.isEqual(version2));
}

TEST_F(VersionTest, TestSerializeAndDeserialized0Version) {
  ProtobufVersion protobufVersion = this->startVersion1.serialize();
  Version version2 = Version(protobufVersion);
  EXPECT_TRUE(this->startVersion1.isEqual(version2));
}

TEST_F(VersionTest, TestSerializeAndDeserializedrandomVersion) {
  ProtobufVersion protobufVersion = this->randomVersion1.serialize();
  Version version2 = Version(protobufVersion);
  EXPECT_TRUE(this->randomVersion1.isEqual(version2));
}

TEST_F(VersionTest, TestSerializeAndDeserializedhighVersion) {
  ProtobufVersion protobufVersion = this->highVersion1.serialize();
  Version version2 = Version(protobufVersion);
  EXPECT_TRUE(this->highVersion1.isEqual(version2));
}

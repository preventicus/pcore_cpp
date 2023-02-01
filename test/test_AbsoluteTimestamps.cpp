#include <gtest/gtest.h>
#include <vector>
#include "AbsoluteTimestamps.h"
class AbsoluteTimestampsTest : public ::testing::Test {
 protected:
  AbsoluteTimestamps absoluteTimestampsNormal1;
  AbsoluteTimestamps absoluteTimestampsNormal2;
  AbsoluteTimestamps absoluteTimestampsTwoElement1;
  AbsoluteTimestamps absoluteTimestampsTwoElement2;
  AbsoluteTimestamps absoluteTimestampsOneElement1;
  AbsoluteTimestamps absoluteTimestampsOneElement2;
  AbsoluteTimestamps absoluteTimestamps01;
  AbsoluteTimestamps absoluteTimestamps02;
  AbsoluteTimestamps absoluteTimestampsEmpty1;
  AbsoluteTimestamps absoluteTimestampsEmpty2;
  std::vector<uint64_t> unixNormal_ms = {1, 2, 3};
  std::vector<uint64_t> unixTwoElements_ms = {1, 2};
  std::vector<uint64_t> unixOneElement_ms = {1};
  std::vector<uint64_t> unix0_ms = {0};
  std::vector<uint64_t> unixEmpty_ms = {};
  virtual void SetUp() {
    this->absoluteTimestampsNormal1 = AbsoluteTimestamps(this->unixNormal_ms);
    this->absoluteTimestampsNormal2 = AbsoluteTimestamps(this->unixNormal_ms);
    this->absoluteTimestampsTwoElement1 = AbsoluteTimestamps(this->unixTwoElements_ms);
    this->absoluteTimestampsTwoElement2 = AbsoluteTimestamps(this->unixTwoElements_ms);
    this->absoluteTimestampsOneElement1 = AbsoluteTimestamps(this->unixOneElement_ms);
    this->absoluteTimestampsOneElement2 = AbsoluteTimestamps(this->unixOneElement_ms);
    this->absoluteTimestamps01 = AbsoluteTimestamps(this->unix0_ms);
    this->absoluteTimestamps02 = AbsoluteTimestamps(this->unix0_ms);
    this->absoluteTimestampsEmpty1 = AbsoluteTimestamps(this->unixEmpty_ms);
    this->absoluteTimestampsEmpty2 = AbsoluteTimestamps(this->unixEmpty_ms);
  }
};

TEST_F(AbsoluteTimestampsTest, TestGetAndSetValues) {
  EXPECT_EQ(this->absoluteTimestampsNormal1.getUnix(), this->unixNormal_ms);
}

TEST_F(AbsoluteTimestampsTest, TestGetAndSetEmptyValues) {
  EXPECT_EQ(this->absoluteTimestampsEmpty1.getUnix(), this->unixEmpty_ms);
}

TEST_F(AbsoluteTimestampsTest, TestGetAndSet0Values) {
  EXPECT_EQ(this->absoluteTimestamps01.getUnix(), this->unix0_ms);
}

TEST_F(AbsoluteTimestampsTest, CompareEmptyAndFullBlocks) {
  EXPECT_FALSE(this->absoluteTimestampsNormal1.isEqual(this->absoluteTimestampsEmpty1));
}

TEST_F(AbsoluteTimestampsTest, CompareShortAndFullBlocks) {
  EXPECT_FALSE(this->absoluteTimestampsOneElement1.isEqual(this->absoluteTimestampsNormal1));
}

TEST_F(AbsoluteTimestampsTest, CompareSameContentBlocks) {
  EXPECT_TRUE(this->absoluteTimestampsNormal1.isEqual(this->absoluteTimestampsNormal2));
}

TEST_F(AbsoluteTimestampsTest, CompareFullandOneBlocks) {
  EXPECT_FALSE(this->absoluteTimestampsNormal1.isEqual(this->absoluteTimestampsOneElement1));
}

TEST_F(AbsoluteTimestampsTest, CompareFullandShortBlocks) {
  EXPECT_FALSE(this->absoluteTimestampsNormal1.isEqual(this->absoluteTimestampsOneElement1));
}

TEST_F(AbsoluteTimestampsTest, CompareEmptyWithEmptyBlocks) {
  EXPECT_TRUE(this->absoluteTimestampsEmpty1.isEqual(this->absoluteTimestampsEmpty2));
}

TEST_F(AbsoluteTimestampsTest, CompareZeroWithZeroBlocks) {
  EXPECT_TRUE(this->absoluteTimestamps01.isEqual(this->absoluteTimestamps02));
}

TEST_F(AbsoluteTimestampsTest, CompareEmptyWithZeroBlocks) {
  EXPECT_FALSE(this->absoluteTimestamps01.isEqual(this->absoluteTimestampsEmpty1));
}

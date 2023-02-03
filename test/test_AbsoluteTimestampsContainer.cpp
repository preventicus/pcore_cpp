#include <gtest/gtest.h>
#include <vector>
#include "AbsoluteTimestampsContainer.h"
class AbsoluteTimestampsTest : public ::testing::Test {
 protected:
  AbsoluteTimestampsContainer absoluteTimestampsNormal1;
  AbsoluteTimestampsContainer absoluteTimestampsNormal2;
  AbsoluteTimestampsContainer absoluteTimestampsTwoElement1;
  AbsoluteTimestampsContainer absoluteTimestampsTwoElement2;
  AbsoluteTimestampsContainer absoluteTimestampsOneElement1;
  AbsoluteTimestampsContainer absoluteTimestampsOneElement2;
  AbsoluteTimestampsContainer absoluteTimestamps01;
  AbsoluteTimestampsContainer absoluteTimestamps02;
  AbsoluteTimestampsContainer absoluteTimestampsEmpty1;
  AbsoluteTimestampsContainer absoluteTimestampsEmpty2;
  std::vector<uint64_t> unixTimestampsNormal_ms = {1, 2, 3};
  std::vector<uint64_t> unixTimestampsTwoElements_ms = {1, 2};
  std::vector<uint64_t> unixTimestampsOneElement_ms = {1};
  std::vector<uint64_t> unixTimestamps0_ms = {0};
  std::vector<uint64_t> unixTimestampsEmpty_ms = {};
  virtual void SetUp() {
    this->absoluteTimestampsNormal1 = AbsoluteTimestampsContainer(this->unixTimestampsNormal_ms);
    this->absoluteTimestampsNormal2 = AbsoluteTimestampsContainer(this->unixTimestampsNormal_ms);
    this->absoluteTimestampsTwoElement1 = AbsoluteTimestampsContainer(this->unixTimestampsTwoElements_ms);
    this->absoluteTimestampsTwoElement2 = AbsoluteTimestampsContainer(this->unixTimestampsTwoElements_ms);
    this->absoluteTimestampsOneElement1 = AbsoluteTimestampsContainer(this->unixTimestampsOneElement_ms);
    this->absoluteTimestampsOneElement2 = AbsoluteTimestampsContainer(this->unixTimestampsOneElement_ms);
    this->absoluteTimestamps01 = AbsoluteTimestampsContainer(this->unixTimestamps0_ms);
    this->absoluteTimestamps02 = AbsoluteTimestampsContainer(this->unixTimestamps0_ms);
    this->absoluteTimestampsEmpty1 = AbsoluteTimestampsContainer(this->unixTimestampsEmpty_ms);
    this->absoluteTimestampsEmpty2 = AbsoluteTimestampsContainer(this->unixTimestampsEmpty_ms);
  }
};

TEST_F(AbsoluteTimestampsTest, TestGetUnixTimestamps) {
  EXPECT_EQ(this->absoluteTimestampsNormal1.getUnixTimestamps(), this->unixTimestampsNormal_ms);
}

TEST_F(AbsoluteTimestampsTest, TestGetEmptyUnixTimestamps) {
  EXPECT_EQ(this->absoluteTimestampsEmpty1.getUnixTimestamps(), this->unixTimestampsEmpty_ms);
}

TEST_F(AbsoluteTimestampsTest, TestGet0UnixTimestamps) {
  EXPECT_EQ(this->absoluteTimestamps01.getUnixTimestamps(), this->unixTimestamps0_ms);
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

TEST_F(AbsoluteTimestampsTest, CompareFullAndOneBlocks) {
  EXPECT_FALSE(this->absoluteTimestampsNormal1.isEqual(this->absoluteTimestampsOneElement1));
}

TEST_F(AbsoluteTimestampsTest, CompareFullAndShortBlocks) {
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

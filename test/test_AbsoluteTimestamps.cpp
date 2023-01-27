#include <gtest/gtest.h>
#include <vector>
#include "AbsoluteTimestamps.h"

TEST(runUnitTest, TestGetAndSetUnix) {
  std::vector<uint64_t> unix = {1, 2, 3};
  AbsoluteTimestamps timestamps = AbsoluteTimestamps(unix);
  EXPECT_EQ(timestamps.getUnix(), unix);
}

TEST(runUnitTest, TestGetAndSetEmptyUnix) {
  std::vector<uint64_t> unix = {};
  AbsoluteTimestamps timestamps = AbsoluteTimestamps(unix);
  EXPECT_EQ(timestamps.getUnix(), unix);
}

TEST(runUnitTest, TestGetAndSet0Unix) {
  std::vector<uint64_t> unix = {0};
  AbsoluteTimestamps timestamps = AbsoluteTimestamps(unix);
  EXPECT_EQ(timestamps.getUnix(), unix);
}

TEST(runUnitTest, CompareEmptyAndFullTimestamps) {
  std::vector<uint64_t> unix1 = {};
  std::vector<uint64_t> unix2 = {1, 2, 3};
  AbsoluteTimestamps timestamps1 = AbsoluteTimestamps(unix1);
  AbsoluteTimestamps timestamps2 = AbsoluteTimestamps(unix2);
  EXPECT_FALSE(timestamps1.isEqual(timestamps2));
}

TEST(runUnitTest, CompareShortAndFullTimestamps) {
  std::vector<uint64_t> unix1 = {1};
  std::vector<uint64_t> unix2 = {1, 2, 3};
  AbsoluteTimestamps timestamps1 = AbsoluteTimestamps(unix1);
  AbsoluteTimestamps timestamps2 = AbsoluteTimestamps(unix2);
  EXPECT_FALSE(timestamps1.isEqual(timestamps2));
}

TEST(runUnitTest, CompareEqualTimestamps) {
  std::vector<uint64_t> unix1 = {1, 2, 3};
  std::vector<uint64_t> unix2 = {1, 2, 3};
  AbsoluteTimestamps timestamps1 = AbsoluteTimestamps(unix1);
  AbsoluteTimestamps timestamps2 = AbsoluteTimestamps(unix2);
  EXPECT_TRUE(timestamps1.isEqual(timestamps2));
}

TEST(runUnitTest, CompareFullandEmptyTimestamps) {
  std::vector<uint64_t> unix1 = {1, 2, 3};
  std::vector<uint64_t> unix2 = {};
  AbsoluteTimestamps timestamps1 = AbsoluteTimestamps(unix1);
  AbsoluteTimestamps timestamps2 = AbsoluteTimestamps(unix2);
  EXPECT_FALSE(timestamps1.isEqual(timestamps2));
}

TEST(runUnitTest, CompareFullandShortTimestamps) {
  std::vector<uint64_t> unix1 = {1, 2, 3};
  std::vector<uint64_t> unix2 = {1};
  AbsoluteTimestamps timestamps1 = AbsoluteTimestamps(unix1);
  AbsoluteTimestamps timestamps2 = AbsoluteTimestamps(unix2);
  EXPECT_FALSE(timestamps1.isEqual(timestamps2));
}

TEST(runUnitTest, CompareLongWithMediumTimestamps) {
  std::vector<uint64_t> unix1 = {1, 2, 3};
  std::vector<uint64_t> unix2 = {1, 2};
  AbsoluteTimestamps timestamps1 = AbsoluteTimestamps(unix1);
  AbsoluteTimestamps timestamps2 = AbsoluteTimestamps(unix2);
  EXPECT_FALSE(timestamps1.isEqual(timestamps2));
}

TEST(runUnitTest, CompareEmptyWithEmptyTimestamps) {
  std::vector<uint64_t> unix1 = {};
  std::vector<uint64_t> unix2 = {};
  AbsoluteTimestamps timestamps1 = AbsoluteTimestamps(unix1);
  AbsoluteTimestamps timestamps2 = AbsoluteTimestamps(unix2);
  EXPECT_TRUE(timestamps1.isEqual(timestamps2));
}

TEST(runUnitTest, CompareZeroWithZeroTimestamps) {
  std::vector<uint64_t> unix1 = {0};
  std::vector<uint64_t> unix2 = {0};
  AbsoluteTimestamps timestamps1 = AbsoluteTimestamps(unix1);
  AbsoluteTimestamps timestamps2 = AbsoluteTimestamps(unix2);
  EXPECT_TRUE(timestamps1.isEqual(timestamps2));
}

TEST(runUnitTest, CompareEmptyWithZeroTimestamps) {
  std::vector<uint64_t> unix1 = {};
  std::vector<uint64_t> unix2 = {0};
  AbsoluteTimestamps timestamps1 = AbsoluteTimestamps(unix1);
  AbsoluteTimestamps timestamps2 = AbsoluteTimestamps(unix2);
  EXPECT_FALSE(timestamps1.isEqual(timestamps2));
}

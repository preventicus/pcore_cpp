#include <gtest/gtest.h>
#include <vector>
#include "AbsoluteTimestamps.h"

TEST(runUnitTest, TestGetAndSetUnix) {
  std::vector<uint64_t> unix_ms = {1, 2, 3};
  AbsoluteTimestamps timestamps;
  timestamps.setUnix(unix_ms);
  EXPECT_EQ(timestamps.getUnix(), unix_ms);
}

TEST(runUnitTest, TestGetAndSetEmptyUnix) {
  std::vector<uint64_t> unix_ms = {};
  AbsoluteTimestamps timestamps;
  timestamps.setUnix(unix_ms);
  EXPECT_EQ(timestamps.getUnix(), unix_ms);
}

TEST(runUnitTest, TestGetAndSet0Unix) {
  std::vector<uint64_t> unix_ms = {0};
  AbsoluteTimestamps timestamps;
  timestamps.setUnix(unix_ms);
  EXPECT_EQ(timestamps.getUnix(), unix_ms);
}

TEST(runUnitTest, CompareEmptyAndFullTimestamps) {
  std::vector<uint64_t> unix_ms1 = {};
  std::vector<uint64_t> unix_ms2 = {1, 2, 3};
  AbsoluteTimestamps timestamps1;
  timestamps1.setUnix(unix_ms1);
  AbsoluteTimestamps timestamps2;
  timestamps2.setUnix(unix_ms2);
  EXPECT_FALSE(timestamps1.isEqual(timestamps2));
}

TEST(runUnitTest, CompareShortAndFullTimestamps) {
  std::vector<uint64_t> unix_ms1 = {1};
  std::vector<uint64_t> unix_ms2 = {1, 2, 3};
  AbsoluteTimestamps timestamps1;
  timestamps1.setUnix(unix_ms1);
  AbsoluteTimestamps timestamps2;
  timestamps2.setUnix(unix_ms2);
  EXPECT_FALSE(timestamps1.isEqual(timestamps2));
}

TEST(runUnitTest, CompareEqualTimestamps) {
  std::vector<uint64_t> unix_ms1 = {1, 2, 3};
  std::vector<uint64_t> unix_ms2 = {1, 2, 3};
  AbsoluteTimestamps timestamps1;
  timestamps1.setUnix(unix_ms1);
  AbsoluteTimestamps timestamps2;
  timestamps2.setUnix(unix_ms2);

  EXPECT_TRUE(timestamps1.isEqual(timestamps2));
}

TEST(runUnitTest, CompareFullandEmptyTimestamps) {
  std::vector<uint64_t> unix_ms1 = {1, 2, 3};
  std::vector<uint64_t> unix_ms2 = {};
  AbsoluteTimestamps timestamps1;
  timestamps1.setUnix(unix_ms1);
  AbsoluteTimestamps timestamps2;
  timestamps2.setUnix(unix_ms2);

  EXPECT_FALSE(timestamps1.isEqual(timestamps2));
}

TEST(runUnitTest, CompareFullandShortTimestamps) {
  std::vector<uint64_t> unix_ms1 = {1, 2, 3};
  std::vector<uint64_t> unix_ms2 = {1};
  AbsoluteTimestamps timestamps1;
  timestamps1.setUnix(unix_ms1);
  AbsoluteTimestamps timestamps2;
  timestamps2.setUnix(unix_ms2);

  EXPECT_FALSE(timestamps1.isEqual(timestamps2));
}

TEST(runUnitTest, CompareLongWithMediumTimestamps) {
  std::vector<uint64_t> unix_ms1 = {1, 2, 3};
  std::vector<uint64_t> unix_ms2 = {1, 2};
  AbsoluteTimestamps timestamps1;
  timestamps1.setUnix(unix_ms1);
  AbsoluteTimestamps timestamps2;
  timestamps2.setUnix(unix_ms2);

  EXPECT_FALSE(timestamps1.isEqual(timestamps2));
}

TEST(runUnitTest, CompareEmptyWithEmptyTimestamps) {
  std::vector<uint64_t> unix_ms1 = {};
  std::vector<uint64_t> unix_ms2 = {};
  AbsoluteTimestamps timestamps1;
  timestamps1.setUnix(unix_ms1);
  AbsoluteTimestamps timestamps2;
  timestamps2.setUnix(unix_ms2);

  EXPECT_TRUE(timestamps1.isEqual(timestamps2));
}

TEST(runUnitTest, CompareZeroWithZeroTimestamps) {
  std::vector<uint64_t> unix_ms1 = {0};
  std::vector<uint64_t> unix_ms2 = {0};
  AbsoluteTimestamps timestamps1;
  timestamps1.setUnix(unix_ms1);
  AbsoluteTimestamps timestamps2;
  timestamps2.setUnix(unix_ms2);
  EXPECT_TRUE(timestamps1.isEqual(timestamps2));
}

TEST(runUnitTest, CompareEmptyWithZeroTimestamps) {
  std::vector<uint64_t> unix_ms1 = {};
  std::vector<uint64_t> unix_ms2 = {0};
  AbsoluteTimestamps timestamps1;
  timestamps1.setUnix(unix_ms1);
  AbsoluteTimestamps timestamps2;
  timestamps2.setUnix(unix_ms2);

  EXPECT_FALSE(timestamps1.isEqual(timestamps2));
}

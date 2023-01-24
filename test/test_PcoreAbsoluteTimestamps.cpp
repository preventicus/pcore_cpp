#include <gtest/gtest.h>
#include <vector>
#include "PcoreAbsoluteTimestamps.h"

TEST(runUnitTest, TestGetAndSetUnix) {
  std::vector<uint64_t> unix = {1, 2, 3};
  PcoreAbsoluteTimestamps timestamps;
  timestamps.setUnix(unix);
  EXPECT_EQ(timestamps.getUnix(), unix);
}

TEST(runUnitTest, TestGetAndSetEmptyUnix) {
  std::vector<uint64_t> unix = {};
  PcoreAbsoluteTimestamps timestamps;
  timestamps.setUnix(unix);
  EXPECT_EQ(timestamps.getUnix(), unix);
}

TEST(runUnitTest, TestGetAndSet0Unix) {
  std::vector<uint64_t> unix = {0};
  PcoreAbsoluteTimestamps timestamps;
  timestamps.setUnix(unix);
  EXPECT_EQ(timestamps.getUnix(), unix);
}

TEST(runUnitTest, CompareEmptyAndFullTimestamps) {
  std::vector<uint64_t> unix1 = {};
  std::vector<uint64_t> unix2 = {1, 2, 3};

  PcoreAbsoluteTimestamps timestamps1;
  timestamps1.setUnix(unix1);
  PcoreAbsoluteTimestamps timestamps2;
  timestamps2.setUnix(unix2);
  EXPECT_FALSE(timestamps1.isEqual(timestamps2));
}

TEST(runUnitTest, CompareShortAndFullTimestamps) {
  std::vector<uint64_t> unix1 = {1};
  std::vector<uint64_t> unix2 = {1, 2, 3};

  PcoreAbsoluteTimestamps timestamps1;
  timestamps1.setUnix(unix1);
  PcoreAbsoluteTimestamps timestamps2;
  timestamps2.setUnix(unix2);
  EXPECT_FALSE(timestamps1.isEqual(timestamps2));
}

TEST(runUnitTest, CompareEqualTimestamps) {
  std::vector<uint64_t> unix1 = {1, 2, 3};
  std::vector<uint64_t> unix2 = {1, 2, 3};

  PcoreAbsoluteTimestamps timestamps1;
  timestamps1.setUnix(unix1);
  PcoreAbsoluteTimestamps timestamps2;
  timestamps2.setUnix(unix2);

  EXPECT_TRUE(timestamps1.isEqual(timestamps2));
}

TEST(runUnitTest, CompareFullandEmptyTimestamps) {
  std::vector<uint64_t> unix1 = {1, 2, 3};
  std::vector<uint64_t> unix2 = {};

  PcoreAbsoluteTimestamps timestamps1;
  timestamps1.setUnix(unix1);
  PcoreAbsoluteTimestamps timestamps2;
  timestamps2.setUnix(unix2);

  EXPECT_FALSE(timestamps1.isEqual(timestamps2));
}

TEST(runUnitTest, CompareFullandShortTimestamps) {
  std::vector<uint64_t> unix1 = {1, 2, 3};
  std::vector<uint64_t> unix2 = {1};

  PcoreAbsoluteTimestamps timestamps1;
  timestamps1.setUnix(unix1);
  PcoreAbsoluteTimestamps timestamps2;
  timestamps2.setUnix(unix2);

  EXPECT_FALSE(timestamps1.isEqual(timestamps2));
}

TEST(runUnitTest, CompareLongWithMediumTimestamps) {
  std::vector<uint64_t> unix1 = {1, 2, 3};
  std::vector<uint64_t> unix2 = {1, 2};

  PcoreAbsoluteTimestamps timestamps1;
  timestamps1.setUnix(unix1);
  PcoreAbsoluteTimestamps timestamps2;
  timestamps2.setUnix(unix2);

  EXPECT_FALSE(timestamps1.isEqual(timestamps2));
}

TEST(runUnitTest, CompareEmptyWithEmptyTimestamps) {
  std::vector<uint64_t> unix1 = {};
  std::vector<uint64_t> unix2 = {};

  PcoreAbsoluteTimestamps timestamps1;
  timestamps1.setUnix(unix1);
  PcoreAbsoluteTimestamps timestamps2;
  timestamps2.setUnix(unix2);

  EXPECT_TRUE(timestamps1.isEqual(timestamps2));
}

TEST(runUnitTest, CompareZeroWithZeroTimestamps) {
  std::vector<uint64_t> unix1 = {0};
  std::vector<uint64_t> unix2 = {0};

  PcoreAbsoluteTimestamps timestamps1;
  timestamps1.setUnix(unix1);
  PcoreAbsoluteTimestamps timestamps2;
  timestamps2.setUnix(unix2);
  EXPECT_TRUE(timestamps1.isEqual(timestamps2));
}

TEST(runUnitTest, CompareEmptyWithZeroTimestamps) {
  std::vector<uint64_t> unix1 = {};
  std::vector<uint64_t> unix2 = {0};

  PcoreAbsoluteTimestamps timestamps1;
  timestamps1.setUnix(unix1);
  PcoreAbsoluteTimestamps timestamps2;
  timestamps2.setUnix(unix2);

  EXPECT_FALSE(timestamps1.isEqual(timestamps2));
}

#include <gtest/gtest.h>
#include <vector>
#include "PcoreAbsoluteTimestamps.h"

TEST(runUnitTest, compareEmptyAndFullTimestamps) {
  std::vector<uint64_t> unix1 = {};
  std::vector<uint64_t> unix2 = {1, 2, 3};

  PcoreAbsoluteTimestamps timestamps1 = PcoreAbsoluteTimestamps(unix1);
  PcoreAbsoluteTimestamps timestamps2 = PcoreAbsoluteTimestamps(unix2);
  EXPECT_FALSE(timestamps1.isEqual(timestamps2));
}

TEST(runUnitTest, compareshortAndFullTimestamps) {
  std::vector<uint64_t> unix1 = {1};
  std::vector<uint64_t> unix2 = {1, 2, 3};

  PcoreAbsoluteTimestamps timestamps1 = PcoreAbsoluteTimestamps(unix1);
  PcoreAbsoluteTimestamps timestamps2 = PcoreAbsoluteTimestamps(unix2);

  EXPECT_FALSE(timestamps1.isEqual(timestamps2));
}

TEST(runUnitTest, compareMediumAndFullTimestamps) {
  std::vector<uint64_t> unix1 = {1, 2};
  std::vector<uint64_t> unix2 = {1, 2, 3};

  PcoreAbsoluteTimestamps timestamps1 = PcoreAbsoluteTimestamps(unix1);
  PcoreAbsoluteTimestamps timestamps2 = PcoreAbsoluteTimestamps(unix2);

  EXPECT_FALSE(timestamps1.isEqual(timestamps2));
}

TEST(runUnitTest, compareSameContentTimestamps) {
  std::vector<uint64_t> unix1 = {1, 2, 3};
  std::vector<uint64_t> unix2 = {1, 2, 3};

  PcoreAbsoluteTimestamps timestamps1 = PcoreAbsoluteTimestamps(unix1);
  PcoreAbsoluteTimestamps timestamps2 = PcoreAbsoluteTimestamps(unix2);

  EXPECT_TRUE(timestamps1.isEqual(timestamps2));
}

TEST(runUnitTest, compareFullandEmptyTimestamps) {
  std::vector<uint64_t> unix1 = {1, 2, 3};
  std::vector<uint64_t> unix2 = {};

  PcoreAbsoluteTimestamps timestamps1 = PcoreAbsoluteTimestamps(unix1);
  PcoreAbsoluteTimestamps timestamps2 = PcoreAbsoluteTimestamps(unix2);

  EXPECT_FALSE(timestamps1.isEqual(timestamps2));
}

TEST(runUnitTest, compareFullandShortTimestamps) {
  std::vector<uint64_t> unix1 = {1, 2, 3};
  std::vector<uint64_t> unix2 = {1};

  PcoreAbsoluteTimestamps timestamps1 = PcoreAbsoluteTimestamps(unix1);
  PcoreAbsoluteTimestamps timestamps2 = PcoreAbsoluteTimestamps(unix2);

  EXPECT_FALSE(timestamps1.isEqual(timestamps2));
}

TEST(runUnitTest, compareLongWithMediumTimestamps) {
  std::vector<uint64_t> unix1 = {1, 2, 3};
  std::vector<uint64_t> unix2 = {1, 2};

  PcoreAbsoluteTimestamps timestamps1 = PcoreAbsoluteTimestamps(unix1);
  PcoreAbsoluteTimestamps timestamps2 = PcoreAbsoluteTimestamps(unix2);

  EXPECT_FALSE(timestamps1.isEqual(timestamps2));
}
TEST(runUnitTest, compareEmptyWithEmptyTimestamps) {
  std::vector<uint64_t> unix1 = {};
  std::vector<uint64_t> unix2 = {};

  PcoreAbsoluteTimestamps timestamps1 = PcoreAbsoluteTimestamps(unix1);
  PcoreAbsoluteTimestamps timestamps2 = PcoreAbsoluteTimestamps(unix2);

  EXPECT_TRUE(timestamps1.isEqual(timestamps2));
}
TEST(runUnitTest, compareZeroWithZeroTimestamps) {
  std::vector<uint64_t> unix1 = {0};
  std::vector<uint64_t> unix2 = {0};

  PcoreAbsoluteTimestamps timestamps1 = PcoreAbsoluteTimestamps(unix1);
  PcoreAbsoluteTimestamps timestamps2 = PcoreAbsoluteTimestamps(unix2);

  EXPECT_TRUE(timestamps1.isEqual(timestamps2));
}
TEST(runUnitTest, compareEmptyWithZeroTimestamps) {
  std::vector<uint64_t> unix1 = {};
  std::vector<uint64_t> unix2 = {0};

  PcoreAbsoluteTimestamps timestamps1 = PcoreAbsoluteTimestamps(unix1);
  PcoreAbsoluteTimestamps timestamps2 = PcoreAbsoluteTimestamps(unix2);

  EXPECT_FALSE(timestamps1.isEqual(timestamps2));
}

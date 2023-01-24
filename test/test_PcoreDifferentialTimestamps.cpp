#include <gtest/gtest.h>
#include "DeserializedDifferentialTimestamps.h"

TEST(runUnitTests, TestGetAndSetFirstTimestamp) {
  uint64_t first_timestamp_ms = 1690921;
  DeserializedDifferentialTimestamps differentialTimestamps;
  differentialTimestamps.setFirstTimestamp(first_timestamp_ms);
  EXPECT_EQ(differentialTimestamps.getFirstTimestamp(), first_timestamp_ms);
}

TEST(runUnitTests, TestGetAndSetFirstTimestamp0) {
  uint64_t first_timestamp_ms = 0;
  DeserializedDifferentialTimestamps differentialTimestamps;
  differentialTimestamps.setFirstTimestamp(first_timestamp_ms);
  EXPECT_EQ(differentialTimestamps.getFirstTimestamp(), first_timestamp_ms);
}

TEST(runUnitTests, TestGetAndSetBlockIntervals) {
  std::vector<uint32_t> block_intervals_ms = {12, 12, 23, 34};
  DeserializedDifferentialTimestamps differentialTimestamps;
  differentialTimestamps.setBlockIntervals(block_intervals_ms);
  EXPECT_EQ(differentialTimestamps.getBlockIntervals(), block_intervals_ms);
}

TEST(runUnitTests, TestGetAndSetBlockIntervals0) {
  std::vector<uint32_t> block_intervals_ms = {0};
  DeserializedDifferentialTimestamps differentialTimestamps;
  differentialTimestamps.setBlockIntervals(block_intervals_ms);
  EXPECT_EQ(differentialTimestamps.getBlockIntervals(), block_intervals_ms);
}

TEST(runUnitTests, TestGetAndSetBlockIntervalsEmpty) {
  std::vector<uint32_t> block_intervals_ms = {};
  DeserializedDifferentialTimestamps differentialTimestamps;
  differentialTimestamps.setBlockIntervals(block_intervals_ms);
  EXPECT_EQ(differentialTimestamps.getBlockIntervals(), block_intervals_ms);
}

TEST(runUnitTests, TestGetAndSetTimestampsIntervals) {
  std::vector<uint32_t> timestamps_intervals_ms = {134, 31, 124};
  DeserializedDifferentialTimestamps differentialTimestamps;
  differentialTimestamps.setTimestampsIntervals(timestamps_intervals_ms);
  EXPECT_EQ(differentialTimestamps.getTimestampsIntervals(),
            timestamps_intervals_ms);
}

TEST(runUnitTests, TestGetAndSetTimestampsIntervals0) {
  std::vector<uint32_t> timestamps_intervals_ms = {0};
  DeserializedDifferentialTimestamps differentialTimestamps;
  differentialTimestamps.setTimestampsIntervals(timestamps_intervals_ms);
  EXPECT_EQ(differentialTimestamps.getTimestampsIntervals(),
            timestamps_intervals_ms);
}

TEST(runUnitTests, TestGetAndSetTimestampsIntervalsEmpty) {
  std::vector<uint32_t> timestamps_intervals_ms = {};
  DeserializedDifferentialTimestamps differentialTimestamps;
  differentialTimestamps.setTimestampsIntervals(timestamps_intervals_ms);
  EXPECT_EQ(differentialTimestamps.getTimestampsIntervals(),
            timestamps_intervals_ms);
}

TEST(runUnitTests, CompareEqualTimestamps) {
  uint64_t first_timestamp_ms1 = 1690921;
  uint64_t first_timestamp_ms2 = 1690921;
  std::vector<uint32_t> timestamps_intervals_ms1 = {134, 31, 124};
  std::vector<uint32_t> timestamps_intervals_ms2 = {134, 31, 124};
  std::vector<uint32_t> block_intervals_ms1 = {12, 12, 23, 34};
  std::vector<uint32_t> block_intervals_ms2 = {12, 12, 23, 34};
  DeserializedDifferentialTimestamps differentialTimestamps1;
  DeserializedDifferentialTimestamps differentialTimestamps2;
  differentialTimestamps1.setFirstTimestamp(first_timestamp_ms1);
  differentialTimestamps1.setBlockIntervals(block_intervals_ms1);
  differentialTimestamps1.setTimestampsIntervals(timestamps_intervals_ms1);
  differentialTimestamps2.setFirstTimestamp(first_timestamp_ms2);
  differentialTimestamps2.setBlockIntervals(block_intervals_ms2);
  differentialTimestamps2.setTimestampsIntervals(timestamps_intervals_ms2);
  EXPECT_TRUE(differentialTimestamps1.isEqual(differentialTimestamps2));
}

TEST(runUnitTests, CompareDifferentFirstTimestamps) {
  uint64_t first_timestamp_ms1 = 1690921;
  uint64_t first_timestamp_ms2 = 1800123;
  std::vector<uint32_t> timestamps_intervals_ms1 = {134, 31, 124};
  std::vector<uint32_t> timestamps_intervals_ms2 = {134, 31, 124};
  std::vector<uint32_t> block_intervals_ms1 = {12, 12, 23, 34};
  std::vector<uint32_t> block_intervals_ms2 = {12, 12, 23, 34};
  DeserializedDifferentialTimestamps differentialTimestamps1;
  DeserializedDifferentialTimestamps differentialTimestamps2;
  differentialTimestamps1.setFirstTimestamp(first_timestamp_ms1);
  differentialTimestamps1.setBlockIntervals(block_intervals_ms1);
  differentialTimestamps1.setTimestampsIntervals(timestamps_intervals_ms1);
  differentialTimestamps2.setFirstTimestamp(first_timestamp_ms2);
  differentialTimestamps2.setBlockIntervals(block_intervals_ms2);
  differentialTimestamps2.setTimestampsIntervals(timestamps_intervals_ms2);
  EXPECT_FALSE(differentialTimestamps1.isEqual(differentialTimestamps2));
}

TEST(runUnitTests, CompareDifferentBlockintervals) {
  uint64_t first_timestamp_ms1 = 1690921;
  uint64_t first_timestamp_ms2 = 1690921;
  std::vector<uint32_t> timestamps_intervals_ms1 = {134, 31, 124};
  std::vector<uint32_t> timestamps_intervals_ms2 = {134, 31, 124};
  std::vector<uint32_t> block_intervals_ms1 = {12, 12, 23, 34};
  std::vector<uint32_t> block_intervals_ms2 = {12, 45, 23, 98};
  DeserializedDifferentialTimestamps differentialTimestamps1;
  DeserializedDifferentialTimestamps differentialTimestamps2;
  differentialTimestamps1.setFirstTimestamp(first_timestamp_ms1);
  differentialTimestamps1.setBlockIntervals(block_intervals_ms1);
  differentialTimestamps1.setTimestampsIntervals(timestamps_intervals_ms1);
  differentialTimestamps2.setFirstTimestamp(first_timestamp_ms2);
  differentialTimestamps2.setBlockIntervals(block_intervals_ms2);
  differentialTimestamps2.setTimestampsIntervals(timestamps_intervals_ms2);
  EXPECT_FALSE(differentialTimestamps1.isEqual(differentialTimestamps2));
}

TEST(runUnitTests, CompareDifferentTimestampsIntervals) {
  uint64_t first_timestamp_ms1 = 1690921;
  uint64_t first_timestamp_ms2 = 1690921;
  std::vector<uint32_t> timestamps_intervals_ms1 = {134, 31, 124};
  std::vector<uint32_t> timestamps_intervals_ms2 = {55, 123, 187};
  std::vector<uint32_t> block_intervals_ms1 = {12, 12, 23, 34};
  std::vector<uint32_t> block_intervals_ms2 = {12, 12, 23, 34};
  DeserializedDifferentialTimestamps differentialTimestamps1;
  DeserializedDifferentialTimestamps differentialTimestamps2;
  differentialTimestamps1.setFirstTimestamp(first_timestamp_ms1);
  differentialTimestamps1.setBlockIntervals(block_intervals_ms1);
  differentialTimestamps1.setTimestampsIntervals(timestamps_intervals_ms1);
  differentialTimestamps2.setFirstTimestamp(first_timestamp_ms2);
  differentialTimestamps2.setBlockIntervals(block_intervals_ms2);
  differentialTimestamps2.setTimestampsIntervals(timestamps_intervals_ms2);
  EXPECT_FALSE(differentialTimestamps1.isEqual(differentialTimestamps2));
}

TEST(runUnitTests, TestSerializeandDeserializeEqualTimestamps) {
  uint64_t first_timestamp_ms1 = 1690921;
  std::vector<uint32_t> timestamps_intervals_ms1 = {134, 31, 124};
  std::vector<uint32_t> block_intervals_ms1 = {12, 113, 23, 34};
  DeserializedDifferentialTimestamps differentialTimestamps1;
  differentialTimestamps1.setFirstTimestamp(first_timestamp_ms1);
  differentialTimestamps1.setBlockIntervals(block_intervals_ms1);
  differentialTimestamps1.setTimestampsIntervals(timestamps_intervals_ms1);
  SerializedTimestampContainer serializedTimestampContainer =
      differentialTimestamps1.serialize();
  DeserializedDifferentialTimestamps differentialTimestamps2;
  differentialTimestamps2.deserialize(serializedTimestampContainer);
  EXPECT_TRUE(differentialTimestamps1.isEqual(differentialTimestamps2));
}

TEST(runUnitTests, TestSerializeandDeserializeBetweenTwoTimestamps) {
  uint64_t first_timestamp_ms1 = 1690921;
  std::vector<uint32_t> timestamps_intervals_ms1 = {134, 31, 124};
  std::vector<uint32_t> block_intervals_ms1 = {12, 12, 23, 34};
  DeserializedDifferentialTimestamps differentialTimestamps1;
  differentialTimestamps1.setFirstTimestamp(first_timestamp_ms1);
  differentialTimestamps1.setBlockIntervals(block_intervals_ms1);
  differentialTimestamps1.setTimestampsIntervals(timestamps_intervals_ms1);
  SerializedTimestampContainer serializedTimestampContainer1 =
      differentialTimestamps1.serialize();
  DeserializedDifferentialTimestamps differentialTimestamps2;
  differentialTimestamps2.deserialize(serializedTimestampContainer1);
  uint64_t first_timestamp_ms2 = 1690921;
  std::vector<uint32_t> timestamps_intervals_ms2 = {134, 31, 124};
  std::vector<uint32_t> block_intervals_ms2 = {12, 12, 23, 34};
  DeserializedDifferentialTimestamps differentialTimestamps3;
  differentialTimestamps3.setFirstTimestamp(first_timestamp_ms2);
  differentialTimestamps3.setBlockIntervals(block_intervals_ms2);
  differentialTimestamps3.setTimestampsIntervals(timestamps_intervals_ms2);
  SerializedTimestampContainer serializedTimestampContainer2 =
      differentialTimestamps3.serialize();
  DeserializedDifferentialTimestamps differentialTimestamps4;
  differentialTimestamps4.deserialize(serializedTimestampContainer2);
  EXPECT_TRUE(differentialTimestamps2.isEqual(differentialTimestamps4));
}

TEST(runUnitTests, TestSerializeandDeserializeTwoDifferentTimestamps) {
  uint64_t first_timestamp_ms1 = 12;
  std::vector<uint32_t> timestamps_intervals_ms1 = {134, 31, 124};
  std::vector<uint32_t> block_intervals_ms1 = {12, 12, 23, 34};
  DeserializedDifferentialTimestamps differentialTimestamps1;
  differentialTimestamps1.setFirstTimestamp(first_timestamp_ms1);
  differentialTimestamps1.setBlockIntervals(block_intervals_ms1);
  differentialTimestamps1.setTimestampsIntervals(timestamps_intervals_ms1);
  SerializedTimestampContainer serializedTimestampContainer1 =
      differentialTimestamps1.serialize();
  DeserializedDifferentialTimestamps differentialTimestamps2;
  differentialTimestamps2.deserialize(serializedTimestampContainer1);
  uint64_t first_timestamp_ms2 = 1690921;
  std::vector<uint32_t> timestamps_intervals_ms2 = {134, 31, 124};
  std::vector<uint32_t> block_intervals_ms2 = {12, 12, 23, 34};
  DeserializedDifferentialTimestamps differentialTimestamps3;
  differentialTimestamps3.setFirstTimestamp(first_timestamp_ms2);
  differentialTimestamps3.setBlockIntervals(block_intervals_ms2);
  differentialTimestamps3.setTimestampsIntervals(timestamps_intervals_ms2);
  SerializedTimestampContainer serializedTimestampContainer2 =
      differentialTimestamps3.serialize();
  DeserializedDifferentialTimestamps differentialTimestamps4;
  differentialTimestamps4.deserialize(serializedTimestampContainer2);
  EXPECT_FALSE(differentialTimestamps2.isEqual(differentialTimestamps4));
}

TEST(runUnitTests, TestCalculateFirstTimestampInBlock) {
  uint64_t first_timestamp_ms1 = 10;
  std::vector<uint32_t> block_intervals_ms1 = {
      0, 113, 23,
      34};  // first block_intervall[0] is always null - one loop less is needed
  uint32_t blockIdx = 2;
  DeserializedDifferentialTimestamps differentialTimestamps1;
  differentialTimestamps1.setFirstTimestamp(first_timestamp_ms1);
  differentialTimestamps1.setBlockIntervals(block_intervals_ms1);
  uint32_t firstTimestampInBlock =
      differentialTimestamps1.calculateFirstTimestampInBlock(blockIdx);
  EXPECT_EQ(firstTimestampInBlock, 146);
}

TEST(runUnitTests, TestCalculateLastTimestampInBlock) {
  uint64_t first_timestamp_ms1 = 10;
  uint32_t blockIdx = 2;
  std::vector<uint32_t> timestamps_intervals_ms = {134, 31, 124};
  std::vector<uint32_t> block_intervals_ms1 = {
      0, 113, 23,
      34};  // first block_intervall[0] is always null - one loop less is needed
  DeserializedDifferentialTimestamps differentialTimestamps1;
  differentialTimestamps1.setFirstTimestamp(first_timestamp_ms1);
  differentialTimestamps1.setBlockIntervals(block_intervals_ms1);
  differentialTimestamps1.setTimestampsIntervals(timestamps_intervals_ms);
  uint32_t firstTimestampInBlock = 146;
  std::vector<int32_t> diffValues = {30, 32, 54};
  DeserializedDifferentialBlock deserializedDifferentialBlock;
  deserializedDifferentialBlock.setDiffValues(diffValues);

  uint32_t lastTimestampInBlock =
      differentialTimestamps1.calculateLastTimestampInBlock(
          blockIdx, firstTimestampInBlock, deserializedDifferentialBlock);
  EXPECT_EQ(lastTimestampInBlock, 518);
}

TEST(runUnitTests, TestCalculateLastTimestampInBlock0) {
  uint32_t blockIdx = 0;
  uint32_t firstTimestampInBlock = 150;
  std::vector<uint32_t> timestamps_intervals_ms = {134, 31, 124};
  std::vector<int32_t> diffValues = {30, 32, 54};
  DeserializedDifferentialTimestamps differentialTimestamps1;
  differentialTimestamps1.setTimestampsIntervals(timestamps_intervals_ms);
  DeserializedDifferentialBlock deserializedDifferentialBlock;
  deserializedDifferentialBlock.setDiffValues(diffValues);
  uint32_t lastTimestampInBlock =
      differentialTimestamps1.calculateLastTimestampInBlock(
          blockIdx, firstTimestampInBlock, deserializedDifferentialBlock);
  EXPECT_EQ(lastTimestampInBlock, 552);
}

TEST(runUnitTests, TestCalculateLastTimestampInBlockException) {
  try {
    uint64_t first_timestamp_ms1 = 10;
    uint32_t blockIdx = 7;
    std::vector<uint32_t> timestamps_intervals_ms = {134, 31, 124};
    std::vector<uint32_t> block_intervals_ms1 = {
        0, 113, 23, 34};  // first block_intervall[0] is always null - one loop
                          // less is needed
    DeserializedDifferentialTimestamps differentialTimestamps1;
    differentialTimestamps1.setFirstTimestamp(first_timestamp_ms1);
    differentialTimestamps1.setBlockIntervals(block_intervals_ms1);
    differentialTimestamps1.setTimestampsIntervals(timestamps_intervals_ms);
    uint32_t firstTimestampInBlock =
        differentialTimestamps1.calculateFirstTimestampInBlock(
            2);  // firstTimestampInBlock = 146
    std::vector<int32_t> diffValues = {30, 32, 54};
    DeserializedDifferentialBlock deserializedDifferentialBlock;
    deserializedDifferentialBlock.setDiffValues(diffValues);
    uint32_t lastTimestampInBlock =
        differentialTimestamps1.calculateLastTimestampInBlock(
            blockIdx, firstTimestampInBlock, deserializedDifferentialBlock);
  } catch (const std::invalid_argument& e) {
    EXPECT_EQ(e.what(), "blockIdx is higher than number of block_intervals_ms");
    FAIL() << "Expected std::invalid_argument";
  } catch (std::invalid_argument const& e) {
    EXPECT_EQ(
        e.what(),
        std::string("blockIdx is higher than number of block_intervals_ms"));
  } catch (...) {
    FAIL() << "Expected std::invalid_argument";
  }
}
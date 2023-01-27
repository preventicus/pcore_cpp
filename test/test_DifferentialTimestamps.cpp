#include <gtest/gtest.h>
#include "DifferentialTimestamps.h"

TEST(runUnitTests, TestGetAndSetFirstTimestamp) {
  uint64_t firstTimestamp_ms = 1690921;
  std::vector<uint32_t> blockIntervals_ms = {12, 12, 23, 34};
  std::vector<uint32_t> timestampsIntervals_ms = {134, 31, 124};
  DifferentialTimestamps differentialTimestamps = DifferentialTimestamps(firstTimestamp_ms, blockIntervals_ms, timestampsIntervals_ms);
  EXPECT_EQ(differentialTimestamps.getFirstTimestamp(), firstTimestamp_ms);
}

TEST(runUnitTests, TestGetAndSetFirstTimestamp0) {
  uint64_t firstTimestamp_ms = 0;
  std::vector<uint32_t> blockIntervals_ms = {12, 12, 23, 34};
  std::vector<uint32_t> timestampsIntervals_ms = {134, 31, 124};
  DifferentialTimestamps differentialTimestamps = DifferentialTimestamps(firstTimestamp_ms, blockIntervals_ms, timestampsIntervals_ms);
  EXPECT_EQ(differentialTimestamps.getFirstTimestamp(), firstTimestamp_ms);
}

TEST(runUnitTests, TestGetAndSetBlockIntervals) {
  uint64_t firstTimestamp_ms = 0;
  std::vector<uint32_t> blockIntervals_ms = {12, 12, 23, 34};
  std::vector<uint32_t> timestampsIntervals_ms = {134, 31, 124};
  DifferentialTimestamps differentialTimestamps = DifferentialTimestamps(firstTimestamp_ms, blockIntervals_ms, timestampsIntervals_ms);
  EXPECT_EQ(differentialTimestamps.getBlockIntervals(), blockIntervals_ms);
}

TEST(runUnitTests, TestGetAndSetBlockIntervals0) {
  uint64_t firstTimestamp_ms = 0;
  std::vector<uint32_t> blockIntervals_ms = {0};
  std::vector<uint32_t> timestampsIntervals_ms = {134, 31, 124};
  DifferentialTimestamps differentialTimestamps = DifferentialTimestamps(firstTimestamp_ms, blockIntervals_ms, timestampsIntervals_ms);
  EXPECT_EQ(differentialTimestamps.getBlockIntervals(), blockIntervals_ms);
}

TEST(runUnitTests, TestGetAndSetBlockIntervalsEmpty) {
  uint64_t firstTimestamp_ms = 0;
  std::vector<uint32_t> blockIntervals_ms = {};
  std::vector<uint32_t> timestampsIntervals_ms = {134, 31, 124};
  DifferentialTimestamps differentialTimestamps = DifferentialTimestamps(firstTimestamp_ms, blockIntervals_ms, timestampsIntervals_ms);
  EXPECT_EQ(differentialTimestamps.getBlockIntervals(), blockIntervals_ms);
}

TEST(runUnitTests, TestGetAndSetTimestampsIntervals) {
  uint64_t firstTimestamp_ms = 0;
  std::vector<uint32_t> blockIntervals_ms = {12, 12, 23, 34};
  std::vector<uint32_t> timestampsIntervals_ms = {134, 31, 124};
  DifferentialTimestamps differentialTimestamps = DifferentialTimestamps(firstTimestamp_ms, blockIntervals_ms, timestampsIntervals_ms);
  EXPECT_EQ(differentialTimestamps.getTimestampsIntervals(), timestampsIntervals_ms);
}

TEST(runUnitTests, TestGetAndSetTimestampsIntervals0) {
  uint64_t firstTimestamp_ms = 0;
  std::vector<uint32_t> blockIntervals_ms = {12, 12, 23, 34};
  std::vector<uint32_t> timestampsIntervals_ms = {0};
  DifferentialTimestamps differentialTimestamps = DifferentialTimestamps(firstTimestamp_ms, blockIntervals_ms, timestampsIntervals_ms);
  EXPECT_EQ(differentialTimestamps.getTimestampsIntervals(), timestampsIntervals_ms);
}

TEST(runUnitTests, TestGetAndSetTimestampsIntervalsEmpty) {
  uint64_t firstTimestamp_ms = 0;
  std::vector<uint32_t> blockIntervals_ms = {12, 12, 23, 34};
  std::vector<uint32_t> timestampsIntervals_ms = {};
  DifferentialTimestamps differentialTimestamps = DifferentialTimestamps(firstTimestamp_ms, blockIntervals_ms, timestampsIntervals_ms);
  EXPECT_EQ(differentialTimestamps.getTimestampsIntervals(), timestampsIntervals_ms);
}

TEST(runUnitTests, CompareEqualTimestamps) {
  uint64_t firstTimestamp_ms1 = 1690921;
  uint64_t firstTimestamp_ms2 = 1690921;
  std::vector<uint32_t> timestampsIntervals_ms1 = {134, 31, 124};
  std::vector<uint32_t> timestampsIntervals_ms2 = {134, 31, 124};
  std::vector<uint32_t> blockIntervals_ms1 = {12, 12, 23, 34};
  std::vector<uint32_t> blockIntervals_ms2 = {12, 12, 23, 34};
  DifferentialTimestamps differentialTimestamps1 = DifferentialTimestamps(firstTimestamp_ms1, blockIntervals_ms2, timestampsIntervals_ms1);
  DifferentialTimestamps differentialTimestamps2 = DifferentialTimestamps(firstTimestamp_ms2, blockIntervals_ms2, timestampsIntervals_ms2);
  EXPECT_TRUE(differentialTimestamps1.isEqual(differentialTimestamps2));
}

TEST(runUnitTests, CompareDifferentFirstTimestamps) {
  uint64_t firstTimestamp_ms1 = 1690921;
  uint64_t firstTimestamp_ms2 = 1800123;
  std::vector<uint32_t> timestampsIntervals_ms1 = {134, 31, 124};
  std::vector<uint32_t> timestampsIntervals_ms2 = {134, 31, 124};
  std::vector<uint32_t> blockIntervals_ms1 = {12, 12, 23, 34};
  std::vector<uint32_t> blockIntervals_ms2 = {12, 12, 23, 34};
  DifferentialTimestamps differentialTimestamps1 = DifferentialTimestamps(firstTimestamp_ms1, blockIntervals_ms1, timestampsIntervals_ms1);
  DifferentialTimestamps differentialTimestamps2 = DifferentialTimestamps(firstTimestamp_ms2, blockIntervals_ms2, timestampsIntervals_ms2);

  EXPECT_FALSE(differentialTimestamps1.isEqual(differentialTimestamps2));
}

TEST(runUnitTests, CompareDifferentBlockintervals) {
  uint64_t firstTimestamp_ms1 = 1690921;
  uint64_t firstTimestamp_ms2 = 1690921;
  std::vector<uint32_t> timestampsIntervals_ms1 = {134, 31, 124};
  std::vector<uint32_t> timestampsIntervals_ms2 = {134, 31, 124};
  std::vector<uint32_t> blockIntervals_ms1 = {12, 12, 23, 34};
  std::vector<uint32_t> blockIntervals_ms2 = {12, 45, 23, 98};
  DifferentialTimestamps differentialTimestamps1 = DifferentialTimestamps(firstTimestamp_ms1, blockIntervals_ms1, timestampsIntervals_ms1);
  DifferentialTimestamps differentialTimestamps2 = DifferentialTimestamps(firstTimestamp_ms2, blockIntervals_ms2, timestampsIntervals_ms2);

  EXPECT_FALSE(differentialTimestamps1.isEqual(differentialTimestamps2));
}

TEST(runUnitTests, CompareDifferentTimestampsIntervals) {
  uint64_t firstTimestamp_ms1 = 1690921;
  uint64_t firstTimestamp_ms2 = 1690921;
  std::vector<uint32_t> timestampsIntervals_ms1 = {134, 31, 124};
  std::vector<uint32_t> timestampsIntervals_ms2 = {55, 123, 187};
  std::vector<uint32_t> blockIntervals_ms1 = {12, 12, 23, 34};
  std::vector<uint32_t> blockIntervals_ms2 = {12, 12, 23, 34};
  DifferentialTimestamps differentialTimestamps1 = DifferentialTimestamps(firstTimestamp_ms1, blockIntervals_ms1, timestampsIntervals_ms1);
  DifferentialTimestamps differentialTimestamps2 = DifferentialTimestamps(firstTimestamp_ms2, blockIntervals_ms1, timestampsIntervals_ms2);

  EXPECT_FALSE(differentialTimestamps1.isEqual(differentialTimestamps2));
}

TEST(runUnitTests, TestSerializeandDeserializeEqualTimestamps) {
  uint64_t firstTimestamp_ms = 1690921;
  std::vector<uint32_t> timestampsIntervals_ms = {134, 31, 124};
  std::vector<uint32_t> blockIntervals_ms = {12, 113, 23, 34};
  DifferentialTimestamps differentialTimestamps1 = DifferentialTimestamps(firstTimestamp_ms, blockIntervals_ms, timestampsIntervals_ms);
  ProtobufTimestampContainer protobufTimestampContainer = differentialTimestamps1.serialize();
  DifferentialTimestamps differentialTimestamps2 = DifferentialTimestamps(protobufTimestampContainer);
  EXPECT_TRUE(differentialTimestamps1.isEqual(differentialTimestamps2));
}

TEST(runUnitTests, TestSerializeandDeserializeBetweenTwoDifferentTimestamps) {
  uint64_t firstTimestamp_ms1 = 1690921;
  std::vector<uint32_t> timestampsIntervals_ms1 = {134, 31, 124};
  std::vector<uint32_t> blockIntervals_ms1 = {12, 12, 23, 34};
  DifferentialTimestamps differentialTimestamps1 = DifferentialTimestamps(firstTimestamp_ms1, blockIntervals_ms1, timestampsIntervals_ms1);
  ProtobufTimestampContainer protobufTimestampContainer1 = differentialTimestamps1.serialize();
  uint64_t firstTimestamp_ms2 = 1690921;
  std::vector<uint32_t> timestampsIntervals_ms2 = {134, 31, 124};
  std::vector<uint32_t> blockIntervals_ms2 = {12, 12, 23, 34};
  DifferentialTimestamps differentialTimestamps2 = DifferentialTimestamps(firstTimestamp_ms2, blockIntervals_ms2, timestampsIntervals_ms2);
  ProtobufTimestampContainer protobufTimestampContainer2 = differentialTimestamps2.serialize();
  DifferentialTimestamps differentialTimestamps3 = DifferentialTimestamps(protobufTimestampContainer1);
  DifferentialTimestamps differentialTimestamps4 = DifferentialTimestamps(protobufTimestampContainer2);
  EXPECT_TRUE(differentialTimestamps3.isEqual(differentialTimestamps4));
}

TEST(runUnitTests, TestSerializeandDeserializeBetweenTwoTimestamps) {
  uint64_t firstTimestamp_ms1 = 0;
  std::vector<uint32_t> timestampsIntervals_ms1 = {134, 31, 124};
  std::vector<uint32_t> blockIntervals_ms1 = {12, 12, 23, 34};
  DifferentialTimestamps differentialTimestamps1 = DifferentialTimestamps(firstTimestamp_ms1, blockIntervals_ms1, timestampsIntervals_ms1);
  ProtobufTimestampContainer protobufTimestampContainer1 = differentialTimestamps1.serialize();
  uint64_t firstTimestamp_ms2 = 1690921;
  std::vector<uint32_t> timestampsIntervals_ms2 = {134, 31, 124};
  std::vector<uint32_t> blockIntervals_ms2 = {12, 12, 23, 34};
  DifferentialTimestamps differentialTimestamps2 = DifferentialTimestamps(firstTimestamp_ms2, blockIntervals_ms2, timestampsIntervals_ms2);
  ProtobufTimestampContainer protobufTimestampContainer2 = differentialTimestamps2.serialize();
  DifferentialTimestamps differentialTimestamps3 = DifferentialTimestamps(protobufTimestampContainer1);
  DifferentialTimestamps differentialTimestamps4 = DifferentialTimestamps(protobufTimestampContainer2);
  EXPECT_FALSE(differentialTimestamps3.isEqual(differentialTimestamps4));
}

TEST(runUnitTests, TestCalculateFirstTimestampInBlock) {
  uint64_t firstTimestamp_ms = 10;
  std::vector<uint32_t> blockIntervals_ms = {0, 113, 23, 34};  // first block_intervall[0] is always null - one loop less is needed
  std::vector<uint32_t> timestampsIntervals_ms = {134, 31, 124};
  uint32_t blockIdx = 2;
  DifferentialTimestamps differentialTimestamps = DifferentialTimestamps(firstTimestamp_ms, blockIntervals_ms, timestampsIntervals_ms);
  EXPECT_EQ(differentialTimestamps.calculateFirstTimestampInBlock(blockIdx), 146);
}

TEST(runUnitTests, TestCalculateLastTimestampInBlock) {
  uint64_t firstTimestamp_ms = 10;
  uint32_t blockIdx = 2;
  std::vector<uint32_t> timestampsIntervals_ms = {134, 31, 124};
  std::vector<uint32_t> blockIntervals_ms = {0, 113, 23, 34};  // first block_intervall[0] is always null - one loop less is needed
  DifferentialTimestamps differentialTimestamps = DifferentialTimestamps(firstTimestamp_ms, blockIntervals_ms, timestampsIntervals_ms);
  uint32_t firstTimestampInBlock = 146;
  std::vector<int32_t> diffValues = {30, 32, 54};
  DifferentialBlock protobufDifferentialBlock = DifferentialBlock(diffValues);
  EXPECT_EQ(differentialTimestamps.calculateLastTimestampInBlock(blockIdx, firstTimestampInBlock, protobufDifferentialBlock), 518);
}

TEST(runUnitTests, TestCalculateLastTimestampInBlock0) {
  uint64_t firstTimestamp_ms = 10;
  std::vector<uint32_t> blockIntervals_ms = {0, 113, 23, 34};
  uint32_t blockIdx = 0;
  uint32_t firstTimestampInBlock = 150;
  std::vector<uint32_t> timestampsIntervals_ms = {134, 31, 124};
  std::vector<int32_t> diffValues = {30, 32, 54};
  DifferentialTimestamps differentialTimestamps = DifferentialTimestamps(firstTimestamp_ms, blockIntervals_ms, timestampsIntervals_ms);
  DifferentialBlock differentialBlock = DifferentialBlock(diffValues);
  EXPECT_EQ(differentialTimestamps.calculateLastTimestampInBlock(blockIdx, firstTimestampInBlock, differentialBlock), 552);
}

TEST(runUnitTests, TestCalculateLastTimestampInBlockException) {
  uint64_t firstTimestamp_ms = 10;
  std::vector<uint32_t> timestampsIntervals_ms = {134, 31, 124};
  std::vector<uint32_t> blockIntervals_ms = {0, 113, 23, 34};  // first block_intervall[0] is always null - one loop less is needed
  DifferentialTimestamps differentialTimestamps = DifferentialTimestamps(firstTimestamp_ms, blockIntervals_ms, timestampsIntervals_ms);
  uint32_t blockIdx = 10;
  std::vector<int32_t> diffValues = {30, 32, 54};
  DifferentialBlock protobufDifferentialBlock = DifferentialBlock(diffValues);
  EXPECT_THROW(differentialTimestamps.calculateFirstTimestampInBlock(blockIdx), std::invalid_argument);
}

#include <gtest/gtest.h>
#include "DeserializedDifferentialTimestamps.h"

TEST(runUnitTests, TestGetAndSetFirstTimestamp) {
  uint64_t firstTimestamp_ms = 1690921;
  DeserializedDifferentialTimestamps differentialTimestamps;
  differentialTimestamps.setFirstTimestamp(firstTimestamp_ms);
  EXPECT_EQ(differentialTimestamps.getFirstTimestamp(), firstTimestamp_ms);
}

TEST(runUnitTests, TestGetAndSetFirstTimestamp0) {
  uint64_t firstTimestamp_ms = 0;
  DeserializedDifferentialTimestamps differentialTimestamps;
  differentialTimestamps.setFirstTimestamp(firstTimestamp_ms);
  EXPECT_EQ(differentialTimestamps.getFirstTimestamp(), firstTimestamp_ms);
}

TEST(runUnitTests, TestGetAndSetBlockIntervals) {
  std::vector<uint32_t> blockIntervals_ms = {12, 12, 23, 34};
  DeserializedDifferentialTimestamps differentialTimestamps;
  differentialTimestamps.setBlockIntervals(blockIntervals_ms);
  EXPECT_EQ(differentialTimestamps.getBlockIntervals(), blockIntervals_ms);
}

TEST(runUnitTests, TestGetAndSetBlockIntervals0) {
  std::vector<uint32_t> blockIntervals_ms = {0};
  DeserializedDifferentialTimestamps differentialTimestamps;
  differentialTimestamps.setBlockIntervals(blockIntervals_ms);
  EXPECT_EQ(differentialTimestamps.getBlockIntervals(), blockIntervals_ms);
}

TEST(runUnitTests, TestGetAndSetBlockIntervalsEmpty) {
  std::vector<uint32_t> blockIntervals_ms = {};
  DeserializedDifferentialTimestamps differentialTimestamps;
  differentialTimestamps.setBlockIntervals(blockIntervals_ms);
  EXPECT_EQ(differentialTimestamps.getBlockIntervals(), blockIntervals_ms);
}

TEST(runUnitTests, TestGetAndSetTimestampsIntervals) {
  std::vector<uint32_t> timestampsIntervals_ms = {134, 31, 124};
  DeserializedDifferentialTimestamps differentialTimestamps;
  differentialTimestamps.setTimestampsIntervals(timestampsIntervals_ms);
  EXPECT_EQ(differentialTimestamps.getTimestampsIntervals(), timestampsIntervals_ms);
}

TEST(runUnitTests, TestGetAndSetTimestampsIntervals0) {
  std::vector<uint32_t> timestampsIntervals_ms = {0};
  DeserializedDifferentialTimestamps differentialTimestamps;
  differentialTimestamps.setTimestampsIntervals(timestampsIntervals_ms);
  EXPECT_EQ(differentialTimestamps.getTimestampsIntervals(), timestampsIntervals_ms);
}

TEST(runUnitTests, TestGetAndSetTimestampsIntervalsEmpty) {
  std::vector<uint32_t> timestampsIntervals_ms = {};
  DeserializedDifferentialTimestamps differentialTimestamps;
  differentialTimestamps.setTimestampsIntervals(timestampsIntervals_ms);
  EXPECT_EQ(differentialTimestamps.getTimestampsIntervals(), timestampsIntervals_ms);
}

TEST(runUnitTests, CompareEqualTimestamps) {
  uint64_t firstTimestamp_ms1 = 1690921;
  uint64_t firstTimestamp_ms2 = 1690921;
  std::vector<uint32_t> timestampsIntervals_ms1 = {134, 31, 124};
  std::vector<uint32_t> timestampsIntervals_ms2 = {134, 31, 124};
  std::vector<uint32_t> blockIntervals_ms1 = {12, 12, 23, 34};
  std::vector<uint32_t> blockIntervals_ms2 = {12, 12, 23, 34};
  DeserializedDifferentialTimestamps differentialTimestamps1;
  DeserializedDifferentialTimestamps differentialTimestamps2;
  differentialTimestamps1.setFirstTimestamp(firstTimestamp_ms1);
  differentialTimestamps1.setBlockIntervals(blockIntervals_ms1);
  differentialTimestamps1.setTimestampsIntervals(timestampsIntervals_ms1);
  differentialTimestamps2.setFirstTimestamp(firstTimestamp_ms2);
  differentialTimestamps2.setBlockIntervals(blockIntervals_ms2);
  differentialTimestamps2.setTimestampsIntervals(timestampsIntervals_ms2);
  EXPECT_TRUE(differentialTimestamps1.isEqual(differentialTimestamps2));
}

TEST(runUnitTests, CompareDifferentFirstTimestamps) {
  uint64_t firstTimestamp_ms1 = 1690921;
  uint64_t firstTimestamp_ms2 = 1800123;
  std::vector<uint32_t> timestampsIntervals_ms1 = {134, 31, 124};
  std::vector<uint32_t> timestampsIntervals_ms2 = {134, 31, 124};
  std::vector<uint32_t> blockIntervals_ms1 = {12, 12, 23, 34};
  std::vector<uint32_t> blockIntervals_ms2 = {12, 12, 23, 34};
  DeserializedDifferentialTimestamps differentialTimestamps1;
  DeserializedDifferentialTimestamps differentialTimestamps2;
  differentialTimestamps1.setFirstTimestamp(firstTimestamp_ms1);
  differentialTimestamps1.setBlockIntervals(blockIntervals_ms1);
  differentialTimestamps1.setTimestampsIntervals(timestampsIntervals_ms1);
  differentialTimestamps2.setFirstTimestamp(firstTimestamp_ms2);
  differentialTimestamps2.setBlockIntervals(blockIntervals_ms2);
  differentialTimestamps2.setTimestampsIntervals(timestampsIntervals_ms2);
  EXPECT_FALSE(differentialTimestamps1.isEqual(differentialTimestamps2));
}

TEST(runUnitTests, CompareDifferentBlockintervals) {
  uint64_t firstTimestamp_ms1 = 1690921;
  uint64_t firstTimestamp_ms2 = 1690921;
  std::vector<uint32_t> timestampsIntervals_ms1 = {134, 31, 124};
  std::vector<uint32_t> timestampsIntervals_ms2 = {134, 31, 124};
  std::vector<uint32_t> blockIntervals_ms1 = {12, 12, 23, 34};
  std::vector<uint32_t> blockIntervals_ms2 = {12, 45, 23, 98};
  DeserializedDifferentialTimestamps differentialTimestamps1;
  DeserializedDifferentialTimestamps differentialTimestamps2;
  differentialTimestamps1.setFirstTimestamp(firstTimestamp_ms1);
  differentialTimestamps1.setBlockIntervals(blockIntervals_ms1);
  differentialTimestamps1.setTimestampsIntervals(timestampsIntervals_ms1);
  differentialTimestamps2.setFirstTimestamp(firstTimestamp_ms2);
  differentialTimestamps2.setBlockIntervals(blockIntervals_ms2);
  differentialTimestamps2.setTimestampsIntervals(timestampsIntervals_ms2);
  EXPECT_FALSE(differentialTimestamps1.isEqual(differentialTimestamps2));
}

TEST(runUnitTests, CompareDifferentTimestampsIntervals) {
  uint64_t firstTimestamp_ms1 = 1690921;
  uint64_t firstTimestamp_ms2 = 1690921;
  std::vector<uint32_t> timestampsIntervals_ms1 = {134, 31, 124};
  std::vector<uint32_t> timestampsIntervals_ms2 = {55, 123, 187};
  std::vector<uint32_t> blockIntervals_ms1 = {12, 12, 23, 34};
  std::vector<uint32_t> blockIntervals_ms2 = {12, 12, 23, 34};
  DeserializedDifferentialTimestamps differentialTimestamps1;
  DeserializedDifferentialTimestamps differentialTimestamps2;
  differentialTimestamps1.setFirstTimestamp(firstTimestamp_ms1);
  differentialTimestamps1.setBlockIntervals(blockIntervals_ms1);
  differentialTimestamps1.setTimestampsIntervals(timestampsIntervals_ms1);
  differentialTimestamps2.setFirstTimestamp(firstTimestamp_ms2);
  differentialTimestamps2.setBlockIntervals(blockIntervals_ms2);
  differentialTimestamps2.setTimestampsIntervals(timestampsIntervals_ms2);
  EXPECT_FALSE(differentialTimestamps1.isEqual(differentialTimestamps2));
}

TEST(runUnitTests, TestSerializeandDeserializeEqualTimestamps) {
  uint64_t firstTimestamp_ms1 = 1690921;
  std::vector<uint32_t> timestampsIntervals_ms1 = {134, 31, 124};
  std::vector<uint32_t> blockIntervals_ms1 = {12, 113, 23, 34};
  DeserializedDifferentialTimestamps differentialTimestamps1;
  differentialTimestamps1.setFirstTimestamp(firstTimestamp_ms1);
  differentialTimestamps1.setBlockIntervals(blockIntervals_ms1);
  differentialTimestamps1.setTimestampsIntervals(timestampsIntervals_ms1);
  SerializedTimestampContainer serializedTimestampContainer = differentialTimestamps1.serialize();
  DeserializedDifferentialTimestamps differentialTimestamps2;
  differentialTimestamps2.deserialize(serializedTimestampContainer);
  EXPECT_TRUE(differentialTimestamps1.isEqual(differentialTimestamps2));
}

TEST(runUnitTests, TestSerializeandDeserializeBetweenTwoTimestamps) {
  uint64_t firstTimestamp_ms1 = 1690921;
  std::vector<uint32_t> timestampsIntervals_ms1 = {134, 31, 124};
  std::vector<uint32_t> blockIntervals_ms1 = {12, 12, 23, 34};
  DeserializedDifferentialTimestamps differentialTimestamps1;
  differentialTimestamps1.setFirstTimestamp(firstTimestamp_ms1);
  differentialTimestamps1.setBlockIntervals(blockIntervals_ms1);
  differentialTimestamps1.setTimestampsIntervals(timestampsIntervals_ms1);
  SerializedTimestampContainer serializedTimestampContainer1 = differentialTimestamps1.serialize();
  DeserializedDifferentialTimestamps differentialTimestamps2;
  differentialTimestamps2.deserialize(serializedTimestampContainer1);
  uint64_t firstTimestamp_ms2 = 1690921;
  std::vector<uint32_t> timestampsIntervals_ms2 = {134, 31, 124};
  std::vector<uint32_t> blockIntervals_ms2 = {12, 12, 23, 34};
  DeserializedDifferentialTimestamps differentialTimestamps3;
  differentialTimestamps3.setFirstTimestamp(firstTimestamp_ms2);
  differentialTimestamps3.setBlockIntervals(blockIntervals_ms2);
  differentialTimestamps3.setTimestampsIntervals(timestampsIntervals_ms2);
  SerializedTimestampContainer serializedTimestampContainer2 = differentialTimestamps3.serialize();
  DeserializedDifferentialTimestamps differentialTimestamps4;
  differentialTimestamps4.deserialize(serializedTimestampContainer2);
  EXPECT_TRUE(differentialTimestamps2.isEqual(differentialTimestamps4));
}

TEST(runUnitTests, TestSerializeandDeserializeTwoDifferentTimestamps) {
  uint64_t firstTimestamp_ms1 = 12;
  std::vector<uint32_t> timestampsIntervals_ms1 = {134, 31, 124};
  std::vector<uint32_t> blockIntervals_ms1 = {12, 12, 23, 34};
  DeserializedDifferentialTimestamps differentialTimestamps1;
  differentialTimestamps1.setFirstTimestamp(firstTimestamp_ms1);
  differentialTimestamps1.setBlockIntervals(blockIntervals_ms1);
  differentialTimestamps1.setTimestampsIntervals(timestampsIntervals_ms1);
  SerializedTimestampContainer serializedTimestampContainer1 = differentialTimestamps1.serialize();
  DeserializedDifferentialTimestamps differentialTimestamps2;
  differentialTimestamps2.deserialize(serializedTimestampContainer1);
  uint64_t firstTimestamp_ms2 = 1690921;
  std::vector<uint32_t> timestampsIntervals_ms2 = {134, 31, 124};
  std::vector<uint32_t> blockIntervals_ms2 = {12, 12, 23, 34};
  DeserializedDifferentialTimestamps differentialTimestamps3;
  differentialTimestamps3.setFirstTimestamp(firstTimestamp_ms2);
  differentialTimestamps3.setBlockIntervals(blockIntervals_ms2);
  differentialTimestamps3.setTimestampsIntervals(timestampsIntervals_ms2);
  SerializedTimestampContainer serializedTimestampContainer2 = differentialTimestamps3.serialize();
  DeserializedDifferentialTimestamps differentialTimestamps4;
  differentialTimestamps4.deserialize(serializedTimestampContainer2);
  EXPECT_FALSE(differentialTimestamps2.isEqual(differentialTimestamps4));
}

TEST(runUnitTests, TestCalculateFirstTimestampInBlock) {
  uint64_t firstTimestamp_ms1 = 10;
  std::vector<uint32_t> blockIntervals_ms1 = {0, 113, 23, 34};  // first block_intervall[0] is always null - one loop less is needed
  uint32_t blockIdx = 2;
  DeserializedDifferentialTimestamps differentialTimestamps1;
  differentialTimestamps1.setFirstTimestamp(firstTimestamp_ms1);
  differentialTimestamps1.setBlockIntervals(blockIntervals_ms1);
  uint32_t firstTimestampInBlock_ms = differentialTimestamps1.calculateFirstTimestampInBlock(blockIdx);
  EXPECT_EQ(firstTimestampInBlock_ms, 146);
}

TEST(runUnitTests, TestCalculateLastTimestampInBlock) {
  uint64_t firstTimestamp_ms1 = 10;
  uint32_t blockIdx = 2;
  std::vector<uint32_t> timestampsIntervals_ms = {134, 31, 124};
  std::vector<uint32_t> blockIntervals_ms1 = {0, 113, 23, 34};  // first block_intervall[0] is always null - one loop less is needed
  DeserializedDifferentialTimestamps differentialTimestamps1;
  differentialTimestamps1.setFirstTimestamp(firstTimestamp_ms1);
  differentialTimestamps1.setBlockIntervals(blockIntervals_ms1);
  differentialTimestamps1.setTimestampsIntervals(timestampsIntervals_ms);
  uint32_t firstTimestampInBlock_ms = 146;
  std::vector<int32_t> diffValues = {30, 32, 54};
  DeserializedDifferentialBlock deserializedDifferentialBlock;
  deserializedDifferentialBlock.setDiffValues(diffValues);

  uint32_t lastTimestampInBlock_ms =
      differentialTimestamps1.calculateLastTimestampInBlock(blockIdx, firstTimestampInBlock_ms, deserializedDifferentialBlock);
  EXPECT_EQ(lastTimestampInBlock_ms, 518);
}

TEST(runUnitTests, TestCalculateLastTimestampInBlock0) {
  uint32_t blockIdx = 0;
  uint32_t firstTimestampInBlock_ms = 150;
  std::vector<uint32_t> timestampsIntervals_ms = {134, 31, 124};
  std::vector<int32_t> diffValues = {30, 32, 54};
  DeserializedDifferentialTimestamps differentialTimestamps1;
  differentialTimestamps1.setTimestampsIntervals(timestampsIntervals_ms);
  DeserializedDifferentialBlock deserializedDifferentialBlock;
  deserializedDifferentialBlock.setDiffValues(diffValues);
  uint32_t lastTimestampInBlock_ms =
      differentialTimestamps1.calculateLastTimestampInBlock(blockIdx, firstTimestampInBlock_ms, deserializedDifferentialBlock);
  EXPECT_EQ(lastTimestampInBlock_ms, 552);
}

TEST(runUnitTests, TestCalculateLastTimestampInBlockException) {
  try {
    uint64_t firstTimestamp_ms1 = 10;
    uint32_t blockIdx = 7;
    std::vector<uint32_t> timestampsIntervals_ms = {134, 31, 124};
    std::vector<uint32_t> blockIntervals_ms1 = {0, 113, 23, 34};  // first block_intervall[0] is always null - one loop
                                                                  // less is needed
    DeserializedDifferentialTimestamps differentialTimestamps1;
    differentialTimestamps1.setFirstTimestamp(firstTimestamp_ms1);
    differentialTimestamps1.setBlockIntervals(blockIntervals_ms1);
    differentialTimestamps1.setTimestampsIntervals(timestampsIntervals_ms);
    uint32_t firstTimestampInBlock_ms = differentialTimestamps1.calculateFirstTimestampInBlock(2);  // firstTimestampInBlock_ms = 146
    std::vector<int32_t> diffValues = {30, 32, 54};
    DeserializedDifferentialBlock deserializedDifferentialBlock;
    deserializedDifferentialBlock.setDiffValues(diffValues);
    uint32_t lastTimestampInBlock_ms =
        differentialTimestamps1.calculateLastTimestampInBlock(blockIdx, firstTimestampInBlock_ms, deserializedDifferentialBlock);
  } catch (const std::invalid_argument& e) {
    EXPECT_EQ(e.what(), "blockIdx is higher than number of blockIntervals_ms");
    FAIL() << "Expected std::invalid_argument";
  } catch (std::invalid_argument const& e) {
    EXPECT_EQ(e.what(), std::string("blockIdx is higher than number of blockIntervals_ms"));
  } catch (...) {
    FAIL() << "Expected std::invalid_argument";
  }
}
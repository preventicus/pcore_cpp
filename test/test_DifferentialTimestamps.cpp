#include <gtest/gtest.h>
#include "DifferentialTimestamps.h"

class DifferentialTimestampsTest : public ::testing::Test {
 protected:
  DifferentialTimestamps differentialTimestampsWithNormalTimestamps1;
  DifferentialTimestamps differentialTimestampsWithNormalTimestamps2;
  DifferentialTimestamps differentialTimestampsWith0Timestamps1;
  DifferentialTimestamps differentialTimestampsWith0Timestamps2;
  DifferentialTimestamps differentialTimestampsEmptyTimestamps1;
  DifferentialTimestamps differentialTimestampsEmptyTimestamps2;
  uint64_t normalFirstTimestamp_ms = 10;
  uint64_t zeroFirstTimestamp_ms = 0;
  std::vector<uint32_t> normalBlockIntervals_ms = {0, 113, 23, 34};  // first block_intervall[0] is always null - one loop less is needed
  std::vector<uint32_t> zeroBlockIntervals_ms = {0};                 // first block_intervall[0] is always null - one loop less is needed
  std::vector<uint32_t> emptyBlockIntervals_ms = {};
  std::vector<uint32_t> normalTimestampsIntervals_ms = {134, 31, 124};
  std::vector<uint32_t> zeroTimestampsIntervals_ms = {0};
  std::vector<uint32_t> emptyTimestampsIntervals_ms = {};

  virtual void SetUp() {
    this->differentialTimestampsWithNormalTimestamps1 =
        DifferentialTimestamps(this->normalFirstTimestamp_ms, this->normalBlockIntervals_ms, this->normalTimestampsIntervals_ms);
    this->differentialTimestampsWithNormalTimestamps2 =
        DifferentialTimestamps(this->normalFirstTimestamp_ms, this->normalBlockIntervals_ms, this->normalTimestampsIntervals_ms);
    this->differentialTimestampsWith0Timestamps1 =
        DifferentialTimestamps(this->zeroFirstTimestamp_ms, this->zeroBlockIntervals_ms, this->zeroTimestampsIntervals_ms);
    this->differentialTimestampsWith0Timestamps2 =
        DifferentialTimestamps(this->zeroFirstTimestamp_ms, this->zeroBlockIntervals_ms, this->zeroTimestampsIntervals_ms);
    this->differentialTimestampsEmptyTimestamps1 =
        DifferentialTimestamps(this->zeroFirstTimestamp_ms, this->emptyBlockIntervals_ms, this->emptyTimestampsIntervals_ms);
    this->differentialTimestampsEmptyTimestamps2 =
        DifferentialTimestamps(this->zeroFirstTimestamp_ms, this->emptyBlockIntervals_ms, this->emptyTimestampsIntervals_ms);
  }
};

TEST_F(DifferentialTimestampsTest, TestGetAndSetMethodeTimestampsContainer) {
  EXPECT_EQ(this->differentialTimestampsWithNormalTimestamps1.getFirstTimestamp(), this->normalFirstTimestamp_ms);
  EXPECT_EQ(this->differentialTimestampsWithNormalTimestamps1.getBlockIntervals(), this->normalBlockIntervals_ms);
  EXPECT_EQ(this->differentialTimestampsWithNormalTimestamps1.getTimestampsIntervals(), this->normalTimestampsIntervals_ms);
}

TEST_F(DifferentialTimestampsTest, TestGetAndSetTimestampsContainerFirstTimestamp0) {
  EXPECT_EQ(this->differentialTimestampsWith0Timestamps1.getFirstTimestamp(), this->zeroFirstTimestamp_ms);
  EXPECT_EQ(this->differentialTimestampsWith0Timestamps1.getBlockIntervals(), this->zeroBlockIntervals_ms);
  EXPECT_EQ(this->differentialTimestampsWith0Timestamps1.getTimestampsIntervals(), this->zeroTimestampsIntervals_ms);
}

TEST_F(DifferentialTimestampsTest, TestGetAndSetEmptyTimestampsContainer) {
  EXPECT_EQ(this->differentialTimestampsEmptyTimestamps1.getFirstTimestamp(), this->zeroFirstTimestamp_ms);
  EXPECT_EQ(this->differentialTimestampsEmptyTimestamps1.getBlockIntervals(), this->emptyBlockIntervals_ms);
  EXPECT_EQ(this->differentialTimestampsEmptyTimestamps1.getTimestampsIntervals(), this->emptyTimestampsIntervals_ms);
}

TEST_F(DifferentialTimestampsTest, CompareEqualTimestamps) {
  EXPECT_TRUE(this->differentialTimestampsWithNormalTimestamps1.isEqual(this->differentialTimestampsWithNormalTimestamps2));
}

TEST_F(DifferentialTimestampsTest, CompareEqualZeroTimestamps) {
  EXPECT_TRUE(this->differentialTimestampsWith0Timestamps1.isEqual(this->differentialTimestampsWith0Timestamps2));
}

TEST_F(DifferentialTimestampsTest, CompareEqualEmptyTimestamps) {
  EXPECT_TRUE(this->differentialTimestampsEmptyTimestamps1.isEqual(this->differentialTimestampsEmptyTimestamps2));
}

TEST_F(DifferentialTimestampsTest, CompareDifferentTimestampsIntervals) {
  EXPECT_FALSE(this->differentialTimestampsWithNormalTimestamps1.isEqual(this->differentialTimestampsWith0Timestamps1));
}

TEST_F(DifferentialTimestampsTest, TestSerializeandDeserializeEqualTimestamps) {
  ProtobufTimestampContainer protobufTimestampContainer = this->differentialTimestampsWithNormalTimestamps1.serialize();
  DifferentialTimestamps differentialTimestamps = DifferentialTimestamps(protobufTimestampContainer);
  EXPECT_TRUE(this->differentialTimestampsWithNormalTimestamps1.isEqual(differentialTimestamps));
}

TEST_F(DifferentialTimestampsTest, TestSerializeandDeserializeBetweenTwoDifferentTimestamps) {
  ProtobufTimestampContainer protobufTimestampContainer1 = this->differentialTimestampsWithNormalTimestamps1.serialize();
  ProtobufTimestampContainer protobufTimestampContainer2 = this->differentialTimestampsWith0Timestamps1.serialize();
  DifferentialTimestamps baseDifferentialTimestamps = DifferentialTimestamps(protobufTimestampContainer1);
  DifferentialTimestamps comparableDifferentialTimestamps = DifferentialTimestamps(protobufTimestampContainer2);
  EXPECT_FALSE(baseDifferentialTimestamps.isEqual(comparableDifferentialTimestamps));
}

TEST_F(DifferentialTimestampsTest, TestSerializeandDeserializeBetweenTwoTimestamps) {
  ProtobufTimestampContainer protobufTimestampContainer1 = this->differentialTimestampsWithNormalTimestamps1.serialize();
  ProtobufTimestampContainer protobufTimestampContainer2 = this->differentialTimestampsWithNormalTimestamps2.serialize();
  DifferentialTimestamps baseDifferentialTimestamps = DifferentialTimestamps(protobufTimestampContainer1);
  DifferentialTimestamps comparableDifferentialTimestamps = DifferentialTimestamps(protobufTimestampContainer2);
  EXPECT_TRUE(baseDifferentialTimestamps.isEqual(comparableDifferentialTimestamps));
}

TEST_F(DifferentialTimestampsTest, TestSerializeandDeserializeBetweenTwoZeroTimestamps) {
  ProtobufTimestampContainer protobufTimestampContainer1 = this->differentialTimestampsWith0Timestamps1.serialize();
  ProtobufTimestampContainer protobufTimestampContainer2 = this->differentialTimestampsWith0Timestamps2.serialize();
  DifferentialTimestamps baseDifferentialTimestamps = DifferentialTimestamps(protobufTimestampContainer1);
  DifferentialTimestamps comparableDifferentialTimestamps = DifferentialTimestamps(protobufTimestampContainer2);
  EXPECT_TRUE(baseDifferentialTimestamps.isEqual(comparableDifferentialTimestamps));
}

TEST_F(DifferentialTimestampsTest, TestSerializeandDeserializeBetweenTwoEmptyTimestamps) {
  ProtobufTimestampContainer protobufTimestampContainer1 = this->differentialTimestampsEmptyTimestamps1.serialize();
  ProtobufTimestampContainer protobufTimestampContainer2 = this->differentialTimestampsEmptyTimestamps2.serialize();
  DifferentialTimestamps baseDifferentialTimestamps = DifferentialTimestamps(protobufTimestampContainer1);
  DifferentialTimestamps comparableDifferentialTimestamps = DifferentialTimestamps(protobufTimestampContainer2);
  EXPECT_TRUE(baseDifferentialTimestamps.isEqual(comparableDifferentialTimestamps));
}

TEST_F(DifferentialTimestampsTest, TestCalculateFirstTimestampInBlock) {
  uint32_t blockIdx = 2;
  EXPECT_EQ(this->differentialTimestampsWithNormalTimestamps1.calculateFirstTimestampInBlock(blockIdx), 146);
}

TEST_F(DifferentialTimestampsTest, TestCalculateLastTimestampInBlock) {
  uint32_t blockIdx = 2;
  uint32_t firstTimestampInBlock = 146;  // reference to the UnitTest before
  std::vector<int32_t> diffValues = {30, 32, 54};
  DifferentialBlock differentialBlock = DifferentialBlock(diffValues);
  EXPECT_EQ(this->differentialTimestampsWithNormalTimestamps1.calculateLastTimestampInBlock(blockIdx, firstTimestampInBlock, differentialBlock), 518);
}

TEST_F(DifferentialTimestampsTest, TestCalculateLastTimestampInBlock0) {
  uint32_t blockIdx = 0;
  uint32_t firstTimestampInBlock = 150;
  std::vector<int32_t> diffValues = {30, 32, 54};
  DifferentialBlock differentialBlock = DifferentialBlock(diffValues);
  EXPECT_EQ(this->differentialTimestampsWithNormalTimestamps1.calculateLastTimestampInBlock(blockIdx, firstTimestampInBlock, differentialBlock), 552);
}

TEST_F(DifferentialTimestampsTest, TestCalculateLastTimestampInBlockException) {
  uint32_t blockIdx = 10;
  std::vector<int32_t> diffValues = {30, 32, 54};
  DifferentialBlock differentialBlock = DifferentialBlock(diffValues);
  EXPECT_THROW(this->differentialTimestampsWithNormalTimestamps1.calculateFirstTimestampInBlock(blockIdx), std::invalid_argument);
}

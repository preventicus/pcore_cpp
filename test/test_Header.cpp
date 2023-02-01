#include <gtest/gtest.h>
#include "Header.h"
class HeaderTest : public ::testing::Test {
 protected:
  Header normalHeaderWitchPositiveTimeZoneOffset_min1;
  Header normalHeaderWitchPositiveTimeZoneOffset_min2;
  Header normalHeaderWitchNegativeTimeZoneOffset_min1;
  Header normalHeaderWitchNegativeTimeZoneOffset_min2;
  Header normalHeaderWitchNoTimeZoneOffset_min1;
  Header normalHeaderWitchNoTimeZoneOffset_min2;
  Header invalidHeaderWitchPositiveTimeZoneOffset_min;
  Header invalidHeaderWitchNegativeTimeZoneOffset_min;
  Header headerWitchMaxTimeZoneOffset_min1;
  Header headerWitchMaxTimeZoneOffset_min2;
  Header headerWitchMinTimeZoneOffset_min1;
  Header headerWitchMinTimeZoneOffset_min2;
  uint32_t majorOne = 1;
  uint32_t minorTwo = 2;
  uint32_t patchZero = 0;
  Version version = Version(majorOne, minorTwo, patchZero);
  int32_t positiveTimeZoneOffset_min = 120;
  int32_t negativeTimeZoneOffset_min = -120;
  int32_t noTimeZoneOffset_min = 0;
  int32_t maxTimeZoneOffset_min = 840;
  int32_t minTimeZoneOffset_min = -720;
  virtual void SetUp() {
    this->normalHeaderWitchPositiveTimeZoneOffset_min1 = Header(this->version, this->positiveTimeZoneOffset_min);
    this->normalHeaderWitchPositiveTimeZoneOffset_min2 = Header(this->version, this->positiveTimeZoneOffset_min);
    this->normalHeaderWitchNegativeTimeZoneOffset_min1 = Header(this->version, this->negativeTimeZoneOffset_min);
    this->normalHeaderWitchNegativeTimeZoneOffset_min2 = Header(this->version, this->negativeTimeZoneOffset_min);
    this->normalHeaderWitchNoTimeZoneOffset_min1 = Header(this->version, this->noTimeZoneOffset_min);
    this->normalHeaderWitchNoTimeZoneOffset_min2 = Header(this->version, this->noTimeZoneOffset_min);
    this->headerWitchMaxTimeZoneOffset_min1 = Header(this->version, this->maxTimeZoneOffset_min);
    this->headerWitchMaxTimeZoneOffset_min2 = Header(this->version, this->maxTimeZoneOffset_min);
    this->headerWitchMinTimeZoneOffset_min1 = Header(this->version, this->minTimeZoneOffset_min);
    this->headerWitchMinTimeZoneOffset_min2 = Header(this->version, this->minTimeZoneOffset_min);
  }
};

TEST_F(HeaderTest, GetSetMethodeWithPositiveOffSetValue) {
  EXPECT_EQ(this->normalHeaderWitchPositiveTimeZoneOffset_min1.getTimeZoneOffset(), this->positiveTimeZoneOffset_min);
}

TEST_F(HeaderTest, GetSetMethodeWithNegativeOffSetValue) {
  EXPECT_EQ(this->normalHeaderWitchNegativeTimeZoneOffset_min1.getTimeZoneOffset(), this->negativeTimeZoneOffset_min);
}

TEST_F(HeaderTest, CompareSameTimeZoneOffset) {
  EXPECT_TRUE(this->normalHeaderWitchPositiveTimeZoneOffset_min1.isEqual(this->normalHeaderWitchPositiveTimeZoneOffset_min2));
}

TEST_F(HeaderTest, CompareSameNegativeTimeZoneOffset) {
  EXPECT_TRUE(this->normalHeaderWitchNegativeTimeZoneOffset_min1.isEqual(this->normalHeaderWitchNegativeTimeZoneOffset_min2));
}

TEST_F(HeaderTest, CompareDifferentTimeZoneOffset) {
  EXPECT_FALSE(this->normalHeaderWitchNegativeTimeZoneOffset_min1.isEqual(this->normalHeaderWitchPositiveTimeZoneOffset_min1));
}

TEST_F(HeaderTest, CompareTimeZoneOffsetWith0) {
  EXPECT_FALSE(this->normalHeaderWitchNoTimeZoneOffset_min1.isEqual(this->normalHeaderWitchPositiveTimeZoneOffset_min1));
}

TEST_F(HeaderTest, CompareSameTimeZoneOffsetWith0) {
  EXPECT_TRUE(this->normalHeaderWitchNoTimeZoneOffset_min1.isEqual(this->normalHeaderWitchNoTimeZoneOffset_min2));
}

TEST_F(HeaderTest, CompareSameTimeZoneOffsetWithMaxOffSet) {
  EXPECT_TRUE(this->headerWitchMaxTimeZoneOffset_min1.isEqual(this->headerWitchMaxTimeZoneOffset_min2));
}

TEST_F(HeaderTest, CompareSameTimeZoneOffsetWithMinOffSet) {
  EXPECT_TRUE(this->headerWitchMinTimeZoneOffset_min1.isEqual(this->headerWitchMinTimeZoneOffset_min2));
}

TEST_F(HeaderTest, SerializeAndDeserialize) {
  ProtobufHeader protobufHeader = this->normalHeaderWitchPositiveTimeZoneOffset_min1.serialize();
  Header header2 = Header(protobufHeader);
  EXPECT_TRUE(this->normalHeaderWitchPositiveTimeZoneOffset_min1.isEqual(header2));
}

TEST_F(HeaderTest, SerializeAndDeserializeWith0) {
  ProtobufHeader protobufHeader = this->normalHeaderWitchNoTimeZoneOffset_min1.serialize();
  Header header2 = Header(protobufHeader);
  EXPECT_TRUE(this->normalHeaderWitchNoTimeZoneOffset_min1.isEqual(header2));
}

TEST_F(HeaderTest, SerializeAndDeserializeWithNegativeValue) {
  ProtobufHeader protobufHeader = this->headerWitchMinTimeZoneOffset_min1.serialize();
  Header header2 = Header(protobufHeader);
  EXPECT_TRUE(this->headerWitchMinTimeZoneOffset_min1.isEqual(header2));
}

TEST_F(HeaderTest, TestExecptionPositiveOutOfRange) {
  int32_t invalidPositiveTimeZoneOffset_min = 1000;
  EXPECT_THROW(Header invalidHeaderWitchPositiveTimeZoneOffset_min = Header(this->version, invalidPositiveTimeZoneOffset_min), std::out_of_range);
}

TEST_F(HeaderTest, TestExecptionNegativeOutOfRange) {
  int32_t invalidNegativeTimeZoneOffset_min = -1000;
  EXPECT_THROW(Header invalidHeaderWitchNegativeTimeZoneOffset_min = Header(this->version, invalidNegativeTimeZoneOffset_min), std::out_of_range);
}

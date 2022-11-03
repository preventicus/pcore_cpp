#include <gtest/gtest.h>

#include <../src/pcore_extern.cpp>

TEST(PcoreTest, HasVersionStructTheRightValues) {
  Pcore_Version version = coreLibraryVersion();
  EXPECT_EQ(PCORE_VERSION_MAJOR, version.major);
  EXPECT_EQ(PCORE_VERSION_MINOR, version.minor);
  EXPECT_EQ(PCORE_VERSION_PATCH, version.patch);
}

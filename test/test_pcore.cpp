#include <gtest/gtest.h>

#include <pcore_extern.h>

TEST(PcoreTest, HasVersionStructTheRightValues) {
  Pcore_Version version = coreLibraryVersion();
  EXPECT_EQ(PCORE_VERSION_MAJOR, version.major);
  EXPECT_EQ(PCORE_VERSION_MINOR, version.minor);
  EXPECT_EQ(PCORE_VERSION_PATCH, version.patch);
}

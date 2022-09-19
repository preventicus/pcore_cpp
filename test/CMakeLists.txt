FILE(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/test/*.cpp)

ADD_EXECUTABLE(runUnitTests ${TEST_SRC_FILES})

TARGET_LINK_LIBRARIES(runUnitTests gtest gtest_main)
TARGET_LINK_LIBRARIES(runUnitTests libpcore_extern)

ADD_TEST(UnitTests runUnitTests)

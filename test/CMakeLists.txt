SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test/lib)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test/lib)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test/bin)
SET(BINARY ${CMAKE_PROJECT_NAME}_test)
INCLUDE(FetchContent)
FetchContent_Declare(   
    googletest
    GIT_REPOSITORY URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)
INCLUDE_DIRECTORIES(${gtest__INCLUDE_DIRS})
FILE(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/test/*.cpp)
ADD_EXECUTABLE(
    runUnitTests
    ${TEST_SRC_FILES}
)
INCLUDE(GoogleTest)

TARGET_LINK_LIBRARIES(runUnitTests gtest gtest_main)
TARGET_LINK_LIBRARIES(runUnitTests libpcore_extern)

gtest_DISCOVER_TESTS(runUnitTests)
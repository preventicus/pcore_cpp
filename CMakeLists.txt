# Minimum required version
CMAKE_MINIMUM_REQUIRED(VERSION 3.12)

# TODO with first release: Receive the current version from git
#EXECUTE_PROCESS(COMMAND git describe --tags
#    OUTPUT_VARIABLE GIT_TAG_VERSION
#    OUTPUT_STRIP_TRAILING_WHITESPACE
# )
#STRING(REGEX REPLACE "v([0-9]+)\\.([0-9]+)\\.([0-9]+).*" "\\1" PCORE_MAJOR_VERSION_GIT ${GIT_TAG_VERSION})
#STRING(REGEX REPLACE "v([0-9]+)\\.([0-9]+)\\.([0-9]+).*" "\\2" PCORE_MINOR_VERSION_GIT ${GIT_TAG_VERSION})
#STRING(REGEX REPLACE "v([0-9]+)\\.([0-9]+)\\.([0-9]+).*" "\\3" PCORE_PATCH_VERSION_GIT ${GIT_TAG_VERSION})
# Write default version numbers. Values can be overwritten on command line.
#SET(PCORE_MAJOR_VERSION "${PCORE_MAJOR_VERSION_GIT}" CACHE STRING "pcore major version")
#SET(PCORE_MINOR_VERSION "${PCORE_MINOR_VERSION_GIT}" CACHE STRING "pcore minor version")
#SET(PCORE_PATCH_VERSION "${PCORE_PATCH_VERSION_GIT}" CACHE STRING "pcore patch version")
#SET(PCORE_PRE_RELEASE_VERSION "" CACHE STRING "pcore pre-release version")

SET(PCORE_MAJOR_VERSION "0" CACHE STRING "pcore major version")
SET(PCORE_MINOR_VERSION "0" CACHE STRING "pcore minor version")
SET(PCORE_PATCH_VERSION "1" CACHE STRING "pcore patch version")
STRING(CONCAT PCORE_VERSION "${PCORE_MAJOR_VERSION}.${PCORE_MINOR_VERSION}.${PCORE_PATCH_VERSION}")

# Set project title
PROJECT(pcore_cpp VERSION "${PCORE_VERSION}")
CONFIGURE_FILE(configure/pcoreConfig.h.in include/pcoreConfig.h)

SET(CMAKE_CXX_FLAGS "-g -Wall")
SET(CMAKE_CXX_STANDARD 17)

set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES(${COMMON_INCLUDES})
# Need the protobuf lib
# TODO: Build Protobuf lib
# TODO: Build Protobuf compiler

# TODO: generate cpp code (./generated/*) with Protobuf compiler

# Add source directory
ADD_SUBDIRECTORY(src)

# Do some unit testing

ADD_SUBDIRECTORY(./external/googletest)
enable_testing()
INCLUDE_DIRECTORIES(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

ADD_SUBDIRECTORY(test)


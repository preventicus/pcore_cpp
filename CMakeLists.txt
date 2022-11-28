# Minimum required version
CMAKE_MINIMUM_REQUIRED(VERSION 3.24.2)

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

SET(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES(${COMMON_INCLUDES})

INCLUDE(FetchContent)

FetchContent_Declare(
        jsoncpp
        GIT_REPOSITORY https://github.com/open-source-parsers/jsoncpp.git
        GIT_TAG        1.9.5
)
FetchContent_MakeAvailable(jsoncpp)

#Build Protobuf
SET(PROTOBUF_ROOT ${PROJECT_BINARY_DIR}/google/protobuf)
execute_process(
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/scripts/
    COMMAND ./INSTALL_PROTOBUF.sh ${PROJECT_SOURCE_DIR}/external/google-protobuf ${PROTOBUF_ROOT})

#Include Protobuf
list(APPEND CMAKE_PREFIX_PATH ${PROTOBUF_ROOT})
include(${PROTOBUF_ROOT}/lib/cmake/protobuf/protobuf-config.cmake)
include(${PROTOBUF_ROOT}/lib/cmake/protobuf/protobuf-module.cmake)
include(${PROTOBUF_ROOT}/lib/cmake/protobuf/protobuf-options.cmake)
include(${PROTOBUF_ROOT}/lib/cmake/protobuf/protobuf-targets.cmake)

FIND_PACKAGE( Protobuf REQUIRED PATHS ${PROTOBUF_ROOT}/bin/lib/cmake/protobuf )
if ( Protobuf_FOUND )
    message( STATUS "Protobuf version : ${Protobuf_VERSION}" )
    message( STATUS "Protobuf include path : ${Protobuf_INCLUDE_DIRS}" )
    message( STATUS "Protobuf libraries : ${Protobuf_LIBRARIES}" )
    message( STATUS "Protobuf compiler libraries : ${Protobuf_PROTOC_LIBRARIES}")
    message( STATUS "Protobuf lite libraries : ${Protobuf_LITE_LIBRARIES}")
else()
    message( WARNING "Protobuf package not found -> specify search path via PROTOBUF_ROOT variable")
endif()

SET (PCORE_LOCATION ${PROJECT_SOURCE_DIR}/build/pcore-prefix/src)
# INCLUDE(ExternalProject)
# ExternalProject_Add(
#     Pcore proto definition files
#     GIT_REPOSITORY git@gitlab.preventicus.com:research/pcore-proto-definition-files.git
#     GIT_TAG 1.0.0
#     CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${PCORE_LOCATION}
# )
# INCLUDE_DIRECTORIES(${PCORE_LOCATION}/include)
# LINK_DIRECTORIES(${PCORE_LOCATION}/lib)

SET(PROTO_ROOT ${PROJECT_SOURCE_DIR}/build/Pcore-prefix/src/Pcore)
EXECUTE_PROCESS(
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/scripts/
    COMMAND ./GENERATE_PROTO_DATA.sh ${PROJECT_SOURCE_DIR})
LIST(APPEND CMAKE_PREFIX_PATH ${PROTO_ROOT})

# TODO: Build Protobuf lib
# TODO: Build Protobuf compiler
# TODO: generate cpp code (./generated/*) with Protobuf compiler
# Add source directory
# Add source directory
ADD_SUBDIRECTORY(src)
INCLUDE_DIRECTORIES(${Jsoncpp_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${Protobuf_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${Pcore_INCLUDE_DIR})
# Do some unit testing

ENABLE_TESTING()
INCLUDE_DIRECTORIES(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

ADD_SUBDIRECTORY(test)

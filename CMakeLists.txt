# Minimum required version
CMAKE_MINIMUM_REQUIRED(VERSION 3.12.0)

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
LIST(APPEND COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/build/google/protobuf/include)

INCLUDE_DIRECTORIES(${COMMON_INCLUDES})

INCLUDE(FetchContent)

FETCHCONTENT_DECLARE(
        jsoncpp
        GIT_REPOSITORY https://github.com/open-source-parsers/jsoncpp.git
        GIT_TAG        1.9.5
)
FETCHCONTENT_MAKEAVAILABLE(jsoncpp)

#Build Protobuf
SET(PROTOBUF_ROOT ${PROJECT_BINARY_DIR}/google/protobuf)
EXECUTE_PROCESS(
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/scripts/
    COMMAND ./INSTALL_PROTOBUF.sh ${PROJECT_SOURCE_DIR}/external/google-protobuf ${PROTOBUF_ROOT})
#Include Protobuf
LIST(APPEND CMAKE_PREFIX_PATH ${PROTOBUF_ROOT})
INCLUDE(${PROTOBUF_ROOT}/lib/cmake/protobuf/protobuf-config.cmake)
INCLUDE(${PROTOBUF_ROOT}/lib/cmake/protobuf/protobuf-module.cmake)
INCLUDE(${PROTOBUF_ROOT}/lib/cmake/protobuf/protobuf-options.cmake)
INCLUDE(${PROTOBUF_ROOT}/lib/cmake/protobuf/protobuf-targets.cmake)

INCLUDE(FindProtobuf)
FIND_PACKAGE( Protobuf REQUIRED PATHS ${PROTOBUF_ROOT}/bin/lib/cmake/protobuf )
if ( Protobuf_FOUND )
    MESSAGE( STATUS "Protobuf version : ${Protobuf_VERSION}" )
    MESSAGE( STATUS "Protobuf include path : ${Protobuf_INCLUDE_DIRS}" )
    MESSAGE( STATUS "Protobuf libraries : ${Protobuf_LIBRARIES}" )
    MESSAGE( STATUS "Protobuf compiler libraries : ${Protobuf_PROTOC_LIBRARIES}")
    MESSAGE( STATUS "Protobuf lite libraries : ${Protobuf_LITE_LIBRARIES}")
else()
    MESSAGE( WARNING "Protobuf package not found -> specify search path via PROTOBUF_ROOT variable")
endif()

INCLUDE(ExternalProject)
EXTERNALPROJECT_ADD(Pcore proto definition files

  GIT_REPOSITORY    git@gitlab.preventicus.com:research/pcore-proto-definition-files.git
  GIT_TAG           main
  SOURCE_DIR        "${CMAKE_BINARY_DIR}/pcore-src"
  BINARY_DIR        "${CMAKE_BINARY_DIR}/pcore-build"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)

FILE(TO_NATIVE_PATH ${CMAKE_CURRENT_BINARY_DIR}/pcore-src/ PROTOMODEL_PATH)
FILE(TO_NATIVE_PATH ${PROJECT_SOURCE_DIR}/include/protobuf PROTOBINDING_PATH)

FILE(GLOB DATAMODEL_PROTOS ${CMAKE_CURRENT_BINARY_DIR}/pcore-src/*.proto)


FOREACH(proto ${DATAMODEL_PROTOS})
   FILE(TO_NATIVE_PATH ${proto} proto_native)
   EXECUTE_PROCESS(COMMAND ${PROTOBUF_PROTOC_EXECUTABLE} --proto_path=${PROTOMODEL_PATH} --cpp_out=${PROTOBINDING_PATH} ${proto_native}
   RESULT_VARIABLE rv)
   IF(${rv})
        MESSAGE("Generation of data model returned ${rv} for proto ${proto_native}")
   ENDIF()
ENDFOREACH(proto)


FILE(GLOB PROTO_SRC ${PROJECT_SOURCE_DIR}/include/protobuf/*.cc)
FILE(GLOB PROTO_H ${PROJECT_SOURCE_DIR}/include/protobuf/*.h)


INCLUDE_DIRECTORIES(${PROJECT_BINARY_DIR})

LIST(APPEND CMAKE_PREFIX_PATH ${PROTO_ROOT})

INCLUDE_DIRECTORIES(${Jsoncpp_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${Protobuf_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${Pcore_INCLUDE_DIR})

# Add source directory

ADD_SUBDIRECTORY(src)

# Do some unit testing

ENABLE_TESTING()


ADD_SUBDIRECTORY(test)

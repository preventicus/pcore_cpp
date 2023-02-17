#[[
Created by Jakob Glück 2023

Copyright © 2023 PREVENTICUS GmbH

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors
   may be used to endorse or promote products derived from this software without
   specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
]]
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test/lib)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test/lib)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test/bin)
SET(BINARY ${CMAKE_PROJECT_NAME}_test)
SET(FACTORIES_INCLUDES ${PROJECT_SOURCE_DIR}/test/exampleFactories/include/)
SET(JSON ${PROJECT_SOURCE_DIR}/test/JsonDataTest/})
INCLUDE_DIRECTORIES(${FACTORIES_INCLUDES})
INCLUDE_DIRECTORIES(${COMMON_INCLUDES})
INCLUDE_DIRECTORIES(${JSON})
INCLUDE(FetchContent)
FETCHCONTENT_DECLARE(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        release-1.12.1
)
FETCHCONTENT_MAKEAVAILABLE(googletest)
INCLUDE_DIRECTORIES(${gtest__INCLUDE_DIRS})

FILE(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/test/*.cpp)
File(GLOB FACTORIES_SRC ${PROJECT_SOURCE_DIR}/test/exampleFactories/src/*.cpp)
File(GLOB FACTORIES_H ${PROJECT_SOURCE_DIR}/test/exampleFactories/include/*.h)
FILE(GLOB JSON_FLIES ${PROJECT_SOURCE_DIR}/test/JsonTestData/*.json)
ADD_LIBRARY(FACTORIES STATIC ${FACTORIES_H} ${FACTORIES_SRC})
TARGET_LINK_LIBRARIES(FACTORIES jsoncpp_lib)

ADD_EXECUTABLE(
    runUnitTest ${TEST_SRC_FILES})

INCLUDE(GoogleTest)
TARGET_LINK_LIBRARIES(runUnitTest  gtest gtest_main)
TARGET_LINK_LIBRARIES(runUnitTest FACTORIES libpcore_extern)
gtest_DISCOVER_TESTS(runUnitTest)

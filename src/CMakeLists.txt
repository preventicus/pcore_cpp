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
FILE(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
MESSAGE( "SRC_ files : ${SRC_FILES}")
FILE(GLOB HEADER_FILES ${PROJECT_SOURCE_DIR}/include/*.h)
MESSAGE("HEADER : ${HEADER_FILES}")
ADD_LIBRARY(libpcore_extern  ${SRC_FILES} ${HEADER_FILES})
SET(PROTOBUF_LIB protobuf_lib)
ADD_LIBRARY(${PROTOBUF_LIB} STATIC ${PROTO_H} ${PROTO_SRC})
TARGET_LINK_LIBRARIES(libpcore_extern jsoncpp_lib)
TARGET_LINK_LIBRARIES(libpcore_extern ${Protobuf_LIBRARIES} ${PROTOBUF_LIB} absl::synchronization absl::hash absl::raw_hash_set absl::str_format_internal absl::status)
MESSAGE("protobuf : ${Protobuf_LIBRARIES}")
#INCLUDE_DIRECTORIES(${Protobuf_INCLUDE_DIRS})
SET(INCLUDE_FOLDER ${PROJECT_SOURCE_DIR}/include/ ;${CMAKE_BINARY_DIR}/include/)
INCLUDE_DIRECTORIES(${COMMON_INCLUDES})
TARGET_INCLUDE_DIRECTORIES(libpcore_extern PUBLIC ${INCLUDE_FOLDER})

SET_TARGET_PROPERTIES(libpcore_extern PROPERTIES
    OUTPUT_NAME pcore_extern
    VERSION ${PCORE_VERSION}
    SOVERSION ${PCORE_MAJOR_VERSION}
    PUBLIC_HEADER "${CMAKE_SOURCE_DIR}/include/pcore_extern.h;${CMAKE_BINARY_DIR}/include/pcoreConfig.h"
)


INSTALL(TARGETS libpcore_extern
    RUNTIME DESTINATION pcore/bin
    LIBRARY DESTINATION pcore/lib
    ARCHIVE DESTINATION pcore/lib
    PUBLIC_HEADER DESTINATION pcore/include
)

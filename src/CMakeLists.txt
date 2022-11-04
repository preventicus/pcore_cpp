FILE(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)

ADD_LIBRARY(libpcore_extern STATIC ${SRC_FILES})

#TODO: include Protobuf
GET_TARGET_PROPERTY (Protobuf_INCLUDE_DIRS protobuf::libprotobuf INTERFACE_INCLUDE_DIRECTORIES)
SET(PROTOBUFSOURCE ${PROJECT_SOURCE_DIR}/external/protobuf/defintions/pcore_external.proto)
# protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS $PROTOBUFSOURCE)
# protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS EXPORT_MACRO DLL_EXPORT $PROTOBUFSOURCE)
# protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS DESCRIPTORS PROTO_DESCS $PROTOBUFSOURCE)
# protobuf_generate_python(PROTO_PY $PROTOBUFSOURCE)
include_directories(${Protobuf_INCLUDE_DIRS})
target_link_libraries(libpcore_extern ${Protobuf_LIBRARIES})
# Include jsoncpp
GET_TARGET_PROPERTY(JSON_INC_PATH jsoncpp_lib INTERFACE_INCLUDE_DIRECTORIES)
INCLUDE_DIRECTORIES(${JSON_INC_PATH})
TARGET_LINK_LIBRARIES(libpcore_extern jsoncpp_lib)

SET(INCLUDE_FOLDER ${PROJECT_SOURCE_DIR}/include/;${CMAKE_BINARY_DIR}/include/)

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

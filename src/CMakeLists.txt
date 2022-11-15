FILE(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)

ADD_LIBRARY(libpcore_extern STATIC ${SRC_FILES})

#TODO: include Protobuf

target_link_libraries(libpcore_extern ${Protobuf_LIBRARIES})
# Include jsoncpp

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

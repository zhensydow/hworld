file( GLOB SRC_SOURCES "*.cpp")

include_directories( . )
include_directories( ${PROJECT_SOURCE_DIR}/soil )

add_definitions( -Wall -Wextra -std=c++11 )
add_executable( hworld ${SRC_SOURCES} )

target_link_libraries( hworld ${OPENGL_LIBRARIES} )
target_link_libraries( hworld ${SFML_LIBRARIES} )
target_link_libraries( hworld soil )

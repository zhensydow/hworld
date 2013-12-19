file( GLOB SRC_SOURCES "*.cpp")

include_directories( . )
include_directories( ${Boost_INCLUDE_DIR} )
include_directories( ${PROJECT_SOURCE_DIR}/soil )
include_directories( ${LUA_INCLUDE_DIRS})

link_directories( ${Boost_LIBRARY_DIRS} )

add_definitions( -Wall -Wextra -std=c++11 -O3 )
add_executable( hworld ${SRC_SOURCES} )

target_link_libraries( hworld ${OPENGL_LIBRARIES} )
target_link_libraries( hworld ${SFML_LIBRARIES} )
target_link_libraries( hworld ${Boost_LIBRARIES})
target_link_libraries( hworld ${LUA_LIBRARIES} )
target_link_libraries( hworld soil )

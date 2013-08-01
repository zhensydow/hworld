include_directories( . )
include_directories( ${PROJECT_SOURCE_DIR}/soil )

add_definitions( -Wall -std=c++11 )
add_executable( hworld main.cpp shader.cpp )

target_link_libraries( hworld ${OPENGL_LIBRARIES} )
target_link_libraries( hworld ${SFML_LIBRARIES} )
target_link_libraries( hworld soil )

include_directories( . )

add_definitions( -Wall -std=c++11 )
add_executable( test_sfml01 test_sfml01.cpp )

target_link_libraries( test_sfml01 ${OPENGL_LIBRARIES} )
target_link_libraries( test_sfml01 ${SFML_LIBRARIES} )

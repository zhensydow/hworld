include_directories( . )
include_directories( ${PROJECT_SOURCE_DIR}/common )

add_definitions( -Wall -Wextra -std=c++11 )

add_executable( test_sfml01 test_sfml01.cpp )

target_link_libraries( test_sfml01 ${OPENGL_LIBRARIES} )
target_link_libraries( test_sfml01 ${SFML_LIBRARIES} )

add_executable( test_simple01 test_simple01.cpp )
target_link_libraries( test_simple01 libcommon )

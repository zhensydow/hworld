file( GLOB SRC_SOURCES "*.cpp" "ent/*.cpp")

include_directories( . )
include_directories( ent )
include_directories( ${Boost_INCLUDE_DIR} )
include_directories( ${PROJECT_SOURCE_DIR} )
include_directories( ${PROJECT_SOURCE_DIR}/soil )
include_directories( ${LUA_INCLUDE_DIRS} )
include_directories( ${jsoncpp_INCLUDE_DIRS} )
include_directories( ${assimp_INCLUDE_DIRS} )

link_directories( ${Boost_LIBRARY_DIRS} )

add_executable( hworld ${SRC_SOURCES} )

add_definitions( -Wall -Wextra -std=c++11 )
#add_definitions( -Weffc++ )

if( CMAKE_BUILD_TYPE MATCHES RELEASE )
  add_definitions( -flto )
  add_definitions( -fomit-frame-pointer )
  add_definitions( -Wl,-O1 -Wl,--discard-all )
endif( CMAKE_BUILD_TYPE MATCHES RELEASE )

set_target_properties( hworld PROPERTIES LINK_FLAGS_RELEASE -flto )

target_link_libraries( hworld ${OPENGL_LIBRARIES} )
target_link_libraries( hworld ${SFML_LIBRARIES} )
target_link_libraries( hworld ${Boost_LIBRARIES})
target_link_libraries( hworld ${LUA_LIBRARIES} )
target_link_libraries( hworld ${jsoncpp_LIBRARIES} )
target_link_libraries( hworld ${assimp_LIBRARIES} )
target_link_libraries( hworld soil )

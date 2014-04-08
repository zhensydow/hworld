include_directories( . )
include_directories( ${PROJECT_SOURCE_DIR} )
include_directories( ${PROJECT_SOURCE_DIR}/common )
include_directories( ${jsoncpp_INCLUDE_DIRS} )

add_definitions( -Wall -Wextra -std=c++11 )
#add_definitions( -Weffc++ )

if( CMAKE_BUILD_TYPE MATCHES RELEASE )
  add_definitions( -flto )
  add_definitions( -fomit-frame-pointer )
  add_definitions( -Wl,-O1 -Wl,--discard-all )
endif( CMAKE_BUILD_TYPE MATCHES RELEASE )

add_executable( genhworld main_genhworld.cpp )

set_target_properties( genhworld PROPERTIES LINK_FLAGS_RELEASE -flto )

target_link_libraries( genhworld ${SFML_LIBRARIES} )
target_link_libraries( genhworld ${jsoncpp_LIBRARIES} )
target_link_libraries( genhworld libcommon )

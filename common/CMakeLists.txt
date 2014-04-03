file( GLOB LIBCOMMON_SOURCES "*.cpp" )

include_directories( . )
include_directories( ${PROJECT_SOURCE_DIR} )

add_definitions( -Wall -Wextra -std=c++11 )

if( CMAKE_BUILD_TYPE MATCHES RELEASE )
  add_definitions( -flto )
  add_definitions( -fomit-frame-pointer )
  add_definitions( -Wl,-O1 -Wl,--discard-all )
endif( CMAKE_BUILD_TYPE MATCHES RELEASE )

add_library( libcommon STATIC ${LIBCOMMON_SOURCES} )

set_target_properties( libcommon PROPERTIES LINK_FLAGS_RELEASE -flto )

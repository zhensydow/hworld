cmake_minimum_required( VERSION 2.8 )
set( PROJECT_NAME "hworld" )
project( ${PROJECT_NAME} )
enable_testing()
set( VERSION_MAJOR 0 )
set( VERSION_MINOR 1 )
set( VERSION_RELEASE 0 )

set( CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules" ${CMAKE_MODULE_PATH} )

find_package( OpenGL REQUIRED )
find_package( SFML 2.0 REQUIRED system window graphics )
find_package( Boost 1.52 COMPONENTS system filesystem REQUIRED )
find_package( LuaJIT REQUIRED )
find_package( Luabind REQUIRED )
set(LUA_INCLUDE_DIRS ${LuaJIT_INCLUDE_DIR} ${LUABIND_INCLUDE_DIR} )
set(LUA_LIBRARIES ${LuaJIT_LIBRARIES} ${LUABIND_LIBRARIES} )
find_package( jsoncpp REQUIRED )
find_package( assimp REQUIRED )

add_definitions( -O3 )
if( CMAKE_BUILD_TYPE MATCHES RELEASE )
  add_definitions( -march=native )
  add_definitions( -mtune=native )
endif( CMAKE_BUILD_TYPE MATCHES RELEASE )

add_subdirectory( soil )
add_subdirectory( common )
add_subdirectory( src )
add_subdirectory( tools )
add_subdirectory( test )

# documentation
find_package( Doxygen )
if( DOXYGEN_FOUND )
  find_package( Perl )
  set( DOXYGEN_INPUTS
    "${PROJECT_SOURCE_DIR}/doc ${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/src/ent " )
  set(DOXYGEN_DEFINES "")
  set(DOXYGEN_IMG_PATH "${PROJECT_SOURCE_DIR}/doc" )

  if( DOXYGEN_DOT_PATH )
    set( DOXYGEN_HAVE_DOT "YES" )
  else()
    set( DOXYGEN_HAVE_DOT "NO" )
  endif()

  configure_file( "${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in"
    "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile" @ONLY)
  add_custom_target(doc
    ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen" VERBATIM
    )
endif()

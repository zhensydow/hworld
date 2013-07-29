cmake_minimum_required( VERSION 2.8 )
set( PROJECT_NAME "hworld" )
project( ${PROJECT_NAME} )
set( VERSION_MAJOR 0 )
set( VERSION_MINOR 1 )
set( VERSION_RELEASE 0 )

set( CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH} )

find_package( OpenGL REQUIRED )
find_package( SFML 2.0 REQUIRED system window graphics )

add_subdirectory( src )


# documentation
find_package( Doxygen )
if( DOXYGEN_FOUND )
  find_package( Perl )
  set( DOXYGEN_INPUTS
    "${PROJECT_SOURCE_DIR}/doc ${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}" )
  set(DOXYGEN_DEFINES "")

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

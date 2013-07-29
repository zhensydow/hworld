cmake_minimum_required( VERSION 2.8 )
project( hworld )
set( hworld_VERSION_MAJOR 0 )
set( hworld_VERSION_MINOR 1 )

set( CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH} )

find_package( OpenGL REQUIRED )
find_package( SFML 2.0 REQUIRED system window graphics )

add_subdirectory( src )

# documentation
find_package(Doxygen)
if(DOXYGEN_FOUND)
  # set(DOXYGEN_INPUTS
  #   "${PROJECT_SOURCE_DIR}/doc/doxydoc ${PROJECT_SOURCE_DIR}/mongoc ${PROJECT_SOURCE_DIR}/common ${PROJECT_SOURCE_DIR}/machen ${PROJECT_SOURCE_DIR}/outcsv")
  # set(DOXYGEN_DEFINES "")

  configure_file( "${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in"
    "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile" @ONLY)
  add_custom_target(doc
    ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen" VERBATIM
    )
endif()

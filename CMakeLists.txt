cmake_minimum_required( VERSION 2.8 )
project( hworld )
set( hworld_VERSION_MAJOR 0 )
set( hworld_VERSION_MINOR 1 )

set( CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH} )

find_package( OpenGL REQUIRED )
find_package( SFML 2.0 REQUIRED system window graphics )

add_subdirectory( src )

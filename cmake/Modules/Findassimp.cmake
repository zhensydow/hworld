# - Try to find ImageMagick++
# Once done, this will define
#
#  assimp_FOUND - system has Assimp
#  assimp_INCLUDE_DIRS - the Assimp include directories
#  assimp_LIBRARIES - link these to use Assimp

include(LibFindMacros)

# Use pkg-config to get hints about paths
libfind_pkg_check_modules( assimp_PKGCONF assimp )

# Include dir
find_path( assimp_INCLUDE_DIR
  NAMES assimp/scene.h
  PATHS ${assimp_PKGCONF_INCLUDE_DIRS}
)

# Finally the library itself
find_library( assimp_LIBRARY
  NAMES assimp
  PATHS ${assimp_PKGCONF_LIBRARY_DIRS}
)

set( assimp_PROCESS_INCLUDES assimp_INCLUDE_DIR )
set( assimp_PROCESS_LIBS assimp_LIBRARY )
libfind_process( assimp )

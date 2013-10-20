# - Try to find ImageMagick++
# Once done, this will define
#
#  jsoncpp_FOUND - system has Magick++
#  jsoncpp_INCLUDE_DIRS - the Magick++ include directories
#  jsoncpp_LIBRARIES - link these to use Magick++

include(LibFindMacros)

# Use pkg-config to get hints about paths
libfind_pkg_check_modules( jsoncpp_PKGCONF jsoncpp )

# Include dir
find_path( jsoncpp_INCLUDE_DIR
  NAMES json/json.h
  PATHS ${jsoncpp_PKGCONF_INCLUDE_DIRS}
)

# Finally the library itself
find_library( jsoncpp_LIBRARY
  NAMES jsoncpp
  PATHS ${jsoncpp_PKGCONF_LIBRARY_DIRS}
)

set( jsoncpp_PROCESS_INCLUDES jsoncpp_INCLUDE_DIR )
set( jsoncpp_PROCESS_LIBS jsoncpp_LIBRARY )
libfind_process( jsoncpp )

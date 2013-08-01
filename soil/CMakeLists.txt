file( GLOB SOIL_SOURCES "*.c")

add_library( soil STATIC ${SOIL_SOURCES} )

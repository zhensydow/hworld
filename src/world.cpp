/** @file world.cpp
    @brief World Definition.
    @author Luis Cabellos
    @date 2013-09-01
*/
//------------------------------------------------------------------------------
#include "world.hpp"
#include "util.hpp"

//------------------------------------------------------------------------------
World::World(){
    // create a minimal world
    m_terrain[ 0 ] = createRandomChunk( -5, 5 );
}

//------------------------------------------------------------------------------
Chunk & World::getChunk( unsigned int idx ){
    return m_terrain[ idx ];
}

//------------------------------------------------------------------------------

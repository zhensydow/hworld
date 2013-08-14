/** @file util.cpp
    @brief Util functions.
    @author Luis Cabellos
    @date 2013-08-05
*/
//------------------------------------------------------------------------------
#include "util.hpp"
#include <random>

//------------------------------------------------------------------------------
Chunk createRandomChunk( int min, int max ){
    Chunk chunk;

    std::random_device rd;
    std::mt19937 gen( rd() );
    std::uniform_int_distribution<> dis( min, max );

    for( int i = 0 ; i < 7 ; ++i ){
        chunk.setHeight( i, dis( gen ) );
    }

    return chunk;
}

//------------------------------------------------------------------------------
ChunkProp createChunkProp( const Chunk & chunk ){
    ChunkProp cprop( chunk.m_heights );

    return cprop;
}

//------------------------------------------------------------------------------

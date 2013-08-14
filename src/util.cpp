/** @file util.cpp
    @brief Util functions.
    @author Luis Cabellos
    @date 2013-08-05
*/
//------------------------------------------------------------------------------
#include "util.hpp"
#include <random>

//------------------------------------------------------------------------------
Chunk createRandomChunk( float min, float max ){
    Chunk chunk;

    std::random_device rd;
    std::mt19937 gen( rd() );
    std::uniform_real_distribution<> dis( min, max );

    for( int i = 0 ; i < 7 ; ++i ){
        chunk.setHeight( 0, dis( gen ) );
    }

    return chunk;
}

//------------------------------------------------------------------------------


/** @file util.hpp
    @brief Util functions.
    @author Luis Cabellos
    @date 2013-08-05
*/
//------------------------------------------------------------------------------
#ifndef UTIL_HPP_
#define UTIL_HPP_

//------------------------------------------------------------------------------
#include "chunk.hpp"
#include "chunkprop.hpp"

//------------------------------------------------------------------------------
Chunk createRandomChunk( int min, int max );
ChunkProp createChunkProp( const Chunk & chunk );

//------------------------------------------------------------------------------
#endif//UTIL_HPP_

//------------------------------------------------------------------------------

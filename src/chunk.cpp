/** @file chunk.cpp
    @brief Chunk class definition.
    @author Luis Cabellos
    @date 2013-08-05
*/
//------------------------------------------------------------------------------
#include "chunk.hpp"

//------------------------------------------------------------------------------
Chunk::Chunk(){
    std::fill( m_neighbours.begin(), m_neighbours.end(), CHUNK_NULL_IDX );
}

//------------------------------------------------------------------------------

/** @file chunk.cpp
    @brief Chunk class definition.
    @author Luis Cabellos
    @date 2013-08-05
*/
//------------------------------------------------------------------------------
#include "chunk.hpp"

//------------------------------------------------------------------------------
ChunkProp Chunk::createProp(){
    ChunkProp cprop( this->m_heights );

    return cprop;
}

//------------------------------------------------------------------------------

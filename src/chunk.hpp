/** @file chunk.hpp
    @brief Chunk Class Definition.
    @author Luis Cabellos
    @date 2013-08-05
*/
//------------------------------------------------------------------------------
#ifndef CHUNK_HPP_
#define CHUNK_HPP_

//------------------------------------------------------------------------------
#include <array>
#include "chunkprop.hpp"

//------------------------------------------------------------------------------
class Chunk{
public:
    ChunkProp createProp();

    void setHeight( unsigned int i, const float val );

private:
    std::array<float,7> m_heights;
};

//------------------------------------------------------------------------------
inline
void Chunk::setHeight( unsigned int i, const float val ){
    m_heights[ i ] = val;
}

//------------------------------------------------------------------------------
#endif//CHUNK_HPP_

//------------------------------------------------------------------------------

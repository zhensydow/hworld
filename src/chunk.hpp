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

//------------------------------------------------------------------------------
class Chunk{
public:
    constexpr static unsigned int NTILES = 7;

    void setHeight( unsigned int i, const int val );

    std::array< int, NTILES > m_heights;
};

//------------------------------------------------------------------------------
inline
void Chunk::setHeight( unsigned int i, const int val ){
    if( i < NTILES ){
        m_heights[ i ] = val;
    }
}

//------------------------------------------------------------------------------
#endif//CHUNK_HPP_

//------------------------------------------------------------------------------

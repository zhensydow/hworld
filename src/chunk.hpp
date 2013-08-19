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
#include "gfxinc.hpp"

//------------------------------------------------------------------------------
class Chunk{
public:
    constexpr static unsigned int NTILES = 7;
    constexpr static unsigned int VERTS_TILE = 6;
    constexpr static float STEP_SIZE = 0.2f;

    void setHeight( unsigned int i, const int val );

    std::array< int, NTILES > m_heights;
};

//------------------------------------------------------------------------------
constexpr GLfloat sqrt3 = sqrt( 3 );
constexpr GLfloat TileCZ = 0.5 * sqrt3;
constexpr GLfloat TileCX = 0.5;

//------------------------------------------------------------------------------
constexpr std::array< GLfloat, Chunk::VERTS_TILE*2 > TilePos{ {
        -TileCX, -TileCZ, TileCX, -TileCZ, 1.0f, 0.0f,
            TileCX, TileCZ, -TileCX, TileCZ, -1.0f, 0.0f } };

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

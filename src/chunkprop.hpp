/** @file chunkprop.hpp
    @brief ChunkProp class declaration.
    @author Luis Cabellos
    @date 2013-08-05
*/
//------------------------------------------------------------------------------
#ifndef CHUNKPROP_HPP_
#define CHUNKPROP_HPP_

//------------------------------------------------------------------------------
#include <array>
#include "gfxinc.hpp"
#include "chunk.hpp"

//------------------------------------------------------------------------------
class ChunkProp{
public:
    ChunkProp( const std::array<int,7> & heigths );
    void draw();

private:
    constexpr static int m_numVertex = 6*7;
    constexpr static int m_numTris = 4*7;

    std::array< GLuint, 3 > m_buffers;
    std::array< GLfloat, m_numVertex*3 > m_vertexData;
    std::array< GLfloat, m_numVertex*2 > m_uvData;
    std::array< GLushort, m_numTris*3 > m_elemData;
};

//------------------------------------------------------------------------------
#endif//CHUNKPROP_HPP_

//------------------------------------------------------------------------------

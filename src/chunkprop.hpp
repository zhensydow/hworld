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

//------------------------------------------------------------------------------
class ChunkProp{
public:
    ChunkProp( const std::array<int,7> & heigths );
    void draw();

private:
    std::array< GLuint, 3 > m_buffers;
    std::array< GLfloat, 3*3 > m_vertexData;
    std::array< GLfloat, 3*2 > m_uvData;
    std::array< GLushort, 3 > m_elemData;
};

//------------------------------------------------------------------------------
#endif//CHUNKPROP_HPP_

//------------------------------------------------------------------------------

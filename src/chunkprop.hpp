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
class Renderer;

//------------------------------------------------------------------------------
class ChunkProp{
public:
    ChunkProp( const std::array< int, Chunk::NTILES> & heigths );
    void draw( Renderer & renderer );

    constexpr static unsigned int VERTS_TILE = 6;
    constexpr static unsigned int TRIS_TILE = 4;
    constexpr static unsigned int FACES_TILE = 6;
    constexpr static unsigned int VERTS_FACE = 4;
    constexpr static unsigned int TRIS_FACE = 2;

    constexpr static unsigned int m_numVertex = Chunk::NTILES*VERTS_TILE;
    constexpr static unsigned int m_numTris = Chunk::NTILES*TRIS_TILE;
    constexpr static unsigned int m_numFaceVerts =
        Chunk::NTILES*FACES_TILE*VERTS_FACE;
    constexpr static unsigned int m_numFaceTris =
        Chunk::NTILES*FACES_TILE*TRIS_FACE;

    std::array< GLuint, 3 > m_buffers;
    std::array< GLfloat, m_numVertex*3 > m_vertexData;
    std::array< GLfloat, m_numVertex*2 > m_uvData;
    std::array< GLushort, m_numTris*3 > m_elemData;

    std::array< GLuint, 3 > m_faceBuffers;
    std::array< GLfloat, m_numFaceVerts*3 > m_faceVerts;
    std::array< GLfloat, m_numFaceVerts*2 > m_faceUVs;
    std::array< GLushort, m_numFaceTris*3 > m_faceTris;
};

//------------------------------------------------------------------------------
#endif//CHUNKPROP_HPP_

//------------------------------------------------------------------------------

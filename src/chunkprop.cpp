/** @file chunkprop.cpp
    @brief ChunkProp class definition.
    @author Luis Cabellos
    @date 2013-08-05
*/
//------------------------------------------------------------------------------
#include "chunkprop.hpp"
#include <algorithm>
#include "renderer.hpp"

//------------------------------------------------------------------------------
using namespace std;

//------------------------------------------------------------------------------
std::array< GLuint, 2 > ChunkProp::s_floorBuffers;
std::array< GLfloat, ChunkProp::m_numFloorVerts*3 > ChunkProp::s_floorVerts;
std::array< GLushort, ChunkProp::m_numFloorTris*3 > ChunkProp::s_floorTris;

//------------------------------------------------------------------------------
void ChunkProp::setupCommon(){
    // generate floor
    glGenBuffers( s_floorBuffers.size(), &s_floorBuffers[0] );

    glm::vec2 offset;
    for( unsigned int tile = 0 ; tile < Chunk::NTILES - 1 ; ++tile ){
        offset = glm::rotate( glm::vec2( 0, -sqrt3 ), 60.0f * tile );

        for( unsigned int i = 0 ; i < 3 ; ++i ){
            auto dst = (tile*3 + i)*3;
            auto src0 = ((tile + i + (Chunk::VERTS_TILE-1))
                         % Chunk::VERTS_TILE)*2;

            s_floorVerts[ dst + 0 ] = TilePos[ src0 ] + offset.x;
            s_floorVerts[ dst + 1 ] = 0.0f;
            s_floorVerts[ dst + 2 ] = TilePos[ src0 + 1 ] + offset.y;
        }

        auto dst = tile * 2 * 3;
        auto src0 = tile * 3;
        auto srcN = (src0 + 3) % (Chunk::VERTS_TILE*3);

        s_floorTris[ dst + 0 ] = src0;
        s_floorTris[ dst + 1 ] = src0 + 1;
        s_floorTris[ dst + 2 ] = src0 + 2;
        s_floorTris[ dst + 3 ] = src0;
        s_floorTris[ dst + 4 ] = src0 + 2;
        s_floorTris[ dst + 5 ] = srcN;
    }

    auto dst = 2 * (Chunk::NTILES - 1) * 3;
    s_floorTris[ dst + 0 ] = 0;
    s_floorTris[ dst + 1 ] = 3;
    s_floorTris[ dst + 2 ] = 6;

    s_floorTris[ dst + 3 ] = 0;
    s_floorTris[ dst + 4 ] = 6;
    s_floorTris[ dst + 5 ] = 9;

    s_floorTris[ dst + 6 ] = 0;
    s_floorTris[ dst + 7 ] = 9;
    s_floorTris[ dst + 8 ] = 12;

    s_floorTris[ dst + 9 ] = 0;
    s_floorTris[ dst + 10 ] = 12;
    s_floorTris[ dst + 11 ] = 15;

    // send buffers to openGL
    glBindBuffer( GL_ARRAY_BUFFER, s_floorBuffers[0] );
    glBufferData( GL_ARRAY_BUFFER, s_floorVerts.size()*sizeof(GLfloat),
                  &s_floorVerts[0], GL_STATIC_DRAW );

    glBindBuffer( GL_ARRAY_BUFFER, 0 );

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, s_floorBuffers[1] );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, s_floorTris.size()*sizeof(GLushort),
                  &s_floorTris[0], GL_STATIC_DRAW );

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
}

//------------------------------------------------------------------------------
ChunkProp::ChunkProp(){
    Chunk chunk;
    setup( chunk );
}

//------------------------------------------------------------------------------
ChunkProp::ChunkProp( const Chunk & chunk ){
    setup( chunk );
}

//------------------------------------------------------------------------------
void ChunkProp::setup( const Chunk & chunk ){
    auto heigths = chunk.m_heights;

    // generate tiles
    glGenBuffers( 3, &m_buffers[0] );
    glm::vec2 offset;
    GLfloat h;
    for( unsigned int tile = 0 ; tile < Chunk::NTILES ; ++tile ){
        if( tile == 0 ){
            offset = glm::vec2( 0, 0 );
        }else{
            offset = glm::rotate( glm::vec2( 0, -sqrt3 ),
                                  60.0f * (tile - 1) );
        }

        h = heigths[tile] * Chunk::STEP_SIZE;

        for( unsigned int vert = 0 ; vert < Chunk::VERTS_TILE ; ++vert ){
            auto pvert = tile*Chunk::VERTS_TILE + vert;
            auto dst0 = pvert*3;
            auto dst1 = pvert*2;

            m_vertexData[ dst0 ] = TilePos[ vert*2 ] + offset.x;
            m_vertexData[ dst0 + 1 ] = h;
            m_vertexData[ dst0 + 2 ] = TilePos[ vert*2 + 1 ] + offset.y;

            m_uvData[ dst1 ] = m_vertexData[ dst0 ];
            m_uvData[ dst1 + 1 ] = m_vertexData[ dst0 + 2 ];
        }

        for( unsigned int tri = 0 ; tri < TRIS_TILE ; ++tri ){
            auto p = (tile*TRIS_TILE + tri)*3;

            m_elemData[ p ] = tile*Chunk::VERTS_TILE;
            m_elemData[ p + 1 ] = tile*Chunk::VERTS_TILE + tri + 2;
            m_elemData[ p + 2 ] = tile*Chunk::VERTS_TILE + tri + 1;
        }
    }

    // generate lateral faces
    auto minimun = heigths[0];
    for( unsigned int i = 1 ; i < Chunk::NTILES ; ++i ){
        minimun = min( minimun, heigths[i] );
    }
    GLfloat minh = (minimun - 1) * Chunk::STEP_SIZE;

    glGenBuffers( 3, &m_faceBuffers[0] );

    for( unsigned int tile = 0 ; tile < Chunk::NTILES ; ++tile ){
        if( tile == 0 ){
            offset = glm::vec2( 0, 0 );
        }else{
            offset = glm::rotate( glm::vec2( 0, -sqrt3 ),
                                  60.0f * (tile - 1) );
        }

        h = heigths[tile] * Chunk::STEP_SIZE;
        auto uvh = abs( heigths[tile] * Chunk::STEP_SIZE - minh );

        for( unsigned int face = 0 ; face < FACES_TILE ; ++face ){
            auto pface = tile*FACES_TILE + face;
            auto src0 = face*2;
            auto src1 = ((face+1) % Chunk::VERTS_TILE)*2;
            auto dst = pface*VERTS_FACE*3;

            m_faceVerts[ dst + 0 ] = TilePos[ src0 ] + offset.x;
            m_faceVerts[ dst + 1 ] = h;
            m_faceVerts[ dst + 2 ] = TilePos[ src0 + 1 ] + offset.y;
            m_faceVerts[ dst + 3 ] = TilePos[ src1 ] + offset.x;
            m_faceVerts[ dst + 4 ] = h;
            m_faceVerts[ dst + 5 ] = TilePos[ src1 + 1 ] + offset.y;
            m_faceVerts[ dst + 6 ] = TilePos[ src0 ] + offset.x;
            m_faceVerts[ dst + 7 ] = minh;
            m_faceVerts[ dst + 8 ] = TilePos[ src0 + 1 ] + offset.y;
            m_faceVerts[ dst + 9 ] = TilePos[ src1 ] + offset.x;
            m_faceVerts[ dst + 10 ] = minh;
            m_faceVerts[ dst + 11 ] = TilePos[ src1 + 1 ] + offset.y;

            dst = pface*VERTS_FACE*2;

            m_faceUVs[ dst + 0 ] = 0.0f;
            m_faceUVs[ dst + 1 ] = uvh;
            m_faceUVs[ dst + 2 ] = 1.0f;
            m_faceUVs[ dst + 3 ] = uvh;
            m_faceUVs[ dst + 4 ] = 0.0f;
            m_faceUVs[ dst + 5 ] = 0.0f;
            m_faceUVs[ dst + 6 ] = 1.0f;
            m_faceUVs[ dst + 7 ] = 0.0f;

            auto src = pface*VERTS_FACE;
            dst = pface*TRIS_FACE*3;

            m_faceTris[ dst + 0 ] = src;
            m_faceTris[ dst + 1 ] = src + 1;
            m_faceTris[ dst + 2 ] = src + 3;
            m_faceTris[ dst + 3 ] = src;
            m_faceTris[ dst + 4 ] = src + 3;
            m_faceTris[ dst + 5 ] = src + 2;
        }
    }

    // send buffers to openGL
    glBindBuffer( GL_ARRAY_BUFFER, m_buffers[0] );
    glBufferData( GL_ARRAY_BUFFER, m_vertexData.size()*sizeof(GLfloat),
                  &m_vertexData[0], GL_STATIC_DRAW );

    glBindBuffer( GL_ARRAY_BUFFER, m_buffers[1] );
    glBufferData( GL_ARRAY_BUFFER, m_uvData.size()*sizeof(GLfloat),
                  &m_uvData[0], GL_STATIC_DRAW );

    glBindBuffer( GL_ARRAY_BUFFER, m_faceBuffers[0] );
    glBufferData( GL_ARRAY_BUFFER, m_faceVerts.size()*sizeof(GLfloat),
                  &m_faceVerts[0], GL_STATIC_DRAW );

    glBindBuffer( GL_ARRAY_BUFFER, m_faceBuffers[1] );
    glBufferData( GL_ARRAY_BUFFER, m_faceUVs.size()*sizeof(GLfloat),
                  &m_faceUVs[0], GL_STATIC_DRAW );

    glBindBuffer( GL_ARRAY_BUFFER, 0 );

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_buffers[2] );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, m_elemData.size()*sizeof(GLushort),
                  &m_elemData[0], GL_STATIC_DRAW );

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_faceBuffers[2] );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, m_faceTris.size()*sizeof(GLushort),
                  &m_faceTris[0], GL_STATIC_DRAW );

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );

    // setup positions
    m_floorPos = glm::vec3( 0.0f, minh, 0.0f);
}

//------------------------------------------------------------------------------
void ChunkProp::draw( Renderer & renderer ){
    renderer.render( *this );
}

//------------------------------------------------------------------------------

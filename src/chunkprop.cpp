/** @file chunkprop.cpp
    @brief ChunkProp class definition.
    @author Luis Cabellos
    @date 2013-08-05
*/
//------------------------------------------------------------------------------
#include "chunkprop.hpp"
#include <algorithm>

//------------------------------------------------------------------------------
using namespace std;

//------------------------------------------------------------------------------
ChunkProp::ChunkProp( const array< int,Chunk::NTILES > & heigths ){
    // Generate buffers
    glGenBuffers( 3, &m_buffers[0] );

    // template tile
    constexpr GLfloat sqrt3 = sqrt( 3 );
    constexpr GLfloat cz = 0.5 * sqrt3;
    constexpr GLfloat cx = 0.5;

    constexpr array< GLfloat, VERTS_TILE*2 > vpos{ {
            -cx, -cz, cx, -cz, 1.0f, 0.0f,
                cx, cz, -cx, cz, -1.0f, 0.0f } };

    // generate tiles
    glm::vec2 offset;
    GLfloat h;
    for( unsigned int tile = 0 ; tile < Chunk::NTILES ; ++tile ){
        if( tile == 0 ){
            offset = glm::vec2( 0, 0 );
        }else{
            offset = glm::rotate( glm::vec2( 0, -sqrt3 ),
                                  60.0f * (tile - 1) );
        }

        h = heigths[tile] * 0.1f;

        for( unsigned int vert = 0 ; vert < VERTS_TILE ; ++vert ){
            auto pvert = tile*VERTS_TILE + vert;
            auto dst0 = pvert*3;
            auto dst1 = pvert*2;

            m_vertexData[ dst0 ] = vpos[ vert*2 ] + offset.x;
            m_vertexData[ dst0 + 1 ] = h;
            m_vertexData[ dst0 + 2 ] = vpos[ vert*2 + 1 ] + offset.y;

            m_uvData[ dst1 ] = m_vertexData[ dst0 ];
            m_uvData[ dst1 + 1 ] = m_vertexData[ dst0 + 2 ];
        }

        for( unsigned int tri = 0 ; tri < TRIS_TILE ; ++tri ){
            auto p = (tile*TRIS_TILE + tri)*3;

            m_elemData[ p ] = tile*VERTS_TILE;
            m_elemData[ p + 1 ] = tile*VERTS_TILE + tri + 2;
            m_elemData[ p + 2 ] = tile*VERTS_TILE + tri + 1;
        }
    }

    // generate lateral faces
    auto minimun = heigths[0];
    for( unsigned int i = 1 ; i < Chunk::NTILES ; ++i ){
        minimun = min( minimun, heigths[i] );
    }
    GLfloat minh = minimun * 0.1f - 0.1f;;

    // Generate buffers
    glGenBuffers( 3, &m_faceBuffers[0] );

    for( unsigned int tile = 0 ; tile < Chunk::NTILES ; ++tile ){
        h = abs( heigths[tile] * 0.1f - minh );

        for( unsigned int face = 0 ; face < FACES_TILE ; ++face ){
            auto pface = tile*FACES_TILE + face;
            auto src0 = face + tile*VERTS_TILE;
            auto src1 = (face+1) % VERTS_TILE + tile*FACES_TILE;
            auto dst = pface*VERTS_FACE*3;

            m_faceVerts[ dst + 0 ] = m_vertexData[ src0*3 + 0 ];
            m_faceVerts[ dst + 1 ] = m_vertexData[ src0*3 + 1 ];
            m_faceVerts[ dst + 2 ] = m_vertexData[ src0*3 + 2 ];
            m_faceVerts[ dst + 3 ] = m_vertexData[ src1*3 + 0 ];
            m_faceVerts[ dst + 4 ] = m_vertexData[ src1*3 + 1 ];
            m_faceVerts[ dst + 5 ] = m_vertexData[ src1*3 + 2 ];
            m_faceVerts[ dst + 6 ] = m_vertexData[ src0*3 + 0 ];
            m_faceVerts[ dst + 7 ] = minh;
            m_faceVerts[ dst + 8 ] = m_vertexData[ src0*3 + 2 ];
            m_faceVerts[ dst + 9 ] = m_vertexData[ src1*3 + 0 ];
            m_faceVerts[ dst + 10 ] = minh;
            m_faceVerts[ dst + 11 ] = m_vertexData[ src1*3 + 2 ];

            dst = pface*VERTS_FACE*2;

            m_faceUVs[ dst + 0 ] = 0.0f;
            m_faceUVs[ dst + 1 ] = 0.0f;
            m_faceUVs[ dst + 2 ] = 1.0f;
            m_faceUVs[ dst + 3 ] = 0.0;
            m_faceUVs[ dst + 4 ] = 0.0f;
            m_faceUVs[ dst + 5 ] = h;
            m_faceUVs[ dst + 6 ] = 1.0f;
            m_faceUVs[ dst + 7 ] = h;

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
}

//------------------------------------------------------------------------------
void ChunkProp::draw(){
    glEnableVertexAttribArray( 0 );
    glBindBuffer( GL_ARRAY_BUFFER, m_buffers[0] );
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, nullptr );

    glEnableVertexAttribArray( 1 );
    glBindBuffer( GL_ARRAY_BUFFER, m_buffers[1] );
    glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 0, nullptr );

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_buffers[2] );

    glDrawElements( GL_TRIANGLES, m_elemData.size(), GL_UNSIGNED_SHORT, nullptr);

    glEnableVertexAttribArray( 0 );
    glBindBuffer( GL_ARRAY_BUFFER, m_faceBuffers[0] );
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, nullptr );

    glEnableVertexAttribArray( 1 );
    glBindBuffer( GL_ARRAY_BUFFER, m_faceBuffers[1] );
    glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 0, nullptr );

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_faceBuffers[2] );

    glUniform1i( 1, 1 );

    glDrawElements( GL_TRIANGLES, m_faceTris.size(), GL_UNSIGNED_SHORT, nullptr);

    glBindBuffer( GL_ARRAY_BUFFER, 0 );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
}

//------------------------------------------------------------------------------

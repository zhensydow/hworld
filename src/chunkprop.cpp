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

    // fillup the data
    constexpr GLfloat sqrt3 = sqrt( 3 );
    constexpr GLfloat cz = 0.5 * sqrt3;
    constexpr GLfloat cx = 0.5;

    constexpr array< GLfloat, VERTS_TILE*2 > vpos{ {
            -cx, -cz, cx, -cz, 1.0f, 0.0f,
                cx, cz, -cx, cz, -1.0f, 0.0f } };

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

        for( unsigned int i = 0 ; i < VERTS_TILE ; ++i ){
            auto p = tile*VERTS_TILE*3;

            m_vertexData[ p + i*3 ] = vpos[ i*2 ] + offset.x;
            m_vertexData[ p + i*3 + 1 ] = h;
            m_vertexData[ p + i*3 + 2 ] = vpos[ i*2 + 1 ] + offset.y;
        }
    }

    for( unsigned int i = 0 ; i < Chunk::NTILES*VERTS_TILE ; ++i ){
        m_uvData[ i*2 ] = m_vertexData[ i*3 ];
        m_uvData[ i*2 + 1 ] = m_vertexData[ i*3 + 2 ];
    }

    for( unsigned int tile = 0 ; tile < Chunk::NTILES ; ++tile ){
        for( unsigned int i = 0 ; i < TRIS_TILE ; ++i ){
            auto p = tile*TRIS_TILE*3;

            m_elemData[ p + i*3 ] = tile*VERTS_TILE;
            m_elemData[ p + i*3 + 1 ] = tile*VERTS_TILE + i + 2;
            m_elemData[ p + i*3 + 2 ] = tile*VERTS_TILE + i + 1;
        }
    }

    auto minimun = heigths[0];
    for( unsigned int i = 1 ; i < Chunk::NTILES ; ++i ){
        minimun = min( minimun, heigths[i] );
    }
    GLfloat minh = minimun * 0.1f - 0.1f;;

    for( unsigned int tile = 0 ; tile < Chunk::NTILES ; ++tile ){
        h = abs( heigths[tile] * 0.1f - minh );

        for( unsigned int face = 0 ; face < FACES_TILE ; ++face ){
            auto pface = tile*FACES_TILE + face;
            auto src0 = face + tile*VERTS_TILE;
            auto src1 = (face+1) % VERTS_TILE + tile*FACES_TILE;
            auto dst = Chunk::NTILES*VERTS_TILE*3 + pface*VERTS_FACE*3;

            m_vertexData[ dst + 0 ] = m_vertexData[ src0*3 + 0 ];
            m_vertexData[ dst + 1 ] = m_vertexData[ src0*3 + 1 ];
            m_vertexData[ dst + 2 ] = m_vertexData[ src0*3 + 2 ];
            m_vertexData[ dst + 3 ] = m_vertexData[ src1*3 + 0 ];
            m_vertexData[ dst + 4 ] = m_vertexData[ src1*3 + 1 ];
            m_vertexData[ dst + 5 ] = m_vertexData[ src1*3 + 2 ];
            m_vertexData[ dst + 6 ] = m_vertexData[ src0*3 + 0 ];
            m_vertexData[ dst + 7 ] = minh;
            m_vertexData[ dst + 8 ] = m_vertexData[ src0*3 + 2 ];
            m_vertexData[ dst + 9 ] = m_vertexData[ src1*3 + 0 ];
            m_vertexData[ dst + 10 ] = minh;
            m_vertexData[ dst + 11 ] = m_vertexData[ src1*3 + 2 ];

            dst = Chunk::NTILES*VERTS_TILE*2 + pface*VERTS_FACE*2;

            m_uvData[ dst + 0 ] = 0.0f;
            m_uvData[ dst + 1 ] = 0.0f;
            m_uvData[ dst + 2 ] = 1.0f;
            m_uvData[ dst + 3 ] = 0.0;
            m_uvData[ dst + 4 ] = 0.0f;
            m_uvData[ dst + 5 ] = h;
            m_uvData[ dst + 6 ] = 1.0f;
            m_uvData[ dst + 7 ] = h;

            auto src = Chunk::NTILES*VERTS_TILE + pface*VERTS_FACE;
            dst = Chunk::NTILES*TRIS_TILE*3 + pface*TRIS_FACE*3;

            m_elemData[ dst + 0 ] = src;
            m_elemData[ dst + 1 ] = src + 1;
            m_elemData[ dst + 2 ] = src + 3;
            m_elemData[ dst + 3 ] = src;
            m_elemData[ dst + 4 ] = src + 3;
            m_elemData[ dst + 5 ] = src + 2;
        }
    }

    // send buffers to openGL
    glBindBuffer( GL_ARRAY_BUFFER, m_buffers[0] );
    glBufferData( GL_ARRAY_BUFFER, m_vertexData.size()*sizeof(GLfloat),
                  &m_vertexData[0], GL_STATIC_DRAW );

    glBindBuffer( GL_ARRAY_BUFFER, m_buffers[1] );
    glBufferData( GL_ARRAY_BUFFER, m_uvData.size()*sizeof(GLfloat),
                  &m_uvData[0], GL_STATIC_DRAW );

    glBindBuffer( GL_ARRAY_BUFFER, 0 );

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_buffers[2] );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, m_elemData.size()*sizeof(GLushort),
                  &m_elemData[0], GL_STATIC_DRAW );

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

    glBindBuffer( GL_ARRAY_BUFFER, 0 );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
}

//------------------------------------------------------------------------------

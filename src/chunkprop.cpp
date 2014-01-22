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

std::array< GLuint, 3 > ChunkProp::s_tileBuffers;
std::array< GLfloat, Chunk::VERTS_TILE*3 > ChunkProp::s_tileVerts;
std::array< GLfloat, Chunk::VERTS_TILE*2 > ChunkProp::s_tileUVs;
std::array< GLushort, ChunkProp::TRIS_TILE*3 > ChunkProp::s_tileTris;
std::array< GLushort, ChunkProp::m_numFaceTris*3 > ChunkProp::s_faceTris;
GLuint ChunkProp::s_faceTrisBuffer;


//------------------------------------------------------------------------------
void ChunkProp::setupCommon(){
    // generate base tile
    glGenBuffers( s_tileBuffers.size(), &s_tileBuffers[0] );

    for( unsigned int vert = 0 ; vert < Chunk::VERTS_TILE ; ++vert ){
        auto dst0 = vert*3;
        auto dst1 = vert*2;

        s_tileVerts[ dst0 ] = TilePos[ vert*2 ];
        s_tileVerts[ dst0 + 1 ] = 0.0f;
        s_tileVerts[ dst0 + 2 ] = TilePos[ vert*2 + 1 ];

        s_tileUVs[ dst1 ] = s_tileVerts[ dst0 ];
        s_tileUVs[ dst1 + 1 ] = s_tileVerts[ dst0 + 2 ];
    }

    for( unsigned int tri = 0 ; tri < TRIS_TILE ; ++tri ){
        auto p = tri*3;

        s_tileTris[ p ] = 0;
        s_tileTris[ p + 1 ] = tri + 2;
        s_tileTris[ p + 2 ] = tri + 1;
    }

    // generate floor
    glm::vec2 offset;

    glGenBuffers( s_floorBuffers.size(), &s_floorBuffers[0] );

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

    for( auto i = 0 ; i < 4; ++i ){
        auto dst = (2 * (Chunk::NTILES - 1) + i) * 3;
        s_floorTris[ dst + 0 ] = 0;
        s_floorTris[ dst + 1 ] = ( i + 1 )*3;
        s_floorTris[ dst + 2 ] = ( i + 2 )*3;
    }

    // generate face tris
    glGenBuffers( 1, &s_faceTrisBuffer );
    for( unsigned int tile = 0 ; tile < Chunk::NTILES ; ++tile ){
        for( unsigned int face = 0 ; face < FACES_TILE ; ++face ){
            auto pface = tile*FACES_TILE + face;
            auto dst = pface*TRIS_FACE*3;
            auto src = pface*VERTS_FACE;

            s_faceTris[ dst + 0 ] = src;
            s_faceTris[ dst + 1 ] = src + 1;
            s_faceTris[ dst + 2 ] = src + 3;
            s_faceTris[ dst + 3 ] = src;
            s_faceTris[ dst + 4 ] = src + 3;
            s_faceTris[ dst + 5 ] = src + 2;
        }
    }

    // send buffers to openGL
    glBindBuffer( GL_ARRAY_BUFFER, s_floorBuffers[0] );
    glBufferData( GL_ARRAY_BUFFER, s_floorVerts.size()*sizeof(GLfloat),
                  &s_floorVerts[0], GL_STATIC_DRAW );

    glBindBuffer( GL_ARRAY_BUFFER, s_tileBuffers[0] );
    glBufferData( GL_ARRAY_BUFFER, s_tileVerts.size()*sizeof(GLfloat),
                  &s_tileVerts[0], GL_STATIC_DRAW );

    glBindBuffer( GL_ARRAY_BUFFER, s_tileBuffers[1] );
    glBufferData( GL_ARRAY_BUFFER, s_tileUVs.size()*sizeof(GLfloat),
                  &s_tileUVs[0], GL_STATIC_DRAW );

    glBindBuffer( GL_ARRAY_BUFFER, 0 );

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, s_floorBuffers[1] );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, s_floorTris.size()*sizeof(GLushort),
                  &s_floorTris[0], GL_STATIC_DRAW );

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, s_tileBuffers[2] );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, s_tileTris.size()*sizeof(GLushort),
                  &s_tileTris[0], GL_STATIC_DRAW );

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, s_faceTrisBuffer );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, s_faceTris.size()*sizeof(GLushort),
                  &s_faceTris[0], GL_STATIC_DRAW );

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

    // generate tile positions
    glm::vec2 offset;
    for( unsigned int tile = 0 ; tile < Chunk::NTILES ; ++tile ){
        if( tile == 0 ){
            offset = glm::vec2( 0, 0 );
        }else{
            offset = glm::rotate( glm::vec2( 0, -sqrt3 ),
                                  60.0f * (tile - 1) );
        }

        m_tilePos[ tile ] = glm::vec3( offset.x,
                                       heigths[tile] * Chunk::STEP_SIZE,
                                       offset.y );
    }

    // generate lateral faces
    auto minimun = heigths[0];
    for( unsigned int i = 1 ; i < Chunk::NTILES ; ++i ){
        minimun = min( minimun, heigths[i] );
    }
    GLfloat minh = (minimun - 1) * Chunk::STEP_SIZE;

    glGenBuffers( m_faceBuffers.size(), &m_faceBuffers[0] );

    for( unsigned int tile = 0 ; tile < Chunk::NTILES ; ++tile ){
        if( tile == 0 ){
            offset = glm::vec2( 0, 0 );
        }else{
            offset = glm::rotate( glm::vec2( 0, -sqrt3 ),
                                  60.0f * (tile - 1) );
        }

        auto h = heigths[tile] * Chunk::STEP_SIZE;
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

            auto p0 = glm::vec3( m_faceVerts[ dst + 0 ],
                                 m_faceVerts[ dst + 1 ],
                                 m_faceVerts[ dst + 2 ] );
            auto p1 = glm::vec3( m_faceVerts[ dst + 3 ],
                                 m_faceVerts[ dst + 4 ],
                                 m_faceVerts[ dst + 5 ] );
            auto p2 = glm::vec3( m_faceVerts[ dst + 6 ],
                                 m_faceVerts[ dst + 7 ],
                                 m_faceVerts[ dst + 8 ] );

            auto n = glm::normalize(glm::cross(p0 - p2, p1 - p2));

            for( unsigned int k = 0 ; k < VERTS_FACE ; ++k ){
                m_faceNorms[ dst + k*3 + 0 ] = n.x;
                m_faceNorms[ dst + k*3 + 1 ] = n.y;
                m_faceNorms[ dst + k*3 + 2 ] = n.z;
            }

            dst = pface*VERTS_FACE*2;

            m_faceUVs[ dst + 0 ] = 0.0f;
            m_faceUVs[ dst + 1 ] = uvh;
            m_faceUVs[ dst + 2 ] = 1.0f;
            m_faceUVs[ dst + 3 ] = uvh;
            m_faceUVs[ dst + 4 ] = 0.0f;
            m_faceUVs[ dst + 5 ] = 0.0f;
            m_faceUVs[ dst + 6 ] = 1.0f;
            m_faceUVs[ dst + 7 ] = 0.0f;
        }
    }

    // send buffers to openGL
    glBindBuffer( GL_ARRAY_BUFFER, m_faceBuffers[0] );
    glBufferData( GL_ARRAY_BUFFER, m_faceVerts.size()*sizeof(GLfloat),
                  &m_faceVerts[0], GL_STATIC_DRAW );

    glBindBuffer( GL_ARRAY_BUFFER, m_faceBuffers[1] );
    glBufferData( GL_ARRAY_BUFFER, m_faceNorms.size()*sizeof(GLfloat),
                  &m_faceNorms[0], GL_STATIC_DRAW );

    glBindBuffer( GL_ARRAY_BUFFER, m_faceBuffers[2] );
    glBufferData( GL_ARRAY_BUFFER, m_faceUVs.size()*sizeof(GLfloat),
                  &m_faceUVs[0], GL_STATIC_DRAW );

    glBindBuffer( GL_ARRAY_BUFFER, 0 );

    // setup positions
    m_floorPos = glm::vec3( 0.0f, minh, 0.0f);
}

//------------------------------------------------------------------------------
void ChunkProp::draw( Renderer & renderer ){
    renderer.render( *this );
}

//------------------------------------------------------------------------------

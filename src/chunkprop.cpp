/** @file chunkprop.cpp
    @brief ChunkProp class definition.
    @author Luis Cabellos
    @date 2013-08-05
*/
//------------------------------------------------------------------------------
#include "chunkprop.hpp"

//------------------------------------------------------------------------------
ChunkProp::ChunkProp( const std::array<int,7> & heigths ){
    // Generate buffers
    glGenBuffers( 3, &m_buffers[0] );

    // fillup the data
    constexpr GLfloat sqrt3 = sqrt( 3 );
    constexpr GLfloat cz = 0.5 * sqrt3;
    constexpr GLfloat cx = 0.5;

    constexpr std::array< GLfloat,12 > vpos{ {
            -cx, -cz, cx, -cz, 1.0f, 0.0f,
                cx, cz, -cx, cz, -1.0f, 0.0f } };

    glm::vec2 offset;
    GLfloat h;
    for( auto tile = 0 ; tile < 7 ; ++tile ){
        if( tile == 0 ){
            offset = glm::vec2( 0, 0 );
        }else{
            offset = glm::rotate( glm::vec2( 0, -sqrt3 ),
                                  60.0f * (tile - 1) );
        }

        h = heigths[tile] * 0.1f;

        for( int i = 0 ; i < 6 ; ++i ){
            auto p = 6*3 * tile;

            m_vertexData[ p + i*3 ] = vpos[ i*2 ] + offset.x;
            m_vertexData[ p + i*3 + 1 ] = h;
            m_vertexData[ p + i*3 + 2 ] = vpos[ i*2 + 1 ] + offset.y;
        }
    }

    for( unsigned int i = 0 ; i < Chunk::NTILES*6 ; ++i ){
        m_uvData[ i*2 ] = m_vertexData[ i*3 ];
        m_uvData[ i*2 + 1 ] = m_vertexData[ i*3 + 2 ];
    }

    for( unsigned int tile = 0 ; tile < Chunk::NTILES ; ++tile ){
        for( int i = 0 ; i < 4 ; ++i ){
            auto p = 4*3*tile;

            m_elemData[ p + i*3 ] = 6*tile;
            m_elemData[ p + i*3 + 1 ] = 6*tile + i + 2;
            m_elemData[ p + i*3 + 2 ] = 6*tile + i + 1;
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

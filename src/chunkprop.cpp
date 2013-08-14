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
    for( size_t i = 0 ; i < m_elemData.size() ; ++i ){
        m_elemData[ i ] = i;
    }

    m_vertexData[ 0 ] = -1.0f;
    m_vertexData[ 1 ] = -1.0f;
    m_vertexData[ 2 ] = 0.0f;
    m_vertexData[ 3 ] = 1.0f;
    m_vertexData[ 4 ] = -1.0f;
    m_vertexData[ 5 ] = 0.0f;
    m_vertexData[ 6 ] = 0.0f;
    m_vertexData[ 7 ] = 1.0f;
    m_vertexData[ 8 ] = 0.0f;

    m_uvData[ 0 ] = 0.0f;
    m_uvData[ 1 ] = 0.0f;
    m_uvData[ 2 ] = 0.0f;
    m_uvData[ 3 ] = 1.0f;
    m_uvData[ 4 ] = 1.0f;
    m_uvData[ 5 ] = 1.0f;

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

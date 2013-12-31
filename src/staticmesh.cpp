/** @file staticmesh.cpp
    @brief StaticMesh definitions.
    @author Luis Cabellos
    @date 2013-12-31
*/
//------------------------------------------------------------------------------
#include "staticmesh.hpp"
#include "renderer.hpp"

//------------------------------------------------------------------------------
void StaticMesh::setupGL(){
    // generate mesh buffers
    glGenBuffers( m_meshBuffers.size(), &m_meshBuffers[0] );

    // send buffers to openGL
    glBindBuffer( GL_ARRAY_BUFFER, m_meshBuffers[0] );
    glBufferData( GL_ARRAY_BUFFER, m_verts.size()*sizeof(GLfloat),
                  &m_verts[0], GL_STATIC_DRAW );

    glBindBuffer( GL_ARRAY_BUFFER, 0 );

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_meshBuffers[1] );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, m_tris.size()*sizeof(GLushort),
                  &m_tris[0], GL_STATIC_DRAW );

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
}

//------------------------------------------------------------------------------
void StaticMesh::draw( Renderer & renderer ){
    renderer.render( *this );
}

//------------------------------------------------------------------------------

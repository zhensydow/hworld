/*------------------------------------------------------------------------------
    Copyright 2014, HexWorld Authors.

    This file is part of HexWorld.

    HexWorld is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    HexWorld is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with HexWorld.  If not, see <http://www.gnu.org/licenses/>.
------------------------------------------------------------------------------*/
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

    glBindBuffer( GL_ARRAY_BUFFER, m_meshBuffers[1] );
    glBufferData( GL_ARRAY_BUFFER, m_normals.size()*sizeof(GLfloat),
                  &m_normals[0], GL_STATIC_DRAW );

    glBindBuffer( GL_ARRAY_BUFFER, 0 );

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_meshBuffers[2] );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, m_tris.size()*sizeof(GLushort),
                  &m_tris[0], GL_STATIC_DRAW );

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
}

//------------------------------------------------------------------------------
void StaticMesh::draw( const Material & mat, Renderer & renderer ){
    renderer.render( mat, *this );
}

//------------------------------------------------------------------------------

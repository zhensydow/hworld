/**
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
**/
/** @file renderer3d.cpp
    @brief Renderer 3D definitions.
    @author Luis Cabellos
    @date 2014-01-26
*/
//------------------------------------------------------------------------------
#include "renderer3d.hpp"
#include "material.hpp"
#include "staticmesh.hpp"
#include "shader.hpp"
#include "engine.hpp"

//------------------------------------------------------------------------------
Renderer3D::Renderer3D(){
    auto & engine = Engine::instance();

    m_objmat_prg = loadProgram( engine.getDataFilename( "shaders/objmat" ) );
}

//------------------------------------------------------------------------------
void Renderer3D::render( const Material & material, const StaticMesh & mesh ){
    auto matrix_id = glGetUniformLocation( m_objmat_prg, "MVP");
    auto matrix_M_id = glGetUniformLocation( m_objmat_prg, "M");
    auto matrix_V_id = glGetUniformLocation( m_objmat_prg, "V");
    auto diffuse_id = glGetUniformLocation( m_objmat_prg, "diffuse");
    auto lightDir_id = glGetUniformLocation( m_objmat_prg, "lightDir");

    glUseProgram( m_objmat_prg );

    const auto & difc = material.getDiffuse();
    glUniform3fv( diffuse_id, 1, &difc[0] );
    glUniform3fv( lightDir_id, 1, &sundir[0] );

    auto & mod = getModel();
    auto m_mvp = proj * view * mod;
    glUniformMatrix4fv( matrix_id, 1, GL_FALSE, &m_mvp[0][0] );
    glUniformMatrix4fv( matrix_M_id, 1, GL_FALSE, &mod[0][0] );
    glUniformMatrix4fv( matrix_V_id, 1, GL_FALSE, &view[0][0] );

    glEnableVertexAttribArray( 0 );
    glBindBuffer( GL_ARRAY_BUFFER, mesh.vertsBuff() );
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, nullptr );

    glEnableVertexAttribArray( 1 );
    glBindBuffer( GL_ARRAY_BUFFER, mesh.normalsBuff() );
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, nullptr );

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, mesh.trisBuff() );

    glDrawElements( GL_TRIANGLES, mesh.trisSize(),
                    GL_UNSIGNED_SHORT, nullptr);

    glBindBuffer( GL_ARRAY_BUFFER, 0 );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
    glBindTexture( GL_TEXTURE_2D, 0 );
    glDisableVertexAttribArray( 0 );
    glDisableVertexAttribArray( 1 );

    glUseProgram( 0 );
}

//------------------------------------------------------------------------------

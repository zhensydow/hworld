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
/** @file renderer.cpp
    @brief Renderer Definition.
    @author Luis Cabellos
    @date 2013-08-19
*/
//------------------------------------------------------------------------------
#include "renderer.hpp"
#include "chunkprop.hpp"
#include "shader.hpp"
#include "terminal.hpp"
#include "staticmesh.hpp"
#include "material.hpp"
#include "engine.hpp"

//------------------------------------------------------------------------------
//void Renderer::render( const ChunkProp & chunkprop ){
    // auto matrix_id = glGetUniformLocation( m_chk_tile_prg , "MVP");
    // auto matrix_M_id = glGetUniformLocation( m_chk_tile_prg, "M");
    // auto matrix_V_id = glGetUniformLocation( m_chk_tile_prg, "V");
    // auto lightDir_id = glGetUniformLocation( m_chk_tile_prg, "lightDir");
    // auto offset_id = glGetUniformLocation( m_chk_tile_prg , "offset");
    // auto texture_id = glGetUniformLocation( m_chk_tile_prg , "texSampler");

    // glUseProgram( m_chk_tile_prg );

    // glUniform3fv( lightDir_id, 1, &m_sundir[0] );

    // glActiveTexture( GL_TEXTURE0 );
    // glBindTexture( GL_TEXTURE_2D, m_tex_2d0 );
    // glUniform1i( texture_id, 0 );

    // glEnableVertexAttribArray( 0 );
    // glBindBuffer( GL_ARRAY_BUFFER, chunkprop.tileVertsBuff() );
    // glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, nullptr );

    // glEnableVertexAttribArray( 1 );
    // glBindBuffer( GL_ARRAY_BUFFER, chunkprop.tileUVBuff() );
    // glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 0, nullptr );

    // glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, chunkprop.tileTrisBuff() );

    // auto chunkPos = chunkprop.getPosition();
    // auto model = glm::mat4(1.0f);

    // glUniformMatrix4fv( matrix_V_id, 1, GL_FALSE, &view[0][0] );

    // for( unsigned i = 0 ; i < Chunk::NTILES ; ++i ){
    //     auto pos = chunkprop.tilePos( i );
    //     model = glm::translate( pos + chunkPos );
    //     m_mvp = proj * view * model;
    //     glUniformMatrix4fv( matrix_id, 1, GL_FALSE, &m_mvp[0][0] );
    //     glUniformMatrix4fv( matrix_M_id, 1, GL_FALSE, &model[0][0] );
    //     glUniform2f( offset_id, pos.x, pos.z );
    //     glDrawElements( GL_TRIANGLES, chunkprop.tileTrisSize(),
    //                     GL_UNSIGNED_SHORT, nullptr);
    // }

    // matrix_id = glGetUniformLocation( m_chk_wall_prg, "MVP");
    // matrix_M_id = glGetUniformLocation( m_chk_wall_prg, "M");
    // matrix_V_id = glGetUniformLocation( m_chk_wall_prg, "V");
    // lightDir_id = glGetUniformLocation( m_chk_wall_prg, "lightDir");
    // texture_id = glGetUniformLocation( m_chk_wall_prg, "texSampler");
    // glUseProgram( m_chk_wall_prg );

    // glUniform3fv( lightDir_id, 1, &m_sundir[0] );

    // glActiveTexture( GL_TEXTURE0 );
    // glBindTexture( GL_TEXTURE_2D, m_tex_2d1 );

    // glUniform1i( texture_id, 0 );

    // glEnableVertexAttribArray( 0 );
    // glBindBuffer( GL_ARRAY_BUFFER, chunkprop.faceVertsBuff() );
    // glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, nullptr );

    // glEnableVertexAttribArray( 1 );
    // glBindBuffer( GL_ARRAY_BUFFER, chunkprop.faceUVBuff() );
    // glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 0, nullptr );

    // glEnableVertexAttribArray( 2 );
    // glBindBuffer( GL_ARRAY_BUFFER, chunkprop.faceNormsBuff() );
    // glVertexAttribPointer( 2, 3, GL_FLOAT, GL_FALSE, 0, nullptr );

    // glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, chunkprop.faceTrisBuff() );

    // model = glm::translate( chunkPos );
    // m_mvp = proj * view * model;
    // glUniformMatrix4fv( matrix_id, 1, GL_FALSE, &m_mvp[0][0] );
    // glUniformMatrix4fv( matrix_M_id, 1, GL_FALSE, &model[0][0] );
    // glUniformMatrix4fv( matrix_V_id, 1, GL_FALSE, &view[0][0] );
    // glDrawElements( GL_TRIANGLES, chunkprop.faceTrisSize(),
    //                 GL_UNSIGNED_SHORT, nullptr);

    // glDisableVertexAttribArray( 3 );
    // glBindTexture( GL_TEXTURE_2D, 0 );

    // matrix_id = glGetUniformLocation( m_chk_floor_prg, "MVP");

    // glUseProgram( m_chk_floor_prg );

    // model = glm::translate( chunkprop.floorPos() + chunkPos );
    // m_mvp = proj * view * model;
    // glUniformMatrix4fv( matrix_id, 1, GL_FALSE, &m_mvp[0][0] );

    // glEnableVertexAttribArray( 0 );
    // glBindBuffer( GL_ARRAY_BUFFER, chunkprop.floorVertsBuff() );
    // glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, nullptr );

    // glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, chunkprop.floorTrisBuff() );

    // glDrawElements( GL_TRIANGLES, chunkprop.floorTrisSize(),
    //                 GL_UNSIGNED_SHORT, nullptr);

    // glBindBuffer( GL_ARRAY_BUFFER, 0 );
    // glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
    // glBindTexture( GL_TEXTURE_2D, 0 );
    // glDisableVertexAttribArray( 0 );
    // glDisableVertexAttribArray( 1 );
    // glUseProgram( 0 );
    //}

//------------------------------------------------------------------------------
//void Renderer::render( const Material & material, const StaticMesh & mesh ){
    // auto matrix_id = glGetUniformLocation( m_objmat_prg, "MVP");
    // auto matrix_M_id = glGetUniformLocation( m_objmat_prg, "M");
    // auto matrix_V_id = glGetUniformLocation( m_objmat_prg, "V");
    // auto diffuse_id = glGetUniformLocation( m_objmat_prg, "diffuse");
    // auto lightDir_id = glGetUniformLocation( m_objmat_prg, "lightDir");

    // glUseProgram( m_objmat_prg );

    // const auto & difc = material.getDiffuse();
    // glUniform3fv( diffuse_id, 1, &difc[0] );
    // glUniform3fv( lightDir_id, 1, &m_sundir[0] );

    // auto & mod = getModel();
    // m_mvp = proj * view * mod;
    // glUniformMatrix4fv( matrix_id, 1, GL_FALSE, &m_mvp[0][0] );
    // glUniformMatrix4fv( matrix_M_id, 1, GL_FALSE, &mod[0][0] );
    // glUniformMatrix4fv( matrix_V_id, 1, GL_FALSE, &view[0][0] );

    // glEnableVertexAttribArray( 0 );
    // glBindBuffer( GL_ARRAY_BUFFER, mesh.vertsBuff() );
    // glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, nullptr );

    // glEnableVertexAttribArray( 1 );
    // glBindBuffer( GL_ARRAY_BUFFER, mesh.normalsBuff() );
    // glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, nullptr );

    // glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, mesh.trisBuff() );

    // glDrawElements( GL_TRIANGLES, mesh.trisSize(),
    //                 GL_UNSIGNED_SHORT, nullptr);

    // glBindBuffer( GL_ARRAY_BUFFER, 0 );
    // glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
    // glBindTexture( GL_TEXTURE_2D, 0 );
    // glDisableVertexAttribArray( 0 );
    // glDisableVertexAttribArray( 1 );

    // glUseProgram( 0 );
//}

//------------------------------------------------------------------------------

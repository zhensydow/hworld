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
/** @file renderer3d.hpp
    @brief Renderer 3D definition.
    @author Luis Cabellos
    @date 2014-01-26
*/
//------------------------------------------------------------------------------
#ifndef RENDERER3D_HPP_
#define RENDERER3D_HPP_

//------------------------------------------------------------------------------
#include "renderer.hpp"

//------------------------------------------------------------------------------
class Renderer3D : public Renderer{
public:
    Renderer3D();

    void render( const ChunkProp & chunkprop ) override;
    void render( const Material & material, const StaticMesh & mesh ) override;

    glm::mat4 view;
    glm::mat4 proj;
    glm::vec3 sundir;

private:
    GLuint m_tex_2d0;
    GLuint m_tex_2d1;

    GLuint m_chk_wall_prg;
    GLuint m_chk_tile_prg;
    GLuint m_chk_floor_prg;

    GLuint m_objmat_prg;
};

//------------------------------------------------------------------------------
#endif//RENDERER3D_HPP_

//------------------------------------------------------------------------------

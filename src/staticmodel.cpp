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
/** @file staticmodel.cpp
    @brief StaticModel definitions.
    @author Luis Cabellos
    @date 2014-01-03
*/
//------------------------------------------------------------------------------
#include "staticmodel.hpp"

//------------------------------------------------------------------------------
void StaticModel::insertNullMaterial(){
    Material mat;
    mat.setDiffuse( glm::vec3( 0.8, 0, 0.8 ) );
    insertMaterial( std::move(mat) );
}

//------------------------------------------------------------------------------
void StaticModel::draw( Renderer & renderer ){
    for( auto & mesh: m_meshes ){
        const auto & mat = m_materials[ mesh->getMaterialIdx() ];
        mesh->draw( mat, renderer );
    }
}

//------------------------------------------------------------------------------

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
/** @file staticmodel.hpp
    @brief StaticModel declarations.
    @author Luis Cabellos
    @date 2014-01-02
*/
//------------------------------------------------------------------------------
#ifndef STATICMODEL_HPP_
#define STATICMODEL_HPP_

//------------------------------------------------------------------------------
#include <memory>
#include "staticmesh.hpp"
#include "material.hpp"

//------------------------------------------------------------------------------
class StaticModel {
public:
    void insertMesh( std::unique_ptr<StaticMesh> mesh );
    void insertMaterial( Material && material );
    void insertNullMaterial();
    void draw( Renderer & renderer );

    unsigned int getNumMaterials() const noexcept;

private:
    std::vector< std::unique_ptr<StaticMesh> > m_meshes;
    std::vector< Material > m_materials;
};

//------------------------------------------------------------------------------
inline
void StaticModel::insertMesh( std::unique_ptr<StaticMesh> mesh ){
    if( mesh ){
        m_meshes.push_back( std::move(mesh) );
    }
}

//------------------------------------------------------------------------------
inline
void StaticModel::insertMaterial( Material && material ){
    m_materials.push_back( std::move(material) );
}

//------------------------------------------------------------------------------
inline
unsigned int StaticModel::getNumMaterials() const noexcept{
    return m_materials.size();
}

//------------------------------------------------------------------------------
#endif//STATICMODEL_HPP_

//------------------------------------------------------------------------------

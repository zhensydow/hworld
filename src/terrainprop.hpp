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
/** @file terrainprop.hpp
     @brief TerrainProp declaration.
     @author Luis Cabellos
     @date 2013-09-01
 */
//------------------------------------------------------------------------------
#ifndef TERRAINPROP_HPP_
#define TERRAINPROP_HPP_

//------------------------------------------------------------------------------
#include <unordered_map>
#include <memory>

//------------------------------------------------------------------------------
class World;
class Renderer;
class ChunkProp;

//------------------------------------------------------------------------------
class TerrainProp{
public:
    TerrainProp( World & world );

    void setFocus( unsigned int index );

    void draw( Renderer & renderer );

private:
    World & m_world;

    std::unordered_map< unsigned int, std::shared_ptr< ChunkProp > > m_chunks;
};

//------------------------------------------------------------------------------
#endif//TERRAINPROP_HPP_

//------------------------------------------------------------------------------

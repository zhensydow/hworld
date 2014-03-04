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
#include "chunk.hpp"

//------------------------------------------------------------------------------
class World;
class Renderer;
class ChunkProp;

//------------------------------------------------------------------------------
class TerrainProp{
public:
    TerrainProp( World & world );

    ChunkID getFocus() const;
    void setFocus( ChunkID index );

    void draw( Renderer & renderer );

    std::shared_ptr<ChunkProp> getChunkProp( ChunkID chunk );

private:
    World & m_world;

    ChunkID m_focus {CHUNK_NULL_IDX};

    std::unordered_map< ChunkID, std::shared_ptr<ChunkProp> > m_chunks;
};

//------------------------------------------------------------------------------
inline
ChunkID TerrainProp::getFocus() const{
    return m_focus;
}

//------------------------------------------------------------------------------
#endif//TERRAINPROP_HPP_

//------------------------------------------------------------------------------

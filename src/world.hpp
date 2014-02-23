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
/** @file world.hpp
    @brief World Declaration.
    @author Luis Cabellos
    @date 2013-09-01
*/
//------------------------------------------------------------------------------
#ifndef WORLD_HPP_
#define WORLD_HPP_

//------------------------------------------------------------------------------
#include <unordered_map>
#include "chunk.hpp"

//------------------------------------------------------------------------------
class World{
public:
    World();

    bool hasChunk( unsigned int ) const;
    Chunk & getChunk( unsigned int );

    bool hasEntity( unsigned int chunk, unsigned int tile ) const;
    bool insertEntity( unsigned int chunk, unsigned int tile, unsigned int id );

    const std::unordered_map< unsigned int, Chunk> & getTerrain() const;

private:
    std::unordered_map< unsigned int, Chunk> m_terrain;
};

//------------------------------------------------------------------------------
inline
const std::unordered_map< unsigned int, Chunk> & World::getTerrain() const{
    return m_terrain;
}

//------------------------------------------------------------------------------
#endif//WORLD_HPP_

//------------------------------------------------------------------------------

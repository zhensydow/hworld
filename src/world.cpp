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
/** @file world.cpp
    @brief World Definition.
    @author Luis Cabellos
    @date 2013-09-01
*/
//------------------------------------------------------------------------------
#include "world.hpp"
#include "util.hpp"

//------------------------------------------------------------------------------
World::World(){
    // create a minimal world
    m_terrain[ 0 ] = createRandomChunk( -5, 5 );
    m_terrain[ 1 ] = createRandomChunk( -3, 3 );
    m_terrain[ 2 ] = createRandomChunk( -3, 3 );
    m_terrain[ 3 ] = createRandomChunk( -3, 3 );
    m_terrain[ 4 ] = createRandomChunk( -3, 3 );
    m_terrain[ 5 ] = createRandomChunk( -3, 3 );
    m_terrain[ 6 ] = createRandomChunk( -3, 3 );
    m_terrain[ 0 ].m_neighbours[ 0 ] = 1;
    m_terrain[ 0 ].m_neighbours[ 1 ] = 2;
    m_terrain[ 0 ].m_neighbours[ 2 ] = 3;
    m_terrain[ 0 ].m_neighbours[ 3 ] = 4;
    m_terrain[ 0 ].m_neighbours[ 4 ] = 5;
    m_terrain[ 0 ].m_neighbours[ 5 ] = 6;
}

//------------------------------------------------------------------------------
bool World::hasChunk( unsigned int idx ) const{
    return m_terrain.find( idx ) != m_terrain.end();
}

//------------------------------------------------------------------------------
Chunk & World::getChunk( unsigned int idx ){
    return m_terrain[ idx ];
}

//------------------------------------------------------------------------------
bool World::insertEntity( unsigned int idx, unsigned int tile, unsigned int id ){
    auto chunk = m_terrain.find( idx );
    if( chunk != m_terrain.end() ){
        return chunk->second.insertEntity( tile, id );
    }

    return false;
}

//------------------------------------------------------------------------------
bool World::hasEntity( unsigned int idx, unsigned int tile ) const {
    auto chunk = m_terrain.find( idx );
    if( chunk != m_terrain.end() ){
        return chunk->second.hasEntity( tile );
    }

    return false;
}

//------------------------------------------------------------------------------

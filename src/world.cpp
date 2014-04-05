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
/** @file world.cpp
    @brief World Definition.
    @author Luis Cabellos
    @date 2013-09-01
*/
//------------------------------------------------------------------------------
#include "world.hpp"
#include "glminc.hpp"
#include "constants.hpp"
#include "util.hpp"
#include "debug.hpp"

//------------------------------------------------------------------------------
World::World(){
    // create a minimal world
    m_quad = createWorldQuad( 3, glm::vec2(-10.0, -10.0),
                              glm::vec2(10.0, 10.0) );
    assert( m_quad && "Can't create World Quad" );

    auto chunk00 = createRandomChunk( 0, 50 );
    addChunk( 0, chunk00 );
    auto inserted = m_quad->addChunk( 0, m_terrain[0].m_pos );
    if( not inserted ){
        logW( "Chunk ", 0, " not inserted" );
    }

    for( ChunkID i = 1 ; i < 7 ; ++i ){
        auto chunk = createRandomChunk( 0, 3 );
        addChunk( i, chunk );
        linkChunks( 0, i-1, i );
        inserted = m_quad->addChunk( i, m_terrain[i].m_pos );
        if( not inserted ){
            logW( "Chunk ", i, " not inserted" );
        }
    }

    for( ChunkID i = 7 ; i < 13 ; ++i ){
        auto chunk = createRandomChunk( -3, 3 );
        addChunk( i, chunk );
        linkChunks( i-6, i-7, i );
        inserted = m_quad->addChunk( i, m_terrain[i].m_pos );
        if( not inserted ){
            logW( "Chunk ", i, " not inserted" );
        }
    }

    for( ChunkID i = 13 ; i < 19 ; ++i ){
        auto chunk = createRandomChunk( -3, 1 );
        addChunk( i, chunk );
        linkChunks( i-12, (i-12)%6, i );
        inserted = m_quad->addChunk( i, m_terrain[i].m_pos );
        if( not inserted ){
            logW( "Chunk ", i, " not inserted" );
        }
    }

    m_quad->printDebug();
}

//------------------------------------------------------------------------------
void World::addChunk( ChunkID idx, Chunk chunk ){
    m_terrain[ idx ] = chunk;
}

//------------------------------------------------------------------------------
void World::linkChunks( ChunkID root, unsigned int tile, ChunkID branch ){
    constexpr GLfloat sqrt3 = sqrt( 3 );

    if( tile < 6 and hasChunk( root ) and hasChunk( branch ) ){
        auto tileBranch = (tile + 3) % 6;
        auto & rootChunk = m_terrain[root];

        rootChunk.m_neighbours[ tile ] = branch;

        auto & branchChunk = m_terrain[branch];
        auto offset = glm::rotate( glm::vec2( 1.5, -(5./2.)*sqrt3 ),
                                   sixthPart * tile );
        branchChunk.m_pos = rootChunk.m_pos + offset;
        branchChunk.m_neighbours[ tileBranch ] = root;
    }
}

//------------------------------------------------------------------------------
bool World::hasChunk( ChunkID idx ) const{
    return m_terrain.find( idx ) != m_terrain.end();
}

//------------------------------------------------------------------------------
Chunk & World::getChunk( ChunkID idx ){
    return m_terrain[ idx ];
}

//------------------------------------------------------------------------------
bool World::insertEntity( ChunkID idx, unsigned int tile, EntityID id ){
    auto chunk = m_terrain.find( idx );
    if( chunk != m_terrain.end() ){
        return chunk->second.insertEntity( tile, id );
    }

    return false;
}

//------------------------------------------------------------------------------
bool World::hasEntity( ChunkID idx, unsigned int tile ) const {
    auto chunk = m_terrain.find( idx );
    if( chunk != m_terrain.end() ){
        return chunk->second.hasEntity( tile );
    }

    return false;
}

//------------------------------------------------------------------------------

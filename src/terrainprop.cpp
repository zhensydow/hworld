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
/** @file terrainprop.cpp
    @brief TerrainProp definition.
    @author Luis Cabellos
    @date 2013-09-01
*/
//------------------------------------------------------------------------------
#include "terrainprop.hpp"
#include <queue>
#include "chunkprop.hpp"
#include "world.hpp"
#include "util.hpp"
#include "renderer.hpp"
#include "debug.hpp"

//------------------------------------------------------------------------------
TerrainProp::TerrainProp( World & world ) : m_world(world) {
    ChunkProp::setupCommon();
}

//------------------------------------------------------------------------------
void TerrainProp::setFocus( unsigned int center ){
    auto queue = std::queue< std::pair< unsigned int, glm::vec3 > >();

    queue.emplace( std::make_pair( center, glm::vec3{0.0f, 0.0f, 0.0f} ) );

    m_chunks.clear();

    unsigned int idx;
    glm::vec3 pos;
    while( not queue.empty() and m_chunks.size() < 10 ){
        std::tie( idx, pos ) = queue.front();
        logI( "Inserted element: ", idx, " at (",
              pos.x, ", ", pos.y, ", ", pos.z, ")" );
        queue.pop();

        auto cit = m_chunks.find( idx );
        if( cit == m_chunks.end() ){
            auto chunk = m_world.getChunk( idx );
            auto cprop = std::make_shared<ChunkProp>( createChunkProp( chunk ) );

            cprop->setPosition( pos );

            m_chunks.emplace( std::make_pair( idx, cprop ) );
        }
    }

    m_focus = center;
}

//------------------------------------------------------------------------------
void TerrainProp::draw( Renderer & renderer ){
    for( auto & chunk: m_chunks ){
        renderer.render( *chunk.second );
    }
}

//------------------------------------------------------------------------------
